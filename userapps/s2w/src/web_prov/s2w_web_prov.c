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
* $RCSfile: s2w_web_prov.c,v $
*
* Description : s2w GEPS interface file
*******************************************************************************/
#include "gsn_includes.h"
#include "main/app_main_ctx.h"
#include "S2w_process.h"
#include "config/app_resource_config.h"
#ifdef S2W_WEB_PROV

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_api.h"
#include "app_rtc_mem.h"

//#include <trsocket.h>
//#include <trmacro.h>

//#include <trtype.h>
//#include <trproto.h>
//#include <trglobal.h>



#include <string.h>


#include "hal/s2w.h"

#if 1
#include "modules/http/gsn_httpd.h"
//#include "hal\s2w_types.h"
#include "modules/xml_string_parser/gsn_xml_string_parser.h"
#endif
   
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "parser/s2w_process.h"
#include "hal/s2w_timer.h"
#include "hal/s2w_net.h"
#include "hal/s2w_config.h"
#include "hal/s2w_cert_mgmt.h"
#include "main/app_main_ctx.h"
#include "s2w_web_prov.h"
#include "config/app_httpd_config.h"
#include "config/app_ncm_config.h"
#include "html/app_http_fs.h"
#include "fs/api/api_safe.h"

#if 1
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_file_api.h"
#include "gsn_httpd_config.h"
#include "gsn_httpd_prov.h"
   

#include "modules/http/gsn_httpd_logo.h"
//#include "modules/http/gsn_httpd_fw.h"
#include "modules/http/gsn_httpd_file_api.h"
#endif

#include "config/app_httpd_config.h"
#include "app_mib.h"

#include "gsn_sys_config.h"


#include "web_prov\s2w_web_prov.h"
#ifdef ADK_PROV
static UINT8 prePoplnDone = 0;
#endif


/* Define this to test SSL server with the test certificate. Make sure the 
   node IP address is kept 192.168.1.99 */
//#define S2W_SSL_SERVER_TEST
#ifdef S2W_SSL_SERVER_TEST
extern const UINT8 server_key[610];
extern const UINT8 server_cert[1001];
extern const UINT8 ca_cert[1391];
#endif
//TODO:::::
//extern UINT8 webProvFlag;
extern S2W_PROFILE_T s2wCurrent;
//extern S2W_WLANINFO_T current_wlan_info;
extern PUBLIC UINT8 *pS2wHttpdTaskStack;
extern S2W_SSL_CERT_SRAM_TABLE_T s2w_ssl_cert_table[S2W_MAX_NUM_CERT];
extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;
//#define WEB_DEBUG

#ifdef WEB_DEBUG
#define webPrintf S2w_Printf
#else
#define webPrintf(...)
#endif

#ifdef S2W_FILE_UPLOAD_API
#define GSN_SSLCERTUPLOAD_URI   "/gainspan/system/sslcertupload"
#define TAG_SSLCERT 			"SSLCERT"
#endif
/**
 *******************************************************************************
 * @file s2w_web_prov.c
 * @brief S2W Application geps interface routines.
 *      This file contains the s2w application specific implimentation which
 *      Interface the s2w command processing network stack.
 ******************************************************************************/
/*******************************************************************************
 *  Private Variables
 ******************************************************************************/
//#define S2W_STACK_ALLOC_STATIC



/*******************************************************************************
 *  Extern Variables
 ******************************************************************************/
UINT8 storeParams = 0;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

extern UINT8 s2wNetRecvTaskStack[APP_CFG_NET_RX_STACK_SIZE];
//extern S2W_MIB_PROFILE_T s2wProfileParm;
S2W_MIB_PROFILE_T s2wProfileParm;
#ifdef TRROM_FILE_SYS
extern void
tfRomFsInit(ttRomFilePtr romFile, tt16Bit romPageSize,
                 tt16Bit romPages, tt16Bit romFiles);
#endif

#ifdef S2W_FILE_UPLOAD_API
extern BOOL S2wFileUpload_FwupCb(GSN_HTTPD_ELEMENT_INFO_T fileInfo, INT8 *buffer, 
		UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event, 
		GSN_HTTPD_STATUS_INFO_T *statusMsg);
#endif

extern VOID
GsnHttpd_FileApiDeInit();
extern VOID GsnHttpdApi_LogoDeInit();
extern VOID GsnHttpdApi_FwDeInit();

/*******************************************************************************
 *  Private Definitions
 ******************************************************************************/
//#define LOGO_AND_FACT_DFLT_SETNG_PAGE_START   (GSN_FLASH1_BASE_ADDRESS + (122*1024))

//#define LOGO_LOCATION (GSN_FLASH1_BASE_ADDRESS + (122*1024)+256)

/*******************************************************************************
 *  Private Inline Functions
 ******************************************************************************/

#ifdef ADK_PROV
PRIVATE VOID
S2wWeb_Config(GSN_SYS_CONFIG_T *pConfig, UINT8 method);
/* Put Values into */
PRIVATE VOID
S2wConfig_SetValues(GSN_SYS_CONFIG_T *pConfig);

/* Get Values from  */
PRIVATE VOID
S2wConfig_GetValues(GSN_SYS_CONFIG_T *pConfig);

#endif
#if S2W_HTTPD_DATE_CONFIG
GSN_HTTPD_STATUS_T 
AppS2w_configTimecb(ttHttpdUserEvent event, const char* uri,ttHttpdUserConHandle conHandle); 
#endif					
#ifdef S2W_HTTPD_SSLCERT_UPLOAD											
GSN_HTTPD_STATUS_T 
AppS2w_SslCertcb(ttHttpdUserEvent event, const char* uri,ttHttpdUserConHandle conHandle);
#endif
/*******************************************************************************
 *  Public Functions
 ******************************************************************************/
#ifdef  S2W_FILE_UPLOAD_API

F_FILE *fd; 


//UINT8 *certName;
#define S2W_CERT_MAX_NAME_LENGTH 32
BOOL
S2wWebProv_FileUploadCb(GSN_HTTPD_ELEMENT_INFO_T fileInfo, INT8 *buffer, 
	UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event, 
	GSN_HTTPD_STATUS_INFO_T *statusInfo)
{
	UINT8 tagName[S2W_CERT_MAX_NAME_LENGTH+16];
	INT32 status, len;
	webPrintf("\n\rIn file upload CB: %x\n\r", event);
	memset(tagName, 0, S2W_CERT_MAX_NAME_LENGTH+16);
	switch(event)
	{
		case START_UPLOAD:
			s2wappMainTaskCtxt->fileOperationStatus=0;
			s2wappMainTaskCtxt->fileuploadCnt=0;
			break;
		case START_FILE:
			webPrintf("TagNameLen: %d", fileInfo.nameLen);
			if(fileInfo.nameLen)
			{
				status = f_mkdir("A:/certs");
				memset(tagName, 0, S2W_CERT_MAX_NAME_LENGTH+8);
				if(status == F_NO_ERROR || status == F_ERR_DUPLICATED )
				{
					if(strncmp(fileInfo.name,TAG_SSLCERT,fileInfo.nameLen) == 0)
					{
						if(fileInfo.filenameLen > S2W_CERT_MAX_NAME_LENGTH)
							fileInfo.filenameLen = S2W_CERT_MAX_NAME_LENGTH-1;
												
								len= sprintf((char*)tagName,"A:/certs/");
							memcpy(tagName + len, fileInfo.filename, fileInfo.filenameLen);
							fd= f_open((const char *)tagName, "w");
					}
					else /*EAP Certificates*/
					{
								len= sprintf((char*)tagName,"A:/certs/");
							memcpy(tagName + len, fileInfo.name, fileInfo.nameLen);
							fd= f_open((const char *)tagName, "w");
					}
					if(fd == NULL)
					{				
						s2wappMainTaskCtxt->fileOperationStatus = 1;
						return 0;
					}
					s2wappMainTaskCtxt->fileuploadCnt++;
				}
				else
				{
					s2wappMainTaskCtxt->fileOperationStatus = 1;
				}
				webPrintf("\r\nFile Name is = %s:%d \r\n", tagName,fileInfo.filenameLen);
			}
			break;
		case CONTINUE_FILE:
			webPrintf("\r\nBufferLength=%d\r\n",bufferLen);
			if(fd != NULL)
			{
				len = f_write(buffer, 1, bufferLen , fd);
				if(len != bufferLen)
					s2wappMainTaskCtxt->fileOperationStatus = 1;	
			}
#ifdef WEB_DEBUG			
            UINT32 index=0;
			while(bufferLen)
			{
				webPrintf("%02x",buffer[index++]);
				bufferLen--;
			};
#endif			
			break;
		case END_FILE:
		{
			if(fd!= NULL)
							{
				f_close(fd);

					}

			if(strcmp((const char *)tagName,S2W_CERT_NAME_CA) == 0)
			{
				s2wCurrent.security.eap.useCaCert = 1;
			}
			break;
		}
		case END_UPLOAD:
			
			webPrintf("END UPLOAD:%d\n\r",s2wappMainTaskCtxt->fileOperationStatus);
			if(s2wappMainTaskCtxt->fileOperationStatus == 0)
			{
			sprintf(statusInfo->pMsg,"<Response><status>SUCCESS</status><msg>");
				statusInfo->msgLength =	sprintf(statusInfo->pMsg, "%s %d files Uploaded</msg></Response>", \
										statusInfo->pMsg, s2wappMainTaskCtxt->fileuploadCnt);
			}
			else
			{
				sprintf(statusInfo->pMsg,"<Response><status>FAILED</status><msg>");
				statusInfo->msgLength =	sprintf(statusInfo->pMsg, "%s %d file Uploaded</msg></Response>",\
										statusInfo->pMsg, s2wappMainTaskCtxt->fileuploadCnt);
			}
			s2wappMainTaskCtxt->fileuploadCnt=0;
			break;
		case CONNEC_LOST:
#ifdef WEB_DEBUG			
			webPrintf("END CONNEC_LOST\n\r");
#endif			
			break;
	}
return 0;
}
#endif

#ifdef ADK_PROV

#ifdef S2W_SECURITY_WPS_ENABLE
#define APP_WPS_TYPE_PB 1
#define APP_WPS_TYPE_PIN 2
VOID 
S2wWebProv_WpsCbFn(char* mode, char* pin)
{
    UINT8 i, wpsPin[GSN_WDD_SEC_WPS_PIN_LEN];
    UINT8* p = &wpsPin[0];
	UINT32 message;

	memset((INT8 *)&s2wappMainTaskCtxt->wpsapSsid, 0, sizeof(s2wappMainTaskCtxt->wpsapSsid));
    if (!strcmp(mode, "pbc"))
    {
        //S2w_Printf("[tlswebapp] WPS PBC method requested\r\n");
	  memset(s2wappMainTaskCtxt->wpsParams.pin,0x00,GSN_WDD_SEC_WPS_PIN_LEN);
      webPrintf("[tlswebapp] WPS PBC method requested\r\n");
		s2wappMainTaskCtxt->wpsParams.type = APP_WPS_TYPE_PB;
    }
    else if (!strcmp(mode, "pin"))
    {
        webPrintf("[tlswebapp]  WPS PIN method requested %s\r\n",pin);
        //S2w_Printf("[tlswebapp] WPS PIN method requested %s\r\n", pin);
		s2wappMainTaskCtxt->wpsParams.type = APP_WPS_TYPE_PIN;
        if (GSN_WDD_SEC_WPS_PIN_LEN != strlen((const char*) pin))
        {
            return;
        }
        for (i = 0; i < GSN_WDD_SEC_WPS_PIN_LEN; i++)
        {
            if (*(pin + i) < '0' || *(pin + i) > '9')
            {
                return;
            }
            //*(p + i) = *(pin + i) - '0'; /* convert to integer */
            *(p+i)= *(pin+i);
        }
        memcpy(s2wappMainTaskCtxt->wpsParams.pin, p, GSN_WDD_SEC_WPS_PIN_LEN);
    }

	/*500 ms delay to complete the post response*/
	GsnTaskSleep(500);
	if(S2W_WEB_PARAMS_STORE == 	storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
		s2wappMainTaskCtxt->wpsParams.storeL2ConInfo=TRUE;
	else
		s2wappMainTaskCtxt->wpsParams.storeL2ConInfo=FALSE;
	
	message = APP_NOTIFICATION_WPS_START;
	(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);

	   /* reboot */
			
}
#endif
#endif /* #ifdef ADK_PROV */

PUBLIC VOID
S2wWebProv_WebProvStop()
{
#ifdef ADK_PROV
    GsnHttpdApi_ConfigDeInit();
    GsnHttpdApi_ProvDeInit();
#endif

#ifdef S2W_HTTPD_DATE_CONFIG
	GsnHttpd_UriHandlerConfig("/gainspan/system/time", 0, NULL, NULL, 0);
#endif
#ifdef S2W_HTTPD_SSLCERT_UPLOAD
	GsnHttpd_UriHandlerConfig("/gainspan/system/sslcerts", 0, NULL, NULL, 0);
#endif

    GsnHttpdApi_ApiDeInit();
#ifdef S2W_WEB_SRVR_LOGO_INTRNL_FLASH
    GsnHttpdApi_LogoDeInit(App_LogoInfoCb);
#endif
    GsnHttpdApi_FwDeInit();
#ifdef S2W_FILE_UPLOAD_API
	GsnHttpd_FileApiDeInit();
#endif
     //webProvFlag = 0;
	s2wappMainTaskCtxt->webProvStatus = IDLE;
#ifdef ADK_PROV
	prePoplnDone=0;
#endif

}

extern GSN_NW_PKT_POOL_HANDLE   trPktPoolHndl;
extern void                    *s2wHttpdPktPtr;
#define S2W_HTTPD_PKT_POOL  (32*1024)
PUBLIC VOID
S2wWebProv_WebProvStart()
{
   	INT8 httpdStatus;
    
    GSN_HTTPD_CONFIG_T config;
    UINT32  index, certLength, wlanVer;
    GSN_NWIF_IP_CONFIG_T nwParams;
    //GSN_STATUS ret;
#ifdef ADK_PROV 
    GSN_HTTPD_PROV_CONFIG_T provConfig;
#endif
    
    //char ipAddrStr[16];
    SERVER_CERT_DETAIL_T certDetail, *pCertDtl = NULL;
	
	if(TRUE == GsnHttpd_IsRunning())
	{
		goto WebProvUriRegister;
	}
    (VOID)pCertDtl;
	//memset((INT8 *)&certDetail, 0, sizeof(certDetail));
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
    if( s2wappMainTaskCtxt->WebServerCfg.sslEnabled )
    {
        pCertDtl = &certDetail;

#ifndef S2W_SSL_SERVER_TEST
        index = S2wCert_SearchRamTable(S2W_SSL_CERT_NAME_CA);
		 if(index == -1)
        {
			 index = S2wCert_FlashFileLoad(S2W_SSL_CERT_NAME_CA);
		 }
		 if(index == -1)
		 {
			 s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
			 S2w_Printf("\n\rCertificate %s Not Found", S2W_SSL_CERT_NAME_CA);
			 goto WebProvStartExit;
		 }
		 certDetail.CaCertName = (char const *)s2w_ssl_cert_table[index].name;
            certDetail.CaCertLocation = s2w_ssl_cert_table[index].certAddress + 2;        
            certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
            certLength <<= 8;
            certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
            certDetail.CaCertLen = certLength;
		/* CA certificate is optional*/
        /*else return retVal; */
        
        index = S2wCert_SearchRamTable(S2W_SSL_CERT_NAME_SERVER);
		 if(index == -1)
        {
			 index = S2wCert_FlashFileLoad(S2W_SSL_CERT_NAME_SERVER);
		 }
		 if(index == -1)
		 {
			 s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
			 S2w_Printf("\n\rCertificate %s Not Found", S2W_SSL_CERT_NAME_SERVER);
			 goto WebProvStartExit;
		 }
		 certDetail.ClientCertName = (const char *)s2w_ssl_cert_table[index].name;
            certDetail.ClientCertLocation = s2w_ssl_cert_table[index].certAddress + 2;        
            certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
            certLength <<= 8;
            certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
            certDetail.ClientCertLen = certLength;
		 index = S2wCert_SearchRamTable(S2W_SSL_CERT_NAME_KEY);
		 if(index == -1)
		 {
			 index = S2wCert_FlashFileLoad(S2W_SSL_CERT_NAME_KEY);
        }
		 if(index == -1)
        {      	
			s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
			 S2w_Printf("\n\rCertificate %s Not Found", S2W_SSL_CERT_NAME_KEY);
			goto WebProvStartExit;
        }
		 certDetail.PrivateKeyName = (const char *)s2w_ssl_cert_table[index].name;
            certDetail.PrivateKeyLocation = s2w_ssl_cert_table[index].certAddress + 2;        
            certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
            certLength <<= 8;
            certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
            certDetail.PrivateKeyLen = certLength;
 
#else
//#else
        certDetail.CaCertName = "ca_cert.crt";
        certDetail.CaCertLocation = ca_cert;
        certDetail.CaCertLen = sizeof(ca_cert);
        certDetail.ClientCertName = "server_cert.crt";
        certDetail.ClientCertLocation = server_cert;
        certDetail.ClientCertLen = sizeof(server_cert);    
        certDetail.PrivateKeyName = "server_key.key";
        certDetail.PrivateKeyLocation = server_key;
        certDetail.PrivateKeyLen = sizeof(server_key);
#endif
    }
	storeParams = s2wappMainTaskCtxt->WebServerCfg.storeParams;
    /* we will be sharing the stack with n/w receive task */
    /*GsnOsal_ThreadDelete(&s2wappMainTaskCtxt->s2wNetRxTask);*/

    /* get the ip information by calling geps API */
    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx, &nwParams);
    //inet_ntop(AF_INET, &nwParams.ipv4.ipAddr, ipAddrStr, sizeof(ipAddrStr));
#ifdef TRROM_FILE_SYS
    /* initialise the Rom File System that contains Welcome Page*/
    tfRomFsInit(tlRomFile, tlRomPageSize, tlRomPages, tlRomFiles);
#endif

    /* Initialize web parameters */
    memset(&config, 0, sizeof(GSN_HTTPD_CONFIG_T));

    /* store user mane and passwd*/
    strcpy(config.username, s2wappMainTaskCtxt->WebServerCfg.username);
    strcpy(config.password, s2wappMainTaskCtxt->WebServerCfg.passwd);
    config.port = APP_HTTPD_PORT;
    config.maxConnPerIp = APP_HTTPD_MAX_PER_IP_CONN;
    config.maxConnTotal = APP_HTTPD_MAX_TOTAL_CONN;
    config.blockingState = APP_HTTPD_BLOCKING_STATE;
    config.threadPriority = APP_HTTPD_THREAD_PRIORITY;
    config.idleTimeout = APP_HTTPD_IDLE_TIMEOUT;
	config.sysQualTskID = APP_CFG_SQ_HTTPD_TASK_ID;
	config.sysQualTicks = APP_CFG_SQ_TICKS_FOR_HTTPD_TASK;
	if(0 != s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut)
	{
		config.idleTimeout = s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut;
	}


#ifdef USE_V6
    //memcpy(config.ipAddr, (const INT8 *)nwParams.ipv6.linkLocalAddr, 16);
	config.ip_flag = GSN_USE_IPV6;
    memcpy(config.ipAddr6, s2wappMainTaskCtxt->if0.nwifCtx.ipHndl.nx_ip_interface[0].nxd_interface_ipv6_address_list_head->nxd_ipv6_address_next->nxd_ipv6_address, 16);
#else
    config.ip_flag = GSN_USE_IPV4;
    config.ipAddr = nwParams.ipv4.ipAddr;
#endif
    config.rootCgiDir = NULL;
    config.rootDir = "/";
    config.defaultFileName = "index.html";
	config.mallocTimeout = 2 *1000; /* 2 Sec. */

    config.stack = S2wApp_WebserverStack_Get(s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
	 pS2wHttpdTaskStack = config.stack;
	 if(NULL == config.stack)
	{
		s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
		goto WebProvStartExit;
     
	}
    config.stackSize  = S2wApp_WebserverStackSize_Get(s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
    //config.pWdd = &s2wappMainTaskCtxt->wdd;

    //config.pool_hdl = trPktPoolHndl;//&(s2wappMainTaskCtxt->nwCtx.trPktPoolHndl);
    //config.pool_hdl = &(s2wappMainTaskCtxt->nwCtx.trPktPoolHndl);
    /* Initialize web parameters */
    //memset(&trPktPoolHndl, 0, sizeof(trPktPoolHndl));
    /* TODO: need to check proper place to free this buffer */
#if 1

    config.pool_hdl = GsnNw_PktPoolHndlGet(&s2wappMainTaskCtxt->nwCtx, GSN_NW_LBUF_PKT_POOL);
#endif


    config.mallocTimeout = 2 *1000; /* 2 Sec. */
    /* Start httpd */
    httpdStatus = GsnHttpd_Start(config ,pCertDtl  );
	if(httpdStatus == GSN_HTTPD_FAILURE)
	{
        S2wApp_WebserverStack_Free(config.stack);
		pS2wHttpdTaskStack = NULL;
#ifdef  S2W_NCM_SUPPORT_ENABLE
		s2wappMainTaskCtxt->ncmAutoConEn = 0;
#endif
		s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
		goto WebProvStartExit;
	}
WebProvUriRegister:

#ifdef ADK_PROV
    /* System Configuration URI Handler  */
    GsnHttpdApi_ConfigInit(S2wWeb_Config);

    /* Scan Configuration URI Handler */
    memset(&provConfig, 0x0, sizeof(provConfig));
  //  provConfig.pWdd = &(s2wappMainTaskCtxt->wdd);
    //AppCfg_Get( APP_CFG_REG_DOMAIN_ID, &regDomain);
    provConfig.domain = (GSN_WLAN_REG_DOMAIN_T)s2wCurrent.regDomain;
	provConfig.pWdd = &s2wappMainTaskCtxt->if0.wddCtx;
#ifdef S2W_SECURITY_WPS_ENABLE
    provConfig.pWpsCbFn = (GSN_HTTPD_PROV_WPS_CB_FN_T) S2wWebProv_WpsCbFn;
#endif
    GsnHttpdApi_ProvInit(&provConfig);
#endif

#ifdef S2W_HTTPD_DATE_CONFIG
		GsnHttpd_UriHandlerConfig("/gainspan/system/time", GSN_HTTPD_URI_METHOD_GET_POST,
			"Date/Time Configuration", AppS2w_configTimecb, GSN_HTTPD_CONTENT_APP_XML);
#endif
#ifdef S2W_HTTPD_SSLCERT_UPLOAD
		GsnHttpd_UriHandlerConfig("/gainspan/system/certs", GSN_HTTPD_URI_METHOD_GET_POST,
			"SSL Certificate Configuration", AppS2w_SslCertcb, GSN_HTTPD_CONTENT_APP_XML);
#endif
    /* API Configuration URI Handler */
    GsnHttpdApi_ApiInit();
   // tfHttpdUserSendFile (1,"/html.html",0);
#ifdef S2W_WEB_SRVR_LOGO_INTRNL_FLASH
    /* Logo Configuration URI Handler*/
    GsnHttpdApi_LogoInit(App_LogoInfoCb);
#endif
    /* Initiailze version handlers */
 	GsnSysCtl_WlanFwVerGet(&s2wappMainTaskCtxt->sysCtlCtx,&wlanVer);
    GsnHttpdApi_FwInit(wlanVer, S2W_SW_VERSION);//S2W_BUILD_VERSION);




#ifdef S2W_FILE_UPLOAD_API
	GsnHttpd_FileApiInit();
	/* Register URI handler for certificate upload. */
	GsnHttpd_FileApiConfig("/gainspan/system/wpacertupload", S2wWebProv_FileUploadCb, GSN_HTTPD_URI_METHOD_POST);
	GsnHttpd_FileApiConfig(GSN_SSLCERTUPLOAD_URI, S2wWebProv_FileUploadCb, GSN_HTTPD_URI_METHOD_POST);	
#ifdef S2W_EXT_FLASH_FWUP_PUSH_METHOD
#ifdef ADK_OTAFU
	/* Register URI handler for external flash firmware update */
	//GsnHttpd_FileApiConfig("/gainspan/system/fwuploc", S2wFileUpload_FwupCb, GSN_HTTPD_URI_METHOD_POST);
	AppOtafu_Init(s2wappMainTaskCtxt);
	AppExtOtafu_Init(s2wappMainTaskCtxt);

#endif
#endif
#endif	
   // webProvFlag = 1;
#ifdef S2W_WEB_PROV
	s2wappMainTaskCtxt->webProvStatus= RUNNING;	
#endif
	s2wappMainTaskCtxt->WebServerCfg.status =S2W_SUCCESS;
WebProvStartExit:	
	GsnOsal_SemRelease(&s2wappMainTaskCtxt->webServerSync);
	// flush the data for spi-dma interface
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }

}
//#endif
#ifdef S2W_WEB_SRVR_LOGO_INTRNL_FLASH
PUBLIC UINT32
S2wWebProv_webLogoStore(UINT8 *pLogo, UINT32 logoLen)
{
   UINT8 *p = (UINT8 *)GSN_FACT_DFLT_START_ADDR;
   UINT32 tempLen;
   UINT32 tempBuff[8];/* 32 bytes buffer*/
   UINT32 *factryDfltSetngs;

   if(logoLen > (2044-256))/*2048 - 4: 4 bytes for file length*/
   {
        return S2W_FAILURE;
   }
   
   factryDfltSetngs = (UINT32 *)gsn_malloc(256);
   
   if(NULL == factryDfltSetngs)
   {
       return S2W_FAILURE;
   }
   /* copy factory default settings before erasing the flash*/
   memcpy((UINT8 *)factryDfltSetngs, p, 256);
   GsnFlash_Erase(p, 2000, 0);
   /* write factory default setting back to flash*/
   GsnFlash_Write((UINT32 *)p, factryDfltSetngs, 256, 0);
   
   gsn_free(factryDfltSetngs);

   p = (UINT8 *)GSN_FACT_DFLT_LOGO_ADDR;
   GsnFlash_SingleWordWrite((UINT32 *)p, logoLen, 0);
   p += sizeof(UINT32);

   tempLen = 0;
   while(logoLen)
    {
        memset(tempBuff, 0, sizeof(tempBuff));
        tempLen = sizeof(tempBuff);
        if(tempLen > logoLen)
        {
           tempLen =  logoLen;
        }
        memcpy((UINT8 *)tempBuff, pLogo, tempLen);
        
        GsnFlash_Write((UINT32 *)p, tempBuff, tempLen, 0);

        pLogo += tempLen;
        p += tempLen;
        logoLen -= tempLen;        
    }
   return S2W_SUCCESS;
}
#endif

#ifdef S2W_HTTPD_SSLCERT_UPLOAD

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process extract SSL certificate name. 
 *   This function gets the certificate name from URI.
  * @param uri        pointer to to current URI
 * @return certName Pointer to certificate name .
 ******************************************************************/
UINT8 * 
AppS2w_CertNameGet(UINT8 *uri)
{
	UINT32 len;
	UINT8 *certName=NULL;
	len = strlen((const char *)uri);
	webPrintf("\r\n URI:%s:%d",uri,len);
	while(len)
	{	
		if(uri[len] == '/')
		{
			certName = (UINT8 *)uri + len + 1;
			break;
		}
		len--;
	}
	webPrintf("\r\n certname:%s",certName);
	return certName;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process SSL certificate view/delete URI call back. 
 *   This function get/delete the certificate loaded basesd on the method. 
 * @param event 	ttHttpdUserEvent. 		   						
 * @param uri        pointer to current URI
 * @param conHandle  Connection handler
 * @return o  - operation successful.
 * @retval -1  - operation failure-cerificate deletion failed.
 ******************************************************************/
GSN_HTTPD_STATUS_T 
AppS2w_SslCertcb(ttHttpdUserEvent event, const char* uri,
										  ttHttpdUserConHandle conHandle)
{
 	int errorCode;
    UINT32 bufferLen=0;
   
	UINT8* certName;
	F_FIND find;
	INT8* buffer = (INT8 *)GsnHttpd_GetBuffer();	
	if (!buffer)
		  return GSN_HTTPD_FAILURE;
	webPrintf("\r\n AppS2w_SslCertcb:%d",event);
    switch (event)
	{
		case TM_HTTPD_EVENT_ALL_RECV:
		{
			if (GsnHttpd_GetHttpMethod(conHandle) ==  TM_HTTP_METHOD_POST)
        	{
			bufferLen = TM_BODY_BUFFER_LEN;
			tfHttpdUserGetRequestBody(conHandle, buffer, (ttUserIntPtr)&bufferLen ,0);
			certName = AppS2w_CertNameGet((UINT8 *)uri);
				if(certName != NULL)
					s2wappMainTaskCtxt->fileOperationStatus = AppS2w_CertDelete(certName);			
			if(strcmp((const char*)certName,S2W_CERT_NAME_CA) == 0) 			
			{
				s2wCurrent.security.eap.useCaCert=0;			
				}
			}
			webPrintf("\r\n STAT:%d",s2wappMainTaskCtxt->fileOperationStatus);
		}
		break;
        case TM_HTTPD_EVENT_SEND_READY:
		{
        	if (GsnHttpd_GetHttpMethod(conHandle) == TM_HTTP_METHOD_GET)
            {
            	bufferLen = sprintf(buffer,"<certs>");	
				if (!f_findfirst("A:/certs/*.*",&find)) 
				{
				do
				{							
						webPrintf ("filename:%s",find.filename);
						if(find.filename != NULL &&
							(strncmp(find.filename , ".",strlen(find.filename))!=0) && 
							(strncmp(find.filename , "..",strlen(find.filename))!=0))
					{
							bufferLen += sprintf((buffer+bufferLen),"<cert><name>%s</name></cert>",find.filename);
						}
					} while (!f_findnext(&find));
					}
				bufferLen += sprintf((buffer+bufferLen),"</certs>");
        	}
            else
            {
            	if(s2wappMainTaskCtxt->fileOperationStatus == S2W_SUCCESS)
                	bufferLen = sprintf(buffer, "<status>ok</status>");
				else
					bufferLen = sprintf(buffer, "<status>error</status>");
            }
            GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, bufferLen, TM_BLOCKING_ON, &errorCode);
		}
		break;
    }
    if (buffer)
    {
    	GsnHttpd_ReleaseBuffer(buffer);
    	buffer = NULL;
    }
	return GSN_HTTPD_SUCCESS;
}
#endif

#ifdef S2W_HTTPD_DATE_CONFIG
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process extract time from the http body . 
 *   This function parse the time from XML data.
  * @param buffer        pointer to buffer
  * @param bufferLen   buffer Length
 * @return iptime extracted time.
 ******************************************************************/
ULONG64
AppS2w_ParseTime(INT8 *buffer ,INT32 bufferLen)
{
	INT8 *start,*end;
	ULONG64 iptime;
	INT8 p[16];
	memset(p,0,16);
	start =  strstr(buffer,">");
	start++;
	end =  strstr(start,"<");	
	memcpy(p,start,(end-start));
	AppS2wParse_64BitNumber(p,&iptime);
	webPrintf("\r\n Time:%lld",iptime);
	return iptime;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process time set/get URI call back. 
 *   This function get/set the time. 
 * @param event 	ttHttpdUserEvent. 		   						
 * @param uri        pointer to current URI
 * @param conHandle  Connection handler
 * @return o  - operation successful.
 * @retval -1  - operation failure-cerificate deletion failed.
 ******************************************************************/
GSN_HTTPD_STATUS_T 
AppS2w_configTimecb(ttHttpdUserEvent event, const char* uri, 
											ttHttpdUserConHandle conHandle)
{
 	int errorCode;
    UINT32 bufferLen=0,len=0;
	ULONG64 ipTime;	
	INT8* buffer = (INT8 *)GsnHttpd_GetBuffer();	
	if (!buffer)
		  return GSN_HTTPD_FAILURE;
    switch (event)
    {
		case TM_HTTPD_EVENT_BODY_RECV:
		{
			bufferLen = TM_BODY_BUFFER_LEN;
			tfHttpdUserGetRequestBody(conHandle, buffer, (ttUserIntPtr)&bufferLen ,0);
			ipTime = AppS2w_ParseTime(buffer,bufferLen);
			AppS2w_SetTime(ipTime);
		}
		break;
 		case TM_HTTPD_EVENT_SEND_READY:
		{
        	if (GsnHttpd_GetHttpMethod(conHandle) == TM_HTTP_METHOD_GET)
               	bufferLen = sprintf(buffer,"<time>%lld</time>",AppS2w_GetTime());	
			else		
				bufferLen = sprintf(buffer, "<status>ok</status>"); 		
    	    GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, bufferLen, TM_BLOCKING_ON, &errorCode);			
		}
		break;
	}
    if (buffer)
    {
    	GsnHttpd_ReleaseBuffer(buffer);
    	buffer = NULL;
	}
	return GSN_HTTPD_SUCCESS;
}
#endif

#ifdef ADK_PROV

/*******************************************************************************
 *  Private Functions
 ******************************************************************************/
 /*
  * Callback function for the /gainspan/config handler
  * It is up to the application to deal with the configuration.
  * This function further dispatches GET and POST
  * separately.
  */
 PRIVATE VOID
 S2wWeb_Config(GSN_SYS_CONFIG_T *pConfig, UINT8 method)
 {
     //webPrintf("[S2W] Configuration callback:%d\r\n",method);
     if (method == GSN_HTTPD_URI_METHOD_GET)
         S2wConfig_GetValues(pConfig);
     if (method == GSN_HTTPD_URI_METHOD_POST)
              S2wConfig_SetValues(pConfig);
     
     
     return;
 }
#endif /*  #ifdef ADK_PROV */

#if 0
/*Outer type          Inner type           Security*/

/*.................................................*/
#define S2W_WEB_EAPAUTH_TBL_ENTRY	6
/*Outer type, inner type*/
UINT32 eapAuthTable[S2W_WEB_EAPAUTH_TBL_ENTRY][3]=
{{43, 26, GSN_EAP_TYPE_FAST},/*  EAP- FAST */
{21, 26, GSN_EAP_TYPE_TTLS},/*EAP-TTLS*/
{13, 26, GSN_EAP_TYPE_TLS},/*EAP- TLS*/
{25, 26, GSN_EAP_TYPE_PEAP},/*EAP- PEAPV0*/
{25, 6, GSN_EAP_TYPE_NONE},/*EAP- PEAPV1*/
{43, 6, GSN_EAP_TYPE_NONE},/*EAP- GTC*/
};

#if 0
PRIVATE GSN_STATUS 
S2wWeb_EapAuthTypeGet(UINT32 eapType, UINT32 *outrAuth, UINT32 *innerAuth)
{
	UINT8 i;
	GSN_STATUS retVal = GSN_FAILURE;
	for(i = 0; i < S2W_WEB_EAPAUTH_TBL_ENTRY; i++)
		{
			if(eapAuthTable[i][2] == eapType)
				{
					*outrAuth = eapAuthTable[i][0];
					*innerAuth = eapAuthTable[i][1];
					retVal = GSN_SUCCESS;
					break;
				}
		}
	return retVal;
}
#endif
#else
/*Outer type          Inner type           Security*/

/*.................................................*/
#define S2W_WEB_EAPAUTH_TBL_ENTRY	7
/*Outer type, inner type*/
UINT32 eapAuthTable[S2W_WEB_EAPAUTH_TBL_ENTRY][2]=
{
	{43, 26,},	/*  EAP- FAST */
	{21, 26},	/*EAP-TTLS*/
	{13, 26},	/*EAP- TLS*/
	{25, 26},	/*EAP- PEAPV0*/
	{25, 6 },	/*EAP- PEAPV1*/
	{43, 6 },	/*EAP- GTC*/
	{0,  0 }	/*None*/
};

PRIVATE UINT32 
S2wWeb_EapAuthTypeGet( UINT8 outrAuth, UINT8 innerAuth)
{
	UINT8 i;
	UINT32 retVal = S2W_WEB_EAPAUTH_TBL_ENTRY;
	for(i = 0; i < S2W_WEB_EAPAUTH_TBL_ENTRY; i++)
		{
		if(outrAuth == eapAuthTable[i][0] && innerAuth == eapAuthTable[i][1])
				{
			retVal = i;
				}
		}
	return retVal;
}
void S2wWeb_EapAuthTypeSet( UINT8 eapType,UINT32 *outrAuth, UINT32 *innerAuth)
{
	if(eapType < S2W_WEB_EAPAUTH_TBL_ENTRY)
	{
		*outrAuth  = eapAuthTable[eapType][0];
		*innerAuth = eapAuthTable[eapType][1];	
	}
}

#endif
#ifdef ADK_PROV

/* send info to host */
PRIVATE VOID S2wConfig_SetValues(GSN_SYS_CONFIG_T *pConfig)
{
    UINT32 ipAddr =0;
    S2W_FLASH_PARAMS_T flashParams;
    S2W_PROFILE_T *pS2wProfile;
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();  
     
    pS2wProfile = &s2wCurrent;/*Store values in current profile*/
   
    memset(&flashParams, 0, sizeof(S2W_FLASH_PARAMS_T));    
    if (pConfig->sysConfigChangeApply)
    {

#ifdef ADK_PROV_CONFIG_CLIENT
	if(S2W_WEB_PARAMS_STORE == storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
	{
/*ssid*/
	    if((strncmp(pS2wProfile->security.wpa.ssid,(char*)pConfig->networkConfig.clientConfig.ssid.array,
	           pConfig->networkConfig.clientConfig.ssid.length)))
	    {
			pS2wProfile->security.wpa.ssidLen =0;
			pS2wProfile->security.wpa.pskValid = 0;
	    }
        pS2wProfile->autoWlandata.ssidLen = pConfig->networkConfig.clientConfig.ssid.length;
		memset(pS2wProfile->autoWlandata.ssid,0,S2W_MAX_SSID_LEN);
	    memcpy(pS2wProfile->autoWlandata.ssid, pConfig->networkConfig.clientConfig.ssid.array, 
		   pS2wProfile->autoWlandata.ssidLen);
/*channel*/
	    pS2wProfile->autoWlandata.channel = pConfig->networkConfig.clientConfig.channel;
		pS2wProfile->securityType = SECTYPE_AUTO;
/*wep key*/
	    if (pConfig->networkConfig.clientConfig.securityType == GSN_WLAN_WEP)
 	    {
			UINT8 i;
			UINT8 wepIndx = pConfig->networkConfig.clientConfig.wepKeyConfig.KeyId;

			pS2wProfile->security.wep.keyIdx = wepIndx;
			pS2wProfile->security.wep.keyLen[wepIndx - 1] = pConfig->networkConfig.clientConfig.wepKeyConfig.KeyLen;
			for(i = 0; i< pConfig->networkConfig.clientConfig.wepKeyConfig.KeyLen; i++)
			{
				pS2wProfile->security.wep.key[wepIndx - 1][i] = pConfig->networkConfig.clientConfig.wepKeyConfig.Key[i];
			}

			pS2wProfile->security.authMode = pConfig->networkConfig.clientConfig.wepAuthType;
 	    }
	    else if (pConfig->networkConfig.clientConfig.securityType == GSN_WLAN_WPA_PERSONAL)
    	{
    		/*WPA Personal*/	
        	// if pass phrase is differnt reset the psk valid
	        if(strncmp(pS2wProfile->security.wpa.wpaPassPhrase,(char*)pConfig->networkConfig.clientConfig.passphrase.Passphrase,
	           pConfig->networkConfig.clientConfig.passphrase.Len))
	        {
		       pS2wProfile->security.wpa.ssidLen =0;
		       pS2wProfile->security.wpa.pskValid = 0;
		    }
            pS2wProfile->security.wpa.passPhraseLen = pConfig->networkConfig.clientConfig.passphrase.Len;
			memset((VOID *)pS2wProfile->security.wpa.wpaPassPhrase,0,S2W_PSK_PASSPHRASE_LEN_MAX);
			memset((VOID *)pS2wProfile->security.wpa.ssid,0,S2W_MAX_SSID_LEN);
			memcpy(pS2wProfile->security.wpa.ssid,pConfig->networkConfig.clientConfig.ssid.array, 
		   			pS2wProfile->autoWlandata.ssidLen); 
			pS2wProfile->security.wpa.ssidLen = pS2wProfile->autoWlandata.ssidLen;
		    memcpy(pS2wProfile->security.wpa.wpaPassPhrase, 
		           pConfig->networkConfig.clientConfig.passphrase.Passphrase,
			       pS2wProfile->security.wpa.passPhraseLen);
        }
	    else if (pConfig->networkConfig.clientConfig.securityType == GSN_WLAN_WPA_ENTERPRISE)
	    {
			S2wWeb_EapAuthTypeSet(pConfig->networkConfig.clientConfig.eapType,&pS2wProfile->security.eap.outerAuth,
								&pS2wProfile->security.eap.innerAuth);
		    pS2wProfile->security.eap.passwordLen = pConfig->networkConfig.clientConfig.eapPassword.Length;

             memcpy(pS2wProfile->security.eap.password, pConfig->networkConfig.clientConfig.eapPassword.Pwd,
	              pConfig->networkConfig.clientConfig.eapPassword.Length);

           	 pS2wProfile->security.eap.usrNameLen = pConfig->networkConfig.clientConfig.eapUsername.Length;

              memcpy(pS2wProfile->security.eap.usrName, pConfig->networkConfig.clientConfig.eapUsername.Name,
	                              pConfig->networkConfig.clientConfig.eapUsername.Length);
              pS2wProfile->security.validKeys |= S2W_SECURITY_VALID_EAP; 	 			 
			 
           }

/*L2 configurations*/
	pS2wProfile->netConf.dhcp = pConfig->networkConfig.clientConfig.dhcpFlag;
	if(pConfig->networkConfig.clientConfig.dhcpFlag == 0)
	        {
	    	    ipAddr = htonl(pConfig->networkConfig.clientConfig.ipAddress);
	            
	            if(ipAddr) 
		    {
	                memcpy(pS2wProfile->netConf.ipAddr, &(ipAddr), 4);
		    }
	            ipAddr = htonl(pConfig->networkConfig.clientConfig.subnetmask);
				if(ipAddr)
					memcpy(pS2wProfile->netConf.netMask, &ipAddr, 4);

	            ipAddr= htonl(pConfig->networkConfig.clientConfig.gateway);
	            if( ipAddr)
					memcpy(pS2wProfile->netConf.gateway, &ipAddr, 4);

	            ipAddr = htonl(pConfig->networkConfig.clientConfig.dnsServer);
	            if( ipAddr) 
					memcpy(pS2wProfile->dns1, &ipAddr, 4);
	    
	            ipAddr = htonl(pConfig->networkConfig.clientConfig.dnsServer);
	            if( ipAddr)
					memcpy(pS2wProfile->dns1, &ipAddr, 4);
	         }
    }
    if(S2W_WEB_PARAMS_SND_TO_HOST == storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
    {
        /* Page 2 values - Basic WiFi*/
	S2w_Printf("SSID=");
	AppS2wHal_CharNPut(pConfig->networkConfig.clientConfig.ssid.array,pConfig->networkConfig.clientConfig.ssid.length);
        S2w_Printf("\r\nCHNL=%d\r\nCONN_TYPE=%d\r\nMODE=%d\r\nSECURITY=%d\r\n",
               pConfig->networkConfig.clientConfig.channel,0,0,pConfig->networkConfig.clientConfig.securityType);
    
        if (pConfig->networkConfig.clientConfig.securityType == GSN_WLAN_WEP)
        {
            UINT8 i;
        
            //webPrintf("WEP_AUTH_MODE=%s\r\n",s2wProvInfo.wepAuthMode);
            S2w_Printf("WEP_ID=%d\r\nWEP_KEY=",pConfig->networkConfig.clientConfig.wepKeyConfig.KeyId);
            //S2w_Printf("WEP_KEY=");
        
            for(i = 0; i< pConfig->networkConfig.clientConfig.wepKeyConfig.KeyLen; i++)
            {
                S2w_Printf("%02x",pConfig->networkConfig.clientConfig.wepKeyConfig.Key[i]);
            }
            S2w_Printf("\r\n");
        }
        else if (pConfig->networkConfig.clientConfig.securityType == GSN_WLAN_WPA_PERSONAL)
             {
                 S2w_Printf("PSK_PASS_PHRASE=");
		 AppS2wHal_CharNPut(pConfig->networkConfig.clientConfig.passphrase.Passphrase,
							pConfig->networkConfig.clientConfig.passphrase.Len);
		 S2w_Printf("\r\n");
             }
	     else if (pConfig->networkConfig.clientConfig.securityType == GSN_WLAN_WPA_ENTERPRISE)
	          {
                      S2w_Printf("EAP_USERNAME=");
		      AppS2wHal_CharNPut(pConfig->networkConfig.clientConfig.eapUsername.Name,
			pConfig->networkConfig.clientConfig.eapUsername.Length);
		
		      S2w_Printf("\r\nEAP_PASSWORD=");
		      AppS2wHal_CharNPut(pConfig->networkConfig.clientConfig.eapPassword.Pwd,
                             pConfig->networkConfig.clientConfig.eapPassword.Length);
		      
                      S2w_Printf("\r\n");
                   }

#ifndef IP2WIFI
    /* Page 3 values - IP Network*/
        S2w_Printf("DHCP_ENBL=%d\r\n",pConfig->networkConfig.clientConfig.dhcpFlag);

        if(pConfig->networkConfig.clientConfig.dhcpFlag == 0)
        {
            ipAddr= pConfig->networkConfig.clientConfig.ipAddress;
            if(ipAddr) S2w_Printf("STATIC_IP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));

            ipAddr= pConfig->networkConfig.clientConfig.subnetmask;
            if(ipAddr) S2w_Printf("SUBNT_MASK=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));
   
            ipAddr= pConfig->networkConfig.clientConfig.gateway;
            if( ipAddr) S2w_Printf("GATEWAY_IP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));


            S2w_Printf("AUTO_DNS_ENBL=%d\r\n",0);

            ipAddr = pConfig->networkConfig.clientConfig.dnsServer;
            if( ipAddr) S2w_Printf("PRIMERY_DNS_IP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));
 
            ipAddr = pConfig->networkConfig.clientConfig.dnsServer;

            if(ipAddr) S2w_Printf("SECNDRY_DNS_IP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));
        }
#endif /* IP2WIFI*/
    }
#endif
#ifdef ADK_PROV_CONFIG_LIMITED_AP
	if(S2W_WEB_PARAMS_STORE == storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
	{
	        if(pConfig->networkConfig.apConfig.ssid.length)
        {
            pS2wProfile->lmtdApConf.ssid.length = pConfig->networkConfig.apConfig.ssid.length;
		memset(pS2wProfile->lmtdApConf.ssid.array,0,GSN_MAC_SSID_LEN);

            memcpy( pS2wProfile->lmtdApConf.ssid.array, pConfig->networkConfig.apConfig.ssid.array,
			pConfig->networkConfig.apConfig.ssid.length);
	}
	if(pConfig->networkConfig.apConfig.channel)
	{
            pS2wProfile->lmtdApConf.channel = pConfig->networkConfig.apConfig.channel;
	}

        if(pConfig->networkConfig.apConfig.beaconInterval)
        {
            pS2wProfile->lmtdApConf.beaconInterval = pConfig->networkConfig.apConfig.beaconInterval;
	}
    pS2wProfile->lmtdApConf.securityType = (GSN_WLAN_SECURITY_TYPE_T)pConfig->networkConfig.apConfig.securityType;	
	if (pConfig->networkConfig.apConfig.securityType == GSN_WLAN_WPA_PERSONAL)
	{			
            pS2wProfile->lmtdApConf.passphrase.Len =
						pConfig->networkConfig.apConfig.passphrase.Len;
			memset(pS2wProfile->lmtdApConf.passphrase.Passphrase,0,GSN_WDD_SEC_PASSPHRASE_LEN);
            memcpy(pS2wProfile->lmtdApConf.passphrase.Passphrase,
				pConfig->networkConfig.apConfig.passphrase.Passphrase,
				pConfig->networkConfig.apConfig.passphrase.Len);
            pS2wProfile->lmtdApConf.securityType = SECTYPE_WPA2PSK;
			pS2wProfile->lmtdApConf.lmtdApPskValid =0;
	}
	else if (pConfig->networkConfig.apConfig.securityType == GSN_WLAN_WEP)
	    {
	        pS2wProfile->lmtdApConf.wepKeyConfig.KeyId = pConfig->networkConfig.apConfig.wepKeyConfig.KeyId;
			pS2wProfile->lmtdApConf.wepKeyConfig.KeyLen = pConfig->networkConfig.apConfig.wepKeyConfig.KeyLen;
			memcpy(pS2wProfile->lmtdApConf.wepKeyConfig.Key, pConfig->networkConfig.apConfig.wepKeyConfig.Key,
			pConfig->networkConfig.apConfig.wepKeyConfig.KeyLen);
			pS2wProfile->lmtdApConf.securityType = SECTYPE_WEP;
		pS2wProfile->lmtdApConf.wepKeyConfig.authType = pConfig->networkConfig.apConfig.wepKeyConfig.authType;
		}
		if(pConfig->networkConfig.apConfig.ipAddress)
		{
		     pS2wProfile->lmtdApConf.ipAddress = htonl(pConfig->networkConfig.apConfig.ipAddress);
		}
		if(pConfig->networkConfig.apConfig.subnetmask)
		{
		   pS2wProfile->lmtdApConf.subnetmask = htonl(pConfig->networkConfig.apConfig.subnetmask);
		}
		if( pConfig->networkConfig.apConfig.gateway)
		{
			pS2wProfile->lmtdApConf.gateway = htonl(pConfig->networkConfig.apConfig.gateway);
		}
		pS2wProfile->lmtdApConf.dhcpServerEnable = pConfig->networkConfig.apConfig.dhcpServerEnable;

		if(pConfig->networkConfig.apConfig.dhcpAddressStart)
		{
			pS2wProfile->lmtdApConf.dhcpAddressStart = htonl(pConfig->networkConfig.apConfig.dhcpAddressStart);
		}

	    pS2wProfile->lmtdApConf.dhcpNumAddresses = pConfig->networkConfig.apConfig.dhcpNumAddresses;
	    pS2wProfile->lmtdApConf.dnsServerEnable = pConfig->networkConfig.apConfig.dnsServerEnable;
	    strcpy((char *)pS2wProfile->lmtdApConf.dnsDomainName, (const char *)pConfig->networkConfig.apConfig.dnsDomainName);
	}
	
	if(S2W_WEB_PARAMS_SND_TO_HOST == storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
	{
	S2w_Printf("AP-SSID=");
	AppS2wHal_CharNPut(pConfig->networkConfig.apConfig.ssid.array,pConfig->networkConfig.apConfig.ssid.length);
    S2w_Printf("\r\nAP-CHNL=%d\r\nAP-BEACON-INTRL=%d\r\nAP-SECURITY=%d\r\n",
                pConfig->networkConfig.apConfig.channel,pConfig->networkConfig.apConfig.beaconInterval,
                pConfig->networkConfig.apConfig.securityType);

         if (pConfig->networkConfig.apConfig.securityType == GSN_WLAN_WPA_PERSONAL)
         {
         	S2w_Printf("AP-PSK_PASS_PHRASE=");
			AppS2wHal_CharNPut(pConfig->networkConfig.apConfig.passphrase.Passphrase,
							  pConfig->networkConfig.apConfig.passphrase.Len);
			S2w_Printf("\r\n");
         }
         else if (pConfig->networkConfig.apConfig.securityType == GSN_WLAN_WEP)
              {
			UINT8 i;
                   S2w_Printf("AP-WEP_ID=%d\r\nAP-WEP_KEY=",pConfig->networkConfig.apConfig.wepKeyConfig.KeyId);
	        for(i = 0; i< pConfig->networkConfig.apConfig.wepKeyConfig.KeyLen; i++)
                  {
            	S2w_Printf("%02x",pConfig->networkConfig.apConfig.wepKeyConfig.Key[i]);
                  }
                  S2w_Printf("\r\n");
              }

		    ipAddr= (pConfig->networkConfig.apConfig.ipAddress);		
		    if(ipAddr) S2w_Printf("AP-STATIC_IP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));

    ipAddr= pConfig->networkConfig.apConfig.subnetmask;
		    if(ipAddr) S2w_Printf("AP-SUBNT_MASK=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));

    ipAddr= pConfig->networkConfig.apConfig.gateway;
		    if( ipAddr) S2w_Printf("AP-GATEWAY_IP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));

    S2w_Printf("AP-DHCPSRVR-ENABLE=%d\r\n",pConfig->networkConfig.apConfig.dhcpServerEnable);
    ipAddr= pConfig->networkConfig.apConfig.dhcpAddressStart;
    if(ipAddr) S2w_Printf("AP-AP-DHCPSRVR-STARTIP=%d.%d.%d.%d\r\n",(ipAddr & 0xff),((ipAddr >>8) & 0xff),((ipAddr >> 16) & 0xff),((ipAddr >>24) & 0xff));
    S2w_Printf("AP-DHCPSRVR-NO-CONN=%d\r\nAP-DNSSRVR-ENABLE=%d\r\nAP-DNS-DOMAIN-NAME=%s\r\n",
               pConfig->networkConfig.apConfig.dhcpNumAddresses,pConfig->networkConfig.apConfig.dnsServerEnable,pConfig->networkConfig.apConfig.dnsDomainName);

	}
#endif
	if(S2W_WEB_PARAMS_STORE ==	storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
	{
	    /* Page 4 values - Device Configuration*/
	    if(0 != strlen((char*)pConfig->httpdConfig.username))
	        strcpy((char*)pS2wProfile->httpSrvrConf.username, (const char *)pConfig->httpdConfig.username);
	    if(0 != strlen((char*)pConfig->httpdConfig.password))
	    {
	        strcpy((char*)pS2wProfile->httpSrvrConf.password, (const char*)pConfig->httpdConfig.password);
	    }
		/* system name*/
		if(0 != strlen((char*)pConfig->sysIdConfig.name))
		{
			memset(pS2wProfile->hostName,0,GSN_NWIF_HOST_NAME_MAX_LEN+1);
			strncpy((char*)pS2wProfile->hostName,(const char *)pConfig->sysIdConfig.name, GSN_NWIF_HOST_NAME_MAX_LEN);
		}
		
	}
	if(S2W_WEB_PARAMS_SND_TO_HOST == storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
	{
      /* Administartive settings is common to both AP and Client*/
        if(0 != strlen((char*)pConfig->httpdConfig.username))
            S2w_Printf("NEW_USER_NAME=%s\r\n",pConfig->httpdConfig.username);
        if(0 != strlen((char*)pConfig->httpdConfig.password))
        {
            S2w_Printf("NEW_PASS=%s\r\n",pConfig->httpdConfig.password);

        }
		if(1 == s2wappMainTaskCtxt->formatVersion)
		{
			S2w_Printf("WEP_AUTH_MODE=%d",pS2wProfile->security.authMode);
			S2w_Printf("AP-WEP_AUTH_MODE=%d",pS2wProfile->lmtdApConf.wepKeyConfig.authType);			
		}
	}

	// flush the data for spi-dma interface
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }


	if(S2W_WEB_PARAMS_STORE == storeParams || S2W_WEB_PARAMS_SND_AND_STORE == storeParams)
	{
#ifdef  S2W_NCM_SUPPORT_ENABLE
		/*update the mode if ncmauto connect is enabled*/
	if(s2wappMainTaskCtxt->ncmAutoConEn)
			pS2wProfile->ncmAutoMgr =  1;			
		else
			pS2wProfile->ncmAutoMgr = 0;
	if(s2wCurrent.mode == S2W_WLANDATA_MODE_PROV_AP)
		pAppRtcLtchInfo->grpProvVerify = 1;
		
		pS2wProfile->mode =  (pConfig->networkConfig.networkMode == GSN_LIMITED_AP)	? GSN_LIMITED_AP : GSN_INFRA_CLIENT;
#endif		
		/* Store updated profile in NVDS */	
		memcpy(&flashParams.profile[0], pS2wProfile, sizeof(S2W_PROFILE_T));
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
	    S2w_SaveS2wProfile(&flashParams, 0);
 	}
 #ifdef  S2W_FS_SPI_ENABLE
     //AppS2w_FsSpiFlush();
  #endif
#ifdef	S2W_UART_ENABLE
  	while(S2wUart_TxStatusGet());
#endif
     /* reboot */
 		(s2wappMainTaskNotifier)(APP_NOTIFICATION_APPLY_SYS_REST, s2wappMainTaskCtxt);
 }
}

#endif /*  #ifdef ADK_PROV */


 #ifdef ADK_PROV
PRIVATE VOID 
S2wConfig_InitValues(GSN_SYS_CONFIG_T *pConfig,UINT8 networkMode)
{
	UINT8 i=0;
#ifdef ADK_PROV_CONFIG_LIMITED_AP
	 pConfig->networkConfig.apConfig.ssid.length = s2wCurrent.lmtdApConf.ssid.length;
	 memcpy(pConfig->networkConfig.apConfig.ssid.array, s2wCurrent.lmtdApConf.ssid.array,
				s2wCurrent.lmtdApConf.ssid.length);
	 pConfig->networkConfig.apConfig.channel = s2wCurrent.lmtdApConf.channel;
	 
	 pConfig->networkConfig.apConfig.securityType  = GSN_WLAN_SECURITY_NONE;
	 
	 if ((s2wCurrent.lmtdApConf.securityType == SECTYPE_WPA2PSK) \
		 || (s2wCurrent.lmtdApConf.securityType == SECTYPE_WPAPSK)	\
		 || (s2wCurrent.lmtdApConf.securityType == SECTYPE_WPA2PSK_TKIP))
	 {	 
		 pConfig->networkConfig.apConfig.securityType =GSN_WLAN_WPA_PERSONAL;
	 }
	 else if (s2wCurrent.lmtdApConf.securityType == SECTYPE_WEP )
	 {
	 
		 pConfig->networkConfig.apConfig.securityType = GSN_WLAN_WEP;		 
	 }
 
	 pConfig->networkConfig.apConfig.beaconInterval = s2wCurrent.lmtdApConf.beaconInterval;
	 
	 pConfig->networkConfig.apConfig.dhcpNumAddresses = s2wCurrent.lmtdApConf.dhcpNumAddresses;
	 pConfig->networkConfig.apConfig.ipAddress = ntohl(s2wCurrent.lmtdApConf.ipAddress);
	 pConfig->networkConfig.apConfig.subnetmask = ntohl(s2wCurrent.lmtdApConf.subnetmask);
	 pConfig->networkConfig.apConfig.gateway = ntohl(s2wCurrent.lmtdApConf.gateway);
	 pConfig->networkConfig.apConfig.dhcpServerEnable = s2wCurrent.lmtdApConf.dhcpServerEnable;
	 if(0 != s2wCurrent.lmtdApConf.dhcpServerEnable)
	 {
		  pConfig->networkConfig.apConfig.dhcpAddressStart = ntohl(s2wCurrent.lmtdApConf.dhcpAddressStart);
 
	 }

#ifdef S2W_DNS_SERVER_ENABLE
	 pConfig->networkConfig.apConfig.dnsServerEnable = s2wCurrent.lmtdApConf.dnsServerEnable;
	 if(s2wCurrent.lmtdApConf.dnsServerEnable)
	 {
		 strcpy((INT8 *)pConfig->networkConfig.apConfig.dnsDomainName, (const INT8 *)s2wCurrent.lmtdApConf.dnsDomainName);
	 }
#endif		 	 
#endif
#ifdef ADK_PROV_CONFIG_CLIENT
	 pConfig->networkConfig.clientConfig.channel = s2wCurrent.autoWlandata.channel;
	 pConfig->networkConfig.clientConfig.ssid.length = s2wCurrent.autoWlandata.ssidLen;
	 if(s2wCurrent.autoWlandata.ssidLen)
	 {
		 memcpy(pConfig->networkConfig.clientConfig.ssid.array,s2wCurrent.autoWlandata.ssid,
				s2wCurrent.autoWlandata.ssidLen);
	 }
	 pConfig->networkConfig.clientConfig.wepKeyConfig.KeyId = s2wCurrent.security.wep.keyIdx-1;
	 pConfig->networkConfig.clientConfig.wepKeyConfig.KeyLen =
									   (GSN_WDD_WEP_KEY_LEN_T)s2wCurrent.security.wep.keyLen[s2wCurrent.security.wep.keyIdx - 1];
	 for(i = 0; i< s2wCurrent.security.wep.keyLen[s2wCurrent.security.wep.keyIdx - 1]; i++)
	 {
		 pConfig->networkConfig.clientConfig.wepKeyConfig.Key[i] =
							 s2wCurrent.security.wep.key[s2wCurrent.security.wep.keyIdx -1 ][i];
	 }
	 pConfig->networkConfig.clientConfig.wepAuthType = s2wCurrent.security.authMode ;
	 pConfig->networkConfig.clientConfig.passphrase.Len = s2wCurrent.security.wpa.passPhraseLen;
	 if(s2wCurrent.security.wpa.passPhraseLen)
	 {
		 memcpy(pConfig->networkConfig.clientConfig.passphrase.Passphrase,
				s2wCurrent.security.wpa.wpaPassPhrase,
				s2wCurrent.security.wpa.passPhraseLen);
		pConfig->networkConfig.clientConfig.passphrase.Passphrase[pConfig->networkConfig.clientConfig.passphrase.Len+1] = '\0';		 
	 }
	 pConfig->networkConfig.clientConfig.dhcpFlag = s2wCurrent.netConf.dhcp ;
	 if(pConfig->networkConfig.clientConfig.dhcpFlag == 0)
	 {
		 memcpy( (UINT8*)&pConfig->networkConfig.clientConfig.ipAddress,(s2wCurrent.netConf.ipAddr), 4);
		 memcpy( (UINT8*)&pConfig->networkConfig.clientConfig.subnetmask,(s2wCurrent.netConf.netMask), 4);
		 memcpy( (UINT8*)&pConfig->networkConfig.clientConfig.gateway,(s2wCurrent.netConf.gateway), 4);
		 memcpy( (UINT8*)&pConfig->networkConfig.clientConfig.dnsServer,(s2wCurrent.dns1), 4);
		 pConfig->networkConfig.clientConfig.ipAddress = ntohl(pConfig->networkConfig.clientConfig.ipAddress);
		 pConfig->networkConfig.clientConfig.subnetmask = ntohl(pConfig->networkConfig.clientConfig.subnetmask);
		 pConfig->networkConfig.clientConfig.gateway = ntohl(pConfig->networkConfig.clientConfig.gateway);
		 pConfig->networkConfig.clientConfig.dnsServer = ntohl(pConfig->networkConfig.clientConfig.dnsServer);
	}
#endif	
}

/* Get Values from NVDS */
PRIVATE VOID 
S2wConfig_GetValues(GSN_SYS_CONFIG_T *pConfig)
{
    GSN_NWIF_IP_CONFIG_T nwParams;
    UINT8 i=0;
	GSN_WDD_WLAN_CFG_T *pWlanConfig;

	GSN_WIF_WLAN_NW_TYPE_T networkMode=GSN_WIF_WLAN_NW_TYPE_STA;
    if(prePoplnDone)
        return;
    prePoplnDone = 1;
	pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    S2wConfig_InitValues(pConfig,networkMode);
	networkMode =	s2wappMainTaskCtxt->if0.wddCtx.wlanNwType;
	
    //AppS2wHal_InfoGet(&info);
    pConfig->networkConfig.networkMode = (GSN_NETWORK_MODE_T)networkMode;
    //AppCfg_Get( APP_CFG_REG_DOMAIN_ID, &regDomain);
    pConfig->networkConfig.regDomain = (GSN_WLAN_REG_DOMAIN_T)s2wCurrent.regDomain;

    /* get the ip information by calling geps API */
    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx, &nwParams);
    pConfig->networkConfig.ipConfig.ipAddr = ntohl(nwParams.ipv4.ipAddr);

    GsnWdd_PhyAddrGet(&s2wappMainTaskCtxt->if0.wddCtx, (INT8 *)pConfig->networkConfig.macAddr);
    sprintf((char*)pConfig->sysIdConfig.uid, "%02x%02x%02x%02x%02x%02x",
           pConfig->networkConfig.macAddr[0],
           pConfig->networkConfig.macAddr[1],
           pConfig->networkConfig.macAddr[2],
           pConfig->networkConfig.macAddr[3],
           pConfig->networkConfig.macAddr[4],
           pConfig->networkConfig.macAddr[5]);

	if(strlen((const char *)s2wCurrent.hostName) == 0)
	{
		sprintf((char*)pConfig->sysIdConfig.name, "GS_%02x%02x%02x",
           pConfig->networkConfig.macAddr[3],
           pConfig->networkConfig.macAddr[4],
           pConfig->networkConfig.macAddr[5]);
	}
	else
	{
		strcpy((char *)pConfig->sysIdConfig.name,(char *)s2wCurrent.hostName);
	}
#ifdef ADK_PROV_CONFIG_LIMITED_AP

	if(networkMode ==  (GSN_WIF_WLAN_NW_TYPE_T)GSN_LIMITED_AP)
	{
    	pConfig->networkConfig.apConfig.ssid.length = pWlanConfig->ssid.length;			
	    memcpy(pConfig->networkConfig.apConfig.ssid.array, pWlanConfig->ssid.array,
               pWlanConfig->ssid.length);
    	pConfig->networkConfig.apConfig.channel = pWlanConfig->channel[0];//s2wCurrent.lmtdApConf.channel;
	
	pConfig->networkConfig.apConfig.securityType  = GSN_WLAN_SECURITY_NONE;
	
		if ((pWlanConfig->securityCfg.mode== S2W_AUTH_MODE_WPA2) \
			|| (pWlanConfig->securityCfg.mode  == S2W_AUTH_MODE_WPA) )
		{	
			pConfig->networkConfig.apConfig.securityType =GSN_WLAN_WPA_PERSONAL;
			pConfig->networkConfig.apConfig.passphrase.Len= pWlanConfig->securityCfg.pskConfig.passPhrase.Len;
			 if(pWlanConfig->securityCfg.pskConfig.passPhrase.Len)
		    {
				memcpy(pConfig->networkConfig.apConfig.passphrase.Passphrase,
					   pWlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
					   pWlanConfig->securityCfg.pskConfig.passPhrase.Len);
			}
		}
		else if (pWlanConfig->securityCfg.mode   == S2W_AUTH_MODE_WEP)

		{	
			pConfig->networkConfig.apConfig.securityType = GSN_WLAN_WEP;		
			pConfig->networkConfig.apConfig.wepKeyConfig.KeyId=  pWlanConfig->securityCfg.wepConfig.KeyId+1;
			pConfig->networkConfig.apConfig.wepKeyConfig.KeyLen=  pWlanConfig->securityCfg.wepConfig.KeyLen;
			memcpy(pConfig->networkConfig.apConfig.wepKeyConfig.Key,pWlanConfig->securityCfg.wepConfig.Key,
			pConfig->networkConfig.apConfig.wepKeyConfig.KeyLen);
	}
		else if(pWlanConfig->securityCfg.mode   == S2W_AUTH_MODE_WPA2_ENTERPICE)
			pConfig->networkConfig.apConfig.securityType = GSN_WLAN_WPA_ENTERPRISE;	

	    pConfig->networkConfig.apConfig.beaconInterval = pWlanConfig->apSpecificCfg.beaconInterval;

    pConfig->networkConfig.apConfig.dhcpNumAddresses = s2wCurrent.lmtdApConf.dhcpNumAddresses;

	    pConfig->networkConfig.apConfig.ipAddress = ntohl(nwParams.ipv4.ipAddr);
	    pConfig->networkConfig.apConfig.subnetmask = ntohl(nwParams.ipv4.subnetMask);
	    pConfig->networkConfig.apConfig.gateway = ntohl(nwParams.ipv4.gatewayIpAddr);
    pConfig->networkConfig.apConfig.dhcpServerEnable = s2wCurrent.lmtdApConf.dhcpServerEnable;
	    if(0 != pConfig->networkConfig.apConfig.dhcpServerEnable)
	{
	         pConfig->networkConfig.apConfig.dhcpAddressStart = (ntohl(nwParams.ipv4.ipAddr + 1));

    }
#ifdef S2W_DNS_SERVER_ENABLE
	  pConfig->networkConfig.apConfig.dnsServerEnable = s2wCurrent.lmtdApConf.dnsServerEnable;
	 if(s2wCurrent.lmtdApConf.dnsServerEnable)
    {
	 	if(s2wCurrent.lmtdApConf.dnsDomainName[0] != 0)
        strcpy((INT8 *)pConfig->networkConfig.apConfig.dnsDomainName, (const INT8 *)s2wCurrent.lmtdApConf.dnsDomainName);
    }
#endif

	}
    // fill the client info
#endif    
#ifdef ADK_PROV_CONFIG_CLIENT
	if(networkMode ==(GSN_WIF_WLAN_NW_TYPE_T) GSN_INFRA_CLIENT)
	{
        pConfig->networkConfig.clientConfig.channel = pWlanConfig->channel[0];
    	pConfig->networkConfig.clientConfig.ssid.length = pWlanConfig->ssid.length;
	    if( pWlanConfig->ssid.length)
    {
			memcpy(pConfig->networkConfig.clientConfig.ssid.array, pWlanConfig->ssid.array,
			        pWlanConfig->ssid.length);
	}
    // populate wep key
	    pConfig->networkConfig.clientConfig.wepKeyConfig.KeyId =  pWlanConfig->securityCfg.wepConfig.KeyId+1;

    pConfig->networkConfig.clientConfig.wepKeyConfig.KeyLen =
														   pWlanConfig->securityCfg.wepConfig.KeyLen;

	    for(i = 0; i< pWlanConfig->securityCfg.wepConfig.KeyLen; i++)
    {
        pConfig->networkConfig.clientConfig.wepKeyConfig.Key[i] =
	                            pWlanConfig->securityCfg.wepConfig.Key[i];
    }
		pConfig->networkConfig.clientConfig.securityType = GSN_WLAN_SECURITY_NONE;
		if ((pWlanConfig->securityCfg.mode   == S2W_AUTH_MODE_WPA2) \
					|| (pWlanConfig->securityCfg.mode == S2W_AUTH_MODE_WPA) )
		{	
			pConfig->networkConfig.clientConfig.securityType = GSN_WLAN_WPA_PERSONAL;
		}
		else if (pWlanConfig->securityCfg.mode   == S2W_AUTH_MODE_WEP )
		{
			pConfig->networkConfig.clientConfig.securityType =  GSN_WLAN_WEP;		
			pConfig->networkConfig.clientConfig.wepAuthType = GSN_MAC_AUTH_OPEN;
			if(	GSN_WDD_SEC_WEP_SHARED  == pWlanConfig->securityCfg.wepConfig.authType)
				pConfig->networkConfig.clientConfig.wepAuthType =	GSN_MAC_AUTH_SHARED;
		}
		else if(pWlanConfig->securityCfg.mode	 == S2W_AUTH_MODE_WPA_ENTERPICE ||
			    pWlanConfig->securityCfg.mode	 == S2W_AUTH_MODE_WPA2_ENTERPICE   )
    	{
			pConfig->networkConfig.clientConfig.securityType = GSN_WLAN_WPA_ENTERPRISE; 
			pConfig->networkConfig.clientConfig.eapType = (GsnProvEapType)S2wWeb_EapAuthTypeGet(pWlanConfig->securityCfg.eapConfig.outerAuthType,
																				pWlanConfig->securityCfg.eapConfig.innerAuthType); 
			memcpy(pConfig->networkConfig.clientConfig.eapUsername.Name,pWlanConfig->securityCfg.eapConfig.userName.Name, 
				pWlanConfig->securityCfg.eapConfig.userName.Length);
			pConfig->networkConfig.clientConfig.eapUsername.Length=pWlanConfig->securityCfg.eapConfig.userName.Length;
			memcpy(pConfig->networkConfig.clientConfig.eapPassword.Pwd, pWlanConfig->securityCfg.eapConfig.password.Pwd, 
				pWlanConfig->securityCfg.eapConfig.password.Length);
			pConfig->networkConfig.clientConfig.eapPassword.Length = pWlanConfig->securityCfg.eapConfig.password.Length;
    }
	    
    // populate client ip info
	    pConfig->networkConfig.clientConfig.passphrase.Len = pWlanConfig->securityCfg.pskConfig.passPhrase.Len;
	    if(pWlanConfig->securityCfg.pskConfig.passPhrase.Len)
    {
			memcpy(pConfig->networkConfig.clientConfig.passphrase.Passphrase,
				   pWlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
				   pWlanConfig->securityCfg.pskConfig.passPhrase.Len);

   }
	    pConfig->networkConfig.clientConfig.dhcpFlag   = (nwParams.ipv4.staticIp)?0:1;
		pConfig->networkConfig.clientConfig.ipAddress  = ntohl(nwParams.ipv4.ipAddr);
		pConfig->networkConfig.clientConfig.subnetmask = ntohl(nwParams.ipv4.subnetMask);
	    pConfig->networkConfig.clientConfig.gateway	   = ntohl(nwParams.ipv4.gatewayIpAddr);
	    pConfig->networkConfig.clientConfig.dnsServer  = ntohl(nwParams.ipv4.dnsPriSrvrIp);

	}
	#endif
}


#ifdef S2W_WEB_SRVR_LOGO_INTRNL_FLASH
/*
 * Callback function for logo handler. This will be called by the
 * logo URI handler to obtain information about the logo location.
 * This function should fill in the location and size
 */
PRIVATE VOID
App_LogoInfoCb(GSN_HTTPD_LOGO_INFO_T* pInfo)
{
    UINT32 logoSize = 0;
    memcpy(&logoSize, (INT8 *)(GSN_FACT_DFLT_LOGO_ADDR), sizeof(UINT32));
    if(logoSize == 0xffffffff)
    {
        logoSize = 0;
    }

    pInfo->location = (INT8*) GSN_FACT_DFLT_LOGO_ADDR + sizeof(UINT32);
    pInfo->size = logoSize;
}
#endif
#endif
#endif



#if defined(S2W_WEB_SERVER) || defined(S2W_WEB_PROV)
#ifdef S2W_WEB_SRVR_STACK_STATIC
#pragma ghs section bss = ".bss_NoZeroInit"
#ifdef S2W_SSL_SERVER_SUPPORT
	PRIVATE UINT32 s2wWebServerTaskStack[APP_CFG_SSL_WEB_SRVR_STACK_SIZE/4];
#else
	PRIVATE UINT32 s2wWebServerTaskStack[APP_CFG_WEB_SRVR_STACK_SIZE/4];
#endif
#endif
        
PUBLIC UINT8*
S2wApp_WebserverStack_Get(UINT32 sslEnbl)
{
#ifdef S2W_WEB_SRVR_STACK_STATIC
	return ((UINT8 *)s2wWebServerTaskStack);
#else
	UINT32 stackSize = APP_CFG_WEB_SRVR_STACK_SIZE;
	if(sslEnbl)
	{
		stackSize = APP_CFG_SSL_WEB_SRVR_STACK_SIZE;
	}
	return (UINT8 *)gsn_malloc(stackSize);
#endif	
}
PUBLIC UINT32
S2wApp_WebserverStackSize_Get(UINT32 sslEnbl)
{
#ifdef S2W_WEB_SRVR_STACK_STATIC
	return (sizeof(s2wWebServerTaskStack));
#else
	UINT32 stackSize = APP_CFG_WEB_SRVR_STACK_SIZE;
	if(sslEnbl)
	{
		stackSize = APP_CFG_SSL_WEB_SRVR_STACK_SIZE;
	}
	return stackSize;
#endif
}
PUBLIC VOID
S2wApp_WebserverStack_Free(UINT8* stackPtr)
{
#ifndef S2W_WEB_SRVR_STACK_STATIC
	gsn_free(stackPtr);
#endif
}
#endif
