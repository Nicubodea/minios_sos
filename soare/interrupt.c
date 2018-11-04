#include "interrupt.h"
#include "screen.h"

#define INTERRUPT_HANDLE_SIZE 7

#pragma pack(push)
#pragma pack(1)
typedef struct _ISR {
    WORD Bits0_15;      // offset bits 0..15
    WORD Selector;      // a code segment selector in GDT or LDT
    BYTE Ist;           // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    BYTE TypeAttr;      // type and attributes
    WORD Bits16_31;     // offset bits 16..31
    DWORD Bits32_63;    // offset bits 32..63
    DWORD Zero;         // reserved
} ISR, *PISR;

typedef struct _IDTR
{
    WORD Limit;
    PISR Base;
} IDTR, *PIDTR;

typedef struct _ISR_DESCRIPTOR
{
    PFUNC_SosInterruptHandler Handler;
} ISR_DESCRIPTOR, *PISR_DESCRIPTOR;
#pragma pack(pop)

IDTR gIdtr;
ISR gIsrs[256];
ISR_DESCRIPTOR gDescriptors[256];

VOID
SosInitInterrupts(
    VOID
)
{
    gIdtr.Limit = 256 * 16;
    gIdtr.Base = gIsrs;

    __lidt(&gIdtr);
}


extern VOID AsmHandler();


BOOLEAN
SosRegisterInterrupt(
    DWORD InterruptNumber,
    PFUNC_SosInterruptHandler Handler,
    BYTE Type
)
{
    QWORD oldAddr = 0;

    oldAddr = gIsrs[InterruptNumber].Bits0_15 | (gIsrs[InterruptNumber].Bits16_31 << 16) | (((QWORD)gIsrs[InterruptNumber].Bits32_63) << 32LL);

    if (oldAddr != 0)
    {
        // don't overwrite interrupts
        return FALSE;
    }

    QWORD pAsmHandler = (QWORD)AsmHandler + INTERRUPT_HANDLE_SIZE * InterruptNumber;

    gIsrs[InterruptNumber].Bits0_15 = (QWORD)pAsmHandler & 0xFFFF;
    gIsrs[InterruptNumber].Bits16_31 = ((QWORD)pAsmHandler & 0xFFFF0000) >> 16;
    gIsrs[InterruptNumber].Bits32_63 = (((QWORD)pAsmHandler) & 0xFFFFFFFF00000000) >> 32LL;

    gIsrs[InterruptNumber].Selector = 0x18;
    gIsrs[InterruptNumber].TypeAttr = 0b10000000 | Type;

    gDescriptors[InterruptNumber].Handler = Handler;
    
    return TRUE;
}


VOID
SosGenericInterruptHandler(
    DWORD InterruptNumber,
    PCONTEXT Context
)
{
    if (gDescriptors[InterruptNumber].Handler == NULL)
    {
        SosDumpInterruptContext(Context);
        return;
    }
    gDescriptors[InterruptNumber].Handler(Context);
}


VOID
SosDumpInterruptContext(
    PCONTEXT Context
)
{
    printf("EXCEPTION #%x, error code: %x\n", Context->InterruptNumber, Context->ErrorCode);
    printf("~~~~DUMPING TRAPFRAME~~~~\n");
    printf("Rip: 0x%x\n", Context->RegRip);
    printf("Cs: 0x%x\n", Context->RegCs);
    printf("Rflags: 0x%x\n", Context->RegRflags);
    printf("Rsp: 0x%x\n", Context->RegRsp);
    printf("Ss: 0x%x\n", Context->RegSs);
    printf("~~~~DUMPING GPRS~~~~\n");
    printf("Cr2: 0x%x\n", Context->RegCr2);
    printf("Rax: 0x%x\n", Context->RegRax);
    printf("Rbx: 0x%x\n", Context->RegRbx);
    printf("Rcx: 0x%x\n", Context->RegRcx);
    printf("Rdx: 0x%x\n", Context->RegRdx);
    printf("Rbp: 0x%x\n", Context->RegRbp);
    printf("Rsi: 0x%x\n", Context->RegRsi);
    printf("Rdi: 0x%x\n", Context->RegRdi);
    printf("R8: 0x%x\n", Context->RegR8);
    printf("R9: 0x%x\n", Context->RegR9);
    printf("R10: 0x%x\n", Context->RegR10);
    printf("R11: 0x%x\n", Context->RegR11);
    printf("R12: 0x%x\n", Context->RegR12);
    printf("R13: 0x%x\n", Context->RegR13);
    printf("R14: 0x%x\n", Context->RegR14);
    printf("R15: 0x%x\n", Context->RegR15);
}