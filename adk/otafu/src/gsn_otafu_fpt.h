/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_otafu_fpt.h,v
*/
#ifndef _GSN_OTAFU_FPT_H_
#define _GSN_OTAFU_FPT_H_

#include "..\inc\gsn_otafu.h"

typedef INT32
(*GsnOtafu_BinIndexGet_FP_T)(char* pTagName, INT32 tagNameLength);
extern _RPST_ GsnOtafu_BinIndexGet_FP_T GsnOtafu_BinIndexGet_FP;

typedef GSN_STATUS
(*GsnOtafu_FwupInit_FP_T)(GSN_OTAFU_CTX_T *pCtx);
extern _RPST_ GsnOtafu_FwupInit_FP_T GsnOtafu_FwupInit_FP;

typedef GSN_STATUS
(*GsnOtafu_FwupContinue_FP_T)(GSN_OTAFU_CTX_T *pCtx, INT8 *buffer, UINT32 bufferLen);
extern _RPST_ GsnOtafu_FwupContinue_FP_T GsnOtafu_FwupContinue_FP;

typedef GSN_STATUS
(*GsnOtafu_FwupEnd_FP_T)(GSN_OTAFU_CTX_T *pCtx);
extern _RPST_ GsnOtafu_FwupEnd_FP_T GsnOtafu_FwupEnd_FP;

typedef GSN_STATUS
(*GsnOtafu_DeInit_FP_T)(GSN_OTAFU_CTX_T *pCtx);
extern _RPST_ GsnOtafu_DeInit_FP_T GsnOtafu_DeInit_FP;

typedef BOOL
(*GsnOtafu_Cb_FP_T)(GSN_HTTPD_ELEMENT_INFO_T inputElementInfo, INT8 *buffer, UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event, GSN_HTTPD_STATUS_INFO_T *statusMsg);
extern _RPST_ GsnOtafu_Cb_FP_T GsnOtafu_Cb_FP;

typedef PUBLIC VOID
(*GsnOtafu_Init_FP_T)(GSN_OTAFU_CTX_T* pOtafuCtx);
extern _RPST_ GsnOtafu_Init_FP_T GsnOtafu_Init_FP;

#endif
