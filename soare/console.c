#include "console.h"
#include "keyboard.h"
#include "screen.h"
#include "pit.h"

static BYTE gConsoleBuffer[1024];
DWORD gBufferSize = 0;
volatile BOOLEAN gReadEnded;

#define LEFT_SHIFT_KEY      0x29
#define RIGHT_SHIFT_KEY     0x35
#define CAPS_LOCK           0x39
#define ENTER               0x1B
#define BACKSPACE           0xD

static BYTE gToPrintingCharacter[] =
{
    0,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    0,
    0,
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    0,
    0,
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    0,
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0,
    0,
    0,
    ' ',
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static BYTE gToPrintingCharacterShift[] =
{
    0,
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    '_',
    '+',
    0,
    0,
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '{',
    '}',
    0,
    0,
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ':',
    '"',
    '~',
    0,
    '|',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    '<',
    '>',
    '?',
    0,
    0,
    0,
    ' ',
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

BOOLEAN gCapsLock = FALSE;

static
VOID
_SosConsoleReceiveKeyboardEvent(
    PKEYBOARD_EVENT Event
)
{
    BYTE printedCharForEcho = 0;
    if (gReadEnded)
    {
        return;
    }

    if (Event->LastKeyboardEvent.KeyCode == CAPS_LOCK && Event->LastKeyboardEvent.Pressed)
    {
        gCapsLock = !gCapsLock;
        return;
    }

    if (Event->LastKeyboardEvent.KeyCode == ENTER && Event->LastKeyboardEvent.Pressed)
    {
        gReadEnded = TRUE;
        printf("\n");
        return;
    }

    if (Event->LastKeyboardEvent.KeyCode == BACKSPACE && Event->LastKeyboardEvent.Pressed)
    {
        if (gBufferSize == 0)
        {
            return;
        }

        gBufferSize--;
        printf_delete_last_character();
        return;
    }

    if (!Event->LastKeyboardEvent.Pressed)
    {
        return;
    }

    if (Event->IsPressed[LEFT_SHIFT_KEY] || Event->IsPressed[RIGHT_SHIFT_KEY])
    {
        if (Event->LastKeyboardEvent.KeyCode >= sizeof(gToPrintingCharacterShift) ||
            gToPrintingCharacterShift[Event->LastKeyboardEvent.KeyCode] == 0)
        {
            return;
        }

        if (gCapsLock && 
            gToPrintingCharacterShift[Event->LastKeyboardEvent.KeyCode] >= 'A' && 
            gToPrintingCharacterShift[Event->LastKeyboardEvent.KeyCode] <= 'Z')
        {
            gConsoleBuffer[gBufferSize] = gToPrintingCharacterShift[Event->LastKeyboardEvent.KeyCode] + 'a' - 'A';
        }
        else
        {
            gConsoleBuffer[gBufferSize] = gToPrintingCharacterShift[Event->LastKeyboardEvent.KeyCode];
        }

        gBufferSize++;
    }
    else
    {
        if (Event->LastKeyboardEvent.KeyCode >= sizeof(gToPrintingCharacter) ||
            gToPrintingCharacter[Event->LastKeyboardEvent.KeyCode] == 0)
        {
            return;
        }

        if (gCapsLock &&
            gToPrintingCharacter[Event->LastKeyboardEvent.KeyCode] >= 'a' &&
            gToPrintingCharacter[Event->LastKeyboardEvent.KeyCode] <= 'z')
        {
            gConsoleBuffer[gBufferSize] = gToPrintingCharacter[Event->LastKeyboardEvent.KeyCode] + 'A' - 'a';
        }
        else
        {
            gConsoleBuffer[gBufferSize] = gToPrintingCharacter[Event->LastKeyboardEvent.KeyCode];
        }

        gBufferSize++;
    }

    printedCharForEcho = gConsoleBuffer[gBufferSize - 1];
    printf("%c", printedCharForEcho);

}

VOID
SosConsoleInitConsole(
    VOID
    )
{
    SosKeyboardAttachEventHandler(_SosConsoleReceiveKeyboardEvent);
}


VOID
SosConsoleRead(
    char* format, ...
)
{
    UNREFERENCED_PARAMETER(format);
    va_list x;
    va_start(x, format);
    PVOID argv[101];
    DWORD args = 0;
    DWORD argCurrent = 0;
    DWORD j = 0, k = 0;

    gReadEnded = FALSE;
    while (gReadEnded == FALSE)
    {
        // should sleep here or something, but we don't have scheduling yet...
        __halt();
        continue;
    }

    
    for (DWORD i = 0; format[i] != '\0'; i++)
    {
        if ('%' == format[i])
        {
            argv[args] = x;
            args++;
            x = x + 8;
        }
    }

    for (DWORD i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            if (format[i + 1] == 's')
            {
                k = 0;
                while (j < gBufferSize && gConsoleBuffer[j] == ' ')
                {
                    j++;
                }
                while (j < gBufferSize && gConsoleBuffer[j] != ' ')
                {
                    (*(PBYTE*)argv[argCurrent])[k] = gConsoleBuffer[j];
                    k++;
                    j++;
                }

                (*(PBYTE*)argv[argCurrent])[k] = 0;
            }
            if (format[i + 1] == 'd')
            {
                DWORD number = 0;
                while (j < gBufferSize && (gConsoleBuffer[j] < '0' || gConsoleBuffer[j] > '9'))
                {
                    j++;
                }
                while (j < gBufferSize && gConsoleBuffer[j] >='0' && gConsoleBuffer[j] <= '9')
                {
                    number = number * 10 + gConsoleBuffer[j] - '0';
                    j++;
                }

                **(PDWORD*)(argv[argCurrent]) = number;
            }

            i++;
            argCurrent++;
        }
    }
    
    gBufferSize = 0;
}


VOID
SosConsoleStartConsole(
    VOID
)
{
    BYTE buffer[1024] = { 0 };

    while (TRUE)
    {
        printf(">");
        SosConsoleRead("%s", buffer);

        if (strcmp((char*)buffer, "gettime") == 0)
        {
            CLOCK c = SosPitGetClock();
            printf("%d:%d:%d\n", c.Hours, c.Minutes, c.Seconds);
        }
        else if (strcmp((char*)buffer, "settime") == 0)
        {
            DWORD hours, minutes, seconds;
            CLOCK c;

            printf("Give hours: ");
            SosConsoleRead("%d", &hours);
            
            printf("Give minutes: ");
            SosConsoleRead("%d", &minutes);
            
            printf("Give seconds: ");
            SosConsoleRead("%d", &seconds);
        
            c.Hours = hours;
            c.Minutes = minutes;
            c.Seconds = seconds;

            SosPicSetClock(c);
        }
        else
        {
            printf("Unknown command: %s\n", buffer);
        }
    }

}