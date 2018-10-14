#include "pit.h"
#include "pic.h"
#include "interrupt.h"
#include "screen.h"

QWORD gNumberOfTicks = 0;


VOID
TestPit(PCONTEXT Context) 
{
    UNREFERENCED_PARAMETER(Context);

    SosPicSendEoi(PIC_IRQ0_PIT);

    gNumberOfTicks++;

    if (gNumberOfTicks % TIMER_ONE_SECOND == 0)
    {
        printf("Theoretically, a second passed...\n");
    }
}


VOID
SosInitPit(
    VOID
)
{
    QWORD divisor = PIT_RATE / TIMER_FREQUENCY;

    SosPicClearIrqMask(PIC_IRQ0_PIT);
    __outbyte(PIT_COMMAND_PORT, CHANNEL_0 | ACCESS_BOTH_LOHI | MODE_RATE_GENERATOR | BINARY_MODE);

    __outbyte(PIT_DATA_PORT_CH0, divisor & 0xFF);
    __outbyte(PIT_DATA_PORT_CH0, (divisor >> 8) & 0xFF);

    SosRegisterInterrupt(INTERRUPT_TIMER, TestPit, TYPE_INTERRUPT);
}