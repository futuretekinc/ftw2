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
 * $RCSfile: app_httpd_cb.c,v $
 *
 * Description : s2w GEPS interface file
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_api.h"
#include "modules/mdns_sd/gsn_mdns.h"
#include "battery/app_batt_chk.h"

#ifdef ADK_PROV_ENABLE
#include "gsn_httpd_config.h"
#include "gsn_httpd_prov.h"
#endif

#include "modules/http/gsn_httpd_file_api.h"

#ifdef ADK_OTAFU_ENABLE
//#include "gsn_httpd_file_api.h"
#endif

#include "app_net_svcs_priv.h"
#include "api\api_safe.h"
#include "app_httpd_cb.h"
#include "app_debug.h" 
#include "app_main_ctx.h"
/* Compile time flags controlling application behavior */
#define APP_ASYNC_REBOOT

#define APP_CERT_MAX_NAME_LENGTH 	32
#define TAG_SSLCERT 				"SSLCERT"

UINT8  AppFileUploadStatus;
UINT32 AppFileuploadCnt;
F_FILE *certFd;



#ifdef APP_ASYNC_REBOOT

PRIVATE GSN_OSAL_THREAD_TCB_T rebootTask;

VOID App_RebootSoc(UINT32 ctx)
{
    GsnTaskSleep(1000);
    GsnSys_Reset(GSN_RESET_REASON_APP_SW_RESET);
}
#else
VOID App_RebootSoc(UINT32)
{
    GsnSys_Reset(GSN_RESET_REASON_APP_SW_RESET);
}

#endif

VOID App_Reboot(BOOL async)
{
#ifdef APP_ASYNC_REBOOT
    /* Rebooting in a separate thread
     * so that HTTP response can go from httpd to client.
     * FIXME: This however does NOT work
     */
    if (async)
    {
        UINT8* stack = (UINT8*) malloc(2048);
        if (stack)
        {
            GsnOsal_ThreadCreate(App_RebootSoc, NULL, &rebootTask,
                    (UINT8*) "rebootThread", APP_CFG_SYS_REBOOT_THREAD_PRIORITY,
                    stack, 2048, GSN_OSAL_THREAD_INITIAL_READY);
        }
        else
        {
            App_RebootSoc(0);
        }
    }
    else
    {
        App_RebootSoc(0);
    }

#else
    App_RebootSoc();
#endif
}

#ifdef ADK_PROV_ENABLE

PRIVATE VOID App_ApplySysConfig(GSN_SYS_CONFIG_T *pConfig)
{
    //UINT8 state;

    if (pConfig->sysConfigChangeApply)
    {
#ifdef APP_MDNS
            App_MdnsDeInit();
#endif
            App_Reboot(TRUE);
    }
}


extern GSN_NWIF_IP_CONFIG_T s_nwParams;
/*
 * Callback function for the /gainspan/config handler
 * It is up to the application to deal with the configuration.
 * This function further dispatches GET and POST
 * separately.
 */
VOID App_ConfigCb(GSN_SYS_CONFIG_T *pConfig, UINT8 method)
{
    AppDbg_Printf("[%s] Entered\r\n", __FUNCTION__);

    // TODO - Is this the correct place to do this? Revisit
    f_chdrive(0);

	/*copy the passed structure and store it in the flash memory*/
	if(method == GSN_HTTPD_URI_METHOD_GET)
	{
        AppConfig_Load(pConfig);
        pConfig->networkConfig.ipConfig.ipAddr = htonl(s_nwParams.ipv4.ipAddr);
	}

	if (method == GSN_HTTPD_URI_METHOD_POST)
	{
		AppConfig_Save(pConfig);
        /* Apply System configuration, if necesary */
        App_ApplySysConfig(pConfig);
	}

    // TODO - Is this the correct place to do this? Revisit
    f_chdrive(1);


	return;
}
#endif /* ADK_PROV_ENABLE */

#ifdef ADK_FILE_UPLOAD_API

BOOL
AppCertUpload_SslCertUploadCb(GSN_HTTPD_ELEMENT_INFO_T fileInfo, INT8 *buffer, 
	UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event, 
	GSN_HTTPD_STATUS_INFO_T *statusInfo)
{
	UINT8 len;
	INT8 tagName[APP_CERT_MAX_NAME_LENGTH+8];
	INT32 status;
	AppDbg_Printf("\n\rIn file upload CB: %x\n\r", event);
	switch(event)
	{
		case START_UPLOAD:
			AppFileUploadStatus=0;
			AppFileuploadCnt=0;
			break;
		case START_FILE:
			AppDbg_Printf("TagNameLen: %d", fileInfo.nameLen);
			if(fileInfo.nameLen)
			{
				f_chdrive(0);	
				status = f_mkdir("certs");
				memset(tagName, 0, APP_CERT_MAX_NAME_LENGTH+8);
				if(status != F_NO_ERROR || status != F_ERR_DUPLICATED )
				{
					if(strncmp(fileInfo.name,TAG_SSLCERT,fileInfo.nameLen) == 0)
					{
						if(fileInfo.filenameLen > APP_CERT_MAX_NAME_LENGTH)
							fileInfo.filenameLen = APP_CERT_MAX_NAME_LENGTH-1;
												
						len= sprintf(tagName,"certs/");
						memcpy(tagName + len, fileInfo.filename, fileInfo.filenameLen);
						certFd= f_open((const char *)tagName, "w");
					}
					else /*EAP Certificates*/
					{
						len= sprintf(tagName,"certs/");
						memcpy(tagName + len, fileInfo.filename, fileInfo.filenameLen);
						certFd= f_open((const char *)tagName, "w");
					}
					if(certFd == NULL)
					{				
						f_chdrive(1);	
						AppFileUploadStatus = 1;
						return 0;
					}
					AppFileuploadCnt++;
				}
				else
					AppFileUploadStatus = 1;
				
				f_chdrive(1);	
				AppDbg_Printf("\r\nFile Name is = %s:%d \r\n", tagName,fileInfo.filenameLen);
			}
			break;
		case CONTINUE_FILE:
			AppDbg_Printf("\r\nBufferLength=%d\r\n",bufferLen);
			f_chdrive(0);	
			if(certFd != NULL)
			{
				len = f_write(buffer, 1, bufferLen , certFd);
				if(len != bufferLen)
					AppFileUploadStatus = 1;	
			}
			f_chdrive(1);	
			break;
		case END_FILE:
			f_chdrive(0);
			if(certFd != NULL)
			{
				f_close(certFd);
			}
			f_chdrive(1);	
			break;
		case END_UPLOAD:
			AppDbg_Printf("END UPLOAD:%d\n\r",AppFileUploadStatus);
			if(AppFileUploadStatus != 0)
			{
				sprintf(statusInfo->pMsg,"<Response><status>SUCCESS</status><msg>");
				statusInfo->msgLength =	sprintf(statusInfo->pMsg, "%s %d files Uploaded</msg></Response>", \
										statusInfo->pMsg, AppFileuploadCnt);
			}
			else
			{
				sprintf(statusInfo->pMsg,"<Response><status>FAILED</status><msg>");
				statusInfo->msgLength =	sprintf(statusInfo->pMsg, "%s %d file Uploaded</msg></Response>",\
										statusInfo->pMsg, AppFileuploadCnt);
			}
			AppFileuploadCnt=0;
			break;
		case CONNEC_LOST:
			AppDbg_Printf("END CONNEC_LOST\n\r");
			break;
	}
	
	return 0;
}

#endif /* ADK_FILE_UPLOAD_API */
