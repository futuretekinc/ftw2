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
* $RCSfile: gsn_httpd_api_util.c,v
*/

/*
 * gsn_httpd_xml_util.c
 *
 *  Created on: Aug 18, 2011
 *      Author: PViswanathan
 */

#include <stddef.h>
#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"
#include "modules/http/gsn_httpd_util.h"
#include "gsn_httpd_api_util_fpt.h"

void GsnHttpd_SetStrFromXmlStr(UINT8* str, GSN_XML_STRING_T xml_str, int str_len)
{
	if(GsnHttpd_SetStrFromXmlStr_FP)
	{
		(GsnHttpd_SetStrFromXmlStr_FP)(str, xml_str,str_len);
                return ;
	}
    memset(str, 0x0, str_len);
    if ((str_len > 0) && (xml_str.len > str_len))
        return;

    if (xml_str.ptr)
    {
        memcpy(str, xml_str.ptr, xml_str.len);
        str[xml_str.len] = 0;
    }
}




