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
* $RCSfile: gsn_stats.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_STATS_H_
#define _GSN_STATS_H_
#include "core/sys_utils/gsn_sys_rtc_info.h"

typedef struct GSN_SYS_STATS
{
	UINT32 app_wdCnt;
	/* Exception Statistics*/
	UINT32 excp_hardFault;
	UINT32 excp_memManageFault;
	UINT32 excp_busFault;
	UINT32 excp_usageFault;

	/*WLAN CPU related*/
	UINT32 wlan_resetReqCnt;
	UINT32 wlan_WdCnt;
}GSN_SYS_STATS_T;

typedef struct GSN_HIF_STATS
{
	UINT32 txBufAllocSuccess;
	UINT32 txBufReleaseCount;
	/*Msg Sys Error Statistics*/
	UINT32 txBufAllocFail;
	UINT32 dTxTdQfull;
	UINT32 cTxTdQfull;
}GSN_HIF_STATS_T;

/*Wdd*/
typedef struct GSN_WDD_STATS
{
	UINT32  conctRqstCnt;
	UINT32  conctSuccessCnt;
	UINT32  conctFailCnt;
	UINT32  disConctRqstCnt;
	UINT32  disConctSuccessCnt;
	UINT32  disAsssocCnt;
	UINT32  beaconMissCnt;
	UINT32  frameTxFailCnt;
	UINT32	scanAndConctCnt;
	UINT32	wlanNwFoundCnt;/**< requested SSID/BSSID  found count*/
	UINT32	wlanNwSelectedCnt; /**< requested SSID/BSSID, chnnel, security parameters match*/
	UINT32  scanReqCnt;
	UINT32  scanCompltCnt;
	UINT32  scanRsltCnt;
}GSN_WDD_STATS_T;

/* Nwif*/
typedef struct GSN_NWIF_STATS
{
	UINT32 	totalPktsRcvd;/*Packets dropped due to no memory in Rx pool*/
	UINT32  pktFilteredOut;
	UINT32 	pktsDroppedNoMem;/*Packets dropped due to no memory in Rx pool*/
	UINT32 	ipPktsRcvd;
	UINT32 	ipUnicastPktsSent;
	UINT32 	ipBroadCastPktsSent;
	UINT32 	arpRequestRcvd;
	UINT32 	arpRequestSent;
	UINT32 	arpResponseSent;
	UINT32  dhcpSuccessCnt;
	UINT32  dhcpFailCnt;
}GSN_NWIF_STATS_T;

#define GSN_SYS_STATS_PTR	((GSN_SYS_STATS_T *)GSN_SYS_STATS_LOCATION_GET())

#endif
