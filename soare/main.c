#include "boot.h"
#include "screen.h"
#include "sosdefines.h"
#include "apic.h"
#include "pic.h"
#include "interrupt.h"
#include "keyboard.h"
#include "interrupt_handlers.h"
#include "console.h"
#include "pit.h"


VOID 
SosEntryPoint(
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

    printf("[INFO] Init interrupts\n");

    SosInitInterrupts();

    SosInitInterruptHandlers();

    SosInitializePic(PIC_MASTER_BASE, PIC_SLAVE_BASE);

    // Disable all interrupts
    for (BYTE i = 0; i < 16; i++)
    {
        SosPicSetIrqMask(i);
    }

    SosInitKeyboard();

    SosInitPit();

    SosConsoleInitConsole();

    __sti();

    SosConsoleStartConsole();

    while (TRUE)
    {
        continue;
    }
}
