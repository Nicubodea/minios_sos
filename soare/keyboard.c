#include "keyboard.h"
#include "pic.h"
#include "screen.h"

#define KEYBOARD_STATUS_PORT    0x64
#define KEYBOARD_DATA_PORT      0x60

VOID
SosHandleKeyboardEvent(
    PCONTEXT Context
    )
{
    BYTE status, key;

    UNREFERENCED_PARAMETER(Context);

    // send the EOI first
    SosPicSendEoi(PIC_IRQ1_KEYBOARD);

    status = __inbyte(KEYBOARD_STATUS_PORT);

    if (status & 1)
    {
        key = __inbyte(KEYBOARD_DATA_PORT);

        if (key == 0x1e)
        {
            printf("a");
        }
    }
}