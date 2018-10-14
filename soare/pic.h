#ifndef _PIC_H_
#define _PIC_H_

#include "sosdefines.h"

#define PIC1        0x20       
#define PIC2        0xA0       
#define PIC1_COMMAND    PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA   (PIC2+1)

#define PIC_READ_IRR                0x0a 
#define PIC_READ_ISR                0x0b

#define ICW1_ICW4       0x01        /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02        /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04        /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08        /* Level triggered (edge) mode */
#define ICW1_INIT       0x10        /* Initialization - required! */

#define ICW4_8086       0x01        /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02        /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08        /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C        /* Buffered mode/master */
#define ICW4_SFNM       0x10        /* Special fully nested (not) */


#define PIC_EOI         0x20

#define PIC_IRQ0_PIT                        0x0
#define PIC_IRQ1_KEYBOARD                   0x1
#define PIC_IRQ7_MASTER_SPURIOUS_INTERRUPT  0x7
#define PIC_IRQ15_SLAVE_SPURIOUS_INTERRUPT  0xf

#define PIC_MASTER_BASE     0x20
#define PIC_SLAVE_BASE      0x28

VOID
SosInitializePic(
    BYTE MasterRemapOffset,
    BYTE SlaveRemapOffset
    );

VOID
SosPicSetIrqMask(
    BYTE IrqLine
    );

VOID
SosPicClearIrqMask(
    BYTE IrqLine
    );

WORD
SosPicGetIrr(
    VOID
    );

WORD
SosPicGetIsr(
    VOID
    );

VOID
SosPicSendEoi(
    BYTE Irq
    );

#endif