#include "keyboard.h"
#include "pic.h"
#include "screen.h"
#include "keyboard_state_machine.h"

#define KEYBOARD_STATUS_PORT        0x64
#define KEYBOARD_DATA_PORT          0x60

KEYBOARD_STATE gCurrentState;
BYTE gKeyboardBuffer[KEYBOARD_MAX_SCAN_CODE_SIZE];
BYTE gCurrentPosition = 0;



VOID
SosHandleKeyboardEvent(
    PCONTEXT Context
    )
{
    BYTE status, key;
    DWORD i;
    BOOLEAN found;

    UNREFERENCED_PARAMETER(Context);

    // send the EOI first
    SosPicSendEoi(PIC_IRQ1_KEYBOARD);

    status = __inbyte(KEYBOARD_STATUS_PORT);

    if (status & 1)
    {
        key = __inbyte(KEYBOARD_DATA_PORT);

        found = FALSE;
        for (i = 0; i < ARRAYSIZE(gStateMachine); i++)
        {
            if (key == gStateMachine[i].ScanCode && gCurrentState == gStateMachine[i].NeededState)
            {
                gKeyboardBuffer[gCurrentPosition] = key;
                gCurrentPosition++;
                gCurrentState = gStateMachine[i].ResultingState;
                found = TRUE;
                break;
            }
        }

        if (!found)
        {
            printf("[ERROR] State for scan code %x and state %d not found!\n", key, gCurrentState);
            return;
        }

        if (gCurrentState == KeyboardFinishedScanCode)
        {
            // transform scan code to internal kept key code and update keyboard state
            


            gCurrentState = KeyboardNothingToDo;
            gCurrentPosition = 0;
        }
    }
}