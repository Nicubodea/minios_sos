#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "boot.h"

#define START_CONSOLE   0x000B8000
#define END_CONSOLE     0x000B8FA0
#define SECOND_ROW      0x000B80A0
#define END_SECOND_ROW  0x000B8F00

void printf(char* format, ...);
void printf_f(const char* format, void* argv[]);
int sprintf_f(char* str, const char* format, void* argv[]);
void sprintf(char* str, const char* format, ...);

#endif // _SCREEN_H_