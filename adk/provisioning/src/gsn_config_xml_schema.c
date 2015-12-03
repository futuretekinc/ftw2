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
* $RCSfile: gsn_config_xml_schema.c,v
*/

/*
 * gsn_config_xml_schema.c
 *
 *  Created on: Jun 3, 2011
 *      Author: PViswanathan
 */

#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"

/* XML Schema definition - <start> */
typedef struct
{
    UINT8          channel;
    GSN_XML_STRING_T ssid;
    GSN_XML_STRING_T security;
    GSN_XML_STRING_T wepAuthType;
    GSN_XML_STRING_T password;
    GSN_XML_STRING_T eapType;
    GSN_XML_STRING_T eapUserName;
    GSN_XML_STRING_T eapPassword;
} xml_client_wireless_settings_t;

typedef struct
{
    GSN_XML_STRING_T ip_type;
    GSN_XML_STRING_T ip_addr;
    GSN_XML_STRING_T subnetmask;
    GSN_XML_STRING_T gateway;
    GSN_XML_STRING_T dns_addr;
} xml_client_ip_settings_t;


typedef struct
{
    xml_client_wireless_settings_t client_wireless_settings;
    xml_client_ip_settings_t client_ip_settings;
} xml_client_settings_t;

typedef struct
{
    UINT8          channel;
    UINT16          beaconInterval;
    GSN_XML_STRING_T ssid;
    GSN_XML_STRING_T security;
    GSN_XML_STRING_T password;
} xml_ap_wireless_settings_t;

typedef struct
{
    GSN_XML_STRING_T ip_addr;
    GSN_XML_STRING_T subnetmask;
    GSN_XML_STRING_T gateway;
    GSN_XML_STRING_T dhcpServerEnable;
    GSN_XML_STRING_T dhcpStartAddr;
    UINT8 dhcpNumAddrs;
    GSN_XML_STRING_T dnsServerEnable;
    GSN_XML_STRING_T dnsDomain;
} xml_ap_ip_settings_t;

typedef struct
{
    xml_ap_wireless_settings_t ap_wireless_settings;
    xml_ap_ip_settings_t ap_ip_settings;
} xml_ap_settings_t;


typedef struct
{
    GSN_XML_STRING_T ip_addr;
} xml_ip_settings_t;

typedef struct
{
    GSN_XML_STRING_T network_mode;
    GSN_XML_STRING_T ap_mode;
    xml_client_settings_t client_settings;
    xml_ap_settings_t ap_settings;
    GSN_XML_STRING_T reg_domain;
    GSN_XML_STRING_T mac_address;
    xml_ip_settings_t ip_settings;
} xml_network_settings_t;

//                        *pName        objType                    dataType        maxObjOcc    offset
const GSN_XML_OBJ_T xml_network_mode = {"mode", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_network_settings_t, network_mode)};
const GSN_XML_OBJ_T xml_ap_mode = {"ap_mode", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_network_settings_t, ap_mode)};
const GSN_XML_OBJ_T xml_mac_address = {"mac_addr", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_network_settings_t, mac_address)};

const GSN_XML_OBJ_T xml_ip_addr = {"ip_addr", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_ip_settings_t, ip_addr)};

// Ap Config
const GSN_XML_OBJ_T xml_client_channel = {"channel", XML_SIMPLE_ELEMENT, XML_DT_UINT8, 1, offsetof(xml_client_wireless_settings_t, channel)};
const GSN_XML_OBJ_T xml_client_ssid = {"ssid", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_client_wireless_settings_t, ssid)};
const GSN_XML_OBJ_T xml_client_security = {"security",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_wireless_settings_t, security)};
const GSN_XML_OBJ_T xml_client_wepauthtype = {"wepauth",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_wireless_settings_t, wepAuthType)};
const GSN_XML_OBJ_T xml_client_password = {"password",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_wireless_settings_t, password)};
const GSN_XML_OBJ_T xml_client_eapType = {"eap_type",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_wireless_settings_t, eapType)};
const GSN_XML_OBJ_T xml_client_eapUsername = {"eap_username",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_wireless_settings_t, eapUserName)};
const GSN_XML_OBJ_T xml_client_eapPassword = {"eap_password",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_wireless_settings_t, eapPassword)};
const GSN_XML_OBJ_T xml_client_ip_type = {"ip_type",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_ip_settings_t, ip_type)};
const GSN_XML_OBJ_T xml_client_ip_addr = {"ip_addr",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_ip_settings_t, ip_addr)};
const GSN_XML_OBJ_T xml_client_subnetmask = {"subnetmask",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_ip_settings_t, subnetmask)};
const GSN_XML_OBJ_T xml_client_gateway = {"gateway",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_ip_settings_t, gateway)};
const GSN_XML_OBJ_T xml_client_dns_addr = {"dns_addr",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_client_ip_settings_t, dns_addr)};


// Client Config
const GSN_XML_OBJ_T xml_ap_channel = {"channel", XML_SIMPLE_ELEMENT, XML_DT_UINT8, 1, offsetof(xml_ap_wireless_settings_t, channel)};
const GSN_XML_OBJ_T xml_ap_beacon_interval = {"beacon_interval", XML_SIMPLE_ELEMENT, XML_DT_UINT16, 1, offsetof(xml_ap_wireless_settings_t, beaconInterval)};
const GSN_XML_OBJ_T xml_ap_ssid = {"ssid", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_ap_wireless_settings_t, ssid)};
const GSN_XML_OBJ_T xml_ap_security = {"security", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_ap_wireless_settings_t, security)};
const GSN_XML_OBJ_T xml_ap_password = {"password", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_ap_wireless_settings_t, password)};
const GSN_XML_OBJ_T xml_ap_ip_addr = {"ip_addr",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t, ip_addr)};
const GSN_XML_OBJ_T xml_ap_subnetmask = {"subnetmask",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t, subnetmask)};
const GSN_XML_OBJ_T xml_ap_gateway = {"gateway",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t, gateway)};
const GSN_XML_OBJ_T xml_ap_dhcp_server_enable = {"dhcp_server_enable",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t,dhcpServerEnable)};
const GSN_XML_OBJ_T xml_ap_dhcp_start_addr = {"dhcp_start_addr",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t, dhcpStartAddr)};
const GSN_XML_OBJ_T xml_ap_dhcp_num_addrs = {"dhcp_num_addrs", XML_SIMPLE_ELEMENT, XML_DT_UINT8, 1, offsetof(xml_ap_ip_settings_t, dhcpNumAddrs)};
const GSN_XML_OBJ_T xml_ap_dns_server_enable = {"dns_server_enable",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t, dnsServerEnable)};
const GSN_XML_OBJ_T xml_ap_dns_domain = {"dns_domain",XML_SIMPLE_ELEMENT, XML_DT_STR,1, offsetof(xml_ap_ip_settings_t, dnsDomain)};

const GSN_XML_OBJ_T xml_reg_domain = {"reg_domain", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_network_settings_t, reg_domain)};



//                                    *pName            objType                    dataType        maxObjOcc    offset    maxNumOfObj    size                *pObj[]
const GSN_XML_COMPLEX_OBJ_T xml_ip_settings    = {"ip", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_network_settings_t, ip_settings), {1, sizeof(xml_ip_settings_t), {&xml_ip_addr}}};

const GSN_XML_COMPLEX_OBJ_T xml_client_wireless_settings    = {"wireless", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_client_settings_t, client_wireless_settings), {8, sizeof(xml_client_wireless_settings_t), {&xml_client_channel, &xml_client_ssid, &xml_client_security, &xml_client_wepauthtype, &xml_client_password, &xml_client_eapType, &xml_client_eapUsername, &xml_client_eapPassword}}};
const GSN_XML_COMPLEX_OBJ_T xml_client_ip_settings    = {"ip", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_client_settings_t, client_ip_settings), {5, sizeof(xml_client_ip_settings_t), {&xml_client_ip_type, &xml_client_ip_addr, &xml_client_subnetmask, &xml_client_gateway, &xml_client_dns_addr}}};
const GSN_XML_COMPLEX_OBJ_T xml_client_settings    = {"client", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_network_settings_t, client_settings), {2, sizeof(xml_client_settings_t), {(GSN_XML_OBJ_T*)&xml_client_wireless_settings, (GSN_XML_OBJ_T*)&xml_client_ip_settings}}};


const GSN_XML_COMPLEX_OBJ_T xml_ap_wireless_settings    = {"wireless", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_ap_settings_t, ap_wireless_settings), {5, sizeof(xml_ap_wireless_settings_t), {&xml_ap_channel, &xml_ap_beacon_interval, &xml_ap_ssid, &xml_ap_security, &xml_ap_password}}};
const GSN_XML_COMPLEX_OBJ_T xml_ap_ip_settings    = {"ip", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_ap_settings_t, ap_ip_settings), {8, sizeof(xml_ap_ip_settings_t), {&xml_ap_ip_addr, &xml_ap_subnetmask, &xml_ap_gateway, &xml_ap_dhcp_server_enable, &xml_ap_dhcp_start_addr, &xml_ap_dhcp_num_addrs, &xml_ap_dns_server_enable, &xml_ap_dns_domain}}};
const GSN_XML_COMPLEX_OBJ_T xml_ap_settings    = {"ap", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,offsetof(xml_network_settings_t, ap_settings), {2, sizeof(xml_ap_settings_t), {(GSN_XML_OBJ_T*)&xml_ap_wireless_settings, (GSN_XML_OBJ_T*)&xml_ap_ip_settings}}};

//#if defined(ADK_PROV_CONFIG_LIMITED_AP) && defined(ADK_PROV_CONFIG_CLIENT)
const GSN_XML_COMPLEX_OBJ_T xml_network_settings    = {"network", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {7, sizeof(xml_network_settings_t), {&xml_network_mode, &xml_ap_mode, (GSN_XML_OBJ_T*)&xml_client_settings, (GSN_XML_OBJ_T*)&xml_ap_settings, &xml_mac_address,(GSN_XML_OBJ_T*)&xml_ip_settings, &xml_reg_domain }}};
/*#elif defined(ADK_PROV_CONFIG_CLIENT)
const GSN_XML_COMPLEX_OBJ_T xml_network_settings    = {"network", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {5, sizeof(xml_network_settings_t), {&xml_network_mode, (GSN_XML_OBJ_T*)&xml_client_settings, &xml_mac_address, (GSN_XML_OBJ_T*)&xml_ip_settings, &xml_reg_domain}}};
#elif defined(ADK_PROV_CONFIG_LIMITED_AP)
const GSN_XML_COMPLEX_OBJ_T xml_network_settings    = {"network", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {6, sizeof(xml_network_settings_t), {&xml_network_mode, &xml_ap_mode, (GSN_XML_OBJ_T*)&xml_ap_settings, &xml_mac_address, (GSN_XML_OBJ_T*)&xml_ip_settings, &xml_reg_domain}}};
#else
const GSN_XML_COMPLEX_OBJ_T xml_network_settings    = {"network", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {4, sizeof(xml_network_settings_t), {&xml_network_mode, &xml_mac_address, (GSN_XML_OBJ_T*)&xml_ip_settings, &xml_reg_domain}}};
#endif
*/
/* XML Schema definition - <end> */

typedef struct
{
    GSN_XML_STRING_T username;
    GSN_XML_STRING_T password;
    UINT16 port;
} xml_httpd_settings_t;

const GSN_XML_OBJ_T xml_httpd_username = {"username", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_httpd_settings_t, username)};
const GSN_XML_OBJ_T xml_httpd_password = {"password", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_httpd_settings_t, password)};
const GSN_XML_OBJ_T xml_httpd_port = {"port", XML_SIMPLE_ELEMENT, XML_DT_UINT16, 1, offsetof(xml_httpd_settings_t, port)};

const GSN_XML_COMPLEX_OBJ_T xml_httpd_settings    = {"httpd", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {3, sizeof(xml_httpd_settings_t), {&xml_httpd_username, &xml_httpd_password, &xml_httpd_port}}};

typedef struct
{
    GSN_XML_STRING_T name;
    GSN_XML_STRING_T uid;
} xml_sys_id_settings_t;

const GSN_XML_OBJ_T xml_sys_id_name = {"name", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_sys_id_settings_t, name)};
const GSN_XML_OBJ_T xml_sys_id_uid = {"uid", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_sys_id_settings_t, uid)};
const GSN_XML_COMPLEX_OBJ_T xml_sys_id_settings    = {"id", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {2, sizeof(xml_sys_id_settings_t), {&xml_sys_id_name, &xml_sys_id_uid}}};

#ifdef GSN_HTTPD_CONFIG_OTAFU
typedef struct
{
    GSN_XML_STRING_T server_ip;
    UINT16 server_port;
    GSN_XML_STRING_T base_loc;
    GSN_XML_STRING_T app1_name;
    GSN_XML_STRING_T app2_name;
    GSN_XML_STRING_T wlan_name;
    GSN_XML_STRING_T proxy_ip;
    UINT16 proxy_port;
    GSN_XML_STRING_T update_needed;
} xml_otafu_settings_t;

const GSN_XML_OBJ_T xml_otafu_server_ip = {"server_ip", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, server_ip)};
const GSN_XML_OBJ_T xml_otafu_server_port = {"server_port", XML_SIMPLE_ELEMENT, XML_DT_UINT16, 1, offsetof(xml_otafu_settings_t, server_port)};
const GSN_XML_OBJ_T xml_otafu_base_loc = {"base_loc", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, base_loc)};
const GSN_XML_OBJ_T xml_otafu_app1_name = {"app1", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, app1_name)};
const GSN_XML_OBJ_T xml_otafu_app2_name = {"app2", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, app2_name)};
const GSN_XML_OBJ_T xml_otafu_wlan_name = {"wlan", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, wlan_name)};
const GSN_XML_OBJ_T xml_otafu_proxy_ip = {"proxy_ip", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, proxy_ip)};
const GSN_XML_OBJ_T xml_otafu_proxy_port = {"proxy_port", XML_SIMPLE_ELEMENT, XML_DT_UINT16, 1, offsetof(xml_otafu_settings_t, proxy_port)};
const GSN_XML_OBJ_T xml_otafu_update_needed = {"update_needed", XML_SIMPLE_ELEMENT, XML_DT_STR, 1, offsetof(xml_otafu_settings_t, update_needed)};
const GSN_XML_COMPLEX_OBJ_T xml_otafu_settings    = {"otafu", XML_COMPLEX_ELEMENT, XML_DT_NONE,    1,0, {9, sizeof(xml_otafu_settings_t), {&xml_otafu_server_ip, &xml_otafu_server_port, &xml_otafu_base_loc, &xml_otafu_app1_name, &xml_otafu_app2_name, &xml_otafu_wlan_name,  &xml_otafu_proxy_ip, &xml_otafu_proxy_port, &xml_otafu_update_needed}}};
#endif
