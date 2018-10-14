#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "boot.h"

#define START_CONSOLE   0x000B8000
#define END_CONSOLE     0x000B8FA0
#define SECOND_ROW      0x000B80A0
#define END_SECOND_ROW  0x000B8F00

#define _Bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_Bnd (A,sizeof(long long)-1))))

void printf(char* format, ...);
void printf_f(const char* format, void* argv[]);
int sprintf_f(char* str, const char* format, void* argv[]);
void sprintf(char* str, const char* format, ...);
void printf_delete_last_character();
void* memcpy(void* dest, void* source, size_t num);
int strlen(const char* x);

#endif // _SCREEN_H_