#ifndef _FS_H_
#define _FS_H_

#include "sosdefines.h"

#define MBR_BYTES_IN_CODE   0x1b4
#define MBR_BYTES_DISK_ID   10
#define MBR_BYTES_PARTITION 16

#define EBPB_BOOT_CODE_SIZE 448

#pragma pack(push)
#pragma pack(1)
typedef struct _FS_PARTITION_TABLE_ENTRY
{
    BYTE BootIndicator;
    BYTE StartingHead;
    struct
    {
        WORD StartingSector : 6;
        WORD StartingCylinder : 10;
    };
    BYTE SystemId;
    BYTE EndingHead;
    struct
    {
        WORD EndingSector : 6;
        WORD EndingCylinder : 10;
    };
    DWORD RelativeSector;
    DWORD TotalSectors;
} FS_PARTITION_TABLE_ENTRY, *PFS_PARTITION_TABLE_ENTRY;


typedef struct _FS_MBR
{
    BYTE Code[MBR_BYTES_IN_CODE];
    BYTE UniqueDiskId[MBR_BYTES_DISK_ID];
    FS_PARTITION_TABLE_ENTRY Partitions[4];
    WORD Signature;
} FS_MBR, *PFS_MBR;

typedef struct _FS_BPB
{
    BYTE JumpCode[3];
    BYTE OemIdentifier[8];
    WORD NumberOfBytesPerSector;
    BYTE NumberOfSectorsPerCluster;
    WORD NumberOfReservedSectors;
    BYTE NumberOfFATs;
    WORD NumberOfDirectoryEntries;
    WORD TotalSectorsSmall;
    BYTE MediaDescriptorType;
    WORD NumberOfSectorsPerFAT;
    WORD NumberOfSectorsPerTrack;
    WORD NumberOfHeads;
    DWORD NumberOfHiddenSectors;
    DWORD TotalSectorsLarge;
    BYTE EBPB[512 - 36];
} FS_BPB, *PFS_BPB;

typedef struct _FS_EBPB_FAT16
{
    BYTE DriveNumber;
    BYTE Reserved;
    BYTE Signature;
    DWORD VolumeSerialNumber;
    BYTE VolumeLabel[11];
    BYTE SystemIdentifier[8];
    BYTE BootCode[EBPB_BOOT_CODE_SIZE];
    WORD BootSignature;
} FS_EBPB_FAT16, *PFS_EBPB_FAT16;

typedef struct _FS_DIRECTORY_ENTRY
{
    BYTE FileName[8];
    BYTE FileExt[3];
    BYTE Attributes;
    BYTE Reserved;
    BYTE CreationTimeTenthOfSeconds;
    struct
    {
        WORD Hours : 5;
        WORD Minutes : 6;
        WORD Seconds : 5;
    } CreationTimeStamp;

    struct
    {
        WORD Year : 7;
        WORD Month : 4;
        WORD Day : 5;
    } CreationDate;

    struct
    {
        WORD Year : 7;
        WORD Month : 4;
        WORD Day : 5;
    } LastAccessedDate;

    WORD ClusterNumberHigh;

    struct
    {
        WORD Hours : 5;
        WORD Minutes : 6;
        WORD Seconds : 5;
    } ModificationTimeStamp;

    struct
    {
        WORD Year : 7;
        WORD Month : 4;
        WORD Day : 5;
    } ModificationDate;

    WORD ClusterNumberLow;
    DWORD FileSize;
};

#pragma pack(pop)

VOID
SosFsInitFileSystem(
    VOID
);

#endif