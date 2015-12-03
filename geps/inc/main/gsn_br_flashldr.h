/******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: gsn_br_flashldr.h,v $
*
* Description : This file contains boot rom's flash booter.
*****************************************************************************/
#ifndef _GSN_BR_FLASHLDR_H_
#define _GSN_BR_FLASHLDR_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"
#include "gsn_types.h"


/**
 *****************************************************************************
 * @file gsn_br_flashldr.h
 * @brief GSN boot rom Flash booter.
 *    This file contains boot rom's flash boot functionality that loads
 *    the initial flash code and starts execution.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnBrFlashLdr GSN Bootrom Flash Boot
 * @brief This module Contains boot rom's flash booter functionality.
 *
 * \verbatim
 * PUBLIC is actually defined as blank.
 * PRIVATE is replaced with the "static" descriptor.
 * TRUE is replaced with 1, FALSE with 0
 * Compile-dependent definitions are provided for INLINE
 * BIT(n) provides n-bit offsets
 * A UINT32 with all bits = 1 is defined.
 *
 *\endverbatim
 *****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


/*****************************************************************************
  *  Definitions
  ****************************************************************************/


typedef struct GSN_BRFLASHLDR_SUPERBLOCK_S
{
    UINT8       flok[4];
    UINT32      fw0Cb1Addr;
    UINT32      fw0Cb2Addr;
    UINT32      fw1Cb1Addr;
    UINT32      fw1Cb2Addr;
    UINT32      fw2Cb1Addr;
    UINT32      fw2Cb2Addr;
	UINT16		facDlftLoc;		/* 0 for Flash, 1 for OTP */
	UINT16		facDlftSize;
    UINT32 		facDfltAddr;    
    UINT32 		fsAddress;		/* should start at 64K Boundary*/
    UINT32		fsSize;			/* should be multiple of 64K */
    UINT32      flashIfDmaRdCtlWd;
    UINT32      flashIfDmaRdCmd;
} GSN_BRFLASHLDR_SUPERBLOCK_T;

typedef enum GSN_BRFLASHLDR_BLOCK_OWNER_E
{
    GSN_BRFLASHLDR_BLOCK_OWNER_APPBR = 0,
    GSN_BRFLASHLDR_BLOCK_OWNER_AFW = 1,
    GSN_BRFLASHLDR_BLOCK_OWNER_WLANBR = 2,
    GSN_BRFLASHLDR_BLOCK_OWNER_WFW =3,
    
} GSN_BRFLASHLDR_BLOCK_OWNER_T;


#define GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOADREMAPRUN     0x1 /* bit 0 */
#define GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOADREMAP        0x2 /* bit 1 */
#define GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOAD             0x4 /* bit 2 */
#define GSN_BRFLASHLDR_BLOCK_DESC_FLAG_LOADRUN          0x8 /* bit 3 */
#define GSN_BRFLASHLDR_BLOCK_DESC_FLAG_WEBFS			0x10 /* bit 4 */

typedef struct GSN_BRFLASHLDR_BLOCK_DESC_S
{
    UINT32 offset;  /* offset starting from beginning of image */
    UINT32 size;    /* size of block in bytes */
    UINT32 programAddr; /* address for remapping */
    UINT32 sramAddr; 
    UINT16 owner;   /* owner of block - who loads the block into sram */
    UINT16 flags;   /* flags + remap index, remap index is in upper 4 bits */
    
} GSN_BRFLASHLDR_BLOCK_DESC_T;

typedef struct GSN_BRFLASHLDR_CTL_BLOCK_S
{
    UINT8       fwok[4];
    UINT32      rev;
    UINT32      ctlBlockSize; /* size of data following this field */
    GSN_BRFLASHLDR_BLOCK_DESC_T blockDesc[0];    /* stretchable array
                                                   of block descriptors */
} GSN_BRFLASHLDR_CTL_BLOCK_T;

typedef enum GSN_BRFLASHLDR_FLASH_BOOT_TYPE_E
{
    GSN_BRFLASHLDR_CUR_FW_LOAD = 0,
    GSN_BRFLASHLDR_FACTORY_FW_RESTORE,
    GSN_BRFLASHLDR_LAST_FW_RESTORE,
    
} GSN_BRFLASHLDR_FLASH_BOOT_TYPE_T;


PUBLIC VOID
GsnBrFlashLdr_FlashCheckAndBoot(GSN_BRFLASHLDR_FLASH_BOOT_TYPE_T flashLdType);


#ifdef __cplusplus
}
#endif

#endif /* _GSN_BR_FLASHLDR_H_ */


