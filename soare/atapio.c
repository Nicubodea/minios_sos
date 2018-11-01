#include "atapio.h"
#include "screen.h"

BOOLEAN
SosAtaPioVerifyStatusForErrors(
    BYTE Status
)
{
    if ((Status & STATUS_ERR) != 0)
    {
        printf("[ERROR] Error register: %x\n", __inbyte(ATAPIO_ERROR_REG_R));
        return TRUE;
    }

    return FALSE;
}


DWORD
SosAtaPioReset(
    VOID
    )
{
    DWORD i;
    BYTE status;
    DWORD retries = PIO_MAX_RETRIES;

    printf("[INFO] SosAtaPioReset called\n");

    while (retries > 0)
    {
        __outbyte(ATAPIO_DEVICE_CONTROL_REG_W, CTRL_SRST);

        // poll 4 retries
        for (i = 0; i < PIO_MAX_RETRIES; i++)
        {
            __inbyte(ATAPIO_STATUS_REG_R);
        }

        status = __inbyte(ATAPIO_STATUS_REG_R);
        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }

        if ((status & STATUS_BSY) == 0 && (status & STATUS_RDY) != 0)
        {
            return PIO_SUCCESS;
        }

        retries--;
    }

    return PIO_RESET_FAILED_AFTER_MAX_RETRY;
}


DWORD
SosAtaPioReadDiskLba28(
    DWORD Lba28,
    BYTE SecCnt,
    WORD* ReturnBuff
    )
{
    BYTE status;
    DWORD i;
    DWORD retries = 0;

    status = __inbyte(ATAPIO_STATUS_REG_R);

    while (((status & STATUS_BSY) != 0 || (status & STATUS_DRQ) != 0) && retries < PIO_MAX_RETRIES)
    {
        // the device is busy, try again
        status = __inbyte(ATAPIO_STATUS_REG_R);

        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }

        retries++;
    }

    if (retries == PIO_MAX_RETRIES)
    {
        DWORD pioStatus = SosAtaPioReset();
        if (PIO_SUCCESS != pioStatus)
        {
            return pioStatus;
        }
    }

    retries = 0;

    while ((status & STATUS_RDY) == 0 && retries < PIO_MAX_RETRIES)
    {
        // the device is not ready, try again
        status = __inbyte(ATAPIO_STATUS_REG_R);

        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }

        retries++;
    }

    if (retries == PIO_MAX_RETRIES)
    {
        DWORD pioStatus = SosAtaPioReset();
        if (PIO_SUCCESS != pioStatus)
        {
            return pioStatus;
        }
    }

    // select device 0, set reserved bits and put the 24-27 bits of the LBA
    __outbyte(ATAPIO_DRIVE_HEAD_REG_RW, DRVHD_LBA | DRVHD_RESERVED_1 | DRVHD_RESERVED_2 | ((Lba28 >> 24) & 0xF));

    __outbyte(ATAPIO_ERROR_REG_R, 0);
    __outbyte(ATAPIO_SEC_CNT_REG_RW, SecCnt & 0xFF);
    __outbyte(ATAPIO_SEC_NR_REG_RW, (Lba28 & 0xFF));
    __outbyte(ATAPIO_CYLINDER_LO_REG_RW, ((Lba28 >> 8) & 0xFF));
    __outbyte(ATAPIO_CYLINDER_HI_REG_RW, ((Lba28 >> 16) & 0xFF));

    __outbyte(ATAPIO_COMMAND_REG_W, COMMAND_READ_PIO_28);

    status = __inbyte(ATAPIO_STATUS_REG_R);

    while ((status & STATUS_DRQ) == 0)
    {
        // wait until the drive is ready to transfer data
        status = __inbyte(ATAPIO_STATUS_REG_R);

        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }
    }

    for (i = 0; i < (DWORD)SecCnt * 256; i++)
    {
        ReturnBuff[i] = __inword(ATAPIO_DATA_REG_RW);
    }

    return PIO_SUCCESS;
}


DWORD
SosAtaPioReadDiskLba48(
    QWORD Lba48,
    WORD SecCnt,
    WORD* ReturnBuff
    )
{
    BYTE status;
    DWORD i;

    DWORD retries = 0;

    status = __inbyte(ATAPIO_STATUS_REG_R);

    while (((status & STATUS_BSY) != 0 || (status & STATUS_DRQ) != 0) && retries < PIO_MAX_RETRIES)
    {
        // the device is busy, try again
        status = __inbyte(ATAPIO_STATUS_REG_R);
        printf("%x\n", status);
        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }

        retries++;
    }

    if (retries == PIO_MAX_RETRIES)
    {
        DWORD pioStatus = SosAtaPioReset();
        if (PIO_SUCCESS != pioStatus)
        {
            return pioStatus;
        }
    }

    retries = 0;

    while ((status & STATUS_RDY) == 0 && retries < PIO_MAX_RETRIES)
    {
        // the device is not ready, try again
        status = __inbyte(ATAPIO_STATUS_REG_R);
        printf("%x\n", status);
        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }

        retries++;
    }

    if (retries == PIO_MAX_RETRIES)
    {
        DWORD pioStatus = SosAtaPioReset();
        if (PIO_SUCCESS != pioStatus)
        {
            return pioStatus;
        }
    }

    // select device 0, set reserved bits and put the 24-27 bits of the LBA
    __outbyte(ATAPIO_DRIVE_HEAD_REG_RW, DRVHD_LBA | DRVHD_RESERVED_1 | DRVHD_RESERVED_2);

    __outbyte(ATAPIO_ERROR_REG_R, 0);
    __outbyte(ATAPIO_SEC_CNT_REG_RW, ((SecCnt >> 8) & 0xFF));
    __outbyte(ATAPIO_SEC_NR_REG_RW, ((Lba48 >> 24) & 0xFF));
    __outbyte(ATAPIO_CYLINDER_LO_REG_RW, ((Lba48 >> 32) & 0xFF));
    __outbyte(ATAPIO_CYLINDER_HI_REG_RW, ((Lba48 >> 40) & 0xFF));

    __outbyte(ATAPIO_ERROR_REG_R, 0);
    __outbyte(ATAPIO_SEC_CNT_REG_RW, (SecCnt & 0xFF));
    __outbyte(ATAPIO_SEC_NR_REG_RW, (Lba48 & 0xFF));
    __outbyte(ATAPIO_CYLINDER_LO_REG_RW, ((Lba48 >> 8) & 0xFF));
    __outbyte(ATAPIO_CYLINDER_HI_REG_RW, ((Lba48 >> 16) & 0xFF));

    __outbyte(ATAPIO_COMMAND_REG_W, COMMAND_READ_PIO_48);

    status = __inbyte(ATAPIO_STATUS_REG_R);

    while ((status & STATUS_DRQ) == 0)
    {
        // wait until the drive is ready to transfer data
        status = __inbyte(ATAPIO_STATUS_REG_R);

        if (SosAtaPioVerifyStatusForErrors(status))
        {
            return PIO_STATUS_FAILED_WITH_ERR;
        }
    }

    for (i = 0; i < (DWORD)SecCnt * 256; i++)
    {
        ReturnBuff[i] = __inword(ATAPIO_DATA_REG_RW);
    }

    return PIO_SUCCESS;
}