#ifndef _SCANCODE_TO_KEY_H_
#define _SCANCODE_TO_KEY_H_

#include "sosdefines.h"
#include "keyboard.h"


static SCANCODE_TO_KEY gScancodeToKeyMatrix[] =
{
    {
        { 0x01 },
        KEYBOARD_KEY_ESCAPE,
        TRUE
    },
    {
        { 0x02 },
        KEYBOARD_KEY_1,
        TRUE
    },
    {
        { 0x03 },
        KEYBOARD_KEY_2,
        TRUE
    },
    {
        { 0x04 },
        KEYBOARD_KEY_3,
        TRUE
    },
    {
        { 0x05 },
        KEYBOARD_KEY_4,
        TRUE
    },
    {
        { 0x06 },
        KEYBOARD_KEY_5,
        TRUE
    },
    {
        { 0x07 },
        KEYBOARD_KEY_6,
        TRUE
    },
    {
        { 0x08 },
        KEYBOARD_KEY_7,
        TRUE
    },
    {
        { 0x09 },
        KEYBOARD_KEY_8,
        TRUE
    },
    {
        { 0x0a },
        KEYBOARD_KEY_9,
        TRUE
    },
    {
        { 0x0b },
        KEYBOARD_KEY_0,
        TRUE
    },
    {
        { 0x0c },
        KEYBOARD_KEY_LINE,
        TRUE
    },
    {
        { 0x0d },
        KEYBOARD_KEY_EQUAL,
        TRUE
    },
    {
        { 0x0e },
        KEYBOARD_KEY_BACKSPACE,
        TRUE
    },
    {
        { 0x0f },
        KEYBOARD_KEY_TAB,
        TRUE
    },
    {
        { 0x10 },
        KEYBOARD_KEY_Q,
        TRUE
    },
    {
        { 0x11 },
        KEYBOARD_KEY_W,
        TRUE
    },
    {
        { 0x12 },
        KEYBOARD_KEY_E,
        TRUE
    },
    {
        { 0x13 },
        KEYBOARD_KEY_R,
        TRUE
    },
    {
        { 0x14 },
        KEYBOARD_KEY_T,
        TRUE
    },
    {
        { 0x15 },
        KEYBOARD_KEY_Y,
        TRUE
    },
    {
        { 0x16 },
        KEYBOARD_KEY_U,
        TRUE
    },
    {
        { 0x17 },
        KEYBOARD_KEY_I,
        TRUE
    },
    {
        { 0x18 },
        KEYBOARD_KEY_O,
        TRUE
    },
    {
        { 0x19 },
        KEYBOARD_KEY_P,
        TRUE
    },
    {
        { 0x1a },
        KEYBOARD_KEY_SQUARE_BRACKET,
        TRUE
    },
    {
        { 0x1b },
        KEYBOARD_KEY_SQUARE_BRACKET_2,
        TRUE
    },
    {
        { 0x1c },
        KEYBOARD_KEY_ENTER,
        TRUE
    },
    {
        { 0x1d },
        KEYBOARD_KEY_LEFT_CTRL,
        TRUE
    },
    {
        { 0x1e },
        KEYBOARD_KEY_A,
        TRUE
    },
    {
        { 0x1f },
        KEYBOARD_KEY_S,
        TRUE
    },
    {
        { 0x20 },
        KEYBOARD_KEY_D,
        TRUE
    },
    {
        { 0x21 },
        KEYBOARD_KEY_F,
        TRUE
    },
    {
        { 0x22 },
        KEYBOARD_KEY_G,
        TRUE
    },
    {
        { 0x23 },
        KEYBOARD_KEY_H,
        TRUE
    },
    {
        { 0x24 },
        KEYBOARD_KEY_J,
        TRUE
    },
    {
        { 0x25 },
        KEYBOARD_KEY_K,
        TRUE
    },
    {
        { 0x26 },
        KEYBOARD_KEY_L,
        TRUE
    },
    {
        { 0x27 },
        KEYBOARD_KEY_SEMICOLON,
        TRUE
    },
    {
        { 0x28 },
        KEYBOARD_KEY_QUOTE,
        TRUE
    },
    {
        { 0x29 },
        KEYBOARD_KEY_BACK_TICK,
        TRUE
    },
    {
        { 0x2a },
        KEYBOARD_KEY_LEFT_SHIFT,
        TRUE
    },
    {
        { 0x2b },
        KEYBOARD_KEY_BACKSLASH,
        TRUE
    },
    {
        { 0x2c },
        KEYBOARD_KEY_Z,
        TRUE
    },
    {
        { 0x2d },
        KEYBOARD_KEY_X,
        TRUE
    },
    {
        { 0x2e },
        KEYBOARD_KEY_C,
        TRUE
    },
    {
        { 0x2f },
        KEYBOARD_KEY_V,
        TRUE
    },
    {
        { 0x30 },
        KEYBOARD_KEY_B,
        TRUE
    },
    {
        { 0x31 },
        KEYBOARD_KEY_N,
        TRUE
    },
    {
        { 0x32 },
        KEYBOARD_KEY_M,
        TRUE
    },
    {
        { 0x33 },
        KEYBOARD_KEY_COMMA,
        TRUE
    },
    {
        { 0x34 },
        KEYBOARD_KEY_DOT,
        TRUE
    },
    {
        { 0x35 },
        KEYBOARD_KEY_SLASH,
        TRUE
    },
    {
        { 0x36 },
        KEYBOARD_KEY_RIGHT_SHIFT,
        TRUE
    },
    {
        { 0x37 },
        KEYBOARD_KEY_KEYPAD_STAR,
        TRUE
    },
    {
        { 0x38 },
        KEYBOARD_KEY_LEFT_ALT,
        TRUE
    },
    {
        { 0x39 },
        KEYBOARD_KEY_SPACE,
        TRUE
    },
    {
        { 0x3a },
        KEYBOARD_KEY_CAPSLOCK,
        TRUE
    },
    {
        { 0x3b },
        KEYBOARD_KEY_F1,
        TRUE
    },
    {
        { 0x3c },
        KEYBOARD_KEY_F2,
        TRUE
    },
    {
        { 0x3d },
        KEYBOARD_KEY_F3,
        TRUE
    },
    {
        { 0x3e },
        KEYBOARD_KEY_F4,
        TRUE
    },
    {
        { 0x3f },
        KEYBOARD_KEY_F5,
        TRUE
    },
    {
        { 0x40 },
        KEYBOARD_KEY_F6,
        TRUE
    },
    {
        { 0x41 },
        KEYBOARD_KEY_F7,
        TRUE
    },
    {
        { 0x42 },
        KEYBOARD_KEY_F8,
        TRUE
    },
    {
        { 0x43 },
        KEYBOARD_KEY_F9,
        TRUE
    },
    {
        { 0x44 },
        KEYBOARD_KEY_F10,
        TRUE
    },
    {
        { 0x45 },
        KEYBOARD_KEY_NUMBER_LOCK,
        TRUE
    },
    {
        { 0x46 },
        KEYBOARD_KEY_SCROLL_LOCK,
        TRUE
    },
    {
        { 0x47 },
        KEYBOARD_KEY_KEYPAD_7,
        TRUE
    },
    {
        { 0x48 },
        KEYBOARD_KEY_KEYPAD_8,
        TRUE
    },
    {
        { 0x49 },
        KEYBOARD_KEY_KEYPAD_9,
        TRUE
    },
    {
        { 0x4a },
        KEYBOARD_KEY_KEYPAD_MINUS,
        TRUE
    },
    {
        { 0x4b },
        KEYBOARD_KEY_KEYPAD_4,
        TRUE
    },
    {
        { 0x4c },
        KEYBOARD_KEY_KEYPAD_5,
        TRUE
    },
    {
        { 0x4d },
        KEYBOARD_KEY_KEYPAD_6,
        TRUE
    },
    {
        { 0x4e },
        KEYBOARD_KEY_KEYPAD_PLUS,
        TRUE
    },
    {
        { 0x4f },
        KEYBOARD_KEY_KEYPAD_1,
        TRUE
    },
    {
        { 0x50 },
        KEYBOARD_KEY_KEYPAD_2,
        TRUE
    },
    {
        { 0x51 },
        KEYBOARD_KEY_KEYPAD_3,
        TRUE
    },
    {
        { 0x52 },
        KEYBOARD_KEY_KEYPAD_0,
        TRUE
    },
    {
        { 0x53 },
        KEYBOARD_KEY_KEYPAD_DOT,
        TRUE
    },
    {
        { 0x57 },
        KEYBOARD_KEY_F11,
        TRUE
    },
    {
        { 0x58 },
        KEYBOARD_KEY_F12,
        TRUE
    },
    {
        { 0x81 },
        KEYBOARD_KEY_ESCAPE,
        TRUE
    },
    {
        { 0x82 },
        KEYBOARD_KEY_1,
        TRUE
    },
    {
        { 0x83 },
        KEYBOARD_KEY_2,
        TRUE
    },
    {
        { 0x84 },
        KEYBOARD_KEY_3,
        TRUE
    },
    {
        { 0x85 },
        KEYBOARD_KEY_4,
        TRUE
    },
    {
        { 0x86 },
        KEYBOARD_KEY_5,
        TRUE
    },
    {
        { 0x87 },
        KEYBOARD_KEY_6,
        TRUE
    },
    {
        { 0x88 },
        KEYBOARD_KEY_7,
        TRUE
    },
    {
        { 0x89 },
        KEYBOARD_KEY_8,
        TRUE
    },
    {
        { 0x8a },
        KEYBOARD_KEY_9,
        TRUE
    },
    {
        { 0x8b },
        KEYBOARD_KEY_0,
        TRUE
    },
    {
        { 0x8c },
        KEYBOARD_KEY_LINE,
        TRUE
    },
    {
        { 0x8d },
        KEYBOARD_KEY_EQUAL,
        TRUE
    },
    {
        { 0x8e },
        KEYBOARD_KEY_BACKSPACE,
        TRUE
    },
    {
        { 0x8f },
        KEYBOARD_KEY_TAB,
        TRUE
    },
    {
        { 0x90 },
        KEYBOARD_KEY_Q,
        TRUE
    },
    {
        { 0x91 },
        KEYBOARD_KEY_W,
        TRUE
    },
    {
        { 0x92 },
        KEYBOARD_KEY_E,
        TRUE
    },
    {
        { 0x93 },
        KEYBOARD_KEY_R,
        TRUE
    },
    {
        { 0x94 },
        KEYBOARD_KEY_T,
        TRUE
    },
    {
        { 0x95 },
        KEYBOARD_KEY_Y,
        TRUE
    },
    {
        { 0x96 },
        KEYBOARD_KEY_U,
        TRUE
    },
    {
        { 0x97 },
        KEYBOARD_KEY_I,
        TRUE
    },
    {
        { 0x98 },
        KEYBOARD_KEY_O,
        TRUE
    },
    {
        { 0x99 },
        KEYBOARD_KEY_P,
        TRUE
    },
    {
        { 0x9A },
        KEYBOARD_KEY_SQUARE_BRACKET,
        TRUE
    },
    {
        { 0x9b },
        KEYBOARD_KEY_SQUARE_BRACKET_2,
        TRUE
    },
    {
        { 0x9c },
        KEYBOARD_KEY_ENTER,
        TRUE
    },
    {
        { 0x9d },
        KEYBOARD_KEY_LEFT_CTRL,
        TRUE
    },
    {
        { 0x9e },
        KEYBOARD_KEY_A,
        TRUE
    },
    {
        { 0x9f },
        KEYBOARD_KEY_S,
        TRUE
    },
    {
        { 0xa0 },
        KEYBOARD_KEY_D,
        TRUE
    },
    {
        { 0xa1 },
        KEYBOARD_KEY_F,
        TRUE
    },
    {
        { 0xa2 },
        KEYBOARD_KEY_G,
        TRUE
    },
    {
        { 0xa3 },
        KEYBOARD_KEY_H,
        TRUE
    },
    {
        { 0xa4 },
        KEYBOARD_KEY_J,
        TRUE
    },
    {
        { 0xa5 },
        KEYBOARD_KEY_K,
        TRUE
    },
    {
        { 0xa6 },
        KEYBOARD_KEY_L,
        TRUE
    },
    {
        { 0xa7 },
        KEYBOARD_KEY_SEMICOLON,
        TRUE
    },
    {
        { 0xa8 },
        KEYBOARD_KEY_QUOTE,
        TRUE
    },
    {
        { 0xa9 },
        KEYBOARD_KEY_BACK_TICK,
        TRUE
    },
    {
        { 0xaa },
        KEYBOARD_KEY_LEFT_SHIFT,
        TRUE
    },
    {
        { 0xab },
        KEYBOARD_KEY_BACKSLASH,
        TRUE
    },
    {
        { 0xac },
        KEYBOARD_KEY_Z,
        TRUE
    },
    {
        { 0xad },
        KEYBOARD_KEY_X,
        TRUE
    },
    {
        { 0xae },
        KEYBOARD_KEY_C,
        TRUE
    },
    {
        { 0xaf },
        KEYBOARD_KEY_V,
        TRUE
    },
    {
        { 0xb0 },
        KEYBOARD_KEY_B,
        TRUE
    },
    {
        { 0xb1 },
        KEYBOARD_KEY_N,
        TRUE
    },
    {
        { 0xb2 },
        KEYBOARD_KEY_M,
        TRUE
    },
    {
        { 0xb3 },
        KEYBOARD_KEY_COMMA,
        TRUE
    },
    {
        { 0xb4 },
        KEYBOARD_KEY_DOT,
        TRUE
    },
    {
        { 0xb5 },
        KEYBOARD_KEY_SLASH,
        TRUE
    },
    {
        { 0xb6 },
        KEYBOARD_KEY_RIGHT_SHIFT,
        TRUE
    },
    {
        { 0xb7 },
        KEYBOARD_KEY_KEYPAD_STAR,
        TRUE
    },
    {
        { 0xb8 },
        KEYBOARD_KEY_LEFT_ALT,
        TRUE
    },
    {
        { 0xb9 },
        KEYBOARD_KEY_SPACE,
        TRUE
    },
    {
        { 0xba },
        KEYBOARD_KEY_CAPSLOCK,
        TRUE
    },
    {
        { 0xbb },
        KEYBOARD_KEY_F1,
        TRUE
    },
    {
        { 0xbc },
        KEYBOARD_KEY_F2,
        TRUE
    },
    {
        { 0xbd },
        KEYBOARD_KEY_F3,
        TRUE
    },
    {
        { 0xbe },
        KEYBOARD_KEY_F4,
        TRUE
    },
    {
        { 0xbf },
        KEYBOARD_KEY_F5,
        TRUE
    },
    {
        { 0xc0 },
        KEYBOARD_KEY_F6,
        TRUE
    },
    {
        { 0xc1 },
        KEYBOARD_KEY_F7,
        TRUE
    },
    {
        { 0xc2 },
        KEYBOARD_KEY_F8,
        TRUE
    },
    {
        { 0xc3 },
        KEYBOARD_KEY_F9,
        TRUE
    },
    {
        { 0xc4 },
        KEYBOARD_KEY_F10,
        TRUE
    },
    {
        { 0xc5 },
        KEYBOARD_KEY_NUMBER_LOCK,
        TRUE
    },
    {
        { 0xc6 },
        KEYBOARD_KEY_SCROLL_LOCK,
        TRUE
    },
    {
        { 0xc7 },
        KEYBOARD_KEY_KEYPAD_7,
        TRUE
    },
    {
        { 0xc8 },
        KEYBOARD_KEY_KEYPAD_8,
        TRUE
    },
    {
        { 0xc9 },
        KEYBOARD_KEY_KEYPAD_9,
        TRUE
    },
    {
        { 0xca },
        KEYBOARD_KEY_KEYPAD_MINUS,
        TRUE
    },
    {
        { 0xcb },
        KEYBOARD_KEY_KEYPAD_4,
        TRUE
    },
    {
        { 0xcc },
        KEYBOARD_KEY_KEYPAD_5,
        TRUE
    },
    {
        { 0xcd },
        KEYBOARD_KEY_KEYPAD_6,
        TRUE
    },
    {
        { 0xce },
        KEYBOARD_KEY_KEYPAD_PLUS,
        TRUE
    },
    {
        { 0xcf },
        KEYBOARD_KEY_KEYPAD_1,
        TRUE
    },
    {
        { 0xd0 },
        KEYBOARD_KEY_KEYPAD_2,
        TRUE
    },
    {
        { 0xd1 },
        KEYBOARD_KEY_KEYPAD_3,
        TRUE
    },
    {
        { 0xd2 },
        KEYBOARD_KEY_KEYPAD_0,
        TRUE
    },
    {
        { 0xd3 },
        KEYBOARD_KEY_KEYPAD_DOT,
        TRUE
    },
    {
        { 0xd7 },
        KEYBOARD_KEY_F11,
        TRUE
    },
    {
        { 0xd8 },
        KEYBOARD_KEY_F12,
        TRUE
    },
    {
        { 0xe0, 0x10 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x19 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x1c },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x1d },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x20 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x22 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x24 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x2E },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x30 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x32 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x35 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x38 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x47 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x48 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x49 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x4B },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x4D },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x4F },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x50 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x51 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x52 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x53 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x5b },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x5c },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x5D },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x5e },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x5f },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x63 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x65 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x66 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x67 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x68 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x69 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x6a },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x6b },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x6c },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x6d },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x90 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x99 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x9C },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x9D },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xA0 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xA1 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xA2 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xA4 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xAE },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xB0 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xB2 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xB5 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xB8 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xC7 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xC8 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xC9 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xCB },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xCD },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xCF },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xD0 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xD1 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xD2 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xD3 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xDB },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xDC },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xDD },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xDE },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xDF },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xE3 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xE5 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xE6 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xE7 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xE8 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xE9 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xEA },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xEB },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xEC },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xED },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0x2a, 0xe0, 0x37 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe0, 0xb7, 0xe0, 0xaa},
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
    {
        { 0xe1, 0x1d, 0x45, 0xe1, 0x9d, 0xc5 },
        KEYBOARD_KEY_UNKNOWN,
        TRUE
    },
};

#endif