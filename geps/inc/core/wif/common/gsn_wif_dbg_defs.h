/******************************************************************************
*
*               COPYRIGHT (c) 20012-2014 GainSpan Corporation
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
* $RCSfile: gsn_wif_dbg_defs.h,v $
*
* Description : This file contains common public definitions for WLAN CPU 
*               debug definitions.
******************************************************************************/
#ifndef _GSN_WIF_DBG_DEFS_H_
#define _GSN_WIF_DBG_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/
/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnWif GSN WLAN Firmware Interface (WIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *	  
 *		Whole GsnWif module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}	END of coresvcdoc.
 *****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wif_dbg_defs.h
 * @brief GSN WIF Debug messages public header.
 * 
 *    This file contains the public APIs and structures of debug
 *    interface.
 *****************************************************************************/



/**
 *****************************************************************************
 * @ingroup GsnWif
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWifDbgDefs GSN WIF Debug Definition
 *    This group of APIs provides debug definitions like peek/poke registers,
 *    read/write memory, etc.
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/	

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief Peek/Poke registers.
 *
 *    read/write registers.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_REG_DESC_S
{
    UINT32 addr;
    UINT32 val;
    UINT32 width;
} GSN_WIF_DBG_REG_DESC_T;

typedef struct GSN_WIF_DBG_REG_PEEKPOKE_S
{
    UINT32 numRegs;
    GSN_WIF_DBG_REG_DESC_T regDesc[0];
} GSN_WIF_DBG_REG_PEEKPOKE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief read/write memory.
 *
 *    read/write memory.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_MEM_RW_S
{
    UINT32 addr; /**< memory address */
    UINT32 len;  /**< number of bytes to read/write */
    UINT8  data[0];
} GSN_WIF_DBG_MEM_RW_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief execute.
 *
 *    start executing from given address.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_EXEC_S
{
    UINT32 addr; /**< address at which to execute */
} GSN_WIF_DBG_EXEC_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief flash read.
 *
 *    flash read using flash cache dma.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_FLASH_READ_S
{
    UINT32 addr; /**< flash address */
    UINT32 len;  /**< length of data */
    UINT8  data[0];
} GSN_WIF_DBG_FLASH_READ_T;


/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief flash erase.
 *
 *    flash erase.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_FLASH_ERASE_S
{
    UINT32 addr; /**< flash address */
    UINT32 len;  /**< length of data */
} GSN_WIF_DBG_FLASH_ERASE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief OTP write.
 *
 *    write given data to OTP.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_OTP_RW_S
{
    UINT8 id; /**< OTP group ID */
    UINT8 ver;  /**< OTP group ver */
    UINT16 len; /**< length of data to be written */
    UINT8  data[0];
} GSN_WIF_DBG_OTP_RW_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief Compute flash checksum.
 *
 *    Compute checksum on given data range in flash and return checksum.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_FLASH_CHKSUM_S
{
    UINT32 addr; /**< start address in flash */
    UINT32 len;  /**< length of data over which checksum should be computed */
} GSN_WIF_DBG_FLASH_CHKSUM_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDbgDefs
 * @brief Flash erase check.
 *
 *    Check if the given range in flash is erased.
 *****************************************************************************/
typedef struct GSN_WIF_DBG_FLASH_ERASE_CHK_S
{
    UINT32 addr; /**< start address in flash */
    UINT32 len;  /**< length of erase check */
} GSN_WIF_DBG_FLASH_ERASE_CHK_T;


#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_DBG_DEFS_H_ */






