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
 * $RCSfile: app_httpd_cb.c,v $
 *
 * Description : s2w GEPS interface file
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_api.h"
#include "modules/mdns_sd/gsn_mdns.h"

#ifdef ADK_PROV_ENABLE
#include "gsn_httpd_config.h"
#include "gsn_httpd_prov.h"
#include "modules/http/gsn_httpd_file_api.h"
#endif

#ifdef ADK_OTAFU_ENABLE
//#include "gsn_httpd_file_api.h"
#endif

#include "app_net_svcs_priv.h"
#include "api\api_safe.h"
#include "app_httpd_cb.h"
#include "app_debug.h" 
#include "app_main_ctx.h"
/* Compile time flags controlling application behavior */
#define APP_ASYNC_REBOOT

#ifdef APP_ASYNC_REBOOT

PRIVATE GSN_OSAL_THREAD_TCB_T rebootTask;

VOID App_RebootSoc(UINT32 ctx)
{
    GsnTaskSleep(1000);
    GsnSys_Reset(GSN_RESET_REASON_APP_ASSERT);
}
#else
VOID App_RebootSoc(UINT32)
{
    GsnSys_Reset(0);
}

#endif

VOID App_Reboot(BOOL async)
{
#ifdef APP_ASYNC_REBOOT
    /* Rebooting in a separate thread
     * so that HTTP response can go from httpd to client.
     * FIXME: This however does NOT work
     */
    if (async)
    {
        UINT8* stack = (UINT8*) malloc(2048);
        if (stack)
        {
            GsnOsal_ThreadCreate(App_RebootSoc, NULL, &rebootTask,
                    (UINT8*) "rebootThread", APP_CFG_SYS_REBOOT_THREAD_PRIORITY,
                    stack, 2048, GSN_OSAL_THREAD_INITIAL_READY);
        }
        else
        {
            App_RebootSoc(0);
        }
    }
    else
    {
        App_RebootSoc(0);
    }

#else
    App_RebootSoc();
#endif
}

#ifdef ADK_PROV_ENABLE

PRIVATE VOID App_ApplySysConfig(GSN_SYS_CONFIG_T *pConfig)
{
    UINT8 state;

    if (pConfig->sysConfigChangeApply)
    {
#ifdef APP_MDNS
            App_MdnsDeInit();
#endif
            App_Reboot(TRUE);
    }
}


extern GSN_NWIF_IP_CONFIG_T s_nwParams;
/*
 * Callback function for the /gainspan/config handler
 * It is up to the application to deal with the configuration.
 * This function further dispatches GET and POST
 * separately.
 */
VOID App_ConfigCb(GSN_SYS_CONFIG_T *pConfig, UINT8 method)
{
    AppDbg_Printf("[%s] Entered\r\n", __FUNCTION__);

    // TODO - Is this the correct place to do this? Revisit
    f_chdrive(0);

	/*copy the passed structure and store it in the flash memory*/
	if(method == GSN_HTTPD_URI_METHOD_GET)
	{
        AppConfig_Load(pConfig);
        pConfig->networkConfig.ipConfig.ipAddr = htonl(s_nwParams.ipv4.ipAddr);
	}

	if (method == GSN_HTTPD_URI_METHOD_POST)
	{
		AppConfig_Save(pConfig);
        /* Apply System configuration, if necesary */
        App_ApplySysConfig(pConfig);
	}

    // TODO - Is this the correct place to do this? Revisit
    f_chdrive(1);


	return;
}
#endif /* ADK_PROV_ENABLE */

#ifdef ADK_PROV_WPS_ENABLE

VOID AppWps_DisconnectCb(VOID *pCtx, GSN_STATUS status )
{
    UINT32 msg = APP_EVENT_STA_WPS_INITIATE;
        // stop the network services
    App_NetworkServicesStop(pCtx);
    /* Notify APP */
    AppMainCtx_TaskNotify(msg,0);
}

/*
 * Callback function for WPS handling
 */
void AppWps_CbFn(char* mode, char* pin)
{
	GSN_STATUS_T status;
    UINT8 i, wpsPin[GSN_WDD_SEC_WPS_PIN_LEN];
    UINT8* p = &wpsPin[0];
    APP_MAIN_CTX_T * appctx = globalAppCtxPtr;


    memset((INT8 *)&appctx->wpsapSsid, 0, sizeof(globalAppCtxPtr->wpsapSsid));
    if (!strcmp(mode, "pbc"))
    {
    	memset(appctx->wpsParams.pin,0x00,GSN_WDD_SEC_WPS_PIN_LEN);
    	appctx->wpsParams.type = APP_WPS_TYPE_PB;
    	status = GsnWdd_Disconnect(&appctx->if0.wddCtx,0,
                AppWps_DisconnectCb, appctx);
    }
    else if (!strcmp(mode, "pin"))
    {
    	appctx->wpsParams.type = APP_WPS_TYPE_PIN;
        if (GSN_WDD_SEC_WPS_PIN_LEN != strlen((const char*) pin))
        {
            return;
        }
        for (i = 0; i < GSN_WDD_SEC_WPS_PIN_LEN; i++)
        {
            if (*(pin + i) < '0' || *(pin + i) > '9')
            {
                return;
            }
            *(p+i)= *(pin+i); /* convert to integer */
        }

        memcpy(appctx->wpsParams.pin, p, GSN_WDD_SEC_WPS_PIN_LEN);

        status = GsnWdd_Disconnect(&appctx->if0.wddCtx,0,
                AppWps_DisconnectCb, appctx);
    }
    /* If the operation is complete, then notify APP
     */
    if (GSN_OPERATION_IN_PROGRESS != status)
    {
    	AppWps_DisconnectCb(appctx, status);
    }


}
#endif /* ADK_PROV_WPS_ENABLE */

