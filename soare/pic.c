#include "pic.h"

VOID
SosInitializePic(
    BYTE MasterRemapOffset,
    BYTE SlaveRemapOffset
)
{
    BYTE oldMasterMask, oldSlaveMask;

    oldMasterMask = __inbyte(PIC1_DATA);
    oldSlaveMask = __inbyte(PIC2_DATA);
    
    __outbyte(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
    
    __outbyte(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);

    __outbyte(PIC1_DATA, MasterRemapOffset);

    __outbyte(PIC2_DATA, SlaveRemapOffset);

    __outbyte(PIC1_DATA, 4);
    
    __outbyte(PIC2_DATA, 2);

    __outbyte(PIC1_DATA, ICW4_8086);

    __outbyte(PIC2_DATA, ICW4_8086);

    __outbyte(PIC1_DATA, oldMasterMask);

    __outbyte(PIC2_DATA, oldSlaveMask);

}


VOID
SosPicSetIrqMask(
    BYTE IrqLine
)
{
    WORD port;
    BYTE value;

    if (IrqLine < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IrqLine -= 8;
    }

    value = __inbyte(port) | (1 << IrqLine);
    __outbyte(port, value);

}


VOID
SosPicClearIrqMask(
    BYTE IrqLine
)
{
    WORD port;
    BYTE value;

    if (IrqLine < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IrqLine -= 8;
    }

    value = __inbyte(port) & (~(1 << IrqLine));
    __outbyte(port, value);
}


static WORD
_SosPicGetIrqReg(
    BYTE Ocw3
)
{
    __outbyte(PIC1_COMMAND, Ocw3);
    __outbyte(PIC2_COMMAND, Ocw3);

    return (__inbyte(PIC2_COMMAND) << 8) | __inbyte(PIC1_COMMAND);
}


WORD
SosPicGetIrr(
    VOID
)
{
    return _SosPicGetIrqReg(PIC_READ_IRR);
}

WORD
SosPicGetIsr(
    VOID
)
{
    return _SosPicGetIrqReg(PIC_READ_ISR);
}

VOID
SosPicSendEoi(
    BYTE Irq
    )
{
    if (Irq >= 8)
    {
        __outbyte(PIC2_COMMAND, PIC_EOI);
    }

    __outbyte(PIC1_COMMAND, PIC_EOI);
}