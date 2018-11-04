#ifndef _PIT_H_
#define _PIT_H_

#include "sosdefines.h"
#include "interrupt.h"
#define PIT_COMMAND_PORT            0x43
#define PIT_DATA_PORT_CH0           0x40

#define CHANNEL_0                   (0b00 << 6)
#define CHANNEL_1                   (0b01 << 6)
#define CHANNEL_2                   (0b10 << 6)
#define READ_BACK                   (0b11 << 6)

#define ACCESS_LATCH_COUNT          (0b00 << 4)
#define ACCESS_LOBYTE               (0b01 << 4)
#define ACCESS_HIBYTE               (0b10 << 4)
#define ACCESS_BOTH_LOHI            (0b11 << 4)

#define MODE_INTERRUPT_TCOUNT       (0b000 << 1)
#define MODE_HW_RT_ONE_SHOT         (0b001 << 1)
#define MODE_RATE_GENERATOR         (0b010 << 1)
#define MODE_SQ_WAVE_GENERATOR      (0b011 << 1)
#define MODE_SW_STROBE              (0b100 << 1)
#define MODE_HW_STROBE              (0b101 << 1)
#define MODE_RATE_GENERATOR_2       (0b110 << 1)
#define MODE_SQ_WAVE_GENERATOR_2    (0b111 << 1)

#define BINARY_MODE                 0
#define BCD_MODE                    1

#define PIT_RATE                    1193182
#define TIMER_FREQUENCY             100 // 10 ms, theoretically
#define TIMER_ONE_SECOND            (10000 / TIMER_FREQUENCY)


typedef struct _CLOCK
{
    DWORD Hours;
    DWORD Minutes;
    DWORD Seconds;
} CLOCK, *PCLOCK;

VOID
SosInitPit(
    VOID
    );

CLOCK
SosPitGetClock(
    VOID
);

VOID
SosPicSetClock(
    CLOCK Clock
    );

VOID
SosPitHandleTimer(
    PCONTEXT Context
);

BOOLEAN gIsHalted;

#endif