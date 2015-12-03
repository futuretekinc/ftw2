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
* $RCSfile: gsn_httpd_api_util.c,v
*/

#ifndef _GSN_HTTPD_API_UTIL_FPT_H_
#define _GSN_HTTPD_API_UTIL_FPT_H_

#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"
typedef PUBLIC VOID
(* GsnHttpd_SetStrFromXmlStr_FP_T)(UINT8* str, GSN_XML_STRING_T xml_str, int str_len);
extern _RPST_  GsnHttpd_SetStrFromXmlStr_FP_T GsnHttpd_SetStrFromXmlStr_FP;

#endif
