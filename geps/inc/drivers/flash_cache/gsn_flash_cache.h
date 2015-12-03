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
* $RCSfile: gsn_flash_cache.h,v $
*
* Description : This file contains public definitions for Flash Cache driver.
******************************************************************************/
#ifndef _GSN_FLASH_CACHE_H_
#define _GSN_FLASH_CACHE_H_
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
    
#include "core/reg/gsn_reg_op.h"
#include "core/util/gsn_ring_buf.h"
  
#include "drivers/reg/gsn_reg_flashcache_spec.h"
#include "drivers/reg/gsn_reg_flashcache_op.h"


/**
 *****************************************************************************
 * @file gsn_flash_cache.h
 * @brief GSN Flash Cache public header.
 *    This file contains the public APIs and structures of Flash Cache
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
 * @defgroup GsnFlashCache GSN Flash Cache API.
 *    This group of APIs implements the Flash Cache driver features. 
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

/*****************************************************************************
 * MACROS 
 ****************************************************************************/

#define GSN_FLASHCACHE_PATCHCACHE_LINE_SIZE1    256
#define GSN_FLASHCACHE_PATCHCACHE_LINE_SIZE2    512
#define GSN_FLASHCACHE_PATCHCACHE_FLASH_SIZE         (128 * 1024)
#define GSN_FLASHCACHE_PATCHCACHE_SRAM_SIZE          (16 * 1024)

#define GSN_FLASHCACHE_PATCHCACHE_TAG_NUM    64
#define GSN_FLASHCACHE_PATCHCACHE_TAG_FIRST  0
#define GSN_FLASHCACHE_PATCHCACHE_TAG_LAST   (GSN_FLASHCACHE_PATCH_CACHETAG_NUM-1)


/* This defines the size in bytes of each block remap register set - 3 registers */
#define GSN_FLASHCACHE_BLK_REMAP_REG_OFFSET     (3 * sizeof(UINT32))

/* This defines the size in bytes of each patch tag register set - 1 register */
#define GSN_FLASHCACHE_PATCHCACHE_TAG_REG_OFFSET     (1 * sizeof(UINT32))


/*****************************************************************************
  * Public definitions
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnFlashCache
 * @brief GSN FLASHCACHE Interrupt Mode Type.
 *    This enum defines Interrupt for FLASHCACHE 
 *
 * @see  GSN_FLASHCACHE_INTR_T.
 ****************************************************************************/
typedef enum GSN_FLASHCACHE_INTR_E
{
    GSN_FLASHCACHE_INTR_UNMAPPED_ACCESS_ERR = 0,
    GSN_FLASHCACHE_INTR_CPU_DMA_DONE
    
} GSN_FLASHCACHE_INTR_T;

/**
 *****************************************************************************
 * @ingroup GsnFlashCache
 * @brief GSN Flash Cache Block Re-Map Index.
 *    This enum defines flash cache block remap index
 *
 * @see  GSN_FLASHCACHE_BLK_REMAP_INDEX_T.
 ****************************************************************************/
typedef enum GSN_FLASHCACHE_BLK_REMAP_INDEX_E
{
    GSN_FLASHCACHE_BLK_REMAP_INDEX_0 = 0,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_1,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_2,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_3,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_4,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_5,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_6,
    GSN_FLASHCACHE_BLK_REMAP_INDEX_7,
        
} GSN_FLASHCACHE_BLK_REMAP_INDEX_T;

/**
 *****************************************************************************
 * @ingroup GsnFlashCache
 * @brief GSN Flash Cache Block Re-Map structure.
 *    This structure defines flash cache block remap
 *
 * @see  GSN_FLASHCACHE_BLK_REMAP_T.
 ****************************************************************************/
typedef struct GSN_FLASHCACHE_BLK_REMAP_S
{
    UINT32 remapIndex;
    UINT32 codeAddr;
    UINT32 sramAddr;
    UINT32 remapSize;
    
} GSN_FLASHCACHE_BLK_REMAP_T;

/**
 *****************************************************************************
 * @ingroup GsnFlashCache
 * @brief GSN FlashCache Cpu DMA Request structure.
 *    This structure defines CPU dma request for FlashCache
 *
 * @see  GSN_FLASHCACHE_CPU_DMAREQ_T.
 ****************************************************************************/
typedef struct GSN_FLASHCACHE_CPU_DMAREQ_S
{
    UINT32 flashAddr;
    UINT32 sramAddr;
    UINT32 dmaLen;
    UINT32 num64Ks;
    UINT32 numBytesRem;
    GSN_CB_T cb;
} GSN_FLASHCACHE_CPU_DMAREQ_T;

/**
 *****************************************************************************
 * @ingroup GsnFlashCache
 * @brief GSN FlashCache Patch Cache Tag structure.
 *    This structure defines FlashCache patch cache tag
 *
 * @see  GSN_FLASHCACHE_PATCHCACHE_TAG_S.
 ****************************************************************************/
typedef struct GSN_FLASHCACHE_PATCHCACHE_TAG_S
{
    UINT32 flashIndex   : 9;    /* 512 lines in flash */
    UINT32 lineValid    : 1;
    UINT32 lock         : 1;
    UINT32 cacheIndex   : 6;    /* 64 lines in sram cache */
    UINT32 unused       :15;
    
} GSN_FLASHCACHE_PATCHCACHE_TAG_T;

#define GSN_FLASHCACHE_CPU_DMAREQ_Q_SIZE   8

/**
 *****************************************************************************
 * @ingroup GsnFlashCache
 * @brief GSN FlashCache structure.
 *    This structure defines FlashCache
 *
 * @see  GSN_FLASHCACHE_T.
 ****************************************************************************/
typedef struct GSN_FLASHCACHE_S
{
    GSN_RING_BUF_T cpuDmaReqQ;
    GSN_FLASHCACHE_CPU_DMAREQ_T cpuDmaReqQBuf[GSN_FLASHCACHE_CPU_DMAREQ_Q_SIZE];

    GSN_FLASHCACHE_CPU_DMAREQ_T cpuDmaReqInProgress;
    
} GSN_FLASHCACHE_T;


/*****************************************************************************
  * Public Variables
  ****************************************************************************/



/*****************************************************************************
  * Public function
  ****************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Version Get API.
 *    This function called to get the FlashCache Version.
 *
 * @return UINT32	- version number.
 *****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashCache_VersionGet()
{
    return FLASHCACHE_FC_VER_GET(FLASHCACHE);
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Interrupt Enable API .
 *    This function called to Enable FlashCache Interrupt.
 *
 * @param intr 		- IN enum for interrupt
 *
 * @return VOID
 *****************************************************************************/
PUBLIC INLINE VOID
GsnFlashCache_IntEnable(GSN_FLASHCACHE_INTR_T intr)
{
    FLASHCACHE_INTCTL_SETBIT(FLASHCACHE, (0x1 << intr));
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Interrupt Disable API .
 *    This function called to Disable FlashCache Interrupts.
 *
 * @param intr 		- IN enum for interrupt
 *
 * @return VOID
 *****************************************************************************/
PUBLIC INLINE VOID
GsnFlashCache_IntDisable(GSN_FLASHCACHE_INTR_T intr)
{
    FLASHCACHE_INTCTL_CLEARBIT(FLASHCACHE, (0x1 << intr));
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Interrupt Status Get API .
 *    This function called to Get FlashCache Interrupt Status.
 *
 * @return UINT32 	- Interrupt status.
 *****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashCache_IntStatusGet()
{
    FLASHCACHE_INTCTL_GET(FLASHCACHE);
    return 0;
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Block Remap Enable API .
 *    This function called for Block Remap Enable
 *
 * @return VOID
 *****************************************************************************/
PUBLIC INLINE VOID
GsnFlashCache_BlkRemapEnable()
{
    FLASHCACHE_BLK_REMAP_CTL_SET(FLASHCACHE, FLASHCACHE_BLK_REMAP_EN_BITMASK);
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Block Remap Status Get API .
 *    This function called to Get FlashCache Block Remap Status.
 *
 * @return UINT32 	- Block Remap status.
 *****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashCache_BlkRemapStatus()
{
    return FLASHCACHE_BLK_REMAP_STATUS_GET(FLASHCACHE);
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache DMA Status Get API .
 *    This function called to Get DMA Status.
 *
 * @return UINT32 	- DMA status.
 *****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashCache_DmaStatusGet()
{
    /* IMPORTANT: this register is for debug only */
    return FLASHCACHE_DMA_STATUS_GET(FLASHCACHE);
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache CPU DMA Done Check API .
 *    This function called to check if CPU DMA is done.
 *
 * @return UINT32 	- DMA done status.
 *****************************************************************************/
PUBLIC INLINE UINT32
GsnFlashCache_CpuDmaDoneCheck()
{
    return FLASHCACHE_DMADONE_INTSTATUS_GET(FLASHCACHE);
}

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Init API .
 *    This function called to Initialize FlashCache.
 *
 * @return GSN_STATUS 	- Initialization successful or Failure.
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnFlashCache_Init();

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Patch Tag Set API .
 *    This function called to set patch tag.
 *
 * @param tag		- IN structure of type GSN_FLASHCACHE_PATCHCACHE_TAG_T 		
 *
 * @return VOID.
 *****************************************************************************/
PUBLIC INLINE VOID
GsnFlashCache_PatchTagSet(GSN_FLASHCACHE_PATCHCACHE_TAG_T tag);

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Patch Tag Get API .
 *    This function called to Get the patch tag.
 *
 * @param cacheIndex		- IN cache index of type UINT32 		
 *
 * @return GSN_FLASHCACHE_PATCHCACHE_TAG_T - returns the patch tag structure.
 *****************************************************************************/
PUBLIC INLINE GSN_FLASHCACHE_PATCHCACHE_TAG_T
GsnFlashCache_PatchTagGet(UINT32 cacheIndex);

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Patch Control Set API .
 *    This function called to Set the patch control.
 *
 * @param flashAddr		- IN Flash address 
 * @param codeAddr		- IN Code address		
 * @param sramAddr		- IN SRAM address
 *
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnFlashCache_PatchCtlSet(UINT32 flashAddr, UINT32 codeAddr, UINT32 sramAddr);

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Block Remap Set API .
 *    This function called to set block remapping.
 *
 * @param remap 		- IN pointer to block remap structure
 *				     
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnFlashCache_BlkRemapSet(GSN_FLASHCACHE_BLK_REMAP_T *remap);

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Block Fetch API .
 *    This function called to Set the patch control.
 *
 * @param flashAddr		- IN Flash address 		
 * @param sramAddr		- IN SRAM address
 * @param blkSize		- IN block size
 * @param pCb  			- IN pionter for callback
 *
 * @return GSN_STATUS 		- Block fetch successful or Failure.
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnFlashCache_BlkFetch(UINT32 flashAddr, UINT32 sramAddr, UINT32 blkSize,
                        GSN_CB_T *pCb);

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache Block Fetch API .
 *    This function called to Set the patch control.
 *
 * @param flashAddr		- IN Flash address
 * @param blkSize		- IN block size
 * @param remap 		- IN pointer to block remap structure
 *
 * @return GSN_STATUS 		- Block fetch successful or Failure.
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnFlashCache_BlkFetchRemap(UINT32 flashAddr, UINT32 blkSize,
                            GSN_FLASHCACHE_BLK_REMAP_T *remap);

/**
 *******************************************************************************
 * @ingroup GsnFlashCache
 * @brief FlashCache ISR.
 *    This function called when interrupt occurs.
 *
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnFlashCache_Isr();


#ifdef __cplusplus
}
#endif
#endif /* _GSN_FLASH_CACHE_H_ */
