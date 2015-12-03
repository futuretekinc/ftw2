/******************************************************************************
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
* $RCSfile: app_sm.c,v $
*
*****************************************************************************/


/*****************************************************************************
  * File Inclusions
  *****************************************************************************/
#include "gsn_includes.h"

#ifdef OS_UVEL
#include "trsocket.h"
#endif

#include "gsn_includes.h"
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
#include "app_debug.h"
#include "config\app_default_cfg.h"
#ifdef GSN_FILE_UPLOAD_API
//#include "gsn_httpd_file_api.h"
#endif
#include "app_rtc_mem.h"
/**
 ******************************************************************************
 * @file app_sm.c
 * @brief GSN Application State machine.
 *    This file contains the application state machine implementation.
 *    The PING application initiate the joining procedure and maintains it.
 *    This application just demonstrate the data path using ping feature.
 ******************************************************************************/

/**
 ******************************************************************************
 * @defgroup AppSm
 *    This group contains the application state machine implementation.
 ******************************************************************************/

/****************************************************************************
  *  Private Variables
  ****************************************************************************/
extern PUBLIC UINT32 App_NetworkServicesStart(APP_MAIN_CTX_T *pAppCtx);
extern PUBLIC GSN_STATUS App_HttpdStop(APP_MAIN_CTX_T *pAppCtx);
extern void App_MdnsDeInit(APP_MAIN_CTX_T *pAppCtx);
extern VOID App_RebootSoc(UINT32 ctx);
extern VOID App_NetworkServicesStop(APP_MAIN_CTX_T *pAppCtx);


/****************************************************************************
  *  Private Functions prototype
  ****************************************************************************/
PRIVATE VOID
AppSm_ConnectSuccessProcess(APP_MAIN_CTX_T *pAppCtx);
#if 0
PRIVATE VOID
AppSm_StaDisconnectSuccessProcess(APP_MAIN_CTX_T *pAppCtx);
#endif
PRIVATE VOID
AppSm_WlanDisassocProcess(APP_MAIN_CTX_T *pAppCtx);
VOID
AppSm_GotoStandby(APP_MAIN_CTX_T *pAppCtx);

/**
 ******************************************************************************
 * @ingroup AppSm
 * @brief Switching On LED.
 *    This Function can be used to Turn ON the LED's.
 * @param ledColor - IN Color of LED.
 ******************************************************************************/
#define GPIO_RED_LED              30
#define GPIO_GREEN_LED            31

/****************************************************************************
  *  Public Functions
  ****************************************************************************/
PUBLIC VOID
AppSm_Init(APP_MAIN_CTX_T *pAppCtx)
{
}

#ifdef ADK_PROV_WPS_ENABLE
#define APP_NCM_CFG_DFLT_WPS_USR_NAME   "WFA-SimpleConfig-Enrollee-1-0"
UINT32 wpsConnDone = FALSE;
UINT8 wpsL2ConInfoStore = FALSE;
GSN_OSAL_SEM_T stWpsAssSemaphore;

VOID
AppSm_WpsManageCredentials(APP_MAIN_CTX_T * pAppCtx)
{
	UINT8 ssid[33];
	INT8 chnl[4];
	UINT8 passphrase[65];
	APP_CLIENT_CONFIG_T *pCliCfg;


	GSN_WDD_WLAN_CFG_T *wlanConfig = GsnWdd_WlanConfigPtrGet(&pAppCtx->if0.wddCtx);
    APP_CONFIG_T * config = &pAppCtx->config;
	memcpy(ssid, wlanConfig->ssid.array, wlanConfig->ssid.length);
	ssid[wlanConfig->ssid.length]= '\0';
	sprintf(chnl, "%u", wlanConfig->channel[0]);
	//AppDbg_Printf("PASSPHRASE length=%d\r\n", wlanConfig->securityCfg.pskConfig.passPhrase.Len);
	memcpy(passphrase, wlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
			wlanConfig->securityCfg.pskConfig.passPhrase.Len);
	passphrase[wlanConfig->securityCfg.pskConfig.passPhrase.Len ]= '\0';

	if ((wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA2_PERSONAL) ||
			 (wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA_PERSONAL))
			{
				AppDbg_Printf("PASSPHRASE=%s\r\n", passphrase);
			}

	if (TRUE == wpsL2ConInfoStore )
	{
		pCliCfg = &config->networkConfig.clientConfig;
		pCliCfg->ssid.length = wlanConfig->ssid.length;

		memset((INT8 *)pCliCfg->ssid.array,0,GSN_WLAN_MAC_SSID_LEN);
		memcpy(pCliCfg->ssid.array, wlanConfig->ssid.array,
				wlanConfig->ssid.length);
		pCliCfg->channel = wlanConfig->channel[0];
		config->networkConfig.networkMode = pAppCtx->config.networkConfig.networkMode;
		{
			if ((wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA2_PERSONAL) ||
				(wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA_PERSONAL))
			{

				pCliCfg->securityType = GSN_WLAN_WPA_PERSONAL;
				pCliCfg->passphrase.Len = strlen((const char *)passphrase);
				memcpy((INT8 *)pCliCfg->passphrase.Passphrase, passphrase, strlen((const char *)passphrase)+1);
				if(wlanConfig->securityCfg.pskConfig.pskValid)
				{
					//pCliCfg->
					//memcpy(pS2wProfile->security.wpa.psk,
									 //  wlanConfig->securityCfg.pskConfig.psk, GSN_WDD_SEC_PMK_LEN);
					//pS2wProfile->security.wpa.pskValid = 1;
				}
			}
			else if(wlanConfig->securityCfg.mode& GSN_WDD_SEC_MODE_WEP)
			{
				pCliCfg->wepKeyConfig.KeyId  = 0;
				pCliCfg->wepKeyConfig.KeyLen = wlanConfig->securityCfg.wepConfig.KeyLen;
				pCliCfg->securityType = GSN_WLAN_WEP;
				memcpy((VOID*)&pCliCfg->wepKeyConfig.Key, wlanConfig->securityCfg.wepConfig.Key,
						   wlanConfig->securityCfg.wepConfig.KeyLen);
			}
			else
			{
				pCliCfg->securityType  = GSN_WLAN_SECURITY_NONE;
			}
		}
		// do we need to change the drive here?
		f_chdrive(0);
		AppConfig_Save(config);
	}
}

PRIVATE VOID
AppSm_WpsAssociateCb(VOID *pCtx, INT32 status)
{
	APP_MAIN_CTX_T * appCtx = (APP_MAIN_CTX_T*) pCtx;
	GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&appCtx->if0.wddCtx);
    //UINT16 capability;

    if (GSN_SUCCESS == status)
    {
        /* return AP credentiials */
        wpsConnDone = TRUE;
    }
	else if(status == GSN_FAILURE/*GSN_WDD_WPS_CONNECT_FAILURE*/)
	 {
		 wpsConnDone = FALSE;
		 wpsL2ConInfoStore=FALSE;// failed to connect
    }
    else if(GSN_WDD_WPS_SESSION_OVERLAP == status || GSN_WDD_SSID_NOT_FOUND == status)
    {
        /* return error */
        wpsConnDone = FALSE;
    }

    GsnOsal_SemRelease(&stWpsAssSemaphore);

}
/**
 ******************************************************************
 * @ingroup TLS WPS Associate
 * @brief TLS wps associate function.
 *    This function associates to the wlan where the wps pbc/pin method
 *    enabled.
 * @param params - IN the app context parameter structure pointer
 * @retval GNS_SUCCESS - operation successful.
 * @retval GSN_FAILURE - operation failure.
 ******************************************************************/
PUBLIC GSN_STATUS
AppSm_WpsAssociate(APP_MAIN_CTX_T *pAppCtx)
{


    GSN_WDD_SECURITY_CONFIG_T *pSecConfig;
    UINT32 connectFlags = 0;
    GSN_STATUS_T retCode;
    UINT8 wpsUserName[] = APP_NCM_CFG_DFLT_WPS_USR_NAME;
    APP_WPS_T *params = &pAppCtx->wpsParams;
    GSN_MAC_SSID_T *ap_ssid = &pAppCtx->wpsapSsid;
    GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&pAppCtx->if0.wddCtx);

    wpsConnDone = FALSE;
	wpsL2ConInfoStore = TRUE;// store the connection info in flash

    /* Get pointer to security config in NW config */
    pSecConfig = &pWlanConfig->securityCfg;

    /* We will wait on this semaphore after issueing the GsnWdd_connect().
    This will be released by wddConnect_cb() */
    GsnOsal_SemCreate(&stWpsAssSemaphore, 0);

    /* Set defaults */
    GsnWdd_WlanConfigDefaultInit(pWlanConfig);
    // do we require this?
    memcpy(pWlanConfig->ssid.array, ap_ssid->array, ap_ssid->length);
    pWlanConfig->ssid.length = ap_ssid->length;

    /* Now initiate wps connection */
    /* Prepare connection request flags */
	connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_MATHOD;

    /* Get the pin */
    memcpy(pSecConfig->wpsConfig.pin, params->pin , sizeof(params->pin));

    /* Get user name */
    pSecConfig->eapConfig.userName.Length = strlen((const char *)wpsUserName);
    memcpy(pSecConfig->eapConfig.userName.Name, wpsUserName,
           strlen((const char *)wpsUserName));

    /*set the channel list*/
    {
    	// make a separate fn to fill channels. see the regulatory domaaun and set it
#if 0
          UINT8 domain;
          AppCfg_Get( APP_CFG_REG_DOMAIN_ID, &domain );
          AppS2w_ChannelFill(&pAppCtx->if0.wddCtx,&pWlanConfig->wlanConfig.channel[0],domain);
#else
		pWlanConfig->channel[0] = 1;
		pWlanConfig->channel[1] = 2;

		pWlanConfig->channel[2] = 3;
		pWlanConfig->channel[3] = 4;
		pWlanConfig->channel[4] = 5;
		pWlanConfig->channel[5] = 6;
		pWlanConfig->channel[6] = 7;
		pWlanConfig->channel[7] = 8;
		pWlanConfig->channel[8] = 9;
		pWlanConfig->channel[9] = 10;
		pWlanConfig->channel[10] = 11;
        pWlanConfig->channel[11] = 0;

		pSecConfig->wpsConfig.pDeviceName = DEFAULT_DEVICE_NAME;
		pSecConfig->wpsConfig.pManufacturer = DEFAULT_DEVICE_MANUFACTURER;
		pSecConfig->wpsConfig.pModelName = DEFAULT_DEVICE_MODEL;
		pSecConfig->wpsConfig.pModelNumber = DEFAULT_DEVICE_MODEL_NUMBER;
		pSecConfig->wpsConfig.pSerialNumber = DEFAULT_DEVICE_SERIAL_NUMBER;
		/*pWlanConfig->securityCfg.wpsConfig.rfBands;*/
		pSecConfig->wpsConfig.pUuid = DEFAULT_DEVICE_UUID;
		pSecConfig->wpsConfig.pFriendlyName = NULL;
		pSecConfig->wpsConfig.pManufacturerUrl = DEFAULT_DEVICE_UUID;
		pSecConfig->wpsConfig.pModelDescription = NULL;
		pSecConfig->wpsConfig.pModelUrl = NULL;
		pSecConfig->wpsConfig.pUpc = NULL;


		if(params->type == APP_WPS_TYPE_PB)
		{
			pSecConfig->wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_PUSHBUTTON;
		}
		if(params->type == APP_WPS_TYPE_PIN)
		{
			memcpy(pSecConfig->wpsConfig.pin, params->pin, sizeof(pSecConfig->wpsConfig.pin));
			pSecConfig->wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_LABEL;
		}
    }

    GsnWdd_WlanConfigSet(&pAppCtx->if0.wddCtx, pWlanConfig);

    /* do L2 connection using WPS */
    retCode = GsnWdd_Connect(&pAppCtx->if0.wddCtx,
                                (GSN_WDD_CONNECT_FLAG_T)connectFlags, pWlanConfig, NULL,
                                AppSm_WpsAssociateCb, pAppCtx);
    if(retCode != GSN_OPERATION_IN_PROGRESS)
    {
        /* it should be failuer */
    	AppSm_WpsAssociateCb(NULL, GSN_FAILURE);
    }

    /* wait for the call back to be get called */
    GsnOsal_SemAcquire( &stWpsAssSemaphore, GSN_OSAL_WAIT_FOREVER);

    if(wpsConnDone == TRUE)
    {

    	AppSm_WpsManageCredentials(pAppCtx);
    	 retCode = GSN_SUCCESS;
    }
    else
    {
        retCode = GSN_FAILURE;
    }
    GsnOsal_SemDelete(&stWpsAssSemaphore);
    return retCode;
}

VOID
App_InterfaceStop(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

VOID
App_IfReinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

#endif

GSN_STATUS App_MacAddrSet(UINT8* macAddr)
  {
	GSN_STATUS status;
     status = GsnWdd_PhyAddrSet(&appCtx.if0.wddCtx, (INT8*)macAddr,TRUE);
     if(status!= GSN_SUCCESS)
           return GSN_FAILURE;
     GsnNwif_UpdatePhyAddr(&appCtx.if0.nwifCtx);
	   return GSN_SUCCESS;
  }
VOID AppWps_DisconnectCb(VOID *pCtx, GSN_STATUS status )
{
    UINT32 msg = APP_EVENT_STA_WPS_IN_PROGRESS;

    /* Notify APP */
    AppMainCtx_TaskNotify(msg,0);
}
#endif /*ADK_PROV_WPS_ENABLE*/
/**
 ******************************************************************************
 * @ingroup AppSm
 * @brief App SM message processing.
 *    This function processes the main task events received by main task on its
 *    message queue.
 * @param pAppCtx - IN Pointer to the Application context.
 * @param msgId - IN Id of the message.
 * @note
 *    The message coming in to this function is one of the types defined in
 *    gsn_notifications.h::GSN_NOTIFICATIONS_T.
 *****************************************************************************/
UINT32 initDone = 0;

PUBLIC GSN_STATUS
AppSm_MsgProcess(APP_MAIN_CTX_T *pAppCtx, APP_MAINTASK_MSG_T msg )
{
    GSN_STATUS retCode = GSN_FAILURE;
    GSN_STATUS status;
	UINT8 macAddr[APP_MAC_ADDR_SIZE] = {0};
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	
    switch ( msg.msgId )
    {
    	case APP_EVENT_NW_START_NCM:
			App_NcmStart(pAppCtx, &pAppCtx->if0);
			break;
        case APP_EVENT_NW_CONNECT_DONE:/*GSN_NCM_CTX_L3CONNECTED*/
            /**< Call APP SM to process connection status */
            if(GSN_WIF_SYS_BOOT_NORMAL_BOOT == GSN_BOOT_REASON_GET())
			{
				nx_arp_table_set(&pAppCtx->if0.nwifCtx.ipHndl, &pAppRtcLtchInfo->arpTablebuf[0], 
								 pAppRtcLtchInfo->arpRecCount);
			}
            AppSm_ConnectSuccessProcess(pAppCtx);
			GsnGpio_OutIndvidualSet(LED_GPIO_8);
#ifdef APP_OPT_PS_IN_PSPOLL            
            GsnOsal_SemRelease(&pAppCtx->synSyncSem);
			initDone = 1;
#endif
            retCode = GSN_SUCCESS;
            break;
        case APP_EVENT_NW_DISCONNECT_DONE:/*GSN_NCM_CTX_L3DISCONNECTED*/
			GsnGpio_OutClear(LED_GPIO_8);   // gpio become high
			AppSm_WlanDisassocProcess(pAppCtx);
            retCode = GSN_SUCCESS;
            break;
		case APP_EVENT_NW_CONNECT_FAILED:
			AppDbg_Printf("Client network connection failed. Restart the board\r\n");
#ifndef APP_OPT_PS_IN_PSPOLL			
			pAppCtx->config.networkConfig.networkMode = GSN_LIMITED_AP;
			AppConfig_Save(&(pAppCtx->config));
			App_RebootSoc(0);
#endif			
			break;
        case APP_EVENT_STA_DISCONNECT_DONE:
             /**< Call APP SM to process client disconnection status */
            //AppSm_StaDisconnectSuccessProcess(pAppCtx);
            retCode = GSN_SUCCESS;
            break;
		case APP_EVENT_NCM_EXECUTE:
			GsnNcm_Execute((GSN_NCM_CTX_T*)msg.msgInfo);
			break;
		case APP_EVENT_MDNS_EXECUTE:
			GsnMdns_Execute((GSN_MDNS_T *)msg.msgInfo);
			break;
		case APP_EVENT_STAT_OUT:
			App_StatsPrint();
			break;
		case APP_EVENT_STANDBY:
			/*AppSm_GotoStandby(pAppCtx);*/
			break;
		case APP_EVENT_DAB_INDIACTION:
			AppSm_GotoStandby(pAppCtx);
			break;
		case APP_EVENT_FWUP_SUCCESS:
            GsnTaskSleep(100);
        	GsnSys_Reset(GSN_RESET_REASON_APP_FWUP);
        	break;
#ifdef ADK_PROV_WPS_ENABLE
		case APP_EVENT_STA_WPS_INITIATE:
		{
	    	status = GsnWdd_Disconnect(&pAppCtx->if0.wddCtx,0,
	                AppWps_DisconnectCb, pAppCtx);
	    	AppDbg_Printf("APP_EVENT_STA_WPS_INITIATE\r\n");
	        /* If the operation is complete, then notify APP
	         */
	        if (GSN_OPERATION_IN_PROGRESS != status)
	        {
	        	AppWps_DisconnectCb(pAppCtx, status);
	        }
	        break;
		}
		case APP_EVENT_STA_WPS_IN_PROGRESS:
		{
	        // stop the network services
			App_NetworkServicesStop(pAppCtx);

			if(pAppCtx->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_AP)
			{
				App_InterfaceStop(pAppCtx, &pAppCtx->if0);
				pAppCtx->config.networkConfig.networkMode = GSN_INFRA_CLIENT;
				pAppCtx->if0.macIfType = GSN_WIF_WLAN_NW_TYPE_STA;
				pAppCtx->if0.macIfNum= APP_DEV_INDX_0;
				App_IfReinit(pAppCtx, &pAppCtx->if0);
				memcpy(macAddr,&pAppCtx->config.networkConfig.macAddr, GSN_WLAN_MAC_ADDR_LEN);
				App_MacAddrSet(macAddr);
				GsnWdd_Ioctl(&pAppCtx->if0.wddCtx,GSN_WDD_IOCTL_RX_MODE_COUNTER_CLEAR, NULL);
				GsnWdd_Ioctl(&pAppCtx->if0.wddCtx, GSN_WDD_IOCTL_RX_ACTIVE_MODE_ON, NULL);
			}
			GsnSq_TaskMonitorStop(APP_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorDeregister(APP_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorRegister(APP_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK_WPS);
			GsnSq_TaskMonitorStart(APP_SQ_MAIN_TASK_ID,0);
			retCode = AppSm_WpsAssociate(pAppCtx);
			f_chdrive(1);
			if(retCode == GSN_FAILURE)
				AppDbg_Printf("WPS failed\r\n");
		  	if(retCode == GSN_SUCCESS || retCode == GSN_FAILURE)
		  	{
				GsnSys_Reset((GSN_RESET_REASON_T)GSN_WIF_SYS_BOOT_SW_RESET_BOOT);
			}
			GsnSq_TaskMonitorStop(APP_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorDeregister(APP_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorRegister(APP_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK);
			GsnSq_TaskMonitorStart(APP_SQ_MAIN_TASK_ID,0);
			break;
		}
#endif // ADK_PROV_WPS_ENABLE
		default:
			break;
    }
    return retCode;
}


/****************************************************************************
  *  Private Functions
  ****************************************************************************/

PRIVATE VOID
AppSm_ConnectSuccessProcess(APP_MAIN_CTX_T *pAppCtx)
{
	UINT32 wlanNwType;
	wlanNwType = pAppCtx->if0.macIfType;

	if(GSN_WIF_WLAN_NW_TYPE_AP ==  wlanNwType)
	{
		GSN_DHCP_SRVR_CFG_T dhcpSrvrCfg = {0};
		GSN_DNS_INIT_PARAM_T dnsInitParams = {0};

		APP_AP_CONFIG_T *pApCfg = &pAppCtx->config.networkConfig.apConfig;

		/* start the dhcp server   */
		dhcpSrvrCfg.serverIpAddr = ntohl(pApCfg->ipAddress);
		dhcpSrvrCfg.subnetMask = ntohl(pApCfg->subnetmask);
		dhcpSrvrCfg.gateway = ntohl(pApCfg->gateway);
		dhcpSrvrCfg.startIpAddr = ntohl(pApCfg->dhcpAddressStart);
		dhcpSrvrCfg.pNwif = &pAppCtx->if0.nwifCtx;
		dhcpSrvrCfg.dns1 = dhcpSrvrCfg.dns2 = ntohl(pApCfg->ipAddress);
		dhcpSrvrCfg.numOfClients = pApCfg->dhcpNumAddresses;
		dhcpSrvrCfg.leaseTime = APP_DFLT_AP_DHCPSRVR_LEASE_TIME;
		GsnDhcpSrvr_Start(&pAppCtx->if0.dhcpSrvrHndl, &dhcpSrvrCfg);

		/* Start the DNS server if it is enabled */
		if (pApCfg->dnsServerEnable)
		{
            /* start the dhcp and dns server   */
            dnsInitParams.serverIpAddr = ntohl(pApCfg->ipAddress);
            dnsInitParams.flags = IP_VERSION_V4;

            GsnDnsSrvr_Start(&pAppCtx->if0.dnsServerHndl, pApCfg->dnsDomainName, &dnsInitParams);
		}
	}
	else
	{
#ifdef APP_OPT_PS_IN_PSPOLL
	   /* bss connect success case just configure the radio and mcast..*/
		GsnWdd_DABindEnable(&pAppCtx->if0.wddCtx, 1);
#endif
	}
	/*In both AP and client case, start the web server*/
	App_NetworkServicesStart(pAppCtx);

}

#if 0
PRIVATE VOID
AppSm_StaDisconnectSuccessProcess(APP_MAIN_CTX_T *pAppCtx)
{
    /* Remove the http entry */
    //GsnDhcpSrvr_ClientDelete(&pAppSm->dhcpSrvr,disconStaMac);
}
#endif

PRIVATE VOID
AppSm_WlanDisassocProcess(APP_MAIN_CTX_T *pAppCtx)
{
	/* STOP the HTTP server, MDNS deinit*/
	App_HttpdStop(pAppCtx);
#ifdef APP_MDNS_ENABLE
	App_MdnsDeInit(pAppCtx);
#endif
}

PRIVATE VOID
AppSm_StoreStdbyData(APP_MAIN_CTX_T *pAppCtx, GSN_SYS_CTL_STDBY_RESP_T * pStdbyResp)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	APP_CONFIG_T *pAppCfg = AppConfig_RTCPtrGet();
	memcpy(pAppCfg, &pAppCtx->config, sizeof(APP_CONFIG_T));
	/*Store WLAN data */
	pAppRtcSecMemInfo->macStdbyCtxLen = pStdbyResp->totalSize;
	memcpy((INT8 *)pAppRtcSecMemInfo->macStdbyCtx, (const INT8 *)pStdbyResp->ctxData,
			pStdbyResp->totalSize);

	AppDbg_Printf("Issue Standby %x %x %x %x\r\n", pStdbyResp->totalSize, pStdbyResp->ctxData[0],
															pStdbyResp->ctxData[1], pStdbyResp->ctxData[2]);
	/*Store IP Configuration*/
	GsnNwIf_IpConfigGet(&pAppCtx->if0.nwifCtx, &pAppRtcLtchInfo->ipConfig);
	nx_arp_table_get(&pAppCtx->if0.nwifCtx.ipHndl, 
								(VOID *)&pAppRtcLtchInfo->arpTablebuf[0], 
								sizeof(pAppRtcLtchInfo->arpTablebuf), 
								&pAppRtcLtchInfo->arpRecCount);

    GsnNwIf_dhcpClientCreateRecord(&pAppCtx->if0.nwifCtx,&pAppRtcSecMemInfo->dhcpClientRecord);
}

VOID
AppSm_GotoStandby(APP_MAIN_CTX_T *pAppCtx)
{
	ULONG64 duration, nextWakeup, currTime;
	GN_SYS_CTL_STDBY_REQ_PARAM_T stdbyReqParam;
	INT8 *pStdbyRespBuf;
	UINT32 stdbyRespBufLen;
	GSN_SYS_CTL_STDBY_RESP_T *pStdbyResp;
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	
	pStdbyRespBuf = (INT8 *)MALLOC(MAX_WLAN_STANDBY_DATA_SIZE);
	if(NULL == pStdbyRespBuf)
	{
		while(1);
	}
	memset((INT8 *)&stdbyReqParam, 0, sizeof(stdbyReqParam));
	stdbyRespBufLen = MAX_WLAN_STANDBY_DATA_SIZE;

	stdbyReqParam.wakeUpForWlanEvents = 0;
	stdbyReqParam.restoreIfBitMap = 0x1;
	stdbyReqParam.waitPeriod[0] = 0xFFFFFFFF;

	GsnSysCtl_StandByReq(&pAppCtx->sysCtlCtx, &stdbyReqParam, pStdbyRespBuf, stdbyRespBufLen);

	/*Store Standby data */
	AppSm_StoreStdbyData(pAppCtx, (GSN_SYS_CTL_STDBY_RESP_T *)pStdbyRespBuf);

	pStdbyResp = (GSN_SYS_CTL_STDBY_RESP_T *)pStdbyRespBuf;

	/*Configure Standby and WakeUp clock sources*/
    RTC_SM_SB_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_HS_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_HS_RC_SET(RTC);

    /*Issue the stby request
     */

	nextWakeup = pStdbyResp->nextWakeUp - GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(10);
	currTime = GsnSoftTmr_CurrentSystemTime();
	if(nextWakeup <= currTime)
	{
		duration = GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(1);
	}
	else
	{
	  duration = nextWakeup - currTime;
	}
	
    
	/*duration = GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(1000 * 2);*/
	/* Store standby duration. Useful for dhcp lease time */
    pAppRtcSecMemInfo->sleepTime = SYSTIME_TO_MSEC(duration);

	FREE(pStdbyRespBuf);
	{
	    /*Configure RTC SRAM Bank*/
		RTC_SRAM_ISO_ENABLE_SET(RTC);
		SX_EN_ULDO_SET(RTC);
		RTC_SX_SWT2LDO_SET(RTC,1);
	}   
    GsnPwrMgmt_EnterStby(duration);
    {
       volatile UINT32 loop=1;
       while(loop);
    }
}


VOID
AppSm_ReStoreStdbyData(APP_MAIN_CTX_T *pAppCtx)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();

	APP_CLIENT_CONFIG_T *pCliCfg;
	pCliCfg = &pAppCtx->config.networkConfig.clientConfig;

	/*Restore IP Configuration*/
	pCliCfg->ipAddress = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.ipAddr);
	pCliCfg->subnetmask = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.subnetMask);
	pCliCfg->gateway = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr);
	pCliCfg->dnsServer = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp);
	pCliCfg->dhcpFlag = FALSE;
}
