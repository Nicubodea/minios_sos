#include "mmap.h"
#include "alloc_phys.h"
#include "screen.h"

extern QWORD __rdrand();

QWORD gSelfmapIndex;

QWORD gVirtualMapStart = KERNEL_BASE_VIRTUAL + STACK_BASE_OFFSET;
QWORD gVirtualKernelVA = KERNEL_BASE_VIRTUAL;

#define PML4_INDEX(x)             (DWORD)(((x) & 0x0000ff8000000000) >> 39)
#define PDP_INDEX(x)              (DWORD)(((x) & 0x0000007fc0000000) >> 30)
#define PD_INDEX(x)               (DWORD)(((x) & 0x000000003fe00000) >> 21)
#define PT_INDEX(x)               (DWORD)(((x) & 0x00000000001ff000) >> 12)

#define PT_P                      1

#define SELFMAP_PML4E                       0xFFFF800000000000 | ((QWORD)(gSelfmapIndex) << 39) | ((QWORD)(gSelfmapIndex) << 30) |\
                                            ((QWORD)(gSelfmapIndex) << 21) | ((QWORD)(gSelfmapIndex) << 12)

#define SELFMAP_PDPTE(pdpt)                 0xFFFF800000000000 | ((QWORD)(gSelfmapIndex) << 39) | ((QWORD)(gSelfmapIndex) << 30) |\
                                            ((QWORD)(gSelfmapIndex) << 21) | ((QWORD)(pdpt & PAGE_OFFSET) << 12)       

#define SELFMAP_PDE(pd, pdpt)               0xFFFF800000000000 | ((QWORD)(gSelfmapIndex) << 39) | ((QWORD)(gSelfmapIndex) << 30) |\
                                            ((QWORD)(pdpt & PAGE_OFFSET) << 21) | ((QWORD)(pd & PAGE_OFFSET) << 12)

#define SELFMAP_PTE(pt, pd, pdpt)           0xFFFF800000000000 | ((QWORD)(gSelfmapIndex) << 39) | ((QWORD)(pdpt & PAGE_OFFSET) << 30) |\
                                            ((QWORD)(pd & PAGE_OFFSET) << 21) | ((QWORD)(pt & PAGE_OFFSET) << 12)

PVOID
SosMapVirtualMemory(
    PVOID PhysicalPage,
    MEMORY_CACHE_TYPE CacheType
    )
{
    DWORD pml4i, pdpti, pdi, pti;
    PQWORD pml4map, pdptmap, pdmap, ptmap;

    pml4i = PML4_INDEX(gVirtualMapStart);
    pdpti = PDP_INDEX(gVirtualMapStart);
    pdi = PD_INDEX(gVirtualMapStart);
    pti = PT_INDEX(gVirtualMapStart);

    //printf("a\n");

    pml4map = (PQWORD)(SELFMAP_PML4E);
    pdptmap = (PQWORD)(SELFMAP_PDPTE(pml4i));
    pdmap = (PQWORD)(SELFMAP_PDE(pdpti, pml4i));
    ptmap = (PQWORD)(SELFMAP_PTE(pdi, pdpti, pml4i));

    if (pml4map[pml4i] == 0)
    {
        pml4map[pml4i] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE) | PT_P;
        
        if (pml4map[pml4i] == 0)
        {
            //bail out
            return NULL;
        }
    }
    //printf("map pml4e %x\n", pml4map[pml4i]);
    if (pdptmap[pdpti] == 0)
    {
        pdptmap[pdpti] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE) | PT_P;
        if (pdptmap[pdpti] == 0)
        {
            //bail out
            return NULL;
        }
    }
    //printf("map pdpte %x\n", pdptmap[pdpti]);
    if (pdmap[pdi] == 0)
    {
        pdmap[pdi] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE) | PT_P;
        if (pdmap[pdi] == 0)
        {
            //bail out
            return NULL;
        }
    }
    //printf("map pde %x\n", pdmap[pdi]);

    ptmap[pti] = ((QWORD)(PhysicalPage) & (~PAGE_OFFSET)) | ((!CacheType) << 4) | PT_P;

    //printf("mapped pte %x\n", pti);

    gVirtualMapStart += PAGE_SIZE;

    // flush the TLBs
    __writecr3(__readcr3());

    return (PVOID)(gVirtualMapStart - PAGE_SIZE + ((QWORD)(PhysicalPage) & PAGE_OFFSET));

}


static PVOID
_SosMapVirtualMemoryInVirtualSpace(
    PVOID PhysicalPage,
    MEMORY_CACHE_TYPE CacheType,
    QWORD VirtualSpace
)
{
    DWORD pml4i, pdpti, pdi, pti;
    PQWORD pml4map = NULL, pdptmap = NULL, pdmap = NULL, ptmap = NULL;
    PVOID toRet;

    pml4i = PML4_INDEX(gVirtualKernelVA);
    pdpti = PDP_INDEX(gVirtualKernelVA);
    pdi = PD_INDEX(gVirtualKernelVA);
    pti = PT_INDEX(gVirtualKernelVA);

    printf("[INFO] phys %x va %x\n", PhysicalPage, gVirtualKernelVA);

    pml4map = SosMapVirtualMemory((PVOID)VirtualSpace, CacheType);
    if (pml4map[pml4i] == 0)
    {
        pml4map[pml4i] = (QWORD)SosAllocPhysAllocate(0, PAGE_SIZE) | PT_P;
        if (pml4map[pml4i] == 0)
        {
            //bail out
            toRet = NULL;
            goto cleanup_and_exit;
        }
    }

    //printf("mapped pml4 @ %x\n", pml4map);

    pdptmap = SosMapVirtualMemory((PVOID)(pml4map[pml4i] & (~PAGE_OFFSET)), CacheType);
    
    if (pdptmap[pdpti] == 0)
    {
        pdptmap[pdpti] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE) | PT_P;
        if (pdptmap[pdpti] == 0)
        {
            //bail out
            toRet = NULL;
            goto cleanup_and_exit;
        }
    }

    //printf("mapped pdpt @ %x\n", pdptmap);

    pdmap = SosMapVirtualMemory((PVOID)(pdptmap[pdpti] & (~PAGE_OFFSET)), CacheType);

    if (pdmap[pdi] == 0)
    {
        pdmap[pdi] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE) | PT_P;
        if (pdmap[pdi] == 0)
        {
            //bail out
            toRet = NULL;
            goto cleanup_and_exit;
        }
    }

    //printf("mapped pd @ %x\n", pdmap);

    ptmap = SosMapVirtualMemory((PVOID)(pdmap[pdi] & (~PAGE_OFFSET)), CacheType);

    ptmap[pti] = ((QWORD)(PhysicalPage) & (~PAGE_OFFSET)) | ((!CacheType) << 4) | PT_P;

    //printf("mapped pt @ %x\n", ptmap);

    gVirtualKernelVA += PAGE_SIZE;

    toRet = (PVOID)(gVirtualKernelVA - PAGE_SIZE + ((QWORD)PhysicalPage & PAGE_OFFSET));

cleanup_and_exit:
    if (pml4map != NULL)
    {
        SosUnmapVirtualMemory(pml4map);
    }
    if (pdptmap != NULL)
    {
        SosUnmapVirtualMemory(pdptmap);
    }
    if (pdmap != NULL)
    {
        SosUnmapVirtualMemory(pdmap);
    }
    if (ptmap != NULL)
    {
        SosUnmapVirtualMemory(ptmap);
    }

    return toRet;
}


VOID
SosUnmapVirtualMemory(
    PVOID VirtualPage
    )
{
    DWORD pml4i, pdpti, pdi, pti;
    PQWORD pml4map, pdptmap, pdmap, ptmap;
    DWORD counter;

    pml4i = PML4_INDEX((QWORD)VirtualPage);
    pdpti = PDP_INDEX((QWORD)VirtualPage);
    pdi = PD_INDEX((QWORD)VirtualPage);
    pti = PT_INDEX((QWORD)VirtualPage);

    pml4map = (PQWORD)(SELFMAP_PML4E);
    pdptmap = (PQWORD)(SELFMAP_PDPTE(pml4i));
    pdmap = (PQWORD)(SELFMAP_PDE(pdpti, pml4i));
    ptmap = (PQWORD)(SELFMAP_PTE(pdi, pdpti, pml4i));

    //printf("unmapping va %x\n", VirtualPage);

    //printf("unmap pte %x\n", ptmap[pti]);
    ptmap[pti] = 0;
    counter = 0;

    for (DWORD i = 0; i < PAGE_SIZE / sizeof(QWORD); i++)
    {
        if (ptmap[i] == 0)
        {
            counter++;
        }
    }

    if (counter == PAGE_SIZE / sizeof(QWORD))
    {
        //printf("unmap pde %x\n", pdmap[pdi]);
        SosAllocPhysFree((PVOID)(pdmap[pdi] & (~PAGE_OFFSET)));
        pdmap[pdi] = 0;

    }
    else
    {
        // no point in checking further as the current PT is still referenced
        return;
    }

    counter = 0;

    for (DWORD i = 0; i < PAGE_SIZE / sizeof(QWORD); i++)
    {
        if (pdmap[i] == 0)
        {
            counter++;
        }
    }

    if (counter == PAGE_SIZE / sizeof(QWORD))
    {
        //printf("unmap pdpte %x\n", pdptmap[pdpti]);
        SosAllocPhysFree((PVOID)(pdptmap[pdpti] & (~PAGE_OFFSET)));
        pdptmap[pdpti] = 0;
    }
    else
    {
        // no point in checking further as the current PD is still referenced
        return;
    }

    counter = 0;

    for (DWORD i = 0; i <  PAGE_SIZE / sizeof(QWORD); i++)
    {
        if (pdptmap[i] == 0)
        {
            counter++;
        }
    }

    if (counter == PAGE_SIZE / sizeof(QWORD))
    {
        //printf("unmap pml4e %x\n", pml4map[pml4i]);
        SosAllocPhysFree((PVOID)(pml4map[pml4i] & (~PAGE_OFFSET)));
        pml4map[pml4i] = 0;
    }
    
}


VOID
SosInitMapping(
    VOID
)
{
    // Get rid of the old page tables and make new page tables

    PQWORD pml4 = SosAllocPhysAllocate(NULL, PAGE_SIZE);

    gSelfmapIndex = 0x1FF;

    // make sure we map the whole kernel + stack in the new virtual space
    for (QWORD i = KERNEL_BASE_PHYSICAL; i < KERNEL_BASE_PHYSICAL + STACK_BASE_OFFSET; i+= PAGE_SIZE)
    {
        if (NULL == _SosMapVirtualMemoryInVirtualSpace((PVOID)i, SosMemoryCachable, (QWORD)pml4))
        {
            printf("[ERROR] Could not map %x!\n", i);
            return;
        }
    }

    // set-up the self-map index
    gSelfmapIndex = __rdrand() % 256 + 256;

    printf("[INFO] Self map index: %x\n", gSelfmapIndex);

    //pml4 = 

    //pml4[gSelfmapIndex] = (QWORD)pml4 | PT_P;

    __writecr3((QWORD)pml4);

    gVirtualMapStart = KERNEL_BASE_VIRTUAL + STACK_BASE_OFFSET;

    // we are done!
}