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
* $RCSfile: gsn_httpd_config.c,v $
*
* Description : Gsn Httpd Config file
*******************************************************************************/


/*******************************************************************************
 * File Inclusions
 ******************************************************************************/

#include <stddef.h>
#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
#include "modules/http/gsn_httpd_debug.h"
#include "gsn_sys_config.h"
#include "gsn_httpd_config.h"
#include "gsn_wlan_scan.h"
#include "gsn_httpd_config_fpt.h"
//#include "app_main_ctx.h"

#if 0
PRIVATE const INT8 *networkMode[]=
{
    "infra-client",
    "ad-hoc",
    "prov-ap",
    "limited-ap"
};
#endif

PRIVATE const UINT8* s_WepAuthOpenStr = "open";
PRIVATE const UINT8* s_WepAuthSharedStr = "shared";

PRIVATE const INT8* secOptions[4] = {GSN_WLAN_SECURITY_NONE_STR,
        GSN_WLAN_WEP_STR,
        GSN_WLAN_WPA_PERSONAL_STR,
        GSN_WLAN_WPA_ENTERPRISE_STR};

static GSN_SYS_CONFIG_T sysConfig;

#define GSN_HTTPD_MAX_STR_LEN_1 16
#define GSN_HTTPD_MAX_STR_LEN_2 8
#define GSN_HTTPD_MAX_IP_STR_LEN 32
// WEP Info is ecoded as "key_index:key"
#define GSN_HTTPD_MAX_WEP_KEY_INDEX_LEN ((GSN_WDD_SEC_MAX_WEP_KEY_LEN*2) + 2 + 1)

/* Place holders for strings to be pointed to by xml_str_type_t */
PRIVATE UINT8 xmlStrNetworkMode[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrApMode[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrIpAddress[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrMacAddress[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrRegDomain[GSN_HTTPD_MAX_STR_LEN_1];

PRIVATE UINT8 xmlStrClientDhcpFlag[GSN_HTTPD_MAX_STR_LEN_2];
PRIVATE UINT8 xmlStrClientSecurityType[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrClientWepAuthType[GSN_HTTPD_MAX_STR_LEN_2];
PRIVATE UINT8 xmlStrClientIpAddress[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrClientSubnetmask[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrClientDnsServer[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrClientGateway[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrClientEapType[GSN_HTTPD_MAX_STR_LEN_1];

PRIVATE UINT8 xmlStrWepKeyClient[30];

//#define LIMITED_AP

PRIVATE UINT8 xmlStrWepKeyAp[30];

PRIVATE UINT8 xmlStrApSecurityType[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrApIpAddress[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrApGateway[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrApSubnetmask[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrApDhcpServerEnabled[GSN_HTTPD_MAX_STR_LEN_2];
PRIVATE UINT8 xmlStrApDhcpStartAddress[GSN_HTTPD_MAX_STR_LEN_1];
PRIVATE UINT8 xmlStrApDnsServerEnabled[GSN_HTTPD_MAX_STR_LEN_2];

#ifdef GSN_HTTPD_CONFIG_OTAFU
PRIVATE UINT8 xmlStrOtafuServerIp[GSN_HTTPD_MAX_IP_STR_LEN];
PRIVATE UINT8 xmlStrOtafuProxyIp[GSN_HTTPD_MAX_IP_STR_LEN];
#endif


PRIVATE GSN_HTTPD_API_CONFIG_CB_FN httpdConfigCbFn = NULL;

#define GSN_GET_IP_STR_FROM_XML(ipStr, ipAddrXml, ipAddrPtr) \
    GsnHttpd_SetStrFromXmlStr(ipStr, ipAddrXml, sizeof(ipStr)); \
    inet_pton(AF_INET, (char*) ipStr, ipAddrPtr);
    //HTTPD_DEBUG_PRINT(("[httpd_config] Got IP from XML %s [%x]\r\n", ipStr, *ipAddrPtr));

#define GSN_SET_STR_XML_FROM_IP(ipAddrPtr, ipAddrStr, ipAddrXml) \
    inet_ntop(AF_INET, ipAddrPtr, (char*)ipAddrStr, sizeof(ipAddrStr)); \
    ipAddrXml.ptr = ipAddrStr; \
    ipAddrXml.len = strlen((char*)ipAddrStr);
    //HTTPD_DEBUG_PRINT(("[httpd_config] Set IP into XML %s [%x]\r\n", ipAddrStr, *ipAddrPtr));

#include "gsn_config_xml_schema.c"

static xml_network_settings_t network_settings;
static xml_httpd_settings_t httpd_settings;
static xml_sys_id_settings_t sys_id_settings;
#ifdef GSN_HTTPD_CONFIG_OTAFU
static xml_otafu_settings_t otafu_settings;
#endif


//extern APP_MAIN_CTX_T *appCtx;

PRIVATE char* GsnHttpd_ToLowerStr(UINT8* str)
{
        if(GsnHttpd_ToLowerStr_FP)
        {
            return GsnHttpd_ToLowerStr_FP(str);
        }

    UINT8* str1 = str, ch;
    while (*str1)
    {
      ch = tolower(*str1);
      *str1++ = ch;
    }
    return (char*) str;
}
#if 0
TM_PROTO_EXTERN const char TM_FAR * inet_ntop(
    int                 af,
    //const void TM_FAR *src,
    unsigned long *src,
    char TM_FAR *       dst,
    int                 size )
{
        if( inet_ntop_FP)
        {
            return     (inet_ntop_FP)(af,src,dst,size);
        }
 INT8 *dest;
  
  dest = gsn_malloc(15);
  
  sprintf(dest,"%d.%d.%d.%d", (int)(0xff&((unsigned long)(*src)>>24)), (int)(0xff&((unsigned long)(*src)>>16)), (int)(0xff&((unsigned long)(*src)>>8)), (int)(0xff&((unsigned long)(*src)>>0)));
  memcpy(dst, dest, 15);
} 
#endif

PRIVATE UINT8
GsnHttpd_ToHex(UINT8 c)
{
	if(GsnHttpd_ToHex_FP)
    {
    	return GsnHttpd_ToHex_FP(c);
    }
    UINT8 val = 0;

    if (c >= '0' && c <= '9')
    {
        val = c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        val = c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        val = c - 'a' + 10;
    }

    return val;
}

PUBLIC INT32
GsnHttpd_ParseMac(UINT8 *s, UINT8 *mac_addr)
{
    if(GsnHttpd_ParseMac_FP)
    {
    	return GsnHttpd_ParseMac_FP(s, mac_addr);
    }
    UINT32 i, val;
    UINT8 dummy[6]={0x00,0x00,0x00,0x00,0x00,0x00}; // 0 mac
    UINT8 dummy1[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; // broadcast mac
    memset(mac_addr, 0, 6);

    for (i = 0; *s != '\0' && i < 7; i++, s++)
    {
        int digits = 0;

        val = 0;
        while (*s != ':' && *s != '\0' && *s != ' ')
        {
            if (!isxdigit(*s))
            {
                return 1;
            }

            val = val * 16 + GsnHttpd_ToHex(*s);
            s++;
            digits++;
        }

        if (!digits || digits > 2)
        {
            return 1;
        }

        if(i<6)
        {
        mac_addr[i] = val;
    }
        if(*s == '\0')
        {
            i++;
            break;
        }
    }
    if((memcmp(mac_addr,dummy,6)== 0) || (memcmp(mac_addr,dummy1,6) == 0))
    {
        return 1;
    }
    return i == 6 ? 0 : 1;
}

PRIVATE VOID
GsnHttpd_WepKeyToStr(GSN_WDD_SEC_WEP_KEY_T* pWepConfig, UINT8 *wepStr)
{
    {
        if(GsnHttpd_WepKeyToStr_FP)
        {
            GsnHttpd_WepKeyToStr_FP(pWepConfig, wepStr);
            return ;
        }
    }
    UINT8 i;
    UINT8* str;
    sprintf((char *)wepStr, "%d:", pWepConfig->KeyId);
    //HTTPD_DEBUG_PRINT(("[httpd_config] wepstring (added key %d) %s\r\n", pWepConfig->KeyId, wepStr));
    str = wepStr + 2;
    for (i = 0; i < pWepConfig->KeyLen; i++)
    {
        sprintf((char*)str, "%02x", pWepConfig->Key[i]);
        //HTTPD_DEBUG_PRINT(("[httpd_config] wepstring (added hex value %02x) %s\r\n", pWepConfig->Key[i], wepStr));
        str += 2;
    }
    *str = 0;
    HTTPD_DEBUG_PRINT(("[httpd_config] wep string is %s", wepStr));
}

PRIVATE UINT32
GsnHttpd_KeyValueGet(UINT8 *str, UINT8 *key)
{
    {
        if(GsnHttpd_KeyValueGet_FP)
        {
            return GsnHttpd_KeyValueGet_FP(str, key);
        }
    }
    UINT32 val = 0, i, j;
    memset(key, 0, 13);

    while (isspace(*str))
    {
        str++;
    }

    for (j = 0; *str != '\0' && j < 13; j++)
    {
        for (val = 0, i = 0; i < 2 && *str != '\0'; str++, i++)
        {
            if (!isxdigit(*str))
            {
                return 0;
            }
            val = val * 16 + GsnHttpd_ToHex(*str);
        }
        if (i != 2)
        {
            return 0;
        }
        key[j] = val;
    }
    return j;
}

void GsnHttpdApiConfig_SetWepFromStr(char* wepInfoStr,
        GSN_WDD_SEC_WEP_KEY_T* pWepConfig )
{
	if(GsnHttpdApiConfig_SetWepFromStr_FP)
	{
		GsnHttpdApiConfig_SetWepFromStr_FP(wepInfoStr, pWepConfig);
        return;
	}
    char* wepKeyStr;
    GSN_WDD_SEC_WEP_KEY_T wepKey;
    UINT8 keyId, keyLen;
    if ((wepKeyStr = strchr(wepInfoStr, ':')) == NULL)
        return;
    else
        wepKeyStr = wepKeyStr + 1;
    keyId =  wepInfoStr[0] - '0';
    if ((keyId > 0) && (keyId <= 4))
        wepKey.KeyId =  keyId;
    //HTTPD_DEBUG_PRINT(("[httpd_config] Got WEP key index %d\r\n", wepKey.KeyId));
    wepKey.KeyLen = (GSN_WDD_WEP_KEY_LEN_T)(strlen(wepKeyStr) / 2);
    //HTTPD_DEBUG_PRINT(("[httpd_config] Got WEP key length in bytes %d\r\n", wepKey.KeyLen));
    keyLen = GsnHttpd_KeyValueGet((UINT8*)wepKeyStr, wepKey.Key);
    if ((keyLen == 5) || (keyLen == 13))
    {
        pWepConfig->KeyId = wepKey.KeyId;
        pWepConfig->KeyLen = wepKey.KeyLen;
        memcpy(pWepConfig, &wepKey, sizeof(wepKey));
        //HTTPD_DEBUG_PRINT(("[httpd_config] Parsed wep key successfully\r\n"));
        HTTPD_DEBUG_PRINT(("[httpd_config] wep key index [%d] length [%d] key[%s]\r\n",
                pWepConfig->KeyId, pWepConfig->KeyLen, wepKeyStr));
    }
    else
        HTTPD_DEBUG_PRINT(("[httpd_config] Unable to get wep key correctly\r\n"));

    return;
}

void GsnHttpdApiConfig_SetWepFromXmlStr(GSN_XML_STRING_T wepInfo,
        GSN_WDD_SEC_WEP_KEY_T* pWepConfig )
{
	if(GsnHttpdApiConfig_SetWepFromXmlStr_FP)
	{
		GsnHttpdApiConfig_SetWepFromXmlStr_FP(wepInfo, pWepConfig);
                return;
	}
    char wepInfoStr[GSN_HTTPD_MAX_WEP_KEY_INDEX_LEN];
    GsnHttpd_SetStrFromXmlStr((UINT8*)wepInfoStr, wepInfo, sizeof(wepInfoStr));
    GsnHttpdApiConfig_SetWepFromStr((char*)wepInfoStr, pWepConfig);
}

void
GsnHttpdApiConfig_SetValuesHttpd()
{
	if(GsnHttpdApiConfig_SetValuesHttpd_FP)
	{
		(GsnHttpdApiConfig_SetValuesHttpd_FP)();
                return;
	}
    // HTTPD settings
    GsnHttpd_SetStrFromXmlStr(sysConfig.httpdConfig.username,
            httpd_settings.username,
            sizeof(sysConfig.httpdConfig.username));
    GsnHttpd_SetStrFromXmlStr(sysConfig.httpdConfig.password,
            httpd_settings.password,
            sizeof(sysConfig.httpdConfig.password));
    sysConfig.httpdConfig.port =
            httpd_settings.port;
    return;
}


void
GsnHttpdApiConfig_SetValuesWpaPersonalClientConfig()
{
	if(GsnHttpdApiConfig_SetValuesWpaPersonalClientConfig_FP)
	{
		(GsnHttpdApiConfig_SetValuesWpaPersonalClientConfig_FP)();
                return;
	}
	if (network_settings.client_settings.client_wireless_settings.password.len)
	{
		sysConfig.networkConfig.clientConfig.passphrase.Len =
				network_settings.client_settings.client_wireless_settings.password.len;
		memcpy(sysConfig.networkConfig.clientConfig.passphrase.Passphrase,
				network_settings.client_settings.client_wireless_settings.password.ptr,
				sysConfig.networkConfig.clientConfig.passphrase.Len);
	}

}
void
GsnHttpdApiConfig_SetValuesWepClientConfig()
{
	if(GsnHttpdApiConfig_SetValuesWepClientConfig_FP)
	{
		(GsnHttpdApiConfig_SetValuesWepClientConfig_FP)();
                return;
	}
	GsnHttpdApiConfig_SetWepFromXmlStr(
					network_settings.client_settings.client_wireless_settings.password,
					&sysConfig.networkConfig.clientConfig.wepKeyConfig);
	GsnHttpd_SetStrFromXmlStr(xmlStrClientWepAuthType,
			network_settings.client_settings.client_wireless_settings.wepAuthType,
			sizeof(xmlStrClientWepAuthType));
	if (!strcmp((char*)xmlStrClientWepAuthType, (char*)s_WepAuthOpenStr))
		sysConfig.networkConfig.clientConfig.wepAuthType = GSN_MAC_AUTH_OPEN;
	else if (!strcmp((char*)xmlStrClientWepAuthType, (char*)s_WepAuthSharedStr))
		sysConfig.networkConfig.clientConfig.wepAuthType = GSN_MAC_AUTH_SHARED;
}
#ifndef ADK_PROV_CONFIG_CLIENT_ENTERPRISE_SUPPORT_DISABLE
void
GsnHttpdApiConfig_SetValuesWpaEnterpriseClientConfig()
{
    if(GsnHttpdApiConfig_SetValuesWpaEnterpriseClientConfig_FP)
	{
		(GsnHttpdApiConfig_SetValuesWpaEnterpriseClientConfig_FP)();
                return;
	}
    GsnHttpd_SetStrFromXmlStr(xmlStrClientEapType,
            network_settings.client_settings.client_wireless_settings.eapType,
            sizeof(xmlStrClientEapType));
    if (!strcmp((char*)xmlStrClientEapType, GSN_WLAN_EAP_FAST_GTC ))
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_FAST_GTC;
	else if (!strcmp((char*)xmlStrClientEapType, GSN_WLAN_EAP_FAST_MSCHAP))
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_FAST_MSCHAP;
    else if (!strcmp((char*)xmlStrClientEapType, GSN_WLAN_EAP_TLS))
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_TLS;
    else if (!strcmp((char*)xmlStrClientEapType, GSN_WLAN_EAP_TTLS))
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_TTLS;
    else if (!strcmp((char*)xmlStrClientEapType, GSN_WLAN_EAP_PEAP0))
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_PEAP0;
    else if (!strcmp((char*)xmlStrClientEapType, GSN_WLAN_EAP_PEAP1))
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_PEAP1;
    else
        sysConfig.networkConfig.clientConfig.eapType = GSN_PROV_EAP_TYPE_NONE;

    if (sysConfig.networkConfig.clientConfig.eapType != GSN_PROV_EAP_TYPE_NONE)
    {
        sysConfig.networkConfig.clientConfig.eapUsername.Length =
                network_settings.client_settings.client_wireless_settings.eapUserName.len;
        memcpy(sysConfig.networkConfig.clientConfig.eapUsername.Name,
                network_settings.client_settings.client_wireless_settings.eapUserName.ptr,
                sysConfig.networkConfig.clientConfig.eapUsername.Length);
        sysConfig.networkConfig.clientConfig.eapPassword.Length =
                network_settings.client_settings.client_wireless_settings.eapPassword.len;
        memcpy(sysConfig.networkConfig.clientConfig.eapPassword.Pwd,
                network_settings.client_settings.client_wireless_settings.eapPassword.ptr,
                sysConfig.networkConfig.clientConfig.eapPassword.Length);
    }
}
#endif
void
GsnHttpdApiConfig_SetValuesClientConfig()
{
    if(GsnHttpdApiConfig_SetValuesClientConfig_FP)
	{
		(GsnHttpdApiConfig_SetValuesClientConfig_FP)();
                return;
	}
    if (network_settings.client_settings.client_wireless_settings.ssid.len)
    {
        sysConfig.networkConfig.clientConfig.ssid.length =
                network_settings.client_settings.client_wireless_settings.ssid.len;
        memcpy(sysConfig.networkConfig.clientConfig.ssid.array,
                network_settings.client_settings.client_wireless_settings.ssid.ptr,
                sysConfig.networkConfig.clientConfig.ssid.length );

        sysConfig.networkConfig.clientConfig.channel =
                network_settings.client_settings.client_wireless_settings.channel;
    }

    GsnHttpd_SetStrFromXmlStr(xmlStrClientSecurityType,
            network_settings.client_settings.client_wireless_settings.security,
            sizeof(xmlStrClientSecurityType));
    //HTTPD_DEBUG_PRINT(("[httpd_config] Got security string %s\r\n", xmlStrClientSecurityType));
    if (!strcmp(GSN_WLAN_SECURITY_NONE_STR, GsnHttpd_ToLowerStr(xmlStrClientSecurityType)))
        sysConfig.networkConfig.clientConfig.securityType = GSN_WLAN_SECURITY_NONE;
    else if (!strcmp(GSN_WLAN_WEP_STR, GsnHttpd_ToLowerStr(xmlStrClientSecurityType)))
    {
        sysConfig.networkConfig.clientConfig.securityType = GSN_WLAN_WEP;		
    	GsnHttpdApiConfig_SetValuesWepClientConfig();
    }
	else if (!strcmp(GSN_WLAN_WPA_PERSONAL_STR, GsnHttpd_ToLowerStr(xmlStrClientSecurityType)))
	{
        sysConfig.networkConfig.clientConfig.securityType = GSN_WLAN_WPA_PERSONAL;
		GsnHttpdApiConfig_SetValuesWpaPersonalClientConfig();
	}
#ifndef ADK_PROV_CONFIG_CLIENT_ENTERPRISE_SUPPORT_DISABLE
    else if (!strcmp(GSN_WLAN_WPA_ENTERPRISE_STR, GsnHttpd_ToLowerStr(xmlStrClientSecurityType)))
    {
        sysConfig.networkConfig.clientConfig.securityType = GSN_WLAN_WPA_ENTERPRISE;
		GsnHttpdApiConfig_SetValuesWpaEnterpriseClientConfig();
    }
#endif

    GsnHttpd_SetStrFromXmlStr(xmlStrClientDhcpFlag,
            network_settings.client_settings.client_ip_settings.ip_type,
            sizeof(xmlStrClientDhcpFlag));
    if (!strcmp((char*)xmlStrClientDhcpFlag, "dhcp"))
        sysConfig.networkConfig.clientConfig.dhcpFlag = 1;
    else if (!strcmp((char*)xmlStrClientDhcpFlag, "static"))
        sysConfig.networkConfig.clientConfig.dhcpFlag = 0;


    GSN_GET_IP_STR_FROM_XML(xmlStrClientIpAddress,
            network_settings.client_settings.client_ip_settings.ip_addr,
            &sysConfig.networkConfig.clientConfig.ipAddress);
    GSN_GET_IP_STR_FROM_XML(xmlStrClientGateway,
            network_settings.client_settings.client_ip_settings.gateway,
            &sysConfig.networkConfig.clientConfig.gateway);
    GSN_GET_IP_STR_FROM_XML(xmlStrClientSubnetmask,
            network_settings.client_settings.client_ip_settings.subnetmask,
            &sysConfig.networkConfig.clientConfig.subnetmask);
    GSN_GET_IP_STR_FROM_XML(xmlStrClientDnsServer,
            network_settings.client_settings.client_ip_settings.dns_addr,
            &sysConfig.networkConfig.clientConfig.dnsServer);

}

void
GsnHttpdApiConfig_SetValuesWpaPersonalApConfig()
{
    if(GsnHttpdApiConfig_SetValuesWpaPersonalApConfig_FP)
	{
		(GsnHttpdApiConfig_SetValuesWpaPersonalApConfig_FP)();
                return;
	}

	if (network_settings.ap_settings.ap_wireless_settings.password.len)
	{
		sysConfig.networkConfig.apConfig.passphrase.Len =
				network_settings.ap_settings.ap_wireless_settings.password.len;
		memcpy(sysConfig.networkConfig.apConfig.passphrase.Passphrase,
				network_settings.ap_settings.ap_wireless_settings.password.ptr,
				sysConfig.networkConfig.apConfig.passphrase.Len);
	}
}


void
GsnHttpdApiConfig_SetValuesAPConfig()
{
    if(GsnHttpdApiConfig_SetValuesAPConfig_FP)
	{
		(GsnHttpdApiConfig_SetValuesAPConfig_FP)();
                return;
	}
/*     sysConfig.networkConfig.apConfig.ssid.length = 32;
     memcpy(sysConfig.networkConfig.apConfig.ssid.array,
                "LINKSYSB1",
                sysConfig.networkConfig.apConfig.ssid.length );
     sysConfig.networkConfig.apConfig.channel = 11;
     
        sysConfig.networkConfig.apConfig.beaconInterval = 10;*/

    // Set AP settings
    if (network_settings.ap_settings.ap_wireless_settings.ssid.len)
    {
        sysConfig.networkConfig.apConfig.ssid.length =
                network_settings.ap_settings.ap_wireless_settings.ssid.len;
        memcpy(sysConfig.networkConfig.apConfig.ssid.array,
                network_settings.ap_settings.ap_wireless_settings.ssid.ptr,
                sysConfig.networkConfig.apConfig.ssid.length );

        sysConfig.networkConfig.apConfig.channel =
                network_settings.ap_settings.ap_wireless_settings.channel;

        sysConfig.networkConfig.apConfig.beaconInterval =
                network_settings.ap_settings.ap_wireless_settings.beaconInterval;
    }

//        sysConfig.networkConfig.apConfig.securityType = GSN_WLAN_SECURITY_NONE;

    GsnHttpd_SetStrFromXmlStr(xmlStrApSecurityType,
            network_settings.ap_settings.ap_wireless_settings.security,
            sizeof(xmlStrApSecurityType));
    if (!strcmp(GSN_WLAN_SECURITY_NONE_STR, GsnHttpd_ToLowerStr(xmlStrApSecurityType)))
            sysConfig.networkConfig.apConfig.securityType = GSN_WLAN_SECURITY_NONE;
    else if (!strcmp(GSN_WLAN_WEP_STR, GsnHttpd_ToLowerStr(xmlStrApSecurityType)))
    {
        sysConfig.networkConfig.apConfig.securityType = GSN_WLAN_WEP;
	    GsnHttpdApiConfig_SetWepFromXmlStr(
            network_settings.ap_settings.ap_wireless_settings.password,
            &sysConfig.networkConfig.apConfig.wepKeyConfig);
    }
    else if (!strcmp(GSN_WLAN_WPA_PERSONAL_STR, GsnHttpd_ToLowerStr(xmlStrApSecurityType)))
    {
        sysConfig.networkConfig.apConfig.securityType = GSN_WLAN_WPA_PERSONAL;
		GsnHttpdApiConfig_SetValuesWpaPersonalApConfig();
	}
   

/*    sysConfig.networkConfig.apConfig.ipAddress = appCtx.if0.nwifCtx.ipConfig.ipv4.ipAddr;
      sysConfig.networkConfig.apConfig.gateway = appCtx.if0.nwifCtx.ipConfig.ipv4.gatewayIpAddr;
        sysConfig.networkConfig.apConfig.subnetmask = appCtx.if0.nwifCtx.ipConfig.ipv4.subnetMask;*/

    GSN_GET_IP_STR_FROM_XML(xmlStrApIpAddress,
            network_settings.ap_settings.ap_ip_settings.ip_addr,
            &sysConfig.networkConfig.apConfig.ipAddress);
    GSN_GET_IP_STR_FROM_XML(xmlStrApGateway,
            network_settings.ap_settings.ap_ip_settings.gateway,
            &sysConfig.networkConfig.apConfig.gateway);
    GSN_GET_IP_STR_FROM_XML(xmlStrApSubnetmask,
            network_settings.ap_settings.ap_ip_settings.subnetmask,
            &sysConfig.networkConfig.apConfig.subnetmask);

/*    sysConfig.networkConfig.apConfig.dhcpServerEnable = 1;
    sysConfig.networkConfig.apConfig.dhcpNumAddresses = 50;
    sysConfig.networkConfig.apConfig.dnsServerEnable = 1;*/

    GsnHttpd_SetStrFromXmlStr(xmlStrApDhcpServerEnabled,
            network_settings.ap_settings.ap_ip_settings.dhcpServerEnable,
            sizeof(xmlStrApDhcpServerEnabled));
    if (!strcmp((char*)xmlStrApDhcpServerEnabled, "true"))
    {
        sysConfig.networkConfig.apConfig.dhcpServerEnable = 1;
        GSN_GET_IP_STR_FROM_XML(xmlStrApDhcpStartAddress,
                network_settings.ap_settings.ap_ip_settings.dhcpStartAddr,
                &sysConfig.networkConfig.apConfig.dhcpAddressStart);
        sysConfig.networkConfig.apConfig.dhcpNumAddresses =
                network_settings.ap_settings.ap_ip_settings.dhcpNumAddrs;
    }
    else if (!strcmp((char*)xmlStrApDhcpServerEnabled, "false"))
        sysConfig.networkConfig.apConfig.dhcpServerEnable = 0;

    GsnHttpd_SetStrFromXmlStr(xmlStrApDnsServerEnabled,
            network_settings.ap_settings.ap_ip_settings.dnsServerEnable,
            sizeof(xmlStrApDnsServerEnabled));
    if (!strcmp((char*)xmlStrApDnsServerEnabled, "true"))
    {
        sysConfig.networkConfig.apConfig.dnsServerEnable = 1;
        GsnHttpd_SetStrFromXmlStr(sysConfig.networkConfig.apConfig.dnsDomainName,
                network_settings.ap_settings.ap_ip_settings.dnsDomain,
                sizeof(sysConfig.networkConfig.apConfig.dnsDomainName));
    }
    else if (!strcmp((char*)xmlStrApDnsServerEnabled, "false"))
        sysConfig.networkConfig.apConfig.dnsServerEnable = 0;

}

void
GsnHttpdApiConfig_SetValuesNetworkMode()
{
    if(GsnHttpdApiConfig_SetValuesNetworkMode_FP)
	{
		(GsnHttpdApiConfig_SetValuesNetworkMode_FP)();
                return;
	}
  //sysConfig.networkConfig.networkMode = GSN_LIMITED_AP;
  //sysConfig.networkConfig.networkMode = GSN_INFRA_CLIENT;
  
    // For now we consider the presence of the xml tag to indicate that a system change is required
    if ((network_settings.network_mode.ptr != NULL) && (network_settings.network_mode.len != 0))
    {
        sysConfig.sysConfigChangeApply = 1;
        GsnHttpd_SetStrFromXmlStr(xmlStrNetworkMode, network_settings.network_mode,
                sizeof(xmlStrNetworkMode));
        //HTTPD_DEBUG_PRINT(("[httpd_config] Got tag mode, value is %s\r\n", xmlStrNetworkMode));
		if (!strcmp((char*)xmlStrNetworkMode, "limited-ap"))
    	{
            sysConfig.networkConfig.networkMode = GSN_LIMITED_AP;
			/* default AP mode is USER-AP mode */
            sysConfig.networkConfig.groupProvMode = GSN_USER_AP;
        }
        else if (!strcmp((char*)xmlStrNetworkMode, "client"))
    	{
            sysConfig.networkConfig.networkMode = GSN_INFRA_CLIENT;
    	}
    }
    else
    {
        sysConfig.sysConfigChangeApply = 0;
    }

}


void
GsnHttpdApiConfig_SetValuesApMode()
{
    if(GsnHttpdApiConfig_SetValuesNetworkMode_FP)
	{
		(GsnHttpdApiConfig_SetValuesNetworkMode_FP)();
                return;
	}
  
    // For now we consider the presence of the xml tag to indicate that a system change is required
    if ((network_settings.ap_mode.ptr != NULL) && (network_settings.ap_mode.len != 0))
    {
        sysConfig.sysConfigChangeApply = 1;
        GsnHttpd_SetStrFromXmlStr(xmlStrApMode, network_settings.ap_mode,
                sizeof(xmlStrApMode));

        if (!strcmp((char*)xmlStrApMode, "user-ap"))
            sysConfig.networkConfig.groupProvMode = GSN_USER_AP;
        else if (!strcmp((char*)xmlStrApMode, "prov-ap"))
            sysConfig.networkConfig.groupProvMode = GSN_PROV_AP;
    }
}


void
GsnHttpdApiConfig_SetValuesMacAddress()
{
    if(GsnHttpdApiConfig_SetValuesMacAddress_FP)
	{
		(GsnHttpdApiConfig_SetValuesMacAddress_FP)();
                return;
	}
    /*GSN_WDD_CTX_T *pWdd;
    
    pWdd = &appCtx.if0.wddCtx;
    memcpy(sysConfig.networkConfig.macAddr, pWdd->macAddr.array, GSN_WLAN_MAC_ADDR_LEN);*/
    
    if ((network_settings.mac_address.ptr != NULL) && (network_settings.mac_address.len != 0))
    {
        UINT8 macAddr[6];
        GsnHttpd_SetStrFromXmlStr(xmlStrMacAddress, network_settings.mac_address,
                        sizeof(xmlStrMacAddress));
        if (GsnHttpd_ParseMac(xmlStrMacAddress, macAddr) == 0)
        {
            memcpy(sysConfig.networkConfig.macAddr, macAddr, 6);
        }
    }
}

void
GsnHttpdApiConfig_SetValuesNetwork()
{
    if(GsnHttpdApiConfig_SetValuesNetwork_FP)
	{
		(GsnHttpdApiConfig_SetValuesNetwork_FP)();
                return;
	}

	sysConfig.sysConfigChangeApply = 0;
	
    GsnHttpdApiConfig_SetValuesMacAddress();

    GsnHttpdApiConfig_SetValuesNetworkMode();

	GsnHttpdApiConfig_SetValuesApMode();

    // Set Client Configuration
    GsnHttpdApiConfig_SetValuesClientConfig();

    // Set AP Configuration
    GsnHttpdApiConfig_SetValuesAPConfig();



    return;
}

void
GsnHttpdApiConfig_SetValuesSysId()
{
    if(GsnHttpdApiConfig_SetValuesSysId_FP)
	{
		(GsnHttpdApiConfig_SetValuesSysId_FP)();
                return;
	}
    GsnHttpd_SetStrFromXmlStr(sysConfig.sysIdConfig.name,
                sys_id_settings.name,
                sizeof(sysConfig.sysIdConfig.name));
}

#ifdef GSN_HTTPD_CONFIG_OTAFU
void
GsnHttpdApiConfig_SetValuesOtafu()
{
    if(GsnHttpdApiConfig_SetValuesOtafu_FP)
	{
		(GsnHttpdApiConfig_SetValuesOtafu_FP)();
                return;
	}
    char tempStr[16];
    GSN_GET_IP_STR_FROM_XML(xmlStrOtafuServerIp,
            otafu_settings.server_ip,
            &sysConfig.otafuConfig.serverIp);
    sysConfig.otafuConfig.serverPort = otafu_settings.server_port;
    GsnHttpd_SetStrFromXmlStr(sysConfig.otafuConfig.baseLoc,
                otafu_settings.base_loc,
                sizeof(sysConfig.otafuConfig.baseLoc));
    GsnHttpd_SetStrFromXmlStr(sysConfig.otafuConfig.app1Name,
                otafu_settings.app1_name,
                sizeof(sysConfig.otafuConfig.app1Name));
    GsnHttpd_SetStrFromXmlStr(sysConfig.otafuConfig.app2Name,
                otafu_settings.app2_name,
                sizeof(sysConfig.otafuConfig.app2Name));
    GsnHttpd_SetStrFromXmlStr(sysConfig.otafuConfig.wlanName,
                otafu_settings.wlan_name,
                sizeof(sysConfig.otafuConfig.wlanName));
    GSN_GET_IP_STR_FROM_XML(xmlStrOtafuProxyIp,
            otafu_settings.proxy_ip,
            &sysConfig.otafuConfig.proxyIp);
    sysConfig.otafuConfig.proxyPort = otafu_settings.proxy_port;
    GsnHttpd_SetStrFromXmlStr((UINT8*)tempStr,
                otafu_settings.update_needed,
                sizeof(tempStr));
    if (!strcmp("true", tempStr))
        sysConfig.otafuConfig.updateNeeded = 1;
    else if (!strcmp("false", tempStr))
        sysConfig.otafuConfig.updateNeeded = 0;
}
#endif


void
GsnHttpdApiConfig_GetValuesHttpd()
{
    if(GsnHttpdApiConfig_GetValuesHttpd_FP)
    {
        (GsnHttpdApiConfig_GetValuesHttpd_FP)();
        return;
    }
// HTTPD Settings
httpd_settings.username.ptr =
        sysConfig.httpdConfig.username;
httpd_settings.username.len =
            strlen((char*)sysConfig.httpdConfig.username);
    httpd_settings.password.ptr =
            sysConfig.httpdConfig.password;
    httpd_settings.password.len =
            strlen((char*)sysConfig.httpdConfig.password);

    httpd_settings.port =
            sysConfig.httpdConfig.port;
    return;
}

void
GsnHttpdApiConfig_GetValuesWpaEnterpriseConfig()
{
    if(GsnHttpdApiConfig_GetValuesWpaEnterpriseConfig_FP)
    {
	(GsnHttpdApiConfig_GetValuesWpaEnterpriseConfig_FP)();
        return;
    }
    if (sysConfig.networkConfig.clientConfig.eapType == GSN_PROV_EAP_TYPE_FAST_MSCHAP)
    {
        network_settings.client_settings.client_wireless_settings.eapType.ptr =
                GSN_WLAN_EAP_FAST_MSCHAP;
        network_settings.client_settings.client_wireless_settings.eapType.len =
                strlen(GSN_WLAN_EAP_FAST_MSCHAP);
    }
    if (sysConfig.networkConfig.clientConfig.eapType == GSN_PROV_EAP_TYPE_FAST_GTC)
    {
        network_settings.client_settings.client_wireless_settings.eapType.ptr =
                GSN_WLAN_EAP_FAST_GTC;
        network_settings.client_settings.client_wireless_settings.eapType.len =
                strlen(GSN_WLAN_EAP_FAST_GTC);
    }
    if (sysConfig.networkConfig.clientConfig.eapType == GSN_PROV_EAP_TYPE_TLS)
    {
        network_settings.client_settings.client_wireless_settings.eapType.ptr =
                GSN_WLAN_EAP_TLS;
        network_settings.client_settings.client_wireless_settings.eapType.len =
                strlen(GSN_WLAN_EAP_TLS);
    }
    if (sysConfig.networkConfig.clientConfig.eapType == GSN_PROV_EAP_TYPE_TTLS)
    {
        network_settings.client_settings.client_wireless_settings.eapType.ptr =
                GSN_WLAN_EAP_TTLS;
        network_settings.client_settings.client_wireless_settings.eapType.len =
                strlen(GSN_WLAN_EAP_TTLS);
    }
    if (sysConfig.networkConfig.clientConfig.eapType == GSN_PROV_EAP_TYPE_PEAP0)
    {
        network_settings.client_settings.client_wireless_settings.eapType.ptr =
                GSN_WLAN_EAP_PEAP0;
        network_settings.client_settings.client_wireless_settings.eapType.len =
                strlen(GSN_WLAN_EAP_PEAP0);
    }

    if (sysConfig.networkConfig.clientConfig.eapType == GSN_PROV_EAP_TYPE_PEAP1)
    {
        network_settings.client_settings.client_wireless_settings.eapType.ptr =
                GSN_WLAN_EAP_PEAP1;
        network_settings.client_settings.client_wireless_settings.eapType.len =
                strlen(GSN_WLAN_EAP_PEAP1);
    }
    network_settings.client_settings.client_wireless_settings.eapUserName.ptr =
            sysConfig.networkConfig.clientConfig.eapUsername.Name;
    network_settings.client_settings.client_wireless_settings.eapUserName.len =
            sysConfig.networkConfig.clientConfig.eapUsername.Length;
    network_settings.client_settings.client_wireless_settings.eapPassword.ptr =
            sysConfig.networkConfig.clientConfig.eapPassword.Pwd;
    network_settings.client_settings.client_wireless_settings.eapPassword.len =
            sysConfig.networkConfig.clientConfig.eapPassword.Length;

}

void
GsnHttpdApiConfig_GetValuesClientConfig()
{
    if(GsnHttpdApiConfig_GetValuesClientConfig_FP)
	{
		(GsnHttpdApiConfig_GetValuesClientConfig_FP)();
                return;
	}
    network_settings.client_settings.client_wireless_settings.channel =
            sysConfig.networkConfig.clientConfig.channel;

    network_settings.client_settings.client_wireless_settings.ssid.ptr =
            sysConfig.networkConfig.clientConfig.ssid.array;
    network_settings.client_settings.client_wireless_settings.ssid.len =
            sysConfig.networkConfig.clientConfig.ssid.length;
    
    // TODO - hack for correct xml parsing
    sysConfig.networkConfig.clientConfig.ssid.array[sysConfig.networkConfig.clientConfig.ssid.length] = 0;

    if ((sysConfig.networkConfig.clientConfig.securityType >= GSN_WLAN_SECURITY_NONE) &&
            (sysConfig.networkConfig.clientConfig.securityType <= GSN_WLAN_WPA_ENTERPRISE))
        strcpy((char*)xmlStrClientSecurityType,
                secOptions[sysConfig.networkConfig.clientConfig.securityType-1]);
    network_settings.client_settings.client_wireless_settings.security.ptr =
            xmlStrClientSecurityType;
    network_settings.client_settings.client_wireless_settings.security.len =
            strlen((char*)xmlStrClientSecurityType);
#ifndef GSN_HTTPD_CONFIG_CLIENT_ENTERPRISE_SUPPORT_DISABLE
    if (sysConfig.networkConfig.clientConfig.securityType == GSN_WLAN_WPA_ENTERPRISE)
    {
        GsnHttpdApiConfig_GetValuesWpaEnterpriseConfig();
    }
    else
#endif
    if (sysConfig.networkConfig.clientConfig.securityType == GSN_WLAN_WEP)
    {
        GsnHttpd_WepKeyToStr(&sysConfig.networkConfig.clientConfig.wepKeyConfig,
                xmlStrWepKeyClient);
        network_settings.client_settings.client_wireless_settings.password.ptr =
                xmlStrWepKeyClient;
        network_settings.client_settings.client_wireless_settings.password.len =
                strlen((char*)xmlStrWepKeyClient);
        if (sysConfig.networkConfig.clientConfig.wepAuthType == GSN_MAC_AUTH_OPEN)
        {
            network_settings.client_settings.client_wireless_settings.wepAuthType.ptr =
		(UINT8*) s_WepAuthOpenStr;
            network_settings.client_settings.client_wireless_settings.wepAuthType.len = strlen((char*)s_WepAuthOpenStr);
        }
        if (sysConfig.networkConfig.clientConfig.wepAuthType == GSN_MAC_AUTH_SHARED)
        {
            network_settings.client_settings.client_wireless_settings.wepAuthType.ptr =
		(UINT8*) s_WepAuthSharedStr;
            network_settings.client_settings.client_wireless_settings.wepAuthType.len = strlen((char*)s_WepAuthSharedStr);
        }
    }
    else
    {
        network_settings.client_settings.client_wireless_settings.password.ptr =
                sysConfig.networkConfig.clientConfig.passphrase.Passphrase;
        network_settings.client_settings.client_wireless_settings.password.len =
                sysConfig.networkConfig.clientConfig.passphrase.Len;
    }
    // TODO - hack for correct xml parsing
    sysConfig.networkConfig.clientConfig.passphrase.Passphrase[sysConfig.networkConfig.clientConfig.passphrase.Len] = 0;


    if (sysConfig.networkConfig.clientConfig.dhcpFlag == 0)
        strcpy((char*)xmlStrClientDhcpFlag, "static");
    else 
        strcpy((char*)xmlStrClientDhcpFlag, "dhcp");
    network_settings.client_settings.client_ip_settings.ip_type.ptr = xmlStrClientDhcpFlag;
    network_settings.client_settings.client_ip_settings.ip_type.len = strlen((char*)xmlStrClientDhcpFlag);

    
    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.clientConfig.ipAddress,
            xmlStrClientIpAddress, network_settings.client_settings.client_ip_settings.ip_addr);

    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.clientConfig.gateway,
            xmlStrClientGateway, network_settings.client_settings.client_ip_settings.gateway);

    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.clientConfig.subnetmask,
            xmlStrClientSubnetmask, network_settings.client_settings.client_ip_settings.subnetmask);

    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.clientConfig.dnsServer,
            xmlStrClientDnsServer, network_settings.client_settings.client_ip_settings.dns_addr);

}



void
GsnHttpdApiConfig_GetValuesAPConfig()
{
    if(GsnHttpdApiConfig_GetValuesAPConfig_FP)
	{
		(GsnHttpdApiConfig_GetValuesAPConfig_FP)();
                return;
	}
    // AP settings
    network_settings.ap_settings.ap_wireless_settings.channel =
            sysConfig.networkConfig.apConfig.channel;

    network_settings.ap_settings.ap_wireless_settings.ssid.ptr =
            sysConfig.networkConfig.apConfig.ssid.array;
    network_settings.ap_settings.ap_wireless_settings.ssid.len =
            sysConfig.networkConfig.apConfig.ssid.length;
    // TODO - hack for correct xml parsing
    sysConfig.networkConfig.apConfig.ssid.array[sysConfig.networkConfig.apConfig.ssid.length] = 0;

    network_settings.ap_settings.ap_wireless_settings.beaconInterval =
            sysConfig.networkConfig.apConfig.beaconInterval;

    if ((sysConfig.networkConfig.apConfig.securityType >= GSN_WLAN_SECURITY_NONE) &&
            (sysConfig.networkConfig.apConfig.securityType <= GSN_WLAN_WPA_PERSONAL))
        strcpy((char*)xmlStrApSecurityType,
                secOptions[sysConfig.networkConfig.apConfig.securityType-1]);
    network_settings.ap_settings.ap_wireless_settings.security.ptr =
            xmlStrApSecurityType;
    network_settings.ap_settings.ap_wireless_settings.security.len =
            strlen((char*)xmlStrApSecurityType);

    if (sysConfig.networkConfig.apConfig.securityType == GSN_WLAN_WEP)
    {
        GsnHttpd_WepKeyToStr(&sysConfig.networkConfig.apConfig.wepKeyConfig,
                xmlStrWepKeyAp);
        network_settings.ap_settings.ap_wireless_settings.password.ptr =
                xmlStrWepKeyAp;
        network_settings.ap_settings.ap_wireless_settings.password.len =
                strlen((char*)xmlStrWepKeyAp);
    }
    else
    {
        network_settings.ap_settings.ap_wireless_settings.password.ptr =
                sysConfig.networkConfig.apConfig.passphrase.Passphrase;
        network_settings.ap_settings.ap_wireless_settings.password.len =
                sysConfig.networkConfig.apConfig.passphrase.Len;
    }
    // TODO - hack for correct xml parsing
    sysConfig.networkConfig.apConfig.passphrase.Passphrase[sysConfig.networkConfig.apConfig.passphrase.Len] = 0;

    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.apConfig.ipAddress,
            xmlStrApIpAddress, network_settings.ap_settings.ap_ip_settings.ip_addr);

    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.apConfig.gateway,
            xmlStrApGateway, network_settings.ap_settings.ap_ip_settings.gateway);

    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.apConfig.subnetmask,
            xmlStrApSubnetmask, network_settings.ap_settings.ap_ip_settings.subnetmask);


    if (sysConfig.networkConfig.apConfig.dhcpServerEnable)
        strcpy((char*)xmlStrApDhcpServerEnabled, "true");
    else
        strcpy((char*)xmlStrApDhcpServerEnabled, "false");
    network_settings.ap_settings.ap_ip_settings.dhcpServerEnable.ptr = xmlStrApDhcpServerEnabled;
    network_settings.ap_settings.ap_ip_settings.dhcpServerEnable.len = strlen((char*)xmlStrApDhcpServerEnabled);
    GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.apConfig.dhcpAddressStart,
            xmlStrApDhcpStartAddress, network_settings.ap_settings.ap_ip_settings.dhcpStartAddr);
    network_settings.ap_settings.ap_ip_settings.dhcpNumAddrs =
            sysConfig.networkConfig.apConfig.dhcpNumAddresses;

    if (sysConfig.networkConfig.apConfig.dnsServerEnable)
        strcpy((char*)xmlStrApDnsServerEnabled, "true");
    else
        strcpy((char*)xmlStrApDnsServerEnabled, "false");
    network_settings.ap_settings.ap_ip_settings.dnsServerEnable.ptr = xmlStrApDnsServerEnabled;
    network_settings.ap_settings.ap_ip_settings.dnsServerEnable.len = strlen((char*)xmlStrApDnsServerEnabled);
    network_settings.ap_settings.ap_ip_settings.dnsDomain.ptr =
            sysConfig.networkConfig.apConfig.dnsDomainName;
    network_settings.ap_settings.ap_ip_settings.dnsDomain.len =
            strlen((char*)sysConfig.networkConfig.apConfig.dnsDomainName);

}


void GsnHttpdApiConfig_GetValuesNetworkMode()
{
    if(GsnHttpdApiConfig_GetValuesNetworkMode_FP)
	{
		(GsnHttpdApiConfig_GetValuesNetworkMode_FP)();
                return;
	}

    if (sysConfig.networkConfig.networkMode == GSN_LIMITED_AP)
        strcpy((char*)xmlStrNetworkMode, "limited-ap");
    else if (sysConfig.networkConfig.networkMode == GSN_INFRA_CLIENT)
        strcpy((char*)xmlStrNetworkMode, "client");
    else
        strcpy((char*)xmlStrNetworkMode, "unknown");
    network_settings.network_mode.ptr = xmlStrNetworkMode;
    network_settings.network_mode.len = strlen((char*)xmlStrNetworkMode);
}


void GsnHttpdApiConfig_GetValuesApMode()
{
    if(GsnHttpdApiConfig_GetValuesNetworkMode_FP)
	{
		(GsnHttpdApiConfig_GetValuesNetworkMode_FP)();
                return;
	}

	/* groupProvMode flag is set in provisioning ap mode*/
    if (sysConfig.networkConfig.groupProvMode == GSN_PROV_AP)
    {
        strcpy((char*)xmlStrApMode, "prov-ap");
	}
    else
	{
        strcpy((char*)xmlStrApMode, "user-ap");
	}
	
    network_settings.ap_mode.ptr = xmlStrApMode;
    network_settings.ap_mode.len = strlen((char*)xmlStrApMode);
}


void GsnHttpdApiConfig_GetValuesRegDomain()
{

    if(GsnHttpdApiConfig_GetValuesRegDomain_FP)
	{
		(GsnHttpdApiConfig_GetValuesRegDomain_FP)();
                return;
	}

    if (sysConfig.networkConfig.regDomain == GSN_WLAN_REG_DOMAIN_ETSI)
    {
        strcpy((char*)xmlStrRegDomain, GSN_WLAN_REG_DOMAIN_ETSI_STR);
    }
    else if (sysConfig.networkConfig.regDomain == GSN_WLAN_REG_DOMAIN_FCC)
    {
        strcpy((char*)xmlStrRegDomain, GSN_WLAN_REG_DOMAIN_FCC_STR);
    }
    else if (sysConfig.networkConfig.regDomain == GSN_WLAN_REG_DOMAIN_TELEC)
    {
        strcpy((char*)xmlStrRegDomain, GSN_WLAN_REG_DOMAIN_TELEC_STR);
    }
    else if (sysConfig.networkConfig.regDomain == GSN_WLAN_REG_DOMAIN_ETSI_MEXS)
    {
        strcpy((char*)xmlStrRegDomain, GSN_WLAN_REG_DOMAIN_ETSI_MEXS_STR);
    }

    else if (sysConfig.networkConfig.regDomain == GSN_WLAN_REG_DOMAIN_UNKNOWN)
    {
        strcpy((char*)xmlStrRegDomain, GSN_WLAN_REG_DOMAIN_UNKNOWN_STR);
    }
    network_settings.reg_domain.ptr = xmlStrRegDomain;
    network_settings.reg_domain.len = strlen((char*)xmlStrRegDomain);
}

void
GsnHttpdApiConfig_GetValuesMacAddress()
{
    if(GsnHttpdApiConfig_GetValuesMacAddress_FP)
	{
		(GsnHttpdApiConfig_GetValuesMacAddress_FP)();
                return;
	}

   // UINT8 myMacAddr[6] = {0x00,0x50,0xc2,0x53,0x10,0xbd};
 // UINT8 i;
  
//  for(i = 0; i < 6; i++)
  //  sysConfig.networkConfig.macAddr[i] = myMacAddr[i];
   
  GSN_SET_STR_XML_FROM_IP(&sysConfig.networkConfig.ipConfig.ipAddr,
                    xmlStrIpAddress, network_settings.ip_settings.ip_addr);
  
    sprintf((char*)xmlStrMacAddress, "%02x:%02x:%02x:%02x:%02x:%02x",
            sysConfig.networkConfig.macAddr[0],
            sysConfig.networkConfig.macAddr[1],
            sysConfig.networkConfig.macAddr[2],
            sysConfig.networkConfig.macAddr[3],
            sysConfig.networkConfig.macAddr[4],
            sysConfig.networkConfig.macAddr[5]);
 
    network_settings.mac_address.ptr = xmlStrMacAddress;
    network_settings.mac_address.len = strlen((char*)xmlStrMacAddress);
}

void
GsnHttpdApiConfig_GetValuesNetwork()
{
    if(GsnHttpdApiConfig_GetValuesNetwork_FP)
	{
		(GsnHttpdApiConfig_GetValuesNetwork_FP)();
                return;
	}
    GsnHttpdApiConfig_GetValuesMacAddress();

    GsnHttpdApiConfig_GetValuesNetworkMode();

	GsnHttpdApiConfig_GetValuesApMode();

    GsnHttpdApiConfig_GetValuesRegDomain();

	// Get Client Configuration
	GsnHttpdApiConfig_GetValuesClientConfig();

	// Get AP Configuration
	GsnHttpdApiConfig_GetValuesAPConfig();
    return;
}

void
GsnHttpdApiConfig_GetValuesSysId()
{
    if(GsnHttpdApiConfig_GetValuesSysId_FP)
	{
		(GsnHttpdApiConfig_GetValuesSysId_FP)();
                return;
	}
    sys_id_settings.name.ptr = sysConfig.sysIdConfig.name;
    sys_id_settings.name.len = strlen((char*)sysConfig.sysIdConfig.name);
    sys_id_settings.uid.ptr = sysConfig.sysIdConfig.uid;
    sys_id_settings.uid.len = strlen((char*)sysConfig.sysIdConfig.uid);

    return;
}

#ifdef GSN_HTTPD_CONFIG_OTAFU
void
GsnHttpdApiConfig_GetValuesOtafu()
{
    if(GsnHttpdApiConfig_GetValuesOtafu_FP)
	{
		(GsnHttpdApiConfig_GetValuesOtafu_FP)();
                return ;
	}
    GSN_SET_STR_XML_FROM_IP(&sysConfig.otafuConfig.serverIp,
        xmlStrOtafuServerIp,
        otafu_settings.server_ip);
    otafu_settings.server_port = sysConfig.otafuConfig.serverPort;
    otafu_settings.base_loc.ptr = sysConfig.otafuConfig.baseLoc;
    otafu_settings.base_loc.len = strlen((char*)sysConfig.otafuConfig.baseLoc);
    otafu_settings.app1_name.ptr = sysConfig.otafuConfig.app1Name;
    otafu_settings.app1_name.len = strlen((char*)sysConfig.otafuConfig.app1Name);
    otafu_settings.app2_name.ptr = sysConfig.otafuConfig.app2Name;
    otafu_settings.app2_name.len = strlen((char*)sysConfig.otafuConfig.app2Name);
    otafu_settings.wlan_name.ptr = sysConfig.otafuConfig.wlanName;
    otafu_settings.wlan_name.len = strlen((char*)sysConfig.otafuConfig.wlanName);
    otafu_settings.proxy_port = sysConfig.otafuConfig.proxyPort;
    GSN_SET_STR_XML_FROM_IP(&sysConfig.otafuConfig.proxyIp,
            xmlStrOtafuProxyIp,
            otafu_settings.proxy_ip);
    if (sysConfig.otafuConfig.updateNeeded)
    {
        otafu_settings.update_needed.ptr = "true";
        otafu_settings.update_needed.len = strlen("true");
    }
    else
    {
        otafu_settings.update_needed.ptr = "false";
        otafu_settings.update_needed.len = strlen("false");
    }

    return;
}
#endif


UINT8 GsnHttpdConfig_IsUriHandlerPresent(const char* uri)
{
    if(GsnHttpdConfig_IsUriHandlerPresent_FP)
	{
		return (GsnHttpdConfig_IsUriHandlerPresent_FP)(uri);
	}

    if (!strcmp(uri, "/gainspan/system/config/network") ||
              !strcmp(uri, "/gainspan/system/config/httpd") ||
              !strcmp(uri, "/gainspan/system/config/id")
#ifdef GSN_HTTPD_CONFIG_OTAFU
              || !strcmp(uri, "/gainspan/system/config/otafu")
#endif
	      )
        return 1;
    else
        return 0;

}

GSN_HTTPD_STATUS_T config_network_cb(ttHttpdUserEvent event, const char* uri, ttHttpdUserConHandle conHandle)
{
    if(config_network_cb_FP)
	{
		return (config_network_cb_FP)(event,uri,conHandle );
	}

    int errorCode;
    UINT32 bufferLen;
    UINT32 encodedSize = 0;
    UINT32 maxSize = GSN_HTTPD_BUF_SIZE;
    INT8* buffer;

    if (!GsnHttpdConfig_IsUriHandlerPresent(uri))
        return GSN_HTTPD_URI_HANDLER_INVALID;

    buffer = GsnHttpd_GetBuffer();

    if (!buffer)
    	return GSN_HTTPD_FAILURE;

    switch (event)
    {
        case TM_HTTPD_EVENT_BODY_RECV:
        //case TM_HTTPD_EVENT_ALL_RECV:
        {
            UINT8 *ParentNodeStart, *ParentNodeEnd;
            // Read body
            bufferLen = TM_BODY_BUFFER_LEN;

            /* Do not copy the body message. Let the HTTPD server process CGI Args in body */
            tfHttpdUserGetRequestBody(conHandle, buffer, (ttUserIntPtr)&bufferLen ,
                    0/*  TM_HTTPD_NO_COPY*/);

            ParentNodeStart = (UINT8*) buffer;     //Parent Node start address
            ParentNodeEnd = (UINT8*)buffer + bufferLen -1;    //Parent Node End adress    

            memset(&network_settings, 0, sizeof(network_settings));
            memset(&httpd_settings, 0, sizeof(httpd_settings));

            if (!strcmp(uri, "/gainspan/system/config/network"))
            {
                GsnXml_Decode(ParentNodeStart, ParentNodeEnd, (GSN_XML_COMPLEX_OBJ_T *)&xml_network_settings, (UINT8 *)&network_settings);
                GsnHttpdApiConfig_SetValuesNetwork();
            }
            else if (!strcmp(uri, "/gainspan/system/config/httpd"))
            {
                GsnXml_Decode(ParentNodeStart, ParentNodeEnd, (GSN_XML_COMPLEX_OBJ_T *)&xml_httpd_settings, (UINT8 *)&httpd_settings);
                GsnHttpdApiConfig_SetValuesHttpd();
            }
            else if (!strcmp(uri, "/gainspan/system/config/id"))
            {
                GsnXml_Decode(ParentNodeStart, ParentNodeEnd, (GSN_XML_COMPLEX_OBJ_T *)&xml_sys_id_settings, (UINT8 *)&sys_id_settings);
                GsnHttpdApiConfig_SetValuesSysId();
            }
#ifdef GSN_HTTPD_CONFIG_OTAFU
            else if (!strcmp(uri, "/gainspan/system/config/otafu"))
            {
                GsnXml_Decode(ParentNodeStart, ParentNodeEnd, (GSN_XML_COMPLEX_OBJ_T *)&xml_otafu_settings, (UINT8 *)&otafu_settings);
                GsnHttpdApiConfig_SetValuesOtafu();
            }
#endif
        }
        break;
        case TM_HTTPD_EVENT_SEND_READY:

            if (GsnHttpd_GetHttpMethod(conHandle) == TM_HTTP_METHOD_GET)
            {
                if (httpdConfigCbFn)
                    (*httpdConfigCbFn)(&sysConfig, GSN_HTTPD_URI_METHOD_GET);
                memset(&network_settings, 0, sizeof(network_settings));
                memset(&httpd_settings, 0, sizeof(httpd_settings));
                if (!strcmp(uri, "/gainspan/system/config/network"))
                {
                  
                    GsnHttpdApiConfig_GetValuesNetwork();
                    
                   GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *)&xml_network_settings, (UINT8*)&network_settings,
                            (UINT8*) buffer, maxSize, &encodedSize);
                }
                else if (!strcmp(uri, "/gainspan/system/config/httpd"))
                {
                    GsnHttpdApiConfig_GetValuesHttpd();
                    GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *)&xml_httpd_settings, (UINT8*)&httpd_settings,
                            (UINT8*) buffer, maxSize, &encodedSize);
                }
                else if (!strcmp(uri, "/gainspan/system/config/id"))
                {
                    GsnHttpdApiConfig_GetValuesSysId();
                    GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *)&xml_sys_id_settings, (UINT8*)&sys_id_settings,
                            (UINT8*) buffer, maxSize, &encodedSize);
                }
#ifdef GSN_HTTPD_CONFIG_OTAFU
                else if (!strcmp(uri, "/gainspan/system/config/otafu"))
                {
                    GsnHttpdApiConfig_GetValuesOtafu();
                    GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *)&xml_otafu_settings, (UINT8*)&otafu_settings,
                            (UINT8*) buffer, maxSize, &encodedSize);
                }
#endif
                GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, encodedSize, TM_BLOCKING_ON, &errorCode);
            }
            else
            {
                sprintf(buffer, "<status>ok</status>");
                GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer), TM_BLOCKING_ON, &errorCode);
                if (GsnHttpd_GetHttpMethod(conHandle) == TM_HTTP_METHOD_POST)
                {
                    if (httpdConfigCbFn)
                                    (*httpdConfigCbFn)(&sysConfig, GSN_HTTPD_URI_METHOD_POST);
                }
            }

            break;
        case TM_HTTPD_EVENT_CON_CLOSE:
            break;
    }

    // TODO FIXME REMINDER - This release needs to happen in all HTTPD callbacks!!
    if (buffer)
    {
    	GsnHttpd_ReleaseBuffer(buffer);
    	buffer = NULL;
    }

    return GSN_HTTPD_SUCCESS;
}

UINT8
GsnHttpdApi_ConfigInit(GSN_HTTPD_API_CONFIG_CB_FN cb_fn)
{
    if(GsnHttpdApi_ConfigInit_FP)
    {
        return GsnHttpdApi_ConfigInit_FP(cb_fn);
    }
    if (cb_fn)
        httpdConfigCbFn = cb_fn;

    sysConfig.sysConfigChangeApply = 0;
    sysConfig.networkConfig.regDomain = GSN_WLAN_REG_DOMAIN_UNKNOWN;

    if (httpdConfigCbFn)
        (*httpdConfigCbFn)(&sysConfig, GSN_HTTPD_URI_METHOD_GET);


    GsnHttpd_UriHandlerConfig("/gainspan/system/config", GSN_HTTPD_URI_METHOD_GET_POST,
            "Network Configuration", config_network_cb, GSN_HTTPD_CONTENT_APP_XML);

    return 0;
}

VOID
GsnHttpdApi_ConfigDeInit()
{
    if(GsnHttpdApi_ConfigDeInit_FP)
    {
        GsnHttpdApi_ConfigDeInit_FP();
        return;
    }
    httpdConfigCbFn = NULL;

    sysConfig.sysConfigChangeApply = 0;
    sysConfig.networkConfig.regDomain = GSN_WLAN_REG_DOMAIN_UNKNOWN;

    GsnHttpd_UriHandlerConfig("/gainspan/system/config", 0, NULL, NULL, 0);

}




