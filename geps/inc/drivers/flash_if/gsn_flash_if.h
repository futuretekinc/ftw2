/******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by GainSpan
* Corporation or its licensors.  Title to the Material remains
* with GainSpan Corporation or its suppliers and licensors.
*
* The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used,
* copied, reproduced, modified, published, uploaded, posted, transmitted,
* distributed, or disclosed in any way except in accordance with the
* applicable license agreement.
*
* No license under any patent, copyright, trade secret or other
* intellectual property right is granted to or conferred upon you by
* disclosure or delivery of the Materials, either expressly, by
* implication, inducement, estoppel, except in accordance with the
* applicable license agreement.
*
* Unless otherwise agreed by GainSpan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by GainSpan
* or GainSpan's suppliers or licensors in any way.
*
* $RCSfile: gsn_flash_if.h,v $
*
* Description : This file contains public definitions for Flash IF driver.
******************************************************************************/
#ifndef _GSN_FLASH_IF_H_
#define _GSN_FLASH_IF_H_
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * File Inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "gsn_bitfield_macros.h"
  
#include "core/reg/gsn_reg_op.h"

#include "drivers/reg/gsn_reg_flashif_spec.h"
#include "drivers/reg/gsn_reg_flashif_op.h"

/**
 *****************************************************************************
 * @file gsn_flash_if.h
 * @brief GSN Flash IF public header.
 *    This file contains the public APIs and structures of flash interface
 *    driver module.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnFlashIf GSN Flash IF API.
 *    This group of APIs implements the Flash IF driver features. 
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

/*****************************************************************************
 * MACROS 
 ****************************************************************************/

#define GSN_FLASHIF_FLASH_SUBSECTOR_SIZE    0x1000      /* 4KB */
#define GSN_FLASHIF_FLASH_SECTOR_SIZE       0x10000     /* 64KB */
#define GSN_FLASHIF_FLASH_PAGE_SIZE         0x100       /* 256B */

#define GSN_FLASHIF_FLASH_SUBSECTOR_INDEX_TO_ADDR(subsectorIndex) \
        ((subsectorIndex) * GSN_FLASHIF_FLASH_SUBSECTOR_SIZE)
        
#define GSN_FLASHIF_FLASH_SECTOR_INDEX_TO_ADDR(sectorIndex) \
            ((sectorIndex) * GSN_FLASHIF_FLASH_SECTOR_SIZE)

#define GSN_FLASHIF_DELAY   10

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Gsn FlashIf PIO Enum for Dir Read and Write.
 *    This enum defines FlashIf PIO Dir Read and Write.
 * @see  GSN_FLASHIF_PIO_CTL_DIR_T.   
 *****************************************************************************/
typedef enum GSN_FLASHIF_PIO_CTL_DIR_E
{
    GSN_FLASHIF_PIO_CTL_DIR_READ = 0,
    GSN_FLASHIF_PIO_CTL_DIR_WRITE = 1
} GSN_FLASHIF_PIO_CTL_DIR_T;

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Gsn FlashIf PIO Enum for Dummy bytes.
 *    This enum defines FlashIf PIO zero, nonzero dummy bytes.
 * @see  GSN_FLASHIF_PIO_CTL_DUMMYBYTES_T.   
 *****************************************************************************/
typedef enum GSN_FLASHIF_PIO_CTL_DUMMYBYTES_E
{
    GSN_FLASHIF_PIO_CTL_DUMMYBYTES_ZERO = 0,
    GSN_FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO = 1
} GSN_FLASHIF_PIO_CTL_DUMMYBYTES_T;

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Gsn FlashIf Enum for FLASH BITLANE.
 *    This enum defines flash bitlane.
 * @see  GSN_FLASHIF_FLASH_BITLANE_T.   
 *****************************************************************************/
typedef enum GSN_FLASHIF_FLASH_BITLANE_E
{
    GSN_FLASHIF_FLASH_BITLANES_1 = 0,
    GSN_FLASHIF_FLASH_BITLANES_2 = 1,
    GSN_FLASHIF_FLASH_BITLANES_4 = 2
    
} GSN_FLASHIF_FLASH_BITLANE_T;


#define GSN_FLASHIF_PIO_CTL_WORD_SIZE   sizeof(UINT32)

CREATE_BITFIELD(FLASHIF_PIO_CTL_DIR, 0, 0);    /* 1-bit direction; 0-read, 1-write */
CREATE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1, 2);    /* 2-bit cmd byte count */
CREATE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3, 5);    /* 3-bit addr byte count */
CREATE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 6, 6);    /* 1-bit dummy bytes type; 0-zero,1-nonzero */
CREATE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 7, 7);   /* 1-bit dummy type; 0-bytes,1-cycles */
CREATE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 8, 9);    /* 2-bit cmd bitlanes */
CREATE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 10, 11);    /* 2-bit addr bitlanes */
CREATE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 12, 13);    /* 2-bit dummy bitlanes */
CREATE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 14, 15);    /* 2-bit data bitlanes */
CREATE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 16, 23);    /* 8-bit dummy bytes */
CREATE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 24, 31);    /* 8-bit unused */


#define GSN_FLASHIF_FLASH_REG_READ_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_REG_WRITE_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_WRITE) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_CMD_ADDR_WRITE_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_WRITE) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_CMD_ADDR_WRITE4X_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_WRITE) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 4) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_READ_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_FASTREAD_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 8) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_QUADREAD_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 10) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

#define GSN_FLASHIF_FLASH_DEEPPWRDOWNREL_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

/**
 ****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Gsn FlashIf DMA control structure.
 *
 *    This structure defines FlashIf DMA control structure
 *
 * @see  GSN_FLASHIF_DMACTL_T.
 ****************************************************************************/
typedef struct GSN_FLASHIF_DMACTL_S
{
    UINT32      dir             : 1;
    UINT32      cmdByteCount    : 2;
    UINT32      addrByteCount   : 3;
    UINT32      dummyBytesNonZero : 1;
    UINT32      dummyCycleCount : 1;
    UINT32      cmdBitlanes     : 2;
    UINT32      addrBitlanes    : 2;
    UINT32      dummyBitlanes   : 2;
    UINT32      dataBitlanes    : 2;
    UINT32      dummyByteCount  : 8;
    UINT32      unused          : 8;
    
} GSN_FLASHIF_DMACTL_T;

/* DMA control word - fast read */
#define GSN_FLASHIF_DMA_READ_CTL_WORD \
    MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

/* DMA control word - fast read */
#define GSN_FLASHIF_DMA_FASTREAD_CTL_WORD \
    MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 0) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 1) \
    | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

/* DMA control word - quad fast read */
#define GSN_FLASHIF_DMA_QUADREAD_CTL_WORD \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 10) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)
#define GSN_FLASHIF_DMA_QUADREAD_CTL_WORD_6DUMMYCYCLES \
        MAKE_BITFIELD(FLASHIF_PIO_CTL_DIR, GSN_FLASHIF_PIO_CTL_DIR_READ) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BYTECOUNT, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BYTECOUNT, 3) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NONZERO, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYCOUNT_CYCLES, 1) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_CMD_BITLANES, 0) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_ADDR_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMY_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DATA_BITLANES, 2) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_DUMMYBYTES_NUM, 6) \
        | MAKE_BITFIELD(FLASHIF_PIO_CTL_UNUSED2, 0)

/**
 ****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Gsn FlashIf Config structure.
 *
 *    This structure defines FlashIf Config structure
 *
 * @see  GSN_FLASHIF_CFG_T.
 ****************************************************************************/
typedef struct GSN_FLASHIF_CFG_S
{
    GSN_FLASHIF_DMACTL_T    dmaCtl;
    UINT32      dmaCmd;
    
} GSN_FLASHIF_CFG_T;

/**
 ****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Gsn FlashIf Context.
 *
 *    This structure defines FlashIf Context.
 *
 * @see  GSN_FLASHIF_CTX_T.
 ****************************************************************************/
typedef struct GSN_FLASHIF_CTX_S
{
    GSN_FLASHIF_CFG_T flashIfCfg;
    
    GSN_OSAL_MUTEX_T mutex;
    
} GSN_FLASHIF_CTX_T;


/*
 * Flash related definitions 
 */

/* Flash instruction definitions */
#define GSN_FLASHIF_FLASH_WREN          0x06    /* write enable */
#define GSN_FLASHIF_FLASH_WRDI          0x04    /* write disable */
#define GSN_FLASHIF_FLASH_RDID          0x9F    /* read identification */
#define GSN_FLASHIF_FLASH_RDSR          0x05    /* read status register */
#define GSN_FLASHIF_FLASH_WRSR          0x01    /* write status register */
#define GSN_FLASHIF_FLASH_READ          0x03    /* read data bytes */
#define GSN_FLASHIF_FLASH_FAST_READ     0x0B    /* read data bytes at higher speed */
#define GSN_FLASHIF_FLASH_DUAL_FAST_READ 0x3B    /* read data bytes at dual fast speed */
#define GSN_FLASHIF_FLASH_QUAD_FAST_READ 0x6B    /* read data bytes at quad fast speed */
#define GSN_FLASHIF_FLASH_QUADIO_FAST_READ 0xEB    /* read data bytes at quad IO fast speed */
#define GSN_FLASHIF_FLASH_PP            0x02    /* page program */
#define GSN_FLASHIF_FLASH_DUAL_FAST_PP  0xA2    /* Dual Input fast page program */
#define GSN_FLASHIF_FLASH_QUAD_FAST_PP  0x32    /* Quad Input fast page program */
#define GSN_FLASHIF_FLASH_SE            0xD8    /* sector erase */
#define GSN_FLASHIF_FLASH_SSE           0x20    /* sector erase */
#define GSN_FLASHIF_FLASH_BE            0xC7    /* bulk erase */
#define GSN_FLASHIF_FLASH_VOLCFG        0x81    /* Non volatile config register */
#define GSN_FLASHIF_FLASH_DP            0xB9    /* deep power down */
#define GSN_FLASHIF_FLASH_RES           0xAB    /* release from power down */
#define GSN_FLASHIF_FLASH_HPM_RESET     0xFF    /* reset high perf mode */


/**
 ****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Flash Status Register structure.
 *
 *    This structure defines Status Registers of Flash.
 *
 * @see  GSN_FLASHIF_FLASH_STATUS_REG_T.
 ****************************************************************************/
typedef struct GSN_FLASHIF_FLASH_STATUS_REG_S
{
    UINT32   wip     : 1;
    UINT32   wel     : 1;
    UINT32   bp      : 3;    /**< block protect */
    UINT32   bottom  : 1;    /**< protected areas start from top or bottom */
    UINT32   unused  : 1;
    UINT32   srwd    : 1;
    UINT32   reserved:24;
    
} GSN_FLASHIF_FLASH_STATUS_REG_T;




/*****************************************************************************
 * Public Variables
 ****************************************************************************/





/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* 
 * Flash If functions 
 */

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Wait for FlashIf Pio Tx fifo empty.
 *
 * @return VOID.
 ****************************************************************************/

PUBLIC INLINE VOID
GsnFlashIf_PioTxFifoEmptyWait()
{
    UINT32 status, i;

    status = FLASHIF_PIO_TXFIFO_EMPTY_GET(FLASHIF);
    while (status == 0)
    {
        for (i = 0; i < GSN_FLASHIF_DELAY; i++);
        status = FLASHIF_PIO_TXFIFO_EMPTY_GET(FLASHIF);
    }
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Pio Tx fifo write.
 *
 * @param data	- IN data to be written to fifo
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_PioTxFifoWrite(UINT32 data)
{
    GsnFlashIf_PioTxFifoEmptyWait();
    
    FLASHIF_PIO_TXFIFO_SET(FLASHIF, data);
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Wait for FlashIf Pio Rx fifo Data.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_PioRxFifoDataWait()
{
    UINT32 status, i;

    status = FLASHIF_PIO_RXFIFO_EMPTY_GET(FLASHIF);
    while (status == 1)
    {
        for (i = 0; i < GSN_FLASHIF_DELAY; i++);
        status = FLASHIF_PIO_RXFIFO_EMPTY_GET(FLASHIF);
    }
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief Read FlashIf Pio Rx fifo Data.
 *
 * @return data.
 ****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashIf_PioRxFifoRead()
{
    UINT32 data;

    GsnFlashIf_PioRxFifoDataWait();
    
    data = FLASHIF_PIO_RXFIFO_GET(FLASHIF);

    return data;
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Status Idle wait.
 *
 * 	This function waits if FlashIf status is Idle
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_StatusIdleWait()
{
    UINT32 status, i;

    status = FLASHIF_ACTIVE_GET(FLASHIF);
    while (status == 1)
    {
        for (i = 0; i < GSN_FLASHIF_DELAY; i++);
        status = FLASHIF_ACTIVE_GET(FLASHIF);
    }
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Pio Request.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_PioReq()
{
    UINT32 gnt;
    
    FLASHIF_PIO_REQ_SET(FLASHIF, FLASHIF_PIO_REQ_F_BITMASK);

    /* poll for grant */
    do
    {
        gnt = FLASHIF_PIO_GNT_F_GET(FLASHIF);
    } while (gnt == 0);
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Pio Release.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_PioRelease()
{
    UINT32 gnt;

    FLASHIF_PIO_REQ_SET(FLASHIF, FLASHIF_PIO_REQ_F_INIT);
    /* poll for grant */
    do
    {
        gnt = FLASHIF_PIO_GNT_F_GET(FLASHIF);
    } while (gnt == 1);
}


/* 
 * Flash operations 
 */

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Id Read.
 *
 * @return data - Data read from Rx fifo.
 ****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashIf_FlashIdRead()
{
    UINT32 data;

    /* write control word */
    data = GSN_FLASHIF_FLASH_REG_READ_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 3 bytes */
    data = 3;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - read ID register */
    data = GSN_FLASHIF_FLASH_RDID;
    GsnFlashIf_PioTxFifoWrite(data);

    data = GsnFlashIf_PioRxFifoRead();

    return data;
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Status Read.
 *
 * @return statusReg - return status reg of type GSN_FLASHIF_FLASH_STATUS_REG_T.
 ****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashIf_FlashStatusRead()
{
    UINT32 data;
    UINT32 statusReg;
    
    /* write control word */
    data = GSN_FLASHIF_FLASH_REG_READ_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 1 byte register */
    data = 1;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - read status register */
    data = GSN_FLASHIF_FLASH_RDSR;
    GsnFlashIf_PioTxFifoWrite(data);

    data = GsnFlashIf_PioRxFifoRead();
    memcpy(&statusReg, &data, sizeof(statusReg));
    
    return statusReg;
    
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf FlashWelBitSetWait.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_FlashWelBitSetWait()
{
    UINT32 flashStatusReg;

    do
    {
        flashStatusReg = GsnFlashIf_FlashStatusRead();
    } while((flashStatusReg & 0x2) == 0x0);
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf FlashWelBitClrWait.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_FlashWelBitClrWait()
{
    UINT32 flashStatusReg;

    do
    {
        flashStatusReg = GsnFlashIf_FlashStatusRead();
    } while((flashStatusReg & 0x2) == 0x2);
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Write Enable.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_FlashWriteEnable()
{
    UINT32 data;

    /* write control word */
    data = GSN_FLASHIF_FLASH_REG_WRITE_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 0 bytes */
    data = 0;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - read status register */
    data = GSN_FLASHIF_FLASH_WREN;
    GsnFlashIf_PioTxFifoWrite(data);

    /* wait for write enable to take effect */
    GsnFlashIf_FlashWelBitSetWait();
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Write Disable.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_FlashWriteDisable()
{
    UINT32 data;

    /* write control word */
    data = GSN_FLASHIF_FLASH_REG_WRITE_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 0 bytes */
    data = 0;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - read status register */
    data = GSN_FLASHIF_FLASH_WRDI;
    GsnFlashIf_PioTxFifoWrite(data);

    /* wait for write disable to take effect */
    GsnFlashIf_FlashWelBitClrWait();
}


/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash status Write.
 *
 * @param val		- IN Value to write
 * @param numBytes	- IN Number of bytes to Write
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC INLINE VOID
GsnFlashIf_FlashStatusWrite(UINT32 val, UINT32 numBytes)
{
    UINT32 data;

    /* enable write for status register write */
    GsnFlashIf_FlashWriteEnable();
    
    /* write control word */
    data = GSN_FLASHIF_FLASH_REG_WRITE_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 1 byte status */
    data = numBytes;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - read status register */
    data = GSN_FLASHIF_FLASH_WRSR;
    GsnFlashIf_PioTxFifoWrite(data);

    data = val;
    GsnFlashIf_PioTxFifoWrite(data);

    /* wait for status register write completion */
    GsnFlashIf_FlashWelBitClrWait();

}

PUBLIC INLINE VOID
GsnFlashIf_HpmReset()
{
    UINT32 data;
    
    /* write control word */
    data = GSN_FLASHIF_FLASH_REG_WRITE_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 0 bytes */
    data = 0;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - HPM reset */
    data = GSN_FLASHIF_FLASH_HPM_RESET;
    GsnFlashIf_PioTxFifoWrite(data);
}
PUBLIC INLINE VOID
GsnFlashIf_DeepPowerDownRelease()
{
    UINT32 data;
    
    /* write control word */
    data = GSN_FLASHIF_FLASH_DEEPPWRDOWNREL_CTL_WORD;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write data transfer length - 0 bytes */
    data = 0;
    GsnFlashIf_PioTxFifoWrite(data);

    /* write flash command - deep power down release */
    data = GSN_FLASHIF_FLASH_RES;
    GsnFlashIf_PioTxFifoWrite(data);

    /* read 1 byte data electronic ID */
    //data = GsnFlashIf_PioRxFifoRead();
}

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Init.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnFlashIf_Init();

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf open.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnFlashIf_Open();

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Close.
 *
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnFlashIf_Close();

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Register Write
 *
 * @param cmd		- IN UINT8 type command
 * @param val		- IN UINT32 type value to be written
 * @param blocking	- IN blocking flag of BOOL type
 * @return status	- returns GSN_SUCCESS or GSN_FAILURE of type UINT.
 ****************************************************************************/
PUBLIC UINT
GsnFlashIf_FlashRegWrite(UINT8 cmd, UINT32 val, BOOL blocking);

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Erase
 *
 * @param addr		- IN UINT32 type address
 * @param len		- IN length to erase of UINT32 type
 * @param blocking	- IN blocking flag of BOOL type
 * @return status	- returns GSN_SUCCESS or GSN_FAILURE of type UINT.
 ****************************************************************************/
PUBLIC UINT
GsnFlashIf_FlashErase(UINT32 addr, UINT32 len, BOOL blocking);

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Bulk Erase
 *
 * @return VOID
 ****************************************************************************/
PUBLIC VOID
GsnFlashIf_FlashBulkErase();

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Sector Erase
 *
 * @param addr		- IN UINT32 type address
 * @param blocking	- IN blocking flag of BOOL type
 * @return status	- returns GSN_SUCCESS or GSN_FAILURE of type UINT.
 ****************************************************************************/
PUBLIC UINT
GsnFlashIf_FlashSectorErase(UINT32 addr, BOOL blocking);

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash SubSector Erase
 *
 * @param addr		- IN UINT32 type address
 * @param blocking	- IN blocking flag of BOOL type
 * @return status	- returns GSN_SUCCESS or GSN_FAILURE of type UINT.
 ****************************************************************************/
PUBLIC UINT
GsnFlashIf_FlashSubsectorErase(UINT32 addr, BOOL blocking);

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Program
 *
 * @param addr		- IN UINT32 type address
 * @param len		- IN length to program of UINT32 type
 * @param pData		- IN pointer to hold data of type UINT8
 * @param blocking	- IN blocking flag of BOOL type
 * @return status	- returns GSN_SUCCESS or GSN_FAILURE of type UINT.
 ****************************************************************************/
PUBLIC UINT
GsnFlashIf_FlashProgram(UINT32 addr, UINT32 len, UINT8 *pData, BOOL blocking);
 
/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Page Program
 *
 * @param addr		- IN UINT32 type address
 * @param len		- IN length to program of UINT32 type
 * @param pData		- IN pointer to hold data of type UINT8
 * @return VOID
 ****************************************************************************/
PRIVATE VOID
GsnFlashIf_FlashPageProgram(UINT32 addr, UINT32 len, UINT8 *pData);

/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash Read
 *
 * @param addr		- IN UINT32 type address
 * @param len		- IN length to read of UINT32 type
 * @param pData		- IN pointer to hold data of type UINT8
 * @param blocking	- IN blocking flag of BOOL type
 * @return status	- returns GSN_SUCCESS or GSN_FAILURE of type UINT.
 ****************************************************************************/
PUBLIC UINT
GsnFlashIf_FlashRead(UINT32 addr, UINT32 len, UINT8 *pData, BOOL blocking);


/**
 *****************************************************************************
 * @ingroup GsnFlashIf
 * @brief FlashIf Flash PowerDown
 *
 * @return VOID
 ****************************************************************************/
PUBLIC VOID
GsnFlashIf_FlashPowerDown();

PUBLIC BOOL
GsnFlashIf_FlashCheckAndConfigure();

#ifdef __cplusplus
}
#endif
#endif /* _GSN_FLASH_IF_H_ */
