#ifndef _FTW_CONFIG_H_
#define _FTW_CONFIG_H_

#include "app_defines_builder.h"
#include "ftw_includes.h"
#include "ftw_net.h"
#include "ftw_mqtt.h"


#define APP_WPS_TYPE_PB         1
#define APP_WPS_TYPE_PIN        2
#define APP_WPS_TYPE_DFLT_PIN   3

#ifdef FTW_UART_ENABLE
#if !defined(FTW_DEFAULT_UART_BAUD) || !((FTW_DEFAULT_UART_BAUD == 9600)||(FTW_DEFAULT_UART_BAUD == 19200)||(FTW_DEFAULT_UART_BAUD == 38400)||(FTW_DEFAULT_UART_BAUD == 57600)||(FTW_DEFAULT_UART_BAUD == 115200) || (FTW_DEFAULT_UART_BAUD == 230400)|| (FTW_DEFAULT_UART_BAUD == 460800)|| (FTW_DEFAULT_UART_BAUD == 921600))
#error "NOT A VALID UART BUAD RATE"
#endif

#if !defined(FTW_DEFAULT_UART_BITS_PER_CHAR) || !((FTW_DEFAULT_UART_BITS_PER_CHAR == 0)||(FTW_DEFAULT_UART_BITS_PER_CHAR == 1)||(FTW_DEFAULT_UART_BITS_PER_CHAR == 2)||(FTW_DEFAULT_UART_BITS_PER_CHAR == 3))
#error "NOT A VALID UART BITS PER CHAR"
#endif

#if !defined(FTW_DEFAULT_UART_PARITY) || !((FTW_DEFAULT_UART_PARITY == 0)||(FTW_DEFAULT_UART_PARITY == 1)||(FTW_DEFAULT_UART_PARITY == 4)|| (FTW_DEFAULT_UART_PARITY == 2))
#error "NOT A VALID UART PARITY"
#endif

#if !defined(FTW_DEFAULT_UART_STOP_BITS) || !((FTW_DEFAULT_UART_STOP_BITS == 0)||(FTW_DEFAULT_UART_STOP_BITS == 1))
#error "NOT A VALID UART STOP BITS"
#endif

#if !defined(FTW_DEFAULT_UART_SW_FLOW) || !((FTW_DEFAULT_UART_SW_FLOW == 0)||(FTW_DEFAULT_UART_SW_FLOW == 1))
#error "NOT A VALID UART SW FLOW"
#endif

#if !defined(FTW_DEFAULT_UART_HW_FLOW) || !((FTW_DEFAULT_UART_HW_FLOW == 0)||(FTW_DEFAULT_UART_HW_FLOW == 1))
#error "NOT A VALID HW FLOW"
#endif

#endif

#ifdef FTW_FS_SPI_ENABLE

#if !((FTW_DEFAULT_SPI_PHASE == 0)||(FTW_DEFAULT_SPI_PHASE == 1))
#error "NOT A VALID SPI PHASE"
#endif

#if !((FTW_DEFAULT_SPI_POLARITY == 0)||(FTW_DEFAULT_SPI_POLARITY == 1))
#error "NOT A VALID SPI POLARIRT"
#endif

#endif

/** OEM Identification */
#define FTW_OEM_ID                 "GainSpan"

/** Hardware version */
#ifdef GS2100
#define FTW_HW_VERSION             "GS2100"
#define APP_FTW_ASYNC_GPIO_MUX   GSN_IOMUX_GPIO_9_AGPIO_9
#define APP_FTW_ASYNC_GPIO            9
#define APP_FTW_ASYNC_GPIO_BITMAP    (1<<9)
#else
#define FTW_HW_VERSION             "GS2011"
#define APP_FTW_ASYNC_GPIO_BITMAP    (1<<19)
#define APP_FTW_ASYNC_GPIO_MUX    GSN_IOMUX_GPIO_19_AGPIO_19
#define APP_FTW_ASYNC_GPIO            19
#endif

/**File system structure versions:
 */
#define FTW_PROFILE_DFLT_VERSION        0x100
#define FTW_PROFILE_PARAM_DFLT_VERSION  0x100

/** Software version */
#define FTW_SW_VERSION                  "5.1.5"
#define FTW_SW_EXT_VERSION              "10"

#ifndef FTW_BIN_TYPE
#define FTW_BIN_TYPE                    "DEFAULT"
#endif
#define FTW_RELEASE_TYPE                "GA"

#define MAKEIP(a,b,c,d) ((ULONG)a<<24 | (ULONG)b << 16 | (ULONG)c << 8 | (ULONG)d )

#define FTW_DHCP_MAX_RETRY_COUNT        5


/** Default antenna selection - U.Fl Antenna  */
#define FTW_DEFAULT_WLAN_ANTENNA_MODE   0x02
/** Default wlan keep alive counter for GS1500M  */
#define FTW_DEFAULT_WKEEP_ALIVE_COUNTER 20

#ifndef FTW_DEFAULT_WLAN_MODE
/** Default 802.11 operating mode. */
#define FTW_DEFAULT_WLAN_MODE       FTW_WLANDATA_MODE_INFRA
#endif

#define FTW_DEFAULT_MODECHANGE_WAIT_PERIOD   10  // msec


#ifndef FTW_DEFAULT_AC_WLAN_MODE
/** Default Auto-Connect 802.11 operating mode. */
#define FTW_DEFAULT_AC_WLAN_MODE    FTW_WLANDATA_MODE_INFRA
#endif

/** Default 802.11 operating channel. */
#ifndef FTW_DEFAULT_AC_WLAN_CHANNEL
#define FTW_DEFAULT_AC_WLAN_CHANNEL 6
#endif

/** Default Network SSID. */
#ifndef FTW_DEFAULT_AC_WLAN_SSID
#define FTW_DEFAULT_AC_WLAN_SSID    "FTW"
#endif

#ifndef FTW_DEFAULT_REG_DOMAIN
    #define FTW_DEFAULT_REG_DOMAIN 0  // fcc
#endif

#ifndef FTW_DEFAULT_WLAN_MODE_RATE
    #define FTW_DEFAULT_WLAN_MODE_RATE 0
#endif


#ifndef FTW_DEFAULT_SECURITY
    #define FTW_DEFAULT_SECURITY 0
#endif

/** Indicates if the default autoconnect BSSID is supplied */
#ifndef FTW_DEFAULT_AC_WLAN_BSSID_VALID
#define FTW_DEFAULT_AC_WLAN_BSSID_VALID 0

/** Default autoconnect BSSID */
static const UINT8 FTW_DEFAULT_AC_WLAN_BSSID[6] =
                    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif

#ifndef FTW_DEFAULT_STA_MAC_ADDR_VALID

static const UINT8 FTW_DEFAULT_STA_MAC_ADDR[6] =
                    {0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00};
#endif

#ifndef FTW_DEFAULT_RETRY_COUNT
    #define FTW_DEFAULT_RETRY_COUNT     8
#endif

#ifndef FTW_DEFAULT_MAC_ACK_MISS_COUNT
    #define FTW_DEFAULT_MAC_ACK_MISS_COUNT 20
#endif

/** Default scan time (in milliseconds) */
#define FTW_DEFAULT_SCAN_TIME                   150

#ifndef FTW_DEFAULT_SCAN_MIN_TIME
    #define FTW_DEFAULT_SCAN_MIN_TIME               150
#endif

#ifndef FTW_DEFAULT_STRICT_SECURITY
    #define FTW_DEFAULT_STRICT_SECURITY 0
#endif

#ifndef FTW_DEFAULT_MCAST_RX
   #define FTW_DEFAULT_MCAST_RX   1
#endif

/** Default Retry Count */

/** Default power save */
#ifndef FTW_DEFAULT_POWER_SAVE
    #define FTW_DEFAULT_POWER_SAVE      0
#endif

/** Default radio mode */
#ifndef FTW_DEFAULT_RADIO_MODE
    #define FTW_DEFAULT_RADIO_MODE      1
#endif

/** syncloss */
#ifndef FTW_DEFAULT_SYNCLOSS_INTERVAL
    #define FTW_DEFAULT_SYNCLOSS_INTERVAL 100
#endif

#ifndef FTW_DEFAULT_LISTEN_INTERVAL
    #define FTW_DEFAULT_LISTEN_INTERVAL 0
#endif


#ifndef FTW_DEFAULT_KEEPALIVE_INTERVAL
    #define FTW_DEFAULT_KEEPALIVE_INTERVAL 45
#endif

/****
  Group Provisioning(AP) Parameters
 */


#ifndef FTW_DEFAULT_AUTO_START
    #define FTW_DEFAULT_AUTO_START            0
#endif

#ifndef FTW_DEFAULT_GRP_PROV_SSID
    #define FTW_DEFAULT_GRP_PROV_SSID         "FTW_PROV_"
#endif

#ifndef FTW_DEFAULT_GRP_PROV_CHANNEL
    #define FTW_DEFAULT_GRP_PROV_CHANNEL      6
#endif

#ifndef FTW_DEFAULT_GRP_PROV_REG_DOMAIN
    #define FTW_DEFAULT_GRP_PROV_REG_DOMAIN   0
#endif

#ifndef FTW_DEFAULT_GRP_PROV_SECURITY
    #define FTW_DEFAULT_GRP_PROV_SECURITY     0  //0-->open,1-->wep , 2--> wpa
#endif

#ifndef FTW_DEFAULT_GRP_PROV_WEP_AUTH
    #define FTW_DEFAULT_GRP_PROV_WEP_AUTH     1   //1-->open , 2 -->shared
#endif

#ifndef FTW_DEFAULT_GRP_PROV_WEP_KEY_LEN
    #define FTW_DEFAULT_GRP_PROV_WEP_KEY_LEN  5   // 5 or 13
#endif


#ifndef FTW_DEFAULT_GRP_PROV_WEP_KEY_ID
    static const UINT8 FTW_DEFAULT_GRP_PROV_WEP_KEY[FTW_DEFAULT_GRP_PROV_WEP_KEY_LEN] ={0x12, 0x34, 0x56, 0x78, 0x90};
#endif

#ifndef FTW_DEFAULT_GRP_PROV_WEP_KEY_ID
    #define FTW_DEFAULT_GRP_PROV_WEP_KEY_ID   1   // 1 to 4
#endif


#ifndef FTW_DEFAULT_GRP_PROV_WPA_PASSPHRASE
    #define FTW_DEFAULT_GRP_PROV_WPA_PASSPHRASE     "Serial2Wifi"
#endif

#ifndef FTW_DEFAULT_GRP_PROV_BEACON_INTERVAL
    #define FTW_DEFAULT_GRP_PROV_BEACON_INTERVAL   100  // msec
#endif

#ifndef FTW_DEFAULT_GRP_PROV_SSID_BROADCAST
    #define FTW_DEFAULT_GRP_PROV_SSID_BROADCAST    1  // 0->disable
#endif

#ifndef FTW_DEFAULT_GRP_PROV_SUPPORTED_STATIONS
    #define FTW_DEFAULT_GRP_PROV_SUPPORTED_STATIONS        8
#endif

#ifndef FTW_DEFAULT_GRP_PROV_IP_ADDRESS
    #define FTW_DEFAULT_GRP_PROV_IP_ADDRESS            MAKEIP(192,168,240,1)
#endif

#ifndef FTW_DEFAULT_GRP_PROV_SUBNET_ADDRESS
    #define FTW_DEFAULT_GRP_PROV_SUBNET_ADDRESS        MAKEIP(255,255,255,0)
#endif

#ifndef FTW_DEFAULT_GRP_PROV_GATE_ADDRESS
    #define FTW_DEFAULT_GRP_PROV_GATE_ADDRESS          MAKEIP(192,168,240,1)
#endif

#ifndef FTW_DEFAULT_GRP_PROV_IP_START_ADDRESS
    #define FTW_DEFAULT_GRP_PROV_IP_START_ADDRESS      MAKEIP(192,168,240,2)
#endif

#ifndef FTW_DEFAULT_GRP_PROV_DNS_NAME
    #define FTW_DEFAULT_GRP_PROV_DNS_NAME             "config.gainspan\0"
#endif

#ifndef FTW_DEFAULT_GRP_PROV_DHCPSRVR_ENABLE
    #define FTW_DEFAULT_GRP_PROV_DHCPSRVR_ENABLE       1
#endif

#ifndef FTW_DEFAULT_GRP_PROV_DNSSRVR_ENABLE
    #define FTW_DEFAULT_GRP_PROV_DNSSRVR_ENABLE        1
#endif


#ifndef FTW_DEFAULT_GRP_PROV_LEASE_TIME
#define FTW_DEFAULT_GRP_PROV_LEASE_TIME    86400  // 24 houres
#endif


/****
 */


/** Default network connection mode. */
#define FTW_DEFAULT_AC_NET_MODE     FTW_NETDATA_MODE_CLIENT
/** Default network connection protocol type. */
#define FTW_DEFAULT_AC_NET_PROTO    FTW_NETDATA_PROTO_TCP
/** Default Server port. */
#define FTW_DEFAULT_AC_NET_PORT     8
/** Default Server IP address. */
#define FTW_DEFAULT_AC_NET_IP_ADDR  MAKEIP(1,1,168,192)
/** Default Transmit power. */
#define FTW_DEFAULT_TX_POWER        0
#define FTW_DEFAULT_TX_EXT_PA_POWER        2


/** Default Network configuration mode.*/
#ifndef FTW_DEFAULT_USE_DHCP
#define FTW_DEFAULT_USE_DHCP        0
#endif
/** Default IP address. */
#ifndef FTW_DEFAULT_IP_ADDR
#define FTW_DEFAULT_IP_ADDR         MAKEIP(192,168,1,99)
#endif
/** Default Net Mask. */
#ifndef FTW_DEFAULT_NET_MASK
#define FTW_DEFAULT_NET_MASK        MAKEIP(255,255,255,0)
#endif
/** Default Gateway. */
#ifndef FTW_DEFAULT_GATEWAY
#define FTW_DEFAULT_GATEWAY         MAKEIP(192,168,1,1)
#endif
/** Default UART echo mode. */
#define FTW_DEFAULT_ECHO            1
/** Default verbose mode. */
#define FTW_DEFAULT_VERBOSE         1
/** Default Serial baud rate. */
#ifdef FTW_IP2WIFI_SUPPORT
#define FTW_DEFAULT_BAUD_RATE       FTW_DEFAULT_UART_BAUD
#else
#define FTW_DEFAULT_BAUD_RATE       FTW_DEFAULT_UART_BAUD
#endif

/** Default value of Serial bits per character. */
#define FTW_DEFAULT_BITS_PER_CHAR   FTW_DEFAULT_UART_BITS_PER_CHAR
/** Default stop bit. */
#define FTW_DEFAULT_STOP_BITS       FTW_DEFAULT_UART_STOP_BITS
/** Default parity. */
#define FTW_DEFAULT_PARITY          FTW_DEFAULT_UART_PARITY
/** Default software flow control. */
#define FTW_DEFAULT_SOFTWARE_FLOW_CONTROL FTW_DEFAULT_UART_SW_FLOW
/** Default hardware flow control. */
#define FTW_DEFAULT_HARDWARE_FLOW_CONTROL FTW_DEFAULT_UART_HW_FLOW

#ifndef FTW_DEFAULT_WEP_AUTH_MODE
/** Default authentication mode */
#define FTW_DEFAULT_WEP_AUTH_MODE       FTW_AUTH_MODE_NONE
#endif
/** Specifies which default keys are specified */
#define FTW_DEFAULT_VALID_KEYS      (FTW_SECURITY_VALID_WEP | FTW_SECURITY_VALID_WPA)

#ifndef FTW_DEFAULT_WEP_KEY_LEN
/** Length of the default WEP key index 1 */
#define FTW_DEFAULT_WEP_KEY_LEN   5
static const UINT8 FTW_DEFAULT_WEP_KEY[FTW_DEFAULT_WEP_KEY_LEN] =
                                    {0x12, 0x34, 0x56, 0x78, 0x90};
#endif

#ifndef FTW_DEFAULT_WEP_KEY_ID
#define FTW_DEFAULT_WEP_KEY_ID   1

#endif
#ifndef FTW_DEFAULT_AP_AUTH_MODE
#define FTW_DEFAULT_AP_AUTH_MODE FTW_AUTH_MODE_NONE
#endif
#ifndef FTW_DEFAULT_AP_WEP_KEY_INDEX
#define FTW_DEFAULT_AP_WEP_KEY_INDEX   1
#endif
#ifndef FTW_DEFAULT_AP_WEP_KEY_LEN
#define FTW_DEFAULT_AP_WEP_KEY_LEN   5
static const UINT8 FTW_DEFAULT_AP_WEP_KEY[FTW_DEFAULT_AP_WEP_KEY_LEN] =
                                    {0x12, 0x34, 0x56, 0x78, 0x90};
#endif
/** Indicates if the default WPA passphrase is supplied */
#define FTW_DEFAULT_WPA_PASSPHRASE_VALID 1

#ifndef FTW_DEFAULT_WPA_PASSPHRASE
/** Default WPA passphrase */
#define FTW_DEFAULT_WPA_PASSPHRASE  "Serial2Wifi"
#endif
#ifndef FTW_DEFAULT_EAP_USERNAME
#define FTW_DEFAULT_EAP_USERNAME "gsn"
#endif
#ifndef FTW_DEFAULT_EAP_PWD
#define FTW_DEFAULT_EAP_PWD "GSDemo123"
#endif
#ifndef FTW_DEFAULT_EAP_USE_CA_CERT
#define FTW_DEFAULT_EAP_USE_CA_CERT 0
#endif
#ifndef FTW_DEFAULT_EAP_INNERAUTH
#define FTW_DEFAULT_EAP_INNERAUTH 0
#endif
#ifndef FTW_DEFAULT_EAP_OUTERAUTH
#define FTW_DEFAULT_EAP_OUTERAUTH 0
#endif
#ifndef FTW_DEFAULT_AP_WPA_PASSPHRASE
#define FTW_DEFAULT_AP_WPA_PASSPHRASE "1234567890"
#endif

/* Unit is 10ms */
/** Default value of Auto association timeout. */
#define FTW_DEFAULT_AUTO_ASSOC_TIMEOUT          500
/** Default value of network connection timeout. */
#define FTW_DEFAULT_NET_CONNECTION_TIMEOUT      1000
/** Default value of TCP connection timeout. */
#define FTW_DEFAULT_TCP_CONNECT_TIMEOUT         7500
/** Default Nagle wait time. */
#define FTW_DEFAULT_NAGLE_WAIT_TIME             10
/** Default Association retry count. */
#define FTW_DEFAULT_ASSOCIATION_RETRY_COUNT     3
/** Default Wireless Count. */
#define FTW_DEFAULT_WIRELESS_RETRY_COUNT        4

#ifndef FTW_DFLT_AUTO_EXIT_TIMEOUT
#define FTW_DFLT_AUTO_EXIT_TIMEOUT              100 // (100 *10 mesc ) 1 sec
#endif
/*S2w SPI port specific config default */

#define FTW_DEFAULT_SPI_CLI_INBAND_FLOW_CONTROL 1     /* Default value of  inband flow control             */
#define FTW_DEFAULT_SPI_ECHO                    1     /** Default echo mode for S2w SPI interface     */
#define FTW_DEFAULT_SPI_VERBOSE                 1     /** Default verbose mode for S2w SPI interface */
/**SPI clock operation mode for S2W application interface
** Note: This configuration must match with Host SPI settting
*/
#define  FTW_SPI_CLK_MODE_0  1  /* MODE -0   [SCPO =0 And SCPH=0 ]*/
#define  FTW_SPI_CLK_MODE_1  0  /* MODE -1   [SCPO =0 And SCPH=1 ] */
#define  FTW_SPI_CLK_MODE_2  0  /* MODE -2   [SCPO =1 And SCPH=0 ]*/
#define  FTW_SPI_CLK_MODE_3  0  /* MODE -3   [SCPO =1 And SCPH=1 ] */
/**SPI Clock polarity and clock phase for S2W application interface  */
#if FTW_SPI_CLK_MODE_0
/*  MODE-0   [SCPO =0 And SCPH=0 ]*/
#define FTW_SPI_DEFAULT_CLK_POL                 FTW_DEFAULT_SPI_POLARITY//GSN_SPI_CLK_POL_INACTIVELOW
#define FTW_SPI_DEFAULT_CLK_PHASE               FTW_DEFAULT_SPI_PHASE//GSN_SPI_CLK_PHASE_0
#endif

#if FTW_SPI_CLK_MODE_1
/*  In this mode GS1011 acting as a Slave allows the remote Master to send consecutive words without
**   any gap between the words.
*/
/*  MODE-1   [SCPO =0 And SCPH=1 ]*/
#define FTW_SPI_DEFAULT_CLK_POL                 GSN_SPI_CLK_POL_INACTIVELOW
#define FTW_SPI_DEFAULT_CLK_PHASE               GSN_SPI_CLK_PHASE_180
#endif

#if FTW_SPI_CLK_MODE_2
/*  MODE-2   [SCPO =1 And SCPH=0 ]*/
#define FTW_SPI_DEFAULT_CLK_POL                 GSN_SPI_CLK_POL_INACTIVEHIGH
#define FTW_SPI_DEFAULT_CLK_PHASE               GSN_SPI_CLK_PHASE_0
#endif

#if FTW_SPI_CLK_MODE_3
/*  MODE-3  [SCPO =1 And SCPH=1 ]*/
#define FTW_SPI_DEFAULT_CLK_POL                 GSN_SPI_CLK_POL_INACTIVEHIGH
#define FTW_SPI_DEFAULT_CLK_PHASE               GSN_SPI_CLK_PHASE_180
#endif

#ifdef GS1500M
#define FTW_P2P_CLIENT_MAX_CONNECT_RETRY     12
#endif

// ncm  default congigs
#ifndef FTW_NCM_DFLT_CPUWAIT_PERIOD
#define FTW_NCM_DFLT_CPUWAIT_PERIOD       1000 // in msec
#endif

#ifndef FTW_NCM_DFLT_KNOWNCH_SCAN_PERIOD
#define FTW_NCM_DFLT_KNOWNCH_SCAN_PERIOD  1000
#endif

#define FTW_NCM_DFLT_SPECCH_SCAN_PERIOD   1000

#ifndef FTW_NCM_DFLT_ALLCH_SCAN_PERIOD
#define FTW_NCM_DFLT_ALLCH_SCAN_PERIOD    1000
#endif

#ifndef FTW_NCM_DFLT_L3CONNECT_PERIOD
#define FTW_NCM_DFLT_L3CONNECT_PERIOD     1000
#endif

#ifndef FTW_NCM_DFLT_KNOWNCH_SCAN_COUNT
#define FTW_NCM_DFLT_KNOWNCH_SCAN_COUNT  10
#endif

#define FTW_NCM_DFLT_SPECCH_SCAN_COUNT  1

#ifndef FTW_NCM_DFLT_ALLCH_SCAN_COUNT
#define FTW_NCM_DFLT_ALLCH_SCAN_COUNT  10
#endif

#ifndef FTW_NCM_DFLT_L3CONNECT_COUNT
#define FTW_NCM_DFLT_L3CONNECT_COUNT  100
#endif

#ifndef FTW_NCM_DFLT_DTIMPERIOD_VALUE
#define FTW_NCM_DFLT_DTIMPERIOD_VALUE   3
#endif
#ifndef FTW_NCM_DFLT_INACTIVITY_TMEOUT_VALUE
#define FTW_NCM_DFLT_INACTIVITY_TMEOUT_VALUE   360
#endif

#ifndef FTW_NCM_DFLT_GRP_KEY_UPDATE_INTERVAL
#define FTW_NCM_DFLT_GRP_KEY_UPDATE_INTERVAL   3600
#endif

#ifndef FTW_NCM_DFLT_L4CONNECT_PERIOD
    #define FTW_NCM_DFLT_L4CONNECT_PERIOD 50
#endif

#ifndef FTW_NCM_DFLT_L4CONNECT_COUNT
    #define FTW_NCM_DFLT_L4CONNECT_COUNT   3
#endif

#ifndef FTW_NCM_DFLT_ROAMING
    #define FTW_NCM_DFLT_ROAMING 0
#endif

#ifndef FTW_NCM_DFLT_ROAMING_LOW_RSSI_THRESH
    #define FTW_NCM_DFLT_ROAMING_LOW_RSSI_THRESH  70
#endif

#ifndef FTW_NCM_DFLT_ROAMING_HIGH_RSSI_THRESH
    #define FTW_NCM_DFLT_ROAMING_HIGH_RSSI_THRESH  50
#endif

#ifndef FTW_NCM_DFLT_ROAMING_BACKGROUND_SCAN_TIME
    #define FTW_NCM_DFLT_ROAMING_BACKGROUND_SCAN_TIME   1000 //msec
#endif

#ifdef FTW_NCM_ROAMING_SUPPORT

#define FTW_NCM_ROAM_DFLT_ROAMEN  1
#define FTW_NCM_ROAM_DFLT_ROAMDIS 0
#define FTW_NCM_ROAM_DFLT_RSSILOWERTH  170 // -70 db
#define FTW_NCM_ROAM_DFLT_RSSIHIGHERTH 220 // -50 db
#define FTW_NCM_ROAM_DFLT_RSSICHKINTERVAL 1000
#define FTW_NCM_ROAM_DFLT_THCROSSEDCNT  3
#define FTW_NCM_ROAM_DFLT_MAINTAINL3CON   1
#define FTW_NCM_ROAM_DFLT_MAINTAINL4CON   0
#define FTW_NCM_ROAM_DFLT_SCANRETRYCOUNT  5
#define FTW_NCM_ROAM_DFLT_SCANPUASETIME   5000

#endif


// default AP paramters

#ifndef FTW_DEFAULT_AP_MAC_ADDR_VALID

static const UINT8 FTW_DEFAULT_AP_MAC_ADDR[6] =
                    {0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00};
#endif


#ifndef FTW_DEFAULT_AP_WLAN_SSID
#define FTW_DEFAULT_AP_WLAN_SSID                "GainSpanProv"
#endif

#ifndef FTW_DEFAULT_AP_WLAN_CHANNEL
#define FTW_DEFAULT_AP_WLAN_CHANNEL                    1
#endif

#ifndef FTW_DEFAULT_AP_REG_DOMAIN
#define FTW_DEFAULT_AP_REG_DOMAIN           0
#endif

#ifndef FTW_DEFAULT_AP_SECURITY
#define FTW_DEFAULT_AP_SECURITY              0
#endif

#ifndef FTW_DEFAULT_AP_BEACON_INTERVAL
#define FTW_DEFAULT_AP_BEACON_INTERVAL          100
#endif

#ifndef FTW_DEFAULT_AP_SUPPORTED_STATIONS
#define FTW_DEFAULT_AP_SUPPORTED_STATIONS      8
#endif

#ifndef FTW_DFLT_AP_DHCPSRVR_LEASE_TIME
#define FTW_DFLT_AP_DHCPSRVR_LEASE_TIME    86400 // 24 hours in seconds
#endif

#ifndef FTW_DFLT_AP_DNS_IP1
#define FTW_DFLT_AP_DNS_IP1               MAKEIP(192,168,1,1)
#endif

#ifndef FTW_DFLT_AP_DNS_IP2
#define FTW_DFLT_AP_DNS_IP2               MAKEIP(192,168,1,2)
#endif

#ifndef FTW_DFLT_AP_DHCPSRVR_ENABLE
#define FTW_DFLT_AP_DHCPSRVR_ENABLE       1
#endif

#ifndef FTW_DFLT_AP_DNSSRVR_ENABLE
#define FTW_DFLT_AP_DNSSRVR_ENABLE        1
#endif


#ifndef FTW_DFLT_AP_IP_ADDRESS
#define FTW_DFLT_AP_IP_ADDRESS            MAKEIP(192,168,240,1)
#endif

#ifndef FTW_DFLT_AP_SUBNET_ADDRESS
#define FTW_DFLT_AP_SUBNET_ADDRESS        MAKEIP(255,255,255,0)
#endif

#ifndef FTW_DFLT_AP_GATE_ADDRESS
#define FTW_DFLT_AP_GATE_ADDRESS          MAKEIP(192,168,240,1)
#endif

#ifndef FTW_DFLT_AP_IP_START_ADDRESS
#define FTW_DFLT_AP_IP_START_ADDRESS      MAKEIP(192,168,240,2)
#endif

#ifndef FTW_DFLT_AP_DNS_NAME
#define FTW_DFLT_AP_DNS_NAME             "config.gainspan\0"
#endif

#ifndef FTW_DFLT_AP_HOST_NAME
#define FTW_DFLT_AP_HOST_NAME            "GAINSPAN"
#endif

//#define FTW_DFLT_PROV_USERNAME             "admin"
//#define FTW_DFLT_PROV_PWD                  "admin"



#ifndef FTW_DFLT_MDNS_HOST_NAME
#define FTW_DFLT_MDNS_HOST_NAME           "gainspan"
#endif


#ifndef FTW_DFLT_MDNS_SER_INST_NAME
#define FTW_DFLT_MDNS_SER_INST_NAME      "gainspan"
#endif

#ifndef FTW_DFLT_MDNS_SER_SUB_TYPE
#define FTW_DFLT_MDNS_SER_SUB_TYPE		""
#endif

#ifndef FTW_DFLT_MDNS_SER_TYPE
#define FTW_DFLT_MDNS_SER_TYPE            "_http"
#endif
#ifndef FTW_GRPPROV_VERIFY_MDNSSER_TYPE
#define FTW_GRPPROV_VERIFY_MDNSSER_TYPE		"_guid"
#endif

#ifndef FTW_DFLT_MDNS_PROTO
#define FTW_DFLT_MDNS_PROTO               "_tcp"
#endif

#ifndef FTW_DFLT_MDNS_DOMAIN_NAME
#define FTW_DFLT_MDNS_DOMAIN_NAME         "local"
#endif
#ifndef FTW_DFLT_MDNS_PORT
#define FTW_DFLT_MDNS_PORT                  80
#endif

#ifndef FTW_DFLT_MDNS_KEY
#define FTW_DFLT_MDNS_KEY                   1
#endif

#ifndef FTW_DFLT_MDNS_TXT_RECORD
#define FTW_DFLT_MDNS_TXT_RECORD           "api=gs_sys_prov:1.0.1:/gainspan/system/api"
#endif

#ifndef FTW_DFLT_MDNS_AUTOCORRECT
#define FTW_DFLT_MDNS_AUTOCORRECT         1
#endif

#ifndef FTW_DFLT_MDNS_SCOPE
#define FTW_DFLT_MDNS_SCOPE               0
#endif

#ifndef FTW_DFLT_MDNS_CONFLICT_DETECT
#define FTW_DFLT_MDNS_CONFLICT_DETECT       1
#endif

#ifndef FTW_DFLT_MDNS_TTL
#define FTW_DFLT_MDNS_TTL                   10
#endif

#ifndef FTW_DFLT_HTTPC_TYPE
#define FTW_DFLT_HTTPC_TYPE                 0 // 0 http 1 ->https
#endif


#ifndef FTW_DFLT_SNTP_SVR_IP
#define FTW_DFLT_SNTP_SVR_IP                MAKEIP(192,168,1,1)
#endif

#ifndef FTW_DFLT_SNTP_TIMEOUT
#define FTW_DFLT_SNTP_TIMEOUT                100
#endif

#ifndef FTW_DFLT_SNTP_PERIODIC
#define FTW_DFLT_SNTP_PERIODIC                0
#endif

#ifndef FTW_DFLT_SNTP_PERIODIC_PERIOD
#define FTW_DFLT_SNTP_PERIODIC_PERIOD         10
#endif


#ifndef FTW_DFLT_HTTP_SRVR_USRNAME
#define FTW_DFLT_HTTP_SRVR_USRNAME      "admin"
#endif

#ifndef FTW_DFLT_HTTP_SRVR_PWD
#define FTW_DFLT_HTTP_SRVR_PWD                 "admin"
#endif

#ifndef FTW_DFLT_HTTP_SRVR_URI
#define FTW_DFLT_HTTP_SRVR_URI          "/gainspan/profile/mcu"
#endif

#ifndef FTW_DFLT_HTTP_SRVR_CONTENT_TYPE
#define FTW_DFLT_HTTP_SRVR_CONTENT_TYPE      0  // xml
#endif

#ifndef FTW_DFLT_HTTP_SRVR_CLIENT_NO
#define FTW_DFLT_HTTP_SRVR_CLIENT_NO         8
#endif

#ifndef FTW_DFLT_HTTP_SRVR_SSL_ENABLE
#define FTW_DFLT_HTTP_SRVR_SSL_ENABLE            0
#endif

#ifndef FTW_DFLT_HTTP_SRVR_IDLE_TIMEOUT
#define FTW_DFLT_HTTP_SRVR_IDLE_TIMEOUT          120
#endif

#ifndef FTW_DFLT_OTAFU_PULL_SRVR_IP
#define FTW_DFLT_OTAFU_PULL_SRVR_IP         MAKEIP(192,168,1,1)
#endif

#ifndef FTW_DFLT_OTAFU_PULL_SRVR_PORT
#define FTW_DFLT_OTAFU_PULL_SRVR_PORT         9000
#endif

#ifndef FTW_DFLT_OTAFU_PULL_PROXY_SRVR
#define FTW_DFLT_OTAFU_PULL_PROXY_SRVR         0
#endif

#ifndef FTW_DFLT_OTAFU_PULL_PROXY_SRVR_IP
#define FTW_DFLT_OTAFU_PULL_PROXY_SRVR_IP         MAKEIP(192,168,1,1)
#endif

#ifndef FTW_DFLT_OTAFU_PULL_PROXY_SRVR_PORT
#define FTW_DFLT_OTAFU_PULL_PROXY_SRVR_PORT         8000
#endif

#ifndef FTW_DFLT_OTAFU_PULL_BIN_URL
#define FTW_DFLT_OTAFU_PULL_BIN_URL         "gainspan.lan"
#endif

#ifndef FTW_DFLT_OTAFU_PULL_SSL
#define FTW_DFLT_OTAFU_PULL_SSL         0
#endif

#ifndef FTW_DFLT_IEEE_PS_CFG_ENABLE
#define FTW_DFLT_IEEE_PS_CFG_ENABLE			0 /*ieee ps enable*/
#endif
#ifndef FTW_DFLT_IEEE_PS_CFG_WAKEUP_TYPE
#define FTW_DFLT_IEEE_PS_CFG_WAKEUP_TYPE		1 /*GSN_WIF_WLAN_STA_PS_WAKEUP_DTIM*/
#endif

#ifndef FTW_DFLT_IEEE_PS_CFG_BEACON_WAIT_DURATION
#define FTW_DFLT_IEEE_PS_CFG_BEACON_WAIT_DURATION	10
#endif

#ifndef FTW_DFLT_IEEE_PS_CFG_WAKEUP_INTERVAL
#define FTW_DFLT_IEEE_PS_CFG_WAKEUP_INTERVAL	5
#endif

#ifndef FTW_DFLT_IEEE_PS_CFG_LISTN_INTVL_ASSOC
#define FTW_DFLT_IEEE_PS_CFG_LISTN_INTVL_ASSOC 	600
#endif

#ifndef FTW_DFLT_IEEE_PS_CFG_DATA_RX_TYPE
#define FTW_DFLT_IEEE_PS_CFG_DATA_RX_TYPE		1 /*GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_PS_POLL*/
#endif



#define FTW_DFLT_PROV_WEP_KEY_INDEX         1
#define FTW_DFLT_PROV_WEP_KEY_LEN           5
static const UINT8 FTW_DFLT_PROV_WEP_KEY[FTW_DFLT_PROV_WEP_KEY_LEN] = {0x12, 0x34, 0x56, 0x78, 0x90};
#define FTW_DFLT_PROV_PASSPHRASE            "GSDemo123"
UINT8 S2w_SaveS2wProfile(FTW_FLASH_PARAMS_T *s2wProfile, UINT8 index);

UINT8 S2w_LoadS2wProfileParams();

UINT8 S2w_LoadS2wProfile(FTW_PROFILE_T *s2wProfile, UINT8 index);

UINT8 S2w_SaveS2wProfileParams(FTW_PROFILE_PARAMS_T*);

UINT8 S2w_LoadMacAddr(UINT8 *macAddr);

UINT8 S2w_SaveMacAddr(const UINT8 *macAddr);
UINT8 S2w_LoadApMacAddr(UINT8 *macAddr);

UINT8 S2w_SaveApMacAddr(const UINT8 *macAddr);

// macros for dual interface
#ifndef FTW_DFLT_INTERFACE2_UART_HWFLO
#define FTW_DFLT_INTERFACE2_UART_HWFLOW     GSN_UART_HW_NO_SUPPORT
#endif
#ifndef FTW_DFLT_INTERFACE2_UART_SWFLOW
#define FTW_DFLT_INTERFACE2_UART_SWFLOW     GSN_UART_SWFLOW_NO_SUPPORT
#endif
#ifndef FTW_DFLT_INTERFACE2_UART_BAUD
#define FTW_DFLT_INTERFACE2_UART_BAUD       GSN_UART_BAUDRATE_9K6
#endif
#ifndef FTW_DFLT_INTERFACE2_UART_DMA
#define FTW_DFLT_INTERFACE2_UART_DMA        GSN_UART_DMA_NO_SUPPORT
#endif
#ifndef FTW_DFLT_INTERFACE2_UART_CHARFORMAT
#define FTW_DFLT_INTERFACE2_UART_CHARFORMAT GSN_UART_CHARFORMAT_8
#endif
#ifndef FTW_DFLT_INTERFACE2_UART_STOPBITS
#define FTW_DFLT_INTERFACE2_UART_STOPBITS   GSN_UART_STOPBITS_1
#endif
#ifndef FTW_DFLT_INTERFACE2_UART_PARITY
#define FTW_DFLT_INTERFACE2_UART_PARITY     GSN_UART_PARITYBIT_NONE
#endif

// old spi
#ifndef FTW_DFLT_INTERFACE2_SPI_POLARITY
#define FTW_DFLT_INTERFACE2_SPI_POLARITY    0
#endif
#ifndef FTW_DFLT_INTERFACE2_SPI_PHASE
#define FTW_DFLT_INTERFACE2_SPI_PHASE       0
#endif

#ifndef FTW_DEFAULT_APP_LOG_LEVEL
#define FTW_DEFAULT_APP_LOG_LEVEL           0
#endif

/**< 802.15.4 configuration */
#ifndef FTW_MAX_NUM_OF_802_15_4_KEY_SUPPORTED
#define FTW_MAX_NUM_OF_802_15_4_KEY_SUPPORTED 2
#endif
#ifndef FTW_MAX_NUM_OF_802_15_4_DEV_SUPPORTED
#define FTW_MAX_NUM_OF_802_15_4_DEV_SUPPORTED 32
#endif
#ifndef FTW_MAX_NUM_OF_802_15_4_SECURITY_LEVEL_SUPPORTED
#define FTW_MAX_NUM_OF_802_15_4_SECURITY_LEVEL_SUPPORTED  3
#endif

/**< Zigbee-IP configuration */
#ifndef FTW_MAX_NUM_OF_NEIGHBOR_SUPPORTED
#define FTW_MAX_NUM_OF_NEIGHBOR_SUPPORTED 64
#endif
#ifndef FTW_MAX_NUM_OF_PARENT_SUPPORTED
#define FTW_MAX_NUM_OF_PARENT_SUPPORTED  2
#endif
#ifndef FTW_MAX_NUM_OF_NODE_SUPPORTED
#define FTW_MAX_NUM_OF_NODE_SUPPORTED    256
#endif

#ifndef APP_CFG_DCDC_TMR_VAL
#ifdef GS2100M_EVB
#define APP_CFG_DCDC_TMR_VAL 20       //600us
#else
#define APP_CFG_DCDC_TMR_VAL 41       //1.25ms
#endif
#endif

#ifndef FTW_DEFAULT_AP_SSID_BROADCAST
#define FTW_DEFAULT_AP_SSID_BROADCAST 	0
#endif

#if defined (FTW_FTC)
#define FTW_DISABLE_WATCHDOG  
#endif

typedef struct  FTW_CONFIG_STRUCT
{
    FTW_NET_CONFIG  xNet;
    FTW_MQTT_CONFIG xMQTT;
}   FTW_CONFIG, _PTR_ FTW_CONFIG_PTR;

FTW_RET FTW_CONFIG_init(char_ptr pFileName);
FTW_RET FTW_CONFIG_loadDefault(void);

FTW_RET FTW_CONFIG_load(char_ptr pFileName);
FTW_RET FTW_CONFIG_save(char_ptr pFileName);

FTW_NET_CONFIG_PTR  FTW_CONFIG_getNet(void);
FTW_MQTT_CONFIG_PTR FTW_CONFIG_getMQTT(void);

#endif
