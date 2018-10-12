#ifndef _SOS_DEFINES_H_
#define _SOS_DEFINES_H_

#pragma warning (disable: 4005)

typedef void VOID;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long long QWORD;

typedef VOID* PVOID;
typedef BYTE* PBYTE;
typedef WORD* PWORD;
typedef DWORD* PDWORD;
typedef QWORD* PQWORD;

typedef BYTE BOOLEAN;
typedef BOOLEAN* PBOOLEAN;

#define TRUE 1
#define FALSE 0
#define NULL ((PVOID)0)

#define UNREFERENCED_PARAMETER(a) a

#define CR0_PE          (1<<0)
#define CR0_MP          (1<<1)
#define CR0_EM          (1<<2)
#define CR0_TS          (1<<3)
#define CR0_ET          (1<<4)
#define CR0_NE          (1<<5)
#define CR0_WP          (1<<16)
#define CR0_AM          (1<<18)
#define CR0_NW          (1<<29)
#define CR0_CD          (1<<30)
#define CR0_PG          (1<<31)

#define CR4_VME         (1<<0)
#define CR4_PVI         (1<<1)
#define CR4_TSD         (1<<2)
#define CR4_DE          (1<<3)
#define CR4_PSE         (1<<4)
#define CR4_PAE         (1<<5)
#define CR4_MCE         (1<<6)
#define CR4_PGE         (1<<7)
#define CR4_PCE         (1<<8)
#define CR4_OXFXSR      (1<<9)
#define CR4_OSXMMEXCPT  (1<<10)
#define CR4_UMIP        (1<<11)
#define CR4_LA57        (1<<12)
#define CR4_VMXE        (1<<13)
#define CR4_SMXE        (1<<14)
#define CR4_FSGSBASE    (1<<16)
#define CR4_PCIDE       (1<<17)
#define CR4_OSXSAVE     (1<<18)
#define CR4_SMEP        (1<<20)
#define CR4_SMAP        (1<<21)
#define CR4_PKE         (1<<22)

#define IA32_MSR_EFER   0xC0000080
#define IA32_APIC_BASE  0x1B

#define EFER_SCE        (1<<0)
#define EFER_LME        (1<<8)
#define EFER_LMA        (1<<10)
#define EFER_NXE        (1<<11)
#define EFER_SVME       (1<<12)
#define EFER_LMSLE      (1<<13)
#define EFER_FFXSR      (1<<14)
#define EFER_TCE        (1<<15)


#define KERNEL_BASE_PHYSICAL    0x200000

#define PAGE_OFFSET             0xFFF
#define PAGE_SIZE               0x1000

#endif