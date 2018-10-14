#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "sosdefines.h"
#include "interrupt.h"

#define KEYBOARD_MAX_SCAN_CODE_SIZE     6
#define KEYBOARD_SIZE                   248

#define KEYBOARD_KEY_ESCAPE             0
#define KEYBOARD_KEY_1                  1
#define KEYBOARD_KEY_2                  2
#define KEYBOARD_KEY_3                  3
#define KEYBOARD_KEY_4                  4
#define KEYBOARD_KEY_5                  5
#define KEYBOARD_KEY_6                  6
#define KEYBOARD_KEY_7                  7
#define KEYBOARD_KEY_8                  8
#define KEYBOARD_KEY_9                  9
#define KEYBOARD_KEY_0                  10
#define KEYBOARD_KEY_LINE               11
#define KEYBOARD_KEY_EQUAL              12
#define KEYBOARD_KEY_BACKSPACE          13
#define KEYBOARD_KEY_TAB                14
#define KEYBOARD_KEY_Q                  15
#define KEYBOARD_KEY_W                  16
#define KEYBOARD_KEY_E                  17
#define KEYBOARD_KEY_R                  18
#define KEYBOARD_KEY_T                  19
#define KEYBOARD_KEY_Y                  20
#define KEYBOARD_KEY_U                  21
#define KEYBOARD_KEY_I                  22
#define KEYBOARD_KEY_O                  23
#define KEYBOARD_KEY_P                  24
#define KEYBOARD_KEY_SQUARE_BRACKET     25
#define KEYBOARD_KEY_SQUARE_BRACKET_2   26
#define KEYBOARD_KEY_ENTER              27
#define KEYBOARD_KEY_LEFT_CTRL          28
#define KEYBOARD_KEY_A                  29
#define KEYBOARD_KEY_S                  30
#define KEYBOARD_KEY_D                  31
#define KEYBOARD_KEY_F                  32
#define KEYBOARD_KEY_G                  33
#define KEYBOARD_KEY_H                  34
#define KEYBOARD_KEY_J                  35
#define KEYBOARD_KEY_K                  36
#define KEYBOARD_KEY_L                  37
#define KEYBOARD_KEY_SEMICOLON          38
#define KEYBOARD_KEY_QUOTE              39
#define KEYBOARD_KEY_BACK_TICK          40
#define KEYBOARD_KEY_LEFT_SHIFT         41
#define KEYBOARD_KEY_BACKSLASH          42
#define KEYBOARD_KEY_Z                  43
#define KEYBOARD_KEY_X                  44
#define KEYBOARD_KEY_C                  45
#define KEYBOARD_KEY_V                  46
#define KEYBOARD_KEY_B                  47
#define KEYBOARD_KEY_N                  48
#define KEYBOARD_KEY_M                  49
#define KEYBOARD_KEY_COMMA              50
#define KEYBOARD_KEY_DOT                51
#define KEYBOARD_KEY_SLASH              52
#define KEYBOARD_KEY_RIGHT_SHIFT        53
#define KEYBOARD_KEY_KEYPAD_STAR        54
#define KEYBOARD_KEY_LEFT_ALT           55
#define KEYBOARD_KEY_SPACE              56
#define KEYBOARD_KEY_CAPSLOCK           57
#define KEYBOARD_KEY_F1                 58
#define KEYBOARD_KEY_F2                 59
#define KEYBOARD_KEY_F3                 60
#define KEYBOARD_KEY_F4                 61
#define KEYBOARD_KEY_F5                 62
#define KEYBOARD_KEY_F6                 63
#define KEYBOARD_KEY_F7                 64
#define KEYBOARD_KEY_F8                 65
#define KEYBOARD_KEY_F9                 66
#define KEYBOARD_KEY_F10                67
#define KEYBOARD_KEY_NUMBER_LOCK        68
#define KEYBOARD_KEY_SCROLL_LOCK        69
#define KEYBOARD_KEY_KEYPAD_7           70
#define KEYBOARD_KEY_KEYPAD_8           71
#define KEYBOARD_KEY_KEYPAD_9           72
#define KEYBOARD_KEY_KEYPAD_MINUS       73
#define KEYBOARD_KEY_KEYPAD_4           74
#define KEYBOARD_KEY_KEYPAD_5           75
#define KEYBOARD_KEY_KEYPAD_6           76
#define KEYBOARD_KEY_KEYPAD_PLUS        77
#define KEYBOARD_KEY_KEYPAD_1           78
#define KEYBOARD_KEY_KEYPAD_2           79
#define KEYBOARD_KEY_KEYPAD_3           80
#define KEYBOARD_KEY_KEYPAD_0           81
#define KEYBOARD_KEY_KEYPAD_DOT         82
#define KEYBOARD_KEY_F11                83
#define KEYBOARD_KEY_F12                84

#define KEYBOARD_KEY_UNKNOWN            85

typedef struct _SCANCODE_TO_KEY
{
    BYTE ScanCodeBytes[KEYBOARD_MAX_SCAN_CODE_SIZE];
    WORD KeyCode;
    BOOLEAN Pressed;
} SCANCODE_TO_KEY, *PSCANCODE_TO_KEY;

typedef struct _KEYBOARD_EVENT
{
    BOOLEAN IsPressed[KEYBOARD_SIZE];
    SCANCODE_TO_KEY LastKeyboardEvent;
} KEYBOARD_EVENT, *PKEYBOARD_EVENT;

typedef VOID(*PFUNC_SosKeyboardEventHandler)(
    PKEYBOARD_EVENT Event
    );

VOID 
SosHandleKeyboardEvent(
    PCONTEXT Context
    );

VOID
SosKeyboardAttachEventHandler(
    PFUNC_SosKeyboardEventHandler EventHandler
    );

VOID
SosKeyboardDetachEventHandler(
    VOID
    );

VOID
SosInitKeyboard(
    VOID
);

#endif