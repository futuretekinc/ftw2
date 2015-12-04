#include "gsn_types.h"
#include "gsn_includes.h"
#include "gsn_error.h"
#include "app_defines_builder.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_hal_specific.h"
#include "hal/s2w.h"
#include "parser/s2w_process.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "app_rtc_mem.h"
#include "config/app_resource_config.h"
#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "main/gsn_br_flashldr.h"
#include "ftw_config.h"
#include "web_prov\s2w_web_prov.h"
#include "app_rtc_mem.h"
#include "hal/s2w_net.h"
#include "modules/pwr_mgmt/gsn_pwr_mgmt.h"
#include "ext_app/app_ext_flash.h"
#include "parser/s2w_command.h"

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern FTW_LINK_STATE_T s2wLinkState ;
extern FTW_WLANINFO_T current_wlan_info;
extern UINT8 L3ConnectStatus;
extern UINT32 S2wL3Wait;

extern GSN_OSAL_SEM_T s2wL2L3ConnectSemaphore;
/* Semaphore to wait for scan completion
*/

GSN_OSAL_SEM_T stScanSemaphore;

/* Semaphore to wait for disassociation completion
*/
PRIVATE GSN_OSAL_SEM_T stDisassocSemaphore;



void    AppS2wHal_netInit(void)
{
    GsnOsal_SemCreate  ( &stScanSemaphore, 0 );

    GsnOsal_SemCreate  ( &s2wL2L3ConnectSemaphore, 0 );
    
    GsnOsal_SemCreate  ( &stDisassocSemaphore, 0 );    
    
}

VOID 
GratiousArpHandler(NX_IP *ip_ptr,NX_PACKET *packet_ptr)
{
  	nx_packet_release(packet_ptr);
  	nx_dhcp_decline(&s2wappMainTaskCtxt->if0.nwifCtx.dhcpCliHndl);
  	AppMainCtx_TaskNotify(APP_EVENT_DHCPv4_IP_CONFLICT);
}

VOID FTE_NET_wlanRespTmrCB( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle )
{
	GSN_ASSERT(FALSE);
}


PUBLIC UINT8
AppS2wHal_NwContextRestore()
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	//APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	GSN_NWIF_DHCP_PARAMS_T	dhcpParams;
	GSN_NWIF_IP_CONFIG_T ipConfig;
    GSN_WDD_WLAN_CFG_T *pWddConf;
    GSN_STATUS retVal;
    
	if(FALSE == GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx))
	{
        return FTW_FAILURE;
	}
	/* Set L2 Configuration */
	pWddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
	//memset(&WddConf,0,sizeof(GSN_WDD_WLAN_CFG_T));
	s2wappMainTaskCtxt->if0.wddCtx.assocStatus = pAppRtcLtchInfo->AssocStatus;
	s2wLinkState = (FTW_LINK_STATE_T)s2wappMainTaskCtxt->if0.wddCtx.assocStatus;
	memcpy(&pWddConf->bssid, &pAppRtcLtchInfo->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
	memcpy(&current_wlan_info.bssid, &pWddConf->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
	current_wlan_info.validBssid = TRUE;
	memcpy(&pWddConf->ssid, &pAppRtcLtchInfo->ssid, sizeof(GSN_WLAN_MAC_SSID_T));
	pWddConf->securityCfg.mode = pAppRtcLtchInfo->wsec;
    pWddConf->securityCfg.wepConfig.authType = pAppRtcLtchInfo->authType;
	pWddConf->channel[0] = pAppRtcLtchInfo->channel;
    current_wlan_info.mode = pAppRtcLtchInfo->wmode;
	current_wlan_info.authMode = pWddConf->securityCfg.mode;
	current_wlan_info.channel = pWddConf->channel[0];
	memcpy(current_wlan_info.ssid, pWddConf->ssid.array, pWddConf->ssid.length);
	current_wlan_info.ssidLen = pWddConf->ssid.length;
	//GsnWdd_WlanConfigSet(&s2wappMainTaskCtxt->if0.wddCtx, &WddConf);
    
	/* Set IP config - read NW parameters from RTC
    */
	ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
	ipConfig.ipv4.staticIp = pAppRtcLtchInfo->ipConfig.ipv4.staticIp;
    
	ipConfig.ipv4.ipAddr = pAppRtcLtchInfo->ipConfig.ipv4.ipAddr;
	ipConfig.ipv4.subnetMask = pAppRtcLtchInfo->ipConfig.ipv4.subnetMask;
	ipConfig.ipv4.gatewayIpAddr = pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr;
    
    s2wappMainTaskCtxt->ipaddr = pAppRtcLtchInfo->ipConfig.ipv4.ipAddr;
    s2wappMainTaskCtxt->subnetMask =  pAppRtcLtchInfo->ipConfig.ipv4.subnetMask;
    
	ipConfig.ipv4.dnsPriSrvrIp = pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp;
	ipConfig.ipv4.dnsSecSrvrIp = pAppRtcLtchInfo->ipConfig.ipv4.dnsSecSrvrIp;
	ipConfig.ipv4.dhcpLeaseExpireTime = pAppRtcLtchInfo->ipConfig.ipv4.dhcpLeaseExpireTime;
    memcpy(ipConfig.ipv4.hostName,pAppRtcLtchInfo->hostName,GSN_NWIF_HOST_NAME_MAX_LEN+1);
    
	memset(&dhcpParams,0,sizeof(dhcpParams));
	dhcpParams.dhcpMaxRetryCnt = FTW_DHCP_MAX_RETRY_COUNT;
	s2wappMainTaskCtxt->if0.nwifCtx.notifyCb = DHCP_notify;
    
    
    if(!pAppRtcLtchInfo->ipConfig.ipv4.staticIp)
    {
        // if(GsnNwIf_dhcpClientRestoreRecord(&s2wappMainTaskCtxt->if0.nwifCtx,&pAppRtcSecMemInfo->dhcpClientParams,((ULONG)pAppRtcSecMemInfo->sleepTime)/10) != GSN_SUCCESS)
        //   S2w_Printf("\r\nDHCP RESTORE FAILED\r\n");
        dhcpParams.timeElapsed = ((ULONG)pAppRtcLtchInfo->sleepTime)/100;
        dhcpParams.pDhcpCliRecord = &pAppRtcLtchInfo->dhcpClientParams;         
        dhcpParams.requestLeaseTime = s2wCurrent.dhcpRequestLeaseTime;
        dhcpParams.dhcpRetryTimeout = s2wCurrent.dhcpRetryTimeout;
        //S2wL3Wait = TRUE;
    }
    L3ConnectStatus = FALSE;
    retVal = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, &dhcpParams);
    if(retVal == GSN_FAILURE)
    {
        if(s2wCurrent.logLevel > 0)S2w_Printf("\r\nIP CONFIG FAIL");
        GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
        return FTW_FAILURE;
    }
    else if(retVal == GSN_OPERATION_IN_PROGRESS)
    {
        S2wL3Wait = TRUE;
        GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
        if(L3ConnectStatus == FALSE)
        {
            if(s2wCurrent.logLevel > 0)S2w_Printf("\r\nIP CONFIG FAIL");
            GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
            return FTW_FAILURE;
        }
    }
    //S2wL3Wait = FALSE;
    L3ConnectStatus = TRUE;   
    s2wCurrent.netConf.dhcp = !ipConfig.ipv4.staticIp; 	   
#if 0
    memcpy(&s2wCurrent.netConf.ipAddr,(UINT8*)&(ipConfig.ipv4.ipAddr),4);
    memcpy(&s2wCurrent.netConf.netMask,(UINT8*)&(ipConfig.ipv4.subnetMask),4);
    memcpy(&s2wCurrent.netConf.gateway,(UINT8*)&(ipConfig.ipv4.gatewayIpAddr),4);
    memcpy(&s2wCurrent.dns1,(UINT8*)&(ipConfig.ipv4.dnsPriSrvrIp),4);
    memcpy(&s2wCurrent.dns2,(UINT8*)&(ipConfig.ipv4.dnsSecSrvrIp),4);
#endif
    
    
	if(pAppRtcLtchInfo->arpCacheEn)
        nx_arp_table_set(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl, &pAppRtcLtchInfo->arpTablebuf[0], 
                         pAppRtcLtchInfo->arpRecCount);
    nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,GratiousArpHandler);
    return FTW_SUCCESS;
}

/**
******************************************************************
* @ingroup S2w-Application
* @brief S2w wlan Rssi get function.
*    This function returns the rssi value.
* @param VOID.
* @retval UINT32 - the Rssi value.
******************************************************************/
PUBLIC INT8
AppS2wHal_RssiGet(void)
{
    GSN_WIF_WLAN_RSSI_T    wRssi;
    if(GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == FALSE)
    {
        return 0;
    }
    /* call the geps API to get the RSSI value.
    */
    GsnWdd_RSSIGet(&s2wappMainTaskCtxt->if0.wddCtx, (INT8*)&wRssi, sizeof(GSN_WIF_WLAN_RSSI_T));
    
    return wRssi.rssi;
    
    
}

/**
******************************************************************
* @ingroup S2w-Application
* @brief S2w wpa-psk key compute function.
*    This function compute the psk key from the SSID and passphrase and
*    returns that value
* @param wpaPsk - IN the wpa-psk paramater structure pointer.
* @retval FTW_SUCCESS.
******************************************************************/

int pbkdf2_sha1(const char *passphrase, const char *ssid, size_t ssid_len,
                int iterations, unsigned char *buf, size_t buflen); 
PUBLIC UINT8
AppS2wHal_WpaPskCompute(FTW_WPAPSK_T* wpaPsk )
{ 
    if(pbkdf2_sha1(wpaPsk->wpaPassPhrase,wpaPsk->ssid,wpaPsk->ssidLen,4096,wpaPsk->psk,FTW_PSK_LEN) != FTW_SUCCESS)
        
        return FTW_FAILURE;
    
	return FTW_SUCCESS;
}

VOID
FTW_NET_dissociateDB( VOID *ctx, GSN_STATUS status )
{
    if(status == GSN_SUCCESS)
    {
        s2wLinkState = FTW_LINK_STATE_DISCONNECTED;
    }
    /* Disconnect success, waiting in FTW_NET_disassociate()
    */
    GsnOsal_SemRelease ( &stDisassocSemaphore );
    
}

VOID
s2wDisassocCb(VOID *ctx,GSN_WDD_DISASSOCIATION_CB_INFO *pDisAssocInfo)
{
    UINT32 msg = APP_EVENT_NW_LINK_FAILURE;
    if(s2wappMainTaskCtxt->dpSleep )
    {
        AppS2w_GpioWkUpDisable();
		AppS2w_ExitDpSleep();
    }
    // for auto connection (data pipe make the async gpio low-so that host will not send data)
    if(s2wIsAutoconnected)
    {
        S2w_AsyncMsgGpioOp(0);
    }
    AppMainCtx_TaskNotify(msg);
    
}

VOID 
s2wDisassocSyncLossCb(VOID *ctx,UINT32 missBeacon)
{
    UINT32 msg = APP_EVENT_SYNC_LOSS_INDICATION;
    if(s2wappMainTaskCtxt->dpSleep )
    {
        AppS2w_GpioWkUpDisable();
		AppS2w_ExitDpSleep();
    }
    // for auto connection (data pipe make the async gpio low-so that host will not send data)
    if(s2wIsAutoconnected)
    {
        S2w_AsyncMsgGpioOp(0);
    }
    AppMainCtx_TaskNotify(msg);
}

UINT8 FTW_NET_disassociate(UINT8 parentTask)
{
	INT32 status;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	if(pAppRtcLtchInfo->arpCacheEn)
    {
    	AppArp_Invalidate();
    }
    s2wLinkState = FTW_LINK_STATE_DISCONNECTED;
    status = GsnWdd_Disconnect(&s2wappMainTaskCtxt->if0.wddCtx,8,FTW_NET_dissociateDB,s2wappMainTaskCtxt);
    
    /* If the operation is complete, then notify APP       */
    if (GSN_OPERATION_IN_PROGRESS != status)
    {
        FTW_NET_dissociateDB(NULL, status);
    }
    else
    {
        status = FTW_SUCCESS;
    }
#ifndef FTW_IP2WIFI_SUPPORT
	AppS2wHal_HttpdClose(parentTask);
#ifdef GSN_MDNS_ENABLE     
	AppS2wHal_MdnsDeInit(parentTask);
#endif	
#ifdef FTW_DHCP_SERVER_ENABLE        
    if(dhcpServerFlags & FTW_DHCP_SRVR_ENABLED)
    {
        GsnDhcpSrvr_Stop(&dhcpSrvr);
        dhcpServerFlags &= 0xfe;
    }
#endif   
    
	AppS2wHal_NetCloseAll(1);
	GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
#endif
    GsnOsal_SemAcquire ( &stDisassocSemaphore, GSN_OSAL_WAIT_FOREVER );
	return status;
}
UINT8 
AppS2wHal_NetworkConfig(FTW_NETCONF_T *params)
{
	UINT8 isStaticIP;
    GSN_NWIF_DHCP_PARAMS_T dhcpParams;
    GSN_NWIF_IP_CONFIG_T ipConfig;
    GSN_STATUS retVal;
	isStaticIP = !params->dhcp;
    memset(&ipConfig,0,sizeof(ipConfig));
    ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
	if (s2wLinkState == FTW_LINK_STATE_CONNECTED)
	{
        if(isStaticIP)
        {
            ipConfig.ipv4.staticIp = 1;
            memcpy((UINT8*)&ipConfig.ipv4.ipAddr,s2wCurrent.netConf.ipAddr,4 );
            memcpy((UINT8*)&ipConfig.ipv4.subnetMask,s2wCurrent.netConf.netMask,4 );
            memcpy((UINT8*)&ipConfig.ipv4.gatewayIpAddr,s2wCurrent.netConf.gateway,4 );
            memcpy((UINT8*)&ipConfig.ipv4.dnsPriSrvrIp,s2wCurrent.dns1,4);
            memcpy((UINT8*)&ipConfig.ipv4.dnsSecSrvrIp,s2wCurrent.dns2,4);
        }
        else
        {
            ipConfig.ipv4.staticIp = 0;
            L3ConnectStatus=0;
            s2wappMainTaskCtxt->if0.nwifCtx.notifyCb = DHCP_notify;
            memset(&dhcpParams,0,sizeof(dhcpParams));
            dhcpParams.dhcpMaxRetryCnt = FTW_DHCP_MAX_RETRY_COUNT;
            if(strlen((const char *)s2wCurrent.hostName) != 0)
            {
                memcpy(ipConfig.ipv4.hostName, s2wCurrent.hostName,
                       (GSN_NWIF_HOST_NAME_MAX_LEN + 1));
            }
            dhcpParams.radioMode = s2wCurrent.netConf.dhcpRadioMode;
            dhcpParams.requestLeaseTime = s2wCurrent.dhcpRequestLeaseTime;
            dhcpParams.dhcpRetryTimeout = s2wCurrent.dhcpRetryTimeout;
        }
        S2wL3Wait = TRUE;
        retVal = GsnNwif_IPv4Configure(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig.ipv4, &dhcpParams);
        if(GSN_NW_IF_CLOSED == retVal)
        {
            retVal = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, &dhcpParams);
            
        }		
        if(isStaticIP)
        {
            L3ConnectStatus = TRUE;
            AppS2wHdrAndIpv4_Print();
            return FTW_SUCCESS;
            
        }
        
        else if(GSN_OPERATION_IN_PROGRESS != retVal) 
        {
            
            DHCP_notify(GSN_FAILURE, &s2wappMainTaskCtxt->if0.nwifCtx);
            
        }
        GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
        if(TRUE == L3ConnectStatus)
        {
            AppS2wHdrAndIpv4_Print();
            return FTW_SUCCESS;
        }
        else
        {
            GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
            return FTW_ENOIP;
        }
    }
    return FTW_SUCCESS;
}

#ifdef FTW_SECURITY_WPS_ENABLE

#define APP_NCM_CFG_DFLT_WPS_USR_NAME   "WFA-SimpleConfig-Enrollee-1-0"
UINT32 wpsConnDone = FALSE;
UINT8 wpsL2ConInfoStore = FALSE;
GH_SEM stWpsAssSemaphore;

/*****************************************************************************
*  Private Functions
********s*********************************************************************/
VOID FTW_NET_WPS_manageCredentials(void)
{
	UINT8 ssid[33];
	INT8 chnl[4];
	UINT8 passphrase[65];
	UINT8 WepKey[20];
	//UINT32 message;
	FTW_FLASH_PARAMS_T s2wProfileParm;
    FTW_PROFILE_T *pS2wProfile;
	UINT32 i;
	GSN_WDD_WLAN_CFG_T *wlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
	//wpsConnDone = FALSE;
    memset(&s2wProfileParm, 0, sizeof(FTW_FLASH_PARAMS_T));    
	pS2wProfile = &s2wCurrent;/*Store values in current profile*/	
	memcpy(ssid, wlanConfig->ssid.array, wlanConfig->ssid.length);
	ssid[wlanConfig->ssid.length]= '\0';
	sprintf(chnl, "%u", wlanConfig->channel[0]);
    
	S2w_Printf("\r\nSSID=%s\r\nCHANNEL=%s\r\n", ssid, chnl);		
	if ((wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA2_PERSONAL) ||
        (wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA_PERSONAL))
	{
		if(0 != wlanConfig->securityCfg.pskConfig.passPhrase.Len)
        {
            memcpy(passphrase, wlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
                   wlanConfig->securityCfg.pskConfig.passPhrase.Len);
            passphrase[wlanConfig->securityCfg.pskConfig.passPhrase.Len ]= '\0';
			S2w_Printf("PASSPHRASE=%s\r\n", passphrase);
        }
		else if(1 == wlanConfig->securityCfg.pskConfig.pskValid)
        {
            memcpy(passphrase,wlanConfig->securityCfg.pskConfig.psk,
                   sizeof(wlanConfig->securityCfg.pskConfig.psk));
            passphrase[sizeof(wlanConfig->securityCfg.pskConfig.psk)] = '\0';
            
			S2w_Printf("PASSPHRASE=");
			for(i = 0; i<sizeof(wlanConfig->securityCfg.pskConfig.psk); i++)
			{
				S2w_Printf("%02x", passphrase[i]);
			}
			S2w_Printf("\r\n");
		}
	}
	else if(wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WEP) 
	{
		UINT8 i = 0;
		memcpy(WepKey, wlanConfig->securityCfg.wepConfig.Key,
			   wlanConfig->securityCfg.wepConfig.KeyLen);
		S2w_Printf("WEPKEY=");
		for(i=0;i<wlanConfig->securityCfg.wepConfig.KeyLen;i++)
		{
			S2w_Printf("%02x",WepKey[i]);
		}
		S2w_Printf("\r\nWEPKEYINDEX=%d\r\n", wlanConfig->securityCfg.wepConfig.KeyId+1);
	}	
	if(TRUE == wpsL2ConInfoStore )
	{
		pS2wProfile->autoWlandata.ssidLen = wlanConfig->ssid.length;
		memset(pS2wProfile->autoWlandata.ssid,0,FTW_MAX_SSID_LEN);
		memcpy(pS2wProfile->autoWlandata.ssid, wlanConfig->ssid.array,
               wlanConfig->ssid.length);
		pS2wProfile->netConf.dhcp = 1;
		pS2wProfile->autoWlandata.channel = wlanConfig->channel[0];
        
		if ((wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA2_PERSONAL) ||
            (wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA_PERSONAL))
		{
			/* 
            if the pskvalid  flag was set after  WPS , then reset the passpharse. 
			*/	
			if(0 != wlanConfig->securityCfg.pskConfig.passPhrase.Len)
			{
				pS2wProfile->security.wpa.pskValid = 0;
				memset(pS2wProfile->security.wpa.wpaPassPhrase,0,FTW_PSK_PASSPHRASE_LEN_MAX);
				memcpy(pS2wProfile->security.wpa.wpaPassPhrase, wlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
                       wlanConfig->securityCfg.pskConfig.passPhrase.Len);
				pS2wProfile->security.wpa.passPhraseLen =wlanConfig->securityCfg.pskConfig.passPhrase.Len;
			}				
			else if(1 == wlanConfig->securityCfg.pskConfig.pskValid)			
			{
				memcpy(pS2wProfile->security.wpa.psk,
                       wlanConfig->securityCfg.pskConfig.psk, GSN_WDD_SEC_PMK_LEN);
				pS2wProfile->security.wpa.pskValid = 1;
				memset(pS2wProfile->security.wpa.ssid,0,FTW_MAX_SSID_LEN);
				memcpy(pS2wProfile->security.wpa.ssid,wlanConfig->ssid.array,wlanConfig->ssid.length);
				pS2wProfile->security.wpa.ssidLen = wlanConfig->ssid.length;
				memset(pS2wProfile->security.wpa.wpaPassPhrase,0,FTW_PSK_PASSPHRASE_LEN_MAX);
				pS2wProfile->security.wpa.passPhraseLen =0;
			}
            
		}
		else if(wlanConfig->securityCfg.mode& GSN_WDD_SEC_MODE_WEP)
		{				
			pS2wProfile->security.wep.keyIdx = 0;
			pS2wProfile->security.wep.keyLen[0] = wlanConfig->securityCfg.wepConfig.KeyLen;
			memcpy(pS2wProfile->security.wep.key[0], wlanConfig->securityCfg.wepConfig.Key,
				   wlanConfig->securityCfg.wepConfig.KeyLen);
		}
		pS2wProfile->securityType= SECTYPE_AUTO;
#ifdef  FTW_NCM_SUPPORT_ENABLE
		if(s2wappMainTaskCtxt->ncmAutoConEn)
		{
			pS2wProfile->ncmAutoMgr =  1;			
			pS2wProfile->mode =  1;
		}
		else
			pS2wProfile->ncmAutoMgr = 0;
#endif
		memcpy(&s2wProfileParm.profile[0], pS2wProfile, sizeof(FTW_PROFILE_T));
		S2w_SaveS2wProfile(&s2wProfileParm, 0);
	}
}

VOID FTW_NET_WPS_associateCB(VOID *pCtx, INT32 status)
{
	/*stop timer*/
	GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
    // UINT32 msg = APP_EVENT_WPS_ASSOC;
    if (GSN_SUCCESS == status)
    {
        /* return AP credentiials */
        wpsConnDone = TRUE;
    }
	else if(status == GSN_FAILURE/*GSN_WDD_WPS_CONNECT_FAILURE*/)
	{
        wpsConnDone = FALSE;
        wpsL2ConInfoStore=FALSE;
        //FTW_NET_WPS_manageCredentials();
    }
    else if(GSN_WDD_WPS_SESSION_OVERLAP == status || GSN_WDD_SSID_NOT_FOUND == status )
    {
        /* return error */
        wpsConnDone = FALSE;
    }
    else if( GSN_WDD_WPS_DONE == status )
    {
        wpsConnDone = FALSE;
        //FTW_NET_WPS_manageCredentials();
    }
    GsnOsal_SemRelease(&stWpsAssSemaphore);
    //AppMainCtx_TaskNotify(msg);
    
    
}

VOID FTW_NET_WPS_associateNotify(VOID *pCtx/*, INT32 status*/)
{
	GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    
    
    if(TRUE == wpsConnDone || TRUE == wpsL2ConInfoStore )
    {
    	if( GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE)
    	{
            s2wLinkState = FTW_LINK_STATE_CONNECTED;
		}
    	else
    	{
    		s2wLinkState = FTW_LINK_STATE_DISCONNECTED;
		}
        /* get the info */
        /*GsnWdd_WlanConfigGet(&s2wappMainTaskCtxt->wdd, &wlanConfig);*/
        
        /* copy to the info structure and return
        */
        /* copy the ssid and len  and channel
        */
        memcpy(current_wlan_info.ssid,pWlanConfig->ssid.array,
               pWlanConfig->ssid.length );
        current_wlan_info.ssidLen = pWlanConfig->ssid.length;
        
        /* associated ch will be at 0 index
        */
        current_wlan_info.channel = pWlanConfig->channel[0];
        
        memcpy(current_wlan_info.bssid, pWlanConfig->bssid.array,6);
        current_wlan_info.validBssid = 1;
        
        {
            current_wlan_info.mode = FTW_WLANDATA_MODE_INFRA;
        }
        
        /* not required */
    }
    else
    {
        s2wLinkState = FTW_LINK_STATE_DISCONNECTED;
    }
    
    //GsnOsal_SemRelease(&stWpsAssSemaphore);
    
}

#define FTW_WPS_TIMEOUT  (150)
/**
******************************************************************
* @ingroup S2w-Application
* @brief S2w wps associate function.
*    This function associates to the wlan where the wps pbc/pin method
*    enabled.If it already associated first it will do a dissociate and then
*    Associates.
* @param params - IN the wlan parameter structure pointer
* @retval FTW_SUCCESS - operation successful.
* @retval FTW_FAILURE - operation failure.
******************************************************************/
//UINT8 const  pin[8] =  {'4', '1', '0','8', '5', '1', '8', '9'};
UINT8 FTW_NET_WPS_associate(FTW_WPS_T *params, GSN_MAC_SSID_T *ap_ssid,UINT8 parentTask)
{
    GSN_WDD_SECURITY_CONFIG_T *pSecConfig;
    UINT32 connectFlags = 0;
    GSN_STATUS retCode;
    UINT8 wpsUserName[] = APP_NCM_CFG_DFLT_WPS_USR_NAME;
    GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    
    wpsConnDone = FALSE;
	wpsL2ConInfoStore = params->storeL2ConInfo;
    UINT8 WpsUuid[16] = {'g','a','i','n','s', 'p', 'a', 'n'};
    
#ifdef GSN_SECURITY_WPS_REGISTRAR_ENABLE
    if(s2wCurrent.mode == 2)
    {
        UINT8 pbc = 1;
        if ( params->type == 2 || params->type == 3)
        {
            pbc = 0;
        }
        GsnWps_Trigger( &s2wappMainTaskCtxt->wdd, pbc,  params->pin );
        return FTW_SUCCESS;
    }
#endif
    
    /* if already associated, disassociate */
    if (s2wLinkState != FTW_LINK_STATE_DISCONNECTED)
    {
        /* disassociate */
		s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
                                                           GSN_SOFT_TMR_ONESHOT,0,
                                                           SEC_TO_SYSTIME(FTW_WLAN_RESPTIMEOUT),
                                                           ( GSN_SOFT_TMR_CBR_T )FTE_NET_wlanRespTmrCB,NULL);
        FTW_NET_disassociate(parentTask);
        
		GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
    }
    if(params->type == 3)
        connectFlags = GSN_WDD_CONNECT_FLAG_WPS_WITH_DFLT_PIN_METHOD;
    /* Get pointer to security config in NW config */
    pSecConfig = &pWlanConfig->securityCfg;
    
    /* We will wait on this semaphore after issueing the GsnWdd_connect().
    This will be released by wddConnect_cb() */
    GsnOsal_SemCreate(&stWpsAssSemaphore, 0);
    
    /* Set defaults */
    GsnWdd_WlanConfigDefaultInit(pWlanConfig);
    if(0 != s2wCurrent.listenInterval)
    {   /* overide the default. Set the configured listenInterval*/
        pWlanConfig->staSpecificCfg.listenInterval = s2wCurrent.listenInterval;
    }
    memcpy(pWlanConfig->ssid.array, ap_ssid->array, ap_ssid->length);
    pWlanConfig->ssid.length = ap_ssid->length;
    
    /* Compute private and public enrolee keys */
    /* Now initiate wps connection */
    
    /* Prepare connection request flags */
    //connectFlags |= GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT;
    //connectFlags |= GSN_WDD_CONNECT_FLAG_ACTIVE_SCAN;
	connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_MATHOD;
    //connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_REGISTER;
#ifdef FTW_WPS_CERTIFICATION
    connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_CERTIFICATION;
#endif
    /* Get the pin */
    memcpy(pSecConfig->wpsConfig.pin, params->pin , sizeof(pSecConfig->wpsConfig.pin));
    
    /* Get user name */
    pSecConfig->eapConfig.userName.Length = strlen((const char *)wpsUserName);
    memcpy(pSecConfig->eapConfig.userName.Name, wpsUserName,
           strlen((const char *)wpsUserName));
    
    /*set the channel list*/
    {
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
        switch(s2wCurrent.regDomain)
        {
        case FTW_DOMAIN_FCC:
            pWlanConfig->channel[11] = 0;
			break;
        case FTW_DOMAIN_ETSI:
            pWlanConfig->channel[11] = 12;
            pWlanConfig->channel[12] = 13;
            pWlanConfig->channel[13] = 0;
			break;
        case FTW_DOMAIN_TELEC:
            pWlanConfig->channel[11] = 12;
            pWlanConfig->channel[12] = 13;
            pWlanConfig->channel[13] = 14;
            pWlanConfig->channel[14] = 0;
			break;
        default:
            pWlanConfig->channel[11] = 0;
			break;
		}
        
		//memcpy(pWlanConfig->securityCfg.wpsConfig.pin, pin, 8);
		//pWlanConfig->securityCfg.wpsConfig.pin[] =
		pSecConfig->wpsConfig.pDeviceName = "GainSpan WiFi Module";
		pSecConfig->wpsConfig.pManufacturer = "GainSpan";
		pSecConfig->wpsConfig.pModelName = FTW_HW_VERSION;
		pSecConfig->wpsConfig.pModelNumber = "2000";
		pSecConfig->wpsConfig.pSerialNumber = "12345678";
		pSecConfig->wpsConfig.rfBands = (GSN_WDD_WPS_RF_T)0x01;
        
        WpsUuid[7] &= 0x1F;
        WpsUuid[8] = 11;
        WpsUuid[9] = 12;
        GsnWdd_PhyAddrGet(&s2wappMainTaskCtxt->if0.wddCtx, (INT8 *)&WpsUuid[10]);
		pSecConfig->wpsConfig.pUuid = WpsUuid;
        
        
		pSecConfig->wpsConfig.pFriendlyName = NULL;
		pSecConfig->wpsConfig.pManufacturerUrl = "gainspan.com";
		pSecConfig->wpsConfig.pModelDescription = NULL;
		pSecConfig->wpsConfig.pModelUrl = NULL;
		pSecConfig->wpsConfig.pUpc = NULL;
        
		//pWlanConfig->securityCfg.wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_LABEL;
		pWlanConfig->securityCfg.wpsConfig.configMethods = (GSN_WDD_WPS_CONFIG_METHOD_T)(GSN_WDD_WPS_CONFIG_LABEL |
                                                                                         GSN_WDD_WPS_CONFIG_PUSHBUTTON |
                                                                                             GSN_WDD_WPS_CONFIG_VIRT_PUSHBUTTON);
		/* Only thing that needs to be */
    }
    
    GsnWdd_WlanConfigSet(&s2wappMainTaskCtxt->if0.wddCtx, pWlanConfig);
    
	/* start the timer*/
	s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
                                                       GSN_SOFT_TMR_ONESHOT,0,
                                                       SEC_TO_SYSTIME(FTW_WPS_TIMEOUT),
                                                       ( GSN_SOFT_TMR_CBR_T )FTE_NET_wlanRespTmrCB,NULL);
    
    /* Init crypto engine */
    GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
    
    /* do L2 connection using WPS */
    retCode = GsnWdd_Connect(&s2wappMainTaskCtxt->if0.wddCtx,
                             (GSN_WDD_CONNECT_FLAG_T)connectFlags, pWlanConfig, NULL,
                             FTW_NET_WPS_associateCB, NULL);
    if(retCode != GSN_OPERATION_IN_PROGRESS)
    {
        /* it should be failuer */
        FTW_NET_WPS_associateCB(NULL, GSN_FAILURE);
    }
    
    /* wait for the call back to be get called */
    GsnOsal_SemAcquire( &stWpsAssSemaphore, GSN_OSAL_WAIT_FOREVER);
    
    /*Disable crypto */
    GsnHeIf_DriverSuspend();
    
    FTW_NET_WPS_associateNotify(s2wappMainTaskCtxt);
    if( wpsL2ConInfoStore == TRUE && wpsConnDone == FALSE )
    {
    	//wpsL2ConInfoStore = FALSE;
    	FTW_NET_WPS_manageCredentials();
    }
    else if(wpsConnDone == TRUE)
    {
		FTW_NET_WPS_manageCredentials();
		/*Clear Scan data base in Wlan*/
		//GsnWif_ClearScanDataBase(&s2wappMainTaskCtxt->if0.wifCtx);
        retCode = FTW_SUCCESS;
    }
    else
    {
        retCode = FTW_FAILURE;
    }
    /* Set the security to auto */
    s2wCurrent.securityType = 0;
    GsnOsal_SemDelete(&stWpsAssSemaphore);
    return retCode;
    
    
    
}

#endif /*GSN_SECURITY_WPS_ENABLE*/