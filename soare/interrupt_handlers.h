#ifndef _INTERRUPT_HANDLERS_H_
#define _INTERRUPT_HANDLERS_H_

#include "sosdefines.h"
#include "interrupt.h"

VOID
SosInitInterruptHandlers(
    VOID
);

VOID
SosHandleDivisionError(
    PCONTEXT Context
);

VOID
SosHandleDebugException(
    PCONTEXT Context
);

VOID
SosHandleNMI(
    PCONTEXT Context
);

VOID
SosHandleBreakpoint(
    PCONTEXT Context
);

VOID
SosHandleOverflow(
    PCONTEXT Context
);

VOID
SosHandleBoundRangeExceeded(
    PCONTEXT Context
);

VOID
SosHandleInvalidOpcode(
    PCONTEXT Context
);

VOID
SosHandleDeviceNotAvailable(
    PCONTEXT Context
);

VOID
SosHandleDoubleFault(
    PCONTEXT Context
);

VOID
SosHandleCoprocessorSegment(
    PCONTEXT Context
);

VOID
SosHandleInvalidTSS(
    PCONTEXT Context
);

VOID
SosHandleSegmentNotPresent(
    PCONTEXT Context
);

VOID
SosHandleStackFault(
    PCONTEXT Context
);

VOID
SosHandleGeneralProtection(
    PCONTEXT Context
);

VOID
SosHandlePageFault(
    PCONTEXT Context
);

VOID
SosHandleFloatingPointError(
    PCONTEXT Context
);

VOID
SosHandleAlignmentCheck(
    PCONTEXT Context
);

VOID
SosHandleMachineCheck(
    PCONTEXT Context
);

VOID
SosHandleSIMDFloatingPoint(
    PCONTEXT Context
);

VOID
SosHandleVirtualizationException(
    PCONTEXT Context
);

#endif