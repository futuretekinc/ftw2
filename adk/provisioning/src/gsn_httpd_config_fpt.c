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
* $RCSfile: gsn_httpd_config_fpt.c,v $
*
* Description : Gsn Httpd Config file
*******************************************************************************/

#include "gsn_httpd_config_fpt.h"
_RPST_ GsnHttpd_ToLowerStr_FP_T GsnHttpd_ToLowerStr_FP = NULL;

_RPST_ GsnHttpd_ToHex_FP_T GsnHttpd_ToHex_FP = NULL;

_RPST_ GsnHttpd_ParseMac_FP_T GsnHttpd_ParseMac_FP = NULL;

_RPST_ GsnHttpd_WepKeyToStr_FP_T GsnHttpd_WepKeyToStr_FP = NULL;

_RPST_ GsnHttpd_KeyValueGet_FP_T GsnHttpd_KeyValueGet_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetWepFromStr_FP_T GsnHttpdApiConfig_SetWepFromStr_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetWepFromXmlStr_FP_T GsnHttpdApiConfig_SetWepFromXmlStr_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesHttpd_FP_T GsnHttpdApiConfig_SetValuesHttpd_FP = NULL;


_RPST_ GsnHttpdApiConfig_SetValuesWpaPersonalClientConfig_FP_T GsnHttpdApiConfig_SetValuesWpaPersonalClientConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesWepClientConfig_FP_T GsnHttpdApiConfig_SetValuesWepClientConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesWpaEnterpriseClientConfig_FP_T GsnHttpdApiConfig_SetValuesWpaEnterpriseClientConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesClientConfig_FP_T GsnHttpdApiConfig_SetValuesClientConfig_FP = NULL;



_RPST_ GsnHttpdApiConfig_SetValuesWpaPersonalApConfig_FP_T GsnHttpdApiConfig_SetValuesWpaPersonalApConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesAPConfig_FP_T GsnHttpdApiConfig_SetValuesAPConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesNetworkMode_FP_T GsnHttpdApiConfig_SetValuesNetworkMode_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesMacAddress_FP_T GsnHttpdApiConfig_SetValuesMacAddress_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesNetwork_FP_T GsnHttpdApiConfig_SetValuesNetwork_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesSysId_FP_T GsnHttpdApiConfig_SetValuesSysId_FP = NULL;

_RPST_ GsnHttpdApiConfig_SetValuesOtafu_FP_T GsnHttpdApiConfig_SetValuesOtafu_FP = NULL;


_RPST_ GsnHttpdApiConfig_GetValuesHttpd_FP_T GsnHttpdApiConfig_GetValuesHttpd_FP = NULL;


_RPST_ GsnHttpdApiConfig_GetValuesWpaEnterpriseConfig_FP_T GsnHttpdApiConfig_GetValuesWpaEnterpriseConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesClientConfig_FP_T GsnHttpdApiConfig_GetValuesClientConfig_FP = NULL;


_RPST_ GsnHttpdApiConfig_GetValuesAPConfig_FP_T GsnHttpdApiConfig_GetValuesAPConfig_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesNetworkMode_FP_T GsnHttpdApiConfig_GetValuesNetworkMode_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesRegDomain_FP_T GsnHttpdApiConfig_GetValuesRegDomain_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesMacAddress_FP_T GsnHttpdApiConfig_GetValuesMacAddress_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesNetwork_FP_T GsnHttpdApiConfig_GetValuesNetwork_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesSysId_FP_T GsnHttpdApiConfig_GetValuesSysId_FP = NULL;

_RPST_ GsnHttpdApiConfig_GetValuesOtafu_FP_T GsnHttpdApiConfig_GetValuesOtafu_FP = NULL;

_RPST_ GsnHttpdConfig_IsUriHandlerPresent_FP_T GsnHttpdConfig_IsUriHandlerPresent_FP = NULL;

_RPST_ config_network_cb_FP_T config_network_cb_FP = NULL;

_RPST_ GsnHttpdApi_ConfigInit_FP_T GsnHttpdApi_ConfigInit_FP = NULL;

_RPST_ GsnHttpdApi_ConfigDeInit_FP_T GsnHttpdApi_ConfigDeInit_FP = NULL;

