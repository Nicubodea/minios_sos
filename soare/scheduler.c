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
        PTHREAD pTerminated = NULL;

        while (list != &gThreadList)
        {
            PTHREAD pThr = (PTHREAD)CONTAINING_RECORD(list, THREAD, Link);

            list = list->Flink;

            if (pThr->State == SosThreadTerminated)
            {
                // should de-alloc thread
                pTerminated = pThr;
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

        if (pTerminated != NULL)
        {
            //SosVirtFreeVirtual(pTerminated->Stack, 'SStk');
            //SosVirtFreeVirtual(pTerminated, 'SThr');
        }

        if (!bAnyThreadsInList)
        {
            return;
        }
    }
    //printf("[INFO] Thread %x at rip %x", pSelectedThread, pSelectedThread->SavedContext.RegRip);

    //printf("[INFO] %x (%x)\n", CurrentContext->RegSs, CurrentContext->RegRsp);
    //printf("Current %x, selected: %x\n", currentThread, pSelectedThread);
    SosScheduleSaveCurrentThreadContext(CurrentContext, currentThread);

    SosScheduleLoadThreadContext(CurrentContext, pSelectedThread);

    //printf("[INFO] Writing the FS\n");
    __writefs((QWORD)pSelectedThread);

    //printf("[INFO] %x (%x)\n", pSelectedThread->SavedContext.RegSs, pSelectedThread->SavedContext.RegRsp);

    //printf("[INFO] gogogo\n");

   // printf("[INFO] Rip -> %x\n", CurrentContext->RegRip);
    
}