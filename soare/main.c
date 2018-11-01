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
#include "atapio.h"


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

    WORD buff1[512] = { 0 }, buff2[512] = { 0 };
    DWORD pioStatus;
    
    pioStatus = SosAtaPioReadDiskLba28(1, 2, buff1);
    if (pioStatus != PIO_SUCCESS)
    {
        printf("[ERROR] SosAtaPioReadDiskLba28 failed with status %d\n", pioStatus);
    }

    pioStatus = SosAtaPioReadDiskLba28(1, 2, buff2);
    if (pioStatus != PIO_SUCCESS)
    {
        printf("[ERROR] SosAtaPioReadDiskLba48 failed with status %d\n", pioStatus);
    }

    for (DWORD i = 0; i < 512; i++)
    {
        if (buff1[i] != buff2[i])
        {
            printf("lba mismatch %x vs %x\n", buff1[i], buff2[i]);
        }
    }

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
