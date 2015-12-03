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
* $RCSfile: gsn_hi_mb_fpt.h,v $
*
* Description : This file contains function poointer definitions for the event handler
* module.
******************************************************************************/


/*****************************************************************************
* File Inclusion
*****************************************************************************/

#ifndef _GSN_HI_MB_FPT_H_
#define _GSN_HI_MB_FPT_H_


#include "gsn_includes.h"

typedef VOID (* GsnHiMb_Init_FP_T)(GSN_HI_MB_CTX_T *pHiMbCtx);
extern _RPST_ GsnHiMb_Init_FP_T GsnHiMb_Init_FP;

typedef VOID (* GsnHiMb_RecvCbRegister_FP_T)(GSN_HI_MB_CTX_T *pHiMbCtx, GSN_CB_T *recvCbInfo);
extern _RPST_ GsnHiMb_RecvCbRegister_FP_T GsnHiMb_RecvCbRegister_FP;

typedef GSN_STATUS (* GsnHiMb_MsgSend_FP_T)(GSN_HI_MB_CTX_T *pHiMbCtx, UINT32 *msg);
extern _RPST_ GsnHiMb_MsgSend_FP_T GsnHiMb_MsgSend_FP;

typedef VOID (* GsnHiMb_MsgRcv_FP_T)(VOID *pThis, const VOID *pParam);
extern _RPST_ GsnHiMb_MsgRcv_FP_T GsnHiMb_MsgRcv_FP;

typedef VOID (* GsnHiMb_AckRcv_FP_T)(VOID *pThis, const VOID *pParam);
extern _RPST_ GsnHiMb_AckRcv_FP_T  GsnHiMb_AckRcv_FP;

#endif
