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
* $RCSfile: app_rtc_mem.c,v $
*
* Description : This file contains RTC memory structure definition.
* parameters  .
******************************************************************/
#include "gsn_includes.h"
#include "gsn_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_rtc_mem.h"

GSN_SYS_STATS_T	gsnSysStatsSram;
PUBLIC VOID
APP_RtcInit(UINT8 clearRtcMem)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T *PAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
    //UINT32 rstSize = sizeof(APP_RTC_LATCH_MEM_INFO_T) - offsetof(APP_RTC_LATCH_MEM_INFO_T, ifc_1) - sizeof(GSN_SYS_RESERVD_RTC_INFO_T);
    /* If reset size exceeds 1024 bytes, address gets rounded to 0 and starting memory gets reset */
    UINT32 rstSize = 1024 - offsetof(APP_RTC_LATCH_MEM_INFO_T, ifc_1) - sizeof(GSN_SYS_RESERVD_RTC_INFO_T);
	GSN_SYS_RTC_INFO_INIT_PARAM_T param;
	
	//GsnRtc_RtcSramBlockEn(GSN_RTC_SRAM_BLOCK0);
	if(clearRtcMem == 1)
	{
		memset((INT8 *)GSN_RTC_LATCH_MEM_ADDR, 0, GSN_RTC_LATCH_MEM_BLOCK_SIZE);
		memset((INT8 *)GSN_RTC_SRAM_BLOCK0_ADDR, 0, GSN_RTC_SRAM_BLOCK_SIZE);
	}
	else if(clearRtcMem == 2)
	{
		memset(&pAppRtcLtchMemInfo->ifc_1, 0, rstSize);
	}
	
	param.sysStatsLocation = (UINT32)&gsnSysStatsSram;
	param.sysResetInfoRtcLocn = (UINT32)&pAppRtcLtchMemInfo->sysResetInfo;
	
	GsnSysRtcInfo_Init(&param);	

	GSN_RTC_RSVD_INFO_VALID_SET();
}

