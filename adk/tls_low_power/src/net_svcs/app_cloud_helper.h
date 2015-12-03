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
 * app_cloud_helper.h
 *
 *  Created on: 17-May-2013
 *      Author: Dhanya Lakshmi
 */

#ifndef APP_CLOUD_HELPER_H_
#define APP_CLOUD_HELPER_H_

//#include "gsn_includes.h"
#include "app_net_svcs_priv.h"
#include "gsn_cloud_api.h"



void App_CloudUpdaterInit(APP_MAIN_CTX_T *pAppCtx);

VOID App_CloudUpdaterCb(enum GSN_CALLBACK_METHOD method, GSN_CLOUD_CALLBACK_DATA_T* cloudCallbackData);



#endif /* APP_CLOUD_HELPER_H_ */
