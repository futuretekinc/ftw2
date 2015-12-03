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

/*******************************************************************************
 * Function Pointer Table
 ******************************************************************************/

#include "gsn_wlan_scan_fpt.h"
#include "gsn_includes.h"

 _RPST_ GsnWlanScan_Init_FP_T GsnWlanScan_Init_FP = NULL;

_RPST_ GsnWlanScan_DeInit_FP_T GsnWlanScan_DeInit_FP = NULL;

_RPST_ GsnWlanScan_SecurityTypeSet_FP_T GsnWlanScan_SecurityTypeSet_FP = NULL;

_RPST_ GsnWlanScan_ChannelFill_FP_T GsnWlanScan_ChannelFill_FP = NULL;

_RPST_ GsnWlanScan_Notification_FP_T GsnWlanScan_Notification_FP = NULL;

_RPST_ GsnWlanScan_ProvWscan_FP_T GsnWlanScan_ProvWscan_FP = NULL;

