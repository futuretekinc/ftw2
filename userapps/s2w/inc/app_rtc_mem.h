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
* $RCSfile: app_rtc_mem.h,v $
*
* Description : This file contains RTC memory structure definition.
* parameters  .
******************************************************************/
#ifndef _GSN_RTC_MEM_APP_H_
#define _GSN_RTC_MEM_APP_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"
#include "gsn_defines.h"

#define MAX_ARP_ENTRY_STORE	2
#define MAX_WLAN_STANDBY_DATA_SIZE	1536

/*	stand by request with this val keeps the node  in stand by for about
	1.5 days
*/
#define APP_BATT_CHK_LONG_STANDBY_WAKEUP_TIME 0xFFFFFFFFFFFFFFFF


/**
 *****************************************************************************
 * @ingroup S2w-Application
 * @brief batt check info structure .
 *    This structure defines the batt check data structure  for rtc memory.
 *****************************************************************************/
typedef struct APP_BATTCHK_INFO
{
	UINT32 chkFreq;
	UINT32 latestVal;
    UINT32 lowestAvgVal;
    UINT32 warningLvl;
    UINT32 stdByLvl;
    UINT32 prevReadings[4];
    UINT8  indx;
    UINT8  warngsCnt;
	UINT8  warngFreq;
    UINT8  battState;

}APP_BATTCHK_INFO_T;

/*battery state definitions*/
typedef enum
{
    APP_BATT_CHK_BATT_STATE_GOOD = 0,
    APP_BATT_CHK_BATT_STATE_DEAD = 1,
    APP_BATT_CHK_BATT_STATE_LOW = 2
} APP_BATT_CHK_BATT_STATE_T;

typedef struct APP_IFC_RTC_INFO_T
{
	GSN_WDD_PERSIST_INFO_T wddRtcInfo;
}APP_IFC_RTC_INFO_T;

//#pragma pack(1)

/*Things To be stored in RTC Latch Memeory*/
typedef struct APP_RTC_LATCH_MEM_INFO
{
	GSN_SYS_RESET_INFO_T sysResetInfo;
	UINT8 grpProvVerify;
	APP_IFC_RTC_INFO_T	ifc_1;
	GSN_WLAN_MAC_SSID_T  	ssid;
    GSN_WLAN_MAC_ADDR_T  	bssid;
    GSN_WDD_SEC_MODE_T wsec;
	GSN_WDD_WEP_AUTH_TYPE_T authType;
	UINT8 channel;
    UINT8 wmode;
    UINT8 AssocStatus;
	UINT8 arpTablebuf[sizeof(ARP_REC) * MAX_ARP_ENTRY_STORE];
	UINT8 arpCacheEn;
	UINT8 psStbycmd;	
#ifdef S2W_PERSISTENT_TMR_SUPPORT
	UINT8  persistTmr[( GSN_P_TMR_NVRAM_MEM_SIZE( APP_NUM_OF_CONST_PERSIST_TMR, 
			APP_NUM_OF_VAR_PERSIST_TMR )) ]; 
#endif
	UINT8	arpRecCount;
	UINT32 	randomSeed;
	GSN_NWIF_IP_CONFIG_T	ipConfig;
	
	GSN_SYS_STATS_T	sysStats;
	/*Standby sleep time*/
	ULONG64 		sleepTime;
	/*Dhcp cleint record*/
	NX_DHCP_CLIENT_RECORD dhcpClientParams;
	/*Host name*/
	UINT8			hostName[GSN_NWIF_HOST_NAME_MAX_LEN + 1]; 
	/* Battery check params*/
	APP_BATTCHK_INFO_T battchkinfo;
	UINT8 hibernate;
}
APP_RTC_LATCH_MEM_INFO_T;

//#pragma pack()

/*Things To be stored in RTC Latch Memeory*/
typedef struct APP_RTC_SECNDRY_MEM_INFO
{
	UINT32				macStdbyCtxLen;
	INT8 				macStdbyCtx[MAX_WLAN_STANDBY_DATA_SIZE];
	UINT32				cryptoSeed[32/sizeof(UINT32)];
    GSN_WPAIF_PMK_CACHE_ENTRY pmkCache[1];

}APP_RTC_SECNDRY_MEM_INFO_T;

INLINE APP_RTC_LATCH_MEM_INFO_T *
App_RtcLatchMemInfoPtrGet()
{	
	return (APP_RTC_LATCH_MEM_INFO_T *)(GSN_SYS_RTC_LATCH_MEM_USERAPP_ADDR);
}

INLINE APP_RTC_SECNDRY_MEM_INFO_T *
App_RtcSecMemInfoPtrGet()
{	
	return (APP_RTC_SECNDRY_MEM_INFO_T *)(GSN_RTC_SRAM_BLOCK0_ADDR);
}


PUBLIC VOID
APP_RtcInit(UINT8 clearRtcMem);
#endif /* _GSN_RTC_MEM_APP_H_ */

/*****************************************************************/

