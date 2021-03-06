#include "console.h"
#include "keyboard.h"
#include "screen.h"
#include "pit.h"
#include "atapio.h"
#include "alloc_phys.h"
#include "mmap.h"
#include "threads.h"

static BYTE gConsoleBuffer[1024];
DWORD gBufferSize = 0;
EVENT gReadEvent;
BOOLEAN gReadEnded = FALSE;

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
        SosThreadSignalEvent(&gReadEvent);
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
    va_list x;
    va_start(x, format);
    PVOID argv[101];
    DWORD args = 0;
    DWORD argCurrent = 0;
    DWORD j = 0, k = 0;

    UNREFERENCED_PARAMETER(format);

    SosThreadWaitForEvent(&gReadEvent);

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
            if (format[i + 1] == 'x')
            {
                QWORD number = 0;
                while (j < gBufferSize && (gConsoleBuffer[j] < '0' || gConsoleBuffer[j] > '9') && (gConsoleBuffer[j] < 'A' || gConsoleBuffer[j] > 'F'))
                {
                    j++;
                }
                while (j < gBufferSize && ((gConsoleBuffer[j] >= '0' && gConsoleBuffer[j] <= '9') || (gConsoleBuffer[j] >='A' && gConsoleBuffer[j] <= 'F')))
                {
                    if (gConsoleBuffer[j] >= 'A' && gConsoleBuffer[j] <= 'F')
                    {
                        switch (gConsoleBuffer[j])
                        {
                        case 'A':
                            number = number * 16 + 10;
                            break;
                        case 'B':
                            number = number * 16 + 11;
                            break;
                        case 'C':
                            number = number * 16 + 12;
                            break;
                        case 'D':
                            number = number * 16 + 13;
                            break;
                        case 'E':
                            number = number * 16 + 14;
                            break;
                        case 'F':
                            number = number * 16 + 15;
                            break;
                        }
                    }
                    else
                    {
                        number = number * 16 + gConsoleBuffer[j] - '0';
                    }
                    j++;
                }

                **(PQWORD*)(argv[argCurrent]) = number;
            }

            i++;
            argCurrent++;
        }
    }
    
    gBufferSize = 0;
    gReadEnded = FALSE;
}


VOID
SosConsoleStartConsole(
    VOID
)
{
    BYTE buffer[1024] = { 0 };

    SosThreadCreateEvent(&gReadEvent);

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
        else if (strcmp((char*)buffer, "readsect") == 0)
        {
            DWORD sect, pioStatus;
            WORD sector[WORDS_IN_SECTOR];
            DWORD i;

            printf("Give sector: ");
            SosConsoleRead("%d", &sect);

            pioStatus = SosAtaPioRead(sect, 1, sector);
            if (pioStatus != PIO_SUCCESS)
            {
                printf("[ERROR] SosAtaPioRead failed with error: %d\n", pioStatus);
                continue;
            }

            for (i = 0; i < WORDS_IN_SECTOR; i++)
            {
                printf("%x, ", sector[i]);
            }

            printf("\n");
        }
        else if (strcmp((char*)buffer, "allocp") == 0)
        {
            DWORD size;
            QWORD desired;

            printf("Give desired addr (0 for any): ");
            SosConsoleRead("%d", &desired);

            printf("Give size: ");
            SosConsoleRead("%d", &size);

            printf("Alloc returned: %x\n", SosAllocPhysAllocate((PVOID)desired, size));
        }
        else if (strcmp((char*)buffer, "freep") == 0)
        {
            QWORD address;

            printf("Give free addr: ");

            SosConsoleRead("%d", &address);

            SosAllocPhysFree((PVOID)address);
        }
        else if (strcmp((char*)buffer, "readphys") == 0)
        {
            QWORD phys;
            PQWORD pMap;

            printf("Give phys addr: ");

            SosConsoleRead("%x", &phys);

            pMap = SosMapVirtualMemory((PVOID)phys, SosMemoryUncachable);

            if (pMap != NULL)
            {
                printf("%x\n", pMap[0]);
                SosUnmapVirtualMemory(pMap);
            }
            else
            {
                printf("Physical memory could not be mapped!\n");
            }

        }
        else if (strcmp((char*)buffer, "writephys") == 0)
        {
            QWORD phys;
            PQWORD pMap;
            QWORD value;

            printf("Give phys addr: ");

            SosConsoleRead("%x", &phys);

            printf("What to write: ");

            SosConsoleRead("%x", &value);

            pMap = SosMapVirtualMemory((PVOID)phys, SosMemoryUncachable);

            if (pMap != NULL)
            {
                pMap[0] = value;
                printf("Succesfully written!\n");
                SosUnmapVirtualMemory(pMap);
            }
            else
            {
                printf("Physical memory could not be mapped!\n");
            }

        }
        else if (strcmp((char*)buffer, "showallocp") == 0)
        {
            SosAllocPhysPrintAllocs();
        }
        else
        {
            printf("Unknown command: %s\n", buffer);
        }
    }

}