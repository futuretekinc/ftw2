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
* $RCSfile: gsn_wif_fpt.h,v $
*
* Description : Patch header file for gsn_wif.c
*****************************************************************************/
#ifndef GSN_WIF_FPT_H_
#define GSN_WIF_FPT_H_

/*****************************************************************************
 * Function pointer definitions
 ****************************************************************************/

typedef GSN_STATUS 
(* GsnWif_Init_FP_T)(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_INIT_PARAM_T *pParam);

extern _RPST_  GsnWif_Init_FP_T GsnWif_Init_FP;

typedef  PUBLIC GSN_STATUS 
(* GsnWif_Reinit_FP_T)(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_RE_INIT_PARAM_T *pParam);

extern _RPST_  GsnWif_Reinit_FP_T GsnWif_Reinit_FP;
 
typedef VOID 
(* GsnWif_CtrlCb_FP_T)(VOID * pCtx, GSN_WIF_CTL_TD_T *pCtrlTD);
extern _RPST_ GsnWif_CtrlCb_FP_T GsnWif_CtrlCb_FP;

typedef VOID 
(* GsnWif_DataCb_FP_T)(VOID * pCtx, GSN_WIF_DATA_TD_T *pDataTD);

extern _RPST_ GsnWif_DataCb_FP_T GsnWif_DataCb_FP;



#endif /*GSN_WIF_FPT_H_*/


