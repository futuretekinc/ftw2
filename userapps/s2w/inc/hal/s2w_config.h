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
* $RCSfile: s2w_config.h,v $
*
* Description : This file defines the default configuration settings for Serial2WiFi.
*****************************************************************************/

#ifndef S2W_CONFIG_H
#define S2W_CONFIG_H

// XTRA
#undef  S2W_DEFAULT_UART_BAUD
#define S2W_DEFAULT_UART_BAUD   115200


#define APP_WPS_TYPE_PB 1
#define APP_WPS_TYPE_PIN 2
#define APP_WPS_TYPE_DFLT_PIN 3
#ifdef S2W_UART_ENABLE

#if !((S2W_DEFAULT_UART_BAUD == 9600)||(S2W_DEFAULT_UART_BAUD == 19200)||(S2W_DEFAULT_UART_BAUD == 38400)||(S2W_DEFAULT_UART_BAUD == 57600)||(S2W_DEFAULT_UART_BAUD == 115200) || (S2W_DEFAULT_UART_BAUD == 230400)|| (S2W_DEFAULT_UART_BAUD == 460800)|| (S2W_DEFAULT_UART_BAUD == 921600))
#error "NOT A VALID UART BUAD RATE"
#endif

#if !((S2W_DEFAULT_UART_BITS_PER_CHAR == 0)||(S2W_DEFAULT_UART_BITS_PER_CHAR == 1)||(S2W_DEFAULT_UART_BITS_PER_CHAR == 2)||(S2W_DEFAULT_UART_BITS_PER_CHAR == 3))
#error "NOT A VALID UART BITS PER CHAR"
#endif

#if !((S2W_DEFAULT_UART_PARITY == 0)||(S2W_DEFAULT_UART_PARITY == 1)||(S2W_DEFAULT_UART_PARITY == 4)|| (S2W_DEFAULT_UART_PARITY == 2))
#error "NOT A VALID UART PARITY"
#endif

#if !((S2W_DEFAULT_UART_STOP_BITS == 0)||(S2W_DEFAULT_UART_STOP_BITS == 1))
#error "NOT A VALID UART STOP BITS"
#endif

#if !((S2W_DEFAULT_UART_SW_FLOW == 0)||(S2W_DEFAULT_UART_SW_FLOW == 1))
#error "NOT A VALID UART SW FLOW"
#endif

#if !((S2W_DEFAULT_UART_HW_FLOW == 0)||(S2W_DEFAULT_UART_HW_FLOW == 1))
#error "NOT A VALID HW FLOW"
#endif

#endif

#ifdef S2W_FS_SPI_ENABLE

#if !((S2W_DEFAULT_SPI_PHASE == 0)||(S2W_DEFAULT_SPI_PHASE == 1))
#error "NOT A VALID SPI PHASE"
#endif

#if !((S2W_DEFAULT_SPI_POLARITY == 0)||(S2W_DEFAULT_SPI_POLARITY == 1))
#error "NOT A VALID SPI POLARIRT"
#endif

#endif

/** OEM Identification */
#define S2W_OEM_ID                 "GainSpan"

/** Hardware version */
#ifdef GS2100
#define S2W_HW_VERSION             "GS2100"
#define APP_S2W_ASYNC_GPIO_MUX   GSN_IOMUX_GPIO_9_AGPIO_9
#define APP_S2W_ASYNC_GPIO            9
#define APP_S2W_ASYNC_GPIO_BITMAP    (1<<9)
#else
#define S2W_HW_VERSION             "GS2011"
#define APP_S2W_ASYNC_GPIO_BITMAP    (1<<19)
#define APP_S2W_ASYNC_GPIO_MUX    GSN_IOMUX_GPIO_19_AGPIO_19
#define APP_S2W_ASYNC_GPIO            19
#endif

/**File system structure versions:
 */
#define S2W_PROFILE_DFLT_VERSION  0x100
#define S2W_PROFILE_PARAM_DFLT_VERSION 0x100

/** Software version */
#define S2W_SW_VERSION             "5.1.5"
#define S2W_SW_EXT_VERSION         "10"
#ifndef S2W_BIN_TYPE
#define S2W_BIN_TYPE   "DEFAULT"
#endif
#define S2W_RELEASE_TYPE "GA"

#define MAKEIP(a,b,c,d) ((ULONG)a<<24 | (ULONG)b << 16 | (ULONG)c << 8 | (ULONG)d )

#define S2W_DHCP_MAX_RETRY_COUNT  5


/** Default antenna selection - U.Fl Antenna  */
#define S2W_DEFAULT_WLAN_ANTENNA_MODE               0x02
/** Default wlan keep alive counter for GS1500M  */
#define S2W_DEFAULT_WKEEP_ALIVE_COUNTER             20

#ifndef S2W_DEFAULT_WLAN_MODE
/** Default 802.11 operating mode. */
#define S2W_DEFAULT_WLAN_MODE       S2W_WLANDATA_MODE_INFRA
#endif

#define S2W_DEFAULT_MODECHANGE_WAIT_PERIOD   10  // msec


#ifndef S2W_DEFAULT_AC_WLAN_MODE
/** Default Auto-Connect 802.11 operating mode. */
#define S2W_DEFAULT_AC_WLAN_MODE    S2W_WLANDATA_MODE_INFRA
#endif

/** Default 802.11 operating channel. */
#ifndef S2W_DEFAULT_AC_WLAN_CHANNEL
#define S2W_DEFAULT_AC_WLAN_CHANNEL 6
#endif

/** Default Network SSID. */
#ifndef S2W_DEFAULT_AC_WLAN_SSID
#define S2W_DEFAULT_AC_WLAN_SSID    "GSDemoKit"
#endif

#ifndef S2W_DEFAULT_REG_DOMAIN
    #define S2W_DEFAULT_REG_DOMAIN 0  // fcc
#endif

#ifndef S2W_DEFAULT_WLAN_MODE_RATE
    #define S2W_DEFAULT_WLAN_MODE_RATE 0
#endif


#ifndef S2W_DEFAULT_SECURITY
    #define S2W_DEFAULT_SECURITY 0
#endif

/** Indicates if the default autoconnect BSSID is supplied */
#ifndef S2W_DEFAULT_AC_WLAN_BSSID_VALID
#define S2W_DEFAULT_AC_WLAN_BSSID_VALID 0

/** Default autoconnect BSSID */
static const UINT8 S2W_DEFAULT_AC_WLAN_BSSID[6] =
                    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif

#ifndef S2W_DEFAULT_STA_MAC_ADDR_VALID

static const UINT8 S2W_DEFAULT_STA_MAC_ADDR[6] =
                    {0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00};
#endif

#ifndef S2W_DEFAULT_RETRY_COUNT
    #define S2W_DEFAULT_RETRY_COUNT     8
#endif

#ifndef S2W_DEFAULT_MAC_ACK_MISS_COUNT
    #define S2W_DEFAULT_MAC_ACK_MISS_COUNT 20
#endif

/** Default scan time (in milliseconds) */
#define S2W_DEFAULT_SCAN_TIME                   150

#ifndef S2W_DEFAULT_SCAN_MIN_TIME
    #define S2W_DEFAULT_SCAN_MIN_TIME               150
#endif

#ifndef S2W_DEFAULT_STRICT_SECURITY
    #define S2W_DEFAULT_STRICT_SECURITY 0
#endif

#ifndef S2W_DEFAULT_MCAST_RX
   #define S2W_DEFAULT_MCAST_RX   1
#endif

/** Default Retry Count */

/** Default power save */
#ifndef S2W_DEFAULT_POWER_SAVE
    #define S2W_DEFAULT_POWER_SAVE      0
#endif

/** Default radio mode */
#ifndef S2W_DEFAULT_RADIO_MODE
    #define S2W_DEFAULT_RADIO_MODE      1
#endif

/** syncloss */
#ifndef S2W_DEFAULT_SYNCLOSS_INTERVAL
    #define S2W_DEFAULT_SYNCLOSS_INTERVAL 100
#endif

#ifndef S2W_DEFAULT_LISTEN_INTERVAL
    #define S2W_DEFAULT_LISTEN_INTERVAL 0
#endif


#ifndef S2W_DEFAULT_KEEPALIVE_INTERVAL
    #define S2W_DEFAULT_KEEPALIVE_INTERVAL 45
#endif

/****
  Group Provisioning(AP) Parameters
 */


#ifndef S2W_DEFAULT_AUTO_START
    #define S2W_DEFAULT_AUTO_START            0
#endif

#ifndef S2W_DEFAULT_GRP_PROV_SSID
    #define S2W_DEFAULT_GRP_PROV_SSID         "GS_PROV_"
#endif

#ifndef S2W_DEFAULT_GRP_PROV_CHANNEL
    #define S2W_DEFAULT_GRP_PROV_CHANNEL      6
#endif

#ifndef S2W_DEFAULT_GRP_PROV_REG_DOMAIN
    #define S2W_DEFAULT_GRP_PROV_REG_DOMAIN   0
#endif

#ifndef S2W_DEFAULT_GRP_PROV_SECURITY
    #define S2W_DEFAULT_GRP_PROV_SECURITY     0  //0-->open,1-->wep , 2--> wpa
#endif

#ifndef S2W_DEFAULT_GRP_PROV_WEP_AUTH
    #define S2W_DEFAULT_GRP_PROV_WEP_AUTH     1   //1-->open , 2 -->shared
#endif

#ifndef S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN
    #define S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN  5   // 5 or 13
#endif


#ifndef S2W_DEFAULT_GRP_PROV_WEP_KEY_ID
    static const UINT8 S2W_DEFAULT_GRP_PROV_WEP_KEY[S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN] ={0x12, 0x34, 0x56, 0x78, 0x90};
#endif

#ifndef S2W_DEFAULT_GRP_PROV_WEP_KEY_ID
    #define S2W_DEFAULT_GRP_PROV_WEP_KEY_ID   1   // 1 to 4
#endif


#ifndef S2W_DEFAULT_GRP_PROV_WPA_PASSPHRASE
    #define S2W_DEFAULT_GRP_PROV_WPA_PASSPHRASE     "Serial2Wifi"
#endif

#ifndef S2W_DEFAULT_GRP_PROV_BEACON_INTERVAL
    #define S2W_DEFAULT_GRP_PROV_BEACON_INTERVAL   100  // msec
#endif

#ifndef S2W_DEFAULT_GRP_PROV_SSID_BROADCAST
    #define S2W_DEFAULT_GRP_PROV_SSID_BROADCAST    1  // 0->disable
#endif

#ifndef S2W_DEFAULT_GRP_PROV_SUPPORTED_STATIONS
    #define S2W_DEFAULT_GRP_PROV_SUPPORTED_STATIONS        8
#endif

#ifndef S2W_DEFAULT_GRP_PROV_IP_ADDRESS
    #define S2W_DEFAULT_GRP_PROV_IP_ADDRESS            MAKEIP(192,168,240,1)
#endif

#ifndef S2W_DEFAULT_GRP_PROV_SUBNET_ADDRESS
    #define S2W_DEFAULT_GRP_PROV_SUBNET_ADDRESS        MAKEIP(255,255,255,0)
#endif

#ifndef S2W_DEFAULT_GRP_PROV_GATE_ADDRESS
    #define S2W_DEFAULT_GRP_PROV_GATE_ADDRESS          MAKEIP(192,168,240,1)
#endif

#ifndef S2W_DEFAULT_GRP_PROV_IP_START_ADDRESS
    #define S2W_DEFAULT_GRP_PROV_IP_START_ADDRESS      MAKEIP(192,168,240,2)
#endif

#ifndef S2W_DEFAULT_GRP_PROV_DNS_NAME
    #define S2W_DEFAULT_GRP_PROV_DNS_NAME             "config.gainspan\0"
#endif

#ifndef S2W_DEFAULT_GRP_PROV_DHCPSRVR_ENABLE
    #define S2W_DEFAULT_GRP_PROV_DHCPSRVR_ENABLE       1
#endif

#ifndef S2W_DEFAULT_GRP_PROV_DNSSRVR_ENABLE
    #define S2W_DEFAULT_GRP_PROV_DNSSRVR_ENABLE        1
#endif


#ifndef S2W_DEFAULT_GRP_PROV_LEASE_TIME
#define S2W_DEFAULT_GRP_PROV_LEASE_TIME    86400  // 24 houres
#endif


/****
 */


/** Default network connection mode. */
#define S2W_DEFAULT_AC_NET_MODE     S2W_NETDATA_MODE_CLIENT
/** Default network connection protocol type. */
#define S2W_DEFAULT_AC_NET_PROTO    S2W_NETDATA_PROTO_TCP
/** Default Server port. */
#define S2W_DEFAULT_AC_NET_PORT     8
/** Default Server IP address. */
#define S2W_DEFAULT_AC_NET_IP_ADDR  MAKEIP(1,1,168,192)
/** Default Transmit power. */
#define S2W_DEFAULT_TX_POWER        0
#define S2W_DEFAULT_TX_EXT_PA_POWER        2


/** Default Network configuration mode.*/
#ifndef S2W_DEFAULT_USE_DHCP
#define S2W_DEFAULT_USE_DHCP        0
#endif
/** Default IP address. */
#ifndef S2W_DEFAULT_IP_ADDR
#define S2W_DEFAULT_IP_ADDR         MAKEIP(192,168,1,99)
#endif
/** Default Net Mask. */
#ifndef S2W_DEFAULT_NET_MASK
#define S2W_DEFAULT_NET_MASK        MAKEIP(255,255,255,0)
#endif
/** Default Gateway. */
#ifndef S2W_DEFAULT_GATEWAY
#define S2W_DEFAULT_GATEWAY         MAKEIP(192,168,1,1)
#endif
/** Default UART echo mode. */
#define S2W_DEFAULT_ECHO            1
/** Default verbose mode. */
#define S2W_DEFAULT_VERBOSE         1
/** Default Serial baud rate. */
#ifdef S2W_IP2WIFI_SUPPORT
#define S2W_DEFAULT_BAUD_RATE       S2W_DEFAULT_UART_BAUD
#else
#define S2W_DEFAULT_BAUD_RATE       S2W_DEFAULT_UART_BAUD
#endif

/** Default value of Serial bits per character. */
#define S2W_DEFAULT_BITS_PER_CHAR   S2W_DEFAULT_UART_BITS_PER_CHAR
/** Default stop bit. */
#define S2W_DEFAULT_STOP_BITS       S2W_DEFAULT_UART_STOP_BITS
/** Default parity. */
#define S2W_DEFAULT_PARITY          S2W_DEFAULT_UART_PARITY
/** Default software flow control. */
#define S2W_DEFAULT_SOFTWARE_FLOW_CONTROL S2W_DEFAULT_UART_SW_FLOW
/** Default hardware flow control. */
#define S2W_DEFAULT_HARDWARE_FLOW_CONTROL S2W_DEFAULT_UART_HW_FLOW

#ifndef S2W_DEFAULT_WEP_AUTH_MODE
/** Default authentication mode */
#define S2W_DEFAULT_WEP_AUTH_MODE       S2W_AUTH_MODE_NONE
#endif
/** Specifies which default keys are specified */
#define S2W_DEFAULT_VALID_KEYS      (S2W_SECURITY_VALID_WEP | S2W_SECURITY_VALID_WPA)

#ifndef S2W_DEFAULT_WEP_KEY_LEN
/** Length of the default WEP key index 1 */
#define S2W_DEFAULT_WEP_KEY_LEN   5
static const UINT8 S2W_DEFAULT_WEP_KEY[S2W_DEFAULT_WEP_KEY_LEN] =
                                    {0x12, 0x34, 0x56, 0x78, 0x90};
#endif

#ifndef S2W_DEFAULT_WEP_KEY_ID
#define S2W_DEFAULT_WEP_KEY_ID   1

#endif
#ifndef S2W_DEFAULT_AP_AUTH_MODE
#define S2W_DEFAULT_AP_AUTH_MODE S2W_AUTH_MODE_NONE
#endif
#ifndef S2W_DEFAULT_AP_WEP_KEY_INDEX
#define S2W_DEFAULT_AP_WEP_KEY_INDEX   1
#endif
#ifndef S2W_DEFAULT_AP_WEP_KEY_LEN
#define S2W_DEFAULT_AP_WEP_KEY_LEN   5
static const UINT8 S2W_DEFAULT_AP_WEP_KEY[S2W_DEFAULT_AP_WEP_KEY_LEN] =
                                    {0x12, 0x34, 0x56, 0x78, 0x90};
#endif
/** Indicates if the default WPA passphrase is supplied */
#define S2W_DEFAULT_WPA_PASSPHRASE_VALID 1

#ifndef S2W_DEFAULT_WPA_PASSPHRASE
/** Default WPA passphrase */
#define S2W_DEFAULT_WPA_PASSPHRASE  "Serial2Wifi"
#endif
#ifndef S2W_DEFAULT_EAP_USERNAME
#define S2W_DEFAULT_EAP_USERNAME "gsn"
#endif
#ifndef S2W_DEFAULT_EAP_PWD
#define S2W_DEFAULT_EAP_PWD "GSDemo123"
#endif
#ifndef S2W_DEFAULT_EAP_USE_CA_CERT
#define S2W_DEFAULT_EAP_USE_CA_CERT 0
#endif
#ifndef S2W_DEFAULT_EAP_INNERAUTH
#define S2W_DEFAULT_EAP_INNERAUTH 0
#endif
#ifndef S2W_DEFAULT_EAP_OUTERAUTH
#define S2W_DEFAULT_EAP_OUTERAUTH 0
#endif
#ifndef S2W_DEFAULT_AP_WPA_PASSPHRASE
#define S2W_DEFAULT_AP_WPA_PASSPHRASE "1234567890"
#endif

/* Unit is 10ms */
/** Default value of Auto association timeout. */
#define S2W_DEFAULT_AUTO_ASSOC_TIMEOUT          500
/** Default value of network connection timeout. */
#define S2W_DEFAULT_NET_CONNECTION_TIMEOUT      1000
/** Default value of TCP connection timeout. */
#define S2W_DEFAULT_TCP_CONNECT_TIMEOUT         7500
/** Default Nagle wait time. */
#define S2W_DEFAULT_NAGLE_WAIT_TIME             10
/** Default Association retry count. */
#define S2W_DEFAULT_ASSOCIATION_RETRY_COUNT     3
/** Default Wireless Count. */
#define S2W_DEFAULT_WIRELESS_RETRY_COUNT        4

#ifndef S2W_DFLT_AUTO_EXIT_TIMEOUT
#define S2W_DFLT_AUTO_EXIT_TIMEOUT              100 // (100 *10 mesc ) 1 sec
#endif
/*S2w SPI port specific config default */

#define S2W_DEFAULT_SPI_CLI_INBAND_FLOW_CONTROL 1     /* Default value of  inband flow control             */
#define S2W_DEFAULT_SPI_ECHO                    1     /** Default echo mode for S2w SPI interface     */
#define S2W_DEFAULT_SPI_VERBOSE                 1     /** Default verbose mode for S2w SPI interface */
/**SPI clock operation mode for S2W application interface
** Note: This configuration must match with Host SPI settting
*/
#define  S2W_SPI_CLK_MODE_0  1  /*  MODE -0   [SCPO =0 And SCPH=0 ]*/
#define  S2W_SPI_CLK_MODE_1  0  /* MODE  -1   [SCPO =0 And SCPH=1 ] */
#define  S2W_SPI_CLK_MODE_2  0  /*  MODE -2   [SCPO =1 And SCPH=0 ]*/
#define  S2W_SPI_CLK_MODE_3  0  /* MODE  -3   [SCPO =1 And SCPH=1 ] */
/**SPI Clock polarity and clock phase for S2W application interface  */
#if S2W_SPI_CLK_MODE_0
/*  MODE-0   [SCPO =0 And SCPH=0 ]*/
#define S2W_SPI_DEFAULT_CLK_POL                 S2W_DEFAULT_SPI_POLARITY//GSN_SPI_CLK_POL_INACTIVELOW
#define S2W_SPI_DEFAULT_CLK_PHASE               S2W_DEFAULT_SPI_PHASE//GSN_SPI_CLK_PHASE_0
#endif

#if S2W_SPI_CLK_MODE_1
/*  In this mode GS1011 acting as a Slave allows the remote Master to send consecutive words without
**   any gap between the words.
*/
/*  MODE-1   [SCPO =0 And SCPH=1 ]*/
#define S2W_SPI_DEFAULT_CLK_POL                 GSN_SPI_CLK_POL_INACTIVELOW
#define S2W_SPI_DEFAULT_CLK_PHASE               GSN_SPI_CLK_PHASE_180
#endif

#if S2W_SPI_CLK_MODE_2
/*  MODE-2   [SCPO =1 And SCPH=0 ]*/
#define S2W_SPI_DEFAULT_CLK_POL                 GSN_SPI_CLK_POL_INACTIVEHIGH
#define S2W_SPI_DEFAULT_CLK_PHASE               GSN_SPI_CLK_PHASE_0
#endif

#if S2W_SPI_CLK_MODE_3
/*  MODE-3  [SCPO =1 And SCPH=1 ]*/
#define S2W_SPI_DEFAULT_CLK_POL                 GSN_SPI_CLK_POL_INACTIVEHIGH
#define S2W_SPI_DEFAULT_CLK_PHASE               GSN_SPI_CLK_PHASE_180
#endif

#ifdef GS1500M
#define S2W_P2P_CLIENT_MAX_CONNECT_RETRY     12
#endif

// ncm  default congigs
#ifndef S2W_NCM_DFLT_CPUWAIT_PERIOD
#define S2W_NCM_DFLT_CPUWAIT_PERIOD       1000 // in msec
#endif

#ifndef S2W_NCM_DFLT_KNOWNCH_SCAN_PERIOD
#define S2W_NCM_DFLT_KNOWNCH_SCAN_PERIOD  1000
#endif

#define S2W_NCM_DFLT_SPECCH_SCAN_PERIOD   1000

#ifndef S2W_NCM_DFLT_ALLCH_SCAN_PERIOD
#define S2W_NCM_DFLT_ALLCH_SCAN_PERIOD    1000
#endif

#ifndef S2W_NCM_DFLT_L3CONNECT_PERIOD
#define S2W_NCM_DFLT_L3CONNECT_PERIOD     1000
#endif

#ifndef S2W_NCM_DFLT_KNOWNCH_SCAN_COUNT
#define S2W_NCM_DFLT_KNOWNCH_SCAN_COUNT  10
#endif

#define S2W_NCM_DFLT_SPECCH_SCAN_COUNT  1

#ifndef S2W_NCM_DFLT_ALLCH_SCAN_COUNT
#define S2W_NCM_DFLT_ALLCH_SCAN_COUNT  10
#endif

#ifndef S2W_NCM_DFLT_L3CONNECT_COUNT
#define S2W_NCM_DFLT_L3CONNECT_COUNT  100
#endif

#ifndef S2W_NCM_DFLT_DTIMPERIOD_VALUE
#define S2W_NCM_DFLT_DTIMPERIOD_VALUE   3
#endif
#ifndef S2W_NCM_DFLT_INACTIVITY_TMEOUT_VALUE
#define S2W_NCM_DFLT_INACTIVITY_TMEOUT_VALUE   360
#endif

#ifndef S2W_NCM_DFLT_GRP_KEY_UPDATE_INTERVAL
#define S2W_NCM_DFLT_GRP_KEY_UPDATE_INTERVAL   3600
#endif

#ifndef S2W_NCM_DFLT_L4CONNECT_PERIOD
    #define S2W_NCM_DFLT_L4CONNECT_PERIOD 50
#endif

#ifndef S2W_NCM_DFLT_L4CONNECT_COUNT
    #define S2W_NCM_DFLT_L4CONNECT_COUNT   3
#endif

#ifndef S2W_NCM_DFLT_ROAMING
    #define S2W_NCM_DFLT_ROAMING 0
#endif

#ifndef S2W_NCM_DFLT_ROAMING_LOW_RSSI_THRESH
    #define S2W_NCM_DFLT_ROAMING_LOW_RSSI_THRESH  70
#endif

#ifndef S2W_NCM_DFLT_ROAMING_HIGH_RSSI_THRESH
    #define S2W_NCM_DFLT_ROAMING_HIGH_RSSI_THRESH  50
#endif

#ifndef S2W_NCM_DFLT_ROAMING_BACKGROUND_SCAN_TIME
    #define S2W_NCM_DFLT_ROAMING_BACKGROUND_SCAN_TIME   1000 //msec
#endif

#ifdef S2W_NCM_ROAMING_SUPPORT

#define S2W_NCM_ROAM_DFLT_ROAMEN  1
#define S2W_NCM_ROAM_DFLT_ROAMDIS 0
#define S2W_NCM_ROAM_DFLT_RSSILOWERTH  170 // -70 db
#define S2W_NCM_ROAM_DFLT_RSSIHIGHERTH 220 // -50 db
#define S2W_NCM_ROAM_DFLT_RSSICHKINTERVAL 1000
#define S2W_NCM_ROAM_DFLT_THCROSSEDCNT  3
#define S2W_NCM_ROAM_DFLT_MAINTAINL3CON   1
#define S2W_NCM_ROAM_DFLT_MAINTAINL4CON   0
#define S2W_NCM_ROAM_DFLT_SCANRETRYCOUNT  5
#define S2W_NCM_ROAM_DFLT_SCANPUASETIME   5000

#endif


// default AP paramters

#ifndef S2W_DEFAULT_AP_MAC_ADDR_VALID

static const UINT8 S2W_DEFAULT_AP_MAC_ADDR[6] =
                    {0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00};
#endif


#ifndef S2W_DEFAULT_AP_WLAN_SSID
#define S2W_DEFAULT_AP_WLAN_SSID                "GainSpanProv"
#endif

#ifndef S2W_DEFAULT_AP_WLAN_CHANNEL
#define S2W_DEFAULT_AP_WLAN_CHANNEL                    1
#endif

#ifndef S2W_DEFAULT_AP_REG_DOMAIN
#define S2W_DEFAULT_AP_REG_DOMAIN           0
#endif

#ifndef S2W_DEFAULT_AP_SECURITY
#define S2W_DEFAULT_AP_SECURITY              0
#endif

#ifndef S2W_DEFAULT_AP_BEACON_INTERVAL
#define S2W_DEFAULT_AP_BEACON_INTERVAL          100
#endif

#ifndef S2W_DEFAULT_AP_SUPPORTED_STATIONS
#define S2W_DEFAULT_AP_SUPPORTED_STATIONS      8
#endif

#ifndef S2W_DFLT_AP_DHCPSRVR_LEASE_TIME
#define S2W_DFLT_AP_DHCPSRVR_LEASE_TIME    86400 // 24 hours in seconds
#endif

#ifndef S2W_DFLT_AP_DNS_IP1
#define S2W_DFLT_AP_DNS_IP1               MAKEIP(192,168,1,1)
#endif

#ifndef S2W_DFLT_AP_DNS_IP2
#define S2W_DFLT_AP_DNS_IP2               MAKEIP(192,168,1,2)
#endif

#ifndef S2W_DFLT_AP_DHCPSRVR_ENABLE
#define S2W_DFLT_AP_DHCPSRVR_ENABLE       1
#endif

#ifndef S2W_DFLT_AP_DNSSRVR_ENABLE
#define S2W_DFLT_AP_DNSSRVR_ENABLE        1
#endif


#ifndef S2W_DFLT_AP_IP_ADDRESS
#define S2W_DFLT_AP_IP_ADDRESS            MAKEIP(192,168,240,1)
#endif

#ifndef S2W_DFLT_AP_SUBNET_ADDRESS
#define S2W_DFLT_AP_SUBNET_ADDRESS        MAKEIP(255,255,255,0)
#endif

#ifndef S2W_DFLT_AP_GATE_ADDRESS
#define S2W_DFLT_AP_GATE_ADDRESS          MAKEIP(192,168,240,1)
#endif

#ifndef S2W_DFLT_AP_IP_START_ADDRESS
#define S2W_DFLT_AP_IP_START_ADDRESS      MAKEIP(192,168,240,2)
#endif

#ifndef S2W_DFLT_AP_DNS_NAME
#define S2W_DFLT_AP_DNS_NAME             "config.gainspan\0"
#endif

#ifndef S2W_DFLT_AP_HOST_NAME
#define S2W_DFLT_AP_HOST_NAME            "GAINSPAN"
#endif

//#define S2W_DFLT_PROV_USERNAME             "admin"
//#define S2W_DFLT_PROV_PWD                  "admin"



#ifndef S2W_DFLT_MDNS_HOST_NAME
#define S2W_DFLT_MDNS_HOST_NAME           "gainspan"
#endif


#ifndef S2W_DFLT_MDNS_SER_INST_NAME
#define S2W_DFLT_MDNS_SER_INST_NAME      "gainspan"
#endif

#ifndef S2W_DFLT_MDNS_SER_SUB_TYPE
#define S2W_DFLT_MDNS_SER_SUB_TYPE		""
#endif

#ifndef S2W_DFLT_MDNS_SER_TYPE
#define S2W_DFLT_MDNS_SER_TYPE            "_http"
#endif
#ifndef S2W_GRPPROV_VERIFY_MDNSSER_TYPE
#define S2W_GRPPROV_VERIFY_MDNSSER_TYPE		"_guid"
#endif

#ifndef S2W_DFLT_MDNS_PROTO
#define S2W_DFLT_MDNS_PROTO               "_tcp"
#endif

#ifndef S2W_DFLT_MDNS_DOMAIN_NAME
#define S2W_DFLT_MDNS_DOMAIN_NAME         "local"
#endif
#ifndef S2W_DFLT_MDNS_PORT
#define S2W_DFLT_MDNS_PORT                  80
#endif

#ifndef S2W_DFLT_MDNS_KEY
#define S2W_DFLT_MDNS_KEY                   1
#endif

#ifndef S2W_DFLT_MDNS_TXT_RECORD
#define S2W_DFLT_MDNS_TXT_RECORD           "api=gs_sys_prov:1.0.1:/gainspan/system/api"
#endif

#ifndef S2W_DFLT_MDNS_AUTOCORRECT
#define S2W_DFLT_MDNS_AUTOCORRECT         1
#endif

#ifndef S2W_DFLT_MDNS_SCOPE
#define S2W_DFLT_MDNS_SCOPE               0
#endif

#ifndef S2W_DFLT_MDNS_CONFLICT_DETECT
#define S2W_DFLT_MDNS_CONFLICT_DETECT       1
#endif

#ifndef S2W_DFLT_MDNS_TTL
#define S2W_DFLT_MDNS_TTL                   10
#endif

#ifndef S2W_DFLT_HTTPC_TYPE
#define S2W_DFLT_HTTPC_TYPE                 0 // 0 http 1 ->https
#endif


#ifndef S2W_DFLT_SNTP_SVR_IP
#define S2W_DFLT_SNTP_SVR_IP                MAKEIP(192,168,1,1)
#endif

#ifndef S2W_DFLT_SNTP_TIMEOUT
#define S2W_DFLT_SNTP_TIMEOUT                100
#endif

#ifndef S2W_DFLT_SNTP_PERIODIC
#define S2W_DFLT_SNTP_PERIODIC                0
#endif

#ifndef S2W_DFLT_SNTP_PERIODIC_PERIOD
#define S2W_DFLT_SNTP_PERIODIC_PERIOD         10
#endif


#ifndef S2W_DFLT_HTTP_SRVR_USRNAME
#define S2W_DFLT_HTTP_SRVR_USRNAME      "admin"
#endif

#ifndef S2W_DFLT_HTTP_SRVR_PWD
#define S2W_DFLT_HTTP_SRVR_PWD                 "admin"
#endif

#ifndef S2W_DFLT_HTTP_SRVR_URI
#define S2W_DFLT_HTTP_SRVR_URI          "/gainspan/profile/mcu"
#endif

#ifndef S2W_DFLT_HTTP_SRVR_CONTENT_TYPE
#define S2W_DFLT_HTTP_SRVR_CONTENT_TYPE      0  // xml
#endif

#ifndef S2W_DFLT_HTTP_SRVR_CLIENT_NO
#define S2W_DFLT_HTTP_SRVR_CLIENT_NO         8
#endif

#ifndef S2W_DFLT_HTTP_SRVR_SSL_ENABLE
#define S2W_DFLT_HTTP_SRVR_SSL_ENABLE            0
#endif

#ifndef S2W_DFLT_HTTP_SRVR_IDLE_TIMEOUT
#define S2W_DFLT_HTTP_SRVR_IDLE_TIMEOUT          120
#endif

#ifndef S2W_DFLT_OTAFU_PULL_SRVR_IP
#define S2W_DFLT_OTAFU_PULL_SRVR_IP         MAKEIP(192,168,1,1)
#endif

#ifndef S2W_DFLT_OTAFU_PULL_SRVR_PORT
#define S2W_DFLT_OTAFU_PULL_SRVR_PORT         9000
#endif

#ifndef S2W_DFLT_OTAFU_PULL_PROXY_SRVR
#define S2W_DFLT_OTAFU_PULL_PROXY_SRVR         0
#endif

#ifndef S2W_DFLT_OTAFU_PULL_PROXY_SRVR_IP
#define S2W_DFLT_OTAFU_PULL_PROXY_SRVR_IP         MAKEIP(192,168,1,1)
#endif

#ifndef S2W_DFLT_OTAFU_PULL_PROXY_SRVR_PORT
#define S2W_DFLT_OTAFU_PULL_PROXY_SRVR_PORT         8000
#endif

#ifndef S2W_DFLT_OTAFU_PULL_BIN_URL
#define S2W_DFLT_OTAFU_PULL_BIN_URL         "gainspan.lan"
#endif

#ifndef S2W_DFLT_OTAFU_PULL_SSL
#define S2W_DFLT_OTAFU_PULL_SSL         0
#endif

#ifndef S2W_DFLT_IEEE_PS_CFG_ENABLE
#define S2W_DFLT_IEEE_PS_CFG_ENABLE			0 /*ieee ps enable*/
#endif
#ifndef S2W_DFLT_IEEE_PS_CFG_WAKEUP_TYPE
#define S2W_DFLT_IEEE_PS_CFG_WAKEUP_TYPE		1 /*GSN_WIF_WLAN_STA_PS_WAKEUP_DTIM*/
#endif

#ifndef S2W_DFLT_IEEE_PS_CFG_BEACON_WAIT_DURATION
#define S2W_DFLT_IEEE_PS_CFG_BEACON_WAIT_DURATION	10
#endif

#ifndef S2W_DFLT_IEEE_PS_CFG_WAKEUP_INTERVAL
#define S2W_DFLT_IEEE_PS_CFG_WAKEUP_INTERVAL	5
#endif

#ifndef S2W_DFLT_IEEE_PS_CFG_LISTN_INTVL_ASSOC
#define S2W_DFLT_IEEE_PS_CFG_LISTN_INTVL_ASSOC 	600
#endif

#ifndef S2W_DFLT_IEEE_PS_CFG_DATA_RX_TYPE
#define S2W_DFLT_IEEE_PS_CFG_DATA_RX_TYPE		1 /*GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_PS_POLL*/
#endif



#define S2W_DFLT_PROV_WEP_KEY_INDEX         1
#define S2W_DFLT_PROV_WEP_KEY_LEN           5
static const UINT8 S2W_DFLT_PROV_WEP_KEY[S2W_DFLT_PROV_WEP_KEY_LEN] = {0x12, 0x34, 0x56, 0x78, 0x90};
#define S2W_DFLT_PROV_PASSPHRASE            "GSDemo123"
UINT8 S2w_SaveS2wProfile(S2W_FLASH_PARAMS_T *s2wProfile, UINT8 index);

UINT8 S2w_LoadS2wProfileParams();

UINT8 S2w_LoadS2wProfile(S2W_PROFILE_T *s2wProfile, UINT8 index);

UINT8 S2w_SaveS2wProfileParams(S2W_PROFILE_PARAMS_T*);

UINT8 S2w_LoadMacAddr(UINT8 *macAddr);

UINT8 S2w_SaveMacAddr(const UINT8 *macAddr);
UINT8 S2w_LoadApMacAddr(UINT8 *macAddr);

UINT8 S2w_SaveApMacAddr(const UINT8 *macAddr);

// macros for dual interface
#ifndef S2W_DFLT_INTERFACE2_UART_HWFLO
#define S2W_DFLT_INTERFACE2_UART_HWFLOW     GSN_UART_HW_NO_SUPPORT
#endif
#ifndef S2W_DFLT_INTERFACE2_UART_SWFLOW
#define S2W_DFLT_INTERFACE2_UART_SWFLOW     GSN_UART_SWFLOW_NO_SUPPORT
#endif
#ifndef S2W_DFLT_INTERFACE2_UART_BAUD
#define S2W_DFLT_INTERFACE2_UART_BAUD       GSN_UART_BAUDRATE_9K6
#endif
#ifndef S2W_DFLT_INTERFACE2_UART_DMA
#define S2W_DFLT_INTERFACE2_UART_DMA        GSN_UART_DMA_NO_SUPPORT
#endif
#ifndef S2W_DFLT_INTERFACE2_UART_CHARFORMAT
#define S2W_DFLT_INTERFACE2_UART_CHARFORMAT GSN_UART_CHARFORMAT_8
#endif
#ifndef S2W_DFLT_INTERFACE2_UART_STOPBITS
#define S2W_DFLT_INTERFACE2_UART_STOPBITS   GSN_UART_STOPBITS_1
#endif
#ifndef S2W_DFLT_INTERFACE2_UART_PARITY
#define S2W_DFLT_INTERFACE2_UART_PARITY     GSN_UART_PARITYBIT_NONE
#endif

// old spi
#ifndef S2W_DFLT_INTERFACE2_SPI_POLARITY
#define S2W_DFLT_INTERFACE2_SPI_POLARITY    0
#endif
#ifndef S2W_DFLT_INTERFACE2_SPI_PHASE
#define S2W_DFLT_INTERFACE2_SPI_PHASE       0
#endif

#ifndef S2W_DEFAULT_APP_LOG_LEVEL
#define S2W_DEFAULT_APP_LOG_LEVEL           0
#endif

/**< 802.15.4 configuration */
#ifndef S2W_MAX_NUM_OF_802_15_4_KEY_SUPPORTED
#define S2W_MAX_NUM_OF_802_15_4_KEY_SUPPORTED 2
#endif
#ifndef S2W_MAX_NUM_OF_802_15_4_DEV_SUPPORTED
#define S2W_MAX_NUM_OF_802_15_4_DEV_SUPPORTED 32
#endif
#ifndef S2W_MAX_NUM_OF_802_15_4_SECURITY_LEVEL_SUPPORTED
#define S2W_MAX_NUM_OF_802_15_4_SECURITY_LEVEL_SUPPORTED  3
#endif

/**< Zigbee-IP configuration */
#ifndef S2W_MAX_NUM_OF_NEIGHBOR_SUPPORTED
#define S2W_MAX_NUM_OF_NEIGHBOR_SUPPORTED 64
#endif
#ifndef S2W_MAX_NUM_OF_PARENT_SUPPORTED
#define S2W_MAX_NUM_OF_PARENT_SUPPORTED  2
#endif
#ifndef S2W_MAX_NUM_OF_NODE_SUPPORTED
#define S2W_MAX_NUM_OF_NODE_SUPPORTED    256
#endif

#ifndef APP_CFG_DCDC_TMR_VAL
#ifdef GS2100M_EVB
#define APP_CFG_DCDC_TMR_VAL 20       //600us
#else
#define APP_CFG_DCDC_TMR_VAL 41       //1.25ms
#endif
#endif

#ifndef S2W_DEFAULT_AP_SSID_BROADCAST
#define S2W_DEFAULT_AP_SSID_BROADCAST 	0
#endif

#if defined (S2W_FTC)
#define S2W_DISABLE_WATCHDOG  
#endif
#endif
