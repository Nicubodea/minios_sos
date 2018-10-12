#include "mmap.h"

PVOID
SosMapVirtualMemory(
    PVOID PhysicalPage,
    MEMORY_CACHE_TYPE CacheType
    )
{
    UNREFERENCED_PARAMETER(PhysicalPage);
    UNREFERENCED_PARAMETER(CacheType);
    return NULL;
}


VOID
SosUnmapVirtualMemory(
    PVOID PhysicalPage
    )
{
    UNREFERENCED_PARAMETER(PhysicalPage);
}