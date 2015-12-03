/*******************************************************************************
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
 * $RCSfile: app_batt_chk.c,v $
 *
 * Created on: Aug 14, 2014
 * Author: NUpadhyay
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/

#include "gsn_includes.h"
#include "battery/app_batt_chk.h"


/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Battery check condition.
 *      This function handle the battery check condition and
 *      store the latest value.
 * @param ctx    - IN pointer to the context.
 * @param ctrl   - IN control.
 * @retval VOID.
******************************************************************************/

PUBLIC VOID
AppBatt_ChkIndCb(VOID* ctx,GSN_SYS_CTL_BATT_CHK_IND_T *battChkInd)
{
    APP_BATT_CTX_T *pAppBattCtx = (APP_BATT_CTX_T *)ctx;

	pAppBattCtx->pRtcBattCtx->currBattVal = battChkInd->batteryMeasure;
}

/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Handling the battery check Init operation.
 *    This function handle the battery Init start operation.
 *    This function initialize the battery check module and registers the
 *    call back function for indication.
 * @param ctx - IN  pointer to the App Battery context
 * @param ctx - IN  pointer to the Rtc Battery context
 * @param ctx - IN  pointer to the Wfi System control module context
 * @retval VOID.
******************************************************************************/

PUBLIC VOID
AppBatt_Init(APP_BATT_CTX_T *pAppBattCtx, APP_BATT_RTC_CTX_T *pAppBattRtcCtx, GSN_SYS_CTL_CTX_T *pSysCtlCtx)
{
	GSN_STATUS status;
	GSN_SYS_CTL_BATT_CHK_REQ_PARAM_T battChkReqParam;

	pAppBattCtx->pRtcBattCtx = pAppBattRtcCtx;

	battChkReqParam.repeatNumTx = 1;

	/*register with WLAN Interface */
	GsnSysCtl_BatteryChkStart(pSysCtlCtx,&battChkReqParam,
								   AppBatt_ChkIndCb,pAppBattCtx);

}


/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Get the latest battery value stored in RTC memory.
 *    This function getting called from application to get the latest battery
 *    Value stored in Battery context.
 * @param ctx    - IN pointer to the App Battery context.
 * @param pData  - IN user data.
 * @retval S2W_SUCCESS or S2W_FAILURE.
 *****************************************************************************/

PUBLIC GSN_STATUS_T
AppBatt_LatestBattValGet(APP_BATT_CTX_T *pAppBattCtx, UINT32 *battValue)
{

	*battValue = pAppBattCtx->pRtcBattCtx->currBattVal;

	return GSN_SUCCESS;
}
