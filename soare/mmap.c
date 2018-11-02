#include "mmap.h"
#include "alloc_phys.h"

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


VOID
SosInitMapping(
    VOID
)
{
    // Get rid of the old page tables and make new page tables



}