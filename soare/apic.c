#include "apic.h"
#include "screen.h"

BOOLEAN
SosApicIsApicAvailable(
    VOID
    )
{
    int regs[4];
    __cpuid(regs, 1);

    // Intel SDM 10.4.2: Beginning with the P6 family processors, the presence or absence of an on-chip local APIC can be detected using
    // the CPUID instruction.When the CPUID instruction is executed with a source operand of 1 in the EAX register, bit
    // 9 of the CPUID feature flags returned in the EDX register indicates the presence(set) or absence(clear) of a local
    // APIC
    return !!(regs[3] & (1 << 9));
}



DWORD
SosApicGetCurrentApicId(
    VOID
    )
{
    int regs[4];
    __cpuid(regs, 1);

    return (regs[1] >> 24);
}