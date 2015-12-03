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
* $RCSfile: gsn_sys_config.h,v $
*
* Description : System Configuration Definition and API (used by HTTP API)
*******************************************************************************/

#ifndef _GSN_SYS_CONFIG_H
#define _GSN_SYS_CONFIG_H

#include "gsn_wlan_scan.h"
#include "modules/http/gsn_httpd.h"

/**
 *******************************************************************************
 * @file gsn_sys_config.h
 * @brief GSN System Configuration
 *    This file contains declarations of structures and functions for
 *    managing System Configuration. This includes Client, AP, HTTPD and other
 *    general system configuraiton.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnHttpApis
 * @brief Max DNS Domain Name Length
 *    This macro defines the maximum DNS domain name length
 *****************************************************************************/
#define GSN_MAX_DNS_DOMAIN_LEN 64
#define GSN_MAX_SYS_ID_LEN 64
#define GSN_MAX_OTAFU_URL_LEN 64

/**
 *****************************************************************************
 * @ingroup GsnHttpApis
 * @brief Types of netowrk modes supported (Infrastructure client and AP)
 *****************************************************************************/
typedef enum
{
    GSN_INFRA_CLIENT = 1,
    GSN_LIMITED_AP
} GSN_NETWORK_MODE_T;

/**
 *****************************************************************************
 * @ingroup GsnHttpApis
 * @brief Types of netowrk AP modes supported (user-ap and prov-ap)
 *****************************************************************************/
typedef enum
{
	GSN_PROV_AP = 1,
	GSN_USER_AP
}GSN_AP_MODE_T;

typedef enum {
	 GSN_PROV_EAP_TYPE_FAST_MSCHAP=0,
	 GSN_PROV_EAP_TYPE_TTLS,
	 GSN_PROV_EAP_TYPE_TLS,
	 GSN_PROV_EAP_TYPE_PEAP0,
	 GSN_PROV_EAP_TYPE_PEAP1,
	 GSN_PROV_EAP_TYPE_FAST_GTC,
	 GSN_PROV_EAP_TYPE_NONE
} GsnProvEapType;
/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief  Client Configuration
 *     Definition of structure containing (infrastructure) client configuration
 ******************************************************************************/
#if 1//def GSN_HTTPD_CONFIG_CLIENT
typedef struct GSN_SYS_CONFIG_CLIENT
{
    GSN_MAC_SSID_T ssid;   /**<  SSID */
    GSN_WDD_SEC_PSK_T passphrase; /**< WPA/WPA2 PSK Passphrase  */
    GSN_WDD_SEC_WEP_KEY_T wepKeyConfig; /**< Pointer to WEP KEY configuration */
    UINT8 wepAuthType; /**< Pointer to WEP Authenticaiton Type */
    UINT8 channel; /**< Channel on which AP is available */
    UINT8 dhcpFlag; /**< DHCP enabled/disabled flag */
    GSN_WLAN_SECURITY_TYPE_T securityType; /**< Network WLAN security type */
    GsnProvEapType eapType;
    GSN_WDD_SEC_EAP_UNAME_T eapUsername;
    GSN_WDD_SEC_EAP_PWD_T eapPassword;
    UINT32 ipAddress; /**< IP address for static configuration */
    UINT32 subnetmask; /**< Subnet mask for static configuration */
    UINT32 dnsServer; /**< DNS Server for static configuration */
    UINT32 gateway; /**< Gateway for static configuration */
} GSN_SYS_CONFIG_CLIENT_T;
#endif

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief AP configuration
 *    Definition of structure containing AP configuration.
 ******************************************************************************/
#if 1//def GSN_HTTPD_CONFIG_LIMITED_AP
typedef struct GSN_SYS_CONFIG_AP
{
    GSN_MAC_SSID_T ssid;  /**<  SSID */
    GSN_WDD_SEC_PSK_T passphrase; /**< WPA/WPA2 PSK Passphrase  */
    GSN_WLAN_SECURITY_TYPE_T securityType; /**< Network WLAN security type */
    GSN_WDD_SEC_WEP_KEY_T wepKeyConfig; /**< Pointer to WEP KEY configuration */
    UINT8 channel; /**< Channel on which AP should operate */
    UINT16 beaconInterval; /**< Beacon interval for AP */
    UINT32 ipAddress; /**< IP address of AP */
    UINT32 subnetmask; /**< Subnet mask as served by AP DHCP server */
    UINT32 gateway; /**< Gateway address as served by AP DHCP server*/
    UINT8 dhcpServerEnable; /**< Flag indicating whether DHCP server is enabled*/
    UINT8 dhcpNumAddresses; /**< Number of DHCP addresses served*/
    UINT32 dhcpAddressStart; /**< Starting DHCP server address*/
    UINT8 dnsServerEnable; /**< Flag indicating whether DNS server is enabled*/
    UINT8 dnsDomainName[GSN_MAX_DNS_DOMAIN_LEN]; /**< DNS domain name*/
} GSN_SYS_CONFIG_AP_T;
#endif

typedef struct GSN_SYS_CONFIG_IP
{
    UINT32 ipAddr;
} GSN_SYS_CONFIG_IP_T;


/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Network configuration
 *        Definition of structure containing Network configuration, which
 *        includes both AP and client configuration. It also contains the
 *        current mode of operation.
 ******************************************************************************/
typedef struct GSN_SYS_CONFIG_NETWORK
{
    GSN_NETWORK_MODE_T networkMode;  /**<  Current mode of operation */
    UINT8 macAddr[6];
    GSN_SYS_CONFIG_IP_T ipConfig;
#if 1//def GSN_HTTPD_CONFIG_LIMITED_AP
    GSN_SYS_CONFIG_AP_T apConfig;  /**<  AP configuration */
	GSN_AP_MODE_T groupProvMode; /**<  USER_AP / PROV_AP mode */
#endif
#if 1//def GSN_HTTPD_CONFIG_CLIENT
    GSN_SYS_CONFIG_CLIENT_T clientConfig;  /**<  Client configuration */
#endif
    GSN_WLAN_REG_DOMAIN_T regDomain; /**< Regulatory domain */
} GSN_SYS_CONFIG_NETWORK_T;

typedef struct GSN_SYS_CONFIG_SYS_ID
{
    UINT8 name[GSN_MAX_SYS_ID_LEN];
    UINT8 uid[GSN_MAX_SYS_ID_LEN];
} GSN_SYS_CONFIG_SYS_ID_T;

typedef struct GSN_SYS_OTAFU
{
    UINT32 serverIp;
    UINT16 serverPort;
    UINT8 baseLoc[GSN_MAX_OTAFU_URL_LEN];
    UINT8 app1Name[GSN_MAX_OTAFU_URL_LEN];
    UINT8 app2Name[GSN_MAX_OTAFU_URL_LEN];
    UINT8 wlanName[GSN_MAX_OTAFU_URL_LEN];
    UINT32 proxyIp;
    UINT16 proxyPort;
    UINT8 updateNeeded;
} GSN_SYS_CONFIG_OTAFU_T;

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief System configuration
 *      Definition of complete system configuration. This includes network
 *      configuration and HTTPD configuration. It also contains a flag that
 *      indicates whether the changes should be applied to the device.
 ******************************************************************************/
typedef struct GSN_SYS_CONFIG
{
    UINT8 sysConfigChangeApply; /**<  Flag indicating whether change should be applied */
    GSN_SYS_CONFIG_HTTPD_T httpdConfig; /**<  HTTPD Configuration */
    GSN_SYS_CONFIG_NETWORK_T networkConfig; /**<  Network Configuration */
    GSN_SYS_CONFIG_SYS_ID_T sysIdConfig;
#if 1//fdef GSN_HTTPD_CONFIG_OTAFU
    GSN_SYS_CONFIG_OTAFU_T otafuConfig;
#endif
} GSN_SYS_CONFIG_T;


#define GSN_WLAN_EAP_FAST_GTC "eap-fast-gtc"
#define GSN_WLAN_EAP_FAST_MSCHAP "eap-fast-mschap"
#define GSN_WLAN_EAP_TLS  "eap-tls"
#define GSN_WLAN_EAP_TTLS "eap-ttls"
#define GSN_WLAN_EAP_PEAP0 "eap-peap0"
#define GSN_WLAN_EAP_PEAP1 "eap-peap1"

#endif
