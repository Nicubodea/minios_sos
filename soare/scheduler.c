#include "scheduler.h"
#include "lists.h"
#include "interrupt.h"
#include "threads.h"
#include "screen.h"
#include "mmap.h"

extern LIST_ENTRY gThreadList;
extern QWORD __rdrand();
extern QWORD __readfs();
extern VOID __writefs(QWORD fs);

VOID
SosScheduleSaveCurrentThreadContext(
    PCONTEXT Context,
    PTHREAD Thread
)
{
    // we may have a NULL current thread
    if (Thread == NULL)
    {
        return;
    }

    memcpy(&Thread->SavedContext, Context, sizeof(CONTEXT));
}

VOID
SosScheduleLoadThreadContext(
    PCONTEXT Context,
    PTHREAD Thread
)
{
    memcpy(Context, &Thread->SavedContext, sizeof(CONTEXT));
}


VOID
SosScheduleJobs(
    PCONTEXT CurrentContext
)
{
    PTHREAD currentThread = (PTHREAD)__readfs();
    LIST_ENTRY* list;
    BOOLEAN foundSchedule = FALSE;
    PTHREAD pSelectedThread = NULL;

    while (!foundSchedule)
    {
        list = gThreadList.Flink;

        BOOLEAN bAnyThreadsInList = FALSE;

        while (list != &gThreadList)
        {
            PTHREAD pThr = (PTHREAD)CONTAINING_RECORD(list, THREAD, Link);

            list = list->Flink;

            if (pThr->State != SosThreadRunning)
            {
                continue;
            }

            bAnyThreadsInList = TRUE;

            // magic
            if (__rdrand() % 33 == 0)
            {
                foundSchedule = TRUE;
                pSelectedThread = pThr;
            }
        }

        if (!bAnyThreadsInList)
        {
            printf("[ERROR] I don't have anything to schedule!\n");
            __cli();
            __halt();
            return;
        }
    }

    if (currentThread != NULL && currentThread->State == SosThreadTerminated)
    {
        RemoveEntryList(&currentThread->Link);

        // TODO: can't free stack if we are on that stack
        //SosVirtFreeVirtual(currentThread->Stack, 'SStk');
        SosVirtFreeVirtual(currentThread, 'SThr');
    }
    else
    {
        SosScheduleSaveCurrentThreadContext(CurrentContext, currentThread);
    }

    SosScheduleLoadThreadContext(CurrentContext, pSelectedThread);

    __writefs((QWORD)pSelectedThread);
    
}


VOID
SosScheduleAdjustSleepingThreads(
    VOID
)
{
    LIST_ENTRY* list;

    list = gThreadList.Flink;
    while (list != &gThreadList)
    {
        PTHREAD pThr = (PTHREAD)CONTAINING_RECORD(list, THREAD, Link);

        list = list->Flink;

        if (pThr->State == SosThreadSleeping)
        {
            pThr->SleepSeconds--;
            if (pThr->SleepSeconds == 0)
            {
                pThr->State = SosThreadRunning;
            }
        }
    }
}