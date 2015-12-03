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
 * $RCSfile: app_httpd.c,v $
 *
 * Description : s2w GEPS interface file
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_api.h"
#include "modules/http/gsn_httpd_logo.h"

#ifdef ADK_PROV_ENABLE
#include "gsn_httpd_config.h"
#include "gsn_httpd_prov.h"
#include "modules/http/gsn_httpd_file_api.h"
#endif

#ifdef ADK_OTAFU_ENABLE
//#include "gsn_httpd_file_api.h"
#include "modules/http/gsn_httpd_file_api.h"
#include "gsn_otafu.h"
#endif

#include "app_net_svcs_priv.h"
#include "app_httpd_cb.h"
#include "app_cfg.h"
#include "app_debug.h"

#ifdef ADK_PROV_ENABLE
GSN_WLAN_REG_DOMAIN_T appWlanRegDomain =  GSN_WLAN_REG_DOMAIN_UNKNOWN;
#endif

PUBLIC INT8 AppHttp_ApiInit(VOID);

/*[ TO DO] - This declaration should come from a header file*/
//extern UINT8 GsnHttpdApi_FwInit(UINT32 wlanVer, UINT8* appVersion);

//extern UINT8 GsnHttpdApi_SysDebugInit();

#define APP_HTTPD_MAX_TOTAL_CONN    32
#define APP_HTTPD_MAX_PER_IP_CONN   16
#define APP_HTTPD_IDLE_TIMEOUT      5
#define APP_HTTPD_PORT              80

#define APP_HTTPD_BLOCKING_STATE    1

/*
 * This is the entry point for the HTTP Server
 */
PUBLIC GSN_STATUS 
App_HttpdStart(APP_MAIN_CTX_T *pAppCtx)
{
    UINT32 wlanVer = 0;
    GSN_HTTPD_CONFIG_T config;	
	GSN_NWIF_IP_CONFIG_T ipConfig;

#ifdef ADK_PROV_ENABLE	
    GSN_HTTPD_PROV_CONFIG_T provConfig;	
	GSN_WLAN_REG_DOMAIN_T appWlanRegDomain = GSN_WLAN_REG_DOMAIN_UNKNOWN;
#endif

    AppDbg_Printf("[%s] Entered\r\n", __FUNCTION__);

    /* get the ip information by calling geps API */
    GsnNwIf_IpConfigGet(&pAppCtx->if0.nwifCtx, &ipConfig);

	/* Initialize web parameters */
    memset(&config, 0, sizeof(GSN_HTTPD_CONFIG_T));

    /* store user mane and passwd*/
    strcpy(config.username, (const INT8 *)pAppCtx->config.httpdConfig.username);
    strcpy(config.password, (const INT8 *)pAppCtx->config.httpdConfig.password);
    config.port = APP_HTTPD_PORT;
    config.maxConnPerIp = APP_HTTPD_MAX_PER_IP_CONN;
    config.maxConnTotal = APP_HTTPD_MAX_TOTAL_CONN;
    config.blockingState = APP_HTTPD_BLOCKING_STATE;
    config.threadPriority = APP_CFG_WEB_SRVR_THREAD_PRIORITY;
    config.idleTimeout = APP_HTTPD_IDLE_TIMEOUT;
	
    config.ip_flag = GSN_USE_IPV4;
    config.ipAddr = ipConfig.ipv4.ipAddr;

    config.rootCgiDir = NULL;
    config.rootDir = "/";
    config.defaultFileName = "index.html";
	config.mallocTimeout = 2 *1000; /* 2 Sec. */

    config.stack = (UINT8 *)MALLOC(APP_CFG_WEB_SRVR_STACK_SIZE);	 
	if(NULL == config.stack)
	{
		return GSN_FAILURE;
	}
    config.stackSize  = APP_CFG_WEB_SRVR_STACK_SIZE;
    config.pool_hdl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_LBUF_PKT_POOL);
	config.sysQualTskID = APP_CFG_SQ_HTTPD_TASK_ID;
	config.sysQualTicks = APP_CFG_SQ_TICKS_FOR_HTTPD_TASK;
    /* Start httpd */
    GsnHttpd_Start(config, NULL);
	
#ifdef ADK_PROV_ENABLE
    /* System Configuration URI Handler  */
    GsnHttpdApi_ConfigInit(App_ConfigCb);

	/* Scan Configuration URI Handler */
    memset(&provConfig, 0x0, sizeof(provConfig));
    provConfig.pWdd = &pAppCtx->if0.wddCtx;
    provConfig.domain = appWlanRegDomain;

#ifdef ADK_PROV_WPS_ENABLE
    provConfig.pWpsCbFn = (GSN_HTTPD_PROV_WPS_CB_FN_T) AppWps_CbFn;
#endif /* ADK_PROV_WPS_ENABLE */
    GsnHttpdApi_ProvInit(&provConfig);
#endif /* ADK_PROV_ENABLE */

    /* API Configuration URI Handler */
    GsnHttpdApi_ApiInit();

#ifdef ADK_API_SYS_DEBUG_ENABLE
    GsnHttpdApi_SysDebugInit();
#endif /*ADK_API_SYS_DEBUG_ENABLE */

    /*Get Wlan Version*/
    GsnSysCtl_WlanFwVerGet(&pAppCtx->sysCtlCtx,&wlanVer);
    GsnHttpdApi_FwInit(wlanVer, (UINT8*)AppConfig_GetAppNameAndVersion());

    /* Application's URI Handler*/
    AppHttp_ApiInit();

	/* File Upload App Configuration Handler */
#ifdef ADK_FILE_UPLOAD_API
	GsnHttpd_FileApiInit();
#ifdef ADK_FILE_UPLOAD_APP_CONTENT_DISPLAY
	GsnHttpd_FileApiConfig("/gainspan/system/fileupload", AppFileUpload_FilesPrintCb, GSN_HTTPD_URI_METHOD_POST);
#endif

#ifdef ADK_OTAFU_ENABLE
	AppOtafu_Init(pAppCtx);
#endif
#endif /*ADK_FILE_UPLOAD_API*/

    return GSN_SUCCESS;
}

PUBLIC GSN_STATUS 
App_HttpdStop(APP_MAIN_CTX_T *pAppCtx)
{
	return GsnHttpd_Stop();
}

