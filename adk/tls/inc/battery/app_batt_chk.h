/******************************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: app_batt_chk.h,v $
*
* Description : This file contains battery structure definition and public APIs declaration.
* parameters  .
******************************************************************/

#ifndef _APP_BATT_CHK_H_
#define _APP_BATT_CHK_H_


typedef struct _APP_BATT_RTC_CTX
{
    UINT32 currBattVal;

}APP_BATT_RTC_CTX_T;

typedef struct _APP_BATT_CTX
{
    APP_BATT_RTC_CTX_T *pRtcBattCtx;

}APP_BATT_CTX_T;


PUBLIC VOID
AppBatt_Init(APP_BATT_CTX_T *pAppBattCtx, APP_BATT_RTC_CTX_T *pAppBattRtcCtx, GSN_SYS_CTL_CTX_T *pSysCtlCtx);

PUBLIC VOID
AppBatt_ChkIndCb(VOID* ctx,GSN_SYS_CTL_BATT_CHK_IND_T *battChkInd);

PUBLIC GSN_STATUS_T
AppBatt_LatestBattValGet(APP_BATT_CTX_T *pAppBattCtx, UINT32 *battValue);

#endif
