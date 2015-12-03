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
* $RCSfile: app_net_svcs_priv.h,v
*/

#ifndef APP_NET_SCVS_PRIV_H_
#define APP_NET_SCVS_PRIV_H_

/* APP file inclusion section */
#include "app_events.h"
#include "app_defines.h"
#include "config\app_resource_config.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "battery/app_batt_chk.h"
#include "main\app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_defs.h"

#ifndef APP_PRINTF
#endif

GSN_STATUS App_HttpdStart(APP_MAIN_CTX_T *pAppCtx);

void App_DebugPrintf(const char *format, ...);

GSN_STATUS App_HttpdStop(APP_MAIN_CTX_T *pAppCtx);

void App_NetworkServicesStop(APP_MAIN_CTX_T *pAppCtx);

#endif /* APP_NET_SCVS_PRIV_H_ */
