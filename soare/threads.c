#include "threads.h"
#include "mmap.h"
#include "screen.h"

#define DEFAULT_STACK_SIZE      0x600

extern QWORD __readfs();
extern VOID __writefs(QWORD fs);
extern VOID __cli();
extern VOID __sti();
extern VOID SosThreadStartup();

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

    //printf("[INFO] stack base %x, rsp %x\n", pThr->Stack, pThr->SavedContext.RegRsp);

    //printf("Thr @ %x -> %x", pThr->SavedContext.RegRax, pThr->SavedContext.RegRcx);
    pThr->State = SosThreadRunning;

    if (__readfs() == 0)
    {
        __writefs((QWORD)pThr);
    }

    // disable interrupts as we don't want to be interrupted while we alter the thread list
    __cli();
    InsertTailList(&gThreadList, &pThr->Link);
    __sti();
    
    return pThr;
}


VOID
SosTerminateCurrentThread(
    VOID
)
{
    PTHREAD pThr = (PTHREAD)__readfs();
    printf("%x\n", pThr);

    // will be cleanup-ed by the scheduler
    //pThr->State = SosThreadTerminated;
    __halt();
}