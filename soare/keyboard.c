#include "keyboard.h"
#include "pic.h"
#include "screen.h"
#include "keyboard_state_machine.h"
#include "scancode_to_key.h"

#define KEYBOARD_STATUS_PORT        0x64
#define KEYBOARD_DATA_PORT          0x60

KEYBOARD_STATE gCurrentState;
BYTE gKeyboardBuffer[KEYBOARD_MAX_SCAN_CODE_SIZE];
BYTE gCurrentPosition = 0;
KEYBOARD_EVENT gCurrentEvent;

PFUNC_SosKeyboardEventHandler gAttached = NULL;


VOID
SosKeyboardAttachEventHandler(
    PFUNC_SosKeyboardEventHandler EventHandler
)
{
    gAttached = EventHandler;
}

VOID 
SosKeyboardDetachEventHandler(
    VOID
)
{
    gAttached = NULL;
}


static
VOID
_SosKeyboardSendEventToAttached(
    VOID
)
{
    if (gAttached == NULL)
    {
        return;
    }

    gAttached(&gCurrentEvent);
}


static __forceinline
BOOLEAN
_SosKeyboardGetIsPressed(
    VOID
)
{
    if (gKeyboardBuffer[0] == 0xE0 && gCurrentPosition == 2)
    {
        return !(gKeyboardBuffer[1] & 0x80);
    }
    else if (gKeyboardBuffer[0] == 0xE0)
    {
        return (gKeyboardBuffer[1] == 0x2A);
    }
    else if (gKeyboardBuffer[0] == 0xE1)
    {
        return TRUE;
    }
    else
    {
        return !(gKeyboardBuffer[0] & 0x80);
    }
}


static
PSCANCODE_TO_KEY
_SosKeyboardScancodeToKey(
    VOID
    )
{
    WORD i, j;

    for (i = 0; i < ARRAYSIZE(gScancodeToKeyMatrix); i++)
    {
        BOOLEAN isGood = TRUE;

        for (j = 0; j < gCurrentPosition; j++)
        {
            if (gScancodeToKeyMatrix[i].ScanCodeBytes[j] != gKeyboardBuffer[j])
            {
                isGood = FALSE;
                break;
            }
        }

        if (isGood)
        {
            gScancodeToKeyMatrix[i].Pressed = _SosKeyboardGetIsPressed();

            return &gScancodeToKeyMatrix[i];
        }
    }

    return NULL;
}


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
            PSCANCODE_TO_KEY internalKey = _SosKeyboardScancodeToKey();

            if (internalKey == NULL)
            {
                printf("[ERROR] internal key not found, will not handle event!\n");
                return;
            }

            gCurrentEvent.LastKeyboardEvent = *internalKey;

            gCurrentEvent.IsPressed[internalKey->KeyCode] = internalKey->Pressed;

            // send the current keyboard state to attached
            _SosKeyboardSendEventToAttached();

            gCurrentState = KeyboardNothingToDo;
            gCurrentPosition = 0;
        }
    }
}


VOID
SosInitKeyboard(
    VOID
    )
{
    SosPicClearIrqMask(PIC_IRQ1_KEYBOARD);

    SosRegisterInterrupt(INTERRUPT_KEYBOARD, SosHandleKeyboardEvent, TYPE_INTERRUPT);
}