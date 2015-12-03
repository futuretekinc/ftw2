/******************************************************************************
*
*               COPYRIGHT (c) 2013-2014 GainSpan Corporation
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
* $RCSfile: gsn_emu_sdadc.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_EMU_SDADC_H_
#define _GSN_EMU_SDADC_H_

#ifdef  __cplusplus
extern "C" {
#endif


/**
  ******************************************************************************
  *
  *  File inclusion 
  *
  *****************************************************************************/
#include "modules/emu/gsn_emu_common.h"
#include "modules/emu/gsn_emu_private.h"


/**
  ******************************************************************************
  *
  *  Macros 
  *
  *****************************************************************************/


/**
  ******************************************************************************
  *
  *  Public data types 
  *
  *****************************************************************************/

/**
  ******************************************************************************
  *
  *  Public variable 
  *
  *****************************************************************************/



/**
  ******************************************************************************
  *
  *  Private variable 
  *
  *****************************************************************************/



/**
  ******************************************************************************
  *
  *  Public Functions 
  *
  *****************************************************************************/

PUBLIC GSN_EMU_STATUS_T
GsnEmu_SdAdcStart(VOID * arg1, VOID *arg2);

PUBLIC VOID
GsnEmu_SdAdcCb (UINT32 *conbuf_0,UINT32 *conbuf_1,UINT32 *conbuf_2,UINT16 *size,
                UINT32 status,VOID *ctx);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_SdAdcStop(VOID * arg1, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_SdAdcLoadControl(BOOL onOff, VOID * arg1, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_SdAdcResetEnergy(VOID * arg1, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_SdAdcComputeElecParams(VOID *arg1, VOID *arg2, VOID *arg3);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_SdAdcGetInstantValues(VOID *arg1, VOID *arg2, VOID *arg3);


/**
  ******************************************************************************
  *
  *  Private Functions 
  *
  *****************************************************************************/




#ifdef  __cplusplus
}
#endif

#endif //GSN__EMU_SDADC_H_


