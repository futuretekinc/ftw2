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
* $RCSfile: s2w_types.h,v $
*
* Description : This file contains macros and structure definitions used for s2w.
*******************************************************************************/
#ifndef FTW_TYPES_H
#define FTW_TYPES_H
#include "modules/nw/netx/gsn_nwif.h"
#include "fs/api/api_safe.h"

#include "hal/s2w_os_specific.h"
#include "app_events.h"
#include "modules/http/gsn_httpc.h"
#include "modules/http/gsn_httpd.h"
/*******************************************************************************
 *  Type Definitions
 ******************************************************************************/

#define  ASYNC_UNSOLICITED_TX 1
#define  ASYNC_TX_FRAME 2
#define  ASYNC_RX_FRAME 3
#define  WAVE_TX_FRAME  4

#define FTW_DHCP_SRVR_MAX_CLIENTS  64  //Same as GSN config.
#define FTW_DHCP_SRVR_ENABLED           0x01
#define FTW_DHCP_SRVR_CFG_DONE          0x02  

typedef UINT8 FTW_IPADDR_T[4];

//#ifdef FTW_IPv6_SUPPORT

#define FTW_IPv6_ADDR_LENGTH                    16            
#define FTW_IPv6_DEFAULT_PREFIX_LENGTH          64
typedef UINT32 FTW_IPv6ADDR_T[4];

#ifdef FTW_IPv6_SUPPORT
const char* 
inet_ntop6(const unsigned char *src, char *dst, size_t size);
inline UINT8 S2w_ntop(ULONG *ipv6,INT8 *buffer)
{
  UINT32 ipv6_temp[4];
  memcpy(ipv6_temp,ipv6,16);
  memset(buffer,0,INET6_ADDRSTRLEN);
  GSN_IPv6_CHANGE_ENDIAN(ipv6_temp);
  if(inet_ntop6((void*)ipv6_temp,buffer,INET6_ADDRSTRLEN) != NULL)
    return 0;
  else
    return 1;
}




#endif //FTW_IPv6_SUPPORT

#define FTW_NCM_CPUWAIT_PERIOD 0
#define FTW_NCM_PS_PERIOD 1
#define FTW_NCM_SCANKNOWN_CH_PERIOD 2
#define FTW_NCM_SCANSPEC_CH_PERIOD 3
#define FTW_NCM_SCANALL_CH_PERIOD 4
#define FTW_NCM_L3CONNECT_PERIOD 5


#define FTW_NCM_SCANKNOWN_CH_COUNT 8
#define FTW_NCM_SCANSPEC_CH_COUNT 9
#define FTW_NCM_SCANALL_CH_COUNT 10
#define FTW_NCM_L3CONNECT_COUNT  11
#define FTW_NCM_HIDDENSSID_VALUE   12
#define FTW_NCM_DTIMPERIOD_VALUE   13
#define FTW_NCM_INACTIVITY_TMEOUT_VALUE   14
#define FTW_NCM_GRP_KEY_UPDATE_INTERVAL   15

#ifdef FTW_NCM_ROAMING_SUPPORT 

#define FTW_NCM_ROAM_ENABLE_ID         16
#define FTW_NCM_ROAM_LOWER_THID        17
#define FTW_NCM_ROAM_HIGHER_THID       18
#define FTW_NCM_ROAM_RSSICHKINTERVAL_ID     19
#define FTW_NCM_ROAM_THCROSSEDCNT_ID   20
#define FTW_NCM_ROAM_MAINTAINL3CON_ID  		21 
#define FTW_NCM_ROAM_MAINTAINL4CON_ID  		22
#define FTW_NCM_ROAM_SCANRETRYCNT_ID   		23
#define FTW_NCM_ROAM_SCANPAUSETIME_ID  		24

#endif
#define FTW_NCM_DHCP_RADIO_MODE         25/* Shall we use */

#define FTW_NCM_EXTN_EXTN_BASE              26/* This is the start of extended parameters*/
#define FTW_NCM_EXTN_DHCP_RQST_LEASE        26
#define FTW_NCM_EXTN_DHCP_RETRANS_TIMEOUT   27

#define MAX_DNS_DOMAIN_LEN 64

//#define htonl_t(a) a=htonl(a)
#define STOP	3
#define RUNNING 2
#define START	1
#define IDLE	0

#define FTW_DFLT_CCA_TIMEOUT 5000 // micro seconds(5 msec)
#define FTW_DFLT_CCA_THR     80 //db
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Macro definition for PSK Passphrase.
 *     These macros defines the psk passphrase settings
 ******************************************************************************/
#define FTW_PSK_PASSPHRASE_LEN_MAX  64
#define FTW_PSK_PASSPHRASE_LEN_MIN  8
#define FTW_PSK_LEN                 32

#define FTW_SECURITY_VALID_WEP  0x01
#define FTW_SECURITY_VALID_WPA  0x02
#define FTW_SECURITY_VALID_EAP  0x04

#define FTW_AUTH_MODE_AUTO  0x00
#define FTW_AUTH_MODE_NONE  0x00
#define FTW_AUTH_MODE_OPEN  0x01
#define FTW_AUTH_MODE_SHARED    0x02
#define FTW_AUTH_MODE_WEP   0x04
#define FTW_AUTH_MODE_WPA   0x08
#define FTW_AUTH_MODE_WPA2  0x20
#define FTW_AUTH_MODE_WPA_ENTERPICE 0x10
#define FTW_AUTH_MODE_WPA2_ENTERPICE 0x40
#define FTW_MAX_SSID_LEN    32
#define FTW_MAX_EAP_USR_NAME_LEN 32
#define FTW_MAX_EAP_PASSWORD_LEN 32
#define FTW_ICMP_MASK 			0x01
#define FTW_UDP_TCP_MASK 		0x02
#define FTW_PROTO_ALL_MASK (FTW_ICMP_MASK | FTW_UDP_TCP_MASK)
#define FTW_MDNS_PORT 5353
#define FTW_HTTP_PORT 80
#define FTW_HTTPS_PORT 443
#define FTW_DNS_PORT 53
#define FTW_SNTP_PORT 123
#define FTW_COAP_PORT 5683
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for TCP/IP Network configurations.
 *     This structure defines the tcp/ip netwrok configuration parametres
 ******************************************************************************/
typedef struct FTW_NETCONF
{
    UINT8 dhcp;
    UINT8 dhcpRadioMode;
    UINT16 unused2;
    FTW_IPADDR_T ipAddr;   /**< IP address. */
    FTW_IPADDR_T netMask;  /**< Net mask. */
    FTW_IPADDR_T gateway;  /**< Default Gateway. */
	ULONG64         dhcpLeaseExpireTime;
    UINT8 dhcpv6;
} FTW_NETCONF_T;
#if 1
typedef struct FTW_LIMITED_APCONF
{
    GSN_MAC_SSID_T ssid;  /**<  SSID */
    GSN_MAC_ADDR_T macAddr;
    GSN_WDD_SEC_PSK_T passphrase; /**< WPA/WPA2 PSK Passphrase  */
    UINT8 securityType; /**< Network WLAN security type */
    GSN_WDD_SEC_WEP_KEY_T wepKeyConfig; /**< Pointer to WEP KEY configuration */
	UINT8 lmtdApPskValid;				/*lmt ap psk valid*/
	UINT8 lmtdApPsk[FTW_PSK_LEN];		/*lmt ap psk */
    UINT8 channel; /**< Channel on which AP should operate */
	UINT8 noStations;
    UINT8 regDomain;
    UINT16 beaconInterval; /**< Beacon interval for AP */
    UINT32 ipAddress; /**< IP address of AP */
    UINT32 subnetmask; /**< Subnet mask as served by AP DHCP server */
    UINT32 gateway; /**< Gateway address as served by AP DHCP server*/
    UINT8 dhcpServerEnable; /**< Flag indicating whether DHCP server is enabled*/
    UINT8 dhcpNumAddresses; /**< Number of DHCP addresses served*/
    UINT32 dhcpAddressStart; /**< Starting DHCP server address*/
    UINT8 dnsServerEnable; /**< Flag indicating whether DNS server is enabled*/
    UINT8 dnsDomainName[MAX_DNS_DOMAIN_LEN]; /**< DNS domain name*/
    UINT32 dhcpLeaseTime;
}FTW_LIMITED_APCONF_T;


#endif
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for TCP/IP connection settings
 *     This structure defines the tcp/ip netwrok connection setting parametres
 ******************************************************************************/
typedef struct FTW_NETDATA
{
    UINT8 mode;             /**< Connection mode, Server/Client. */
    UINT8 proto;            /**< Protocol type, UDP/TCP. */
    UINT16 port;            /**< Server port number. */
    FTW_IPADDR_T ipAddr;    /**< IP address of the server. */
    FTW_IPv6ADDR_T ipv6Addr;/**<Ipv6 address of the server. */
    UINT8 isFqdn;
    UINT8 fqdn[32];
} FTW_NETDATA_T;


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for FwUp configurations.
 *     This structure defines the firmware upgrade configuration  parametres
 ******************************************************************************/
typedef struct FTW_FWUP_CONF
{
    FTW_IPADDR_T fwSrvIp;
    UINT32 dstPort;
    UINT32 srcPort;
    UINT32 retry;
#ifdef FTW_IP2WIFI_SUPPORT
    FTW_IPADDR_T nodeIp;
    FTW_IPADDR_T nodMask;
    FTW_IPADDR_T nodeGateway;
#endif
} FTW_FWUP_CONF_T;

typedef struct FTW_OTA_FWUP_CONF
{
    struct sockaddr_storage sockAddr;
    struct sockaddr_storage proxySockAddr;
    UINT8  proxyFlag;
    UINT8 sslFlag;
    UINT8 *certAddr;
    UINT8* urls[6];
    UINT8 *connectReqatPath;
	UINT8 *fwSrvHostName;
	UINT8  dnsError;
}FTW_OTA_FWUP_CONF_T;


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for dns configurations.
 *     This structure defines the dns configuration  parametres
 ******************************************************************************/
typedef struct FTW_DNSINFO
{
    INT8 hostName[100];
    UINT32 retry;
    UINT32 timeout;
    UINT8 ipAddr[4];
    UINT8 clearCacheEntry;
}FTW_DNSINFO_T;


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief macro definition for uart configurations.
 *     These macros defines the uart configuration  parametres for stop bit,
 *     char format, parirty setting.
 ******************************************************************************/
#define FTW_UARTCONF_BITS_5 0
#define FTW_UARTCONF_BITS_6 1
#define FTW_UARTCONF_BITS_7 2
#define FTW_UARTCONF_BITS_8 3

#define FTW_UARTCONF_STOP_1 0
#define FTW_UARTCONF_STOP_2 1

#define FTW_UARTCONF_PARITY_NONE 0
#define FTW_UARTCONF_PARITY_ODD  1
#define FTW_UARTCONF_PARITY_EVEN 2

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for uart configurations.
 *     This structure defines the uart configuration  parametres
 ******************************************************************************/
typedef struct FTW_UARTCONF
{
    UINT32 bits :2;     /**< Bits per character. */
    UINT32 stop :1;     /**< Stop bit. */
    UINT32 parity   :3; /**< Parity. */
    UINT32 softflow :1; /**< Software flow control. */
    UINT32 hardflow :1; /**< Hardware flow control. */
    UINT32 baudrate;    /**< Baud rate. */
} FTW_UARTCONF_T;       /**< A type definition for struct s2w_uartconf. */
#if 1
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for SPI specific configurations.
 *     This structure defines the SPI specific  configuration  parametres
 ******************************************************************************/
typedef struct FTW_SPICONF
{
    UINT32 flowCtrl ; /**< Inband flow control.- For future usage */
	GSN_SPI_CLOCKPOLARITY_T   clockPolarity;    /**< SPI clock polarity */
    GSN_SPI_CLOCKPHASE_T      clockPhase;       /**< SPI clock phase    */

} FTW_SPICONF_T;    /**< A type definition for struct FTW_SPICONF_T. */
#endif
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for common  configurations for SPI/UART
 *     This structure defines the UART/SPI configuration  parametres
 ******************************************************************************/
typedef struct FTW_COMMONCONF
{
    UINT8 echo;            /**< Echo mode. */
    UINT8 verbose;         /**< Verbose response. */
} FTW_COMMONCONF_T;     /**< A type definition for struct FTW_COMMONCONF_T. */

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for WEP configurations.
 *     This structure defines the WEP configuration  parametres
 ******************************************************************************/
typedef struct FTW_WEPDATA
{
    UINT8 keyIdx;     /**< Key index, the key to be used for encryption */
    UINT8 keyLen[4];  /**< Key len, 5 or 13 */
    UINT8 key[4][13]; /**< Keys */
} FTW_WEPDATA_T;


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief structure definition for wpa-psk configuration.
 *     This structure defines the wpa-psk configuration parameters.
 ******************************************************************************/
typedef struct FTW_WPAPSK
{
    INT8  wpaPassPhrase[FTW_PSK_PASSPHRASE_LEN_MAX]; /**< WPA passphrase. */
    UINT8 passPhraseLen;
    UINT8           pskValid;
    UINT8           psk[FTW_PSK_LEN];
    INT8            ssid[FTW_MAX_SSID_LEN];
    UINT8           ssidLen;
}FTW_WPAPSK_T;

typedef struct FTW_EAP
{
	UINT32 outerAuth;
	UINT32 innerAuth;
	UINT8  useCaCert;
    UINT8 usrNameLen;
    UINT8 usrName[FTW_MAX_EAP_USR_NAME_LEN];
    UINT8 passwordLen;
    UINT8 password[FTW_MAX_EAP_PASSWORD_LEN];
}FTW_EAP_T;

typedef struct FTW_WPS
{
    UINT32 type;
    UINT8 pin[32];
	UINT8 storeL2ConInfo;

}FTW_WPS_T;
#define FTW_HTTPD_MAX_USERNAME_LEN  16
#define FTW_HTTPD_MAX_PASSWORD_LEN  16
typedef struct FTW_WBPROV_DATA
{
    INT8 username[FTW_HTTPD_MAX_USERNAME_LEN + 1];
    INT8 passwd[FTW_HTTPD_MAX_PASSWORD_LEN +  1];
    UINT8 sslEnabled;
	UINT8 storeParams;
	UINT16 IdleTimeOut;
}FTW_WBPROV_DATA_T;
typedef struct FTW_WBSERVER_CONFIG
{
    INT8 username[FTW_HTTPD_MAX_USERNAME_LEN + 1];
    INT8 passwd[FTW_HTTPD_MAX_PASSWORD_LEN + 1];
	UINT8 status;
    UINT8 sslEnabled;
	UINT8 storeParams;
	UINT16 IdleTimeOut;
#ifdef FTW_HTTP_CUSTOM_SUPPORT
    UINT32  httpdHdrBmap;
    UINT32  sendReq;
    UINT32  sendCgi;
#endif
}FTW_WBSERVER_CONFIG_T;
typedef struct FTW_WEB_LOGO
{
    UINT32 Size;
    UINT8 *lablePtr;
    UINT32 numBytesWrite;
}FTW_WEB_LOGO_T;
typedef struct FTW_FILE
{
    F_FILE *fd;
    UINT8 *pName;
    UINT8 *flags;
    UINT32 size;
}FTW_FILE_T;
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief structure definition for WiFi security configuration.
 *     This structure defines the WiFi security configuration parameters.
 ****************************************************************************/
typedef struct FTW_SECURITY
{
    UINT8 authMode;      /**< Authentication mode */
    UINT8 validKeys;     /**< Valid keys */
    FTW_WEPDATA_T wep;
    FTW_WPAPSK_T  wpa;
    FTW_EAP_T   eap;
    //UINT8* eapCert[3];
} FTW_SECURITY_T; /**< A type definition for struct s2w_security. */


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Macro definition for wlan configuration.
 *     These macros defines the wlan configuration parameters.
 ****************************************************************************/


/** Infrastructure mode. */
#define FTW_WLANDATA_MODE_INFRA 	1
#define FTW_WLANDATA_MODE_AP   		2
/** Ad hoc mode. */
#define FTW_WLANDATA_MODE_ADHOC 	3
#define FTW_WLANDATA_MODE_15_4		4
#define FTW_WLANDATA_MODE_ISOTX 	5
#define FTW_WLANDATA_MODE_PROV_AP 	6
#define FTW_WLANDATA_MODE_ZIP 	    7


#define FTW_WLANDATA_CHANNEL_MIN 1
#define FTW_WLANDATA_CHANNEL_MAX 14

/** Client mode network connection. */
#define FTW_NETDATA_MODE_CLIENT 0
/** TCP/IP Server mode connection. */
#define FTW_NETDATA_MODE_SERVER 1
#define FTW_NETDATA_MODE_CLIENT_TRANSIENT 7

/** UDP mode connection. */
#define FTW_NETDATA_PROTO_UDP 0
/** TCP mode connection. */
#define FTW_NETDATA_PROTO_TCP 1

/** MAC address size. */
#define FTW_MAC_ADDR_SIZE   6

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for scan/association information.
 *    This structure defines the wlan scan/association parameters.
 ****************************************************************************/
typedef struct FTW_WLANDATA
{
    UINT8 mode;             /**< WiFi Operating mode    */
    UINT8 channel;          /**< WiFi Operating channel     */
    UINT8 ssidLen;          /**< Length of SSID     */
    UINT8 validBssid;       /**< Is the BSSID valid     */
    UINT8 bssid[FTW_MAC_ADDR_SIZE]; /**< BSSID of network */
    UINT8 ssid[FTW_MAX_SSID_LEN];   /**< SSID of network        */
    UINT32 scanTime;        /**< Maximum scan time      */
} FTW_WLANDATA_T;           /**< A type definition for struct s2w_wlandata */

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for current network information.
 *    This structure defines the current network status parameters.
 ****************************************************************************/
typedef struct FTW_WLANINFO
{
    UINT8 mode;             /**< WiFi Operating mode    */
    UINT8 channel;          /**< WiFi Operating channel     */
    UINT8 ssidLen;          /**< Length of SSID     */
    UINT8 validBssid;       /**< Is the BSSID valid     */
    UINT8 bssid[FTW_MAC_ADDR_SIZE]; /**< BSSID of network       */
    UINT8 ssid[FTW_MAX_SSID_LEN];   /**< SSID of network        */
    GSN_WDD_SEC_MODE_T authMode;                 /**< Authentication mode    */
} FTW_WLANINFO_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for current network information.
 *    This structure defines the current network status parameters.
 ****************************************************************************/
typedef struct FTW_STATUS_INFO
{
    FTW_WLANINFO_T wlanInfo;
    UINT32 rssi;
    UINT32 rxCount;
    UINT32 txCount;
    UINT32 wstate;
    GSN_NWIF_IP_CONFIG_T nwParams;
    UINT8  macAddr[FTW_MAC_ADDR_SIZE];
} FTW_STATUS_INFO_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for version info.
 *    This structure defines the version information parameters of s2w.
 ****************************************************************************/
typedef struct FTW_VERSION_INFO
{
    UINT8 appVersion[4];
    UINT8 gepsVersion[4];
    UINT8 wlanVersion[4];
}FTW_VERSION_INFO_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for cid info.
 *    This structure defines the cid information parameters of s2w.
 ****************************************************************************/
typedef struct FTW_CID_INFO
{
    UINT8 conType;   /** Type of connection */
    UINT8 conMode;   /** Connection mode */
    UINT16 localPort;
    UINT16 remotePort;
    UINT8 remoteIp[4];
    UINT8 cid;
}FTW_CID_INFO_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for ipref configuration.
 *    This structure defines the iperf configuration parameters of s2w.
 ****************************************************************************/
typedef struct FTW_IPERF_DATA
{
    UINT8 srvIp[20];
    UINT32 bufLen;
    UINT32 protoSizeorDrate;
    UINT32 timeTorun;
    UINT8 proto;
}FTW_IPERF_DATA_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for ping configuration.
 *    This structure defines the ping configuration parameters .
 ****************************************************************************/
typedef struct FTW_PINGDATA
{
    UINT32 Ipv4Addr;
#ifdef FTW_IPv6_SUPPORT
    UINT8 IpVersion;
    NXD_ADDRESS ip_address;
#endif
    UINT32 interval;
    UINT32 dataLen;
    UINT32 tos;
    UINT32 ttl;
    UINT32 trails;
    INT8  payload[16];
}FTW_PINGDATA_T;


typedef struct FTW_PING_STATS
{
   ULONG rttMax;
   ULONG rttMin;
   ULONG rttAvg;
   UINT32 pingSentCnt;
   UINT32 pingRecvCnt;

}FTW_PING_STATS_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for trace route configuration.
 *    This structure defines the trace route configuration parameters .
 ****************************************************************************/
typedef struct FTW_TRACEDATA
{
    FTW_IPADDR_T ipAddr;
    UINT32 maxHops;
    UINT32 minHops;
    UINT32 tos;
    UINT32 interval;
    INT8 payload[16];

}FTW_TRACEDATA_T;


typedef struct FTW_UNSOLICITED_FRAME
{
	UINT32 wmmInfo;
    UINT32 frameControl;
    UINT32 seqControl;
    UINT32 channel;
    UINT32 txRate;
    UINT32 len;
    UINT8 remoteAddr[FTW_MAC_ADDR_SIZE]; /**< BSSID of network */
    UINT8 bssid[FTW_MAC_ADDR_SIZE];   /**< SSID of network */


}FTW_UNSOLICITED_FRAME_T;
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for error count.
 *    This structure defines the error count parameters of s2w .
 ****************************************************************************/
typedef struct FTW_ERROR_COUNTt
{
    UINT8 appWdogCount;
    UINT8 wlanWdogCount;
    UINT8 wlanAbortCount;
    UINT8 wlanAssertCount;

    UINT8 appSwResetCount;
    UINT8 wlanSwResetCount;
    UINT8 unused1;
    UINT8 unused2;
} FTW_ERROR_COUNT_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for alarm configuration.
 *    This structure defines the alarm configuration parameters .
 ****************************************************************************/
typedef struct FTW_ALARM_INFO
{
    UINT8 alarm1Valid;
    UINT8 alarm1Pol;
    UINT8 alarm2Valid;
    UINT8 alarm2Pol;
}FTW_ALARM_INFO_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition serial port  configuration.
 *    This structure defines the serial port  configuration parameters .
 ****************************************************************************/
typedef struct FTW_SERIAL_PORT_CONF
{
	FTW_COMMONCONF_T commonConf;  /**< Common configuration for UART and SPI serial port */

	struct
	{
		FTW_UARTCONF_T	 uart;	 /**< UART specific configuration */
		FTW_SPICONF_T	 spi;	 /**< SPI specific configuration */
	}conf;

}FTW_SERIAL_PORT_CONF_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief enum definition for ATS command.
 *    This enum defines the ATS command parameters .
 ****************************************************************************/
enum {
    /** Timeout for network connection in auto connect */
    FTW_REG_NET_CONNECTION_TIMEOUT = 0,

    /** Timeout for association in auto connect */
    FTW_REG_AUTO_ASSOC_TIMEOUT,

    /** Timeout for TCP connection */
    FTW_REG_TCP_CONNECT_TIMEOUT,

    /** Number of times to retry association on link loss */
    FTW_REG_ASSOC_RETRY_COUNT,

    /** Nagle algorithm wait time */
    FTW_REG_NAGLE_WAIT_TIME,

    /** Scan time */
    FTW_REG_SCAN_TIME,

    FTW_NCM_AUTO_L4_TIME,
    FTW_NCM_AUTO_L4_RETRY,


    FTW_NUM_TIMEOUTS
};

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief enum definition for ATI command.
 *    This enum defines the ATI command parameters .
 ****************************************************************************/
/** Identifier types for ATI command */
enum {
    /** OEM identification */
    FTW_ID_OEM,

    /** Hardwre version */
    FTW_ID_HW_VERSION,

    /** Software version */
    FTW_ID_SW_VERSION,

    /** Rx/Tx statistics */
    FTW_ID_STATISTICS,
    FTW_NUM_IDS
};

#define SECTYPE_AUTO 0
#define SECTYPE_NONE 1
#define SECTYPE_WEP  2
#define SECTYPE_WPAPSK 4
#define SECTYPE_WPA2PSK 8
#define SECTYPE_WPA 16
#define SECTYPE_WPA2 32

#define SECTYPE_WPA2PSK_TKIP 64

/*Association timeout in seconds*/
#define FTW_WLAN_RESPTIMEOUT  150


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for s2w profile.
 *    This structure defines the s2w profile parameters .
 ****************************************************************************/
/**
 * Structure definition for Serial2WiFi profile.
 */
typedef struct FTW_PROFILE
{
	UINT32      version;
    UINT8       mode;           /**< WiFi operating mode */
    UINT8       txPower;       /**< Transmitter Power */
    UINT8       retryCount;    /**< Retry count */
    UINT8       powerSave;     /**< Power save */
    UINT8       radio;          /**< Radio mode */
    FTW_WLANDATA_T  autoWlandata;  /**< Auto Connect WLAN settings */
    FTW_NETDATA_T   autoNetdata;   /**< Auto Connect network settings */
    FTW_SECURITY_T  security;   /**< 802.11 security profile */
    FTW_NETCONF_T   netConf;     /**< TCP/IP configuration */
    FTW_IPADDR_T dns1;           /**< Dns1IP address. */
    FTW_IPADDR_T dns2;           /**< Dns2 IP address. */

	FTW_SERIAL_PORT_CONF_T serialPortConf;    /**<S2w serial port configuration parameters */
    UINT16      registers[FTW_NUM_TIMEOUTS];  /**< Serial2WiFi register settings. */
	UINT8		bulkTxEnable;
    UINT8      securityType;
    UINT16     minScanTime;
   UINT8    asyncMsgFormat;
   UINT16   listenInterval;
   UINT8 hostName[GSN_NWIF_HOST_NAME_MAX_LEN + 1]; /**< Node Host Name. */
   FTW_LIMITED_APCONF_T   lmtdApConf;/**<Limited Ap configuration parameters */
	GSN_SYS_CONFIG_HTTPD_T httpSrvrConf;

    UINT8 ncmAutoMgr;
    UINT8 ncmAutoLvl;
    UINT32 ncmAutoConf[26];
	UINT8 ncmAutoCid;
    UINT8 regDomain;
	GSN_WIF_WLAN_STA_PS_CFG_T ieeePScfg;
	UINT16 udpSrcPort; 				 	    /**< Server port number. */
	UINT8  logLevel;
	UINT8 clkCalibEn;         /**< Enable temperature based clock caliberation */
	UINT32 clkCalibPeriod;    /**< Clock caliberation period */
	UINT8 ieeePScfgEn;
	GSN_WDD_ASSOC_CONFIG_T assocConf;    
    UINT8   eapCertTimeValidChkDisbl;
    UINT32 :0;          /** Padding. Profile API's use sizeof() to store and restore profile. 
                                 Padding is done to ensure that new elements starts at word aligned address.
                                 This should be checked at every release if new elements got added. Rel: 5.1.4*/
	UINT8 socRdCnt;
	UINT32 autoExitTimeout;	
    UINT32 dhcpRequestLeaseTime;
    UINT32 dhcpRetryTimeout;
    UINT32 ncmAutoConf_extn[10];
    UINT32 :0;          /** padding if any. 5.1.5*/
} FTW_PROFILE_T; /**< A typedefinition for struct s2w_profile. */

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief Structure definition for flash parameters.
 *    This structure defines the flash parameters .
 ****************************************************************************/
typedef struct FTW_FLASH_PARAMS
{
    FTW_PROFILE_T profile[2];   /**< Buffers to store the profiles. */
} FTW_FLASH_PARAMS_T;

/* s2w profile parameters to be loaded and saved to file system */
typedef struct FTW_PROFILE_PARAMS
{
	  UINT32 vsersion;
      UINT8 autoConnect;         
      UINT8 defaultProfile;
      UINT16 reserved;            
    
}FTW_PROFILE_PARAMS_T;


/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief macro definition for status codes.
 *    These macros defines error codes-status codes of s2w application.
 ****************************************************************************/
/* Status codes */
/** Success status. */
#define FTW_SUCCESS     0
/* Failure of operation. */
#define FTW_FAILURE     1
/** Invalid Command parameter */
#define FTW_EINVAL      2
/** Network system call failed. */
#define FTW_SOCKFAILURE     3
/** CID table is full. */
#define FTW_ENCID       4
/** Bad CID */
#define FTW_EBADCID     5
/** Feature is not supported. */
#define FTW_ENOTSUP     6
/** TCP/IP connection successful. */
#define FTW_CON_SUCCESS     7
/** Lost the TCP connection. */
#define FTW_ECIDCLOSE       8
/** WiFi link lost. */
#define FTW_LINK_LOST_EVT   9

#define FTW_DISASSO_EVT     10

#define FTW_STBY_TMR_EVT    11

#define FTW_STBY_ALM_EVT    12

#define FTW_DPSLEEP_EVT     13

#define FTW_BOOT_UNEXPECTED_EVT 14

#define FTW_ENOIP               15

#define FTW_INITIAL_BOOT_MSG    16
#define FTW_EXTPA_INITIAL_BOOT_MSG    17
#define FTW_ASSO_SUCCESS_MSG 18
#define FTW_ENEWIP       19
// new id added
#define FTW_BOOT_RST_WLAN_WD   20
#define FTW_BOOT_RST_APP_WD    21
#define FTW_BOOT_RST_WLAN_SW   22

#define FTW_BOOT_RST_APP_SW    23
#define FTW_BOOT_RST_WLAN_EXPT 24
#define FTW_BOOT_RST_EXT_FLASH_FWUP_SUCCESS 25
#define FTW_BOOT_UNKNOWN      26
#define FTW_BOOT_EXT_RST      27
#define FTW_BOOT_CRYPTO       28
#define FTW_BOOT_RST_JTAG     29
#define FTW_BOOT_RST_BROWNOUT 30
#define FTW_DHCP_IP_CONFLICT 31
#define FTW_MDNS_REG_FAILED_ID   32
#define FTW_MDNS_REG_SUCESS_ID   33
/** Command processing is not completed. */
#define FTW_CMD_INPROCESS   50

//async msg ids
#define FTW_ASYNC_SOCKFAILURE 0
#define FTW_ASYNC_CON_SUCCESS 1
#define FTW_ASYNC_ECIDCLOSE 2
#define FTW_ASYNC_DISASSO_EVT 3

#define FTW_ASYNC_STBY_TMR_EVT 4
#define FTW_ASYNC_STBY_ALM_EVT 5
#define FTW_ASYNC_DPSLEEP_EVT 6
#define FTW_ASYNC_BOOT_UNEXPECTED_EVT 7
#define FTW_ASYNC_DHCP_FAIL_EVT 8
#define FTW_ASYNC_INITIAL_BOOT_MSG 9
#define FTW_EXTPA_ASYNC_INITIAL_BOOT_MSG 10
#define FTW_ASYNC_ERROR_MSG 11
#define FTW_ASYNC_ASSO_SUCCESS_MSG 12
#define FTW_ASYNC_DHCP_NEW_IP 13

#define FTW_ASYNC_BOOT_RST_WLAN_WD   14
#define FTW_ASYNC_BOOT_RST_APP_WD    15
#define FTW_ASYNC_BOOT_RST_WLAN_SW   16

#define FTW_ASYNC_BOOT_RST_APP_SW    17
#define FTW_ASYNC_BOOT_RST_WLAN_EXPT 18
#define FTW_ASYNC_BOOT_RST_EXT_FLASH_FWUP_SUCCESS 19
#define FTW_ASYNC_BOOT_UNKNOWN      20
#define FTW_ASYNC_BOOT_EXT_RST      21
#define FTW_ASYNC_BOOT_CRYPTO       22
#define FTW_ASYNC_BOOT_RST_JTAG     23
#define FTW_ASYNC_BOOT_RST_BROWNOUT 24

#define FTW_ASYNC_DHCP_IP_CONFLICT 25
#define FTW_ASYNC_MDNS_REG_FAILED_ID   26
#define FTW_ASYNC_MDNS_REG_SUCESS_ID   27


#define FTW_ASYNC_NCM_SUCCESS 18
#define FTW_AUTO_CONCT_L4RETRY_INFINITE 4294967295

// err list
#define FTW_ERR_NOERROR 00
#define FTW_ERR_SSID_NOT_FOUND 01
#define FTW_ERR_PSK_INVALID 02
#define FTW_ERR_AUTH_TIMEOUT 03
#define FTW_ERR_AUTH_EAP_FAST_FAILURE 04
#define FTW_ERR_AUTH_EAP_CRED_FAILURE 05
/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief macro definition for special chars.
 *    These macros defines special chars used in s2w .
 ****************************************************************************/
/* Escape Sequences */
/** Start of data indicator. */
#define FTW_SOD     'S'
/** End of data indicator. */
#define FTW_EOD     'E'
/** Escape character. */
#define FTW_ESC     033
/** Back space character. */
#define FTW_BACKSPC     010
/** Carriage return character */
#define FTW_CR      015
/** Line feed character. */
#define FTW_LF      012
/** XOFF character. */
#define FTW_XOFF    023
/** XON character. */
#define FTW_XON     021

#define FTW_COLON     072
/*Note:  Till FTW_HTTPC_CFG_PARAM_HEADER_WWW_AUTHENTICATE, its aligned to
GSN_HTTP_USER_HEADER_TYPE_T definitions.*/
#ifdef FTW_HTTPC_SUPPORT
typedef enum FTW_HTTPC_CFG_PARAM
{
    FTW_HTTPC_CFG_PARAM_INV,
    FTW_HTTPC_CFG_PARAM_HEADER_ALLOW,
    FTW_HTTPC_CFG_PARAM_HEADER_AUTHORIZATION,
    FTW_HTTPC_CFG_PARAM_HEADER_CONNECTION,
    FTW_HTTPC_CFG_PARAM_HEADER_CONTENT_ENCODING,
    FTW_HTTPC_CFG_PARAM_HEADER_CONTENT_LENGTH,
    FTW_HTTPC_CFG_PARAM_HEADER_CONTENT_RANGE,
    FTW_HTTPC_CFG_PARAM_HEADER_CONTENT_TYPE,
    FTW_HTTPC_CFG_PARAM_HEADER_COOKIE,
    FTW_HTTPC_CFG_PARAM_HEADER_COOKIE2,
    FTW_HTTPC_CFG_PARAM_HEADER_DATE,
    FTW_HTTPC_CFG_PARAM_HEADER_EXPIRES,
    FTW_HTTPC_CFG_PARAM_HEADER_FROM,
    FTW_HTTPC_CFG_PARAM_HEADER_HOST,
    FTW_HTTPC_CFG_PARAM_HEADER_IF_MODIFIED_SINCE,
    FTW_HTTPC_CFG_PARAM_HEADER_LAST_MODIFIED,
    FTW_HTTPC_CFG_PARAM_HEADER_LOCATION,
    FTW_HTTPC_CFG_PARAM_HEADER_PRAGMA,
    FTW_HTTPC_CFG_PARAM_HEADER_RANGE,
    FTW_HTTPC_CFG_PARAM_HEADER_REFERER,
    FTW_HTTPC_CFG_PARAM_HEADER_SERVER,
    FTW_HTTPC_CFG_PARAM_HEADER_SET_COOKIE,
    FTW_HTTPC_CFG_PARAM_HEADER_TRANSFER_ENCODING,
    FTW_HTTPC_CFG_PARAM_HEADER_USER_AGENT,
    FTW_HTTPC_CFG_PARAM_HEADER_WWW_AUTHENTICATE,
    FTW_HTTPC_CFG_PARAM_HEADER_COUNT1,
    FTW_HTTPC_CFG_PARAM_REQUEST_URL,
    FTW_HTTPC_CFG_PARAM_HEADER_COUNT,   /* total number of headers defined above    */
    FTW_HTTPC_CFG_PARAM_HEADER_ALL,   /* special value to refer to all headers    */
    /* till this point the CFG definitions and header name index in Gsn_http.h
    are one to one*/
    /*custom header start. Add any standard header before this*/
    FTW_HTTPC_CFG_PARAM_HEADER_CUSTOM = 255,
    FTW_HTTPC_CFG_PARAM_HEADER_CUSTOM_MAX = 0xFFFFFFFF,
}FTW_HTTPC_CFG_PARAM_T;
typedef struct FTW_HTTP_DATA
{
    void *pHttpHandle;
    UINT16 portNumber;
    UINT16 caCertLen;
    UINT8 *pCaCert;
    GSN_HTTP_TYPE_T httpType;
    struct sockaddr_storage sockAddr;
    UINT8 proxyServer;
    GSN_OSAL_SEM_T opInProgress;
    INT32 connTimeOut;
    UINT16 clientCertLen;
    UINT8 *pClientCert;
    UINT16 clientKeyLen;
    UINT8 *pClientKey;
	/*Used for HTTPS conn in wdd task context*/
	GSN_HTTPC_CONN_PARAMS_T *pConnParams;
	GSN_HTTPC_CONF_INFO_T *pHttpConfInfo;
}FTW_HTTP_DATA_T;
#endif

typedef struct FTW_MDNS_HN_PARAM
{
    UINT8 *hostname;
    UINT8 *domain;
    INT8 *ipAddr;
    UINT8 autoCorrect;
    UINT8 scope;
    UINT8 conflctDetect;
    UINT32 ttl;
    UINT8 IpVersion;
}FTW_MDNS_HN_PARAM_T;


typedef struct FTW_MDNS_SRV_PARAM
{
    UINT8 *srvcInstance;
    UINT8 *srvcSubName;
    UINT8 *subType;
    UINT8 *srvcType;
    UINT8 *proto;
    UINT8 *domain;
    INT16 port;
    UINT8 scope;
    UINT8 *keyVal[5];
    UINT8 autoCorrect;
    UINT8 conflctDetect;
    UINT32 ttl;
}FTW_MDNS_SRV_PARAM_T;

typedef struct FTW_MDNS_ANNOUNCE_PARAM_T
{
        UINT8 type;     //1-Host Naem, 2-Service.
	UINT8 *srvceName;
	UINT8 *domain;
        UINT8 *srvceSubType;/* Name of the subtype excluding "_sub". "_sub" is added implicitly*/
	UINT8 *srvceType;
	UINT8 *srvceProto;
}FTW_MDNS_ANNOUNCE_PARAM_T;
typedef struct FTW_MDNS_SRVCDISCVR_PARAM
{
	UINT8 *srvcSubType;
	UINT8 *srvcType;
	UINT8 *srvcProto;
	UINT8 *domain;
	UINT8 scope;
}FTW_MDNS_SRVCDISCVR_PARAM_T;
//#endif
typedef struct FTW_SOCK_OP
{
	UINT32 cid;
	UINT32 type;
	UINT32 param;
	UINT32 paramValue;
    UINT32 paramSize;

}FTW_SOCK_OP_T;

typedef enum FTW_RADIO_TEST_TX_RATE
{
    FTW_RADIO_TEST_TX_RATE_1M  = 0,  /**< DSSS 1mbps */
    FTW_RADIO_TEST_TX_RATE_2M  = 1,  /**< DSSS 2mbps */
    FTW_RADIO_TEST_TX_RATE_5M5 = 2,  /**< CCK 5.5 Mbps */
    FTW_RADIO_TEST_TX_RATE_11M = 3,  /**< CCK 11 Mbps */
    FTW_RADIO_TEST_TX_RATE_INVALID = 4, /**< Dont add any more rates here */
} FTW_RADIO_TEST_TX_RATE_T;

typedef enum FTW_MAC_RATE_T
{
    FTW_MAC_RATE_1MBPS   =   2,
    FTW_MAC_RATE_2MBPS   =   4,
    FTW_MAC_RATE_5_5MBPS =  11,
    FTW_MAC_RATE_11MBPS  =  22,
    FTW_MAC_RATE_6MBPS   =  12,
    FTW_MAC_RATE_9MBPS   =  18,

} FTW_MAC_RATE_T;

typedef enum FTW_REG_DOMAIN_T
{
    FTW_DOMAIN_FCC   =   0,
    FTW_DOMAIN_ETSI  =   1,
    FTW_DOMAIN_TELEC =   2,
    FTW_MAX_REG_DOMAIN = 3,

} FTW_REG_DOMAIN_T;


typedef struct FTW_RADIO_TEST_TX_PARAMS
{
    UINT8 ssid[FTW_MAX_SSID_LEN];   /**< SSID of network        */
    UINT32 ssid_len;
    UINT32 channel;              /**< transmission channel */
    FTW_RADIO_TEST_TX_RATE_T rate; /**< transmission rate */
    BOOL preambleLong;          /**< FALSE = short preamble, TRUE = long preamble */
    BOOL scramblerOff;          /**< TRUE = scrambler off, FALSE = scrambler on */
    BOOL continuousTx;          /**< In case of GS1011 , TRUE = continuous tx, must be TRUE for wave Tx
                                                          **< In case of GS1500,  FALSE = TX99, TRUE = TX100, Applicable for modulated signal
                                                           */
    BOOL externalPa;            /**< TRUE = use external PA, FALSE = use internal PA */
    UINT32 powerIndex;           /**< 0 - 7, 0 = highest power, 1-7 increasing */
#ifdef GS1500M
    /* GS1500 platform specific parameters */
    UINT32  txDataPattern;       /**< 0: all zeros; 1: all ones; 2: repeating 10; 3: PN7; 4: PN9; 5: PN15 */
    UINT8  shortGuard;          /**<0-Short guard OFF, 1-Short guard ON */

#endif
    UINT32 len;
} FTW_RADIO_TEST_TX_PARAMS_T;

typedef struct FTW_ASYNCHRONOUSTX_METADATA
{
    UINT32 power;
    UINT32 channel;
    UINT32 dataRate;
    UINT32 noOfTimes;
    UINT32 frameInterval;   /**<In case of GS1500M  used for Arbitration Inter-Frame Space Number  0 to 252 */
    UINT32 frameControl;    /**<In case of GS1500M  0 - Async frame, 1- TX99,   2-TX100 ,  3 - unmodulated */
    UINT32 durationId;      /**<In case of GS1500M  0-Short guard OFF, 1-Short guard ON */
    UINT32 seqControl;      /**<In case of GS1500M  used for data pattern,    0: all zeros; 1: all ones; 2: repeating 10; 3: PN7; 4: PN9; 5: PN15 */
    UINT32 macFrameLen;
    UINT8 preamble;
    UINT8 scrambler;
    UINT8 addr1[6];
    UINT8 addr2[6];
    UINT8 addr3[6];
    UINT8 addr4[6];

} FTW_ASYNCHRONOUSTX_METADATA_T;

/*Notifications used to get some of the activities in Wdd Task context. This mathod is
used for optimum usage of stacks*/
typedef enum FTW_MUDULE_NOTIFICATIONS
{
	FTW_MOD_NOTIF_START = 600,
	FTW_MOD_NOTIF_CONN_START = FTW_MOD_NOTIF_START,
	FTW_MOD_NOTIF_CONN_END = 615,
	FTW_MOD_NOTIF_ASSOC = 650,
	FTW_MOD_NOTIF_PSKCALC = 660,
	FTW_MOD_NOTIF_WPS_KEY_CALC = 670,
	FTW_MOD_NOTIF_NWIF_OPEN = 680,
	FTW_MOD_NOTIF_P2P_JOIN = 690,
	FTW_MOD_NOTIF_P2P_GOSTART = 695,
	FTW_MOD_NOTIF_END = 700,
}FTW_MUDULE_NOTIFICATIONS_T;
/*Connection parameters, used in case the association is done in Wdd task context*/

/*NwIf open is now done in Wdd context. Parmameter data type for the same is defined here*/
typedef struct FTW_NWIF_OPEN_PARAMS
{
	GSN_NWIF_IP_CONFIG_T *pIpConfig;
	GSN_NOTIFICATION_FUNC_T notifyCb;
	VOID *notifyCtxt;

}FTW_NWIF_OPEN_PARAMS_T;


typedef struct FTW_USR_BUF
{
UINT8 *ps2wUserBuf;
UINT s2wBufLen;
}FTW_USR_BUF_T;

extern BOOL ncmAutoMode;
extern FTW_PROFILE_T s2wCurrent;
extern GSN_DNS_SERVER_T dnsServer;
extern GSN_DHCP_SRVR_T dhcpSrvr;
extern GSN_DHCP_SRVR_CFG_T dhcpSrvrCfg;
extern UINT8 dhcpServerFlags;

/*   Structure definitions for command table   */
typedef struct FTW_EXTFLASH_CMD
{
    const char *cmd;                /**< Command string */
    UINT8 (*process) (UINT8 *ptr);  /**< Command handler */
}FTW_EXTFLASH_CMD_T;

/**
 *******************************************************************************
 * @ingroup S2w-Application
 * @brief structure definition for ARP Cache Enable/Disable configuration.
 *     This structure defines the ARP Cache Enable/Disable configuration parameters.
 ******************************************************************************/


#define FTW_MAX_ARPENTRY   8
extern UINT8 globalUseHRssi;

/**/
/**/
typedef struct FTW_MSG
{
    union
    {
        INT32 dataSock;
        void  *dataPtr;
    }rData;
    INT16 msgLen;
    INT16 msgType;
}FTW_MSG_T;


typedef enum FTW_MSG_TYPE
{
    FTW_RECV_TYPE_SOCKET = APP_EVENT_MAX, /*Considered as the Extension of events. Usful in case main task and
											S2w Nw Rx tas are merged*/
    FTW_RECV_TYPE_RAWDATA,
    FTW_RECV_TYPE_SOCK_ERROR,
    FTW_RECV_TYPE_SOCK_DISCONNECT,
    FTW_RECV_TYPE_SOCK_ACCEPT,
    FTW_RECV_TYPE_HTTPS_CLOSE,
    FTW_RECV_TYPE_SOCK_DATA_DISCONNECT,
    FTW_RECV_TYPE_UAMDATA,
}FTW_MSG_TYPE_T;


#define FTW_NUM_UAM_BUFS 3
#endif
