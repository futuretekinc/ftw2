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
* $RCSfile: gsn_emu_pl722x_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_EMU_PL722x_FPT_H_
#define _GSN_EMU_PL722x_FPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"


/*****************************************************************************
  *  Definitions
****************************************************************************/

typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Pl722xStart_FP_T)(VOID *arg1, VOID *arg2);

extern _RPST_ GsnEmu_Pl722xStart_FP_T GsnEmu_Pl722xStart_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Pl722xStop_FP_T)(VOID * arg1, VOID *arg2);

extern _RPST_ GsnEmu_Pl722xStop_FP_T GsnEmu_Pl722xStop_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Pl722xLoadControl_FP_T)(BOOL onOff, VOID * arg1, VOID *arg2);

extern _RPST_ GsnEmu_Pl722xLoadControl_FP_T GsnEmu_Pl722xLoadControl_FP;

typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Pl722xResetEnergy_FP_T)(VOID * arg1, VOID *arg2);

extern _RPST_ GsnEmu_Pl722xResetEnergy_FP_T GsnEmu_Pl722xResetEnergy_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Pl722xComputeElecParams_FP_T)(VOID * arg1, VOID *arg2, VOID *arg3);

extern _RPST_ GsnEmu_Pl722xComputeElecParams_FP_T GsnEmu_Pl722xComputeElecParams_FP;


typedef PUBLIC VOID
(* GsnEmu_Pl722xTimerCb_FP_T)( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle );

extern _RPST_ GsnEmu_Pl722xTimerCb_FP_T GsnEmu_Pl722xTimerCb_FP;


#ifdef __cplusplus
}
#endif

#endif /* _GSN_EMU_PL722X_FPT_H_ */