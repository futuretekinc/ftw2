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
* $RCSfile: gsn_flash_if_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/


/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

  
  
  
/*****************************************************************************
  *  Definitions
  ****************************************************************************/  
typedef VOID 
(* GsnFlashIf_Init_FP_T)(VOID);

extern _RPST_   GsnFlashIf_Init_FP_T GsnFlashIf_Init_FP;

typedef VOID 
(* GsnFlashIf_Open_FP_T)(VOID);

extern _RPST_   GsnFlashIf_Open_FP_T GsnFlashIf_Open_FP;

typedef VOID 
(* GsnFlashIf_Close_FP_T)(VOID);

extern _RPST_   GsnFlashIf_Close_FP_T GsnFlashIf_Close_FP;

typedef UINT 
(* GsnFlashIf_DmaCtlSet_FP_T)(UINT32 dmaReadCtlWord, 
                                UINT32 dmaCmd, BOOL blocking);

extern _RPST_   GsnFlashIf_DmaCtlSet_FP_T GsnFlashIf_DmaCtlSet_FP;


typedef UINT 
(* GsnFlashIf_FlashRegWrite_FP_T)(UINT8 cmd, 
                                   UINT32 val, BOOL blocking);

extern _RPST_   GsnFlashIf_FlashRegWrite_FP_T GsnFlashIf_FlashRegWrite_FP;

typedef UINT 
(* GsnFlashIf_FlashErase_FP_T)(UINT32 addr, UINT32 len, BOOL blocking);

extern _RPST_   GsnFlashIf_FlashErase_FP_T GsnFlashIf_FlashErase_FP;

typedef VOID 
(* GsnFlashIf_FlashBulkErase_FP_T)(VOID);

extern _RPST_   GsnFlashIf_FlashBulkErase_FP_T GsnFlashIf_FlashBulkErase_FP;

typedef UINT 
(* GsnFlashIf_FlashSectorErase_FP_T)(UINT32 addr, BOOL blocking);

extern _RPST_   GsnFlashIf_FlashSectorErase_FP_T GsnFlashIf_FlashSectorErase_FP;

typedef UINT 
(* GsnFlashIf_FlashSubsectorErase_FP_T)(UINT32 addr, BOOL blocking);

extern _RPST_   GsnFlashIf_FlashSubsectorErase_FP_T GsnFlashIf_FlashSubsectorErase_FP; 

typedef UINT 
(* GsnFlashIf_FlashProgram_FP_T) (UINT32 addr, UINT32 len, UINT8 *pData, BOOL blocking);

extern _RPST_   GsnFlashIf_FlashProgram_FP_T GsnFlashIf_FlashProgram_FP;

typedef UINT 
(* GsnFlashIf_FlashRead_FP_T)(UINT32 addr, UINT32 len, UINT8 *pData, BOOL blocking);

extern _RPST_   GsnFlashIf_FlashRead_FP_T GsnFlashIf_FlashRead_FP;

typedef VOID 
(* GsnFlashIf_FlashPowerDown_FP_T)(VOID);

extern _RPST_   GsnFlashIf_FlashPowerDown_FP_T GsnFlashIf_FlashPowerDown_FP;









