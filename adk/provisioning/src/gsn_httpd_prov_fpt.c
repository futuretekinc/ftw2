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
 * $RCSfile: gsn_httpd_prov_fpt.c,v $
 *
 * Description : GSN Provision  file
 *******************************************************************************/
#include "gsn_httpd_prov_fpt.h"

 _RPST_ GsnHttpd_ScanParamsCb_FP_T GsnHttpd_ScanParamsCb_FP = NULL;

 _RPST_ GsnHttpd_WpsCb_FP_T GsnHttpd_WpsCb_FP = NULL;
 _RPST_ GsnHttpd_WpsConfigInit_FP_T GsnHttpd_WpsConfigInit_FP = NULL;
 
 _RPST_ GsnHttpd_ScanSetSockOpt_FP_T GsnHttpd_ScanSetSockOpt_FP = NULL;
 
 _RPST_ GsnHttpd_IsPrintableStr_FP_T GsnHttpd_IsPrintableStr_FP = NULL;
 
 _RPST_ GsnHttpd_Scan_And_Send_Response_FP_T GsnHttpd_Scan_And_Send_Response_FP = NULL;
 
 _RPST_ GsnHttpd_ApListCb_FP_T GsnHttpd_ApListCb_FP = NULL;
 
 _RPST_ GsnHttpdApi_cb_FP_T GsnHttpdApi_cb_FP = NULL;

 _RPST_ GsnHttpd_ScanConfigInit_FP_T GsnHttpd_ScanConfigInit_FP = NULL;
 
 _RPST_ GsnHttpd_WpsInit_FP_T GsnHttpd_WpsInit_FP = NULL;

 _RPST_ GsnHttpdApi_ProvInit_FP_T GsnHttpdApi_ProvInit_FP = NULL;
 
 _RPST_ GsnHttpdApi_ProvDeInit_FP_T GsnHttpdApi_ProvDeInit_FP = NULL;
 

