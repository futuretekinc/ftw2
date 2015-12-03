/*****************************************************************
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
* $RCSfile: s2w_misc_command.c,v $
*
* Description : s2w command interprter file
******************************************************************/
#ifndef IOT_APP_ENABLE


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include "time.h"
#include <ctype.h>
#include <string.h>
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "hal/s2w_timer.h"
#include "parser/s2w_parse.h"
#include "parser/s2w_process.h"
#include "parser/s2w_command.h"
#include "hal/s2w_net.h"
#include "app_defines_builder.h"
#include "hal/s2w_config.h"
//#include "config\app_config_private.h"
#include "hal/s2w_cert_mgmt.h"
#include "main/app_main_ctx.h"
#include "config/app_stat_config.h"
#include "app_rtc_mem.h"
#include "app_events.h"
//#include "modules\gsn_dyn_alloc_chk.h"
#include "config/app_resource_config.h"
#include "config/app_httpd_config.h"
//#include "config\app_ncm_config.h"
//#include "web_prov/html/app_http_fs.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
//#include "gsn_httpd_config.h"
//#include "gsn_httpd_prov.h"
//#include "modules/gsn_httpd_logo.h"
//#include "config/app_httpd_config.h"
#include "web_prov\s2w_web_prov.h"
#include "../src/gslink\app_mcu_def.h"
#ifdef S2W_GSLINK
#ifdef S2W_GSLINK_XML
#include "modules/xml_string_parser/gsn_xml_string_parser.h"
#endif
#endif
//#include "web_prov\s2w_web_prov.h"
#if defined(S2W_DTLS_CLIENT_SUPPORT)
#include "modules/dtls/gsn_dtls.h"
#endif

#ifdef GSN_MEM_TRACE
#include "modules\dbg\gsn_dyn_alloc_chk.h"
#endif

#include "ftw_includes.h"
#include "ftw_net.h"
#include "ftw_mqtt.h"


#define TX_BUF_ELEMENTS                 19
#define TX_MAC_INDEX                    0x06
#define TX_BSSID_INDEX                  0x07
#define TX99_BUF_ELEMENTS               21
#define TX99_MAC_DESTADDR_INDEX         6
#define TX99_MAC_BSSID_INDEX            7
#define TX100_BUF_ELEMENTS              14
#define CR_WAVE_BUF_ELEMENTS            5
#define RX_BUF_ELEMENTS                 6
#define RX_MAC_INDEX                    0x03
#define HTTP_SEND_CHUNK_SIZE   			1000

#ifdef S2W_HTTP_CUSTOM_SUPPORT
#define HTTP_HDR_BITMAP_STR_SIZE        8
#endif

typedef enum RF_TEST
{
	RF_TX_TEST,
	RF_TX99_TEST,
	RF_TX100_TEST,
	RF_CARRIER_WAVE_TEST,
	RF_RX_TEST

}RF_TEST_T;

#ifdef ADK_PROV
#include "modules/http/gsn_httpd_api.h"
#endif
#ifdef ADK_OTAFU
#endif
PUBLIC UINT8 *pS2wHttpdTaskStack;
extern S2W_PROFILE_T s2wCurrent;
extern GSN_OSAL_QUEUE_T s2wNetQueue;
UINT8 mdnsv6Enable;
/**
 ******************************************************************************
 * @file s2w_misc_command.c
 * @brief S2W Application command routines.
 *      This file contains the s2w application specific implimentation for
 *      functions for each command .
******************************************************************************/

/*****************************************************************************
  *  Private Variables
  *****************************************************************************/

/*****************************************************************************
  *  Public Variables
  *****************************************************************************/

extern UINT8 curCid;
extern S2W_LINK_STATE_T s2wLinkState ;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern UINT8 s2wNRAWState;
extern UINT8 stbySuccess;
extern UINT8 storeParams;
extern BOOL ncmAutoMode;
#ifdef S2W_RFTEST
extern UINT32 asyncFrameCount;
#endif
extern S2W_PROFILE_PARAMS_T profile_params;
UINT8 frameTransmissionType = 0;
#ifdef S2W_UNASSOC_TXRX_SUPPORT
S2W_UNSOLICITED_FRAME_T frame;
#endif

#if 0
PRIVATE const char *S2W_ErrList[] =
{
    "NO ERROR",                         /* S2W_ERR_NOERROR */
    "ERR:SSID NOT FOUND",                /* S2W_ERR_SSID_NOT_FOUND */
    "ERR:AUTH FAIL:PSK INVALID",         /* S2W_ERR_PSK_INVALID */
    "ERR:AUTH FAIL:TIMEOUT",             /* S2W_ERR_AUTH_TIMEOUT */
    "ERR:AUTH FAIL:EAP_FAST_FAILURE",     /* S2W_ERR_AUTH_EAP_FAST_FAILURE */
    "ERR:AUTH FAIL:EAP_CRED_FAILURE",     /* S2W_ERR_AUTH_EAP_CRED_FAILURE */
};
#endif


#define S2W_INVALID_CERT_INDEX 0xFFFFFFFF
extern UINT32 certIndex, certFormat, certFileSize;
extern S2W_SSL_CERT_SRAM_TABLE_T s2w_ssl_cert_table[];
extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;
extern S2W_CID_T s2wCidList[];
#ifdef S2W_HTTPC_SUPPORT
extern GSN_HTTPC_CONF_INFO_T httpConfInfo;
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypes[];
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypesModified[];
#endif

/* packet pool handle to be used by HTTP server */
GSN_NW_PKT_POOL_HANDLE   trPktPoolHndl;
void                    *s2wHttpdPktPtr;
#define S2W_HTTPD_PKT_POOL  (10*1024)

#endif
extern const UINT8 server_key[];
extern const UINT8 server_cert[];
extern const UINT8 ca_cert[];

/*****************************************************************************
 *  Private Functions
 *****************************************************************************/


VOID S2w_AsyncMsgGpioOp(UINT8 flag);


#ifdef S2W_GSLINK
UINT8
AppS2w_HttpdCtxInit(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT8 reinit);

#ifdef S2W_WEB_SERVER

GSN_HTTPD_STATUS_T
McuHttpCb(ttHttpdUserEvent event, const char* uri,
        ttHttpdUserConHandle conHandle);
#endif
#ifdef S2W_GSLINK_XML

extern VOID
App_XmlParserCb(VOID *cbContext,GSNXMLSTR_CB_PARAM_T *xmlCbparams);
#endif
#endif /* S2W_GSLINK */

extern INT8*
GsnHttpd_GetBuffer();

#ifdef S2W_MDNS_ENABLE

VOID
AppS2wHal_MdnsInit(UINT8*);

PUBLIC UINT8
AppS2wHal_MdnsHostNameReg(S2W_MDNS_HN_PARAM_T *pHNparam);

PUBLIC UINT8
AppS2wHal_MdnsHostNameDereg(S2W_MDNS_HN_PARAM_T *pHNparam);

PUBLIC UINT8
AppS2wHal_MdnsServiceReg(S2W_MDNS_SRV_PARAM_T *pSrvParam);

PUBLIC UINT8
AppS2wHal_MdnsServiceReg(S2W_MDNS_SRV_PARAM_T *pSrvParam);

PUBLIC UINT8
AppS2wHal_MdnsSrvcDiscover(S2W_MDNS_SRVCDISCVR_PARAM_T *mdnsSrvDscr);

#endif

#ifdef S2W_ISOTX_SUPPORT
extern GSN_STATUS
GsnIsotx_BlinkReq(GSN_ISOTX_CTX_T *pIsotxCtx, 	GSN_ISOTX_BLINK_REQ_PARAM *pParam);

extern GSN_STATUS
GsnIsotx_StopReq(GSN_ISOTX_CTX_T *pIsotxCtx);

extern GSN_STATUS
GsnIsotx_RegWriteReq(GSN_ISOTX_CTX_T *pIsotxCtx, 	GSN_ISOTX_REG_WRITE_REQ_PARAM *pParam);
extern VOID
App_IsotxCtrlNotifCb(VOID *ctx, UINT16 msgId, UINT16 msgLen,	VOID *pMsg);

#endif


#ifdef S2W_MEM_ACCESS
extern PUBLIC GSN_STATUS
GsnSysCtl_MemReadReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_MEM_READ_REQ_T * pMemReadReqParam);
extern PUBLIC GSN_STATUS
GsnSysCtl_MemWriteReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx,          GSN_SYS_CTL_MEM_WRITE_REQ_T *pMemWrReqParam);

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief help print function
 *   This function prints the help information of all commands.
 * @param cmd - IN  Pointer to the user input command.
 * @param desc - IN Pointer to the desription.
 * @return none.
 ******************************************************************/
VOID
AppS2wHelp_Print(const char *cmd, const char *desc)
{
    int len = cmd ? strlen(cmd) : 1;
    int desclen = strlen(desc);
    int left = 78;
    int i;

    S2W_ASSERT(desclen <= left);

    AppS2wHal_CharNPut("\r\n", 2);
    AppS2wHal_CharNPut(cmd ? cmd : " ", len);

    left -= len;
    if (desclen > left)
    {
        AppS2wHal_CharNPut("\r\n", 2);
        left = 78;
    }

    for (i = 0; i < left - desclen; i++)
    {
        S2w_PutChar(' ');
    }

    AppS2wHal_CharNPut(desc, desclen);
}

#if 0
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the Help command
 *        Help command lists all the Serial2WiFi Host commands.
 *        It also displays the command format and the brief descriptions about
 *        the command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Help(UINT8 *ptr)
{

/**************** Command Interface********************************************************************************/
	AppS2wHelp_Print("AT",	"verify that the command interface is operating correctly \
					\n\rit should return a successful response OK (or 0 if verbose mode is disabled");
    AppS2wHelp_Print("ATE<0|1>", "Disable/enable echo");
    AppS2wHelp_Print("ATV<0|1>", "Disable/enable verbose responses");
    AppS2wHelp_Print("AT?", "Help");
/****************************************************************************************************************/

/**************** UART/ADAPTER Interface Configuration***************************************************************/
    AppS2wHelp_Print("ATB=<rate>,<bitsperchar>,<parity>,<stopbits>",
                      "Configure serial port");
    AppS2wHelp_Print("AT&K<0|1>", "Disable/enable software flow control");
    AppS2wHelp_Print("AT&R<0|1>", "Disable/enable hardware flow control");
    AppS2wHelp_Print("ATSparam=value", "Set configuration parameters");
	AppS2wHelp_Print("AT+UARTFLVL=<?>/<Rx Level>,<Tx Level>" ,"Sets/displays the UART FIFO thresholds");
    AppS2wHelp_Print("ATI<n>", "Display identification number n");	
	AppS2wHelp_Print("AT+WST=<Min scan time>,<Max scantime> <passive time>","configures the scan time");
/****************************************************************************************************************/

/****************************Profile Management*******************************************************************/
    AppS2wHelp_Print("AT&W<0|1>", "Save Settings to profile 0/1");
    AppS2wHelp_Print("ATZ<0|1>", "Load Settings from profile 0/1");
    AppS2wHelp_Print("AT&Y<0|1>",
                     "Set default power on profile to profile 0/1");
    AppS2wHelp_Print("AT&V", "Output current configuration");
    AppS2wHelp_Print("AT&F", "Reset to factory defaults");

/****************************************************************************************************************/

/****************************WiFi Interface************************************************************************/
	AppS2wHelp_Print("AT+NMAC=<?>/<mac>",
						 "Get/Set MAC address and store in flash");
    AppS2wHelp_Print("AT+WREGDOMAIN=<?>/<domain>","Get/Set Reg.Domain.domain values:fcc->0,etsi->1,telec->2");	
    AppS2wHelp_Print("AT+WS[=<SSID>[,<BSSID>][,<Ch>][,<ScanTime>]]",
                     "Perform wireless scan");
	AppS2wHelp_Print("AT+WM=<0|1>",
							 "Set mode to Infrastructure (0) or ad-hoc (1)");
    AppS2wHelp_Print("AT+WA=<SSID>[[,<BSSID>][,<Ch>]]",
                     "Associate to network or form ad-hoc network");
    AppS2wHelp_Print("AT+WD or ATH", "Disassociate from current network");
#ifdef S2W_SECURITY_WPS_ENABLE
	AppS2wHelp_Print("AT+WWPS=<1/2>,<wps pin>",
					 "Associate to an AP using WPS. 1 - Push Button mathod.   \
					 2 - PIN mathod. Provide <wps pin> only in case of PIN mathod");
#endif
#ifndef S2W_IP2WIFI_SUPPORT
		AppS2wHelp_Print("AT+NSTAT=?", "Display current network context");
#endif
	AppS2wHelp_Print("WLANSTATS=?","");
	AppS2wHelp_Print("AT+WRSSI=?", "Query the current RSSI value");
	AppS2wHelp_Print("AT+WRATE=?", "Query the current WiFi rate used");
    AppS2wHelp_Print("AT+WRETRY=n", "Set the wireless retry count");
	AppS2wHelp_Print("AT+APCLIENTINFO=?", "Get the information about the clients associated to node \
					\n\rwhen it acts as a limited AP");
	AppS2wHelp_Print("AT+BCONMISSTHRHLD=<BeaconMissThresholdTime>,<BeaconMissThresholdCount>",
			 		 "Configure the beacon miss threshold count and time");
	AppS2wHelp_Print("AT+TKIPCNTRMSR=<0|1>", "");	
	AppS2wHelp_Print("AT+TKIPSEQSET=","");	
/*******************************************************************************************************************/
    AppS2wHelp_Print("AT+WRXACTIVE=<0|1>", "Enable/disable the radio");
    AppS2wHelp_Print("AT+WRXPS=<0|1>", "Enable/disable 802.11 power save");
    AppS2wHelp_Print("AT+WP=<power>", "Set the transmit power");
    AppS2wHelp_Print("AT+WSTATUS", "Display current Wireless Status");
    AppS2wHelp_Print("AT+WSYNCINTRL=<interval>","configure the sync loss interval in TBTT interval");
	AppS2wHelp_Print("AT+WAPSM=<0|1|2|3>", " configure 802.11 power save mode to be used during association");
	AppS2wHelp_Print("AT+WIEEEPSPOLL=<n>[,listen beacon interval]", "sets the listen intervals for n beacons  \
					 \n\r The interval range is 1 to 65535 beacons");				 
    AppS2wHelp_Print("AT+PSPOLLINTRL=<interval>", "configure the Ps poll interval in Seconds");
	AppS2wHelp_Print("AT+MCSTSET=<0/1>", " enable or disable multicast and broadcast reception");
/*******************************************************************************************************************/

/****************************WiFi Security***************************************************************/
	AppS2wHelp_Print("AT+WAUTH=<authmode>",
						 "Set authmode (1->open,2->shared)");	
	AppS2wHelp_Print("AT+WWEPn=<key>",
						 "Set WEP key (10 or 26 hex digits) with index n (1-4)");
	AppS2wHelp_Print("AT+WWPA=passphrase",
						 "Set WPA passphrase (8 - 63 chars)");
	AppS2wHelp_Print("AT+WPAPSK=<SSID>,<PassPhrase>",
						 "Calculate and store the PSK");
	AppS2wHelp_Print("AT+WPSK=<PSK>", "Store the PSK");		
#if defined(S2W_SECURITY_ENTERPRISE_TLS_AVAILABLE) || defined(S2W_SECURITY_ENTERPRISE_FAST_MSCHAPV2_AVAILABLE) || defined(S2W__SECURITY_ENTERPRISE_PEAP_V0_AVAILABLE)|| defined(S2W__SECURITY_ENTERPRISE_TTLS_AVAILABLE) || defined(S2W_SECURITY_ENTERPRISE_FAST_GTC_AVAILABLE)|| defined(S2W__SECURITY_ENTERPRISE_PEAP_V1_AVAILABLE)
	AppS2wHelp_Print("AT+WEAPCONF=<outer authtype>,<inner authtype>,<user name>,<password>",
		   "Configure auth type,user name and password for EAP");
	AppS2wHelp_Print("AT+WEAP=<type>,<format>,<size>,<location>\n\r<ESC>W<data of size above>",
		"Provision certificate for EAP TLS. Type-CA/CLIENT/PUB_KEY(0/1/2),format\
		-binary/ascii(0/1),location- flash/RAM(0/1).Follow the escape sequence to send data.");
#endif
#ifndef S2W_IP2WIFI_SUPPORT
	AppS2wHelp_Print("AT+TCERTADD=<name>,<format>,<size>,<location>\n\r<ESC>W<data of size above>",
		   "Provisions a certificate. format-binary/ascii(0/1),location-FLASH/RAM.\
			\n\rFollow the escape sequence to send data.");
	AppS2wHelp_Print("AT+TCERTDEL=<name>", "Delete a certificate");
#endif
	AppS2wHelp_Print("AT+WSEC=n", "configure the security[0 - Auto,1 - Open,  2 - WEP \
					\n\r 3 - WPA-PSK,4 - WPA2-PSK,16 - WPA Enterprise, 32 - WPA2 Enterprise");
/*******************************************************************************************************************/

/*****************Connection Management *****************************************************************************/
#ifndef S2W_IP2WIFI_SUPPORT
    AppS2wHelp_Print("AT+NCTCP=<IP>,<Port>", "Open TCP client");
    AppS2wHelp_Print("AT+NCUDP=<IP>,<RemotePort>,[<LocalPort>]",
                     "Open UDP client");
    AppS2wHelp_Print("AT+NSTCP=<Port>", "Open TCP server on Port");
    AppS2wHelp_Print("AT+NSUDP=<Port>", "Open UDP server on Port");
    AppS2wHelp_Print("AT+NCLOSE=cid", "Close the specified connection");
    AppS2wHelp_Print("AT+NCLOSEALL", "Close all connections");
    AppS2wHelp_Print("AT+SETSOCKOPT=<cid>,<type>,<parameter>,<value>,<length>",
                      "Set options of a socket specified by cid");
    AppS2wHelp_Print("AT+NXSETSOCKOPT=<cid>,<type>,<parameter>,<value>,<length>",
                      "Set options of a socket specified by cid");

	AppS2wHelp_Print("AT+SSLOPEN=<cid>,<name>",
		"Opens a ssl connection. name-Name of certificate to use");
	AppS2wHelp_Print("AT+SSLCLOSE=<cid>","Close a SSL connection");
	AppS2wHelp_Print("AT+HTTPOPEN=<hostName/ip addr>,[<port>,<secured/non secured>,<certificate name>]",\
		"Opens a http/https connection");
	AppS2wHelp_Print("AT+HTTPCLOSE=<cid>", "Closes a http connection");
	AppS2wHelp_Print("AT+HTTPSEND=<cid>,<Method>,<TimeOut>,<Page>[,<Size>]\n\r<ESC>H<data of size above>",
		"Send a Get or POST request.Method- GET/HEAD/POST(1/2/3) Follow the escape sequence to send data");
	AppS2wHelp_Print("AT+HTTPCONF=<Param>,<Value>", "Configures http parameters");
	AppS2wHelp_Print("AT+HTTPCONFDEL=<Param>", "Delete the http Configuration parameters");		
	AppS2wHelp_Print("AT+CID=?", "Display The CID info");
#ifdef S2W_WEB_PROV
#ifdef S2W_IP2WIFI_SUPPORT
	   AppS2wHelp_Print("AT+WEBPROV=<user name>,<passwd>,<ip addr><subnet mask> <gateway>",
							"start web server. username passwd are used for authentication\
							The server is atarted with the given ip addr, subnetmask and gateway");
#else
	   AppS2wHelp_Print("AT+WEBPROV=<user name>,<passwd>,[<SSL enable>,<Store params>,<Idle timeout>,<NCM auto connect>]",
							   "start/stop web server. 1-start,0-stop. username passwd are used for authentication\r\n");
	   AppS2wHelp_Print("AT+WEBPROVSTOP=",
							"stops the web server\r\n");
	   AppS2wHelp_Print("AT+ NURIREDIR=<URL>",	"Adds the redirection URI");
#endif
#ifdef S2W_WEB_SRVR_LOGO_INTRNL_FLASH
	   AppS2wHelp_Print("AT+WEBLOGOADD=<size>","add webserver logo of size <size>. After issuing \
					  the command, send <esc> followed by l/L	and send the content of the logo file");
#endif
#endif
#ifdef S2W_UNASSOC_TXRX_SUPPORT	
	AppS2wHelp_Print("AT+UNSOLICITEDTX=<FC>,<SC>,<CH>,<Rate>,<Power>,<CCA Enable>,<FrameLength>,<Rx_WaitTime>, \
					<DestAddr>,[<RxAddr3>],[<TxAddr4>]<FC>,<SC>,<CH>,<Rate>,<Wmm>,<Receiver Mac>,<Bssid>,<FrameLen>",
					"\n\rconfigure and start unsolicited Tx.After issuing this cmd send <ESC> followed by \
					\n\r D/d and frame content");
	AppS2wHelp_Print("AT+UNSOLICITEDRX=<TypeBitmap>,<IEFilterEnable>,<IEID>,<Channel>,<Rx_WaitTime>",
					"\n\rconfigure and start unsolicited Rx.Data will send <ESC>D<Data> format");
	AppS2wHelp_Print("AT+UNSOLICITEDRX=<TypeBitmap>,<IEFilterEnable>,<IEID>,<Channel>,<Rx_WaitTime>",
					"\n\r start Unsolicited data reception"); 
	AppS2wHelp_Print("AT+UNSOLICITEDRXSTOP", "Stops unsolicited Rx");
#endif
#ifdef S2W_ISOTX_SUPPORT
	AppS2wHelp_Print("AT+ISOTXSTART=<frequency>,<gain>,<blink type>,<bandwidth>,<mode>,<no of blinks> \
					[,<interval between 1st blink>,,<interval between 2nd blink>,...]>",
					"\n\r starts the ISOTX Transmission");
	AppS2wHelp_Print("AT+ISOTXSTOP=","stops the ISOTX Transmission");
	AppS2wHelp_Print("AT+ISOTXREGWR= <addr>,<value>","configures the ISOTX");
#endif	
	AppS2wHelp_Print("AT++NIPMULTICASTJOIN=<ip>", "Joins multicast group");
	AppS2wHelp_Print("AT++NIPMULTICASTLEAVE=<ip>", "Leaves multicast group");
#endif
/***************** ***** ***** ***** *****************************************************************************/
/****************Auto connection************************************************************************************/
    AppS2wHelp_Print("AT+WAUTO=<Mode>,<SSID>,<bssid>,[Channel]",
                     "Configure auto connect wireless settings");
	AppS2wHelp_Print("AT+NCMAUTO=<Mode>,<Start/Stop>[,Level] ,[<Nvds store flag>]",
					 "starts the Network Connection Manager \n\r\
					 Mode: 0-station,1-Limited AP \n\r\
					 Level: 0-L2+L3 Connection,1-L2+L3+L4 connection");
    AppS2wHelp_Print("AT+NAUTO=<Type>,<Protocol>,<DestIP>,<DestPort>",
            "Configure auto connection");
    AppS2wHelp_Print(NULL,
                     "Client(0)/server(1), protocol UDP(0)/TCP(1),and host");
	AppS2wHelp_Print("AT+APCONF=<1>","Enable the NCM AP configuration");
#ifndef S2W_IP2WIFI_SUPPORT
/***************Misc Commands************************************************************************************/
    AppS2wHelp_Print("AT+BDATA=<0|1> ","Enable bulk data");
	AppS2wHelp_Print("AT+RESET","Resets the Device");
	AppS2wHelp_Print("AT+NTIMESYNC= <Enable>,<Server IP>,<Timeout>,<Periodic>,[<frequency>]",
					 "\n\rSets the system time using the SNTP");
	AppS2wHelp_Print("AT+SETTIME=<dd/mm/yyyy>,<HH:MM:SS>","Set the system time");
	AppS2wHelp_Print("AT+GETTIME=?","Get the system time in Milli-seconds since Epoch(1970)");
	AppS2wHelp_Print("AT+DGPIO=<GPIO_PIN>,<1-SET/0-RESET>","Set/reset a gpio pin");
	AppS2wHelp_Print("AT+VER=?|?", "Get the Version Info");
	AppS2wHelp_Print("AT+PING=<Ip>,<Trails>,<Interval>,<Len>,<TOS>,<TTL>,<PAYLAOD(16 Bytes)>",
						 "Starts Ping");
    AppS2wHelp_Print("AT+NSET=<IP>,<NetMask>,<Gateway>",
                     "Configure network address");
	AppS2wHelp_Print("AT+SOTAFWUPSTART=<value>", "start the Firmware upgrading procedure");
	AppS2wHelp_Print("AT+SOTAFWUPCONF=<param>,<value>","configure the firware upgrade parameters");
	AppS2wHelp_Print("AT+ASYNCMSGFMT=<0|1>","enable/disable enhanced asynchronous notification ");
/****************************************************************************************************************/
	#if 0
    AppS2wHelp_Print("ATC<0|1>", "Disable/enable auto connection");
    AppS2wHelp_Print("ATA", "Initiate AutoConnect");
    AppS2wHelp_Print("ATA2", "Initiate AutoConnect-tcp/udp level");
    AppS2wHelp_Print("ATO", "Return to Auto Data mode");

    AppS2wHelp_Print("+++",
                     "Switch to Command mode while in auto-connect mode");

    AppS2wHelp_Print("ATSparam=value", "Set configuration parameters");
    AppS2wHelp_Print(NULL,
                     "Network connection timeout (0) / Auto associate timeout (1)");
    AppS2wHelp_Print(NULL,
                     "TCP connection timeout (2) / Association retry count (3)");
    AppS2wHelp_Print(NULL, "Nagle algorithm wait time (4)");
	 AppS2wHelp_Print("AT+FWUP=<SrvIp>,<SrvPort>,<SrcPort>", "Start FW Upgrade");
#endif
#endif
   

#ifndef S2W_IP2WIFI_SUPPORT

/****************Network Interface***************************************************************************************/
	AppS2wHelp_Print("AT+DNS=1/0,<url>" , "start/stop the DNS server,URL is the DNS name \
					\n\r associated to the DNS IP address");
	AppS2wHelp_Print("AT+DHCPSRVR=<Start/Stop>[,<DnsOptionDisable>,<GatewayOptionDisable>]",
					 "\n\r start/stop the DHCP server");
	AppS2wHelp_Print("AT+DHCPSRVRCFG=<start IP addr>,<no Clients>","configure DHCP server");
	AppS2wHelp_Print("AT+NDHCP=<0|1>", "Disable/Enable DHCP");
    AppS2wHelp_Print("AT+DNSLOOKUP=<URL>,[<RETRY>,<TIMEOUT-S>]",
                     "Get the ip from host name");
    AppS2wHelp_Print("AT+DNSSET=<DNS1-IP>,[<DNS2-IP>]",
                     "Set static DNS IP addresses");
#ifdef S2W_MDNS_ENABLE
	AppS2wHelp_Print("AT+MDNSSTART","Initialise MDNS module");
	AppS2wHelp_Print("AT+MDNSHNREG=<Host name>,<Domain name>,[<TTL>,<scope><Conflict Detect>]","Register Host Name");
	AppS2wHelp_Print("AT+MDNSHNDEREG==<host name>,<Domain name>", "De-register Host Name");
	AppS2wHelp_Print("AT+MDNSSRVREG=<ServiceInstanceName>,<ServiceSubType>,<ServiceType>, <Protocol>,\
					\n\r <Domain>,<port>,<Default Key=Val>...<key n=valn >,<TTL>[<TTL>,<scope>\
					,\n\r<Conflict Detect>]",
					"Register MDNS service");
	AppS2wHelp_Print("AT+MDNSSRVDEREG=<ServiceInstanceName>,[<ServiceSubType>],<ServiceType>, <Protocol>,<Domain>",
					"De-register MDNS service");
	AppS2wHelp_Print("AT+MDNSSD=[<Service subtype>],<Service type>,<Protocol>,<Domain>",
					  "Discover the mDNC service");
	AppS2wHelp_Print("AT+MDNSANNOUNCE", "Announce the mDNS services");	
#endif
	AppS2wHelp_Print("AT+STORENWCONN", "Store the nw context");
	AppS2wHelp_Print("AT+RESTORENWCONN", "Restore the nw context");
#endif
/****************************************************************************************************************/

/****************Battery Check*************************************************************************************/
    AppS2wHelp_Print("AT+BCHKSTRT=<Measure interval>","Start the batt chk ");
    AppS2wHelp_Print("AT+BCHK=<?>/<Measure interval>",
                     "Get/Set batt chk param ");
    AppS2wHelp_Print("AT+BATTVALGET",
                     " Get the latest battery value stored in RTC");
    AppS2wHelp_Print("AT+BCHKSTOP ","Stop the batt chk ");

    AppS2wHelp_Print("AT+BATTLVLSET=<Warning Level>,<warning Freq>,<Standby Level>",
                     "Set batt warning level, frequency of reporting warning and batt standby levl ");

/****************************************************************************************************************/
#ifdef S2W_RFTEST
    AppS2wHelp_Print("AT+RFFRAMETXSTART=<CH>,<Power>,<Rate>,<No.Of.Times>,<Fr.Intrvel>,<FC>,<DurationId>,<SC>,<frameLen>,\
    				\n\r<Preamble>,<Scrambler>[,<DstMac>,<Src Mac>]",
    				"\n\rconfigure and start async Tx.After issuing this cmd send <ESC> followed by A/a and frame content");
    AppS2wHelp_Print("AT+RFWAVETXSTART=<Modulated>,<CH>,<rate>,<PreambleLong>,<ScamblerOff>,<Cont.Tx>,<Power>,<ssid>",
					"\n\rstart modulated/unmodulated Wave Tx.");
    AppS2wHelp_Print("AT+RFRXSTART=<CH>[,<sendtouser>]","start async Reception on channel CH.");
    AppS2wHelp_Print("AT+RFSTOP","stop the rf test which has been started.");
	AppS2wHelp_Print("AT+WFRAMETXTEST=<Channel>,<bandWidth>,<numFrames>,<frameLen>,<txRate>,<txPower>,<destAddr>,<bssid>,<htEnable> \
					,<guardInterval>,<greenField>,<preambleType>,<qosEnable>,<ackPolicy>,<scrambler>,<aifsnVal>,<antenna>",
					"\n\rn Enable the frame transmissionwith the given configurations");
	AppS2wHelp_Print("AT+WTX99TEST=<Channel>,<bandWidth>,<numFrames>,<frameLen>,<txRate>,<txPower>,<destAddr>,<bssid>,<guardInterval> \
					  ,<greenField>,<antenna>,<cca>,<agc>,<contPreambleMode>,<spreader>,<scrambler>,<preamble>,<preambleType>,\
					  <phyTestTxtRate>,<modeSelect>", "Starts TX99 mode with the given configurations");
	AppS2wHelp_Print("AT+WTX100TEST=<Channel>,<bandWidth>,<txPower>,<antenna>,<cca>,<agc>,<contPreambleMode>,<spreader>,<scrambler>\
					  ,<preamble>,<preambleType>,<testPatternType>,<phyTestTxRate>,<modeSelect>",
					  "\n\rStarts TX100 mode with given configurations");
	AppS2wHelp_Print("AT+WCARWAVTEST=<Channel>,<bandWidth>,<txPower>,<antenna>,<customWavePeriod>","Starts Carrier Wave mode \
					  \n\rwith given configurations");
	AppS2wHelp_Print("AT+WRXTEST=<Channel>,<bandWidth>,<rxFrameTypeFilter>,<rxaddrFilter>,<antenna>", "Enables the frame reception");
	AppS2wHelp_Print("AT+WRXSTOP", "Stops the frame reception and displays the PER stats");
	AppS2wHelp_Print("AT+WCALIB","");
	AppS2wHelp_Print("AT+WTXSTOP","");
#endif
/****************Power Management********************************************************************************/
    AppS2wHelp_Print("AT+PSDPSLEEP", "Enable deep sleep");
    AppS2wHelp_Print("AT+PSSTBY=<n>[,<delay time>,<alarm1-pol>,<alarm2-pol>]",
                     "Standby request for n milliseconds");
/********************************************************************************************************************/
/****************GSLINK**********************************************************************************************/
	AppS2wHelp_Print("AT+WEBSERVER=<start/stop>,<user name>,<passwd>,[<SSL enable>,<Idle timeout>,<Response Timeout>]",
						"start web server. username passwd are used for authentication\r\n");
	AppS2wHelp_Print("AT+XMLPARSE=<enable/disable>",
						  "Enable/Disable the XML parser. 1-Enable,0-Disable\r\n");
    AppS2wHelp_Print("AT+XMLSEND=<cid>,<Method>,<TimeOut>,<URL>,<root tag>,[<No of Tags>]",
			"Send a Get or POST request for XML data.Method- GET Response/POST Response(6/7) \r\n\
			 Follow the escape sequence to send data-<ESC>G<cid><len>tag:value");
	AppS2wHelp_Print("AT+URIRECV=<URI>[,Content Type]","Modifies the default URI and content type \n\r\
					  Content Type:	0-application/xml \r\n1-application/json,2-application/html\
					  \r\n 3-img/gif,4-application/octet-stream");
/********************************************************************************************************************/
#ifdef  S2W_FS_SPI_ENABLE
   AppS2wHelp_Print("AT+SPICONF=<CPOL(0/1)>,<CPH(0/1)>","Configure SPI clock polarity and clock phase");
#endif

/****************EMU Commands**********************************************************************************************/
#ifdef S2W_ISOTX_SUPPORT
	AppS2wHelp_Print("AT+EMUVER=?", "prints the EMU software version");
	AppS2wHelp_Print("AT+EMUSUPMOD=?", "prints the supported module lists");
	AppS2wHelp_Print("AT+EMUSTART", "starts the EMU");
	AppS2wHelp_Print("AT+EMUSTOP", "stops the EMU");
	AppS2wHelp_Print("AT+EMUSETCONF=<Param>,<Value>", "configures the EMU parameters");
	AppS2wHelp_Print("AT+EMUSETCONF=<Channel>,<Enable\Disable>,[<GainValue>]" ,
					 "\n\rconfigures the channel to a given gain value");
	AppS2wHelp_Print("AT+EMUGETCONF=<Param>", "prints configuration value set for the EMU");
	AppS2wHelp_Print("AT+EMUGETVALUES", "prints the last read raw ADC values of voltage and current");
	AppS2wHelp_Print("AT+EMULOADCTRL= <1/0>", "switches ON(1)/)OFF(0) the load"); 
	AppS2wHelp_Print("AT+EMURESETENERGY", "resets the energy");
	AppS2wHelp_Print("AT+EMUGETSTATUS", "gets the status of the EMU");
	AppS2wHelp_Print("AT+EMULOADSTATUS", "gets the load status of the EMU");
#endif
/***************************************************************************************************************************/
/****************Persistent Timer Commands**********************************************************************************************/
#if S2W_PERSISTENT_TMR_SUPPORT 
	AppS2wHelp_Print("AT+PRSTMRSTART=<ID>,<TYPE>,<PERIOD>", "Create a persistent Timer");
	AppS2wHelp_Print("AT+PRSTMRSTOP=<ID>", "Stop Persistent timer");
	AppS2wHelp_Print"AT+PRSTMRDEL=<ID>", "Delete persistent timer");
	AppS2wHelp_Print"AT+PRSTMRRESTART=<ID>,< PERIOD >", "Restart persistent timer with new period");
#endif

#ifdef S2W_IPv6_SUPPORT
   AppS2wHelp_Print("AT+NSETv6=<IPv6 Linklocal/Global Address>", "Configure Interface static IPv6 address");
   AppS2wHelp_Print("AT+NDHCPv6=<Enable/Disable>", "Configure Interface IPv6 address");
   AppS2wHelp_Print("AT+NCUDPv6=<IPv6 Address>,<Port>", "Connect to a remote UDP server with IPv6 address");
   AppS2wHelp_Print("AT+NSUDPv6=<Port>", "Open UDP server over IPv6");
   AppS2wHelp_Print("AT+NCTCPv6=<IPv6 Adrress>,<Remote Port>", "Connect to a remote TCP server with IPv6 address");
   AppS2wHelp_Print("AT+NSTCPv6=<Port>", "Open TCP server over IPv6");
   AppS2wHelp_Print("AT+DHCPSERVERv6=<Enable/Disable>", "Start DHCPv6 server");
   AppS2wHelp_Print("AT+PING=<IPv6 address>", "Ping to a IPv6 address");
   AppS2wHelp_Print("AT+DNSLOOKUPv6=<IPv6 FQDN>", "Resolve host name to IPv6 address");
   AppS2wHelp_Print("AT+DNSSET=<DNSv6 server address>", "Set static IPv6 DNS server");
   AppS2wHelp_Print("AT+MDNSv6START", "Start MDNS service over IPv6");
#endif   


    return S2W_SUCCESS;
}

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+PSPOLLINTRL Command.
 *   This function set the keep alive timer interval .
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure.
 ******************************************************************/
PUBLIC UINT8
S2w_CmdPsPollIntervelset(UINT8 *ptr)

{
    UINT32 interval;
    UINT8 *p;
    UINT8 status = S2W_EINVAL;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &interval);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(interval > 255)
    {
        return S2W_EINVAL;
    }
    /* bug id: 5823. Setting 0 will stop keep alive (to make it backward compatible with 1011) */
#if 0
    if(interval == 0)
    {
        interval = 45;/*Default*/
    }
#endif    
    status = AppS2wHal_PsPollIntervelset(interval);
    return status;
}


#ifdef S2W_CODE_COVERAGE
/**
 *******************************************************************************
 * code coverage commands
 *******************************************************************************/
 /*       CODECOVG01=<adcMode><refVoltage><clockSelect><samplePeriod>
 CODECOVG01=<GSN_ADC_PSMODE_OFF><GSN_ADC_REF_BANDGAP><GSN_ADC_CLK_SEL_1MHZ><20>
    AT+CODECOVG01= 0, 0, 0,20
 */

PUBLIC UINT8
AppS2wCmd_codeCvg01(UINT8 *ptr)
{
    UINT8 status;
    UINT32 adcMode;
    UINT32 refVoltage;
    UINT32 clockSelect;
    UINT32 samplePeriod;
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &adcMode);
    if(status != S2W_SUCCESS)
    {
        return status;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
      return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &refVoltage);
    if(status != S2W_SUCCESS)
    {
        return status;
    }

     p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &clockSelect);
    if(status != S2W_SUCCESS)
    {
        return status;
    }

     p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &samplePeriod);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
        return S2W_EINVAL;
    }
    return AppS2wHal_codeCovg01(adcMode, refVoltage, clockSelect, samplePeriod);


}

PUBLIC UINT8
AppS2wCmd_codeCvg02(UINT8 *ptr)
{
    UINT8 *p;
    UINT8 status;
    UINT32 waitTime;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
      return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &waitTime);
    if(status != S2W_SUCCESS)
    {
        return status;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
      return S2W_EINVAL;
    }
    return AppS2wHal_codeCovg02(waitTime);
}

PUBLIC UINT8
AppS2wCmd_codeCvg03(UINT8 *ptr)
{
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
      return S2W_EINVAL;
    }
    return AppS2wHal_codeCovg03();
}

PUBLIC UINT8
AppS2wCmd_codeCvg04(UINT8 *ptr)
{
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
      return S2W_EINVAL;
    }
    return AppS2wHal_codeCovg04();

}

PUBLIC UINT8
AppS2wCmd_codeCvg05(UINT8 *ptr)
{
    UINT8 status;
    UINT32 numElemnts;
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
      return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &numElemnts);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    return APPS2wHal_codeCovg05(numElemnts);
}

PUBLIC UINT8
AppS2wCmd_codeCvg06(UINT8 *ptr)
{
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
      return S2W_EINVAL;
    }

    return APPS2wHal_codeCovg06();

}

PUBLIC UINT8
AppS2wCmd_codeCvg07(UINT8 *ptr)
{
    UINT8 status;
    UINT32 txPowLvl;
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
      return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &txPowLvl);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    return AppS2wHal_codeCovg07(txPowLvl);
}

PUBLIC UINT8
AppS2wCmd_codeCvg08(UINT8 *ptr)
{
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
      return S2W_EINVAL;
    }

    return AppS2wHal_codeCovg08();
}

PUBLIC UINT8
AppS2wCmd_codeCvg09(UINT8 *ptr)
{
    UINT8 *p;

    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
      return S2W_EINVAL;
    }

    return AppS2wHal_codeCovg09();
}
#endif




/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WPSK command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
#if 0 
UINT8
AppS2wCmd_Psk(UINT8 *ptr)
{
    UINT8 status;
    UINT8 psk[32];
    status = AppS2wParse_Psk(ptr,psk);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    return AppS2wHal_PskKeyStore(psk);
}
#endif


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WSEC command. This function set the strict
 * security feature.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
 #if 0
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

    {
        s2wCurrent.securityType = SecMode;
    }

    return S2W_SUCCESS;
}

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WAPSM Command.
     This function call the wdd ioctl function to set then association
     ps poll conserve.
 * @param ptr Pointer to the user string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure- disconnect failed.
 ******************************************************************/

#ifdef GSN_DHCP_SERVER_ENABLE
extern GSN_DHCP_SRVR_T dhcpSrvr;
extern GSN_MAC_ADDR_T* disconStaMac;
PUBLIC VOID
AppS2w_StaDisconnectSuccessProcess()
{
    /* Remove the http entry */
    GsnDhcpSrvr_ClientDelete(&dhcpSrvr,disconStaMac );
}
#endif


VOID S2w_AsyncMsgGpioInit()
{
    GsnIoMux_Sel(APP_S2W_ASYNC_GPIO, APP_S2W_ASYNC_GPIO_MUX);
    GsnIoMux_PullDownEnable (APP_S2W_ASYNC_GPIO);
    /* Initialise as Output */
    GsnGpio_Init(APP_S2W_ASYNC_GPIO_BITMAP, ~APP_S2W_ASYNC_GPIO_BITMAP);

}

VOID S2w_AsyncMsgGpioOp(UINT8 flag)
{
    if(flag)
    {
        GsnGpio_OutIndvidualSet(APP_S2W_ASYNC_GPIO_BITMAP);
    }
    else
    {
        GsnGpio_OutClear(APP_S2W_ASYNC_GPIO_BITMAP);
    }
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+ASYNCMSGFMT command
 *   This function check the input parameter and start/stop the
 *   enhanced asynchronous notification.
 * @param ptr Pointer to the user input string.
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_AsyncMsgFmt(UINT8 *ptr)
{
    UINT8 val;
    UINT8 status = S2W_SUCCESS;

    status = AppS2wParse_Boolean(ptr, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wCurrent.asyncMsgFormat = val;
    if(s2wCurrent.asyncMsgFormat)
    {
       S2w_AsyncMsgGpioInit();
       S2w_AsyncMsgGpioOp(0);
    }
    return status;
}



#ifdef GSN_DHCP_SERVER_ENABLE
extern GSN_DHCP_SRVR_T dhcpSrvr;
#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+VER command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/


#ifdef GS1500M
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WSTAT Command.
 *
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 ******************************************************************/


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+AGGR Command.
 *	 This function is used to enable or disable agrregation
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_AggregationSet(UINT8 *ptr)
{
	UINT8    status;
	UINT32   txTidMask;
	UINT32	 rxTidMask;
	UINT32	 val;
    UINT8 *p;

	p = AppS2wParse_NextParamGet(&ptr);

	 if (!p)
    {
        return S2W_EINVAL;
    }

	status = AppS2wParse_Hex(p, &txTidMask);  /* 16-bit mask allowing uplink ADDBA  negotiation; bit position indicates TID*/
	if (status != S2W_SUCCESS)
	{
		return status;
	}

	p = AppS2wParse_NextParamGet(&ptr);
	 if (!p)
    {
        return S2W_EINVAL;
    }

	status = AppS2wParse_Hex(p, &rxTidMask); /* 16-bit mask to allow donwlink ADDBA negotiation; bit position indicates TID*/
	if (status != S2W_SUCCESS)
	{
		return status;
	}

	val = (txTidMask <<16 ) |  rxTidMask;

	GsnWdd_AggregationSet(&s2wappMainTaskCtxt->wdd, val);

	return status;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WKEEPALIVE  Command.
 *	 This function is used to configure keep alive interval
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_KeepAliveSet(UINT8 *ptr)
{
	UINT8    status;
	UINT32    keepAliveInterval;
    UINT8 *p;


	p = AppS2wParse_NextParamGet(&ptr);

	 if (!p)
    {
        return S2W_EINVAL;
    }

	   /* validate the parameter as enable/disable
     */
    status = AppS2wParse_Int(p, &keepAliveInterval);
    if (status != S2W_SUCCESS)
    {
        return status;
    }


	GsnWdd_KeepAliveSet(&s2wappMainTaskCtxt->wdd, (UINT8)keepAliveInterval);
	/* Update in RTC memory */
	//appRtcMemData.wlanKeepAliveCount= (UINT8)keepAliveInterval;
	//GsnWif_SysRtcMemWrite(&s2wappMainTaskCtxt->wifCtx, sizeof(appRtcMemData),
      //                    (UINT8 *)&appRtcMemData);

	return status;
}
#endif

#if 0
#ifdef S2W_FILE_SYS
#define S2W_WR_BUFF_SIZE	1024
PUBLIC UINT8
AppS2wHal_FileWriteDataGet(INT32 fd, UINT32 dataLen)
{
    GSN_STATUS status = S2W_SUCCESS;
	UINT8 *dataBuff;
	UINT32 writeLen;

	dataBuff = (UINT8 *)gsn_malloc(S2W_WR_BUFF_SIZE);
    if(NULL ==  dataBuff)
    {
        status = S2W_FAILURE;
        goto AppS2wHal_FileWriteDataGetExit;
    }
	writeLen = 0;
    while(dataLen)
    {
        writeLen = dataLen >= S2W_WR_BUFF_SIZE? S2W_WR_BUFF_SIZE:dataLen;

        AppS2wHal_CharNGet(dataBuff,writeLen);
		/* write in to file */
		GsnFs_write(fd, dataBuff, writeLen);

		dataLen -= writeLen;
        /*S2w_Printf("%d\r\n", dataLen);*/
    }
	/* free the buffer */
	gsn_free(dataBuff);
AppS2wHal_FileWriteDataGetExit:
	S2w_Printf("\r\nOK\r\n");
   return status;
}
#endif
#endif





INT32 s2wErrorCode=0;





#ifdef S2W_GSLINK_RAW
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
AppS2wHal_RawhttpContentGet(UINT32 dataLen, UINT8 hCid)
{
    GSN_STATUS status = S2W_SUCCESS;
    s2wCidList[hCid].httpdCtx.moreData=1;
    while(dataLen)
    {
        s2wCidList[hCid].httpdCtx.httpdBufferLenUsed = dataLen >= 1000? 1000:dataLen;
#ifndef S2W_DUAL_INTERFACE_SUPPORT  
        AppS2wHal_CharNGet((UINT8*)s2wCidList[hCid].httpdCtx.httpdBuffer,s2wCidList[hCid].httpdCtx.httpdBufferLenUsed);
#else
        AppS2wHal_CharNGet1((UINT8*)s2wCidList[hCid].httpdCtx.httpdBuffer,s2wCidList[hCid].httpdCtx.httpdBufferLenUsed);
#endif
        dataLen = dataLen - s2wCidList[hCid].httpdCtx.httpdBufferLenUsed;
	    if(0 == dataLen )
	    {
	        s2wCidList[hCid].httpdCtx.moreData = 0;
	    }
         AppS2w_HttpSemRelease(hCid);
        GsnOsal_SemAcquire(&s2wCidList[hCid].httpdCtx.httpdSendSem,GSN_OSAL_WAIT_FOREVER);
		if(s2wappMainTaskCtxt->gsLinkSendStatus  == S2W_FAILURE)
		{
			status = S2W_FAILURE;
			break;
		}
	}
    return status;
}
#endif
#ifdef S2W_HTTPC_SUPPORT
#ifdef S2W_GSLINK

UINT8
AppS2wHal_GetStausCode(INT8 *httpRxBuf,UINT8 *statusCodeLen)
{
	INT8 *current;
	INT8 statusCode[5];
	UINT8 status=S2W_SUCCESS;
	UINT32 len=0;
	//current = strstr((const char *)httpRxBuf," ");
	memcpy(statusCode,httpRxBuf,3);
	if(memcmp(statusCode,"200",3) != 0)
	{
		status = S2W_FAILURE;	
	}
	current = strstr((const char *)httpRxBuf,"\n");
	if(current == NULL)
		status = S2W_FAILURE;	
	len = (current - httpRxBuf)+1;
	*statusCodeLen = len;
	return status;
}	

#ifdef S2W_HTTP_CUSTOM_SUPPORT
VOID
AppS2w_HttpStatusLineSet(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT8 statusline)
{
    if(httpdCtx != NULL)
    {
        httpdCtx->statusline = statusline;
    }
}

VOID
AppS2w_HttpHdrCountSet(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT32 headercount)
{
    if(httpdCtx != NULL)
    {
        httpdCtx->appheadercount = headercount;
    }
}

PUBLIC UINT8
AppS2wCmd_RecvConf(UINT8 *ptr)
{
    int cid, sendRespHdrs, sendStatus;
    UINT8 *p = NULL;
    UINT8 *hdr = NULL;
    UINT8 *status = NULL;
    UINT32 httpHddrBmap = 0;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    cid = AppS2w_CidValidate(*p);
    if( cid == INVALID_CID)
        return S2W_EBADCID;


    status = AppS2wParse_NextParamGet(&ptr);
    if (!status)
    {
       return S2W_EINVAL;
    }
    AppS2wParse_Int(status, &sendStatus);
    if(1 == sendStatus)
    {
        httpConfInfo.sendStatus = 1;
    }
    else
    {
    	httpConfInfo.sendStatus = 0;
    }

    /* Parse the Http header bitmap */
    hdr = AppS2wParse_NextParamGet(&ptr);
    if (!hdr)
    {
       return S2W_EINVAL;
    }
    AppS2wParse_HexString(hdr, &httpHddrBmap, HTTP_HDR_BITMAP_STR_SIZE);
    httpConfInfo.httpcHdrBmap = httpHddrBmap;

    return S2W_SUCCESS;
}
#endif


/**
******************************************************************
* @ingroup S2w-Application
* @brief Process AT+XMLRECV command
*	 This function adds the new URI.
* @param ptr Pointer to the user input string.
*
* @return S2W_SUCCESS - operation successful.
* @return S2W_FAILURE - operation Failed.
* @return S2W_EINVAL - operation Failed-invalid input
*************************************************************/




#ifdef S2W_GSLINK_XML

PUBLIC void
AppS2w_XmlRxBufferMgmtCb(VOID *context,
                   GSN_HTTPC_CONN_HANDLE conHandle,
                     INT8 *httpRxDataBuf,
                     INT32 httpRxDataLen,
                     INT32* rxBufferOffset)
{
    UINT8 cid,status,headerLen,statusCodeLen=0;
    INT8 startMark[10];
    ttHttpcConEntryPtr conEntryPtr = (ttHttpcConEntryPtr)conHandle;
	GSN_STATUS decodeStatus = GSN_FAILURE;
	headerLen=0;
    cid = AppS2wHal_CidFind(conEntryPtr->hconSd);
	if(s2wCidList[cid].httpdCtx.methodLineReceived==0)
	{
		status = AppS2wHal_GetStausCode(httpRxDataBuf,&statusCodeLen);
		headerLen = sprintf(startMark,"%c%c%x%04d", S2W_ESC, 'H', cid,statusCodeLen);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(startMark, headerLen);
		AppS2wHal_CharNPut(httpRxDataBuf,statusCodeLen);
#else
		AppS2wHal_CharNPut1(startMark, headerLen);
		AppS2wHal_CharNPut1(httpRxDataBuf,statusCodeLen);
#endif
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
		s2wCidList[cid].httpdCtx.methodLineReceived=1;		
		if(status == S2W_SUCCESS)
		{				
			decodeStatus = GsnXMLStr_Decode(s2wCidList[cid].xmlParserCtx,(UINT8 *)httpRxDataBuf,httpRxDataLen,App_XmlParserCb,NULL);
		}			
	}
	else				
	{
		decodeStatus= GsnXMLStr_Decode(s2wCidList[cid].xmlParserCtx,(UINT8 *)httpRxDataBuf,httpRxDataLen,App_XmlParserCb,NULL);
	}
	if(decodeStatus == GSN_XML_PARTIAL_ELEMENT)
	{
		*rxBufferOffset = s2wCidList[cid].xmlParserCtx->bytesTodecode;// S2W_SUCCESS;
	}
	else if((decodeStatus == GSN_INVALID_PARAM) || (decodeStatus == GSN_FAILURE))
		*rxBufferOffset = -1;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Http client send function.
 * @param cid                - IN the cid needs to be closed
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_EBADCID     - cid is not valid.
 * @retval S2W_FAILURE     - operation failed.
 ******************************************************************/
PUBLIC GSN_STATUS S2wHttp_XmlSend(UINT8 cid)
{
    UINT8 *httpRxDataBuf = NULL;
    UINT32 httpRxDataLen = 0;
    UINT32 ret = S2W_SUCCESS;
    INT8 startMark[10];
	UINT8 statusCodeLen=0,headerLen=0;
#ifdef S2W_HTTPC_SUPPORT
    S2W_HTTP_DATA_T *pHttpData;
#endif
    pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(cid);
    if(pHttpData == NULL)
    {
         return S2W_FAILURE;
    }
    if(0 == httpConfInfo.moredata)
    {/* prepare to receive response */
        httpRxDataLen = 1024 ;
        httpRxDataBuf = gsn_malloc(1024);
        if(NULL == httpRxDataBuf)
        {
            ret = S2W_FAILURE;
			goto S2wHttp_XmlSendExit;
        }
        httpConfInfo.rxBufferMgmtCb = AppS2w_XmlRxBufferMgmtCb;
      httpConfInfo.rxBufferMgmtCbCtx = NULL;
    }
	/*Make all the custom headers types as 255 - This is done to coply withi the ROM code which is
	compiled with header type array being defined as array of UINT8 */
	{
		UINT8 i;
		for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
        {
        	if(headerTypes[i] >= (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM)
			{
				headerTypesModified[i] = (GSN_HTTP_USER_HEADER_TYPE_T) TM_HTTP_HEADER_CUSTOM;
			}
			else
			{
        		headerTypesModified[i] = headerTypes[i];
			}
        }
	}
    ret = GsnHttp_Send(pHttpData->pHttpHandle, (INT8 *)httpRxDataBuf,
                       &httpRxDataLen, httpConfInfo.httpTimeOut, &httpConfInfo);
    if(GSN_SUCCESS == ret)
    {
        if(0 == httpConfInfo.moredata)
        {
			if(s2wCidList[cid].httpdCtx.methodLineReceived==0)
        	{
				ret = AppS2wHal_GetStausCode((INT8 *)httpRxDataBuf,&statusCodeLen);
    			headerLen = sprintf(startMark,"%c%c%x%04d", S2W_ESC, 'H', cid,statusCodeLen);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
				AppS2wHal_CharNPut(startMark, headerLen);
				AppS2wHal_CharNPut(httpRxDataBuf,statusCodeLen);
#else
				AppS2wHal_CharNPut1(startMark, headerLen);
				AppS2wHal_CharNPut1(httpRxDataBuf,statusCodeLen);
#endif
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
				s2wCidList[cid].httpdCtx.methodLineReceived=0;
				if(ret == S2W_SUCCESS)
				{				
					 GsnXMLStr_Decode(s2wCidList[cid].xmlParserCtx,(UINT8 *)httpRxDataBuf,httpRxDataLen,App_XmlParserCb,NULL);
				}			
			}
			else				
			{
				 GsnXMLStr_Decode(s2wCidList[cid].xmlParserCtx,(UINT8 *)httpRxDataBuf,httpRxDataLen,App_XmlParserCb,NULL);
			}						
        }
        ret = S2W_SUCCESS;
    }
    else /* ERROR or TimeOut */
    {
        ret = S2W_FAILURE;
    }
    if(NULL != httpRxDataBuf)
    {
        gsn_free(httpRxDataBuf);
        httpRxDataBuf = NULL;
    }
		if(NULL != httpConfInfo.reqPathPtr)
		   {
			   gsn_free(httpConfInfo.reqPathPtr);
			   httpConfInfo.reqPathPtr = NULL;
		   }
S2wHttp_XmlSendExit:
		if(NULL != httpConfInfo.reqPathPtr)
		   {
			   gsn_free(httpConfInfo.reqPathPtr);
			   httpConfInfo.reqPathPtr = NULL;
		   }
    return ret;
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the http data from the serial interface.
 *   This function reads the http data and sends to wifi.
 * @param hCid the cid of the http connection.
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_XmlPost( UINT8 hCid)
{
	GSN_STATUS status = S2W_SUCCESS;
    //S2W_HTTP_DATA_T *pHttpData;
	INT8 *buffer;
	UINT32 	dataLen=0/*,sendDataCount=0*/;

	buffer = s2wCidList[hCid].httpdCtx.httpdBuffer;
	//buffer = buffer - s2wCidList[hCid].httpdCtx.httpdBufferLenUsed;
	dataLen = s2wCidList[hCid].httpdCtx.httpdBufferLenUsed;
    httpConfInfo.moredata = 1;
	httpConfInfo.reqBodyPtr = buffer;
    httpConfInfo.reqBodyLen = dataLen;

    if(0 == s2wCidList[hCid].xmlParserCtx->moreData )
    {
        httpConfInfo.moredata = 0;
    }
    status = S2wHttp_XmlSend(hCid);

	httpConfInfo.reqBodyLen = 0;
    if(status != S2W_SUCCESS)
    {
    	httpConfInfo.moredata = 0;
        return S2W_FAILURE;
    }
return status;
}


#ifdef S2W_HTTP_CUSTOM_SUPPORT
extern ttConstCharPtr const TM_CONST_QLF
tlHttpdContentTypes[TM_HTTPD_CONTENT_TYPES_MAX] ;

extern const char  TM_CONST_QLF tlHttpdChunked[];
UINT8
AppS2w_HttpAddHdr(S2W_HTTPD_CONTEXT_T *httpdCtx, ttHttpUserHeaderType httphdrtype, UINT8  *httphdrvalptr)
{
    UINT32   i;
    UINT32 totalhdrcount;

    if((NULL == httpdCtx) || (NULL == httpdCtx->httphdrvalptrptr) ||
       (NULL == httpdCtx->httphdrnameptrptr) || (NULL == httpdCtx->httphdrtypeptr) || (NULL == httphdrvalptr))
    {
        return S2W_FAILURE;
    }

    totalhdrcount = httpdCtx->appheadercount + HTTP_STATIC_HDR_COUNT;
    /* search for an empty slot */
    for(i = 0; i < totalhdrcount; i++)
    {
        if(NULL == httpdCtx->httphdrvalptrptr[i])
        {
            //httpdCtx->httphdrnameptrptr[i] = gsn_malloc(hdrnamelen + 1);
            *(httpdCtx->httphdrvalptrptr + i) = gsn_malloc(strlen(httphdrvalptr) + 1);
            memset((*(httpdCtx->httphdrvalptrptr + i)), 0, (strlen(httphdrvalptr) + 1));
            break;
        }
    }

    if(i < totalhdrcount)
    {
//        strncpy(httpdCtx->httphdrnameptrptr, dataBuffer, hdrnamelen);
        strncpy(httpdCtx->httphdrvalptrptr[i], httphdrvalptr, strlen(httphdrvalptr));
        httpdCtx->httphdrtypeptr[i] = httphdrtype;
        httpdCtx->headercount++;
    }
    return S2W_SUCCESS;
}

UINT8 AppS2w_HttpAddStaticHdr(S2W_HTTPD_CONTEXT_T *httpdCtx, UINT32 totalhdrcount)
{
    UINT8        headerValue[32];
    UINT8       *tmpPtr;
    if(NULL == httpdCtx)
    {
        return S2W_FAILURE;
    }

    /* Get the HTTP format string of the current time */
    memset(headerValue, 0, 32);
    tmpPtr = tfHttpGetCurrentTime(headerValue, 32);
    if (tmpPtr == headerValue)
    /* no converstion, because the buffer was too small */
    {
        return S2W_FAILURE;
    }

    AppS2w_HttpAddHdr(httpdCtx, TM_HTTP_HEADER_DATE, headerValue);
    AppS2w_HttpAddHdr(httpdCtx, TM_HTTP_HEADER_CONTENT_TYPE, (unsigned char *)tlHttpdContentTypes[TM_HTTPD_CONTENT_TEXT_XML]);
    AppS2w_HttpAddHdr(httpdCtx, TM_HTTP_HEADER_TRANSFER_ENCODING, (unsigned char *)tlHttpdChunked);
}

UINT8
AppS2w_HttpDataProcess(UINT8 cid,UINT8 *dataBuffer,UINT32 inBuflen, UINT32 elementType)
{
    UINT32 bufSpaceLeft;
    UINT8 status = S2W_SUCCESS;
    UINT32  statuscode;
    UINT8   *databuf;
    UINT32   count = 0;
    UINT32   i, hdrnamelen, hdrvallen, totalhdrcount;
    UINT8   statuscodestr[4];
    //s2wCidList[cid].httpdCtx.

    if (httpConfInfo.reqMethod == GSN_HTTP_METHOD_GETRESP || httpConfInfo.reqMethod == GSN_HTTP_METHOD_POSTRESP)
    {
        if(S2W_HTTP_RESPONSE_LINE == elementType)
        {
            /* Get status code from incoming buffer */
            strncpy(statuscodestr, dataBuffer, 3);
            AppS2wParse_Int(statuscodestr, &statuscode);
            if(0 != statuscode)
            {
                s2wCidList[cid].httpdCtx.statuscode = statuscode;
            }
            /* Copy response phrase from incoming buffer */
            databuf = dataBuffer;
            while((*databuf != ':') && (count < inBuflen))
            {
                databuf++;
                count++;
            }
            if(count < inBuflen)
            {
                s2wCidList[cid].httpdCtx.respphrase = gsn_malloc(inBuflen - count + 1);
                if(NULL != s2wCidList[cid].httpdCtx.respphrase)
                {
                    strncpy(s2wCidList[cid].httpdCtx.respphrase, (databuf + 1), (inBuflen - count - 1));
                    *(s2wCidList[cid].httpdCtx.respphrase + (inBuflen - count - 1)) = '\0';
                }
            }
        }
        if(S2W_HTTP_HEADER == elementType)
        {
            if(0 != s2wCidList[cid].httpdCtx.appheadercount)
            {
               /* calculate the length of the header name and header value */
               databuf = dataBuffer;
               while((*databuf != '=') && (count < inBuflen))
               {
                   databuf++;
                   count++;
               }
               if(count < inBuflen)
               {
                   hdrnamelen = count;
                   hdrvallen = inBuflen - count - 1;
                   totalhdrcount = s2wCidList[cid].httpdCtx.appheadercount + HTTP_STATIC_HDR_COUNT;
                   /* If it is the first header coming in, allocate buffer to accommodate all the header ptrs */
                   if((NULL == s2wCidList[cid].httpdCtx.httphdrvalptrptr) && (NULL == s2wCidList[cid].httpdCtx.httphdrnameptrptr) &&
                       (NULL == s2wCidList[cid].httpdCtx.httphdrtypeptr))
                   {
                       s2wCidList[cid].httpdCtx.httphdrvalptrptr = gsn_malloc(totalhdrcount * sizeof(s2wCidList[cid].httpdCtx.httphdrvalptrptr));
                       s2wCidList[cid].httpdCtx.httphdrnameptrptr = gsn_malloc(totalhdrcount * sizeof(s2wCidList[cid].httpdCtx.httphdrnameptrptr));
                       s2wCidList[cid].httpdCtx.httphdrtypeptr = gsn_malloc(totalhdrcount * sizeof(s2wCidList[cid].httpdCtx.httphdrtypeptr));
                       /* Add static headers here */
                       if((NULL != s2wCidList[cid].httpdCtx.httphdrvalptrptr) && (NULL != s2wCidList[cid].httpdCtx.httphdrnameptrptr) &&
                          (NULL != s2wCidList[cid].httpdCtx.httphdrtypeptr))
                       {
                           memset(s2wCidList[cid].httpdCtx.httphdrtypeptr, 0, (totalhdrcount * sizeof(s2wCidList[cid].httpdCtx.httphdrtypeptr)));
                           memset(s2wCidList[cid].httpdCtx.httphdrnameptrptr, 0, (totalhdrcount * sizeof(s2wCidList[cid].httpdCtx.httphdrnameptrptr)));
                           memset(s2wCidList[cid].httpdCtx.httphdrvalptrptr, 0, (totalhdrcount * sizeof(s2wCidList[cid].httpdCtx.httphdrvalptrptr)));
                           AppS2w_HttpAddStaticHdr(&s2wCidList[cid].httpdCtx, totalhdrcount);
                       }
                   }
                   /* start filling the headers */
                   if((NULL != s2wCidList[cid].httpdCtx.httphdrvalptrptr) && (NULL != s2wCidList[cid].httpdCtx.httphdrnameptrptr) &&
                      (NULL != s2wCidList[cid].httpdCtx.httphdrtypeptr))
                   {
                       /* search for an empty slot */
                       for(i = 0; i < totalhdrcount; i++)
                       {
                           if(NULL == s2wCidList[cid].httpdCtx.httphdrvalptrptr[i])
                           {
                               s2wCidList[cid].httpdCtx.httphdrvalptrptr[i] = gsn_malloc(hdrvallen + 1);
                               s2wCidList[cid].httpdCtx.httphdrnameptrptr[i] = gsn_malloc(hdrnamelen + 1);
                               s2wCidList[cid].httpdCtx.httphdrtypeptr[i] = TM_HTTP_HEADER_CUSTOM;
                               break;
                           }
                       }

                       if(i < totalhdrcount)
                       {
                           memcpy(s2wCidList[cid].httpdCtx.httphdrnameptrptr[i], dataBuffer, hdrnamelen);
                           *(s2wCidList[cid].httpdCtx.httphdrnameptrptr[i] + hdrnamelen) = '\0';
                           memcpy(s2wCidList[cid].httpdCtx.httphdrvalptrptr[i], databuf+1, hdrvallen);
                           *(s2wCidList[cid].httpdCtx.httphdrvalptrptr[i] + hdrvallen) = '\0';
                           s2wCidList[cid].httpdCtx.headercount++;
                       }
                   }

               }
            }
        }
    }
    return status;
}
#endif

#endif

#endif
#endif

#ifdef S2W_RF_TEST
//PRIVATE UINT8 AppS2sw_RfTestTx99(UINT8 *ptr,GSN_WIF_API_WLAN_RF_TEST_TX99_START_PARAM_T *param);

//PRIVATE UINT8 AppS2sw_RfTestTx100(UINT8 *ptr,GSN_WIF_API_WLAN_RF_TEST_TX100_START_PARAM_T *param);

PUBLIC UINT8 
AppS2wCmd_RfTestStop (UINT8 *ptr)
{
	UINT8 status;
	GSN_WDD_CTX_T *pWddRfTest;
	pWddRfTest = &appCtx.if0.wddCtx;
	status = GsnWdd_RfTestModeStop(pWddRfTest);
	return status;
}


PUBLIC UINT8
AppS2wCmd_RfTestStart (UINT8 *ptr)
{
	UINT8 status;
	GSN_WDD_CTX_T *pWddRfTest;
	pWddRfTest = &appCtx.if0.wddCtx;
	GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
	status = GsnWdd_RfTestModeStart(pWddRfTest);
	return status;
}

PUBLIC UINT8
AppS2wCmd_RfTestTxStart(UINT8 *ptr)
{
	GSN_WDD_RFTEST_TX_START_PARAM_T param;
	GSN_STATUS retVal;
	UINT8 status = S2W_SUCCESS;
	UINT8 index=0;
	UINT32 temp;
	UINT8 *p;
	UINT32 IntArray[TX_BUF_ELEMENTS] = {0};
	UINT8 MacAddr[S2W_MAC_ADDR_SIZE];
	UINT8 Bssid[S2W_MAC_ADDR_SIZE];
        //GSN_WIF_WLAN_TX_STATS_T txStats;
	GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	do
	{
		if(!((index == TX_MAC_INDEX) || (index == TX_BSSID_INDEX)))
		{
			status = AppS2wParse_Int(p, &temp);
			if (status != S2W_SUCCESS)
			{
			return status;
			}
			IntArray[index] = temp;
		}
		else if (index == TX_MAC_INDEX)
		{
			status = AppS2wParse_Mac(p, MacAddr);
			if (status != S2W_SUCCESS)
			{
			return status;
			}
		}
		else if (index == TX_BSSID_INDEX)
		{
			status = AppS2wParse_Mac(p, Bssid);
			if (status != S2W_SUCCESS)
			{
				return status;
			}
		}
		index++;
	}while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL);

	param.generalOptions.userPrefChannel = IntArray[0];
	param.generalOptions.bandWidth = IntArray[1];
	param.numFrames = IntArray[2];
	param.frameLen  = IntArray[3];
	param.txRate    = IntArray[4];
	param.txPower   = IntArray[5];
	memcpy((INT8 *)param.destAddr, (const INT8 *)MacAddr, 6);
	memcpy((INT8 *)param.bssid, (const INT8 *)Bssid, 6);
	param.htEnable = IntArray[8];
	param.guardInterval = IntArray[9];    
	param.greenField = IntArray[10];
	param.preambleType = IntArray[11];

	param.qosEnable = IntArray[12];
	param.ackPolicy = IntArray[13];
	param.scrambler = IntArray[14];
	param.aifsnVal  = IntArray[15];
	param.antenna   = IntArray[16];
	param.ccaBypass = IntArray[17];
#if 0
	S2w_Printf("\r\nuserPrefChannel:%d\r\n",param.generalOptions.userPrefChannel);
	S2w_Printf("\r\nbandWidth: %d\r\n",param.generalOptions.bandWidth);
	S2w_Printf("\r\nnumFrames: %d\r\n",param.numFrames);
	S2w_Printf("\r\nframeLen: %d\r\n",param.frameLen);
	S2w_Printf("\r\ntxRate: %d\r\n",param.txRate);
	S2w_Printf("\r\ntxPower: %d\r\n",param.txPower);
	S2w_Printf("\r\nhtEnable: %d\r\n",param.htEnable);
	S2w_Printf("\r\ngreenField: %d\r\n",param.greenField);
	S2w_Printf("\r\nguardInterval: %d\r\n",param.guardInterval);
	S2w_Printf("\r\npreambleType: %d\r\n",param.preambleType);
	S2w_Printf("\r\nqosEnable: %d\r\n",param.qosEnable);
	S2w_Printf("\r\nackPolicy: %d\r\n",param.ackPolicy);
	S2w_Printf("\r\nscrambler: %d\r\n",param.scrambler);
	S2w_Printf("\r\naifsnVal: %d\r\n",param.aifsnVal);
	S2w_Printf("\r\nantenna: %d\r\n",param.antenna);    
#endif        
	GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
	retVal = GsnWdd_RfTestTxStart(pWdd, &param);
	if(GSN_SUCCESS != retVal)
	{
		status = S2W_FAILURE;
	}

	return status;
}

PUBLIC UINT8
AppS2wCmd_RfTestTx99Start(UINT8 *ptr)
{
	UINT8 status;
	UINT8 index=0;
	UINT32 temp;
	UINT8 *p;
	UINT32 IntArray[TX99_BUF_ELEMENTS];
	UINT8 MacAddrBssid[S2W_MAC_ADDR_SIZE];
    
    UINT8 MacAddrDest[S2W_MAC_ADDR_SIZE];    
	GSN_WIF_API_WLAN_RF_TEST_TX99_START_PARAM_T param;

    
    GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(!p)
	{
		return S2W_EINVAL;
	}
    do
    {
        if((index != TX99_MAC_BSSID_INDEX) && (index != TX99_MAC_DESTADDR_INDEX) )
        {
            status = AppS2wParse_Int(p, &temp);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
            IntArray[index] = temp;
        }
        else if (index == TX99_MAC_BSSID_INDEX)
        {
            status = AppS2wParse_Mac(p, MacAddrBssid);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
        }
        else if (index == TX99_MAC_DESTADDR_INDEX)
        {
            status = AppS2wParse_Mac(p, MacAddrDest);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
        }
        index++;
    }while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL);

    param.generalOptions.userPrefChannel = IntArray[0];
    param.generalOptions.bandWidth = IntArray[1];
    param.numFrames = IntArray[2];
    param.frameLen = IntArray[3];
    param.txRate = IntArray[4];
    param.txPower= IntArray[5];
    memcpy((INT8 *)param.destAddr, (const INT8*)MacAddrDest, 6);
    memcpy((INT8 *)param.bssid, (const INT8*)MacAddrBssid, 6);    
    param.guardInterval = IntArray[8];    
    param.greenField = IntArray[9];
    param.antenna= IntArray[10];    
    param.cca = IntArray[11];
    param.agc = IntArray[12];
    param.contPreambleMode = IntArray[13];
    param.spreader = IntArray[14];
    param.scrambler = IntArray[15];
    param.preamble = IntArray[16];
    param.preambleType = IntArray[17];
    param.testPatternType = IntArray[18];
    param.phyTestTxRate = IntArray[19];
    param.modeSelect = IntArray[20];
#if 0
    S2w_Printf("\r\nuserPrefChannel: %d\r\n",param.generalOptions.userPrefChannel);
    S2w_Printf("\r\nbandWidth: %d\r\n",param.generalOptions.bandWidth);
    S2w_Printf("\r\nnumFrames: %d\r\n",param.numFrames);
    S2w_Printf("\r\nframeLen: %d\r\n",param.frameLen);
    S2w_Printf("\r\ntxRate: %d\r\n",param.txRate);
    S2w_Printf("\r\ntxPower: %d\r\n",param.txPower);
    S2w_Printf("\r\nguardInterval: %d\r\n",param.guardInterval);
    S2w_Printf("\r\ngreenField: %d\r\n",param.greenField);
    S2w_Printf("\r\nantenna: %d\r\n",param.antenna);
    S2w_Printf("\r\ncca: %d\r\n",param.cca);
    S2w_Printf("\r\nagc: %d\r\n",param.agc);
    S2w_Printf("\r\ncontPreambleMode: %d\r\n",param.contPreambleMode);
    S2w_Printf("\r\nspreader: %d\r\n",param.spreader);
    S2w_Printf("\r\nscrambler: %d\r\n",param.scrambler);
    S2w_Printf("\r\npreamble: %d\r\n",param.preamble);
    S2w_Printf("\r\npreambleType: %d\r\n",param.preambleType);
    S2w_Printf("\r\ntestPatternType: %d\r\n",param.testPatternType);
    S2w_Printf("\r\nphyTestTxRate: %d\r\n",param.phyTestTxRate);
    S2w_Printf("\r\nmodeSelect: %d\r\n",param.modeSelect);
#endif
    GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
      status = GsnWdd_RfTestTx99Start(pWdd, &param);

    return status;

}

PUBLIC UINT8
AppS2wCmd_RfTestTx100Start(UINT8 *ptr)
{
    UINT8 status;
    UINT8 index=0;
    UINT32 temp;
    UINT8 *p;
    UINT32 IntArray[TX100_BUF_ELEMENTS];

	GSN_WIF_API_WLAN_RF_TEST_TX100_START_PARAM_T param;

    GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;

    while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
     {
         status = AppS2wParse_Int(p, &temp);
         if (status != S2W_SUCCESS)
         {
             return status;
         }
         IntArray[index] = temp;
         index++;
     }

    param.generalOptions.userPrefChannel = IntArray[0];
    param.generalOptions.bandWidth = IntArray[1];
    param.txPower  = IntArray[2];
    param.antenna  = IntArray[3];    
    param.cca = IntArray[4];
    param.agc = IntArray[5];
    param.contPreambleMode = IntArray[6];
    param.spreader = IntArray[7];
    param.scrambler = IntArray[8];
    param.preamble = IntArray[9];
    param.preambleType = IntArray[10];
    param.testPatternType = IntArray[11];
    param.phyTestTxRate = IntArray[12];
    param.modeSelect = IntArray[13];
#if 0
    S2w_Printf("\r\nuserPrefChannel: %d\r\n",param.generalOptions.userPrefChannel);
    S2w_Printf("\r\nbandWidth: %d\r\n",param.generalOptions.bandWidth);
    S2w_Printf("\r\ntxPower: %d\r\n",param.txPower);
    S2w_Printf("\r\nantenna: %d\r\n",param.antenna);
    S2w_Printf("\r\ncca: %d\r\n",param.cca);
    S2w_Printf("\r\nagc: %d\r\n",param.agc);
    S2w_Printf("\r\ncontPreambleMode: %d\r\n",param.contPreambleMode);
    S2w_Printf("\r\nspreader: %d\r\n",param.spreader);
    S2w_Printf("\r\nscrambler: %d\r\n",param.scrambler);
    S2w_Printf("\r\npreamble: %d\r\n",param.preamble);
    S2w_Printf("\r\npreambleType: %d\r\n",param.preambleType);
    S2w_Printf("\r\ntestPatternType: %d\r\n",param.testPatternType);
    S2w_Printf("\r\nphyTestTxRate: %d\r\n",param.phyTestTxRate);
    S2w_Printf("\r\nmodeSelect: %d\r\n",param.modeSelect);
#endif
    GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
        GsnWdd_RfTestTx100Start(pWdd, &param);

    return status;

}

PUBLIC UINT8
AppS2wCmd_RfTestCarrierWaveStart(UINT8 *ptr)
{
	UINT8 status;
	UINT8 index=0;
	UINT32 temp;
	UINT8 *p;
	UINT32 IntArray[CR_WAVE_BUF_ELEMENTS];
	GSN_WIF_API_WLAN_RF_TEST_CARRIER_WAVE_START_PARAM_T param;

	GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;

	while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
	{
		status = AppS2wParse_Int(p, &temp);
		if (status != S2W_SUCCESS)
		{
			return status;
		}
		IntArray[index] = temp;
		index++;
	}
	param.generalOptions.userPrefChannel = IntArray[0];
	param.generalOptions.bandWidth = IntArray[1];
    param.txPower= IntArray[2];
    param.antenna= IntArray[3];
	param.customWavePeriod = IntArray[4];
#if 0
	S2w_Printf("\r\nuserPrefChannel: %d\r\n",param.generalOptions.userPrefChannel);
	S2w_Printf("\r\nbandWidth: %d\r\n",param.generalOptions.bandWidth);
    S2w_Printf("\r\ntxPower: %d\r\n",param.txPower);
    S2w_Printf("\r\nantenna: %d\r\n",param.antenna);
	S2w_Printf("\r\ncustomWavePeriod: %d\r\n",param.customWavePeriod);
#endif
	GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
	GsnWdd_RfTestCarrierWaveStart(pWdd, &param);
	return status;
}

PUBLIC UINT8 AppS2wCmd_RfTestTxStop (UINT8 *ptr)
{
	/* [TO DO] */
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wCmd_RfTestRxStart(UINT8 *ptr)
{
	UINT8 status;
	UINT8 index=0;
	UINT32 temp;
	UINT8 *p;
	UINT32 IntArray[RX_BUF_ELEMENTS];
	UINT8 MacAddr[S2W_MAC_ADDR_SIZE];
	GSN_WIF_API_WLAN_RF_TEST_RX_START_PARAM_T param;

	GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	do
	{
		if(!(index == RX_MAC_INDEX))
		{
			status = AppS2wParse_Int(p, &temp);
			if (status != S2W_SUCCESS)
			{
				return status;
			}
			IntArray[index] = temp;
		}
		else if (index == RX_MAC_INDEX)
		{
			status = AppS2wParse_Mac(p, MacAddr);
			if (status != S2W_SUCCESS)
			{
			return status;
			}
		}
		index++;
	}while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL);
	
	param.generalOptions.userPrefChannel = IntArray[0];
	param.generalOptions.bandWidth = IntArray[1];
	param.rxFrameTypeFilter = IntArray[2];
	memcpy((INT8 *)param.rxAddrFilter, (const INT8 *)MacAddr, 6);
    param.antenna   = IntArray[4];
#if 0
	S2w_Printf("\r\nuserPrefChannel: %d\r\n",param.generalOptions.userPrefChannel);
	S2w_Printf("\r\nbandWidth: %d\r\n",param.generalOptions.bandWidth);
	S2w_Printf("\r\nrxFrameTypeFilter: %d\r\n",param.rxFrameTypeFilter);
    S2w_Printf("\r\nrxFrameTypeFilter: %d\r\n",param.antenna);
#endif
	GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
	GsnWdd_RfTestRxStart(pWdd, &param);
	return status;
}



PUBLIC UINT8 AppS2wCmd_RfTestRxStop (UINT8 *ptr)
{
	UINT8 status;
	GSN_WDD_CTX_T *pWddRfTest;
 	GSN_WLAN_RF_TEST_RX_STATS_T rxStats;
        
	pWddRfTest = &appCtx.if0.wddCtx;
	GsnSysCtl_AppTempSend(&appCtx.sysCtlCtx);
	status = GsnWdd_RfTestRxStop(pWddRfTest, &rxStats);
	
	S2w_Printf("\r\nNo of packets received = %d\r\n", rxStats.rxPackets);
	S2w_Printf("No of bytes received = %d\r\n", rxStats.rxBytes);
				S2w_Printf("No of packets received with CRC Errors = %d\r\n", rxStats.crcErrors);
	S2w_Printf("No of packets received with Security Errors = %d\r\n", rxStats.secErrors);
	S2w_Printf("No of duplicate packets received = %d\r\n", rxStats.dupPackets);
	S2w_Printf("No of header errors received = %d\r\n", rxStats.headerErrors);
	S2w_Printf("Average RSSI of the received packets = %d\r\n", rxStats.avgRssi);

	S2w_Printf(" No of packets received at 1M and Long Preamble = %d\r\n", rxStats.rxRate1_long);
	S2w_Printf(" No of packets received at 2M and Long Preamble = %d\r\n", rxStats.rxRate2_long);
	S2w_Printf("No of packets received at 5M and Long Preamble = %d\r\n", rxStats.rxRate5_long);
	S2w_Printf("No of packets received at 11M and Long Preamble = %d\r\n",rxStats.rxRate11_long );
	S2w_Printf("No of packets received at 2M and Short Preamble = %d\r\n", rxStats.rxRate2_short);
	S2w_Printf("No of packets received at 5M and Short Preamble = %d\r\n", rxStats.rxRate5_short);
	S2w_Printf("No of packets received at 11M and Short Preamble = %d\r\n",rxStats.rxRate11_short );

	S2w_Printf("No of packets received at 6M = %d\r\n", rxStats.rxRate6);
	S2w_Printf("No of packets received at 9M = %d\r\n", rxStats.rxRate9);
	S2w_Printf("No of packets received at 12M = %d\r\n", rxStats.rxRate12);
	S2w_Printf("No of packets received at 18M = %d\r\n", rxStats.rxRate18);
	S2w_Printf("No of packets received at 24M = %d\r\n", rxStats.rxRate24);
	S2w_Printf("No of packets received at 36M = %d\r\n", rxStats.rxRate36);
	S2w_Printf("No of packets received at 48M = %d\r\n", rxStats.rxRate48);
	S2w_Printf("No of packets received at 54M = %d\r\n", rxStats.rxRate54);
	
	S2w_Printf("No of packets received at"
			    "respective MCS Index with Short GI=\r\n");
	{
		UINT8 i;
		for(i = 0; i<8; i++)S2w_Printf("%x ", rxStats.rxMcsSgi[i]);
		S2w_Printf("\r\n");
									
	}
	S2w_Printf("No of packets received at"
				"respective MCS Index with Long GI = \r\n");
	{
		UINT8 i;
		for(i = 0; i<8; i++)S2w_Printf("%x ", rxStats.rxMcsLgi[i]);
		S2w_Printf("\r\n");
	}
	
	return status;
}
VOID S2w_Wlan_Cal_Cb(VOID *ctx, GSN_WDD_CAL_RUN_RSP_T *resp)
{
	UINT32 i = 0;
	S2w_Printf("Calibration Info:\r\n");
	if(GSN_WIF_CAL_SUCCESS == resp->status)
	{
		S2w_Printf("status = %s\r\n", "SUCCESS");		
	}
	else
	{
		S2w_Printf("status = %s\r\n", "FAIL");
	}

	S2w_Printf("Length = %d\r\n", resp->len);
	S2w_Printf("Data:\r\n\r\n");
	for(i = 0; i < resp->len ; i++)
	{
		S2w_Printf("%x ", resp->data[i]);
	}
	S2w_Printf("\r\n");
    GsnOsal_SemRelease ( &s2wWlanOpSyncSem);
}
PUBLIC UINT8 AppS2wCmd_WlanCalib (UINT8 *ptr)
{
	UINT8 status;;
	GSN_WDD_CAL_RUN_REQ_T calRunReq;
	UINT32 temp = 0;	
	GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;
	UINT8 *p;

	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &temp);
	if (status != S2W_SUCCESS)
	{
		return status;
	}
	calRunReq.calType = temp;

	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);	
	if(!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &temp);
	if (status != S2W_SUCCESS)
	{
		return status;
	}	
	calRunReq.calSubtype = temp;

	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &temp);
	if (status != S2W_SUCCESS)
	{
		return status;
	}
	calRunReq.channel = temp;
	calRunReq.modType = 0xFF;// unknown
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if (p && *p)
	{
		status = AppS2wParse_Int(p, &temp);
	    if (status != S2W_SUCCESS)
	    {
	    	return status;
	    }
	    calRunReq.modType = (UINT8)temp;
	}
	S2w_Printf("\r\n ModType:%d\r\n",calRunReq.modType);
	status = GsnWdd_CalibrnRun(pWdd, &calRunReq, S2w_Wlan_Cal_Cb, NULL);
	GsnOsal_SemAcquire ( &s2wWlanOpSyncSem, GSN_OSAL_WAIT_FOREVER );
	/* [TO DO] : Print the stat values*/
	return status;
}

#endif



#ifdef S2W_WEB_SERVER

/******************************************************************
* @ingroup S2w-Application
* @brief Process AT+WEBSERVER command
*	 This Command starts webserver
* @param ptr Pointer to the user input string.
*
* @return S2W_SUCCESS - operation successful.
* @return S2W_FAILURE - operation Failed.
* @return S2W_EINVAL - operation Failed-invalid input
*************************************************************/

UINT8
AppS2wCmd_WebServer(UINT8* ptr)
{
	UINT8 status = S2W_FAILURE;
	UINT32 webSrvrEnable;
	UINT8 *p;
	UINT8 dfltUnamePwd[8];
	UINT32 message;
	UINT8 i;
	UINT32 val = 0;

	memset(&s2wappMainTaskCtxt->WebServerCfg,0,sizeof(S2W_WBSERVER_CONFIG_T));
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
	{
	   return S2W_EINVAL;
	}

	AppS2wParse_Int(p, &webSrvrEnable);

	if( (webSrvrEnable==0) && (TRUE == GsnHttpd_IsRunning()) && s2wappMainTaskCtxt->webServerStatus == RUNNING)
	{
		message = APP_NOTIFICATION_SRVR_ONLY_STOP;
		(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
		GsnOsal_SemAcquire(&s2wappMainTaskCtxt->webServerSync,GSN_OSAL_WAIT_FOREVER);
		memset(&s2wappMainTaskCtxt->WebServerCfg,0,sizeof(S2W_WBSERVER_CONFIG_T));
		s2wappMainTaskCtxt->respTimeOut=0;
		s2wappMainTaskCtxt->responseInprogress=0;
		GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl);		
		return S2W_SUCCESS;
	}
	else if( (webSrvrEnable==0) && (FALSE == GsnHttpd_IsRunning()) )
	{
		return S2W_FAILURE;
	}
	else if( (webSrvrEnable==1) && (TRUE == GsnHttpd_IsRunning()) && s2wappMainTaskCtxt->webServerStatus == RUNNING)
	{
		return S2W_FAILURE;
	}
	memset(&s2wappMainTaskCtxt->WebServerCfg,0,sizeof(S2W_WBSERVER_CONFIG_T));
	/* get user name and password*/
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p || (strlen((const char *)p) > S2W_HTTPD_MAX_USERNAME_LEN))
    {
       	return S2W_EINVAL;
    }
    strcpy((INT8 *)s2wappMainTaskCtxt->WebServerCfg.username,(const INT8 *) p);
	if(7 == strlen((INT8 *)p))
	{
		for(i = 0; i< 7; i++)
		{
			dfltUnamePwd[i] = toupper(p[i]);
		}
		dfltUnamePwd[i] = 0;
		if(0 == strcmp((const char *)dfltUnamePwd, "DEFAULT"))
		{
			strcpy(s2wappMainTaskCtxt->WebServerCfg.username, (const char *)s2wCurrent.httpSrvrConf.username);
		}
	}
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p || (strlen((const char *)p) > S2W_HTTPD_MAX_PASSWORD_LEN) )
    {
        return S2W_EINVAL;
    }
    strcpy(s2wappMainTaskCtxt->WebServerCfg.passwd, (const INT8 *)p);
	if(7 == strlen((INT8 *)p))
	{
		for(i = 0; i< 7; i++)
		{
			dfltUnamePwd[i] = toupper(p[i]);
		}
		dfltUnamePwd[i] = 0;
		if(0 == strcmp((const char *)dfltUnamePwd, "DEFAULT"))
		{
			strcpy(s2wappMainTaskCtxt->WebServerCfg.passwd, (const char *)s2wCurrent.httpSrvrConf.password);
		}
	}
    /* Assume SSL is not used */
    s2wappMainTaskCtxt->WebServerCfg.sslEnabled = S2W_DFLT_HTTP_SRVR_SSL_ENABLE;

	/* see if more parameters are present */
    p = AppS2wParse_NextParamGet(&ptr);
	if (p && 0 != strlen ((INT8 *)p))
	{
	   status = AppS2wParse_Boolean(p, &s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
	   if (status != S2W_SUCCESS)
	   {
		   return status;
	   }
	}
	s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut = S2W_DFLT_HTTP_SRVR_IDLE_TIMEOUT;
	p = AppS2wParse_NextParamGet(&ptr);
	if (p && 0 != strlen ((INT8 *)p))
	{
		status = AppS2wParse_Int(p, &val);
		if (status != S2W_SUCCESS)
	    {
	        return status;
	    }
		s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut = val;
	}
	p = AppS2wParse_NextParamGet(&ptr);
#if (defined(S2W_GSLINK_XML) || defined(S2W_GSLINK_RAW))
		s2wappMainTaskCtxt->respTimeOut = 0;
		s2wappMainTaskCtxt->responseInprogress=0;
		if (p && 0 != strlen ((INT8 *)p))
		{
			status = AppS2wParse_Int(p, &val);
			if (status != S2W_SUCCESS)
				return status;	
			s2wappMainTaskCtxt->respTimeOut = val*TIMER_INTERRUPT_1_MS;
		}
#endif
    	
	message = APP_NOTIFICATION_SRVR_START;
	(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
	GsnOsal_SemAcquire(&s2wappMainTaskCtxt->webServerSync,GSN_OSAL_WAIT_FOREVER);
	return s2wappMainTaskCtxt->WebServerCfg.status;
}

VOID
AppS2w_WebServerStop()
{
#ifdef S2W_GSLINK
	App_McuHttpApiDeInit();
#endif
	s2wappMainTaskCtxt->webServerStatus = IDLE;

}

PUBLIC VOID
AppS2w_WebServerStart()
{

	INT8 httpdStatus;
	//UINT8 status = S2W_FAILURE;
	UINT32 index,certLength;

	GSN_HTTPD_CONFIG_T config;
    GSN_NWIF_IP_CONFIG_T nwParams;
	//char ipAddrStr[16];
	SERVER_CERT_DETAIL_T certDetail, *pCertDtl = NULL;
	//UINT8 i;
    //GSN_STATUS ret;
	if(TRUE == GsnHttpd_IsRunning() )
	{
		goto WebServer_RegURI;
	}
    if(NULL != s2wHttpdPktPtr)
    {
        gsn_free(s2wHttpdPktPtr);
        s2wHttpdPktPtr = NULL;
    }
    (VOID)pCertDtl;
	memset((INT8 *)&certDetail, 0, sizeof(certDetail));
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
#if 1
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
            goto webServerExit;
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
            goto webServerExit;
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
            goto webServerExit;
        }
        certDetail.PrivateKeyName = (const char *)s2w_ssl_cert_table[index].name;
        certDetail.PrivateKeyLocation = s2w_ssl_cert_table[index].certAddress + 2;
        certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
        certLength <<= 8;
        certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
        certDetail.PrivateKeyLen = certLength;

#else
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
#endif
	//storeParams = serverData.storeParams;

    /* get the ip information by calling geps API */
#if 1
        GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx, &nwParams);
    //inet_ntop(AF_INET, &nwParams.ipv4.ipAddr, ipAddrStr, sizeof(ipAddrStr));
#else
    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->nwIf, &nwParams);
    inet_ntop(AF_INET, &nwParams.ipAddr, ipAddrStr, sizeof(ipAddrStr));
#endif
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
    config.maxConnTotal = S2W_DFLT_HTTP_SRVR_CLIENT_NO;//APP_HTTPD_MAX_TOTAL_CONN;
    config.blockingState = APP_HTTPD_BLOCKING_STATE;
    config.threadPriority = APP_HTTPD_THREAD_PRIORITY;
    config.idleTimeout = APP_HTTPD_IDLE_TIMEOUT;
	if(0 != s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut)
	{
		config.idleTimeout = s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut;
	}

#if 1
#ifdef USE_V6
    //memcpy(config.ipAddr, (const INT8 *)nwParams.ipv6.linkLocalAddr, 16);
	config.ip_flag = GSN_USE_IPV6;
        GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx, &nwParams);
        memcpy(config.ipAddr6,nwParams.ipv6.globalAddr, 16);
#else
    config.ip_flag = GSN_USE_IPV4;
    config.ipAddr = nwParams.ipv4.ipAddr;
#endif
#endif
    config.rootCgiDir = NULL;
    config.rootDir = "/";
    config.defaultFileName = "index.html";
	config.mallocTimeout = 2 *1000; /* 2 Sec. */
	config.sysQualTskID = APP_CFG_SQ_HTTPD_TASK_ID;
	config.sysQualTicks = APP_CFG_SQ_TICKS_FOR_HTTPD_TASK;

    config.stack = S2wApp_WebserverStack_Get(s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
	 pS2wHttpdTaskStack = config.stack;
	 if(NULL == config.stack)
	{
		s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
		goto webServerExit;

	}
    config.stackSize  = S2wApp_WebserverStackSize_Get(s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
    //config.pWdd = &s2wappMainTaskCtxt->wdd;
#if 1
    //config.pool_hdl = &(s2wappMainTaskCtxt->nwCtx.trPktPoolHndl);
#if 0
    /* Initialize web parameters */
    memset(&trPktPoolHndl, 0, sizeof(trPktPoolHndl));
    /* TODO: need to check proper place to free this buffer */
    s2wHttpdPktPtr = (void*)gsn_malloc(S2W_HTTPD_PKT_POOL);
    if(NULL == s2wHttpdPktPtr)
    {
		s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
		goto webServerExit;
    }
    /*Create a packet pool for tcp layer */
    ret = nx_packet_pool_create(&trPktPoolHndl, "", 1600,
             s2wHttpdPktPtr, S2W_HTTPD_PKT_POOL);
    if(ret)
    {
		s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
		goto webServerExit;
    }
#else
    config.pool_hdl = GsnNw_PktPoolHndlGet(&s2wappMainTaskCtxt->nwCtx, GSN_NW_LBUF_PKT_POOL);
#endif
#endif
    /* Start httpd */
    httpdStatus = GsnHttpd_Start(config
#if 1//def GSN_SSL_SERVER_SUPPORT
	    ,pCertDtl
#endif
	    );

	if(httpdStatus == GSN_HTTPD_FAILURE)
	{
	    S2wApp_WebserverStack_Free(config.stack);
		pS2wHttpdTaskStack = NULL;
		s2wappMainTaskCtxt->WebServerCfg.status = S2W_FAILURE;
		goto webServerExit;
	}
WebServer_RegURI:
#ifdef S2W_GSLINK
    App_McuHttpApiInit();
#endif
 #ifdef S2W_WEB_SERVER
	s2wappMainTaskCtxt->webServerStatus = RUNNING;
#endif
	s2wappMainTaskCtxt->WebServerCfg.status = S2W_SUCCESS;
webServerExit:
	GsnOsal_SemRelease(&s2wappMainTaskCtxt->webServerSync);
}

PUBLIC UINT8
AppS2wCmd_CfgUri(UINT8 *ptr)
{
	UINT8 *p,*ctype;
    GSN_HTTPD_STATUS_T status=GSN_HTTPD_FAILURE;
	UINT32 contentType;
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    UINT8 *cgi,*reqLine, *hdr;
    UINT32  sendCgi = 0;
    UINT32 sendReq = 0;
    UINT32 httpHddrBmap = 0;
#endif
	if(!GsnHttpd_IsRunning())
		return S2W_FAILURE;
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
	   return S2W_EINVAL;
	}
	ctype = AppS2wParse_NextParamGet(&ptr);
	if (ctype != NULL)
	{
		AppS2wParse_Int(ctype, &contentType);
		if(contentType > GSN_HTTPD_CONTENT_TYPES_MAX)
			return S2W_EINVAL;
	}
	else
		contentType = GSN_HTTPD_CONTENT_APP_XML;
	if(strlen((const char *)p) > GSN_HTTPD_MAX_URI_LENGTH)
		return S2W_EINVAL;
#ifdef  S2W_GSLINK
	if(GSN_HTTPD_MAX_URI_LENGTH == strlen((const char *)p))
	{
		p[GSN_HTTPD_MAX_URI_LENGTH - 1] = '\0';
	}
	status = GsnHttpd_UriHandlerConfig((char *)s2wappMainTaskCtxt->currenturi,
			   0, NULL,NULL, 0);
	if(status != GSN_HTTPD_SUCCESS)
		return S2W_FAILURE;
	memset(s2wappMainTaskCtxt->currenturi,0,GSN_HTTPD_MAX_URI_LENGTH);
	memcpy(s2wappMainTaskCtxt->currenturi,p,strlen((const char*)p));
	status  = GsnHttpd_UriHandlerConfig((char *)s2wappMainTaskCtxt->currenturi,
			   GSN_HTTPD_URI_METHOD_GET_POST, APP_MCU_PROFILE_DESC,
			   McuHttpCb, (UINT8)contentType);
#endif
	if(status != GSN_HTTPD_SUCCESS)
		return S2W_FAILURE;
	
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    cgi = AppS2wParse_NextParamGet(&ptr);
    if (!cgi)
    {
       return S2W_EINVAL;
    }
    AppS2wParse_Int(cgi, &sendCgi);
    if(1 == sendCgi)
    {
        s2wappMainTaskCtxt->WebServerCfg.sendCgi = 1;
    }
    else
    {
        s2wappMainTaskCtxt->WebServerCfg.sendCgi = 0;
    }
/* need to check about this global variable, not sure where to declare this*/
    reqLine = AppS2wParse_NextParamGet(&ptr);
    if (!reqLine)
    {
       return S2W_EINVAL;
    }
    AppS2wParse_Int(reqLine, &sendReq);
    if(1 == sendReq)
    {
        s2wappMainTaskCtxt->WebServerCfg.sendReq = 1;
    }
    else
    {
        s2wappMainTaskCtxt->WebServerCfg.sendReq = 0;
    }
    hdr = AppS2wParse_NextParamGet(&ptr);
    if (!hdr)
    {
       return S2W_EINVAL;
    }
    AppS2wParse_HexString(hdr, &httpHddrBmap, HTTP_HDR_BITMAP_STR_SIZE);
    if(0 != httpHddrBmap)
    {
        s2wappMainTaskCtxt->WebServerCfg.httpdHdrBmap = httpHddrBmap;
    }
    else
    {
        s2wappMainTaskCtxt->WebServerCfg.httpdHdrBmap = 0;
    }
#endif
    return S2W_SUCCESS;
}
#endif
#if S2W_WEB_PROV

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WEBPROV command
 *      This function vaidate the input parameters and start the
 *      Web server.
 * @param ptr Pointer to the user input string.
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 * @retval S2W_FAILURE - operation failure
 ******************************************************************/
UINT8
APPS2wCmd_WebProv(UINT8 *ptr)
{
#ifdef S2W_IP2WIFI_SUPPORT
    S2W_NETCONF_T NetworkParams;
#endif
	UINT32 message,val = 0;
    UINT8 status;
    UINT8 *p;
	UINT8 dfltUnamePwd[8];
	UINT8 i ;
	if(s2wappMainTaskCtxt->webProvStatus == RUNNING)
	{
		return S2W_FAILURE;
	}

	memset(&s2wappMainTaskCtxt->WebServerCfg,0,sizeof(S2W_WBSERVER_CONFIG_T));
    /* get user name and password*/
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p || (strlen((const char *)p) > S2W_HTTPD_MAX_USERNAME_LEN))
    {
        return S2W_EINVAL;
    }
    strcpy(s2wappMainTaskCtxt->WebServerCfg.username,(const INT8 *) p);
	if(7 == strlen((INT8 *)p))
	{

		for(i = 0; i< 7; i++)
		{
			dfltUnamePwd[i] = toupper(p[i]);
		}
		dfltUnamePwd[i] = 0;
		if(0 == strcmp((const char *)dfltUnamePwd, "DEFAULT"))
		{
			strcpy(s2wappMainTaskCtxt->WebServerCfg.username, (const char *)s2wCurrent.httpSrvrConf.username);
		}
	}
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p || (strlen((const char *)p) > S2W_HTTPD_MAX_PASSWORD_LEN))
    {
        return S2W_EINVAL;
    }
    strcpy(s2wappMainTaskCtxt->WebServerCfg.passwd, (const INT8 *)p);
	if(7 == strlen((INT8 *)p))
	{
		for(i = 0; i< 7; i++)
		{
			dfltUnamePwd[i] = toupper(p[i]);
		}
		dfltUnamePwd[i] = 0;
		if(0 == strcmp((const char *)dfltUnamePwd, "DEFAULT"))
		{
			strcpy(s2wappMainTaskCtxt->WebServerCfg.passwd, (const char *)s2wCurrent.httpSrvrConf.password);
		}
	}
    /* Assume SSL is not used */
    s2wappMainTaskCtxt->WebServerCfg.sslEnabled = S2W_DFLT_HTTP_SRVR_SSL_ENABLE;
#ifndef S2W_IP2WIFI_SUPPORT
    /* see if more parameters are present */
    p = AppS2wParse_NextParamGet(&ptr);
    if (p && (0 != strlen((const char *)p)))
    {
        status = AppS2wParse_Boolean(p, &s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }    
    
#else /* This block is for IP2wifi*/
    /* here onwards its setting up L3 connection*/
    memcpy(&NetworkParams, &s2wCurrent.netConf, sizeof(NetworkParams));

    /* get IP */
    p = AppS2wParse_NextParamGet(&ptr);

    status = AppS2wParse_Ip(p, (UINT8 *)NetworkParams.ipAddr);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* get subnet mask and gateway */
    p = AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Ip(p, (UINT8 *)NetworkParams.netMask);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    p = AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Ip(p, (UINT8 *)NetworkParams.gateway);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Boolean(p, &s2wappMainTaskCtxt->WebServerCfg.sslEnabled);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    /* see if more parameters are present */
    p = AppS2wParse_NextParamGet(&ptr);
    if (p)
    {
        return S2W_EINVAL;
    }

    NetworkParams.dhcp = 0;
    /* call hal ip config function to configure the static IP
     */
    status = AppS2wHal_NetworkConfig(&NetworkParams);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* update the active profile paramater
     */
    memcpy(&s2wCurrent.netConf, &NetworkParams, sizeof(s2wCurrent.netConf));
#endif

	s2wappMainTaskCtxt->WebServerCfg.storeParams = 0;
	p = AppS2wParse_NextParamGet(&ptr);
	if (p && 0 != strlen((INT8*)p))
	{
		UINT32 val = 0;
		status = AppS2wParse_Int(p, &val);
		if (status != S2W_SUCCESS)
	    {
	        return status;
	    }
		s2wappMainTaskCtxt->WebServerCfg.storeParams = val;
	}
	s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut = S2W_DFLT_HTTP_SRVR_IDLE_TIMEOUT;
	p = AppS2wParse_NextParamGet(&ptr);
	if (p && 0 != strlen((INT8*)p))
	{
		status = AppS2wParse_Int(p, &val);
		if (status != S2W_SUCCESS)
	    {
	        return status;
	    }
		s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut = val;
		
	}
#ifdef  S2W_NCM_SUPPORT_ENABLE	
	s2wappMainTaskCtxt->ncmAutoConEn = 0;
#endif
	p = AppS2wParse_NextParamGet(&ptr);
	if (p && 0 != strlen((INT8*)p))
	{
		val=0;
		status = AppS2wParse_Int(p, &val);
		if (status != S2W_SUCCESS)
	    {
	        return status;
	    }
		if(( s2wappMainTaskCtxt->WebServerCfg.storeParams  == S2W_WEB_PARAMS_SND_TO_HOST)	&& val == 1 )		
		{
			 return S2W_FAILURE;			 
		}
#ifdef  S2W_NCM_SUPPORT_ENABLE
		else
		{
			s2wappMainTaskCtxt->ncmAutoConEn = val;
		}
#endif
		
	}
	s2wappMainTaskCtxt->formatVersion = 0;
	p = AppS2wParse_NextParamGet(&ptr);
	if (p && 0 != strlen((INT8*)p))
	{
		val=0;
		status = AppS2wParse_Int(p, &val);
		if (status != S2W_SUCCESS)
	    {
	        return status;
	    }
		s2wappMainTaskCtxt->formatVersion = val;
	}
	
	message = APP_NOTIFICATION_PROV_START;
    s2wappMainTaskCtxt->webProvStatus=START;
	(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
	GsnOsal_SemAcquire(&s2wappMainTaskCtxt->webServerSync,GSN_OSAL_WAIT_FOREVER);
    return s2wappMainTaskCtxt->WebServerCfg.status;
}
UINT8
APPS2wCmd_WebProvStop(UINT8 *ptr)
{
	UINT32 message;
	if( (TRUE == GsnHttpd_IsRunning()) && s2wappMainTaskCtxt->webProvStatus == RUNNING)
	{
		message = APP_NOTIFICATION_PROV_ONLY_STOP;
		(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
		GsnOsal_SemAcquire(&s2wappMainTaskCtxt->webServerSync,GSN_OSAL_WAIT_FOREVER);
		return S2W_SUCCESS;
	}
	return S2W_FAILURE;
}
UINT8
APPS2wCmd_AddRedirURI(UINT8 *ptr)
{
	UINT8 status;
	if(TRUE == GsnHttpd_IsRunning())
	{
		memset(s2wappMainTaskCtxt->rediruri,0,GSN_HTTPD_MAX_URI_LENGTH);
		memcpy(s2wappMainTaskCtxt->rediruri,ptr,strlen((const char *)ptr));
		status = GsnHttpd_AddRedirURI(s2wappMainTaskCtxt->rediruri);
		if(status != GSN_SUCCESS)
			return S2W_FAILURE;
		else
			return S2W_SUCCESS;
	}
	else
		return S2W_FAILURE;
}
#endif

#ifdef S2W_MDNS_ENABLE
extern UINT8 mdnsFlag;
UINT32 mdnsStarted;

UINT8 mdnsATConfig=0;
extern S2W_MDNS_HN_PARAM_T mdnsHnParam;
__no_init UINT8 mdnsParamBuff[256];
S2W_MDNS_SRV_PARAM_T mdnsSrvcParam;
S2W_MDNS_ANNOUNCE_PARAM_T mdnsAnnceParam;

#ifdef S2W_IPv6_SUPPORT

PUBLIC UINT8
AppS2wCmd_MdnsInitv6(UINT8 *ptr)
{
    UINT8 ptr1='6';
    ptr=&ptr1;
    mdnsv6Enable = TRUE;
    AppS2wHal_MdnsInit(ptr);

    return S2W_SUCCESS;
}
#endif
PUBLIC UINT8
AppS2wCmd_MdnsInit(UINT8 *ptr)
{
    if((!mdnsv6Enable) && !(mdnsStarted == TRUE))
    {
      AppS2wHal_MdnsInit(ptr);
    }
    else
    {
      return S2W_FAILURE;
    }
    mdnsStarted = TRUE;
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wCmd_MdnsDeInit(VOID)
{
    if(mdnsFlag && mdnsStarted)
    {
     AppS2wHal_MdnsDeInit();
     mdnsv6Enable = FALSE;
     mdnsStarted = FALSE;
     return S2W_SUCCESS; 
    }
    else
    {
     return S2W_FAILURE;
    }
}

PUBLIC UINT8
AppS2wCmd_MdnsHostNameReg(UINT8 *ptr)
{
    UINT8 *p;
    UINT16 len;
    UINT16 totalLen = 0;
    //UINT8 status;
    UINT32 param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    len = strlen((const char *)p);

    mdnsHnParam.hostname = mdnsParamBuff;

    if(0 != len)
    {
        strcpy((INT8 *)mdnsHnParam.hostname, (const char *)p);
    }
    else
    {/*Read the default system name*/
       len = strlen((const INT8 *)s2wCurrent.hostName);

       strcpy((INT8 *)mdnsHnParam.hostname, (const char *)s2wCurrent.hostName);
    }
    totalLen += (len+1);
  
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    len = strlen((const char *)p);
  
    mdnsHnParam.domain = &mdnsParamBuff[totalLen];
  
    strcpy((INT8 *)mdnsHnParam.domain, (const char *)p);

    totalLen += (len+1);
     
    if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {
    AppS2wParse_Int(p, &param);
    mdnsHnParam.ttl = param;
    }
    else
    	mdnsHnParam.ttl =  S2W_DFLT_MDNS_TTL; 
    
    if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {
    AppS2wParse_Int(p, &param);
       
    mdnsHnParam.scope = (UINT8)param;
    }
    else
    mdnsHnParam.scope = S2W_DFLT_MDNS_SCOPE;
    
    
   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {

    AppS2wParse_Int(p, &param);
    mdnsHnParam.conflctDetect = (UINT8)param;
    }
   else
    mdnsHnParam.conflctDetect = S2W_DFLT_MDNS_CONFLICT_DETECT;

    if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {    
    AppS2wParse_Int(p, &param);
    mdnsHnParam.autoCorrect = (UINT8)param;
    }
    else
    mdnsHnParam.autoCorrect = S2W_DFLT_MDNS_AUTOCORRECT;
    
    if(mdnsv6Enable)
    mdnsHnParam.IpVersion |= ADDR_TYPE_IPv6;
    else
    mdnsHnParam.IpVersion = ADDR_TYPE_IPv4;
    
     mdnsATConfig =1;
    return (AppS2wHal_MdnsHostNameReg(&mdnsHnParam));
}

#ifdef ADK_OTAFU
#define S2W_OTAFU_MDNS_KEY_VAL "api="GSN_HTTP_OTAFU_API_NAME":"GSN_HTTP_OTAFU_API_VERSION":"GSN_HTTP_OTAFU_API_PATH
#endif
#ifdef ADK_PROV
#define S2W_SYS_MDNS_KEY_VAL "api="GSN_HTTP_SYS_API_NAME":"GSN_HTTP_SYS_API_VERSION":"GSN_HTTP_SYS_API_PATH
#endif

PUBLIC UINT8
AppS2wCmd_MdnsServiceReg(UINT8 *ptr)
{
    
    UINT8 *p;
    UINT16 len;
    UINT16 totalLen = 0;
    //UINT8 status;
    UINT32 param = 0;
    UINT8  KeyValPrsnt = 0;
    UINT8  KeyValIndx=0;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.srvcInstance = mdnsParamBuff;
    strcpy((INT8 *)mdnsSrvcParam.srvcInstance, (const INT8 *)p);
    totalLen += (len+1);
   
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.subType = &mdnsParamBuff[totalLen];;
    strcpy((INT8 *)mdnsSrvcParam.subType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.srvcType= &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvcParam.srvcType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.proto = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvcParam.proto, (const INT8 *)p);
    totalLen += (len+1);
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.domain = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvcParam.domain, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
     if (!p)
     {
         return S2W_EINVAL;
     }
     AppS2wParse_Int(p, &param);
     mdnsSrvcParam.port = param;
     
	 mdnsSrvcParam.keyVal[KeyValIndx] = NULL;
	 p = AppS2wParse_NextParamGet(&ptr);
     if (p)
     {
         
		param = 0;
		AppS2wParse_Int(p, &param);
		if(1 == param)
		{
#ifdef ADK_PROV
		mdnsSrvcParam.keyVal[KeyValIndx] = S2W_SYS_MDNS_KEY_VAL;
		KeyValIndx++;
#else
		return S2W_EINVAL; 		 
#endif
		}
		else if(2 == param)
		{ 
#ifdef ADK_OTAFU
		//mdnsSrvcParam.keyVal[KeyValIndx] = S2W_OTAFU_MDNS_KEY_VAL;
		KeyValIndx++;
#else
		return S2W_EINVAL; 		 
#endif
		}   
     }

	/* key=valuepairpresent*/
	KeyValPrsnt= 1;
	while(KeyValPrsnt)
	{
		p = AppS2wParse_NextParamGet(&ptr);
		if(p)
		{
			if(TRUE == AppS2wParse_MdnsKeyValidate(p,strlen((char*)p)))
			{
			   mdnsSrvcParam.keyVal[KeyValIndx] = (UINT8 *)p;
			   KeyValIndx++;
			}
			else
			{
				 KeyValPrsnt = 0;
				 mdnsSrvcParam.keyVal[KeyValIndx] = NULL;
			}
		}
		else
		{
			KeyValPrsnt = 0;
			mdnsSrvcParam.keyVal[KeyValIndx] = NULL;
		}
	}
   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {
    AppS2wParse_Int(p, &param);
    mdnsSrvcParam.ttl = param;
    }
    else
    	mdnsSrvcParam.ttl =  S2W_DFLT_MDNS_TTL; 
    
    if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {
    	AppS2wParse_Int(p, &param);       
    	mdnsSrvcParam.scope = (UINT8)param;
    }
    else
    	mdnsSrvcParam.scope = S2W_DFLT_MDNS_SCOPE;    
    
   if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {

    AppS2wParse_Int(p, &param);
    mdnsSrvcParam.conflctDetect = (UINT8)param;
    }
   else
    	mdnsSrvcParam.conflctDetect = S2W_DFLT_MDNS_CONFLICT_DETECT;

    if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {    
    	AppS2wParse_Int(p, &param);
    	mdnsSrvcParam.autoCorrect = (UINT8)param;
    }
    else
    	mdnsSrvcParam.autoCorrect = S2W_DFLT_MDNS_AUTOCORRECT;
       
     AppS2wHal_MdnsServiceReg(&mdnsSrvcParam);
     mdnsATConfig =1;
    return S2W_SUCCESS;
}


PUBLIC UINT8
AppS2wCmd_MdnsHostNmDeReg(UINT8 *ptr)
{
    UINT8 *p;
    UINT16 len;
    UINT16 totalLen = 0;
    //UINT8 status;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsHnParam.hostname = mdnsParamBuff;
    if(0 != len)
    {
        strcpy((INT8 *)mdnsHnParam.hostname, (const char *)p);
    }
    else
    {/*Read the default system name*/
       len = strlen((const INT8 *)s2wCurrent.hostName);
       strcpy((INT8 *)mdnsHnParam.hostname, (const char *)s2wCurrent.hostName);
    }
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsHnParam.domain = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsHnParam.domain, (const char*)p);
    totalLen += (len+1);

    AppS2wHal_MdnsHostNameDereg(&mdnsHnParam);

    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wCmd_MdnsSrvDeReg(UINT8 *ptr)
{
  UINT8 *p;
    UINT16 len;
    UINT16 totalLen = 0;
   // UINT8 status;
    //UINT32 param = 0;
   // UINT8  KeyValPrsnt = 0;
   // UINT8  KeyValIndx=0;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.srvcInstance = mdnsParamBuff;
    strcpy((INT8 *)mdnsSrvcParam.srvcInstance, (const INT8 *)p);
    totalLen += (len+1);
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.subType = &mdnsParamBuff[totalLen];;
    strcpy((INT8 *)mdnsSrvcParam.subType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.srvcType= &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvcParam.srvcType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.proto = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvcParam.proto, (const INT8 *)p);
    totalLen += (len+1);
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvcParam.domain = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvcParam.domain, (const INT8 *)p);
    totalLen += (len+1);

    AppS2wHal_MdnsServiceDereg(&mdnsSrvcParam);
    
    return S2W_SUCCESS;
    
}

PUBLIC UINT8
AppS2wCmd_MdnsAnnounceAll(UINT8 *ptr)
{
  // check the config paramaters are not populated then populate from dflt
  APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();  
  UINT8 macaddr[GSN_MAC_ADDR_LEN],grpProvUuid[17] = {'g','a','i','n','s', 'p', 'a', 'n','_'};
  INT32 grpMdnsPort =80;
  S2w_macAddrRTCGet(macaddr);
  AppS2wParse_IntToStr(&macaddr[3],&grpProvUuid[9],3);
  grpProvUuid[15] = 0;

  if( mdnsATConfig != 1)
  { // register with default parameter
  		// register with default parameter
	  UINT8 tmpBuff[255],len;

	  memset(tmpBuff,0,255);
		if(s2wCurrent.mode == S2W_WLANDATA_MODE_PROV_AP || pAppRtcLtchInfo->grpProvVerify == 1)
	   	{
			len = sprintf((char*)tmpBuff,"%s,%s,%d,%d,%d,%d",
                    grpProvUuid,S2W_DFLT_MDNS_DOMAIN_NAME,S2W_DFLT_MDNS_TTL,
                    S2W_DFLT_MDNS_SCOPE,S2W_DFLT_MDNS_CONFLICT_DETECT,
                    S2W_DFLT_MDNS_AUTOCORRECT);
	   	}
	   	else
	   	{
	   		/* use configuration from builder*/
			len = sprintf((char*)tmpBuff,"%s,%s,%d,%d,%d,%d",
				   S2W_DFLT_MDNS_HOST_NAME,S2W_DFLT_MDNS_DOMAIN_NAME,S2W_DFLT_MDNS_TTL,
				   S2W_DFLT_MDNS_SCOPE,S2W_DFLT_MDNS_CONFLICT_DETECT,
				   S2W_DFLT_MDNS_AUTOCORRECT);
	   	}
       	tmpBuff[len]='\0';
       AppS2wCmd_MdnsHostNameReg(tmpBuff);

      	/* service registration */
       	memset(tmpBuff,0,255);
       	if(s2wCurrent.mode == S2W_WLANDATA_MODE_PROV_AP) // for grp provision need to use ssl port
       	{
       		/* group provision start*/
			grpMdnsPort = 443;
		   	len = sprintf((char*)tmpBuff,"%s,%s,%s,%s,%s,%d,%d,%s",
                    S2W_DFLT_MDNS_SER_INST_NAME,S2W_DFLT_MDNS_SER_SUB_TYPE,S2W_DFLT_MDNS_SER_TYPE,
                    S2W_DFLT_MDNS_PROTO,S2W_DFLT_MDNS_DOMAIN_NAME,grpMdnsPort,S2W_DFLT_MDNS_KEY,
                    S2W_DFLT_MDNS_TXT_RECORD );
	   		
	   	}
	   	else if(pAppRtcLtchInfo->grpProvVerify == 1)
	   	{	   		
	   		/* group provision verification*/
      		len = sprintf((char*)tmpBuff,"%s,%s,%s,%s,%s,%d,%d,%s",
				  	grpProvUuid,S2W_DFLT_MDNS_SER_SUB_TYPE,S2W_GRPPROV_VERIFY_MDNSSER_TYPE,
                    S2W_DFLT_MDNS_PROTO,S2W_DFLT_MDNS_DOMAIN_NAME,grpMdnsPort,S2W_DFLT_MDNS_KEY,
                    S2W_DFLT_MDNS_TXT_RECORD );
			pAppRtcLtchInfo->grpProvVerify = 0;			
	   	}
	   	else
	   	{
	   		/* use configuration from builder*/	
	   		len = sprintf((char*)tmpBuff,"%s,%s,%s,%s,%s,%d,%d,%s",
					S2W_DFLT_MDNS_SER_INST_NAME,S2W_DFLT_MDNS_SER_SUB_TYPE,S2W_DFLT_MDNS_SER_TYPE,
					S2W_DFLT_MDNS_PROTO,S2W_DFLT_MDNS_DOMAIN_NAME,S2W_DFLT_MDNS_PORT,S2W_DFLT_MDNS_KEY,
					S2W_DFLT_MDNS_TXT_RECORD );
	   	}
		
       	tmpBuff[len]='\0';
       	AppS2wCmd_MdnsServiceReg(tmpBuff);
       	mdnsATConfig = 0;
  	}
  
  if(GsnMdns_AnnounceAll(&s2wappMainTaskCtxt->mdns) != S2W_SUCCESS)
  {
    return S2W_FAILURE;
  }
  return S2W_SUCCESS;
  
}

PUBLIC UINT8
AppS2wCmd_MdnsAnnounce(UINT8 *ptr)
{
    UINT8 *p;
    UINT16 len;
    UINT16 totalLen = 0;
   // UINT8 status;
    UINT32 param = 0;
   // UINT8  KeyValPrsnt = 0;
   // UINT8  KeyValIndx=0;
    S2W_MDNS_ANNOUNCE_PARAM_T mdnsAnnceParam;
   
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &param);
    mdnsAnnceParam.type = param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsAnnceParam.srvceName = mdnsParamBuff;
    strcpy((INT8 *)mdnsAnnceParam.srvceName, (const INT8 *)p);
    totalLen += (len+1);
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsAnnceParam.domain = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsAnnceParam.domain, (const INT8 *)p);
    totalLen += (len+1);
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsAnnceParam.srvceSubType = &mdnsParamBuff[totalLen];;
    strcpy((INT8 *)mdnsAnnceParam.srvceSubType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsAnnceParam.srvceType= &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsAnnceParam.srvceType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsAnnceParam.srvceProto = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsAnnceParam.srvceProto, (const INT8 *)p);
    totalLen += (len+1);
    
    
    
    return AppS2wHal_MdnsAnnounce(&mdnsAnnceParam);
}


PUBLIC UINT8
AppS2wCmd_MdnsSrvcDiscover(UINT8 *ptr)
{
    UINT8 *p;
    UINT16 len;
    UINT16 totalLen = 0;
    UINT32 val;
    S2W_MDNS_SRVCDISCVR_PARAM_T mdnsSrvDscr;
    
    //S2w_Printf("\r\nAppS2wCmd_MdnsSrvcDiscover\r\n");
    
        p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    
    mdnsSrvDscr.srvcSubType = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvDscr.srvcSubType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvDscr.srvcType= &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvDscr.srvcType, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvDscr.srvcProto = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvDscr.srvcProto, (const INT8 *)p);
    totalLen += (len+1);
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    len = strlen((const char *)p);
    mdnsSrvDscr.domain = &mdnsParamBuff[totalLen];
    strcpy((INT8 *)mdnsSrvDscr.domain, (const INT8 *)p);
    totalLen += (len+1);

    p = AppS2wParse_NextParamGet(&ptr);
    
	if(p)
    AppS2wParse_Int(p, &val);
	else
		val=S2W_DFLT_MDNS_SCOPE;
    mdnsSrvDscr.scope = (UINT8 )val;
    /* check service discovery */
    AppS2wHal_MdnsSrvcDiscover(&mdnsSrvDscr);
    return S2W_SUCCESS;
}

#endif // # GSN_MDNS_ENABLE
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WRSSI Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Wrssi(UINT8 *ptr)
{
    INT8 rssi;
    if (ptr[0] == '?' && ptr[1] == '\0')
    {
       rssi = AppS2wHal_RssiGet();
       S2w_Printf("\r\n%d", (signed char)rssi);
       return S2W_SUCCESS;
    }
    return S2W_EINVAL;
}


VOID
AppS2wCmd_GetSecurityString(GSN_WDD_WLAN_CFG_T *WddConf,const char **security )
{
    
    *security = "NONE";

    switch (WddConf->securityCfg.mode)
    {
        case GSN_WDD_SEC_MODE_DISABLE:
            *security = "NONE";
            break;
        case GSN_WDD_SEC_MODE_WEP:
            if(GSN_WDD_SEC_WEP_OPEN == WddConf->securityCfg.wepConfig.authType)
                *security = "WEP (OPEN)";
            else
                *security = "WEP (SHARED)";
            break;
        case GSN_WDD_SEC_MODE_WPA_PERSONAL:
        *security = "WPA-PERSONAL";
        break;
        case GSN_WDD_SEC_MODE_WPA2_PERSONAL:
        *security = "WPA2-PERSONAL";
        break;
        case GSN_WDD_SEC_MODE_WPA_ENTERPRISE:
            *security = "WPA-ENTERPRISE";
        break;
        case GSN_WDD_SEC_MODE_WPA2_ENTERPRISE:
            *security = "WPA2-ENTERPRISE";
        break;
    }
    return;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WSTATUS Command.
 *   This function dispaly the connected network status.
 * @param ptr pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_Wstatus(UINT8 *ptr)
{
    const char *security = "NONE";
    S2W_WLANINFO_T info;
    UINT8 status,mode = 2;
    GSN_WDD_WLAN_CFG_T *WddConf;

	GSN_WLAN_MAC_ADDR_T bssid;
    /* call the hal function to get the network status
     */
    status = AppS2wHal_InfoGet(&info);

    if (status != S2W_SUCCESS)
    {
        S2w_Printf("\r\nNOT ASSOCIATED\r\n");
        return S2W_SUCCESS;
    }
    if(info.mode == S2W_WLANDATA_MODE_INFRA)
    {
        mode = 0;
    }

    S2w_Printf("\r\nMODE:%d CHANNEL:%d SSID:\"",
            mode, info.channel);
    AppS2wHal_CharNPut(info.ssid, info.ssidLen);
    S2w_Printf("\"");

	if(GSN_WIF_WLAN_NW_TYPE_AP == s2wappMainTaskCtxt->if0.wddCtx.wlanNwType)
	{ 				  
		GsnWdd_PhyAddrGet(&s2wappMainTaskCtxt->if0.wddCtx,(INT8 *)&bssid);
		S2w_Printf("\r\nBSSID:%02x:%02x:%02x:%02x:%02x:%02x",
		   bssid.array[0], bssid.array[1], bssid.array[2],
		   bssid.array[3], bssid.array[4], bssid.array[5]);
	}
	else
	{
    if (info.validBssid)
    {
        S2w_Printf("\r\nBSSID:%02x:%02x:%02x:%02x:%02x:%02x",
            info.bssid[0], info.bssid[1], info.bssid[2],
            info.bssid[3], info.bssid[4], info.bssid[5]);
	   	}
    }
    WddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    AppS2wCmd_GetSecurityString(WddConf, &security);

    S2w_Printf(" SECURITY:%s", security);

    return S2W_SUCCESS;
}

#ifdef S2W_GSLINK


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+XMLPARSE command
 *   This function enable/disable the XML string parser.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 * @return S2W_EINVAL - operation Failed-invalid input
 *************************************************************/

PUBLIC UINT8
AppS2wCmd_XmlParseEnable(UINT8 *ptr)
{
    UINT8 status = S2W_SUCCESS;
	UINT8 *p;
	UINT32 ParseEn=0;//,cid;
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
	AppS2wParse_Int(p, (UINT32 *)&ParseEn);
	s2wappMainTaskCtxt->xmlParseEn = (UINT8)ParseEn;
	return(status);
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process httpd context initialisation.
 *   This function configures the httpd context initialisation.
 * @param cid - connection identifier.
 *@param reinit - reinit flag.
 * @return NONE
 *************************************************************/

UINT8
AppS2w_HttpdCtxInit(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT8 reinit)
{
	UINT8 status= S2W_SUCCESS;
	httpdCtx->httpdBufferLenUsed=0;
	httpdCtx->httpdMaxBufferSize= 1024 ;//GSN_HTTPD_BUF_SIZE;
	if(reinit == 0 )
	{
		httpdCtx->httpdBuffer=(INT8*)GsnHttpd_GetBuffer();
		if(httpdCtx->httpdBuffer == NULL)
			return S2W_FAILURE;
		GsnOsal_SemCreate(&httpdCtx->httpdSendSem, 0 );
		httpdCtx->moreData=0;
		httpdCtx->methodLineReceived=0;
		httpdCtx->reqBodyLen = 0;
		httpdCtx->method= 0;
		return status;
	}
	else if(httpdCtx->httpdBuffer == NULL)
	{
		return S2W_FAILURE;
	}
	return status;
 }
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process httpd context initialisation.
 *   This function configures the httpd context initialisation.
 * @param cid - connection identifier.
 *@param reinit - reinit flag.
 * @return NONE
 *************************************************************/
VOID
AppS2w_HttpdCtxDeInit(S2W_HTTPD_CONTEXT_T *httpdCtx)
{
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    UINT32 totalhdrcount = 0;
    UINT32 i = 0;
#endif

	/* HTTP context Init*/
	//UINT8 status= S2W_SUCCESS;
    if(NULL != httpdCtx->httpdBuffer)
    {
    	GsnHttpd_ReleaseBuffer(httpdCtx->httpdBuffer);
    	httpdCtx->httpdBuffer=NULL;
    }

	httpdCtx->httpdBufferLenUsed=0;
	httpdCtx->httpdMaxBufferSize=0;
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    /* Fre up all the allocated memmory for cutom headers */
    if(NULL != httpdCtx->httphdrnameptrptr)
    {
        totalhdrcount = httpdCtx->appheadercount + HTTP_STATIC_HDR_COUNT;
        /* search for an empty slot */
        for(i = 0; i < totalhdrcount; i++)
        {
            if(NULL != httpdCtx->httphdrnameptrptr[i])
            {
                gsn_free(httpdCtx->httphdrnameptrptr[i]);
                httpdCtx->httphdrnameptrptr[i] = NULL;
                break;
            }
        }
        gsn_free(httpdCtx->httphdrnameptrptr);
        httpdCtx->httphdrnameptrptr = NULL;
    }
    if(NULL != httpdCtx->httphdrvalptrptr)
    {
        totalhdrcount = httpdCtx->appheadercount + HTTP_STATIC_HDR_COUNT;
        /* search for an empty slot */
        for(i = 0; i < totalhdrcount; i++)
        {
            if(NULL != httpdCtx->httphdrvalptrptr[i])
            {
                gsn_free(httpdCtx->httphdrvalptrptr[i]);
                httpdCtx->httphdrvalptrptr[i] = NULL;
                break;
            }
        }
        gsn_free(httpdCtx->httphdrvalptrptr);
        httpdCtx->httphdrvalptrptr = NULL;
    }
    if(NULL != httpdCtx->httphdrtypeptr)
    {
        gsn_free(httpdCtx->httphdrtypeptr);
        httpdCtx->httphdrtypeptr = NULL;
    }
#endif
	GsnOsal_SemDelete(&httpdCtx->httpdSendSem);
 }

VOID
AppS2w_HttpdMethodSet(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT8 method)
{
	if(httpdCtx != NULL)
		httpdCtx->method= method;
}
#ifdef S2W_GSLINK_RAW
VOID
AppS2w_HttpdBodyLenSet(S2W_HTTPD_CONTEXT_T *httpdCtx,UINT32 len)
{
                if(httpdCtx != NULL)
                                httpdCtx->reqBodyLen= len;

}
/**
******************************************************************
* @ingroup S2w-Application
* @brief Process Sends the http data to serial interface.
*   This function Sends the http data to serial interface.
* @param cid the cid of the http connection.
* @param dataLen the input data length.
@return None.
******************************************************************/
VOID
AppS2w_RawDataSend(UINT8 cid, UINT8 *buffer,UINT32 httpRxDataLen)
{
    INT8 startMark[10],len;
    len=sprintf(startMark,"%c%c%x%04d", S2W_ESC, 'H', cid,httpRxDataLen);


	
#ifndef S2W_DUAL_INTERFACE_SUPPORT
	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);	
    AppS2wHal_CharNPut(startMark, len);
#else
	GsnOsal_SemAcquire(&s2wSyncSemID1, GSN_OSAL_WAIT_FOREVER);
    AppS2wHal_CharNPut1(startMark, len);
#endif
	if(buffer != NULL)
    {
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(buffer, httpRxDataLen);
#else
         AppS2wHal_CharNPut1(buffer, httpRxDataLen);
#endif
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
#ifndef S2W_DUAL_INTERFACE_SUPPORT
	GsnOsal_SemRelease(&s2wSyncSemID);
#else
	GsnOsal_SemRelease(&s2wSyncSemID1);
#endif
	

}

#endif

#ifdef S2W_GSLINK_XML

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+XMLSEND command
 *   This function configures the http send paramters.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 * @return S2W_FAILURE - operation Failed.
 * @return S2W_EINVAL - operation Failed-invalid input
 *************************************************************/


PUBLIC UINT8
AppS2wCmd_XmlSend(UINT8 *ptr)
{

    UINT32 cid, method;
    UINT8 /**page, *content,*/ *p,*profName /*,*httpRxDataBuf */;
    UINT32 /*httpRxDataLen = 0, temp, ret, */ timeOut,len;

#if defined (S2W_HTTPS_SUPPORT) || (S2W_HTTPC_SUPPORT)
			S2W_HTTP_DATA_T *pHttpData;
#endif
    UINT8 status = S2W_SUCCESS;
#ifdef S2W_HTTP_CUSTOM_SUPPORT
    UINT8 statusline;
    UINT32 headercount;
#endif


	/* cid,type,timeout,uri,n*/
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
	cid = AppS2w_CidValidate(*p);
	if( cid == INVALID_CID)
        return S2W_EBADCID;
    p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}
	AppS2wParse_Int(p, (UINT32 *)&method);

    if(method == S2W_HTTP_METHOD_GETRESP)
    {
    	method = GSN_HTTP_METHOD_GETRESP;
    }
    else if(method == S2W_HTTP_METHOD_POSTRESP)
    {
    	method = GSN_HTTP_METHOD_POSTRESP;
    }
#if defined (S2W_HTTPS_SUPPORT) || (S2W_HTTPC_SUPPORT)
	httpConfInfo.reqMethod = (GSN_HTTP_USER_METHOD_T)method;
#endif

	/*timeout*/
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
			return 	status;
	}
#endif
#if defined (S2W_HTTPS_SUPPORT) || (S2W_HTTPC_SUPPORT)
		httpConfInfo.httpTimeOut =timeOut;
#endif
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}
   	len = strlen((const char *)p);
#if defined (S2W_HTTPS_SUPPORT) || defined (S2W_HTTPC_SUPPORT)

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
    	/* Set the HTTP version */
   	httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
#endif

	profName = AppS2wParse_NextParamGet(&ptr);
#if (defined(S2W_GSLINK_XML) &&  defined(S2W_WEB_SERVER))

	if((method == GSN_HTTP_METHOD_GETRESP || method == GSN_HTTP_METHOD_POSTRESP || method == GSN_HTTP_METHOD_PUTRESP || method == GSN_HTTP_METHOD_DELETERESP)
		&& s2wappMainTaskCtxt->xmlParseEn == 1)
	{

		if(strcmp((const char *)s2wappMainTaskCtxt->currenturi,(const INT8 *)p) != 0)
			return S2W_FAILURE;

		//if (!(*profName))
		if ((NULL == profName) || (*profName == NULL))
		{
			return S2W_EINVAL;
		}
		GsnXMLStr_SetRootTag(s2wCidList[cid].xmlParserCtx,profName);
        len=0;
		/*Number of tags*/
		p = AppS2wParse_NextParamGet(&ptr);
		if (p != NULL)
		AppS2wParse_Int(p,  &len);
		if(len != 0)

		GsnXMLStr_SetTagCount(s2wCidList[cid].xmlParserCtx,len);
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
            AppS2wParse_Int(p,  &len);
            if(len != 0)
            {
                headercount = len;
            }
        }
#endif
		status = AppS2w_HttpdCtxInit(&s2wCidList[cid].httpdCtx,1);
		AppS2w_HttpdMethodSet(&s2wCidList[cid].httpdCtx,(UINT8)method);
#ifdef S2W_HTTP_CUSTOM_SUPPORT
        AppS2w_HttpStatusLineSet(&s2wCidList[cid].httpdCtx, statusline);
        AppS2w_HttpHdrCountSet(&s2wCidList[cid].httpdCtx, headercount);
#endif
		if(s2wappMainTaskCtxt->respTimeOut !=0)
		{
			s2wappMainTaskCtxt->responseInprogress=1;
		GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl);
		s2wappMainTaskCtxt->respTimeOutTmrHndl = GsnSoftTmr_Start(&s2wappMainTaskCtxt->respTimeOutTmr,
						  GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(s2wappMainTaskCtxt->respTimeOut),
						  ( GSN_SOFT_TMR_CBR_T )AppMcu_RespTimeoutCb, &s2wCidList[cid].sd );
		}
		return status;
	}
	else
#endif
#if (defined(S2W_GSLINK_XML) || defined(S2W_GSLINK_RAW )) &&  (defined (S2W_HTTPS_SUPPORT) || defined(S2W_HTTPC_SUPPORT))
	if((method == GSN_HTTP_METHOD_GET) && s2wappMainTaskCtxt->xmlParseEn == 1)
    {
        if(GSN_HTTP_METHOD_POST == method)
        {
            gsn_free(httpConfInfo.reqPathPtr);
            /* type is post and content length is not optional */
            return S2W_EINVAL;
        }
        httpConfInfo.reqBodyTotalLen = 0;
        httpConfInfo.reqBodyLen = 0;

        pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(cid);
        if(pHttpData != NULL)
        {
            GsnOsal_SemAcquire(&pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
			status = AppS2w_GslinkInit(cid);
			if(status == S2W_FAILURE)
				return status;
			status = S2wHttp_XmlSend(cid);
			AppS2w_GslinkDeInit(cid,0);
        }
        else
        {
            return S2W_FAILURE;
        }

        if(pHttpData != NULL)
        {
            GsnOsal_SemRelease(&pHttpData->opInProgress);
        }
    }
    else if(s2wappMainTaskCtxt->xmlParseEn == 1)    	/*http post*/
    {

		if ((NULL == profName) || (*profName == NULL))
		{
			return S2W_EINVAL;
		}
		/*Number of tags*/
		p = AppS2wParse_NextParamGet(&ptr);
		if (!p)
		{
			return S2W_EINVAL;
		}
		AppS2wParse_Int(p, &len);
		if(len == 0)
			return S2W_EINVAL;
		pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(cid);
		if(pHttpData == NULL)
		{
			return S2W_FAILURE;
		}
		GsnOsal_SemAcquire(&pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
		status = AppS2w_GslinkInit(cid);
		if(status == S2W_FAILURE)
			return status;
		GsnXMLStr_SetRootTag(s2wCidList[cid].xmlParserCtx,profName);
		GsnXMLStr_SetTagCount(s2wCidList[cid].xmlParserCtx,len);
    }
	else
		return S2W_FAILURE;
#endif
    return status;

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the xml data.
 *   This function encodes the xml data .
 * @param cid - cid of the http connection.
 * @param dataBuffer - data buffer
  * @param inBuflen - data buffer length
 * @return None
 ******************************************************************/

VOID
AppS2w_XmlDataProcess(UINT8 cid,UINT8 *dataBuffer,UINT32 inBuflen,UINT32 elementType)
{
	UINT32 bufSpaceLeft;
	UINT8 status=S2W_SUCCESS;
	GSN_STATUS encodeStatus;
	do
	{
		/* Check for valid xmlparser context, if socket closed or sent failed , then closed  the cid */
		if(s2wCidList[cid].xmlParserCtx == NULL)
		{
			return;
		}
		bufSpaceLeft =  s2wCidList[cid].httpdCtx.httpdMaxBufferSize - s2wCidList[cid].httpdCtx.httpdBufferLenUsed;
		encodeStatus = GsnXMLStr_Encode((s2wCidList[(cid)].xmlParserCtx),dataBuffer,inBuflen ,elementType,
				&(s2wCidList[(cid)].httpdCtx.httpdBuffer),s2wCidList[(cid)].httpdCtx.httpdBufferLenUsed,&bufSpaceLeft);
#if (defined (S2W_HTTPS_SUPPORT) || defined(S2W_HTTPC_SUPPORT))
	if((httpConfInfo.reqMethod == GSN_HTTP_METHOD_POST))
	{
		if(encodeStatus == GSN_SUCCESS)
		{
				S2W_HTTP_DATA_T *pHttpData;
			s2wCidList[(cid)].httpdCtx.httpdBufferLenUsed +=bufSpaceLeft;
			status = AppS2wHal_XmlPost(cid);
			AppS2w_GslinkDeInit(cid,0);
			GsnOsal_SemAcquire(&s2wSyncSemID,GSN_OSAL_WAIT_FOREVER);
			AppS2wProcess_StatusNotify(status, 0);
			GsnOsal_SemRelease(&s2wSyncSemID);
			pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(cid);
			if(pHttpData != NULL)
			{
				GsnOsal_SemRelease(&pHttpData->opInProgress);
			}
		}
		else if(encodeStatus == GSN_BUFFER_FULL)/* NO space in buffer to store the encoded data*/
		{
			status = AppS2wHal_XmlPost(cid);
			if(status == S2W_FAILURE)
			{
					GsnOsal_SemAcquire(&s2wSyncSemID,GSN_OSAL_WAIT_FOREVER);
					AppS2wProcess_StatusNotify(status, 0);					
					GsnOsal_SemRelease(&s2wSyncSemID);
					AppS2w_GslinkDeInit(cid,0);
			}
				status = AppS2w_HttpdCtxInit(&s2wCidList[cid].httpdCtx,1);
		}
		else if	(encodeStatus == GSN_INVALID_PARAM)
		{
			GsnOsal_SemAcquire(&s2wSyncSemID,GSN_OSAL_WAIT_FOREVER);
			AppS2wProcess_StatusNotify(S2W_FAILURE, 0);
			GsnOsal_SemRelease(&s2wSyncSemID);
		}
		else
			{
			s2wCidList[(cid)].httpdCtx.httpdBufferLenUsed +=bufSpaceLeft;
	}
		}
#endif
#if defined(S2W_GSLINK_XML)  &&  defined(S2W_WEB_SERVER)
		if (s2wCidList[(cid)].httpdCtx.method == GSN_HTTP_METHOD_GETRESP || s2wCidList[(cid)].httpdCtx.method == GSN_HTTP_METHOD_POSTRESP)
	{
		if(encodeStatus == GSN_SUCCESS)
		{
			s2wCidList[(cid)].httpdCtx.httpdBufferLenUsed +=bufSpaceLeft;
			GsnOsal_SemAcquire(&s2wSyncSemID,GSN_OSAL_WAIT_FOREVER);
			AppS2w_HttpSemRelease(cid);			
			status = s2wappMainTaskCtxt->gsLinkSendStatus ;
			AppS2wProcess_StatusNotify(status, 0);
			GsnOsal_SemRelease(&s2wSyncSemID);
		}
		else if(encodeStatus == GSN_BUFFER_FULL)/* NO space in buffer to store the encoded data*/
		{
			AppS2w_HttpSemRelease(cid);
			GsnOsal_SemAcquire(&s2wCidList[cid].httpdCtx.httpdSendSem,GSN_OSAL_WAIT_FOREVER);
			s2wCidList[(cid)].httpdCtx.httpdBufferLenUsed = 0;
			if(S2W_FAILURE == s2wappMainTaskCtxt->gsLinkSendStatus)
			{
				//S2w_Printf("\r\n$$$ s2wappMainTaskCtxt->gsLinkSendStatus: %d", s2wappMainTaskCtxt->gsLinkSendStatus);
				GsnOsal_SemAcquire(&s2wSyncSemID,GSN_OSAL_WAIT_FOREVER);
				AppS2wProcess_StatusNotify(S2W_FAILURE, 0);
				GsnOsal_SemRelease(&s2wSyncSemID);
				encodeStatus = GSN_INVALID_PARAM;
			}

			if(status == S2W_FAILURE)
			{/* to do */
			}
		}
		else if (encodeStatus == GSN_INVALID_PARAM)
		{
			GsnOsal_SemAcquire(&s2wSyncSemID,GSN_OSAL_WAIT_FOREVER);
			AppS2wProcess_StatusNotify(S2W_FAILURE, 0);
			GsnOsal_SemRelease(&s2wSyncSemID);
		}
		else
			{
				s2wCidList[(cid)].httpdCtx.httpdBufferLenUsed +=bufSpaceLeft;
				if(s2wappMainTaskCtxt->respTimeOut !=0)
				{
					s2wappMainTaskCtxt->responseInprogress=1;
				s2wappMainTaskCtxt->respTimeOutTmrHndl = GsnSoftTmr_Start(&s2wappMainTaskCtxt->respTimeOutTmr,
								GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(s2wappMainTaskCtxt->respTimeOut),
								  ( GSN_SOFT_TMR_CBR_T )AppMcu_RespTimeoutCb, &s2wCidList[cid].sd);
				}
			}
			if(s2wappMainTaskCtxt->gsLinkSendStatus == S2W_FAILURE)
			{
				return;
	}
		}
#endif
	}while(encodeStatus == GSN_BUFFER_FULL);
}

#endif
#endif


#ifdef S2W_ISOTX_SUPPORT
#define S2W_ISOTX_BLINK_INDEX 6
extern GSN_OSAL_SEM_T isoTxSem;
UINT8
AppS2wCmd_IsoTxStart(UINT8 *ptr)
{
    UINT8 *p;
    UINT8 status, index=0,times=0;
    UINT32 IntArray[RX_BUF_ELEMENTS],temp;
    GSN_ISOTX_BLINK_REQ_PARAM param;
    memset(&param,0,sizeof(GSN_ISOTX_BLINK_REQ_PARAM));
    // first parameter frequency
    // 2nd param-gain
    // 3rd param-blink type
    // 4th parambandwidth
    // 5th param-mode
    // 6th param- no of blinks
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
	do
	{
		if(index < S2W_ISOTX_BLINK_INDEX)
		{
			status = AppS2wParse_Int(p, &temp);
			if (status != S2W_SUCCESS)
			{
				return status;
			}
			IntArray[index] = temp;
		}
		else
		{
            break;
		}
		index++;
	}while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL);
	
	param.frequency    = IntArray[0];
	param.gain         = IntArray[1];
	param.blinkType    = IntArray[2];
	param.bandwidth    = IntArray[3];
	param.testMode     = IntArray[4];
	param.subBlinkCnt  = IntArray[5];
    if( (param.subBlinkCnt > GSN_WIF_WLAN_ISOTX_SUBBLINKS_MAX) || (param.subBlinkCnt < 1))
    {
		return S2W_EINVAL;
	}
   // 7th param- time b/w blinks
 	do
	{
               if(times < param.subBlinkCnt)
		{
			status = AppS2wParse_Int(p, &temp);
			if (status != S2W_SUCCESS)
			{
				return status;
			}
			param.subBlinkInt[times] = temp;
		}
		else
		{
             break;
		}
		index++;
		times++;
	}while((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL);
    status= GsnIsotx_BlinkReq(&s2wappMainTaskCtxt->isotxCtx,&param);
    if(status != GSN_SUCCESS)
    {
        App_IsotxCtrlNotifCb(s2wappMainTaskCtxt,0,0,NULL);
    }
	// wait on a semaphore
    GsnOsal_SemAcquire(&isoTxSem, GSN_OSAL_WAIT_FOREVER);
    return S2W_SUCCESS;
}


UINT8
AppS2wCmd_IsoTxStop(UINT8 *ptr)
{
    return GsnIsotx_StopReq(&s2wappMainTaskCtxt->isotxCtx);
}


UINT8
AppS2wCmd_IsoTxConfig(UINT8 *ptr)
{
    UINT8 *p;
    UINT8 status;
    GSN_ISOTX_REG_WRITE_REQ_PARAM param;
	UINT32 addr;
    // addr
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &addr);
    if (status != S2W_SUCCESS)
	{
	    return status;
	}
	param.regAddrVals[0].addr= addr;
   // value
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &(param.regAddrVals[0].val));
    if (status != S2W_SUCCESS)
	{
	    return status;
	}
	param.numRegVals=1;
	return (GsnIsotx_RegWriteReq(&s2wappMainTaskCtxt->isotxCtx, &param));

}

#endif

#ifdef S2W_UNASSOC_TXRX_SUPPORT
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Unsolicited tx configuration function.
 *   This function validate the parameter passed and configures
 *   the same for unsolicited data transmission.
 * @param ptr pointer to the input parameter
 * @return S2W_SUCCESS - operation successful.
 * @retval S2W_EINVAL  - operation failure-invalid command.
 ******************************************************************/
UINT8
S2w_CmdUnSolicitedTx(UINT8 *ptr)
{
    UINT8 *p, status;
    UINT32 temp=0;

    memset(&s2wappMainTaskCtxt->frame,0,sizeof(s2wappMainTaskCtxt->frame));
    /* get the frame control */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.frameControl=temp;
    /* get the seq control */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.seqControl=temp;
    /* get the channel */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.channelNum = temp;
    /* get the txrate */

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.txRate = temp;
    /* get the power info */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.power = temp;
    /* get the ccaenable info */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.ccaEnable = temp;
    /* get the len */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.macFrameLen = temp;
    // tx wait time
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->frame.rxWaitTime = temp;

   /* get the remote mac addr1  */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Mac(p,s2wappMainTaskCtxt->frame.addr1.array);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    /* get the addr3 */
    p = AppS2wParse_NextParamGet(&ptr);
    if ((p) && (*p != '\0'))
    {
        status = AppS2wParse_Mac(p,s2wappMainTaskCtxt->frame.addr3.array);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }
    /* get the addr4 */
    p = AppS2wParse_NextParamGet(&ptr);
    if ((p) && (*p != '\0'))
    {
        status = AppS2wParse_Mac(p,s2wappMainTaskCtxt->frame.addr4.array);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }
    // optional field for time stamp return
    p = AppS2wParse_NextParamGet(&ptr);
    if ((p) && (*p != '\0'))
    {
        status = AppS2wParse_Boolean(p,&s2wappMainTaskCtxt->uamTimeStampReturn);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }
    // optional field for tx and rx
    p = AppS2wParse_NextParamGet(&ptr);
    if ((p) && (*p != '\0'))
    {
        status = AppS2wParse_Int(p,&s2wappMainTaskCtxt->RxParam.rxFrameTypeBitMap);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }
    // optional field for tx and rx
    p = AppS2wParse_NextParamGet(&ptr);
    if ((p) && (*p != '\0'))
    {
        status = AppS2wParse_Boolean(p,&s2wappMainTaskCtxt->RxParam.ieFilterEnable);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        // if filter is enabled then filter
        p = AppS2wParse_NextParamGet(&ptr);
		if ((p) && (*p != '\0'))
		{
			UINT32 temp;
		    status = AppS2wParse_Int(p,&temp);
		    if (status != S2W_SUCCESS)
		    {
		        return status;
		    }
		    s2wappMainTaskCtxt->RxParam.ieFilterId = temp;
         }

    }
    // addr2 is the src addr
    //S2w_LoadMacAddr(s2wappMainTaskCtxt->frame.addr2.array);
    S2w_macAddrRTCGet(s2wappMainTaskCtxt->frame.addr2.array);
    // set the default cca threshold and timeout
    s2wappMainTaskCtxt->ccaThr = (INT8)((~S2W_DFLT_CCA_THR)+1);
	s2wappMainTaskCtxt->ccaTimeout = S2W_DFLT_CCA_TIMEOUT;
    return status;
}


UINT8 s2wUamBufs[S2W_NUM_UAM_BUFS][1500];
UINT8 uamRxInit=0;
PUBLIC GSN_STATUS
s2wUamRx_Init()
{
    GSN_STATUS retCode = GSN_SUCCESS;
    int i =0;
    UINT8 *pBuf;

    if(!uamRxInit)
    {
    GsnRingBuf_Init( &s2wappMainTaskCtxt->s2wUamBufQ, sizeof(UINT32), S2W_NUM_UAM_BUFS+1,
        s2wappMainTaskCtxt->s2wUamBufQBuf);
    for (i = 0; i  < S2W_NUM_UAM_BUFS; i++)
    {
        pBuf = s2wUamBufs[i];
        GsnRingBuf_Put( &s2wappMainTaskCtxt->s2wUamBufQ, &pBuf);
    }
        uamRxInit =1;
	}
    return retCode;
}

VOID
S2W_UnassocDataIndCB(VOID *ctx, INT8 *data, UINT16 dataLen)
{
    S2W_MSG_T recvMsg;
    UINT8 *rawbuf;
    if (GSN_SUCCESS == GsnRingBuf_Get( &s2wappMainTaskCtxt->s2wUamBufQ, &rawbuf))
    {
         /* Buffer allocation successful, copy frame. This buffer is
            freed in S2W recv task */
         memcpy(rawbuf, (data+1), dataLen-1);
         recvMsg.msgType = S2W_RECV_TYPE_UAMDATA;
         recvMsg.rData.dataPtr = rawbuf;
         recvMsg.msgLen = dataLen;

         if( GSN_OSAL_SUCCESS != GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg))
         {
              GsnRingBuf_Put(&s2wappMainTaskCtxt->s2wUamBufQ,  &rawbuf);
         }
    }
}
VOID
S2w_UamRx(void *buf, INT16 len)
{
    INT32 InterruptEnableStatus;
GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    S2w_Printf("%cD", S2W_ESC);
#else
    S2w_Printf1("%cD", S2W_ESC);
#endif

#ifndef S2W_DUAL_INTERFACE_SUPPORT
    AppS2wHal_CharNPut(buf, len);
#else
    AppS2wHal_CharNPut1(buf, len);
#endif
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
GsnOsal_SemRelease(&s2wSyncSemID);

    InterruptEnableStatus = GsnOsal_IntrDisable();

        /*Now free the buffer*/
    GsnRingBuf_Put(&s2wappMainTaskCtxt->s2wUamBufQ,  &buf);

        /**< Reenable the interrupts */
    GsnOsal_IntrEnable( InterruptEnableStatus );
}


 /******************************************************************/
UINT8
S2w_CmdUnSolicitedRx(UINT8 *ptr)
{
    UINT8 *p, status;
    UINT32 temp=0;
    GSN_WDD_UAM_DRX_CONFIG_PARAM_T param;
    GSN_WDD_UAM_DRX_START_PARAM sParam;

    memset(&param,0,sizeof(param));
    /* get the frame type */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&param.rxFrameTypeBitMap);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p,&param.ieFilterEnable);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    param.ieFilterId = temp;

    // channel
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&temp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    sParam.chNum = temp;
    // wait time
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&sParam.rxWaitTime);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    //S2w_Printf("\r\n start Rx mode\r\n");
    // start the mode
    GSN_WDD_UAM_START_RESP_T resp;
    status= GsnWdd_UAMStart(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp);
    if(status != GSN_SUCCESS)
    {
        return(status);
    }
    //S2w_Printf("\r\n start Rx config\r\n");
    // configure it
    status= GsnWdd_UAMDataRxConfig(&(s2wappMainTaskCtxt->if0.wddCtx), &param);
    if(status != GSN_SUCCESS)
    {
        return(status);
    }
    s2wUamRx_Init();
    // cb register for data rx
    GsnWdd_DataIndCbReg(&(s2wappMainTaskCtxt->if0.wddCtx), S2W_UnassocDataIndCB, s2wappMainTaskCtxt);
    // start the reception
    GSN_WDD_UAM_DRX_START_RESP_T stResp;
    status = GsnWdd_UamDataRxStart(&(s2wappMainTaskCtxt->if0.wddCtx), &sParam,
								     &stResp);

    return status;
}


UINT8
S2w_CmdUnSolicitedRxstop(UINT8 *ptr)
{
	UINT8 status;
	GSN_WDD_UAM_DRX_STOP_PARAM param;
	GSN_WDD_UAM_DRX_STOP_RESP_T resp;
	param.ifNum =0;
	status = GsnWdd_UAMDataRxStop(&(s2wappMainTaskCtxt->if0.wddCtx), &param, &resp);
	if(status != GSN_SUCCESS)
	{
		return status;
	}
	// stop the mode
    GSN_WDD_UAM_STOP_RESP_T resp1;
    return (GsnWdd_UAMStop(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp1));
}


UINT8
S2w_CmdUnSolicitedCcaConf(UINT8 *ptr)
{
    UINT8 status,*p;
    UINT32 thresh=0;
    p = AppS2wParse_NextParamGet(&ptr);//threshold in db
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&thresh);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    s2wappMainTaskCtxt->ccaThr = (INT8)(~(thresh)+1);// 2s compliment
    s2wappMainTaskCtxt->ccaTimeout = S2W_DFLT_CCA_TIMEOUT;
    p = AppS2wParse_NextParamGet(&ptr); // timeout in micro- sec
    if (p)
    {
        if(*p != '\0')
        {
            status = AppS2wParse_Int(p,&s2wappMainTaskCtxt->ccaTimeout);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
       	}
	}
	return S2W_SUCCESS;
}
#endif


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+APCLIENTINFO command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_ApClientInfoGet(UINT8* ptr)
{
   UINT8 status = S2W_EINVAL;
   //GSN_MAC_ADDR_T mac[32];
   INT8 mac[(6 * 64) + 4];
   GSN_MAC_ADDR_T *pMac;
   GSN_WIF_WLAN_CONNECTED_STA_LIST_RSP_T *pConctedStaListResp;
   GSN_DHCP_SRVR_CLIENT_T client[64];
   UINT8 macCount=0,ipCount=0,i=0,j=0,k=0,localFlag=0;
   if (ptr[0] == '?' && ptr[1] == '\0')
   {
       if((s2wCurrent.mode == 2)
#ifdef S2W_NCM_SUPPORT_ENABLE
          || (ncmAutoMode)
#endif
#ifdef GSN_P2P 
        || ((s2wCurrent.mode == 3)  &&  (s2wappMainTaskCtxt->wdd.wddP2pConf.roleGo == P2P_ROLE_GO))
#endif
	   )// only on Ap mode
       {
           macCount = GsnWdd_ConctedStaListGet(&s2wappMainTaskCtxt->if0.wddCtx, &mac[0],sizeof(mac));
			pConctedStaListResp = (GSN_WIF_WLAN_CONNECTED_STA_LIST_RSP_T *)&mac[0];
			macCount = pConctedStaListResp->numStaConnected;
           S2w_Printf("\r\nNo.Of Stations Connected=%d\r\n",macCount);
#ifdef S2W_DHCP_SERVER_ENABLE
           ipCount = GsnDhcpSrvr_ClientQuery(&dhcpSrvr, &client[0],64);
#endif
           if(macCount>0)
           {
               localFlag = 0;
               S2w_Printf("No     MacAddr                   IP\r\n");
			   pMac = (GSN_MAC_ADDR_T *) pConctedStaListResp->addr;
               while(macCount--)
               {
                  S2w_Printf("%d      ", j+1);
                  for(i=0;i<6;i++)
                  {
                      S2w_Printf("%02x", pMac->array[i]);
                      if( i<5)
                      {
                          S2w_Printf(":");
                      }
                      // serach in dhcp table
                  }
                  for(k=0;k<ipCount;k++)
                  {
                      if((memcmp(client[k].macAddr,pMac->array, GSN_MAC_ADDR_LEN) ==0 ) && 
					  	 (client[k].allocated == 1)) // dhcp
                      {
                          UINT32 ipaddr= ntohl(client[k].ipAddr);
                          S2w_Printf("         %d.%d.%d.%d",((ipaddr >> 24) & 0xff),((ipaddr >> 16) & 0xff),
                                        ((ipaddr >> 8) & 0xff),(ipaddr & 0xff)) ;
                          localFlag = 1;
                          break;
                      }
                  }
                  if(localFlag == 0) // static ip
                  {
                      S2w_Printf("         ****");
                  }
                  localFlag = 0;
                  j=j+1;
				  pMac++;
                  S2w_Printf("\r\n");
               }
           }
           status = S2W_SUCCESS;
       }
       else
       {
           status = S2W_FAILURE;
       }
   }
   return status;
}


UINT8
AppS2wCmd_ArpEntrySet(UINT8 *ptr)
{
  UINT8 *p,status;
  UINT32 ipAddr;
  UINT8 macAddr[6];
  ULONG hwMsw=0,hwLsw=0;
  
  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    
    status = AppS2wParse_Ip(p,(UINT8*)&ipAddr);
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
    
    status = AppS2wParse_Mac(p,macAddr);
	if (status != S2W_SUCCESS)
	{
          return status;
	}
  }
  else
  {
    return S2W_EINVAL;
  }
  memcpy(&hwMsw,macAddr,2);
  memcpy(&hwLsw,macAddr+2,4);
   
  hwMsw = htonl(hwMsw);
  hwLsw = htonl(hwLsw);
  ipAddr = htonl(ipAddr);
  hwMsw >>= 16;
  if(nx_arp_static_entry_create(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,ipAddr,hwMsw,hwLsw) != NX_SUCCESS)
    return S2W_FAILURE;
  
  return S2W_SUCCESS;
  
}
UINT8
AppS2wCmd_ArpEntryGet(UINT8 *ptr)
{
	//APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    ULONG32 numOfEntries=0;
	UINT8 index=0;
	ARP_REC *ArpTbl_From_NwStack;//[MAX_ARP_ENTRY_STORE];
	
    /*memset( ArpTbl_From_NwStack, 0, sizeof( ArpTbl_From_NwStack ));*/
	
    if(*ptr == '?')
    {
    	ArpTbl_From_NwStack = (ARP_REC *)MALLOC(1024);
		if(NULL == ArpTbl_From_NwStack)
		{
			return S2W_FAILURE;
		}
		nx_arp_table_get(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl, 
							(VOID *)ArpTbl_From_NwStack, 
							1024, &numOfEntries);
        for(index =0; index<numOfEntries;index++)
        {
            S2w_Printf("\r\n%02x:%02x:%02x:%02x:%02x:%02x : ", ((ArpTbl_From_NwStack[ index ].msw >>8)&  0xff),(ArpTbl_From_NwStack[ index ].msw & 0xff),
                     ((ArpTbl_From_NwStack[ index ].lsw >> 24)& 0xff),((ArpTbl_From_NwStack[ index ].lsw >> 16)& 0xff),
                     ((ArpTbl_From_NwStack[ index ].lsw >> 8)& 0xff), ArpTbl_From_NwStack[ index ].lsw & 0xff);
            S2w_Printf("%d.%d.%d.%d",(( ArpTbl_From_NwStack[ index ].ip_address >> 24)& 0xff),(( ArpTbl_From_NwStack[ index ].ip_address >> 16) & 0xff),
          (( ArpTbl_From_NwStack[ index ].ip_address >> 8)& 0xff),(( ArpTbl_From_NwStack[ index ].ip_address )& 0xff));
        }
		FREE(ArpTbl_From_NwStack);
    }
    else
    {
        return S2W_EINVAL;
    }
    return S2W_SUCCESS;
}


UINT8
AppS2wCmd_ArpAutoSet(UINT8 *ptr)
{
  
  UINT8 *p,status;
  UINT32 enable;
  
  /* get the frame type */
  p = AppS2wParse_NextParamGet(&ptr);
  if (!p)
  {
	  return S2W_EINVAL;
  }
  status = AppS2wParse_Int(p,&enable);
  if (status != S2W_SUCCESS)
  {
	  return status;
  }

  _nx_arp_auto_arp_entry_enable(enable);
  
  return S2W_SUCCESS;
  
  
}


UINT8
AppS2wCmd_ArpEntryDelete(UINT8 *ptr)
{
  
  UINT8 *p,status;
  UINT32 ipAddr;
  UINT8 macAddr[6];
  ULONG hwMsw=0,hwLsw=0;
  
  if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
  {
    
    status = AppS2wParse_Ip(p,(UINT8*)&ipAddr);
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
    
    status = AppS2wParse_Mac(p,macAddr);
	if (status != S2W_SUCCESS)
	{
          return status;
	}
  }
  else
  {
    return S2W_EINVAL;
  }
  memcpy(&hwMsw,macAddr,2);
  memcpy(&hwLsw,macAddr+2,4);
   
  hwMsw = htonl(hwMsw);
  hwLsw = htonl(hwLsw);
  ipAddr = htonl(ipAddr);
  hwMsw >>= 16;
  if(nx_arp_static_entry_delete(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,ipAddr,hwMsw,hwLsw) != NX_SUCCESS)
    return S2W_FAILURE;
  
  return S2W_SUCCESS;
  
  
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NARPCACHEEN command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_ArpCacheEn(UINT8 *ptr)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    UINT8 status = S2W_EINVAL;
    UINT8 CacheEn;
    status = AppS2wParse_Boolean(ptr, &CacheEn);
	// S2w_Printf("arp =%x",CacheEn);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    pAppRtcLtchInfo->arpCacheEn = CacheEn;
    return status;
}

/**
 ******************************************************************************
 * @ingroup App
 * @brief Invalidate NW stack Arp Entry.
 *    This function Invalidates the  the ARP entries .
 * @param pNcmCtx - None.
 * @note
 ******************************************************************************/
PUBLIC VOID
AppArp_Invalidate(  )
{

	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	nx_arp_dynamic_entries_invalidate(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl);
   	memset(&pAppRtcLtchInfo->arpTablebuf[0],0,(sizeof(ARP_REC) * MAX_ARP_ENTRY_STORE));	
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+NARPCACHEDEL command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_ArpCacheDel(UINT8 *ptr)
{
    if (*ptr)
    {
        return S2W_EINVAL;
    }
    else
    {
        AppArp_Invalidate();
    }
    return S2W_SUCCESS;
}

#if defined(S2W_DTLS_CLIENT_SUPPORT)
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+DTSLOPEN command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS or S2W_FAILURE.
 ******************************************************************/
UINT8
AppS2wCmd_DTSLOpen(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT8 cid;
    UINT8 valCid;
    UINT8 *p;
    UINT8 endParam = 1;
    //S2w_Printf("\r\nAppS2wCmd_DTSLOpen\r\n");

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        S2w_Printf("Error-2\r\n");
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

        if( S2W_NETDATA_MODE_CLIENT == AppS2w_ConnModeGet(valCid))
        {
            //S2w_Printf("Start processing DTLS Joining\r\n");
            status = AppS2w_DtslClientOpen(valCid, (char*)pCertName, pClientCertName,
                                          pClientKeyName);
        }

#if 0
        if( S2W_NETDATA_MODE_SERVER == AppS2w_ConnModeGet(valCid))
        {
            status = AppS2w_SslServerOpen(valCid, pCertName);
        }
#endif
        //S2w_Printf("Error-3, status = %d\r\n", status);
        return status;
    }
    else
    {
        S2w_Printf("Error-1\r\n");
        return S2W_EBADCID;
    }
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process AT+DTLSCLOSE command.
 * @param ptr Pointer to the user input string.
 * @return status, S2W_SUCCESS or S2W_FAILURE.
 ******************************************************************/
UINT8
AppS2wCmd_DTSLClose(UINT8 *ptr)
{
    UINT8 cid;
    UINT8 *p;
    UINT8 valCid;
    //UINT8 status;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        S2w_Printf("Error-2\r\n");
        return S2W_EINVAL;
    }

    cid = *p;

    if ((valCid = AppS2w_CidValidate(cid)) == INVALID_CID)
    {
        return S2W_EINVAL;//AppS2w_SslClose(valCid);
    }
    nx_bsd_callback_register(s2wCidList[valCid].sd, NULL, 0);
	if(s2wCidList[valCid].conMode == S2W_NETDATA_MODE_CLIENT)
    {
        GsnDtls_Close((GSN_DTLS_CONN_T *)s2wCidList[valCid].ssl.sslConn);
	}
    s2wCidList[valCid].ssl.sslConn = NULL;
    s2wCidList[valCid].sslflag = FALSE;
    soc_close(s2wCidList[valCid].sd);
    s2wCidList[valCid].localPort = 0;
    s2wCidList[valCid].remotePort = 0;
	s2wCidList[valCid].sd = CID_NOTINUSE;
    return S2W_SUCCESS;
}
#endif

PUBLIC UINT8
AppS2wCmd_WlanStaPsCfg(UINT8 *ptr)
{
	UINT8 status;
	 UINT8 *p = NULL;
	GSN_WDD_STA_PS_CFG_SET_PARAM_T psCfgParam;
	UINT32 val;
    GSN_STATUS retVal;
	
    GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;

	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.wakeupType= (GSN_WIF_WLAN_STA_PS_WAKEUP_T)val;
	
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.wakeupInterval= val;


	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.listenIntervalAssoc= val;



	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.dataRxType = (GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_T) val;


	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.uapsdEnable = val;


	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.txAtTbttWakeup= val;


	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.beaconWaitTimeout = val;

	retVal= GsnWdd_RadioPowerSaveCfgSet(pWdd, &psCfgParam);
	if(GSN_SUCCESS != retVal)
	{
		return S2W_FAILURE;
	}
	return S2W_SUCCESS;
	
}
PUBLIC UINT8
AppS2wCmd_WlanApPsCfg(UINT8 *ptr)
{
	UINT8 status;
	 UINT8 *p = NULL;
	GSN_WDD_AP_PS_CFG_SET_PARAM psCfgParam;
	UINT32 val;
    GSN_STATUS retVal;
	
    GSN_WDD_CTX_T *pWdd = &appCtx.if0.wddCtx;

	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.deepSleepEnable= val;
	
	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.ctsToSelfBeforeSleep= val;


	p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}

	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	psCfgParam.rxOnAfterTx = val;

    p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &val);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    psCfgParam.rxOnAfterTx |= (val << 16);
    
	retVal = GsnWdd_ApPowerSaveCfgSet(pWdd, &psCfgParam);
	if(GSN_SUCCESS != retVal)
	{
		return S2W_FAILURE;
	}
	return S2W_SUCCESS;
}


UINT8
AppS2w_CmdL2ConfigSet(UINT8 *ptr)
{
	UINT8 status = S2W_SUCCESS;
	UINT32 proto;
	UINT32 disable;
	UINT8 *p;
	if (ptr[0] == '?' && ptr[1] == '\0')
	{
		S2w_Printf("\r\nCONFIG MAP:%02x\r\n", s2wappMainTaskCtxt->l2ConfigBitField);
	}
	else
	{
		p = AppS2wParse_NextParamGet(&ptr);
		if (!p)
		{
			return S2W_EINVAL;
		}
		status = AppS2wParse_Int(p, &proto);
		if ((status != S2W_SUCCESS) ||((proto & S2W_PROTO_ALL_MASK) == 0))
		{
			return S2W_EINVAL;
		}
		p = AppS2wParse_NextParamGet(&ptr);
		if (!p)
		{
			return S2W_EINVAL;
		}
		status = AppS2wParse_Int(p, &disable);
		if ((status != S2W_SUCCESS)||(disable > S2W_PROTO_ALL_MASK))
		{
			return S2W_EINVAL;
		}
		s2wappMainTaskCtxt->l2ConfigBitField = (s2wappMainTaskCtxt->l2ConfigBitField & (~proto)) |( proto & disable);
	}
	return status;
}


#ifdef S2W_PWM_SUPPORT
GSN_PWM_HANDLE_T pwm_handle;
GSN_PWM_PATTERN_T pattern;
UINT8 pwmInit=0;
UINT8
AppS2wCmd_PwmStart(UINT8 *ptr)
{
    UINT8 *p, status = S2W_EINVAL;
    UINT32 pwmId=0,prescalerValue=0,period=0,phaseDelay01=0,phaseDelay12=0;
    BOOL on_off=0,polarity=0,clocksel=0,frequency=0;


    GSN_PWM_INFO_T pwmInfo;
    GSN_PWM_CONFIG_T pwmConfig;
    
    if(pwmInit)
    {
       return S2W_FAILURE;
    }
    p = AppS2wParse_NextParamGet(&ptr);  /* pwm id */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &pwmId);
    if((status != GSN_SUCCESS) || (pwmId >4 ) || (pwmId < 1 ))
    {
        return S2W_EINVAL;
    }

    p = AppS2wParse_NextParamGet(&ptr); /* on or off */
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Boolean(p, &on_off );
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    p = AppS2wParse_NextParamGet(&ptr); /* polarity */
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Boolean(p, &polarity );
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    p = AppS2wParse_NextParamGet(&ptr); /* period */
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Int(p, &period );
    if ((status != S2W_SUCCESS) || (period  == 0)||(period  > 1000))
    {
        return status;
    }
    p = AppS2wParse_NextParamGet(&ptr);  /* frequency */
    if (p)
    {
        status = AppS2wParse_Boolean(p,&frequency );
        if (status != S2W_SUCCESS)
        {
            return status;
        }
    }
    p = AppS2wParse_NextParamGet(&ptr);  /* clock sel */
    if (p)
    {
         status = AppS2wParse_Boolean(p,&clocksel );
         if (status != S2W_SUCCESS)
         {
              return status;
         }
    }
    if(clocksel == GSN_PWM_CLOCKSEL_PRESCALECLOCK)
    {
        p = AppS2wParse_NextParamGet(&ptr);  /* prescalar value */
        if (p)
        {
            status = AppS2wParse_Int(p,&prescalerValue );
            if (status != S2W_SUCCESS)
            {
                 return status;
            }
        }

    }
    
    p = AppS2wParse_NextParamGet(&ptr); /* phaseDelay01 */
    if ((p) && (*p != '\0'))
    {
    status = AppS2wParse_Int(p, &phaseDelay01 );
    if ((status != S2W_SUCCESS) || (phaseDelay01  > 1000))
    {
        return status;
    }
	}
    
    p = AppS2wParse_NextParamGet(&ptr); /* phaseDelay12 */
    if ((p) && (*p != '\0'))
    {
    status = AppS2wParse_Int(p, &phaseDelay12 );
    if ((status != S2W_SUCCESS) || (phaseDelay12 > 1000))
    {
        return status;
    }
	}
    
    pwm_handle.pwmInitialized = 0;

    pattern.framePeriod = period;
    if(on_off)
    {
        pattern.timeON = (UINT16)period/2;
    }
    else
    {
        pattern.timeON = 0;
    }

    pwmInfo.channelId   = (GSN_PWM_NO)(pwmId-1);
    pwmInfo.callback    = NULL;
    pwmInfo.callBackCtx = NULL;
    pwmInfo.recurrences = 0;


    memset(&pwmConfig, 0, sizeof(GSN_PWM_CONFIG_T));
    pwmConfig.eClockFrequency = (GSN_PWM_CLOCKFREQ)frequency ;
    pwmConfig.eClockSelect  = (GSN_PWM_CLOCKSEL)clocksel;
    pwmConfig.prescaleValue = prescalerValue;
    pwmConfig.phaseDelay01  = phaseDelay01;
    pwmConfig.phaseDelay12  = phaseDelay12;
    pwmConfig.ePolarity[0]  = (GSN_PWM_POLARITY)polarity;
    pwmConfig.eSystemClkSelect = (GSN_PWM_SYSTEM_CLOCKSEL)GSN_PWM_CLK_XTAL ;
    /*pwmConfig.ePolarity[] = iotInput.pwmConfig.ePolarity;*/
    
    /* gpio muxing for PWM */
    if((GSN_PWM_NO)(pwmId-1) == GSN_PWM_1)
    {
        GsnIoMux_Sel(10,GSN_IOMUX_GPIO_10_APWM_0);
        GsnIoMux_PullDownDisable(10);
    }
    else if((GSN_PWM_NO)(pwmId-1) == GSN_PWM_2)
    {
        GsnIoMux_Sel(30,GSN_IOMUX_GPIO_30_APWM_1);
        GsnIoMux_PullDownDisable(30);
    }
    else if((GSN_PWM_NO)(pwmId-1) == GSN_PWM_3)
    {
        GsnIoMux_Sel(31,GSN_IOMUX_GPIO_31_APWM_2);
        GsnIoMux_PullDownDisable(31);
      
    }
    else if((GSN_PWM_NO)(pwmId-1) ==  GSN_PWM_SYNC)
    {
        /* sync Mode  */
        GsnIoMux_Sel(10,GSN_IOMUX_GPIO_10_APWM_0);
        GsnIoMux_PullDownDisable(10);
        GsnIoMux_Sel(30,GSN_IOMUX_GPIO_30_APWM_1);
        GsnIoMux_PullDownDisable(30);
        GsnIoMux_Sel(31,GSN_IOMUX_GPIO_31_APWM_2);
        GsnIoMux_PullDownDisable(31);
    }

    if(GsnPwm_Open(&pwm_handle,&pwmConfig) != GSN_SUCCESS)
    {
        S2w_Printf("\r\nERROR: PWM open failed \r\n");
        return S2W_FAILURE;
    }

    if(GsnPwm_Start(&pwm_handle, (GSN_PWM_NO)(pwmId-1), &pwmConfig,
                    &pattern, &pwmInfo) != GSN_SUCCESS)
    {
        S2w_Printf("\r\nERROR: PWM start failed \r\n");
        return S2W_FAILURE;
    }
    pwmInit = 1;
    return status;

}

UINT8
AppS2wCmd_PwmStop(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT32 pwmId=0;
    if(!pwmInit)
    {
       return S2W_FAILURE;
    }
    status = AppS2wParse_Int(ptr,&pwmId);
    if((status != GSN_SUCCESS) || (pwmId > 4) || (pwmId < 1 ))
    {
        status= S2W_EINVAL;
    }
    pwmInit = 0;
    GsnPwm_Stop(&pwm_handle,(GSN_PWM_NO)(pwmId-1));

    return status;

}


UINT8
AppS2wCmd_PwmCtrl(UINT8 *ptr)
{
    UINT8 *p, status = S2W_EINVAL;
    UINT32 pwmId=0,duty_cycle;
    if(!pwmInit)
    {
       return S2W_FAILURE;
    }
    p = AppS2wParse_NextParamGet(&ptr);  /* pwm id */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &pwmId);
    if((status != GSN_SUCCESS) || (pwmId >4) || (pwmId < 1 ))
    {
        return S2W_EINVAL;
    }
    p = AppS2wParse_NextParamGet(&ptr);  /* duty cycle */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &duty_cycle);
    if((status != GSN_SUCCESS) || (duty_cycle > 100) ||(duty_cycle == 0))
    {
        return S2W_EINVAL;
    }

    pattern.timeON = (UINT16)((pattern.framePeriod)*(duty_cycle)/100);
    status= GsnPwm_PatternUpdate(&pwm_handle,(GSN_PWM_NO)(pwmId-1),&pattern);
    return status;

}


#endif

#ifdef S2W_MEM_ACCESS
#define S2W_APP 0
#define S2W_WLAN 1
UINT8
AppS2wCmd_MemRead(UINT8 *ptr)
{
    UINT8 *p, status = S2W_EINVAL;
    BOOL device=0;
    UINT32 size=0, address=0,count=0;
    INT32* addrPtr;
    p = AppS2wParse_NextParamGet(&ptr);  /*app or wlan */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &device);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }

    p = AppS2wParse_NextParamGet(&ptr);  /*address */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &address);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }
    addrPtr = (INT32*)address;
    p = AppS2wParse_NextParamGet(&ptr);  /*size in bytes */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &size);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }

    // do the read depends on the address is on wlan or app
    S2w_Printf("\r\n");
    if(device == S2W_APP)
    {
        for(count=0;count<(size/4);count++)
        {
            S2w_Printf("0x%08x:%08x\r\n",(address+(count*4)),*(addrPtr+count));
        }
    }
    else
    {
        UINT32 buff[32];
        GSN_SYS_CTL_MEM_READ_REQ_T readParam;
        readParam.addr = address;
        readParam.len = size;
        readParam.respBuf = (UINT8*)buff;
        GsnSysCtl_MemReadReq(&s2wappMainTaskCtxt->sysCtlCtx,&readParam);
        for(count=0;count<(size/4);count++)
        {
            S2w_Printf("0x%08x:%08x\r\n",(address+(count*4)),buff[count]);
        }
    }
    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_MemWrite(UINT8 *ptr)
{
    UINT8 *p, status = S2W_EINVAL;
    BOOL device=0;
    UINT32 size=0, address=0,count=0,data=0;
    INT32 *addrPtr;
    p = AppS2wParse_NextParamGet(&ptr);  /*app or wlan */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &device);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }

    p = AppS2wParse_NextParamGet(&ptr);  /*address */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &address);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }
    addrPtr = (INT32*)address;
    p = AppS2wParse_NextParamGet(&ptr);  /*size in bytes */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &size);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }

    // do the write depends on the address is on wlan or app
    //S2w_Printf("\r\n");
    if(device == S2W_APP)
    {
         while(((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL) && ((size/4)))
         {
             status = AppS2wParse_Hex(p, &data);
             if (status != S2W_SUCCESS)
             {
                 return status;
             }
             *(addrPtr+count) = data;
             count++;
             size -= 4;
         }
    }
    else
    {
         UINT8 buff[32];
         GSN_SYS_CTL_MEM_WRITE_REQ_T writeParam;
         writeParam.addr = address;
         writeParam.len = size;
         count=0;
         while(((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL) && (size))
         {
             status = AppS2wParse_Hex(p, &data);
             if (status != S2W_SUCCESS)
             {
                 return status;
             }
             memcpy(&buff[count*4],(UINT8*)&data,4);
             count++;
             size -= 4;
        }

        writeParam.data = (UINT8*)buff;
        GsnSysCtl_MemWriteReq(&s2wappMainTaskCtxt->sysCtlCtx,&writeParam);
    }
    return S2W_SUCCESS;
}

#endif

UINT8
AppS2wCmd_LogLevelSet(UINT8* ptr)
{
	UINT32 param;
    UINT8 *p, status = S2W_EINVAL;
    p = AppS2wParse_NextParamGet(&ptr);  /*log level */
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &param);
    if(status != GSN_SUCCESS)
    {
        return S2W_EINVAL;
    }
    s2wCurrent.logLevel = (UINT8)param;
    //s2wappMainTaskCtxt->logLevel = (UINT8)param;

    return S2W_SUCCESS;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+BCHKSTRT command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_BattCheckStart(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT32 freq=0;

    status = AppS2wParse_Int(ptr,&freq);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if((freq < 1) || (freq > 100))
    {
        return S2W_EINVAL;
    }
	
    status = AppS2wHal_BattChkStart(freq);
	if(S2W_SUCCESS == status)
		s2wappMainTaskCtxt->battChk.battChckStarted =1;
		
	return status;  	

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+BATTLVLSET command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_BattLvlSet(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT8 *p;
    UINT32 warningLvl =0;
    UINT32 warningFreq = 0;
    UINT32 stdByLvl = 0;

    /* Get warning level*/
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &warningLvl);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    /* Get warning indication freq */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &warningFreq);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    /* Get standby  level*/
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &stdByLvl);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if(warningLvl > 3700 || stdByLvl > 3700)
    {
        return S2W_EINVAL;
    }
    return AppS2wHal_BattChkLvlSet(warningLvl, warningFreq,stdByLvl);

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+BCHK command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_BattCheckSet(UINT8 *ptr)
{
    UINT8 status = S2W_EINVAL;
    UINT32 battParam =0;

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        status = AppS2wHal_BattChkParam(&battParam);
        S2w_Printf("\r\nBatt.Measure Freq:%d",battParam);
        return status;
    }

	status = AppS2wParse_Int(ptr,&battParam);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
    if((battParam < 1) || (battParam > 100))
    {
        return S2W_EINVAL;
    }
	
    if(s2wappMainTaskCtxt->battChk.battChckStarted ==  1)
    {
		AppS2wHal_BattChkSet(battParam);	
		if(S2W_SUCCESS == AppS2wHal_BattChkStop() )
		{
			return AppS2wHal_BattChkStart(battParam);
		}
    }
	return S2W_FAILURE;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+BATTVALGET command
 *   This function get the latest battery value by calling the hal function.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
	
UINT8
AppS2wCmd_BattValueGet(UINT8 *ptr)
{
	UINT16 battValue=0;
	UINT8 status = S2W_EINVAL;
	UINT32 value;
	UINT8 deciPart;

	if (*ptr)
	   return S2W_EINVAL;
	if(s2wappMainTaskCtxt->battChk.battChckStarted == 1)
		status = AppS2wHal_BattChkValueGet(&battValue); 
	if(S2W_SUCCESS == status)
	{
		deciPart = battValue/1000;
		value = battValue - (1000*deciPart);
		S2w_Printf("\r\nBattery Value:%d.%03d V\r\n",deciPart,value);
	}
	return status;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+BCHKSTOP command
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
UINT8
AppS2wCmd_BattCheckStop(UINT8 *ptr)
{
	UINT8 status;
    if (*ptr)
       return S2W_EINVAL;
    else
    {
		if(s2wappMainTaskCtxt->battChk.battChckStarted)
		{

			status=  AppS2wHal_BattChkStop();
			if(S2W_SUCCESS == status)
				s2wappMainTaskCtxt->battChk.battChckStarted = 0;
			return status;
		}
	   	else	   	
		   return S2W_EINVAL;
    }
}



#ifdef GSN_MEM_TRACE
UINT8* moduleName[] = {"Supplicant", "GHS", "GSN"};

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+MEMTRACE Command.
 *   This function display the memory trace information.
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_memTraceGet(UINT8 *ptr)
{
     alloc_data_t * list;
     UINT32 i = 0;
     UINT8 module=0;
     GsnDynAllChk_ResetTrace();
     S2w_Printf("\r\n******  Memory Trace starts Here ******* \r\n");
     S2w_Printf(" \r\n Number Of Allocation    : %d \r\n", GsnDynAllChk_NumOfAlloc());
     S2w_Printf(" Number Of Free          : %d \r\n", GsnDynAllChk_NumOfFree());
     S2w_Printf(" Current Used Memory in bytes   : %d \r\n", GsnDynAllChk_TotalAllocMemSize());
     S2w_Printf(" Peak Memory Usage in bytes     : %d \r\n", GsnDynAllChk_PeakAllocMemSize());

     S2w_Printf("\r\n**The Following Memory Not Freed**\r\n");
     S2w_Printf("Address ,Line , Size ,Module\r\n");
     S2w_Printf("------- ,---- , ----,------  \r\n");
     while(1)
    {

        list = GsnDynAllChk_GetList(&module);
        if(list == NULL)
        {
            break;
        }
        S2w_Printf("%x,%5d,%5d, %s\r\n",(UINT32)list,list->line,list->size, moduleName[module]);
        i++;
    }
    S2w_Printf("\r\nNumber of Allocations to be Freed: %d \r\n",i);
    S2w_Printf("****** Memory Trace Ends Here ****** \r\n");

    return S2W_SUCCESS;
}

#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+WLANSTATS Command.
 *   
 * @param ptr Pointer to the user input string.
 *
 * @return S2W_SUCCESS - operation successful.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_WlanStatsGet(UINT8 *ptr)
{
	UINT8 reset=1;
	UINT8 status;
	UINT32 i;
	GSN_WIF_WLAN_TX_STATS_T *txStats;
	GSN_WIF_WLAN_RX_STATS_T *rxStats;
	
	txStats = gsn_malloc(sizeof(GSN_WIF_WLAN_TX_STATS_T));
	if(NULL == txStats)
		return S2W_FAILURE;

	memset(txStats,0,sizeof(GSN_WIF_WLAN_TX_STATS_T));
    status = GsnWdd_WlanStatsGet(&s2wappMainTaskCtxt->if0.wddCtx,reset,GSN_WDD_WLAN_STAT_TYPE_TX,(INT8*)txStats,sizeof(GSN_WIF_WLAN_TX_STATS_T));
    if(status != S2W_SUCCESS)
    {
      return S2W_FAILURE;
    }
	
    
     /* TX stats */
	S2w_Printf("\r\nitxs=%d\r\nitxto=%d\r\nitxf=%d",txStats->st.itxs,txStats->st.itxto,txStats->st.itxf);
	  
	S2w_Printf("\r\nwep40=%d\r\nwep104=%d\r\ntkip=%d\r\nccmp=%d\r\nunencryp=%d\r\nukencryp=%d",
	 		    txStats->cip_type.wep40,txStats->cip_type.wep104,txStats->cip_type.tkip,txStats->cip_type.ccmp,
	 		    txStats->cip_type.unencryp,txStats->cip_type.ukencryp);

	S2w_Printf("\r\nleg=");
	for(i=0;i<14;i++)
	{
		S2w_Printf("%d,%d:",txStats->dr.leg[i][0],txStats->dr.leg[i][1]);  	
	}                                          
	S2w_Printf("%d,%d",txStats->dr.leg[15][0],txStats->dr.leg[15][1]);	

	S2w_Printf("\r\nht20l=");
	for(i=0;i<GSN_WLAN_MAX_MCS_SUPPORTED;i++)
	{
		S2w_Printf("%d,%d:",txStats->dr.ht20l[i][0],txStats->dr.ht20l[i][1]);		
	}										   
	S2w_Printf("%d,%d",txStats->dr.ht20l[GSN_WLAN_MAX_MCS_SUPPORTED][0],txStats->dr.ht20l[GSN_WLAN_MAX_MCS_SUPPORTED][1]);		

	S2w_Printf("\r\nht40l=");
	for(i=0;i<GSN_WLAN_MAX_MCS_SUPPORTED;i++)
	{
		S2w_Printf("%d,%d:",txStats->dr.ht40l[i][0],txStats->dr.ht40l[i][1]);	
	}										   
	S2w_Printf("%d,%d",txStats->dr.ht40l[GSN_WLAN_MAX_MCS_SUPPORTED][0],txStats->dr.ht40l[GSN_WLAN_MAX_MCS_SUPPORTED][1]);	
	
	S2w_Printf("\r\nht40s=");
	for(i=0;i<(GSN_WLAN_MAX_MCS_SUPPORTED);i++)
	{
		S2w_Printf("%d,%d:",txStats->dr.ht40s[i][0],txStats->dr.ht40s[i][1]);		
	}									
	S2w_Printf("%d,%d",txStats->dr.ht40s[GSN_WLAN_MAX_MCS_SUPPORTED][0],txStats->dr.ht40s[GSN_WLAN_MAX_MCS_SUPPORTED][1]);		

	S2w_Printf("\r\nht20s=");
	for(i=0;i<GSN_WLAN_MAX_MCS_SUPPORTED;i++)
	{
		S2w_Printf("%d,%d:",txStats->dr.ht20s[i][0],txStats->dr.ht20s[i][1]);		
	}										   
	S2w_Printf("%d,%d",txStats->dr.ht20s[GSN_WLAN_MAX_MCS_SUPPORTED][0],txStats->dr.ht20s[GSN_WLAN_MAX_MCS_SUPPORTED][1]);		

	S2w_Printf("\r\nmcs32s=%d,%d",txStats->dr.mcs32s[0],txStats->dr.mcs32s[1]);
	S2w_Printf("\r\nmcs32l=%d,%d",txStats->dr.mcs32l[0],txStats->dr.mcs32l[1]);

	S2w_Printf("\r\nprobersp=%d",txStats->type.probersp);       
	S2w_Printf("\r\nprobereq=%d",txStats->type.probereq);       
	S2w_Printf("\r\nmc_data=%d",txStats->type.mc_data);       
	S2w_Printf("\r\nuc_data=%d",txStats->type.uc_data);       
	S2w_Printf("\r\nqos_uc_data=%d",txStats->type.qos_uc_data);       
	S2w_Printf("\r\nqos_mc_data=%d",txStats->type.qos_mc_data);       
	S2w_Printf("\r\namsdu_uc_data=%d",txStats->type.amsdu_uc_data);       
	S2w_Printf("\r\namsdu_mc_data=%d",txStats->type.amsdu_mc_data);       	
	S2w_Printf("\r\nampdu_uc_data=%d",txStats->type.ampdu_uc_data);       
	S2w_Printf("\r\nampdu_mc_data=%d",txStats->type.ampdu_mc_data);       
	S2w_Printf("\r\noth_mgmt=%d",txStats->type.oth_mgmt);       
	S2w_Printf("\r\noth=%d",txStats->type.oth);       
	S2w_Printf("\r\nctrl=%d",txStats->type.ctrl);       

	S2w_Printf("\r\nretries=%d",txStats->retries); 
	S2w_Printf("\r\nmultiple_retries=%d",txStats->multiple_retries); 
	S2w_Printf("\r\nfragments=%d",txStats->fragments); 

	free(txStats);	
	 /* RX stats */

	rxStats = gsn_malloc(sizeof(GSN_WIF_WLAN_RX_STATS_T));
	if(NULL == rxStats)
		return S2W_FAILURE;
	
	memset(rxStats,0,sizeof(GSN_WIF_WLAN_RX_STATS_T));
	status = GsnWdd_WlanStatsGet(&s2wappMainTaskCtxt->if0.wddCtx,reset,GSN_WDD_WLAN_STAT_TYPE_RX,(INT8*)rxStats,sizeof(GSN_WIF_WLAN_RX_STATS_T));
	if(status != S2W_SUCCESS)
	{
	  return S2W_FAILURE;
	}
	 
	S2w_Printf("\r\nirx0=%d",rxStats->st.irx0);        
	S2w_Printf("\r\nirxf=%d",rxStats->st.irxf);                
	S2w_Printf("\r\nirxs=%d",rxStats->st.irxs);                
	S2w_Printf("\r\nirxd=%d",rxStats->st.irxd);                
	S2w_Printf("\r\nirxmf=%d",rxStats->st.irxmf);               
	S2w_Printf("\r\nirxkf=%d",rxStats->st.irxkf);               
	S2w_Printf("\r\nirxicvf=%d",rxStats->st.irxicvf);             
	S2w_Printf("\r\nirxtkipicvf=%d",rxStats->st.irxtkipicvf);         
	S2w_Printf("\r\nrxtkipmf=%d",rxStats->st.irxtkipmf);          
	S2w_Printf("\r\nrxrf=%d",rxStats->st.irxrf);               
	S2w_Printf("\r\nrxtkiprf=%d",rxStats->st.irxtkiprf);           
	S2w_Printf("\r\nrxdip=%d",rxStats->st.irxdip);              
	S2w_Printf("\r\nrxdf=%d",rxStats->st.irxdf);               
	S2w_Printf("\r\nrxex=%d",rxStats->st.irxex);               

	S2w_Printf("wep40=%d\r\nwep104=%d\r\ntkip=%d\r\nccmp:%d\r\nunencryp=%d\r\nukencryp=%d",
			 rxStats->cip_type.wep40,rxStats->cip_type.wep104,rxStats->cip_type.tkip,rxStats->cip_type.ccmp,
			 rxStats->cip_type.unencryp,rxStats->cip_type.ukencryp);

	S2w_Printf("\r\nleg=");
	for(i=0;i<14;i++)
	{
		S2w_Printf("%d,%d:",rxStats->dr.leg[i][0],rxStats->dr.leg[i][1]);	 
	}											
	S2w_Printf("%d,%d",rxStats->dr.leg[15][0],rxStats->dr.leg[15][1]);	 

	S2w_Printf("\r\nht20l=");
	for(i=0;i<(GSN_WLAN_MAX_MCS_SUPPORTED);i++)
	{
		S2w_Printf("%d,%d:",rxStats->dr.ht20l[i][0],rxStats->dr.ht20l[i][1]);	 
	}											
	S2w_Printf("%d,%d",rxStats->dr.ht20l[GSN_WLAN_MAX_MCS_SUPPORTED][0],rxStats->dr.ht20l[GSN_WLAN_MAX_MCS_SUPPORTED][1]);	 

	S2w_Printf("\r\nht40l=");
	for(i=0;i<(GSN_WLAN_MAX_MCS_SUPPORTED);i++)
	{
		S2w_Printf("%d,%d:",rxStats->dr.ht40l[i][0],rxStats->dr.ht40l[i][1]); 
	}											
	S2w_Printf("%d,%d",rxStats->dr.ht40l[GSN_WLAN_MAX_MCS_SUPPORTED][0],rxStats->dr.ht40l[GSN_WLAN_MAX_MCS_SUPPORTED][1]); 

	S2w_Printf("\r\nht40s=");
	for(i=0;i<(GSN_WLAN_MAX_MCS_SUPPORTED);i++)
	{
		S2w_Printf("%d,%d:",rxStats->dr.ht40s[i][0],rxStats->dr.ht40s[i][1]);		 
	}				
	S2w_Printf("%d,%d",rxStats->dr.ht40s[GSN_WLAN_MAX_MCS_SUPPORTED],rxStats->dr.ht40s[GSN_WLAN_MAX_MCS_SUPPORTED][1]);		 
	
	S2w_Printf("\r\nht20s=");
	for(i=0;i<(GSN_WLAN_MAX_MCS_SUPPORTED);i++)
	{
		S2w_Printf("%d,%d:",rxStats->dr.ht20s[i][0],rxStats->dr.ht20s[i][1]) ;	 
	}	
	S2w_Printf("%d,%d:",rxStats->dr.ht20s[GSN_WLAN_MAX_MCS_SUPPORTED][0],rxStats->dr.ht20s[GSN_WLAN_MAX_MCS_SUPPORTED][1]) ;	 
	
	S2w_Printf("\r\nmcs32s=%d,%d",rxStats->dr.mcs32s[0],rxStats->dr.mcs32s[1]);
	S2w_Printf("\r\nmcs32l=%d,%d",rxStats->dr.mcs32l[0],rxStats->dr.mcs32l[1]);

	S2w_Printf("\r\nbcn=%d",rxStats->type.bcn);       
	S2w_Printf("\r\nrts=%d",rxStats->type.rts);       
	S2w_Printf("\r\ncts=%d",rxStats->type.cts);       
	S2w_Printf("\r\nack=%d",rxStats->type.ack);       
	S2w_Printf("\r\nprobersp=%d",rxStats->type.probersp);       
	S2w_Printf("\r\nprobereq=%d",rxStats->type.probereq);     
	S2w_Printf("\r\natim=%d",rxStats->type.atim);
	S2w_Printf("\r\ncfend=%d",rxStats->type.cfend);
	S2w_Printf("\r\nback=%d",rxStats->type.back);
	S2w_Printf("\r\nbar=%d",rxStats->type.bar);	
	S2w_Printf("\r\nmc_data=%d",rxStats->type.mc_data);       
	S2w_Printf("\r\nuc_data=%d",rxStats->type.uc_data);       
	S2w_Printf("\r\noth_data=%d",rxStats->type.oth_data);
	S2w_Printf("\r\nqos_uc_data=%d",rxStats->type.qos_uc_data);     
	S2w_Printf("\r\nqos_mc_data=%d",rxStats->type.qos_mc_data);      
	S2w_Printf("\r\nqos_oth_data=%d",rxStats->type.qos_oth_data);     	
	S2w_Printf("\r\namsdu_uc_data=%d",rxStats->type.amsdu_uc_data);       
	S2w_Printf("\r\namsdu_mc_data=%d",rxStats->type.amsdu_mc_data);       	
	S2w_Printf("\r\namsdu_oth_data=%d",rxStats->type.amsdu_oth_data);     
	S2w_Printf("\r\noth_mgmt=%d",rxStats->type.oth_mgmt);       
	S2w_Printf("\r\noth=%d",rxStats->type.oth_ctrl);       
	S2w_Printf("\r\nctrl=%d",txStats->type.ctrl);       
	free(rxStats);	
	return S2W_SUCCESS;
	  
}
#if   defined(S2W_FS_SPI_ENABLE) || defined(S2W_FS_SPI_HI_ENABLE)
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the AT+SPI Command.
 * @param ptr Pointer to the user input string.
 * @return status.
 ******************************************************************/
PUBLIC UINT8
AppS2wCmd_SpiConfig(UINT8 *ptr)
{

   UINT8   clockPolarity;    /**< SPI clock polarity */
   UINT8   clockPhase;       /**< SPI clock phase    */
    UINT8   status = S2W_SUCCESS;
   UINT8   *p=0;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Boolean(p, &clockPolarity);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    p = AppS2wParse_NextParamGet(&ptr);
   if (!p)
    {
        return S2W_EINVAL;
    }

    if (p)
    {
        if (*p != '\0')
        {
            status = AppS2wParse_Boolean(p, &clockPhase);
            if (status != S2W_SUCCESS)
            {
                return status;
            }
        }
      else
      {
          return S2W_EINVAL;
      }
    }


   if((clockPhase == (UINT8)(s2wCurrent.serialPortConf.conf.spi.clockPhase)) &&
      (clockPolarity == (UINT8)(s2wCurrent.serialPortConf.conf.spi.clockPolarity)))
   {/* already configured */
      return S2W_SUCCESS;
   }

   if(clockPhase != (UINT8)(s2wCurrent.serialPortConf.conf.spi.clockPhase))
   {
      /*Set the clock phase for data change on output */
      s2wCurrent.serialPortConf.conf.spi.clockPhase = (GSN_SPI_CLOCKPHASE_T)clockPhase ;
   }

   if(clockPolarity != (UINT8)(s2wCurrent.serialPortConf.conf.spi.clockPolarity))
   {
      /*Set the new clock polarity */
      s2wCurrent.serialPortConf.conf.spi.clockPolarity = (GSN_SPI_CLOCKPOLARITY_T)clockPolarity;

   }

   return status;

}
#endif



UINT8
AppS2wCmd_WlanOtpRead (UINT8 *ptr)
{
	UINT8 status;;
	UINT32 temp = 0;
	UINT8 *p;
        UINT8 otpGrpId, otpGrpVer;
	UINT8 data[255] ={0};
        UINT16 dataLen=255;
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &temp);
	if ((status != S2W_SUCCESS) ||(temp > 255))
	{
		return S2W_EINVAL;
	}
	otpGrpId = temp;

    // version
    otpGrpVer = GSN_OTP_MM_VER_UNKNOWN ;
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);

    if((p) && (*p != '\0'))
    {
	status = AppS2wParse_Int(p, &temp);
	if ((status != S2W_SUCCESS) ||(temp > 255))
	{
		    return S2W_EINVAL;
	}
	otpGrpVer = temp;
	}

    if(GSN_SUCCESS != GsnSysCtl_OtpReadReq(&s2wappMainTaskCtxt->sysCtlCtx,otpGrpId,otpGrpVer,
                                  data,&dataLen))
    {
        return S2W_FAILURE;
    }
    else
    {
		UINT8 k=0;
		for(k=0;(k<(dataLen/GSN_OTP_NUM_BYTES_PER_WORD ));k++)
		{
	UINT8 i =0;
            S2w_Printf("\r\n0x");
            for(i=(8+k*8);i>(k*8);i--)
        {
               S2w_Printf("%02x",data[i-1]);
		    }
	}
    }
    return status;
}

UINT8
AppS2wCmd_AppOtpRead (UINT8 *ptr)
{
	UINT8 status;;
	UINT32 temp = 0;
	UINT8 *p;
    UINT8 otpGrpId, otpGrpVer;
	UINT8 data[255] ={0};
    UINT16 dataLen=0;

    //id
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &temp);
	if ((status != S2W_SUCCESS) ||(temp > 255))
	{
		return S2W_EINVAL;
	}
	otpGrpId = temp;

    // version
    otpGrpVer = GSN_OTP_MM_VER_UNKNOWN ;
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);

    if((p) && (*p != '\0'))
    {
	status = AppS2wParse_Int(p, &temp);
	if ((status != S2W_SUCCESS) ||(temp > 255))
	{
		    return S2W_EINVAL;
	}
	otpGrpVer = temp;
	}
    if(GSN_SUCCESS != GsnOtpMm_Read(otpGrpId,otpGrpVer,
                                  &dataLen, data))
    {
        return S2W_FAILURE;
    }
    else
    {
        UINT8 k=0;
        for(k=0;(k<(dataLen/GSN_OTP_NUM_BYTES_PER_WORD ));k++)
		{
	UINT8 i =0;
            S2w_Printf("\r\n0x");
            for(i=(8+k*8);i>(k*8);i--)
        {
               S2w_Printf("%02x",data[i-1]);
	        }
	}
    }
    return status;
}



UINT8
AppS2wCmd_SetAssocTimeout(UINT8 *ptr)
{
	UINT32 temp = 0, timeout = 0;
	UINT8 *p;
	UINT8 status;
	p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;
	}
	status = AppS2wParse_Int(p, &temp);
	if(status != S2W_SUCCESS)
	{
		return S2W_EINVAL;
	}
	if(1 == temp)
	{
		p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
		if(!p)
		{
			return S2W_EINVAL;
		}
		status = AppS2wParse_Int(p, &timeout);
		if(status != S2W_SUCCESS)
		{
			return S2W_EINVAL;
		}
	}
	else if(0 != temp)
	{
		return S2W_EINVAL;
	}
    s2wCurrent.assocConf.enableAssocConf = temp;
    s2wCurrent.assocConf.assocTimeout = timeout;

    return S2W_SUCCESS;

}

UINT8
AppS2wCmd_HwCryptoEn(UINT8 *ptr)
{
    UINT8 *p, enable, status;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Boolean(p, &enable);
    if(status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }

    if(enable)
    {
        GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
    }
    else
    {
        GsnHeIf_DriverSuspend();
    }
    return S2W_SUCCESS;
}

UINT8
AppS2wCmd_GratArpSend(UINT8 *ptr)
{
   
    nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,NULL);
    return S2W_SUCCESS;
}

#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)

S2W_SSL_CONF_T s2wSslConf = {0};

UINT8
AppS2wCmd_SslConfig(UINT8 *ptr)
{
    UINT8 *p, status;
    UINT32 temp = 0, bufLen = 0;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
	status = AppS2wParse_Int(p, &temp);
	if(status != S2W_SUCCESS)
	{
		return S2W_EINVAL;
	}
	if(1 == temp)
	{
		p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
		if(!p)
		{
			return S2W_EINVAL;
		}
		status = AppS2wParse_Int(p, &bufLen);
		if(status != S2W_SUCCESS)
		{
			return S2W_EINVAL;
		}
		s2wSslConf.dnsBufferLen = bufLen;

	}
    return S2W_SUCCESS;
}
#endif

static char _pCACert[] = "-----BEGIN CERTIFICATE-----\n\
MIIDoDCCAogCCQCzzVQyLqdAvzANBgkqhkiG9w0BAQsFADCBkTELMAkGA1UEBhMC\n\
S1IxDjAMBgNVBAgTBVNlb3VsMQ8wDQYDVQQHEwZKb25ncm8xEjAQBgNVBAoTCURh\n\
bGl3b3JrczEMMAoGA1UECxMDSU9UMRkwFwYDVQQDExBjYS5kYWxpd29ya3MubmV0\n\
MSQwIgYJKoZIhvcNAQkBFhVjb250YWN0QGRhbGl3b3Jrcy5uZXQwHhcNMTMwODMx\n\
MTgwMTQ4WhcNNDEwMTE1MTgwMTQ4WjCBkTELMAkGA1UEBhMCS1IxDjAMBgNVBAgT\n\
BVNlb3VsMQ8wDQYDVQQHEwZKb25ncm8xEjAQBgNVBAoTCURhbGl3b3JrczEMMAoG\n\
A1UECxMDSU9UMRkwFwYDVQQDExBjYS5kYWxpd29ya3MubmV0MSQwIgYJKoZIhvcN\n\
AQkBFhVjb250YWN0QGRhbGl3b3Jrcy5uZXQwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n\
DwAwggEKAoIBAQDQFsofdqVk3/srSNCnyqQHmlKkfrtXdBJ1VenDT/HU564wGjyl\n\
Ku++Wmh8/KzDkHdDlsqKA4TPhyI3baJauYHTSyVpRxQ1khCSbCdEG1KMD4YggYnw\n\
JIanrktOHDgZrwthDRqTHy2d7TAJvHnVjXhLtU9yeQafO0fByAXUYVYZ9fFa5Wbc\n\
KByd/TWD7/8lKa5R0WIpzpfwWwwmB/dAjp5defr2xUHJbdBWndSsTfbi3DxfP+Nl\n\
4iAS3R1Zp3DjYyC4Fq3WpV7uQuo5Z7k08GY9v80nAID/P1sJKJlDCBLLweFf7fJl\n\
F4jUxpbELtJMNXHwtRjMBOfuLMVD+HkJ0O31AgMBAAEwDQYJKoZIhvcNAQELBQAD\n\
ggEBACqkd3D3rgIgTQ9RKoiDk4V44xxvD4f4wYwCkNxnnBON8AeoN4gVEHqtvrsk\n\
4RH95wtuAde0+thcokYu7qaWu0AuPRRZ7kyMcoGLDm0Beatma6ZW/Kv4DoEHo2Zz\n\
uTILyWZ+jProaNGjeLZztZ01KrOWuVM2SZbQaC6eK5jPFtTHbkf+lR9FHE4rMDbj\n\
HbT1BmjuHrGabVOLOOLesz3v+kVQwV0Y/3/3uLWL5j4xaFeanTRJfdTlgGA2m9o8\n\
B1v82hqLoYNidhAUPGfH+kuJifH9S5cx120RQXIUMVOb8xu0WJ1dfxiL4dkG0Rcl\n\
VE8GlZykSVNxiFDmX5S0rIVSPso=\n\
-----END CERTIFICATE-----\n";

UINT8
AppS2wCmd_MqttStart(UINT8 *ptr)
{
    if (S2wCert_FlashFileLoad("ca-cert") == -1)
    {
        INT32 status;
        F_FILE *certFile;

        FTW_TRACE("CA Certication not found.\n");
	    status = f_mkdir("certs");
		if(status != F_NO_ERROR || status != F_ERR_DUPLICATED )
		{
		}
        else
        {
            FTW_TRACE("Can't creat dir(certs) = %d\n", status);
        }
        
        certFile = f_open("certs/ca-cert", "w");
        if(certFile == NULL)
        {
            FTW_TRACE("Can't create ca-cert file\n");
            return S2W_FAILURE;
        }

        f_write(_pCACert, 1, strlen(_pCACert), certFile);
        f_close(certFile);
    }

    if (S2wCert_FlashFileLoad("ca-cert") != -1)
    {
        FTW_TRACE("CA Cert Loaded\n");
    }

    FTW_CONFIG_init("ftw.cfg");

    if((FTW_CONFIG_getNet() == NULL) || (FTW_CONFIG_getMQTT() == NULL))
    {
        return  S2W_FAILURE;
    }
 
    FTW_MODULE_TRACE_ON(FTW_DBG_MODULE_NET);
    FTW_MODULE_TRACE_ON(FTW_DBG_MODULE_MQTT);
    
    FTW_NET_init(FTW_CONFIG_getNet());
    FTW_MQTT_init(FTW_CONFIG_getMQTT());
    
    return  S2W_SUCCESS;
}

