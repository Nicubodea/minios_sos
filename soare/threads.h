#include "sosdefines.h"
#include "lists.h"
#include "interrupt.h"

typedef enum _THREAD_STATE
{
    SosThreadRunning,
    SosThreadWaiting,
    SosThreadTerminated
} THREAD_STATE;

typedef struct _THREAD
{
    LIST_ENTRY Link;
    QWORD KernelStack;
    CONTEXT SavedContext;
    THREAD_STATE State;
    PVOID Stack;
} THREAD, *PTHREAD;

typedef VOID(*PFUNC_ThrFunc)(PVOID Arg);

VOID
SosThreadInit(
    VOID
);

PTHREAD
SosThreadCreate(
    PFUNC_ThrFunc Function,
    PVOID Argument
);

VOID
SosTerminateCurrentThread(
    VOID
);