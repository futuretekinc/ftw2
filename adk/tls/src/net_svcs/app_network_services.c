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
 * $RCSfile: app_network_services.c,v $
 *
 * Description : s2w GEPS interface file
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
/* APP file inclusion section */
#include "app_net_svcs_priv.h"
#include "app_debug.h"
#include "app_iot_gateway_updater.h"
#include "app_cloud_helper.h"

extern void App_MdnsInit(APP_MAIN_CTX_T *pAppCtx);

extern void App_MdnsDeInit(APP_MAIN_CTX_T *pAppCtx);
/**
 * This function starts the various network services required by the
 * application.
 */
// FIXME
GSN_NWIF_IP_CONFIG_T s_nwParams;

PUBLIC UINT32 App_NetworkServicesStart(APP_MAIN_CTX_T *pAppCtx)
{
    AppDbg_Printf("[%s] Entered\r\n", __FUNCTION__);
    /* get the ip information by calling geps API */
    GsnNwIf_IpConfigGet(&pAppCtx->if0.nwifCtx, &s_nwParams);

    /* Start HTTP Server */
    App_HttpdStart(pAppCtx);

    /* Start MDNS */
#ifdef APP_MDNS_ENABLE
    App_MdnsInit(pAppCtx);
#endif


    if (pAppCtx->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_STA)
    {
		#ifdef ADK_CLOUD_ENABLE
    		App_CloudUpdaterInit(pAppCtx);
		#endif
		#ifdef ADK_IOT_GATEWAY_ENABLE
            App_IotGatewayUpdaterStart(pAppCtx);
		#endif
    }

    return GSN_SUCCESS;
}

PUBLIC VOID App_NetworkServicesStop(APP_MAIN_CTX_T *pAppCtx)
{
	App_HttpdStop(pAppCtx);
#ifdef APP_MDNS_ENABLE
	App_MdnsDeInit(pAppCtx);
#endif
}

