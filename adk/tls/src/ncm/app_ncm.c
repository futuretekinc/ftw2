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
 * $RCSfile: app_ncm.c,v $
 *
 *****************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "gsn_ncm.h"
#include "app_events.h"
#include "config\app_resource_config.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "battery/app_batt_chk.h"
#include "main\app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_debug.h"
#include "app_default_cfg.h" 
#include "app_rtc_mem.h"

#ifdef __GSNFILENUM__
#undef __GSNFILENUM__
#define __GSNFILENUM__ APP_NCM_C
#endif

#ifdef __GSNMODULENUM__
#undef __GSNMODULENUM__
#define __GSNMODULENUM__ APP_MODULE
#endif

#define CPU_WAIT_PERIOD  1
#define MAX_SCAN_CH_COUNT 10
#define MAX_L3_CONNECT_COUNT 3

/* NCM*/
UINT8 ncmMsgQueueBuf[APP_CFG_NCM_MSG_HDLR_MAX_MSG_IN_MBOX * sizeof(GSN_NCM_MSG_T)];

PRIVATE VOID
AppNcm_NcmNotifCb(VOID *cbCtx, VOID* pNcm, GSN_NCM_NOTIF_ID_T notifId);

PRIVATE VOID
AppNcm_NcmExecuteCb(VOID *cbCtx, VOID* pNcm);

/*****************************************************************************
 *  Public Functions
 *****************************************************************************/
PUBLIC VOID
AppNcm_Init(APP_MAIN_CTX_T *pAppCtx)
{   
	GSN_NCM_INIT_PARAM_T ncmInitParam;
	  
	ncmInitParam.pNwif = &pAppCtx->if0.nwifCtx;
	ncmInitParam.pWdd = &pAppCtx->if0.wddCtx;

	ncmInitParam.msgQueueBuff = ( UINT8* )ncmMsgQueueBuf;
	ncmInitParam.msgQueueBuffSize = sizeof(ncmMsgQueueBuf);
	
	ncmInitParam.execMsgPostCb = AppNcm_NcmExecuteCb;	 
	ncmInitParam.execMsgPostCbCtx = NULL;

	ncmInitParam.notifCb = AppNcm_NcmNotifCb;
	ncmInitParam.notifCbCtx = NULL;
	
	GsnNcm_Init(&pAppCtx->if0.ncmCtx, &ncmInitParam);
}

PRIVATE VOID 
AppNcm_UserApCfgGet(GSN_NCM_CONFIG_T* pNcmCfg, APP_CONFIG_T *pAppCfg)
{
	AppDbg_Printf("**********\r\nAPP NCM started in USER-AP mode\r\n**********\r\n");

	APP_AP_CONFIG_T *pApCfg = &pAppCfg->networkConfig.apConfig;
	
	/* NCM WLAN config set*/
	GSN_WDD_SSID_CPY(&pNcmCfg->wlanCfg.ssid,&pApCfg->ssid);
	
	pNcmCfg->wlanCfg.channel[0] = pApCfg->channel;
	pNcmCfg->wlanCfg.channel[1] = 0;
	pNcmCfg->regDomain = GSN_NCM_REG_DOMAIN_FCC;
	pNcmCfg->inactivityTimeoutInSec = NCM_DFLT_INACTIVITY_TMEOUT_VALUE;
	pNcmCfg->groupKeyUpdateTime= NCM_DFLT_GRP_KEY_UPDATE_INTERVAL;
	pNcmCfg->wlanCfg.apSpecificCfg.dtimPeriod= NCM_DFLT_DTIMPERIOD_VALUE;
	
	if (pApCfg->securityType == GSN_WLAN_WPA_PERSONAL)
	{
		pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_WPA2_PERSONAL;
	}
	else if (pApCfg->securityType == GSN_WLAN_WEP)
	{
		// TODO - WEP support needs to be added. As of now fallback to no security
		pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
		//pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_WEP;
	}
	else
	{
		pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
	}
	
	pNcmCfg->wlanCfg.securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_AES;
	pNcmCfg->wlanCfg.securityCfg.pskConfig.pskValid = 0;
	pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Len = strlen(DEFAULT_AP_PASSPHRASE);
	memcpy( pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Passphrase, DEFAULT_AP_PASSPHRASE,
	pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Len );
	
	pNcmCfg->ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
	pNcmCfg->ipConfig.ipv4.staticIp = TRUE;
	pNcmCfg->ipConfig.ipv4.ipAddr = ntohl(pApCfg->ipAddress);
	pNcmCfg->ipConfig.ipv4.subnetMask = ntohl(pApCfg->subnetmask);
	pNcmCfg->ipConfig.ipv4.gatewayIpAddr = ntohl(pApCfg->gateway);
}

#ifdef ADK_PROV_GROUP_SECURE
PRIVATE VOID 
AppNcm_ProvApCfgGet(GSN_NCM_CONFIG_T* pNcmCfg, APP_CONFIG_T *pAppCfg)
{
	AppDbg_Printf("**********\r\nAPP NCM started in PROV-AP mode\r\n**********\r\n");

	APP_AP_CONFIG_T *pApCfg = &pAppCfg->networkConfig.apConfig;
    
	/* NCM WLAN config set for PROV-AP mode */
	GSN_MAC_SSID_T prov_ssid;
	prov_ssid.length = sprintf((void*)prov_ssid.array,
				DEFAULT_GROUP_PROV_SSID"%02x%02x%02x",
				pAppCfg->networkConfig.macAddr[3],
				pAppCfg->networkConfig.macAddr[4],
				pAppCfg->networkConfig.macAddr[5]);
	GSN_WDD_SSID_CPY(&pNcmCfg->wlanCfg.ssid,&prov_ssid);

	pNcmCfg->wlanCfg.channel[0] = pApCfg->channel;
	pNcmCfg->wlanCfg.channel[1] = 0;
	pNcmCfg->regDomain = GSN_NCM_REG_DOMAIN_FCC;

	/* No security in prov-ap mode */	
	pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
	
	pNcmCfg->wlanCfg.securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_AES;
	pNcmCfg->wlanCfg.securityCfg.pskConfig.pskValid = 0;
	pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Len = strlen(DEFAULT_AP_PASSPHRASE);
	memcpy( pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Passphrase, DEFAULT_AP_PASSPHRASE,
	pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Len );
	
	pNcmCfg->ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
	pNcmCfg->ipConfig.ipv4.staticIp = TRUE;
	pNcmCfg->ipConfig.ipv4.ipAddr = ntohl(pApCfg->ipAddress);
	pNcmCfg->ipConfig.ipv4.subnetMask = ntohl(pApCfg->subnetmask);
	pNcmCfg->ipConfig.ipv4.gatewayIpAddr = ntohl(pApCfg->gateway);
}
#endif

PUBLIC GSN_STATUS
App_NcmStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T * pIfInfo)
{
	GSN_NCM_CONFIG_T* pNcmCfg = &pIfInfo->ncmCtx.config;
	//UINT8 *pAddr;
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	APP_CONFIG_T *pAppCfg = &pAppCtx->config;

	memset(pNcmCfg, 0, sizeof(GSN_NCM_CONFIG_T));
	if(GSN_WIF_WLAN_NW_TYPE_STA == pIfInfo->macIfType)
	{
		APP_CLIENT_CONFIG_T *pCliCfg = &pAppCfg->networkConfig.clientConfig;
		/* NCM WLAN config set*/
		GSN_WDD_SSID_CPY(&pNcmCfg->wlanCfg.ssid,&pCliCfg->ssid);

		pNcmCfg->wlanCfg.channel[0]	= pCliCfg->channel;
		pNcmCfg->wlanCfg.channel[1] = 0;

		if (pCliCfg->securityType == GSN_WLAN_WPA_PERSONAL)
		{
            pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_ANY;
		    if (pCliCfg->passphrase.Len)
		    {
                pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Len =
                            pCliCfg->passphrase.Len;
                memcpy(pNcmCfg->wlanCfg.securityCfg.pskConfig.passPhrase.Passphrase,
                        pCliCfg->passphrase.Passphrase,
                        pCliCfg->passphrase.Len);
		    }
		    // TODO - compute PSK so that next time we can use it directly
            pNcmCfg->wlanCfg.securityCfg.pskConfig.pskValid = 0;
            pNcmCfg->wlanCfg.securityCfg.pskConfig.wpaAlgo =
                    GSN_WDD_WPA_ALGO_MIXED;
		}
		else if (pCliCfg->securityType == GSN_WLAN_WEP)
		{
            pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_WEP;
		    if (pCliCfg->wepKeyConfig.KeyLen)
		    {
                pNcmCfg->wlanCfg.securityCfg.wepConfig.KeyLen =
                        pCliCfg->wepKeyConfig.KeyLen;
                pNcmCfg->wlanCfg.securityCfg.wepConfig.KeyId =
                        pCliCfg->wepKeyConfig.KeyId - 1;
                memcpy(pNcmCfg->wlanCfg.securityCfg.wepConfig.Key,
                        pCliCfg->wepKeyConfig.Key, pCliCfg->wepKeyConfig.KeyLen);
                if (pCliCfg->wepAuthType == GSN_MAC_AUTH_SHARED)
                        pNcmCfg->wlanCfg.securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_SHARED;
                else
                        pNcmCfg->wlanCfg.securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_OPEN;
		    }
		}
		else if (pCliCfg->securityType == GSN_WLAN_WPA_ENTERPRISE)
		{
		    // NOTE: This is NOT supported. So setting to "No Security"
            pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
		}
		else
		{
            pNcmCfg->wlanCfg.securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
		}
		pNcmCfg->regDomain = GSN_NCM_REG_DOMAIN_FCC;

		/*NCM IP config*/
		pNcmCfg->ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
		pNcmCfg->ipConfig.ipv4.staticIp = !pCliCfg->dhcpFlag;
		if(pNcmCfg->ipConfig.ipv4.staticIp == 1)
		{
			pNcmCfg->ipConfig.ipv4.ipAddr = ntohl(pCliCfg->ipAddress);
			pNcmCfg->ipConfig.ipv4.subnetMask = ntohl(pCliCfg->subnetmask);
			pNcmCfg->ipConfig.ipv4.gatewayIpAddr = ntohl(pCliCfg->gateway);
			pNcmCfg->ipConfig.ipv4.dnsPriSrvrIp = ntohl(pCliCfg->dnsServer);
			pNcmCfg->ipConfig.ipv4.dnsSecSrvrIp = ntohl(pCliCfg->dnsServer);
		}
		AppDbg_Printf("APP NCM ipaddr = %x\r\n", pNcmCfg->ipConfig.ipv4.ipAddr);
		pNcmCfg->dhcpV4Cfg.dhcpMaxRetryCnt = DEFAULT_CLI_DHCP_MAX_RETRYCNT;
		pNcmCfg->dhcpV4Cfg.sysQualTskID = APP_CFG_SQ_DHCPV4_TASK_ID;
		pNcmCfg->dhcpV4Cfg.sysQualTicks = APP_CFG_SQ_TICKS_FOR_DHCPV4_TASK;
		pNcmCfg->dhcpV4Cfg.pDhcpCliRecord = &pAppRtcSecMemInfo->dhcpClientRecord;
		pNcmCfg->dhcpV4Cfg.timeElapsed = pAppRtcSecMemInfo->sleepTime/10;
		pAppRtcSecMemInfo->sleepTime = 0;
		/*NCM retry config*/	
		pNcmCfg->retryPeriodConfig.scanKnownChRetryIntrvl = 0;
		pNcmCfg->retryPeriodConfig.scanSpecChRetryIntrvl = 0;
		pNcmCfg->retryPeriodConfig.scanAllChRetryIntrvl = 0;
		pNcmCfg->retryPeriodConfig.cpuWaitPeriod = CPU_WAIT_PERIOD;
		
		pNcmCfg->retryCountsConfig.maxScanKnownChCnt = 0;
		pNcmCfg->retryCountsConfig.maxScanSpecChCnt = 0;
		pNcmCfg->retryCountsConfig.maxScanAllChCnt = MAX_SCAN_CH_COUNT;
		pNcmCfg->retryCountsConfig.maxL3ConnectCnt = MAX_L3_CONNECT_COUNT;
		
		/*Set Sync Loss threshold*/
		
		GsnWdd_BeaconMissThresholdSet(&pAppCtx->if0.wddCtx, 0,100);
	}	
	else if(GSN_WIF_WLAN_NW_TYPE_AP == pIfInfo->macIfType)
	{
		if(GSN_PROV_AP == pAppCfg->networkConfig.groupProvMode)
		{
			#ifdef ADK_PROV_GROUP_SECURE
				AppNcm_ProvApCfgGet(pNcmCfg, pAppCfg);
			#else
				AppNcm_UserApCfgGet(pNcmCfg, pAppCfg);
			#endif
		}
		else
		{
			AppNcm_UserApCfgGet(pNcmCfg, pAppCfg);
		}
		
		/*AP mode connect needs BSSID*/
		memcpy((INT8 *)pNcmCfg->wlanCfg.bssid.array, pAppCfg->networkConfig.macAddr, 6);
	}
	/* start NCM*/
	return GsnNcm_Start(&pAppCtx->if0.ncmCtx, AppNcm_NcmNotifCb, pAppCtx);
}

PRIVATE VOID
AppNcm_NcmNotifCb(VOID *cbCtx, VOID* pNcm, GSN_NCM_NOTIF_ID_T notifId)
{
	APP_MAIN_CTX_T *pAppCtx = cbCtx;
	INT32 msgId;
	
	switch(notifId)
	{
		case GSN_NCM_NOTIF_ID_L2_CONNECTED:{msgId = APP_EVENT_INVALID ;break;}
		case GSN_NCM_NOTIF_ID_L2_DISCONNECTED:
		{
			msgId = APP_EVENT_INVALID ;
			//if (GSN_WIF_WLAN_NW_TYPE_AP == pAppCtx->if0.macIfType)
			{
				if(pAppCtx->nwConnected )
				{
					pAppCtx->nwConnected  = FALSE;
					msgId = APP_EVENT_NW_DISCONNECT_DONE ;
				}
			}
			break;
		}
		case GSN_NCM_NOTIF_ID_L3_CONNECTED:
		{
			pAppCtx->nwConnected = TRUE;
			msgId = APP_EVENT_NW_CONNECT_DONE ;			
		}
		break;
		case GSN_NCM_NOTIF_ID_L3_DISCONNECTED:
		{
			msgId = APP_EVENT_INVALID ;
			if(pAppCtx->nwConnected )
			{
				pAppCtx->nwConnected  = FALSE;
				msgId = APP_EVENT_NW_DISCONNECT_DONE ;
			}
			break;
		}
		case GSN_NCM_NOTIF_ID_L2_CONNECT_FAIL:
		{
			//msgId = APP_EVENT_INVALID;
			msgId = APP_EVENT_NW_CONNECT_FAILED; 
			break;
		}
	}
	if(APP_EVENT_INVALID != msgId)
	{
		//AppDbg_Printf("*****[APP] NcmNotifCb: mainTaskNotify event = %d\r\n", msgId);
		AppMainCtx_TaskNotify(msgId, 0);
	}
}

PRIVATE VOID
AppNcm_NcmExecuteCb(VOID *cbCtx, VOID* pNcm)
{	
	AppMainCtx_TaskNotify(APP_EVENT_NCM_EXECUTE, (UINT32) pNcm);	
}


