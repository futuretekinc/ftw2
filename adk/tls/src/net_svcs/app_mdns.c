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
 * $RCSfile: app_mdns.c,v $
 *
 * Description : App Mdns File
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"

#include "modules\http\gsn_httpd_api.h"
#include "modules\mdns_sd\gsn_mdns.h"

#ifdef ADK_OTAFU_ENABLE
#include "gsn_otafu.h"
#endif
#include "gsn_ncm.h"
#include "config/app_cfg.h"
#include "app_fsIf.h"
#include "battery/app_batt_chk.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_debug.h"

#include "app_net_svcs_priv.h"
#include "app_iot_gateway_updater.h"
GSN_OSAL_SEM_T appTlsServiceDiscoverWaitSem;
BOOL serviceDiscovered;

#ifdef APP_MDNS_ENABLE

#define TEXT_RECORD_DATA "=api=gs_profile_proxyserver:0.9.0:gainspan/profile/proxyserver"
 
#define APP_SVC_MDNS_KEY_VAL "api="APP_HTTP_API_NAME":"APP_HTTP_API_VERSION":"APP_HTTP_API_PATH
UINT8 *keyValAppSvc[3] =
{
    "path=" APP_WEB_APP_PATH,
    APP_SVC_MDNS_KEY_VAL,
    0
};

#ifdef ADK_OTAFU_ENABLE
#define APP_OTAFU_MDNS_KEY_VAL "api="GSN_HTTP_OTAFU_API_NAME":"GSN_HTTP_OTAFU_API_VERSION":"GSN_HTTP_OTAFU_API_PATH
UINT8 *keyValFwup[3] =
{
    "path=/otafu.html",
    APP_OTAFU_MDNS_KEY_VAL,
     0
};
#endif

#ifdef ADK_PROV_ENABLE
#define APP_SYS_MDNS_KEY_VAL "api="GSN_HTTP_SYS_API_NAME":"GSN_HTTP_SYS_API_VERSION":"GSN_HTTP_SYS_API_PATH
#ifdef GSN_WEB_APP_PROV_AP
UINT8 *keyValProv[3] =
{
    "path=/gsap.html",
    APP_SYS_MDNS_KEY_VAL,
    0
};
#else
UINT8 *keyValProv[3] =
{
    "path=/gsprov.html",
    APP_SYS_MDNS_KEY_VAL,
    0
};
#endif
#endif

INT8 App_MdnsProvSrv[64];
INT8 App_MdnsAppSvcSrv[64];
INT8 App_MdnsFwupSrv[64];
INT8 App_MdnsHostName[64];

VOID
App_MdnsMsgPostCb(VOID *cbCtx, VOID *pMdns);

GSN_STATUS  
App_MdnsHNreg(GSN_MDNS_T *pMdns, UINT32          ipAddr);

GSN_STATUS  
App_MdnsSrvcReg(GSN_MDNS_T *pMdns, UINT8 httpsFlag);

VOID
AppMainCtx_TaskNotify(INT32 msgId, UINT32 msgInfo);

VOID AppWebProv_RrRegCb(void *pData, UINT8 *rrName, UINT32 status)
{
	/*[TO DO]*/
    /*GsnMdns_Announce(&mdns);*/
}

/**
 * Initialize values (host name and service names) used when registering
 * mDNS/DNS-SD service names and records
 */
void App_MdnsInitValues(APP_MAIN_CTX_T *pAppCtx)
{
    strcpy((char*)App_MdnsHostName, (void*)pAppCtx->config.sysIdConfig.name);
	sprintf(App_MdnsAppSvcSrv, "%s" APP_NAME_SUFFIX, App_MdnsHostName);
#ifdef ADK_PROV_ENABLE	
    sprintf(App_MdnsProvSrv, "%s_Prov", App_MdnsHostName);
#endif
#ifdef ADK_OTAFU_ENABLE
    sprintf(App_MdnsFwupSrv, "%s_Otafu", App_MdnsHostName);
#endif
}

#if 0
PRIVATE GSN_OSAL_THREAD_TCB_T appMdnsThread;
PRIVATE UINT32 appMdnsThreadStack[APP_CFG_MDNS_STACK_SIZE/sizeof(UINT32)];

PRIVATE VOID   
App_MdnsThreadEntry(UINT32 ctx)
{

    /*UINT status;*/
    //UINT32 msg = 0;

   /* Start debug UART before starting the idle handler because the 
       debug UART flushing is done in idle handler context */

    /**< Initialize debug module */
   APP_MAIN_CTX_T *pAppCtx;
   pAppCtx = (APP_MAIN_CTX_T *)ctx;
   
   
    GsnMdns_Execute(&pAppCtx->mdns);/* This will not exit*/
}
#endif
/*
 * Initialize the MDNS services
 */
void App_MdnsInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_MDNS_INIT_PARAM_T initParam;
	//int i;
	GSN_MDNS_T *pMdns = &pAppCtx->if0.mdns;
	UINT32 ipV4Addr = pAppCtx->if0.nwifCtx.ipConfig.ipv4.ipAddr;
	memset((INT8*)&initParam, 0, sizeof(initParam));

	initParam.pNwif = &pAppCtx->if0.nwifCtx;
	initParam.ipV4Addr = ipV4Addr ;
	initParam.msgQueueBuffSize = APP_CFG_MDNS_MSG_HDLR_MAX_MSG_IN_MBOX * sizeof(GSN_MDNS_MSG_T);				  
	initParam.msgQueueBuff = MALLOC(initParam.msgQueueBuffSize);
	if(NULL == initParam.msgQueueBuff)
	{
		while(1);
	}
	initParam.noSeparatetsk = FALSE;
	initParam.blockingOn = FALSE;
	initParam.msgPostCb = App_MdnsMsgPostCb;
	initParam.msgPostCbCtx = NULL;
    if(NULL == pMdns)
    {
        AppDbg_Printf("\nmdns ctxt null....EXIT\n");
    }
	GsnMdns_Init(pMdns, &initParam);
#if 0	
	/* create a mdns task*/
	GsnOsal_ThreadCreate(App_MdnsThreadEntry, &appCtx, &appMdnsThread,
		"App Mdns Ctx", APP_MDNS_THREAD_PRI, (UINT8 *)appMdnsThreadStack,
		sizeof(appMdnsThreadStack), GSN_OSAL_THREAD_INITIAL_READY);
#endif   
    App_MdnsInitValues(pAppCtx);
	App_MdnsHNreg(pMdns, ipV4Addr);
	App_MdnsSrvcReg(pMdns, pAppCtx->httpsInfo.httpsFlag);
}

GSN_STATUS  
App_MdnsHNreg(GSN_MDNS_T *pMdns, UINT32          ipAddr)
{
	GSN_STATUS retVal;
	GSN_MDNS_HNREG_PARAM_T param;
	UINT8 domain[]="local";

	memset((INT8 *)&param, 0, sizeof(param));
	param.hostname = (unsigned char*)App_MdnsHostName;
	param.domain   = domain;
	param.ttl   = 10;
	param.scope = GSN_MDNS_SCOPE_IPV4_LOCAL;
	param.autoCorrect  = 1;
	param.conflctDetect = 1; 
	param.ipAddr.addr.v4 = ipAddr;
	param.cb           = NULL;
	param.cbCtx        = NULL;

	retVal = GsnMdns_HostnameRegister(pMdns, &param);

	return retVal;

}

GSN_STATUS  
App_MdnsSrvcReg(GSN_MDNS_T *pMdns, UINT8 httpsFlag)
{  
	GSN_STATUS retVal;
	GSN_MDNS_SRVCREG_PARAM_T pParam;
	UINT8 proto[] = "_tcp";
	UINT8 domain[] = "local";
	pParam.srvceName = (UINT8 *)App_MdnsAppSvcSrv;
	pParam.srvceSubType = NULL;
	pParam.srvceProto = proto;
	pParam.domain = domain;

	/* set the correct port number for http and https */
	if(1 == httpsFlag)
	{
        /* TODO Note: srvcType should be changed to _https when apps provide the functionality */
		UINT8 srvcType[] = "_http";
        pParam.srvceType = srvcType;
		pParam.port = 443;
	}
	else
	{
		UINT8 srvcType[] = "_http";
        pParam.srvceType = srvcType;
		pParam.port = 80;
	}
	
	pParam.ttl = 10;
	pParam.keyVal = keyValAppSvc;
	pParam.scope = GSN_MDNS_SCOPE_IPV4_LOCAL;
	pParam.autoCorrect  = 1;
	pParam.conflctDetect = 1;
	pParam.cb =   AppWebProv_RrRegCb;
	pParam.cbCtx =   NULL;

	retVal = GsnMdns_ServiceRegister(pMdns,&pParam);
#ifdef ADK_PROV_ENABLE
	pParam.srvceName	   = (UINT8 *)App_MdnsProvSrv;
	pParam.keyVal 	   = keyValProv;
	retVal = GsnMdns_ServiceRegister(pMdns,&pParam);
#endif  
#ifdef ADK_OTAFU_ENABLE
	pParam.srvceName	   = (UINT8 *)App_MdnsFwupSrv;
	pParam.keyVal 	   = keyValFwup;
	retVal = GsnMdns_ServiceRegister(pMdns,&pParam);
#endif
    return retVal;
    //return GSN_SUCCESS;
}
GSN_STATUS
App_MdnsAnnounce(GSN_MDNS_T *pMdns)
{
    GSN_MDNS_ANNOUNCE_PARAM_T pParam;
	UINT8 srvcType[] = "_http";
	UINT8 proto[] = "_tcp";
	UINT8 domain[] = "local";
    
    pParam.srvceName = (unsigned char*)App_MdnsAppSvcSrv;
    pParam.domain = domain;
    
//    if(mdnsAnnceParam->type == 2)
  //  {
        pParam.srvceSubType = NULL;
        pParam.srvceType = srvcType;
        pParam.srvceProto = proto;
    //} 
//    else
  //  {
         /*pParam.srvceSubType = NULL;
         pParam.srvceType = NULL;
         pParam.srvceProto = NULL;*/
    //}
    GsnMdns_Announce(pMdns, &pParam);
    return GSN_SUCCESS;
//    return retVal;
}

void App_MdnsDeInit(APP_MAIN_CTX_T *pAppCtx)
{
	/* [TO DO] Deregister HN*/
	/* [TO DO] Deregister Services*/
	/* Deinit Mdns module*/
	GsnMdns_DeInit(&pAppCtx->if0.mdns);
}

VOID
App_MdnsMsgPostCb(VOID *cbCtx, VOID *pMdns)
{
	AppMainCtx_TaskNotify(APP_EVENT_MDNS_EXECUTE, (UINT32) pMdns);	
}

VOID App_serviceDiscoveryCallback(void *pData, const GSN_MDNS_SRVC_INFO_T *srvinfo,
        UINT32 status)
{
	// call back funtion
	//gets called back with service discovery data and signal the semaphore
        PROXY_UPDATER_DATA *ctx;
        int i;
	printf("App_serviceDiscoveryCallback +\r\n");
	ctx = (PROXY_UPDATER_DATA*)pData;
	if(status !=  GSN_MDNS_SD_NO_SRVC_INFO)
	{
		if(ctx != NULL && srvinfo->txtInfo != NULL)
		{
			printf("inside if\r\n");
			if((memcmp(TEXT_RECORD_DATA,srvinfo->txtInfo,tm_strlen(TEXT_RECORD_DATA))) == 0)
			{
				printf("text record matched\r\n");
				printf("AppServiceDiscover_RrRegCb ip address = %d.%d.%d.%d\r\n",srvinfo->ipAddr[0],srvinfo->ipAddr[1],srvinfo->ipAddr[2],srvinfo->ipAddr[3]);

				printf("srvinfo->textRecord = %s\r\n",srvinfo->textRecord);
				// copy the IP address and port
				/*ctx->IPAddress[0] = srvinfo->ipAddress[0];
				ctx->IPAddress[1] = srvinfo->ipAddress[1];
				ctx->IPAddress[2] = srvinfo->ipAddress[2];
				ctx->IPAddress[3] = srvinfo->ipAddress[3];
				ctx->portNo = srvinfo->port;
				*/
				//ctx->IPAddress = *((UINT32 *)srvinfo->ipAddr);
				for(i = 0; i < 4; i++)
					ctx->IPAddress[i] = ( srvinfo->ipAddr >> (i*8) ) & 0xFF;
				ctx->portNo = srvinfo->port;
				serviceDiscovered = TRUE;
			}
		}
	}
	if(status == GSN_MDNS_SD_LAST_SRVC_INFO || serviceDiscovered == TRUE || status == GSN_MDNS_SD_NO_SRVC_INFO)
	{
		// if its the last service then release the semaphore and wait if service is not found
		printf("App_serviceDiscoveryCallback releasing semaphore serviceDiscovered =%d,status = %d\r\n",serviceDiscovered,status);
		GsnOsal_SemRelease( &ctx->appTlsServiceDiscoverWaitSem);
	}

	printf("App_serviceDiscoveryCallback -\r\n");
}

void App_StartServiceDiscovery(PROXY_UPDATER_DATA *proxyUpdater,GSN_MDNS_T *mdns)
{
	// start the service discovery
	printf("App_StartServiceDiscovery +\r\n");
	serviceDiscovered = FALSE;
	GSN_MDNS_SRVCDISCVR_PARAM_T mdnsparams;
	memset(&mdnsparams,0,sizeof(mdnsparams));
	mdnsparams.srvcSubType = NULL;
	mdnsparams.srvcType = (UINT8*)gsn_malloc(30);
	mdnsparams.srvcProto = (UINT8*)gsn_malloc(30);
	mdnsparams.domain = (UINT8*)gsn_malloc(30);
	strcpy((char*)mdnsparams.srvcType,"_http");
	strcpy((char*)mdnsparams.srvcProto,"_tcp");
	strcpy((char*)mdnsparams.domain,"local");
	mdnsparams.cb = App_serviceDiscoveryCallback;
	mdnsparams.cbCtx = proxyUpdater;
	GsnOsal_SemCreate ( &proxyUpdater->appTlsServiceDiscoverWaitSem, 0 );

	while(!serviceDiscovered)
	{
	  GsnMdns_ServiceDiscover(mdns, &mdnsparams);
	  GsnOsal_SemAcquire( &proxyUpdater->appTlsServiceDiscoverWaitSem, GSN_OSAL_WAIT_FOREVER );
	  printf("semaphore released,serviceDiscovered =  %d\r\n",serviceDiscovered);
	 }
	 GsnOsal_SemDelete ( &proxyUpdater->appTlsServiceDiscoverWaitSem );
	 if(mdnsparams.srvcType != NULL)
	 {
		 gsn_free(mdnsparams.srvcType);
		 mdnsparams.srvcType = NULL;
	 }
	 if(mdnsparams.srvcProto != NULL)
	 {
		 gsn_free(mdnsparams.srvcProto);
			 mdnsparams.srvcProto = NULL;
	 }
	 if(mdnsparams.domain != NULL)
	 {
		 gsn_free(mdnsparams.domain);
			 mdnsparams.srvcProto = NULL;
	 }
	  printf("App_StartServiceDiscovery -\r\n");
}
#endif
