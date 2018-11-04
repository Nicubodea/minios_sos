#include "alloc_phys.h"
#include "screen.h"

static QWORD gCurrentPhysical = PHYSICAL_HEAP_START;
static QWORD gBitmap[(PHYSICAL_HEAP_END - PHYSICAL_HEAP_START) / (0x1000 * 64)];
static DWORD gAllocSizes[(PHYSICAL_HEAP_END - PHYSICAL_HEAP_START) / (0x1000)];

#define IS_BIT_SET(x) !!(gBitmap[x/64] & (1LL<<(x % 64)))
#define SET_BIT(x)    (gBitmap[x/64] |= (1LL<<(x % 64)))
#define CLEAR_BIT(x)  (gBitmap[x/64] &= ~(1LL<<(x % 64)))

PVOID
SosAllocPhysAllocate(
    PVOID DesiredPhysicalAddress,
    DWORD Size
)
{
    QWORD desired = (QWORD)(DesiredPhysicalAddress) & (~PAGE_OFFSET);
    QWORD chosenAddress = 0;
    BOOLEAN goneBack = FALSE;
    DWORD currentCnt = 0, totalCnt;

    if (Size == 0)
    {
        return NULL;
    }

    totalCnt = Size % PAGE_SIZE ? (Size / PAGE_SIZE) + 1 : Size / PAGE_SIZE;

    if (DesiredPhysicalAddress == NULL)
    {
        goto _choose_address;
    }
    
    if (desired < PHYSICAL_HEAP_START || desired + Size > PHYSICAL_HEAP_END)
    {
        // if NULL was not provided in Desired Physical Address & desired physical address is not in our range, bail out
        printf("[ERROR] Desired address out of range\n");
        return NULL;
    }

    // verify if all pages in range (desired, desired + size) are free
    for (QWORD current = desired; current < desired + Size; current += PAGE_SIZE)
    {

        if (IS_BIT_SET(PAGE_NUMBER(current)))
        {
            // page is already allocated
            printf("[ERROR] Address %x already allocated\n", current);
            return NULL;
        }
    }

    chosenAddress = desired;
    goto _skip_chose_another_address;

_choose_address:
    for (QWORD current = gCurrentPhysical; ; current += PAGE_SIZE)
    {
        if (current >= PHYSICAL_HEAP_END)
        {
            current = PHYSICAL_HEAP_START;
            currentCnt = 0;

            if (goneBack)
            {
                // we already went through all ranges and we didn't found anything
                return NULL;
            }

            goneBack = TRUE;
        }

        if (!IS_BIT_SET(PAGE_NUMBER(current)))
        {
            currentCnt++;
        }
        else
        {
            currentCnt = 0;
        }

        if (currentCnt == totalCnt)
        {
            chosenAddress = current - (totalCnt - 1) * PAGE_SIZE;
            break;
        }
        
    }

_skip_chose_another_address:
    
    gAllocSizes[PAGE_NUMBER(chosenAddress)] = totalCnt;

    gCurrentPhysical = chosenAddress + totalCnt * PAGE_SIZE;

    for (QWORD current = chosenAddress; totalCnt; totalCnt--, current += PAGE_SIZE)
    {
        SET_BIT(PAGE_NUMBER(current));
    }

    return (PVOID)chosenAddress;
}


VOID
SosAllocPhysFree(
    PVOID Address
)
{
    QWORD address = (QWORD)(Address);

    if (address < PHYSICAL_HEAP_START || address > PHYSICAL_HEAP_END)
    {
        // for now return but we should do something bad
        printf("[ERROR] Invalid free address %x! Not in range\n", address);
        return;
    }

    if (gAllocSizes[PAGE_NUMBER(address)] == 0)
    {
        // for now return, but this is an invalid free
        printf("[ERROR] Invalid free address! Size is 0\n");
        return;
    }

    for (QWORD current = address;
        gAllocSizes[PAGE_NUMBER(address)];
        gAllocSizes[PAGE_NUMBER(address)]--, current += PAGE_SIZE)
    {
        if (!IS_BIT_SET(PAGE_NUMBER(current)))
        {
            // something is bad
            printf("[ERROR] Already freed paged %x!\n", current);
            continue;
        }

        CLEAR_BIT(PAGE_NUMBER(current));
    }
    
}


VOID
SosAllocPhysPrintAllocs(
    VOID
)
{
    for (QWORD current = PHYSICAL_HEAP_START; current < PHYSICAL_HEAP_END; current += PAGE_SIZE)
    {
        if (gAllocSizes[PAGE_NUMBER(current)])
        {
            printf("Allocation [%x (%d) - %x (%d)]\n", current,
                current,
                current + gAllocSizes[PAGE_NUMBER(current)] * PAGE_SIZE,
                current + gAllocSizes[PAGE_NUMBER(current)] * PAGE_SIZE
                );
        }
    }
}