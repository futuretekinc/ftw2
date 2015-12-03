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
 * $RCSfile: app_httpd.c,v $
 *
 * Description : s2w GEPS interface file
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_api.h"
#include "modules/http/gsn_httpd_logo.h"
#include "battery/app_batt_chk.h"
#ifdef ADK_PROV_ENABLE
#include "gsn_httpd_config.h"
#include "gsn_httpd_prov.h"
#include "modules/http/gsn_httpd_file_api.h"
#endif

#ifdef ADK_OTAFU_ENABLE
//#include "gsn_httpd_file_api.h"
#include "modules/http/gsn_httpd_file_api.h"
#include "gsn_otafu.h"
#endif

#ifdef ADK_FS_UPLOAD_ENABLE
#include "modules/http/gsn_httpd_file_api.h"
#include "gsn_httpd_file_upload.h"
#endif

#include "app_net_svcs_priv.h"
#include "app_httpd_cb.h"
#include "app_cfg.h"
#include "app_debug.h"

#ifdef ADK_PROV_ENABLE
GSN_WLAN_REG_DOMAIN_T appWlanRegDomain =  GSN_WLAN_REG_DOMAIN_UNKNOWN;
#endif

PUBLIC INT8 AppHttp_ApiInit(VOID);


PUBLIC VOID App_HttpSecure(APP_MAIN_CTX_T *pAppCtx);

/*[ TO DO] - This declaration should come from a header file*/
//extern UINT8 GsnHttpdApi_FwInit(UINT32 wlanVer, UINT8* appVersion);

//extern UINT8 GsnHttpdApi_SysDebugInit();

extern VOID AppOtafu_Init(APP_MAIN_CTX_T* pAppCtx);

#define APP_HTTPD_MAX_TOTAL_CONN    32
#define APP_HTTPD_MAX_PER_IP_CONN   16
#define APP_HTTPD_IDLE_TIMEOUT      120
#define APP_HTTPD_PORT              80

#define APP_HTTPD_BLOCKING_STATE    1

#define APP_SSL_CERT_NAME_CA        "SSL_CA"
#define APP_SSL_CERT_NAME_SERVER    "SSL_SERVER"
#define APP_SSL_CERT_NAME_KEY       "SSL_KEY"
#define GSN_SSLCERTUPLOAD_URI   	"/gainspan/system/sslcertupload"
#define APP_INVALID_CERT_INDEX 		0xFFFFFFFF
#define APP_MAX_NUM_CERT        	8


typedef enum APP_CERT_LOCATION
{
	CERT_IN_FLASH,
	CERT_IN_RAM
}APP_CERT_LOCATION_T;

/* The Entry for the SRAM Certificate Table */
typedef struct APP_SSL_CERT_SRAM_TABLE
{
	/* The Actual 32bit address for the certificate */
	UINT8 *certAddress;
	/* Pinter to name of the certificate */
	UINT8 *name;
	APP_CERT_LOCATION_T location;
}APP_SSL_CERT_SRAM_TABLE_T;

APP_SSL_CERT_SRAM_TABLE_T APP_ssl_cert_table[APP_MAX_NUM_CERT];
SERVER_CERT_DETAIL_T *pCertDtl = NULL;

/*
 * This is the entry point for the HTTP Server
 */
PUBLIC GSN_STATUS 
App_HttpdStart(APP_MAIN_CTX_T *pAppCtx)
{
    UINT32 wlanVer = 0;
    GSN_HTTPD_CONFIG_T config;	
	GSN_NWIF_IP_CONFIG_T ipConfig;

#ifdef ADK_PROV_ENABLE	
    GSN_HTTPD_PROV_CONFIG_T provConfig;	
	GSN_WLAN_REG_DOMAIN_T appWlanRegDomain = GSN_WLAN_REG_DOMAIN_UNKNOWN;
#endif

    AppDbg_Printf("[%s] Entered\r\n", __FUNCTION__);

    /* get the ip information by calling geps API */
    GsnNwIf_IpConfigGet(&pAppCtx->if0.nwifCtx, &ipConfig);

	/* Initialize web parameters */
    memset(&config, 0, sizeof(GSN_HTTPD_CONFIG_T));

    /* store user mane and passwd*/
    strcpy(config.username, (const INT8 *)pAppCtx->config.httpdConfig.username);
    strcpy(config.password, (const INT8 *)pAppCtx->config.httpdConfig.password);
    config.port = APP_HTTPD_PORT;
    config.maxConnPerIp = APP_HTTPD_MAX_PER_IP_CONN;
    config.maxConnTotal = APP_HTTPD_MAX_TOTAL_CONN;
    config.blockingState = APP_HTTPD_BLOCKING_STATE;
    config.threadPriority = APP_CFG_WEB_SRVR_THREAD_PRIORITY;
    config.idleTimeout = APP_HTTPD_IDLE_TIMEOUT;
	
    config.ip_flag = GSN_USE_IPV4;
    config.ipAddr = ipConfig.ipv4.ipAddr;

    config.rootCgiDir = NULL;
    config.rootDir = "/";
    config.defaultFileName = "index.html";
	config.mallocTimeout = 2 *1000; /* 2 Sec. */

    config.stack = (UINT8 *)MALLOC(APP_CFG_WEB_SRVR_STACK_SIZE);	 
	if(NULL == config.stack)
	{
		return GSN_FAILURE;
	}
    config.stackSize  = APP_CFG_WEB_SRVR_STACK_SIZE;
    config.pool_hdl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_LBUF_PKT_POOL);
	config.sysQualTskID = APP_CFG_SQ_HTTPD_TASK_ID;
	config.sysQualTicks = APP_CFG_SQ_TICKS_FOR_HTTPD_TASK;

	/* start http based on httpsFlag*/
	if(pAppCtx->httpsInfo.httpsFlag == 1)
	{
		AppDbg_Printf("**********\r\nHTTPS: httpd server start in secured mode\r\n**********\r\n");
		
		/* Get certificate details for https functionality */
		App_HttpSecure(pAppCtx);
		
		/* Start httpd in secured mode*/
		GsnHttpd_Start(config, pCertDtl);
	}
	else
	{
		AppDbg_Printf("**********\r\nHTTP: httpd server start in normal mode\r\n**********\r\n");
		
	    /* Start httpd */
	    GsnHttpd_Start(config, NULL);
	}
	
#ifdef ADK_PROV_ENABLE
    /* System Configuration URI Handler  */
    GsnHttpdApi_ConfigInit(App_ConfigCb);

	/* Scan Configuration URI Handler */
    memset(&provConfig, 0x0, sizeof(provConfig));
    provConfig.pWdd = &pAppCtx->if0.wddCtx;
    provConfig.domain = appWlanRegDomain;

#ifdef ADK_PROV_WPS_ENABLE
    provConfig.pWpsCbFn = (GSN_HTTPD_PROV_WPS_CB_FN_T) AppWps_CbFn;
#endif /* ADK_PROV_WPS_ENABLE */
    GsnHttpdApi_ProvInit(&provConfig);
#endif /* ADK_PROV_ENABLE */

    /* API Configuration URI Handler */
    GsnHttpdApi_ApiInit();

#ifdef ADK_API_SYS_DEBUG_ENABLE
    GsnHttpdApi_SysDebugInit();
#endif /*ADK_API_SYS_DEBUG_ENABLE */

    /*Get Wlan Version*/
    GsnSysCtl_WlanFwVerGet(&pAppCtx->sysCtlCtx,&wlanVer);
    GsnHttpdApi_FwInit(wlanVer, (UINT8*)AppConfig_GetAppNameAndVersion());

    /* Application's URI Handler*/
    AppHttp_ApiInit();

	/* File Upload App Configuration Handler */
#ifdef ADK_FILE_UPLOAD_API
	GsnHttpd_FileApiInit();
	GsnHttpd_FileApiConfig(GSN_SSLCERTUPLOAD_URI, AppCertUpload_SslCertUploadCb, GSN_HTTPD_URI_METHOD_POST);	

#ifdef ADK_FILE_UPLOAD_APP_CONTENT_DISPLAY
	GsnHttpd_FileApiConfig("/gainspan/system/fileupload", AppFileUpload_FilesPrintCb, GSN_HTTPD_URI_METHOD_POST);
#endif

#ifdef ADK_OTAFU_ENABLE
	AppOtafu_Init(pAppCtx);
#endif
#ifdef ADK_FS_UPLOAD_ENABLE
	 GsnFsUpload_Init();
#endif
#endif /*ADK_FILE_UPLOAD_API*/

    return GSN_SUCCESS;
}

PUBLIC GSN_STATUS 
App_HttpdStop(APP_MAIN_CTX_T *pAppCtx)
{
	/* Free allocated memory for certificates*/
	if(pAppCtx->httpsInfo.httpsFlag == 1)
	{
		for(int i = 0; i < APP_MAX_NUM_CERT; i++)
		{
			if (!APP_ssl_cert_table[i].certAddress)
			{
				gsn_free (APP_ssl_cert_table[i].certAddress);
				APP_ssl_cert_table[i].certAddress = NULL;
			}
			if (!APP_ssl_cert_table[i].name)
			{
				gsn_free(APP_ssl_cert_table[i].name);
				APP_ssl_cert_table[i].name = NULL;
			}
		}
	}

	return GsnHttpd_Stop();
}

PUBLIC INT32
AppCert_MemAlloc (UINT16 size)
{
	UINT32 i = 0;
	UINT8 *pBuf;
	while (i < APP_MAX_NUM_CERT)
	{
		if (!APP_ssl_cert_table[i].certAddress)
			break;
		i++;
	}
	if(i == APP_MAX_NUM_CERT)
	{
		return -1;
	}
	pBuf = gsn_malloc(size + 2);
	if(pBuf == NULL)
		return -1;
	APP_ssl_cert_table[i].certAddress = pBuf;
	return i;
}

PUBLIC GSN_STATUS
AppCert_MemFree(UINT8 *name)
{
	UINT32 index = 0;
	while(index < APP_MAX_NUM_CERT)
	{
		if(!strcmp((const char *)APP_ssl_cert_table[index].name, (const char *)name))
		{
			gsn_free (APP_ssl_cert_table[index].certAddress);
			/* Marking the SRAM entry as Invalid */
			gsn_free(APP_ssl_cert_table[index].name);
			APP_ssl_cert_table[index].name = NULL;
			APP_ssl_cert_table[index].certAddress = NULL;
			return GSN_SUCCESS;
		}
	}
	return GSN_FAILURE;
}

PUBLIC INT32
AppCert_SearchRamTable(char *ptr)
{
	INT32 i = 0;
	while(i < APP_MAX_NUM_CERT)
	{
		//AppDbg_Printf("name: %s\n\r", APP_ssl_cert_table[i].cert.name);
		if( !strcmp((const char *)APP_ssl_cert_table[i].name, ptr))
		{
			/* certificate found */
			//AppDbg_Printf("found\n\r");
			break;
		}
		i++;
	}
	if (i == APP_MAX_NUM_CERT) {

		i = -1;
	}
	return i;

}

PUBLIC INT32
AppCert_FlashFileLoad(char *fileName)
{
	INT32 fileLen,index;
	F_FILE *fd; 
	//char name[38];
	
	if(fileName == NULL)
		return -1;

	f_chdir("certs");
	fileLen = f_filelength(fileName);
	if(fileLen == -1)
	{
		f_chdir("..");
		f_chdrive(1);		
		f_chdir("certs");
		fileLen = f_filelength(fileName);
		if(fileLen == -1)
		{					
			index = -1; 	
			goto FlashFileLoadExit;
		}
	}	
	index = AppCert_MemAlloc (fileLen);
	if(index != -1)
	{
		APP_ssl_cert_table[index].name = gsn_malloc(strlen(fileName) + 1);
		if(APP_ssl_cert_table[index].name == NULL)
		{
			AppCert_MemFree(APP_ssl_cert_table[index].certAddress);
			index = -1; 	
			goto FlashFileLoadExit;
		}
		strcpy((char*)APP_ssl_cert_table[index].name, fileName);
		APP_ssl_cert_table[index].location = CERT_IN_FLASH;
		fd = f_open(fileName, "r");
		if(fd == NULL)
		{
			AppCert_MemFree(APP_ssl_cert_table[index].certAddress);
			gsn_free(APP_ssl_cert_table[index].name);
			index = -1; 	
			goto FlashFileLoadExit;
		}
		f_read(APP_ssl_cert_table[index].certAddress+2, 1, fileLen, fd);
		APP_ssl_cert_table[index].certAddress[0] = (fileLen & 0xff);
		APP_ssl_cert_table[index].certAddress[1] = ((fileLen >> 8) & 0xff);
		f_close(fd);
	}
FlashFileLoadExit:
	f_chdir("..");		
	f_chdrive(0);	
	return index;
}


PUBLIC VOID 
App_HttpSecure(APP_MAIN_CTX_T *pAppCtx)
{
	UINT32 index, certLength;

	(VOID)pCertDtl;
	memset(&(pAppCtx->httpsInfo.certDetail), 0, sizeof(pAppCtx->httpsInfo.certDetail));
	pCertDtl = &(pAppCtx->httpsInfo.certDetail);

	/* Fetch CA Certificate details */
	index = AppCert_SearchRamTable(APP_SSL_CERT_NAME_CA);
	if(index == -1)
	{
		index = AppCert_FlashFileLoad(APP_SSL_CERT_NAME_CA);
	}
	if(index == -1)
	{
		AppDbg_Printf("\n\rCertificate %s Not Found", APP_SSL_CERT_NAME_CA);
	}
	pAppCtx->httpsInfo.certDetail.CaCertName = (char const *)APP_ssl_cert_table[index].name;
	pAppCtx->httpsInfo.certDetail.CaCertLocation = APP_ssl_cert_table[index].certAddress + 2;		  
	certLength = *(APP_ssl_cert_table[index].certAddress + 1);
	certLength <<= 8;
	certLength = certLength | (*(APP_ssl_cert_table[index].certAddress));
	pAppCtx->httpsInfo.certDetail.CaCertLen = certLength;

	/* Fetch SERVER Certificate details */
	index = AppCert_SearchRamTable(APP_SSL_CERT_NAME_SERVER);
	if(index == -1)
	{
		index = AppCert_FlashFileLoad(APP_SSL_CERT_NAME_SERVER);
	}
	if(index == -1)
	{
		AppDbg_Printf("\n\rCertificate %s Not Found", APP_SSL_CERT_NAME_SERVER);
	}
	pAppCtx->httpsInfo.certDetail.ClientCertName = (const char *)APP_ssl_cert_table[index].name;
	pAppCtx->httpsInfo.certDetail.ClientCertLocation = APP_ssl_cert_table[index].certAddress + 2;		  
	certLength = *(APP_ssl_cert_table[index].certAddress + 1);
	certLength <<= 8;
	certLength = certLength | (*(APP_ssl_cert_table[index].certAddress));
	pAppCtx->httpsInfo.certDetail.ClientCertLen = certLength;

	/* Fetch Certificate KEY details */
	index = AppCert_SearchRamTable(APP_SSL_CERT_NAME_KEY);
	if(index == -1)
	{
		index = AppCert_FlashFileLoad(APP_SSL_CERT_NAME_KEY);
	}
	if(index == -1)
	{		
		AppDbg_Printf("\n\rCertificate %s Not Found", APP_SSL_CERT_NAME_KEY);
	}
	pAppCtx->httpsInfo.certDetail.PrivateKeyName = (const char *)APP_ssl_cert_table[index].name;
	pAppCtx->httpsInfo.certDetail.PrivateKeyLocation = APP_ssl_cert_table[index].certAddress + 2;		  
	certLength = *(APP_ssl_cert_table[index].certAddress + 1);
	certLength <<= 8;
	certLength = certLength | (*(APP_ssl_cert_table[index].certAddress));
	pAppCtx->httpsInfo.certDetail.PrivateKeyLen = certLength;
}

