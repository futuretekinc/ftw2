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
* $RCSfile: gsn_emu_pl722x.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_EMU_PL722X_H_
#define _GSN_EMU_PL722X_H_

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
#include "modules/emu/gsn_drivers_pl722x.h"

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
  
PUBLIC VOID
GsnEmu_Pl722xTimerCb( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle );

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Pl722xStart(VOID * arg, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Pl722xStop(VOID * arg, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Pl722xLoadControl(BOOL onOff, VOID * arg1, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Pl722xResetEnergy(VOID * arg1, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Pl722xComputeElecParams(VOID *arg1, VOID *arg2, VOID *arg3);


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



/**
  ******************************************************************************
  *
  *  Private Functions 
  *
  *****************************************************************************/


#ifdef  __cplusplus
}
#endif

#endif //_GSN_EMU_PL722X_H_

