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
#ifndef S2W_COMMAND_H
#define S2W_COMMAND_H

UINT8 AppS2wProcess_AutoConnectStart(S2W_PROFILE_T *profile);
UINT8
AppS2wProcess_AutoConnectStop(S2W_PROFILE_T *profile);
UINT8 AppS2wCommand_Process(UINT8 *cmd);
VOID AppS2wProcess_LoadProfile(UINT8 profile_num);
PUBLIC VOID
AppS2wProcess_AsyncStatusNotify(UINT8 status, UINT32 arg);
VOID
AppS2wHdrAndIp_Print();

extern UINT8 s2wIsAutoconnected;
extern S2W_FLASH_PARAMS_T *s2wFlashParams;

#define S2W_HTTP_METHOD_GETRESP 6
#define S2W_HTTP_METHOD_POSTRESP 7
#define S2W_HTTP_METHOD_POST GSN_HTTP_METHOD_POST
#define S2W_HTTP_METHOD_GET GSN_HTTP_METHOD_GET

#ifdef S2W_HTTP_CUSTOM_SUPPORT
enum S2W_XML_ELEMENT_TYPE_IDS
{
    S2W_HTTP_REQUEST_LINE = 9991,
    S2W_HTTP_HEADER,
    S2W_HTTP_CGI_PARAMS,
    S2W_HTTP_RESPONSE_LINE,
	S2W_XML_ELEMENT_TYPE_START_ID = 9995,
    S2W_XML_ATTRIBUTE_ID,
	S2W_XML_COMPLEX_TAG_END_ID,
	S2W_XML_COMPLEX_TAG_START_ID,
	S2W_XML_ELEMENT_TYPE_END_ID
};
#else
enum S2W_XML_ELEMENT_TYPE_IDS
{
	S2W_XML_ELEMENT_TYPE_START_ID = 9995,
    S2W_XML_ATTRIBUTE_ID,
	S2W_XML_COMPLEX_TAG_END_ID,
	S2W_XML_COMPLEX_TAG_START_ID,
	S2W_XML_ELEMENT_TYPE_END_ID
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


enum S2W_STATE
{
    S2W_STATE_CMD,
    S2W_STATE_DATA,
    S2W_STATE_DATA_ESC,
    S2W_STATE_CMD_ESC,
    S2W_STATE_CID,
    S2W_STATE_RAW,
    S2W_STATE_RAW_DATA,
    S2W_STATE_ASYNC_TX,
    S2W_STATE_UNSOLICITED_HDR,
    S2W_STATE_UNSOLICITED_DATA,
    S2W_STATE_IPPORT,
    S2W_STATE_IP_STRING,
    S2W_STATE_PORT_STRING,
    S2W_STATE_DATA_AUTO,
    S2W_STATE_CERT,
    S2W_STATE_WEB_LOGO,
    S2W_STATE_HTTP_CONTENT_CID,
    S2W_STATE_COAP_CONTENT_CID,
    S2W_STATE_HTTP_CONTENT_DATA,
    S2W_STATE_BULK_DATA,
    S2W_STATE_FWRITE,
	
   S2W_STATE_GSLINK_RECV,
   
	S2W_STATE_GET_CID,
    S2W_STATE_XML_LEN,
    S2W_STATE_XML_PROCESS,
    S2W_STATE_BUFF_STORE,
    S2W_STATE_EXTFLASH
};


enum S2W_OTAFWUP_IDS
{
    S2W_OTAFWUP_SRVRIP,
    S2W_OTAFWUP_SRVRPORT,
    S2W_OTAFWUP_PROXY_PRESENT,
    S2W_OTAFWUP_PROXY_SRVRIP,
    S2W_OTAFWUP_PROXY_SRVRPORT,
    S2W_OTAFWUP_SSL_ENABLED,
    S2W_OTAFWUP_CERT_NAME,
    S2W_OTAFWUP_APP_IMAGE_URL,
    S2W_OTAFWUP_INFO_URL,
    S2W_OTAFWUP_SRVR_HOST_NAME,
    S2W_OTAFWUP_APP_SIGN_URL,
    S2W_OTAFWUP_APP_ENABLE_DNS_ERR
};

enum S2W_OTAFU_URL_IDS
{
	S2W_OTAFU_URL_FW_IMAGE,
	S2W_OTAFU_URL_XML,
	S2W_OTAFU_URL_SIGN_IMAGE,
};
extern enum S2W_STATE s2wState;

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

#ifdef S2W_GSLINK

#ifdef S2W_GSLINK_XML

UINT8
AppS2wCmd_XmlSend(UINT8 * ptr);

UINT8
AppS2wCmd_XmlParseEnable(UINT8 * ptr);
#endif
#endif


#if defined(S2W_GSLINK) && defined(S2W_WEB_SERVER)

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
#ifdef S2W_PING_TRACE
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
#ifdef S2W_WEB_PROV

UINT8
AppS2wCmd_WebLogoAdd(UINT8 *ptr);


UINT8
APPS2wCmd_WebProv(UINT8 *ptr);

UINT8
APPS2wCmd_AddRedirURI(UINT8 *ptr);

#endif /*S2W_WEB_PROV*/

UINT8
S2w_CmdUnSolicitedTx(UINT8 *ptr);
#ifdef S2W_RFTEST
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
AppS2wProfile_Display(S2W_PROFILE_T *profile);
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

#ifdef  S2W_FS_SPI_ENABLE
UINT8
AppS2wCmd_SpiConfig(UINT8 *ptr);
#endif
UINT8
AppS2wCmd_RegDomainSet(UINT8 *ptr);

#ifdef S2W_CODE_COVERAGE
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
#ifdef S2W_HTTPC_SUPPORT
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

#ifdef S2W_PWM_SUPPORT
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

#ifdef S2W_MEM_ACCESS

UINT8
AppS2wCmd_MemRead(UINT8 *ptr);

UINT8
AppS2wCmd_MemWrite(UINT8 *ptr);

#endif

UINT8
AppS2wHal_PowerSaveConfigSet();
VOID
AppS2wHdrAndIpv4_Print();

VOID
AppS2w_XmlDataProcess(UINT8 cid,UINT8 *dataBuffer,UINT32 inBuflen,UINT32 elementType);
#ifdef  S2W_NCM_SUPPORT_ENABLE
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

#ifdef S2W_OTP_RDWR_SUPPORT
UINT8
AppS2wCmd_AppOtpWrite (UINT8 *ptr);
#endif
UINT8
AppS2wCmd_AppOtpRead (UINT8 *ptr);


#ifdef S2W_DUAL_INTERFACE_SUPPORT
VOID AppS2wProcess_Serial2Input();
PUBLIC UINT8
AppS2wHal_UartCharGetNB(UINT8 *ch);
PUBLIC UINT8
AppS2wHal_UartCharGetNB1(UINT8 *ch);
VOID AppS2wHal_CharNGet1(UINT8*buf, UINT32 len);
VOID AppS2wHal_CharNPut1(const void *buf, UINT32 len);
UINT8 AppS2wHal_CharGet1(UINT8*buf);
#endif

UINT8
otpMac_Read(UINT8* mac, UINT8 id);
UINT8
AppS2wCmd_LogLevelSet(UINT8* ptr);
UINT8 AppS2w_DtslClientOpen(UINT8 cliCid, char* caCertName,
                           UINT8 *clientCertName, UINT8 *clientKeyName);

#ifdef S2W_EXTFLASH_DRIVER_TEST
PUBLIC UINT32
AppS2wExternalFlashData(UINT8 ch1);
#endif

VOID
S2W_UnassocDataIndCB(VOID *ctx, INT8 *data, UINT16 dataLen);
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

#if   defined(S2W_FS_SPI_ENABLE) || defined(S2W_FS_SPI_HI_ENABLE)
PUBLIC UINT8
AppS2wCmd_SpiConfig(UINT8 *ptr);
#endif

UINT8
S2w_CmdUnSolicitedCcaConf(UINT8 *ptr);

#ifdef S2W_FTC
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
