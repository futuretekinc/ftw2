/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_prov_scan_fpt.c,v
*
*  Description : GEPS scan helper
*/


#ifndef _GSN_WLAN_SCAN_FPT_H_
#define _GSN_WLAN_SCAN_FPT_H_

#include "gsn_includes.h"
#include "gsn_wlan_scan.h"

typedef PUBLIC VOID
(*GsnWlanScan_Init_FP_T)(GSN_WDD_CTX_T* pWdd);
extern _RPST_ GsnWlanScan_Init_FP_T GsnWlanScan_Init_FP;

typedef PUBLIC VOID
(*GsnWlanScan_DeInit_FP_T)();
extern _RPST_ GsnWlanScan_DeInit_FP_T GsnWlanScan_DeInit_FP;

typedef PUBLIC VOID
(*GsnWlanScan_SecurityTypeSet_FP_T)(UINT16 capabilityInfo,UINT8 encryptionType,UINT8 authType,
                     GSN_WLAN_SECURITY_TYPE_T *securityType);
extern _RPST_ GsnWlanScan_SecurityTypeSet_FP_T GsnWlanScan_SecurityTypeSet_FP;

typedef PUBLIC VOID
(*GsnWlanScan_ChannelFill_FP_T)(UINT8 *chTable,UINT8 domain,UINT8 phyMode);
extern _RPST_ GsnWlanScan_ChannelFill_FP_T GsnWlanScan_ChannelFill_FP;

typedef PUBLIC VOID
(*GsnWlanScan_Notification_FP_T)(VOID* pScanResult,INT32 status, INT8 *rsltBuff,
   	                     UINT32 rsltCount);
extern _RPST_ GsnWlanScan_Notification_FP_T GsnWlanScan_Notification_FP;

typedef PUBLIC GSN_STATUS
(*GsnWlanScan_ProvWscan_FP_T)(GSN_WLAN_SCAN_PARAM_T *sParams,GSN_WLAN_SCAN_RESULT_T *pScanResult, INT32 *maxScanElements);
extern _RPST_ GsnWlanScan_ProvWscan_FP_T GsnWlanScan_ProvWscan_FP;

#endif
