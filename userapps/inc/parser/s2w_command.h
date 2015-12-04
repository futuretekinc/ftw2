/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: s2w_command.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef FTW_COMMAND_H
#define FTW_COMMAND_H

UINT8 AppS2wProcess_AutoConnectStart(FTW_PROFILE_T *profile);
UINT8
AppS2wProcess_AutoConnectStop(FTW_PROFILE_T *profile);
UINT8 AppS2wCommand_Process(UINT8 *cmd);
VOID AppS2wProcess_LoadProfile(UINT8 profile_num);
PUBLIC VOID
AppS2wProcess_AsyncStatusNotify(UINT8 status, UINT32 arg);
VOID
AppS2wHdrAndIp_Print();

extern UINT8 s2wIsAutoconnected;
extern FTW_FLASH_PARAMS_T *s2wFlashParams;

#define FTW_HTTP_METHOD_GETRESP 6
#define FTW_HTTP_METHOD_POSTRESP 7
#define FTW_HTTP_METHOD_POST GSN_HTTP_METHOD_POST
#define FTW_HTTP_METHOD_GET GSN_HTTP_METHOD_GET

#ifdef FTW_HTTP_CUSTOM_SUPPORT
enum FTW_XML_ELEMENT_TYPE_IDS
{
    FTW_HTTP_REQUEST_LINE = 9991,
    FTW_HTTP_HEADER,
    FTW_HTTP_CGI_PARAMS,
    FTW_HTTP_RESPONSE_LINE,
	FTW_XML_ELEMENT_TYPE_START_ID = 9995,
    FTW_XML_ATTRIBUTE_ID,
	FTW_XML_COMPLEX_TAG_END_ID,
	FTW_XML_COMPLEX_TAG_START_ID,
	FTW_XML_ELEMENT_TYPE_END_ID
};
#else
enum FTW_XML_ELEMENT_TYPE_IDS
{
	FTW_XML_ELEMENT_TYPE_START_ID = 9995,
    FTW_XML_ATTRIBUTE_ID,
	FTW_XML_COMPLEX_TAG_END_ID,
	FTW_XML_COMPLEX_TAG_START_ID,
	FTW_XML_ELEMENT_TYPE_END_ID
};
#endif

#if 0//def GSN_HTTP_CUSTOM_SUPPORT

enum HTTP_HEADER_INDEX
{
    GSN_HTTP_HEADER_ALLOW,
    GSN_HTTP_HEADER_AUTHORIZATION,
    GSN_HTTP_HEADER_CONNECTION,
    GSN_HTTP_HEADER_CONTENT_ENCODING,
    GSN_HTTP_HEADER_CONTENT_LENGTH,
    GSN_HTTP_HEADER_CONTENT_RANGE,
    GSN_HTTP_HEADER_CONTENT_TYPE,
    GSN_HTTP_HEADER_COOKIE,
    GSN_HTTP_HEADER_COOKIE2,
    GSN_HTTP_HEADER_DATE,
    GSN_HTTP_HEADER_EXPIRES,
    GSN_HTTP_HEADER_FROM,
    GSN_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_IF_MODIFIED_SINCE,
    GSN_HTTP_HEADER_LAST_MODIFIED,
    GSN_HTTP_HEADER_LOCATION,
    GSN_HTTP_HEADER_PRAGMA,
    GSN_HTTP_HEADER_RANGE,
    GSN_HTTP_HEADER_REFERER,
    GSN_HTTP_HEADER_SERVER,
    GSN_HTTP_HEADER_TRANSFER_ENCODING,
    GSN_HTTP_HEADER_USER_AGENT,
    GSN_HTTP_HEADER_CUSTOM

};
#endif


enum FTW_STATE
{
    FTW_STATE_CMD,
    FTW_STATE_DATA,
    FTW_STATE_DATA_ESC,
    FTW_STATE_CMD_ESC,
    FTW_STATE_CID,
    FTW_STATE_RAW,
    FTW_STATE_RAW_DATA,
    FTW_STATE_ASYNC_TX,
    FTW_STATE_UNSOLICITED_HDR,
    FTW_STATE_UNSOLICITED_DATA,
    FTW_STATE_IPPORT,
    FTW_STATE_IP_STRING,
    FTW_STATE_PORT_STRING,
    FTW_STATE_DATA_AUTO,
    FTW_STATE_CERT,
    FTW_STATE_WEB_LOGO,
    FTW_STATE_HTTP_CONTENT_CID,
    FTW_STATE_COAP_CONTENT_CID,
    FTW_STATE_HTTP_CONTENT_DATA,
    FTW_STATE_BULK_DATA,
    FTW_STATE_FWRITE,
	
   FTW_STATE_GSLINK_RECV,
   
	FTW_STATE_GET_CID,
    FTW_STATE_XML_LEN,
    FTW_STATE_XML_PROCESS,
    FTW_STATE_BUFF_STORE,
    FTW_STATE_EXTFLASH
};


enum FTW_OTAFWUP_IDS
{
    FTW_OTAFWUP_SRVRIP,
    FTW_OTAFWUP_SRVRPORT,
    FTW_OTAFWUP_PROXY_PRESENT,
    FTW_OTAFWUP_PROXY_SRVRIP,
    FTW_OTAFWUP_PROXY_SRVRPORT,
    FTW_OTAFWUP_SSL_ENABLED,
    FTW_OTAFWUP_CERT_NAME,
    FTW_OTAFWUP_APP_IMAGE_URL,
    FTW_OTAFWUP_INFO_URL,
    FTW_OTAFWUP_SRVR_HOST_NAME,
    FTW_OTAFWUP_APP_SIGN_URL,
    FTW_OTAFWUP_APP_ENABLE_DNS_ERR
};

enum FTW_OTAFU_URL_IDS
{
	FTW_OTAFU_URL_FW_IMAGE,
	FTW_OTAFU_URL_XML,
	FTW_OTAFU_URL_SIGN_IMAGE,
};
extern enum FTW_STATE s2wState;

extern UINT32 s2wTxBytes;
extern UINT32 s2wRxBytes;

UINT8
AppS2wCmd_Ncloseall(UINT8 *ptr);
UINT8
AppS2wCmd_Nclose(UINT8 *ptr);
UINT8
AppS2wCmd_Wauto(UINT8 *ptr);
UINT8
AppS2wCmd_AutoConnect(UINT8 *ptr);
UINT8
AppS2wCmd_GoOnline(UINT8 *ptr);
UINT8
AppS2wCmd_Nauto(UINT8 *ptr);
UINT8
AppS2wCmd_Ncudp(UINT8 *ptr);

//UINT8
//AppS2wCmd_NwConnRestore(UINT8 *ptr);

UINT8
AppS2wCmd_Nctcp(UINT8 *ptr);
UINT8
AppS2wCmd_Nstcp(UINT8 *ptr);
UINT8
AppS2wCmd_Nsudp(UINT8 *ptr);
UINT8
AppS2wCmd_SetSockOp(UINT8 *ptr);

UINT8
AppS2wCmd_Dns(UINT8 *ptr);
UINT8
AppS2wCmd_DhcpSrvr(UINT8 *ptr);

UINT8
AppS2wCmd_SSLOpen(UINT8 *ptr);
UINT8
AppS2wCmd_SSLClose(UINT8 *ptr);

UINT8
AppS2wCmd_Wrate(UINT8 *ptr);

UINT8
AppS2wCmd_Verbose(UINT8 *ptr);

UINT8
AppS2wCmd_Echo(UINT8 *ptr);

UINT8
AppS2wCmd_Acmode(UINT8 *ptr);

UINT8
AppS2wCmd_PowerSaveDpsleep(UINT8 *ptr);
UINT8
AppS2wCmd_PowerSaveStby(UINT8 *ptr);

UINT8
AppS2wCmd_CidInfo(UINT8 *ptr);

#ifdef FTW_GSLINK

#ifdef FTW_GSLINK_XML

UINT8
AppS2wCmd_XmlSend(UINT8 * ptr);

UINT8
AppS2wCmd_XmlParseEnable(UINT8 * ptr);
#endif
#endif


#if defined(FTW_GSLINK) && defined(FTW_WEB_SERVER)

UINT8
AppS2wCmd_CfgUri(UINT8 * ptr);

#endif

UINT8
AppS2wCmd_BattCheckStart(UINT8 *ptr);

UINT8
AppS2wCmd_BattLvlSet(UINT8 *ptr);
UINT8
AppS2wCmd_BattValueGet(UINT8 *ptr);
UINT8
AppS2wCmd_BattCheckSet(UINT8 *ptr);
UINT8
AppS2wCmd_BattCheckStop(UINT8 *ptr);

UINT8
AppS2wCmd_ArpCacheEn(UINT8 *ptr);

UINT8
AppS2wCmd_ArpCacheDel(UINT8 *ptr);
#ifdef FTW_PING_TRACE
UINT8
AppS2wCmd_Ping(UINT8 *ptr);
#endif
UINT8
AppS2wCmd_TraceRoute(UINT8 *ptr);

#ifdef GSN_RAW_TRANSMISSION_ENABLE
UINT8
S2w_CmdNRAWState(UINT8 *ptr);
#endif


UINT8
S2w_CmdBulkDataState(UINT8 *ptr);
#ifdef FTW_WEB_PROV

UINT8
AppS2wCmd_WebLogoAdd(UINT8 *ptr);


UINT8
APPS2wCmd_WebProv(UINT8 *ptr);

UINT8
APPS2wCmd_AddRedirURI(UINT8 *ptr);

#endif /*FTW_WEB_PROV*/

UINT8
S2w_CmdUnSolicitedTx(UINT8 *ptr);
#ifdef FTW_RFTEST
UINT8
S2w_CmdRfTxStart(UINT8 *ptr);
UINT8
S2w_CmdRfWTxStart(UINT8 *ptr);
UINT8
S2w_CmdRfRxStart(UINT8 *ptr);
UINT8
S2w_CmdRfStop(UINT8 *ptr);

#endif

#ifdef GSN_MEM_TRACE
UINT8
AppS2wCmd_memTraceGet(UINT8 *ptr);
#endif
UINT8
AppS2wCmd_Settings(UINT8 *ptr);

VOID
AppS2wProfile_Display(FTW_PROFILE_T *profile);
UINT8
AppS2wCmd_ConfigOutput(UINT8 *ptr);
UINT8
S2w_CmdExtPASet(UINT8 *ptr);
UINT8
AppS2wCmd_psPollIntervelset(UINT8 *ptr);
UINT8
AppS2wCmd_ErrorCount(UINT8 *ptr);
UINT8
AppS2wCmd_DnsLookup(UINT8 *ptr);

UINT8
AppS2w_HangUp(void);
UINT8
AppS2wCmd_Restore(UINT8 *ptr);
UINT8
AppS2wCmd_Help(UINT8 *ptr);
UINT8
AppS2wCmd_AutoConnectLayer4(UINT8 *ptr);
UINT8
S2w_CmdSyncLossIntrvlSet(UINT8 *ptr);
UINT8
App2wCmd_Version(UINT8* ptr);

UINT8
AppS2wCmd_SystemTimeGet(UINT8 *ptr);

UINT8
AppS2wCmd_Wstatus(UINT8 *ptr);

UINT8
AppS2wCmd_Nmac2(UINT8 *ptr);
UINT8
AppS2wCmd_Wrssi(UINT8 *ptr);

UINT8
AppS2wCmd_DnsSrvSet(UINT8 *ptr);

UINT8
AppS2wCmd_ieeePsPollSet(UINT8 *ptr);

UINT8
AppS2wCmd_ntpTimeSet(UINT8 *ptr);

#ifdef  FTW_FS_SPI_ENABLE
UINT8
AppS2wCmd_SpiConfig(UINT8 *ptr);
#endif
UINT8
AppS2wCmd_RegDomainSet(UINT8 *ptr);

#ifdef FTW_CODE_COVERAGE
UINT8
AppS2wCmd_codeCvg01(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg02(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg03(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg04(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg05(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg06(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg07(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg08(UINT8 *ptr);
UINT8
AppS2wCmd_codeCvg09(UINT8 *ptr);
#endif

 UINT8
AppS2wCmd_SslCertificateAdd(UINT8 *ptr);
 UINT8
AppS2wCmd_SslCertificateDelete(UINT8 *ptr);
#ifdef FTW_HTTPC_SUPPORT
UINT8
AppS2wCmd_HttpClientSend(UINT8 *ptr);

 UINT8
AppS2wCmd_HttpClientOpen(UINT8 *ptr);

 UINT8
AppS2wCmd_HttpClientClose(UINT8 *ptr);

 UINT8
AppS2wCmd_HttpClientConfig(UINT8 *ptr);
 UINT8
AppS2wCmd_HttpClientConfigDel(UINT8 *ptr);
#endif

UINT8
AppS2wCmd_SystemTimeSet(UINT8 *ptr);

UINT8
AppS2wCmd_Wretry(UINT8 *ptr);

UINT8
AppS2wCmd_Wpower(UINT8 *ptr);

UINT8
AppS2wCmd_PowerSave(UINT8 *ptr);

#ifdef GS1500M
PUBLIC UINT8
AppS2wCmd_AntennaSet(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_AggregationSet(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_KeepAliveSet(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_WStatsGet(UINT8 *ptr);

#endif

UINT8
AppS2wCmd_scanTimeSet(UINT8 *ptr);
#endif

UINT8
AppS2wCmd_AssocPSModeSet( UINT8* ptr);

UINT8
AppS2wCmd_Psk(UINT8 *ptr);

UINT8
AppS2wCmd_ApClientInfoGet(UINT8* ptr);

UINT8
AppS2w_CmdL2ConfigSet(UINT8 * ptr);
UINT8
AppS2wCmd_McastRecvSet(UINT8 *ptr);

UINT8
AppS2wCmd_SecuritySet(UINT8 *ptr);
#ifdef GSN_EXTERNAL_FLASH_FWUP
UINT8
AppS2wCmd_OtaFwupConf(UINT8* ptr);
UINT8
AppS2wCmd_OtaFwupExtFlashStart(UINT8* ptr);
#endif

#ifdef FTW_PWM_SUPPORT
UINT8
AppS2wCmd_PwmStart(UINT8 *ptr);
UINT8
AppS2wCmd_PwmStop(UINT8 *ptr);
UINT8
AppS2wCmd_PwmCtrl(UINT8 *ptr);

#endif

VOID
s2wAutoExit_CB(UINT8 status, VOID* ctxt);

UINT8
AppS2wCmd_ArpEntryGet(UINT8 *ptr);
UINT8
AppS2wCmd_ErrorCode(UINT8* ptr);

UINT8
AppS2wCmd_IdOutput(UINT8 *ptr);

VOID S2w_AsyncMsgGpioOp(UINT8 flag);
UINT8
AppS2wCmd_Acmode(UINT8 *ptr);
UINT8
AppS2wCmd_AutoConnect(UINT8 *ptr);
UINT8
AppS2wCmd_GoOnline(UINT8 *ptr);

UINT8
AppS2wCmd_ApConf(UINT8* ptr);

#ifdef FTW_MEM_ACCESS

UINT8
AppS2wCmd_MemRead(UINT8 *ptr);

UINT8
AppS2wCmd_MemWrite(UINT8 *ptr);

#endif

VOID
AppS2wHdrAndIpv4_Print();

VOID
AppS2w_XmlDataProcess(UINT8 cid,UINT8 *dataBuffer,UINT32 inBuflen,UINT32 elementType);
#ifdef  FTW_NCM_SUPPORT_ENABLE
UINT8
AppS2wCmd_NcmAuto(UINT8* ptr);
UINT8
AppS2wCmd_NcmAutoConf(UINT8* ptr);
#endif //NCM_SUPPORT_ENABLE
VOID S2w_AsyncMsgGpioInit();
VOID
AppS2wHelp_Print(const char *cmd, const char *desc);

VOID
AppS2wHal_MdnsDeInit();

PUBLIC GSN_STATUS
S2wHttp_Send(UINT8 cid);
PUBLIC UINT8 AppS2w_ConnStateGet(UINT8 cid);
PUBLIC UINT8 AppS2w_ConnHttpStateGet(UINT8 cid);
PUBLIC VOID
AppS2wProcess_AutoStart(VOID);
VOID
AppS2w_WebServerStop();
PUBLIC VOID
AppS2w_DeepSleepHandler(VOID);

#ifdef FTW_OTP_RDWR_SUPPORT
UINT8
AppS2wCmd_AppOtpWrite (UINT8 *ptr);
#endif
UINT8
AppS2wCmd_AppOtpRead (UINT8 *ptr);

UINT8
otpMac_Read(UINT8* mac, UINT8 id);
UINT8
AppS2wCmd_LogLevelSet(UINT8* ptr);
UINT8 AppS2w_DtslClientOpen(UINT8 cliCid, char* caCertName,
                           UINT8 *clientCertName, UINT8 *clientKeyName);

#ifdef FTW_EXTFLASH_DRIVER_TEST
PUBLIC UINT32
AppS2wExternalFlashData(UINT8 ch1);
#endif

VOID
FTW_UnassocDataIndCB(VOID *ctx, INT8 *data, UINT16 dataLen);
PUBLIC GSN_STATUS
s2wUamRx_Init();
VOID
S2w_UamRx(void *buf, INT16 len);

PUBLIC UINT8
AppS2wCmd_NwConnStore(UINT8 *ptr);

UINT8
APPS2wCmd_WebProv(UINT8 *ptr);
UINT8
APPS2wCmd_WebProvStop(UINT8 * ptr);

#if   defined(FTW_FS_SPI_ENABLE) || defined(FTW_FS_SPI_HI_ENABLE)
PUBLIC UINT8
AppS2wCmd_SpiConfig(UINT8 *ptr);
#endif

UINT8
S2w_CmdUnSolicitedCcaConf(UINT8 *ptr);

#ifdef FTW_FTC
PUBLIC UINT8
AppS2wCmd_FtcSdAdc(UINT8 * ptr);

PUBLIC UINT8
AppS2wCmd_FtcSarAdc(UINT8 * ptr);
PUBLIC UINT8
AppS2wCmd_FtcExtFlashID(UINT8 * ptr);
PUBLIC UINT8
AppS2wCmd_rftcExtFlashID(UINT8 * ptr);
PUBLIC UINT8
AppS2wCmd_rFtcSarAdc(UINT8 * ptr);
PUBLIC UINT8
AppS2wCmd_rFtcSdAdc(UINT8 * ptr);
#endif
