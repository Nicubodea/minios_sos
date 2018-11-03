#ifndef _ALLOC_PHYS_H_
#define _ALLOC_PHYS_H_

#include "sosdefines.h"

#define PHYSICAL_HEAP_START     (KERNEL_BASE_PHYSICAL + STACK_BASE_OFFSET)
#define PHYSICAL_HEAP_END       (PHYSICAL_HEAP_START  + 1024*1024*64) // TODO: memory map

#define PAGE_NUMBER(x)          (((x) - PHYSICAL_HEAP_START) / PAGE_SIZE)

#endif

PVOID
SosAllocPhysAllocate(
    PVOID DesiredPhysicalAddress,
    DWORD Size
);

VOID
SosAllocPhysFree(
    PVOID Address
);

VOID
SosAllocPhysPrintAllocs(
    VOID
);