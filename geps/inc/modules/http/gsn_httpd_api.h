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
* $RCSfile: gsn_httpd_api.h,v
*/

#ifndef GSN_HTTPD_API_H_
#define GSN_HTTPD_API_H_

#include "modules/xml_parser/test/modules/gsn_xml.h"


#define GSN_HTTP_SYS_API_VERSION "1.0.0"
#define GSN_HTTP_SYS_API_PATH "/gainspan/system/api"
#define GSN_HTTP_SYS_API_NAME "gs_sys_prov"

typedef struct http_api_elem
{
    GSN_XML_STRING_T uri;
    GSN_XML_STRING_T methods;
    GSN_XML_STRING_T desc;
} http_api_elem_xml_t;

typedef struct http_api_xml
{
    http_api_elem_xml_t     http_api_elem;
} http_api_xml_t;

UINT8
GsnHttpdApi_ApiInit();

/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Initialize HTTP API module
 *    This function initializes the API module 
 * 
 ******************************************************************************/

VOID GsnHttpdApi_ApiDeInit();


#endif /* GSN_HTTPD_API_H_ */
