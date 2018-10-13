#ifndef _KEYBOARD_STATE_MACHINE_H_
#define _KEYBOARD_STATE_MACHINE_H_

#include "sosdefines.h"

#define KEYBOARD_MAX_SCAN_CODE_SIZE 6

typedef enum _KEYBOARD_STATE
{
    KeyboardNothingToDo,
    KeyboardWaitForScanCode,
    KeyboardFinishedScanCode,
    KeyboardStateUnknown
} KEYBOARD_STATE;

typedef struct _SCANCODE_STATE
{
    BYTE ScanCode;
    KEYBOARD_STATE NeededState;
    KEYBOARD_STATE ResultingState;
} SCANCODE_STATE, *PSCANCODE_STATE;

typedef struct _SCANCODE_TO_KEY
{
    BYTE ScanCodeBytes[KEYBOARD_MAX_SCAN_CODE_SIZE];
    WORD KeyCode;
} SCANCODE_TO_KEY, *PSCANCODE_TO_KEY;



static SCANCODE_STATE gStateMachine[] = 
{
    {
        0x01,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x02,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x03,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x04,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x05,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x06,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x07,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x08,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x09,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x0a,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x0b,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x0c,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xd,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xe,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xf,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x10,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x11,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x12,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x13,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x14,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x15,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x16,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x17,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x18,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x19,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x1a,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x1b,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x1c,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x1d,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x1e,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x1f,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x20,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x21,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x22,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x23,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x24,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x25,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x26,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x27,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x28,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x29,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x2a,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x2b,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x2c,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x2d,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x2e,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x2f,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x30,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x31,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x32,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x33,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x34,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x35,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x36,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x37,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x38,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x39,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x3a,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x3b,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x3c,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x3d,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x3e,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x3f,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x40,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x41,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x42,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x43,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x44,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x45,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x46,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x47,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x48,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x49,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x4a,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x4b,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x4c,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x4d,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x4e,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x4f,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x50,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x51,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x52,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x53,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x57,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x58,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x81,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x82,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x83,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x84,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x85,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x86,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x87,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x88,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x89,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x8a,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x8b,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x8c,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x8d,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x8e,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x8f,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x90,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x91,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x92,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x93,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x94,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x95,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x96,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x97,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x98,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x99,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x9A,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x9B,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x9C,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x9D,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x9E,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0x9F,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA0,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA1,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA2,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA3,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA4,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA5,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA6,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA7,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA8,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xA9,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xAA,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xAB,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xAC,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xAD,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xAE,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xAF,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB0,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB1,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB2,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB3,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB4,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB5,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB6,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB7,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB8,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xB9,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xBA,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xBB,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xBC,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xBD,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xBE,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xBF,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC0,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC1,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC2,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC3,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC4,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC5,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC6,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC7,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC8,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xC9,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xCA,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xCB,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xCD,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xCE,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xCF,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xD0,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xD1,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xD2,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xD3,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xD7,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xD8,
        KeyboardNothingToDo,
        KeyboardFinishedScanCode
    },
    {
        0xE0,
        KeyboardNothingToDo,
        KeyboardWaitForScanCode
    },
    {
        0x10,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x19,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x1C,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x1D,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x20,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x21,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x22,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x24,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x2E,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x30,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x32,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x35,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x38,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x47,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x48,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x49,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x4B,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x4D,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x4F,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x50,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x51,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x52,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x53,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x5B,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x5C,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x5D,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x5E,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x5F,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x63,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x65,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x66,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x67,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x68,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x69,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x6A,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x6B,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x6C,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x6D,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x90,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x99,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x9C,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x9D,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xA0,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xA1,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xA2,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xA4,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xAE,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xB0,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xB2,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xB5,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xB8,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xC7,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xC8,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xC9,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xCB,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xCD,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xCF,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xD0,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xD1,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xD2,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xD3,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xDB,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xDC,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xDD,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xDE,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xDF,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE3,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE5,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE6,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE7,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE8,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE9,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xEA,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xEB,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xEC,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xED,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0x2A,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0xE0,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0x37,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xB7,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0xAA,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
    {
        0xE1,
        KeyboardNothingToDo,
        KeyboardWaitForScanCode
    },
    {
        0x1D,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0x45,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0xE1,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0x9D,
        KeyboardWaitForScanCode,
        KeyboardWaitForScanCode
    },
    {
        0xC5,
        KeyboardWaitForScanCode,
        KeyboardFinishedScanCode
    },
};

#endif