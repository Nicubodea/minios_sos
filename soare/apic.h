#ifndef _APIC_H_
#define _APIC_H_

#include "sosdefines.h"

BOOLEAN
SosApicIsApicAvailable(
    VOID
    );

DWORD
SosApicGetCurrentApicId(
    VOID
    );

#endif