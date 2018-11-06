#ifndef _LISTS_H_
#define _LISTS_H_

#include "sosdefines.h"

#define RESTRICTED_POINTER __restrict
typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, *RESTRICTED_POINTER PRLIST_ENTRY;

#define CONTAINING_RECORD(address, type, field)     ((type *)((PCHAR)(address) - (ULONG_PTR)(&((type *)0)->field)))


VOID
InitializeListHead(
    PLIST_ENTRY ListHead
);

VOID
InsertHeadList(
    PLIST_ENTRY ListHead,
    PLIST_ENTRY Entry
);

VOID
InsertTailList(
    PLIST_ENTRY ListHead,
    PLIST_ENTRY Entry
);

BOOLEAN
IsListEmpty(
    const LIST_ENTRY *ListHead
);

BOOLEAN
RemoveEntryList(
    PLIST_ENTRY Entry
);

PLIST_ENTRY
RemoveHeadList(
    PLIST_ENTRY ListHead
);

PLIST_ENTRY
RemoveTailList(
    PLIST_ENTRY ListHead
);


#endif