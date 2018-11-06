#include "pit.h"
#include "pic.h"
#include "interrupt.h"
#include "screen.h"
#include "scheduler.h"

QWORD gNumberOfTicks = 0;
QWORD gNumberOfSeconds = 0;


VOID
SosPitHandleTimer(
    PCONTEXT Context
    )
{
    UNREFERENCED_PARAMETER(Context);

    SosPicSendEoi(PIC_IRQ0_PIT);

    gNumberOfTicks++;

    if (gNumberOfTicks % TIMER_ONE_SECOND == 0)
    {
        CLOCK c;
        gNumberOfSeconds++;

        c = SosPitGetClock();

        printf_pos((char*)END_TOOLAR - 18, "%d:%d:%d", c.Hours, c.Minutes, c.Seconds);
        
        SosScheduleJobs(Context);
    }
}


CLOCK
SosPitGetClock(
    VOID
    )
{
    CLOCK clock;

    clock.Hours = (DWORD)(gNumberOfSeconds / 3600);
    clock.Minutes = (gNumberOfSeconds % 3600) / 60;
    clock.Seconds = (gNumberOfSeconds % 3600) % 60;

    return clock;
}

VOID
SosPicSetClock(
    CLOCK Clock
    )
{
    gNumberOfSeconds = Clock.Hours * 3600 + Clock.Minutes * 60 + Clock.Seconds;
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

    SosRegisterInterrupt(INTERRUPT_TIMER, SosPitHandleTimer, TYPE_INTERRUPT);
}