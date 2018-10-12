#include "interrupt_handlers.h"

VOID
SosInitInterruptHandlers(
    VOID
)
{
    SosRegisterInterrupt(INTERRUPT_DE, SosHandleDivisionError, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_DB, SosHandleDebugException, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_NMI, SosHandleNMI, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_BP, SosHandleBreakpoint, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_OF, SosHandleOverflow, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_BR, SosHandleBoundRangeExceeded, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_UD, SosHandleInvalidOpcode, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_NM, SosHandleDeviceNotAvailable, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_DF, SosHandleDoubleFault, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_COPROCESSOR, SosHandleCoprocessorSegment, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_TS, SosHandleInvalidTSS, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_NP, SosHandleSegmentNotPresent, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_SS, SosHandleStackFault, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_GP, SosHandleGeneralProtection, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_PF, SosHandlePageFault, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_MF, SosHandleMachineCheck, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_AC, SosHandleAlignmentCheck, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_MC, SosHandleMachineCheck, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_XM, SosHandleSIMDFloatingPoint, TYPE_TRAP);
    SosRegisterInterrupt(INTERRUPT_VE, SosHandleVirtualizationException, TYPE_TRAP);

}


VOID
SosHandleDivisionError(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}

VOID
SosHandleDebugException(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleNMI(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleBreakpoint(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleOverflow(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleBoundRangeExceeded(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleInvalidOpcode(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleDeviceNotAvailable(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleDoubleFault(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleCoprocessorSegment(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleInvalidTSS(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleSegmentNotPresent(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleStackFault(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleGeneralProtection(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandlePageFault(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleFloatingPointError(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleAlignmentCheck(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleMachineCheck(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleSIMDFloatingPoint(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}


VOID
SosHandleVirtualizationException(
    PCONTEXT Context
)
{
    SosDumpInterruptContext(Context);
    __halt();
}
