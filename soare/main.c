#include "boot.h"
#include "screen.h"
#include "sosdefines.h"
#include "apic.h"
#include "pic.h"

#include "interrupt.h"



VOID
TestPF(
    PCONTEXT Context
)
{
    printf("INTERRUPT #%x arrived: \n", Context->InterruptNumber);
    
    SosDumpInterruptContext(Context);

    __halt();
}

VOID
Cplm(
    PCONTEXT Context
)
{
    UNREFERENCED_PARAMETER(Context);
    printf("hERE");

    SosPicSendEoi(1);

    printf("eoi sent");
    //__halt();
}

VOID SosEntryPoint(
    VOID
    )
{
    QWORD apicBase = 0;

    printf("[INFO] Starting boot SOARE OS!\n");

    if (!SosApicIsApicAvailable())
    {
        printf("[ERROR] This configurations lacks APIC which is needed to boot the OS.\n");
        return;
    }

    printf("[INFO] APIC available.\n");

    apicBase = __readmsr(IA32_APIC_BASE);

    printf("[INFO] BSP: %d, global enable: %d, apic base: %x", !!(apicBase & (1 << 8)), !!(apicBase & (1 << 11)), (apicBase & ~PAGE_OFFSET));

    printf("[INFO] Local apic id: %d\n", SosApicGetCurrentApicId());

    SosInitializePic(0, 0);

    // Disable all interrupts
    for (BYTE i = 0; i < 16; i++)
    {
        SosPicSetIrqMask(i);
    }

    // enable IRQ1 - the keyboard interrupt
    SosPicClearIrqMask(1);

    printf("[INFO] Init interrupts\n");

    SosInitInterrupts();

    SosRegisterInterrupt(14, TestPF, 0xF);
    SosRegisterInterrupt(0x21, Cplm, 0xE);

    //*(PQWORD)(0xc0c0c0c0c0) = 69;

    while (TRUE)
    {
        continue;
    }
}
