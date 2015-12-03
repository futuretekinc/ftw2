/*****************************************************************
 *
*               COPYRIGHT (c) 20012-2013 GainSpan Corporation
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
* $RCSfile: s2w_general_command.c,v $
*
* Description : s2w command interprter file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include "time.h"
#include <ctype.h>
#include <string.h>
#include "gsn_includes.h"
#include "gsn_version.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "hal/s2w_timer.h"
#include "parser/s2w_parse.h"
#include "parser/s2w_process.h"
#include "parser/s2w_command.h"
#include "hal/s2w_net.h"
#include "main/app_main_ctx.h"

#include "config/app_ncm_config.h"
#include "config/app_resource_config.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_cert_mgmt.h"
#include "modules/http/gsn_httpc.h"

#include "config/app_stat_config.h"
#include "app_rtc_mem.h"
#include "app_events.h"
#include "app_defines_builder.h"
#include "fs/api/api_safe.h"

#include "hal/s2w_config.h"

#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/flashdrv.h"

#include "gslink\app_mcu_def.h"

#include "app_rtc_mem.h"
#include "emu/app_emu.h"

#include "gsn_ncm.h"
#include "gsn_ncm_roam.h"
#include "modules/pwr_mgmt/gsn_pwr_mgmt.h"

#include "modules/coap/gsn_coap.h"
#include "modules/coap/gsn_coap_impl.h"

#include "clk_tune/app_clk_tune.h"
#ifdef S2W_IPv6_SUPPORT
#include "modules/dhcpv6_server/gsn_dhcpv6_server.h"
#endif
#include "ext_app/app_ext_flash.h"
#include "main/gsn_br_flashldr.h"
#include "modules/fwup/gsn_fwup.h"
/**
 ******************************************************************************
 * @file s2w_general_command.c
 * @brief s2w Application command file.
 *    This file contains the function implementation for each AT command.
 ******************************************************************************/

/*****************************************************************************
  *  Public Variables
  ****************************************************************************/
//#define EXTFLASH_DRIVER_TEST
//#define EXT_FLASH_CMD_ENABLE
extern S2W_PROFILE_PARAMS_T profile_params;
UINT8 s2wWepKeyAscii =0;
extern S2W_EXTFLASH_CMD_T s2wExtFlashCmdTable[6];
#ifdef S2W_SECURITY_WPS_ENABLE
extern UINT32 wpsConnDone;
#endif
extern UINT8 curCid;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
UINT32 certIndex = S2W_INVALID_CERT_INDEX, certFormat, certFileSize;
F_FILE *certFile;


extern GSN_OSAL_SEM_T s2wL2L3ConnectSemaphore;

extern S2W_CID_T s2wCidList[];

#ifdef S2W_PING_TRACE
UINT8 s2wPingStarted;
#endif
extern UINT8 s2wUserInitNetOpen;
extern S2W_SSL_CERT_SRAM_TABLE_T s2w_ssl_cert_table[];
extern S2W_LINK_STATE_T s2wLinkState ;
extern S2W_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle;
extern S2W_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle1;

extern GSN_OSAL_SEM_T stbyDelaySemaphore;
#ifdef S2W_NCM_SUPPORT_ENABLE
extern S2W_TIMER_T acNcmTimer;
#endif


NXD_ADDRESS             DNSv6ServerAddr[2];
UINT32                  DNSv4ServerAddr[2];
UINT8                   S2W_DNS_CLIENT_FALGS;

#define S2W_DNS_CLIENT_ENABLED          0x01
#define S2W_DNSv6_SERVER_SET            0x02
#define S2W_DNSv4_SERVER_SET            0x04
#define S2W_DNS_REQ_DEF_TIME_OUT        5
#define S2W_DNS_REQ_DEF_RETRIES         3


UINT8 stbySuccess=0;
UINT32 apModeBeaconIntrl=100;
UINT8 globalUseHRssi=0;
/*__no_init*/ S2W_PROFILE_T s2wCurrent;

#ifdef S2W_DNS_SERVER_ENABLE
GSN_DNS_SERVER_T dnsServer;
#endif

#ifdef S2W_DHCP_SERVER_ENABLE


UINT8 dhcpServerFlags;
__no_init GSN_DHCP_SRVR_T dhcpSrvr;
__no_init GSN_DHCP_SRVR_CFG_T dhcpSrvrCfg;

#endif

#ifdef S2W_IPv6_SUPPORT
GSN_DHCPv6_SERVER_T serverId;
#endif

UINT32 S2wL3Wait;
extern GSN_OSAL_SEM_T s2wL2L3ConnectSemaphore;


#define HTTP_SEND_CHUNK_SIZE    1000

/* data structure to hold current wireless info
 */
S2W_WLANINFO_T current_wlan_info;

#ifdef S2W_EMU
/*buffers to for emu*/
__no_init UINT16 s2w_emu_buf1[1000],s2w_emu_buf2[1000],s2w_emu_buf3[1000],s2w_emu_buf4[1000];
UINT32 adcSize = 1000;

#endif

#ifdef S2W_PING_TRACE

PUBLIC GSN_OSAL_QUEUE_T pingThreadMsgQueue;
UINT8 * pingThreadMsgQueueBuf;

PRIVATE GSN_OSAL_THREAD_TCB_T pingThread;

UINT8 * pingThreadStack;
UINT32 pingThreadCreated = 0;

#endif

/*****************************************************************************
  *  Private Variables
  ****************************************************************************/

/*   Structure definitions for command table   */
struct S2W_CMD
{
    const char *cmd;                /**< Command string */
    UINT8 (*process) (UINT8 *ptr);  /**< Command handler */
};


/*****************************************************************************
  *  Private Definitions
  ****************************************************************************/


    
#define S2W_MAX_CH 11   
extern GSN_OSAL_SEM_T stScanSemaphore;
extern UINT8 s2wAutoConnState ;

extern VOID
AppMcu_RespTimeoutCb( VOID* context,GSN_SOFT_TMR_HANDLE_T timerHandle );
extern VOID
App_InterfaceStop(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
extern VOID
App_InterfaceStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
extern VOID
App_IfReinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

extern S2W_SCAN_DISPLAY_INFO_T scanDisplayInfo[20];

UINT8 scanDisplayInfoCount=0,scanDisplayAllCount=0;

__no_init GSN_WDD_SCAN_ENTRY_T s2wScanUserEntryBuff[2];

void S2w_getDhcpv6Clientconfig(GSN_NWIF_DHCP_PARAMS_T *dhcpv6Params);

VOID AppS2w_ConctCbProcess(VOID* ctext,INT32 status);
extern void nx_dns_retry_count_set(NX_DNS *dns_ptr,UINT retries);

void GsnHeIf_DriverSuspend();
extern INT8 GsnIntTempSen_Get();

/*****************************************************************************
  *  Private Functions
  ****************************************************************************/


VOID
AppS2wRegisters_Display(const S2W_PROFILE_T *profile);
PRIVATE UINT8
AppS2wCmd_Wmode(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Wscan(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Wassoc(UINT8 *ptr);


PRIVATE UINT8
AppS2wCmd_Write(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_read(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Nset(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Nmac(UINT8 *ptr);

UINT8
AppS2wCmd_OtaFwupConf(UINT8* ptr);

UINT8
AppS2wCmd_OtaFwupExtFlashStart(UINT8* ptr);

UINT8
AppS2wCmd_OtaFwupRollBack(UINT8* ptr);

#ifdef S2W_UART_ENABLE
PRIVATE UINT8
AppS2wCmd_BaudRate(UINT8 *ptr);
PRIVATE UINT8
AppS2wCmd_UartFifoLevel(UINT8 * ptr);

#endif

PRIVATE UINT8
AppS2wCmd_SetDefaultProfile(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Disconnect(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Factory(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Wradio(UINT8 *ptr);

#ifndef S2W_IP2WIFI_SUPPORT
PRIVATE UINT8
AppS2wCmd_Ndhcp(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_Nstat(UINT8 *ptr);
#endif
UINT8




AppS2wCmd_FsTest(UINT8 * ptr);

#if 0
PRIVATE UINT8
AppS2wCmd_SslCertificateOpen(UINT8 *ptr);
#endif

#ifdef S2W_UART_ENABLE
PRIVATE UINT8
AppS2wCmd_HardFlow(UINT8 *ptr);
#endif

PUBLIC UINT8
AppS2wCmd_Dgpio(UINT8 *ptr);

UINT8
AppS2wCmd_reset(UINT8* ptr);

PUBLIC UINT8
AppS2wCmd_SetSockOp(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_AsyncMsgFmt(UINT8 *ptr);

extern APP_MAIN_CTX_T appCtx;
extern UINT32 nwConfigSuccess;

PUBLIC UINT8
AppS2wCmd_RfTestStop (UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestStart (UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestTxStart(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestTx99Start(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestTx100Start(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestCarrierWaveStart(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestRxStart(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestTxStop (UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_RfTestRxStop (UINT8 *ptr);
PUBLIC UINT8 AppS2wCmd_WlanCalib (UINT8 *ptr);

#ifdef S2W_OTP_RDWR_SUPPORT
UINT8
AppS2wCmd_WlanOtpWrite (UINT8 *ptr);
#endif
UINT8
AppS2wCmd_WlanOtpRead (UINT8 *ptr);

/* private functions used for call back
 */

VOID PRIVATE
s2wApp_ConnectCb(VOID* ctext, INT32 status);

VOID
AppS2w_WlanRespTmrCb(VOID * context,GSN_SOFT_TMR_HANDLE_T timerHandle);

VOID DHCP_notify(INT32 status,void *ctx);

#ifdef S2W_SNTP
UINT8
AppS2wCmd_ntpTimeSet(UINT8 *ptr);
#endif

PRIVATE UINT8
AppS2wCmd_Weap(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_WeapConf(UINT8 *ptr);

UINT8
AppS2wCmd_BeaconMissThresholdSet(UINT8 *ptr);

UINT8
AppS2wCmd_TkipContrMsrStart(UINT8 *ptr);

UINT8
AppS2wCmd_TkipSeqNumGet(UINT8 *ptr);

UINT8
AppS2wCmd_WlanStatsGet(UINT8 *ptr);

UINT8
AppS2wCmd_WlanRecvFiltrSet(UINT8 *ptr);

UINT8
AppS2wCmd_RtsEnable(UINT8 *ptr);

UINT8
AppS2wCmd_BlockAckReq(UINT8 *ptr);

UINT8
AppS2wCmd_AmsduReqt(UINT8 *ptr);

UINT8
AppS2wCmd_AmpduReq(UINT8 *ptr);

UINT8
AppS2wCmd_FrameTxFailCntLmitSet(UINT8 *ptr);

UINT8
AppS2wCmd_SecuritySet(UINT8 *ptr);

UINT8
AppS2wCmd_Wauth(UINT8 *ptr);

UINT8
AppS2wCmd_Wwpa(UINT8 *ptr);

UINT8
AppS2wCmd_WpaPsk(UINT8 *ptr);

UINT8
AppS2wCmd_Psk(UINT8 *ptr);

UINT8
AppS2wCmd_Wwep(UINT8 *ptr);
UINT8
AppS2wCmd_WwepConf(UINT8 *ptr);

UINT8
AppS2wCmad_WsrvrValidationEn(UINT8 *ptr);

UINT8
AppS2wCmad_WeapTimeChk(UINT8 *ptr);

VOID
AppS2wHal_PsHibernateRequest(S2W_ALARM_INFO_T *alarm);

UINT8 AppS2wCmd_Hibernate(UINT8 *ptr);

#ifdef S2W_COAP_SUPPORT

typedef struct S2W_COAP_OPTION
{
	UINT8 optionKey;
	char *optionValue;
	struct S2W_COAP_OPTION * next;
}S2W_COAP_OPTION_T;

S2W_COAP_OPTION_T * optionHead;

#define COAP_POST "POST"
#define COAP_GET "GET"
#define COAP_CON "CON"
#define COAP_NON "NON"
#define COAP_MAX_RESPONSE_TIMEOUT 60
PRIVATE UINT8
AppS2wCmd_CoapOpen(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_CoapClose(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_CoapSetOption(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_CoapRemoveOption(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_CoapSend(UINT8 *ptr);

GSN_COAP_CONTEXT_T*
AppS2wHal_CoapHandleGet(UINT8 cid);

PUBLIC GSN_COAP_CONN_PARAMS_T*
AppS2wHal_CoapParamsGet(UINT8 cid);
#endif

extern UINT8
AppS2wCmd_MdnsInit(UINT8 *ptr);
#ifdef S2W_IPv6_SUPPORT
extern UINT8
AppS2wCmd_MdnsInitv6(UINT8 *ptr);
#endif
extern UINT8
AppS2wCmd_MdnsDeInit(UINT8 *ptr);
extern UINT8
AppS2wCmd_MdnsHostNameReg(UINT8 *ptr);
extern UINT8
AppS2wCmd_MdnsServiceReg(UINT8 *ptr);
extern UINT8
AppS2wCmd_MdnsHostNmDeReg(UINT8 *ptr);
extern UINT8
AppS2wCmd_MdnsSrvDeReg(UINT8 *ptr);
extern  UINT8
AppS2wCmd_MdnsAnnounce(UINT8 *ptr);
extern UINT8
AppS2wCmd_MdnsAnnounceAll(UINT8 *ptr);
extern UINT8
AppS2wCmd_MdnsSrvcDiscover(UINT8 *ptr);
#if defined (S2W_GSLINK) && defined (S2W_WEB_SERVER)
extern UINT8
AppS2wCmd_WebServer(UINT8* ptr);
#endif

UINT8
AppS2wCmd_Wphymode(UINT8* ptr);

#ifdef S2W_IPv6_SUPPORT

UINT8
AppS2wCmd_Nsetv6(UINT8* ptr);

UINT8
AppS2wCmd_Ndhcpv6(UINT8 *ptr);

#ifdef S2W_PING_TRACE
UINT8
AppS2wCmd_Ping(UINT8* ptr);
#endif
UINT8
AppS2wCmd_Ncudpv6(UINT8* ptr);

UINT8
AppS2wCmd_Nsudpv6(UINT8* ptr);

UINT8
AppS2wCmd_Nctcpv6(UINT8* ptr);

UINT8
AppS2wCmd_Nstcpv6(UINT8* ptr);

UINT8
AppS2wCmd_Dhcpv6Server(UINT8 *ptr);
#endif //S2W_IPv6_SUPPORT

#ifdef S2W_DNS_CLIENT

UINT8
AppS2wCmd_DnsLookup(UINT8 *ptr);

#ifdef S2W_IPv6_SUPPORT
UINT8
AppS2wCmd_DnsLookupv6(UINT8 *ptr);
#endif
UINT8
AppS2wCmd_DnsServerSet(UINT8 *ptr);

#endif //S2W_DNS_CLIENT

#ifdef S2W_HTTP_CUSTOM_SUPPORT
extern UINT8
AppS2wCmd_RecvConf(UINT8 *ptr);
#endif

#ifdef S2W_GSLINK
VOID
AppS2w_HttpdBodyLenSet(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT32 len);

VOID
AppS2w_HttpdMethodSet(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT8 method);
#endif

PUBLIC GSN_STATUS
APPS2w_ExtFlashStart( S2W_OTA_FWUP_CONF_T *pOtaFwupConf);

UINT8
AppS2wCmd_PowerSaveStby(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_NwConnRestore();



extern VOID
AppS2wCmd_GetSecurityString(GSN_WDD_WLAN_CFG_T *WddConf,const char **security );
UINT8
AppS2wCmd_Wauto(UINT8* ptr);
UINT8
AppS2wCmd_Nauto(UINT8* ptr);

#ifdef S2W_DHCP_SERVER_ENABLE
PUBLIC UINT8
AppS2wCmd_DhcpSrvrConfig(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_DhcpSrvr(UINT8 *ptr);
#endif //S2W_DHCP_SERVER_ENABLE


PUBLIC UINT8
AppS2wCmd_IpMulticastJoin(UINT8 *ptr);

PUBLIC UINT8
AppS2wCmd_IpMulticastLeave(UINT8 *ptr);

UINT8
AppS2wCmd_SoftFlow(UINT8 *ptr);

UINT8
AppS2wCmd_ApClientInfoGet(UINT8 *ptr);

#ifdef S2W_THROUGHPUT_TEST
UINT8
AppS2wCmd_SockTpTest(UINT8 *ptr);
UINT8
AppS2wCmd_SockTpTestStat(UINT8 * ptr);
#endif

extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;


#ifdef S2W_SECURITY_WPS_ENABLE
PRIVATE UINT8
AppS2wCmd_Wwps(UINT8 *ptr);
#endif

#ifdef S2W_EMU
PRIVATE UINT8
AppS2wCmd_EmuVer(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_SupportedModules(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuStart(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuStop(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuGetValues(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuGetConf(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuSetConf(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuLoadCtl(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuResetEnergy(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuGetStatus(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuGetInstValues(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuLoadStatus(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_EmuPrint(UINT8 *ptr);

#endif

/*Commands for adc*/

#ifdef S2W_ADC_SUPPORT
#ifndef GS2100 // adc is not there in 2100
PRIVATE UINT8
AppS2wCmd_AdcConf(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_AdcStart(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_AdcRead(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_AdcStop(UINT8 *ptr);
#endif
#endif

PUBLIC UINT8 
AppS2wCmd_PerstTmrStart(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_PerstTmrStop(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_PerstTmrDelete(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_PerstTmrReStart(UINT8 *ptr);

#ifdef S2W_ISOTX_SUPPORT
UINT8
AppS2wCmd_IsoTxStart(UINT8 *ptr);
UINT8
AppS2wCmd_IsoTxStop(UINT8 *ptr);
UINT8
AppS2wCmd_IsoTxConfig(UINT8 *ptr);
#endif

#ifdef S2W_UNASSOC_TXRX_SUPPORT
UINT8
S2w_CmdUnSolicitedTx(UINT8 *ptr);
UINT8
S2w_CmdUnSolicitedRx(UINT8 *ptr);
UINT8
S2w_CmdUnSolicitedRxstop(UINT8 *ptr);
#endif
#ifdef S2W_SNTP
PRIVATE VOID
S2wApp_TimeSyncDoneCb(INT32 msg, VOID* context);

PRIVATE VOID
AppS2w_sntpTimerCb( VOID* context,
    GSN_SOFT_TMR_HANDLE_T timerHandle );
#endif
#ifdef S2W_15DOT4_SUPPORT
UINT8
AppS2wCmd_154Channel(UINT8 *ptr);

UINT8
AppS2wCmd_154PanId(UINT8 *ptr);

UINT8
AppS2wCmd_154ShortAddr(UINT8 *ptr);

UINT8
AppS2wCmd_154ExtendedAddr(UINT8 *ptr);

UINT8
AppS2wCmd_154RetryCount(UINT8 *ptr);

UINT8
AppS2wCmd_154JoinPermit(UINT8 *ptr);

UINT8
AppS2wCmd_154SupreFrmCfg(UINT8 *ptr);
UINT8
AppS2wCmd_154CoordExtndedAddr(UINT8 *ptr);
UINT8
AppS2wCmd_154CoordShortAddr(UINT8 *ptr);

UINT8
AppS2wCmd_154ScanNetwork(UINT8 *ptr);

UINT8
AppS2wCmd_154JoinNetwork(UINT8 *ptr);

UINT8
AppS2wCmd_154AddNode(UINT8 *ptr);

UINT8
AppS2wCmd_154StartNetwork(UINT8 *ptr);

UINT8
AppS2wCmd_154LeaveNetwork(UINT8 *ptr);

UINT8
AppS2wCmd_154PollData(UINT8 *ptr);

UINT8
AppS2wCmd_154DataSend(UINT8 *ptr);

UINT8
AppS2wCmd_154DataPurge(UINT8 *ptr);
UINT8
AppS2wCmd_154RxEnable(UINT8 *ptr);
PUBLIC UINT8 AppS2wCmd_I154RxTest (UINT8 *ptr);
PUBLIC UINT8 AppS2wCmd_I154RxTestStop (UINT8 *ptr);
PUBLIC UINT8 AppS2wCmd_I154TxTest (UINT8 *ptr);
UINT8
AppS2wCmd_154GTSReq(UINT8 *ptr);
UINT8
AppS2wCmd_154SetReq(UINT8 *ptr);
UINT8
AppS2wCmd_154GetReq(UINT8 *ptr);
UINT8
AppS2wCmd_154SyncReq(UINT8 *ptr);
#ifdef GSN_802_15_4_TEST_SUPPORT
UINT8 AppS2wCmd_154TmrReq(UINT8 *ptr);
UINT8
AppS2wCmd_154GenericTest(UINT8 *ptr);
#endif
#endif

#ifdef S2W_EXTFLASH_DRIVER_TEST
UINT8
AppS2wCmd_ExtFlashInit(UINT8* ptr);

UINT8
AppS2wCmd_ExtFlashWrite(UINT8* ptr);

UINT8
AppS2wCmd_ExtFlashRead(UINT8* ptr);

UINT8
AppS2wCmd_ExtFlashErase(UINT8* ptr);

UINT8
AppS2wCmd_ExtFlashChipErase(UINT8* ptr);

UINT8
AppS2wCmd_ExtFlashSpiConf(UINT8* ptr);

#endif

#if defined(S2W_DTLS_CLIENT_SUPPORT)
UINT8
AppS2wCmd_DTSLClose(UINT8 *ptr);

UINT8
AppS2wCmd_DTSLOpen(UINT8 *ptr);
#endif

UINT8
S2wRateValidation(UINT32 value);

extern UINT8
AppS2wCmd_WlanStaPsCfg(UINT8 *ptr);

extern  UINT8
AppS2wCmd_WlanApPsCfg(UINT8 *ptr);

UINT8
AppS2wCmd_ieeePsPollSet(UINT8 *ptr);
UINT8
S2w_CmdPsPollIntervelset(UINT8 *ptr);

UINT8
AppS2wCmd_ArpEntrySet(UINT8 *ptr);

UINT8
AppS2wCmd_ArpEntryDelete(UINT8 *ptr);

UINT8
AppS2wCmd_ArpAutoSet(UINT8 *ptr);

#ifdef S2W_I2C_SUPPORT
/*Commands to test I2C*/
PRIVATE UINT8
AppS2wCmd_I2cConf(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_I2cStart(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_I2cWrite(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_I2cRead(UINT8 *ptr);

PRIVATE UINT8
AppS2wCmd_I2cStop(UINT8 *ptr);
#endif
UINT8
AppS2wCmd_BaBitMapSet(UINT8* ptr);

UINT8
AppS2wCmd_RadioStateGet(UINT8* ptr);

UINT8 AppS2wCmd_ZipScan( UINT8 *ptr );
UINT8 AppS2wCmd_ZipStart( UINT8 *ptr );
UINT8 AppS2wCmd_ZipStop( UINT8 *ptr );
UINT8 AppS2wCmd_ZipSetMacAddr( UINT8 *ptr );

#ifdef S2W_ADC_SUPPORT
UINT8 App_ClkTuneCmd(UINT8 *ptr);
#endif

#ifdef GSN_MEM_TRACE
PUBLIC UINT8
AppS2wCmd_memTraceGet(UINT8 *ptr);
#endif

UINT8
AppS2wCmd_SetAssocTimeout(UINT8 *ptr);

INT32
App_TemperatureGet();

UINT8 
AppS2wCmd_TempGet(UINT8 *ptr);

UINT8 
AppS2wCmd_TempReadStart(UINT8 *ptr);

UINT8
AppS2wCmd_HwCryptoEn(UINT8 *ptr);

UINT8
AppS2wCmd_GratArpSend(UINT8 *ptr);



typedef enum S2W_ERROR_CODE
{
	S2W_ERROR_CODE_AP_NOT_FOUND = 1,
	S2W_ERROR_CODE_WLAN_FAIL_TO_CONCT = 2,
	S2W_ERROR_CODE_WPA_AUTH_FAILURE = 3,
}S2W_ERROR_CODE_T;
const char *S2WError_List[] =
{
	"\r\nNO ERROR",
	"\r\nSSID NOT FOUND",
	"\r\nWLAN CONNECT ERROR",
	"\r\nWPA AUTH FAIL",
};

#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)

UINT8
AppS2wCmd_SslConfig(UINT8 *ptr);

#endif

UINT8
AppS2wCmd_MqttStart(UINT8 *ptr);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Table contains all the Serial2WiFi Host commands and
 *        corresponding call backs to process the command.This array
 *        can be exteded to add more host commands.
 ******************************************************************/
PRIVATE const struct S2W_CMD s2wCmdTable[] =
{
    {"+WA=",        AppS2wCmd_Wassoc},
    {"+WPHYMODE=", AppS2wCmd_Wphymode},
    {"+BCONMISSTHRHLD=",   AppS2wCmd_BeaconMissThresholdSet},
    {"+TKIPCNTRMSR=",      AppS2wCmd_TkipContrMsrStart},
    {"+TKIPSEQSET=",   AppS2wCmd_TkipSeqNumGet},
    {"+WLANSTATS", AppS2wCmd_WlanStatsGet},
    {"+RXFILTER=",  AppS2wCmd_WlanRecvFiltrSet},
    {"+WRTS=",      AppS2wCmd_RtsEnable},
    {"+WBLOCKACK=",   AppS2wCmd_BlockAckReq},
    {"+WAMSDU=",     AppS2wCmd_AmsduReqt},
    {"+WAMPDU=",     AppS2wCmd_AmpduReq},
    {"+TXFAILLMT=", AppS2wCmd_FrameTxFailCntLmitSet},
#ifndef S2W_IP2WIFI_SUPPORT
    {"+NDHCP=",     AppS2wCmd_Ndhcp},
    {"+NSTAT=",     AppS2wCmd_Nstat},
    {"+CID=",       AppS2wCmd_CidInfo},
    {"+NCLOSEALL",  AppS2wCmd_Ncloseall},
    {"+NCLOSE=",    AppS2wCmd_Nclose},
#endif
    {"+WRXACTIVE=", AppS2wCmd_Wradio},
    {"+WRETRY=",    AppS2wCmd_Wretry},
#ifndef S2W_IP2WIFI_SUPPORT
    {"+NCTCP=",     AppS2wCmd_Nctcp},
    {"+NCUDP=",     AppS2wCmd_Ncudp},
    {"+NSTCP=",     AppS2wCmd_Nstcp},
    {"+NSUDP=",     AppS2wCmd_Nsudp},
#ifdef S2W_MDNS_ENABLE
    {"+MDNSSTART", AppS2wCmd_MdnsInit},
#ifdef S2W_IPv6_SUPPORT
    {"+MDNSv6START", AppS2wCmd_MdnsInitv6},
#endif
    {"+MDNSSTOP", AppS2wCmd_MdnsDeInit},
//    {"+MDNSANNOUNCE=", AppS2wCmd_MdnsAnnounceAll},
    {"+MDNSANNOUNCE",  AppS2wCmd_MdnsAnnounceAll},
    {"+MDNSHNREG=", AppS2wCmd_MdnsHostNameReg},
    {"+MDNSSRVREG=", AppS2wCmd_MdnsServiceReg},
    {"+MDNSSD=", AppS2wCmd_MdnsSrvcDiscover},
    {"+MDNSHNDEREG=", AppS2wCmd_MdnsHostNmDeReg},
    {"+MDNSSRVDEREG=", AppS2wCmd_MdnsSrvDeReg},
#endif
    {"+NXSETSOCKOPT=",  AppS2wCmd_SetSockOp},
#endif
    {"+NMAC=",      AppS2wCmd_Nmac},
    {"+WSEC=", AppS2wCmd_SecuritySet},
    {"+WAUTH=",     AppS2wCmd_Wauth},
    {"+WWPA=",  AppS2wCmd_Wwpa},
    {"+WPAPSK=", AppS2wCmd_WpaPsk},
    {"+WPSK=",   AppS2wCmd_Psk},
    {"+WWEPCONF=",   AppS2wCmd_WwepConf},
    {"+WWEP",   AppS2wCmd_Wwep},    
    {"+WSYNCINTRL=", S2w_CmdSyncLossIntrvlSet},
    {"+WSTATUS",	  AppS2wCmd_Wstatus},
    {"+WST=", AppS2wCmd_scanTimeSet},
    {"+WS",         AppS2wCmd_Wscan},
    {"+NSET=",  AppS2wCmd_Nset},
    {"+WM=",    AppS2wCmd_Wmode},
    {"+WRXPS=", AppS2wCmd_PowerSave},
    {"+WIEEEPSPOLL=", AppS2wCmd_ieeePsPollSet},
    {"+WP=",    AppS2wCmd_Wpower},
    {"+WD",     AppS2wCmd_Disconnect},
    {"+WRSSI=", AppS2wCmd_Wrssi},
    {"+WRATE=",    AppS2wCmd_Wrate},
    {"+WAPSM=",  AppS2wCmd_AssocPSModeSet},
    {"+MCSTSET=",   AppS2wCmd_McastRecvSet},
    {"+WIEEEPSPOLL=", AppS2wCmd_ieeePsPollSet},
	{"+NARP=",		AppS2wCmd_ArpEntryGet},
	{"+NARPCHACHEEN=",	AppS2wCmd_ArpCacheEn},
	{"+NARPCHACHEDEL", AppS2wCmd_ArpCacheDel},
    {"+NARPSET=",		AppS2wCmd_ArpEntrySet},
    {"+NARPDELETE=",	AppS2wCmd_ArpEntryDelete},
    {"+NARPAUTO=",	AppS2wCmd_ArpAutoSet},
    {"+srvvalidationen=",AppS2wCmad_WsrvrValidationEn},
	{"+WEAPTIMECHK=",AppS2wCmad_WeapTimeChk},
#ifdef S2W_UART_ENABLE    
    {"B=",      AppS2wCmd_BaudRate},
    {"+UARTFLVL=",AppS2wCmd_UartFifoLevel},
    {"&R",      AppS2wCmd_HardFlow},
    {"&K",      AppS2wCmd_SoftFlow},
#endif
    {"&F",      AppS2wCmd_Factory},
    {"&V",      AppS2wCmd_ConfigOutput},
    {"&W",      AppS2wCmd_Write},
    {"Z",       AppS2wCmd_read},
    {"&Y",      AppS2wCmd_SetDefaultProfile},
    {"S",       AppS2wCmd_Settings},
    {"E",       AppS2wCmd_Echo},
    {"V",       AppS2wCmd_Verbose},
    {"I",       AppS2wCmd_IdOutput},
    //{"?",		AppS2wCmd_Help},
#ifdef  S2W_NCM_SUPPORT_ENABLE
    {"A",       AppS2wCmd_AutoConnect},
#endif
    {"H",       AppS2wCmd_Disconnect},
    {"C",       AppS2wCmd_Acmode},
    {"O",       AppS2wCmd_GoOnline},
    {"+VER=",    App2wCmd_Version},
    {"+MCSTSET=",   AppS2wCmd_McastRecvSet},
    {"+BDATA=",  S2w_CmdBulkDataState},
    {"+RESET", AppS2wCmd_reset},
    {"+APCONF=",AppS2wCmd_ApConf},
    {"+APCLIENTINFO=", AppS2wCmd_ApClientInfoGet},
	{"+L2CONFIG=",	AppS2w_CmdL2ConfigSet},
#ifdef S2W_SNTP
    {"+NTIMESYNC=",   AppS2wCmd_ntpTimeSet},
#endif
#ifdef S2W_DNS_SERVER_ENABLE    
	{"+DNS=",       AppS2wCmd_Dns},
#endif        
#ifdef S2W_DHCP_SERVER_ENABLE        
	{"+DHCPSRVR=",  AppS2wCmd_DhcpSrvr},
        {"+DHCPSRVRCFG=",  AppS2wCmd_DhcpSrvrConfig},
#endif         
    {"+SETTIME=",  AppS2wCmd_SystemTimeSet},
    {"+GETTIME=",  AppS2wCmd_SystemTimeGet},
#ifdef S2W_SECURITY_WPS_ENABLE

   {"+WWPS=",  AppS2wCmd_Wwps},
#endif /* GSN_SECURITY_WPS_ENABLE */
	{"+TCERTADD=", AppS2wCmd_SslCertificateAdd},
    {"+TCERTDEL=", AppS2wCmd_SslCertificateDelete},
    {"+WEAP=",   AppS2wCmd_Weap},
    {"+WEAPCONF=",	AppS2wCmd_WeapConf},
#ifdef S2W_HTTPC_SUPPORT    
    {"+HTTPOPEN=", AppS2wCmd_HttpClientOpen},
    {"+HTTPCLOSE=", AppS2wCmd_HttpClientClose},
    {"+HTTPCONF=", AppS2wCmd_HttpClientConfig},
    {"+HTTPCONFDEL=", AppS2wCmd_HttpClientConfigDel},
    {"+HTTPSEND=", AppS2wCmd_HttpClientSend},
#endif    
#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD    
    {"+SOTAFWUPCONF=", AppS2wCmd_OtaFwupConf},
    {"+SOTAFWUPSTART", AppS2wCmd_OtaFwupExtFlashStart},
    {"+SOTAFWUPROLLBACK", AppS2wCmd_OtaFwupRollBack},
#endif    
    //{"+FSTEST=", AppS2wCmd_FsTest},
    {"+WAUTO=",     AppS2wCmd_Wauto},
    {"+NAUTO=",     AppS2wCmd_Nauto},
    {"+PSDPSLEEP", AppS2wCmd_PowerSaveDpsleep},
#ifdef S2W_PING_TRACE
    {"+PING=",      AppS2wCmd_Ping},
#endif
#ifdef S2W_IPv6_SUPPORT
    {"+NSETv6=",     AppS2wCmd_Nsetv6},
    {"+NDHCPv6=",    AppS2wCmd_Ndhcpv6},
    {"+NCUDPv6=",    AppS2wCmd_Ncudpv6},
    {"+NSUDPv6=",    AppS2wCmd_Nsudpv6},
    {"+NCTCPv6=",    AppS2wCmd_Nctcpv6},
    {"+NSTCPv6=",    AppS2wCmd_Nstcpv6},
    {"+DHCPSERVERv6=",AppS2wCmd_Dhcpv6Server},
#endif
#ifdef S2W_DNS_CLIENT
    {"+DNSSET=",AppS2wCmd_DnsServerSet},
    {"+DNSLOOKUP=",AppS2wCmd_DnsLookup},
#ifdef S2W_IPv6_SUPPORT
    {"+DNSLOOKUPv6=",     AppS2wCmd_DnsLookupv6},
#endif
#endif

    {"+WREGDOMAIN=", AppS2wCmd_RegDomainSet},
#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
    {"+SSLOPEN=",   AppS2wCmd_SSLOpen},
    {"+SSLCLOSE=",   AppS2wCmd_SSLClose},
	{"+SSLCONF=", AppS2wCmd_SslConfig},
#endif
#ifdef S2W_RF_TEST
	{"+WRFTESTSTART",  AppS2wCmd_RfTestStart},
	{"+WRFTESTSTOP",  AppS2wCmd_RfTestStop},
    {"+WFRAMETXTEST=",  AppS2wCmd_RfTestTxStart},
    {"+WTX99TEST=",  AppS2wCmd_RfTestTx99Start},
    {"+WTX100TEST=",  AppS2wCmd_RfTestTx100Start},
    {"+WCARWAVTEST=",  AppS2wCmd_RfTestCarrierWaveStart},
	{"+WTXSTOP=", AppS2wCmd_RfTestTxStop},
    {"+WRXTEST=",  AppS2wCmd_RfTestRxStart},
    {"+WRXSTOP",  AppS2wCmd_RfTestRxStop},
	{"+WCALIB=",  AppS2wCmd_WlanCalib},
#ifdef S2W_15DOT4_SUPPORT        
    {"+I154RXTEST=",AppS2wCmd_I154RxTest},
    {"+I154RXSTOP=",AppS2wCmd_I154RxTestStop},
    {"+I154TXTEST=",AppS2wCmd_I154TxTest},  
#endif    
#endif
#ifdef S2W_OTP_RDWR_SUPPORT
    {"+WOTPWR=",AppS2wCmd_WlanOtpWrite},
    {"+AOTPWR=",AppS2wCmd_AppOtpWrite},
#endif
    {"+WOTPRD=",AppS2wCmd_WlanOtpRead},
    {"+AOTPRD=",AppS2wCmd_AppOtpRead},

#ifdef S2W_WEB_PROV
	{"+WEBPROV=", APPS2wCmd_WebProv},
    {"+WEBPROVSTOP", APPS2wCmd_WebProvStop},    
    {"+NURIREDIR=", APPS2wCmd_AddRedirURI},
#endif
#if defined(S2W_GSLINK) && defined (S2W_WEB_SERVER)
    {"+WEBSERVER=", AppS2wCmd_WebServer},  
    {"+URIRECV=",AppS2wCmd_CfgUri},
#endif
#ifdef S2W_GSLINK_XML
    {"+XMLSEND=",   AppS2wCmd_XmlSend},
    {"+XMLPARSE=",   AppS2wCmd_XmlParseEnable},    

#endif   
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    {"+HTTPRECVCONF=",   AppS2wCmd_RecvConf},
#endif
	{"+PSSTBY="   , AppS2wCmd_PowerSaveStby},
    {"+STORENWCONN",  AppS2wCmd_NwConnStore},
    {"+RESTORENWCONN",AppS2wCmd_NwConnRestore},
    {"+HIBERNATE=", AppS2wCmd_Hibernate},
#ifdef  S2W_NCM_SUPPORT_ENABLE
    {"+NCMAUTO=",AppS2wCmd_NcmAuto},
    {"+NCMAUTOCONF=",AppS2wCmd_NcmAutoConf},
#endif 
    {"+ASYNCMSGFMT=", AppS2wCmd_AsyncMsgFmt},
#ifdef S2W_THROUGHPUT_TEST
	{"+SOCKTPTEST=",   AppS2wCmd_SockTpTest},
	{"+SOCKTPTESTSTAT=",   AppS2wCmd_SockTpTestStat},
#endif

     {"+NIPMULTICASTJOIN=", AppS2wCmd_IpMulticastJoin},
     {"+NIPMULTICASTLEAVE=", AppS2wCmd_IpMulticastLeave},
     {"+DGPIO=",  AppS2wCmd_Dgpio},
#if S2W_PERSISTENT_TMR_SUPPORT     
     {"+PRSTMRSTART=", AppS2wCmd_PerstTmrStart},
     {"+PRSTMRSTOP=", AppS2wCmd_PerstTmrStop},
     {"+PRSTMRDEL=", AppS2wCmd_PerstTmrDelete},
     {"+PRSTMRRESTART=", AppS2wCmd_PerstTmrReStart},
#endif     

#ifdef S2W_ISOTX_SUPPORT

     {"+ISOTXSTART=", AppS2wCmd_IsoTxStart},
     {"+ISOTXSTOP", AppS2wCmd_IsoTxStop},
     {"+ISOTXREGWR=", AppS2wCmd_IsoTxConfig},
#endif
#ifdef S2W_UNASSOC_TXRX_SUPPORT
     {"+UNSOLICITEDTX=", S2w_CmdUnSolicitedTx},
     {"+UNSOLICITEDRX=", S2w_CmdUnSolicitedRx},
     {"+UNSOLICITEDRXSTOP", S2w_CmdUnSolicitedRxstop},
     {"+UAMCCA=", S2w_CmdUnSolicitedCcaConf},
#endif
#ifdef S2W_EMU  
      /*Commands for EMU*/
    {"+emuver=", AppS2wCmd_EmuVer}, 
    {"+emusupmod=",AppS2wCmd_SupportedModules},
    {"+emustart",AppS2wCmd_EmuStart},  
    {"+emustop",AppS2wCmd_EmuStop},
    {"+emusetconf=",AppS2wCmd_EmuSetConf},
    {"+emugetvalues",AppS2wCmd_EmuGetValues},
    {"+emugetconf=",AppS2wCmd_EmuGetConf},
    {"+emuloadctrl=",AppS2wCmd_EmuLoadCtl}, 
    {"+emugetinstvalues",AppS2wCmd_EmuGetInstValues},
    {"+emuresetenergy",AppS2wCmd_EmuResetEnergy},
    {"+emugetstatus",AppS2wCmd_EmuGetStatus},
    {"+emuloadstatus",AppS2wCmd_EmuLoadStatus},
    {"+emuprint",AppS2wCmd_EmuPrint},
#endif
#ifdef S2W_ADC_SUPPORT
#ifndef GS2100
    {"+adcconf=",AppS2wCmd_AdcConf},
    {"+adcstart",AppS2wCmd_AdcStart},
    {"+adcread=",AppS2wCmd_AdcRead},
    {"+adcstop",AppS2wCmd_AdcStop},
#endif
#endif
#ifdef S2W_I2C_SUPPORT
    /*Commands for I2C*/
    {"+i2cconf=",AppS2wCmd_I2cConf},
    {"+i2cstart",AppS2wCmd_I2cStart},
    {"+i2cwrite=",AppS2wCmd_I2cWrite},
    {"+i2cread=",AppS2wCmd_I2cRead},
    {"+i2cstop",AppS2wCmd_I2cStop},
#endif    
#ifdef S2W_15DOT4_SUPPORT
    {"+PCH="   , AppS2wCmd_154Channel},
    {"+PPID="  , AppS2wCmd_154PanId},
    {"+PSA="   , AppS2wCmd_154ShortAddr},
    {"+PLA="   , AppS2wCmd_154ExtendedAddr},   
    {"+PMR="   , AppS2wCmd_154RetryCount},
    {"+PJP="   , AppS2wCmd_154JoinPermit},
    {"+PSC="   , AppS2wCmd_154SupreFrmCfg},
    {"+PCE="   , AppS2wCmd_154CoordExtndedAddr},   
    {"+PCA="   , AppS2wCmd_154CoordShortAddr},
    {"+PSN="   , AppS2wCmd_154ScanNetwork},
    {"+PJN="   , AppS2wCmd_154JoinNetwork},
    {"+PAN="   , AppS2wCmd_154AddNode},   
    {"+PFN="   , AppS2wCmd_154StartNetwork},
    {"+PLN="   , AppS2wCmd_154LeaveNetwork},
    {"+PPL="   , AppS2wCmd_154PollData},
    {"+PDS="   , AppS2wCmd_154DataSend}, 
    {"+PDP="   , AppS2wCmd_154DataPurge},
    {"+PRXEN="  , AppS2wCmd_154RxEnable},
    {"+PSR="    , AppS2wCmd_154SetReq},
    {"+PGR="    , AppS2wCmd_154GetReq},
    {"+PGTS=", AppS2wCmd_154GTSReq},
    {"+PSYNCR=", AppS2wCmd_154SyncReq},

#endif
#ifdef S2W_EXTFLASH_DRIVER_TEST
	 {"+EXFLASHINIT=", AppS2wCmd_ExtFlashInit},
	 {"+EXFLASHWRITE=", AppS2wCmd_ExtFlashWrite},
	 {"+EXFLASHREAD=", AppS2wCmd_ExtFlashRead},
	 {"+EXFLASHERASE=", AppS2wCmd_ExtFlashErase},
	 {"+EXFLASHCERASE", AppS2wCmd_ExtFlashChipErase},
	 {"+EXFLASHSPICONF=", AppS2wCmd_ExtFlashSpiConf},
#endif
#if defined(S2W_DTLS_CLIENT_SUPPORT)
	    {"+DTLSOPEN=",   AppS2wCmd_DTSLOpen},
	    {"+DTLSCLOSE=",   AppS2wCmd_DTSLClose},
#endif

	{"+WSTAPSCFG=", AppS2wCmd_WlanStaPsCfg},
	{"+WAPPSCFG=", AppS2wCmd_WlanApPsCfg},
	{"+PSPOLLINTRL=", S2w_CmdPsPollIntervelset},
	{"+WKEEPALIVE=", S2w_CmdPsPollIntervelset},
#ifdef S2W_PWM_SUPPORT
        {"+PWMSTART=", AppS2wCmd_PwmStart},
        {"+PWMSTOP=", AppS2wCmd_PwmStop},
        {"+PWMCNTRL=", AppS2wCmd_PwmCtrl},
#endif

#ifdef S2W_MEM_ACCESS
    {"+MEMREAD=", AppS2wCmd_MemRead},
    {"+MEMWRITE=", AppS2wCmd_MemWrite},

#endif
    {"+LOGLVL=", AppS2wCmd_LogLevelSet},
	{"+BCHKSTRT=",	AppS2wCmd_BattCheckStart},
	{"+BATTVALGET", AppS2wCmd_BattValueGet},
	{"+BCHK=",		AppS2wCmd_BattCheckSet},
	{"+BCHKSTOP",	AppS2wCmd_BattCheckStop},
	{"+BATTLVLSET=", AppS2wCmd_BattLvlSet},
#ifdef S2W_ADC_SUPPORT        
	{"+CLKTUNE=", App_ClkTuneCmd},
#endif        
#ifdef S2W_COAP_SUPPORT
    {"+COAPOPEN=", AppS2wCmd_CoapOpen},
    {"+COAPSENDRECIEVE=", AppS2wCmd_CoapSend},
    {"+COAPCLOSE=", AppS2wCmd_CoapClose},
    {"+COAPOPTCONF=", AppS2wCmd_CoapSetOption},
    {"+COAPOPTCONFDEL=", AppS2wCmd_CoapRemoveOption},
#endif
	{"+WBACKEN=",AppS2wCmd_BaBitMapSet},

	{"+WRADIOSTATE=",AppS2wCmd_RadioStateGet},
#ifdef S2W_15DOT4_SUPPORT
    {"+ZSC=",AppS2wCmd_ZipScan},
    {"+ZST=",AppS2wCmd_ZipStart},
    {"+ZSP=",AppS2wCmd_ZipStop},
    {"+ZMS=",AppS2wCmd_ZipSetMacAddr},
#endif    

#ifdef GSN_MEM_TRACE
    {"+MEMTRACE", AppS2wCmd_memTraceGet},
#endif    
#if defined(S2W_FS_SPI_ENABLE) || defined(S2W_FS_SPI_HI_ENABLE)
    {"+SPICONF=", AppS2wCmd_SpiConfig},
#endif /* S2W_FS_SPI_ENABLE */
#ifdef S2W_FTC
	{"+FTCSDADC", AppS2wCmd_FtcSdAdc},
	{"+FTCSARADC", AppS2wCmd_FtcSarAdc},
	{"+FTCEXFLID", AppS2wCmd_FtcExtFlashID},	
	{"+RFTCEXFLID", AppS2wCmd_rftcExtFlashID},
	{"+RFTCSARADC" , AppS2wCmd_rFtcSarAdc},
	{"+RFTCSDADC"   ,AppS2wCmd_rFtcSdAdc},
#endif
    {"+WASSOCCONF=",AppS2wCmd_SetAssocTimeout},
    {"+TEMPVALGET=", AppS2wCmd_TempGet},
    {"+WTEMPREAD=", AppS2wCmd_TempReadStart},
    {"+CRYPTOEN=", AppS2wCmd_HwCryptoEn},
    {"+GRATARP", AppS2wCmd_GratArpSend},
    
    {"+MQTT=", AppS2wCmd_MqttStart},
};

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+PSDPSLEEP command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_PowerSaveDpsleep(UINT8 *ptr)
{
    UINT32 timeout = 0;
    S2W_ALARM_INFO_T alarm;
    UINT8 status;
    UINT8 *p, pwrMeasure = 0;
    memset(&alarm,0,sizeof(alarm));
    if (*ptr)
    {
        if(ptr[0] == '=')
        {
            ptr++;
            p = AppS2wParse_NextParamGet(&ptr);
            if (p)
            {
                if (*p != '\0')
                {
                    status = AppS2wParse_Int(p, &timeout);
                    if (status != S2W_SUCCESS)
                    {
                        return status;
                    }
                }
            }
            p = AppS2wParse_NextParamGet(&ptr);
            if (p)
            {
                if (*p != '\0')
                {
                    status = AppS2wParse_Boolean(p, &(alarm.alarm1Pol));
                    if (status != S2W_SUCCESS)
                    {
                        return status;
                    }
                    alarm.alarm1Valid = 1;
                }
                p = AppS2wParse_NextParamGet(&ptr);
                if (p)
                {
                    if (*p != '\0')
                    {
                        status = AppS2wParse_Boolean(p, &(alarm.alarm2Pol));
                        if (status != S2W_SUCCESS)
                        {
                            return status;
                        }
                        alarm.alarm2Valid = 1;
                    }
                }
                p = AppS2wParse_NextParamGet(&ptr);
                if (p)
                {
                    if (*p != '\0')
                    {
                        status = AppS2wParse_Boolean(p, &pwrMeasure);
                        if (status != S2W_SUCCESS)
                        {
                            return status;
                        }
                    }
                }
            }
        }
    else
        {
       return S2W_EINVAL;
        }
    }

    return AppS2wHal_PsDpSleepStart(timeout, &alarm, pwrMeasure);
}

#ifdef S2W_HTTPC_SUPPORT

void
AppS2w_HttpRxBufferMgmtCb(GSN_HTTPC_CONN_HANDLE conHandle,
                     INT8 *httpRxDataBuf,
                     INT32 httpRxDataLen,
                     INT32* rxBufferMgmtstatus);
GSN_HTTPC_CONF_INFO_T httpConfInfo;
INT8 *headerValues[S2W_HTTPC_MAX_HDR_SUPPORTED];
GSN_HTTP_USER_HEADER_TYPE_T headerTypes[S2W_HTTPC_MAX_HDR_SUPPORTED];
GSN_HTTP_USER_HEADER_TYPE_T headerTypesModified[S2W_HTTPC_MAX_HDR_SUPPORTED];
UINT8 httpConfAtCmd=0;


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+HTTPOPEN command
 *   This function open a new http client connection.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 * @return S2W_EINVAL - operation Failed-invalid input
 ******************************************************************/
#if defined(S2W_SSL_CLIENT_SUPPORT)

extern S2W_SSL_CONF_T s2wSslConf;
#endif
 UINT8
AppS2wCmd_HttpClientOpen(UINT8 *ptr)
{
    S2W_HTTP_DATA_T *pHttpData;
    UINT8 *p, i=0, status = S2W_EINVAL, /*ret,*/ endParam = 0, *tmp = NULL;
    UINT32 cid = -1, httpType, portNumber,len;
    INT32 certID;
    ULONG hostIpAddress;
    pHttpData = gsn_malloc(sizeof(S2W_HTTP_DATA_T));
    if(NULL == pHttpData)
    {
        return S2W_FAILURE;
    }
    memset(pHttpData,0,sizeof(S2W_HTTP_DATA_T));
    p = AppS2wParse_NextParamGet(&ptr);

    if (!p)
    {
        status = S2W_EINVAL;
        goto AppS2wCmd_HttpClientOpenExit;
    }
    len = strlen((const char *)p);
    tmp = gsn_malloc(len+1);
    if(NULL != tmp)
    {
        strcpy((char *)tmp, (char *)p);
    }
    if(inet_pton(AF_INET, (char const*)p, &pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr) == 1)
    {
        pHttpData->sockAddr.addr.ipv4.sin_family = AF_INET;
    }
    else if(inet_pton(AF_INET6, (char const*)p, pHttpData->sockAddr.addr.ipv6.sin6_addr.s6_addr32) == 1)
    {
    	pHttpData->sockAddr.addr.ipv6.sin6_family = AF_INET6;
    }
    else
    {
 	   /*Dns look up */
		status = GsnNwIf_DnsHostByNameGet(&s2wappMainTaskCtxt->if0.nwifCtx, (UINT8*)p,\
										 &hostIpAddress, 5);
		pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr = ntohl(hostIpAddress);
		if (hostIpAddress == 0)
			return S2W_FAILURE;
		
        /* Send IP address back to host */
		S2w_Printf("\r\nIP:%d.%d.%d.%d",(pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr & 0x000000ff),
										(pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr & 0x0000ff00)>>8,
										(pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr & 0x00ff0000)>>16,
										(pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr & 0xff000000)>>24);		
		pHttpData->sockAddr.addr.ipv4.sin_family = AF_INET;
    }
    /* port Number */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        endParam = 1;
    }
    else
    {
        AppS2wParse_Int(p, &portNumber);
        pHttpData->sockAddr.ss_port = portNumber;

    }

    /* security */
    if(!endParam)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            endParam = 1;
        }
        else
        {
            AppS2wParse_Int(p, &httpType);
            pHttpData->httpType = (GSN_HTTP_TYPE_T)httpType;
        }
    }
#if defined(S2W_SSL_CLIENT_SUPPORT)
    /* certificate name */
    if(!endParam)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            endParam = 1;
        }
        else
        {
            if(0 != strlen((const INT8 *)p))
            {
//				certID = S2wCert_Get((INT8 *)p);
        		certID = S2wCert_SearchRamTable((INT8*)p);
		        if(certID == -1)
        		{
        			certID = S2wCert_FlashFileLoad((INT8*)p);
        		}

                if(certID != -1)
                {
                    pHttpData->caCertLen = *(UINT16 *)s2w_ssl_cert_table[certID].certAddress;
                    pHttpData->pCaCert = s2w_ssl_cert_table[certID].certAddress + 2;
                }
                else
                {
                    S2w_Printf("\n\rCA certificate not found");
                    status = S2W_FAILURE;
                    goto AppS2wCmd_HttpClientOpenExit;
                }
            }
        }
    }
#endif
    /* proxy server */
    if(!endParam)
    {
        UINT32 proxy = 0;
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            endParam = 1;
        }
        else
        {
            AppS2wParse_Int(p, &proxy);
            pHttpData->proxyServer = proxy;
        }
    }
	pHttpData->connTimeOut=25;
    if(!endParam)
    {
        UINT32 connTimeout = 0;
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            endParam = 1;
        }
        else
        {
            AppS2wParse_Int(p, &connTimeout);
			if(connTimeout != 0)
	            pHttpData->connTimeOut = connTimeout;
        }
    }
#if defined(S2W_SSL_CLIENT_SUPPORT)
    if(!endParam)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            endParam = 1;
        }
        else
        {
            if(0 != strlen((const INT8 *)p))
            {
                //certID = S2wCert_Get((INT8 *)p);
        		certID = S2wCert_SearchRamTable((INT8*)p);
        		if(certID == -1)
        		{
        			certID = S2wCert_FlashFileLoad((INT8*)p);
        		}
                if(certID != -1)
                {
                    pHttpData->clientCertLen= *(UINT16 *)s2w_ssl_cert_table[certID].certAddress;
                    pHttpData->pClientCert= s2w_ssl_cert_table[certID].certAddress + 2;
                }
                else
                {
                    S2w_Printf("\n\r client certificate not found");
                    status = S2W_FAILURE;
                    goto AppS2wCmd_HttpClientOpenExit;
                }
            }
        }
    }

    if(!endParam)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            endParam = 1;
        }
        else
        {
            if(0 != strlen((const INT8 *)p))
            {
                //certID = S2wCert_Get((INT8 *)p);
        		certID = S2wCert_SearchRamTable((INT8*)p);
        		if(certID == -1)
		        {
        			certID = S2wCert_FlashFileLoad((INT8*)p);
        		}
        		if(certID != -1)
                {
                    pHttpData->clientKeyLen = *(UINT16 *)s2w_ssl_cert_table[certID].certAddress;
                    pHttpData->pClientKey = s2w_ssl_cert_table[certID].certAddress + 2;
                }
                
                else
                {
                    S2w_Printf("\n\rclient Key not found");
                    status = S2W_FAILURE;
                    goto AppS2wCmd_HttpClientOpenExit;
                }
            }
        }
    }
#endif
    // check the default paramters are configured
    if((httpConfAtCmd != 1) &&(!httpConfInfo.reqHeaderCount))
    {
        memset(&headerTypes[0], GSN_HTTP_HEADER_INVAL, sizeof(headerTypes));
        memset(&headerValues[0], 0, sizeof(headerValues));
        httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
        httpConfInfo.reqHeaderTypes = (GSN_HTTP_USER_HEADER_TYPE_T *)headerTypesModified;
        httpConfInfo.reqHeaderValues = headerValues;
        httpConfInfo.reqHeaderCount = 0;

        // configure the header
#if defined(S2W_DFLT_HTTPC_AUTH) || defined(S2W_DFLT_HTTPC_HOST_IP)					
        INT8 *pValue;
        UINT32 len;
#endif		
#ifdef S2W_DFLT_HTTPC_AUTH					
        len= sizeof(S2W_DFLT_HTTPC_AUTH);
        pValue = gsn_malloc(len+1);
        if(pValue == NULL)
        {
            return S2W_FAILURE;
        }
        memset(pValue, 0 , len+1);
        memcpy(pValue, S2W_DFLT_HTTPC_AUTH, len);
        pValue[len] = '\0';
        headerValues[i] = pValue;
	    headerTypes[i++] = GSN_HTTP_HEADER_AUTHORIZATION;
        httpConfInfo.reqHeaderCount +=1;
#endif

#ifdef S2W_DFLT_HTTPC_HOST_IP			
        len= sizeof(S2W_DFLT_HTTPC_HOST_IP);
        pValue = gsn_malloc(len+1);
        if(pValue == NULL)
        {
            return S2W_FAILURE;
        }
        memset(pValue, 0 , len+1);
        memcpy(pValue, (UINT8*)S2W_DFLT_HTTPC_HOST_IP, len);
        pValue[len] = '\0';
        headerValues[i] = pValue;
	    headerTypes[i++] = (GSN_HTTP_USER_HEADER_TYPE_T)(GSN_HTTP_HEADER_HOST);
        httpConfInfo.reqHeaderCount +=1;
#endif		
 	}
	/*Make all the custom headers types as 255 - This is done to coply withi the ROM code which is
	compiled with header type array being defined as array of UINT8 */
	{
		
		for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
        {
        	if(headerTypes[i] >= (GSN_HTTP_USER_HEADER_TYPE_T)GSN_HTTP_HEADER_CUSTOM)
			{
				headerTypesModified[i] = (GSN_HTTP_USER_HEADER_TYPE_T)GSN_HTTP_HEADER_CUSTOM;
			}
			else
			{
        		headerTypesModified[i] = headerTypes[i];
			}
        }
	}
    status = AppS2wHal_HttpOpen(pHttpData, &cid);

AppS2wCmd_HttpClientOpenExit:
    if(status == S2W_SUCCESS)
    {
        S2w_Printf("\n\r%x", cid);
#if defined(S2W_SSL_CLIENT_SUPPORT)
        if((NULL != tmp) && (GSN_HTTPS == pHttpData->httpType) && (NULL != s2wSslConf.dnsNameBuf))
        {
            status = AppS2wHal_HttpCheckDns(tmp);
        }
#endif		
        if(NULL != tmp)
        {
            gsn_free(tmp);
            tmp = NULL;
        }
#if defined(S2W_SSL_CLIENT_SUPPORT)
        if(NULL != s2wSslConf.dnsNameBuf)
        {
        	gsn_free(s2wSslConf.dnsNameBuf);
        	s2wSslConf.dnsNameBuf = NULL;
        	s2wSslConf.dnsBufferLen = 0;
        }
#endif		
        return S2W_SUCCESS;
    }
    else
    {
        if(NULL != pHttpData)
            gsn_free(pHttpData);
        if(NULL != tmp)
        {
            gsn_free(tmp);
            tmp = NULL;
        }
#if defined(S2W_SSL_CLIENT_SUPPORT)
        if(NULL != s2wSslConf.dnsNameBuf)
        {
        	gsn_free(s2wSslConf.dnsNameBuf);
        	s2wSslConf.dnsNameBuf = NULL;
        	s2wSslConf.dnsBufferLen = 0;
        }
#endif		
        return status;
    }
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+HTTPCLOSE command
 *   This function close the http connection opened.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 * @return S2W_EINVAL - operation Failed-invalid input
 ******************************************************************/
 UINT8
AppS2wCmd_HttpClientClose(UINT8 *ptr)
{
    UINT8 status;
    UINT8 *p ;
    UINT32 cid;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    else
    {
        if(AppS2w_CidValidate(*p) == INVALID_CID)
            return S2W_EBADCID;
        status = AppS2wParse_Hex(p, &cid);
        if (status != S2W_SUCCESS)
        {
        	return status;
        }
        return AppS2wHal_HttpClose(cid);
    }
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+HTTPCONF command
 *   This function configures the http client paramters.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 * @return S2W_EINVAL - operation Failed-invalid input
 ******************************************************************/

 UINT8
 AppS2wCmd_HttpClientConfig(UINT8 *ptr)
 {
     UINT32 param, len,Userparam/*, index = 0*/;
     static UINT8 initDone;
     UINT8 *p, i, newParam = 0;
     INT8 *pValue;

    if(!initDone)
    {
        memset(&headerTypes[0], GSN_HTTP_HEADER_INVAL, sizeof(headerTypes));
        memset(&headerValues[0], 0, sizeof(headerValues));
        httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
        httpConfInfo.reqHeaderTypes = (GSN_HTTP_USER_HEADER_TYPE_T *)headerTypesModified;
        httpConfInfo.reqHeaderValues = headerValues;
        httpConfInfo.reqHeaderCount = 0;

        initDone = 1;
    }

     p = AppS2wParse_NextParamGet(&ptr);
     if (!p)
     {
         return S2W_EINVAL;
     }
     AppS2wParse_Int(p, &param);

	 Userparam = param;

     len = strlen((INT8 *)ptr);
     if(len == 0)
     {
         return S2W_EINVAL;
     }
	if((GSN_HTTP_USER_HEADER_TYPE_T)param >= GSN_HTTP_HEADER_DATE &&  Userparam < GSN_HTTP_HEADER_COUNT )
	{
	   param = param + 2;
	}
	if((GSN_HTTP_USER_HEADER_TYPE_T)param > GSN_HTTP_HEADER_SERVER &&  Userparam < GSN_HTTP_HEADER_COUNT)
	{
	   param = param + 1;
	}
    if(param == S2W_HTTPC_CFG_PARAM_REQUEST_URL)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }
        len = strlen((const char *)p);
        if(NULL != httpConfInfo.reqPathPtr)
        {
            gsn_free(httpConfInfo.reqPathPtr);
            httpConfInfo.reqPathPtr = NULL;
        }
        httpConfInfo.reqPathPtr = gsn_malloc(len+1);
        if(NULL == httpConfInfo.reqPathPtr)
        {
            return S2W_FAILURE;
        }
        strncpy(httpConfInfo.reqPathPtr, (const INT8 *)p, len);
        httpConfInfo.reqPathPtr[len] ='\0';

    }
    else if((param > S2W_HTTPC_CFG_PARAM_INV && param < S2W_HTTPC_CFG_PARAM_HEADER_COUNT1)
        || (param >= S2W_HTTPC_CFG_PARAM_HEADER_CUSTOM))
    {
        pValue = gsn_malloc(len+1);

        if(pValue == NULL)
        {
            return S2W_FAILURE;
        }

        memset(pValue, 0 , len+1);
        strncpy(pValue, (const INT8 *)ptr, len);
        pValue[len] = '\0';

        for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
        {
            if((headerValues[i] == NULL) || (headerTypes[i] == param))
            {
                if(headerValues[i])
                {
                 gsn_free(headerValues[i]);
                }
                else
                {
                 newParam = 1;
                }
                break;
           }
       }
     if( i < S2W_HTTPC_MAX_HDR_SUPPORTED)
     {
	     headerValues[i] = pValue;
	     headerTypes[i] = (GSN_HTTP_USER_HEADER_TYPE_T)param;
     }
     if(newParam)
         httpConfInfo.reqHeaderCount++;
    }
    else
    {
        return S2W_EINVAL;
    }
     httpConfAtCmd =1;
     return S2W_SUCCESS;

 }
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+HTTPCONFDEL command
 *   This function delete the particular http configuration
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 * @return S2W_EINVAL - operation Failed-invalid input
 ******************************************************************/

 UINT8
AppS2wCmd_HttpClientConfigDel(UINT8 *ptr)
{
    UINT32 param, i;
    //static UINT8 initDone;
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &param);

	if((GSN_HTTP_USER_HEADER_TYPE_T)param >= GSN_HTTP_HEADER_DATE)
	{
	   param = param + 2;
	}
	if((GSN_HTTP_USER_HEADER_TYPE_T)param > GSN_HTTP_HEADER_SERVER)
	{
	   param = param + 1;
	}
    if(param == S2W_HTTPC_CFG_PARAM_REQUEST_URL)
    {
        if(NULL != httpConfInfo.reqPathPtr)
        {
            gsn_free(httpConfInfo.reqPathPtr);
            httpConfInfo.reqPathPtr = NULL;
        }
        return S2W_SUCCESS;
    }

    if((param > S2W_HTTPC_CFG_PARAM_INV && param < S2W_HTTPC_CFG_PARAM_HEADER_COUNT1)
        || (param >= S2W_HTTPC_CFG_PARAM_HEADER_CUSTOM))
    {/*delete Header Configuration*/

        for( i = 0; i < httpConfInfo.reqHeaderCount; i++)
        {
            if(headerTypes[i] == param)
            {
                if(headerValues[i])
                    gsn_free(headerValues[i]);
                break;
            }
        }

        if(i == httpConfInfo.reqHeaderCount)
            return S2W_FAILURE;

        for( ; i < (httpConfInfo.reqHeaderCount - 1); i++)
        {
            headerTypes[i] = headerTypes[i+1];
            headerValues[i] = headerValues[i+1];
        }
        headerValues[i] = NULL;
        headerTypes[i] = GSN_HTTP_HEADER_INVAL;
        httpConfInfo.reqHeaderCount--;
    }
    else
    {
        return S2W_EINVAL;
    }

    return S2W_SUCCESS;

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the http data from the serial interface.
 *   This function reads the http data and sends to wifi.
 * @param dataLen the input data length.
 * @param hCid the cid of the http connection.
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 ******************************************************************/

PUBLIC UINT8
AppS2wHal_httpContentDataGet(UINT32 dataLen, UINT8 hCid)
{
    GSN_STATUS status = S2W_SUCCESS;
    S2W_HTTP_DATA_T *pHttpData;
    httpConfInfo.reqBodyLen = 0;
    httpConfInfo.moredata = 1;
    httpConfInfo.reqBodyPtr = (INT8 *)gsn_malloc(1022);
    if(NULL ==  httpConfInfo.reqBodyPtr)
    {
        status = S2W_FAILURE;
        goto AppS2wHal_httpContentDataGetExit;
    }
    pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(hCid);
    if(pHttpData != NULL)
    {
        GsnOsal_SemAcquire(&pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
    }
    else
    {
        status = S2W_FAILURE;
        goto AppS2wHal_httpContentDataGetExit;
    }
    while(dataLen)
    {

        httpConfInfo.reqBodyLen = dataLen >= HTTP_SEND_CHUNK_SIZE?
                                                HTTP_SEND_CHUNK_SIZE:dataLen;

        if(s2wCidList[hCid].sd != INVALID_CID)
        {
#ifndef S2W_DUAL_INTERFACE_SUPPORT
			AppS2wHal_CharNGet((UINT8 *)httpConfInfo.reqBodyPtr,httpConfInfo.reqBodyLen);
#else
            AppS2wHal_CharNGet1((UINT8 *)httpConfInfo.reqBodyPtr,httpConfInfo.reqBodyLen);
#endif
			
        	dataLen -= httpConfInfo.reqBodyLen;

       		if(0 == dataLen )
        	{
            	httpConfInfo.moredata = 0;
        	}
	        status = S2wHttp_Send(hCid);
        	httpConfInfo.reqBodyLen = 0;
        }
		else
			status = S2W_FAILURE;
        if(status != S2W_SUCCESS)
        {
            status = S2W_FAILURE;
            break;
        }
    }
    if(pHttpData != NULL)
    {
        GsnOsal_SemRelease(&pHttpData->opInProgress);
    }
    if(NULL != httpConfInfo.reqBodyPtr)
    {
        gsn_free(httpConfInfo.reqBodyPtr);
        httpConfInfo.reqBodyPtr = NULL;
    }
AppS2wHal_httpContentDataGetExit:
	httpConfInfo.moredata = 0;
   return status;
}

UINT8
AppS2wCmd_HttpClientSend(UINT8 *ptr)
{
	UINT8 cid;
    UINT32  method;
    UINT8 *p;//,*page, *content,  *httpRxDataBuf;
    UINT32 /*httpRxDataLen = 0, temp, ret,*/ timeOut,dataLen=0;
#ifdef S2W_HTTPC_SUPPORT
	S2W_HTTP_DATA_T *pHttpData;
	UINT32 len;
#endif
    UINT8 status = S2W_SUCCESS;
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    UINT8 statusline;
    UINT32 headercount;
    UINT32 size;
#endif
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
	cid = AppS2w_CidValidate(*p);
    if(cid == INVALID_CID)
        return S2W_EBADCID;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &method);
    if(method == S2W_HTTP_METHOD_GETRESP)
    {
    	method = GSN_HTTP_METHOD_GETRESP;
    }
    else if(method == S2W_HTTP_METHOD_POSTRESP)
    {
    	method = GSN_HTTP_METHOD_POSTRESP;
    }
#ifdef S2W_HTTPC_SUPPORT
    httpConfInfo.reqMethod = (GSN_HTTP_USER_METHOD_T)method;
#endif
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &timeOut);
    if(timeOut == 0)
        timeOut = 5;
#ifdef S2W_WEB_SERVER
	if(TRUE == GsnHttpd_IsRunning())
	{
		status = AppS2w_HttpdSetTimeOut(cid,timeOut);
		if(status != S2W_SUCCESS)
			return	status;
	}
#endif
#ifdef S2W_HTTPC_SUPPORT
	httpConfInfo.httpTimeOut = timeOut;
#endif
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

#ifdef S2W_HTTPC_SUPPORT
 	len = strlen((const char *)p);
    if(NULL != httpConfInfo.reqPathPtr)
    {
        gsn_free(httpConfInfo.reqPathPtr);
        httpConfInfo.reqPathPtr = NULL;
    }
    httpConfInfo.reqPathPtr = gsn_malloc(len+1);
    if(NULL == httpConfInfo.reqPathPtr)
    {
        return S2W_FAILURE;
    }
    strncpy(httpConfInfo.reqPathPtr, (const INT8 *)p, len);
    httpConfInfo.reqPathPtr[len] ='\0';
    httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
#endif
#if (defined(S2W_GSLINK_XML) || defined(S2W_GSLINK_RAW )) &&  defined(S2W_WEB_SERVER)
	if((method == GSN_HTTP_METHOD_GETRESP || method == GSN_HTTP_METHOD_POSTRESP ) &&
		(strcmp((const char *)s2wappMainTaskCtxt->currenturi,(const INT8 *)p) != 0))
	{
		return S2W_FAILURE;
	}
#endif
    p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
    {
#ifdef S2W_HTTPC_SUPPORT
		if(GSN_HTTP_METHOD_POST == method)
        {
            gsn_free(httpConfInfo.reqPathPtr);
            return S2W_EINVAL;
        }
        httpConfInfo.reqBodyTotalLen = 0;
        httpConfInfo.reqBodyLen = 0;
        pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(cid);
        if(pHttpData != NULL)
        {
            GsnOsal_SemAcquire(&pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
            status = S2wHttp_Send(cid);
        }
        else
        {
            return S2W_FAILURE;
        }
        if(pHttpData != NULL)
        {
            GsnOsal_SemRelease(&pHttpData->opInProgress);
        }
#endif
    }
    else
    {
         AppS2wParse_Int(p, &dataLen);
#ifdef S2W_HTTPC_SUPPORT
		httpConfInfo.reqBodyTotalLen = dataLen;
#endif
#if defined(S2W_GSLINK) && defined(S2W_GSLINK_RAW )&& defined(S2W_WEB_SERVER)
		if((method == GSN_HTTP_METHOD_GETRESP || method == GSN_HTTP_METHOD_POSTRESP))
		{
			status = AppS2w_HttpdCtxInit(&s2wCidList[cid].httpdCtx,1);
			AppS2w_HttpdBodyLenSet(&s2wCidList[cid].httpdCtx,dataLen);
			AppS2w_HttpdMethodSet(&s2wCidList[cid].httpdCtx,(UINT8)method);
			if(s2wappMainTaskCtxt->respTimeOut !=0)
			{
				s2wappMainTaskCtxt->responseInprogress=1;
			GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl);
			s2wappMainTaskCtxt->respTimeOutTmrHndl = GsnSoftTmr_Start(&s2wappMainTaskCtxt->respTimeOutTmr, GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(s2wappMainTaskCtxt->respTimeOut),
							  ( GSN_SOFT_TMR_CBR_T )AppMcu_RespTimeoutCb, &s2wCidList[cid].sd );
			}
#ifdef S2W_HTTP_CUSTOM_SUPPORT
            /* check if custom headers has to be added */
            p = NULL;
            len = 0;

            p = AppS2wParse_NextParamGet(&ptr);
            if (NULL != p)
            {
                status = AppS2wParse_Boolean(p, &statusline);
                if (status != S2W_SUCCESS)
                {
                    return status;
                }
                p = NULL;
                p = AppS2wParse_NextParamGet(&ptr);
                AppS2wParse_Int(p,  &size);
                if(size != 0)
                {
                    headercount = size;
                }
                AppS2w_HttpStatusLineSet(&s2wCidList[cid].httpdCtx, statusline);
                AppS2w_HttpHdrCountSet(&s2wCidList[cid].httpdCtx, headercount);
            }
#endif
		}
#endif
    }
    return status;
}

#endif

#if 0
UINT8
AppS2wCmd_SslCertificateAdd(UINT8 *ptr)
{
    UINT8 *p, *name;
    INT32 len, i = 0;
    UINT32 certStore;

    name = AppS2wParse_NextParamGet(&ptr);     //get cert name
    if (!name)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)name);
    if( len > 32)
        return S2W_EINVAL;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certFormat);
    if(certFormat > 1)
        return S2W_EINVAL;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(p, &certFileSize);

    certFileSize = certFileSize >> certFormat;
    //S2w_Printf("\n\rfile size %d", certFileSize);

    p = AppS2wParse_NextParamGet(&ptr);     //get wehre to store SRAM/FLASH
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certStore);

    if(certStore > 1)
        return S2W_EINVAL;

	if(S2wCert_findFile(name) == -1)
	{
		S2w_Printf("\n\rFILE EXISTS\n\r");
		return S2W_FAILURE;
	}
    if(certStore)
    {
    	i = S2wCert_MemAlloc(certFileSize);
	    //S2w_Printf("\nmem-alloc :%d\n",i);
	    if(i == -1)
	    	return S2W_FAILURE;
        p = gsn_malloc(len+1); //allocate memory for storing name
        if(p == NULL)
            return S2W_FAILURE;
        strcpy((INT8 *)p, (const char *)name);
        s2w_ssl_cert_table[i].name = p; //copy pointer to SRAM entry
        s2w_ssl_cert_table[i].location = CERT_IN_RAM;
        certIndex = i;
    }
    else
    {
        certFile = f_open(name, "w");
        if(certFile == NULL)
        	return S2W_FAILURE;
        certIndex = S2W_INVALID_CERT_INDEX;
    }

    /* Store the Cert Index in a global. This is used when the actual certificate
      is received in the next escape sequence */

    return S2W_SUCCESS;
}

PUBLIC UINT32
AppS2wCertificateData(UINT8 ch1)
{
    UINT8 *buf, ch;
    UINT16 i = 2, index = 2;

    if ( (certIndex == S2W_INVALID_CERT_INDEX) && (certFile == NULL))
            return S2W_FAILURE;

    if( certFileSize == 0)
            return S2W_FAILURE;

    buf = gsn_malloc((certFileSize << certFormat) + 2);

    if(buf == NULL)
        return S2W_FAILURE;

    *buf = certFileSize & 0x00FF;
    *(buf + 1) = (certFileSize & 0xFF00) >> 8;
    /* if format is hex size will be double */
    certFileSize = certFileSize << certFormat;

    /* store incoming byte in temparory bufer */
    AppS2wHal_CharNGet((buf+2), certFileSize);

    if(certFormat)
    {
        for(i = 2; i < (certFileSize + 2);)
        {
            buf[index] = (AppS2wParse_ToHex(buf[i]) << 4) | (AppS2wParse_ToHex(buf[i + 1]) & 0x0F);
            i = i + 2;
            index++;
        }
    }


    /* recieving file is complete. If the Cert Address is in the 0x8000000
    range store it in flash else store it in SRAM (0x4000000 range) */
    if ( certIndex !=  S2W_INVALID_CERT_INDEX)
    {
        /* store in SRAM */
        memcpy((UINT8 *) s2w_ssl_cert_table[certIndex].certAddress, buf,
            ((certFileSize >> certFormat) + 2));

    }
    else
    {
        /* store in flash */
        f_write(buf, 1, (certFileSize >> certFormat) + 2, certFile);
		f_close(certFile);
    }
    /* reset variables */
    certIndex = S2W_INVALID_CERT_INDEX;
    certFileSize = 0;
	certFile = NULL;
    gsn_free(buf);
    S2w_Printf("\r\nOK\r\n");
    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_SslCertificateDelete(UINT8 *ptr)
{
    UINT8 *p;
    INT32 certIndex, retVal =0;

    p = AppS2wParse_NextParamGet(&ptr);     //get cert name
    if (!p)
    {
         return S2W_EINVAL;
    }
    certIndex = S2wCert_SearchRamTable(p);
    if(certIndex != -1)
    {
    	gsn_free (s2w_ssl_cert_table[certIndex].certAddress);
        gsn_free(s2w_ssl_cert_table[certIndex].name);
        s2w_ssl_cert_table[certIndex].name = NULL;
        s2w_ssl_cert_table[certIndex].certAddress = NULL;
        if( s2w_ssl_cert_table[certIndex].location == CERT_IN_FLASH )
    	{
    		retVal = f_delete(p);
    	}
    }
    else
    {
    	retVal = f_delete(p);
    }

    if(!retVal)
    {
    	if(strcmp((const char*)p,S2W_CERT_NAME_CA) == 0)
    	{
			s2wCurrent.security.eap.useCaCert=0;
    	}
        return S2W_SUCCESS;
    }
    else
        return S2W_FAILURE;
}

PRIVATE UINT8
AppS2wCmd_Weap(UINT8 *ptr)
{
    UINT8 *name, *p;
    INT32 i = 0;
    UINT32 certStore, certType;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certType);

    if(certType > 2)
        return S2W_EINVAL;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(p, &certFormat);

    if(certFormat > 1)
        return S2W_EINVAL;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certFileSize);
    certFileSize = certFileSize >> certFormat;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certStore);

    if(certStore > 1)
        return S2W_EINVAL;

    if(certStore)
    {
    	i = S2wCert_MemAlloc(certStore, certFileSize);

	    if(i == -1)
	        return S2W_FAILURE;

        name = gsn_malloc(32);
        if(certType == 0)
            strcpy((INT8 *)name, S2W_CERT_NAME_CA);
        else if(certType == 1)
            strcpy((INT8 *)name, S2W_CERT_NAME_CLIENT);
        else
            strcpy((INT8 *)name, S2W_CERT_NAME_KEY);
        s2w_ssl_cert_table[i].name = name;
        s2w_ssl_cert_table[i].location = CERT_IN_RAM;
		certIndex = i;
    }
    else
    {
        /* write certificate name in flash */
        if(certType == 0)
            certFile = f_open(S2W_CERT_NAME_CA, "w");
        else if(certType == 1)
            certFile = f_open(S2W_CERT_NAME_CLIENT, "w");
        else
            certFile = f_open(S2W_CERT_NAME_KEY, "w");

        if(certFile == NULL)
        	return S2W_FAILURE;
        certIndex = S2W_INVALID_CERT_INDEX;
    }
    /* Store the Cert Index in a global. This is used when the actual certificate
      is received in the next escape sequence */
    return S2W_SUCCESS;
}
#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+SETTIME Command.
 *   This function set the system time. The input time in dd/mm/yyyy and
 *   HH:MM:SS format
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_SystemTimeSet(UINT8 *ptr)
{
    GSN_SYSTEM_TIME_T currentTime, newTime, timeDifference;
    UINT8 i, *p, len, j,flag=0;
    struct tm time;
    BOOL diffNegative;
    ULONG64 time64=0;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if(p && *p)
    {
    len = strlen((char *)p);

    i = 0;
    while(i < len)
    {
        if(p[i] == '/')
            {
            break;
            }
        i++;
    }

    if( i >= len )
    {
        return S2W_EINVAL;
    }
    p[i] = '\0';

    AppS2wParse_Int(p, (UINT32 *)&time.tm_mday);
        //S2w_Printf("\n\r%d", time.tm_mday);
    if(time.tm_mday > 31)
        {
        return S2W_EINVAL;
        }
    j = ++i;
    while(i < len)
    {
        if(p[i] == '/')
            {
            break;
            }
        i++;
    }

    if( i >= len )
    {
        return S2W_EINVAL;
    }
    p[i] = '\0';

    AppS2wParse_Int(&p[j], (UINT32 *)&time.tm_mon);
        //S2w_Printf(":%d", time.tm_mon);
    if(time.tm_mon > 12)
        {
        return S2W_EINVAL;
        }
    time.tm_mon--;
    ++i;

    if( i >= len )
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(&p[i], (UINT32 *)&time.tm_year);
        //S2w_Printf(":%d", time.tm_year);
    if(time.tm_year < 1900)
        {
        return S2W_EINVAL;
        }

    p = AppS2wParse_NextParamGet(&ptr);

    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((char *)p);

    i = 0;
    while(i < len)
    {
        if(p[i] == ':')
            {
            break;
            }
        i++;
    }

    if( i >= len )
    {
        return S2W_EINVAL;
    }
    p[i] = '\0';

    AppS2wParse_Int(p, (UINT32 *)&time.tm_hour);
        //S2w_Printf(" %d:", time.tm_hour);
    if(time.tm_hour > 23)
        {
        return S2W_EINVAL;
        }
    j = ++i;
    while(i < len)
    {
        if(p[i] == ':')
            {
            break;
            }
        i++;
    }

    if( i >= len )
    {
        return S2W_EINVAL;
    }
    p[i] = '\0';

    AppS2wParse_Int(&p[j], (UINT32 *)&time.tm_min);
        //S2w_Printf("%d:", time.tm_min);
    if(time.tm_min > 59)
        {
        return S2W_EINVAL;
        }

    ++i;
    if( i >= len )
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(&p[i], (UINT32 *)&time.tm_sec);
        if(time.tm_sec > 60)
        {
            return S2W_EINVAL;
        }
        flag =1;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if(p && *p)
    {
        if(flag)
        {
        return S2W_EINVAL;
        }
        AppS2wParse_64BitNumber(p,&time64);
    }
	if(flag)
	{
        time.tm_year = time.tm_year - 1900;
        time.tm_isdst = 0;
         
    
    	newTime = mktime(&time);    /* time in seconds*/
	}
	else
		newTime = time64/1000;
    newTime = (newTime <<15);      /*time in ticks*/
	/* calculate the difference*/
    currentTime = GsnTod_Get();

    if (currentTime > newTime)
    {
        diffNegative = TRUE;
        timeDifference = currentTime - newTime;
    }
    else
    {
        diffNegative = FALSE;
        timeDifference = newTime - currentTime;
    }

    GsnTod_AdjustOffset(diffNegative, timeDifference);
   
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wCmd_SystemTimeGet(UINT8 *ptr)
{
    GSN_SYSTEM_TIME_T currentTime,mSeconds=0,seconds;

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        struct tm *time_local;
        currentTime = GsnTod_Get();
		mSeconds = SYSTIME_TO_MSEC(currentTime);
		seconds = mSeconds / 1000;
        time_local = gmtime((time_t*)&seconds);
        S2w_Printf("\r\n%d/%d/%d,%d:%d:%d,%lld\r\n",time_local->tm_mday,
        time_local->tm_mon+1,time_local->tm_year+1900,time_local->tm_hour,
        time_local->tm_min,time_local->tm_sec,(mSeconds));
    }
    else
    {
        return S2W_EINVAL;
    }
    return S2W_SUCCESS;
}

#ifdef S2W_IPv6_SUPPORT
VOID
AppS2wHdrAndIpv6_Print()
{
    INT8 ipv6str[INET6_ADDRSTRLEN];
    INT8 routerStr[INET6_ADDRSTRLEN]={0};
    GSN_NWIF_IP_CONFIG_T nwParams;
    ULONG ipv6Router[4]={0};
     
    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
    if((s2wLinkState != S2W_LINK_STATE_DISCONNECTED)  && (GsnNwif_Ipv6RouterGet(&s2wappMainTaskCtxt->if0.nwifCtx,ipv6Router) == GSN_SUCCESS))
    {
          S2w_ntop(ipv6Router,routerStr);
    }
    S2w_ntop(nwParams.ipv6.linkLocalAddr,ipv6str);
    S2w_Printf("\r\nIPv6-Linklocal=%s  Prefix=%d  Router=%s\r\n",ipv6str,64,routerStr );
    S2w_ntop(nwParams.ipv6.globalAddr,ipv6str);
    S2w_Printf("\nIPv6-Global=%s  Prefix=%d  Router=%s\r\n",ipv6str,64,routerStr);
}
#endif



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Ip address display function
 *   This function prints the ip address,sunbet and gateway address to
 *   the serial input.
 * @retval none.
 ******************************************************************/
VOID
AppS2wHdrAndIpv4_Print()
{
    GSN_NWIF_IP_CONFIG_T nwParams;
    UINT8 ipaddr[4];
    UINT8 subaddr[4];
    UINT8 gateaddr[4];


    /* get the ip address by calling the geps API
     */
    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);

    memcpy(ipaddr,(UINT8*)&(nwParams.ipv4.ipAddr),4);
    memcpy(subaddr,(UINT8*)&(nwParams.ipv4.subnetMask),4);
    memcpy(gateaddr,(UINT8*)&(nwParams.ipv4.gatewayIpAddr),4);

	{
		//s2wCurrent.netConf.dhcp = 1;
#if 0		
        memcpy(&s2wCurrent.netConf.ipAddr,(UINT8*)&(nwParams.ipv4.ipAddr),4);
        memcpy(&s2wCurrent.netConf.netMask,(UINT8*)&(nwParams.ipv4.subnetMask),4);
        memcpy(&s2wCurrent.netConf.gateway,(UINT8*)&(nwParams.ipv4.gatewayIpAddr),4);
        memcpy(&s2wCurrent.dns1,(UINT8*)&(nwParams.ipv4.dnsPriSrvrIp),4);
        memcpy(&s2wCurrent.dns2,(UINT8*)&(nwParams.ipv4.dnsSecSrvrIp),4);
#endif		
	}
    s2wappMainTaskCtxt->ipaddr = nwParams.ipv4.ipAddr;
    s2wappMainTaskCtxt->subnetMask = nwParams.ipv4.subnetMask;
    /* print on the uart
     */
    S2w_Printf("\n    IP              SubNet         Gateway   \r\n ");
    S2w_Printf("%d.%d.%d.%d:%d.%d.%d.%d:%d.%d.%d.%d ",ipaddr[3],ipaddr[2],ipaddr[1],ipaddr[0],
               subaddr[3],subaddr[2],subaddr[1],subaddr[0],
               gateaddr[3],gateaddr[2],gateaddr[1],gateaddr[0]);

}




/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief serial input process function
 *    This function process each serial input command(AT) and call
 *    the corresponding function to process the command. This function
 *    also check the validity of each AT commands.
 * @param cmd - IN  command string.
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC UINT8
AppS2wCommand_Process(UINT8 *cmd)
{
    UINT8 status = S2W_EINVAL;
    UINT8 *ptr;
    UINT8 *cmdptr;

    UINT32 i;
    UINT32 j=0;

    /* this semaphore takes care of not mixing the command response
       and incomming data
     */
    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);

    /* Validate the AT sequence. */
    if (toupper(cmd[0]) != 'A' || toupper(cmd[1]) != 'T')
    {
		if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_SDIO)
        {
    		UINT32 msg = APP_EVENT_S2W_EINVAL;
		    AppMainCtx_TaskNotify(msg);
		    GsnOsal_SemRelease(&s2wSyncSemID);
		}
		else
		{
        AppS2wProcess_StatusNotify(S2W_EINVAL, 0);
        GsnOsal_SemRelease(&s2wSyncSemID);
		}
        return status;
    }

    if (cmd[2] == '\0')
    {
        AppS2wProcess_StatusNotify(S2W_SUCCESS, 0);
        GsnOsal_SemRelease(&s2wSyncSemID);
        return status;
    }
    ptr = (cmd + 2);
    {

       cmdptr =(cmd + 2);

       while((cmdptr[j]) != '\0')

       {

        if((cmdptr[j]) == '=')

        {
		
			/* Bug Fix 5886 - Command to configure max recv/recvfrom on socket is not working */
           if(((cmdptr[j-1] >='0') && (cmdptr[j-1] <='9') ) && !((cmdptr[j-2] == 'c') || (cmdptr[j-2] == 'C')))
           {
               j--;
           }
           else
           {
               j++;
           }
           break;
        }
          j++;

      }

      if(((cmdptr[0] == '&') && (j > 2)) || (((cmdptr[1] >= '0')&&(cmdptr[1] <= '3')) &&(j == 2)))

      {
         if( !((cmdptr[0] == 'a') || (cmdptr[0] == 'A')))
         j--;

      }


   }


    /* Call the call back function corresponding to the command. */
    for (i = 0; i < sizeof(s2wCmdTable) / sizeof(s2wCmdTable[0]); i++)
    {
        UINT32  len = strlen(s2wCmdTable[i].cmd);

        if (!AppS2wParse_StrnCaseCmp((char *)ptr, s2wCmdTable[i].cmd, len))
        {
         if(len != j)

         {

             if(!((len == 3) && ((ptr[2] == 's') || (ptr[2] == 'S')))   /* AT+WS */
                && !((len == 10) && ((ptr[9] == 'p') || (ptr[9] == 'P')))  /* AT+PSDPSLEEP */
                && !((len == 10) && ((ptr[9] == 'k') || (ptr[9] == 'K'))) /* AT+P2PPROVOK */
#ifdef S2W_IPv6_SUPPORT
                && !((ptr[len-2] == '6') && ((ptr[len-3] == 'v') || ptr[len-3] == 'V'))/* IPv6 */
#endif //S2W_IPv6_SUPPORT
                )
             {
                 status = S2W_EINVAL;
                 break;
             }

         }

            status = s2wCmdTable[i].process(ptr + len);
            break;
        }
    }
	
#ifdef S2W_EXT_FLASH_FS_SUPPORT	
    for (i = 0; i < sizeof(s2wExtFlashCmdTable) / sizeof(s2wExtFlashCmdTable[0]); i++)
	{
        UINT32  len = strlen(s2wExtFlashCmdTable[i].cmd);

        if (!AppS2wParse_StrnCaseCmp((char *)ptr, s2wExtFlashCmdTable[i].cmd, len))
        {
            status = s2wExtFlashCmdTable[i].process(ptr + len);
            break;
        }
    }
#endif
    /* Notify the status to the host
     */
    if((0 == s2wappMainTaskCtxt->dpSleep ) && (stbySuccess == 0))
    {
        AppS2wProcess_StatusNotify(status, 0);
    }

    // flush out all response for spi DMA
       if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
       {
           s2wSpiFs_Flush();
       }

    GsnOsal_SemRelease(&s2wSyncSemID);
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+CID command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_CidInfo(UINT8 *ptr)
{
    UINT32 cidnos =0,i=0;
    UINT8 status = S2W_EINVAL;
    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        S2W_CID_INFO_T cidinfo[16];
        memset(cidinfo,0,sizeof(cidinfo));
        status = AppS2wHal_CidInfoGet(cidinfo,&cidnos);
        if (cidnos == 0)
        {
            S2w_Printf("\r\n No valid Cids\r\n");
        }
        else
        {
            S2w_Printf("\r\nCID\tTYPE\tMODE\tLOCAL PORT\tREMOTE PORT\tREMOTE IP\r\n");
            for(i=0;i<cidnos;i++)
            {
            	// fix for issue 5884 added-cid in hex not in decimal
                S2w_Printf("%x\t",cidinfo[i].cid);
                if( cidinfo[i].conType ==1)
                {
                    S2w_Printf("UDP\t");
                }
                else
                {
					if (1 == AppS2w_ConnStateGet(cidinfo[i].cid))
					{
						S2w_Printf("TCP-SSL ");
					}
					else if(AppS2w_ConnHttpStateGet(cidinfo[i].cid) == 1)
					{
						S2w_Printf("HTTP\t");
					}
					else
                    {
                        S2w_Printf("TCP\t");
                    }
                }
                cidinfo[i].conMode?S2w_Printf("SERVER\t"):
                                   S2w_Printf("CLIENT\t");
#ifdef S2W_IPv6_SUPPORT
            if(s2wCidList[i].addrType & ADDR_TYPE_IPv6)
            {
              INT8 ipv6str[INET6_ADDRSTRLEN];
              S2w_ntop((ULONG*)s2wCidList[i].remoteIpv6,ipv6str);
              S2w_Printf("%4d\t\t%4d\t\t %s \r\n",cidinfo[i].localPort,cidinfo[i].remotePort,ipv6str);  
              
             }
            else
#endif 
            
                S2w_Printf("%4d\t\t%4d\t\t%3d.%3d.%3d.%3d\r\n",cidinfo[i].localPort,
                          cidinfo[i].remotePort,cidinfo[i].remoteIp[0],cidinfo[i].remoteIp[1],
                           cidinfo[i].remoteIp[2],cidinfo[i].remoteIp[3]);
            }
        }

    }
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+BDATA command
 *      This function set/reset bulk mode.
 * @param ptr Pointer to the user input string.
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
UINT8
S2w_CmdBulkDataState(UINT8 *ptr)
{
    UINT8 status;
    UINT8 mode;

    status = AppS2wParse_Boolean(ptr, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wCurrent.bulkTxEnable = mode;
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NCTCP Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Nctcp(UINT8 *ptr)
{
    S2W_NETDATA_T peerData;
    UINT8 *temp = ptr;
    UINT32 status;
    UINT8 cid;

    if (s2wIsAutoconnected)
    {
        return S2W_EINVAL;
    }
    if(s2wLinkState == S2W_LINK_STATE_DISCONNECTED)
    {
        return S2W_LINK_LOST_EVT;
    }
    status = AppS2wParse_AddrPort(&temp, &peerData);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    peerData.proto = S2W_NETDATA_PROTO_TCP;
    peerData.mode = S2W_NETDATA_MODE_CLIENT;

    status = AppS2wHal_NetTcpClient(&peerData, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);
    return status;

}

PUBLIC UINT8
AppS2wCmd_scanTimeSet(UINT8 *ptr)
{
    UINT8 status = S2W_SUCCESS;
    UINT8 *p;
    UINT32 minTime=0,maxTime=0,passiveTime=0;

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        S2w_Printf("\r\nMinScanTime=%d\r\nMaxScanTime=%d\r\n", s2wCurrent.minScanTime,
                    s2wCurrent.registers[S2W_REG_SCAN_TIME]);
        return S2W_SUCCESS;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &minTime);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &maxTime);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(maxTime < minTime)
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if(p)
    {
        status = AppS2wParse_Int(p, &passiveTime);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }
    
   status = GsnWdd_ScanParamSet(&s2wappMainTaskCtxt->if0.wddCtx,minTime,maxTime,passiveTime);

   /* update the default in profile */
    s2wCurrent.registers[S2W_REG_SCAN_TIME] = maxTime;
    s2wCurrent.minScanTime = (UINT16)minTime;

    return  status;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+NSTCP command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS or S2W_FAILURE.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Nstcp(UINT8 *ptr)
{
    S2W_NETDATA_T peerData;
    UINT8 status;
    UINT32 port;
    UINT8 cid;
	UINT32 maxConn=0;
    UINT8 *p;

    if (s2wIsAutoconnected)
    {
        return S2W_EINVAL;
    }
    if(s2wLinkState == S2W_LINK_STATE_DISCONNECTED)
    {
        return S2W_LINK_LOST_EVT;
    }
	p = AppS2wParse_NextParamGet(&ptr);
	if (*p == 0)
	{
	  return S2W_EINVAL;
	}
    status = AppS2wParse_Int(p, &port);
    if (status != S2W_SUCCESS || !is_valid_port(port))
    {
        return S2W_EINVAL;
    }
	p = AppS2wParse_NextParamGet(&ptr);
	maxConn = 15;
	if (p != NULL)
	{
		status = AppS2wParse_Int(p, &maxConn);
		if (status != S2W_SUCCESS )
		{
			return S2W_EINVAL;
		}
    }

    peerData.port = port;
    peerData.proto = S2W_NETDATA_PROTO_TCP;
    peerData.mode = S2W_NETDATA_MODE_SERVER;


    status = AppS2wHal_NetTcpServer(&peerData, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	AppS2wHal_TcpSrvMaxConSet(cid,maxConn);

    AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * Process AT+NSUDP command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS or S2W_FAILURE.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Nsudp(UINT8 *ptr)
{
    S2W_NETDATA_T peerData;
    UINT8 status;
    UINT32 port;
    UINT8 cid;

    if (s2wIsAutoconnected)
    {
        return S2W_EINVAL;
    }
    if(s2wLinkState == S2W_LINK_STATE_DISCONNECTED)
    {
        return S2W_LINK_LOST_EVT;
    }

    status = AppS2wParse_Int(ptr, &port);
    if (status != S2W_SUCCESS || !is_valid_port(port))
    {
        return S2W_EINVAL;
    }
    peerData.port = port;
    peerData.proto = S2W_NETDATA_PROTO_UDP;
    peerData.mode = S2W_NETDATA_MODE_SERVER;

    status = AppS2wHal_NetUdpServer(&peerData, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * Process AT+SETSOCKOPT command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS ,S2W_FAILURE or S2W_EINVAL.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_SetSockOp(UINT8 *ptr)
{
    UINT8 status;
    S2W_SOCK_OP_T params;
    UINT8 *p;


    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &params.cid);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &params.type);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Hex(p, &params.param);
    if (status != S2W_SUCCESS)
    {
    	return status;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &params.paramValue);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &params.paramSize);

    status = AppS2wHal_SockOpSet(&params);

    return status;
}





/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+ERRCOUNT command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_ErrorCount(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    //S2W_ERROR_COUNT_T errorParam;


    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        /* print the error counts */
        //S2w_Printf("\r\nAPP-WD     :%d\r\nWLAN-WD    :%d\r\nWLAN-ABORT :%d\r\nWLAN-ASSERT:%d\r\nAPP-SW-RST :%d\r\nWLAN-SW-RST:%d\r\n",
          //         appRtcMemData.err.appWdCount,appRtcMemData.err.wlanWdCount,
            //       appRtcMemData.err.wlanAbortCount,appRtcMemData.err.wlanAssertCount,
              //     appRtcMemData.err.appSwResetCount,appRtcMemData.err.wlanSwResetCount);
        status = S2W_SUCCESS;
    }
    return status;
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Close all connections and disassociate.
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC UINT8
AppS2w_HangUp(VOID)
{
	UINT8 status=S2W_FAILURE;
    s2wIsAutoconnected = 0;

    /* close all connections
     */
    AppS2wHal_NetCloseAll(0);
    curCid = INVALID_CID;
    /* call the hal disassociate function
     */
	s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
					   GSN_SOFT_TMR_ONESHOT,0,
						SEC_TO_SYSTIME(S2W_WLAN_RESPTIMEOUT),
					  ( GSN_SOFT_TMR_CBR_T )AppS2w_WlanRespTmrCb,NULL);
    status=AppS2wHal_Disassociate(0);	
	GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
	return status;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Display the scan result in the format, "SSID,BSSID,Channel,RSSI,Mode".
 *   This function should be called from HAL function for scan,
 *   after finishing the scan.
 * @param ssid    - IN SSID of network.
 * @param ssidLen - IN SSID length.
 * @param bssid   - IN BSSID of network.
 * @param channel - IN Channel.
 * @param rssi    - IN RSSI.
 * @param adhoc   - IN 802.11 operating mode.
 * @return None.
 ******************************************************************/
PUBLIC VOID
AppS2wScanResult_Print(UINT8 *ssid, UINT8 ssidLen, UINT8 *bssid,
        UINT8 channel, UINT8 rssi,  UINT8 adhoc)
{
    UINT8 len=0;
    static const char prefix[] = "\r\n";

    /*print format --> bssid  ssid  channel  type   Security  RSSI
     */
    AppS2wHal_CharNPut(prefix, sizeof(prefix) - 1);
    S2w_Printf(" %02x:%02x:%02x:%02x:%02x:%02x, ",
           bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);

    AppS2wHal_CharNPut(ssid, ssidLen);

    for(len = (32- ssidLen);len>0;len--)
    {
        S2w_Printf(" ");
    }
    S2w_Printf(", %02d", channel);
    if(adhoc)
    {
        S2w_Printf(",  ADHOC ");
    }
    else
    {
        S2w_Printf(",  INFRA ");
    }

    S2w_Printf(", %d ,",(signed char)rssi);
}






#ifndef IOT_APP_ENABLE

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WM Command.
 *   This function check the validy of the parameter passed and set the
 *   wireless mode as per the parameter.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Wmode(UINT8 *ptr)
{
    UINT8 status;
    UINT32 mode,interval,noStations,dtimPeriod;
	UINT32 inactivityTimeoutInSec,grpKeyUpdtIntrvl;
    UINT8 *p;
    GSN_WIF_WLAN_NW_TYPE_T prevWlanNwType;


    /* check the validity of the parameter passed
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Int(p, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(mode > S2W_WLANDATA_MODE_PROV_AP || S2W_WLANDATA_MODE_ADHOC == mode )
    {
        return S2W_EINVAL;
    }
    // remap the mode
    if(mode == 0)
    {
        mode = S2W_WLANDATA_MODE_INFRA;
    }
	if(mode == s2wCurrent.mode)
	{			
		if((mode == S2W_WLANDATA_MODE_AP) || (mode == S2W_WLANDATA_MODE_PROV_AP))
		{
			s2wappMainTaskCtxt->bcastSsid = S2W_DEFAULT_AP_SSID_BROADCAST;
			s2wappMainTaskCtxt->inactivityTimeoutInSec= 360;
			s2wappMainTaskCtxt->dtimPeriod = 3;
		    s2wappMainTaskCtxt->grpKeyUpdtIntrvl= 3600;
		    GsnWdd_SetGrpKeyUpdateTime(&s2wappMainTaskCtxt->if0.wddCtx, s2wappMainTaskCtxt->grpKeyUpdtIntrvl);
		}
	}

    /* if the mode selected is 2(AP) accept the next param(beacon interval )also */
    prevWlanNwType = s2wappMainTaskCtxt->if0.macIfType;
    if((mode == S2W_WLANDATA_MODE_AP) || (mode == S2W_WLANDATA_MODE_PROV_AP))
    {
        s2wappMainTaskCtxt->bcastSsid = S2W_DEFAULT_AP_SSID_BROADCAST;
		s2wCurrent.lmtdApConf.noStations = S2W_DEFAULT_AP_SUPPORTED_STATIONS;
        p = AppS2wParse_NextParamGet(&ptr);
        if ((p) && (*p != '\0'))
        {
            status = AppS2wParse_Int(p, &interval);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            if((interval < 50) || (interval > 1500))
            {
                return S2W_EINVAL;
            }
            s2wCurrent.lmtdApConf.beaconInterval = interval;
        }
        p = AppS2wParse_NextParamGet(&ptr);
        if ((p) && (*p != '\0'))
        {
            status = AppS2wParse_Boolean(p, &s2wappMainTaskCtxt->bcastSsid);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
        }
		p = AppS2wParse_NextParamGet(&ptr);
        if ((p) && (*p != '\0'))
        {
            status = AppS2wParse_Int(p, &noStations);
            if (status != S2W_SUCCESS || noStations == 0)
            {
                return S2W_EINVAL;
            }
			s2wCurrent.lmtdApConf.noStations = (UINT8)noStations;
        }
		s2wappMainTaskCtxt->dtimPeriod = 3;
		p = AppS2wParse_NextParamGet(&ptr);
		if ((p) && (*p != '\0'))
		{
			status = AppS2wParse_Int(p, &dtimPeriod);
			if (status != S2W_SUCCESS || dtimPeriod == 0)
			{
				return S2W_EINVAL;
			}
			s2wappMainTaskCtxt->dtimPeriod= (UINT8)dtimPeriod;
		}
		s2wappMainTaskCtxt->inactivityTimeoutInSec= 360;
		p = AppS2wParse_NextParamGet(&ptr);
		if ((p) && (*p != '\0'))
		{
			status = AppS2wParse_Int(p, &inactivityTimeoutInSec);
			if (status != S2W_SUCCESS || inactivityTimeoutInSec == 0)
			{
				return S2W_EINVAL;
			}
			s2wappMainTaskCtxt->inactivityTimeoutInSec= (UINT16)inactivityTimeoutInSec;
		}
	
		s2wappMainTaskCtxt->grpKeyUpdtIntrvl= 3600;
		p = AppS2wParse_NextParamGet(&ptr);
		if ((p) && (*p != '\0'))
		{
			status = AppS2wParse_Int(p, &grpKeyUpdtIntrvl);
			if (status != S2W_SUCCESS || grpKeyUpdtIntrvl == 0)
			{
				return S2W_EINVAL;
			}
			s2wappMainTaskCtxt->grpKeyUpdtIntrvl= (UINT16)grpKeyUpdtIntrvl;
		}
		if(mode == s2wCurrent.mode)
			return S2W_SUCCESS;
		App_InterfaceStop(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
		
		s2wappMainTaskCtxt->if0.macIfNum = 0;
		s2wappMainTaskCtxt->if0.macIfType = GSN_WIF_WLAN_NW_TYPE_AP;

        if(prevWlanNwType == S2W_WLANDATA_MODE_ISOTX)
        {
            App_IfInit(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);            
            /*Open the interface*/
            App_InterfaceStart(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
        }
        else
        {
            App_IfReinit(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
        }
		

	    GsnWdd_SetGrpKeyUpdateTime(&s2wappMainTaskCtxt->if0.wddCtx, s2wappMainTaskCtxt->grpKeyUpdtIntrvl);

	}
    else if (S2W_WLANDATA_MODE_INFRA == mode)/*STA Mode*/
    {
       
	   App_InterfaceStop(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
	   
	   s2wappMainTaskCtxt->if0.macIfNum = 0;
	   s2wappMainTaskCtxt->if0.macIfType = GSN_WIF_WLAN_NW_TYPE_STA;

        if(prevWlanNwType == S2W_WLANDATA_MODE_ISOTX)
        {
            App_IfInit(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);            
            /*Open the interface*/
            App_InterfaceStart(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
        }
        else
        {
	        App_IfReinit(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
        }
        
       AppS2w_SetWlanDfltParams(profile_params.defaultProfile);
       GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,S2W_DEFAULT_SYNCLOSS_INTERVAL);

    }
    else if (S2W_WLANDATA_MODE_ISOTX == mode)/*STA Mode*/
    {
#ifdef S2W_ISOTX_SUPPORT       
	   App_InterfaceStop(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
	   
	   s2wappMainTaskCtxt->if0.macIfNum = 0;
	   s2wappMainTaskCtxt->if0.macIfType = GSN_WIF_WLAN_NW_TYPE_ISOTX;
	   
       App_IfInit(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);            
       /*Open the interface*/
       App_InterfaceStart(s2wappMainTaskCtxt, &s2wappMainTaskCtxt->if0);
#else
	   return S2W_EINVAL;
#endif

    }
    // update the mac address after switching the mode
    {
        UINT8 macAddr[6];
        // depends on mode the mac changes
        if(mode == S2W_WLANDATA_MODE_INFRA)
        {
        //S2w_LoadMacAddr(macAddr);
        S2w_macAddrRTCGet(macAddr);
		}
		else
		{
			memcpy(macAddr,s2wCurrent.lmtdApConf.macAddr.array , 6);
		}

        AppS2wHal_MacAddrSet(macAddr, TRUE);
    }
    /* update the mode in active profile
     */
    s2wCurrent.mode = mode;
    return S2W_SUCCESS;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * Process AT+WRXPS command.
 *   This funcion validates the parameter passed  and call the hal function
 *   to configure the PS-POLL mode.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-Power save configuration failed.
 ******************************************************************/
UINT8
AppS2wCmd_PowerSave(UINT8 *ptr)
{
    UINT8 enable;
    UINT8 status;
	UINT8 *p;
	UINT32 beaconWaitDur = 10;
    /* valiadate the parameter as TRUE or FALSE
     */
    p = AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Boolean(p, &enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

	p = AppS2wParse_NextParamGet(&ptr);
	if (p)
	{
		status = AppS2wParse_Int(p, &beaconWaitDur);
		if (status != S2W_SUCCESS)
		{
			return status;
		}
		
		GsnWdd_PsCfgBeaconWaitDurSet(&s2wappMainTaskCtxt->if0.wddCtx, beaconWaitDur);
	}
    /* call the hal function to configure the PS-POLL mode
     */
    status = AppS2wHal_PowerSaveConfig(enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wCurrent.powerSave = enable;
    return status;
}

PUBLIC VOID
AppS2wScan_Notification( VOID* cText,INT32 status, INT8 *rsltBuff,
   	                     UINT32 rsltCount )
{
	/* copy the data to user buffer and return
	 */
    UINT8 i=0;

    for(i=0;i<rsltCount;i++)
    {
        
        GSN_WDD_SCAN_ENTRY_T* scanEntryBuff = (GSN_WDD_SCAN_ENTRY_T*)(rsltBuff + (i*sizeof(GSN_WDD_SCAN_ENTRY_T))) ;
        if(scanEntryBuff->channel > 0)
        {
        scanDisplayInfo[scanDisplayInfoCount].channel = scanEntryBuff->channel;
        scanDisplayInfo[scanDisplayInfoCount].rssi = scanEntryBuff->rssi;
        memcpy(scanDisplayInfo[scanDisplayInfoCount].bssid.array,scanEntryBuff->bssid,6);
        memcpy(&scanDisplayInfo[scanDisplayInfoCount].ssid,&scanEntryBuff->ssid,sizeof(GSN_WLAN_MAC_SSID_T));
        scanDisplayInfo[scanDisplayInfoCount].capability = GsnMacUtil_ExtractCapaInfo((GSN_MAC_FRAME_T*)scanEntryBuff->frame);

        scanDisplayInfo[scanDisplayInfoCount].encryptionType = GsnMacUtil_ExtractEncryptionStatus((GSN_MAC_FRAME_T*)scanEntryBuff->frame,scanEntryBuff->frameLen,GSN_MAC_BEACON_SSID_OFT,&scanDisplayInfo[scanDisplayInfoCount].authType);
        scanDisplayInfoCount++;
        }
     
    }

    // if the scan finished release the scan wait semaphore
    if(status == GSN_WDD_SCAN_COMPLETE)
    {
                //UINT8 ret;
		 /*ret = */GsnOsal_SemRelease ( &stScanSemaphore );
                 
	}
}




PUBLIC VOID
s2wScanResult_Print(S2W_SCAN_DISPLAY_INFO_T scanDisplayInfo[],UINT8 count)
{
    UINT8 len=0,i=0;
    for(i=0;i<count;i++)
    {
        /*print format --> bssid  ssid  channel  type   Security  RSSI
         */
         S2w_Printf("\r\n %02x:%02x:%02x:%02x:%02x:%02x, ",
           scanDisplayInfo[i].bssid.array[0], scanDisplayInfo[i].bssid.array[1], scanDisplayInfo[i].bssid.array[2],
           scanDisplayInfo[i].bssid.array[3], scanDisplayInfo[i].bssid.array[4], scanDisplayInfo[i].bssid.array[5]);

         AppS2wHal_CharNPut(scanDisplayInfo[i].ssid.array, scanDisplayInfo[i].ssid.length);

         for(len = (32- scanDisplayInfo[i].ssid.length);len>0;len--)
         {
             S2w_Printf(" ");
         }
         S2w_Printf(", %02d", scanDisplayInfo[i].channel);

         if((scanDisplayInfo[i].capability & GSN_MAC_CAPA_IBSS) )
         {
             S2w_Printf(",  ADHOC ");
         }
         else
         {
             S2w_Printf(",  INFRA ");
         }
         S2w_Printf(", %d ,",(signed char)scanDisplayInfo[i].rssi);

         /* print the security info
          */
         {
             UINT8* security = "NONE";
             if(scanDisplayInfo[i].capability & GSN_MAC_CAPA_PRIVA)
             {
                 if (scanDisplayInfo[i].encryptionType & GSN_MAC_ENC_WPA2)
                 {
                     if (GSN_MAC_RSNIE_KEYMGT_PSK  == scanDisplayInfo[i].authType)
                     {
                         security = "WPA2-PERSONAL";
                     }
                     else if (scanDisplayInfo[i].authType == GSN_MAC_RSNIE_KEYMGT_8021X)
                     {
                         security = "WPA2-ENTERPRISE";
                     }
                 }
                 else if (scanDisplayInfo[i].encryptionType & GSN_MAC_ENC_WPA)
                 {
                     if (GSN_MAC_RSNIE_KEYMGT_PSK  == scanDisplayInfo[i].authType)
                     {
                         security = "WPA-PERSONAL";
                     }
                     else if (scanDisplayInfo[i].authType == GSN_MAC_RSNIE_KEYMGT_8021X)
                     {
                         security = "WPA-ENTERPRISE";
                     }
                 }
                 else
                 {
                     /* Open with WEP cannot be identified from capabilities
                      */
                     security = "WEP";
                 }
             }
             S2w_Printf(" %s", security);
   		 }
	 }
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WS Command.
 *   This function check the validy of the parameter passed and call the
 *   hal function to start the scan.
 *
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-scan failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Wscan(UINT8 *ptr)
{
    UINT32 status = S2W_SUCCESS;
    UINT8 allChScan=0,i=0;
    S2W_WLANDATA_T params;
    GSN_WDD_SCAN_PARAMS_T scanParams;
    
    scanDisplayAllCount = 0;
    memset(&params, 0, sizeof(params));


    if (*ptr == '=')
    {
        /* check the parameter passed is valid
         */
        status = AppS2wParse_Wcmd(ptr + 1, &params, pwc_scan);
    }
    else if (*ptr)
    {
        status = S2W_FAILURE;
    }

    if (status != S2W_SUCCESS)
    {
        return status;
    }

    params.mode = s2wCurrent.mode;

    /* start the scan
     */
    if(!params.channel)  //scan all the channels
    {
		allChScan=1;
    }
    memset(&scanParams,0,sizeof(GSN_WDD_SCAN_PARAMS_T));
    scanParams.scanType = GSN_MAC_SCAN_TYPE_ACTIVE;
    scanParams.ssid.length = params.ssidLen;
    scanParams.channel[1] = 0;
    if(scanParams.ssid.length)
    {
        memcpy(scanParams.ssid.array, params.ssid, scanParams.ssid.length);
    }
	
    if(params.validBssid)
    {
        memcpy(scanParams.bssid.array, params.bssid,S2W_MAC_ADDR_SIZE);
    }    
    
     S2w_Printf("\r\n       BSSID              SSID                     Channel  Type  RSSI Security");
    for(i=1;i<15;i++)
    {
        if(!params.channel)  //scan all the channels
        {
            /* fill the channels in the scanParams structure
             */
            scanParams.channel[0] = i;
		}
        else
        {
            scanParams.channel[0] = params.channel;

        }
       
        scanDisplayInfoCount = 0;

        status = GsnWdd_Scan(&s2wappMainTaskCtxt->if0.wddCtx,&scanParams,(INT8 *)s2wScanUserEntryBuff,
		                 (2 * sizeof(GSN_WDD_SCAN_ENTRY_T)),(GSN_WDD_SCAN_NOTIF_CB_T)AppS2wScan_Notification,s2wappMainTaskCtxt);
		if(status == GSN_OPERATION_IN_PROGRESS)
		{
			// wait on a semaphore to finish the scan
			GsnOsal_SemAcquire ( &stScanSemaphore, GSN_OSAL_WAIT_FOREVER );
		}
			if(params.ssid[0])
                        {
                          for(UINT index=0;index<scanDisplayInfoCount;index++)
                          {
                            if(!memcmp(&scanDisplayInfo[index].ssid.array,&params.ssid,scanDisplayInfo[index].ssid.length))
                  {
                              s2wScanResult_Print(&scanDisplayInfo[index],1); 
                       scanDisplayAllCount++;
                  }
                          }  
                          
                        }
                          
                         else
		{
                        /* get the scanned info which is stored in the buffer and print it on serial
			   then contimue.
			 */
			s2wScanResult_Print(scanDisplayInfo,scanDisplayInfoCount);
			scanDisplayAllCount +=scanDisplayInfoCount;
		}
			// break the loop if scan for only one channel or finished
		if((allChScan !=1) || ((scanParams.channel[0] == S2W_MAX_CH) && (s2wCurrent.regDomain == S2W_DOMAIN_FCC))
		   ||((scanParams.channel[0] == (S2W_MAX_CH+2)) && (s2wCurrent.regDomain == S2W_DOMAIN_ETSI)) ||
		     ((scanParams.channel[0] == (S2W_MAX_CH+3)) && (s2wCurrent.regDomain == S2W_DOMAIN_TELEC)))
			{
				break;
		}

	}
	    S2w_Printf("\r\nNo.Of AP Found:%d\r\n",scanDisplayAllCount);

    status = S2W_SUCCESS;
    return status;
}

VOID
S2w_getApSecurityConfig(GSN_WDD_WLAN_CFG_T *pWlanConfig, UINT8 securityType)
{
	switch(securityType)
    {
    	case SECTYPE_AUTO:
      	{
      		pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_ANY;
        	pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_MIXED;
    	}
    	break;
    	case SECTYPE_WEP:
    	{
			pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WEP;
            if(s2wCurrent.mode == S2W_WLANDATA_MODE_PROV_AP)
            {
                pWlanConfig->securityCfg.wepConfig.KeyId = S2W_DEFAULT_GRP_PROV_WEP_KEY_ID -1  ;
                pWlanConfig->securityCfg.wepConfig.KeyLen = (GSN_WDD_WEP_KEY_LEN_T)S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN ; /**< Key len, 5 or 13 */
                memcpy(&pWlanConfig->securityCfg.wepConfig.Key,S2W_DEFAULT_GRP_PROV_WEP_KEY,
                        S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN);
                if(S2W_DEFAULT_GRP_PROV_WEP_AUTH == GSN_MAC_AUTH_SHARED)
                {
                    pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_SHARED;
                }
                else // open
                {
                    pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_OPEN;
                }
            }
            else
            {
			pWlanConfig->securityCfg.wepConfig.KeyId = s2wCurrent.lmtdApConf.wepKeyConfig.KeyId -1  ;
			pWlanConfig->securityCfg.wepConfig.KeyLen = s2wCurrent.lmtdApConf.wepKeyConfig.KeyLen ; /**< Key len, 5 or 13 */
			memcpy(&pWlanConfig->securityCfg.wepConfig.Key,&s2wCurrent.lmtdApConf.wepKeyConfig.Key,
					s2wCurrent.lmtdApConf.wepKeyConfig.KeyLen); 
			if(s2wCurrent.lmtdApConf.wepKeyConfig.authType== GSN_MAC_AUTH_SHARED)
			{
				pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_SHARED;
			}
			if(s2wCurrent.security.authMode == GSN_MAC_AUTH_OPEN)
			{
				pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_OPEN;
			}
    	}
    	}
    	break;
    	case SECTYPE_NONE:
    	{
        	pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
    	}
   		break;

		case SECTYPE_WPAPSK:
    	{
        	pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA_PERSONAL;
        	pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_TKIP;
    	}
    	break;
   		case SECTYPE_WPA2PSK:
   		{
       		pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA2_PERSONAL;
       		pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_AES;
   		}
	    break;
        case SECTYPE_WPA2PSK_TKIP:
	    {
    	   	pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA2_PERSONAL;
       		pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_MIXED;
   		}
   		break;
	}
    if((securityType == SECTYPE_WPAPSK) || \
       (securityType == SECTYPE_WPA2PSK) || \
       (securityType == SECTYPE_WPA2PSK_TKIP))
    {
       if(s2wCurrent.mode == S2W_WLANDATA_MODE_PROV_AP)
       {
           pWlanConfig->securityCfg.pskConfig.passPhrase.Len = sizeof (S2W_DEFAULT_GRP_PROV_WPA_PASSPHRASE)- 1 ;
           memcpy( pWlanConfig->securityCfg.pskConfig.passPhrase.Passphrase, S2W_DEFAULT_GRP_PROV_WPA_PASSPHRASE,
                   pWlanConfig->securityCfg.pskConfig.passPhrase.Len);
           pWlanConfig->securityCfg.pskConfig.pskValid = 0;

       }
       else
	{
		pWlanConfig->securityCfg.pskConfig.passPhrase.Len = s2wCurrent.lmtdApConf.passphrase.Len ;
		memcpy( pWlanConfig->securityCfg.pskConfig.passPhrase.Passphrase, s2wCurrent.lmtdApConf.passphrase.Passphrase,
				 s2wCurrent.lmtdApConf.passphrase.Len);
		pWlanConfig->securityCfg.pskConfig.pskValid = s2wCurrent.lmtdApConf.lmtdApPskValid;
		if(s2wCurrent.lmtdApConf.lmtdApPskValid == 1)
		{
			memcpy( pWlanConfig->securityCfg.pskConfig.psk, s2wCurrent.lmtdApConf.lmtdApPsk,
				 S2W_PSK_LEN);
		 }
	}
}
}
VOID
S2w_getSecurityConfig(GSN_WDD_WLAN_CFG_T *pWlanConfig)
{
    /* copy the security parameter passed
     */
    pWlanConfig->securityCfg.wepConfig.KeyId =
                                            s2wCurrent.security.wep.keyIdx-1;
    pWlanConfig->securityCfg.wepConfig.KeyLen =
            (GSN_WDD_WEP_KEY_LEN_T)s2wCurrent.security.wep.keyLen[s2wCurrent.security.wep.keyIdx-1];
    memcpy(pWlanConfig->securityCfg.wepConfig.Key,
            s2wCurrent.security.wep.key[s2wCurrent.security.wep.keyIdx-1],
            s2wCurrent.security.wep.keyLen[s2wCurrent.security.wep.keyIdx-1]);

    pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_ANY;
    pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_MIXED;

    switch(s2wCurrent.securityType)
    {
        case SECTYPE_AUTO:
        {
            pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_ANY;
            pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_MIXED;
			if(s2wCurrent.security.authMode == GSN_MAC_AUTH_SHARED)
			{
				pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_SHARED;
			}
			if(s2wCurrent.security.authMode == GSN_MAC_AUTH_OPEN)
			{
				pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_OPEN;
			}
        }
        break;
        case SECTYPE_WEP:
        {
			pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WEP;
			if(s2wCurrent.security.authMode == GSN_MAC_AUTH_SHARED)
			{
				pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_SHARED;
			}
			if(s2wCurrent.security.authMode == GSN_MAC_AUTH_OPEN)
			{
				pWlanConfig->securityCfg.wepConfig.authType = GSN_WDD_SEC_WEP_OPEN;
			}
        }
        break;
        case SECTYPE_NONE:
        {
            pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_DISABLE;
        }
        break;
        case SECTYPE_WPAPSK:
        {
            pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA_PERSONAL;
            pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_TKIP;
        }
        break;
        case SECTYPE_WPA:
        {
            pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA_ENTERPRISE;
			pWlanConfig->securityCfg.pskConfig.wpaAlgo =GSN_WDD_WPA_ALGO_TKIP	;
            break;
        }
       case SECTYPE_WPA2PSK:
       {
           pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA2_PERSONAL;
           pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_AES;
       }
       break;
	   case SECTYPE_WPA2:
	   {
		   pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA2_ENTERPRISE;
		   pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_MIXED;
		   break;
	   }
       case SECTYPE_WPA2PSK_TKIP:
       {
           pWlanConfig->securityCfg.mode = GSN_WDD_SEC_MODE_WPA2_PERSONAL;
           pWlanConfig->securityCfg.pskConfig.wpaAlgo = GSN_WDD_WPA_ALGO_MIXED;
       }
       break;
    }


    /* if psk key is valid copy that to wlan structure
     */
    if(s2wCurrent.security.wpa.pskValid) // copy the psk
    {
        memcpy(&pWlanConfig->securityCfg.pskConfig.psk,
                      s2wCurrent.security.wpa.psk, 32);
        /* if psk is valid check the profile ssid matches with ssid passed else make it false
         */
        if((memcmp(s2wCurrent.security.wpa.ssid, pWlanConfig->ssid.array,pWlanConfig->ssid.length) != 0) &&
            (s2wCurrent.security.wpa.ssidLen > 0))
        {
            s2wCurrent.security.wpa.pskValid = 0;
        }
        else if((memcmp(s2wCurrent.security.wpa.ssid,pWlanConfig->ssid.array,pWlanConfig->ssid.length) == 0) &&
               (pWlanConfig->ssid.length != s2wCurrent.security.wpa.ssidLen) &&
               (s2wCurrent.security.wpa.ssidLen > 0))
        {
            s2wCurrent.security.wpa.pskValid = 0;
            memset(s2wCurrent.security.wpa.ssid,0,sizeof(s2wCurrent.security.wpa.ssid));
        }
    }
    pWlanConfig->securityCfg.pskConfig.pskValid =
                                               s2wCurrent.security.wpa.pskValid;

    memcpy(pWlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
           s2wCurrent.security.wpa.wpaPassPhrase,
           s2wCurrent.security.wpa.passPhraseLen);
    pWlanConfig->securityCfg.pskConfig.passPhrase.Len =
                                       s2wCurrent.security.wpa.passPhraseLen;

}




#define APP_NWIF_DHCPv6_CLIENT_THREAD_STACK_SIZE  2048
INT32 L2ConnectStatus = 0;
UINT8 L3ConnectStatus=0;
UINT8 L3ConnectStatus_v6=0;
UINT8 L3Dhcpv6Status=0;
INT8 dhcpv6ClientStack[APP_NWIF_DHCPv6_CLIENT_THREAD_STACK_SIZE];

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WA Command.
 *   This command check the validity of parameters passed and call the
 *   hal association function.
 * @param ptr pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-scan failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Wassoc(UINT8 *ptr)
{
    S2W_WLANDATA_T params;
#ifndef S2W_IP2WIFI_SUPPORT
    GSN_NWIF_DHCP_PARAMS_T dhcpParams;
    GSN_NWIF_IP_CONFIG_T ipConfig;
#endif
#ifdef S2W_IPv6_SUPPORT
    GSN_NWIF_DHCP_PARAMS_T dhcpv6Params;
    GSN_NWIF_IPv6_CONFIG_T userIpv6Config;


#endif
    INT32  index;
	UINT8 mac[6],macStr[25];

    UINT32 status;
    GSN_WDD_CONNECT_FLAG_T conctflags=GSN_WDD_CONNECT_FLAG_NONE;
    GSN_STATUS retVal = GSN_SUCCESS;
    UINT8 eapFastRetryCnt = 0;
    memset(&params, 0, sizeof(params));
    globalUseHRssi = 0;
	L3ConnectStatus=0;
        L3ConnectStatus_v6=0;
    /* check the validity of the parameters passed
     */
    status = AppS2wParse_Wcmd(ptr, &params, pwc_assoc);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
#ifdef S2W_SECURITY_WPS_ENABLE
    wpsConnDone = FALSE;
#endif
    if ((s2wLinkState != S2W_LINK_STATE_DISCONNECTED) || (GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE))
    {
        //S2w_Debug("disconnecting\n\n");
		s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
						   GSN_SOFT_TMR_ONESHOT,0,
							SEC_TO_SYSTIME(S2W_WLAN_RESPTIMEOUT),
						  ( GSN_SOFT_TMR_CBR_T )AppS2w_WlanRespTmrCb,NULL);
        retVal = AppS2wHal_Disassociate(0);
		GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
#ifndef S2W_IP2WIFI_SUPPORT
        if(retVal != GSN_FAILURE)
        {
            GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
		}
#endif
    }

    /* Copy the mode.
     */
    params.mode = s2wCurrent.mode;
    /* execute the wdd part for connection
     */

        GSN_WDD_WLAN_CFG_T *pWlanConfig;
      //  GsnOsal_SemCreate  ( &s2wConnectSemaphore, 0 );
        pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
        memset(pWlanConfig, 0, sizeof(*pWlanConfig));
        pWlanConfig->ssid.length = params.ssidLen;
        memcpy((INT8 *)pWlanConfig->ssid.array, params.ssid, pWlanConfig->ssid.length);
		if(params.validBssid)
		{
			memcpy((INT8 *)pWlanConfig->bssid.array,params.bssid,S2W_MAC_ADDR_SIZE);
			conctflags = GSN_WDD_CONNECT_FLAG_USE_BSSID;
		}

        if(params.channel)
        {
        pWlanConfig->channel[0] = params.channel;
        pWlanConfig->channel[1] = 0;
		}
		else
		{
			pWlanConfig->channel[0] = 1;
            pWlanConfig->channel[1] = 2;
            pWlanConfig->channel[2] = 3;
            pWlanConfig->channel[3] = 4;
            pWlanConfig->channel[4] = 5;
            pWlanConfig->channel[5] = 6;
            pWlanConfig->channel[6] = 7;
            pWlanConfig->channel[7] = 8;
            pWlanConfig->channel[8] = 9;
            pWlanConfig->channel[9] = 10;
            pWlanConfig->channel[10] = 11;
            switch(s2wCurrent.regDomain)
            {
				case S2W_DOMAIN_FCC:
            pWlanConfig->channel[11] = 0;
				break;
				case S2W_DOMAIN_ETSI:
				pWlanConfig->channel[11] = 12;
				pWlanConfig->channel[12] = 13;
				pWlanConfig->channel[13] = 0;
				break;
				case S2W_DOMAIN_TELEC:
				pWlanConfig->channel[11] = 12;
				pWlanConfig->channel[12] = 13;
				pWlanConfig->channel[13] = 14;
				pWlanConfig->channel[14] = 0;
				break;
				default:
				pWlanConfig->channel[11] = 0;
				break;
			}
		}
        
        S2w_getSecurityConfig(pWlanConfig);
		if(s2wappMainTaskCtxt->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_STA)
		{
			conctflags = (GSN_WDD_CONNECT_FLAG_T) (conctflags | (GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT | GSN_WDD_CONNECT_FLAG_ACTIVE_SCAN | GSN_WDD_CONNECT_FLAG_HIGHEST_RSSI_NW));
		}
		else if(s2wappMainTaskCtxt->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_AP)
		{
			conctflags = GSN_WDD_CONNECT_FLAG_NONE;
			pWlanConfig->apSpecificCfg.beaconInterval = s2wCurrent.lmtdApConf.beaconInterval;
			pWlanConfig->apSpecificCfg.hiddenSsid = s2wappMainTaskCtxt->bcastSsid;
			pWlanConfig->apSpecificCfg.dtimPeriod = s2wappMainTaskCtxt->dtimPeriod;
			s2wappMainTaskCtxt->if0.wddCtx.wlanConfigExtn.inactivityTimeoutInSec =s2wappMainTaskCtxt->inactivityTimeoutInSec;
			if( (GSN_MAC_AUTH_SHARED == s2wCurrent.security.authMode ) ||
				(GSN_MAC_AUTH_OPEN == s2wCurrent.security.authMode))
			{
				pWlanConfig->securityCfg.mode= GSN_WDD_SEC_MODE_WEP;
			}
        }
                
        /*AppS2wHal_MacAddrSet(s2wCurrent.macAddr);*/
		L2ConnectStatus = 0;
		pWlanConfig->securityCfg.eapConfig.outerAuthType = s2wCurrent.security.eap.outerAuth;
		pWlanConfig->securityCfg.eapConfig.innerAuthType = s2wCurrent.security.eap.innerAuth;
		memcpy(pWlanConfig->securityCfg.eapConfig.userName.Name, s2wCurrent.security.eap.usrName, s2wCurrent.security.eap.usrNameLen);
		pWlanConfig->securityCfg.eapConfig.userName.Length = s2wCurrent.security.eap.usrNameLen;
		memcpy(pWlanConfig->securityCfg.eapConfig.password.Pwd, s2wCurrent.security.eap.password, s2wCurrent.security.eap.passwordLen);
		pWlanConfig->securityCfg.eapConfig.password.Length = s2wCurrent.security.eap.passwordLen;

        if(s2wCurrent.eapCertTimeValidChkDisbl)
        {
	        pWlanConfig->securityCfg.eapConfig.eapFlags |= GSN_WPAIF_EAP_FLAG_NO_TIME_STAMP_CHECK;
        }
#if 1
		if( s2wCurrent.security.eap.useCaCert ||
			(( 13 == s2wCurrent.security.eap.outerAuth)&&
			( 26 == s2wCurrent.security.eap.innerAuth )))
		{
            index = S2wCert_SearchRamTable(S2W_CERT_NAME_CA);
            if(index == -1)
            {
                index = S2wCert_FlashFileLoad(S2W_CERT_NAME_CA);
            }
	    if(index != -1)
	    {
                pWlanConfig->securityCfg.eapConfig.pCaCert = (char*)s2w_ssl_cert_table[index].certAddress + 2;
                pWlanConfig->securityCfg.eapConfig.caCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
	    }
		}
        index = S2wCert_SearchRamTable(S2W_CERT_NAME_CLIENT);
        if(index == -1)
        {
            index = S2wCert_FlashFileLoad(S2W_CERT_NAME_CLIENT);
        }
	    if(index != -1)
	    {
	    	pWlanConfig->securityCfg.eapConfig.pClientCert  = (char*)s2w_ssl_cert_table[index].certAddress + 2;
            pWlanConfig->securityCfg.eapConfig.clientCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
	    }
        index = S2wCert_SearchRamTable(S2W_CERT_NAME_KEY);
        if(index == -1)
        {
            index = S2wCert_FlashFileLoad(S2W_CERT_NAME_KEY);
	    }
	    if(index != -1)
	    {
	        pWlanConfig->securityCfg.eapConfig.pPrivateKey = (char*)s2w_ssl_cert_table[index].certAddress + 2;
            pWlanConfig->securityCfg.eapConfig.privateKeyLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
	    }
#endif
TRY_AGAIN:
		/* start the timer*/
		s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
						   GSN_SOFT_TMR_ONESHOT,0,
							SEC_TO_SYSTIME(S2W_WLAN_RESPTIMEOUT),
						  ( GSN_SOFT_TMR_CBR_T )AppS2w_WlanRespTmrCb,NULL);

		/* Enable crypto */
		GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
		
        status = GsnWdd_Connect(&s2wappMainTaskCtxt->if0.wddCtx, conctflags, pWlanConfig, NULL,
                       s2wApp_ConnectCb, s2wappMainTaskCtxt);
        if (GSN_OPERATION_IN_PROGRESS != status)
        {
            s2wApp_ConnectCb( NULL,status);
        }
        else
        {
            status = GSN_SUCCESS;
        }

        /* wait on a semaphore to finish the asociation
         */
        GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
        
       AppS2w_ConctCbProcess(s2wappMainTaskCtxt, L2ConnectStatus);
       
       
       if(0 == eapFastRetryCnt && s2wLinkState == S2W_LINK_STATE_DISCONNECTED &&
            s2wCurrent.security.eap.outerAuth == GSN_EAP_TYPE_FAST)
       {
            eapFastRetryCnt++;
            goto TRY_AGAIN;
       }
       
       
        if(params.mode == 2)
        {
            current_wlan_info.mode = S2W_WLANDATA_MODE_AP;
	    }
	    else
	    {
	        GsnHeIf_DriverSuspend();
            current_wlan_info.mode = S2W_WLANDATA_MODE_INFRA;
		}
#ifdef S2W_IP2WIFI_SUPPORT  // ip2wifi
        if((status == GSN_SUCCESS) &&(L2ConnectStatus == GSN_SUCCESS ))  
        {
            return S2W_SUCCESS;
        }
        else
        {
            return S2W_FAILURE;
        }
        
#else // s2w 
        if((status == GSN_SUCCESS) && (TRUE == GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx)))

        {
            
            memset(&ipConfig,0,sizeof(ipConfig));
            GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
            ipConfig.flag =  GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
            
            ipConfig.ipv4.staticIp = !s2wCurrent.netConf.dhcp;
            if(ipConfig.ipv4.staticIp) // static ip
            {
                memcpy((UINT8*)&ipConfig.ipv4.ipAddr,s2wCurrent.netConf.ipAddr,4);
                memcpy((UINT8*)&ipConfig.ipv4.subnetMask, s2wCurrent.netConf.netMask, 4);
                memcpy((UINT8*)&ipConfig.ipv4.gatewayIpAddr,s2wCurrent.netConf.gateway,4);
                memcpy((UINT8*)&ipConfig.ipv4.dnsPriSrvrIp,s2wCurrent.dns1,4);
                memcpy((UINT8*)&ipConfig.ipv4.dnsSecSrvrIp,s2wCurrent.dns2,4);
                S2wL3Wait = TRUE;
            }
             if(strlen((const char *)s2wCurrent.hostName) != 0)
			 {
				 memcpy(ipConfig.ipv4.hostName, s2wCurrent.hostName,
					 (GSN_NWIF_HOST_NAME_MAX_LEN + 1));
			 }
			else
			{     
     			S2w_macAddrRTCGet(mac);
		      	sprintf((char*)macStr,"%s%2.2x%2.2x%2.2x","GS_",mac[3],mac[4],mac[5]);
			    memcpy(s2wCurrent.hostName,macStr,strlen((char*)macStr));
				memcpy(ipConfig.ipv4.hostName, s2wCurrent.hostName,
					 (GSN_NWIF_HOST_NAME_MAX_LEN + 1));
    		}
            s2wappMainTaskCtxt->if0.nwifCtx.notifyCb = DHCP_notify;
            memset(&dhcpParams,0,sizeof(dhcpParams));
            dhcpParams.dhcpMaxRetryCnt = S2W_DHCP_MAX_RETRY_COUNT;
            dhcpParams.radioMode = s2wCurrent.netConf.dhcpRadioMode;
            dhcpParams.requestLeaseTime = s2wCurrent.dhcpRequestLeaseTime;            
            dhcpParams.dhcpRetryTimeout = s2wCurrent.dhcpRetryTimeout;
              S2wL3Wait = TRUE;
           
            status = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, &dhcpParams);

             if((status != GSN_OPERATION_IN_PROGRESS) && !ipConfig.ipv4.staticIp)
                {
                    DHCP_notify(status,NULL);
                }
            if(ipConfig.ipv4.staticIp)
            {
                if(GSN_SUCCESS == status)
                {
                    L3ConnectStatus = TRUE;
            	}
            }
            else
            {
            	GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
            }
            
#ifdef S2W_IPv6_SUPPORT
            memset(&dhcpv6Params,0,sizeof(GSN_NWIF_DHCP_PARAMS_T));
            memset(&userIpv6Config,0,sizeof(GSN_NWIF_IPv6_CONFIG_T));
            S2w_getDhcpv6Clientconfig(&dhcpParams); 
            if(s2wCurrent.netConf.dhcpv6)
            {
            	userIpv6Config.flags = (GSN_NWIF_IP6_FLG_T)(GSN_NWIF_IP6_FLG_AUTO_LINK_LOCAL_ADDR | GSN_NWIF_IP6_FLG_DHCP_V6_CONFIG );
            }
            else
            {
              userIpv6Config.flags = (GSN_NWIF_IP6_FLG_T)GSN_NWIF_IP6_FLG_AUTO_LINK_LOCAL_ADDR;
            }
            S2wL3Wait = TRUE;
            status = GsnNwif_PrivateIPv6Config(&s2wappMainTaskCtxt->if0.nwifCtx, &userIpv6Config, &dhcpParams);
            if(status != GSN_OPERATION_IN_PROGRESS)
                {
                    DHCP_notify(status,NULL);
                }
            GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
#endif
            
            if(L3ConnectStatus)
            {
                AppS2wHdrAndIpv4_Print();
#ifdef S2W_IPv6_SUPPORT
                if(L3ConnectStatus_v6)
                AppS2wHdrAndIpv6_Print();
#endif                
			}

        }

	if((GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE) && (L3ConnectStatus==1))
        {
                S2wL3Wait = FALSE;
               if(ipConfig.ipv4.staticIp)
               {
                nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,GratiousArpHandler);
               }
                GsnNwif_DnsServerGet(&s2wappMainTaskCtxt->if0.nwifCtx,(ULONG*)s2wCurrent.dns1,GSN_PRIMARY_DNS_SERVER);
                GsnNwif_DnsServerGet(&s2wappMainTaskCtxt->if0.nwifCtx,(ULONG*)s2wCurrent.dns2,GSN_SECONDARY_DNS_SERVER);
 
		return S2W_SUCCESS;
        }
        else if((GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE) && (L3ConnectStatus==0))
        {
                GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
                S2wL3Wait = FALSE;
           // AppS2wProcess_DhcpFailNotify();
			return S2W_ENOIP;
        }
        else
        {
			// failure case so check the log level and depends on it print info
			//if(s2wappMainTaskCtxt->logLevel > 0)s2wCurrent.logLevel
        	if(s2wCurrent.logLevel > 0)
			{
				 UINT32 errorCode=0;
				 GSN_WDD_ERROR_T *logInfo = GsnWdd_ErrorGet(&s2wappMainTaskCtxt->if0.wddCtx);
                 if(logInfo->errorCode & GSN_WDD_CONNECT_ERROR_AP_NOT_FOUND)
                 {
                      errorCode = S2W_ERROR_CODE_AP_NOT_FOUND;
				 }
				 else if(logInfo->errorCode & GSN_WDD_CONNECT_ERROR_WLAN_FAIL_TO_CONCT)
				 {
					  errorCode = S2W_ERROR_CODE_WLAN_FAIL_TO_CONCT;
				 }
				 else if(logInfo->errorCode & GSN_WDD_CONNECT_ERROR_WPA_AUTH_FAILURE)
				 {
					  errorCode = S2W_ERROR_CODE_WPA_AUTH_FAILURE;
				 }
				 S2w_Printf(S2WError_List[errorCode]);
				 if(logInfo->reasonString != NULL)
				 {
					 S2w_Printf("\r\n");
                     S2w_Printf(logInfo->reasonString);
				 }

			}
          return S2W_FAILURE;
        }
//return S2W_SUCCESS;
#endif // ip2wifi
}
VOID DHCP_notify(INT32 status,void *ctx)
{
	if (GSN_SUCCESS == status)
	{
        L3ConnectStatus = TRUE;
#ifdef S2W_IPv6_SUPPORT
        L3Dhcpv6Status = TRUE;
         L3ConnectStatus_v6 = TRUE;
#endif       
         nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,GratiousArpHandler);
	}
	else if(GSN_NW_DHCP_LEASE_EXPIRED == status)
	{
		AppMainCtx_TaskNotify(APP_EVENT_DHCP_LEASETIME_EXPIRED);
		return;
	}

    else
    {
        L3ConnectStatus = FALSE;
#ifdef S2W_IPv6_SUPPORT
        /* Link local is present by default */
         L3ConnectStatus_v6 = TRUE;
#endif        
	}

    if(S2wL3Wait)
    {
        S2wL3Wait =0;
    	GsnOsal_SemRelease(&s2wL2L3ConnectSemaphore);
    }
    else // dgcp renew case
    {
        UINT32 message;
        if((L3ConnectStatus == FALSE) && (s2wLinkState != S2W_LINK_STATE_DISCONNECTED))
        {
            message = APP_EVENT_DHCP_RENEW_FAILURE;
            /* for auto connection (data pipe make the async gpio low-so that host will not send data)
             */
            if(s2wIsAutoconnected)
	        {
		        S2w_AsyncMsgGpioOp(0);
            }
            (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);

        }
        else if(s2wLinkState != S2W_LINK_STATE_DISCONNECTED)
        {
            // check the ip address got is same as previous one if not post a msg else do nothing
            GSN_NWIF_IP_CONFIG_T nwParams;
            /* get the ip address by calling the geps API
             */
            GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);

            if((s2wappMainTaskCtxt->ipaddr!=nwParams.ipv4.ipAddr) ||
               (s2wappMainTaskCtxt->subnetMask !=nwParams.ipv4.subnetMask))
            {
                // update the values first
                s2wappMainTaskCtxt->ipaddr = nwParams.ipv4.ipAddr;
                s2wappMainTaskCtxt->subnetMask = nwParams.ipv4.subnetMask;

                message = APP_EVENT_DHCP_RENEW_IP_CHANGED;
                /* for auto connection (data pipe make the async gpio low-so that host will not send data)
                 */
                if(s2wIsAutoconnected)
		        {
		            S2w_AsyncMsgGpioOp(0);
                }
                (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
            }
       }
    }
  // AppMainCtx_TaskNotify(APP_EVENT_DHCP_STOP_REQUEST);
#ifdef S2W_IPv6_SUPPORT
   AppMainCtx_TaskNotify(APP_EVENT_DHCPv6_STOP_REQUEST);
#endif
	return;

}


void s2wDhcpv6Stop()
{
  GsnNwIf_DhcpV6Stop(&s2wappMainTaskCtxt->if0.nwifCtx);
  
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the ATZ Command. ATZ command reads the profile
 *        from the flash.This function check the validity of the profile
 *        id and update the flash.
 * @param ptr Pointer to the user string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-flash write failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_read(UINT8 *ptr)
{
    UINT8 profileNum;
    UINT8 status;
    
    /* check the validity of parameter
     */
    status = AppS2wParse_Boolean(ptr, &profileNum);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
    status = S2w_LoadS2wProfile(&s2wCurrent,profileNum);
    
     if(status != S2W_SUCCESS)
        status = S2W_FAILURE;
      
      return status;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT&W Command. AT&W command writes the profile
 *        to the flash.This function check the validity of the profile
 *        id and update the flash.
 * @param ptr Pointer to the user string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-flash write failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Write(UINT8 *ptr)
{
    S2W_PROFILE_T *profile;
    //UINT32 whatChanged;
    UINT8 profileNum;
    UINT8 status;


    /* check the validity of parameter
     */
    status = AppS2wParse_Boolean(ptr, &profileNum);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    profile = &s2wFlashParams->profile[profileNum];
    memcpy(profile, &s2wCurrent, sizeof(S2W_PROFILE_T));
#ifdef S2W_NCM_SUPPORT_ENABLE
	if(profile->ncmAutoMgr)
	{
		profile->ncmAutoMgr = (s2wappMainTaskCtxt->ncmAutoConStoreProfile)?0:1;
	}
#endif
    /* call the hal function to update the flash
     */
    // if it is a warm boot check the file system is initialized else initialize it...
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
                f_enterFS();
	}
      status = S2w_SaveS2wProfile(s2wFlashParams, profileNum);
      if(status != S2W_SUCCESS)
        status = S2W_FAILURE;
      
      return status;
}

#ifndef S2W_IP2WIFI_SUPPORT
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NDHCP command
 *   This function validate the parameter passed and call the hal function
 *   to do ip configuration(DHCP or static ip).This function also updates the
 *   dhcp flag of the active profile.
 * @param ptr Pointer to the user input string.

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-ip config failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Ndhcp(UINT8 *ptr)
{
    UINT8 status;
    UINT8 mode, *p, len,mac[6],macStr[GSN_NWIF_HOST_NAME_MAX_LEN + 1];
    UINT32 radioMode;

    /* check the validity of parameter passed     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(mode == 0)
    {
      GsnNwIf_DhcpStop(&s2wappMainTaskCtxt->if0.nwifCtx);
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if(p && (0 != strlen((const char *)p)))
    {
        len = strlen((const char *)p);
        if(len > GSN_NWIF_HOST_NAME_MAX_LEN)
        {
            return S2W_FAILURE;
        }
        memcpy(s2wCurrent.hostName, p, (len + 1));
    }
     else
    {
      //S2w_LoadMacAddr(mac);
      S2w_macAddrRTCGet(mac);
      sprintf((char*)macStr,"%s%2.2x%2.2x%2.2x","GS_",mac[3],mac[4],mac[5]);
      memcpy(s2wCurrent.hostName,macStr,strlen((char*)macStr));
    }
    
    p = AppS2wParse_NextParamGet(&ptr);
    s2wCurrent.netConf.dhcpRadioMode = 0;/* Default mode - PS POLL*/
    if(p && (0 != strlen((const char *)p)))
    {
        
        status = AppS2wParse_Int(p, &radioMode);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        if(radioMode >= 4)
        {
            return S2W_EINVAL;
        }
        s2wCurrent.netConf.dhcpRadioMode = (UINT8)radioMode;
    } 
    p = AppS2wParse_NextParamGet(&ptr);
    if(p && (0 != strlen((const char *)p)))
    {
        UINT32 leaseTime = 0;
        status = AppS2wParse_Int(p, &leaseTime);
        if (status != S2W_SUCCESS)
        {
            s2wCurrent.dhcpRequestLeaseTime = 0;
            return status;
        }
        s2wCurrent.dhcpRequestLeaseTime = leaseTime;
    }    
    p = AppS2wParse_NextParamGet(&ptr);
    if(p && (0 != strlen((const char *)p)))
    {
        UINT32 retransInterval = 0;
        status = AppS2wParse_Int(p, &retransInterval);
        if (status != S2W_SUCCESS)
        {
            s2wCurrent.dhcpRequestLeaseTime = 0;
            return status;
        }
        s2wCurrent.dhcpRetryTimeout = retransInterval;
    }
    /* update the active profile
     */
    s2wCurrent.netConf.dhcp = mode;

	status = AppS2wHal_NetworkConfig(&s2wCurrent.netConf);
         GsnNwif_DnsServerGet(&s2wappMainTaskCtxt->if0.nwifCtx,(ULONG*)s2wCurrent.dns1,GSN_PRIMARY_DNS_SERVER);
         GsnNwif_DnsServerGet(&s2wappMainTaskCtxt->if0.nwifCtx,(ULONG*)s2wCurrent.dns2,GSN_SECONDARY_DNS_SERVER);
      if((status == S2W_SUCCESS) && (mode == 0))
      {
         nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,GratiousArpHandler);
      }
    
 
    //return status;

		
#if 0
    if (!L3ConnectStatus && (mode == 1))
    {
        s2wCurrent.netConf.dhcp = oldDhcp;
        S2wL3Wait = FALSE;
        GsnNwIf_DhcpStop(&s2wappMainTaskCtxt->if0.nwifCtx);
        //GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
        L3ConnectStatus = L3OldStatus;
        retVal = GsnNwif_IPv4Configure(&s2wappMainTaskCtxt->if0.nwifCtx,&DefaultConfig,NULL);
        return S2W_FAILURE;
    }
#endif
    S2wL3Wait = FALSE;
    return status;
}

#endif


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NSET command parameters.
 *   This function check the validty if input parameters(ip addres,
 *   subnet mask,gateway) and call the hal ip config function to configure
 *   the static IP.
 * @param ptr pointer to the char string which holds the arguments.

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-Ip config failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Nset(UINT8 *ptr)
{
    UINT8 *p;
    UINT8 status;
    GSN_STATUS  retval;
    GSN_NWIF_IPv4_CONFIG_T UsrIPv4Cfg;
    S2W_IPADDR_T ipAddr;
    S2W_IPADDR_T subNetmask;
    GSN_NWIF_IP_CONFIG_T ipConfig;
    
    memset(&UsrIPv4Cfg,0,sizeof(GSN_NWIF_IPv4_CONFIG_T));
   
    UsrIPv4Cfg.staticIp = 1;
    
     if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Ip(p,ipAddr);
      
	if (status != S2W_SUCCESS)
	{
          return status;
	}

        UsrIPv4Cfg.ipAddr = (ipAddr[0] << 24 | ipAddr[1] << 16 | ipAddr[2] << 8 | ipAddr[3] );
        
  }
  else
    return S2W_EINVAL;

   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    
    status = AppS2wParse_Ip(p,subNetmask);
	if (status != S2W_SUCCESS)
	{
          return status;
	}
    
         UsrIPv4Cfg.subnetMask = (subNetmask[0] << 24 | subNetmask[1] << 16 | subNetmask[2] << 8 | subNetmask[3] );

  }
    else
    return S2W_EINVAL;
  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    
        status = AppS2wParse_Ip(p,ipAddr);

	if (status != S2W_SUCCESS)
	{
          return status;
	}
        
        UsrIPv4Cfg.gatewayIpAddr = (ipAddr[0] << 24 | ipAddr[1] << 16 | ipAddr[2] << 8 | ipAddr[3] );
  }
  else
    return S2W_EINVAL;
  
      /* Check for valid IP address */
    if(((UsrIPv4Cfg.ipAddr & 0xFFFFFF00) == 0xFFFFFF00) || (UsrIPv4Cfg.ipAddr == 0x00000000))
    {
        return S2W_EINVAL;
    }
    
      /*check for valid broadcast address */
    if(((UsrIPv4Cfg.subnetMask & 0xFF000000) != 0xFF000000) || (UsrIPv4Cfg.subnetMask == 0x00000000))
        return S2W_EINVAL;

    /*  check for valid gateway Address  */
    if(((UsrIPv4Cfg.gatewayIpAddr & 0xFFFFFF00) == 0xFFFFFF00 ) || (UsrIPv4Cfg.gatewayIpAddr == 0x00000000))
        return S2W_EINVAL;

    
    ipConfig.flag =  GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
    /* call GSN ip config function to configure the static IP
     */
      ipConfig.ipv4 = UsrIPv4Cfg;
      retval = GsnNwif_IPv4Configure(&s2wappMainTaskCtxt->if0.nwifCtx, &UsrIPv4Cfg, NULL);
      if(GSN_NW_IF_CLOSED == retval)
      {
          retval = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, NULL);
      }	
      if(retval != GSN_SUCCESS )
	    return S2W_FAILURE;
     
	if(s2wappMainTaskCtxt->apConf)// if Ap conf enabled then store in Ap conf
	{
		UINT32 ipaddr=0;
		memcpy((UINT8*)&s2wCurrent.lmtdApConf.ipAddress,&UsrIPv4Cfg.ipAddr,4);
		memcpy((UINT8*)&s2wCurrent.lmtdApConf.subnetmask,&UsrIPv4Cfg.subnetMask,4);
		memcpy((UINT8*)&s2wCurrent.lmtdApConf.gateway,&UsrIPv4Cfg.gatewayIpAddr,4);
		ipaddr = htonl(s2wCurrent.lmtdApConf.ipAddress) + 1;
		s2wCurrent.lmtdApConf.dhcpAddressStart = ntohl(ipaddr);//s2wCurrent.lmtdApConf.ipAddress + 1;
	}
	else
	{
       /* update the active profile paramater  */

        s2wCurrent.netConf.dhcp = 0;
        
        memcpy(&s2wCurrent.netConf.ipAddr,&UsrIPv4Cfg.ipAddr,4);
        memcpy(&s2wCurrent.netConf.netMask,&UsrIPv4Cfg.subnetMask,4);
        memcpy(&s2wCurrent.netConf.gateway,&UsrIPv4Cfg.gatewayIpAddr,4);
		if(s2wCurrent.mode == S2W_WLANDATA_MODE_AP)
		{
			memset(&s2wCurrent.dns1,0,sizeof(S2W_IPADDR_T));
			memset(&s2wCurrent.dns2,0,sizeof(S2W_IPADDR_T));
		}
    
	}   
        if(s2wLinkState != S2W_LINK_STATE_DISCONNECTED)
        {
          L3ConnectStatus = TRUE;
          AppS2wHdrAndIpv4_Print();
        }
      return S2W_SUCCESS;

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NMAC command
 *   This function check the validity of the mac address passed and
 *   call the hal function to configure the mac address.
 *   This function returns the mac address configured if the parameter
 *   is '?'.
 * @param ptr pointer to the char string which holds the arguments.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-MAC configuration failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Nmac(UINT8 *ptr)
{
    UINT8 macAddr[S2W_MAC_ADDR_SIZE];
    UINT8 status;

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        /* get the mac address and send it on serial interface
         */
        if(s2wCurrent.mode == S2W_WLANDATA_MODE_INFRA)
        {
          //status = S2w_LoadMacAddr(macAddr);
          S2w_macAddrRTCGet(macAddr);

		}
		else
		{
			memcpy(macAddr,s2wCurrent.lmtdApConf.macAddr.array, 6);
		}

        S2w_Printf("\r\n%02x:%02x:%02x:%02x:%02x:%02x",
                macAddr[0], macAddr[1],
                macAddr[2], macAddr[3],
                macAddr[4], macAddr[5]);

         return S2W_SUCCESS;
    }

    /* check the mac address passed is valid
     */
    status = AppS2wParse_Mac(ptr, macAddr);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* Call the hal function to configure the mac address
     */
    status = AppS2wHal_MacAddrSet(macAddr, TRUE);
    if (status != S2W_SUCCESS)
    {
        return S2W_FAILURE;
    }
    // depends on the mode configured store to the sta/ap mac
    if(s2wCurrent.mode == S2W_WLANDATA_MODE_INFRA)
    {
        if(!s2wappMainTaskCtxt->fsInit)
        {
           App_FsInit();
           s2wappMainTaskCtxt->fsInit = TRUE;
           f_enterFS();
        }
  S2w_SaveMacAddr(macAddr);
        S2w_macAddrRTCSet(macAddr); // set in the rtc also
	}
	else
	{
        if(!s2wappMainTaskCtxt->fsInit)
        {
           App_FsInit();
           s2wappMainTaskCtxt->fsInit = TRUE;
           f_enterFS();
        }
		 S2w_SaveApMacAddr(macAddr);
		 memcpy(s2wCurrent.lmtdApConf.macAddr.array, macAddr,6);
	}
      
    /* after mac configuration disassociate in case of station mode
     */
    if(s2wCurrent.mode == S2W_WLANDATA_MODE_INFRA)
	{
    AppS2w_HangUp();
	}
    return S2W_SUCCESS;
}




#ifdef S2W_UART_ENABLE
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the ATB Command.
 *   This function validate the parameter passed and call the hal uart
 *   configuration function to configure the uart with the valid parameters
 *   passed.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-uart configuration failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_BaudRate(UINT8 *ptr)
{

    S2W_SERIAL_PORT_CONF_T params;
    UINT32 temp;
    UINT8 status;
    UINT8 *p;


    memcpy(&params, &s2wCurrent.serialPortConf, sizeof(params));

    /* Get the first parameter- baud rate
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    /* validate the baude rate
     */
    status = AppS2wParse_Int(p, &temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if (!temp)
    {
        return S2W_EINVAL;
    }

    params.conf.uart.baudrate= temp;

    /* get the 2nd parameter-bits per char
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (p && *p)
    {
        status = AppS2wParse_Int(p, &temp);
        if (status != S2W_SUCCESS)
        {
            return status;
        }

#if (S2W_UARTCONF_BITS_5 != 0) || (S2W_UARTCONF_BITS_8 != 3)
#error Fix bits macros
#endif

        if (temp < 5 || temp > 8)
        {
            return S2W_EINVAL;
        }

        params.conf.uart.bits = temp - 5;
    }

    /* get the 3rd parameter-parity
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (p && *p)
    {
        if (p[1] != '\0')
        {
            return S2W_EINVAL;
        }

        switch (toupper(*p))
        {
            case 'N':
            params.conf.uart.parity= S2W_UARTCONF_PARITY_NONE;
            break;

            case 'O':
            params.conf.uart.parity = S2W_UARTCONF_PARITY_ODD;
            break;

            case 'E':
            params.conf.uart.parity = S2W_UARTCONF_PARITY_EVEN;
            break;

            default:
            return S2W_EINVAL;
        }
    }

    /* get the 4th parameter- stop bits
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (p && *p)
    {
        status = AppS2wParse_Int(p, &temp);
        if (status != S2W_SUCCESS)
        {
            return status;
        }

        if (temp != 1 && temp != 2)
        {
            return S2W_EINVAL;
        }

        params.conf.uart.stop = temp == 1 ?
                  S2W_UARTCONF_STOP_1 : S2W_UARTCONF_STOP_2;
    }

    /* call the hal uart configuration function
     */
    status = AppS2wHal_UartConfig(&params);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* update the current active profile
     */
    memcpy(&s2wCurrent.serialPortConf, &params, sizeof(s2wCurrent.serialPortConf));

    return S2W_SUCCESS;

}



PRIVATE UINT8
AppS2wCmd_UartFifoLevel(UINT8 *ptr)
{
    UINT32 txLevel=0,rxLevel=0;
    UINT8 status;
    UINT8 *p;
    if((ptr[0] =='?') &&(ptr[1] =='\0'))
    {
        S2w_Printf("\r\nRXLEVEL=%02x,TXLEVEL=%02x\r\n",GsnUart_IntrFifoRxLevelGet(&s2wSerialPortHandle.uartHandle),
                   GsnUart_IntrFifoTxLevelGet(&s2wSerialPortHandle.uartHandle));
    }
    else
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Int(p, &rxLevel);
        if ((status != S2W_SUCCESS) || (rxLevel < 1) || (rxLevel > 15))
        {
            return S2W_EINVAL;
        }
        GsnUart_IntrFifoRxLevelSet(&s2wSerialPortHandle.uartHandle,(GSN_UART_IFL_T)rxLevel);
        p = AppS2wParse_NextParamGet(&ptr);
        if (p && *p)
        {
            status = AppS2wParse_Int(p, &txLevel);
            if ((status != S2W_SUCCESS) || (txLevel > 15))
            {
                return S2W_EINVAL;
            }
            GsnUart_IntrFifoTxLevelSet(&s2wSerialPortHandle.uartHandle,(GSN_UART_IFL_T)txLevel);
		}
    }
    return S2W_SUCCESS;
}
#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT&Y Command. AT&Y configures the power on
 *        profile identifier.This function calls the hal flash write API
          to update the parameter.
 * @param ptr Pointer to the user string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure- profile setting failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_SetDefaultProfile(UINT8 *ptr)
{
    UINT8 profile;
    UINT8 status;
    /* validate the input parameter as a vlaid identifier
     */
    status = AppS2wParse_Boolean(ptr, &profile);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    profile_params.defaultProfile = profile;
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
                f_enterFS();
	}
    return S2w_SaveS2wProfileParams(&profile_params);
}




/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the ATH Command.
     This function call the hal function function to disconnect the network
     association.
 * @param ptr Pointer to the user string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure- disconnect failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Disconnect(UINT8 *ptr)
{
    if (*ptr)
    {
        return S2W_EINVAL;
    }
    
    return AppS2w_HangUp();
}


UINT8
AppS2wCmd_AssocPSModeSet( UINT8* ptr)
{
    UINT32 temp;
    UINT8 status;
    UINT8 *p;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    return S2W_SUCCESS;
/*
    if( temp <= GSN_WDD_ASSOC_PS_MODE_RX_PS_POLL_CONSERVE )
    {
       GsnWdd_Ioctl( &s2wappMainTaskCtxt->wdd,
       GSN_L2DEV_IOCTL_PS_MODE_RX_STATE_SET, &temp );
       return S2W_SUCCESS;
   }
   else
   {
       return S2W_EINVAL;
   }
*/
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT&F Command. AT&F command restores the configuration
 *        to the factory settings.
 * @param ptr Pointer to the user input string.

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Factory(UINT8 *ptr)
{

    if (*ptr)
    {
        return S2W_EINVAL;
    }

    /* get the default profile stored in flash
     */
    AppS2wProcess_DefaulConfigtLoad(s2wFlashParams);

    /* Load the profile values to the current active profile
     */
    S2W_PROFILE_T *profile = &s2wFlashParams->profile[profile_params.defaultProfile];

    s2wIsAutoconnected = 0;

    /* close all cids
     */
    AppS2wHal_NetCloseAll(0);
    memcpy(&s2wCurrent, profile, sizeof(s2wCurrent));

    /* configure the ip parameters
     */
    AppS2w_SetWlanDfltParams(profile_params.defaultProfile);
    AppS2wHal_NetworkConfig(&s2wCurrent.netConf);

    return S2W_SUCCESS;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WRXACTIVE Command.
     This function validate the input parameter as enable or disable
     and call the hal function to switch ON/OF the active radio.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure- radio configuration failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Wradio(UINT8 *ptr)
{
    UINT8   status;
    UINT8   mode;

    /* validate the parameter as enable/disable
     */
    status = AppS2wParse_Boolean(ptr, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* call the hal function to switch ON/OFF radio
     */
    status = AppS2wHal_RadioModeConfig(mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* update the active profile parameter
     */
    s2wCurrent.radio = mode;
    return status;
}



#ifndef S2W_IP2WIFI_SUPPORT

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NSTAT command.
 *   This function display the current network status information.
 *   It displays the connection status,ip address,AP information,
 *   RSSI,DNS address etc
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Nstat(UINT8 *ptr)
{
    S2W_STATUS_INFO_T statusInfo;
    const char *security = "NONE";
    GSN_WIF_WLAN_RSSI_T    wRssi;

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        memset(&statusInfo,0,sizeof(S2W_STATUS_INFO_T));
        statusInfo.wlanInfo.mode = current_wlan_info.mode;
        AppS2wHal_MacAddrGet(statusInfo.macAddr);
        statusInfo.wstate = s2wLinkState;

        statusInfo.wstate = GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx);
        
        /* display mac address,network connection status and mode */
        
        S2w_Printf("\nMAC=%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                    statusInfo.macAddr[0],statusInfo.macAddr[1],
                    statusInfo.macAddr[2],statusInfo.macAddr[3],
                    statusInfo.macAddr[4],statusInfo.macAddr[5]);
        statusInfo.wstate?(S2w_Printf("WSTATE=CONNECTED   ")):
                          (S2w_Printf("WSTATE=NOT CONNECTED  "));

        if(statusInfo.wstate == 0)
        {
            S2w_Printf("  MODE=NONE \r\n");

        }
        else
        {
            if(s2wappMainTaskCtxt->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_IBSS)
            {
              S2w_Printf("  MODE=IBSS \r\n");
			}
            else if(s2wappMainTaskCtxt->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_AP)
            {
               S2w_Printf("  MODE=AP \r\n");
        }
		    else
		    {
				S2w_Printf("  MODE=STA \r\n");
			}
        }

        
        if(statusInfo.wstate)
        {
          GSN_WDD_WLAN_CFG_T *WddConf;
		  GSN_WLAN_MAC_ADDR_T *pBssid;
		  GSN_WLAN_MAC_ADDR_T bssid;

            WddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
			pBssid = &WddConf->bssid;
			if(GSN_WIF_WLAN_NW_TYPE_AP == s2wappMainTaskCtxt->if0.wddCtx.wlanNwType)
			{					
				GsnWdd_PhyAddrGet(&s2wappMainTaskCtxt->if0.wddCtx,(INT8 *)&bssid);
				pBssid = &bssid;
			}
			
			S2w_Printf("BSSID=%02x:%02x:%02x:%02x:%02x:%02x   SSID=\"",
			pBssid->array[0], pBssid->array[1],
			pBssid->array[2],pBssid->array[3],
			pBssid->array[4],pBssid->array[5]);
          
           AppS2wHal_CharNPut(WddConf->ssid.array,(WddConf->ssid.length));
           S2w_Printf("\"");

        if( WddConf->channel[0] == 0)
        {
            S2w_Printf(" CHANNEL=NONE  ");
        }
        else
        {
            S2w_Printf(" CHANNEL=%d  ", WddConf->channel[0]);
        }
        AppS2wCmd_GetSecurityString(WddConf, &security);

        GsnWdd_RSSIGet(&s2wappMainTaskCtxt->if0.wddCtx, (INT8*)&wRssi, sizeof(GSN_WIF_WLAN_RSSI_T));
        S2w_Printf(" SECURITY=%s\r\nRSSI=%d\r\n", security, (signed char)wRssi.rssi);
          
        }
        /* display bssid,ssid,channel
         */
        else
        {
            S2w_Printf("BSSID=00:00:00:00:00:00   SSID=\"");

        S2w_Printf("\"");

            S2w_Printf(" CHANNEL=NONE  ");
        /* display security information
         */

            security ="NONE";
        S2w_Printf(" SECURITY=%s\r\nRSSI=%d\r\n", security,(signed char) statusInfo.rssi);
        }
        /* display ip address,subnet,gateway  */

        if(statusInfo.wstate)
           GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&statusInfo.nwParams);
         
        S2w_Printf("IP addr=%d.%d.%d.%d   SubNet=%d.%d.%d.%d ",(statusInfo.nwParams.ipv4.ipAddr& 0xff000000)>>24,(statusInfo.nwParams.ipv4.ipAddr& 0x00ff0000)>>16,(statusInfo.nwParams.ipv4.ipAddr & 0x0000ff00)>>8,
                    (statusInfo.nwParams.ipv4.ipAddr& 0x000000ff),
                    (statusInfo.nwParams.ipv4.subnetMask& 0xff000000)>>24,(statusInfo.nwParams.ipv4.subnetMask& 0x00ff0000)>>16,(statusInfo.nwParams.ipv4.subnetMask & 0x0000ff00)>>8,
                    (statusInfo.nwParams.ipv4.subnetMask& 0x000000ff));
        S2w_Printf(" Gateway=%d.%d.%d.%d\r\n",(statusInfo.nwParams.ipv4.gatewayIpAddr& 0xff000000)>>24,(statusInfo.nwParams.ipv4.gatewayIpAddr& 0x00ff0000)>>16,(statusInfo.nwParams.ipv4.gatewayIpAddr & 0x0000ff00)>>8,
                    (statusInfo.nwParams.ipv4.gatewayIpAddr& 0x000000ff));
                
          /* display Dns1, Dns2 address,Rx and Tx counts  */
        S2w_Printf("DNS1=%d.%d.%d.%d       DNS2=%d.%d.%d.%d\r\nRx Count=%d     Tx Count=%d \r\n",
                    (statusInfo.nwParams.ipv4.dnsPriSrvrIp& 0xff000000)>>24,(statusInfo.nwParams.ipv4.dnsPriSrvrIp& 0x00ff0000)>>16,(statusInfo.nwParams.ipv4.dnsPriSrvrIp & 0x0000ff00)>>8,
                    (statusInfo.nwParams.ipv4.dnsPriSrvrIp& 0x000000ff),(statusInfo.nwParams.ipv4.dnsSecSrvrIp& 0xff000000)>>24,
                    (statusInfo.nwParams.ipv4.dnsSecSrvrIp& 0x00ff0000)>>16, (statusInfo.nwParams.ipv4.dnsSecSrvrIp& 0x0000ff00)>>8,(statusInfo.nwParams.ipv4.dnsSecSrvrIp& 0x000000ff),
                    s2wappMainTaskCtxt->if0.nwifCtx.pStats->totalPktsRcvd,
                    (s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipUnicastPktsSent + s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipBroadCastPktsSent + \
					 s2wappMainTaskCtxt->if0.nwifCtx.pStats->arpRequestSent + s2wappMainTaskCtxt->if0.nwifCtx.pStats->arpResponseSent));
#ifdef S2W_IPv6_SUPPORT
            AppS2wHdrAndIpv6_Print();
#endif  // S2W_IPv6_SUPPORT
        return S2W_SUCCESS;        

    }

    return S2W_EINVAL;
}
#endif



#ifdef S2W_UART_ENABLE
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT&R Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_HardFlow(UINT8 *ptr)
{
    UINT8 enable;
    UINT8 status;
    UINT8 oldflow;

    status = AppS2wParse_Boolean(ptr, &enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    oldflow = s2wCurrent.serialPortConf.conf.uart.hardflow;
    s2wCurrent.serialPortConf.conf.uart.hardflow = !!enable;

    if(s2wCurrent.serialPortConf.conf.uart.hardflow)
    {
        GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AUART0_CTS_N);
        GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AUART0_RTS_N);
        GsnIoMux_PullDownDisable(25);		// uart rts. These together consume 125uA
        //GsnIoMux_PullDownDisable(24);      // CTS
    }
    else
    {
        if(oldflow == GSN_UART_HW_SUPPORT)
        {
            GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AGPIO_24);
            GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AGPIO_25);
            GsnIoMux_PullDownEnable(25);
        }
    }

    status = AppS2wHal_UartConfig(&s2wCurrent.serialPortConf);

    if (status != S2W_SUCCESS)
    {
        if((s2wCurrent.serialPortConf.conf.uart.hardflow == GSN_UART_HW_SUPPORT) && (oldflow == GSN_UART_HW_NO_SUPPORT))
        {
            GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AGPIO_24);
            GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AGPIO_25);
            GsnIoMux_PullDownEnable(25);
        }
        else if((s2wCurrent.serialPortConf.conf.uart.hardflow == GSN_UART_HW_NO_SUPPORT) && (oldflow == GSN_UART_HW_SUPPORT))
        {
            GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AUART0_CTS_N);
            GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AUART0_RTS_N);
            GsnIoMux_PullDownDisable(25);
        }
        s2wCurrent.serialPortConf.conf.uart.hardflow = oldflow;
    }

    return status;


}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT&K Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_SoftFlow(UINT8 *ptr)
{

    UINT8 enable;
    UINT8 status = S2W_SUCCESS;

    status = AppS2wParse_Boolean(ptr, &enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

   s2wCurrent.serialPortConf.conf.uart.softflow = !!enable;
   GsnUart_SwFlowSupportSet(&s2wSerialPortHandle.uartHandle,(GSN_UART_SWFLOW_T)enable);
   return status;


}



#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the ATVn Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Verbose(UINT8 *ptr)
{
    return AppS2wParse_Boolean(ptr, &(s2wCurrent.serialPortConf.commonConf.verbose));
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the ATEn Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Echo(UINT8 *ptr)
{
   return AppS2wParse_Boolean(ptr,&(s2wCurrent.serialPortConf.commonConf.echo));
}





/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Hex print function
 *   This function print the value in hex  passed.
 * @param data - IN  Pointer to the data
 * @param len - IN the length of the data .
 *
 * @return none.
 ******************************************************************/

PUBLIC VOID
AppS2wHex_Print(UINT8 *data, UINT32 len)
{
    static const char hex_asc[] = "0123456789abcdef";
    UINT32 i;

    for (i = 0; i < len; i++)
    {
        S2w_PutChar(hex_asc[(data[i] & 0xf0) >> 4]);
        S2w_PutChar(hex_asc[(data[i] & 0x0f)]);
    }

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+VER command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
App2wCmd_Version(UINT8* ptr)
{
    UINT32 wlanVer=0;
    ULONG64 featurebmap = 0;
    UINT8 status = S2W_EINVAL;
	UINT32 pltVersion;

    if (ptr[0] == '?' && ( ptr[1] == '\0') || (ptr[1] == '?'))
    {
        pltVersion = GsnVersion_Get();
        status = GsnSysCtl_WlanFwVerGet(&s2wappMainTaskCtxt->sysCtlCtx,&wlanVer);

        status = GsnSysCtl_WlanFeatureBmapGet(&s2wappMainTaskCtxt->sysCtlCtx,&featurebmap);

#ifndef S2W_IP2WIFI_SUPPORT
        S2w_Printf("\r\nS2W APP VERSION=%s\r\nS2W GEPS VERSION=%d.%d.%d",
                    S2W_SW_VERSION,(pltVersion >>24),
               ((pltVersion >>16) & 0xff),((pltVersion>>8) & 0xff));

        S2w_Printf("\r\nS2W WLAN VERSION=%d.%d.%d\r\n",((wlanVer >> 24) & 0xff),
                     ((wlanVer >>16) & 0xff),((wlanVer>> 8 ) & 0xff));
#else
        S2w_Printf("\r\nIP2WIFI APP VERSION=%s\r\nIP2WIFI GEPS VERSION=%d.%d.%d",
                    S2W_SW_VERSION,(pltVersion >>24),
                    ((pltVersion >>16) & 0xff),((pltVersion>>8) & 0xff));

        S2w_Printf("\r\nIP2WIFI WLAN VERSION=%d.%d.%d\r\n",((wlanVer >> 24) & 0xff),
                     ((wlanVer >>16) & 0xff),((wlanVer>> 8 ) & 0xff));
        status = S2W_SUCCESS;
#endif
    }

    if((ptr[0] == '?') && (ptr[1] == '?') && (ptr[2] == '\0'))
    {
#ifndef S2W_IP2WIFI_SUPPORT
        S2w_Printf("S2W BIN TYPE=%s\r\nS2W RELEASE TYPE=%s\r\n",
                   S2W_BIN_TYPE,S2W_RELEASE_TYPE);
#else
        S2w_Printf("IP2WIFI BIN TYPE=%s\r\nIP2WIFI RELEASE TYPE=%s\r\n",
                   S2W_BIN_TYPE,S2W_RELEASE_TYPE);
#endif
        S2w_Printf("BUILD TIME=%s\r\n",__TIME__);
        S2w_Printf("BUILD DATE=%s\r\n",__DATE__);
        S2w_Printf("WLAN EXT VERSION=%d\r\n",((wlanVer) & 0xff));

#ifndef S2W_IP2WIFI_SUPPORT
        S2w_Printf("S2W APP EXT VERSION=%s\r\n",S2W_SW_EXT_VERSION);
#else
        S2w_Printf("IP2WIFI APP EXT VERSION=%s\r\n",S2W_SW_EXT_VERSION);
#endif
        S2w_Printf("WLAN FEAT BMAP=%016llx\r\n",featurebmap);
        S2w_Printf("GEPS EXT VERSION=%d\r\n",(pltVersion&0xff));
        // get the flash connected details
        {
			UINT32 flashId = 0;
			UINT8* des=NULL;
			/* request PIO control */
            GsnFlashIf_PioReq();
            flashId = GsnFlashIf_FlashIdRead() & 0xFFFF;
            if(flashId ==0x0000)
            {
				S2w_Printf("No Flash");
			}
			else
			{
				S2w_Printf("FLASH ID=0x%08x",flashId);
				switch(flashId)
				{
					case 0x20c2:
					   des = "MICRONIX-4MB";
					break;
					case 0x24c2:
					   des = "MICRONIX-2MB";
					break;
					case 0x25c2:
					   des = "MICRONIX-4MB";
					break;
					case 0x60c8:
					   des = "GIGA-4MB";
					break;
					case 0x40c8:
					   des = "GIGA-2MB";
					break;
					case 0x151c:
					   des = "EON-2MB";
					break;
					case 0x301c:
					   des = "EON-4MB";
					break;
					default:
					   des = "UNKNOWN";
					break;

				}
				S2w_Printf(":%s",des);
			}
			/* release PIO control */
			GsnFlashIf_PioRelease();


		}
	}
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+RESET command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/

UINT8
AppS2wCmd_reset(UINT8* ptr)
{
	// make sure spi-Dma gpio goes low
	if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
	{
	    GsnGpio_OutClear(s2wSerialPortHandle.spiFsHandle.spi.spiGpioBitMap);
	}
    GsnSys_Reset(GSN_RESET_REASON_APP_ASSERT);
    return S2W_SUCCESS;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+apconf command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_ApConf(UINT8* ptr)
{
    UINT8 status;
    BOOL init=0;
    status = AppS2wParse_Boolean(ptr, &init);
    if (status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }
    s2wappMainTaskCtxt->apConf = init;
    return S2W_SUCCESS;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WSYNCINTRL command
 * This function validate the input parameter passed and set the
 * syncloss interval as the value passed. The paramter value in number
 * beacons.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
S2w_CmdSyncLossIntrvlSet(UINT8 *ptr)
{
    UINT32 interval;
    UINT8 status = S2W_EINVAL;

    status = AppS2wParse_Int(ptr, &interval);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if((interval < 1) || (interval > 65535))
    {
        return S2W_EINVAL;
    }
    status = AppS2wHal_SyncLossIntrvlSet(interval);

    return status;
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NCLOSEALL Command.
 *   This function call the hal function to close all the tcp/udp socket
 *   opened.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_FAILURE - operation failure.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Ncloseall(UINT8 *ptr)
{
    /* call the hal function which close all the tcp/udp sockets
     */
    if (*ptr)
        return S2W_EINVAL;
    else
        return AppS2wHal_NetCloseAll(0);
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NCLOSE Command.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-socket close failed.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Nclose(UINT8 *ptr)
{
    UINT8 status;
    UINT32 cid;

    /* parse the parameter-cid
     */
    status = AppS2wParse_Hex(ptr, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    /* call the hal function to close a particular cid created
     */
    return AppS2wHal_NetClose(cid);
}

VOID
AppS2wSecurity_Display(S2W_SECURITY_T *sec)
{
    INT32 i;

    S2w_Printf("+WAUTH=%d +WWPA=\"%s\"", sec->authMode,
           sec->wpa.wpaPassPhrase);
    S2w_Printf("+PSK-valid=%d +SSID=%s",sec->wpa.pskValid,sec->wpa.ssid);
    for (i = 0; i < 4; i++)
    {
        S2w_Printf("%s+WWEP%d=", !(i & 1) ? "\r\n" : " ", i + 1);
        AppS2wHex_Print(sec->wep.key[i], sec->wep.keyLen[i]);
    }

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Ip address print function
 *   This function display Ip address passed.
 * @param ip - IN ptr Pointer to the user input ip string.
 *
 * @return none.
 ******************************************************************/
PUBLIC VOID
AppS2wIp_Print(S2W_IPADDR_T ip)
{
    S2w_Printf("%d.%d.%d.%d", ip[3], ip[2], ip[1], ip[0]);
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief profile display function.
 *   This function dispaly active and stored profile parameters.
 * @param profile of the profile to display

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC VOID
AppS2wProfile_Display(S2W_PROFILE_T *profile)
{
#ifndef S2W_IP2WIFI_SUPPORT
    UINT8 vBuff[4]={"\","};
#endif
#ifdef S2W_UART_ENABLE
    INT8 c;
#endif
    if (profile == &s2wCurrent)
    {
        /* C and Y are common settings */
        S2w_Printf("C%d " "&Y%d ",
                profile_params.autoConnect,
                profile_params.defaultProfile);
    }

#if  0  //GSN_FS_SPI_ENABLE
if(APP_S2W_GET_SERIAL_DEVICE_ID())
{//S2W_PORT_SPI

/* Dispaly SPI configurations
    */
   S2w_Printf("E%d V%d",
         profile->serialPortConf.commonConf.echo,
         profile->serialPortConf.commonConf.verbose);

   S2w_Printf(" &K%d CPL%d CPH%d\r\n",
         profile->serialPortConf.conf.spi.flowCtrl,
         profile->serialPortConf.conf.spi.clockPolarity,
         profile->serialPortConf.conf.spi.clockPhase);

}else
#endif
{

#ifdef S2W_UART_ENABLE
    /* Dispaly uart configurations
      */
    S2w_Printf("E%d V%d B=%u,%d,",
            profile->serialPortConf.commonConf.echo,
            profile->serialPortConf.commonConf.verbose,
            profile->serialPortConf.conf.uart.baudrate, profile->serialPortConf.conf.uart.bits + 5);

    switch (profile->serialPortConf.conf.uart.parity)
    {
        case S2W_UARTCONF_PARITY_ODD:
        c = 'O';
        break;

       case S2W_UARTCONF_PARITY_EVEN:
        c = 'E';
        break;

        default:
        c = 'N';
    }

    S2w_Printf("%c,%d", c,
           profile->serialPortConf.conf.uart.stop == S2W_UARTCONF_STOP_2 ? 2 : 1);

    S2w_Printf(" &K%d &R%d\r\n",
           profile->serialPortConf.conf.uart.softflow, profile->serialPortConf.conf.uart.hardflow);
#endif

}

    /* Display Ip settings
     */

    S2w_Printf("+NDHCP=%d +NSET=", profile->netConf.dhcp);
    AppS2wIp_Print(profile->netConf.ipAddr);
    S2w_PutChar(',');

    AppS2wIp_Print(profile->netConf.netMask);
    S2w_PutChar(',');
    AppS2wIp_Print(profile->netConf.gateway);
    
    S2w_Printf("\r\n+DNS1=");
    AppS2wIp_Print(profile->dns1);
    S2w_Printf(", +DNS2=");
    AppS2wIp_Print(profile->dns2);
    
    if(profile->mode == S2W_WLANDATA_MODE_INFRA)
    {
        S2w_Printf("\r\n+WM=%d ", 0);
    }
    else
    {
        S2w_Printf("\r\n+WM=%d ", profile->mode);
    }
#ifndef S2W_IP2WIFI_SUPPORT
    if(profile->autoWlandata.mode == S2W_WLANDATA_MODE_INFRA)
    {
        S2w_Printf("+WAUTO=%d,\"", 0);
	}
	else
	{
    S2w_Printf("+WAUTO=%d,\"", profile->autoWlandata.mode);
	}
    AppS2wHal_CharNPut(profile->autoWlandata.ssid,
            profile->autoWlandata.ssidLen);
    if (profile->autoWlandata.validBssid)
    {
        S2w_Printf("\",%02x:%02x:%02x:%02x:%02x:%02x",
                profile->autoWlandata.bssid[0],
                profile->autoWlandata.bssid[1],
                profile->autoWlandata.bssid[2],
                profile->autoWlandata.bssid[3],
                profile->autoWlandata.bssid[4],
                profile->autoWlandata.bssid[5]);
    }
    else
    {
        AppS2wHal_CharNPut(vBuff,2);
    }

    if(0 == profile->autoWlandata.channel)
    {
        S2w_Printf(",\r\n");
    }
    else
    {
        S2w_Printf(",%d\r\n", profile->autoWlandata.channel);
    }
#endif
    S2w_Printf("+WRETRY=%u +WP=%d +WRXPS=%d +WRXACTIVE=%d\r\n",
            profile->retryCount, profile->txPower,
            profile->powerSave, profile->radio);
#ifndef S2W_IP2WIFI_SUPPORT
    S2w_Printf("+NAUTO="
            "%d,"
            "%d,",
            profile->autoNetdata.mode,
            profile->autoNetdata.proto);
    *(ULONG*)profile->autoNetdata.ipAddr = ntohl(*(ULONG*)profile->autoNetdata.ipAddr);
    AppS2wIp_Print(profile->autoNetdata.ipAddr);
    *(ULONG*)profile->autoNetdata.ipAddr = ntohl(*(ULONG*)profile->autoNetdata.ipAddr);
    S2w_Printf(",%d", profile->autoNetdata.port);
    if((profile->autoNetdata.mode == 0) &&(profile->autoNetdata.proto == S2W_NETDATA_PROTO_UDP))
    {
		S2w_Printf(",%d", profile->udpSrcPort);
	}
	S2w_Printf("\r\n");
	
#endif
    /* display security parameters
     */
    AppS2wSecurity_Display(&profile->security);

    /* Display registers
     */
#ifndef S2W_IP2WIFI_SUPPORT
    AppS2wRegisters_Display(profile);
#endif
    S2w_Printf("\r\n+BDATA=%d  +WSEC=%d  +ASYNCMSG=%d ", profile->bulkTxEnable,
               profile->securityType,profile->asyncMsgFormat);
}



PUBLIC VOID
AppS2wNcmProfile_Display(S2W_PROFILE_T *profile)
{
	#ifndef S2W_IP2WIFI_SUPPORT
	    UINT8 vBuff[4]={"\","};
    #endif
	S2w_Printf("\r\nACTIVE CLIENT PROFILE\r\n");

    S2w_Printf("+NDHCP=%d +NSET=", profile->netConf.dhcp);
    AppS2wIp_Print(profile->netConf.ipAddr);
    S2w_PutChar(',');

    AppS2wIp_Print(profile->netConf.netMask);
    S2w_PutChar(',');
    AppS2wIp_Print(profile->netConf.gateway);

    S2w_Printf("\r\n+DNS1=");
    AppS2wIp_Print(profile->dns1);
    S2w_Printf(", +DNS2=");
    AppS2wIp_Print(profile->dns2);

    if(profile->mode == S2W_WLANDATA_MODE_INFRA)
    {
        S2w_Printf("\r\n+WM=%d ", 0);
    }
    else
    {
        S2w_Printf("\r\n+WM=%d ", profile->mode);
    }
#ifndef S2W_IP2WIFI_SUPPORT
    if(profile->autoWlandata.mode == S2W_WLANDATA_MODE_INFRA)
    {
        S2w_Printf("+WAUTO=%d,\"", 0);
	}
	else
	{
		S2w_Printf("+WAUTO=%d,\"", profile->autoWlandata.mode);
	}
    AppS2wHal_CharNPut(profile->autoWlandata.ssid,
            profile->autoWlandata.ssidLen);
    if (profile->autoWlandata.validBssid)
    {
        S2w_Printf("\",%02x:%02x:%02x:%02x:%02x:%02x",
                profile->autoWlandata.bssid[0],
                profile->autoWlandata.bssid[1],
                profile->autoWlandata.bssid[2],
                profile->autoWlandata.bssid[3],
                profile->autoWlandata.bssid[4],
                profile->autoWlandata.bssid[5]);
    }
    else
    {
        AppS2wHal_CharNPut(vBuff,2);
    }

    if(0 == profile->autoWlandata.channel)
    {
        S2w_Printf(",\r\n");
    }
    else
    {
        S2w_Printf(",%d\r\n", profile->autoWlandata.channel);
    }
#endif
#ifndef S2W_IP2WIFI_SUPPORT
    S2w_Printf("+NAUTO="
            "%d,"
            "%d,",
            profile->autoNetdata.mode,
            profile->autoNetdata.proto);
    *(ULONG*)profile->autoNetdata.ipAddr = ntohl(*(ULONG*)profile->autoNetdata.ipAddr);
    AppS2wIp_Print(profile->autoNetdata.ipAddr);
    *(ULONG*)profile->autoNetdata.ipAddr = ntohl(*(ULONG*)profile->autoNetdata.ipAddr);
    S2w_Printf(",%d", profile->autoNetdata.port);
    if((profile->autoNetdata.mode == 0) &&(profile->autoNetdata.proto == S2W_NETDATA_PROTO_UDP))
    {
		S2w_Printf(",%d", profile->udpSrcPort);
	}
	S2w_Printf("\r\n");

#endif
    /* display security parameters
     */
    AppS2wSecurity_Display(&profile->security);
    S2w_Printf("\r\n");

	S2w_Printf("\r\nACTIVE LIMITED-AP PROFILE\r\n+NSET=");
    AppS2wIp_Print((UINT8*)&profile->lmtdApConf.ipAddress);
    S2w_PutChar(',');

    AppS2wIp_Print((UINT8*)&profile->lmtdApConf.subnetmask);
    S2w_PutChar(',');
    AppS2wIp_Print((UINT8*)&profile->lmtdApConf.gateway);
    S2w_Printf("\r\n+WAUTO=%d,\"", 2);
    AppS2wHal_CharNPut(profile->lmtdApConf.ssid.array,
            profile->lmtdApConf.ssid.length);
    S2w_Printf("\"");
    if(0 == profile->lmtdApConf.channel)
    {
        S2w_Printf(",\r\n");
    }
    else
    {
        S2w_Printf(",%d\r\n", profile->lmtdApConf.channel);
    }
    S2w_Printf("+STATIONS=%d  +REGDOMAIN=%d  +BEACONINTRL=%d ", profile->lmtdApConf.noStations,
               profile->lmtdApConf.regDomain,profile->lmtdApConf.beaconInterval);
    S2w_Printf("\r\n+DHCPSRVR=%d  +DHCPCLIENTS=%d  +DHCPLEASE=%d ", profile->lmtdApConf.dhcpServerEnable,
               profile->lmtdApConf.dhcpNumAddresses,(ntohl(profile->lmtdApConf.dhcpLeaseTime)));
    S2w_Printf("\r\n+DNSSRVR=%d  +DNSDOMAIN=%s", profile->lmtdApConf.dnsServerEnable,
               profile->lmtdApConf.dnsDomainName);
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT&V Command.
     This function displays the current configuration.It displays the
     current active profile,profile1 and profile2.
 * @param ptr Pointer to the user input string.

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_ConfigOutput(UINT8 *ptr)
{

    if (*ptr)
        return S2W_EINVAL;

    S2w_Printf("\r\nACTIVE PROFILE\r\n");
    AppS2wProfile_Display(&s2wCurrent);

    S2w_Printf("\r\n\r\nSTORED PROFILE 0\r\n");
    AppS2wProfile_Display(&s2wFlashParams->profile[0]);

    S2w_Printf("\r\n\r\nSTORED PROFILE 1\r\n");
    AppS2wProfile_Display(&s2wFlashParams->profile[1]);
    S2w_Printf("\r\n");

    return S2W_SUCCESS;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WRETRY Command.
 *   Thif function check the validity of the retry parameter and call the
 *   hal function to configure the wlan retry.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-Retry configuration failed.
 ******************************************************************/
UINT8
AppS2wCmd_Wretry(UINT8 *ptr)
{
    UINT8 status;
    UINT32 retryCount;

    /* check the retry count is valid
     */
    status = AppS2wParse_Int(ptr, &retryCount);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    /* retry_count is a UINT32 but wlan limited to 255*/
    if (retryCount > 255)
    {
        return S2W_EINVAL;
    }

    /* call the wdd API function to configure the wlan retry count
     */

    status = GsnWdd_TxNumRetrySet(&s2wappMainTaskCtxt->if0.wddCtx, (UINT16)retryCount);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* update the active profile retry parameter
     */
    s2wCurrent.retryCount = retryCount;

    return S2W_SUCCESS;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WP Command.
 *   This function check the validity of the power number passed and call
     the hal function to configure the wlan radio power.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-power configuration failed.
 ******************************************************************/
UINT8
AppS2wCmd_Wpower(UINT8 *ptr)
{
    UINT8 status;
    UINT32 power[5],i=0;
    UINT8 *p;
    GSN_WDD_TX_POW_SET_PARAM_T param;

    /* check the power number passed is valid
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
		return S2W_EINVAL;
	}
	memset(&param,0,sizeof(GSN_WDD_TX_POW_SET_PARAM_T));
    status = AppS2wParse_Int(p, &power[0]);
    if ((status != S2W_SUCCESS) || (power[0] > 15))
    {
        return S2W_EINVAL;
    }
    param.txPow[0]= power[0];
    for(i=1;i<5;i++)
    {
		p = AppS2wParse_NextParamGet(&ptr);
		if (p && *p)
        {
		    status = AppS2wParse_Int(p, &power[i]);
		    if ((status != S2W_SUCCESS) || (power[i] > 15))
    {
        return S2W_EINVAL;
    }
            param.txPow[i]= power[i];
		}
	}
    status = GsnWdd_TxPowerSet(&s2wappMainTaskCtxt->if0.wddCtx, &param);
    /* call the wdd function to set the wlan radio power
     */
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* update the active profile power number
     */
    s2wCurrent.txPower = power[0];
    return S2W_SUCCESS;
}



#ifdef S2W_IPv6_SUPPORT


UINT8
AppS2wCmd_Nsetv6(UINT8* ptr)
{
  GSN_NWIF_IPv6_CONFIG_T Ipv6Params;
  UINT8 *p;
  UINT32 IPv6Addr[4],IPv6AddrType,status;

  memset(&Ipv6Params,0,sizeof(GSN_NWIF_IPv6_CONFIG_T));
  
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  if(p == NULL)
    return S2W_FAILURE;

  status = inet_pton(AF_INET6, (const char*)p, (VOID*)IPv6Addr);
   if(status != TRUE)
    return S2W_EINVAL;

  GSN_IPv6_CHANGE_ENDIAN(IPv6Addr);


  IPv6AddrType = GSN_IPv6_ADDR_TYPE(IPv6Addr);

  switch(IPv6AddrType)
  {


      /* Set LinkLocal IPv6 address    */
    case GSN_IPv6_LINK_LOCAL:

      Ipv6Params.flags |= GSN_NWIF_IP6_FLG_MANUAL_LINK_LOCAL_ADDR;
      memcpy(Ipv6Params.linkLocalAddr,IPv6Addr,S2W_IPv6_ADDR_LENGTH);
      break;

    /* Set Global address   */
    case GSN_IPv6_GLOBAL:

      Ipv6Params.flags |= GSN_NWIF_IP6_FLG_MANUAL_GLOBAL_ADDR;
      memcpy(Ipv6Params.globalAddr,IPv6Addr,S2W_IPv6_ADDR_LENGTH);
      break;
    /* Can not set these as interface ipv6 address */
    case GSN_IPv6_INVALID:
    case GSN_IPv6_MULTICAST:
    case GSN_IPv6_LOOPBACK:
    case GSN_IPv6_UNSPECIFIED:
      return S2W_EINVAL;


    default:
      return S2W_EINVAL;
  }


   p=(UINT8*)AppS2wParse_NextParamGet(&ptr);

  if(!p)
    Ipv6Params.prefixLen = S2W_IPv6_DEFAULT_PREFIX_LENGTH;
  else
  {
    status = AppS2wParse_Int(p, (UINT32*)&Ipv6Params.prefixLen);
    if (status != S2W_SUCCESS)
    {
      return S2W_EINVAL;
    }

  }

  status = GsnNwif_IPv6Configure(&s2wappMainTaskCtxt->if0.nwifCtx,&Ipv6Params,NULL);

   if(GSN_NW_IF_CLOSED == status)
	{
		GSN_NWIF_IP_CONFIG_T ipCfg = {0};

		ipCfg .flag = GSN_NWIF_IPCONFIG_FLAG_IPV6_INIT;

		memcpy((UINT8 *)&ipCfg.ipv6, (UINT8 *)&Ipv6Params, sizeof(Ipv6Params));
		
		status = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipCfg, NULL);
	}	
	if(status != GSN_SUCCESS )
	{
		return S2W_FAILURE;
	}

    return S2W_SUCCESS;
}

void S2w_getDhcpv6Clientconfig(GSN_NWIF_DHCP_PARAMS_T *dhcpv6Params)
{
      dhcpv6Params->ianaID = 0x12345678;
      dhcpv6Params->T1 = 0x11111111;
      dhcpv6Params->T2 = 0x11111111;
      dhcpv6Params->preferredLifeTime = 0x0000ffff;
      dhcpv6Params->validLifeTime = 0x0000ffff;
  
      s2wappMainTaskCtxt->if0.nwifCtx.notifyIpv6Cb = DHCP_notify;
      dhcpv6Params->pStack =  (UINT8 *)dhcpv6ClientStack;
      dhcpv6Params->stackSize = APP_NWIF_DHCPv6_CLIENT_THREAD_STACK_SIZE;
      dhcpv6Params->pPktPoolHndl = GsnNw_PktPoolHndlGet(&s2wappMainTaskCtxt->nwCtx, GSN_NW_LBUF_PKT_POOL);
 
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NDHCPv6 Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Ndhcpv6(UINT8 *ptr)
{
  UINT8 *p,enable,oldStatus;
  UINT32 status;
  GSN_NWIF_IPv6_CONFIG_T userIpv6Conf;
  S2W_STATUS_INFO_T currentConfig;
  GSN_NWIF_DHCP_PARAMS_T dhcpv6Params;
  
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  status = AppS2wParse_Boolean(p, &enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    oldStatus = s2wCurrent.netConf.dhcpv6;
    if(enable)
    {
      if(GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE)
      {
          memset(&userIpv6Conf,0,sizeof(GSN_NWIF_IPv6_CONFIG_T));
          memset(&currentConfig,0,sizeof(S2W_STATUS_INFO_T));
          memset(&dhcpv6Params,0,sizeof(GSN_NWIF_DHCP_PARAMS_T));
      
   
          userIpv6Conf.flags = GSN_NWIF_IP6_FLG_DHCP_V6_CONFIG;

          S2w_getDhcpv6Clientconfig(&dhcpv6Params);

          /* stop if dhcpv6 thread is already running */
          GsnNwIf_DhcpV6Stop(&s2wappMainTaskCtxt->if0.nwifCtx);
      
          status = GsnNwif_PrivateIPv6Config(&s2wappMainTaskCtxt->if0.nwifCtx, &userIpv6Conf, &dhcpv6Params);
          S2wL3Wait = TRUE;
          if(status != GSN_OPERATION_IN_PROGRESS)
          DHCP_notify(GSN_FAILURE, &s2wappMainTaskCtxt->if0.nwifCtx);
      
          GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
          if(L3Dhcpv6Status)
          {
          AppS2wHdrAndIpv6_Print();
          L3Dhcpv6Status = FALSE;
          s2wCurrent.netConf.dhcpv6 = TRUE;
          return S2W_SUCCESS;
          }
          else
          {
          L3Dhcpv6Status = FALSE;
          s2wCurrent.netConf.dhcpv6 = oldStatus;
          return S2W_FAILURE;
          }
     
    }
    else
    {
      /* No L2 connection */
      s2wCurrent.netConf.dhcpv6 = TRUE;
      return S2W_SUCCESS;
    }
    
    }
    
    else
    {
      s2wCurrent.netConf.dhcpv6 = FALSE;
    }
    return S2W_SUCCESS;
  
}













/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NCUDPv6 Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Ncudpv6(UINT8 *ptr)
{
  UINT8 status;
  UINT8 cid;
  UINT8 *p;
  UINT32 remotePort,sourcePort=0;
  S2W_NETDATA_T remoteServerData;
  
  memset(&remoteServerData,0,sizeof(S2W_NETDATA_T));
  
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  if(p == NULL)
    return S2W_FAILURE;
  

  
   status = inet_pton(AF_INET6, (const char*)p, (VOID*)remoteServerData.ipv6Addr);
   
     if(status != TRUE)
        return S2W_EINVAL;

      GSN_IPv6_CHANGE_ENDIAN(remoteServerData.ipv6Addr);



  
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  if(p == NULL)
    return S2W_FAILURE;
 
  status = AppS2wParse_Int(p, &remotePort);

  if (status != S2W_SUCCESS || !is_valid_port(remotePort))
  {
    return S2W_EINVAL;
  }
  
  remoteServerData.port = remotePort;
  
  /* If source port is specified */
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  if(p != NULL)
  {
    status = AppS2wParse_Int(p, &sourcePort);
 
    if (status != S2W_SUCCESS || !is_valid_port(sourcePort))
    {
      return S2W_EINVAL;
    }
    
    if (AppS2wParse_NextParamGet(&ptr))
      return S2W_EINVAL;
  }
    
    remoteServerData.proto = S2W_NETDATA_PROTO_UDP;
    remoteServerData.mode  = S2W_NETDATA_MODE_CLIENT;
  
  status = AppS2wHal_NetUdpClientv6(&remoteServerData, &cid,(UINT16)sourcePort);
    
        return status;
    
    
     
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NSUDPv6 Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Nsudpv6(UINT8* ptr)
{
    S2W_NETDATA_T serverData;
    UINT8 status;
    UINT32 port;
    UINT8 cid;
    
    status = AppS2wParse_Int(ptr, &port);
    if (status != S2W_SUCCESS || !is_valid_port(port))
    {
        return S2W_EINVAL;
    }
    serverData.port = port;
    serverData.proto = S2W_NETDATA_PROTO_UDP;
    serverData.mode = S2W_NETDATA_MODE_SERVER;
    
    status = AppS2wHal_NetUdpServerv6(&serverData, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);
    return status;
 
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NCTCPv Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Nctcpv6(UINT8* ptr)
{
    UINT32 status;
    UINT8 cid;
    UINT8 *p;
    UINT32 remotePort;
    S2W_NETDATA_T remoteServerData;
  
  memset(&remoteServerData,0,sizeof(S2W_NETDATA_T));
  
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  if(p == NULL)
    return S2W_FAILURE;
  
  
   status = inet_pton(AF_INET6, (const char*)p, (VOID*)remoteServerData.ipv6Addr);
    if(status != TRUE)
      return S2W_EINVAL;

      GSN_IPv6_CHANGE_ENDIAN(remoteServerData.ipv6Addr);

  
  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  if(p == NULL)
    return S2W_FAILURE;
 
  status = AppS2wParse_Int(p, &remotePort);
  
  if (status != S2W_SUCCESS || !is_valid_port(remotePort))
  {
    return S2W_EINVAL;
  }
  
  remoteServerData.port = remotePort;
  
  remoteServerData.proto = S2W_NETDATA_PROTO_TCP;
  remoteServerData.mode  = S2W_NETDATA_MODE_CLIENT;
  
  status = AppS2wHal_NetTcpClientv6(&remoteServerData, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    } 
    
  AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);
  
  return status;
  
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NSTCPv6 Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Nstcpv6(UINT8* ptr)
{
    S2W_NETDATA_T serverData;
    UINT8 status;
    UINT32 port;
    UINT8 cid;

    status = AppS2wParse_Int(ptr, &port);
    if (status != S2W_SUCCESS || !is_valid_port(port))
    {
        return S2W_EINVAL;
    }

    serverData.port = port;
    serverData.proto = S2W_NETDATA_PROTO_TCP;
    serverData.mode = S2W_NETDATA_MODE_SERVER;

    status = AppS2wHal_NetTcpServerv6(&serverData, &cid);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);

    return status;
}

/**
 ******************************************************************
* @ingroup S2w-Application
 * @brief Process the AT+DHCPvSERVER command
 *   This function validate the parameter passed and call the dhcpv6 server start function.
 * @param ptr Pointer to the user input string.

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-ip config failed.
 ******************************************************************/

UINT8 AppS2wCmd_Dhcpv6Server(UINT8 *ptr)
{

  UINT8 status;
  UINT8 enable, *p;
  GSN_DHCPV6_SRVR_INIT_PARAM_T dhcpv6ServerInitParams;
  UINT8 macAddr[6];
  GSN_NWIF_IP_CONFIG_T nwParams;


  p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

        if(enable)
        {
          GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
          memcpy(dhcpv6ServerInitParams.startAddr,nwParams.ipv6.globalAddr,16);
          dhcpv6ServerInitParams.serverId.opCode = OPTION_SERVERID;  /* DHCPV6_SERVER_DUID_TYPE_LINK_ONLY  is  only supported. */
          dhcpv6ServerInitParams.serverId.optionLength = 0x000A;
          dhcpv6ServerInitParams.serverId.duidType = DHCPV6_SERVER_DUID_TYPE_LINK_ONLY;
          dhcpv6ServerInitParams.serverId.hardwareType = DHCPV6_HW_TYPE_IEEE_802;
		  //status = S2w_LoadMacAddr(macAddr);
		  S2w_macAddrRTCGet(macAddr);
		  //if (status != S2W_SUCCESS)
			//return S2W_FAILURE;

		  macAddr[0] += macAddr[1];
          macAddr[1] = macAddr[0]-macAddr[1];
          macAddr[0] -= macAddr[1];
          *(ULONG*)(macAddr+2) = htonl(*(ULONG*)(macAddr+2));
          memcpy((VOID*)&dhcpv6ServerInitParams.serverId.linkLayerAddressMsw,(VOID*)macAddr,2);
          memcpy((VOID*)&dhcpv6ServerInitParams.serverId.linkLayerAddressLsw,(VOID*)(macAddr+2),4);

          serverId.pNwif = &s2wappMainTaskCtxt->if0.nwifCtx;

          status = GsnDhcpv6Srvr_start(&serverId,&dhcpv6ServerInitParams);
          
          if(status != S2W_SUCCESS)
            return S2W_FAILURE;
        }
      else
      {
        status = GsnDhcpv6Srvr_Stop(&serverId);
        return status;
      }
        return status;

}


#endif


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NCUDP Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Ncudp(UINT8 *ptr)
{
    S2W_NETDATA_T peerData;
    UINT8 *temp = ptr;
    UINT32 status;
    UINT8 cid;
    UINT32 srcPort=0;
    UINT8 *p;

    if (s2wIsAutoconnected)
    {
        return S2W_EINVAL;
    }
    if(s2wLinkState == S2W_LINK_STATE_DISCONNECTED)
    {
        return S2W_LINK_LOST_EVT;
    }

    status = AppS2wParse_AddrPort(&temp, &peerData);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    peerData.proto = S2W_NETDATA_PROTO_UDP;
    peerData.mode = S2W_NETDATA_MODE_CLIENT;

    /* check the srs port given */
    p = AppS2wParse_NextParamGet(&temp);
    if (p)
    {
        status = AppS2wParse_Int(p, &srcPort);
        if (status != S2W_SUCCESS || !is_valid_port(srcPort))
        {
            return S2W_EINVAL;
        }
        if (AppS2wParse_NextParamGet(&temp))
            return S2W_EINVAL;


    }
    status = AppS2wHal_NetUdpClient(&peerData, &cid,(UINT16)srcPort);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    AppS2wProcess_StatusNotify(S2W_CON_SUCCESS, cid);

    return status;

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the ATS Command.
 *   This function updates the register setting of S2W.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure- Register setting failed.
 ******************************************************************/
UINT8
AppS2wCmd_Settings(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT32 value;
    UINT8 which;

	/* Bug Fix 5886 - Command to configure max recv/recvfrom on socket is not working */
    if (*ptr < '0' || *ptr > '9' || *(ptr + 1) != '=')
    {
       return S2W_EINVAL;
    }
	
    which = *ptr - '0';

	if (which > (S2W_NUM_TIMEOUTS + 2))
    {
        return S2W_EINVAL;
    }

    ptr += 2;
    while (isspace(*ptr))
    {
        ptr++;
    }

    if (*ptr == '?')
    {
		UINT32 localValue=0;
        status = S2W_SUCCESS;
		switch(which)
		{
			case 9:
			localValue = s2wCurrent.socRdCnt;
			break;
			case 8:
			localValue = s2wCurrent.autoExitTimeout;
			break;
			default:
			if(which < S2W_NUM_TIMEOUTS)
				localValue = s2wCurrent.registers[which];
			break;
    }
		S2w_Printf("\r\n%u", localValue);
	}
    else if (isdigit(*ptr))
    {
        /* validate the input string
         */
        status = AppS2wParse_Int(ptr, &value);
        if (status != S2W_SUCCESS || value > 65535)
        {
            return S2W_EINVAL;
        }

        /* update the current active profile
         */
		if(which < S2W_NUM_TIMEOUTS)
        s2wCurrent.registers[which] = value;

		if(which == 9)
		{
			s2wCurrent.socRdCnt=value;
		}
		else if(which == 8)
		{
			s2wCurrent.autoExitTimeout = value;
		}
        if(S2W_REG_SCAN_TIME == which)/* scan time in mSec. Set it in wlan Fw too*/
        {
            /* set the scan time
            */
            s2wCurrent.minScanTime = value;
            status = GsnWdd_ScanParamSet(&s2wappMainTaskCtxt->if0.wddCtx,s2wCurrent.minScanTime,s2wCurrent.minScanTime,0);
        }
    }
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+MCSTSET command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_McastRecvSet(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT8 set=0;

    status = AppS2wParse_Boolean(ptr,&set);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    return AppS2wHal_McastRecvSet(set);

}


PUBLIC UINT8
AppS2wCmd_ieeePsPollSet(UINT8 *ptr)
{
    UINT8 *p,status;
    UINT32 enable=0;
	UINT32 val = 0;
	GSN_WDD_STA_PS_CFG_SET_PARAM_T psCfg ;
	GSN_STATUS retVal=GSN_FAILURE;
    memset(&psCfg,0,sizeof(psCfg));
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &enable);
    if(status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }
    if(enable)
    {
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			/*[listenInterval]. This the listen interval that will be advertised in the association request*/
			val = 0;
			status = AppS2wParse_Int(p, &val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			psCfg.listenIntervalAssoc = val;
		}
		
		/*[wakeupType]*/
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{			
			status = AppS2wParse_Int(p, &val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			val++;/*Mapping to GSN_WIF_WLAN_STA_PS_WAKEUP_T*/
			psCfg.wakeupType = (GSN_WIF_WLAN_STA_PS_WAKEUP_T)val;
		}
		/*[wakeupInterval]*/
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			status = AppS2wParse_Int(p, &val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			psCfg.wakeupInterval = val;
		}
		/* Set default beacon Wait Duration to 10 mSec*/
		psCfg.beaconWaitTimeout = 10;/* Default for 
										PS Poll is 10 MSec*/
		/*[the beacon Wait Duration ]*/
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			status = AppS2wParse_Int(p, &val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			psCfg.beaconWaitTimeout = val;/**/
		}
        
        /*[data Rx type - GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_T ]*/
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			status = AppS2wParse_Boolean(p, (UINT8 *)&val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			if(val)
			{
			    psCfg.dataRxType = GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_SWITCH_TO_ACTIVE;/* */
			}
			else 
			{
			    psCfg.dataRxType = GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_PS_POLL;/* */
			}
		}
        /*[Active to off switch timeout offset in ms ]*/
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			status = AppS2wParse_Int(p, &val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			psCfg.activeToOffTimeout = val;/**/
		}
		/*[Periodicity to switch to Active in ms ]*/
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			status = AppS2wParse_Int(p, &val);
			if(status != S2W_SUCCESS)
			{
				return S2W_EINVAL;
			}
			psCfg.switchToActivePeriod= val;/**/
		}
    }

    if(enable)
    {
    	if(2 == enable)/* Just set the IEEE PS configuration*/
		{
			psCfg.uapsdEnable = 0x00;
    		retVal = GsnWdd_RadioPowerSaveCfgSet(&s2wappMainTaskCtxt->if0.wddCtx, &psCfg);
			if(retVal != GSN_SUCCESS)
				return S2W_FAILURE;				
			memcpy(&s2wCurrent.ieeePScfg,&psCfg,sizeof(GSN_WDD_STA_PS_CFG_SET_PARAM_T));			
		}
       	else if(1 == enable)
		{
        	GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_IEEEPS_MODE_ON,NULL);			
			s2wCurrent.powerSave = 0;
			s2wCurrent.ieeePScfgEn=1;
		}
    }
    else
    {
        GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_IEEEPS_MODE_OFF,NULL);
		//s2wCurrent.powerSave = 0;
		s2wCurrent.ieeePScfgEn=0;
    }
    return S2W_SUCCESS;
}


#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+SSLOPEN command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS or S2W_FAILURE.
 ******************************************************************/
UINT8
AppS2wCmd_SSLOpen(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT8 cid;
    UINT8 valCid;
    UINT8 *p;
    UINT8 endParam = 1;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        S2w_Printf("Invalid Parameter\n");
        return S2W_EINVAL;
    }

    cid = *p;

    valCid = AppS2w_CidValidate(cid);

    if (valCid != INVALID_CID)
    {
        UINT8 *pCertName = NULL;
        UINT8 *pClientCertName = NULL;
        UINT8 *pClientKeyName = NULL;

        (VOID)pClientCertName;
        (VOID)pClientKeyName;

        p = AppS2wParse_NextParamGet(&ptr);

        if (p != NULL)
        {
            pCertName = p;
            endParam = 0;

        }

        if(!endParam)
        {
            endParam = 1;
            p = AppS2wParse_NextParamGet(&ptr);
            if(NULL != p)
            {
                endParam = 0;
                pClientCertName = p;
            }
        }

        if(!endParam)
        {
            endParam = 1;
            p = AppS2wParse_NextParamGet(&ptr);
            if(NULL != p)
            {
                endParam = 0;
                pClientKeyName = p;
            }
        }
#ifdef S2W_SSL_CLIENT_SUPPORT
        if( S2W_NETDATA_MODE_CLIENT == AppS2w_ConnModeGet(valCid))
        {
            status = AppS2w_SslClientOpen(valCid, (INT8*)pCertName, pClientCertName,
                                          pClientKeyName);
        }
#endif
#ifdef S2W_SSL_SERVER_SUPPORT
        if( S2W_NETDATA_MODE_SERVER == AppS2w_ConnModeGet(valCid))
        {
            status = AppS2w_SslServerOpen(valCid, (char*)pCertName);
        }
#endif
        return status;
    }
    else
    {
        S2w_Printf("Invalid CID\n");
        return S2W_EBADCID;
    }
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+SSLOPEN command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS or S2W_FAILURE.
 ******************************************************************/
UINT8
AppS2wCmd_SSLClose(UINT8 *ptr)
{
    //UINT8 status;
    UINT8 cid = *ptr;
    UINT8 valCid;

    if ((valCid = AppS2w_CidValidate(cid)) != INVALID_CID)
    {
        return AppS2w_SslClose(valCid);
    }
    else
    {
        return S2W_EBADCID;
	}
}

#endif


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief s2w rigister info display function
 *   This function print s2w register inforamtion passed.
 * @param profile - IN  Pointer to the profile data
 *
 * @return none.
 ******************************************************************/
VOID
AppS2wRegisters_Display(const S2W_PROFILE_T *profile)
{
    INT32 i;

    for (i = 0; i < S2W_NUM_TIMEOUTS; i++)
    {
        S2w_Printf("%sS%d=%05u", !i ? "\r\n" : " ",
                i, profile->registers[i]);
    }
}

VOID AppS2w_ConctCbProcess(VOID* ctext,INT32 status)
{
	GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    if(status == GSN_SUCCESS)
    {
        s2wLinkState = S2W_LINK_STATE_CONNECTED;
    }
    else
    {
        /* get the association status by calling geps API
         */
        if(GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE)
        {
            s2wLinkState = S2W_LINK_STATE_CONNECTED;
        }
        else
        {
            s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
        }

    }
    
    if(s2wLinkState == S2W_LINK_STATE_CONNECTED)
    {
		s2wCurrent.security.wpa.pskValid = pWlanConfig->securityCfg.pskConfig.pskValid;

		if(pWlanConfig->securityCfg.pskConfig.pskValid)
		{
			 memcpy(s2wCurrent.security.wpa.psk,
					pWlanConfig->securityCfg.pskConfig.psk, 32);			 
			 memset(s2wCurrent.security.wpa.ssid,0,S2W_MAX_SSID_LEN);
			 memcpy(s2wCurrent.security.wpa.ssid,pWlanConfig->ssid.array,
						 pWlanConfig->ssid.length );
					 s2wCurrent.security.wpa.ssidLen = pWlanConfig->ssid.length;
		 }
        /* copy the ssid and len  and channel       */
        memcpy(current_wlan_info.ssid,pWlanConfig->ssid.array,
               pWlanConfig->ssid.length );
        current_wlan_info.ssidLen = pWlanConfig->ssid.length;

        /* associated ch will be at 0 index
         */
        current_wlan_info.channel = pWlanConfig->channel[0];

        memcpy(current_wlan_info.bssid, pWlanConfig->bssid.array,6);
        current_wlan_info.validBssid = 1;
        current_wlan_info.mode = ((APP_MAIN_CTX_T*)ctext)->if0.wddCtx.wlanNwType;
        // update the security info
        current_wlan_info.authMode = pWlanConfig->securityCfg.mode;
        if(pWlanConfig->securityCfg.mode == GSN_WDD_SEC_MODE_WEP)
        {
            if(pWlanConfig->securityCfg.wepConfig.authType == GSN_WDD_SEC_WEP_SHARED)
            {
                current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_SHARED;
            }
            else
            {
                current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_OPEN;
            }
        }
    }
}

VOID
AppS2w_WlanRespTmrCb( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle )
{
	GSN_ASSERT(FALSE);
}
VOID
s2wApp_ConnectCb( VOID* ctext, INT32 status)
{	
	/*stop timer*/
	GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
	L2ConnectStatus = status;
    GsnOsal_SemRelease ( &s2wL2L3ConnectSemaphore);
}

#ifdef S2W_SNTP



PUBLIC VOID AppS2wProcess_SntpTimerNotify()
{
    GsnSntp_TimeSync(&s2wappMainTaskCtxt->sntpCtx, s2wappMainTaskCtxt->sntpSrvIp,
                      s2wappMainTaskCtxt->sntpSrvTimeout ,
                      S2wApp_TimeSyncDoneCb, &s2wappMainTaskCtxt->sntpCtx);
}


UINT8
AppS2wCmd_ntpTimeSet(UINT8 *ptr)
{
    BOOL enable=0, periodic=0;
    UINT8 *p,status;
    S2W_IPADDR_T srvIp;
	GSN_STATUS ret;
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &enable);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }

    if(enable)
    {
        p = AppS2wParse_NextParamGet(&ptr); // serv ip
        if ((p) && (*p != '\0'))
        {
            status = AppS2wParse_Ip(p, srvIp );
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            memcpy((UINT8*)&s2wappMainTaskCtxt->sntpSrvIp,srvIp,4);

            p = AppS2wParse_NextParamGet(&ptr);  // srv timeout
            if (!p)
            {
                return S2W_EINVAL;
            }
            status = AppS2wParse_Int(p,&s2wappMainTaskCtxt->sntpSrvTimeout );
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            p = AppS2wParse_NextParamGet(&ptr);  // periodic/oneshot
            if (!p)
            {
                return S2W_EINVAL;
            }
            status = AppS2wParse_Boolean(p,&periodic );
            if (status != S2W_SUCCESS)
            {
                return status;
            }

            if(periodic)
            {
                p = AppS2wParse_NextParamGet(&ptr);  // timer period
                if (!p)
                {
                    return S2W_EINVAL;
                }
                status = AppS2wParse_Int(p,&s2wappMainTaskCtxt->sntpTimerPeriod );
                if (status != S2W_SUCCESS)
                {
                    return status;
                }
                // start a timer
            }
            else
            {
                if(s2wLinkState != S2W_LINK_STATE_CONNECTED)
                  return S2W_FAILURE;
            }
	    }
	    else // with default values
	    {
            if(S2W_DFLT_SNTP_PERIODIC)
            {
                periodic=1;
                s2wappMainTaskCtxt->sntpTimerPeriod = S2W_DFLT_SNTP_PERIODIC_PERIOD;
			}
			else
			{
				periodic=0;
			}
            s2wappMainTaskCtxt->sntpSrvIp = ntohl(S2W_DFLT_SNTP_SVR_IP);
            s2wappMainTaskCtxt->sntpSrvTimeout = S2W_DFLT_SNTP_TIMEOUT;
		}
        s2wappMainTaskCtxt->sntpCtx.pWdd = &s2wappMainTaskCtxt->if0.wddCtx;
        	ret = GsnSntp_TimeSync(&s2wappMainTaskCtxt->sntpCtx, s2wappMainTaskCtxt->sntpSrvIp,
                                                    s2wappMainTaskCtxt->sntpSrvTimeout ,
                                                    S2wApp_TimeSyncDoneCb, &s2wappMainTaskCtxt->sntpCtx);
            if (GSN_SNTP_BUSY== ret)
            {
				S2w_Printf("\r\n\r\nSNTP busy\r\n");			
                return S2W_FAILURE;
            }
			else if(GSN_OPERATION_IN_PROGRESS != ret)
                return S2W_FAILURE;

        if(1 == periodic)
		{
            GsnSoftTmr_Start (&s2wappMainTaskCtxt->appSntpTimer, GSN_SOFT_TMR_PERIODIC,
                                      0,((TIMER_INTERRUPT_1_S * s2wappMainTaskCtxt->sntpTimerPeriod)),
                                      ( GSN_SOFT_TMR_CBR_T )AppS2w_sntpTimerCb,
                                  NULL );
		}
    }
    else // disable
    {
        if(*ptr)
        {
            return S2W_EINVAL;
        }
        GsnSoftTmr_Stop (&s2wappMainTaskCtxt->appSntpTimer);
    }
    return S2W_SUCCESS;

}

PRIVATE VOID
S2wApp_TimeSyncDoneCb(INT32 status, VOID* context)
{
	GSN_SNTP_CTX_T *pSntpCtx = (GSN_SNTP_CTX_T *)context;
	if(status == GSN_SUCCESS)
	{
		GsnTod_AdjustOffset(pSntpCtx->diffNegative, pSntpCtx->timeDiff);
	}
}


PRIVATE VOID
AppS2w_sntpTimerCb( VOID* context,
    GSN_SOFT_TMR_HANDLE_T timerHandle )
{
     UINT32 message = APP_TIME_SYNC_TIMER_INDICATION;
    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);

}
#endif

#ifdef S2W_DHCP_SERVER_ENABLE

PUBLIC UINT8
AppS2wCmd_DhcpSrvrConfig(UINT8 *ptr)
{
    UINT8 status;
    UINT8 * p;
  
    /* can only be set before starting DHCP server */ 
    if(dhcpServerFlags & S2W_DHCP_SRVR_ENABLED)
     {
       return S2W_EINVAL;
     }
    memset(&dhcpSrvrCfg,0,sizeof(GSN_DHCP_SRVR_CFG_T));
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
   status = AppS2wParse_Ip(p, (UINT8 *)&dhcpSrvrCfg.startIpAddr); 
   
   dhcpSrvrCfg.startIpAddr = ntohl(dhcpSrvrCfg.startIpAddr);
    
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&dhcpSrvrCfg.numOfClients);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    
    if(dhcpSrvrCfg.numOfClients > S2W_DHCP_SRVR_MAX_CLIENTS)
    {
       return S2W_EINVAL;
    }
    
    memcpy(&dhcpSrvrCfg.subnetMask, s2wCurrent.netConf.netMask, 4);
    memcpy(&dhcpSrvrCfg.gateway, s2wCurrent.netConf.gateway, 4);
    dhcpServerFlags |= S2W_DHCP_SRVR_CFG_DONE;
    
     return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wCmd_DhcpSrvr(UINT8 *ptr)
{
    UINT8 status;
    UINT32 mode;
    UINT8 dns=0,gateway=0;
    INT32 retVal, ipAddr;
    UINT8 * p;
    GSN_NWIF_IP_CONFIG_T  ipconfig;

    /* check the validity of parameter passed */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(mode != 0)
    {
		if(dhcpServerFlags & S2W_DHCP_SRVR_ENABLED)
		return S2W_FAILURE;
       if(!(dhcpServerFlags & S2W_DHCP_SRVR_CFG_DONE))
       {
        memset(&dhcpSrvrCfg,0,sizeof(GSN_DHCP_SRVR_CFG_T));
        dhcpSrvrCfg.numOfClients = s2wCurrent.lmtdApConf.dhcpNumAddresses;
       }
        p = AppS2wParse_NextParamGet(&ptr);
        if ((p) && (*p != '\0'))
        {
            status = AppS2wParse_Boolean(p, &dns);
		    if (status != S2W_SUCCESS)
		    {
		        return status;
		    }
        }
        p = AppS2wParse_NextParamGet(&ptr);
        if ((p) && (*p != '\0'))
        {
            status = AppS2wParse_Boolean(p, &gateway);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
        }

        
        GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&ipconfig);
        memcpy(&ipAddr,&ipconfig.ipv4.ipAddr, 4);
        dhcpSrvrCfg.serverIpAddr = ipAddr;
        if(!dns)
        {
          dhcpSrvrCfg.dns1 = ipAddr;
          if(S2W_DNS_CLIENT_FALGS & S2W_DNSv4_SERVER_SET)
          {
            dhcpSrvrCfg.dns1 = *(ULONG*)s2wCurrent.dns1;
            dhcpSrvrCfg.dns2 = *(ULONG*)s2wCurrent.dns1;
          }
        }
        else
        {
            dhcpSrvrCfg.dns1 = 0;
            dhcpSrvrCfg.dns2 = 0;
        }
        
        if(!(dhcpServerFlags & S2W_DHCP_SRVR_CFG_DONE))
        {
       
        dhcpSrvrCfg.startIpAddr = ipAddr + 1;
        
        memcpy(&dhcpSrvrCfg.subnetMask, s2wCurrent.netConf.netMask, 4);
        }
        
        dhcpSrvrCfg.pNwif = &s2wappMainTaskCtxt->if0.nwifCtx;
        dhcpSrvrCfg.pWdd = &s2wappMainTaskCtxt->if0.wddCtx;
        if(!gateway)
        {
         	/* Bug Fix 5676 - LimitedAP is offering Default gateway even when it is 
         	          configured to different gateway with NCM */
        	if(S2W_WLANDATA_MODE_PROV_AP == s2wCurrent.mode )
        	{
				dhcpSrvrCfg.gateway = S2W_DEFAULT_GRP_PROV_GATE_ADDRESS;
        	}
			else if(S2W_WLANDATA_MODE_AP == s2wCurrent.mode )
			{			
	            memcpy(&dhcpSrvrCfg.gateway, &s2wCurrent.netConf.gateway, 4);
			}
			else if(S2W_WLANDATA_MODE_INFRA == s2wCurrent.mode )
			{
				 memcpy(&dhcpSrvrCfg.gateway, &s2wCurrent.netConf.gateway, 4);
			}
			
        }
        else
        {
            dhcpSrvrCfg.gateway = 0;
        }
		dhcpSrvrCfg.leaseTime	 = s2wCurrent.lmtdApConf.dhcpLeaseTime;
		if(0 == dhcpSrvrCfg.leaseTime)
		{
                        dhcpSrvrCfg.leaseTime = htonl((UINT32)(S2W_DFLT_AP_DHCPSRVR_LEASE_TIME));
                      
		}
         
        /* Client connect/Disconnect notification callbacks */        
        GsnDhcpSrvr_ClientConnectNotify(&dhcpSrvrCfg,NULL);
        GsnDhcpSrvr_ClientDisconnectNotify(&dhcpSrvrCfg,NULL);   
        
        retVal = GsnDhcpSrvr_Start(&dhcpSrvr, &dhcpSrvrCfg);
    }
    else
    {
        retVal = GsnDhcpSrvr_Stop(&dhcpSrvr);
        if(retVal < 0)
        {
          return S2W_FAILURE;
        }
        else
        {
         dhcpServerFlags &= 0xfe;
         return S2W_SUCCESS;
        }
    }

    if(retVal < 0)
    {
        return S2W_FAILURE;
    }
    else
    {
        dhcpServerFlags |= S2W_DHCP_SRVR_ENABLED;
        return S2W_SUCCESS;
    }
}

#endif //S2W_DHCP_SERVER_ENABLE

#ifdef S2W_DNS_SERVER_ENABLE

VOID S2wDnsConfigGet(GSN_DNS_INIT_PARAM_T *gsnDnsInitParams)
{
    INT32 ip;
    GSN_NWIF_IP_CONFIG_T  ipconfig;
    memcpy(&ip, s2wCurrent.netConf.ipAddr, sizeof(S2W_IPADDR_T));
  
    gsnDnsInitParams->flags = IP_VERSION_V4
    #ifdef S2W_IPv6_SUPPORT
      //| IP_VERSION_V6
    #endif
        ;
     memset(&ipconfig,0,sizeof(GSN_NWIF_IP_CONFIG_T));

    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&ipconfig);
    if(ipconfig.ipv4.ipAddr)
    memcpy(&ip, &ipconfig.ipv4.ipAddr, sizeof(S2W_IPADDR_T)); 
#ifdef S2W_IPv6_SUPPORT    
    if(ipconfig.ipv6.globalAddr)
    memcpy(gsnDnsInitParams->serverIpv6Addr,ipconfig.ipv6.globalAddr,16);
    else
    memcpy(gsnDnsInitParams->serverIpv6Addr,ipconfig.ipv6.linkLocalAddr,16);
#endif    
    
    gsnDnsInitParams->serverIpAddr = ip;
}


PUBLIC UINT8
AppS2wCmd_Dns(UINT8 *ptr)
{
    UINT8 status;
    UINT8 mode, *p;
    INT32 retVal;

    GSN_DNS_INIT_PARAM_T gsnDnsInitParams;

    /* check the validity of parameter passed */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
 // dnsServer.pNwif = &s2wappMainTaskCtxt->if0.nwifCtx;
   memset(&gsnDnsInitParams,0,sizeof(GSN_DNS_INIT_PARAM_T));
   S2wDnsConfigGet(&gsnDnsInitParams);

     if(mode)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        /*if (!p)
        	{
           		 return S2W_EINVAL;
       		 }*/
        retVal = GsnDnsSrvr_Start(&dnsServer, p,&gsnDnsInitParams);
		if(retVal == GSN_SUCCESS)
		{
			s2wCurrent.lmtdApConf.dnsServerEnable=1;
			memset(s2wCurrent.lmtdApConf.dnsDomainName,0,MAX_DNS_DOMAIN_LEN);
			if(p != NULL)
				memcpy(s2wCurrent.lmtdApConf.dnsDomainName,p,strlen((const char *)p));
    	}
    }
    else
    {
        retVal = GsnDnsSrvr_Stop(&dnsServer);
		if(retVal == GSN_SUCCESS)
		{
			s2wCurrent.lmtdApConf.dnsServerEnable=0;			
			memset(s2wCurrent.lmtdApConf.dnsDomainName,0,MAX_DNS_DOMAIN_LEN);
		}
    }
    if(retVal < 0)
        return S2W_FAILURE;
    else
        return S2W_SUCCESS;
}

#endif //S2W_DNS_SERVER_ENABLE

UINT8
AppS2wCmd_SslCertificateAdd(UINT8 *ptr)
{
    UINT8 *p, *name;
    INT32 len,fileLen ,i = 0;
    UINT32 certStore;
	INT32 status;
	UINT8 buf[38]={0};
    name = AppS2wParse_NextParamGet(&ptr);     //get cert name
    if (!name)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)name);
    if( len > 32)
        return S2W_EINVAL;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certFormat);
    if(certFormat > 1)
        return S2W_EINVAL;
    //S2w_Printf("\n\rfile format %d", certFormat);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(p, &certFileSize);

    certFileSize = certFileSize >> certFormat;
    //S2w_Printf("\n\rfile size %d", certFileSize);

    p = AppS2wParse_NextParamGet(&ptr);     //get wehre to store SRAM/FLASH
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certStore);

    if(certStore > 1)
        return S2W_EINVAL;

	if(S2wCert_findFile((char*)name) == -1)
	{
		S2w_Printf("\n\rFILE EXISTS\n\r");
		return S2W_FAILURE;
	}
    if(certStore)
    {
    	i = S2wCert_MemAlloc(certFileSize);
	    //S2w_Printf("\nmem-alloc :%d\n",i);
	    if(i == -1)
	    	return S2W_FAILURE;
        p = gsn_malloc(len+1); //allocate memory for storing name
        if(p == NULL)
            return S2W_FAILURE;
        strcpy((INT8 *)p, (const char *)name);
        s2w_ssl_cert_table[i].name = p; //copy pointer to SRAM entry
        s2w_ssl_cert_table[i].location = CERT_IN_RAM;
        certIndex = i;
    }
    else
    {
	    status = f_mkdir("certs");
		if(status != F_NO_ERROR || status != F_ERR_DUPLICATED )
		{
			fileLen= sprintf((char*)buf,"certs/");
			memcpy(buf + fileLen, name, len);
	        certFile = f_open((const char *)buf, "w");
        if(certFile == NULL)
        	return S2W_FAILURE;
		}
        certIndex = S2W_INVALID_CERT_INDEX;
    }

    /* Store the Cert Index in a global. This is used when the actual certificate
      is received in the next escape sequence */

    return S2W_SUCCESS;
}

PUBLIC UINT32
AppS2wCertificateData(UINT8 ch1)
{
    UINT8 *buf,*tempBuff;//, ch;
    UINT16 i = 2, index = 0;
	UINT8 certInRam=0;

    if ( (certIndex == S2W_INVALID_CERT_INDEX) && (certFile == NULL))
            return S2W_FAILURE;

    if( certFileSize == 0)
            return S2W_FAILURE;

	if((certIndex != S2W_INVALID_CERT_INDEX) && (CERT_IN_RAM == s2w_ssl_cert_table[certIndex].location ) )
	{
		buf = gsn_malloc((certFileSize << certFormat) + 2 );
		certInRam=1;
    }
	else
    buf = gsn_malloc((certFileSize << certFormat) );

    if(buf == NULL)
        return S2W_FAILURE;
	tempBuff = buf;

	if(certInRam)
	{
    	*buf = certFileSize & 0x00FF;
	    *(buf + 1) = (certFileSize & 0xFF00) >> 8;
		buf+=2;
	}
    certFileSize = certFileSize << certFormat;

    /* store incoming byte in temparory bufer */
    AppS2wHal_CharNGet((buf), certFileSize);

    if(certFormat)
    {
        for(i = 0; i < certFileSize ;)
        {
            buf[index] = (AppS2wParse_ToHex(buf[i]) << 4) | (AppS2wParse_ToHex(buf[i + 1]) & 0x0F);
            i = i + 2;
            index++;
        }
    }


    /* recieving file is complete. If the Cert Address is in the 0x8000000
    range store it in flash else store it in SRAM (0x4000000 range) */
    if ( certIndex !=  S2W_INVALID_CERT_INDEX)
    {
        /* store in SRAM */
        memcpy((UINT8 *) s2w_ssl_cert_table[certIndex].certAddress, tempBuff,
            ((certFileSize >> certFormat) + 2));

    }
    else
    {
        /* store in flash */
        f_write(tempBuff, 1, (certFileSize >> certFormat) , certFile);
		f_close(certFile);
    }
    /* reset variables */
    certIndex = S2W_INVALID_CERT_INDEX;
    certFileSize = 0;
	certFile = NULL;
    gsn_free(tempBuff);
    S2w_Printf("\r\nOK\r\n");
    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_SslCertificateDelete(UINT8 *ptr)
{
    UINT8 *p, retVal =0;;
    INT32 certIndex;

    p = AppS2wParse_NextParamGet(&ptr);     //get cert name
    if (!p)
    {
         return S2W_EINVAL;
    }
    certIndex = S2wCert_SearchRamTable((char*)p);
    if(certIndex != -1)
    {
    	gsn_free (s2w_ssl_cert_table[certIndex].certAddress);
        gsn_free(s2w_ssl_cert_table[certIndex].name);
        s2w_ssl_cert_table[certIndex].name = NULL;
        s2w_ssl_cert_table[certIndex].certAddress = NULL;
        if( s2w_ssl_cert_table[certIndex].location == CERT_IN_FLASH )
    	{
			retVal = AppS2w_CertDelete(p);
    	}
    }
    else
    {
    	retVal = AppS2w_CertDelete(p);
    }

    if(retVal == S2W_SUCCESS)
    {
    	if(strcmp((const char*)p,S2W_CERT_NAME_CA) == 0)
    	{
			s2wCurrent.security.eap.useCaCert=0;
    	}
        return S2W_SUCCESS;
    }
    else
        return S2W_FAILURE;
}

PRIVATE UINT8
AppS2wCmd_Weap(UINT8 *ptr)
{
    UINT8 *name, *p;
    INT32 i = 0;
    UINT32 certStore, certType;
	INT32 status;
	INT32 fileLen;
	UINT8 buf[38]={0};

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certType);

    if(certType > 2)
        return S2W_EINVAL;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(p, &certFormat);

    if(certFormat > 1)
        return S2W_EINVAL;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certFileSize);
    certFileSize = certFileSize >> certFormat;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &certStore);

    if(certStore > 1)
        return S2W_EINVAL;

    if(certStore)
    {
    	i = S2wCert_MemAlloc(certFileSize);

	    if(i == -1)
	        return S2W_FAILURE;

        name = gsn_malloc(32);
        if(certType == 0)
            strcpy((INT8 *)name, S2W_CERT_NAME_CA);
        else if(certType == 1)
            strcpy((INT8 *)name, S2W_CERT_NAME_CLIENT);
        else
            strcpy((INT8 *)name, S2W_CERT_NAME_KEY);
        s2w_ssl_cert_table[i].name = name;
        s2w_ssl_cert_table[i].location = CERT_IN_RAM;
		certIndex = i;
    }
    else
    {
        /* write certificate name in flash */
		status = f_mkdir("certs");
		if(status != F_NO_ERROR || status != F_ERR_DUPLICATED )
		{
			fileLen= sprintf((char*)buf,"certs/");
        if(certType == 0)
				memcpy(buf + fileLen, S2W_CERT_NAME_CA, strlen(S2W_CERT_NAME_CA));	           
        else if(certType == 1)
				memcpy(buf + fileLen, S2W_CERT_NAME_CLIENT, strlen(S2W_CERT_NAME_CLIENT));
        else
				memcpy(buf + fileLen, S2W_CERT_NAME_KEY, strlen(S2W_CERT_NAME_KEY));
			certFile = f_open((const char *)buf, "w");

        if(certFile == NULL)
        	return S2W_FAILURE;
        certIndex = S2W_INVALID_CERT_INDEX;
    	}
    }
    /* Store the Cert Index in a global. This is used when the actual certificate
      is received in the next escape sequence */
    return S2W_SUCCESS;
}

#endif /* IOT_APP_ENABLE */

UINT8 AppS2wCmd_BeaconMissThresholdSet(UINT8 *ptr)
{
  UINT8 status;
  UINT32 beaconMissThresholdTime=0;
  UINT32 beaconMissThresholdNo=0;
  UINT8 *p;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Int(p, &beaconMissThresholdTime);
      if (status != S2W_SUCCESS)
      {
          return status;
      }
   }

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Int(p, &beaconMissThresholdNo);
      if (status != S2W_SUCCESS)
      {
          return status;
      }
   }

  status = GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,beaconMissThresholdTime,beaconMissThresholdNo);

     return status;
}



UINT8 AppS2wCmd_TkipContrMsrStart(UINT8 *ptr)
{
  UINT8 status = S2W_FAILURE, enable = 0;
  UINT8 *p;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Boolean(p, &enable);
      if (status != S2W_SUCCESS)
      {
          return status;
      }
   }

  if(enable)
  status =  GsnWdd_TkipContrMsrStart(&s2wappMainTaskCtxt->if0.wddCtx);

  return status;

}


UINT8 AppS2wCmd_TkipSeqNumGet(UINT8 *ptr)
{
  UINT8 status = S2W_FAILURE,enable = 0;
  UINT8 *p;
  GSN_WIF_WLAN_TKIP_COUNTER_GET_RSP_T Resp;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Boolean(p, &enable);
      if (status != S2W_SUCCESS)
      {
          return status;
      }
   }

  if(enable)
    status =  GsnWdd_TkipSeqNumGet(&s2wappMainTaskCtxt->if0.wddCtx,&Resp);

  if(status == S2W_SUCCESS)
    S2w_Printf("\r\nTKIP Sequence Number:%x %x\r\n",&Resp.msb,&Resp.lsb);

  return status;
}



UINT8 AppS2wCmd_WlanRecvFiltrSet(UINT8 *ptr)
{
  UINT8 status;
  UINT8 *p;
  GSN_WDD_WLAN_RECV_FILTR_SET_PARAM_T RecvFiltrParams;

   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Int(p,&RecvFiltrParams.filter);
      if (status != S2W_SUCCESS)
      {
          return status;
      }
   }

  status = GsnWdd_WlanRecvFiltrSet(&s2wappMainTaskCtxt->if0.wddCtx,&RecvFiltrParams);

  return status;

}


UINT8 AppS2wCmd_RtsEnable(UINT8 *ptr)
{
  UINT8 status;
  UINT32 temp;
  UINT8 *p;
  GSN_WDD_RTS_ENBL_PARAM_T RstParams;

   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Int(p,&temp);
      if (status != S2W_SUCCESS)
      {
          return status;
      }

      RstParams.threshold = temp;
   }

   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    status = AppS2wParse_Boolean(p,&RstParams.txOpEnable);
      if (status != S2W_SUCCESS)
      {
          return status;
      }
   }

   status = GsnWdd_RtsEnable(&s2wappMainTaskCtxt->if0.wddCtx,&RstParams);

  return status;
}

UINT8 AppS2wCmd_BlockAckReq(UINT8 *ptr)
{
  UINT8 status,action;
  UINT8 *p;
  UINT32 temp;
  GSN_WDD_BLOCKACK_REQ_T BlockAckReq;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Mac(p, BlockAckReq.ra);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
  }

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Int(p, &temp);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
      BlockAckReq.tid = temp;
  }


  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
     status = AppS2wParse_Boolean(p, &action);
      if (status != S2W_SUCCESS)
      {
          return status;
      }

      BlockAckReq.action = action;
   }


  status = GsnWdd_BlockAckReq(&s2wappMainTaskCtxt->if0.wddCtx,&BlockAckReq);

  return status;

}

UINT8 AppS2wCmd_AmsduReqt(UINT8 *ptr)
{
  UINT8 status,action;
  UINT8 *p;
  UINT32 temp;
  GSN_WDD_AMSDU_REQ_T AmsduReq;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Mac(p, AmsduReq.ra);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
  }

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Int(p, &temp);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
      AmsduReq.tid = temp;
  }


  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
     status = AppS2wParse_Boolean(p, &action);
      if (status != S2W_SUCCESS)
      {
          return status;
      }

      AmsduReq.action = action;
   }

  status =GsnWdd_AmsduReq(&s2wappMainTaskCtxt->if0.wddCtx,&AmsduReq);

  return status;
}


UINT8 AppS2wCmd_AmpduReq(UINT8 *ptr)
{
  UINT8 status,action;
  UINT8 *p;
  UINT32 temp;
  GSN_WDD_AMSDU_REQ_T AmpduReq;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Mac(p, AmpduReq.ra);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
  }

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Int(p, &temp);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
      AmpduReq.tid = temp;
  }


  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
     status = AppS2wParse_Boolean(p, &action);
      if (status != S2W_SUCCESS)
      {
          return status;
      }

      AmpduReq.action = action;
   }

  status =GsnWdd_AmpduReq(&s2wappMainTaskCtxt->if0.wddCtx,(GSN_WDD_AMPDU_REQ_T *)&AmpduReq);

  return status;

}



UINT8 AppS2wCmd_FrameTxFailCntLmitSet(UINT8 *ptr)
{
  UINT8 status;
  UINT8 *p;
  UINT32 temp;
  GSN_WDD_FRAME_TX_FAIL_CNT_LIMIT_SET_T TxFailLmt;

  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
      status = AppS2wParse_Int(p, &temp);
      if (status != S2W_SUCCESS)
	{
          return status;
	}
      TxFailLmt.frameTxFailCountThreshold = temp;
  }

  status = GsnWdd_FrameTxFailCntLmitSet(&s2wappMainTaskCtxt->if0.wddCtx,&TxFailLmt);

  return status;

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WSEC command. This function set the strict
 * security feature.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
UINT8
AppS2wCmd_SecuritySet(UINT8 *ptr)
{
    UINT8 status;
    UINT32 SecMode;

    /* check the validity of parameter passed
     */
    status = AppS2wParse_Int(ptr, &SecMode);
    if (status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }
    /*  allowed values are upto 32(0x40) and or'd values also other than 0
    0-->auto
    1-->none
    2-->wep
    4-->wpapsk
    8-->wpa2psk
    16-->wpaE
    32-->wpa2E
    */
    if(!((SecMode == SECTYPE_AUTO) || (SecMode == SECTYPE_NONE) ||(SecMode == SECTYPE_WEP)
         ||(SecMode == SECTYPE_WPAPSK)||(SecMode == SECTYPE_WPA2PSK)||(SecMode == SECTYPE_WPA)
         ||(SecMode == SECTYPE_WPA2)||(SecMode == SECTYPE_WPA2PSK_TKIP)))
    {
        return S2W_EINVAL;
    }

    /* update the active profile parameter
     */
    if(s2wappMainTaskCtxt->apConf)// if Ap conf enabled then store in Ap conf
    {
        s2wCurrent.lmtdApConf.securityType = SecMode;
    }
    else
    {
        s2wCurrent.securityType = SecMode;
    }

    return S2W_SUCCESS;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WAUTH command
 *   This function check the validity of the parameters passed and
 *   update the active profile authentication with the same.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
UINT8
AppS2wCmd_Wauth(UINT8 *ptr)
{
    UINT8 status;
    UINT32 mode;

    /* check the validity of parameter passed
     */
    status = AppS2wParse_Int(ptr, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if(mode > S2W_AUTH_MODE_SHARED)
    {
        return S2W_EINVAL;
    }
    /* update the active profile parameter   */
    if(s2wappMainTaskCtxt->apConf)
    {
		if((mode == S2W_AUTH_MODE_SHARED) ||
		   (mode == S2W_AUTH_MODE_OPEN))
		{
		    s2wCurrent.lmtdApConf.securityType = SECTYPE_WEP;
			s2wCurrent.lmtdApConf.wepKeyConfig.authType= (GSN_WDD_WEP_AUTH_TYPE_T)mode;
		}
	}
	else
	{
    	s2wCurrent.security.authMode = mode;
	}

    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WPA command.
 *   This function check the validity of the parameter passed and update
 *   the active profile wpa passphrase.
 * @param ptr Pointer to the user input string.

 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
UINT8
AppS2wCmd_Wwpa(UINT8 *ptr)
{
    S2W_SECURITY_T params;
    UINT32 len;
    UINT8 *p;
    memcpy(&params, &s2wCurrent.security, sizeof(params));

    /* Validate the input string.
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    len = strlen((char *)p);
    if ((len > S2W_PSK_PASSPHRASE_LEN_MAX - 1) ||
        (len < S2W_PSK_PASSPHRASE_LEN_MIN))
    {
        return S2W_EINVAL;
    }

    memset(params.wpa.wpaPassPhrase, 0, S2W_PSK_PASSPHRASE_LEN_MAX);
    memcpy(params.wpa.wpaPassPhrase, p, len);
    params.wpa.passPhraseLen = len;
    params.validKeys |= S2W_SECURITY_VALID_WPA;

    /* update the active profile parameter */
    if(s2wappMainTaskCtxt->apConf)// if Ap conf enabled then store in Ap conf
    {
        s2wCurrent.lmtdApConf.passphrase.Len = params.wpa.passPhraseLen;
        memcpy(s2wCurrent.lmtdApConf.passphrase.Passphrase, params.wpa.wpaPassPhrase,
               params.wpa.passPhraseLen);
    }
    else
    {
        memcpy(&s2wCurrent.security, &params, sizeof(s2wCurrent.security));
        s2wCurrent.security.wpa.pskValid =0;
    }
        return S2W_SUCCESS;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WPAPSK command.
 *   This function validate the parameters passed and call the hal
 *   function to calculate the psk key.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure- psk key calculation failed.
 ******************************************************************/
UINT8
AppS2wCmd_WpaPsk(UINT8 *ptr)
{
    UINT8 status;
    UINT8 *p;
    S2W_WPAPSK_T wpaPsk;
    UINT8 len=0;


    
    /* get the 1st parameter-ssid
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    memset(&wpaPsk,0,sizeof(wpaPsk));

    /* Validate the 1st parameter-ssid.
     */
    status = AppS2wParse_Ssid(p,(unsigned char*)wpaPsk.ssid,&wpaPsk.ssidLen );
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* get the 2nd parameter-passphrase
     */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    len = strlen((char *)p);
    if ((len > S2W_PSK_PASSPHRASE_LEN_MAX - 1) ||(len < S2W_PSK_PASSPHRASE_LEN_MIN))
    {
        return S2W_EINVAL;
    }

    memcpy(wpaPsk.wpaPassPhrase, p, len);
    wpaPsk.passPhraseLen = len;
    S2w_Printf("\nComputing PSK from SSID and PassPhrase...\r\n");

    /* call the hal function to calculate the psk key from
       ssid and passphrase
     */
    /* Init crypto engine */
    GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
    
    AppS2wHal_WpaPskCompute(&wpaPsk );
    wpaPsk.pskValid =1;

    /*Disable crypto */
    GsnHeIf_DriverSuspend();

    
    /* update the current active profile
     */
    if(s2wappMainTaskCtxt->apConf)
    {
    	s2wCurrent.lmtdApConf.lmtdApPskValid =1;
	    memcpy(&(s2wCurrent.lmtdApConf.lmtdApPsk), &wpaPsk.psk,S2W_PSK_LEN);		
	    memcpy(&(s2wCurrent.lmtdApConf.passphrase.Passphrase), &wpaPsk.wpaPassPhrase,wpaPsk.passPhraseLen);		
		s2wCurrent.lmtdApConf.passphrase.Len=wpaPsk.passPhraseLen;
	}
	else
	{
    memcpy(&(s2wCurrent.security.wpa), &wpaPsk,sizeof(wpaPsk));
	}
  
    return S2W_SUCCESS;
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WPSK command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_Psk(UINT8 *ptr)
{
    UINT8 status;
    UINT8 psk[32];
    //GSN_WDD_WLAN_CFG_T *pWlanConfig;

    //pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    
    
    status = AppS2wParse_Psk(ptr,psk);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    
    //pWlanConfig->securityCfg.pskConfig.pskValid = 1;
    //memcpy(pWlanConfig->securityCfg.pskConfig.psk,psk,GSN_WDD_SEC_PMK_LEN);
    
    s2wCurrent.security.wpa.pskValid = 1;
    memcpy(s2wCurrent.security.wpa.psk,psk,GSN_WDD_SEC_PMK_LEN);

    return AppS2wHal_PskKeyStore(psk);
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WWEP Command.
 *   This function check the validity of parameter passed and
 *   update the active profile wep key.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Wwep(UINT8 *ptr)
{
    S2W_SECURITY_T params;
    UINT8 status;
    UINT8 idx,len=0;

    memcpy(&params, &s2wCurrent.security, sizeof(params));

    if (*ptr < '1' || *ptr > '4' || *(ptr + 1) != '=')
    {
        return S2W_EINVAL;
    }

    idx = *ptr - '0';

    /* Parse and validate the wep key.
     */
    // if the wep key set for ascii then parse it as ascii
    if(s2wWepKeyAscii)
    {
		len = strlen((char *)ptr+2);
		if ((len != 5) && (len != 13))
	    {
		    return S2W_EINVAL;
		}
		params.wep.keyLen[idx-1] = len;
        memcpy(params.wep.key[idx-1],ptr+2,len);
	}
	else
	{
        status = AppS2wParse_WepKey(ptr + 2, &params.wep, idx);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
	}

    params.wep.keyIdx = idx;
    params.validKeys |= S2W_SECURITY_VALID_WEP;

    if(s2wappMainTaskCtxt->apConf)// if Ap conf enabled then store in Ap conf
    {
        s2wCurrent.lmtdApConf.wepKeyConfig.KeyId = (params.wep.keyIdx);
        s2wCurrent.lmtdApConf.wepKeyConfig.KeyLen =(GSN_WDD_WEP_KEY_LEN_T) params.wep.keyLen[params.wep.keyIdx-1];
        memcpy(&s2wCurrent.lmtdApConf.wepKeyConfig.Key, params.wep.key[params.wep.keyIdx-1],
               params.wep.keyLen[params.wep.keyIdx-1]);
    }
    else
    {
        memcpy(&s2wCurrent.security, &params, sizeof(s2wCurrent.security));
    }
    return S2W_SUCCESS;
}

UINT8
AppS2wCmad_WsrvrValidationEn(UINT8 *ptr)
{
    UINT8 status;
    UINT32 val;
    BOOL skipValidation = 0;
    /* check the validity of parameter passed
     */
    status = AppS2wParse_Int(ptr, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    skipValidation = !val;

    GsnWdd_SkipSuppSrvValidation(skipValidation);

    return S2W_SUCCESS;
}

    
UINT8
AppS2wCmad_WeapTimeChk(UINT8 *ptr)
{
    UINT8 status;
    UINT32 val;
    /* check the validity of parameter passed
     */
    status = AppS2wParse_Int(ptr, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    s2wCurrent.eapCertTimeValidChkDisbl = !val;

    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_WwepConf(UINT8 *ptr)
{

	if(*ptr == '1')
	{
		s2wWepKeyAscii=1;
	}
	else if(*ptr == '0')
	{
		s2wWepKeyAscii=0;
	}
	else
	{
		return S2W_EINVAL;
	}
	return S2W_SUCCESS;


}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+RFFWREGDOMAIN Command.
 *   This function set the region information .
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_RegDomainSet(UINT8 *ptr)
{
    const char *region = "FCC";
    UINT32 domainId=0;
    UINT8 status = S2W_EINVAL,domain=0;
    S2W_FLASH_PARAMS_T s2wProfile;
    
    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        /* get the reg domain send it on serial interface
         */
        //status = AppS2wHal_RegDomainGet(&domain);
    //    AppCfg_Get( APP_CFG_REG_DOMAIN_ID, &domain );
	    if(!s2wappMainTaskCtxt->fsInit)
	    {
			App_FsInit();
			s2wappMainTaskCtxt->fsInit = TRUE;
	        f_enterFS();
		}
		if(s2wCurrent.mode == S2W_WLANDATA_MODE_AP)
		{
			domain = s2wCurrent.lmtdApConf.regDomain;
		}
		else
		{
	    	domain = s2wCurrent.regDomain;
		}

        switch (domain)
        {
            case S2W_DOMAIN_FCC:
                region = "FCC";
            break;

            case S2W_DOMAIN_ETSI:
                region = "ETSI";
            break;

            case S2W_DOMAIN_TELEC:
                region = "TELEC ";
            break;

            default:
            break;
        }
        S2w_Printf("\r\nREG_DOMAIN=%s\n",region);
        return S2W_SUCCESS;
    }
    status = AppS2wParse_Int(ptr, &domainId);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(domainId >= S2W_MAX_REG_DOMAIN)
    {
       return S2W_EINVAL;
    }
    domain = (UINT8)domainId;
	if(s2wCurrent.mode == S2W_WLANDATA_MODE_AP)
	{
		s2wCurrent.lmtdApConf.regDomain=domain;
	}
	else
	{
    	s2wCurrent.regDomain = domain;
	}
    
    s2wProfile.profile[0] =  s2wCurrent;
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
                f_enterFS();
	}
    status = S2w_SaveS2wProfile(&s2wProfile,0);
    if(status != S2W_SUCCESS)
      return S2W_FAILURE;
    
    return S2W_SUCCESS;
}


UINT8 AppS2wCmd_Wphymode(UINT8* ptr)
{
   UINT8 status = S2W_FAILURE;
   UINT8 *p;
   UINT32 temp;
   

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
      
      /* Call WDD API to get PHY mode */
      
      return status;
    }
    
      /* Set the PHY mode  */
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
  
    status = AppS2wParse_Int(p, &temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(temp >= 256)
    {
        return S2W_EINVAL;
    }
    /* Call WDD API to set PHY mode  */
    GsnWdd_PhyModeSet(&s2wappMainTaskCtxt->if0.wddCtx, (UINT8 )temp);
    return status;
    
}

#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD
S2W_OTA_FWUP_CONF_T OtaFwupConfParam;
UINT8
AppS2wCmd_OtaFwupConf(UINT8* ptr)
{
    UINT8* p;
    UINT32 id=0,port,flag=0, dnsErr = 0;
     UINT8 status = S2W_EINVAL;
     INT32 certID=-1;
     /* get the 1st parameter ID
     */
     p = AppS2wParse_NextParamGet(&ptr);
     if (!p)
     {
         return S2W_EINVAL;
     }
     status = AppS2wParse_Int(p, &id);
     if (status != S2W_SUCCESS)
     {
         return status;
     }
     p = AppS2wParse_NextParamGet(&ptr);
     if (!p)
     {
         return S2W_EINVAL;
     }
     switch(id)
     {
        case S2W_OTAFWUP_SRVRIP:
           //status = AppS2wParse_Ip(p, (UINT8 *) &OtaFwupConfParam.fwSrvIp);
           	if(inet_pton(AF_INET, (const char*)p, &OtaFwupConfParam.sockAddr.addr.ipv4.sin_addr.s_addr) == 1)
		    {
		        OtaFwupConfParam.sockAddr.addr.ipv4.sin_family = AF_INET;
		    }
		    else if(inet_pton(AF_INET6, (const char*)p, &OtaFwupConfParam.sockAddr.addr.ipv6.sin6_addr.s6_addr32) == 1)
		    {
		    	OtaFwupConfParam.sockAddr.addr.ipv6.sin6_family = AF_INET6;
		    }
		    else
		    {
               return S2W_EINVAL;
           	}
           break;
        case S2W_OTAFWUP_SRVRPORT:
           status = AppS2wParse_Int(p,(UINT32 *)&port);
           if (status != S2W_SUCCESS)
           {
               return status;
           }
           OtaFwupConfParam.sockAddr.ss_port = (UINT16)port;
           break;
        case S2W_OTAFWUP_PROXY_PRESENT:
           status = AppS2wParse_Int(p,&flag);
           if (status != S2W_SUCCESS)
           {
               return status;
           }
           OtaFwupConfParam.proxyFlag = flag;
           break;
        case S2W_OTAFWUP_PROXY_SRVRIP:
            if(! OtaFwupConfParam.proxyFlag)
            {
                return S2W_EINVAL;
            }
            //status = AppS2wParse_Ip(p, (UINT8 *) &OtaFwupConfParam.proxyIp);
            if(inet_pton(AF_INET, (const char*)p, &OtaFwupConfParam.proxySockAddr.addr.ipv4.sin_addr.s_addr) == 1)
            {
		        OtaFwupConfParam.proxySockAddr.addr.ipv4.sin_family = AF_INET;
		    }
		    else if(inet_pton(AF_INET6, (const char*)p, &OtaFwupConfParam.proxySockAddr.addr.ipv6.sin6_addr.s6_addr32) == 1)
		    {
		    	OtaFwupConfParam.proxySockAddr.addr.ipv6.sin6_family = AF_INET6;
		    }
		    else
		    {
               return S2W_EINVAL;
            }
            break;
        case S2W_OTAFWUP_PROXY_SRVRPORT:
            if(! OtaFwupConfParam.proxyFlag)
            {
                return S2W_EINVAL;
            }
            status = AppS2wParse_Int(p, (UINT32 *) &port);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            OtaFwupConfParam.proxySockAddr.ss_port = (UINT16)port;
            break;
        case S2W_OTAFWUP_SSL_ENABLED:
            status = AppS2wParse_Int(p,&flag);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            OtaFwupConfParam.sslFlag = flag;
            break;
        case S2W_OTAFWUP_CERT_NAME:
            if(! OtaFwupConfParam.sslFlag)
            {
                return S2W_EINVAL;
            }
            if(strlen((const char *)p) == 0)
            {
                OtaFwupConfParam.certAddr = NULL;
                return S2W_SUCCESS;
            }
            certID = S2wCert_SearchRamTable((INT8*)p);
            if(certID == -1)
            {
                certID = S2wCert_FlashFileLoad((INT8*)p);
            }
            if(certID != -1)
            {
                OtaFwupConfParam.certAddr = s2w_ssl_cert_table[certID].certAddress;
            }
            else
            {
                S2w_Printf("\n\rCertificate Not Found\n\r");
            }
        break;
        case S2W_OTAFWUP_APP_IMAGE_URL:
			/* Configure wlan url */
            if(OtaFwupConfParam.urls[S2W_OTAFU_URL_FW_IMAGE] != NULL)
                gsn_free(OtaFwupConfParam.urls[S2W_OTAFU_URL_FW_IMAGE]);
            OtaFwupConfParam.urls[S2W_OTAFU_URL_FW_IMAGE]= gsn_malloc(strlen((const char *)p)+1);
            strncpy((INT8 *)OtaFwupConfParam.urls[S2W_OTAFU_URL_FW_IMAGE],(const char *)p,strlen((const char *)p)+1);
        break;
		case S2W_OTAFWUP_APP_SIGN_URL:
			/* Configure wlan url */
            if(OtaFwupConfParam.urls[S2W_OTAFU_URL_SIGN_IMAGE] != NULL)
                gsn_free(OtaFwupConfParam.urls[S2W_OTAFU_URL_SIGN_IMAGE]);
            OtaFwupConfParam.urls[S2W_OTAFU_URL_SIGN_IMAGE]= gsn_malloc(strlen((const char *)p)+1);
            strncpy((INT8 *)OtaFwupConfParam.urls[S2W_OTAFU_URL_SIGN_IMAGE],(const char *)p,strlen((const char *)p)+1);
        break;
		case S2W_OTAFWUP_INFO_URL:
			/* Configure informational xml url */
			if(OtaFwupConfParam.urls[S2W_OTAFU_URL_XML] != NULL)
                gsn_free(OtaFwupConfParam.urls[S2W_OTAFU_URL_XML]);
            OtaFwupConfParam.urls[S2W_OTAFU_URL_XML]= gsn_malloc(strlen((const char *)p)+1);
            strncpy((INT8 *)OtaFwupConfParam.urls[S2W_OTAFU_URL_XML],(const char *)p,strlen((const char *)p)+1);
			break;
		case S2W_OTAFWUP_SRVR_HOST_NAME:
			/* Configure FWUP srver hostname */
			if(OtaFwupConfParam.fwSrvHostName != NULL)
				gsn_free(OtaFwupConfParam.fwSrvHostName);
			OtaFwupConfParam.fwSrvHostName = gsn_malloc(strlen((const char *)p)+1);
			memset(OtaFwupConfParam.fwSrvHostName, 0, strlen((const char *)p)+1);
			strcpy((INT8 *)OtaFwupConfParam.fwSrvHostName,(const char *)p);
			break;
		case S2W_OTAFWUP_APP_ENABLE_DNS_ERR:
            status = AppS2wParse_Int(p, &dnsErr);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            OtaFwupConfParam.dnsError = dnsErr;
            break;
       default:
            return S2W_EINVAL;
     }
     return status;
}

UINT8
AppS2wCmd_OtaFwupExtFlashStart(UINT8* ptr)
{
     UINT32 status;
#if defined(S2W_DFLT_HTTPC_AUTH) || defined(S2W_DFLT_HTTPC_HOST_IP)					
	 INT8 *pValue;
	 UINT32 len,i=0;
#endif		
     // check the fwup parameters are configured via cmd if not update with default
     if((OtaFwupConfParam.sockAddr.addr.ipv4.sin_addr.s_addr == 0) && (OtaFwupConfParam.proxySockAddr.addr.ipv4.sin_addr.s_addr == 0)
              && (OtaFwupConfParam.fwSrvHostName == NULL))
     {
         // update the deafult parameter
         OtaFwupConfParam.sockAddr.addr.ipv4.sin_addr.s_addr = htonl(S2W_DFLT_OTAFU_PULL_SRVR_IP);
#ifdef S2W_IPv6_SUPPORT
		OtaFwupConfParam.sockAddr.addr.ipv4.sin_family = AF_INET6;
#else
		OtaFwupConfParam.sockAddr.addr.ipv4.sin_family = AF_INET;
#endif
        OtaFwupConfParam.sockAddr.ss_port = S2W_DFLT_OTAFU_PULL_SRVR_PORT;
        OtaFwupConfParam.proxyFlag = S2W_DFLT_OTAFU_PULL_PROXY_SRVR;
#ifdef S2W_IPv6_SUPPORT		
		OtaFwupConfParam.proxySockAddr.addr.ipv4.sin_family = AF_INET6;
#else
		OtaFwupConfParam.proxySockAddr.addr.ipv4.sin_family = AF_INET;
#endif

         OtaFwupConfParam.sslFlag = S2W_DFLT_OTAFU_PULL_SSL;
        OtaFwupConfParam.proxySockAddr.addr.ipv4.sin_addr.s_addr = htonl(S2W_DFLT_OTAFU_PULL_PROXY_SRVR_IP);
         OtaFwupConfParam.proxySockAddr.ss_port = S2W_DFLT_OTAFU_PULL_PROXY_SRVR_PORT;
         OtaFwupConfParam.urls[S2W_OTAFU_URL_FW_IMAGE]= gsn_malloc(sizeof(S2W_DFLT_OTAFU_PULL_BIN_URL)+1);
         memcpy((INT8 *)OtaFwupConfParam.urls[S2W_OTAFU_URL_FW_IMAGE],S2W_DFLT_OTAFU_PULL_BIN_URL,sizeof(S2W_DFLT_OTAFU_PULL_BIN_URL));
		if((httpConfAtCmd != 1) &&(!httpConfInfo.reqHeaderCount))
		{
			memset(&headerTypes[0], GSN_HTTP_HEADER_INVAL, sizeof(headerTypes));
			memset(&headerValues[0], 0, sizeof(headerValues));
			httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
			httpConfInfo.reqHeaderTypes = (GSN_HTTP_USER_HEADER_TYPE_T *)headerTypesModified;
			httpConfInfo.reqHeaderValues = headerValues;
			httpConfInfo.reqHeaderCount = 0;
			// configure the header
#ifdef S2W_DFLT_HTTPC_AUTH			
			len= sizeof(S2W_DFLT_HTTPC_AUTH);
			pValue = gsn_malloc(len+1);
			if(pValue == NULL)
			{
				return S2W_FAILURE;
			}
			memset(pValue, 0 , len+1);
			memcpy(pValue, S2W_DFLT_HTTPC_AUTH, len);
			pValue[len] = '\0';
			headerValues[i] = pValue;
			headerTypes[i++] = GSN_HTTP_HEADER_AUTHORIZATION;
			httpConfInfo.reqHeaderCount++;
#endif
#ifdef S2W_DFLT_HTTPC_HOST_IP			
			len= sizeof(S2W_DFLT_HTTPC_HOST_IP);
			pValue = gsn_malloc(len+1);
			if(pValue == NULL)
			{
				return S2W_FAILURE;
			}
			memset(pValue, 0 , len+1);
			memcpy(pValue, (UINT8*)S2W_DFLT_HTTPC_HOST_IP, len);
			pValue[len] = '\0';
			headerValues[i] = pValue;
			headerTypes[i++] = (GSN_HTTP_USER_HEADER_TYPE_T)(GSN_HTTP_HEADER_HOST);
			httpConfInfo.reqHeaderCount++;
#endif			
		}
     
     }
     status = APPS2w_ExtFlashStart(&OtaFwupConfParam);

     if(status != GSN_SUCCESS)
        return S2W_FAILURE;
     else
        return S2W_SUCCESS;
}
#endif

#ifdef S2W_DNS_CLIENT
UINT8
AppS2wCmd_DnsServerSet(UINT8 *ptr)
{
  
  UINT8 *p,status,index=0;
#ifdef S2W_IPv6_SUPPORT
  UINT32 IPv6[4],IPv6AddrType;
#endif
  S2W_IPADDR_T IPv4;
   
 while(((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL) && (index < 2))
 {
    status = AppS2wParse_Ip(p,IPv4);
      
    if (status == S2W_SUCCESS)
    {
      DNSv4ServerAddr[index] = (IPv4[0] << 24 | IPv4[1] << 16 | IPv4[2] << 8 | IPv4[3]);

      GsnNwif_DnsServerAdd(&s2wappMainTaskCtxt->if0.nwifCtx,DNSv4ServerAddr[index],index);

      S2W_DNS_CLIENT_FALGS |= S2W_DNSv4_SERVER_SET;
    }

#ifdef S2W_IPv6_SUPPORT
    else   /* Check for IPv6 address  */
    {
      status = inet_pton(AF_INET6, (const char*)p, (VOID*)IPv6);
        if(status != TRUE)
        return S2W_EINVAL;

        GSN_IPv6_CHANGE_ENDIAN(IPv6);


      IPv6AddrType = GSN_IPv6_ADDR_TYPE(IPv6);
  
      switch(IPv6AddrType)
      {
    
    
        case GSN_IPv6_LINK_LOCAL:
        case GSN_IPv6_GLOBAL:
          
           /* Clear the previous DNSv6 server */
            nxd_dns_server_remove(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,&DNSv6ServerAddr[index]);

            DNSv6ServerAddr[index].nxd_ip_version = 0x6;
            DNSv6ServerAddr[index].nxd_ip_address.v6[0] = IPv6[0];
            DNSv6ServerAddr[index].nxd_ip_address.v6[1] = IPv6[1];
            DNSv6ServerAddr[index].nxd_ip_address.v6[2] = IPv6[2];
            DNSv6ServerAddr[index].nxd_ip_address.v6[3] = IPv6[3];

            status = nxd_dns_server_add(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl, &DNSv6ServerAddr[index]);
            if (status != S2W_SUCCESS)
              return S2W_FAILURE;
            S2W_DNS_CLIENT_FALGS |= S2W_DNSv6_SERVER_SET;
            break;
          
        default:
            return S2W_EINVAL;
      }
    }
#endif //S2W_IPv6_SUPPORT   
    index++;
 }

    GsnNwif_DnsServerGet(&s2wappMainTaskCtxt->if0.nwifCtx,(ULONG*)s2wCurrent.dns1,GSN_PRIMARY_DNS_SERVER);
    GsnNwif_DnsServerGet(&s2wappMainTaskCtxt->if0.nwifCtx,(ULONG*)s2wCurrent.dns2,GSN_SECONDARY_DNS_SERVER);

    S2W_DNS_CLIENT_FALGS |= S2W_DNS_CLIENT_ENABLED;
#ifdef S2W_DHCP_SERVER_ENABLE
    /* Restart DHCP server */
    if(dhcpServerFlags & S2W_DHCP_SRVR_ENABLED)
    {
      UINT8 buff[8]={0};
      sprintf((char*)buff,"%d",1);
      GsnDhcpSrvr_Stop(&dhcpSrvr);
      dhcpServerFlags &= 0xfe;
      AppS2wCmd_DhcpSrvr(buff);
    }
#endif
    if(index > 2)
      return S2W_FAILURE;
    
    return S2W_SUCCESS;
}


UINT8
AppS2wCmd_DnsLookup(UINT8 *ptr)
{
   UINT8 *p,status,*temp;
   ULONG hostIpAddress;
   UINT32 retries=0,timeout=0,clearCache;

   if(s2wLinkState != S2W_LINK_STATE_CONNECTED)
     return S2W_FAILURE;
  
   
   p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
      if(p == NULL)
      return S2W_FAILURE;
	temp = p;
  
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(p != NULL)
    {
  
      status = AppS2wParse_Int(p, &retries);
      if (status != S2W_SUCCESS)
        return S2W_EINVAL;
    }
    
    retries = (retries) ? retries : S2W_DNS_REQ_DEF_RETRIES;
    
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(p != NULL)
    {  
      status = AppS2wParse_Int(p, &timeout);
      if (status != S2W_SUCCESS)
        return S2W_EINVAL;
    }
    
    timeout = (timeout) ? timeout : S2W_DNS_REQ_DEF_TIME_OUT;
    
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(p != NULL)
    {
      /* Netx Doesnt have any cache */
      status = AppS2wParse_Int(p, &clearCache);
      if (status != S2W_SUCCESS)
        return S2W_EINVAL;
    }
    GsnNwIf_DnsRetryCountSet(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,retries);
   status = GsnNwIf_DnsHostByNameGet(&s2wappMainTaskCtxt->if0.nwifCtx, (UINT8*)temp, &hostIpAddress, timeout);

    if (status != S2W_SUCCESS || hostIpAddress == 0)
      return S2W_FAILURE;

  
    S2w_Printf("\r\nIP:%d.%d.%d.%d\r",(hostIpAddress & 0xff000000)>>24,(hostIpAddress & 0x00ff0000)>>16,(hostIpAddress & 0x0000ff00)>>8,(hostIpAddress & 0x000000ff));
    
    return S2W_SUCCESS;
}


#ifdef S2W_IPv6_SUPPORT
UINT8
AppS2wCmd_DnsLookupv6(UINT8 *ptr)
{
   UINT8 *p,status,*temp;
   //ULONG hostIpAddress;
   UINT32 retry,timeout,clearCache;
   GSN_NWIF_IP_CONFIG_T nwParams;
   NXD_ADDRESS     host_ipduo_address;

   
   
    if(!(S2W_DNS_CLIENT_FALGS & S2W_DNS_CLIENT_ENABLED))
    {

      S2W_DNS_CLIENT_FALGS |= S2W_DNS_CLIENT_ENABLED;
    }
    
    if(!(S2W_DNS_CLIENT_FALGS & S2W_DNSv6_SERVER_SET))
    {
      
      GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);

       nxd_dns_server_remove(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,&DNSv6ServerAddr[0]);
       nxd_dns_server_remove(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,&DNSv6ServerAddr[1]);

            DNSv6ServerAddr[0].nxd_ip_version = 0x6;
            DNSv6ServerAddr[0].nxd_ip_address.v6[0] = nwParams.ipv6.primaryDnsSrvrAddr[0];
            DNSv6ServerAddr[0].nxd_ip_address.v6[1] = nwParams.ipv6.primaryDnsSrvrAddr[1];
            DNSv6ServerAddr[0].nxd_ip_address.v6[2] = nwParams.ipv6.primaryDnsSrvrAddr[2];
            DNSv6ServerAddr[0].nxd_ip_address.v6[3] = nwParams.ipv6.primaryDnsSrvrAddr[3];
            
            
            DNSv6ServerAddr[1].nxd_ip_version = 0x6;
            DNSv6ServerAddr[1].nxd_ip_address.v6[0] = nwParams.ipv6.secndryDnsSrvrAddr[0];
            DNSv6ServerAddr[1].nxd_ip_address.v6[1] = nwParams.ipv6.secndryDnsSrvrAddr[1];
            DNSv6ServerAddr[1].nxd_ip_address.v6[2] = nwParams.ipv6.secndryDnsSrvrAddr[2];
            DNSv6ServerAddr[1].nxd_ip_address.v6[3] = nwParams.ipv6.secndryDnsSrvrAddr[3];

            status = nxd_dns_server_add(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl, &DNSv6ServerAddr[0]);
            status = nxd_dns_server_add(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl, &DNSv6ServerAddr[1]);

        S2W_DNS_CLIENT_FALGS |= S2W_DNSv6_SERVER_SET;
    }
    
   
   temp = ptr;
   p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
  
  
    if(p == NULL)
      return S2W_FAILURE;
  
    if(!(S2W_DNS_CLIENT_FALGS & S2W_DNSv4_SERVER_SET))
     return S2W_FAILURE;
  
    
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(p != NULL)
    {
  
      /* Netx API doesnt support this. Use this when available. */
      status = AppS2wParse_Int(p, &retry);
      if (status != S2W_SUCCESS)
        return S2W_EINVAL;
    }
    
    timeout = S2W_DNS_REQ_DEF_TIME_OUT;
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(p != NULL)
    {  
      status = AppS2wParse_Int(p, &timeout);
      if (status != S2W_SUCCESS)
        return S2W_EINVAL;
    }
    
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(p != NULL)
    {
      /* Netx Doesnt have any cache */
      status = AppS2wParse_Int(p, &clearCache);
      if (status != S2W_SUCCESS)
        return S2W_EINVAL;
    }


    status = nxd_dns_host_by_name_get(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,(UINT8*)temp, &host_ipduo_address, timeout*100, 0x6);
    if (status != S2W_SUCCESS)
    return S2W_FAILURE;

    S2w_Printf("\r\n%x:%x:%x:%x:%x:%x:%x:%x\r\n",*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+1),*((UINT16*)host_ipduo_address.nxd_ip_address.v6),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+3),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+2),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+5),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+4),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+7),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+6));    
    
    return S2W_SUCCESS;
}

#endif
#endif //S2W_DNS_CLIENT

UINT8
AppS2wCmd_PowerSaveStby(UINT8 *ptr)
{
    UINT8 status;
    UINT32 dtime=0;
    ULONG64 time=0;
    S2W_ALARM_INFO_T alarm;
    UINT8 *p;
    memset(&alarm,0,sizeof(S2W_ALARM_INFO_T));
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_64BitNumber(p, &time);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    memset(&alarm,0,sizeof(alarm));
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
        if (*p != '\0')
        {
            status = AppS2wParse_Int(p, &dtime);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
        }

        p = AppS2wParse_NextParamGet(&ptr);
        if (p)
        {
            if (*p != '\0')
            {
                status = AppS2wParse_Boolean(p, &(alarm.alarm1Pol));
                if (status != S2W_SUCCESS)
                {
                    return status;
                }
                alarm.alarm1Valid = 1;

            }
            p = AppS2wParse_NextParamGet(&ptr);
            if (p)
            {
                if (*p != '\0')
                {
                    status = AppS2wParse_Boolean(p, &(alarm.alarm2Pol));
                    if (status != S2W_SUCCESS)
                    {
                        return status;
                    }
                    alarm.alarm2Valid = 1;
                }
            }

        }

    }
    status = AppS2wHal_PsStbyRequest(time, dtime, &alarm);
    if(status == S2W_SUCCESS)
    {
        stbySuccess =1;
    }
    return status;

}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w nw context store function.
 *    This function sores the nw context to the flash Basically this
      function stores both L2 and L3 layer information..
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_LINK_LOST_EVT - operation failure- not connected to wlan.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_NwConnStore(UINT8 *ptr)
{
	if (*ptr)
		 return S2W_EINVAL;
	else 
		 return AppS2wHal_NwContextStore();

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w nw context restore function.
 *    This function restore the nw connection. This function initialize the
 *    L3 layer with the parameter stored in the flash by store function.
 *    This function is useful to connect to the wlan without association after
      the system comes out from standby.
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_FAILURE - operation failure.
 ******************************************************************/
 
PUBLIC UINT8
AppS2wCmd_NwConnRestore(UINT8 *ptr)
{
	if (*ptr)
		 return S2W_EINVAL;
	 else
		 return AppS2wHal_NwContextRestore();

        }



#ifdef  S2W_NCM_SUPPORT_ENABLE
UINT32 ncmautoconnectcount=0;
BOOL ncmAutoMode=0;
VOID 
AppS2w_NcmL3ConnProcess()
	
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	GSN_NWIF_IP_CONFIG_T nwParams;
	UINT32 message;
	GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
	/* 
	 	check the ip  is same as old one . And current ip address is not zero 
	*/
	if(((s2wappMainTaskCtxt->ipaddr!=nwParams.ipv4.ipAddr) ||
		(s2wappMainTaskCtxt->subnetMask !=nwParams.ipv4.subnetMask))
		 &&((s2wappMainTaskCtxt->ipaddr != 0) && (s2wappMainTaskCtxt->subnetMask != 0))   
	)
	{
		// update the values first
		s2wappMainTaskCtxt->ipaddr = nwParams.ipv4.ipAddr;
		s2wappMainTaskCtxt->subnetMask = nwParams.ipv4.subnetMask;
		if(s2wappMainTaskCtxt->dpSleep )
		{
			AppS2w_ExitDpSleep();
		}
		/*
			if roaming cfg is to keep L4 connection , then invoke seperate status notify API
		*/
#ifdef S2W_NCM_ROAMING_SUPPORT 
		if(s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.roamEnable == 1 &&
   	 		s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.maintainL4Con == 1)			   	\
			AppS2wRoam_SatusNotify(S2W_ENEWIP,S2W_ASYNC_DHCP_NEW_IP);
		else		
#endif
			AppS2wProcess_DhcpIpChangeNotify();
	 }
	 else 
	 {	
     	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
		if(!s2wAutoConnState )
    	{
			AppS2wHdrAndIpv4_Print();
    	}			
		if(pAppRtcLtchInfo->arpCacheEn && pAppRtcLtchInfo->arpRecCount != 0 )
			nx_arp_table_set(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl, &pAppRtcLtchInfo->arpTablebuf[0], 
							pAppRtcLtchInfo->arpRecCount);
    	 nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,GratiousArpHandler);
		 
   	 	if((!s2wAutoConnState ) &&( !profile_params.autoConnect))
    	{
   	 
#ifdef S2W_ASYNC_MSG           
            if(s2wCurrent.asyncMsgFormat)
            {
                 S2w_Printf("\r\n");
                 AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_ASSO_SUCCESS_MSG, 0);
            }
            else
#endif
            {
                 AppS2wProcess_StatusNotify(S2W_ASSO_SUCCESS_MSG, 0);
        	}
		}
		GsnOsal_SemRelease(&s2wSyncSemID);
	}
            
    // before start the L4 connection for AP mode start the dhcp/dns server
    if(ncmAutoMode)// AP mode
    {
         s2w_StartDhcpDnsServer();
	}
	if(s2wCurrent.ncmAutoLvl)
	{
       message = APP_EVENT_NCM_L4CONNECT;
	   /*
	   		Bug FIX 5511 - Enhanced Auto connection: L4 timeout gives ERROR message to the MCU
	   		Made auto connection l4 connection retey count to infinite  and never decremts the counter

	   */
	   if(1 == profile_params.autoConnect)
	   {
		   ncmautoconnectcount = S2W_AUTO_CONCT_L4RETRY_INFINITE;
	   }
	   else
	   {
       ncmautoconnectcount = s2wCurrent.registers[S2W_NCM_AUTO_L4_RETRY];
	   }
       (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
	}

#ifdef S2W_NCM_ROAMING_SUPPORT 
	if(s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.roamEnable)
  	{	    
		GsnNcm_RoamStart(&s2wappMainTaskCtxt->appNwConnMgrCtx,s2wCurrent.regDomain);
  	}
#endif /* S2W_NCM_ROAMING_SUPPORT */
	if(pAppRtcLtchInfo->grpProvVerify == 1)
	{
		message = APP_EVENT_GRPPROV_VERIFICATION;
		(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
	}
	/*Set dns server ip*/
	if((0 == ncmAutoMode) && (1 == nwParams.ipv4.staticIp))
	{
		UINT32 dnsSrvrAddr;

		dnsSrvrAddr  = s2wCurrent.dns1[3] << 24 | s2wCurrent.dns1[2] << 16 |
						s2wCurrent.dns1[1] << 8 | s2wCurrent.dns1[0];
		
		GsnNwif_DnsServerAdd(&s2wappMainTaskCtxt->if0.nwifCtx, dnsSrvrAddr , 0);

		dnsSrvrAddr  = s2wCurrent.dns2[3] << 24 | s2wCurrent.dns2[2] << 16 |
						s2wCurrent.dns2[1] << 8 | s2wCurrent.dns2[0];

		GsnNwif_DnsServerAdd(&s2wappMainTaskCtxt->if0.nwifCtx, dnsSrvrAddr , 1);
	}
}	

VOID
AppS2wNetConnMgr_Cb(VOID* ctext, VOID* pNcm, GSN_NCM_NOTIF_ID_T status)
{
	//APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    switch(status)
    {
        case GSN_NCM_NOTIF_ID_L2_CONNECTED:
        {
            s2wLinkState = S2W_LINK_STATE_CONNECTED;
#if 0
            if(ncmAutoMode == 0) // client case only
            {
                if(appRtcMemData.KeepAliveIntrvl == 0)
                {
                    appRtcMemData.KeepAliveIntrvl = S2W_DEFAULT_KEEP_ALIVE_INTRVL;
                }
                AppS2wHal_PsPollIntervelset(appRtcMemData.KeepAliveIntrvl);
            }
#endif
			UINT32 message = APP_EVENT_NCM_L2CONNECT;
			(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
        }
        break;
        case GSN_NCM_NOTIF_ID_L2_CONNECT_FAIL:
        break;
        case GSN_NCM_NOTIF_ID_L2_DISCONNECTED:

        {
			s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
           	if(s2wappMainTaskCtxt->dpSleep )
           	{
           		AppS2w_ExitDpSleep();
           	}
           	if(s2wCurrent.ncmAutoLvl == 1)
           		AppS2wHal_TimerStop(&acNcmTimer);
           // if auto connection is up then make the gpio 19 low
            if((s2wAutoConnState ) && (s2wIsAutoconnected))
            {
                 S2w_AsyncMsgGpioOp(0);
			}
		   	/*
		   		if roaming is enable and l4 maintain flag is set then donot close l4 connections,
		   	*/
#ifdef S2W_NCM_ROAMING_SUPPORT            
		  	if(s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.roamEnable == 1 &&
		   	  s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.maintainL4Con == 1)			   	
		  	{	
				AppS2wRoam_SatusNotify(S2W_DISASSO_EVT,S2W_ASYNC_DISASSO_EVT);
		 	}
		  	else
#endif                          
			{
	           AppS2wProcess_EventNotify(0);
			}	
			s2wappMainTaskCtxt->ipaddr =0;
			s2wappMainTaskCtxt->subnetMask=0;
			/* in Limites Ap mode stop the dhcp/dns servers
			 */
			if(ncmAutoMode)// AP mode
			{
#ifdef S2W_DHCP_SERVER_ENABLE
                GsnDhcpSrvr_Stop(&dhcpSrvr);
#ifdef S2W_DNS_SERVER_ENABLE
                GsnDnsSrvr_Stop(&dnsServer);
#endif
#endif
	        }
        }

        break;
        
        case GSN_NCM_NOTIF_ID_DHCP_STOP:
          {
          
           //AppMainCtx_TaskNotify(APP_EVENT_DHCP_STOP_REQUEST);
          }          
          break;
        case GSN_NCM_NOTIF_ID_L3_CONNECTED:
	        AppS2w_NcmL3ConnProcess();
    	    break;
        case GSN_NCM_NOTIF_ID_L3_DISCONNECTED:
    	{
            if(s2wappMainTaskCtxt->dpSleep )
            {
            	AppS2w_ExitDpSleep();
            }
#ifdef S2W_NCM_ROAMING_SUPPORT             
			if(s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.roamEnable == 1 &&
		   		s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.maintainL4Con == 1)			   	
		  	{
		  		AppS2wRoam_SatusNotify(S2W_ENEWIP,S2W_ASYNC_DHCP_NEW_IP);
		  	}
		  	else	
#endif                          
			{
	            AppS2wProcess_DhcpFailNotify();
				s2wappMainTaskCtxt->ipaddr=0;
				s2wappMainTaskCtxt->subnetMask=0;
			}
		}
        break;
		case GSN_NCM_NOTIF_ID_L3_RENEWSUCCESS :
        {
			GSN_NWIF_IP_CONFIG_T nwParams;
			GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
			/* 
			 	check the ip  is same as old one . And current ip address is not zero 
			*/
			if(s2wappMainTaskCtxt->dpSleep )
			{
				AppS2w_ExitDpSleep();
			}
		
			if(((s2wappMainTaskCtxt->ipaddr!=nwParams.ipv4.ipAddr) ||
				(s2wappMainTaskCtxt->subnetMask !=nwParams.ipv4.subnetMask))
				 &&((s2wappMainTaskCtxt->ipaddr != 0) && (s2wappMainTaskCtxt->subnetMask != 0))   
			)
			{
				// update the values first
				s2wappMainTaskCtxt->ipaddr = nwParams.ipv4.ipAddr;
				s2wappMainTaskCtxt->subnetMask = nwParams.ipv4.subnetMask;
				/*
					if roaming cfg is to keep L4 connection , then invoke seperate status notify API
				*/
#ifdef S2W_NCM_ROAMING_SUPPORT 
				if(s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.roamEnable == 1 &&
		   	 		s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.maintainL4Con == 1)			   	\
					AppS2wRoam_SatusNotify(S2W_ENEWIP,S2W_ASYNC_DHCP_NEW_IP);
				else		
#endif
					AppS2wProcess_DhcpIpChangeNotify();
			 
				 
				if(s2wCurrent.ncmAutoLvl)
				{
                   UINT32 message = APP_EVENT_NCM_L4CONNECT;
					/*
						 Bug FIX 5511 - Enhanced Auto connection: L4 timeout gives ERROR message to the MCU
						 Made auto connection l4 connection retey count to infinite  and never decremts the counter
					
					*/
				   	if(1 == profile_params.autoConnect)
				   	{
					   ncmautoconnectcount = S2W_AUTO_CONCT_L4RETRY_INFINITE;
				   	}
				   	else
				   	{
                   		ncmautoconnectcount = s2wCurrent.registers[S2W_NCM_AUTO_L4_RETRY];
				   	}
                    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
				}
				break;
              }
			  /*
			  	incase of previous renew were failure , start the L4 connect process.
			   */	
			  else if((s2wappMainTaskCtxt->ipaddr == 0) && (s2wappMainTaskCtxt->subnetMask == 0))
			  {
				  s2wappMainTaskCtxt->ipaddr = nwParams.ipv4.ipAddr;
				  s2wappMainTaskCtxt->subnetMask = nwParams.ipv4.subnetMask;
				  if(s2wCurrent.ncmAutoLvl)
			  	  {
				 	UINT32 message = APP_EVENT_NCM_L4CONNECT;
						/*
							 Bug FIX 5511 - Enhanced Auto connection: L4 timeout gives ERROR message to the MCU
							 Made auto connection l4 connection retey count to infinite  and never decremts the counter
						
						*/
						
					   	if(1 == profile_params.autoConnect)
					   	{
						   ncmautoconnectcount = S2W_AUTO_CONCT_L4RETRY_INFINITE;
					   	}
					   	else
				   		{
                   			ncmautoconnectcount = s2wCurrent.registers[S2W_NCM_AUTO_L4_RETRY];
				   		}
                    	(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
				  }
			  }
		}
        break;
		case GSN_NCM_NOTIF_ID_L3_CONNECT_FAIL:
    	{
            if(s2wappMainTaskCtxt->dpSleep )
            {
            	AppS2w_ExitDpSleep();
            }
		   	/*
		   		if roaming is enable and l4 maintain flag is set then donot close l4 connections,
		   	*/
#ifdef S2W_NCM_ROAMING_SUPPORT             
			if(s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.roamEnable == 1 &&
		   		s2wappMainTaskCtxt->appNwConnMgrCtx.config.roamingCfgParams.maintainL4Con == 1)			   	
		  	{
				AppS2wRoam_SatusNotify(S2W_ENOIP,S2W_ASYNC_DHCP_FAIL_EVT);			
		  	}
		  	else	
#endif                          
			{
				s2wappMainTaskCtxt->ipaddr=0;
				s2wappMainTaskCtxt->subnetMask=0;
				// fix for issue no:5051, make the gpio 19 low for auto mode
				if((s2wAutoConnState ) && (s2wIsAutoconnected))
			    {
				    S2w_AsyncMsgGpioOp(0);
			    }
	            AppS2wProcess_DhcpFailNotify();
			}
		break;
		}
		case GSN_NCM_NOTIF_ID_STOP:
			GsnOsal_SemRelease(&s2wappMainTaskCtxt->ncmOpsync);
        break;
#if 0
        case GSN_NCM_L3CONNECT_FAILURE:
        break;
        case GSN_NCM_L3RENEW_SUCCESS:
             GsnNwIf_GratArpSend(&s2wappMainTaskCtxt->nwIf);
        break;
        case GSN_NCM_CPU_WAIT_DELAY:
        break;
        case GSN_NCM_GO_PS_MODE:
        break;
        case GSN_NCM_PROVISIONING:
        break;
#endif
    }
}
UINT8
AppS2wCmd_NcmAuto(UINT8* ptr)
{
    UINT8 status;
    UINT8 *p,macStr[GSN_NWIF_HOST_NAME_MAX_LEN + 1];;
    BOOL  enable=0,value =0;
    GSN_NCM_CONFIG_T gNwConnConfig;
    UINT8 mac[6],macAddr[6];
	INT32 index;
	GSN_STATUS retVal; 
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();	
	//APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();

    // to get the current status
    if (ptr[0] == '?' && ptr[1] == '\0')
    {
         if(s2wappMainTaskCtxt->appNwConnMgrCtx.state != GSN_NCM_STATE_INITIALISED)// ncm started
         {
             S2w_Printf("\r\nNCM STARTED:%d\r\n",s2wappMainTaskCtxt->appNwConnMgrCtx.state);
         }
         else
         {
             S2w_Printf("\r\nNCM NOT STARTED\r\n");
         }
         return S2W_SUCCESS;
    }
    else if(ptr[0] == '?' &&( ptr[1] == '?') && ptr[2] == '\0')
    {
		AppS2wNcmProfile_Display( &s2wCurrent);
		return S2W_SUCCESS;
	}

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &ncmAutoMode);
    if (status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &enable);
    if (status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }
    s2wCurrent.ncmAutoMgr = enable;
	
    if(enable == 0)//disable the connection mgr and disconnect if it connected
    {
		s2wappMainTaskCtxt->ipaddr =0;
		s2wappMainTaskCtxt->subnetMask=0;
        s2wCurrent.ncmAutoMgr = 0;
        s2wCurrent.ncmAutoLvl = 0;
        s2wAutoConnState = 0;
        retVal = GsnNcm_Stop(&s2wappMainTaskCtxt->appNwConnMgrCtx,NULL);
		if (GSN_OPERATION_IN_PROGRESS == retVal)
		{
			GsnOsal_SemAcquire(&s2wappMainTaskCtxt->ncmOpsync,GSN_OSAL_WAIT_FOREVER);
		}
        // stop the s2w ncm timer
        AppS2wHal_TimerStop(&acNcmTimer);
        //AppS2wHal_Register(s2wappMainTaskCtxt->taskNotifier, s2wappMainTaskCtxt);
        // register the normal CB for disso-event and syncloss
        GsnWdd_DisassocIndCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocCb, s2wappMainTaskCtxt);
        GsnWdd_BeaconMissCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocSyncLossCb, s2wappMainTaskCtxt);
        GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,S2W_DEFAULT_SYNCLOSS_INTERVAL);
        AppS2w_HangUp();
        S2w_AsyncMsgGpioOp(0);
        if(ncmAutoMode)// ap mode stop the dhcp srvr
        {
#ifdef S2W_DHCP_SERVER_ENABLE
            GsnDhcpSrvr_Stop(&dhcpSrvr);
#ifdef S2W_DNS_SERVER_ENABLE
            GsnDnsSrvr_Stop(&dnsServer);
#endif
#endif
        }
        return status;
    }
    memset(&gNwConnConfig,0, sizeof(gNwConnConfig));

    if(ncmAutoMode) // start the AP with the nvds info..
    {
		/* next param(level) is an optional for AP mode
		 */
        p = AppS2wParse_NextParamGet(&ptr);
	    if ((p) && (*p != '\0'))
	    {
	        status = AppS2wParse_Boolean(p, &value);
	        if (status != S2W_SUCCESS)
	        {
	            return status;
	        }
            s2wCurrent.ncmAutoLvl = value;
		}
        // for grp provisioning the following code get executed
        if(s2wCurrent.mode == S2W_WLANDATA_MODE_PROV_AP)
        {
             gNwConnConfig.wlanCfg.apSpecificCfg.beaconInterval = S2W_DEFAULT_GRP_PROV_BEACON_INTERVAL;
             gNwConnConfig.wlanCfg.ssid.length = sizeof(S2W_DEFAULT_GRP_PROV_SSID) - 1;;
             memcpy(gNwConnConfig.wlanCfg.ssid.array, S2W_DEFAULT_GRP_PROV_SSID,
                     gNwConnConfig.wlanCfg.ssid.length);

             sprintf((char*)gNwConnConfig.wlanCfg.ssid.array+gNwConnConfig.wlanCfg.ssid.length, "_%02x%02x%02x",
            		s2wCurrent.lmtdApConf.macAddr.array[3],
            		s2wCurrent.lmtdApConf.macAddr.array[4],
            		s2wCurrent.lmtdApConf.macAddr.array[5]);

             gNwConnConfig.wlanCfg.ssid.length += 7;

             gNwConnConfig.wlanCfg.channel[0] = S2W_DEFAULT_GRP_PROV_CHANNEL;
             gNwConnConfig.wlanCfg.channel[1] = 0;
             S2w_getApSecurityConfig(&gNwConnConfig.wlanCfg,S2W_DEFAULT_GRP_PROV_SECURITY);

             gNwConnConfig.ipConfig.flag =  GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
             gNwConnConfig.ipConfig.ipv4.staticIp = 1;//nwMib.staticIp;
             gNwConnConfig.ipConfig.ipv4.ipAddr = S2W_DEFAULT_GRP_PROV_IP_ADDRESS;
             gNwConnConfig.ipConfig.ipv4.subnetMask = S2W_DEFAULT_GRP_PROV_SUBNET_ADDRESS;
             gNwConnConfig.ipConfig.ipv4.gatewayIpAddr = S2W_DEFAULT_GRP_PROV_GATE_ADDRESS;
             memcpy(gNwConnConfig.wlanCfg.bssid.array, s2wCurrent.lmtdApConf.macAddr.array,6);
             GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
        }
        else
        {
			gNwConnConfig.wlanCfg.apSpecificCfg.beaconInterval = s2wCurrent.lmtdApConf.beaconInterval;
				gNwConnConfig.wlanCfg.apSpecificCfg.hiddenSsid = s2wCurrent.ncmAutoConf[S2W_NCM_HIDDENSSID_VALUE];
			
			if(s2wCurrent.ncmAutoConf[S2W_NCM_DTIMPERIOD_VALUE])
			{
				gNwConnConfig.wlanCfg.apSpecificCfg.dtimPeriod= s2wCurrent.ncmAutoConf[S2W_NCM_DTIMPERIOD_VALUE];
			}
			else
			{
				gNwConnConfig.wlanCfg.apSpecificCfg.dtimPeriod= S2W_NCM_DFLT_DTIMPERIOD_VALUE;
			}
			
			if(s2wCurrent.ncmAutoConf[S2W_NCM_INACTIVITY_TMEOUT_VALUE])
			{
				gNwConnConfig.inactivityTimeoutInSec= s2wCurrent.ncmAutoConf[S2W_NCM_INACTIVITY_TMEOUT_VALUE];
			}
			else
			{
				gNwConnConfig.inactivityTimeoutInSec= S2W_NCM_DFLT_INACTIVITY_TMEOUT_VALUE;
			}			
			if(s2wCurrent.ncmAutoConf[S2W_NCM_GRP_KEY_UPDATE_INTERVAL])
			{
				gNwConnConfig.groupKeyUpdateTime= s2wCurrent.ncmAutoConf[S2W_NCM_GRP_KEY_UPDATE_INTERVAL];
			}
			else
			{
				gNwConnConfig.groupKeyUpdateTime = S2W_NCM_DFLT_GRP_KEY_UPDATE_INTERVAL;
			}
			gNwConnConfig.wlanCfg.ssid.length = s2wCurrent.lmtdApConf.ssid.length;
			memcpy(gNwConnConfig.wlanCfg.ssid.array, s2wCurrent.lmtdApConf.ssid.array,
			  s2wCurrent.lmtdApConf.ssid.length);
			gNwConnConfig.wlanCfg.channel[0] = s2wCurrent.lmtdApConf.channel;
			S2w_getApSecurityConfig(&gNwConnConfig.wlanCfg,s2wCurrent.lmtdApConf.securityType);

			gNwConnConfig.ipConfig.flag =  GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
			gNwConnConfig.ipConfig.ipv4.staticIp = 1;//nwMib.staticIp;
			memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.ipAddr,&s2wCurrent.lmtdApConf.ipAddress,4 );
			memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.subnetMask,&s2wCurrent.lmtdApConf.subnetmask,4 );
			memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.gatewayIpAddr,&s2wCurrent.lmtdApConf.gateway,4 );
			memcpy(gNwConnConfig.wlanCfg.bssid.array, s2wCurrent.lmtdApConf.macAddr.array,6);
			GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
    	}
    }
    else
    {
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &value);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wCurrent.ncmAutoLvl = value;
		// new optional parameter to save the ncm to profile or not..default is yes but by setting this to 1 user can disable it
   		p = AppS2wParse_NextParamGet(&ptr);
    	if ((p) && (*p != '\0'))
    	{
        	status = AppS2wParse_Boolean(p, &s2wappMainTaskCtxt->ncmAutoConStoreProfile);
        	if (status != S2W_SUCCESS)
        	{
           		return status;
        	}
		}
    gNwConnConfig.wlanCfg.ssid.length = s2wCurrent.autoWlandata.ssidLen;
    memcpy(gNwConnConfig.wlanCfg.ssid.array,s2wCurrent.autoWlandata.ssid,s2wCurrent.autoWlandata.ssidLen);
    gNwConnConfig.regDomain =  s2wCurrent.regDomain; 
	if(s2wCurrent.autoWlandata.validBssid)
	{
			memcpy((INT8 *)gNwConnConfig.wlanCfg.bssid.array,s2wCurrent.autoWlandata.bssid,S2W_MAC_ADDR_SIZE);
					
	}
		
    if(s2wCurrent.autoWlandata.channel)
      gNwConnConfig.wlanCfg.channel[0] = s2wCurrent.autoWlandata.channel;
    else
      {
            gNwConnConfig.wlanCfg.channel[0] = 1;
            gNwConnConfig.wlanCfg.channel[1] = 2;
            gNwConnConfig.wlanCfg.channel[2] = 3;
            gNwConnConfig.wlanCfg.channel[3] = 4;
            gNwConnConfig.wlanCfg.channel[4] = 5;
            gNwConnConfig.wlanCfg.channel[5] = 6;
            gNwConnConfig.wlanCfg.channel[6] = 7;
            gNwConnConfig.wlanCfg.channel[7] = 8;
            gNwConnConfig.wlanCfg.channel[8] = 9;
            gNwConnConfig.wlanCfg.channel[9] = 10;
            gNwConnConfig.wlanCfg.channel[10] = 11;
            switch(s2wCurrent.regDomain)
            {
		case S2W_DOMAIN_FCC:
                  gNwConnConfig.wlanCfg.channel[11] = 0;
                  break;
		case S2W_DOMAIN_ETSI:
                  gNwConnConfig.wlanCfg.channel[11] = 12;
                  gNwConnConfig.wlanCfg.channel[12] = 13;
                  gNwConnConfig.wlanCfg.channel[13] = 0;
                  break;
		case S2W_DOMAIN_TELEC:
                  gNwConnConfig.wlanCfg.channel[11] = 12;
                  gNwConnConfig.wlanCfg.channel[12] = 13;
                  gNwConnConfig.wlanCfg.channel[13] = 14;
                  gNwConnConfig.wlanCfg.channel[14] = 0;
                  break;
		default:
                  gNwConnConfig.wlanCfg.channel[11] = 0;
                  break;
            }
    }
	gNwConnConfig.specificChnlList[0] = 1;
	gNwConnConfig.specificChnlList[1] = 6;
	gNwConnConfig.specificChnlList[2] = 11;
	gNwConnConfig.specificChnlList[3] = 0;

    S2w_getSecurityConfig(&gNwConnConfig.wlanCfg);
		
	    memcpy(gNwConnConfig.wlanCfg.securityCfg.eapConfig.userName.Name,
                    s2wCurrent.security.eap.usrName, s2wCurrent.security.eap.usrNameLen);
	    memcpy(gNwConnConfig.wlanCfg.securityCfg.eapConfig.password.Pwd,
                    s2wCurrent.security.eap.password, s2wCurrent.security.eap.passwordLen);
	    gNwConnConfig.wlanCfg.securityCfg.eapConfig.password.Length = s2wCurrent.security.eap.passwordLen;
	    gNwConnConfig.wlanCfg.securityCfg.eapConfig.userName.Length = s2wCurrent.security.eap.usrNameLen;

	    gNwConnConfig.wlanCfg.securityCfg.eapConfig.outerAuthType = s2wCurrent.security.eap.outerAuth;
	    gNwConnConfig.wlanCfg.securityCfg.eapConfig.innerAuthType = s2wCurrent.security.eap.innerAuth;

	  //  gNwConnConfig.wlanCfg.securityCfg.eapConfig.fastProvisioningStatus= APP_NCM_CFG_DFLT_FAST_PROVISIONING_STATUS;
	   // gNwConnConfig.wlanCfg.securityCfg.eapConfig.pacOverWrite= APP_NCM_CFG_DFLT_FLASH_PAC_OVER_WRITE;
	    //gNwConnConfig.wlanCfg.securityCfg.eapConfig.pac.pac_opaque_len = 0;


#if 0
    if( s2wCurrent.security.eap.useCaCert ||
      (( 13 == s2wCurrent.security.eap.outerAuth)&&
      ( 26 == s2wCurrent.security.eap.innerAuth )))
    {
			index = S2wCert_findFile(S2W_CERT_NAME_CA);
        if(index != -1)
        {
		  		gNwConnConfig.wlanCfg.securityCfg.eapConfig.pCaCert = (char*)s2w_ssl_cert_table[index].certAddress;
        }
    }
		index = S2wCert_findFile(S2W_CERT_NAME_CLIENT);
    if(index != -1)
    {
		  gNwConnConfig.wlanCfg.securityCfg.eapConfig.pClientCert  = (char*)s2w_ssl_cert_table[index].certAddress;
    }
		index = S2wCert_findFile(S2W_CERT_NAME_KEY);
    if(index != -1)
    {
		  gNwConnConfig.wlanCfg.securityCfg.eapConfig.pPrivateKey =(char*) s2w_ssl_cert_table[index].certAddress;
    }
#else
	if(s2wCurrent.eapCertTimeValidChkDisbl)
	{
		gNwConnConfig.wlanCfg.securityCfg.eapConfig.eapFlags |= GSN_WPAIF_EAP_FLAG_NO_TIME_STAMP_CHECK;
	}
    if( s2wCurrent.security.eap.useCaCert ||
      (( 13 == s2wCurrent.security.eap.outerAuth)&&
      ( 26 == s2wCurrent.security.eap.innerAuth )))
    {
        index = S2wCert_SearchRamTable(S2W_CERT_NAME_CA);
        if(index == -1)
        {
            index = S2wCert_FlashFileLoad(S2W_CERT_NAME_CA);
        }
        if(index != -1)
        {
            gNwConnConfig.wlanCfg.securityCfg.eapConfig.pCaCert = (char*)s2w_ssl_cert_table[index].certAddress + 2;
            gNwConnConfig.wlanCfg.securityCfg.eapConfig.caCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        }
    }
    index = S2wCert_SearchRamTable(S2W_CERT_NAME_CLIENT);
    if(index == -1)
    {
        index = S2wCert_FlashFileLoad(S2W_CERT_NAME_CLIENT);
    }
    if(index != -1)
    {
        gNwConnConfig.wlanCfg.securityCfg.eapConfig.pClientCert  = (char*)s2w_ssl_cert_table[index].certAddress + 2;
        gNwConnConfig.wlanCfg.securityCfg.eapConfig.clientCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
    }
    index = S2wCert_SearchRamTable(S2W_CERT_NAME_KEY);
    if(index == -1)
    {
        index = S2wCert_FlashFileLoad(S2W_CERT_NAME_KEY);
    }
    if(index != -1)
    {
	    gNwConnConfig.wlanCfg.securityCfg.eapConfig.pPrivateKey = (char*)s2w_ssl_cert_table[index].certAddress + 2;
        gNwConnConfig.wlanCfg.securityCfg.eapConfig.privateKeyLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
    }
#endif
    if(s2wCurrent.ncmAutoConf[S2W_NCM_CPUWAIT_PERIOD])
    {
        gNwConnConfig.retryPeriodConfig.cpuWaitPeriod = s2wCurrent.ncmAutoConf[S2W_NCM_CPUWAIT_PERIOD];
    }
    else
    {
        gNwConnConfig.retryPeriodConfig.cpuWaitPeriod = S2W_NCM_DFLT_CPUWAIT_PERIOD;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_SCANKNOWN_CH_PERIOD])
    {
        gNwConnConfig.retryPeriodConfig.scanKnownChRetryIntrvl = s2wCurrent.ncmAutoConf[S2W_NCM_SCANKNOWN_CH_PERIOD];
    }
    else
    {
        gNwConnConfig.retryPeriodConfig.scanKnownChRetryIntrvl = S2W_NCM_DFLT_KNOWNCH_SCAN_PERIOD;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_SCANSPEC_CH_PERIOD])
    {
        gNwConnConfig.retryPeriodConfig.scanSpecChRetryIntrvl = s2wCurrent.ncmAutoConf[S2W_NCM_SCANSPEC_CH_PERIOD];
    }
    else
    {
        gNwConnConfig.retryPeriodConfig.scanSpecChRetryIntrvl = S2W_NCM_DFLT_SPECCH_SCAN_PERIOD;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_SCANALL_CH_PERIOD])
    {
        gNwConnConfig.retryPeriodConfig.scanAllChRetryIntrvl = s2wCurrent.ncmAutoConf[S2W_NCM_SCANALL_CH_PERIOD];
    }
    else
    {
        gNwConnConfig.retryPeriodConfig.scanAllChRetryIntrvl = S2W_NCM_DFLT_ALLCH_SCAN_PERIOD;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_L3CONNECT_PERIOD])
    {
        gNwConnConfig.retryPeriodConfig.l3ConnectRetryIntrvl = s2wCurrent.ncmAutoConf[S2W_NCM_L3CONNECT_PERIOD];
    }
    else
    {
        gNwConnConfig.retryPeriodConfig.l3ConnectRetryIntrvl = S2W_NCM_DFLT_L3CONNECT_PERIOD;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_SCANKNOWN_CH_COUNT])
    {
        gNwConnConfig.retryCountsConfig.maxScanKnownChCnt = s2wCurrent.ncmAutoConf[S2W_NCM_SCANKNOWN_CH_COUNT];
    }
    else
    {
        gNwConnConfig.retryCountsConfig.maxScanKnownChCnt = S2W_NCM_DFLT_KNOWNCH_SCAN_COUNT;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_SCANSPEC_CH_COUNT])
    {
        gNwConnConfig.retryCountsConfig.maxScanSpecChCnt = s2wCurrent.ncmAutoConf[S2W_NCM_SCANSPEC_CH_COUNT];
    }
    else
    {
        gNwConnConfig.retryCountsConfig.maxScanSpecChCnt = S2W_NCM_DFLT_SPECCH_SCAN_COUNT;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_SCANALL_CH_COUNT])
    {
        gNwConnConfig.retryCountsConfig.maxScanAllChCnt = s2wCurrent.ncmAutoConf[S2W_NCM_SCANALL_CH_COUNT];
    }
    else
    {
        gNwConnConfig.retryCountsConfig.maxScanAllChCnt = S2W_NCM_DFLT_ALLCH_SCAN_COUNT;
    }
    if(s2wCurrent.ncmAutoConf[S2W_NCM_L3CONNECT_COUNT])
    {
        gNwConnConfig.retryCountsConfig.maxL3ConnectCnt = s2wCurrent.ncmAutoConf[S2W_NCM_L3CONNECT_COUNT];
        gNwConnConfig.dhcpV4Cfg.dhcpMaxRetryCnt = 6;
        gNwConnConfig.dhcpV4Cfg.radioMode= s2wCurrent.ncmAutoConf[S2W_NCM_DHCP_RADIO_MODE];
        gNwConnConfig.dhcpV4Cfg.requestLeaseTime = 
            s2wCurrent.ncmAutoConf_extn[S2W_NCM_EXTN_DHCP_RQST_LEASE - S2W_NCM_EXTN_EXTN_BASE];
        gNwConnConfig.dhcpV4Cfg.dhcpRetryTimeout= 
            s2wCurrent.ncmAutoConf_extn[S2W_NCM_EXTN_DHCP_RETRANS_TIMEOUT - S2W_NCM_EXTN_EXTN_BASE];

    }
    else
    {
        gNwConnConfig.retryCountsConfig.maxL3ConnectCnt = S2W_NCM_DFLT_L3CONNECT_COUNT;
        gNwConnConfig.dhcpV4Cfg.dhcpMaxRetryCnt = 6; //s2wCurrent.ncmAutoConf[S2W_NCM_L3CONNECT_COUNT];         
        gNwConnConfig.dhcpV4Cfg.radioMode= s2wCurrent.ncmAutoConf[S2W_NCM_DHCP_RADIO_MODE];         
        gNwConnConfig.dhcpV4Cfg.requestLeaseTime = 
            s2wCurrent.ncmAutoConf_extn[S2W_NCM_EXTN_DHCP_RQST_LEASE - S2W_NCM_EXTN_EXTN_BASE];        
        gNwConnConfig.dhcpV4Cfg.dhcpRetryTimeout= 
            s2wCurrent.ncmAutoConf_extn[S2W_NCM_EXTN_DHCP_RETRANS_TIMEOUT - S2W_NCM_EXTN_EXTN_BASE];
    }
#ifdef S2W_NCM_ROAMING_SUPPORT 
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_ENABLE_ID])
		gNwConnConfig.roamingCfgParams.roamEnable = S2W_NCM_ROAM_DFLT_ROAMEN;	
	else
		gNwConnConfig.roamingCfgParams.roamEnable = S2W_NCM_ROAM_DFLT_ROAMDIS;
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_LOWER_THID] )
		gNwConnConfig.roamingCfgParams.rssiLowerTh = s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_LOWER_THID];
	else
		gNwConnConfig.roamingCfgParams.rssiLowerTh = S2W_NCM_ROAM_DFLT_RSSILOWERTH;
    if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_HIGHER_THID]  )
		gNwConnConfig.roamingCfgParams.rssiHigherTh = s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_HIGHER_THID];
	else
		gNwConnConfig.roamingCfgParams.rssiHigherTh = S2W_NCM_ROAM_DFLT_RSSIHIGHERTH;
    if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_RSSICHKINTERVAL_ID])
		gNwConnConfig.roamingCfgParams.rssiLevelChkInterval= (s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_RSSICHKINTERVAL_ID] * TIMER_INTERRUPT_1_MS);
	else
		gNwConnConfig.roamingCfgParams.rssiLevelChkInterval = S2W_NCM_ROAM_DFLT_RSSICHKINTERVAL;
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_THCROSSEDCNT_ID])
		gNwConnConfig.roamingCfgParams.thresholdCrossedCnt= s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_THCROSSEDCNT_ID];
	else
	   gNwConnConfig.roamingCfgParams.thresholdCrossedCnt = S2W_NCM_ROAM_DFLT_THCROSSEDCNT;
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_MAINTAINL3CON_ID] == 0 )
		gNwConnConfig.roamingCfgParams.maintainL3Con= s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_MAINTAINL3CON_ID];
	else
	   gNwConnConfig.roamingCfgParams.maintainL3Con = S2W_NCM_ROAM_DFLT_MAINTAINL3CON;
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_MAINTAINL4CON_ID])
		gNwConnConfig.roamingCfgParams.maintainL4Con= s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_MAINTAINL4CON_ID];
	else
	   gNwConnConfig.roamingCfgParams.maintainL4Con = S2W_NCM_ROAM_DFLT_MAINTAINL4CON;
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_SCANRETRYCNT_ID])
		gNwConnConfig.roamingCfgParams.scanRetryCnt= s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_SCANRETRYCNT_ID];
	else
	   gNwConnConfig.roamingCfgParams.scanRetryCnt = S2W_NCM_ROAM_DFLT_SCANRETRYCOUNT;
	if(s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_SCANPAUSETIME_ID])
		gNwConnConfig.roamingCfgParams.scanPauseTimeMs= s2wCurrent.ncmAutoConf[S2W_NCM_ROAM_SCANPAUSETIME_ID];
	else
	   gNwConnConfig.roamingCfgParams.scanPauseTimeMs = S2W_NCM_ROAM_DFLT_SCANPUASETIME;
#endif /*GSN_NCM_ROAMING_SUPPORT */
    
    gNwConnConfig.scanMode = 2;
    gNwConnConfig.powersaveMode = 0;
    gNwConnConfig.ipConfig.ipv4.staticIp = !s2wCurrent.netConf.dhcp;
    gNwConnConfig.ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT
#ifdef S2W_IPv6_SUPPORT  
#endif
                            ;
    if(gNwConnConfig.ipConfig.ipv4.staticIp)
    {
        memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.ipAddr,s2wCurrent.netConf.ipAddr,4 );
        memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.subnetMask,s2wCurrent.netConf.netMask,4 );
        memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.gatewayIpAddr,s2wCurrent.netConf.gateway,4 );
        memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.dnsPriSrvrIp,s2wCurrent.dns1,4);
        memcpy((UINT8*)&gNwConnConfig.ipConfig.ipv4.dnsSecSrvrIp,s2wCurrent.dns2,4);
    }
    else // store the host name
    {
        if(strlen((const char *)s2wCurrent.hostName) != 0)
        {
            memcpy(gNwConnConfig.ipConfig.ipv4.hostName, s2wCurrent.hostName,
                    (GSN_NWIF_HOST_NAME_MAX_LEN + 1));
        }
		else
		{     
 			S2w_macAddrRTCGet(mac);
	      	sprintf((char*)macStr,"%s%2.2x%2.2x%2.2x","GS_",mac[3],mac[4],mac[5]);
		    memcpy(s2wCurrent.hostName,macStr,strlen((char*)macStr));
			memcpy(gNwConnConfig.ipConfig.ipv4.hostName, s2wCurrent.hostName,
				 (GSN_NWIF_HOST_NAME_MAX_LEN + 1));
		}
	}
	if(TRUE == GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx))
	{
	    gNwConnConfig.ipConfig.ipv4.staticIp = pAppRtcLtchInfo->ipConfig.ipv4.staticIp;
        gNwConnConfig.ipConfig.ipv4.ipAddr = pAppRtcLtchInfo->ipConfig.ipv4.ipAddr;
        gNwConnConfig.ipConfig.ipv4.subnetMask = pAppRtcLtchInfo->ipConfig.ipv4.subnetMask;
        gNwConnConfig.ipConfig.ipv4.gatewayIpAddr = pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr;
        gNwConnConfig.ipConfig.ipv4.dhcpLeaseExpireTime =
                          pAppRtcLtchInfo->ipConfig.ipv4.dhcpLeaseExpireTime;
		gNwConnConfig.ipConfig.ipv4.dnsPriSrvrIp = pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp;
        gNwConnConfig.ipConfig.ipv4.dnsSecSrvrIp = pAppRtcLtchInfo->ipConfig.ipv4.dnsSecSrvrIp;
		memcpy(gNwConnConfig.wlanCfg.ssid.array,pAppRtcLtchInfo->ssid.array,
		   pAppRtcLtchInfo->ssid.length);
		gNwConnConfig.wlanCfg.ssid.length= pAppRtcLtchInfo->ssid.length;
		memcpy(gNwConnConfig.wlanCfg.bssid.array,pAppRtcLtchInfo->bssid.array, 6);
        gNwConnConfig.wlanCfg.channel[0] = pAppRtcLtchInfo->channel;
		gNwConnConfig.wlanCfg.securityCfg.mode = pAppRtcLtchInfo->wsec;
		gNwConnConfig.dhcpV4Cfg.pDhcpCliRecord = &pAppRtcLtchInfo->dhcpClientParams;
		gNwConnConfig.dhcpV4Cfg.timeElapsed = pAppRtcLtchInfo->sleepTime/10;
		pAppRtcLtchInfo->sleepTime = 0;
	}
#if 0
    if(appRtcMemData.ncmState == GSN_NCM_STATE_L3_CONNECTED)
    {
        gNwConnConfig.ipConfig.ipv4.staticIp = appRtcMemData.staticIp;
        gNwConnConfig.ipConfig.ipv4.ipAddr = appRtcMemData.ipAddr;
        gNwConnConfig.ipConfig.ipv4.subnetMask = appRtcMemData.subnetAddr;
        gNwConnConfig.ipConfig.ipv4.gatewayIpAddr = appRtcMemData.gatewayIpAddr;
        if(appRtcMemData.staticIp == 0)
        {
            gNwConnConfig.clientConfig.ipConfig.dhcpLeaseExpireTime =
                          appRtcMemData.connectionInfo.dhcpLeaseTime;
        }
        gNwConnConfig.clientConfig.ipConfig.dnsPriSrvrIp = appRtcMemData.dns1;
        gNwConnConfig.clientConfig.ipConfig.dnsSecSrvrIp = appRtcMemData.dns2;
        memcpy(gNwConnConfig.clientConfig.ssid.array,appRtcMemData.ssid.array,
               appRtcMemData.ssid.length);
        gNwConnConfig.clientConfig.ssid.length = appRtcMemData.ssid.length;
        memcpy(gNwConnConfig.clientConfig.bssid.array,appRtcMemData.bssid, 6);
       gNwConnConfig.clientConfig.validBssid = 1;
        gNwConnConfig.clientConfig.channel = appRtcMemData.channel;
        if(appRtcMemData.encryptionType == GSN_MAC_ENC_NONE)
        {
        }
        else if(appRtcMemData.encryptionType == GSN_MAC_ENC_WEP)
        {
              gNwConnConfig.clientConfig.wepConfig.KeyId =
                                appRtcMemData.securityKey.wepKey.keyId;
              gNwConnConfig.clientConfig.wepConfig.KeyLen =
                                appRtcMemData.securityKey.wepKey.keyLen;
              memcpy(&gNwConnConfig.clientConfig.wepConfig.Key,
                     appRtcMemData.securityKey.wepKey.key,
                     appRtcMemData.securityKey.wepKey.keyLen);
        }
        else
        {
            if(appRtcMemData.pskValid )
            {
                memcpy(&gNwConnConfig.clientConfig.pskConfig.psk,
                       appRtcMemData.securityKey.psk,32);
                gNwConnConfig.clientConfig.pskConfig.pskValid = 1;
                memcpy(s2wCurrent.security.wpa.psk,
                   appRtcMemData.securityKey.psk,32);
                s2wCurrent.security.wpa.pskValid = 1;
            }
        }
        gNwConnConfig.clientConfig.encryptionType =
                                                   appRtcMemData.encryptionType;
        if(appRtcMemData.authMode == GSN_MAC_AUTH_SHARED)
        {
            gNwConnConfig.clientConfig.authType = appRtcMemData.authMode;
        }
        else
        {
            gNwConnConfig.clientConfig.authType = GSN_MAC_AUTH_AUTO;
        }
    }
#endif
    }

    //s2wCurrent.mode = s2wappMainTaskCtxt->if0.macIfType;
    
    // set the mac
    if(s2wCurrent.mode == S2W_WLANDATA_MODE_INFRA)
    {
       //S2w_LoadMacAddr(macAddr);
        S2w_macAddrRTCGet(macAddr);
    }
    else
    {
        memcpy(macAddr,s2wCurrent.lmtdApConf.macAddr.array , 6);
    }

    //AppS2wHal_MacAddrSet(macAddr, FALSE);
    
    /* Init crypto engine */
    GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
	
    GsnNcm_ConfigSet(&s2wappMainTaskCtxt->appNwConnMgrCtx,  &gNwConnConfig);
    status = GsnNcm_Start(&s2wappMainTaskCtxt->appNwConnMgrCtx,  AppS2wNetConnMgr_Cb, NULL);
    return status;
}
UINT8
AppS2wCmd_NcmAutoConf(UINT8* ptr)
{
    UINT8 status;
    UINT8 *p;
    UINT32 id=0;

    UINT32 value;

     p = AppS2wParse_NextParamGet(&ptr);
     if (!p)
     {
         return S2W_EINVAL;
     }
     status = AppS2wParse_Int(p, &id);
     if ((status != S2W_SUCCESS)||((id > 5)&&(id < 8))
#ifdef S2W_NCM_ROAMING_SUPPORT 				 
         || (id > 27)
#else
         || (id > 15 && (id < 25 || id > 27))
#endif
           )
     {
         return S2W_EINVAL;
     }
     p = AppS2wParse_NextParamGet(&ptr);
     if (!p)
     {
         return S2W_EINVAL;
     }
#ifdef S2W_NCM_ROAMING_SUPPORT 				 
	 if((id == S2W_NCM_ROAM_HIGHER_THID || id == S2W_NCM_ROAM_LOWER_THID) && (*p == '-'))
	 {
		status = AppS2wParse_Int(p+1, &value);
		s2wCurrent.ncmAutoConf[id] = (unsigned char)(value * -1);
	 }
	 else if((id == S2W_NCM_ROAM_HIGHER_THID || S2W_NCM_ROAM_LOWER_THID == 3) && (*p != '-'))		
	 {
		return S2W_EINVAL;
	 }
	else
#endif		/*GSN_NCM_ROAMING_SUPPORT */  
     if(id >= 26  && id <= 27)
     {
        value = 0;
        status = AppS2wParse_Int(p, &value);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        s2wCurrent.ncmAutoConf_extn[id - S2W_NCM_EXTN_EXTN_BASE] = value;        
     }
     else 
     {
         status = AppS2wParse_Int(p, &s2wCurrent.ncmAutoConf[id]);
         if (status != S2W_SUCCESS)
         {
             return status;
         }
     }
     return status;
}
#endif // #ifdef  NCM_SUPPORT_ENABLE 


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WAUTO command.
 *   This function Parse and Store the WiFi auto connect settings.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Wauto(UINT8 *ptr)
{
    S2W_WLANDATA_T autoparams;
    UINT8 status;
    memset(&autoparams, 0, sizeof(autoparams));
    status = AppS2wParse_Wcmd(ptr, &autoparams, pwc_wauto);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if(s2wappMainTaskCtxt->apConf &&  autoparams.mode == 2) // if ncm enabled and mode is AP then store in Ap conf
    {
        s2wCurrent.lmtdApConf.ssid.length = autoparams.ssidLen;
        memcpy(s2wCurrent.lmtdApConf.ssid.array,autoparams.ssid,autoparams.ssidLen);
        if(autoparams.channel)
        {
            s2wCurrent.lmtdApConf.channel = autoparams.channel;
        }
        else
        {
			s2wCurrent.lmtdApConf.channel = 1;
		}
		s2wCurrent.autoWlandata.mode = autoparams.mode;
    }
    else
    {
        memcpy(&s2wCurrent.autoWlandata, &autoparams,
           sizeof(s2wCurrent.autoWlandata));
    }
    return S2W_SUCCESS;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WRATE Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Wrate(UINT8 *ptr)
{
    GSN_WDD_TX_RATE_SET_PARAM_T param;
	GSN_WDD_TX_RATE_GET_RESP txRate;
    UINT8 status=S2W_SUCCESS;
	UINT32 val;
	UINT8 *p;
	INT32 retVal;
    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        retVal= GsnWdd_TxRateGet(&s2wappMainTaskCtxt->if0.wddCtx,&txRate);
        if(retVal == GSN_SUCCESS)
        {
			S2w_Printf("\r\n%d", txRate.dataFrameRate);
        	return S2W_SUCCESS;
        }
		else
			return S2W_FAILURE;
    }
    else
    {
		p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return status;
        }
		status = AppS2wParse_Int(p, &val);
        if((status != S2W_SUCCESS)||( S2W_SUCCESS != S2wRateValidation(val)))
            {
			return S2W_EINVAL;
			    }
        param.dataFrameRate = val;
        // update the default the mgmt and ctl rate
        param.mgmtFrameRate = val;
        param.ctlFrameRate = val;

		p = AppS2wParse_NextParamGet(&ptr);
        if (p && *p)
				{
            status = AppS2wParse_Int(p, &val);
			if((status != S2W_SUCCESS) ||( S2W_SUCCESS != S2wRateValidation(val)))
            {
           		return S2W_EINVAL;
            }
		    param.mgmtFrameRate = val;
        }
		p = AppS2wParse_NextParamGet(&ptr);
        if (p && *p)
        {
            status = AppS2wParse_Int(p, &val);
			if((status != S2W_SUCCESS)||( S2W_SUCCESS != S2wRateValidation(val)))
        {
    		return S2W_EINVAL;        
    	}
		    param.ctlFrameRate = val;
        }

        status= GsnWdd_TxRateSet(&s2wappMainTaskCtxt->if0.wddCtx,&param);

    }
    return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NAUTO Command .
 *       AT+NAUTO command stores the settings for network auto connect.
 * @param ptr Pointer to the user string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Nauto(UINT8 *ptr)
{
    S2W_NETDATA_T params;
    UINT8 *temp = ptr;
    UINT8 status = S2W_EINVAL;
    UINT8 *p;
    UINT32 port,srcPort=0;
	ULONG ipAddress;
    UINT8 ipmaskH[4] = {0xff,0xff,0xff,0xff};
    UINT8 ipmaskL[4] = {0x00,0x00,0x00,0x00};
    memset(&params, 0, sizeof(params));
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return status;
    }
    status = AppS2wParse_Boolean(p, &params.mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return status;
    }
    status = AppS2wParse_Boolean(p, &params.proto);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(params.mode == 0)//client-tcp/udp
    {
        //status = AppS2wParse_AddrPort(&temp, &params);
     
       p = AppS2wParse_NextParamGet(&temp);
        if (!p)
        {
          return S2W_EINVAL;
        }
         if(inet_addr((const char *)p) != -1)
         {
              status = AppS2wParse_Ip(p, params.ipAddr );
              if(status != S2W_SUCCESS)
              {

                  return S2W_EINVAL;
            }
            p = AppS2wParse_NextParamGet(&temp);
            if (!p)
            {
              return S2W_EINVAL;
            }
            else
            {
               status = AppS2wParse_Int(p, &port);
              if (status != S2W_SUCCESS || !is_valid_port(port))
              {
                return S2W_EINVAL;
              }
              params.port = port;
            }
         }
        else
        {
           /* Can be URL  */
          if((s2wLinkState != S2W_LINK_STATE_DISCONNECTED)  && (L3ConnectStatus == TRUE))
          {
            	status = GsnNwIf_DnsHostByNameGet(&s2wappMainTaskCtxt->if0.nwifCtx,(UINT8*)p,&ipAddress,5);
            if(status != GSN_SUCCESS)
             return S2W_EINVAL;
				params.ipAddr[0] = (ipAddress & 0xff000000)>>24 ;			
				params.ipAddr[1] = (ipAddress & 0x00ff0000)>>16;
				params.ipAddr[2] = (ipAddress & 0x0000ff00)>>8;
				params.ipAddr[3] = (ipAddress & 0x000000ff);
          }
          else
            {
              params.isFqdn = TRUE;
              /* resolve it during NCM L4 connection */
              memcpy(params.fqdn,p,strlen((const char*)p));
            }
            
            p = AppS2wParse_NextParamGet(&temp);
            if (!p)
            {
              return S2W_EINVAL;
            }
            else
            {
               status = AppS2wParse_Int(p, &port);
              if (status != S2W_SUCCESS || !is_valid_port(port))
              {
                return S2W_EINVAL;
              }
              params.port = port;
            }
        }
    }
    else //server -tcp/udp no need of ip address
    {
        p = AppS2wParse_NextParamGet(&temp);
        if (!p)
        {
            return S2W_EINVAL;
        }
        else
        {
            if(*p != '\0')
            {
                status = AppS2wParse_Ip(p, params.ipAddr );
                if (status != S2W_SUCCESS)
                {
                    return status;
                }
            }
        }
        p = AppS2wParse_NextParamGet(&temp);
        if (!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Int(p, &port);
        if (status != S2W_SUCCESS || !is_valid_port(port))
        {
            return S2W_EINVAL;
        }
        params.port = port;
    }
    if((params.mode == 0) &&(params.proto == S2W_NETDATA_PROTO_UDP))//client-/udp
    {
	    p = AppS2wParse_NextParamGet(&temp);
	    if ( (p) &&(*p != '\0'))
	    {
	        status = AppS2wParse_Int(p, &srcPort);
	        if (status != S2W_SUCCESS || !is_valid_port(srcPort))
	        {
	            return S2W_EINVAL;
	        }
	        if (AppS2wParse_NextParamGet(&temp))
	            return S2W_EINVAL;
        }
        else
        {
			srcPort = 0;
		}
		s2wCurrent.udpSrcPort = srcPort;
	}
    if(params.mode == 0  &&  params.isFqdn != TRUE) // check only in case of client
    {
        if((memcmp((UINT8*)params.ipAddr,ipmaskH,3) ==0) ||
           (memcmp((UINT8*)params.ipAddr,ipmaskL,4) ==0))
        {
            return S2W_EINVAL;
        }
    }
    memcpy(&s2wCurrent.autoNetdata, &params,
           sizeof(s2wCurrent.autoNetdata));
    return S2W_SUCCESS;
}
UINT8
AppS2wCmd_IdOutput(UINT8 *ptr)
{
    UINT32 which;
    UINT8 status;

    status = AppS2wParse_Int(ptr, &which);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    switch (which)
    {
        case S2W_ID_OEM:
            S2w_Printf("\r\n%s", S2W_OEM_ID);
            break;

        case S2W_ID_HW_VERSION:
            {
                S2w_Printf("\r\n%s", S2W_HW_VERSION);
            }
            break;

        case S2W_ID_SW_VERSION:
            S2w_Printf("\r\n%s", S2W_SW_VERSION);
            break;

        default:
            status = S2W_EINVAL;
    }
    return status;
}

#ifdef S2W_PING_TRACE

PUBLIC VOID
AppS2w_PingTaskNotify(INT32 msg)
{
    /**< Signal APP */
    GsnOsal_QueuePut(&pingThreadMsgQueue, (UINT8 *)&msg);
}

PRIVATE VOID
AppS2w_PingThreadEntry(UINT32 ctx)
{	
    UINT32 msg = 0;
    /**< Handle events forever */
    while( TRUE )
    {
        /**< wait on message queue */
        GsnOsal_QueueGet( &pingThreadMsgQueue, ( UINT8* )&msg, GSN_OSAL_WAIT_FOREVER );
		
		if(	APP_EVENT_PING_REQUEST == msg)
		{
			s2wPingStart();
		}
		else if(APP_EVENT_PING_STOP == msg)
		{
        	s2wPingStop();
		}
    }
	
}
VOID AppS2w_PingThreadCreate()
{
	UINT32 pingMsgQueSize = APP_CFG_PING_MAX_MSG_IN_MBOX * sizeof(UINT32);
	
	pingThreadMsgQueueBuf = (UINT8 *)MALLOC(pingMsgQueSize);
	
	/**< Creating the Mailbox to receive messages */
		GsnOsal_QueueCreate( &pingThreadMsgQueue, 1,
								( UINT8* )pingThreadMsgQueueBuf,
								pingMsgQueSize);
	
	pingThreadStack = (UINT8 *)MALLOC(PING_THRAED_STACK_SIZE);
	
	GsnOsal_ThreadCreate(AppS2w_PingThreadEntry, &appCtx, &pingThread,
							"Ping Thread", APP_PING_THREAD_PRI, (UINT8 *)pingThreadStack,
							PING_THRAED_STACK_SIZE, GSN_OSAL_THREAD_INITIAL_READY);

}
UINT8
AppS2wCmd_Ping(UINT8* ptr)
{
  UINT8 *p,status=S2W_FAILURE;
  S2W_PINGDATA_T pingParams;
  
	if(0 == pingThreadCreated)
	{
		AppS2w_PingThreadCreate();
		pingThreadCreated = 1;
	}
    s2wPingStarted = FALSE;
    memset (&pingParams, 0, sizeof (S2W_PINGDATA_T));
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return status;
    }
    status = AppS2wParse_Ip(p, (UINT8*)&pingParams.Ipv4Addr);
    if (status != S2W_SUCCESS)
    {
#ifdef S2W_IPv6_SUPPORT
        status =  inet_pton(AF_INET6, (const char*)p, (VOID*) pingParams.ip_address.nxd_ip_address.v6);
        if(status != TRUE)
          return S2W_EINVAL;
      GSN_IPv6_CHANGE_ENDIAN( (UINT32*)pingParams.ip_address.nxd_ip_address.v6);
      pingParams.ip_address.nxd_ip_version = NX_IP_VERSION_V6;
      pingParams.IpVersion |= ADDR_TYPE_IPv6;
#else     
        /* Can be FQDN */
      pingParams.Ipv4Addr = 0;
      GsnNwIf_DnsRetryCountSet(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,10);
      status = GsnNwIf_DnsHostByNameGet(&s2wappMainTaskCtxt->if0.nwifCtx,(UINT8*)p,(ULONG*)&pingParams.Ipv4Addr,5);
            if(status != GSN_SUCCESS  || pingParams.Ipv4Addr == 0)
        return S2W_FAILURE;
        pingParams.Ipv4Addr = htonl(pingParams.Ipv4Addr);
#endif
   }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
    status = AppS2wParse_Int(p, &pingParams.trails);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
    status = AppS2wParse_Int(p, &pingParams.interval);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if (pingParams.interval &&
        ((pingParams.interval < 1000) || (pingParams.interval > 99000)))
    {
        return S2W_EINVAL;
    }
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
            {
    status = AppS2wParse_Int(p, &pingParams.dataLen);
    if (status != S2W_SUCCESS)
    {
        return status;
            }

    if (pingParams.dataLen > 1024)
    {
        return S2W_EINVAL;
    }
    }
    else
    {
      pingParams.dataLen = 56;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {

    status = AppS2wParse_Int(p, &pingParams.tos);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if (pingParams.tos>99)
    {
        return S2W_EINVAL;
    }
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
    status = AppS2wParse_Int(p, &pingParams.ttl);
    if (status != S2W_SUCCESS)
    {
    return status;
    }
    if (pingParams.ttl>255)
    {
        return S2W_EINVAL;
    }
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
    if (strlen ((const INT8*)p) > 16)
    {
        return S2W_EINVAL;
    }
    strcpy (pingParams.payload, (const INT8*)p);
   } 
    memcpy(&s2wappMainTaskCtxt->pingParams,&pingParams,sizeof(S2W_PINGDATA_T));
    s2wappMainTaskCtxt->pingParams.Ipv4Addr = htonl(s2wappMainTaskCtxt->pingParams.Ipv4Addr);
#ifdef S2W_IPv6_SUPPORT    
         if(s2wappMainTaskCtxt->pingParams.IpVersion & ADDR_TYPE_IPv6)
         {
            INT8 ipv6str[INET6_ADDRSTRLEN];
            S2w_ntop(s2wappMainTaskCtxt->pingParams.ip_address.nxd_ip_address.v6,ipv6str);
        S2w_Printf("\r\nPinging for %s with %d bytes of data\r\n",ipv6str,s2wappMainTaskCtxt->pingParams.dataLen );
         }
         else
#endif         
    S2w_Printf("\r\nPinging for %d.%d.%d.%d with %d bytes of data\r\n",(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0xff000000)>>24,(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0x00ff0000)>>16,(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0x0000ff00)>>8,(s2wappMainTaskCtxt->pingParams.Ipv4Addr & 0x000000ff),s2wappMainTaskCtxt->pingParams.dataLen);
    if(s2wLinkState == S2W_LINK_STATE_DISCONNECTED)
    {
        S2w_Printf("\r\nNo Route to Host\r\n");
        return S2W_FAILURE;
    }
    s2wPingStarted = TRUE;
	AppS2w_PingTaskNotify(APP_EVENT_PING_REQUEST);
    return S2W_SUCCESS;
}

#endif //S2W_PING_TRACE

UINT8
AppS2wCmd_Acmode(UINT8 *ptr)
{
    UINT8 autocon;
    UINT8 status;
    S2W_PROFILE_T *profile;

    status = AppS2wParse_Boolean(ptr, &autocon);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    profile_params.autoConnect = autocon;
    profile = &s2wFlashParams->profile[profile_params.defaultProfile];
    // should disable the ncm
	s2wCurrent.ncmAutoMgr = 0;
    memcpy(profile, &s2wCurrent, sizeof(S2W_PROFILE_T));
    // update the profile
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
    status = S2w_SaveS2wProfile(s2wFlashParams, profile_params.defaultProfile);
    if(status != S2W_SUCCESS)
    {
        status = S2W_FAILURE;
	}

    // update the nvds
    return S2w_SaveS2wProfileParams(&profile_params);

}
#ifdef  S2W_NCM_SUPPORT_ENABLE
UINT8
AppS2wCmd_AutoConnect(UINT8 *ptr)
{
	UINT8 status;
    if (*ptr)
    {
        return S2W_EINVAL;
    }
    /* call the auto connect start function
     */
    profile_params.autoConnect = 1;
    // if it is connected disconnect and connect it back
    if(s2wIsAutoconnected)
    {
		AppS2wProcess_AutoConnectStop(&s2wCurrent);
	}
    status = AppS2wProcess_AutoConnectStart(&s2wCurrent);
    if(status == S2W_SUCCESS)
    {
		return S2W_CMD_INPROCESS;
	}
	return status;
}

#endif
UINT8
AppS2wCmd_GoOnline(UINT8 *ptr)
{
    if (*ptr)
    {
        return S2W_EINVAL;
    }

    if (!s2wIsAutoconnected)
    {
        return S2W_FAILURE;
    }

    /* If the cid is not open, we could be a TCP server
     */
    if (!AppS2wHal_NetIsCidOpen(curCid)
        && (s2wCurrent.autoNetdata.proto != S2W_NETDATA_PROTO_TCP
            || s2wCurrent.autoNetdata.mode != S2W_NETDATA_MODE_SERVER))
    {

        return S2W_FAILURE;
    }
    /* change the state to auto
     */
    s2wState = S2W_STATE_DATA_AUTO;
    /* reregister the auto exit gpio */
	// start a gpio cb for auto mode exit
	GsnGpio_Init(APP_S2W_AUTO_EXIT_GPIO_BIT_MAP , APP_S2W_AUTO_EXIT_GPIO_BIT_MAP );
    /* register callback for GPIO interrupt */
	GsnGpio_IntCbRegister(APP_S2W_AUTO_EXIT_GPIO_NUM,s2wAutoExit_CB,NULL);
	/*enable interrupt*/
	GsnGpio_NEIntEnable(APP_S2W_AUTO_EXIT_GPIO_BIT_MAP);
	// make the data ready gpio as high..
    S2w_AsyncMsgGpioOp(1);
    return S2W_SUCCESS;
}


#ifdef S2W_THROUGHPUT_TEST
extern GSN_OSAL_SEM_T dSendSem;  
UINT8 tpTestBuff[1460];
UINT8
AppS2w_HttpTpTest(UINT8 cid,ULONG64 pktLen, UINT8 *ptr)
{
	UINT8 *p;
	GSN_SYSTEM_TIME_T startTime,endTime,totalTime;	
	UINT32 len,wddTxCnt0,wddTxCnt1,txBufAllocFail,getReqCnt=0;
	ULONG64 tp;
 #ifdef S2W_HTTPC_SUPPORT
	S2W_HTTP_DATA_T *pHttpData;
#endif
    UINT8 status = S2W_SUCCESS;
  	if(s2wCidList[cid].testMode== 0)
  	{		
#ifdef S2W_HTTPC_SUPPORT
	    httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;
#endif
  	}
	else
	{		
#ifdef S2W_HTTPC_SUPPORT
		httpConfInfo.reqMethod = GSN_HTTP_METHOD_GET;
#endif
	}
#ifdef S2W_HTTPC_SUPPORT
	httpConfInfo.httpTimeOut = 100 ;
#endif
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
#ifdef S2W_HTTPC_SUPPORT
 	len = strlen((const char *)p);
    if(NULL != httpConfInfo.reqPathPtr)
    {
        gsn_free(httpConfInfo.reqPathPtr);
        httpConfInfo.reqPathPtr = NULL;
    }
    httpConfInfo.reqPathPtr = gsn_malloc(len+1);
    if(NULL == httpConfInfo.reqPathPtr)
    {
        return S2W_FAILURE;
    }
    strncpy(httpConfInfo.reqPathPtr, (const INT8 *)p, len);
    httpConfInfo.reqPathPtr[len] ='\0';
    httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;	
    httpConfInfo.reqBodyTotalLen = 0;
    httpConfInfo.reqBodyLen = 0;
	if(GSN_HTTP_METHOD_POST== httpConfInfo.reqMethod)
    {
	    httpConfInfo.reqBodyTotalLen = pktLen;
		httpConfInfo.reqBodyPtr = (INT8 *)tpTestBuff;
		memset(tpTestBuff ,0xA5A5A5A5,10);
		httpConfInfo.reqBodyLen = pktLen;
	}
    pHttpData = AppS2wHal_HttpHandleGet(cid);
	txBufAllocFail = s2wappMainTaskCtxt->hiCtx.pStats->txBufAllocFail;
	wddTxCnt0 = s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipUnicastPktsSent+ s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipBroadCastPktsSent	;
	startTime = GsnTod_Get();	
	do
	{
        if(pHttpData != NULL)
        {
            GsnOsal_SemAcquire(&pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
            status = S2wHttp_Send(cid);
			if(status != GSN_SUCCESS)
				s2wCidList[cid].stats.txErr++;
        }
        else
        {
            return S2W_FAILURE;
        }
        if(pHttpData != NULL)
        {
            GsnOsal_SemRelease(&pHttpData->opInProgress);
        }
		getReqCnt++;
		if(GSN_HTTP_METHOD_POST== httpConfInfo.reqMethod)
    	{
			httpConfInfo.reqBodyPtr = (INT8 *)tpTestBuff;
			httpConfInfo.reqBodyLen = pktLen;
		}
	}while(getReqCnt < s2wCidList[cid].iteration);
	endTime = GsnTod_Get();
	totalTime = SYSTIME_TO_MSEC(endTime)-SYSTIME_TO_MSEC(startTime); 
	wddTxCnt1 = s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipUnicastPktsSent + s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipBroadCastPktsSent	;
	S2w_Printf("\r\n Total Requests Send     : %d",getReqCnt);		
	S2w_Printf("\r\n Packet Send From WDD    : %d",(wddTxCnt1-wddTxCnt0));
	S2w_Printf("\r\n Packet Lost From APP    : %d",s2wCidList[cid].stats.txErr);		
	S2w_Printf("\r\n Wdd Tx Buff Fail Cnt    : %d", s2wappMainTaskCtxt->hiCtx.pStats->txBufAllocFail-txBufAllocFail); 
	S2w_Printf("\r\n Bytes Received  	 : %lld",s2wCidList[cid].stats.bytesReceived); 
    S2w_Printf("\r\n Total Time Taken        : %lld usec",(SYSTIME_TO_USEC(endTime)-SYSTIME_TO_USEC(startTime)));									
	tp = (((s2wCidList[cid].stats.bytesReceived*8*1000))/(totalTime));
    S2w_Printf("\r\n Throuhput               : %lld bps",tp);	
	tp =(((s2wCidList[cid].stats.bytesReceived*8*1000))/(totalTime*1024));
    S2w_Printf("\r\n Throuhput               : %lld kbps ",tp);
	s2wCidList[cid].tpTestInProgress=0;
	if(NULL != httpConfInfo.reqPathPtr)
	{
        gsn_free(httpConfInfo.reqPathPtr);
        httpConfInfo.reqPathPtr = NULL;
	}
	httpConfInfo.reqBodyPtr = NULL;
#endif
	return status;

}
UINT8
AppS2wCmd_SockTpTestStat(UINT8 *ptr)
{
	UINT8 cid,validCid;
	UINT8 *p;	
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
 		   return S2W_EINVAL;
    }
    cid = *p;
	validCid = AppS2w_CidValidate(cid);
    if (INVALID_CID == validCid )
		return S2W_FAILURE;
	S2w_Printf("\r\n Packet Received  : %d",s2wCidList[validCid].stats.packetsReceived);
	S2w_Printf("\r\n Packet Lost      : %d",s2wCidList[validCid].stats.rxErr);
	S2w_Printf("\r\n Bytes Received   : %lld",s2wCidList[validCid].stats.bytesReceived); 
	S2w_Printf("\r\n Nwif Packets dropped  : %d" ,s2wappMainTaskCtxt->if0.nwifCtx.pStats->pktsDroppedNoMem);
	S2w_Printf("\r\n Nwif Packets filtered : %d" ,s2wappMainTaskCtxt->if0.nwifCtx.pStats->pktFilteredOut);
	S2w_Printf("\r\n Nwif Packets Received : %d", s2wappMainTaskCtxt->if0.nwifCtx.pStats->totalPktsRcvd);
	S2w_Printf("\r\n ARP Packets Received  : %d", s2wappMainTaskCtxt->if0.nwifCtx.pStats->arpRequestRcvd);		
	S2w_Printf("\r\n IP Packets Received   : %d", s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipPktsRcvd);
	S2w_Printf("\r\n Bytes Received   	   : %lld",s2wCidList[validCid].stats.bytesReceived);
	S2w_Printf("\r\n Total Time Taken	   : %lld sec",s2wCidList[validCid].stats.totalTime);																		
	S2w_Printf("\r\n Throuhput        	   : %lld Kbps",((s2wCidList[validCid].stats.bytesReceived*8)/(1024*s2wCidList[validCid].stats.totalTime)));										
	s2wCidList[validCid].tpTestInProgress=0; 
	return S2W_SUCCESS;
}
UINT8
AppS2wCmd_SockTpTest(UINT8 *ptr)
{
    UINT8 status,cid,validCid;
    UINT32 mode=0;
	UINT8 *p;
	UINT32 wddTxCnt0,wddTxCnt1,txBufAllocFail,seqNo=0;
	GSN_SYSTEM_TIME_T startTime,endTime,totalTime,currTime,diffTime;	
	ULONG64 tp,cnt=0,pktLen;
	
	/* CID */	
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
 		   return S2W_EINVAL;
    }
    cid = *p;
	validCid = AppS2w_CidValidate(cid);

    if (INVALID_CID == validCid )
		return S2W_FAILURE;

	/* mode txtest->0,rxtest->1,both ->2*/
    p = AppS2wParse_NextParamGet(&ptr);
	
    if (!p)
    {
        return S2W_EINVAL;
    }
	
    status = AppS2wParse_Int(p, &mode);
    if (status != S2W_SUCCESS)
    {
        return status;
    }	
	if(mode == 4)
		goto skipArgument;
	/* iteration*/
	p = AppS2wParse_NextParamGet(&ptr);
	s2wCidList[validCid].iteration = 10;
	if (p)
	{
		status = AppS2wParse_Int(p, &s2wCidList[validCid].iteration);
		if (status != S2W_SUCCESS)
		{
			return status;
		}	
		
	}		
	p = AppS2wParse_NextParamGet(&ptr);
	if (p)
	{
		status = AppS2wParse_64BitNumber(p,&pktLen);
		if (status != S2W_SUCCESS)
		{
			return status;
		}	
	}
	else
    {
		pktLen = 1460;
    }
	s2wCidList[validCid].bytesToReceive = (ULONG64)(s2wCidList[validCid].iteration * pktLen);
skipArgument:	
	memset(&s2wCidList[validCid].stats,0,sizeof(S2W_TPSTATS_T));	
	s2wCidList[validCid].testMode=mode;		
	s2wCidList[validCid].tpTestInProgress=1;	
	if(s2wCidList[validCid].httpflag && mode < 2)
		return AppS2w_HttpTpTest(validCid,pktLen,ptr);
    if(mode == 3) 
        {
            pktLen=0;
        }
	s2wCidList[validCid].testMode=mode;		
	s2wCidList[validCid].tpTestInProgress=1;	
	memset(&s2wCidList[validCid].stats,0,sizeof(S2W_TPSTATS_T));
	if(mode == 0 || mode == 2 || mode == 3)
	{	seqNo=0;
	
		memset(tpTestBuff ,0xA5A5A5A5,10);
		s2wCidList[validCid].tpTestInProgress=1;			
		wddTxCnt0 = s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipUnicastPktsSent + s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipBroadCastPktsSent	;	
		txBufAllocFail = s2wappMainTaskCtxt->hiCtx.pStats->txBufAllocFail;
		startTime = GsnTod_Get();	
		do
		{
			tpTestBuff[0] = seqNo & 0xff;			
			tpTestBuff[1] = (seqNo >> 8)& 0xff;			
			tpTestBuff[2] = (seqNo>> 16)& 0xff;			
			tpTestBuff[3] = (seqNo>> 24)& 0xff;			
			/*send*/			
			if(mode == 3) 
			{
				if(pktLen >= 1460)
				{
					pktLen =1;
                             }
				else					
				  pktLen++;
			}
			s2wCidList[validCid].stats.lastPktSndTime = SYSTIME_TO_USEC(GsnTod_Get());	
            GsnOsal_SemAcquire ( &dSendSem,GSN_OSAL_WAIT_FOREVER );
#ifdef S2W_IPv6_SUPPORT
           if(s2wCidList[validCid].addrType & ADDR_TYPE_IPv6)
				AppS2wHal_NetTx(validCid, s2wCidList[validCid].remoteIpv6,s2wCidList[validCid].remotePort,
								(VOID *)tpTestBuff, (UINT32)pktLen);
			else
#endif				
			status = AppS2wHal_NetTx(validCid, s2wCidList[validCid].remoteIp,s2wCidList[validCid].remotePort,
									(VOID *)tpTestBuff, (UINT32)pktLen);
            GsnOsal_SemRelease(&dSendSem);                 
			currTime = SYSTIME_TO_USEC(GsnTod_Get());	
			if(status == S2W_FAILURE)
			{

         	if(s2wCidList[validCid].conType == TCP)
                   break;

			 s2wCidList[validCid].stats.txErr++;
			 
			}
			else
				cnt++;
			seqNo++;
			diffTime = currTime - s2wCidList[validCid].stats.lastPktSndTime ;
            if(diffTime <= 1000)
				s2wCidList[validCid].stats.less1MsCnt++;
            else if(diffTime > 20000)			
				s2wCidList[validCid].stats.more20MsCnt++;
            else if(diffTime > 10000)			
				s2wCidList[validCid].stats.more10MsCnt++;
            else if(diffTime > 5000)			
				s2wCidList[validCid].stats.more5MsCnt++;
            else if(diffTime > 3000)				
				s2wCidList[validCid].stats.more3MsCnt++;
			else if(diffTime > 2000)
				s2wCidList[validCid].stats.more2MsCnt++;
			else if(diffTime > 1000)
				s2wCidList[validCid].stats.more1MsCnt++;

		}while(seqNo < s2wCidList[validCid].iteration);
		endTime = GsnTod_Get();
		totalTime = SYSTIME_TO_MSEC(endTime)-SYSTIME_TO_MSEC(startTime); 
		wddTxCnt1 = s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipUnicastPktsSent + s2wappMainTaskCtxt->if0.nwifCtx.pStats->ipBroadCastPktsSent	;	
		if(s2wCidList[validCid].conType == UDP)
		{
			S2w_Printf("\r\n Packet send From App  : %d",seqNo);
			S2w_Printf("\r\n Packet send From WDD  : %d",(wddTxCnt1-wddTxCnt0));
			S2w_Printf("\r\n Packet Lost From APP  : %d",s2wCidList[validCid].stats.txErr);		
			S2w_Printf("\r\n Wdd Tx Buff Fail Cnt  : %d", s2wappMainTaskCtxt->hiCtx.pStats->txBufAllocFail-txBufAllocFail); 
			S2w_Printf("\r\n Delay More Than 20 Ms : %d",s2wCidList[validCid].stats.more20MsCnt);
			S2w_Printf("\r\n Delay More Than 10 Ms : %d",s2wCidList[validCid].stats.more10MsCnt);
			S2w_Printf("\r\n Delay More Than  5 Ms : %d",s2wCidList[validCid].stats.more5MsCnt);
			S2w_Printf("\r\n Delay More Than  3 Ms : %d",s2wCidList[validCid].stats.more3MsCnt);
			S2w_Printf("\r\n Delay More Than  2 Ms : %d",s2wCidList[validCid].stats.more2MsCnt);							
			S2w_Printf("\r\n Delay More Than  1 Ms : %d",s2wCidList[validCid].stats.more1MsCnt);
			S2w_Printf("\r\n Delay Less Than  1 Ms : %d",s2wCidList[validCid].stats.less1MsCnt);
		}
		else if(mode != 3)
		{
			S2w_Printf("\r\n Bytes send  	       : %lld",cnt *pktLen); 

		}			
		if(mode != 3)
		{
		    S2w_Printf("\r\n Total Time Taken      : %lld usec",(SYSTIME_TO_USEC(endTime)-SYSTIME_TO_USEC(startTime)));									
			tp = (((cnt *pktLen*8*1000))/(totalTime));
		    S2w_Printf("\r\n Throuhput             : %lld bps",tp);	
			tp =(((cnt *pktLen*8*1000))/(totalTime*1024));
            S2w_Printf("\r\n Throuhput             : %lld kbps ",tp);	
		}
		if(mode == 0 || mode == 3 )s2wCidList[validCid].tpTestInProgress=0; 
	}
 	return S2W_SUCCESS;
}
#endif


PUBLIC UINT8
AppS2wCmd_IpMulticastJoin(UINT8 *ptr)
{
  UINT8 *p;
  UINT8 status;
  ULONG ip;

  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
  		return S2W_EINVAL;

  status = AppS2wParse_Ip(p, (UINT8 *)&ip);

   if (status != S2W_SUCCESS)
    {
        return status;
    }

   ip = ntohl(ip);

   if(nx_igmp_multicast_join(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,ip) != S2W_SUCCESS)
     return S2W_FAILURE;

   return S2W_SUCCESS;

}

PUBLIC UINT8
AppS2wCmd_IpMulticastLeave(UINT8 *ptr)
{

  UINT8 *p;
  UINT8 status;
  ULONG ip;

  p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
  		return S2W_EINVAL;

  status = AppS2wParse_Ip(p, (UINT8 *)&ip);

   if (status != S2W_SUCCESS)
    {
        return status;
    }

   ip = ntohl(ip);

   if(nx_igmp_multicast_leave(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,ip) != S2W_SUCCESS)
     return S2W_FAILURE;

   return S2W_SUCCESS;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+DGPIO command
 *      This function sets or resets the specified GPIO pin
 * @param ptr Pointer to the user input string.
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Dgpio(UINT8 *ptr)
{
    UINT32 bit, operation;
    UINT8 *p, status;
    static UINT8 enableGpio=0;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Int(p, &bit);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if(!((S2W_GPIO_UNDER_USE) & (1 << bit)))
    {/* This GPIO can not be used for testing - currently its used as peripheral pin  */
        return S2W_EINVAL;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Int(p, &operation);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if(operation > 1)
    {
        return S2W_EINVAL;
    }
    if(!enableGpio)
    {
        // eanble all gpios available only once for first command
        GsnIoMux_Sel(4, GSN_IOMUX_GPIO_4_AGPIO_4);
        GsnIoMux_Sel(5, GSN_IOMUX_GPIO_5_AGPIO_5);
        GsnIoMux_Sel(6, GSN_IOMUX_GPIO_6_AGPIO_6);
        GsnIoMux_Sel(7, GSN_IOMUX_GPIO_7_AGPIO_7);
#ifndef GS2100
        GsnIoMux_Sel(9, GSN_IOMUX_GPIO_9_AGPIO_9);
#endif
        GsnIoMux_Sel(20, GSN_IOMUX_GPIO_20_AGPIO_20);
        GsnIoMux_Sel(21, GSN_IOMUX_GPIO_21_AGPIO_21);
        GsnIoMux_Sel(29, GSN_IOMUX_GPIO_29_AGPIO_29);
        GsnIoMux_Sel(30, GSN_IOMUX_GPIO_30_AGPIO_30);
        GsnIoMux_Sel(31, GSN_IOMUX_GPIO_31_AGPIO_31);
    }

    /* Call GPIO Init as out direction  */
    GsnGpio_Init((1 << bit), ~(1 << bit));

    if(operation)
    {
        GsnGpio_OutIndvidualSet(1 << bit);
    }
    else
    {
        GsnGpio_OutClear(1 << bit);
    }
    return S2W_SUCCESS;
}

#ifdef S2W_SECURITY_WPS_ENABLE

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WWPS Command.
 *   This command check the validity of parameters passed and call the
 *   hal association function.
 * @param ptr pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure-scan failed.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_Wwps(UINT8 *ptr)
{
#if 1
    S2W_WPS_T params;
    GSN_MAC_SSID_T ap_ssid;
    UINT8 *p;
    UINT8 status;
    UINT8 zeroPin[GSN_WDD_SEC_WPS_PIN_LEN] = {0};
    UINT8 i;
#ifdef GSN_P2P
    UINT8 method=0;
#endif

    ap_ssid.length = 0;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &params.type);
    if(!(params.type == APP_WPS_TYPE_PB || params.type == APP_WPS_TYPE_PIN || params.type == APP_WPS_TYPE_DFLT_PIN) )
    {
        return S2W_EINVAL;
    }

    if(params.type == APP_WPS_TYPE_PIN || params.type == APP_WPS_TYPE_DFLT_PIN)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }
        if(GSN_WDD_SEC_WPS_PIN_LEN != strlen((const char*)p))
        {
            return S2W_EINVAL;
        }
        for(i=0; i< GSN_WDD_SEC_WPS_PIN_LEN; i++)
        {
            if( *(p+i) < '0' || *(p+i) > '9')
            {
                return S2W_EINVAL;
            }
            //*(p+i)= *(p+i)-'0'; /* convert to integer */
            //*(p+i)= *(p+i);
        }
        memcpy(params.pin, p, GSN_WDD_SEC_WPS_PIN_LEN);
#ifdef GSN_P2P
        method = 0;
#endif
        p = AppS2wParse_NextParamGet( &ptr );
        if (p)
        {
            status = AppS2wParse_Ssid(p, ap_ssid.array, &ap_ssid.length );
        }
    }
    else
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (p)
        {/* we donot expect a pin in case of PB mathod*/
            /*return S2W_EINVAL;*/
        }
        memcpy(params.pin, zeroPin, GSN_WDD_SEC_WPS_PIN_LEN);
#ifdef GSN_P2P
        method=1;
#endif
    }
	params.storeL2ConInfo = 0;
	p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {/* we donot expect a pin in case of PB mathod*/
        AppS2wParse_Boolean(p, &params.storeL2ConInfo);
    }
#ifdef GSN_P2P
    if(s2wCurrent.mode == 3)
    {
        GSN_WDD_P2P_CONF_T* p2pConf;

        /* get the P2P info */
        p2pConf = GsnWdd_P2pConfPtrGet(&s2wappMainTaskCtxt->wdd);

        if(p2pConf->roleGo == P2P_ROLE_GO)
        {
            status = GsnWdd_P2pProvStart(&s2wappMainTaskCtxt->wdd,method,params.pin);
        }
        else
        {
            status = AppS2wHal_WpsAssociate(&params, &ap_ssid,0);
        }
    }
    else
#endif
    {
        status = AppS2wHal_WpsAssociate(&params, &ap_ssid,0);
    }

    return status;


#else
    S2W_WPS_T params;
    GSN_MAC_SSID_T ap_ssid;
    UINT8 *p;
    UINT8 status;
    UINT8 zeroPin[GSN_WDD_SEC_WPS_PIN_LEN] = {0};
    UINT8 i;
#ifdef GSN_P2P
    UINT8 method=0;
#endif

    ap_ssid.length = 0;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &params.type);
    if(!(params.type == APP_WPS_TYPE_PB || params.type == APP_WPS_TYPE_PIN))
    {
        return S2W_EINVAL;
    }

    if(params.type == APP_WPS_TYPE_PIN)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }
        if(GSN_WDD_SEC_WPS_PIN_LEN != strlen((const char*)p))
        {
            return S2W_EINVAL;
        }
        for(i=0; i< GSN_WDD_SEC_WPS_PIN_LEN; i++)
        {
            if( *(p+i) < '0' || *(p+i) > '9')
            {
                return S2W_EINVAL;
            }
            *(p+i)= *(p+i)-'0'; /* convert to integer */
        }
        memcpy(params.pin, p, GSN_WDD_SEC_WPS_PIN_LEN);
#ifdef GSN_P2P
        method = 0;
#endif
        p = AppS2wParse_NextParamGet( &ptr );
        if (p)
        {
            status = AppS2wParse_Ssid(p, ap_ssid.array, &ap_ssid.length );
        }
    }
    else
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (p)
        {/* we donot expect a pin in case of PB mathod*/
            /*return S2W_EINVAL;*/
        }
        memcpy(params.pin, zeroPin, GSN_WDD_SEC_WPS_PIN_LEN);
#ifdef GSN_P2P
        method=1;
#endif
    }
	params.storeL2ConInfo = 0;
	p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {/* we donot expect a pin in case of PB mathod*/
        AppS2wParse_Boolean(p, &params.storeL2ConInfo);
    }
#ifdef GSN_P2P
    if(s2wCurrent.mode == 3)
    {
        GSN_WDD_P2P_CONF_T* p2pConf;

        /* get the P2P info */
        p2pConf = GsnWdd_P2pConfPtrGet(&s2wappMainTaskCtxt->wdd);

        if(p2pConf->roleGo == P2P_ROLE_GO)
        {
            status = GsnWdd_P2pProvStart(&s2wappMainTaskCtxt->wdd,method,params.pin);
        }
        else
        {
            status = AppS2wHal_WpsAssociate(&params, &ap_ssid,0);
        }
    }
    else
#endif
    {
        status = AppS2wHal_WpsAssociate(&params, &ap_ssid,0);
    }

    return status;
#endif
}
#endif /* GSN_SECURITY_WPS_ENABLE */

#ifdef S2W_PERSISTENT_TMR_SUPPORT

VOID
AppS2w_PersistentTmrCb(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
    switch ((UINT32)ptr)
    {
        case 0:
            AppMainCtx_TaskNotify(APP_EVENT_PERSISTANT_TMR_0_TIMEOUT);
            break;
        case 1:
            AppMainCtx_TaskNotify(APP_EVENT_PERSISTANT_TMR_1_TIMEOUT);
            break;
        case 2:
            AppMainCtx_TaskNotify(APP_EVENT_PERSISTANT_TMR_2_TIMEOUT);
            break; 
        case 3:
            AppMainCtx_TaskNotify(APP_EVENT_PERSISTANT_TMR_3_TIMEOUT);
            break;
        case 4:
            AppMainCtx_TaskNotify(APP_EVENT_PERSISTANT_TMR_4_TIMEOUT);
            break;    
    }
}

PUBLIC UINT8 
AppS2wCmd_PerstTmrStart(UINT8 *ptr)
{
	UINT8 *p;
	UINT32 time, status, id, type;
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &id);
    if(id > APP_NUM_OF_PERSIST_TMR)
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &type);
    if(type > GSN_TIMER_TYPE_PERSISTENT_VARIABLE )
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    if(AppS2wParse_Int(p, &time))
    {
        return S2W_EINVAL;
    }
    if(GsnPersistTmr_IsActive(id))
    {
        return S2W_FAILURE;
    }
    
    status = GsnPersistTmr_Create( id, type, MSEC_TO_SYSTIME(time) , 
        AppS2w_PersistentTmrCb, (void *)id, TRUE);
    if(status == GSN_SUCCESS)
        return S2W_SUCCESS;
    else
        return S2W_FAILURE;
}
PUBLIC UINT8
AppS2wCmd_PerstTmrStop(UINT8 *ptr)
{
    UINT32 id, status;
    UINT8 *p;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &id);
    if(id > APP_NUM_OF_PERSIST_TMR)
    {
        return S2W_EINVAL;
    }
    status = GsnPersistTmr_Stop(id);
    if(status == GSN_SUCCESS)
        return S2W_SUCCESS;
    else
        return S2W_FAILURE;
}
PUBLIC UINT8
AppS2wCmd_PerstTmrDelete(UINT8 *ptr)
{
	UINT32 id, status;
	UINT8 *p;
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
    {
        return S2W_EINVAL;
    }
	AppS2wParse_Int(p, &id);
	if(id > APP_NUM_OF_PERSIST_TMR)
	{
		return S2W_EINVAL;
	}
	status = GsnPersistTmr_Delete(id);
	if(status == GSN_SUCCESS)
		return S2W_SUCCESS;
	else
		return S2W_FAILURE;

}
PUBLIC UINT8
AppS2wCmd_PerstTmrReStart(UINT8 *ptr)
{
	UINT32 id, status, period;
	UINT8 *p;
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
    {
        return S2W_EINVAL;
    }
	AppS2wParse_Int(p, &id);
	if(id > APP_NUM_OF_PERSIST_TMR)
	{
		return S2W_EINVAL;
	}
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
    {
        return S2W_EINVAL;
    }
	AppS2wParse_Int(p, &period);
	if(id > APP_NUM_OF_PERSIST_TMR)
	{
		return S2W_EINVAL;
	}
	status = GsnPersistTmr_ReStart(id, period, GSN_P_TMR_PREV_EXP_TIME);
	if(status == GSN_SUCCESS)
		return S2W_SUCCESS;
	else
		return S2W_SUCCESS;
}
#endif
#ifdef S2W_EMU
/* Commands for EMU */
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUVER=? command
 *   This function gives the version of EMU.
 *   
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * 
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuVer(UINT8 *ptr)
{
    UINT8 buf[20];

    if (ptr[0] == '?' && ( ptr[1] == '\0') )
    {
	GsnEmu_GetVersion(buf);
	S2w_Printf("\r\n%s\r\n",&buf);
        return S2W_SUCCESS;
    }   
    else
    {
        return S2W_FAILURE;
    }
} 

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUSUPMOD=? command
 *   This function tells  EMU supported modules
 *   
 * @param ptr Pointer to the user input string.
 * @return (OR'ed value of the modules)
 *         1 - Sigma Delta ADC 
 *         2 - PL7223 
 * @return S2W_SUCCESS - operation successful.
 *
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_SupportedModules(UINT8 *ptr)
{
    UINT32 value;
	
    if (ptr[0] == '?' && ( ptr[1] == '\0') )
    {
    	value = GsnEmu_GetSupportedModules();
	S2w_Printf("\r\n%02x\r\n",value); 
        return S2W_SUCCESS; 
    }
    else
    {
        return S2W_FAILURE;
    }       
} 

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMULOADCTRL=<action>(ON or OFF) command
 *   This function loads the EMU control when it is in Running state.
 *   
 * @param ptr Pointer to the user input string.
 *                      1 - ON , 0 - OFF
 * @return S2W_SUCCESS - operation successful.
 * @return EMU STATUS   
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/

PRIVATE UINT8
AppS2wCmd_EmuLoadCtl(UINT8 *ptr)
{

    GSN_EMU_STATUS_T status;
    UINT8 estatus;
    BOOL mode;

    estatus = AppS2wParse_Boolean(ptr, (UINT8 *)&mode);
    
    if (estatus != S2W_SUCCESS)
    {
        return estatus;
    }  
    
    status = GsnEmu_LoadControl(&(appCtx.appEmuCtx.emu),mode);
  
    if (GSN_EMU_STATUS_SUCCESS == status )
    {    
        return S2W_SUCCESS; 
    }
    else
    {
        return S2W_FAILURE;
    }
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMULOADSTATUS command
 *   This function loads the  EMU status.
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS   - operation successful.
 * @return S2W_EINVAL    - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuLoadStatus(UINT8 *ptr)
{	 
    GSN_EMU_STATUS_T status;
    BOOL mode;
    
    if (ptr[0] == '\0')
    {
        status = GsnEmu_GetLoadStatus(&(appCtx.appEmuCtx.emu), &mode);
          
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            if(1 == mode)
            {
                S2w_Printf("\r\nON\r\n");	
            }
            else if(0 == mode)
            {
                S2w_Printf("\r\nOFF\r\n"); 
            }
            return S2W_SUCCESS;
        }
        else
        {
            return S2W_FAILURE;
        }
    }
    else 
    {
	return S2W_EINVAL;
    }
		
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUSTART command
 *   This function starts the EMU
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS   - operation successful.
 * @return EMU STATUS   
  * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuStart(UINT8 *ptr)
{
    GSN_EMU_STATUS_T status = GSN_EMU_STATUS_FAILURE;
    GSN_EMU_SDADC_PINGPONG_BUFF_T buff;
    
    GSN_EMU_STATE_T state;

    /* Configurations can't be set when the system is RUNNING */
    GsnEmu_GetState(&(appCtx.appEmuCtx.emu), &state); 
    
    if( state == GSN_EMU_STATE_RUNNING )
    {
       return S2W_FAILURE;      
    }
    
    if (ptr[0] == '\0')
    {   
        if(appCtx.appEmuCtx.confValue.module == GSN_EMU_MODULE_SIGMADELTA_ADC )
        {
            if(GSN_EMU_STATUS_SUCCESS == AppEmu_BuffAllocate())
            {
                buff.vPriBuff = appCtx.appEmuCtx.appEmuSdadcPbuf1;
                buff.iPriBuff = appCtx.appEmuCtx.appEmuSdadcPbuf2;
                buff.vSecBuff = appCtx.appEmuCtx.appEmuSdadcPbuf3;
                buff.iSecBuff = appCtx.appEmuCtx.appEmuSdadcPbuf4;
                buff.size = APP_EMU_SDADC_BUF_SIZE;
            }
            else
            {
              return S2W_FAILURE;
            }
            status = GsnEmu_Start(&(appCtx.appEmuCtx.emu),&(appCtx.appEmuCtx.confValue),&buff);
        }
        else if(appCtx.appEmuCtx.confValue.module == GSN_EMU_MODULE_PL722X )
        {
            status = GsnEmu_Start(&(appCtx.appEmuCtx.emu),&(appCtx.appEmuCtx.confValue),NULL);
        }
        
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            return S2W_SUCCESS;
        }
        else
        {
          return S2W_FAILURE;
        }
    }
    else 
    {
	return S2W_EINVAL;
    }
		
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUSTOP command
 *   This function stops the EMU
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS   - operation successful.
 * @return EMU STATUS   
  * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuStop(UINT8 *ptr)
{
    GSN_EMU_STATUS_T status;   
    
    if (ptr[0] == '\0')
    {
        status =  GsnEmu_Stop(&(appCtx.appEmuCtx.emu));
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            if(appCtx.appEmuCtx.confValue.module == GSN_EMU_MODULE_SIGMADELTA_ADC)
            {
                if(GSN_EMU_STATUS_SUCCESS == AppEmu_BuffDeallocate())
                {     
                     return S2W_SUCCESS;
                }
                else 
                {
                    return S2W_FAILURE;
                }
            }
            return S2W_SUCCESS;
        }
        else
        {
            return S2W_FAILURE;
        }
    }
    else 
    {
	return S2W_EINVAL;
    }
		
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUGETVALUES command
 *   This function returns the various values associated with EMU.
 *   
 * @param ptr Pointer to the user input string.
 * @return EMU VALUES    - Voltage,Current,Power,Energy,Frequency & 
 *                          Power factor 
 * @return S2W_SUCCESS   - operation successful.
 * @return S2W_EINVAL    - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuGetValues(UINT8 *ptr)
{
    GSN_EMU_ELECTRIC_PARAMS_T eparam;
    GSN_EMU_STATUS_T status;
    
    if (ptr[0] == '\0')
    {
        status = GsnEmu_GetElectricParams(&(appCtx.appEmuCtx.emu),&eparam);
        
  	if(GSN_EMU_STATUS_SUCCESS == status )
        {
            S2w_Printf("\r\nV=%07.3fV\r\n",eparam.vrms);                    
            S2w_Printf("I=%07.3fA\r\n",eparam.irms);	
            S2w_Printf("AP=%07.3fW\r\n",eparam.activePower);
            S2w_Printf("PF=%07.3f\r\n",eparam.powerfactor);
            S2w_Printf("F=%07.3fHz\r\n",eparam.frequency);
            S2w_Printf("E=%07.3fKWH\r\n",eparam.accumulateEnergy);
            return S2W_SUCCESS;
        }
        else
        {
            return S2W_FAILURE;
        }
    }
    else
    {
        return S2W_EINVAL;
    }    
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUGETINTSVALUES command
 *   This function returns the various values associated with EMU.
 *   
 * @param ptr Pointer to the user input string.
 * @return EMU INSTANTVALUES    - Voltage,Current,Power,Energy,
 *                                 Frequency & Power factor 
 *                          
 * @return S2W_SUCCESS   - operation successful.
 * @return S2W_EINVAL    - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuGetInstValues(UINT8 *ptr)
{
    GSN_EMU_ELECTRIC_PARAMS_T eparam;
    GSN_EMU_STATUS_T status;
    
    if (ptr[0] == '\0')
    {
        status = GsnEmu_GetInstantElectricParams(&(appCtx.appEmuCtx.emu),&eparam);
        
  	if(GSN_EMU_STATUS_SUCCESS == status )
        {
            S2w_Printf("\r\nV=%07.3fV\r\n",eparam.vrms);                    
            S2w_Printf("I=%07.3fA\r\n",eparam.irms);	
            S2w_Printf("AP=%07.3fW\r\n",eparam.activePower);
            S2w_Printf("PF=%07.3f\r\n",eparam.powerfactor);
            S2w_Printf("F=%07.3fHz\r\n",eparam.frequency);
            S2w_Printf("E=%07.3fKWH\r\n",eparam.accumulateEnergy);
            return S2W_SUCCESS;
        }
        else
        {
            return S2W_FAILURE;
        }
    }
    else
    {
        return S2W_EINVAL;
    }    
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUSETCONF = 'param','value' command
 *   This function sets the various parameters of EMU.
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL    - invalid input
 ******************************************************************/

PRIVATE UINT8
AppS2wCmd_EmuSetConf(UINT8 *ptr)
{
    UINT8 *p;
    APP_EMU_CONFS_T conf;
    UINT32 value;
    UINT32 param;
    UINT32 modcheck;
    UINT32 modvalue;
    
    GSN_EMU_STATE_T state;

    /* Configurations can't be set when the system is RUNNING */
    GsnEmu_GetState(&(appCtx.appEmuCtx.emu), &state); 
    
   if( state == GSN_EMU_STATE_RUNNING )
   {
      return S2W_EINVAL;      
   }
    
    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &param);
    
    conf = ( APP_EMU_CONFS_T )param;

    if(param >APP_EMU_END)
    {
 	return S2W_FAILURE;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p,&value); 
    
    if( NULL == p)
    {
        return S2W_EINVAL;
    
    }
      
    switch(conf)
    {
        case APP_EMU_CONF_MODULE : 
                modcheck = GsnEmu_GetSupportedModules();
               
                if((value < modcheck) && (((value)&(value-1)) == 0 ) && (value!= 0))
                {
                    appCtx.appEmuCtx.confValue.module = (GSN_EMU_MODULE_T)value;
                }
                else
                {
                   return S2W_EINVAL;
                }
            break;
        case APP_EMU_CONF_SDADC_VCC :        
		appCtx.appEmuCtx.confValue.sdadc_vcc = value;
            
            break;          
        case APP_EMU_CONF_SDADC_ICC:
		appCtx.appEmuCtx.confValue.sdadc_icc = value;
          
            break;
        case APP_EMU_CONF_SDADC_VDCOFFSET:     
		appCtx.appEmuCtx.confValue.sdadc_vdcoffset = value;
           
            break;
        case APP_EMU_CONF_SDADC_IDCOFFSET:     
        	appCtx.appEmuCtx.confValue.sdadc_idcoffset = value;
            
            break;
        case APP_EMU_CONF_SDADC_VSF:     
            	appCtx.appEmuCtx.confValue.sdadc_vsf = value;
            
            break;
        case APP_EMU_CONF_SDADC_ISF:     
            	appCtx.appEmuCtx.confValue.sdadc_isf = value;
            
            break;
        case APP_EMU_CONF_SDADC_SF:     
		appCtx.appEmuCtx.confValue.sdadc_samplingFreq = value;
      
                
            break;    
        case APP_EMU_CONF_SDADC_LCG:
            /*valid gpio numbers are 0 - 37*/
            if((value < 38))
            {
                appCtx.appEmuCtx.confValue.sdadc_load_gpio = value;
            }
            else 
            return S2W_EINVAL;

            break;
        case APP_EMU_CONF_SDADC_VUT:     
                appCtx.appEmuCtx.confValue.sdadc_vut = value;
            
            break;
        case APP_EMU_CONF_SDADC_IUT:     
            	appCtx.appEmuCtx.confValue.sdadc_iut = value;
            
            break;
        case APP_EMU_CONF_SDADC_FUT:     
          	appCtx.appEmuCtx.confValue.sdadc_fut =value;	
            
            break;
        case APP_EMU_CONF_SDADC_VLT:     
       		appCtx.appEmuCtx.confValue.sdadc_vlt = value;
            
            break;
        case APP_EMU_CONF_SDADC_ILT:     
       		appCtx.appEmuCtx.confValue.sdadc_ilt = value;
            
            break;
        case APP_EMU_CONF_SDADC_FLT:     
       		appCtx.appEmuCtx.confValue.sdadc_flt = value;
            
            break;
        case APP_EMU_CONF_SDADC_VAC:     
         
              if(0 == value  )
              {
                  /* 0 refers to adc channel zero */
                  appCtx.appEmuCtx.confValue.sdadc_vac = GSN_EMU_SDADC_CHANNEL_0;
              }
              else if( 1 == value )
              {
                  /* 1 refers to adc channel one */
                  appCtx.appEmuCtx.confValue.sdadc_vac = GSN_EMU_SDADC_CHANNEL_1;
              }
              else if(2 == value )
              {
                  /* 2 refers to adc channel two */
                  appCtx.appEmuCtx.confValue.sdadc_vac = GSN_EMU_SDADC_CHANNEL_2;
              }
              else
                return S2W_EINVAL;
              break;
            
        case APP_EMU_CONF_SDADC_IAC: 
          
              if( 0 == value  )
              {
                  /* 0 refers to adc channel zero */
                  appCtx.appEmuCtx.confValue.sdadc_iac = GSN_EMU_SDADC_CHANNEL_0;
              }
              else if( 1 == value )
              {
                   /* 1 refers to adc channel one */
                  appCtx.appEmuCtx.confValue.sdadc_iac = GSN_EMU_SDADC_CHANNEL_1;
              }
              else if( 2 == value )
              {
                  /* 2 refers to adc channel two */
                  appCtx.appEmuCtx.confValue.sdadc_iac = GSN_EMU_SDADC_CHANNEL_2;
              }
              else
                return S2W_EINVAL;
              break;
              
         case APP_EMU_CONF_SDADC_G0: 
           
              p = AppS2wParse_NextParamGet(&ptr);
              AppS2wParse_Int(p,&modvalue);
                   
              if((1 == value ) && (NULL != p))
              {
                  /* Gain value can be 0,1,2 or 3 */
                  if(0 == modvalue )
                  {     
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag0 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain0 = GSN_EMU_SDADC_GAIN0;
                  }
                  else if( 1 == modvalue )
                  {
                    /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag0 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain0 = GSN_EMU_SDADC_GAIN1;
                  }
                  else if( 2 == modvalue )
                  {
                    /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag0 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain0 = GSN_EMU_SDADC_GAIN2;
                  }
                  else if( 3 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag0 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain0 = GSN_EMU_SDADC_GAIN3;
                  }
                  else 
                    return S2W_EINVAL;
                  break;
              }
    
             else if (( 0 == value ) && (NULL == p))
              {
                  appCtx.appEmuCtx.confValue.gain_flag0 = value;
              }
              
              else
              {
                  return S2W_EINVAL;
              }
               break;
              
         case APP_EMU_CONF_SDADC_G1: 
                   
            p = AppS2wParse_NextParamGet(&ptr);
            AppS2wParse_Int(p,&modvalue); 
            
            if((1 == value ) && (NULL != p))
              {

                  /* Gain value can be 0,1,2 or 3 */
                  if(0 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag1 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain1 = GSN_EMU_SDADC_GAIN0;
                  }
                  else if( 1 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag1 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain1 = GSN_EMU_SDADC_GAIN1;
                  }
                  else if( 2 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag1 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain1 = GSN_EMU_SDADC_GAIN2;
                  }
                  else if( 3 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag1 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain1 = GSN_EMU_SDADC_GAIN3;
                  }
                  else 
                    return S2W_EINVAL;
                  break;
              }
    
             else if (( 0 == value ) && (NULL == p))
              {
                  appCtx.appEmuCtx.confValue.gain_flag1 = value;
              }
              
              else
              {
                  return S2W_EINVAL;
              }
               break;
            
         case APP_EMU_CONF_SDADC_G2: 
           
              p = AppS2wParse_NextParamGet(&ptr);
              AppS2wParse_Int(p,&modvalue);
           
             if((1 == value ) && (NULL != p))
              {

                  /* Gain value can be 0,1,2 or 3 */
                  if(0 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag2 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain2 = GSN_EMU_SDADC_GAIN0;
                  }
                  else if( 1 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag2 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain2 = GSN_EMU_SDADC_GAIN1;
                  }
                  else if( 2 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag2 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain2 = GSN_EMU_SDADC_GAIN2;
                  }
                  else if( 3 == modvalue )
                  {
                      /*enables the gain*/
                      appCtx.appEmuCtx.confValue.gain_flag2 = value;
                      appCtx.appEmuCtx.confValue.sdadc_gain2 = GSN_EMU_SDADC_GAIN3;
                  }
                  else 
                    return S2W_EINVAL;
                  break;
              }
    
              else if (( 0 == value ) && (NULL == p))
              {
                  appCtx.appEmuCtx.confValue.gain_flag2 = value;
              }
              
              else
              {
                  return S2W_EINVAL;
              }
             break;
           
			 
		case APP_EMU_CONF_SDADC_ATTENCONST:
		{
            //appCtx.appEmuCtx.emu.attenuationConstFp = value;
		    break;
		}

        case APP_EMU_CONF_PL722X_SPI_CHANNEL:   
          
              if( (1 == value) || (0 == value))
              {
                  appCtx.appEmuCtx.confValue.pl722x_spi_channel = value;
              }
              else 
              return S2W_EINVAL;
            
            break;
        case APP_EMU_CONF_PL722X_SET_FREQ_MS:     
         	appCtx.appEmuCtx.confValue.pl722x_readFreq_ms = value;
                
            break;
	case APP_EMU_CONF_PL722X_CS_GPIO:
          /*valid gpio numbers are 0 - 37*/
            if((value < 38))
            {
		appCtx.appEmuCtx.confValue.pl722x_gpio_cs = value;
            }
            else 
            return S2W_EINVAL;
                
            break;
	case APP_EMU_CONF_PL722X_RST_GPIO:
          /*valid gpio numbers are 0 - 37*/
            if((value < 38))
            {
		appCtx.appEmuCtx.confValue.pl722x_gpio_rst = value;
            }
            else 
            return S2W_EINVAL;
                
            break;
        default:
             return S2W_EINVAL;
            break;
           
    }
     return S2W_SUCCESS;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUGETCONF = 'value' command
 *   This function returns the various parameters of EMU .
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS   - operation successful.
 * @return S2W_EINVAL    - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuGetConf(UINT8 *ptr)
{
    UINT8 *p;
    UINT32 param;
    APP_EMU_CONFS_T conf;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &param);
    
    conf = (APP_EMU_CONFS_T) param;   
    GsnEmu_GetConfPtr(&(appCtx.appEmuCtx.emu), &(appCtx.appEmuCtx.confValue));
    
    if((param > APP_EMU_END))
    {
 	return S2W_EINVAL;
    }
	
   	switch(conf)
        {
            case APP_EMU_CONF_MODULE:
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.module);  
                 
                 break;
            case APP_EMU_CONF_SDADC_VCC :
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_vcc);    
                 
                 break;
            case APP_EMU_CONF_SDADC_ICC:
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_icc);          
                 
                 break;
            case APP_EMU_CONF_SDADC_VDCOFFSET:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_vdcoffset);          
                 
                 break;
            case APP_EMU_CONF_SDADC_IDCOFFSET:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_idcoffset);          
                 
                 break;
            case APP_EMU_CONF_SDADC_VSF:     
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.sdadc_vsf);          
                 
                 break;
            case APP_EMU_CONF_SDADC_ISF:     
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.sdadc_isf);          
                 
                 break;
            case APP_EMU_CONF_SDADC_SF:     
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.sdadc_samplingFreq);          
                 
                 break;
            case APP_EMU_CONF_SDADC_LCG:     
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.sdadc_load_gpio);          
                 
                 break;
            case APP_EMU_CONF_SDADC_VUT:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_vut);          
                 
                 break;
            case APP_EMU_CONF_SDADC_IUT:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_iut);          
                 
                 break;
            case APP_EMU_CONF_SDADC_FUT:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_fut);          
                 
                 break;
            case APP_EMU_CONF_SDADC_VLT:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_vlt);          
                 
                 break;
            case APP_EMU_CONF_SDADC_ILT:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_ilt);          
                 
                 break;
            case APP_EMU_CONF_SDADC_FLT:     
                 S2w_Printf("\r\n%f\r\n",appCtx.appEmuCtx.confValue.sdadc_flt);          
                 
                 break;
            case APP_EMU_CONF_SDADC_VAC:       
                 
                 if(GSN_EMU_SDADC_CHANNEL_0 == appCtx.appEmuCtx.confValue.sdadc_vac)
                 {
                     S2w_Printf("\r\n0\r\n");  
                 }
                 else if(GSN_EMU_SDADC_CHANNEL_1 == appCtx.appEmuCtx.confValue.sdadc_vac)
                 {
                     S2w_Printf("\r\n1\r\n");  
                 }
                 else if(GSN_EMU_SDADC_CHANNEL_2 == appCtx.appEmuCtx.confValue.sdadc_vac)
                 {
                     S2w_Printf("\r\n2\r\n");  
                 }
                 
                 break;
            case APP_EMU_CONF_SDADC_IAC:      
                 
                 if(GSN_EMU_SDADC_CHANNEL_0 == appCtx.appEmuCtx.confValue.sdadc_iac)
                 {
                     S2w_Printf("\r\n0\r\n");  
                 }
                 else if(GSN_EMU_SDADC_CHANNEL_1 == appCtx.appEmuCtx.confValue.sdadc_iac)
                 {
                     S2w_Printf("\r\n1\r\n");  
                 }
                 else if(GSN_EMU_SDADC_CHANNEL_2 == appCtx.appEmuCtx.confValue.sdadc_iac)
                 {
                     S2w_Printf("\r\n2\r\n");  
                 }
                 
                 break;
            case APP_EMU_CONF_SDADC_G0:
              
                /*check for verbose or nonverbose mode*/
                if(0 == s2wCurrent.serialPortConf.commonConf.verbose )
                {
                     if ( appCtx.appEmuCtx.confValue.gain_flag0 == 0)
                     {
                        S2w_Printf("\r\n0\r\n");
                        break;
                     }
                     else if( appCtx.appEmuCtx.confValue.gain_flag0 == 1)
                     {
                         if( GSN_EMU_SDADC_GAIN0 == appCtx.appEmuCtx.confValue.sdadc_gain0 )
                         {
                           S2w_Printf("\r\n1:0\r\n");  
                         }
                         else if(GSN_EMU_SDADC_GAIN1 == appCtx.appEmuCtx.confValue.sdadc_gain0)
                         {
                           S2w_Printf("\r\n1:1\r\n");  
                         }
                         else if(GSN_EMU_SDADC_GAIN2 == appCtx.appEmuCtx.confValue.sdadc_gain0)
                         {
                           S2w_Printf("\r\n1:2\r\n");  
                         }
                         else if(GSN_EMU_SDADC_GAIN3 == appCtx.appEmuCtx.confValue.sdadc_gain0)
                         {
                           S2w_Printf("\r\n1:3\r\n");  
                         }
                         
                         break;
                     }
                }
                else if(1 == s2wCurrent.serialPortConf.commonConf.verbose)
                {
                    if ( appCtx.appEmuCtx.confValue.gain_flag0 == 0)
                    {
                       S2w_Printf("\r\ndisabled\r\n");
                       break;
                    }
                    else if( appCtx.appEmuCtx.confValue.gain_flag0 == 1)
                    {
                        if(GSN_EMU_SDADC_GAIN0 == appCtx.appEmuCtx.confValue.sdadc_gain0  )
                        {
                          S2w_Printf("\r\nenabled:06db\r\n");  
                        }
                        else if(GSN_EMU_SDADC_GAIN1 == appCtx.appEmuCtx.confValue.sdadc_gain0)
                        {
                          S2w_Printf("\r\nenabled:12db\r\n");  
                        }
                        else if(GSN_EMU_SDADC_GAIN2 == appCtx.appEmuCtx.confValue.sdadc_gain0 )
                        {
                          S2w_Printf("\r\nenabled:18db\r\n");  
                        }
                        else if(GSN_EMU_SDADC_GAIN3 == appCtx.appEmuCtx.confValue.sdadc_gain0)
                        {
                          S2w_Printf("\r\nenabled:24db\r\n");  
                        }
                       
                        break;
                     }
                }
                 
           case APP_EMU_CONF_SDADC_G1:
             
             /*check for verbose or nonverbose mode*/
                if(0 == s2wCurrent.serialPortConf.commonConf.verbose )
                {
                     if ( appCtx.appEmuCtx.confValue.gain_flag1 == 0)
                     {
                        S2w_Printf("\r\n0\r\n");
                        break;
                     }
                     else if( appCtx.appEmuCtx.confValue.gain_flag1 == 1)
                     {
                         if(GSN_EMU_SDADC_GAIN0 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                         {
                           S2w_Printf("\r\n1:0\r\n");  
                         }
                         else if(GSN_EMU_SDADC_GAIN1 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                         {
                           S2w_Printf("\r\n1:1\r\n");  
                         }
                         else if(GSN_EMU_SDADC_GAIN2 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                         {
                           S2w_Printf("\r\n1:2\r\n");  
                         }
                         else if( GSN_EMU_SDADC_GAIN3 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                         {
                           S2w_Printf("\r\n1:3\r\n");  
                         }
                         
                         break;
                     }
                }
                else if(1 == s2wCurrent.serialPortConf.commonConf.verbose)
                {
                    if ( appCtx.appEmuCtx.confValue.gain_flag1 == 0)
                    {
                       S2w_Printf("\r\ndisabled\r\n");
                       break;
                    }
                    else if( appCtx.appEmuCtx.confValue.gain_flag1 == 1)
                    {
                        if( GSN_EMU_SDADC_GAIN0 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                        {
                          S2w_Printf("\r\nenabled:06db\r\n");  
                        }
                        else if(GSN_EMU_SDADC_GAIN1 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                        {
                          S2w_Printf("\r\nenabled:12db\r\n");  
                        }
                        else if(GSN_EMU_SDADC_GAIN2 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                        {
                          S2w_Printf("\r\nenabled:18db\r\n");  
                        }
                        else if( GSN_EMU_SDADC_GAIN3 == appCtx.appEmuCtx.confValue.sdadc_gain1)
                        {
                          S2w_Printf("\r\nenabled:24db\r\n");  
                        }
                       
                        break;
                     }
                }
              

           case APP_EMU_CONF_SDADC_G2:
             
                /*check for verbose or nonverbose mode*/
                if(0 == s2wCurrent.serialPortConf.commonConf.verbose )
                {
                     if ( appCtx.appEmuCtx.confValue.gain_flag2 == 0)
                     {
                        S2w_Printf("\r\n0\r\n");
                        break;
                     }
                     else if( appCtx.appEmuCtx.confValue.gain_flag2 == 1)
                     {
                         if(GSN_EMU_SDADC_GAIN0 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                         {
                           S2w_Printf("\r\n1:0\r\n");  
                         }
                         else if(GSN_EMU_SDADC_GAIN1 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                         {
                           S2w_Printf("\r\n1:1\r\n");  
                         }
                         else if( GSN_EMU_SDADC_GAIN2 == appCtx.appEmuCtx.confValue.sdadc_gain2 )
                         {
                           S2w_Printf("\r\n1:2\r\n");  
                         }
                         else if( GSN_EMU_SDADC_GAIN3 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                         {
                           S2w_Printf("\r\n1:3\r\n");  
                         }
                         
                         break;
                     }
                }
                else if(1 == s2wCurrent.serialPortConf.commonConf.verbose)
                {
                    if ( appCtx.appEmuCtx.confValue.gain_flag2 == 0)
                    {
                       S2w_Printf("\r\ndisabled\r\n");
                       break;
                    }
                    else if( appCtx.appEmuCtx.confValue.gain_flag2 == 1)
                    {
                        if( GSN_EMU_SDADC_GAIN0 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                        {
                          S2w_Printf("\r\nenabled:06db\r\n");  
                        }
                        else if( GSN_EMU_SDADC_GAIN1 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                        {
                          S2w_Printf("\r\nenabled:12db\r\n");  
                        }
                        else if( GSN_EMU_SDADC_GAIN2 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                        {
                          S2w_Printf("\r\nenabled:18db\r\n");  
                        }
                        else if( GSN_EMU_SDADC_GAIN3 == appCtx.appEmuCtx.confValue.sdadc_gain2)
                        {
                          S2w_Printf("\r\nenabled:24db\r\n");  
                        }
                       
                        break;
                     }
                }
				
				case APP_EMU_CONF_SDADC_ATTENCONST:
				{
                    //S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.emu.attenuationConstFp);  
					break;
				}

				
            case APP_EMU_CONF_PL722X_SPI_CHANNEL:     
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.pl722x_spi_channel);          
                 
                 break;
            case APP_EMU_CONF_PL722X_SET_FREQ_MS:     
                 S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.pl722x_readFreq_ms);          
                 
                 break;
            case APP_EMU_CONF_PL722X_CS_GPIO:
		S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.pl722x_gpio_cs);          
			
	        break;
           case APP_EMU_CONF_PL722X_RST_GPIO:
                S2w_Printf("\r\n%d\r\n",appCtx.appEmuCtx.confValue.pl722x_gpio_rst);  
			
     	        break;
            default:
                 return S2W_EINVAL;
                 break;
                 
    	}
        return S2W_SUCCESS;
	
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMURESETENERGY command
 *   This function resets the energy .
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
  * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuResetEnergy(UINT8 *ptr)
{
    
    GSN_EMU_STATUS_T status;
    
    if (ptr[0] == '\0')
    {
        status = GsnEmu_ResetEnergy(&(appCtx.appEmuCtx.emu));
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            return S2W_SUCCESS;
        }
        else
        {
            return S2W_FAILURE;
        }
    }
    else 
    {
	return S2W_EINVAL;
    }
}

/**
* This is just debugging
*/
PRIVATE UINT8
AppS2wCmd_EmuPrint(UINT8 *ptr)
{
    UINT32 i=0;

    if (1 == appCtx.appEmuCtx.emu.moduleCtx.sdAdcCtx.pingPongState)
    {
        S2w_Printf("\r\nV: \r\n");
        for(i=0;i<(1000);i++)
        {
          S2w_Printf("%d:",appCtx.appEmuCtx.appEmuSdadcPbuf3[i] );
        }
        
        S2w_Printf("\r\nI: \r\n");
        for(i=0;i<(1000);i++)
        {
          S2w_Printf("%d:",appCtx.appEmuCtx.appEmuSdadcPbuf4[i] );        
        }
    }  
    else if (2 == appCtx.appEmuCtx.emu.moduleCtx.sdAdcCtx.pingPongState)
    {
        S2w_Printf("\r\nV: \r\n");
        for(i=0;i<(1000);i++)
        {
          S2w_Printf("%d:",appCtx.appEmuCtx.appEmuSdadcPbuf1[i] );        
        }
       
        S2w_Printf("\r\nI: \r\n");
        for(i=0;i<(1000);i++)
        {
          S2w_Printf("%d:",appCtx.appEmuCtx.appEmuSdadcPbuf2[i] );        
        } 
    }
	
    //S2w_Printf("\r\nLastInput:%f\r\n",appCtx.appEmuCtx.emu.lastinputFp);
    //S2w_Printf("\r\nLastOutput:%f\r\n",appCtx.appEmuCtx.emu.lastoutputFp);
	   
    return S2W_SUCCESS;
}

#if 0 /*Commands to be implemented*/
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUPAUSE command
 *   This function pauses the EMU is in running state.
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @return EMU STATUS   
  * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuPause(UINT8 *ptr)
{
	
    GSN_EMU_ELECTRIC_PARAMS_T param;
    GSN_EMU_STATUS_T status;
	   
    S2w_Printf("\r\n");
    
    if (ptr[0] == '\0')
    {
        status = GsnEmu_Pause(&(appCtx.appEmuCtx.emu), &param);
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            return S2W_SUCCESS;
        }
        else
          return S2W_FAILURE;
    }
    else 
    {
	return S2W_EINVAL;
    }	
}		

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMURESUME command
 *   This function resumes the EMU operation which is Pause state.
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @return EMU STATUS   
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_EmuResume(UINT8 *ptr)
{
	
    GSN_EMU_ELECTRIC_PARAMS_T param;   
    GSN_EMU_STATUS_T status;
    
    if (ptr[0] == '\0')
    {
        status = GsnEmu_Resume(&(appCtx.appEmuCtx.emu),&param,
                               &(appCtx.appEmuCtx.confValue));
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            return S2W_SUCCESS;
        }
        else
          return S2W_FAILURE;
    }
    else 
    {
	return S2W_EINVAL;
    }
}

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+EMUGETSTATUS command
 *   This function returns the current state EMU.
 *   
 * @param ptr Pointer to the user input string.
 * @return ENU STATUS
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/

PRIVATE UINT8
AppS2wCmd_EmuGetStatus(UINT8 *ptr)
{
     
    GSN_EMU_STATE_T state;
    GSN_EMU_STATUS_T status;
       
    if (ptr[0] == '\0')
    {
        status = GsnEmu_GetState(&(appCtx.appEmuCtx.emu), &state);
        if(GSN_EMU_STATUS_SUCCESS == status)
        {
            if( state == GSN_EMU_STATE_RUNNING )
            {
                S2w_Printf("\r\nRunning\r\n");         
            }
            else if( state == GSN_EMU_STATE_PAUSED)
            {
                S2w_Printf("\r\nPaused\r\n");
            }
            else if( state == GSN_EMU_STATE_STOPPED )
            {
                S2w_Printf("\r\nStopped\r\n");
            }
           status =( GSN_EMU_STATUS_T )S2W_SUCCESS;
        }
    }
    else 
    {
        status = (GSN_EMU_STATUS_T) S2W_EINVAL;
    }
    return status ;
     
}
#endif /*S2W_EMU*/

#ifdef S2W_ADC_SUPPORT

#ifndef GS2100
__no_init UINT32 app_adc_data[256];
#define S2W_ADC_SINGLE 1
#define S2W_ADC_CONTI  0
#define S2W_ADC_PERIODIC 2

/*Commands for adc*/

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+AADCCONF Command.
 *   This function sets the required configurations for aadc.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - oeration failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_AdcConf(UINT8 *ptr)
{
    UINT8 *p, status;
    UINT32 conf = 0;
    UINT32 value = 0;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &conf);
    if (status != S2W_SUCCESS || (conf >5))
    {
        return S2W_EINVAL;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&value);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    switch(conf)
    {
        case 1 :
          /* select mode for reading */
          if(S2W_ADC_CONTI == value)
          {
            appCtx.appadcconfig.readMode = GSN_ADC_MODE_CONTINUOUS ;
          }
          if (S2W_ADC_SINGLE == value)
          {
             appCtx.appadcconfig.readMode = GSN_ADC_MODE_SINGLE ;
          }
          else
          {
              return S2W_EINVAL;
          }
          break;

        case 2 :

             /*set the slave address*/
             appCtx.appadcconfig.samplingfreq = value ;
          if(value > 2000000)
          {
             return S2W_EINVAL;
          }

             if(value >= 100000)
             {
                 appCtx.appadcconfig.en100kHz = GSN_ADC_EN100K_ENABLE ;

             }
             else
             {
                 appCtx.appadcconfig.en100kHz = GSN_ADC_EN100K_DISABLE ;

             }
             break;

        case 3:
          if( 0 == value )
          {
              appCtx.appadcconfig.threshselect = GSN_ADC_NO_THRESH_SEL;
              appCtx.appadcconfig.thresh0.lower = 0 ;
              appCtx.appadcconfig.thresh0.upper = 0 ;
          }
          else if( 1 == value )
          {
              appCtx.appadcconfig.threshselect = GSN_ADC_SET0_THRESH_SEL;
          }
          else if( 2 == value )
          {
              appCtx.appadcconfig.threshselect = GSN_ADC_SET1_THRESH_SEL;
          }
          else if( 3 == value )
          {
              appCtx.appadcconfig.threshselect = GSN_ADC_SET2_THRESH_SEL;
          }
          else
          {
              return S2W_EINVAL;
          }
          break;

        case 4:
          /*set all the default configurations*/
          if( 0 == value )
          {
              appCtx.appadcconfig.refVoltage = GSN_ADC_REF_EXTERNAL ;
              appCtx.appadcconfig.pdPolarity = GSN_ADC_PDPOLARITY_H;
              appCtx.appadcconfig.sup1p8     = GSN_ADC_AVDD_3Vrange;
              appCtx.appadcconfig.enlvl =  GSN_ADC_LVL_ENABLE ;
              appCtx.appadcconfig.enDvdd = GSN_ADC_DVDD_ENABLE ;
              appCtx.appadcconfig.enTrim = GSN_ADC_TRIM_DISABLE ;
              appCtx.appadcconfig.startPolarity = GSN_ADC_STARTPOLARITY_L ;
              appCtx.appadcconfig.adcClk = GSN_ADC_CLK_SEL_XTAL ;
              appCtx.appadcconfig.startCycles = 1 ;
              appCtx.appadcconfig.powerCycles = 200 ;
              appCtx.appadcconfig.fifoThr = 0x8;

          }
          else
          {
             return S2W_EINVAL;
          }
          break;
        case 5:
          /*Set the flag only when using at+aadcpollread command*/
          if(1 == value )
          {
             appCtx.appadcconfig.singlePolling = TRUE;
          }
          else if (0 == value)
          {
             appCtx.appadcconfig.singlePolling = FALSE;
          }
          else
          {
             return S2W_EINVAL;
          }
          break;
        default:
          return S2W_FAILURE;
    }
    return S2W_SUCCESS;


}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+AADCSTART Command.
 *   This function starts aadc as configured .
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - oeration failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_AdcStart(UINT8 *ptr)

{
    GSN_STATUS status;
    status = GsnADC_Open(&appCtx.appadchandle,&appCtx.appadcconfig);
    if(status == GSN_SUCCESS)
    {
        appCtx.adcStartStatus = TRUE;
    }
    return status;

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+AADCREAD Command.
 *   This function reads the values from aadc as configured .
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - oeration failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_AdcRead(UINT8 *ptr)
{
    UINT8  *p, status;
    UINT32 size=0;
    UINT32 channel=0;
    UINT32 k =0 ;

    p = AppS2wParse_NextParamGet(&ptr);	    /* size */
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Int(p, &size);
    if (status != S2W_SUCCESS || (size >256))
    {
        return S2W_EINVAL;
    }


    p = AppS2wParse_NextParamGet(&ptr);    /* channel no */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&channel);
    if (status != S2W_SUCCESS || (channel > 7))
    {
        return S2W_EINVAL;
    }

    if(!appCtx.adcStartStatus)
    {
        return S2W_FAILURE;
    }
    channel |= 0xf0;
    
    appCtx.appadcrw.buffer.pData = app_adc_data;

    appCtx.appadcrw.buffer.size  = size ;

    appCtx.appadcrw.funcCB = NULL ;

    appCtx.appadcrw.contextCB = NULL ;

    status = GsnADC_PollRead(&appCtx.appadchandle,
                       appCtx.appadcconfig.readMode,
                       channel,
                       &appCtx.appadcrw,
                       GSN_ADC_REF_EXTERNAL);
    if(status != GSN_SUCCESS)
    {
        return S2W_FAILURE;
    }

    S2w_Printf("\r\n");
    for(k = 0 ; k < size ; k++)
    {
       S2w_Printf("0x");
       S2w_Printf("%x\r\n",app_adc_data[k] );
    }

    return S2W_SUCCESS ;

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+AADCSTOP Command.
 *   This function Stops aadc operation.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - oeration failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_AdcStop(UINT8 *ptr)
{
    GSN_STATUS status;

    status = GsnADC_Close(&appCtx.appadchandle);
    if(status == GSN_SUCCESS)
    {
        appCtx.adcStartStatus = FALSE;
    }
    return status;
}

#endif
#endif

#ifdef S2W_I2C_SUPPORT
/*Commands for i2c*/

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+I2CCONF command
 *   This function sets the configurations for I2C
 *   
 * @param ptr Pointer to the user input string.
 * 
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/
/*clock context for i2c*/
GSN_CLK_CTL_CTX_T GsnS2wClkCtx;
/*set the configurations for I2C*/
PRIVATE UINT8
AppS2wCmd_I2cConf(UINT8 *ptr)
{
    UINT8 *p, status;
    UINT32 conf;
    UINT32 value;
    UINT32 param;
 
    p = AppS2wParse_NextParamGet(&ptr);	
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &param);
    if (status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }
    conf = param;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Hex(p,&value); 
    if (status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }
    
    switch(conf)
    {
        case 1 : 
          /* select master or slave*/
          if(0 == value)
          {
            //GsnClkCtl_Init(&GsnS2wClkCtx); fix for issue no:5917
            appCtx.app_i2cConf.gsnI2cMode = GSN_I2C_MNS_SLAVE;
          }
          else if(1 == value )
          {
              appCtx.app_i2cConf.gsnI2cMode = GSN_I2C_MNS_MASTER;
          }
            break;
        case 2 :
             /*set the slave address. when we are master than this is the address of slave device 
              but when we are slave this is the address of our device slave address.*/
            AppS2wParse_Hex(p,&value);
            appCtx.app_i2cConf.gsnI2cSlaveAddr = value ;
            break;
        case 3:
          /*select the address mode*/
          if(0 == value)
          {
             appCtx.app_i2cConf.gsnI2cAddrMode = GSN_I2C_ADMOD_7BITS ;
          }
          else if(1 == value )
          {
              appCtx.app_i2cConf.gsnI2cAddrMode = GSN_I2C_ADMOD_10BITS;
          }
          break;
       case 4:
         /*select the rate 100K/400K/3.4M*/
         if(0 == value)
         {
             appCtx.app_i2cConf.gsnI2cRate = GSN_I2C_ERATE_100KBITS;
         }
         else if(1 == value)
         {
             appCtx.app_i2cConf.gsnI2cRate = GSN_I2C_ERATE_400KBITS;
         }
         else if(2 == value )
         {
             appCtx.app_i2cConf.gsnI2cRate = GSN_I2C_ERATE_HSE;
         }
         else
         {
            AppS2wParse_Int(p,&value); 
            appCtx.app_i2cConf.gsnI2cRate = value;
         }
          break;
      case 5:
        /*select the address mode*/
        if(0 == value)
        {
            appCtx.app_i2cConf.gsnI2cRandomCurrentAddr = GSN_I2C_RCAS_CURRENTADD;
        }
        else if(1 == value )
        {
            appCtx.app_i2cConf.gsnI2cRandomCurrentAddr = GSN_I2C_RCAS_RANDOMADD;
        }
        break;
            
        case 6 :
        /*set address in slave device whrere we want to read in case of random read*/
        appCtx.app_i2cConf.gsnI2cSlaveLocAddr = value ;
        break;
            
        case 7 :
        /*set the slave address*/
        appCtx.app_i2cConf.gsnI2cAddrLocInSlave = value;
        break;        
        
        case 8 :
        /* Memory Address Selection (Single byte or Double byte)*/
        if(0 == value)
        {
        appCtx.app_i2cConf.gsnI2cMemAddSel=GSN_I2C_MEMADD_SINGLE;
        }  
        else if(1 == value)
        {
        appCtx.app_i2cConf.gsnI2cMemAddSel=GSN_I2C_MEMADD_DOUBLE;
        }
        break;
        
        case 9 :
        /* Set the clock for slave to maintain data hold time */ 
        if(0==value) 
        {
        appCtx.app_i2cConf.gsnI2cSlaveDataHoldClkCnt=GSN_I2C_DATA_HOLD_CLOCK_COUNT;
        }
        break;
        
        case 10:
        /* Set Source Clock*/ 
        if(0==value)  
        {
        appCtx.app_i2cConf.clockSelect=GSN_I2C_CLK_HSRC;
        }
        
        else if(1==value)
        {
        appCtx.app_i2cConf.clockSelect=GSN_I2C_CLK_XTAL;      
        }
        
        else if(2==value)
        {
        /* Enable PLL */
        GsnClkCtl_SysPllEn(GSN_CLK_CTL_PLL_FREQ_120MHZ);  
        appCtx.app_i2cConf.clockSelect=GSN_I2C_CLK_PLL;       
        }

        else
        {
        appCtx.app_i2cConf.clockSelect=GSN_I2C_CLK_HSRC;      
        }
        break;
        
       default:
             return S2W_FAILURE;
    }
    return S2W_SUCCESS;

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+I2CSTART command
 *   This function initialises the I2C 
 *   
 * @param ptr Pointer to the user input string.
 * 
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_I2cStart(UINT8 *ptr)
{
  
    GSN_STATUS status;
    
    /* select the mux for I2C */
    
    GsnIoMux_Sel(8,GSN_IOMUX_GPIO_8_AI2C_SDA);
    GsnIoMux_PullDownEnable (8);   
    GsnIoMux_Sel(9,GSN_IOMUX_GPIO_9_AI2C_SCL);
    GsnIoMux_PullDownEnable (9);


    status = GsnI2c_Open(&appCtx.app_i2cHandle,&appCtx.app_i2cConf, NULL);
    if(status != GSN_SUCCESS)
    {
		return S2W_FAILURE;
	}
	appCtx.i2cStatus = S2W_I2C_STARTED;
    return status;

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+I2CWRITE command
 *   This function initiates I2C data write
 *   
 * @param ptr Pointer to the user input string.
 * @input - number of bytes to write
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_I2cWrite(UINT8 *ptr)
{
    UINT8 *p,status;
    UINT32 write_count;
    UINT8 write_msg[128];
    
    if(appCtx.i2cStatus != S2W_I2C_STARTED)
    {
		return S2W_EINVAL;
	}
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &write_count);
    if (status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    //strcpy ((char*)write_msg, (char*)p);
	// data comming as hex so convert it
	{
        UINT32 val = 0, i,j;
	    while (isspace(*p))
	    {
	        p++;
	    }
    
	    for (j = 0; *p != '\0'; j++)
	    {
	        for (val = 0, i = 0; i < 2 && *p != '\0'; p++, i++)
	        {
	            if (!isxdigit(*p))
	            {
	                break;
	            }
		        val = val * 16 + AppS2wParse_ToHex(*p);
		     }
	         if (i != 2)
	         {
	             break;
	         }
   
	         write_msg[j] = val;
	    }
	    if(j != write_count)
    {
		    return S2W_EINVAL;
	    }
    }
       
    
    status = GsnI2c_Write(&appCtx.app_i2cHandle,write_msg,write_count,NULL,NULL);
    if(status == 0)
    {
        return S2W_FAILURE;
    }
   return S2W_SUCCESS;
  
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+I2CREAD command
 *   This function initiates I2C data read 
 *   
 * @param ptr Pointer to the user input string.
 * @input - number of bytes to read
 * @return prints the data recieved by I2C
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_I2cRead(UINT8 *ptr)
{
    UINT8 *p;
    UINT32 read_count;
    UINT8 p_read = 0;
     UINT8 read_msg[128];
    if(appCtx.i2cStatus != S2W_I2C_STARTED)
    {
		return S2W_EINVAL;
	}
    p = AppS2wParse_NextParamGet(&ptr);	
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &read_count);
    if (!p)
    {
        return S2W_EINVAL;
    }
    memset(read_msg,0,128);
    GsnI2c_Read( &(appCtx.app_i2cHandle),read_msg,read_count,TRUE,NULL,NULL);
    
    for(p_read =0;p_read < read_count; p_read++ )
    {
        S2w_Printf("\r\n%02x",read_msg[p_read]);
    }

    return S2W_SUCCESS;
}

 /******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+I2CWRITE command
 *   This function stops I2C operation
 *   
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_EINVAL   - invalid input
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_I2cStop(UINT8 *ptr)
{
    GSN_STATUS status;
    if(appCtx.i2cStatus != S2W_I2C_STARTED)
    {
		return S2W_EINVAL;
	}
    status = GsnI2c_Close(&(appCtx.app_i2cHandle));
    appCtx.i2cStatus = S2W_I2C_STOPPED;
    return status;
}

#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WEAPFAST Command.
 *   This function check the validity of parameter passed and
 *   update the active profile username and password for EAP methods.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
PRIVATE UINT8
AppS2wCmd_WeapConf(UINT8 *ptr)
{
    UINT32 prevAuthType=0;
    UINT32 len;
    UINT8 *p;

    //memcpy(&params, &s2wCurrent.security, sizeof(params));

    /* Validate the input string.
     */
    p = AppS2wParse_NextParamGet(&ptr);     //get outer auth
    if (!p)
    {
        return S2W_EINVAL;
    }
    prevAuthType = s2wCurrent.security.eap.outerAuth;
    s2wCurrent.security.eap.outerAuth = 0;
    AppS2wParse_Int(p, &s2wCurrent.security.eap.outerAuth);

       if(!( FALSE
#if defined(S2W_SECURITY_ENTERPRISE_FAST_MSCHAPV2_AVAILABLE) || defined(S2W_SECURITY_ENTERPRISE_FAST_GTC_AVAILABLE)
          || s2wCurrent.security.eap.outerAuth == GSN_EAP_TYPE_FAST
#endif
#ifdef S2W_SECURITY_ENTERPRISE_TTLS_AVAILABLE
          || s2wCurrent.security.eap.outerAuth == GSN_EAP_TYPE_TTLS
   #endif
#if defined(S2W_SECURITY_ENTERPRISE_PEAP_V0_AVAILABLE)|| defined(S2W_SECURITY_ENTERPRISE_PEAP_V1_AVAILABLE)
          || s2wCurrent.security.eap.outerAuth == GSN_EAP_TYPE_PEAP
   #endif
#if defined(S2W_SECURITY_ENTERPRISE_TLS_AVAILABLE)
           || s2wCurrent.security.eap.outerAuth == GSN_EAP_TYPE_TLS 
#endif
          || s2wCurrent.security.eap.outerAuth == GSN_EAP_TYPE_NONE  ))
    {
      s2wCurrent.security.eap.outerAuth = prevAuthType;
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);     //get outer auth
    if (!p)
    {
        return S2W_EINVAL;
    }
    prevAuthType = s2wCurrent.security.eap.innerAuth;
    s2wCurrent.security.eap.innerAuth= 0;
    AppS2wParse_Int(p, &s2wCurrent.security.eap.innerAuth);
    if(s2wCurrent.security.eap.innerAuth == 253)
    {
        s2wCurrent.security.eap.innerAuth = GSN_EAP_TYPE_NONE;
    }

        if(!(FALSE
   #if defined(S2W_SECURITY_ENTERPRISE_TLS_AVAILABLE) || defined(S2W_SECURITY_ENTERPRISE_FAST_MSCHAPV2_AVAILABLE) || defined(S2W_SECURITY_ENTERPRISE_PEAP_V0_AVAILABLE)|| defined(S2W_SECURITY_ENTERPRISE_TTLS_AVAILABLE)
//#ifdef  GSN_SECURITY_ENTERPRISE_TTLS_AVAILABLE
           || s2wCurrent.security.eap.innerAuth == GSN_EAP_TYPE_MSCHAPV2
#endif
   #if defined(S2W_SECURITY_ENTERPRISE_FAST_GTC_AVAILABLE)|| defined(S2W_SECURITY_ENTERPRISE_PEAP_V1_AVAILABLE)
            || s2wCurrent.security.eap.innerAuth == GSN_EAP_TYPE_GTC 
#endif
            || s2wCurrent.security.eap.innerAuth == GSN_EAP_TYPE_NONE
        ))
    {
      s2wCurrent.security.eap.innerAuth = prevAuthType;
        return S2W_EINVAL;
    }
//        s2wCurrent.security.eap.innerAuth = GSN_EAP_TYPE_MSCHAPV2;
    p = AppS2wParse_NextParamGet(&ptr);     //get usr name
    if (!p)
    {
        return S2W_EINVAL;
    }

    len = strlen((char *)p);
    if(len > S2W_MAX_EAP_USR_NAME_LEN)
    {
        return S2W_EINVAL;
    }
    memset(s2wCurrent.security.eap.usrName, 0, S2W_MAX_EAP_USR_NAME_LEN);
    memcpy(s2wCurrent.security.eap.usrName, p, len);
    s2wCurrent.security.eap.usrNameLen = len;

    p = AppS2wParse_NextParamGet(&ptr);     //get password
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((char *)p);
    if(len > S2W_MAX_EAP_PASSWORD_LEN)
    {
        return S2W_EINVAL;
    }
    memset(s2wCurrent.security.eap.password, 0, S2W_MAX_EAP_PASSWORD_LEN);
    memcpy(s2wCurrent.security.eap.password, p, len);
    s2wCurrent.security.eap.passwordLen = len;
    s2wCurrent.security.validKeys |= S2W_SECURITY_VALID_EAP;

    s2wCurrent.security.eap.useCaCert = FALSE;
    p = AppS2wParse_NextParamGet(&ptr);//get use CA CERT. If it has to be used
    if (p)
    {
        if( S2W_SUCCESS != AppS2wParse_Boolean(p,
            &s2wCurrent.security.eap.useCaCert))
        {
            return S2W_EINVAL;
        }
    }
    return S2W_SUCCESS;
}


#ifdef S2W_EXTFLASH_DRIVER_TEST
UINT8 readBuffer[1024];
UINT32 extFlashFileSize;
UINT8 extFlashGetDatabuf[1024];
UINT32 writeAddr;
UINT32 spiFlag;

PUBLIC UINT32
AppS2wExternalFlashData(UINT8 ch1)
{

    UINT32 rwSize=0;

    if( extFlashFileSize == 0)
            return S2W_FAILURE;

      while(extFlashFileSize)
      {
          memset(extFlashGetDatabuf, 0, sizeof(extFlashGetDatabuf));
          if(extFlashFileSize<1024)
          {
            rwSize = extFlashFileSize;
          }
          if(extFlashFileSize>=1024)
          {
            rwSize = 1024;
          }
          /* store incoming byte in temparory bufer */
          AppS2wHal_CharNGet(extFlashGetDatabuf, rwSize);
		  
		  if(spiFlag)
		  {
                       GsnExtFlash_Write (&s2wappMainTaskCtxt->extFlashCtx,rwSize,writeAddr,extFlashGetDatabuf,GSN_FLASH_SPI_DMA, NULL, NULL);
		  }
		  else
		  {
			GsnExtFlash_Write (&s2wappMainTaskCtxt->extFlashCtx,rwSize,writeAddr,extFlashGetDatabuf,GSN_FLASH_SPI_POLL, NULL, NULL);
		  }
          extFlashFileSize -= rwSize;
          writeAddr += rwSize;
		
      }
	  
      S2w_Printf("\r\nLoading file successfull\r\n");

    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_ExtFlashInit(UINT8* ptr)
{

    UINT8 status = S2W_SUCCESS;
    UINT8 *p;

	if(s2wappMainTaskCtxt->extFlashCtx.extFlashStatus == EXTFLASH_NOT_INITIALIZED)
	{
		if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
	  	{
			status = AppS2wParse_Int(p, &spiFlag);
	      	if (status != S2W_SUCCESS)
	      	{
	          	return status;
	      	}
	   	}
		
		AppExtFlash_Init((GSN_FLASH_SPI_FLAG_T)spiFlag);
	}
	return status;
}

UINT8
AppS2wCmd_ExtFlashSpiConf(UINT8* ptr)
{
	UINT8 status = S2W_SUCCESS;	
	UINT8 *p;
	UINT32 spiPin, gpioNumb, muxVal, pulldown;

	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Int(p, &spiPin);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}

	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Int(p, &gpioNumb);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}
		
	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Int(p, &muxVal);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}

	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Int(p, &pulldown);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}
	
	/*	  GPIO Mux enable for SPI Port-1	   */
	GsnIoMux_Sel(gpioNumb, muxVal);

	if(pulldown)
		GsnIoMux_PullDownEnable (gpioNumb);
	else		
		GsnIoMux_PullDownDisable (gpioNumb);

	if(!muxVal)
	{
		/* Use SPI CS pin10 as GPIO to control from driver */
		GsnGpio_Init((~APP_ALL_GPIO_SET) | (1<<gpioNumb), APP_ALL_GPIO_SET & (~(1<<gpioNumb))); 
		s2wappMainTaskCtxt->extFlashCtx.spiCsGpio = ((~APP_ALL_GPIO_SET) | (1<<gpioNumb));
	}
	
	s2wappMainTaskCtxt->extFlashCtx.spiPinConf |= spiPin;
	return status;
}

UINT8
AppS2wCmd_ExtFlashWrite(UINT8* ptr)
{
	//UINT32 retVal=0;
	UINT8 *p;
	UINT8 status = S2W_SUCCESS;

	writeAddr = 0x00000000;

	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Hex(p, &writeAddr);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}
	
	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Int(p, &extFlashFileSize);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}

	return status;
}


UINT8
AppS2wCmd_ExtFlashRead(UINT8* ptr)
{
	UINT8 status = S2W_SUCCESS;	
	UINT8 *p;
	UINT32 readAddr;
	UINT32 i=0, dataLen;
	//GSN_SPI_CONFIG_T *spiConfig;
	//GSN_SPI_HANDLE_T *spiHandle;
	//spiConfig = &s2wappMainTaskCtxt->extFlashCtx.spiConfig;
	//spiHandle = &s2wappMainTaskCtxt->extFlashCtx.spiHandle;

	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Hex(p, &readAddr);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}
   	else
   	{
   	    return S2W_EINVAL;
   	}
		
	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Int(p, &dataLen);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}
   	else
   	{
   	    return S2W_EINVAL;
   	}

        S2w_Printf("\r\n");


	UINT32 rwSize = 0;
	while(dataLen)
      {
        memset(readBuffer, 0, sizeof(readBuffer));
        if(dataLen<1024)
        {
          rwSize = dataLen;
        }
        if(dataLen>=1024)
        {
          rwSize = 1024;
        }
		if(spiFlag)
		{
			GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx,rwSize,readAddr,readBuffer,GSN_FLASH_SPI_DMA, NULL, NULL); //GSN_FLASH_SPI_DMA , GSN_FLASH_SPI_POLL
		}
		else
		{			
			GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx,rwSize,readAddr,readBuffer,GSN_FLASH_SPI_POLL, NULL, NULL); //GSN_FLASH_SPI_DMA , GSN_FLASH_SPI_POLL
		}
        dataLen -= rwSize;
        readAddr += rwSize;
      
		for(i=0;i<rwSize;i++)
		{
			S2w_Printf("%c",readBuffer[i]);
		}         
      }

	return status;

}

UINT8
AppS2wCmd_ExtFlashErase(UINT8* ptr)
{
	UINT8 status = S2W_SUCCESS;
        UINT8 *p;
	UINT32 eraseSectorAddr;
	//GSN_SPI_HANDLE_T *spiHandle;
	//spiHandle = &s2wappMainTaskCtxt->extFlashCtx.spiHandle;

	if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  	{
    	status = AppS2wParse_Hex(p, &eraseSectorAddr);
      	if (status != S2W_SUCCESS)
      	{
          	return status;
      	}
   	}
   	else
   	{
   	    return S2W_EINVAL;
   	}
	
	if(spiFlag)
	{
		GsnExtFlash_Erase(&s2wappMainTaskCtxt->extFlashCtx,eraseSectorAddr,GSN_FLASH_SPI_DMA,NULL,NULL);
	}
	else
	{
		GsnExtFlash_Erase(&s2wappMainTaskCtxt->extFlashCtx,eraseSectorAddr,GSN_FLASH_SPI_POLL,NULL,NULL);
	}
	
	return status;
}

UINT8
AppS2wCmd_ExtFlashChipErase(UINT8* ptr)
{
	UINT8 status = S2W_SUCCESS;

	//GSN_SPI_HANDLE_T *spiHandle;
	//spiHandle = &s2wappMainTaskCtxt->extFlashCtx.spiHandle;

	if(spiFlag)
	{
		GsnExtFlash_ChipErase(&s2wappMainTaskCtxt->extFlashCtx,GSN_FLASH_SPI_DMA,NULL,NULL);
	}
	else
	{
		GsnExtFlash_ChipErase(&s2wappMainTaskCtxt->extFlashCtx,GSN_FLASH_SPI_POLL,NULL,NULL);
	}
	return status;
}
#endif


UINT8
S2wRateValidation(UINT32 value)
{
	 if((value == GSN_MAC_RATE_1MBPS) || (value == GSN_MAC_RATE_2MBPS)|| (value == GSN_MAC_RATE_5_5MBPS)||
	    (value == GSN_MAC_RATE_6_5MBPS)||(value == GSN_MAC_RATE_6MBPS) ||(value == GSN_MAC_RATE_9MBPS) ||
	    (value == GSN_MAC_RATE_11MBPS) ||(value == GSN_MAC_RATE_12MBPS) || (value == GSN_MAC_RATE_13MBPS) ||
	    (value == GSN_MAC_RATE_18MBPS) || (value == GSN_MAC_RATE_19_5MBPS) ||(value == GSN_MAC_RATE_24MBPS) ||
        (value == GSN_MAC_RATE_26MBPS) || (value == GSN_MAC_RATE_36MBPS) || (value == GSN_MAC_RATE_39MBPS) ||
        (value == GSN_MAC_RATE_48MBPS)|| (value == GSN_MAC_RATE_52MBPS) || (value == GSN_MAC_RATE_54MBPS) ||
	    (value == GSN_MAC_RATE_58_5MBPS) || (value == GSN_MAC_RATE_65MBPS))
	 {
		  return 0;
	 }
	  return 1;
}

#ifdef S2W_COAP_SUPPORT
PRIVATE UINT8
AppS2wCmd_CoapClose(UINT8* ptr)
{
	UINT8 cid;
        UINT8 *p;
	GSN_COAP_CONN_PARAMS_T * coapConnParams;
	GSN_COAP_CONTEXT_T * coapContext;
	// parse for cid
	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	cid = AppS2w_CidValidate(*p);
    if(cid == INVALID_CID)
        return S2W_EBADCID;

    coapContext = AppS2wHal_CoapHandleGet(cid);
    coapConnParams = AppS2wHal_CoapParamsGet(cid);

	GsnCoap_DeInit(coapContext);
        coapContext = NULL;
	s2wCidList[cid].s2wUsrCloseFlag = 1;
	s2wCidList[cid].sd = CID_NOTINUSE;

	if(coapConnParams)
	{
		gsn_free(coapConnParams);
		coapConnParams = NULL;
	}
    return S2W_SUCCESS;
}

PRIVATE UINT8
AppS2wCmd_CoapOpen(UINT8* ptr)
{
	//S2w_Printf("AppS2wCmd_CoapOpen \r\n");
	// parse the ptr for the parameters
	// if dtls is set to 1, then do dtls connection
	// else create coap context and return cid
	UINT8 *p,  status;
	UINT32 dtlsflag;
	UINT8 cid;
	GSN_COAP_CONN_PARAMS_T * connParams;
	GSN_COAP_CONTEXT_T * coapContext;


	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        status = S2W_EINVAL;
        return status;
    }

    /* dtls flag */
    AppS2wParse_Int(p, &dtlsflag);
    if(dtlsflag == 1)
    {
    	// parse the input string further
    }
    else
    {
    	// open a coap context and return cid
    	coapContext = GsnCoap_Init(NULL);
		cid = AppS2wHal_CidGet();
	    if (cid == INVALID_CID)
	    {
	            return S2W_ENCID;
	    }
		s2wCidList[cid].coapContext =  coapContext;
		s2wCidList[cid].sd = coapContext->sockfd;
	    s2wCidList[cid].conType = UDP;
		s2wCidList[cid].serverCid = INVALID_CID;
	    s2wCidList[cid].localPort = 0;
		//S2w_Printf("sockfd = %d\r\n",coapContext->sockfd);
		//S2w_Printf("s2wCidList[cid] coapContext sockfd = %d\r\n",s2wCidList[cid].coapContext->sockfd);

		connParams = (GSN_COAP_CONN_PARAMS_T*) gsn_malloc(sizeof(GSN_COAP_CONN_PARAMS_T));
		memset(connParams,0,sizeof(GSN_COAP_CONN_PARAMS_T));
		s2wCidList[cid].coapConnParams = connParams;
    	S2w_Printf("\r\n%x",cid);

    }
	return S2W_SUCCESS;
}


PRIVATE UINT8
AppS2wCmd_CoapSend(UINT8* ptr)
{
	UINT8 *p;
	UINT32 payloadSize, responseTimeout,len;
    UINT8 cid;
	GSN_COAP_CONTEXT_T * coapContext = NULL;
	GSN_COAP_CONN_PARAMS_T* coapConnParams;
	S2W_COAP_OPTION_T * start = optionHead;
	char respBuf[COAP_MAX_PDU_SIZE];
	INT16 numBytes;
	unsigned int optionLen;
	memset(respBuf,0,COAP_MAX_PDU_SIZE);

	// parse for cid
	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	cid = AppS2w_CidValidate(*p);
    if(cid == INVALID_CID)
        return S2W_EBADCID;

    coapContext = AppS2wHal_CoapHandleGet(cid);
    coapConnParams = AppS2wHal_CoapParamsGet(cid);

	memset(coapConnParams,0,sizeof(GSN_COAP_CONN_PARAMS_T)); // memset the connection params
	if(coapContext == NULL)
	{
		return S2W_EINVAL;
	}

	// parse for coap uri
	p = AppS2wParse_NextParamGet(&ptr);
    if(p)
    {
	    //S2w_Printf("uri length = %d", strlen(p));
	    //S2w_Printf("uri  = %s", p);
	    len = strlen((const char *)p);

	    coapConnParams->uri = (unsigned char*) gsn_malloc((sizeof(unsigned char)*len)+1);
	    memcpy(coapConnParams->uri,p, len);
	    coapConnParams->uriLength = len;
	    //S2w_Printf("coapConnParams.uri  = %s", coapConnParams->uri);
    }

	// parse for connection method

	p = AppS2wParse_NextParamGet(&ptr);
    if(p)
    {
    	if(strcmp((const char*)p, COAP_GET) == 0)
    	{
    		coapConnParams->method = GSN_COAP_REQUEST_GET;
    	}
    	if(strcmp((const char*)p, COAP_POST) == 0)
    	{
    		coapConnParams->method = GSN_COAP_REQUEST_POST;
    	}
    }

	// parse for connection type
	p = AppS2wParse_NextParamGet(&ptr);
    if(p)
    {
		if(strcmp((const char*)p, COAP_CON) == 0)
		{
			coapConnParams->type = GSN_COAP_MESSAGE_CON;
		}
		if(strcmp((const char*)p, COAP_NON) == 0)
		{
			coapConnParams->type = GSN_COAP_MESSAGE_NON;
		}
    }


	// parse for response timeout
	p = AppS2wParse_NextParamGet(&ptr);
    if(p)
    {
		AppS2wParse_Int(p, &responseTimeout);
		if(responseTimeout > COAP_MAX_RESPONSE_TIMEOUT)
			coapConnParams->responseTimeout = COAP_MAX_RESPONSE_TIMEOUT;
		else
			coapConnParams->responseTimeout = responseTimeout;
    }
    coapConnParams->responseBuffer = respBuf;
    coapConnParams->responseBufLen = COAP_MAX_PDU_SIZE;

    // add all the options
    while(start != NULL)
    {
    	optionLen = strlen((const char*)start->optionValue);
    	GsnCoap_SetOption(start->optionKey,(unsigned char*)start->optionValue,optionLen);
    	start = start->next;
    }
	// parse for payload size
	p = AppS2wParse_NextParamGet(&ptr);
    if(p)
    {
		AppS2wParse_Int(p, &payloadSize);

		coapConnParams->payloadSize = payloadSize;
		// parse for payload type
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			len = strlen((const char*)p);
			coapConnParams->payloadType = (unsigned char*) gsn_malloc(sizeof(unsigned char)*len+1);
			memcpy(coapConnParams->payloadType,p,len);
			coapConnParams->payloadType[len] = '\0';
		}
		else
		{
			return S2W_EINVAL;
		}
    }
    else
    {
    	numBytes = GsnCoap_Send_And_Recieve(coapContext,coapConnParams);

    	if(numBytes > 0)
    	{
    		//S2w_Printf("\r\n%d",numBytes);
    		respBuf[numBytes] = '\0';

#ifndef S2W_DUAL_INTERFACE_SUPPORT
    		S2w_Printf("\r\n");
    		AppS2wHal_CharNPut(respBuf,numBytes);
#else
        AppS2wHal_CharNPut1(respBuf,numBytes);
#endif
    	}
    	if(coapConnParams->uri != NULL)
    	{
    		gsn_free(coapConnParams->uri);
    		coapConnParams->uri = NULL;
    	}
    }
    return S2W_SUCCESS;
}

PRIVATE UINT8
AppS2wCmd_CoapSetOption(UINT8* ptr)
{
	UINT8* p;
	UINT8* q;
	UINT32 key;
	S2W_COAP_OPTION_T* node;
	int len = 0;

	// parse for option key
	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	AppS2wParse_Int(p,&key);
	if(	key == 1 ||
			key == 3 ||
			key == 4 ||
			key == 5 ||
			key == 7 ||
			key == 11 ||
			key == 12 ||
			key == 14 ||
			key == 15 ||
			key == 16 ||
			key == 19 ||
			key == 35 )
	{

		// parse for option value
		q = AppS2wParse_NextParamGet(&ptr);
		if( q)
		{
			if(key == 19)// if it is token add it by calling
			{
				GsnCoap_SetToken(strlen((const char*)q),q);
			}
			else
			{
				node = (S2W_COAP_OPTION_T*)gsn_malloc(sizeof(S2W_COAP_OPTION_T));
				len = strlen((const char*)q);
				node->optionValue = (char*)gsn_malloc(len+1);
				node->optionKey = key;
				strcpy(node->optionValue,(char const*)q);
				if(optionHead == NULL)
				{
					optionHead = node;
					node->next = NULL;
				}
				else
				{
					node->next = optionHead;
					optionHead = node;
				}
			}
			return S2W_SUCCESS;
		}
	}
	return S2W_EINVAL;
}

PRIVATE UINT8
AppS2wCmd_CoapRemoveOption(UINT8* ptr)
{
	UINT8* p;
	UINT32 optionKey;
	S2W_COAP_OPTION_T * prev = optionHead;
	S2W_COAP_OPTION_T * curr = optionHead;
	S2W_COAP_OPTION_T * temp = NULL;

	// parse for option key
	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	AppS2wParse_Int(p,&optionKey);
	if(	optionKey == 1 ||
			optionKey == 3 ||
			optionKey == 4 ||
			optionKey == 5 ||
			optionKey == 7 ||
			optionKey == 11 ||
			optionKey == 12 ||
			optionKey == 14 ||
			optionKey == 15 ||
			optionKey == 16 ||
			optionKey == 19 ||
			optionKey == 35 )
	{
	    // delete the option
		if(optionKey == 19)
		{
			GsnCoap_DeleteToken();
		}
		else
		{
			if(optionHead != NULL)
			{
				if(prev->next == NULL) // only one node
				{
					if(prev->optionKey == optionKey)
					{
						gsn_free(prev->optionValue);
						gsn_free(prev);
						prev= NULL;
						optionHead = NULL;
						return S2W_SUCCESS;
					}
				}
				// delete all occurences of the key
				while(curr != NULL)
				{
					if(curr->optionKey == optionKey)
					{
						temp = curr;
						if(prev == curr)
						{
							// first node in the list
							prev = prev->next;
							curr = curr->next;
							optionHead = curr;
						}
						else
						{
							prev->next = curr->next;
							curr = curr->next;
						}
						gsn_free(temp->optionValue);
						gsn_free(temp);
						temp = NULL;
					}
					else
					{
						prev = curr;
						curr = curr->next;
					}
				}
			}
		}
	}

	return S2W_SUCCESS;

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the coap data from the serial interface.
 *   This function reads the coap data and sends to wifi.
 * @param dataLen the input data length.
 * @param hCid the cid of the coap connection.
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 ******************************************************************/

PUBLIC UINT8
AppS2wHal_CoapContentDataGet( UINT8 hCid)
{
    GSN_STATUS status = S2W_SUCCESS;
    GSN_COAP_CONTEXT_T* coapCtx;
    INT16 numBytes;
    UINT32 dataLen;
    char respBuf[COAP_MAX_PDU_SIZE];
    char requestBuf[COAP_MAX_PDU_SIZE];
    GSN_COAP_CONN_PARAMS_T *coapConnParams;
    coapCtx = (GSN_COAP_CONTEXT_T *)AppS2wHal_CoapHandleGet(hCid);

    if(coapCtx == NULL)
    {
    	  return S2W_FAILURE;
    }
    coapConnParams = (GSN_COAP_CONN_PARAMS_T*)AppS2wHal_CoapParamsGet(hCid);
    dataLen = coapConnParams->payloadSize;

	AppS2wHal_CharNGet((UINT8 *)requestBuf,dataLen);

	coapConnParams->payload = requestBuf;
	//S2w_Printf("coapConnParams->payload = %s\r\n",requestBuf);
	coapConnParams->responseBufLen = COAP_MAX_PDU_SIZE;
	coapConnParams->responseBuffer = respBuf;
	numBytes = GsnCoap_Send_And_Recieve(coapCtx,coapConnParams);
	// set the payload
	// call send

	if(numBytes > 0)
	{
		respBuf[numBytes] = '\0';

#ifndef S2W_DUAL_INTERFACE_SUPPORT
		S2w_Printf("\r\n");
		AppS2wHal_CharNPut(respBuf,numBytes);
#else
		AppS2wHal_CharNPut1(respBuf,numBytes);
#endif
	}
	if(coapConnParams->uri != NULL)
	{
		gsn_free(coapConnParams->uri);
		coapConnParams->uri = NULL;
	}

	if(coapConnParams->payloadType != NULL)
	{
		gsn_free(coapConnParams->payloadType);
		coapConnParams->payloadType = NULL;
	}
	if(coapConnParams->payload != NULL)
	{
		gsn_free(coapConnParams->payload);
		coapConnParams->payload = NULL;
	}
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
   return status;
}
#endif

UINT8
AppS2wCmd_BaBitMapSet(UINT8* ptr)
{
	UINT32 param;
	GSN_WDD_ALLOW_BA_BITMAP_SET_PARAM baBitmapSetParam = {0};
    UINT8 *p, status = S2W_EINVAL;
    p = AppS2wParse_NextParamGet(&ptr);  /*BA TX TID */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &param);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }
	baBitmapSetParam.ba_tx_tid = param;

    p = AppS2wParse_NextParamGet(&ptr);  /*BA RX TID */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &param);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }
	baBitmapSetParam.ba_rx_tid = param;
    
	GsnWdd_BlockAckEnable(&s2wappMainTaskCtxt->if0.wddCtx, &baBitmapSetParam);
    
    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_RadioStateGet(UINT8* ptr)
{
	UINT32 radioState = 0;
	UINT8 *radStStr[]= {"", "Active", "PS Poll", "OFF"};
	GSN_WDD_RADIO_MODE_INFO_T radioStateInfo;
	GsnWdd_RadioStateGet(&s2wappMainTaskCtxt->if0.wddCtx, &radioState);

	S2w_Printf("\r\nWLAN Radio State = %d : %s\r\n", radioState, radStStr[radioState]);

	GsnWdd_RadioModeInfoGet(&s2wappMainTaskCtxt->if0.wddCtx, &radioStateInfo);
	
	S2w_Printf("\r\nAPP Radio State Counters:\r\n");
	S2w_Printf("rxActiveReqCnt = %d\r\n", radioStateInfo.rxActiveReqCnt);
	S2w_Printf("rxPSPollReqCnt = %d\r\n", radioStateInfo.rxPSPollReqCnt);
	S2w_Printf("rxPSPollCfgSetFlag = %d\r\n", radioStateInfo.rxPSPollCfgSetFlag);
	S2w_Printf("rxIeeePSPollCfgSetFlag = %d\r\n", radioStateInfo.rxIeeePSPollCfgSetFlag);
	S2w_Printf("rxIeeePSPollReqCnt = %d\r\n", radioStateInfo.rxIeeePSPollReqCnt);
	S2w_Printf("lastPsStateReqsted = %d : %s\r\n", radioStateInfo.lastPsStateReqsted,
													radStStr[radioStateInfo.lastPsStateReqsted]);
	
    return S2W_SUCCESS;
}

UINT8 App_ClkTuneCmd(UINT8 *ptr)
{
    UINT8  *p;
    UINT32 start, period;
   
    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_FAILURE;
    }
    AppS2wParse_Int(p, &start);
    if(start > 1)
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    if(AppS2wParse_Int(p, &period) != S2W_SUCCESS)
    {
        return S2W_FAILURE;
    }
    if(start == TRUE)
    {
        s2wCurrent.clkCalibEn = TRUE;
        s2wCurrent.clkCalibPeriod = period;
        appCtx.clkCaibTmrHndl = GsnSoftTmr_Start(&appCtx.clkCaibTmr, GSN_SOFT_TMR_PERIODIC, 0, SEC_TO_SYSTIME(period), AppS2w_ClkCalibCb, NULL);
    }
    else
    {
        if(appCtx.clkCaibTmrHndl != NULL)
        {
            GsnSoftTmr_Stop(appCtx.clkCaibTmrHndl);
        }
        s2wCurrent.clkCalibEn = FALSE;
    }
    return S2W_SUCCESS;
}


UINT8
AppS2wCmd_Hibernate(UINT8 *ptr)
{
    UINT8 status;
    S2W_ALARM_INFO_T alarm;
    UINT8 *p;
    memset(&alarm,0,sizeof(S2W_ALARM_INFO_T));
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    if (*p != '\0')
    {
        status = AppS2wParse_Boolean(p, &(alarm.alarm1Pol));
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        alarm.alarm1Valid = 1;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
        if (*p != '\0')
        {
            status = AppS2wParse_Boolean(p, &(alarm.alarm2Pol));
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            alarm.alarm2Valid = 1;
        }
    }

    AppS2wHal_PsHibernateRequest(&alarm);
    return S2W_SUCCESS;

}


UINT8 
AppS2wCmd_TempGet(UINT8 *ptr)
{
    INT32 temp;
    UINT8 wlanTemp, *p, cpu, status;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &cpu);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(cpu)
    {
        GsnSysCtl_DieTempGet(&appCtx.sysCtlCtx, &wlanTemp);
        S2w_Printf("\n\rWLAN:%d", wlanTemp);
    }
    else
    {
        temp = GsnIntTempSen_Get();
        S2w_Printf("\n\rAPP:%d", temp);
    }
    
    return S2W_SUCCESS;
}

UINT8 
AppS2wCmd_TempReadStart(UINT8 *ptr)
{
    UINT8 *p, status, enable;
    UINT32 period;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &enable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    if(enable)
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }

        status = AppS2wParse_Int(p, &period);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        GsnSysCtl_DieTempSendTimerStart(&appCtx.sysCtlCtx, period);
    }
    else
    {
        GsnSysCtl_DieTempSendTimerStop(&appCtx.sysCtlCtx);
    }
    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_OtaFwupRollBack(UINT8* ptr)
{
    if(GsnFwup_RollBackOtafu() == GSN_SUCCESS)
    {
        GsnSys_Reset((GSN_RESET_REASON_T)0);
    }
    else
    {
        return S2W_FAILURE;
    }
    return S2W_SUCCESS;
}
