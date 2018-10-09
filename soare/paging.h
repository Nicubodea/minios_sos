#ifndef _PAGING_H_
#define _PAGING_H_
#include "sosdefines.h"

typedef struct _LEGACY_PAGE_TABLE {
    PDWORD PhysicalAddresses;
} LEGACY_PAGE_TABLE, *PLEGACY_PAGE_TABLE; 

typedef struct _LEGACY_PAGE_DIRECTORY
{
    PLEGACY_PAGE_TABLE PageTables;
} LEGACY_PAGE_DIRECTORY, *PLEGACY_PAGE_DIRECTORY;



#endif _PAGING_H_