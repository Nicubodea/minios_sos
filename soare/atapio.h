#ifndef _ATA_PIO_H_
#define _ATA_PIO_H_

#include "sosdefines.h"

#define ATAPIO_PORT_BASE                    0x1F0
#define ATAPIO_DATA_REG_RW                  (ATAPIO_PORT_BASE)
#define ATAPIO_ERROR_REG_R                  (ATAPIO_PORT_BASE+1)
#define ATAPIO_FEATURES_REG_W               (ATAPIO_PORT_BASE+1)
#define ATAPIO_SEC_CNT_REG_RW               (ATAPIO_PORT_BASE+2)
#define ATAPIO_SEC_NR_REG_RW                (ATAPIO_PORT_BASE+3)
#define ATAPIO_CYLINDER_LO_REG_RW           (ATAPIO_PORT_BASE+4)
#define ATAPIO_CYLINDER_HI_REG_RW           (ATAPIO_PORT_BASE+5)
#define ATAPIO_DRIVE_HEAD_REG_RW            (ATAPIO_PORT_BASE+6)
#define ATAPIO_STATUS_REG_R                 (ATAPIO_PORT_BASE+7)
#define ATAPIO_COMMAND_REG_W                (ATAPIO_PORT_BASE+7)

#define ATAPIO_CONTROL_BASE                 0x3F6
#define ATAPIO_ALTERNATE_STATUS_REG_R       (ATAPIO_CONTROL_BASE+0)
#define ATAPIO_DEVICE_CONTROL_REG_W         (ATAPIO_CONTROL_BASE+0)
#define ATAPIO_DRIVE_ACCES_REG_R            (ATAPIO_CONTROL_BASE+1)

#define ERR_AMNF                            (1<<0)
#define ERR_TKZNF                           (1<<1)
#define ERR_ABRT                            (1<<2)
#define ERR_MCR                             (1<<3)
#define ERR_IDNF                            (1<<4)
#define ERR_MC                              (1<<5)
#define ERR_UNC                             (1<<6)
#define ERR_BBK                             (1<<7)

#define DRVHD_HEAD_BLOCK(x)                 ((x) & 0xF)
#define DRVHD_DRV                           (1<<4)
#define DRVHD_RESERVED_1                    (1<<5)
#define DRVHD_LBA                           (1<<6)
#define DRVHD_RESERVED_2                    (1<<7)

#define STATUS_ERR                          (1<<0)
#define STATUS_IDX                          (1<<1)
#define STATUS_CORR                         (1<<2)
#define STATUS_DRQ                          (1<<3)
#define STATUS_SRV                          (1<<4)
#define STATUS_DF                           (1<<5)
#define STATUS_RDY                          (1<<6)
#define STATUS_BSY                          (1<<7)

#define CTRL_nIEN                           (1<<1)
#define CTRL_SRST                           (1<<2)
#define CTRL_HOB                            (1<<7)

#define DADDR_DS0                           (1<<0)
#define DADDR_DS1                           (1<<1)
#define DADDR_HS0_3                         (0xF<<2)
#define DADDR_WTG                           (1<<6)

#define COMMAND_IDENTIFY                    0xEC
#define COMMAND_READ_PIO_28                 0x20
#define COMMAND_READ_PIO_48                 0x24

#define PIO_MAX_RETRIES                     4

#define PIO_SUCCESS                         0
#define PIO_RESET_FAILED_AFTER_MAX_RETRY    1
#define PIO_STATUS_FAILED_WITH_ERR          2

DWORD
SosAtaPioReadDiskLba28(
    DWORD Lba28,
    BYTE SecCnt,
    WORD* ReturnBuff
);

DWORD
SosAtaPioReadDiskLba48(
    QWORD Lba48,
    WORD SecCnt,
    WORD* ReturnBuff
);


#endif