#include "alloc_phys.h"

extern void __rdrand();

static QWORD gCurrentPhysical = PHYSICAL_HEAP_START;

PVOID
SosAllocPhysAllocate(
    PVOID DesiredPhysicalAddress,
    DWORD Size
)
{
    QWORD desired = (QWORD)DesiredPhysicalAddress;
    if (DesiredPhysicalAddress != NULL && (desired < PHYSICAL_HEAP_START || desired > PHYSICAL_HEAP_END))
    {
        // if NULL was not provided in Desired Physical Address & desired physical address is not in our range, bail out
        return NULL;
    }
    


    return NULL;
}