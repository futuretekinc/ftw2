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
* $RCSfile: gsn_sdadc_private_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

#ifndef _GSN_SDADC_PRIVATE_FTP_H_
#define _GSN_SDADC_PRIVATE_FTP_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "drivers/clk_ctl/gsn_clk_ctl.h"
#include "gsn_includes.h"
#include "drivers/sdadc/gsn_sdadc.h"

/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef VOID 
(* GsnSdadc_IsrAdcFifoFull_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle);

extern _RPST_ GsnSdadc_IsrAdcFifoFull_FP_T GsnSdadc_IsrAdcFifoFull_FP;


typedef UINT16 
(* GsnSdadc_IsrDacFifoEmpty_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle);

extern _RPST_ GsnSdadc_IsrDacFifoEmpty_FP_T GsnSdadc_IsrDacFifoEmpty_FP;




#endif

