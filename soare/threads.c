#include "threads.h"
#include "mmap.h"
#include "screen.h"

#define DEFAULT_STACK_SIZE      0x2000

extern QWORD __readfs();
extern VOID __writefs(QWORD fs);
extern VOID __cli();
extern VOID __sti();
extern VOID SosThreadStartup();

DWORD gEventId;

LIST_ENTRY gThreadList;

VOID
SosThreadInit(
    VOID
)
{
    InitializeListHead(&gThreadList);
    __writefs(0);
}

PTHREAD
SosThreadCreate(
    PFUNC_ThrFunc Function,
    PVOID Argument
)
{
    PTHREAD pThr = SosVirtAllocVirtual(sizeof(THREAD), 'SThr');

    pThr->KernelStack = KERNEL_BASE_VIRTUAL + STACK_BASE_OFFSET - 8;
    pThr->SavedContext.RegRax = (QWORD)Function;
    pThr->SavedContext.RegRcx = (QWORD)Argument;
    pThr->Stack = SosVirtAllocVirtual(DEFAULT_STACK_SIZE, 'SStk');
    pThr->SavedContext.RegRsp = (QWORD)pThr->Stack + DEFAULT_STACK_SIZE - 8;
    pThr->SavedContext.RegRip = (QWORD)SosThreadStartup;
    pThr->SavedContext.RegCs = 0x18;
    pThr->SavedContext.RegSs = 0x20;
    pThr->SavedContext.RegRflags = 0x2 | (1<<9); // reserved bit | IF

    pThr->State = SosThreadRunning;

    InsertTailList(&gThreadList, &pThr->Link);
    
    return pThr;
}


VOID
SosTerminateCurrentThread(
    VOID
)
{
    PTHREAD pThr = (PTHREAD)__readfs();

    // will be cleanup-ed by the scheduler
    pThr->State = SosThreadTerminated;

    while (TRUE)
    {
        __halt();
    }
}


VOID
SosThreadSleep(
    DWORD NumberOfSeconds
)
{
    PTHREAD pThr = (PTHREAD)__readfs();
 
    __cli();
    pThr->State = SosThreadSleeping;
    pThr->SleepSeconds = NumberOfSeconds;
    __sti();

    while (pThr->State == SosThreadSleeping)
    {
        __halt();
    }
}


VOID
SosThreadWaitForEvent(
    PEVENT Event
)
{
    PTHREAD pThr = (PTHREAD)__readfs();
    
wait_again:
    __cli();
    
    if (Event->Signaled == 1)
    {
        Event->Signaled = 0;
        __sti();
        goto _already_signaled;
    }

    pThr->State = SosThreadWaiting;
    pThr->WaitingEventId = Event->EventId;

    __sti();
    __halt();

    __cli();
    if (Event->Signaled == 0)
    {
        goto wait_again;
    }

    Event->Signaled = 0;
    __sti();

_already_signaled:
    
    return;
}


VOID
SosThreadCreateEvent(
    PEVENT Event
)
{
    Event->Signaled = 0;
    Event->EventId = gEventId;
    gEventId++;
}


VOID
SosThreadSignalEvent(
    PEVENT Event
)
{
    LIST_ENTRY* list;

    list = gThreadList.Flink;
    Event->Signaled = 1;
    while (list != &gThreadList)
    {
        PTHREAD pThr = (PTHREAD)CONTAINING_RECORD(list, THREAD, Link);

        list = list->Flink;

        if (pThr->State == SosThreadWaiting && pThr->WaitingEventId == Event->EventId)
        {
            pThr->State = SosThreadRunning;
        }
    }
}