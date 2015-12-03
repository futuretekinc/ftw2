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
* $RCSfile: s2w_web_prov.h,v $
*
* Description : s2w GEPS interface file
*******************************************************************************/
#ifndef _S2W_WEB_PROV_H_
#define _S2W_WEB_PROV_H_
PUBLIC UINT32
S2wApp_WebserverStackSize_Get(UINT32 sslEnbl);
PUBLIC UINT8*
S2wApp_WebserverStack_Get(UINT32 sslEnbl);
PUBLIC VOID
S2wApp_WebserverStack_Free(UINT8* stackPtr);
typedef struct S2W_PROV_INIFO
{
    /* Page 2 values - Basic WiFi*/
    INT8 ssid[33];
    INT8 chnl[3];
    INT8 connType[2]; /* 0 or 1*/
    INT8 mode[2]; /* 0 or 1*/
    INT8 security[2]; /* 0 security none. >1 security present*/
    INT8 wepAuthMode[10];
    INT8 wepID[2]; 
    INT8 wepkey[27]; /* its either 10 0r 26 chars*/
    INT8 pskPassPhrase[33];

    INT8 eapType[15];

    INT8 eapUserName[33];
    INT8 eapPassWd[33];

    INT8 privateKeyLen[5];
    INT8 *privateKey;/* enterprise security - private key file*/

    INT8 clientCertLen[5];
    INT8 *clientCert; /* enterprise security - client certificate*/
    
    INT8 cAcertLen[5];
    INT8 *cAcert; /* enterprise security - CA certificate*/
    
    
    /* Page 3 values - IP Network*/
    INT8 dhcpEnbl[2];
    INT8 automaticDns[2];
    INT8 staticIPaddr[16];
    INT8 subnetMask[16];
    INT8 gateWayIp[16];
    INT8 primeDnsIp[16];
    INT8 secDnsIp[16];

    /* Page 4 values - Device Configuration*/
    INT8 userName[32];
    INT8 passwd[32];
    INT8 newUserName[32];
    INT8 newPasswd[32];
    INT8 ValidatePasswd[32];
    
}S2W_PROV_INIFO_T;

typedef struct TAG_VALUE_MAP
{
    INT8 *tag;
    INT8 *value;
}TAG_VALUE_MAP_T;

typedef enum INPUT_ERROR
{
    INPUT_ERROR_NONE,
    INPUT_ERROR_NEW_PASSWD = 1,
    INPUT_ERROR_NEW_PASSWD_LEN = INPUT_ERROR_NEW_PASSWD << 1, // 2
    /*IP netwrk page error*/
    INPUT_ERROR_IP_ADDR = INPUT_ERROR_NEW_PASSWD_LEN << 1, // 2
    INPUT_ERROR_NET_MASK = INPUT_ERROR_IP_ADDR << 1, // 4
    INPUT_ERROR_GATE_WAY = INPUT_ERROR_NET_MASK << 1,// 8
    INPUT_ERROR_PRIME_DNS = INPUT_ERROR_GATE_WAY << 1, // 16
    INPUT_ERROR_SEC_DNS = INPUT_ERROR_PRIME_DNS << 1, // 16

    /*Basic wifi page error*/
    INPUT_ERROR_SSID = INPUT_ERROR_SEC_DNS << 1,
    INPUT_ERROR_CHNL = INPUT_ERROR_SSID << 1, // 16
    INPUT_ERROR_WEP_ID = INPUT_ERROR_CHNL << 1, // 16
    INPUT_ERROR_WEP_KEY = INPUT_ERROR_WEP_ID<<1,
    INPUT_ERROR_PSK_PASSPHRASE = INPUT_ERROR_WEP_KEY<<1,
    INPUT_ERROR_EAP_USERNAME = INPUT_ERROR_PSK_PASSPHRASE <<1,
    INPUT_ERROR_EAP_PASSWD = INPUT_ERROR_EAP_USERNAME<<1
}INPUT_ERROR_T;
 typedef enum S2W_WEB_STORE_PARAMS
{
	S2W_WEB_PARAMS_SND_TO_HOST,
	S2W_WEB_PARAMS_STORE,
	S2W_WEB_PARAMS_SND_AND_STORE
}S2W_WEB_STORE_PARAMS_T;

#define SECURITY_WEP    '1'
#define SECURITY_PSK    '2'
#define SECURITY_EAP    '3'

extern INT8 *webPgBuf;

PUBLIC VOID
S2wWebProv_WebProvStop();

PUBLIC VOID
AppOtafu_Init(APP_MAIN_CTX_T* pAppCtx);

PUBLIC VOID
AppExtOtafu_Init(APP_MAIN_CTX_T* pAppCtx);
#endif /*_S2W_WEB_PROV_H_*/
