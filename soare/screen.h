#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "boot.h"
#include "sosdefines.h"

#define START_CONSOLE   (0x000B8000 + KERNEL_BASE_VIRTUAL)
#define END_CONSOLE     (0x000B8FA0 - 0xA0 + KERNEL_BASE_VIRTUAL)
#define SECOND_ROW      (0x000B80A0 + KERNEL_BASE_VIRTUAL)
#define END_SECOND_ROW  (0x000B8F00 - 0xA0 + KERNEL_BASE_VIRTUAL)

#define START_TOOLBAR   (0x000B8F00 + KERNEL_BASE_VIRTUAL)
#define END_TOOLAR      (0x000B8FA0 + KERNEL_BASE_VIRTUAL)

#define _Bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_Bnd (A,sizeof(long long)-1))))

void printf(char* format, ...);
void printf_f(const char* format, void* argv[]);
int sprintf_f(char* str, const char* format, void* argv[]);
void sprintf(char* str, const char* format, ...);
void printf_delete_last_character();
void* memcpy(void* dest, void* source, size_t num);
int strlen(const char* x);
int strcmp(char* a, char* b);

void printf_pos(char* pos, char* format, ...);
void printf_pos_f(char* pos, char* format, void* argv[]);

#endif // _SCREEN_H_