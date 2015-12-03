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
* $RCSfile: gsn_emu_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_EMU_FPT_H_
#define _GSN_EMU_FPT_H_

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


typedef PUBLIC UINT32
(* GsnEmu_GetSupportedModules_FP_T)();

extern _RPST_ GsnEmu_GetSupportedModules_FP_T GsnEmu_GetSupportedModules_FP;


typedef PUBLIC VOID
(* GsnEmu_GetVersion_FP_T)(UINT8 *ptr);

extern _RPST_ GsnEmu_GetVersion_FP_T GsnEmu_GetVersion_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Init_FP_T) (GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_MODE_T mode,
                  GSN_EMU_TASKNOTIFICATION_FUNC_T taskNotifier,
                  GSN_EMU_APPNOTIFICATION_FUNC_T appCb,
                  VOID* ctx);

extern _RPST_ GsnEmu_Init_FP_T GsnEmu_Init_FP;

typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_DeInit_FP_T)(GSN_EMU_CTX_T* pEmuCtx);

extern _RPST_ GsnEmu_DeInit_FP_T GsnEmu_DeInit_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_GetState_FP_T)(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_STATE_T *state);

extern _RPST_ GsnEmu_GetState_FP_T GsnEmu_GetState_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_GetMode_FP_T)(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_MODE_T *mode);

extern _RPST_ GsnEmu_GetMode_FP_T GsnEmu_GetMode_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_GetElectricParams_FP_T)(GSN_EMU_CTX_T* pEmuCtx,
                          GSN_EMU_ELECTRIC_PARAMS_T*elecParams);

extern _RPST_ GsnEmu_GetElectricParams_FP_T GsnEmu_GetElectricParams_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_GetInstantElectricParams_FP_T)(GSN_EMU_CTX_T* pEmuCtx,
                                  GSN_EMU_ELECTRIC_PARAMS_T*elecParams);

extern _RPST_ GsnEmu_GetInstantElectricParams_FP_T GsnEmu_GetInstantElectricParams_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_GetLoadStatus_FP_T)(GSN_EMU_CTX_T* pEmuCtx, BOOL *onOff);

extern _RPST_ GsnEmu_GetLoadStatus_FP_T GsnEmu_GetLoadStatus_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Start_FP_T)(GSN_EMU_CTX_T *pEmuCtx,
             GSN_EMU_CONF_VALUE_T *confvalue,
             GSN_EMU_SDADC_PINGPONG_BUFF_T *pingBuff);

extern _RPST_ GsnEmu_Start_FP_T GsnEmu_Start_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Stop_FP_T)(GSN_EMU_CTX_T* pEmuCtx);

extern _RPST_ GsnEmu_Stop_FP_T GsnEmu_Stop_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Pause_FP_T)(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_ELECTRIC_PARAMS_T *elecParams);

extern _RPST_ GsnEmu_Pause_FP_T GsnEmu_Pause_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_Resume_FP_T)(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_ELECTRIC_PARAMS_T *elecParams,
                 GSN_EMU_CONF_VALUE_T *confvalue);

extern _RPST_ GsnEmu_Resume_FP_T GsnEmu_Resume_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_LoadControl_FP_T)(GSN_EMU_CTX_T* pEmuCtx, BOOL onOff);

extern _RPST_ GsnEmu_LoadControl_FP_T GsnEmu_LoadControl_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_ResetEnergy_FP_T)(GSN_EMU_CTX_T* pEmuCtx);

extern _RPST_ GsnEmu_ResetEnergy_FP_T GsnEmu_ResetEnergy_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_PrivateCheckThrehold_FP_T)(GSN_EMU_CTX_T* pCtx);

extern _RPST_ GsnEmu_PrivateCheckThrehold_FP_T GsnEmu_PrivateCheckThrehold_FP;


typedef PUBLIC VOID
(* GsnEmu_MsgProcess_FP_T)(GSN_EMU_MSG_T *pMsg);

extern _RPST_ GsnEmu_MsgProcess_FP_T GsnEmu_MsgProcess_FP;


typedef PUBLIC GSN_EMU_STATUS_T
(* GsnEmu_GetConfPtr_FP_T)(GSN_EMU_CTX_T *pCtx, GSN_EMU_CONF_VALUE_T *confValue);

extern _RPST_ GsnEmu_GetConfPtr_FP_T GsnEmu_GetConfPtr_FP;




#ifdef __cplusplus
}
#endif

#endif /* _GSN_EMU_FPT_H_ */