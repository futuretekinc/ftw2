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
* $RCSfile: s2w_process.c,v $
*
* Description : s2w command processor file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "gsn_includes.h"
#include "app_defines_builder.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "hal/s2w_net.h"
#include "hal/s2w_timer.h"
#include "parser/s2w_parse.h"
#include "ftw_config.h"
#include "parser/s2w_command.h"
#include "main/app_main_ctx.h"
#include "config/app_resource_config.h"
#include "config/app_ncm_config.h"
#include "app_events.h"
#include "ftw_config.h"


#include "config/app_stat_config.h"
#include "app_rtc_mem.h"
#include "parser/s2w_process.h"
#include "clk_tune/app_clk_tune.h"

#include "ftw_hal.h"
#include "ftw_spi.h"
#include "ftw_serial.h"
#include "ftw_net.h"
#include "ftw_httpd.h"
      
UINT8 s2wNRAWState = FTW_NRAW_NONE;

/**
 ******************************************************************************
 * @file s2w_process.c
 * @brief S2W Application command process routines.
 *      This file contains the s2w application specific implimentation for
 *      command processing.
******************************************************************************/


/*****************************************************************************
  *  Public Variables
  *****************************************************************************/

/** Current state of the serial handler
 */
enum FTW_STATE s2wState;
#ifdef FTW_PING_TRACE
extern INT32 s2wPingStarted;
extern INT32 s2wTrcStarted;
#endif
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
FTW_LINK_STATE_T s2wLinkState ;
#ifdef FTW_HTTPC_SUPPORT
extern GSN_HTTPC_CONF_INFO_T httpConfInfo;
#endif
extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;
extern UINT8 frameTransmissionType;
#ifdef FTW_UNASSOC_TXRX_SUPPORT
extern FTW_UNSOLICITED_FRAME_T frame;
#endif
//extern GSN_WIF_MM_STARTASYNCHRONOUSTX_FRAME_T pFrame;
static UINT8 hCid=INVALID_CID;
//#define EXTFLASH_DRIVER_TEST
//#define FTW_FILE_SYS

/** Number of bytes transmitted */
UINT32 s2wTxBytes;

/** Number of bytes received */
UINT32 s2wRxBytes;

extern FTW_CID_T s2wCidList[];

extern UINT8 macArray[];
extern FTW_PROFILE_PARAMS_T profile_params;

extern FTW_WLANINFO_T current_wlan_info;
extern void nx_dns_retry_count_set(NX_DNS *dns_ptr,UINT retries);

/**
 * Indicates that an auto connected connection is present.  If this is set, no
 * other connections can be created, until a disconnect (which will unset
 * this).
 */
#define FTW_AUTO_CONN_DATA_PIPE 0x01
#define FTW_AUTO_CONN_DATA_L4_BREAK 0x02
#define FTW_AUTO_CONN_DATA_L3_BREAK 0x04
#define FTW_AUTO_CONN_DATA_L2_BREAK 0x08

UINT8 s2wIsAutoconnected = 0;
UINT8 s2wAutoConnState=0;

/** Current configuration settings */
extern FTW_PROFILE_T s2wCurrent;

/** Parameters read from and to be written to flash */
FTW_FLASH_PARAMS_T *s2wFlashParams;

/** Connection the current data transfer is taking place on */
UINT8 curCid = INVALID_CID;

UINT16 lengthSpecialCmd = 0;
UINT8 lengthConvertIndex = 0;

extern UINT32 S2wL3Wait;


/*****************************************************************************
  *  Private Variables
  *****************************************************************************/

#define FTW_DECLARE_INT_FLAGS(flags) UV_VALUE flags
#if 0
#pragma ghs section bss=".bss_NoZeroInit"
PRIVATE UINT8 S2wSendTaskStack[APP_CFG_NET_TX_STACK_SIZE];
#pragma ghs section bss=default

/** Queue for the receive task */
PRIVATE GH_QUEUE s2wSendQueue;
PRIVATE GH_QUEUE_AREA_DEFINE(s2wSendQueueBuffer, GH_MSG_0_WORDS,
                             APP_CFG_NET_TX_MAX_MSG_IN_MBOX);
#endif
/**
 * Timeout for the +++ escape sequence in auto-connect mode.  Unit is 10ms.
 */
#define FTW_AUTO_ESC_TIMEOUT 100

/** Destination address for the current data transfer (only for UDP servers) */
PRIVATE FTW_IPADDR_T destAddr;

#ifdef FTW_IPv6_SUPPORT
PRIVATE FTW_IPv6ADDR_T destIpv6Addr;
#endif
/** Destination port for the current data transfer (only for UDP servers) */
PRIVATE UINT16 destPort;

/** Timer for Nagle algorithm */
PRIVATE FTW_TIMER_T nagleTimer;
FTW_TIMER_T auto_esc_timer;

/** Timer for auto connect failure */
PRIVATE FTW_TIMER_T acTimer;

#ifdef FTW_NCM_SUPPORT_ENABLE
FTW_TIMER_T acNcmTimer;
#endif //NCM_SUPPORT_ENABLE

/** Buffer for data to be transmitted */
#ifdef IP2WIFI
__no_init PRIVATE UINT8 dataBuffer[FTW_DATABUF_SIZE];
#else
__no_init PRIVATE UINT8 dataBuffer[FTW_DATABUF_SIZE-200];
#endif

/** Index into dataBuffer to indicate used amount */
PRIVATE UINT32 dataIndex=0;


/** Buffer for raw data len */
__no_init PRIVATE UINT8 rawLenBuff[20];
PRIVATE UINT32 rawLenIndex=0;
PRIVATE UINT32 rawLen=0;
#ifdef FTW_IP2WIFI_SUPPORT
PRIVATE UINT32 rawTotalIndex=0;
PRIVATE UINT32 rawColon =0;
#endif

GSN_OSAL_SEM_T dSendSem;

/** unsolicited frame*/

//PRIVATE UINT8 unsolFrameLenBuff[2];
//PRIVATE UINT32 unFramIndex=0;
//PRIVATE UINT16 unFramLen=0;
//PRIVATE UINT32 unSolicitesTotalIndex =0;

#ifdef FTW_RFTEST
PRIVATE UINT32 asyncFramIndex=0;
//PRIVATE UINT16 asyncFramLen=0;

#endif

#ifdef FTW_COAP_SUPPORT
	extern UINT8 AppS2wHal_CoapContentDataGet( UINT8 hCid);
#endif

/**
 * @brief Array which contains the status messages.
 */
PRIVATE const char *FTW_StatusList[] =
{
    "OK",                   /* FTW_SUCCESS */
    "ERROR",                /* FTW_FAILURE */
    "ERROR: INVALID INPUT",         /* FTW_EINVAL */
    "ERROR: SOCKET FAILURE",        /* FTW_SOCKFAILURE */
    "ERROR: NO CID",                /* FTW_ENCID */
    "ERROR: INVALID CID",           /* FTW_EBADCID */
    "ERROR: NOT SUPPORTED",         /* FTW_ENOTSUP */
    "\r\nCONNECT %x\r\n",           /* FTW_CON_SUCCESS */
    "\r\nDISCONNECT %x\r\n",        /* FTW_ECIDCLOSE */
    "DISASSOCIATED",                /* FTW_LINK_LOST_EVT */
    "\r\nDisassociation Event\r\n", /* FTW_DISASSO_EVT */
    "\n\rOut of StandBy-Timer\r\n", /* FTW_STBY_TMR_EVT */
    "\n\rOut of StandBy-Alarm\r\n", /* FTW_STBY_ALM_EVT */
    "\r\nOut of Deep Sleep\r\n",    /* FTW_DPSLEEP_EVT */
    "\r\nUnExpected Warm Boot(Possibly Low Battery)\r\n",
                                   /* FTW_BOOT_UNEXPECTED_EVT */
    "ERROR: IP CONFIG FAIL",       /* FTW_ENOIP */
#ifdef FTW_IP2WIFI_SUPPORT
    "Ip2WiFi APP",
    "Ip2WiFi APP-Ext.PA",
#else
    "Serial2WiFi APP",
    "Serial2WiFi APP-Ext.PA",
#endif
    "NWCONN-SUCCESS",
    "IP CONFIG-NEW IP",
	"\n\rAPP Reset-Wlan-Wd\r\n",
	"\n\rAPP Reset-App-Wd\r\n",
	"\n\rAPP Reset-Wlan SW Reset\r\n",
	"APP Reset-APP SW Reset",
	"\n\rAPP Reset-Wlan Except\r\n",
	"APP Reset External Flash FW-UP-SUCCESS",
	"\n\rSerial2WiFi APP Unknown boot\r\n",
	"\r\nExternal Reset Boot\r\n",
	"\n\nHW Crypto Boot\r\n",
	"\n\rJTAG Reset Boot\r\n",
	"\n\rBrownout Reset Boot\r\n",
    "\n\rIP Conflict Detected\r\n",
    " Registration Failed for RR: ",
	" Registration Success!! for RR: ",
};

/**
 * @brief Array which contains the status messages for async message.
 */

PRIVATE const char *FTW_AsyncStatusList[] =
{
    "ERROR: SOCKET FAILURE",        /* FTW_ASYNC_SOCKFAILURE-->0 */
    "CONNECT",           /* FTW_ASYNC_CON_SUCCESS -->1 */
    "DISCONNECT",        /* FTW_ASYNC_ECIDCLOSE -->2 */
    "Disassociation Event", /* FTW_ASYNC_DISASSO_EVT -->3 */
    "Out of StandBy-Timer", /* FTW_ASYNC_STBY_TMR_EVT -->4 */
    "Out of StandBy-Alarm", /* FTW_ASYNC_STBY_ALM_EVT -->5*/
    "Out of Deep Sleep",    /* FTW_ASYNC_DPSLEEP_EVT  -->6*/
    "UnExpected Warm Boot(Possibly Low Battery)",
                                   /* FTW_BOOT_UNEXPECTED_EVT -->7 */
    "ERROR: IP CONFIG FAIL",   /* FTW_ASYNC_DHCP_FAIL_EVT -->8 */
#ifdef FTW_IP2WIFI_SUPPORT
    "Ip2WiFi APP",
    "Ip2WiFi APP-Ext.PA",
#else
    "Serial2WiFi APP",
    "Serial2WiFi APP-Ext.PA",
#endif
    "ERROR"  ,    // error msg
    "NWCONN-SUCCESS",
    "IP CONFIG-NEW IP",
  	"APP Reset-Wlan-Wd" ,
  	"APP Reset-App-Wd" ,
  	"APP Reset-Wlan SW Reset" ,
   	"APP Reset-APP SW Reset" ,
  	"APP Reset-Wlan Except" ,
  	"APP Reset External Flash FW-UP-SUCCESS" ,
  	"Serial2WiFi APP Unknown boot" ,
  	"External Reset Boot" ,
  	"HW Crypto Boot" ,
  	"JTAG Reset Boot" ,
  	"Brownout Reset Boot",
        "IP Conflict Detected",
    " Registration Failed for RR: ",
    " Registration Success!! for RR: ",
};


extern FTW_USR_BUF_T s2wUserBuf;
/**
 * @brief Macro to calculate the table size.
 */
#define    S_STATUS_TBL    (sizeof(FTW_StatusList) / sizeof(FTW_StatusList[0]))


/*****************************************************************************
  *  Private functions
  *****************************************************************************/
PRIVATE INLINE INT32
AppS2w_VPrintf(const INT8 *format, va_list ap);
#ifdef FTW_DUAL_INTERFACE_SUPPORT
PRIVATE INLINE INT32
AppS2w_VPrintf1(const INT8 *format, va_list ap);
#endif
PRIVATE VOID
AppS2w_AcTimeoutHandler(VOID *data);
PRIVATE VOID
AppS2w_AcNcmTimeoutHandler(VOID *data);

PRIVATE UINT8
AppS2w_Connect(FTW_NETDATA_T *peer_data,UINT16 UdpSrcPort, UINT8 *cid);

#ifndef IOT_APP_ENABLE
PRIVATE VOID
AppS2w_CommandCharProcess(UINT8 ch);
#endif  /* IOT_APP_ENABLE */

PUBLIC UINT8
AppS2w_DataBufferTransmit(VOID);

PUBLIC UINT8
AppS2w_DataTransmit(UINT8 *data);


PRIVATE VOID
AppS2w_DataCharProcess(UINT8 ch);

PRIVATE VOID
AppS2w_AutoEscTimeout(VOID *data);

PUBLIC UINT8
AppS2w_CidValidate(UINT8 ch);

PRIVATE VOID
AppS2w_FailEscParse(VOID);

PUBLIC UINT32
AppS2wCertificateData(UINT8 ch1);
PRIVATE VOID
AppS2w_NagleExpiry(VOID *data);
#ifdef FTW_IP2WIFI_SUPPORT
PRIVATE UINT8
S2w_RawDataBufferTransmit(VOID);
#endif
/**
 * @brief Process the incoming raw data character.
 * @param ch incoming data character
 */

PRIVATE VOID
S2w_RawLenCharProcess(UINT8 ch)
{

    rawLenBuff[rawLenIndex] = ch;
    rawLenIndex++;

}

PRIVATE UINT32
S2w_RawLenCalculate()
{
    UINT32 len = 0;

    rawLenBuff[rawLenIndex] = '\0';
    /* parse the ascii to get the len as integer */
    AppS2wParse_Int(rawLenBuff,&len);
    rawLenIndex = 0;
    return len;
}

#ifdef FTW_RFTEST
PRIVATE VOID
S2w_asyncCharProcess(UINT8 ch);
#endif
#ifdef IOT_APP_ENABLE
PRIVATE VOID AppIot_CommandCharProcess(UINT8 ch);
#endif  /* IOT_APP_ENABLE */

/*****************************************************************************
  *  Public functions
  *****************************************************************************/


/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Formatted print function to print the message on the serial port.
 * @param format- IN  Format string.
 * @param -  IN Variable arguments.
 * @retval Total number of bytes printed.
 ************************************************************************/
PUBLIC INT32
S2w_Printf(const char *format, ...)
{
    va_list args;
    INT32 len;

    va_start(args, format);
    len = AppS2w_VPrintf(format, args);
    va_end(args);
    return len;
}

#ifdef FTW_DUAL_INTERFACE_SUPPORT
PUBLIC INT32
S2w_Printf1(const char *format, ...)
{

    va_list args;
    INT32 len;

    va_start(args, format);
    len = AppS2w_VPrintf1(format, args);
    va_end(args);

    return len;
}
#endif


/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Auto connection timeout function.
 *
 * @retval none.
 ************************************************************************/

PRIVATE VOID
AppS2w_AcTimeoutHandler(void *data)
{
    //acTimedOut = 1;
}

#ifdef FTW_NCM_SUPPORT_ENABLE

PRIVATE VOID
AppS2w_AcNcmTimeoutHandler(void *data)
{
    UINT32 message = APP_EVENT_NCM_L4CONNECT;
    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
}


#endif


/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Loads settings from the specified profile.
 *     This function will first disconnect and close all network connections,
 *     and then load the settings from the specified profile.
 * @param profileNum - IN Profile to load from.  Either 0 or 1.
 * @retval none.
 ************************************************************************/
VOID AppS2w_SetWlanDfltParams(UINT8 profileNum)
{
    UINT32 bootReason;
    UINT8 macAddr[6];

    /* disassociate if connected */
    if (s2wLinkState == FTW_LINK_STATE_CONNECTED)
    {			  
        FTW_NET_disassociate(0);
    }

    bootReason = GSN_BOOT_REASON_GET();
    
    if(s2wCurrent.mode == FTW_WLANDATA_MODE_INFRA)
    {
       S2w_macAddrRTCGet(macAddr);
	}
	else
	{
		memcpy(macAddr,s2wCurrent.lmtdApConf.macAddr.array, 6);
	}
	
	if( GSN_WIF_WLAN_NW_TYPE_STA == s2wCurrent.mode ||
		GSN_WIF_WLAN_NW_TYPE_AP == s2wCurrent.mode  ||
		FTW_WLANDATA_MODE_PROV_AP == s2wCurrent.mode )           
	//!( defined FTW_ISOTX_SUPPORT  && defined FTW_15DOT4_SUPPORT ))
	{
    	if(bootReason != GSN_WIF_SYS_BOOT_NORMAL_BOOT)
    	{
		    /* set MAC address from flash params */
    		 FTW_NET_macAddrSet(macAddr, TRUE);
    

		    /* set the Tx power
		     */
		     if(s2wCurrent.txPower < 16) // the max value allowed is 0-15
		     {
				 GSN_WDD_TX_POW_SET_PARAM_T param;
				 int i=0;
				 for(i=0;i<5;i++)
				 {
					 param.txPow[i]=s2wCurrent.txPower;
				 }
				 GsnWdd_TxPowerSet(&s2wappMainTaskCtxt->if0.wddCtx, &param);
			 }

			 /* set the retry count    */
	
    		GsnWdd_TxNumRetrySet(&s2wappMainTaskCtxt->if0.wddCtx, s2wCurrent.retryCount);

		    /* configure the power save */			
			GsnWdd_PsCfgBeaconWaitDurSet(&s2wappMainTaskCtxt->if0.wddCtx, 10);			
		    FTW_PS_modeSave();
			if(s2wCurrent.powerSave == 1)
			{
                FTW_PS_modeSet(s2wCurrent.powerSave);
			}
			else
				AppS2wHal_IeeePSConfig(s2wCurrent.ieeePScfgEn);
			/* configure the active radio mode 	*/
		    AppS2wHal_RadioModeConfig(s2wCurrent.radio);
			FTW_PS_pollIntervelSet(FTW_DEFAULT_KEEPALIVE_INTERVAL);
			AppS2wHal_McastRecvSet(FTW_DEFAULT_MCAST_RX);
		}
		else
		{
	    	FTW_NET_macAddrSet(macAddr, FALSE);
		}

	    /* set the min and max scan time msec     */
    	GsnWdd_ScanParamSet(&s2wappMainTaskCtxt->if0.wddCtx,s2wCurrent.minScanTime,
                        s2wCurrent.registers[FTW_REG_SCAN_TIME],0);
	}
	//#endif
}
/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Loads settings from the specified profile.
 *     This function will first disconnect and close all network connections,
 *     and then load the settings from the specified profile.
 * @param profileNum - IN Profile to load from.  Either 0 or 1.
 * @retval none.
 ************************************************************************/
PUBLIC VOID
AppS2wProcess_LoadProfile(UINT8 profileNum)
{
    FTW_PROFILE_T *profile = &s2wFlashParams->profile[profileNum];

    s2wIsAutoconnected = 0;

    /* close all cids
     */
    AppS2wHal_NetCloseAll(0);

    memcpy(&s2wCurrent, profile, sizeof(s2wCurrent));

    /* configure the ip parameters
     */
    AppS2wHal_NetworkConfig(&s2wCurrent.netConf);
    
    
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Load the Serial2WiFi default configurations to the global structure.
 * @param params  - Pointer to the Global settings structure, which will be
 *                  loaded with the configurations.
 * @retval VOID - none
 ************************************************************************/
PUBLIC VOID
AppS2wProcess_DefaulConfigtLoad(FTW_FLASH_PARAMS_T *params)
{
    UINT32 temp;
    FTW_PROFILE_T *profile;
    FTW_WLANDATA_T *wlan;
    FTW_NETDATA_T *net;
    FTW_NETCONF_T *netconf;
    FTW_SERIAL_PORT_CONF_T *ptSerialPort;
	UINT32 dnsSrvrIp;
    FTW_SECURITY_T *sec;
	UINT8 mac[6];


    profile = &params->profile[0];
    memset(profile, 0, sizeof(FTW_PROFILE_T));

    wlan = &profile->autoWlandata;
    net = &profile->autoNetdata;
    netconf = &profile->netConf;

   ptSerialPort = &(profile->serialPortConf);

    sec = &profile->security;
	profile->securityType = FTW_DEFAULT_SECURITY;
    profile->version    = FTW_PROFILE_DFLT_VERSION;
	profile->regDomain  = FTW_DEFAULT_REG_DOMAIN;
	profile->ncmAutoMgr = FTW_DEFAULT_AUTO_START;
    profile->mode       = FTW_DEFAULT_WLAN_MODE;

    wlan->mode = FTW_DEFAULT_AC_WLAN_MODE;

    wlan->channel = FTW_DEFAULT_AC_WLAN_CHANNEL;

    wlan->ssidLen = sizeof(FTW_DEFAULT_AC_WLAN_SSID) - 1;
    memcpy(&wlan->ssid, FTW_DEFAULT_AC_WLAN_SSID, wlan->ssidLen);
	if(otpMac_Read(mac,GSN_OTP_MM_ID_MAC_ID0) == FTW_SUCCESS)
	{
		S2w_macAddrRTCSet(mac); // set in the rtc also
	}
	else
	{
		S2w_macAddrRTCSet((UINT8*)FTW_DEFAULT_STA_MAC_ADDR); // set in the rtc also
	}


    wlan->validBssid = FTW_DEFAULT_AC_WLAN_BSSID_VALID;
    memcpy(wlan->bssid, FTW_DEFAULT_AC_WLAN_BSSID, sizeof(wlan->bssid));

    net->mode = FTW_DEFAULT_AC_NET_MODE;

    net->proto = FTW_DEFAULT_AC_NET_PROTO;

    net->port = FTW_DEFAULT_AC_NET_PORT;

    if (FTW_DEFAULT_AC_NET_IP_ADDR)
    {
        temp = FTW_DEFAULT_AC_NET_IP_ADDR;
        memcpy(&net->ipAddr, &temp, sizeof(net->ipAddr));
    }

    sec->authMode = FTW_DEFAULT_WEP_AUTH_MODE;

    sec->validKeys = FTW_DEFAULT_VALID_KEYS;

    sec->wep.keyIdx = FTW_DEFAULT_WEP_KEY_ID;

    sec->wep.keyLen[FTW_DEFAULT_WEP_KEY_ID-1] = FTW_DEFAULT_WEP_KEY_LEN;
    memcpy(sec->wep.key[FTW_DEFAULT_WEP_KEY_ID-1], FTW_DEFAULT_WEP_KEY,
           FTW_DEFAULT_WEP_KEY_LEN);


    FTW_ASSERT(sizeof(FTW_DEFAULT_WPA_PASSPHRASE) >= 8
               && sizeof(FTW_DEFAULT_WPA_PASSPHRASE) <= 64);
    sec->wpa.passPhraseLen = strlen(FTW_DEFAULT_WPA_PASSPHRASE);
    memcpy(sec->wpa.wpaPassPhrase, FTW_DEFAULT_WPA_PASSPHRASE,
           sec->wpa.passPhraseLen);


/* load default eap */
   sec->eap.outerAuth = FTW_DEFAULT_EAP_OUTERAUTH;
   sec->eap.innerAuth = FTW_DEFAULT_EAP_INNERAUTH;
   sec->eap.usrNameLen = sizeof(FTW_DEFAULT_EAP_USERNAME) - 1;	
   memset(sec->eap.usrName,0,FTW_MAX_EAP_USR_NAME_LEN);
   memcpy(sec->eap.usrName,FTW_DEFAULT_EAP_USERNAME,sec->eap.usrNameLen);
   sec->eap.passwordLen= sizeof(FTW_DEFAULT_EAP_PWD)- 1; 
      memset(sec->eap.password,0,FTW_MAX_EAP_PASSWORD_LEN);
   memcpy(sec->eap.password,FTW_DEFAULT_EAP_PWD,  sec->eap.passwordLen);
   sec->eap.useCaCert =FTW_DEFAULT_EAP_USE_CA_CERT;

    profile->txPower = FTW_DEFAULT_TX_POWER;

    profile->retryCount = FTW_DEFAULT_RETRY_COUNT;

    profile->powerSave = FTW_DEFAULT_POWER_SAVE;

    profile->radio = FTW_DEFAULT_RADIO_MODE;

    netconf->dhcp = FTW_DEFAULT_USE_DHCP;

    if (FTW_DEFAULT_IP_ADDR)
    {
        temp = FTW_DEFAULT_IP_ADDR;
        memcpy(&netconf->ipAddr, &temp, sizeof(netconf->ipAddr));
    }

    if (FTW_DEFAULT_NET_MASK)
    {
        temp = FTW_DEFAULT_NET_MASK;
        memcpy(&netconf->netMask, &temp, sizeof(netconf->netMask));
    }

    if (FTW_DEFAULT_GATEWAY)
    {
        temp = FTW_DEFAULT_GATEWAY;
        memcpy(&netconf->gateway, &temp, sizeof(netconf->gateway));
    }

#ifdef FTW_UART_ENABLE
//if(FTW_PORT_UART == APP_FTW_GET_SERIAL_DEVICE_ID())
//if(1)
{/* UART specific initialisation */

    ptSerialPort->conf.uart.bits = FTW_DEFAULT_BITS_PER_CHAR;;


    ptSerialPort->conf.uart.stop = FTW_DEFAULT_STOP_BITS;

    ptSerialPort->conf.uart.parity =  FTW_DEFAULT_PARITY;

    ptSerialPort->conf.uart.softflow = FTW_DEFAULT_SOFTWARE_FLOW_CONTROL;

    ptSerialPort->conf.uart.hardflow = FTW_DEFAULT_HARDWARE_FLOW_CONTROL;

    ptSerialPort->conf.uart.baudrate= FTW_DEFAULT_BAUD_RATE;

}
//else
#endif  /* GSN_UART_ENABLE */
{/* SPI specific initialisation */
/* SPI specific initialisation */
#if defined(FTW_FS_SPI_ENABLE) || defined(FTW_FS_SPI_HI_ENABLE)

   #if FTW_DEFAULT_SPI_ECHO
    ptSerialPort->commonConf.echo = FTW_DEFAULT_SPI_ECHO;
   #endif

   #if FTW_DEFAULT_SPI_VERBOSE
   ptSerialPort->commonConf.verbose = FTW_DEFAULT_SPI_VERBOSE;
   #endif

	ptSerialPort->conf.spi.clockPhase    = (GSN_SPI_CLOCKPHASE_T)FTW_DEFAULT_SPI_PHASE;
	ptSerialPort->conf.spi.clockPolarity = (GSN_SPI_CLOCKPOLARITY_T)FTW_DEFAULT_SPI_POLARITY;

#endif /* GSN_FS_SPI_ENABLE */

}

	ptSerialPort->commonConf.echo = FTW_DEFAULT_ECHO;
	ptSerialPort->commonConf.verbose = FTW_DEFAULT_VERBOSE;

    profile->registers[FTW_REG_TCP_CONNECT_TIMEOUT] =
                     FTW_DEFAULT_TCP_CONNECT_TIMEOUT;

    profile->registers[FTW_REG_NAGLE_WAIT_TIME] =
                     FTW_DEFAULT_NAGLE_WAIT_TIME;

    profile->registers[FTW_REG_AUTO_ASSOC_TIMEOUT] =
                      FTW_DEFAULT_AUTO_ASSOC_TIMEOUT;

    profile->registers[FTW_REG_NET_CONNECTION_TIMEOUT] =
                      FTW_DEFAULT_NET_CONNECTION_TIMEOUT;
    profile->registers[FTW_REG_ASSOC_RETRY_COUNT] =
                       FTW_DEFAULT_ASSOCIATION_RETRY_COUNT;

    profile->registers[FTW_REG_SCAN_TIME] =
                      FTW_DEFAULT_SCAN_TIME;
    profile->minScanTime = FTW_DEFAULT_SCAN_MIN_TIME;

    profile->registers[FTW_NCM_AUTO_L4_TIME] = FTW_NCM_DFLT_L4CONNECT_PERIOD  ;
    profile->registers[FTW_NCM_AUTO_L4_RETRY] = FTW_NCM_DFLT_L4CONNECT_COUNT;

    // Load the limited AP parameters
    profile->lmtdApConf.channel = FTW_DEFAULT_AP_WLAN_CHANNEL;
    profile->lmtdApConf.ssid.length = sizeof(FTW_DEFAULT_AP_WLAN_SSID) - 1;
    memcpy(&profile->lmtdApConf.ssid.array, FTW_DEFAULT_AP_WLAN_SSID, profile->lmtdApConf.ssid.length);
    // read the otp to get the mac for limited AP,
        if(otpMac_Read(mac,GSN_OTP_MM_ID_MAC_ID1) == FTW_SUCCESS)
        {
			memcpy(&profile->lmtdApConf.macAddr, mac, sizeof(profile->lmtdApConf.macAddr));
		}
		else
		{
            memcpy(&profile->lmtdApConf.macAddr, FTW_DEFAULT_AP_MAC_ADDR, sizeof(profile->lmtdApConf.macAddr));
	}

	profile->lmtdApConf.noStations      = FTW_DEFAULT_AP_SUPPORTED_STATIONS;
    profile->lmtdApConf.securityType    = FTW_DEFAULT_AP_SECURITY;
    profile->lmtdApConf.regDomain       = FTW_DEFAULT_AP_REG_DOMAIN;
    profile->lmtdApConf.beaconInterval  = FTW_DEFAULT_AP_BEACON_INTERVAL;
    profile->lmtdApConf.dhcpServerEnable= FTW_DFLT_AP_DHCPSRVR_ENABLE;
    profile->lmtdApConf.dnsServerEnable = FTW_DFLT_AP_DNSSRVR_ENABLE;
    profile->lmtdApConf.dhcpAddressStart= FTW_DFLT_AP_IP_START_ADDRESS;
    profile->lmtdApConf.dhcpNumAddresses= FTW_DHCP_SRVR_MAX_CLIENTS;
    profile->lmtdApConf.ipAddress       = FTW_DFLT_AP_IP_ADDRESS;
    profile->lmtdApConf.subnetmask      = FTW_DFLT_AP_SUBNET_ADDRESS;
    profile->lmtdApConf.gateway         = FTW_DFLT_AP_GATE_ADDRESS;
    profile->lmtdApConf.dhcpLeaseTime   =  htonl((UINT32)FTW_DFLT_AP_DHCPSRVR_LEASE_TIME);
	profile->lmtdApConf.wepKeyConfig.KeyId = FTW_DEFAULT_AP_WEP_KEY_INDEX;
	profile->lmtdApConf.wepKeyConfig.authType = (GSN_WDD_WEP_AUTH_TYPE_T) FTW_DEFAULT_AP_AUTH_MODE;
#if (FTW_DEFAULT_AP_WEP_KEY_LEN == 5) || (FTW_DEFAULT_AP_WEP_KEY_LEN == 13)
		profile->lmtdApConf.wepKeyConfig.KeyLen= (GSN_WDD_WEP_KEY_LEN_T)FTW_DEFAULT_AP_WEP_KEY_LEN;
		memcpy(profile->lmtdApConf.wepKeyConfig.Key, FTW_DEFAULT_AP_WEP_KEY,
			   FTW_DEFAULT_AP_WEP_KEY_LEN);
#endif
	FTW_ASSERT(sizeof(FTW_DEFAULT_AP_WPA_PASSPHRASE) >= 8
				   && sizeof(FTW_DEFAULT_AP_WPA_PASSPHRASE) <= 64);
	profile->lmtdApConf.passphrase.Len = strlen(FTW_DEFAULT_AP_WPA_PASSPHRASE);
	memcpy(profile->lmtdApConf.passphrase.Passphrase, FTW_DEFAULT_AP_WPA_PASSPHRASE,
		   profile->lmtdApConf.passphrase.Len);
	

	dnsSrvrIp = FTW_DFLT_AP_DNS_IP1;
	memcpy(&profile->dns1,(char*)&dnsSrvrIp,4);
	dnsSrvrIp = FTW_DFLT_AP_DNS_IP2;
	memcpy(&profile->dns2,(char*)&dnsSrvrIp,4);

    memcpy(&profile->lmtdApConf.dnsDomainName,FTW_DFLT_AP_DNS_NAME,sizeof(FTW_DFLT_AP_DNS_NAME) - 1);

    //http server
    memcpy(&profile->httpSrvrConf.username,FTW_DFLT_HTTP_SRVR_USRNAME,sizeof(FTW_DFLT_HTTP_SRVR_USRNAME));
    memcpy(&profile->httpSrvrConf.password,FTW_DFLT_HTTP_SRVR_PWD,sizeof(FTW_DFLT_HTTP_SRVR_PWD));
	/*ieee ps configuration*/
	profile->ieeePScfgEn = FTW_DFLT_IEEE_PS_CFG_ENABLE;
	profile->ieeePScfg.wakeupType = (GSN_WIF_WLAN_STA_PS_WAKEUP_T)FTW_DFLT_IEEE_PS_CFG_WAKEUP_TYPE;
	profile->ieeePScfg.wakeupInterval = FTW_DFLT_IEEE_PS_CFG_WAKEUP_INTERVAL;
	profile->ieeePScfg.listenIntervalAssoc = FTW_DFLT_IEEE_PS_CFG_LISTN_INTVL_ASSOC;
	profile->ieeePScfg.dataRxType = (GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_T)FTW_DFLT_IEEE_PS_CFG_DATA_RX_TYPE;
	profile->ieeePScfg.uapsdEnable = 0x0f;
	profile->ieeePScfg.txAtTbttWakeup = 0;
	profile->ieeePScfg.beaconWaitTimeout = FTW_DFLT_IEEE_PS_CFG_BEACON_WAIT_DURATION;
    profile->ieeePScfg.activeToOffTimeout = 10;
    // set the default mac address

    // set the remaining
    profile->asyncMsgFormat  = 0;
    //profile->ncmAutoMgr = 0;

    profile->ncmAutoLvl=0;
    profile->ncmAutoCid =0;
	profile->ncmAutoConf[FTW_NCM_HIDDENSSID_VALUE]= FTW_DEFAULT_AP_SSID_BROADCAST;
    profile->logLevel = FTW_DEFAULT_APP_LOG_LEVEL;
	profile->eapCertTimeValidChkDisbl=0;
    profile->dhcpRequestLeaseTime = 0;    
    profile->dhcpRetryTimeout = 0;
	profile->socRdCnt=3;
	profile->autoExitTimeout = FTW_DFLT_AUTO_EXIT_TIMEOUT;
    memcpy(&params->profile[1], profile, sizeof(FTW_PROFILE_T));
}

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Notify the status of an operation.
 *   This function sends the status information of each command/action to
 *   the serial interface.
 * @param status - IN the status value.
 * @param arg    - IN the arg passed with status
 * @retval VOID  - none.
 ************************************************************************/
PUBLIC VOID
AppS2wProcess_StatusNotify(UINT8 status, UINT32 arg)
{
    const char *msg;

    if (status == FTW_CMD_INPROCESS)
    {
        return;
    }

    if (status == FTW_LINK_LOST_EVT)
    {
        s2wIsAutoconnected = 0;
        AppS2wHal_NetCloseAll(1);
        curCid = INVALID_CID;

        if (s2wState == FTW_STATE_DATA_AUTO)
        {
            s2wState = FTW_STATE_CMD;
        }
    }

    if ((status == FTW_ECIDCLOSE || status == FTW_SOCKFAILURE)
         && s2wIsAutoconnected && curCid == arg)
    {
        curCid = INVALID_CID;

        /* Drop to command mode if the auto connected network
         * connection is closed, except if running as a TCP server
         */
         if (!(s2wCurrent.autoNetdata.proto == FTW_NETDATA_PROTO_TCP
             && s2wCurrent.autoNetdata.mode == FTW_NETDATA_MODE_SERVER))
         {
             s2wState = FTW_STATE_CMD;
             s2wIsAutoconnected = 0;
         }
    }

    /* Validate the status value.
     */
    if (status > S_STATUS_TBL - 1)
    {
        //S2w_Debug("unknown error: %d\r\n", status);
        return;
    }

    /* Use <Esc><'O'> or <Esc><'F'> for status in data mode */
    if ((s2wState == FTW_STATE_DATA_ESC
        || s2wState == FTW_STATE_CID
        || s2wState == FTW_STATE_IP_STRING
        | s2wState == FTW_STATE_PORT_STRING) && (status != FTW_ECIDCLOSE))
    {
        S2w_Printf("%c%c", FTW_ESC, status == FTW_SUCCESS ? 'O' : 'F');
        if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
        {
           FTW_SPI_flush(FTW_SPI_ALL);
        }
        return;
    }

    /* If verbose response is enabled, display the status in the verbose
     * format, if no verbose enabled, display the status in the numeric
     * format.
     */

   if (s2wCurrent.serialPortConf.commonConf.verbose)
    {
        msg = FTW_StatusList[status];
        if (!msg)
        {
            return;
        }
        if (status == FTW_SUCCESS && s2wState == FTW_STATE_DATA)
        {
            S2w_Printf("%cOK", FTW_ESC);
        }
        else if (status == FTW_CON_SUCCESS || ((status == FTW_ECIDCLOSE)
                                               &&(!s2wIsAutoconnected)))
        {
            S2w_Printf(msg, arg);
            if(status == FTW_ECIDCLOSE)
            {
                //s2wState = FTW_STATE_CMD;
                //dataIndex = 0;
            }
        }
        else if ((status == FTW_SOCKFAILURE) &&(!s2wIsAutoconnected))
        {
            S2w_Printf("\r\nERROR: SOCKET FAILURE %x\r\n",arg);
            //s2wState = FTW_STATE_CMD;
            //dataIndex = 0;
        }
		else if ((status == FTW_MDNS_REG_FAILED_ID) || (status == FTW_MDNS_REG_SUCESS_ID))
        {
        	UINT8 *str;
			str = (UINT8 *)arg;
			S2w_Printf("%s%s\r\n",msg,str);
		}
        else
        {
            if((status == FTW_ECIDCLOSE) &&(s2wIsAutoconnected))
            {
                S2w_Printf(msg, arg);
            }
            else if(status == FTW_BOOT_RST_APP_SW)
                S2w_Printf("\n\r%s\r\n", msg);				
            else if((status == FTW_SOCKFAILURE) &&(s2wIsAutoconnected))
            {
                S2w_Printf("\r\nERROR: SOCKET FAILURE %x\r\n",arg);
            }
            else
            {

                S2w_Printf("\r\n%s\r\n", msg);
                if(status == FTW_EBADCID)
                {
                    s2wState = FTW_STATE_CMD;
                    dataIndex = 0;
                }
            }
        }
    }
    else if ((status == FTW_CON_SUCCESS) || (status == FTW_ECIDCLOSE)
             || (status == FTW_SOCKFAILURE))
    {
        S2w_Printf("\r\n%d %x\r\n", status, arg);
        //if((status == FTW_ECIDCLOSE) || (status == FTW_SOCKFAILURE))
        {
            //s2wState = FTW_STATE_CMD;
            //dataIndex = 0;
        }
    }
    else if (s2wState == FTW_STATE_DATA)
    {
        S2w_Printf("%c%d", FTW_ESC, status);
    }
    else if(status == FTW_EXTPA_INITIAL_BOOT_MSG)
    {
         //status =  status -1;
         S2w_Printf("\r\n%d\r\n", status);
    }
    else
    {
        S2w_Printf("\r\n%d\r\n", status);
    }
    if((s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)&&(FTW_CON_SUCCESS != status))
    {
        FTW_SPI_flush(FTW_SPI_ALL);
    }
}


/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Notify the status of an event.
 *   This function is getting called once any asynchronous
 *   events(disassociation) happened.
 * @retval VOID - none.
 ************************************************************************/

PUBLIC VOID
AppS2wProcess_EventNotify(UINT8 flag)
{


    if(flag)
    {
        FTW_NET_disassociate(flag);
    }
	else
	{
    /* close all cids opened
     */
#ifndef FTW_IP2WIFI_SUPPORT
		AppS2wHal_HttpdClose(1);
#ifdef GSN_MDNS_ENABLE     
		AppS2wHal_MdnsDeInit(parentTask);
#endif	
    AppS2wHal_NetCloseAll(1);
#ifdef FTW_DHCP_SERVER_ENABLE        
	if(dhcpServerFlags & FTW_DHCP_SRVR_ENABLED)
	{
		GsnDhcpSrvr_Stop(&dhcpSrvr);
		dhcpServerFlags &= 0xfe;
	}
#endif   
    curCid = INVALID_CID;
    
    GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
    /* Release L3 connect semaphore if dhcp process is going on */
    if(S2wL3Wait)
      DHCP_notify(GSN_FAILURE,NULL);
#endif
	}
        /* make s2w associate state disconnected
         */
     s2wLinkState = FTW_LINK_STATE_DISCONNECTED;

    /* call the status notification function
     */
    dataIndex = 0;
    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
//    AppS2wProcess_StatusNotify(FTW_DISASSO_EVT, 0);
    if((!s2wAutoConnState ) ||(( s2wState == FTW_STATE_CMD) && (s2wIsAutoconnected)))
    {
#ifdef FTW_ASYNC_MSG
	if(s2wCurrent.asyncMsgFormat)
	{
		AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_DISASSO_EVT, 0);

	}
	else
#endif
	{
		AppS2wProcess_StatusNotify(FTW_DISASSO_EVT, 0);
	}
    }
    GsnOsal_SemRelease(&s2wSyncSemID);
    s2wState = FTW_STATE_CMD;
    s2wIsAutoconnected = 0;
}


/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Notify the status of dhcp fail event.
 *   This function sends the status information of dhcp fail event
 *   to the serial interface.
 * @param none.
 * @retval VOID  - none.
 ************************************************************************/

PUBLIC VOID
AppS2wProcess_DhcpFailNotify()
{
     s2wIsAutoconnected = 0;
     /* close all cids opened
      */
#ifndef FTW_IP2WIFI_SUPPORT
     AppS2wHal_NetCloseAll(1);
     curCid = INVALID_CID;
     s2wState = FTW_STATE_CMD;

#endif
     dataIndex = 0;
	 if(s2wappMainTaskCtxt->dpSleep )
	 {
	 	AppS2w_ExitDpSleep();
	 }
     GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
    if(!s2wAutoConnState )
    {
     if(s2wCurrent.asyncMsgFormat)
     {
         AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_DHCP_FAIL_EVT, 0);
     }
     else
    {
        AppS2wProcess_StatusNotify(FTW_ENOIP, 0);
    }
	}
    GsnOsal_SemRelease(&s2wSyncSemID);
}


PUBLIC VOID
AppS2wProcess_DhcpIpChangeNotify()
{

     s2wIsAutoconnected = 0;
     /* close all cids opened
      */

     AppS2wHal_NetCloseAll(1);
     curCid = INVALID_CID;
     s2wState = FTW_STATE_CMD;
     dataIndex = 0;
	 if(s2wappMainTaskCtxt->dpSleep )
	 {
	 	AppS2w_ExitDpSleep();
	 }
     GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
     if(!s2wAutoConnState )
     {
    if(s2wCurrent.asyncMsgFormat)
    {
        AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_DHCP_NEW_IP, 0);

    }
    else
    {
        AppS2wProcess_StatusNotify(FTW_ENEWIP, 0);
}
    AppS2wHdrAndIpv4_Print();
    S2w_Printf("\r\n");
    if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
    {
        FTW_SPI_flush(FTW_SPI_ALL);
    }
    }
    GsnOsal_SemRelease(&s2wSyncSemID);
}


 PUBLIC VOID
 AppS2wProcess_DhcpStop()
 {
   GsnNwIf_DhcpStop(&s2wappMainTaskCtxt->if0.nwifCtx);
 }

 
PUBLIC VOID
AppS2wProcess_IpConflict()
 {
	UINT8 status;
    
    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
     if(s2wCurrent.asyncMsgFormat)
    {
        AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_DHCP_IP_CONFLICT, 0);

    }
    else
    {
        AppS2wProcess_StatusNotify(FTW_DHCP_IP_CONFLICT, 0);
    }
    GsnOsal_SemRelease(&s2wSyncSemID);
    
     s2wCurrent.netConf.dhcp = 0;
     status = AppS2wHal_NetworkConfig(&s2wCurrent.netConf);
    if((status == FTW_SUCCESS) )
      {
         nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,NULL);
      }
     S2wL3Wait = FALSE;
 }
 
/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Accept a new connection for a TCP server
 * @param serverCid - IN connection identifier of the server
 * @param newCid    - IN connection identifier of the new connection
 * @param ip        - IN IP address (only for new connection notification)
 * @param port      - IN Port (only for new connection notification)
 * @return FTW_SUCCESS on success.  If any other status, the connection must be
 *                                   closed.
 ************************************************************************/
PUBLIC UINT8
AppS2wProcess_NetAccept(UINT8 serverCid, UINT8 newCid, UINT8 *ip,UINT16 port)
{
    if (s2wIsAutoconnected)
    {
        /* TCP server already has a client, reject this one */
        if (curCid != INVALID_CID)
        {
            return FTW_FAILURE;
        }

        curCid = newCid;
    }

   GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
    if((!s2wAutoConnState ) && (!profile_params.autoConnect))
    {
#ifdef FTW_ASYNC_MSG
	if(s2wCurrent.asyncMsgFormat)
	{
	   UINT32 argLen=0;
	   INT8 arr[50];
	   argLen = sprintf(arr," %x %x %d.%d.%d.%d %d\r\n",serverCid, newCid, ip[0], ip[1],ip[2], ip[3], port);
	   S2w_Printf("%c%c%x", FTW_ESC,'A',FTW_ASYNC_CON_SUCCESS);
	   const char* msg = FTW_AsyncStatusList[FTW_ASYNC_CON_SUCCESS];

	   if (s2wCurrent.serialPortConf.commonConf.verbose)
	   {
	       S2w_Printf("%02x%s",(strlen(msg) + argLen),msg);
	   }
	   else
	   {
	       S2w_Printf("%02x%d",(argLen + 1),FTW_ASYNC_CON_SUCCESS );
       }
	   //AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_CON_SUCCESS, argLen,FTW_INVALID_INTERFACE);
	}
	else
#endif

    {
        if (s2wCurrent.serialPortConf.commonConf.verbose)
        {
            S2w_Printf("\r\nCONNECT");
        }
        else
        {
            S2w_Printf("\r\n%x", FTW_CON_SUCCESS);
        }
    }
#ifdef FTW_IPv6_SUPPORT
            if(s2wCidList[serverCid].addrType & ADDR_TYPE_IPv6)
            {

              INT8 ipv6str[INET6_ADDRSTRLEN];
              S2w_ntop((ULONG*)ip,ipv6str);
              S2w_Printf("%x %x %s %d\r\n", serverCid, newCid,ipv6str,port );  
            }
            else
#endif 
    S2w_Printf(" %x %x %d.%d.%d.%d %d\r\n",serverCid, newCid,ip[3], ip[2], ip[1], ip[0],port) ;
        if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
        {
             FTW_SPI_flush(FTW_SPI_ALL);
	    }
	}
	else // auto mode
	{
        if(profile_params.autoConnect)
		{
			s2wState = FTW_STATE_DATA_AUTO;
			s2wIsAutoconnected = 1;
			s2wAutoConnState = FTW_AUTO_CONN_DATA_PIPE;
			S2w_AsyncMsgGpioInit(); // make the async gpio as  high to indicate that the data mode ready
			S2w_AsyncMsgGpioOp(1);
					// start a gpio cb for auto mode exit
			GsnGpio_Init(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP , APP_FTW_AUTO_EXIT_GPIO_BIT_MAP );
			/* register callback for GPIO interrupt */
			GsnGpio_IntCbRegister(APP_FTW_AUTO_EXIT_GPIO_NUM,s2wAutoExit_CB,NULL);
			/*enable interrupt*/
			GsnGpio_NEIntEnable(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP);
		}

	}
    GsnOsal_SemRelease(&s2wSyncSemID);
    return FTW_SUCCESS;
}


// XTRA
#if 0
/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Receive data from a network connection.
 * @param cid - IN connection identifier on which the data is received.
 * @param buf - IN Pointer to data buffer.
 * @param len - IN Total number of bytes.
 * @param ip  - IN IP address of the client from which the data was received
 *                    (only for UDP servers)
 * @param port- IN Port of the client from which the data was received (only
 *                 for UDP servers)
 * @retval VOID - none.
 ************************************************************************/
PUBLIC VOID
AppS2wProcess_NetRx(UINT8 cid, void *buf, UINT32 len, UINT8 *ip,
                    UINT16 port)
{
#ifdef FTW_IPv6_SUPPORT
    INT8 ipv6str[INET6_ADDRSTRLEN];
#endif
    UINT8 *p = (UINT8 *) buf;
    s2wRxBytes += len;
    if (s2wState == FTW_STATE_DATA_AUTO)
    {
        if (port)
        {
            /*
             * In UDP server auto-connect mode, any data received
             * on the serial port is transmitted to the host/port
             * from which data was last received.
             */

            curCid = cid;
#ifdef FTW_IPv6_SUPPORT
            if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
              memcpy(destIpv6Addr,ip,sizeof(destIpv6Addr));
#endif //FTW_IPv6_SUPPORT
            memcpy(destAddr, ip, sizeof(destAddr));
            // put it network order
            *(ULONG*)destAddr = ntohl(*(ULONG*)destAddr);
            destPort = port;
        }
#ifndef FTW_DUAL_INTERFACE_SUPPORT
        AppS2wHal_CharNPut(p, len);
        if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
        {
            FTW_SPI_flush(FTW_SPI_ALL);
          }
#else
        FTW_SERIAL_put(FTW_SERIAL_1, p, len);
       if(s2wappMainTaskCtxt->serialDeviceId1 == FTW_PORT_FS_SPI)
       {
           FTW_SPI_flush(FTW_SPI_ALL);
       }
#endif
        return;
    }
    if(s2wCidList[cid].sd != CID_NOTINUSE) // if the cid is closed in between by nclose command(fix for issue no:5537 )
	{


#ifndef FTW_DUAL_INTERFACE_SUPPORT
    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#else
    GsnOsal_SemAcquire(&s2wSyncSemID1, GSN_OSAL_WAIT_FOREVER);
#endif

    if (port)
    {
        if(!s2wCurrent.bulkTxEnable)
        {
#ifdef FTW_IPv6_SUPPORT
            if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
            {
            S2w_ntop((ULONG*)ip,ipv6str);

#ifndef FTW_DUAL_INTERFACE_SUPPORT
            S2w_Printf("%cu%x %s %d\t", FTW_ESC, cid,ipv6str,port );  
#else
                S2w_Printf1("%cu%x %s %d\t", FTW_ESC, cid,ipv6str,port );
#endif
            }
            else
#endif //FTW_IPv6_SUPPORT
            {
#ifndef FTW_DUAL_INTERFACE_SUPPORT
            S2w_Printf("%cu%x%d.%d.%d.%d %d\t", FTW_ESC, cid,
                    ip[3], ip[2], ip[1], ip[0], port);
#else
                S2w_Printf1("%cu%x%d.%d.%d.%d %d\t", FTW_ESC, cid,
                    ip[3], ip[2], ip[1], ip[0], port);
#endif
            }
        }
        else
        {
#ifdef FTW_IPv6_SUPPORT
            if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
            {
            S2w_ntop((ULONG*)ip,ipv6str);
#ifndef FTW_DUAL_INTERFACE_SUPPORT
            S2w_Printf("%cy%x %s %d\t", FTW_ESC, cid,ipv6str,port);  
#else
                S2w_Printf1("%cy%x %s %d\t", FTW_ESC, cid,ipv6str,port);
#endif
            }
            else
#endif //FTW_IPv6_SUPPORT
            {
#ifndef FTW_DUAL_INTERFACE_SUPPORT
            S2w_Printf("%cy%x%d.%d.%d.%d %d\t", FTW_ESC, cid,
                               ip[3], ip[2], ip[1], ip[0],port );
#else
                 S2w_Printf1("%cy%x%d.%d.%d.%d %d\t", FTW_ESC, cid,
				             ip[3], ip[2], ip[1], ip[0],port );
#endif
            }
        }
    }
    else
    {

        if(!s2wCurrent.bulkTxEnable)
#ifndef FTW_DUAL_INTERFACE_SUPPORT
            S2w_Printf("%cS%x", FTW_ESC, cid);
#else
            S2w_Printf1("%cS%x", FTW_ESC, cid);
#endif
        else
#ifndef FTW_DUAL_INTERFACE_SUPPORT
            S2w_Printf("%cZ%x", FTW_ESC, cid);
#else
            S2w_Printf1("%cZ%x", FTW_ESC, cid);
#endif
    }

    if(s2wCurrent.bulkTxEnable)
    {
#ifndef FTW_DUAL_INTERFACE_SUPPORT
        S2w_Printf("%04d", len);
#else
        S2w_Printf1("%04d", len);
#endif
    }

#ifndef FTW_DUAL_INTERFACE_SUPPORT
    AppS2wHal_CharNPut(p, len);
#else
    FTW_SERIAL_put(FTW_SERIAL_1, p, len);
#endif

    if(!s2wCurrent.bulkTxEnable)
#ifndef FTW_DUAL_INTERFACE_SUPPORT
        S2w_Printf("%cE", FTW_ESC);
#else
        S2w_Printf1("%cE", FTW_ESC);
#endif

#ifndef FTW_DUAL_INTERFACE_SUPPORT
       if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
       {
           FTW_SPI_flush(FTW_SPI_ALL);
       }

#else
       if(s2wappMainTaskCtxt->serialDeviceId1 == FTW_PORT_FS_SPI)
       {
           FTW_SPI_flush(FTW_SPI_ALL);
       }
#endif

#ifndef FTW_DUAL_INTERFACE_SUPPORT
    GsnOsal_SemRelease(&s2wSyncSemID);
#else
    GsnOsal_SemRelease(&s2wSyncSemID1);
#endif
}
}
#endif




UINT8 auto_esc;
extern PUBLIC GSN_OSAL_QUEUE_T s2wSerialInputTaskQueue;
/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Process the serial data from the host.
 *    This function continuously polls the serial port, classifies the incoming
 *    characters into Serial2WiFi data and command based on the serial data
 *    encoding.
 *    This function should be called from serial input-output handler thread each
 *    time when a character arrives on serial interface.
 ************************************************************************/
PUBLIC VOID
AppS2wProcess_SerialInput(VOID)
{
	static char esc[4] = { '+', '+', '+', '+' };
    static UINT8 ipnum;
    static char atoibuf[6];
    static UINT8 digits;
    UINT8 status;
    static UINT8 prev = 0;
    static UINT8 prevprev = 0;
    UINT8 ch,softFlow;
  
	UINT8 respTimeOut=0;
    UINT32 elementType;
#ifdef FTW_DUAL_INTERFACE_SUPPORT
    UINT32 msg = 0;
#endif
#ifndef FTW_DUAL_INTERFACE_SUPPORT
    while (FTW_SERIAL_getc(FTW_SERIAL_0, &ch) == 1)
    {
#else  // for dual interface use non blocking call
    while(1)
    {
        FTW_SERIAL_getc(FTW_SERIAL_0, &ch);
        // pend on a message queue
        GsnOsal_QueueGet(&s2wSerialInputTaskQueue, (UINT8 *)&msg, GSN_OSAL_WAIT_FOREVER);

#endif


        if ((s2wCurrent.serialPortConf.commonConf.echo) && (s2wState == FTW_STATE_CMD))
        {
            if (ch != FTW_ESC)
            {
                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                FTW_SERIAL_putc(FTW_SERIAL_0, ch);
                GsnOsal_SemRelease(&s2wSyncSemID);
            }
        }
        // switch to differnt state depends on the previous byte
        switch (s2wState)
        {
            /* special command comes with the length */

            case FTW_STATE_BULK_DATA:
                /* we must read 4 byte ascii lenth
                and then convert it to binary value */
            {
                //UINT8 *dataBufferPointer;
                lengthConvertIndex++;
                /* next after cid  char 2 to 5 */
                lengthSpecialCmd *= 10;
                lengthSpecialCmd += (ch - '0'); /* assuming number will come*/
                if(lengthConvertIndex == 4)
                {
                    FTW_SERIAL_get(FTW_SERIAL_0, dataBuffer, lengthSpecialCmd);
                    dataIndex = lengthSpecialCmd;

                    AppS2w_DataTransmit(dataBuffer);
                    s2wState =  FTW_STATE_CMD;
                }
            }
            break;
            case FTW_STATE_DATA_AUTO:
            {
                if (ch == '+' && auto_esc < 3 && 
					(s2wCurrent.autoExitTimeout))
		        {
		             auto_esc++;
		             AppS2wHal_TimerStop(&nagleTimer);

		             AppS2wHal_TimerStart(&auto_esc_timer,
		               s2wCurrent.autoExitTimeout);

		        }
		        else if (auto_esc && s2wCurrent.autoExitTimeout)
		        {
		             UINT8   i;
		             AppS2wHal_TimerStop(&auto_esc_timer);

		             esc[auto_esc] = ch;
		             i = 0;
		             AppS2wHal_TimerStart(&nagleTimer,
		                    s2wCurrent.registers[FTW_REG_NAGLE_WAIT_TIME]);
		             while (i <= auto_esc)
		             {
		                 AppS2w_DataCharProcess(esc[i++]);
		             }

		             esc[auto_esc] = '+';
		             auto_esc = 0;
		        }
		        else
			    {
		             auto_esc = 0;
		             AppS2w_DataCharProcess(ch);

		        }

			}
			break;
            case FTW_STATE_CMD:
                if (ch == FTW_ESC)
                {
                    s2wState = FTW_STATE_CMD_ESC;
                    continue;
                }
                AppS2w_CommandCharProcess(ch);
            break;

            case FTW_STATE_CMD_ESC:
                if (ch == 'S' || ch == 'u' || ch == 'U')
                {
                    s2wState = FTW_STATE_CID;
                }
#if defined(FTW_GSLINK) && defined(FTW_GSLINK_XML)
                else if(((ch == 'G')  || (ch == 'g'))&& s2wappMainTaskCtxt->xmlParseEn == 1 )
                {
                    rawLen=0;
                    rawLenIndex=0;
                    s2wState = FTW_STATE_GET_CID;
#ifdef FTW_WEB_SERVER			
					if(s2wappMainTaskCtxt->respTimeOut !=0 && s2wappMainTaskCtxt->responseInprogress == 1)
					{
						 if (GSN_SUCCESS != GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl))
							 respTimeOut = 1;					
					}	
					s2wappMainTaskCtxt->responseInprogress = 0;
 #endif			
                }
#endif
                else if((ch == 'Z') || (ch == 'Y'))
                {
                    s2wState = FTW_STATE_CID;
                    lengthSpecialCmd = 0;
                    lengthConvertIndex = 0;
                }
#ifdef FTW_IP2WIFI_SUPPORT
                else if (ch == 'R' || ch == 'r')
                {
                    {
						rawLen=0;
                        rawLenIndex=0;
                        s2wState = FTW_STATE_RAW;
                    }
                }
#endif
                else if ((ch == 'c')|| (ch == 'C'))
                {
#ifndef FTW_IP2WIFI_SUPPORT
#ifdef FTW_PING_TRACE
                    if(s2wPingStarted)
                    {
                        AppS2wHal_PingClose();
                    }
                    if(s2wTrcStarted)
                    {
                      //  AppS2wHal_TraceRouteClose();
                      //  s2wTrcStarted = 0;
                    }
#endif
#endif
                    s2wState = FTW_STATE_CMD;
                }
                else if ((ch == 'w')|| (ch == 'W'))
		        {
		             s2wState = FTW_STATE_CERT;
		             status = AppS2wCertificateData(ch);
		             // flush the data for spi-dma interface
					 if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
					 {
					     FTW_SPI_flush(FTW_SPI_ALL);
                     }
		                if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
		                    s2wState = FTW_STATE_CMD;
		        }
#ifdef FTW_EXTFLASH_DRIVER_TEST
				else if ((ch == 'v')|| (ch == 'V'))
		        {
		             s2wState = FTW_STATE_EXTFLASH;
		             status = AppS2wExternalFlashData(ch);
		                if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
		                    s2wState = FTW_STATE_CMD;
		        }
#endif
#ifdef FTW_EXT_FLASH_FS_SUPPORT
				else if((ch == 'f') || (ch == 'F'))
				{
					s2wState = FTW_STATE_FWRITE; 
					status = AppS2wHal_FileWriteDataGet(s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd, s2wappMainTaskCtxt->appExtFsCtx.fileInfo.size);
					if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
					s2wState = FTW_STATE_CMD;
				}
#endif

		        else if ((ch == 'H')|| (ch == 'h'))
	            {
	                s2wState = FTW_STATE_HTTP_CONTENT_CID;
#if defined(FTW_WEB_SERVER) && defined(FTW_GSLINK_RAW)				
					if(s2wappMainTaskCtxt->respTimeOut !=0 && s2wappMainTaskCtxt->responseInprogress == 1)
					{
						 if (GSN_SUCCESS != GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl))
							 respTimeOut = 1;					
					}
					s2wappMainTaskCtxt->responseInprogress = 0;
#endif			
		        }
		        else if ((ch == 'P')|| (ch == 'p'))
	            {
	                s2wState = FTW_STATE_COAP_CONTENT_CID;
	            }
#ifdef FTW_UNASSOC_TXRX_SUPPORT
                else if ((((ch == 'D')|| (ch == 'd')) && (s2wLinkState == FTW_LINK_STATE_DISCONNECTED)))
                {
                    s2wState = FTW_STATE_UNSOLICITED_DATA;
                    dataIndex = 0;
                }
#endif
                else
                {
                    s2wState = FTW_STATE_CMD;
                    AppS2w_CommandCharProcess(FTW_ESC);
                    AppS2w_CommandCharProcess(ch);
            }
            break;
#ifdef FTW_UNASSOC_TXRX_SUPPORT
            case FTW_STATE_UNSOLICITED_DATA:
                    dataBuffer[0]= ch;
                    if(s2wappMainTaskCtxt->frame.macFrameLen)
                    {
                        FTW_SERIAL_get(FTW_SERIAL_0, &dataBuffer[1], s2wappMainTaskCtxt->frame.macFrameLen-1);
                        dataIndex = s2wappMainTaskCtxt->frame.macFrameLen;
                        // first start the mode

						GSN_WDD_UAM_START_RESP_T resp;
                        status= GsnWdd_UAMStart(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp);
                        if(status != GSN_SUCCESS)
                        {
							AppS2wProcess_StatusNotify(status, 0);
						}
						// configure the rx if it is requetsed
						if(s2wappMainTaskCtxt->frame.rxWaitTime)
						{
							s2wUamRx_Init();
							// first configure the rx
							status= GsnWdd_UAMDataRxConfig(&(s2wappMainTaskCtxt->if0.wddCtx), &s2wappMainTaskCtxt->RxParam);

                            // register the callback
                            GsnWdd_DataIndCbReg(&(s2wappMainTaskCtxt->if0.wddCtx), FTW_UnassocDataIndCB, s2wappMainTaskCtxt);
						}
						{

						    GSN_WDD_UAM_CCA_SET_RESP_T respCCa;
						    GsnWdd_UamCcaConfigSet(&(s2wappMainTaskCtxt->if0.wddCtx),0,s2wappMainTaskCtxt->ccaThr,
                                             (UINT16)s2wappMainTaskCtxt->ccaTimeout,&respCCa);
						}
						GSN_WIF_WLAN_UNASSOCIATED_DATACFM_T wStatus;
                        GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                        status = GsnWdd_UamDataSend_Patch(&(s2wappMainTaskCtxt->if0.wddCtx),&s2wappMainTaskCtxt->frame,
                                           dataBuffer, dataIndex,&wStatus);
                        // if the option enabled then send back the time stamp

                        if((wStatus.status) && (s2wappMainTaskCtxt->uamTimeStampReturn))
                        {
							S2w_Printf("\r\nTS:%x",wStatus.timeStamp);
						}
                        AppS2wProcess_StatusNotify(!wStatus.status, 0);
                        GsnOsal_SemRelease(&s2wSyncSemID);
                        // wait for the rx to complete the stop the mode
                        if(s2wappMainTaskCtxt->frame.rxWaitTime)
						{
							GsnTaskSleep(s2wappMainTaskCtxt->frame.rxWaitTime);
						}
                        // stop the mode
                        GSN_WDD_UAM_STOP_RESP_T resp1;
                        GsnWdd_UAMStop(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp1);

					}
					s2wState = FTW_STATE_CMD;
            break;
#endif
            case FTW_STATE_DATA:
                if (ch == FTW_ESC)
                {
                    s2wState = FTW_STATE_DATA_ESC;
                    continue;
                }
                AppS2w_DataCharProcess(ch);
            break;

            case FTW_STATE_DATA_ESC:
                if(APP_FTW_GET_SERIAL_DEVICE_ID())
                {//Note: Is it not applicable for SPI interface - since we already apply stuffing  at lower layer
                    softFlow = 0x00;
                }
                else
                {
                    softFlow = s2wCurrent.serialPortConf.conf.uart.softflow;
                }
                if (ch == FTW_ESC)
                {
                    AppS2w_DataCharProcess(ch);
                    s2wState = FTW_STATE_DATA;
                }
                else if (ch == 'E' || ch == 'S' || ch == 'u' || ch == 'U')
                {
                    status = AppS2w_DataBufferTransmit();
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(status, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
                    curCid = INVALID_CID;
                    s2wState = ch == 'E' ? FTW_STATE_CMD : FTW_STATE_CID;
                }
                else if (ch == 'C')
                {
                    status = AppS2w_DataBufferTransmit();
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(status, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
                    AppS2wHal_NetClose(curCid);
                    s2wState = FTW_STATE_CMD;
                }
                else if ((ch == 'Q' || ch == 'T')
                          && (softFlow))
                {
                    AppS2w_DataCharProcess(ch == 'Q' ? FTW_XON : FTW_XOFF);
                    s2wState = FTW_STATE_DATA;
                }
                else
                {
                    s2wState = FTW_STATE_DATA;
                }
            break;

            case FTW_STATE_CID:
                curCid = AppS2w_CidValidate(ch);
                if (curCid == INVALID_CID)
                {
                    AppS2w_FailEscParse();
                }
                else
                {
                    digits = 0;
                    ipnum = 0;
#if  defined(FTW_FS_SPI_HI_ENABLE) || defined(FTW_SDIO_ENABLE)
#else

                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(FTW_SUCCESS, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
#endif
                    if (prev == 'S')
                        s2wState = FTW_STATE_DATA;
                    else if (prev == 'u')
                        s2wState = FTW_STATE_IPPORT;
                    else if (prev == 'U')
                        s2wState = FTW_STATE_IP_STRING;
                    else if (prev == 'Z')
                        s2wState = FTW_STATE_BULK_DATA;
                    else if(prev == 'Y')
                    {
                        prevprev = prev;
                        s2wState = FTW_STATE_IP_STRING;
                    }
                }
            break;

            case FTW_STATE_IPPORT:
                if (ipnum < 4)
                {
                    destAddr[ipnum] = ch;
                }
                else if (ipnum == 4)
                {
                    destPort = (UINT16) ch << 8;
                }
                else if (ipnum == 5)
                {
                    destPort |= ch;
                    s2wState = FTW_STATE_DATA;
                }
                ipnum++;
            break;

            case FTW_STATE_IP_STRING:
                if (digits < 3 && isdigit(ch))
                {
                    atoibuf[digits] = ch;
                    digits++;
                }
                else if (digits
                     && ((ipnum < 3 && ch == '.')
                     || (ipnum == 3 && ch == ':')))
                {
                    long temp;
                    atoibuf[digits] = '\0';
                    temp = atol(atoibuf);
                    if (temp < 0 || temp > 255)
                    {
                        AppS2w_FailEscParse();
                        continue;
                    }
                    destAddr[ipnum] = temp;
                    digits = 0;
                    ipnum++;
                    if (ipnum == 4)
                    {
                        ipnum = 0;
                        s2wState = FTW_STATE_PORT_STRING;
                    }
                }
                else
                {
                    AppS2w_FailEscParse();
                }
            break;

            case FTW_STATE_PORT_STRING:
                if (digits < 5 && isdigit(ch))
                {
                    atoibuf[digits] = ch;
                    digits++;
                }
                else if (digits && ch == ':')
                {
                    long    temp;
                    atoibuf[digits] = '\0';
                    temp = atol(atoibuf);
                    if (temp < 0 || temp > 65535)
                    {
                        AppS2w_FailEscParse();
                        continue;
                    }
                    destPort = temp;
                    if(prevprev == 'Y')
                    {
                        s2wState = FTW_STATE_BULK_DATA;
                        prevprev = 0;
                    }
                    else
                    {
                        s2wState = FTW_STATE_DATA;
                    }
                }
                else
                {
                     AppS2w_FailEscParse();
                }
            break;
          
            case FTW_STATE_HTTP_CONTENT_CID:
            {
                hCid = AppS2w_CidValidate(ch);
                if(( hCid != INVALID_CID )/* && ( AppS2w_ConnHttpStateGet(hCid) == 1)*/)
                {
                    UINT8 status=FTW_FAILURE;
#if defined (FTW_HTTPS_SUPPORT) || (FTW_HTTPC_SUPPORT)			
                  if((httpConfInfo.reqMethod == GSN_HTTP_METHOD_POST) || (httpConfInfo.reqMethod == GSN_HTTP_METHOD_PUT))
                  {
                      status = FTW_NET_HTTPD_contentDataGet(httpConfInfo.reqBodyTotalLen, hCid);
                  }
#endif
#if defined(FTW_GSLINK) &&  defined(FTW_GSLINK_RAW) && defined(FTW_WEB_SERVER)
				  if((s2wCidList[(hCid)].httpdCtx.method == GSN_HTTP_METHOD_GETRESP) ||  \
					 (s2wCidList[(hCid)].httpdCtx.method == GSN_HTTP_METHOD_POSTRESP))
                  {
					  if(respTimeOut == 0 )
					 	 status = FTW_NET_HTTPD_rawContentGet(s2wCidList[hCid].httpdCtx.reqBodyLen, hCid); 	  
                  }                                                           
#endif
                  s2wState = FTW_STATE_CMD;
				  	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                  AppS2wProcess_StatusNotify(status, 0);
				  	GsnOsal_SemRelease(&s2wSyncSemID);
             }
             else
             {
                 AppS2w_CommandCharProcess(ch);
                 s2wState = FTW_STATE_CMD;
             }
        }
        break;
            case FTW_STATE_COAP_CONTENT_CID:

            	hCid = AppS2w_CidValidate(ch);
                if( hCid != INVALID_CID )
                {
                	UINT8 status=FTW_FAILURE;

                	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
				#ifdef FTW_COAP_SUPPORT
                	status = AppS2wHal_CoapContentDataGet( hCid);
				#endif
                	GsnOsal_SemRelease(&s2wSyncSemID);
                    s2wState = FTW_STATE_CMD;
                    AppS2wProcess_StatusNotify(status, 0);
                }
                else
                {
                    AppS2w_CommandCharProcess(ch);
                    s2wState = FTW_STATE_CMD;
                }
            break;

#if defined(FTW_GSLINK) && defined(FTW_GSLINK_XML)  
		 case FTW_STATE_GET_CID:   
			curCid = AppS2w_CidValidate(ch);
        	if (curCid == INVALID_CID)
   	    	{
           		 AppS2w_FailEscParse();
       		}
			else				
				s2wState =  FTW_STATE_XML_LEN;		
				elementType=1;

			break;
		 case FTW_STATE_XML_LEN :	/* XML data  length*/
	 		S2w_RawLenCharProcess(ch);
 			if(rawLenIndex == 4 )
			{
				rawLen = S2w_RawLenCalculate();
				rawLenIndex = 0;
				if(rawLen ==	FTW_XML_ATTRIBUTE_ID || rawLen == FTW_XML_COMPLEX_TAG_START_ID )
				{
					elementType=rawLen;					
					break;
				}
				else if(rawLen == 0 || rawLen == FTW_XML_COMPLEX_TAG_END_ID)										
					elementType=rawLen;
#ifdef FTW_HTTP_CUSTOM_SUPPORT
                else if((FTW_HTTP_RESPONSE_LINE == rawLen) || (FTW_HTTP_HEADER == rawLen))
                {
                    elementType = rawLen;
                    break;
                }
#endif
				else			
					/* Start receiving the tags*/
					FTW_SERIAL_get(FTW_SERIAL_0, dataBuffer, rawLen);
#ifdef FTW_WEB_SERVER					
                if(respTimeOut == 0 )
                {
#endif
#ifdef FTW_HTTP_CUSTOM_SUPPORT
                    if((FTW_HTTP_RESPONSE_LINE == elementType) || (FTW_HTTP_HEADER == elementType))
                    {
                        AppS2w_HttpDataProcess(curCid, dataBuffer, rawLen, elementType);
                    }
                    else
#endif
					{	
                        AppS2w_XmlDataProcess(curCid,dataBuffer,rawLen,elementType);
					}
#ifdef FTW_WEB_SERVER
                }
                respTimeOut =0;
#endif				
#if 0
					rawTotalIndex = 0;			   
#endif
					s2wState = FTW_STATE_CMD;
					rawLen =0;				
					rawLenIndex=0;
				}
				//else
					//s2wState = FTW_STATE_CMD;	

			break; 
#endif		
#ifdef FTW_IP2WIFI_SUPPORT
        case FTW_STATE_RAW:

            if(ch == FTW_COLON)
					{
                if(rawColon == 0)
						{
                   rawColon = 1;
							}
                else
							{
                   rawLen = S2w_RawLenCalculate();
                   if(rawLen > 1560)
							{
                       S2w_Printf("\r\nERROR:INVALID LENGTH\r\n");
							s2wState = FTW_STATE_CMD;
						}
						else
						{
  			           FTW_SERIAL_get(FTW_SERIAL_0, dataBuffer, rawLen);
		  		       dataIndex=rawLen;
		  		       S2w_RawDataBufferTransmit();
							s2wState = FTW_STATE_CMD;
	                   rawTotalIndex = 0;
	                   rawLen = 0;
					}
                   rawColon = 0;
					}
				 }
            else
            {
                S2w_RawLenCharProcess(ch);

				 }
				 break;
#endif
        }
        prev = ch;
    }
}

#ifdef FTW_DUAL_INTERFACE_SUPPORT
extern GSN_OSAL_QUEUE_T s2wSerial2InputTaskQueue;
extern GSN_UART_HANDLE_T ptUartHandle1;

VOID AppS2wProcess_Serial2Input()
{
    static char esc1[4] = { '+', '+', '+', '+' };
    static UINT8 ipnum1;
    static char atoibuf1[6];
    static UINT8 digits1;
    static UINT8 prev1 = 0;
    static UINT8 prevprev1 = 0;
	UINT8 ch, softFlow;
    UINT32 msg=0;
    UINT8 status;
    UINT8 respTimeOut=0;
    UINT32 elementType;
    while(1){
    FTW_SERIAL_getc(FTW_SERIAL_1, &ch);
    // pend on a message queue
    GsnOsal_QueueGet(&s2wSerial2InputTaskQueue, (UINT8 *)&msg, GSN_OSAL_WAIT_FOREVER);

    // expect only data so no echo
        switch (s2wState)
        {
            /* special command comes with the length */
			;
            case FTW_STATE_CMD:
                if (ch == FTW_ESC)
                {
                    s2wState = FTW_STATE_CMD_ESC;
                    continue;
                }
                //AppS2w_CommandCharProcess(ch);
            break;
            case FTW_STATE_BULK_DATA:
                /* we must read 4 byte ascii lenth
                and then convert it to binary value */
            {
                //UINT8 *dataBufferPointer;
                lengthConvertIndex++;
                /* next after cid  char 2 to 5 */
                lengthSpecialCmd *= 10;
                lengthSpecialCmd += (ch - '0'); /* assuming number will come*/
                if(lengthConvertIndex == 4)
                {
                    FTW_SERIAL_get(FTW_SERIAL_1, dataBuffer, lengthSpecialCmd);
                    dataIndex = lengthSpecialCmd;

                    AppS2w_DataTransmit(dataBuffer);
                    s2wState =  FTW_STATE_CMD;
                }
            }
            break;
            case FTW_STATE_DATA_AUTO:
            {
                if (ch == '+' && auto_esc < 3)
		        {
		             auto_esc++;
		             AppS2wHal_TimerStop(&nagleTimer);
					 if(s2wCurrent.autoExitTimeout)
                     {
		             	AppS2wHal_TimerStart(&auto_esc_timer,s2wCurrent.autoExitTimeout);
					 }
		        }
		        else if (auto_esc)
		        {
		             UINT8   i;
		             AppS2wHal_TimerStop(&auto_esc_timer);

		             esc1[auto_esc] = ch;
		             i = 0;
		             AppS2wHal_TimerStart(&nagleTimer,
		                    s2wCurrent.registers[FTW_REG_NAGLE_WAIT_TIME]);
		             while (i <= auto_esc)
		             {
		                 AppS2w_DataCharProcess(esc1[i++]);
		             }

		             esc1[auto_esc] = '+';
		             auto_esc = 0;
		        }
		        else
			    {
		             auto_esc = 0;
		             AppS2w_DataCharProcess(ch);

		        }

			}
			break;
            case FTW_STATE_DATA:
                if (ch == FTW_ESC)
                {
                    s2wState = FTW_STATE_DATA_ESC;
                    continue;
                }
                AppS2w_DataCharProcess(ch);
            break;

            case FTW_STATE_DATA_ESC:
                if(APP_FTW_GET_SERIAL_DEVICE_ID())
                {//Note: Is it not applicable for SPI interface - since we already apply stuffing  at lower layer
                    softFlow = 0x00;
                }
                else
                {
                    softFlow = s2wCurrent.serialPortConf.conf.uart.softflow;
                }
                if (ch == FTW_ESC)
                {
                    AppS2w_DataCharProcess(ch);
                    s2wState = FTW_STATE_DATA;
                }
                else if (ch == 'E' || ch == 'S' || ch == 'u' || ch == 'U')
                {
                    status = AppS2w_DataBufferTransmit();
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(status, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
                    curCid = INVALID_CID;
                    s2wState = ch == 'E' ? FTW_STATE_CMD : FTW_STATE_CID;
                }
                else if (ch == 'C')
                {
                    status = AppS2w_DataBufferTransmit();
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(status, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
                    AppS2wHal_NetClose(curCid);
                    s2wState = FTW_STATE_CMD;
                }
                else if ((ch == 'Q' || ch == 'T')
                          && (softFlow))
                {
                    AppS2w_DataCharProcess(ch == 'Q' ? FTW_XON : FTW_XOFF);
                    s2wState = FTW_STATE_DATA;
                }
                else
                {
                    s2wState = FTW_STATE_DATA;
                }
            break;

            case FTW_STATE_CID:
                curCid = AppS2w_CidValidate(ch);
                if (curCid == INVALID_CID)
                {
                    AppS2w_FailEscParse();
                }
                else
                {
                    digits1 = 0;
                    ipnum1 = 0;
#if  defined(FTW_FS_SPI_HI_ENABLE_1) || defined(FTW_SDIO_ENABLE_1)
#else
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(FTW_SUCCESS, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
#endif
                    if (prev1 == 'S')
                        s2wState = FTW_STATE_DATA;
                    else if (prev1 == 'u')
                        s2wState = FTW_STATE_IPPORT;
                    else if (prev1 == 'U')
                        s2wState = FTW_STATE_IP_STRING;
                    else if (prev1 == 'Z')
                        s2wState = FTW_STATE_BULK_DATA;
                    else if(prev1 == 'Y')
                    {
                        prevprev1 = prev1;
                        s2wState = FTW_STATE_IP_STRING;
                    }
                }
            break;

            case FTW_STATE_IPPORT:
                if (ipnum1 < 4)
                {
                    destAddr[ipnum1] = ch;
                }
                else if (ipnum1 == 4)
                {
                    destPort = (UINT16) ch << 8;
                }
                else if (ipnum1 == 5)
                {
                    destPort |= ch;
                    s2wState = FTW_STATE_DATA;
                }
                ipnum1++;
            break;

            case FTW_STATE_IP_STRING:
                if (digits1 < 3 && isdigit(ch))
                {
                    atoibuf1[digits1] = ch;
                    digits1++;
                }
                else if (digits1
                     && ((ipnum1 < 3 && ch == '.')
                     || (ipnum1 == 3 && ch == ':')))
                {
                    long temp;
                    atoibuf1[digits1] = '\0';
                    temp = atol(atoibuf1);
                    if (temp < 0 || temp > 255)
                    {
                        AppS2w_FailEscParse();
                        continue;
                    }
                    destAddr[ipnum1] = temp;
                    digits1 = 0;
                    ipnum1++;
                    if (ipnum1 == 4)
                    {
                        ipnum1 = 0;
                        s2wState = FTW_STATE_PORT_STRING;
                    }
                }
                else
                {
                    AppS2w_FailEscParse();
                }
            break;

            case FTW_STATE_PORT_STRING:
                if (digits1 < 5 && isdigit(ch))
                {
                    atoibuf1[digits1] = ch;
                    digits1++;
                }
                else if (digits1 && ch == ':')
                {
                    long    temp;
                    atoibuf1[digits1] = '\0';
                    temp = atol(atoibuf1);
                    if (temp < 0 || temp > 65535)
                    {
                        AppS2w_FailEscParse();
                        continue;
                    }
                    destPort = temp;
                    if(prevprev1 == 'Y')
                    {
                        s2wState = FTW_STATE_BULK_DATA;
                        prevprev1 = 0;
                    }
                    else
                    {
                        s2wState = FTW_STATE_DATA;
                    }
                }
                else
                {
                     AppS2w_FailEscParse();
                }
            break;
            case FTW_STATE_CMD_ESC:
                if (ch == 'S' || ch == 'u' || ch == 'U')
                {
                    s2wState = FTW_STATE_CID;
                }
#if defined(FTW_GSLINK) && defined(FTW_GSLINK_XML)
                else if(((ch == 'G')  || (ch == 'g'))&& s2wappMainTaskCtxt->xmlParseEn == 1 )
                {
                    rawLen=0;
                    rawLenIndex=0;
                    s2wState = FTW_STATE_GET_CID;
#ifdef FTW_WEB_SERVER
					if(s2wappMainTaskCtxt->respTimeOut !=0 && s2wappMainTaskCtxt->responseInprogress == 1)
					{
						 if (GSN_SUCCESS != GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl))
							 respTimeOut = 1;
					}
					s2wappMainTaskCtxt->responseInprogress = 0;
 #endif
                }
#endif
                else if((ch == 'Z') || (ch == 'Y'))
                {
                    s2wState = FTW_STATE_CID;
                    lengthSpecialCmd = 0;
                    lengthConvertIndex = 0;
                }
#ifdef FTW_IP2WIFI_SUPPORT
                else if (ch == 'R' || ch == 'r')
                {
                    {
						rawLen=0;
                        rawLenIndex=0;
                        s2wState = FTW_STATE_RAW;
                    }
                }
#endif
                else if ((ch == 'c')|| (ch == 'C'))
                {
                   s2wState = FTW_STATE_CMD;
                }
                else if ((ch == 'w')|| (ch == 'W'))
		        {
		             s2wState = FTW_STATE_CERT;
		             status = AppS2wCertificateData(ch);
					 if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
					 {
					     FTW_SPI_flush(FTW_SPI_ALL);
                     }
		                if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
		                    s2wState = FTW_STATE_CMD;
		        }

#ifdef FTW_FILE_SYS
				else if((ch == 'f') || (ch == 'F'))
				{
					s2wState = FTW_STATE_FWRITE;
					status = AppS2wHal_FileWriteDataGet(s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd, s2wappMainTaskCtxt->appExtFsCtx.fileInfo.size);
					if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
					s2wState = FTW_STATE_CMD;
				}
#endif

		        else if ((ch == 'H')|| (ch == 'h'))
	            {
	                s2wState = FTW_STATE_HTTP_CONTENT_CID;
#if defined(FTW_WEB_SERVER) && defined(FTW_GSLINK_RAW)
					if(s2wappMainTaskCtxt->respTimeOut !=0 && s2wappMainTaskCtxt->responseInprogress == 1)
					{
						 if (GSN_SUCCESS != GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl))
							 respTimeOut = 1;
					}
					s2wappMainTaskCtxt->responseInprogress = 0;
#endif
		        }
#ifdef FTW_UNASSOC_TXRX_SUPPORT
                else if ((((ch == 'D')|| (ch == 'd')) && (s2wLinkState == FTW_LINK_STATE_DISCONNECTED)))
                {
                    s2wState = FTW_STATE_UNSOLICITED_DATA;
                    dataIndex = 0;
                }
#endif
                else
                {
                    s2wState = FTW_STATE_CMD;
                    AppS2w_CommandCharProcess(FTW_ESC);
                    AppS2w_CommandCharProcess(ch);
            }
            break;
#ifdef FTW_UNASSOC_TXRX_SUPPORT
            case FTW_STATE_UNSOLICITED_DATA:
                    dataBuffer[0]= ch;
                    if(s2wappMainTaskCtxt->frame.macFrameLen)
                    {
                        FTW_SERIAL_get(FTW_SERIAL_1, &dataBuffer[1], s2wappMainTaskCtxt->frame.macFrameLen-1);
                        dataIndex = s2wappMainTaskCtxt->frame.macFrameLen;
                        // first start the mode

						GSN_WDD_UAM_START_RESP_T resp;
                        status= GsnWdd_UAMStart(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp);
                        if(status != GSN_SUCCESS)
                        {
							AppS2wProcess_StatusNotify(status, 0);
						}
                        status = GsnWdd_UamDataSend(&(s2wappMainTaskCtxt->if0.wddCtx),&s2wappMainTaskCtxt->frame,
                                           dataBuffer, dataIndex);

                        AppS2wProcess_StatusNotify(status, 0);
                        // stop the mode
                        GSN_WDD_UAM_STOP_RESP_T resp1;
                        GsnWdd_UAMStop(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp1);

					}
					s2wState = FTW_STATE_CMD;
            break;
#endif
#ifdef FTW_IP2WIFI_SUPPORT
        case FTW_STATE_RAW:

            if(ch == FTW_COLON)
			{
                if(rawColon == 0)
				{
                   rawColon = 1;
				}
                else
				{
                   rawLen = S2w_RawLenCalculate();
                   if(rawLen > 1560)
				   {
                       S2w_Printf("\r\nERROR:INVALID LENGTH\r\n");
					   s2wState = FTW_STATE_CMD;
				   }
					else
					{
  			           FTW_SERIAL_get(FTW_SERIAL_1, dataBuffer, rawLen);
		  		       dataIndex=rawLen;
		  		       S2w_RawDataBufferTransmit();
					   s2wState = FTW_STATE_CMD;
	                   rawTotalIndex = 0;
	                   rawLen = 0;
					}
                       rawColon = 0;
				}
		    }
            else
            {
                S2w_RawLenCharProcess(ch);

			 }
			 break;
#endif

            case FTW_STATE_HTTP_CONTENT_CID:
            {
                hCid = AppS2w_CidValidate(ch);
                if(( hCid != INVALID_CID )/* && ( AppS2w_ConnHttpStateGet(hCid) == 1)*/)
                {
                    UINT8 status=FTW_FAILURE;
                   GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#if defined (FTW_HTTPS_SUPPORT) || (FTW_HTTPC_SUPPORT)
                  if((httpConfInfo.reqMethod == GSN_HTTP_METHOD_POST) || (httpConfInfo.reqMethod == GSN_HTTP_METHOD_PUT))
                  {
                      status = FTW_NET_HTTPD_contentDataGet(httpConfInfo.reqBodyTotalLen, hCid);
                  }
#endif
#if defined(FTW_GSLINK) &&  defined(FTW_GSLINK_RAW) && defined(FTW_WEB_SERVER)
				  if((s2wCidList[(hCid)].httpdCtx.method == GSN_HTTP_METHOD_GETRESP) ||  \
					 (s2wCidList[(hCid)].httpdCtx.method == GSN_HTTP_METHOD_POSTRESP))
                  {
					  if(respTimeOut == 0 )
					 	 status = FTW_NET_HTTPD_rawContentGet(s2wCidList[hCid].httpdCtx.reqBodyLen, hCid);
                  }
#endif
                  GsnOsal_SemRelease(&s2wSyncSemID);
                  s2wState = FTW_STATE_CMD;
                  AppS2wProcess_StatusNotify(status, 0);
             }
             else
             {
                 AppS2w_CommandCharProcess(ch);
                 s2wState = FTW_STATE_CMD;
             }
        }
        break;
#if defined(FTW_GSLINK) && defined(FTW_GSLINK_XML)
		 case FTW_STATE_GET_CID:
			curCid = AppS2w_CidValidate(ch);
        	if (curCid == INVALID_CID)
   	    	{
           		 AppS2w_FailEscParse();
       		}
			else
				s2wState =  FTW_STATE_XML_LEN;
				elementType=1;

			break;
		 case FTW_STATE_XML_LEN :	/* XML data  length*/
	 		S2w_RawLenCharProcess(ch);
 			if(rawLenIndex == 4 )
			{
				rawLen = S2w_RawLenCalculate();
				rawLenIndex = 0;
				if(rawLen ==	FTW_XML_ATTRIBUTE_ID || rawLen == FTW_XML_COMPLEX_TAG_START_ID )
				{
					elementType=rawLen;
					break;
				}
				else if(rawLen == 0 || rawLen == FTW_XML_COMPLEX_TAG_END_ID)
					elementType=rawLen;
#ifdef FTW_HTTP_CUSTOM_SUPPORT
                else if((FTW_HTTP_RESPONSE_LINE == rawLen) || (FTW_HTTP_HEADER == rawLen))
                {
                    elementType = rawLen;
                    break;
                }
#endif
				else
					/* Start receiving the tags*/
					FTW_SERIAL_get(FTW_SERIAL_1, dataBuffer, rawLen);
#ifdef FTW_WEB_SERVER
                if(respTimeOut == 0 )
                {
#endif
#ifdef FTW_HTTP_CUSTOM_SUPPORT
                    if((FTW_HTTP_RESPONSE_LINE == elementType) || (FTW_HTTP_HEADER == elementType))
                    {
                        AppS2w_HttpDataProcess(curCid, dataBuffer, rawLen, elementType);
                    }
                    else
#endif
                        AppS2w_XmlDataProcess(curCid,dataBuffer,rawLen,elementType);
#ifdef FTW_WEB_SERVER
                }
                respTimeOut =0;
#endif
#if 0
					rawTotalIndex = 0;
#endif
					s2wState = FTW_STATE_CMD;
					rawLen =0;
					rawLenIndex=0;
				}
				//else
					//s2wState = FTW_STATE_CMD;

			break;
#endif



		}
		prev1 = ch;
	}


}


#endif

PUBLIC VOID
AppS2w_ProfileInit(VOID)
{
	UINT32 bootReason;
	bootReason = GSN_BOOT_REASON_GET();
	//bootInfo =  GSN_BOOT_INFO_GET();
	// if the boot is stby/wakeup(normal) read from rtc else from flash
	if( (bootReason == GSN_WIF_SYS_BOOT_NORMAL_BOOT))
	{
        AppS2wHal_RTCRead();// this function reads data s2wFlashParams
	}
    else
    {
        s2wFlashParams = AppS2wHal_FlashRead();
	}

    {
        FTW_PROFILE_T *profile = &s2wFlashParams->profile[profile_params.defaultProfile];
        memcpy(&s2wCurrent, profile, sizeof(s2wCurrent));
 	}
}



/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Initialize the Serial2WiFi stack.
 *
 * This should be called once from the command handler thread,
 * immediately after initializing all the threads.
 ************************************************************************/
PUBLIC VOID
AppS2w_Init(VOID)
{
#ifdef FTW_DEFAULT_NODE_TIME_SET  
	UINT32 bootReason;
	bootReason = GSN_BOOT_REASON_GET();
#endif

    AppS2wHal_TimerInit(&acTimer, AppS2w_AcTimeoutHandler, NULL);
#ifdef FTW_NCM_SUPPORT_ENABLE
    AppS2wHal_TimerInit(&acNcmTimer, AppS2w_AcNcmTimeoutHandler, NULL);
    AppS2wHal_TimerInit(&nagleTimer, AppS2w_NagleExpiry, NULL);
    AppS2wHal_TimerInit(&auto_esc_timer, AppS2w_AutoEscTimeout, &auto_esc);
#endif //NCM_SUPPORT_ENABLE

    AppS2wHal_NetInit();
    // create a semaphore for data transmit in sequential
    GsnOsal_SemCreate  (&dSendSem,1);

    AppS2wProcess_LoadProfile(profile_params.defaultProfile);

    s2wState = FTW_STATE_CMD;
#ifdef FTW_DEFAULT_NODE_TIME_SET
  if( (bootReason == GSN_WIF_SYS_BOOT_FIRST_BOOT))
	  AppS2w_SetTime((ULONG64)FTW_DEFAULT_NODE_TIME);
#endif 
}


/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Vprintf function
 *
 * @retval integer.
 ************************************************************************/
PRIVATE INLINE INT32
AppS2w_VPrintf(const char *format, va_list ap)
{
    static char buf[FTW_MAX_PRINT_LEN];
    int len;

    len = vsnprintf(buf, sizeof(buf), format, ap);
    if (len < 0)
        return -1;

    if (len >= sizeof(buf))
    {
        FTW_ASSERT(0);
        len = sizeof(buf) - 1;
    }

    FTW_SERIAL_put(FTW_SERIAL_0, buf, len);

    return len;
}
#ifdef FTW_DUAL_INTERFACE_SUPPORT
PRIVATE INLINE INT32
AppS2w_VPrintf1(const char *format, va_list ap)
{
    static char buf1[FTW_MAX_PRINT_LEN];
    int len;

    len = vsnprintf(buf1, sizeof(buf1), format, ap);
    if (len < 0)
        return -1;

    if (len >= sizeof(buf1))
    {
        FTW_ASSERT(0);
        len = sizeof(buf1) - 1;
    }

    FTW_SERIAL_put(FTW_SERIAL_1, buf1, len);

    return len;
}
#endif


/**
 *************************************************************************
 * @ingroup S2w-Application.
 * @brief Process the incoming command characters.
 *
 * It will store the command characters to the command buffer. On receiving
 * 'end of command' character it will process the command.
 * @param ch Command character
 * @reval none.
 ***************************************************************************/
#ifndef IOT_APP_ENABLE
PRIVATE VOID
AppS2w_CommandCharProcess(UINT8 ch)
{
    static UINT8 prevBuf[FTW_CMDBUF_SIZE];
    static UINT8 buf[FTW_CMDBUF_SIZE];
    static UINT32 index;

    if ((ch == FTW_CR) ||(ch == FTW_LF) || (index == (sizeof(buf) - 1)))
    {
        if (index == 0)
        {
         if (s2wCurrent.serialPortConf.commonConf.echo)
          {
                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                S2w_Printf("\r\n");
                GsnOsal_SemRelease (&s2wSyncSemID);
            }
            /* Skip LF or CR after LF or CR.
             */
            return;
        }
        /* End of command; Call function to process the command.
         */
        buf[index] = '\0';
        memcpy(prevBuf, buf, index + 1);
        if((s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_SDIO) && (index >256 ))
        {
			index =0;
            UINT32 msg = APP_EVENT_FTW_EINVAL;
		    AppMainCtx_TaskNotify(msg);
		}
		else
		{
        index = 0;
        AppS2wCommand_Process(buf);
	    }
        memset (buf, 0, FTW_CMDBUF_SIZE);

        /* Store the command characters in the command buffer and also
         * handle the backspaces.
         */
    }
    else if (ch == FTW_BACKSPC)
    {
        index = index ? (index - 1) : 0;
    }
    else if (index == 1 && ch == '/' && toupper(buf[0]) == 'A')
    {
        index = 0;

        strcpy((char *)buf, (const char *)prevBuf);
        AppS2wCommand_Process(buf);
    }
    else if (index < sizeof(buf) - 1)
    {
        buf[index++] = ch;
    }
}
#endif /* IOT_APP_ENABLE */
/**
 * @brief Transmit the raw data to the specified L2 connection when the data
 *        is completely received or when the data buffer is full.
 */


/**
 **************************************************************************
 * @ingroup S2w-Application.
 * @brief Transmit the data to the specified TCP/UDP connection when the data
 *        is completely received or when the data buffer is full.
 * @reval none.
 ***************************************************************************/
PUBLIC UINT8
AppS2w_DataBufferTransmit(VOID)
{
    UINT8 status;
    //INT32 intrStatus;
    if (!dataIndex)
    {
        return FTW_SUCCESS;
    }

    status = AppS2wHal_NetTx(curCid, destAddr, destPort, dataBuffer,
                dataIndex);
    if (status == FTW_SUCCESS)
    {
        s2wTxBytes += dataIndex;
    }

    dataIndex = 0;
    return status;
}

PUBLIC UINT8
AppS2w_DataTransmit(UINT8 *data)
{
    UINT8 status;
    //INT32 intrStatus;
    if (!dataIndex)
    {
        return FTW_SUCCESS;
    }

    status = AppS2wHal_NetTx(curCid, destAddr, destPort, data, //dataBuffer,
                dataIndex);
    if (status == FTW_SUCCESS)
    {
        s2wTxBytes += dataIndex;
    }

    dataIndex = 0;
    return status;
}



/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Process the incoming data character.
 *   This function store the data to the data buffer, increment the index,
 *   start the nagle timer for auto connection and send the data out if the
 *   data buffer become full.
 * @param ch - IN incoming data character
 * @retval none.
 *************************************************************************/
PRIVATE VOID
AppS2w_DataCharProcess(UINT8 ch)
{
    UINT8 status;

    if (s2wState == FTW_STATE_DATA_AUTO)
    {
        /* TCP server without a connection
         */
        if (curCid == INVALID_CID)
        {
            return;
        }

        /* Locking to avoid race with expiry timer and send task
         */

        GsnOsal_SemAcquire ( &dSendSem,
                             GSN_OSAL_WAIT_FOREVER );
        dataBuffer[dataIndex] = ch;
        dataIndex++;
        GsnOsal_SemRelease(&dSendSem);

        if ((dataIndex == 1)|| ((dataIndex % 100) == 0))
        {
            AppS2wHal_TimerStart(&nagleTimer,
                    s2wCurrent.registers[FTW_REG_NAGLE_WAIT_TIME]);
        }

        if (dataIndex >= sizeof(dataBuffer))
        {
            /* Don't need the timer since we're transmitting it
             * ourselves */
            AppS2wHal_TimerStop(&nagleTimer);
            GsnOsal_SemAcquire ( &dSendSem,
            GSN_OSAL_WAIT_FOREVER );
            status = AppS2w_DataBufferTransmit();
            GsnOsal_SemRelease(&dSendSem);

        }

    }
    else
    {
        dataBuffer[dataIndex] = ch;
        dataIndex++;

        /* if data buffer is full transmit the data to the peer
         */
        if (dataIndex >= sizeof(dataBuffer))
        {
            status = AppS2w_DataBufferTransmit();
            if (status != FTW_SUCCESS)
            {
                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                AppS2wProcess_StatusNotify(status, 0);
                GsnOsal_SemRelease(&s2wSyncSemID);
            }
        }
    }
}



/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Handles the auto connect mode data timeout.
 *   This function is the timeout handler for auto connection escape sequence
     (+++).This function changes the mode to command mode.
 * @param data - IN data Pointer to the buffer which contains the timeout handler
 *                  data.
 * @retval none.
 ************************************************************************/

PRIVATE VOID
AppS2w_AutoEscTimeout(VOID *data)
{
    UINT8 *autoEsc = data;

    /* Check any data came after escape sequence. */
    if (*autoEsc == 3)
    {
        UINT32 message = APP_NOTIFICATION_AUTO_SEND;
        /* If no data came, flush any remaining data and switch to the
         * command mode */

        AppS2wHal_TimerStop(&nagleTimer);

        //GsnOsal_MailboxPut(&s2wSendQueue, NULL);

        (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);

        s2wState = FTW_STATE_CMD;
        *autoEsc = 0;
        // disable the auto mode exit gpio interrupt
        GsnGpio_NEIntDisable_Patch(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP); //Disable auto mode exit gpio interrupt
        // make the data ready gpio as low..
        S2w_AsyncMsgGpioOp(0);
    }
    else
    {
        char esc1[4] = { '+', '+', '+', '+' };
        UINT8   i=0;
        //AppS2wHal_TimerStart(&nagleTimer,
        //                     s2wCurrent.registers[FTW_REG_NAGLE_WAIT_TIME]);
        while (i < *autoEsc)
        {
            AppS2w_DataCharProcess(esc1[i++]);
        }

        auto_esc = 0;
    }
}



/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Convert the input character to the connection identifier and
 *        validate the connection identifier.
 * @param ch - IN Input character.
 *
 * @retval UINT8 - valid cid.
 ************************************************************************/
PUBLIC UINT8
AppS2w_CidValidate(UINT8 ch)
{
    UINT8 cid;

    /* Validate the input character, convert it to hexadecimal value. */
    if (ch >= '0' && ch <= '9')
    {
        cid = ch - '0';
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        cid = ch - 'A' + 10;
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        cid = ch - 'a' + 10;
    }
    else
    {
        return INVALID_CID;
    }
    return AppS2wHal_NetIsCidOpen(cid) ? cid : INVALID_CID;
}

/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @ingroup S2w-Application.
 * @brief parse Esc fail.
 *   This function notify the application with failure indication and
 *   change the mode to command.
 * @retval VOID - none.
 ************************************************************************/
PRIVATE VOID
AppS2w_FailEscParse(VOID)
{
    dataIndex = 0;
    curCid = INVALID_CID;
    if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_SDIO)
    {
		UINT32 msg = APP_EVENT_CID_FAILURE;
		AppMainCtx_TaskNotify(msg);
	}
	else
	{
    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
    AppS2wProcess_StatusNotify(FTW_FAILURE, 0);
    GsnOsal_SemRelease(&s2wSyncSemID);
	}
    s2wState = FTW_STATE_CMD;
}


VOID
s2wAutoExit_CB(UINT8 status, VOID* ctxt)
{
    UINT32 message = APP_NOTIFICATION_AUTO_SEND;
    /* If no data came, flush any remaining data and switch to the
    * command mode */
    GsnGpio_NEIntDisable_Patch(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP); //Disable auto mode exit gpio interrupt

    AppS2wHal_TimerStop(&nagleTimer);

    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);

    s2wState = FTW_STATE_CMD;
    // make the data ready gpio as low..
    S2w_AsyncMsgGpioOp(0);

}




/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Notify the status of an asynchronous event.
 *   This function sends the status information of each asynchronous event
 *   to the serial interface.
 * @param status - IN the status value.
 * @param arg    - IN the arg passed with status
 * @retval VOID  - none.
 ************************************************************************/
PUBLIC VOID
AppS2wProcess_AsyncStatusNotify(UINT8 status, UINT32 arg)
{
    const char *msg;

    S2w_AsyncMsgGpioOp(1);
    if(status< 15)
    {
        S2w_Printf("%c%c%x", FTW_ESC,'A',status);// for status  <15 put as a single char
	}
	else
	{
        UINT32 firstByteLimit=0x0F;
		S2w_Printf("%c%c%x%x", FTW_ESC,'A',firstByteLimit,(status-firstByteLimit)); //for status >=15  put as F<status>
	}


    if ((status == FTW_ASYNC_ECIDCLOSE || status == FTW_ASYNC_SOCKFAILURE)
         && s2wIsAutoconnected && curCid == arg)
    {
        curCid = INVALID_CID;
        if (!(s2wCurrent.autoNetdata.proto == FTW_NETDATA_PROTO_TCP
                 && s2wCurrent.autoNetdata.mode == FTW_NETDATA_MODE_SERVER))
        {
            s2wState = FTW_STATE_CMD;
            dataIndex = 0;
            s2wIsAutoconnected = 0;
         }
    }
    if (s2wCurrent.serialPortConf.commonConf.verbose)
    {
        msg = FTW_AsyncStatusList[status];
        if (!msg)
        {
            return;
        }
        if (status == FTW_ASYNC_ECIDCLOSE)
        {
             S2w_Printf("%02xDISCONNECT %x\r\n",(strlen(msg) + 4),arg);
            // s2wState = FTW_STATE_CMD;
            // dataIndex = 0;
        }
        else if(status == FTW_ASYNC_CON_SUCCESS)
        {
            S2w_Printf("%02x%s",(strlen(msg) + arg),msg);
        }
        else if (status == FTW_ASYNC_SOCKFAILURE)
        {
            S2w_Printf("%02xERROR: SOCKET FAILURE %x\r\n",(strlen(msg)+4),arg);
           // s2wState = FTW_STATE_CMD;
           // dataIndex = 0;
        }
		else if ((status == FTW_ASYNC_MDNS_REG_FAILED_ID) || (status == FTW_ASYNC_MDNS_REG_SUCESS_ID))
        {
        	UINT8 *str;
			str = (UINT8 *)arg;
			S2w_Printf("%02x%s%s\r\n",(strlen(msg)+strlen((const char *)str)),msg,str);
		}
        else
        {
            S2w_Printf("%02x%s\r\n",strlen(msg),msg);
        }
    }
    else
    {
		UINT8 buff[8],len;
		len = sprintf((char*)buff,"%x",status);
        if(status == FTW_ASYNC_CON_SUCCESS)
        {
            S2w_Printf("%02x%d",(arg + 1),status );
        }
        else if ((status == FTW_ASYNC_ECIDCLOSE) || (status == FTW_ASYNC_SOCKFAILURE) )
        {
            S2w_Printf("%02x%d %x\r\n",5,status, arg); // verbose only 1 char
            //s2wState = FTW_STATE_CMD;
            //dataIndex = 0;
        }
        else if (status == FTW_EXTPA_ASYNC_INITIAL_BOOT_MSG)
        {
            S2w_Printf("%02x%x\r\n",len,status);
        }
        else
        {
            S2w_Printf("%02x%x\r\n",len,status);
        }
    }
    if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
    {
        FTW_SPI_flush(FTW_SPI_ALL);
    }

    S2w_AsyncMsgGpioOp(0);
}

VOID
AppS2wRoam_SatusNotify(UINT32 statusMsg, UINT32 asycStatusMsg)  
 {
#ifdef	FTW_UART_ENABLE
		while(S2wUart_TxStatusGet());
#endif
	 GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);

	 /* Print ip header if msg is new ip*/
	 if(statusMsg == FTW_ENEWIP)
 	 {
		 AppS2wHdrAndIpv4_Print();
 	 }
 
#ifdef FTW_ASYNC_MSG
	 if(s2wCurrent.asyncMsgFormat)
	 {
		 AppS2wProcess_AsyncStatusNotify(asycStatusMsg, 0);
	 }
	 else
#endif
	 {
		 AppS2wProcess_StatusNotify(statusMsg, 0);
	 }
	 GsnOsal_SemRelease(&s2wSyncSemID);

#ifdef	FTW_UART_ENABLE
		while(S2wUart_TxStatusGet());
#endif
	 /* Print ip header if msg is new ip*/
 
 }
 void AppS2w_NwConnRestore()
 {
        APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	//APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
        GSN_WDD_WLAN_CFG_T *pWddConf;
        
	/* Set L2 Configuration */
	pWddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
	//memset(&WddConf,0,sizeof(GSN_WDD_WLAN_CFG_T));
	//s2wappMainTaskCtxt->if0.wddCtx.assocStatus = pAppRtcLtchInfo->AssocStatus;
	////s2wLinkState = s2wappMainTaskCtxt->if0.wddCtx.assocStatus;
	memcpy(&pWddConf->bssid, &pAppRtcLtchInfo->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
	memcpy(&pWddConf->ssid, &pAppRtcLtchInfo->ssid, sizeof(GSN_WLAN_MAC_SSID_T));
	pWddConf->securityCfg.mode = pAppRtcLtchInfo->wsec;
	pWddConf->channel[0] = pAppRtcLtchInfo->channel;
        current_wlan_info.mode = pAppRtcLtchInfo->wmode;
	current_wlan_info.authMode = pWddConf->securityCfg.mode;
	current_wlan_info.channel = pWddConf->channel[0];
	memcpy(current_wlan_info.ssid, pWddConf->ssid.array, pWddConf->ssid.length);
	current_wlan_info.ssidLen = pWddConf->ssid.length;
        
}

PUBLIC VOID
AppS2wProcess_AutoStart(VOID)
{
	UINT32 bootReason,bootInfo;
    UINT8 buff[8]={0}, len=0;
#ifdef  FTW_NCM_SUPPORT_ENABLE
   if(s2wCurrent.ncmAutoMgr)
   {
        
        len = sprintf((char*)buff,"%d,%d,%d",((s2wCurrent.mode == 1) ? 0: 1) ,
              s2wCurrent.ncmAutoMgr,s2wCurrent.ncmAutoLvl);
        buff[len]='\0';
	 	bootReason = GSN_BOOT_REASON_GET();		
		bootInfo =  GSN_BOOT_INFO_GET();
		if( (bootReason == GSN_WIF_SYS_BOOT_NORMAL_BOOT) && ((GSN_WIF_SYS_BOOTINFO_NORMALBOOT_RTC == bootInfo) || 
		                     (GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM == bootInfo)))
	        AppS2w_NwConnRestore();
        AppS2wCmd_NcmAuto(buff);

        
   }
    else if(profile_params.autoConnect)
    {
        len = sprintf((char*)buff,"%d,%d,%d",((s2wCurrent.autoWlandata.mode == 2) ? 1: 0) ,
              1,1);
        buff[len]='\0';
        AppS2wCmd_NcmAuto(buff);
    }
#endif
#ifdef FTW_ADC_SUPPORT
    if(s2wCurrent.clkCalibEn)
    {
        appCtx.clkCaibTmrHndl = GsnSoftTmr_Start(&appCtx.clkCaibTmr, GSN_SOFT_TMR_PERIODIC, 0, SEC_TO_SYSTIME(s2wCurrent.clkCalibPeriod), AppS2w_ClkCalibCb, NULL);
    }
#endif    
}

#ifdef  FTW_NCM_SUPPORT_ENABLE
PUBLIC UINT8
AppS2wProcess_AutoConnectStart(FTW_PROFILE_T *profile)
{
    UINT8 status = FTW_FAILURE;
    UINT8 buff[16],len;
    len = sprintf((char*)buff,"%d,%d,%d",((s2wCurrent.autoWlandata.mode == 2) ? 1: 0) ,
              1,1);
    buff[len]='\0';
    status = AppS2wCmd_NcmAuto(buff);
    return status;
}

PUBLIC UINT8
AppS2wProcess_AutoConnectStop(FTW_PROFILE_T *profile)
{
    UINT8 status = FTW_FAILURE;
    UINT8 buff[16],len;
    len = sprintf((char*)buff,"%d,%d",((s2wCurrent.autoWlandata.mode == 2) ? 1: 0) ,
              0);
    buff[len]='\0';
    status = AppS2wCmd_NcmAuto(buff);
    return status;
}
#endif
/**
 *************************************************************************
 * @ingroup S2w-Application.
 * @brief Perform the network auto connect operation.
 *
 * It will create the client or server of type TCP/UDP.
 *
 * @param  peer_data- IN Pointer to structure that contains
 *         mode, type, IP address and Port number.
 * @param  cid - IN Pointer to connection identifier.
 * @return Status of the operation. Possible status are FTW_SUCCESS (0) on
 *     success, FTW_FAILURE (1) on failure, FTW_ENCID (6) when Cid list is
 *     full, FTW_SOCKFAILURE (4) on failure of any socket system call,
 *         FTW_CMD_INPROCESS (8) when command response is not ready.
 **************************************************************************/
PRIVATE UINT8
AppS2w_Connect(FTW_NETDATA_T *peer_data, UINT16 udpSrcPort, UINT8 *cid)
{
    UINT8 status = FTW_EINVAL;

    if (peer_data->mode == FTW_NETDATA_MODE_SERVER)
    {
        if (peer_data->proto == FTW_NETDATA_PROTO_UDP)
        {
            status = AppS2wHal_NetUdpServer(peer_data, cid);
        }
        else if (peer_data->proto == FTW_NETDATA_PROTO_TCP)
        {
            status = AppS2wHal_NetTcpServer(peer_data, cid);
            *cid = INVALID_CID;
        }
    }
    else if (peer_data->mode == FTW_NETDATA_MODE_CLIENT)
    {
        if (peer_data->proto == FTW_NETDATA_PROTO_TCP)
        {
            status = AppS2wHal_NetTcpClient(peer_data, cid);
        }
        else if (peer_data->proto == FTW_NETDATA_PROTO_UDP)
        {
            status = AppS2wHal_NetUdpClient(peer_data,cid,udpSrcPort);
        }
    }

    return status;
}




#ifdef FTW_NCM_SUPPORT_ENABLE
extern UINT32 ncmautoconnectcount;




UINT8
AppS2wProcess_NcmAutoConnectL4Connect()
{
    UINT8 status = FTW_FAILURE;
	GSN_STATUS ret=GSN_FAILURE;
    UINT8 cid;
	ULONG ipaddr;
    //acTimedOut = 0;
    // auto connection and L4 as tcp/udp server no need to connect it back
       if((s2wIsAutoconnected ) &&(s2wCurrent.autoNetdata.mode == FTW_NETDATA_MODE_SERVER))
       {
		   curCid= INVALID_CID;
		   return 0;
	   }
        //AppS2wHal_TimerStart(&acTimer,s2wCurrent.registers[FTW_REG_NET_CONNECTION_TIMEOUT]);

        //while (!acTimedOut)
        //{

        if(s2wCurrent.autoNetdata.isFqdn)
        {
        GsnNwIf_DnsRetryCountSet(&s2wappMainTaskCtxt->if0.nwifCtx.dnsCliHndl,3);
		/* change  sysqual time to 200 sec*/		   
		GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
		GsnSq_TaskMonitorDeregister(APP_CFG_SQ_MAIN_TASK_ID);
		GsnSq_TaskMonitorRegister(APP_CFG_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK_DNSRESOLVE);
		GsnSq_TaskMonitorStart(APP_CFG_SQ_MAIN_TASK_ID,0);
        ret = GsnNwIf_DnsHostByNameGet(&s2wappMainTaskCtxt->if0.nwifCtx,(UINT8*)s2wCurrent.autoNetdata.fqdn,&ipaddr,5);
		/* change  sysqual time back to 30 sec*/		
		GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
		GsnSq_TaskMonitorDeregister(APP_CFG_SQ_MAIN_TASK_ID);
		GsnSq_TaskMonitorRegister(APP_CFG_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK);
		GsnSq_TaskMonitorStart(APP_CFG_SQ_MAIN_TASK_ID,0);
            if(ret == GSN_FAILURE || ipaddr == 0)
            {
            	/* Not able to resolve the host name , then skip the  connect call.
				    set status to failure and reset the connect retry count
				*/
            	status = FTW_FAILURE;	
			//ncmautoconnectcount=0;
				goto SkipConnect;
            }
			s2wCurrent.autoNetdata.ipAddr[0] = (ipaddr & 0xff000000)>>24 ;			
			s2wCurrent.autoNetdata.ipAddr[1] = (ipaddr & 0x00ff0000)>>16;
			s2wCurrent.autoNetdata.ipAddr[2] = (ipaddr & 0x0000ff00)>>8;
			s2wCurrent.autoNetdata.ipAddr[3] = (ipaddr & 0x000000ff);
			
        }
        status = AppS2w_Connect(&s2wCurrent.autoNetdata,s2wCurrent.udpSrcPort,&cid);
	
SkipConnect:
	
		/*
			 Bug FIX 5511 - Enhanced Auto connection: L4 timeout gives ERROR message to the MCU
			 Made auto connection l4 connection retey count to infinite  and never decremts the counter
	
		*/
		if(FTW_AUTO_CONCT_L4RETRY_INFINITE != ncmautoconnectcount);
    ncmautoconnectcount--;
        if (status != FTW_SUCCESS)
        {
           if(ncmautoconnectcount)
           {
               AppS2wHal_TimerStart(&acNcmTimer,
                   s2wCurrent.registers[FTW_NCM_AUTO_L4_TIME]);
               return status;
            }
            else
            {
				if(s2wLinkState != FTW_LINK_STATE_DISCONNECTED)
				{
                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#ifdef FTW_ASYNC_MSG
                if(s2wCurrent.asyncMsgFormat)
                {
                     AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_ERROR_MSG, 0);
                }
                else
#endif
                {
                     AppS2wProcess_StatusNotify(FTW_FAILURE, 0);
                }
                 GsnOsal_SemRelease(&s2wSyncSemID);
                curCid = cid;
				if(0 == profile_params.autoConnect)
				{
					ncmautoconnectcount = s2wCurrent.registers[FTW_NCM_AUTO_L4_RETRY];
				}
                // if it is auto connection then go back to command mode
                if(profile_params.autoConnect)
                {
					s2wState =FTW_STATE_CMD;
                    GsnGpio_NEIntDisable_Patch(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP); //Disable auto mode exit gpio interrupt
                    AppS2wHal_TimerStop(&nagleTimer);
                    // make the data ready gpio as low..
                    S2w_AsyncMsgGpioOp(0);
                    s2wIsAutoconnected = 0;
				}
            }
        }
        }
        else
        {
            if (cid != INVALID_CID)
            {
                // reset the count
				if(0 == profile_params.autoConnect)
				{                
                ncmautoconnectcount = s2wCurrent.registers[FTW_NCM_AUTO_L4_RETRY];
				}
                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                if((!s2wAutoConnState ) && (!profile_params.autoConnect))
                {// old auto connection
#ifdef FTW_ASYNC_MSG
                if(s2wCurrent.asyncMsgFormat)
                {
                     UINT32 arglen = 2;
                     S2w_Printf("\r\n");
                     AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_CON_SUCCESS, arglen);
                     S2w_Printf(" %x\r\n", cid);
                }
                else
#endif
                {
                    AppS2wProcess_StatusNotify(FTW_CON_SUCCESS, cid);
                }
			    }
                 GsnOsal_SemRelease(&s2wSyncSemID);
                curCid = cid;
				s2wCurrent.ncmAutoCid = cid;

            }
				// if the old auto mode is enabled then start it...
				if(profile_params.autoConnect)
				{
					s2wState = FTW_STATE_DATA_AUTO;
					s2wIsAutoconnected = 1;
					s2wAutoConnState = FTW_AUTO_CONN_DATA_PIPE;

					if(cid != INVALID_CID)// tcp server case, make gpio high once the client get connected.
					{
					S2w_AsyncMsgGpioInit(); // make the async gpio as  high to indicate that the data mode ready
					S2w_AsyncMsgGpioOp(1);
				   	}
					// start a gpio cb for auto mode exit
					GsnGpio_Init(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP , APP_FTW_AUTO_EXIT_GPIO_BIT_MAP );
					/* register callback for GPIO interrupt */
					GsnGpio_IntCbRegister(APP_FTW_AUTO_EXIT_GPIO_NUM,s2wAutoExit_CB,NULL);
					/*enable interrupt*/
					GsnGpio_NEIntEnable(APP_FTW_AUTO_EXIT_GPIO_BIT_MAP);
				}
        

    }
    return FTW_SUCCESS;

}

#endif

/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Handle deep sleep wake-up
 *    This function is called once the node come out of deep-sleep state.
  * @param  - NONE
 * @retval VOID - none.
 ************************************************************************/
PUBLIC VOID
AppS2w_DeepSleepHandler(VOID)
{
   #ifdef  FTW_FS_SPI_ENABLE
   if(FTW_PORT_SPI == APP_FTW_GET_SERIAL_DEVICE_ID())
   {//SPI interface is currently   selected
      /*In case of SPI interface, after waking up from deep-sleep, its required to clean up the FIFO */
      //AppS2w_FsReset();
   }
   #endif

   s2wappMainTaskCtxt->dpSleep = 0;
#ifdef FTW_ASYNC_MSG
   if(s2wCurrent.asyncMsgFormat)
   {
       AppS2wProcess_AsyncStatusNotify(FTW_ASYNC_DPSLEEP_EVT, 0);
   }

   else
 #endif
   {
       AppS2wProcess_StatusNotify(FTW_DPSLEEP_EVT,0);
   }
}


PRIVATE VOID
AppS2w_NagleExpiry(VOID *data)
{
     UINT32 message = APP_NOTIFICATION_AUTO_SEND;
    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
}


#ifdef FTW_IP2WIFI_SUPPORT
VOID
S2w_RawNetRx(void *buf, INT16 len)
{
    UINT8 *p = (UINT8 *) buf;

    FTW_L2_DEV_T *ps2wL2Dev = &s2wappMainTaskCtxt->s2wL2Dev;

    INT32 InterruptEnableStatus;

    s2wRxBytes += len;
#ifndef FTW_DUAL_INTERFACE_SUPPORT
    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
    S2w_Printf("%cR", FTW_ESC);
    S2w_Printf (":");
    S2w_Printf ("%d", len);
    S2w_Printf (":");
#else
    GsnOsal_SemAcquire(&s2wSyncSemID1, GSN_OSAL_WAIT_FOREVER);
    S2w_Printf1("%cR", FTW_ESC);
    S2w_Printf1 (":");
    S2w_Printf1 ("%d", len);
    S2w_Printf1 (":");
#endif
#ifndef FTW_DUAL_INTERFACE_SUPPORT
    AppS2wHal_CharNPut(p, len);
    if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
    {
    	FTW_SPI_flush(FTW_SPI_ALL);
    }
#else
    FTW_SERIAL_put(FTW_SERIAL_1, p, len);
       if(s2wappMainTaskCtxt->serialDeviceId1 == FTW_PORT_FS_SPI)
       {
           FTW_SPI_flush(FTW_SPI_ALL);
       }
#endif

#ifndef FTW_DUAL_INTERFACE_SUPPORT
    GsnOsal_SemRelease(&s2wSyncSemID);
#else
    GsnOsal_SemRelease(&s2wSyncSemID1);
#endif



    InterruptEnableStatus = GsnOsal_IntrDisable();

        /*Now free the buffer*/
    GsnRingBuf_Put(&ps2wL2Dev->s2wRawBufQ, &buf);

        /**< Reenable the interrupts */
    GsnOsal_IntrEnable( InterruptEnableStatus );


}

/**
 * @brief Transmit the raw data to the specified L2 connection when the data
 *        is completely received or when the data buffer is full.
 */
PRIVATE UINT8
S2w_RawDataBufferTransmit(VOID)
{
    GSN_STATUS_T status = GSN_SUCCESS;
#ifndef FTW_IP2WIFI_SUPPORT
    GSN_NWIF_CTX_T *pNwIf = &s2wappMainTaskCtxt->if0.nwifCtx;
#endif
    if (!dataIndex)
    {
        return FTW_FAILURE;
    }

#ifndef FTW_IP2WIFI_SUPPORT
    pNwIf->pL2Dev->send (
        pNwIf->pL2Dev, (GSN_ETHERNET_FRAME_T *)&dataBuffer, dataIndex);
#else
    status = s2wL2Dev_Send((GSN_L2_DEV_T *)&(s2wappMainTaskCtxt->s2wL2Dev),(GSN_ETHERNET_FRAME_T *)dataBuffer, dataIndex );
#endif

    rawTotalIndex += dataIndex;
    dataIndex = 0;
    return (UINT8)status;
}

#endif


// mac address read API
#define OTP_MAC_LEN_MASK 0x7
#define OTP_MAC_LEN 0x8
UINT8
otpMac_Read(UINT8* mac, UINT8 id)
{
    UINT8 otpGrpId, otpGrpVer;
    UINT8 data[OTP_MAC_LEN] ={0},data1[OTP_MAC_LEN];
    UINT16 dataLen=0,i=0, macLen = 6;

	// mac0 at F8, mac1 at F9 mac2 at FA
    // read mac0
    //memset(mac,0,sizeof(GSN_OTP_MM_MAC_T));
    if((id == 0xF8) || (id == 0xF9) || (id == 0xFA))
    {
        otpGrpVer =0;
        otpGrpId = id;
        if(GSN_SUCCESS != GsnOtpMm_Read(otpGrpId,otpGrpVer,
	                  &dataLen, data))
        {
	        return FTW_FAILURE;
        }
        if(dataLen ) // since mac is comming in reverse manner so reverse the string and use it
        {
			for(i=0;i<OTP_MAC_LEN;i++)
			{
				data1[i] = data[OTP_MAC_LEN_MASK - i];
			}
            if(id == 0xFA)macLen = 8;
            memcpy(mac,data1,macLen);
        }
	}
	else
	{
		return FTW_FAILURE;
	}
	return FTW_SUCCESS;
}

