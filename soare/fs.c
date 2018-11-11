#include "fs.h"
#include "atapio.h"
#include "screen.h"

FS_MBR gMbr;
FS_BPB gBpb;

WORD gBuff[256];

VOID
SosFsInitFileSystem(
    VOID
)
{
    DWORD pioStatus;
    DWORD i;
    DWORD startSector = 0, endSector, partitionIndex;
    BOOLEAN found = FALSE;
    PFS_EBPB_FAT16 pEbpbFat16;
    DWORD totalSectorsBpb, fatSize, rootDirsSize, firstDataSect, firstFatSect, nrDataSectors, nrClusters;
    DWORD firstRootDirSect;

    pioStatus = SosAtaPioRead(0, 1, (PWORD)&gMbr);
    if (pioStatus != PIO_SUCCESS)
    {
        printf("[ERROR] Failed to read MBR: %x\n", pioStatus);
        return;
    }

    // find the partition on which we booted
    for (i = 0; i < 4; i++)
    {
        if (gMbr.Partitions[i].BootIndicator & 0x80)
        {
            printf("[FS] Partition index: %d\n", i);
            printf("[FS] Start first sector: %x\n", gMbr.Partitions[i].RelativeSector * 512);
            printf("[FS] End first sector: %x\n", gMbr.Partitions[i].RelativeSector * 512 + gMbr.Partitions[i].TotalSectors * 512);
        
            startSector = gMbr.Partitions[i].RelativeSector;
            endSector = gMbr.Partitions[i].RelativeSector + gMbr.Partitions[i].TotalSectors;
            partitionIndex = i;
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        printf("[ERROR] Failed to find a partition\n");
        return;
    }

    pioStatus = SosAtaPioRead(startSector, 1, (PWORD)&gBpb);
    if (pioStatus != PIO_SUCCESS)
    {
        printf("[ERROR] Failed to read BPB: %x\n", pioStatus);
        return;
    }

    totalSectorsBpb = gBpb.TotalSectorsSmall == 0 ? gBpb.TotalSectorsLarge : gBpb.TotalSectorsSmall;
    fatSize = gBpb.NumberOfSectorsPerFAT;
    if (fatSize == 0)
    {
        printf("[ERROR] Unsupported FAT type!\n");
        return;
    }

    rootDirsSize = (gBpb.NumberOfDirectoryEntries * 32 + (gBpb.NumberOfBytesPerSector - 1)) / (gBpb.NumberOfBytesPerSector);
    firstDataSect = gBpb.NumberOfReservedSectors + (gBpb.NumberOfFATs * fatSize) + rootDirsSize;
    firstFatSect = gBpb.NumberOfReservedSectors;
    nrDataSectors = totalSectorsBpb - (gBpb.NumberOfReservedSectors + (gBpb.NumberOfFATs * fatSize) + rootDirsSize);
    nrClusters = nrDataSectors / gBpb.NumberOfSectorsPerCluster;

    if (nrClusters < 4085 || nrClusters >= 65525)
    {
        printf("[ERROR] Unsupported FAT type due to mismatch number of clusters!\n");
        return;
    }

    pEbpbFat16 = (PFS_EBPB_FAT16)gBpb.EBPB;
    pEbpbFat16->VolumeLabel[10] = 0;
    pEbpbFat16->SystemIdentifier[7] = 0;

    printf("[FS] OEM: %s\n", gBpb.OemIdentifier);

    printf("[FS] Volume label: %s\n", pEbpbFat16->VolumeLabel);
    printf("[FS] System identifier: %s\n", pEbpbFat16->SystemIdentifier);

    firstRootDirSect = startSector + firstDataSect - rootDirsSize;
    
    pioStatus = SosAtaPioRead(firstRootDirSect, 1, gBuff);
    if (pioStatus != PIO_SUCCESS)
    {
        printf("[ERROR] Failed to read rootdir\n");
        return;
    }


    

}