#ifndef _ALLOC_PHYS_H_
#define _ALLOC_PHYS_H_

#include "sosdefines.h"

#define PHYSICAL_HEAP_START     (KERNEL_BASE_PHYSICAL + STACK_BASE_OFFSET)
#define PHYSICAL_HEAP_END       (PHYSICAL_HEAP_START  + 0xC0000000) // TODO: memory map

#endif