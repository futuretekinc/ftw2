/*****************************************************************
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
* $RCSfile: app_main_ctx.h,v $
*
* Description : This file contains the application main task definitions.
*
******************************************************************/
#ifndef _APP_MAIN_CTX_H_
#define _APP_MAIN_CTX_H_

typedef struct APP_IF_INFO
{
	UINT32 macIfNum;
	GSN_WIF_WLAN_NW_TYPE_T macIfType;

	/*Wif context*/
	GSN_WIF_CTX_T	wifCtx;
	/*Wdd (L2 Dev) context */
	GSN_WDD_CTX_T wddCtx;
	/*Nw If (L3 and above) context*/
	GSN_NWIF_CTX_T nwifCtx;

	GSN_DHCP_SRVR_T dhcpSrvrHndl;
	GSN_DNS_SERVER_T dnsServerHndl;
	/*Network connection Manager Context*/
	GSN_NCM_CTX_T ncmCtx;
	/*Mdns Context*/
    GSN_MDNS_T mdns;
}APP_IF_INFO_T;

typedef struct APP_WPS
{
    UINT32 type;
    UINT8 pin[32];
}APP_WPS_T;

typedef struct APP_HTTPS_CERTS_INFO
{
	UINT8 httpsFlag; /**<  Flag indicating whether httpd server should run as http / https */
	SERVER_CERT_DETAIL_T certDetail;
}APP_HTTPS_CERTS_INFO_T;

typedef struct APP_MAIN_CTX
{
	GSN_CLK_CTL_CM3_CLK_CFG_T cm3ClkCfg;
	/* HI ctx*/
	GSN_HI_CTX_T hiCtx;
	/*Sys Control Contexts*/
	GSN_SYSIF_CTX_T sysifCtx;
	GSN_SYS_CTL_CTX_T sysCtlCtx;
	/*Wif message receive handler context*/
	GSN_MSG_HANDLER_CTX_T softTmrMsgHdlrCtx;
	UINT32 softTmrMsg;
	/*Wdd message handler context*/
	GSN_WDD_MSG_HANDLER_T wddMsgHdlrCtx;
	/* Nw context */
	GSN_NW_CTX_T nwCtx;
	/* Bsd Layer Data structure*/
	GSN_NW_BSD_T bsdCtx;
	/*Interface 0 informmation*/
	APP_IF_INFO_T if0;

	APP_BATT_RTC_CTX_T rtcBattCtx;
	APP_BATT_CTX_T appBattCtx;

	/*App Configuration*/
	APP_CONFIG_T config;
	APP_HTTPS_CERTS_INFO_T httpsInfo; 
	UINT32 nwConnected;
	APP_FS_T fs;
	#ifdef ADK_PROV_WPS_ENABLE
		APP_WPS_T wpsParams;
		GSN_MAC_SSID_T wpsapSsid;
	#endif
	GSN_PWR_MGMT_CTX_T pwrMgmtCtx;
#ifdef APP_OPT_PS_IN_PSPOLL
	GSN_OSAL_SEM_T synSyncSem;
	GSN_SOFT_TMR_T synTimeOut;
	GSN_SOFT_TMR_HANDLE_T synTimeOutHndl;
	GSN_SOFT_TMR_T arpStbyDisableTmr;
	GSN_SOFT_TMR_HANDLE_T arpStbyDisableTmrHndl;
#endif
} APP_MAIN_CTX_T;

typedef struct APP_MAINTASK_MSG
{
	UINT32 msgId;
	UINT32 msgInfo;

}APP_MAINTASK_MSG_T;

typedef struct APP_RTC_INFO
{
	GSN_SYS_RESET_INFO_T sysResetInfo;
	GSN_SYS_STATS_T	gsnSysStats;
}APP_RTC_INFO_T;

extern APP_MAIN_CTX_T appCtx;
extern APP_MAIN_CTX_T *globalAppCtxPtr;

PUBLIC VOID
AppMainCtx_Init(VOID);
PUBLIC VOID
AppMainCtx_TaskNotify(INT32 msgId, UINT32 msgInfo);

#endif /*_APP_MAIN_CTX_H_*/


