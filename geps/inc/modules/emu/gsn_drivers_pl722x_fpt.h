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
* $RCSfile: gsn_drivers_pl722x_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_DRIVERS_PL722x_FPT_H_
#define _GSN_DRIVERS_PL722x_FPT_H_

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
typedef PUBLIC PL722X_STATUS
(* PL722X_Init_FP_T)(PL722X_CONFIG_T *config);

extern _RPST_ PL722X_Init_FP_T PL722X_Init_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_ReadParam_FP_T)(PL722X_PARAMS_T* param);

extern _RPST_ PL722X_ReadParam_FP_T PL722X_ReadParam_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_GetElectricUnits_FP_T)(PL722X_ELECTRIC_UNITS_T *elecUnits);

extern _RPST_ PL722X_GetElectricUnits_FP_T PL722X_GetElectricUnits_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_Read_FwVer_FP_T)(PL722X_FW_VER_T *fwVer);

extern _RPST_ PL722X_Read_FwVer_FP_T PL722X_Read_FwVer_FP;


typedef PUBLIC PL722X_STATUS
(* PL722X_Read_FP_T)(UINT16 addr, UINT8 bytesToRead, UINT8 *ptr);

extern _RPST_ PL722X_Read_FP_T PL722X_Read_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_Write_FP_T)(UINT16 addr, UINT8 bytesToWrite, UINT8 *ptr);

extern _RPST_ PL722X_Write_FP_T PL722X_Write_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_Close_FP_T)(VOID);

extern _RPST_ PL722X_Close_FP_T PL722X_Close_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_ControlLoad_FP_T)(BOOL status);

extern _RPST_ PL722X_ControlLoad_FP_T PL722X_ControlLoad_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_ResetKWH_FP_T)(VOID);

extern _RPST_ PL722X_ResetKWH_FP_T PL722X_ResetKWH_FP;

typedef PUBLIC VOID
(* PL722X_DisableOCP_FP_T)(VOID);

extern _RPST_ PL722X_DisableOCP_FP_T PL722X_DisableOCP_FP;

typedef PUBLIC VOID
(* PL722X_EnableOCP_FP_T)(VOID);

extern _RPST_ PL722X_EnableOCP_FP_T PL722X_EnableOCP_FP;

typedef PUBLIC BOOL
(* PL722X_GetOCPStatus_FP_T)(VOID);

extern _RPST_ PL722X_GetOCPStatus_FP_T PL722X_GetOCPStatus_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_GetOCPParams_FP_T)(PL722X_OCP_PARAM_T *param);

extern _RPST_ PL722X_GetOCPParams_FP_T PL722X_GetOCPParams_FP;


typedef PUBLIC PL722X_STATUS
(* PL722X_SetLoadingCurrent_FP_T)(UINT8 *ptr);

extern _RPST_ PL722X_SetLoadingCurrent_FP_T PL722X_SetLoadingCurrent_FP;

typedef PUBLIC PL722X_STATUS
(* PL722X_SetLoadingTime_FP_T)(UINT8 *ptr);

extern _RPST_ PL722X_SetLoadingTime_FP_T PL722X_SetLoadingTime_FP;

typedef PUBLIC VOID
(* GsnSpi_PollMasterByteReadWrite_FP_T)(UINT8 spiChannel, UINT8 txByte, UINT8 *rxByte);

extern _RPST_ GsnSpi_PollMasterByteReadWrite_FP_T GsnSpi_PollMasterByteReadWrite_FP;

#ifdef __cplusplus
}
#endif

#endif /* _GSN_DRIVERS_PL722x_FPT_H_ */