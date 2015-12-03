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
* $RCSfile: gsn_otafu_fpt.c,v
*/

#include "gsn_otafu_fpt.h"

_RPST_ GsnOtafu_BinIndexGet_FP_T GsnOtafu_BinIndexGet_FP = NULL;

_RPST_ GsnOtafu_FwupInit_FP_T GsnOtafu_FwupInit_FP = NULL;

_RPST_ GsnOtafu_FwupContinue_FP_T GsnOtafu_FwupContinue_FP = NULL;

_RPST_ GsnOtafu_FwupEnd_FP_T GsnOtafu_FwupEnd_FP = NULL;

_RPST_ GsnOtafu_DeInit_FP_T GsnOtafu_DeInit_FP = NULL;

_RPST_ GsnOtafu_Cb_FP_T GsnOtafu_Cb_FP = NULL;

_RPST_ GsnOtafu_Init_FP_T GsnOtafu_Init_FP = NULL;

