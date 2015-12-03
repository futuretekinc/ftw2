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
* $RCSfile: gsn_dsv_httpd.c,v $
*
* Description : s2w GEPS interface file
*******************************************************************************/


/*******************************************************************************
 * File Inclusions
 ******************************************************************************/

#if 1//def GSN_WEB_SERVER

#include <stddef.h>
#include "gsn_includes.h"
//#include "modules/xml_parser/gsn_xml.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
#include "modules/http/gsn_httpd_debug.h"
#include "modules/http/gsn_httpd_api.h"
#include "gsn_dsv_httpd.h"


GSN_HTTPD_STATUS_T
GsnDsvHttpd_Cb(ttHttpdUserEvent event, const char* uri, ttHttpdUserConHandle conHandle)
{
   	INT32 respLen = 0;
	int errorCode;

    INT8  *buffer = GsnHttpd_GetBuffer();
	if(buffer == NULL)
		return GSN_HTTPD_FAILURE;

	if (GsnHttpd_GetHttpMethod(conHandle) == TM_HTTP_METHOD_POST)
	{
		sprintf(buffer, "<error>POST not allowed</error>");
		GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer), TM_BLOCKING_ON, &errorCode);
		return GSN_HTTPD_SUCCESS;
	}

	switch (event)
	{
		case TM_HTTPD_EVENT_BODY_RECV:
			break;
		case TM_HTTPD_EVENT_SEND_READY:
		    if (!strcmp(uri, GSN_OTAFU_HTTP_SYS_API_PATH))
		    {
		        sprintf(buffer, "<fwupconfig><dsv>enable</dsv></fwupconfig>");
		        respLen =  strlen(buffer);
		    }
            GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, respLen, TM_BLOCKING_ON,
                    &errorCode);
			break;
	}
	if(NULL != buffer)
		GsnHttpd_ReleaseBuffer(buffer);
	return GSN_HTTPD_SUCCESS;
}


UINT8
GsnDsvHttpd_Init()
{
	GsnHttpd_UriHandlerConfig(GSN_OTAFU_HTTP_SYS_API_PATH, GSN_HTTPD_URI_METHOD_GET, "OTAFU Configuration", GsnDsvHttpd_Cb, GSN_HTTPD_CONTENT_APP_XML);

    return 0;
}

VOID
GsnDsvHttpd_DeInit()
{
	//GsnHttpd_UriHandlerConfig(GSN_OTAFU_HTTP_SYS_API_PATH, 0, NULL, NULL, 0);

}

#endif // GSN_WEB_SERVER

