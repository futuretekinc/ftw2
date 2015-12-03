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
* $RCSfile: gsn_mb_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_MB_FPT_H_
#define _GSN_MB_FPT_H_
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "drivers/clk_ctl/gsn_clk_ctl.h"


/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef VOID 
(* GsnMb_Open_FP_T)(VOID);

extern _RPST_ GsnMb_Open_FP_T GsnMb_Open_FP;

typedef VOID 
(* GsnMb_SbMsgPut_FP_T)(UINT32 sb, 
						UINT32 msg);
extern _RPST_ GsnMb_SbMsgPut_FP_T GsnMb_SbMsgPut_FP;

typedef UINT32 
(* GsnMb_RbMsgGet_FP_T)(UINT32 rb);
extern _RPST_ GsnMb_RbMsgGet_FP_T GsnMb_RbMsgGet_FP;

typedef VOID 
(* GsnMb_RbIntRegister_FP_T)(UINT32 rbNum, 
							  GSN_CB_T *pCb);
extern _RPST_ GsnMb_RbIntRegister_FP_T GsnMb_RbIntRegister_FP;

typedef VOID 
(* GsnMb_RbIntUnregister_FP_T)(UINT32 rbNum);
extern _RPST_ GsnMb_RbIntUnregister_FP_T GsnMb_RbIntUnregister_FP;

typedef VOID 
(* GsnMb_RbIsr_FP_T)(VOID);
extern _RPST_ GsnMb_RbIsr_FP_T GsnMb_RbIsr_FP;

typedef void 
(* GsnMB_Isr_FP_T)(void);
extern _RPST_ GsnMB_Isr_FP_T GsnMB_Isr_FP;


#endif



