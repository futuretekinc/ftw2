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
#include "app_cfg.h"
#include "modules\persistent_timer\gsn_persistent_timer.h"
#define MAX_WLAN_STANDBY_DATA_SIZE	1536
#define MAX_ARP_ENTRY_STORE			2
#define CLOUD_CIK_LEN 41

typedef struct APP_CLOUD_RTC_CIK_T
{
    INT8 CIK[CLOUD_CIK_LEN];
}APP_CLOUD_RTC_CIK_T;

typedef struct APP_IFC_RTC_INFO_T
{
	GSN_WDD_PERSIST_INFO_T wddRtcInfo;
}APP_IFC_RTC_INFO_T;
/*Things To be stored in RTC Latch Memeory*/
typedef struct APP_RTC_LATCH_MEM_INFO
{
	GSN_SYS_RESET_INFO_T 	sysResetInfo;
	UINT32 UdpSeqNo;

	GSN_NWIF_IP_CONFIG_T	ipConfig;
	APP_IFC_RTC_INFO_T		ifc_1;
	UINT8 					linkChkItern;
	UINT8 					numDataTfrItern;
	UINT32 					TLSdata[4];

	UINT8 arpTablebuf[sizeof(ARP_REC) * MAX_ARP_ENTRY_STORE];
	UINT32 arpRecCount;

	UINT8  persistTmrInfoNVRAM[( GSN_P_TMR_NVRAM_MEM_SIZE( APP_NUM_OF_CONST_PERSIST_TMR,
									APP_NUM_OF_VAR_PERSIST_TMR )) ];
	//UINT32 :0; /**< persistent tmr Nvds should start at word aligned addr */
	UINT8 persistTmrInfoNvds[ GSN_P_TMR_NVDS_MEM_SIZE( APP_NUM_OF_PERSIST_TMR ) ];
	UINT8 IotGatewayIpAddress[4];
	UINT16 IotGatewayPort;
	INT8 IotDeviceId;
	INT8 IotLoopCount;
    APP_CLOUD_RTC_CIK_T cloudCIK;
    UINT32 	randomSeed;
}APP_RTC_LATCH_MEM_INFO_T;

/*Things To be stored in RTC Latch Memeory*/
typedef struct APP_RTC_SECNDRY_MEM_INFO
{
	UINT32				macStdbyCtxLen;
	INT8 				macStdbyCtx[MAX_WLAN_STANDBY_DATA_SIZE];
	UINT32 sleepTime;
	NX_DHCP_CLIENT_RECORD dhcpClientRecord;
	GSN_SYS_CONFIG_NETWORK_T  networkConfig;
#if 0
	GSN_STATISTICS_T	gsnStats;
	/*Any App Specific elements shall defined here onwards*/
#endif
	UINT32 dummy;

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
APP_RtcInit(UINT32 clearRtcMem);

#endif /* _GSN_RTC_MEM_APP_H_ */

/*****************************************************************/

