#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "sosdefines.h"

#define INTERRUPT_DE            0x0
#define INTERRUPT_DB            0x1
#define INTERRUPT_NMI           0x2
#define INTERRUPT_BP            0x3
#define INTERRUPT_OF            0x4
#define INTERRUPT_BR            0x5
#define INTERRUPT_UD            0x6
#define INTERRUPT_NM            0x7
#define INTERRUPT_DF            0x8
#define INTERRUPT_COPROCESSOR   0x9
#define INTERRUPT_TS            0xa
#define INTERRUPT_NP            0xb
#define INTERRUPT_SS            0xc
#define INTERRUPT_GP            0xd
#define INTERRUPT_PF            0xe
#define INTERRUPT_MF            0x10
#define INTERRUPT_AC            0x11
#define INTERRUPT_MC            0x12
#define INTERRUPT_XM            0x13
#define INTERRUPT_VE            0x14

#define INTERRUPT_TIMER             0x20
#define INTERRUPT_KEYBOARD          0x21

#define INTERRUPT_SPURIOUS_MASTER    0x27
#define INTERRUPT_SPURIOUS_SLAVE     0x2F

#define TYPE_TRAP               0xF
#define TYPE_INTERRUPT          0xE

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
    QWORD ErrorCode;
    QWORD InterruptNumber;
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
    PFUNC_SosInterruptHandler Handler,
    BYTE Type
    );

VOID
SosDumpInterruptContext(
    PCONTEXT Context
    );

#endif