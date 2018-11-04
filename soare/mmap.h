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


VOID
SosInitMapping(
    VOID
);


#endif