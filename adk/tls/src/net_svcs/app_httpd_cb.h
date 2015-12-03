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
* $RCSfile: app_httpd_cb.h,v
*/

#ifndef APP_HTTPD_CB_H_
#define APP_HTTPD_CB_H_


#ifdef ADK_PROV_ENABLE

void AppWps_CbFn(char* mode, char* pin);
VOID App_ConfigCb(GSN_SYS_CONFIG_T *pConfig, UINT8 method);

#endif

BOOL AppCertUpload_SslCertUploadCb(GSN_HTTPD_ELEMENT_INFO_T fileInfo, INT8 *buffer, 
				UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event,
				GSN_HTTPD_STATUS_INFO_T *statusInfo);

#endif /* APP_HTTPD_CB_H_ */
