#include "paging.h"

// Note: we are very smekers and use the ASM reserved space as a temporary heap until we have an allocator
//PBYTE gTempHeap = KERNEL_BASE_PHYSICAL + 0x4C0;

/*
VOID
SosInitLegacyPageTables(
    QWORD* RootPt
    )
{
    //if(((DWORD)gTempHeap & PAGE_OFFSET))
}
*/