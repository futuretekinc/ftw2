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
* $RCSfile: gsn_sys_rtc_info.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_SYS_RTC_INFO_H_
#define _GSN_SYS_RTC_INFO_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#define RTC_LATCH_MEM_ADDR	0x41010000 

#define GSN_RTC_MAGIC_NUM 0x95959595

typedef struct GSN_SYS_RESERVD_RTC_INFO
{
	UINT32 magicNum;
	UINT32 bootReason;
	UINT32 bootInfo;
	UINT32 AppReq;
	UINT32 sysResetInfoRtcLocn;/**<*/
	UINT32 sysStatsRtcLocn;
	UINT32 cryptoSeedLocn;
	ULONG64 sysTimeOffset;
	UINT32 reserved[11];
}GSN_SYS_RESERVD_RTC_INFO_T;

#define GSN_SYS_RTC_LATCH_MEM_USERAPP_ADDR	(GSN_RTC_LATCH_MEM_ADDR + sizeof(GSN_SYS_RESERVD_RTC_INFO_T))

typedef struct GSN_SYS_RTC_INFO_INIT_PARAM
{	
	UINT32 sysResetInfoRtcLocn;
	UINT32 sysStatsLocation;
	UINT32 cryptoSeedLocn;
}GSN_SYS_RTC_INFO_INIT_PARAM_T;

INLINE VOID
GsnSysRtcInfo_Init(GSN_SYS_RTC_INFO_INIT_PARAM_T *pParam)
{
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	pRtcRsvdInfo->sysStatsRtcLocn = pParam->sysStatsLocation;
	pRtcRsvdInfo->sysResetInfoRtcLocn = pParam->sysResetInfoRtcLocn;
	pRtcRsvdInfo->cryptoSeedLocn = pParam->cryptoSeedLocn;
}

INLINE VOID
GSN_BOOTINFO_SET(UINT32 bootReason, UINT32 bootInfo)
{
	
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	pRtcRsvdInfo->bootReason = bootReason;
	pRtcRsvdInfo->bootInfo = bootInfo;
}

INLINE UINT32
GSN_IS_RTC_RSVD_INFO_VALID(VOID)
{
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	if (pRtcRsvdInfo->magicNum == GSN_RTC_MAGIC_NUM)
		return 1;
	else
		return 0;
}

INLINE VOID
GSN_RTC_RSVD_INFO_VALID_SET(VOID)
{
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	pRtcRsvdInfo->magicNum = GSN_RTC_MAGIC_NUM;
}


INLINE UINT32
GSN_BOOT_REASON_GET(VOID)
{	
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	return pRtcRsvdInfo->bootReason;
}

INLINE UINT32
GSN_BOOT_INFO_GET(VOID)
{	
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	return pRtcRsvdInfo->bootInfo;
}

INLINE UINT32
GSN_SYS_RESET_INFO_LOCATION_GET(VOID)
{	
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	return pRtcRsvdInfo->sysResetInfoRtcLocn;
}

INLINE UINT32
GSN_SYS_STATS_LOCATION_GET(VOID)
{	
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	return pRtcRsvdInfo->sysStatsRtcLocn;
}

INLINE VOID
GSN_APP_REQ_SET(UINT32 val)
{

	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	pRtcRsvdInfo->AppReq = val;
}

INLINE UINT32
GSN_APP_REQ_GET(VOID)
{

	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	return pRtcRsvdInfo->AppReq;
}


INLINE UINT32
GSN_SYS_CRYPTO_SEED_LOCATION_GET(VOID)
{	
	GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
	return pRtcRsvdInfo->cryptoSeedLocn;
}

INLINE VOID 
GSN_SYS_TIME_OFFSET_SET(ULONG64 offset)
{
    GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
    pRtcRsvdInfo->sysTimeOffset = offset;
}

INLINE ULONG64 *
GSN_SYS_TIME_OFFSET_LOC_GET()
{
    GSN_SYS_RESERVD_RTC_INFO_T *pRtcRsvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;
    return &pRtcRsvdInfo->sysTimeOffset;
}
#endif
