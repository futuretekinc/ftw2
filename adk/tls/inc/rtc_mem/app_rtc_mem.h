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

#define MAX_WLAN_STANDBY_DATA_SIZE	1536
typedef struct APP_IFC_RTC_INFO_T
{
	GSN_WDD_PERSIST_INFO_T wddRtcInfo;
}APP_IFC_RTC_INFO_T;
/*Things To be stored in RTC Latch Memeory*/
typedef struct APP_RTC_LATCH_MEM_INFO
{	
	GSN_SYS_RESET_INFO_T sysResetInfo;
	GSN_NWIF_IP_CONFIG_T	ipConfig;
	UINT8 arpTablebuf[sizeof(ARP_REC) * 2];
	ULONG arpRecCount;
	APP_IFC_RTC_INFO_T	ifc_1;
	UINT32 	randomSeed;
	/*This shall be the last elemnt*/
}APP_RTC_LATCH_MEM_INFO_T;

/*Things To be stored in RTC Latch Memeory*/
typedef struct APP_RTC_SECNDRY_MEM_INFO
{
#if 0
	GSN_STATISTICS_T	gsnStats;
	/*Any App Specific elements shall defined here onwards*/
#else
	/*This shall be the last elemnt*/
      UINT32 dummy;
#endif
    NX_DHCP_CLIENT_RECORD dhcpClientRecord;
    ULONG64 sleepTime;
	UINT32				macStdbyCtxLen;
	INT8 				macStdbyCtx[MAX_WLAN_STANDBY_DATA_SIZE];
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

