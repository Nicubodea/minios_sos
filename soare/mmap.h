#ifndef _MMAP_H_
#define _MMAP_H_
#include "sosdefines.h"

typedef enum _MEMORY_CACHE_TYPE
{
    SosMemoryUncachable,
    SosMemoryCachable,
    SosMemoryUnknown
} MEMORY_CACHE_TYPE;

PVOID
SosMapVirtualMemory(
    PVOID PhysicalPage,
    MEMORY_CACHE_TYPE CacheType
);

VOID
SosUnmapVirtualMemory(
    PVOID VirtualPage
    );

PVOID
SosVirtAllocVirtual(
    DWORD Size,
    DWORD Tag
);

VOID
SosInitMapping(
    VOID
);

VOID
SosVirtFreeVirtual(
    PVOID VirtualAddress,
    DWORD Tag
);


#endif