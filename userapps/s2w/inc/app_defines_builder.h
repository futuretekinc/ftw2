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
* $RCSfile: app_defines_builder.h,v $
*
* Description : This file contains definitions for sdk builder.
*****************************************************************************/
#ifndef _APP_DEFINES_BUILDER_H_
#define _APP_DEFINES_BUILDER_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/


/**
 *****************************************************************************
 * @file app_defines_builder.h
 * @brief S2W SDK builder defines.
 *    This file contains general definitions for builder.
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup S2wAppDefines  definitions.
 *    This group contains general definitions.
 *****************************************************************************/



/*****************************************************************************
 *  Definitions
 ****************************************************************************/
/* default bin type
 */
#define S2W_BIN_TYPE "GS2K_DEFAULT"
/* default mode
 */
#define S2W_DEFAULT_WLAN_MODE 1

/* wlan station specific
 */
//#define  S2W_DEFAULT_STA_MAC_ADDR_VALID           0
     //static const UINT8 S2W_DEFAULT_STA_MAC_ADDR[6] ={0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00};

#define S2W_DEFAULT_AC_WLAN_SSID "GSDemoKit"
#define S2W_DEFAULT_AC_WLAN_CHANNEL 1
#define S2W_DEFAULT_REG_DOMAIN 0
//#define S2W_DEFAULT_WLAN_MODE_RATE       0
//#define S2W_DEFAULT_AC_WLAN_BSSID_VALID  0  // 0->not valid
    //static const UINT8 S2W_DEFAULT_AC_WLAN_BSSID[6] =     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#define S2W_DEFAULT_SECURITY 0

//#define S2W_DEFAULT_WEP_AUTH_MODE        1   //1-->open , 2 -->shared
//#define S2W_DEFAULT_WEP_KEY_ID           1   // 1 to 4
//#define S2W_DEFAULT_WEP_KEY_LEN          5   // 5 or 13
    //static const UINT8 S2W_DEFAULT_WEP_KEY[S2W_DEFAULT_WEP_KEY_LEN] ={0x12, 0x34, 0x56, 0x78, 0x90};
//wpa
//#define S2W_DEFAULT_WPA_PASSPHRASE     "Serial2Wifi"
//#define S2W_DEFAULT_AP_WPA_PASSPHRASE     "Serial2Wifi"

//Eap

//#define S2W_DEFAULT_EAP_INNERAUTH     0
//#define S2W_DEFAULT_EAP_OUTERAUTH     0
//#define S2W_DEFAULT_EAP_USERNAME         "GSDemoKit"
//#define S2W_DEFAULT_EAP_PWD              "GSDemoKit"
//#define S2W_DEFAULT_EAP_USE_CA_CERT	 0
//#define S2W_DEFAULT_NODE_TIME_SET         0  // 0- not set, 1-> set
//#define S2W_DEFAULT_NODE_TIME 0

#define S2W_DEFAULT_MAC_ACK_MISS_COUNT 20
#define S2W_DEFAULT_RETRY_COUNT 8
#define S2W_DEFAULT_SCAN_MIN_TIME 150

//#define S2W_DEFAULT_STRICT_SECURITY      0  //0-> disable // this we can remove...

#define S2W_DEFAULT_MCAST_RX 1
#define S2W_DEFAULT_POWER_SAVE 1
#define S2W_DEFAULT_RADIO_MODE 0
#define S2W_DEFAULT_SYNCLOSS_INTERVAL 100
//#define S2W_DEFAULT_LISTEN_INTERVAL      100 // msec
#define S2W_DEFAULT_KEEPALIVE_INTERVAL 45

#define S2W_DEFAULT_USE_DHCP 1
//#define S2W_DEFAULT_IP_ADDR     		MAKEIP(192,168,1,99)
//#define S2W_DEFAULT_NET_MASK  			MAKEIP(255,255,255,0)
//#define S2W_DEFAULT_GATEWAY   		MAKEIP(192,168,1,1)

/* Group Provisioning(AP) Parameters
 */

//#define S2W_DEFAULT_GRP_PROV_SSID         "GSDemoKit"
//#define S2W_DEFAULT_GRP_PROV_CHANNEL      1
//#define S2W_DEFAULT_GRP_PROV_REG_DOMAIN        0  // 0->fcc, 1->etsi, 2->telec 
//#define S2W_DEFAULT_GRP_PROV_SECURITY     0  0-->open,1-->wep , 2--> wpa
//#define S2W_DEFAULT_GRP_PROV_WEP_AUTH     1   //1-->open , 2 -->shared
//#define S2W_DEFAULT_GRP_PROV_WEP_KEY_ID   1   // 1 to 4
//#define S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN  5   // 5 or 13
//    static const UINT8 S2W_DEFAULT_GRP_PROV_WEP_KEY[S2W_DEFAULT_GRP_PROV_WEP_KEY_LEN] ={0x12, 0x34, 0x56, 0x78, 0x90};
//#define S2W_DEFAULT_GRP_PROV_WPA_PASSPHRASE     "Serial2Wifi"

//#define S2W_DEFAULT_GRP_PROV_BEACON_INTERVAL   100  // msec
//#define S2W_DEFAULT_GRP_PROV_SSID_BROADCAST    1  // 0->disable
//#define S2W_DEFAULT_GRP_PROV_SUPPORTED_STATIONS        8
//#define S2W_DEFAULT_GRP_PROV_IP_ADDRESS            MAKEIP(192,168,240,1)
//#define S2W_DEFAULT_GRP_PROV_SUBNET_ADDRESS        MAKEIP(255,255,255,0)
//#define S2W_DEFAULT_GRP_PROV_GATE_ADDRESS          MAKEIP(192,168,240,1)
//#define S2W_DEFAULT_GRP_PROV_IP_START_ADDRESS      MAKEIP(192,168,240,2)
//#define S2W_DEFAULT_GRP_PROV_DNS_NAME             "config.gainspan\0"
//#define S2W_DEFAULT_GRP_PROV_HOST_NAME            "GAINSPAN"
//#define S2W_DEFAULT_GRP_PROV_DHCPSRVR_ENABLE       1
//#define S2W_DEFAULT_GRP_PROV_DNSSRVR_ENABLE        1
//#define S2W_DEFAULT_GRP_PROV_LEASE_TIME    86400  // 24 houres





/* AP related parameters
 */

//#define  S2W_DEFAULT_AP_MAC_ADDR_VALID           0
    //static const UINT8 S2W_DEFAULT_AP_MAC_ADDR[6] ={0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00};
#define S2W_DEFAULT_AP_WLAN_SSID "GSDemoKit"
#define S2W_DEFAULT_AP_WLAN_CHANNEL 1
#define S2W_DEFAULT_AP_REG_DOMAIN 0
//#define S2W_DEFAULT_AP_WLAN_BSSID_VALID  0  // 0->not valid
   //static const UINT8 S2W_DEFAULT_AP_WLAN_BSSID[6] =     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#define S2W_DEFAULT_AP_BEACON_INTERVAL 100
#define S2W_DEFAULT_AP_SSID_BROADCAST 0
#define S2W_DEFAULT_AP_SECURITY 1
#define S2W_DEFAULT_AP_MAC_FILTER 0
#define S2W_DEFAULT_AP_SUPPORTED_STATIONS 64
#define S2W_DFLT_AP_IP_ADDRESS MAKEIP(192,168,240,1)
#define S2W_DFLT_AP_SUBNET_ADDRESS MAKEIP(255,255,255,0)
#define S2W_DFLT_AP_GATE_ADDRESS MAKEIP(192,168,240,1)
//#define S2W_DFLT_AP_IP_START_ADDRESS      MAKEIP(192,168,240,2)
//#define S2W_DFLT_AP_DNS_NAME             "config.gainspan\0"
//#define S2W_DFLT_AP_HOST_NAME            "GAINSPAN"
//#define S2W_DFLT_AP_DHCPSRVR_ENABLE       1
//#define S2W_DFLT_AP_DNSSRVR_ENABLE        1

//#define S2W_DFLT_AP_USERNAME             "admin"
//#define S2W_DFLT_AP_PWD                  "admin"
/* Ncm Specific
 */
#define S2W_DEFAULT_AUTO_START 0
#define S2W_NCM_DFLT_CPUWAIT_PERIOD 1000
#define S2W_NCM_DFLT_KNOWNCH_SCAN_PERIOD 1000
#define S2W_NCM_DFLT_KNOWNCH_SCAN_COUNT 10
#define S2W_NCM_DFLT_ALLCH_SCAN_PERIOD 1000
#define S2W_NCM_DFLT_ALLCH_SCAN_COUNT 10
#define S2W_NCM_DFLT_L3CONNECT_PERIOD 1000
#define S2W_NCM_DFLT_L3CONNECT_COUNT 100
#define S2W_NCM_DFLT_L4CONNECT_PERIOD 1000
#define S2W_NCM_DFLT_L4CONNECT_COUNT 100

#define S2W_NCM_DFLT_ROAMING 0
//#define S2W_NCM_DFLT_ROAMING_LOW_RSSI_THRESH    70  //db
//#define S2W_NCM_DFLT_ROAMING_HIGH_RSSI_THRESH   50  // db
//#define S2W_NCM_DFLT_ROAMING_BACKGROUND_SCAN_TIME   1000 //msec

#define S2W_DFLT_AP_DHCPSRVR_LEASE_TIME 86400
#define S2W_DFLT_AP_DNS_IP1 MAKEIP(192,168,240,1)
#define S2W_DFLT_AP_DNS_IP2 MAKEIP(192,168,240,1)
#define S2W_DFLT_AP_DNS_IP3 MAKEIP(192,168,240,1)

//#define S2W_DFLT_MDNS_HOST_NAME
#define S2W_DFLT_MDNS_DOMAIN_NAME "local"
//#define S2W_DFLT_MDNS_SER_INST_NAME
//#define S2W_DFLT_MDNS_SER_SUB_TYPE
#define S2W_DFLT_MDNS_SER_TYPE "_http"
#define S2W_DFLT_MDNS_PROTO "_tcp"
//#define S2W_DFLT_MDNS_PORT
#define S2W_DFLT_MDNS_KEY 0
//#define S2W_DFLT_MDNS_TXT_RECORD
#define S2W_DFLT_MDNS_AUTOCORRECT 0
#define S2W_DFLT_MDNS_SCOPE 0
#define S2W_DFLT_MDNS_CONFLICT_DETECT 1
#define S2W_DFLT_MDNS_TTL 10


//#define S2W_DFLT_HTTPC_AUTH                "12345676890"
#define S2W_DFLT_HTTPC_HOST_IP "192.168.240.1"

#define S2W_DFLT_SNTP_SVR_IP MAKEIP(192,168,240,1)
#define S2W_DFLT_SNTP_TIMEOUT 1000
#define S2W_DFLT_SNTP_PERIODIC 0
#define S2W_DFLT_SNTP_PERIODIC_PERIOD 10

//#define S2W_DFLT_HTTP_SRVR_USRNAME
//#define S2W_DFLT_HTTP_SRVR_PWD
//#define S2W_DFLT_HTTP_SRVR_URI
#define S2W_DFLT_HTTP_SRVR_CONTENT_TYPE 0
#define S2W_DFLT_HTTP_SRVR_CLIENT_NO 8
#define S2W_DFLT_HTTP_SRVR_IDLE_TIMEOUT 120

#define S2W_DFLT_OTAFU_PULL_SRVR_IP MAKEIP(192,168,240,1)
//#define S2W_DFLT_OTAFU_PULL_SRVR_PORT      8
#define S2W_DFLT_OTAFU_PULL_PROXY_SRVR 0
//#define S2W_DFLT_OTAFU_PULL_PROXY_SRVR_IP      0
//#define S2W_DFLT_OTAFU_PULL_PROXY_SRVR_PORT      0
//#define S2W_DFLT_OTAFU_PULL_BIN_URL      8
#define S2W_DFLT_OTAFU_PULL_SSL 0

//#define S2W_DFLT_OTAFU_UPDATE_OPTIONS          0 //1-->bkp,2-->factory restore ,0-->no copy
#define S2W_DFLT_OTAFU_UPDATE_INTERFACE 0

//#define S2W_FACT_IMAGE_REQ

#define S2W_DFLT_IEEE_PS_CFG_WAKEUP_TYPE 3
#define S2W_DFLT_IEEE_PS_CFG_WAKEUP_INTERVAL 1
//#define S2W_DFLT_IEEE_PS_CFG_LISTN_INTVL_ASSOC          5
//#define S2W_DFLT_IEEE_PS_CFG_DATA_RX_TYPE               1 /*GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_PS_POLL*/
#define S2W_DFLT_IEEE_PS_CFG_ENABLE 0
// Dual interface macros

//#define S2W_DFLT_INTERFACE2_UART_HWFLOW     GSN_UART_HW_NO_SUPPORT
//#define S2W_DFLT_INTERFACE2_UART_SWFLOW     GSN_UART_SWFLOW_NO_SUPPORT
//#define S2W_DFLT_INTERFACE2_UART_BAUD       GSN_UART_BAUDRATE_9K6
//#define S2W_DFLT_INTERFACE2_UART_DMA        GSN_UART_DMA_NO_SUPPORT
//#define S2W_DFLT_INTERFACE2_UART_CHARFORMAT GSN_UART_CHARFORMAT_8
//#define S2W_DFLT_INTERFACE2_UART_STOPBITS   GSN_UART_STOPBITS_1
//#define S2W_DFLT_INTERFACE2_UART_PARITY     GSN_UART_PARITYBIT_NONE

// old spi
//#define S2W_DFLT_INTERFACE2_SPI_POLARITY    0
//#define S2W_DFLT_INTERFACE2_SPI_PHASE       0

#define S2W_DEFAULT_APP_LOG_LEVEL 0
#define S2W_WEB_IMAGE_SECTOR_SIZE 512

/**< 802.15.4 configuration */
//#define S2W_MAX_NUM_OF_802_15_4_KEY_SUPPORTED 2
//#define S2W_MAX_NUM_OF_802_15_4_DEV_SUPPORTED 32
//#define S2W_MAX_NUM_OF_802_15_4_SECURITY_LEVEL_SUPPORTED  3


/**< Zigbee-IP configuration */
//#define S2W_MAX_NUM_OF_NEIGHBOR_SUPPORTED 64
//#define S2W_MAX_NUM_OF_PARENT_SUPPORTED  2
//#define S2W_MAX_NUM_OF_NODE_SUPPORTED    256

#define APP_CFG_DCDC_TMR_VAL 36

#endif /* _APP_DEFINES_H_ */
/*****************************************************************************/

