#include "sosdefines.h"
#include "lists.h"
#include "interrupt.h"

typedef enum _THREAD_STATE
{
    SosThreadRunning,
    SosThreadWaiting,
    SosThreadSleeping,
    SosThreadTerminated
} THREAD_STATE;

typedef struct _THREAD
{
    LIST_ENTRY Link;
    QWORD KernelStack;
    CONTEXT SavedContext;
    THREAD_STATE State;
    DWORD SleepSeconds;
    DWORD WaitingEventId;
    PVOID Stack;
} THREAD, *PTHREAD;

typedef struct _EVENT
{
    DWORD EventId;
    DWORD Signaled;
} EVENT, *PEVENT;

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

VOID
SosThreadSleep(
    DWORD NumberOfSeconds
);

VOID
SosThreadWaitForEvent(
    PEVENT Event
);

VOID
SosThreadCreateEvent(
    PEVENT Event
);

VOID
SosThreadSignalEvent(
    PEVENT Event
);