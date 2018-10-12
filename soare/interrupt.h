#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "sosdefines.h"

typedef struct _CONTEXT {

    QWORD RegRax;
    QWORD RegRbx;
    QWORD RegRcx;
    QWORD RegRdx;
    QWORD RegRsi;
    QWORD RegRdi;
    QWORD RegRbp;
    QWORD RegR8;
    QWORD RegR9;
    QWORD RegR10;
    QWORD RegR11;
    QWORD RegR12;
    QWORD RegR13;
    QWORD RegR14;
    QWORD RegR15;
    QWORD InterruptNumber;
    QWORD ErrorCode;
    QWORD RegRip;
    QWORD RegCs;
    QWORD RegRflags;
    QWORD RegRsp;
    QWORD RegSs;

} CONTEXT, *PCONTEXT;

typedef  VOID(*PFUNC_SosInterruptHandler) (
    PCONTEXT Context
    );

VOID
SosInitInterrupts(
    VOID
    );

BOOLEAN
SosRegisterInterrupt(
    DWORD InterruptNumber,
    PFUNC_SosInterruptHandler Handler
    );

VOID
SosDumpInterruptContext(
    PCONTEXT Context
    );

#endif