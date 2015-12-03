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
 * $RCSfile: app_cfg.c,v $
 *
 * Description : 
 *******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "api\api_safe.h"
#include "safe-flash\nor\phy\micron\n25q_32mb_3v_65nm.h"
#include "safe-flash\nor\flashdrv.h"
#include "app_default_cfg.h"
#include "app_debug.h"
/*******************************************************************************
 * Private definitions
 ******************************************************************************/

/*******************************************************************************
 * Public Functions
 ******************************************************************************/
// mac address read API
#define OTP_MAC_LEN_MASK 0x7
#define OTP_MAC_LEN 0x8
GSN_STATUS
AppConfig_OTPMacRead(UINT8* mac, UINT8 id)
{
    UINT8 otpGrpId, otpGrpVer;
    UINT8 data[OTP_MAC_LEN] ={0},data1[OTP_MAC_LEN];
    UINT16 dataLen=0,i=0, macLen = 6;

	// mac0 at F8, mac1 at F9 mac2 at FA
    // read mac0
    if((id == 0xF8) || (id == 0xF9) || (id == 0xFA))
    {
        otpGrpVer =0;
        otpGrpId = id;
        if(GSN_SUCCESS != GsnOtpMm_Read(otpGrpId,otpGrpVer,
	                  &dataLen, data))
        {
	        return GSN_FAILURE;
        }

#ifndef OTP_OLD_FORMAT_MAC
		if(dataLen ) // since mac is comming in reverse manner so reverse the string and use it
		{
			for(i=0;i<OTP_MAC_LEN;i++)
			{
				data1[i] = data[OTP_MAC_LEN_MASK - i];
			}
			if(id == 0xFA)macLen = 8;
			memcpy(mac,data1,macLen);
		}
#else
        if(dataLen)
        {
            memcpy(mac,data,6);
        }
#endif
	}
	else
	{
		return GSN_FAILURE;
	}
	return GSN_SUCCESS;
}

VOID 
AppConfig_DefaultInit(APP_CONFIG_T * pConfig)
{
	APP_CLIENT_CONFIG_T *pCliCfg;
	APP_AP_CONFIG_T *pAPCfg;

	if(AppConfig_Load(pConfig) != GSN_SUCCESS)
	{
        UINT8 mac[6];
        if(AppConfig_OTPMacRead(mac,GSN_OTP_MM_ID_MAC_ID0) == GSN_SUCCESS)
        {
        	memcpy(pConfig->networkConfig.macAddr, mac, GSN_WLAN_MAC_ADDR_LEN);
        }
        else
		{			
			UINT8 dfltMacAddr[]=DEFAULT_MAC_ADDR;
			/* SYSTEM*/
			memcpy(pConfig->networkConfig.macAddr, dfltMacAddr, GSN_WLAN_MAC_ADDR_LEN);
		}

		/*STA (client Config)*/	
		{			
			UINT8 ipAddr[4] = DEFAULT_CLI_IP_ADDR;
			UINT8 subnetAddr[4] = DEFAULT_CLI_SUBNET_MASK;
			UINT8 gatewayIpAddr[4] = DEFAULT_CLI_GATEWAY_ADDR;
			UINT8 dnsServerAddr[4] = DEFAULT_CLI_DNS_ADDR;
			UINT8 wepKey[DEFAULT_CLI_WEP_KEYLEN] = DEFAULT_CLI_WEP_KEY;

			pCliCfg = &pConfig->networkConfig.clientConfig;
						
			pCliCfg->ssid.length = strlen(DEFAULT_CLI_SSID);
			strcpy((INT8 *)pCliCfg->ssid.array, DEFAULT_CLI_SSID);
			pCliCfg->channel= DEFAULT_CLI_CHNL;
			
			pCliCfg->dhcpFlag = DEFAULT_CLI_DHCP_ENABLE;
			
			pCliCfg->securityType = DEFAULT_CLI_SECURITY;
			pCliCfg->passphrase.Len = strlen(DEFAULT_CLI_PASSPHRASE);
			strcpy((INT8 *)pCliCfg->passphrase.Passphrase, DEFAULT_CLI_PASSPHRASE);
			pCliCfg->wepAuthType = DEFAULT_CLI_WEP_AUTH;
			pCliCfg->wepKeyConfig.authType = DEFAULT_CLI_WEP_AUTH;
			pCliCfg->wepKeyConfig.KeyId = DEFAULT_CLI_WEP_KEYID;
			pCliCfg->wepKeyConfig.KeyLen = DEFAULT_CLI_WEP_KEYLEN;
			memcpy((VOID*)&pCliCfg->wepKeyConfig.Key, wepKey, DEFAULT_CLI_WEP_KEYLEN);

			pCliCfg->eapType = (GsnProvEapType)DEFAULT_CLI_EAP_TYPE;
			pCliCfg->eapUsername.Length = strlen(DEFAULT_CLI_EAP_USERNAME);
			strcpy((INT8 *)pCliCfg->eapUsername.Name, DEFAULT_CLI_EAP_USERNAME);
			pCliCfg->eapPassword.Length = strlen(DEFAULT_CLI_EAP_PASSWORD);
			strcpy((INT8 *)pCliCfg->eapPassword.Pwd, DEFAULT_CLI_EAP_PASSWORD);
			//if(!pCliCfg->dhcpFlag)
			{
				pCliCfg->ipAddress = IP_ADDRESS(ipAddr[3], ipAddr[2], ipAddr[1], ipAddr[0]);
				pCliCfg->subnetmask = IP_ADDRESS(subnetAddr[3], subnetAddr[2], subnetAddr[1], subnetAddr[0]);
				pCliCfg->gateway = IP_ADDRESS(gatewayIpAddr[3], gatewayIpAddr[2], gatewayIpAddr[1], gatewayIpAddr[0]);
				pCliCfg->dnsServer = IP_ADDRESS(dnsServerAddr[3], dnsServerAddr[2], dnsServerAddr[1], dnsServerAddr[0]);
			}
		}
		
		/*AP Config)*/
		{
			
			UINT8 ipAddr[4] = DEFAULT_AP_IP_ADDR;
			UINT8 subnetAddr[4] = DEFAULT_AP_SUBNET_MASK;
			UINT8 gatewayIpAddr[4] = DEFAULT_AP_GATEWAY_ADDR;
			UINT8 dhcpStartAddr[4] = DEFAULT_AP_DHCP_SRVR_ADDR_START;
			UINT8 wepKey[DEFAULT_AP_WEP_KEYLEN] = DEFAULT_AP_WEP_KEY;
			pAPCfg = &pConfig->networkConfig.apConfig;
					
#ifdef ADK_CONFIG_SSID_FROM_MAC_ADDR
	        pAPCfg->ssid.length =sprintf((void*)pAPCfg->ssid.array,
	                    DEFAULT_AP_SSID_PREFIX"%02x%02x%02x",
	                    pConfig->networkConfig.macAddr[3],
	                    pConfig->networkConfig.macAddr[4],
	                    pConfig->networkConfig.macAddr[5]);
#else

			pAPCfg->ssid.length = strlen(DEFAULT_AP_SSID);
			strcpy((INT8 *)pAPCfg->ssid.array, DEFAULT_AP_SSID);
#endif
			pAPCfg->channel =  DEFAULT_AP_CHNL;

			pAPCfg->beaconInterval = DEFAULT_AP_BCN_INTERVAL;
			memcpy((VOID *)&pAPCfg->dhcpAddressStart, dhcpStartAddr, 4);
			pAPCfg->dhcpServerEnable = DEFAULT_AP_DHCP_SRVR_ENABLE;
			pAPCfg->dhcpNumAddresses = DEFAULT_AP_DHCP_SRVR_NUM_ADDRS;

			pAPCfg->dnsServerEnable = DEFAULT_AP_DNS_SRVR_ENABLE;
		    strcpy((INT8 *)pAPCfg->dnsDomainName, DEFAULT_AP_DNS_DOMAIN_NAME);

		    pAPCfg->securityType = DEFAULT_AP_SECURITY;
			pAPCfg->passphrase.Len = strlen(DEFAULT_AP_PASSPHRASE);
			strcpy((INT8 *)pAPCfg->passphrase.Passphrase, DEFAULT_AP_PASSPHRASE);
			pAPCfg->wepKeyConfig.authType = (GSN_WDD_WEP_AUTH_TYPE_T) DEFAULT_AP_WEP_AUTH;
			pAPCfg->wepKeyConfig.KeyId = DEFAULT_AP_WEP_KEYID;
			pAPCfg->wepKeyConfig.KeyLen = DEFAULT_AP_WEP_KEYLEN;
			memcpy((VOID*)&pAPCfg->wepKeyConfig.Key, wepKey, DEFAULT_AP_WEP_KEYLEN);

			pAPCfg->ipAddress = IP_ADDRESS(ipAddr[3], ipAddr[2], ipAddr[1], ipAddr[0]);
			pAPCfg->subnetmask = IP_ADDRESS(subnetAddr[3], subnetAddr[2], subnetAddr[1], subnetAddr[0]);
			pAPCfg->gateway = IP_ADDRESS(gatewayIpAddr[3], gatewayIpAddr[2], gatewayIpAddr[1], gatewayIpAddr[0]);
			pAPCfg->dhcpAddressStart = IP_ADDRESS(dhcpStartAddr[3], dhcpStartAddr[2], dhcpStartAddr[1], dhcpStartAddr[0]);
		}
		
		/* System ID */
		{
		    strncpy((char*)pConfig->sysIdConfig.name, (void*)pAPCfg->ssid.array, pAPCfg->ssid.length + 1);
		    sprintf((char*)pConfig->sysIdConfig.uid, "%02x%02x%02x%02x%02x%02x",
		                pConfig->networkConfig.macAddr[0],
		                pConfig->networkConfig.macAddr[1],
		                pConfig->networkConfig.macAddr[2],
		                pConfig->networkConfig.macAddr[3],
		                pConfig->networkConfig.macAddr[4],
		                pConfig->networkConfig.macAddr[5]);
		}

		/*COMMON*/
		 pConfig->networkConfig.networkMode = DEFAULT_MODE;
		/*Store configuration */		
		AppConfig_Save(pConfig);
	}
	else
	{
 		sprintf((char*)pConfig->sysIdConfig.uid, "%02x%02x%02x%02x%02x%02x",
 						pConfig->networkConfig.macAddr[0],
 						pConfig->networkConfig.macAddr[1],
 						pConfig->networkConfig.macAddr[2],
 						pConfig->networkConfig.macAddr[3],
 						pConfig->networkConfig.macAddr[4],
 						pConfig->networkConfig.macAddr[5]);
	}
}

GSN_STATUS 
AppConfig_Load(APP_CONFIG_T *pConfig)
{
	F_FILE *fp;
	int ret = 0;
	
	fp = f_open(APP_CONFIG_FILE,"r");
	if (!fp)
	{
		return GSN_FAILURE;
	}
#if 0
	else
	{
		f_close(fp);
		return GSN_FAILURE;
	}
#endif

	long file_size = f_filelength(APP_CONFIG_FILE);
	if(file_size != sizeof(APP_CONFIG_T))
	{
		f_close(fp);
		return GSN_FAILURE;
	}

	ret = f_read(pConfig, 1, file_size, fp);	
	if(ret != file_size)
	{
		f_close(fp);
		return GSN_FAILURE;
	}
	
	f_close(fp);

	return GSN_SUCCESS;
}

GSN_STATUS 
AppConfig_Save(APP_CONFIG_T *pConfig)
{
	F_FILE *fp;

	f_delete(APP_CONFIG_FILE);

	fp = f_open(APP_CONFIG_FILE,"w+");
	if (!fp)
	{
		return GSN_FAILURE;
	}

	if(f_write(pConfig, 1, sizeof(APP_CONFIG_T), fp) != sizeof(APP_CONFIG_T))
	{
		f_close(fp);
		return GSN_FAILURE;
	}

	f_close(fp);

	return GSN_SUCCESS;
}

