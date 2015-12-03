/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: app_default_cfg.h,v $
*******************************************************************************/

#ifndef _APP_DEFAULT_CFG_H_
#define _APP_DEFAULT_CFG_H_

/* Common System Configuration */
#define DEFAULT_MODE						GSN_LIMITED_AP /*GSN_LIMITED_AP / GSN_INFRA_CLIENT*/
//#define DEFAULT_MAC_ADDR					{0x00, 0x1d,0xc9, 0x99, 0x99, 0x99}
//#define DEFAULT_MAC_ADDR					{0x00, 0x1d,0xc9, 0x51, 0x52, 0x53}
//#define DEFAULT_MAC_ADDR					{0x00, 0x1d,0xc9, 0x80, 0xae, 0xc0}
//#define DEFAULT_MAC_ADDR					{0x00, 0x1d,0xc9, 0x00, 0x29, 0xb2}
#define DEFAULT_MAC_ADDR					{0x00, 0x1d,0xc9, 0xaa, 0xbb, 0xcc}

/*Default Client configuration*/
#define DEFAULT_CLI_SSID					"GainSpanDemo"
#define DEFAULT_CLI_CHNL					1
#define DEFAULT_CLI_MAX_SCAN_TIME			150
#define DEFAULT_CLI_MIN_SCAN_TIME			150
#define DEFAULT_CLI_IP_ADDR					{192,168,3,99}
#define DEFAULT_CLI_SUBNET_MASK 			{255,255,255,0}
#define DEFAULT_CLI_GATEWAY_ADDR			{192,168,3,1}
#define DEFAULT_CLI_DNS_ADDR     			{192,168,3,1}
#define DEFAULT_CLI_DHCP_MAX_RETRYCNT		4
#define DEFAULT_CLI_DHCP_ENABLE				TRUE
#define DEFAULT_CLI_SECURITY                GSN_WLAN_SECURITY_NONE
#define DEFAULT_CLI_PASSPHRASE              ""
#define DEFAULT_CLI_WEP_AUTH				GSN_WDD_SEC_WEP_OPEN
#define DEFAULT_CLI_WEP_KEYID				0
#define DEFAULT_CLI_WEP_KEYLEN				GSN_WDD_SEC_WEP40_KEY_LEN
#define DEFAULT_CLI_WEP_KEY                 {0xaa,0xbb,0xcc,0xdd,0xee}
#define DEFAULT_CLI_EAP_TYPE                GSN_EAP_TYPE_NONE
#define DEFAULT_CLI_EAP_USERNAME            ""
#define DEFAULT_CLI_EAP_PASSWORD            ""

/*Default AP Configuration*/

#define ADK_CONFIG_SSID_FROM_MAC_ADDR

#define DEFAULT_AP_SSID					APP_NAME_PREFIX"_DEFAULT"
#define DEFAULT_AP_SSID_PREFIX			APP_NAME_PREFIX
#define DEFAULT_AP_CHNL					6
#define DEFAULT_AP_IP_ADDR				{192,168,240,1}
#define DEFAULT_AP_SUBNET_MASK 			{255,255,255,0}
#define DEFAULT_AP_GATEWAY_ADDR			{192,168,240,1}
#define DEFAULT_AP_DHCP_MAX_RETRYCNT	4
#define DEFAULT_AP_BCN_INTERVAL         100
#define DEFAULT_AP_DHCP_SRVR_ENABLE		TRUE
#define DEFAULT_AP_DHCP_SRVR_ADDR_START {192,168,240,2}
#define DEFAULT_AP_DHCP_SRVR_NUM_ADDRS  8
#define DEFAULT_AP_DNS_SRVR_ENABLE      TRUE
#define DEFAULT_AP_DNS_DOMAIN_NAME      "config.gainspan.local"
#define DEFAULT_AP_SECURITY             GSN_WLAN_SECURITY_NONE
#define DEFAULT_AP_PASSPHRASE           "gainspan"
#define DEFAULT_AP_WEP_AUTH				GSN_MAC_AUTH_OPEN
#define DEFAULT_AP_WEP_KEYID			0
#define DEFAULT_AP_WEP_KEYLEN			GSN_WDD_SEC_WEP40_KEY_LEN
#define DEFAULT_AP_WEP_KEY              {0xaa,0xbb,0xcc,0xdd,0xee}

/* Macros for group provisioning */

#define DEFAULT_GROUP_PROV_SSID					"GS_PROV_"
#define DEFAULT_GROUP_PROV_CHNL					6
#define DEFAULT_GROUP_PROV_IP_ADDR				{192,168,240,1}
#define DEFAULT_GROUP_PROV_SUBNET_MASK 			{255,255,255,0}
#define DEFAULT_GROUP_PROV_GATEWAY_ADDR			{192,168,240,1}
#define DEFAULT_GROUP_PROV_DHCP_MAX_RETRYCNT	4
#define DEFAULT_GROUP_PROV_BCN_INTERVAL         100
#define DEFAULT_GROUP_PROV_DHCP_SRVR_ENABLE		TRUE
#define DEFAULT_GROUP_PROV_DHCP_SRVR_ADDR_START {192,168,240,10}
#define DEFAULT_GROUP_PROV_DHCP_SRVR_NUM_ADDRS  8
#define DEFAULT_GROUP_PROV_DNS_SRVR_ENABLE      TRUE
#define DEFAULT_GROUP_PROV_DNS_DOMAIN_NAME      "config.gainspan.local"
#define DEFAULT_GROUP_PROV_SECURITY             GSN_WLAN_SECURITY_NONE
#define DEFAULT_GROUP_PROV_PASSPHRASE           "gainspan"
#define DEFAULT_GROUP_PROV_WEP_AUTH				GSN_MAC_AUTH_OPEN
#define DEFAULT_GROUP_PROV_WEP_KEYID			0
#define DEFAULT_GROUP_PROV_WEP_KEYLEN			GSN_WDD_SEC_WEP40_KEY_LEN
#define DEFAULT_GROUP_PROV_WEP_KEY              {0xaa,0xbb,0xcc,0xdd,0xee}


/* Default WPS Configuration */
#define DEFAULT_DEVICE_NAME "GS2000"
#define DEFAULT_DEVICE_MANUFACTURER "GainSpan"
#define DEFAULT_DEVICE_MODEL "wdd Test App"
#define DEFAULT_DEVICE_MODEL_NUMBER "2000"
#define DEFAULT_DEVICE_SERIAL_NUMBER "test1234"
#define DEFAULT_DEVICE_UUID "gainspan.com"

#endif /* _APP_DEFAULT_CFG_H_ */
