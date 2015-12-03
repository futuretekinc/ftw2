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
* $RCSfile: gsn_flash_cache_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/


/*****************************************************************************
  * File Inclusions
  ****************************************************************************/


  /*****************************************************************************
  *  Definitions
  ****************************************************************************/

  typedef GSN_STATUS 
(* GsnFlashCache_Init_FP_T) (void);
extern _RPST_   GsnFlashCache_Init_FP_T GsnFlashCache_Init_FP;

typedef GSN_FLASHCACHE_PATCHCACHE_TAG_T 
(* GsnFlashCache_PatchTagGet_FP_T)(UINT32 cacheIndex);
extern _RPST_   GsnFlashCache_PatchTagGet_FP_T GsnFlashCache_PatchTagGet_FP; 

typedef VOID 
(* GsnFlashCache_PatchTagSet_FP_T)(GSN_FLASHCACHE_PATCHCACHE_TAG_T tag);
extern _RPST_   GsnFlashCache_PatchTagSet_FP_T GsnFlashCache_PatchTagSet_FP;

typedef VOID 
(* GsnFlashCache_PatchCtlSet_FP_T)(UINT32 flashAddr, 
                                    UINT32 codeAddr, 
									UINT32 sramAddr);
extern _RPST_   GsnFlashCache_PatchCtlSet_FP_T GsnFlashCache_PatchCtlSet_FP;

typedef VOID 
(* GsnFlashCache_BlkRemapSet_FP_T)(GSN_FLASHCACHE_BLK_REMAP_T *remap);
extern _RPST_   GsnFlashCache_BlkRemapSet_FP_T GsnFlashCache_BlkRemapSet_FP;

typedef GSN_STATUS 
(* GsnFlashCache_BlkFetch_FP_T)(UINT32 flashAddr, 
                                 UINT32 sramAddr, 
								 UINT32 blkSize, 
								 GSN_CB_T *pCb);
extern _RPST_   GsnFlashCache_BlkFetch_FP_T GsnFlashCache_BlkFetch_FP;

typedef GSN_STATUS  
(* GsnFlashCache_BlkFetchRemap_FP_T)(UINT32 flashAddr, 
                                      UINT32 blkSize, 
									  GSN_FLASHCACHE_BLK_REMAP_T *remap);
extern _RPST_   GsnFlashCache_BlkFetchRemap_FP_T GsnFlashCache_BlkFetchRemap_FP;


typedef VOID (* GsnFlashCache_Isr_FP_T)();
extern _RPST_   GsnFlashCache_Isr_FP_T GsnFlashCache_Isr_FP;






