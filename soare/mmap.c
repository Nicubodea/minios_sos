#include "mmap.h"
#include "alloc_phys.h"
#include "screen.h"

extern QWORD __rdrand();

QWORD gSelfmapIndex;

QWORD gVirtualMapStart = KERNEL_BASE_VIRTUAL + STACK_BASE_OFFSET;

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

    pml4map = (PQWORD)(SELFMAP_PML4E);
    pdptmap = (PQWORD)(SELFMAP_PDPTE(pml4i));
    pdmap = (PQWORD)(SELFMAP_PDE(pdpti, pml4i));
    ptmap = (PQWORD)(SELFMAP_PTE(pdi, pdpti, pml4i));

    if (pml4map[pml4i] == 0)
    {
        pml4map[pml4i] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE);
        
        if (pml4map[pml4i] == 0)
        {
            //bail out
            return NULL;
        }

        pml4map[pml4i] |= PT_P;
    }

    if (pdptmap[pdpti] == 0)
    {
        pdptmap[pdpti] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE);
        if (pdptmap[pdpti] == 0)
        {
            //bail out
            return NULL;
        }

        pdptmap[pdpti] |= PT_P;
    }

    if (pdmap[pdi] == 0)
    {
        pdmap[pdi] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE);
        if (pdmap[pdi] == 0)
        {
            //bail out
            return NULL;
        }

        pdmap[pdi] |= PT_P;
    }

    ptmap[pti] = ((QWORD)(PhysicalPage) & (~PAGE_OFFSET)) | ((!CacheType) << 4) | PT_P;

    gVirtualMapStart += PAGE_SIZE;

    return (PVOID)(gVirtualMapStart - PAGE_SIZE + ((QWORD)(PhysicalPage) & PAGE_OFFSET));

}


static PVOID
_SosMapVirtualMemoryInVirtualSpace(
    QWORD DesiredVA,
    PVOID PhysicalPage,
    MEMORY_CACHE_TYPE CacheType,
    QWORD VirtualSpace
)
{
    DWORD pml4i, pdpti, pdi, pti;
    PQWORD pml4map = NULL, pdptmap = NULL, pdmap = NULL, ptmap = NULL;
    PVOID toRet;

    pml4i = PML4_INDEX(DesiredVA);
    pdpti = PDP_INDEX(DesiredVA);
    pdi = PD_INDEX(DesiredVA);
    pti = PT_INDEX(DesiredVA);

    pml4map = SosMapVirtualMemory((PVOID)VirtualSpace, CacheType);
    if (pml4map[pml4i] == 0)
    {
        pml4map[pml4i] = (QWORD)SosAllocPhysAllocate(0, PAGE_SIZE);
        if (pml4map[pml4i] == 0)
        {
            //bail out
            toRet = NULL;
            goto cleanup_and_exit;
        }

        pml4map[pml4i] |= PT_P;
    }

    pdptmap = SosMapVirtualMemory((PVOID)(pml4map[pml4i] & (~PAGE_OFFSET)), SosMemoryUncachable);
    
    if (pdptmap[pdpti] == 0)
    {
        pdptmap[pdpti] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE);
        if (pdptmap[pdpti] == 0)
        {
            //bail out
            toRet = NULL;
            goto cleanup_and_exit;
        }

        pdptmap[pdpti] |= PT_P;
    }

    pdmap = SosMapVirtualMemory((PVOID)(pdptmap[pdpti] & (~PAGE_OFFSET)), SosMemoryUncachable);

    if (pdmap[pdi] == 0)
    {
        pdmap[pdi] = (QWORD)SosAllocPhysAllocate(NULL, PAGE_SIZE);
        if (pdmap[pdi] == 0)
        {
            //bail out
            toRet = NULL;
            goto cleanup_and_exit;
        }

        pdmap[pdi] |= PT_P;
    }

    ptmap = SosMapVirtualMemory((PVOID)(pdmap[pdi] & (~PAGE_OFFSET)), SosMemoryUncachable);

    ptmap[pti] = ((QWORD)(PhysicalPage) & (~PAGE_OFFSET)) | ((!CacheType) << 4) | PT_P;

    toRet = (PVOID)(DesiredVA + ((QWORD)PhysicalPage & PAGE_OFFSET));

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

    ptmap[pti] = 0;
    counter = 0;

    __invlpg(VirtualPage);

    for (DWORD i = 0; i < PAGE_SIZE / sizeof(QWORD); i++)
    {
        if (ptmap[i] == 0)
        {
            counter++;
        }
    }

    if (counter == PAGE_SIZE / sizeof(QWORD))
    {
        SosAllocPhysFree((PVOID)(pdmap[pdi] & (~PAGE_OFFSET)));
        pdmap[pdi] = 0;

        __invlpg(ptmap);
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
        SosAllocPhysFree((PVOID)(pdptmap[pdpti] & (~PAGE_OFFSET)));
        pdptmap[pdpti] = 0;

        __invlpg(pdmap);
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
        SosAllocPhysFree((PVOID)(pml4map[pml4i] & (~PAGE_OFFSET)));
        pml4map[pml4i] = 0;

        __invlpg(pdptmap);
    }
    
}


VOID
SosInitMapping(
    VOID
)
{
    // Get rid of the old page tables and make new page tables

    PQWORD pml4 = SosAllocPhysAllocate(NULL, PAGE_SIZE);
    PQWORD pml4Map;
    DWORD selfMapIndex;
    QWORD currentVA;

    gSelfmapIndex = 0x1FF;

    currentVA = KERNEL_BASE_VIRTUAL;

    // make sure we map the whole kernel + stack in the new virtual space
    for (QWORD i = 0; i < KERNEL_BASE_PHYSICAL + STACK_BASE_OFFSET; i+= PAGE_SIZE)
    {
        if (NULL == _SosMapVirtualMemoryInVirtualSpace(currentVA, (PVOID)i, SosMemoryCachable, (QWORD)pml4))
        {
            printf("[ERROR] Could not map %x!\n", i);
            return;
        }

        currentVA += PAGE_SIZE;
    }

    // set-up the self-map index
    selfMapIndex = __rdrand() % 256 + 256;
    
    printf("[INFO] Self map index: %x\n", selfMapIndex);

    pml4Map = SosMapVirtualMemory(pml4, SosMemoryCachable);

    pml4Map[selfMapIndex] = (QWORD)pml4 | PT_P;
    
    SosUnmapVirtualMemory(pml4Map);

    // now it is safe to put in gSelfmapIndex the new index
    gSelfmapIndex = selfMapIndex;

    __writecr3((QWORD)pml4);

    // restore the initial virtual map start
    gVirtualMapStart = KERNEL_BASE_VIRTUAL + STACK_BASE_OFFSET;

    // we are done!
}


typedef struct _VIRTALLOC_HEADER
{
    DWORD Size;
    DWORD Tag;
    PVOID Phys;
} VIRTALLOC_HEADER, *PVIRTALLOC_HEADER;


PVOID
SosVirtAllocVirtual(
    DWORD Size,
    DWORD Tag
)
{
    PBYTE pPhys = NULL, pVirt = NULL, pLastVirt = NULL, pInitPhys = NULL;
    DWORD totalSize = Size + sizeof(VIRTALLOC_HEADER);
    DWORD nrPages = totalSize % PAGE_SIZE ? (totalSize / PAGE_SIZE) + 1 : totalSize / PAGE_SIZE;
    BOOLEAN succeeded = TRUE;
    PVIRTALLOC_HEADER pHeader;

    pPhys = SosAllocPhysAllocate(NULL, Size + sizeof(VIRTALLOC_HEADER));
    if (NULL == pPhys)
    {
        goto cleanup_and_exit;
    }

    pInitPhys = pPhys;

    pVirt = SosMapVirtualMemory(pPhys, SosMemoryCachable);
    if (NULL == pVirt)
    {
        succeeded = FALSE;
        goto cleanup_and_exit;
    }

    for (DWORD i = 1; i < nrPages; i++)
    {
        PBYTE pV = SosMapVirtualMemory(pPhys, SosMemoryCachable);
        if (NULL == pV)
        {
            succeeded = FALSE;
            goto cleanup_and_exit;
        }
        pLastVirt = pV;
        pPhys += PAGE_SIZE;
    }

cleanup_and_exit:
    if (!succeeded)
    {
        if (NULL != pInitPhys)
        {
            SosAllocPhysFree(pInitPhys);
        }
        if (NULL != pLastVirt)
        {
            while (pLastVirt >= pVirt)
            {
                SosUnmapVirtualMemory(pLastVirt);
                pLastVirt -= PAGE_SIZE;
            }
        }
        return NULL;
    }

    pHeader = (PVOID)pVirt;
    pHeader->Tag = Tag;
    pHeader->Size = Size;
    pHeader->Phys = pInitPhys;

    return pVirt + sizeof(VIRTALLOC_HEADER);
}


VOID
SosVirtFreeVirtual(
    PVOID VirtualAddress,
    DWORD Tag
)
{
    PVIRTALLOC_HEADER pHeader;
    DWORD totalSize, nrPages, i;
    PBYTE pPhys, pVirt;

    pHeader = (PVIRTALLOC_HEADER)(((PBYTE)VirtualAddress) - sizeof(VIRTALLOC_HEADER));
    
    if (pHeader->Tag != Tag)
    {
        printf("[ERROR] Tag %x different from given tag %x\n", pHeader->Tag, Tag);
        __cli();
        __halt();
        return;
    }

    totalSize = pHeader->Size + sizeof(VIRTALLOC_HEADER);
    nrPages = totalSize % PAGE_SIZE ? (totalSize / PAGE_SIZE) + 1 : totalSize / PAGE_SIZE;
    pPhys = pHeader->Phys;

    pVirt = ((PBYTE)VirtualAddress - sizeof(VIRTALLOC_HEADER));

    SosAllocPhysFree(pPhys);

    for (i = 0; i < nrPages; i++)
    {
        SosUnmapVirtualMemory(pVirt);

        pVirt += PAGE_SIZE;
    }
}