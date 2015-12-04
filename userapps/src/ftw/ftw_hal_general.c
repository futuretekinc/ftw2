/*****************************************************************
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
* $RCSfile: s2w_app_hal_general.c,v $
*
* Description : s2w GEPS interface file
******************************************************************/


/*****************************************************************
* File Inclusions
*****************************************************************/


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

#include "ftw_serial.h"

/**
******************************************************************************
* @ingroup AppResourceConfig
* @brief Thread priority.
*    These MACRO defines the priority of all the thread used in the system.
******************************************************************************/


#define FTW_SUCCESS     0
#define FTW_FAILURE     1

#define FTW_SPI_FS_CLK_HSRC 1
#define FTW_SPI_FS_CLK_PLL  0
#define FTW_SPI_HOST_WAKEUP_GPIO_BITMAP 0x2000000000
#define FTW_SPI_HOST_WAKEUP_GPIO_NUM    37
//PRIVATE GSN_CLK_CTL_CTX_T gsnBrClkCtlCtx1;

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern FTW_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle;

/*****************************************************************************
Private Variables
****************************************************************************/

/**
*****************************************************************************
* @ingroup GsnWifSysDefs
* @brief Boot reason.
*
*    enumeration containing the reason for the latest SOC boot.
*****************************************************************************/


//PRIVATE UINT32 fwflag =0;

//PRIVATE GSN_CLK_CTL_CTX_T s2wClkCtlCtx;
/* Semaphore to prevent mixing of command response and
incomming data
*/
PUBLIC GSN_OSAL_SEM_T s2wSyncSemID;
PUBLIC GSN_OSAL_SEM_T s2wSyncSemID1;

extern FTW_PROFILE_PARAMS_T profile_params;
extern FTW_LINK_STATE_T s2wLinkState ;
extern FTW_WLANINFO_T current_wlan_info;
extern VOID GsnHeIf_DriverSuspend();
extern PUBLIC GSN_STATUS
GsnWdd_KeepAliveTimeOutSet(GSN_WDD_CTX_T *pWdd, UINT8 timeOut);


VOID AppS2w_GpioWkUpDisable();

VOID
App_WpaSupplicantInit(APP_MAIN_CTX_T * pAppCtx);

VOID AppS2w_SetWlanDfltParams(UINT8 profileNum);

LONG64  APP_FTW_SPI_WAKEUP_GPIO_BITMAP = 0x800000000;

/*****************************************************************************
*  Public Variables
****************************************************************************/

/* application context
*/
#ifdef FTW_RF_TEST
GSN_OSAL_SEM_T s2wWlanOpSyncSem;
#endif

GSN_CLK_CTL_CM3_CLK_CFG_T cm3ClkCfg;		//app cm3 clk config 
extern GSN_EXTFLASH_CTX_T gsExtFlashCtxFs;
/*****************************************************************************
*  Private Functions
*****************************************************************************/

extern UINT8 L3ConnectStatus;

PRIVATE void AppS2wHal_SerialInputTask( UINT32 u32Address );
extern FTW_PROFILE_T s2wCurrent;
__no_init FTW_FLASH_PARAMS_T FlashParams;

/*Initialse File system for External Flash*/
VOID
App_ExtFlash_FsInit();



FTW_PROFILE_PARAMS_T*
S2w_ProfileParamInRTCPtrGet() // right after rtc contents
{
	return (FTW_PROFILE_PARAMS_T *)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T));
    
}

FTW_FLASH_PARAMS_T*
S2w_FlashParamInRTCPtrGet() // right after profile param
{
	return (FTW_FLASH_PARAMS_T *)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T) +
	                              sizeof(FTW_PROFILE_PARAMS_T));
}


FTW_FLASH_PARAMS_T *
AppS2wHal_FlashRead(void)
{
    GSN_STATUS status = GSN_FAILURE;
    
    status = S2w_LoadS2wProfileParams();
    
    if(status == FTW_SUCCESS)
    {
        AppS2wProcess_DefaulConfigtLoad(&FlashParams);
        status = S2w_LoadS2wProfile(&FlashParams.profile[profile_params.defaultProfile],profile_params.defaultProfile);
        S2w_LoadS2wProfile(&FlashParams.profile[!profile_params.defaultProfile],!profile_params.defaultProfile);
        // set the rtc mac
        UINT8 macAddr[6];
        S2w_LoadMacAddr(macAddr);
        S2w_macAddrRTCSet(macAddr); // set in the rtc also
        // read the AP mac address and update the current profile
        S2w_LoadApMacAddr(macAddr);
        memcpy(&FlashParams.profile[profile_params.defaultProfile].lmtdApConf.macAddr,macAddr,6);
    }
    else
    {
        status = FTW_FAILURE;
	}
    
    if (status != GSN_SUCCESS)
    {
        FTW_PROFILE_PARAMS_T def_profile_params;
        
        AppS2wProcess_DefaulConfigtLoad(&FlashParams);
        def_profile_params.vsersion = FTW_PROFILE_PARAM_DFLT_VERSION;
        def_profile_params.autoConnect = 0;
        def_profile_params.defaultProfile = 0;
        
        /* First time, no profile exists in filesystem, store default profile in profile 0 */
        S2w_SaveS2wProfileParams(&def_profile_params);
        S2w_SaveS2wProfile(&FlashParams, 0);
        S2w_SaveS2wProfile(&FlashParams, 1);
        // first time execution so read the otp to get the mac address and update it
        UINT8 mac[6];
        if(otpMac_Read(mac,GSN_OTP_MM_ID_MAC_ID0) == FTW_SUCCESS)
        {
			S2w_SaveMacAddr(mac);
			S2w_macAddrRTCSet(mac); // set in the rtc also
		}
		else
		{
            S2w_SaveMacAddr(FTW_DEFAULT_STA_MAC_ADDR);
            S2w_macAddrRTCSet((UINT8*)FTW_DEFAULT_STA_MAC_ADDR); // set in the rtc also
		}
        status = FTW_FAILURE;
        
        // read the ap mac and update the file system
        if(otpMac_Read(mac,GSN_OTP_MM_ID_MAC_ID1) == FTW_SUCCESS)
        {
			S2w_SaveApMacAddr(mac);
            
		}
		else
		{
            S2w_SaveApMacAddr(FTW_DEFAULT_AP_MAC_ADDR);
            
		}
    }
    
    
    return &FlashParams;
}

UINT8 FTW_NET_macAddrSet(UINT8* macAddr, BOOL flag)
{
    UINT8 status;
    status = GsnWdd_PhyAddrSet(&appCtx.if0.wddCtx, (INT8*)macAddr,flag);
    if(status!= GSN_SUCCESS)
        return FTW_FAILURE;
    GsnNwif_UpdatePhyAddr(&appCtx.if0.nwifCtx);
    return FTW_SUCCESS;
}
UINT8 FTW_PS_pollIntervelSet(UINT32 interval)
{
	GsnWdd_KeepAliveTimeOutSet(&appCtx.if0.wddCtx, (UINT8)interval);
	return FTW_SUCCESS;
}
UINT8 
AppS2wHal_PskKeyStore(UINT8* psk)
{
    return FTW_SUCCESS;
}

UINT8 FTW_NET_macAddrGet(UINT8* macAddr)
{
    GsnWdd_PhyAddrGet(&appCtx.if0.wddCtx,(INT8*)macAddr);
    return FTW_SUCCESS;
}

#ifdef FTW_PERSISTENT_TMR_SUPPORT
VOID
AppS2w_PersistantTmrCfg()
{
	APP_PERSIST_TMR_CFG_T normalCfg;
	F_FILE *fp;
    
	fp = f_open("pstTmr", "r");
	if(fp == NULL)
	{
		fp = f_open("pstTmr", "w");
	    memset( normalCfg.persistTmrNvds, 0, sizeof( APP_PERSIST_TMR_CFG_T ));
	    f_write(&normalCfg, 1, sizeof(APP_PERSIST_TMR_CFG_T), fp);
	    f_close(fp);
    }
    else
    	f_close(fp);
}

VOID
AppS2w_PersistantTmrCfgGet(UINT8 *ptr)
{
	F_FILE *fp;
    
	fp = f_open("pstTmr", "r");
	if(fp != NULL)
	{
		f_read(ptr, 1, sizeof(APP_PERSIST_TMR_CFG_T), fp);
		f_close(fp);
	}
}

VOID
AppS2w_StateExit(APP_MAIN_CTX_T *pAppSm)
{
	F_FILE *fp;
	if( GsnPersistTmr_Store())
    {
    	fp = f_open("pstTmr", "r+");
    	f_seek(fp, offsetof(APP_PERSIST_TMR_CFG_T, persistTmrNvds), F_SEEK_SET);
    	f_write(pAppSm->persistTmrNvds, 1, sizeof(pAppSm->persistTmrNvds), fp);
    	f_close(fp);
    }
}

GSN_STATUS
AppS2w_PersistTmrInit( APP_MAIN_CTX_T *pAppSm )
{
    ULONG64 period;
    APP_PERSIST_TMR_CFG_T normalCfg;
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
    AppS2w_PersistantTmrCfgGet((UINT8 *)&normalCfg);
    memcpy( pAppSm->persistTmrNvds, normalCfg.persistTmrNvds, sizeof(normalCfg.persistTmrNvds) );
    
    /**< Initialize the persistent timer module */
    GsnPersistTmr_Init( pAppRtcLtchMemInfo->persistTmr, pAppSm->persistTmrNvds, 
                       APP_NUM_OF_VAR_PERSIST_TMR, APP_NUM_OF_CONST_PERSIST_TMR, 
                       pAppSm->persistTmrTbl );
    
    return GSN_SUCCESS;
}
#endif




PUBLIC UINT8
AppS2wHal_InfoGet(FTW_WLANINFO_T *info)
{
    if (s2wLinkState != FTW_LINK_STATE_CONNECTED)
    {
        return FTW_FAILURE;
    }
    memset(info,0,sizeof(*info));
    /*
    * current_wlan_info is updated on association/joining/creation using one of
    * update_info_from_element or update_info_from_params.
    */
    memcpy(info, &current_wlan_info, sizeof(*info));
    return FTW_SUCCESS;
}

PUBLIC VOID 
AppS2wHal_Cm3ClkCfg()
{
    UINT32 bootReason;
#ifdef GS2100M
	GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_LP_RC);
#else
	GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_LP_XTAL);
#endif
	cm3ClkCfg.pClkCtlCtx = GsnClkCtl_CtxGet();
    cm3ClkCfg.activeModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    cm3ClkCfg.sleepModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    cm3ClkCfg.deepSleepModeClkReq = (GSN_CLK_CTL_CLK_SRC_T)0;
    cm3ClkCfg.control = 1; //core control
    cm3ClkCfg.cm3ClkSel = GSN_CLK_SEL_HS_RC;
	GsnClkCtl_Cm3ClkCfg(&cm3ClkCfg);
	//GsnClkCtl_Cm3ClkSwitch(&cm3ClkCfg, GSN_CLK_SEL_HS_XTAL);
    bootReason = GSN_BOOT_REASON_GET();
 	if(bootReason == GSN_WIF_SYS_BOOT_FIRST_BOOT)
 	{
 		GsnClkCtl_HsRcCal(&cm3ClkCfg);
 	}
	
}



UINT8
AppS2wHal_NwContextStore()
{
    
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	//APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	GSN_WDD_WLAN_CFG_T *WddConf;
	UINT8 AssocStatus=0;
	GSN_NWIF_IP_CONFIG_T IpConfig;
	UINT32 arpCount = 0;
	NX_DHCP_CLIENT_RECORD dhcpClientRecord = {0};
    
    
	if(s2wLinkState == FTW_LINK_STATE_CONNECTED)
	{
		/*Store Nw parameters*/
		pAppRtcLtchInfo->ipConfig.ipv4.staticIp = !s2wCurrent.netConf.dhcp;
        
		GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx, &IpConfig);
        
        
		pAppRtcLtchInfo->ipConfig.ipv4.ipAddr =  IpConfig.ipv4.ipAddr ;
		pAppRtcLtchInfo->ipConfig.ipv4.subnetMask = IpConfig.ipv4.subnetMask;
		pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr = IpConfig.ipv4.gatewayIpAddr;
		pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp = IpConfig.ipv4.dnsPriSrvrIp;
		pAppRtcLtchInfo->ipConfig.ipv4.dnsSecSrvrIp = IpConfig.ipv4.dnsSecSrvrIp;
		pAppRtcLtchInfo->ipConfig.ipv4.dhcpLeaseExpireTime = 
            IpConfig.ipv4.dhcpLeaseExpireTime;
		
		GsnNwIf_dhcpClientCreateRecord(&s2wappMainTaskCtxt->if0.nwifCtx,&dhcpClientRecord);
		memcpy((VOID*)&pAppRtcLtchInfo->dhcpClientParams,(const VOID*)&dhcpClientRecord,sizeof(NX_DHCP_CLIENT_RECORD));
		memset(pAppRtcLtchInfo->hostName,0,GSN_NWIF_HOST_NAME_MAX_LEN+1);
		memcpy(pAppRtcLtchInfo->hostName,s2wCurrent.hostName,GSN_NWIF_HOST_NAME_MAX_LEN+1);
        
        
        
		/* Store arp table */
		if(pAppRtcLtchInfo->arpCacheEn)
			nx_arp_table_get(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl, 
                             (VOID *)&pAppRtcLtchInfo->arpTablebuf[0], 
                             sizeof(pAppRtcLtchInfo->arpTablebuf), 
                             (ULONG*)&arpCount);
		pAppRtcLtchInfo->arpRecCount = (UINT8 )arpCount;
		/* Store L2 Conf */
		WddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
		AssocStatus = GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx);
		memcpy(&pAppRtcLtchInfo->bssid, &WddConf->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
		memcpy(&pAppRtcLtchInfo->ssid, &WddConf->ssid, sizeof(GSN_WLAN_MAC_SSID_T));
		pAppRtcLtchInfo->wsec = WddConf->securityCfg.mode;
		pAppRtcLtchInfo->channel = WddConf->channel[0];
		pAppRtcLtchInfo->AssocStatus = AssocStatus;
		pAppRtcLtchInfo->wmode = s2wappMainTaskCtxt->if0.macIfType;
		pAppRtcLtchInfo->authType= WddConf->securityCfg.wepConfig.authType;
	}
	else // not connected
	{
		return FTW_LINK_LOST_EVT;
	}
	return FTW_SUCCESS;
    
}
