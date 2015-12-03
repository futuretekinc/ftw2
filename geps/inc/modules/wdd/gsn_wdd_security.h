/*******************************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: gsn_wdd_security.h,v $
*
* Description : This file contains DOT11 security related definitions.
********************************************************************************/
#ifndef _GSN_WDD_SECURITY_H_
#define _GSN_WDD_SECURITY_H_

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stddef.h>

/**
 *******************************************************************************
 * @file gsn_wdd_security.h
 * @brief GSN WDD security definitions.
 *    This file contains WDD security related definitions.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/



/**
 *******************************************************************************
 * @defgroup GsnWddSecurity GSN 802.11 Security Definitions
 *    This group various definitions related to 802.11 link security,
 * used by the Wireless Device Driver (WDD) module.
 ******************************************************************************/


/*******************************************************************************
 * Public Macros
 ******************************************************************************/
typedef void * GSN_WDD_WPAIF_HANDLE_T;


/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Bitmask for supported ciphers.
 ******************************************************************************/
#define GSN_WDD_SEC_CIPHER_NONE WPA_CIPHER_NONE /* No Ciphrer*/
#define GSN_WDD_SEC_CIPHER_WEP40 WPA_CIPHER_WEP40 /* WEP ($0 Bit) Ciphrer*/
#define GSN_WDD_SEC_CIPHER_WEP104 WPA_CIPHER_WEP104 /* WEP (104 Bit)  Ciphrer*/
#define GSN_WDD_SEC_CIPHER_TKIP WPA_CIPHER_TKIP /* TIKIP Ciphrer*/
#define GSN_WDD_SEC_CIPHER_CCMP WPA_CIPHER_CCMP /* CCMP Ciphrer*/

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Bitmask for supported key management protocols.
 ******************************************************************************/

#define GSN_WDD_SEC_KEY_MGMT_IEEE8021X  WPA_KEY_MGMT_IEEE8021X /*IEEE8021X key management*/
#define GSN_WDD_SEC_KEY_MGMT_PSK        WPA_KEY_MGMT_PSK /*PSK key management.*/
#define GSN_WDD_SEC_KEY_MGMT_NONE       WPA_KEY_MGMT_NONE /*no key management.*/


/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Bitmask for Supported protocols.
 ******************************************************************************/
#define GSN_WDD_SEC_PROTO_WPA          WPA_PROTO_WPA /* WPA*/
#define GSN_WDD_SEC_PROTO_RSN           WPA_PROTO_RSN /* WPA2 */
#define GSN_WDD_SEC_PROTO_WPS           WPA_PROTO_WPS /* WPS */

/**
 *******************************************************************************
 * @ingroup GsnWddSecurity
 * @brief EAP FAST PAC key length.
 ******************************************************************************/
#define GSN_WDD_SEC_EAP_FAST_PAC_KEY_LEN    32

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WPA PSK Passphrase length. Passphrase cannot be longer than 63 chars
 *        as per standard but we define one more here for NULL char.
 ******************************************************************************/
#define GSN_WDD_SEC_PASSPHRASE_LEN          64

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief EAP FAST User name length.
 ******************************************************************************/
#define GSN_WDD_SEC_EAP_FAST_UNAME_LEN      32

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief EAP FAST Password length.
 ******************************************************************************/
#define GSN_WDD_SEC_EAP_FAST_PWD_LEN        32

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Maximum WEP Key length in bytes.
 ******************************************************************************/
#define GSN_WDD_SEC_MAX_WEP_KEY_LEN         GSN_WDD_SEC_WEP104_KEY_LEN

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Bitmask for open system authentication. Needed for WPA/RSN.
 ******************************************************************************/
#define GSN_WDD_SEC_WPA_AUTH_ALG_OPEN       BIT(0)

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Bitmask for shared authentication. Requires WEP keys.
 ******************************************************************************/
#define GSN_WDD_SEC_WPA_AUTH_ALG_SHARED     BIT(1)

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief PSK PMK length.
 ******************************************************************************/
#define GSN_WDD_SEC_PMK_LEN                 32

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WPS Pin Length.
 ******************************************************************************/
#define GSN_WDD_SEC_WPS_PIN_LEN             8

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WPS Private and Public Key Length in bytes.
 ******************************************************************************/
#define GSN_WDD_SEC_WPS_KEY_LEN             192


/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WPS UUID Length in bytes.
 ******************************************************************************/
#define GSN_WDD_SEC_WPS_UUID_LEN             16



/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Security mode.
 *      This enum defines the security mode to be used.
 ******************************************************************************/
typedef enum GSN_WDD_SEC_MODE
{
    GSN_WDD_SEC_MODE_DISABLE = BIT(0),
    GSN_WDD_SEC_MODE_ANY = BIT(1),
    GSN_WDD_SEC_MODE_WEP = BIT(2),
    GSN_WDD_SEC_MODE_WPA_PERSONAL = BIT(3),
    GSN_WDD_SEC_MODE_WPA_ENTERPRISE = BIT(4),
    GSN_WDD_SEC_MODE_WPA2_PERSONAL = BIT(5),
    GSN_WDD_SEC_MODE_WPA2_ENTERPRISE = BIT(6)
}GSN_WDD_SEC_MODE_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WEP key length.
 *      This enum defines the WEP key length to be used.
 ******************************************************************************/
typedef enum GSN_WDD_WEP_KEY_LEN
{
    GSN_WDD_SEC_WEP40_KEY_LEN = 5, /* WEP-40 Key length in bytes. */
    GSN_WDD_SEC_WEP104_KEY_LEN = 13 /* WEP-104 Key length in bytes.*/
}GSN_WDD_WEP_KEY_LEN_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WEP authentication mode.
 *      This enum defines the authentication mode to be used.
 ******************************************************************************/
typedef enum GSN_WDD_WEP_AUTH_TYPE
{
    GSN_WDD_SEC_WEP_OPEN, /* WEP-40 Key length in bytes. */
    GSN_WDD_SEC_WEP_SHARED/* WEP-104 Key length in bytes.*/
}GSN_WDD_WEP_AUTH_TYPE_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WEP key structure.
 *      This structure defines the WEP key.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_WEP_KEY
{
  GSN_WDD_WEP_AUTH_TYPE_T authType;
  GSN_WDD_WEP_KEY_LEN_T KeyLen;
  UINT8 KeyId;
  UINT8 Key[GSN_WDD_SEC_MAX_WEP_KEY_LEN];
} GSN_WDD_SEC_WEP_KEY_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief PSK Passphrase.
 *      This structure defines the passphrase type.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_PSK
{
   UINT8 Len;
   UINT8 Passphrase[GSN_WDD_SEC_PASSPHRASE_LEN];
} GSN_WDD_SEC_PSK_T;


/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief EAP username structure.
 *      This structure defines the EAP FAST user name type.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_EAP_UNAME
{
  UINT8 Length;
  UINT8 Name[GSN_WDD_SEC_EAP_FAST_UNAME_LEN];
} GSN_WDD_SEC_EAP_UNAME_T;


/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief EAP password structure.
 *      This structure defines the EAP FAST password type.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_EAP_PWD
{
  UINT8 Length;
  UINT8 Pwd[GSN_WDD_SEC_EAP_FAST_PWD_LEN];
} GSN_WDD_SEC_EAP_PWD_T;


/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Encryption Algorith.
 *      This enum defines the Encryption algorithm.
 ******************************************************************************/
typedef enum GSN_WDD_WPA_ALGO
{
    GSN_WDD_WPA_ALGO_AES,
    GSN_WDD_WPA_ALGO_TKIP,
    GSN_WDD_WPA_ALGO_MIXED /* This can be set to indicate "ANY" encryption algo*/
}GSN_WDD_WPA_ALGO_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Security PSK Configuration.
 *
 *     This structure defines the PSK configuration used for configuring the WDD
 *     for connecting to a WLAN with PSK key mgmt.
 * @see GSN_WDD_SECURITY_CONFIG_T and GSN_WDD_WLAN_CONFIG_T.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_PSK_CONFIG
{
    UINT8   pskValid;     /**< Indicates if pre-computed PSK in psk field is
                                valid */
    GSN_WDD_WPA_ALGO_T  wpaAlgo;
    GSN_WDD_SEC_PSK_T   passPhrase;   /**< Passphrase */
    UINT8   psk[GSN_WDD_SEC_PMK_LEN]; /**< Pre-computed PSK */
} GSN_WDD_SEC_PSK_CONFIG_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Security EAP Types.
 *
 *     EAP Method Types as allocated by IANA:
 * http://www.iana.org/assignments/eap-numbers.
 *
 ******************************************************************************/
typedef enum GSN_EAP_TYPE
{
    GSN_EAP_TYPE_NONE = 0,
    GSN_EAP_TYPE_IDENTITY = 1 /* RFC 3748 */,
    GSN_EAP_TYPE_NOTIFICATION = 2 /* RFC 3748 */,
    GSN_EAP_TYPE_NAK = 3 /* Response only, RFC 3748 */,
    GSN_EAP_TYPE_MD5 = 4, /* RFC 3748 */
    GSN_EAP_TYPE_OTP = 5 /* RFC 3748 */,
    GSN_EAP_TYPE_GTC = 6, /* RFC 3748 */
    GSN_EAP_TYPE_TLS = 13 /* RFC 2716 */,
    GSN_EAP_TYPE_LEAP = 17 /* Cisco proprietary */,
    GSN_EAP_TYPE_SIM = 18 /* RFC 4186 */,
    GSN_EAP_TYPE_TTLS = 21 /* draft-ietf-pppext-eap-ttls-02.txt */,
    GSN_EAP_TYPE_AKA = 23 /* RFC 4187 */,
    GSN_EAP_TYPE_PEAP = 25 /* draft-josefsson-pppext-eap-tls-eap-06.txt */,
    GSN_EAP_TYPE_MSCHAPV2 = 26 /* draft-kamath-pppext-eap-mschapv2-00.txt */,
    GSN_EAP_TYPE_TLV = 33 /* draft-josefsson-pppext-eap-tls-eap-07.txt */,
    GSN_EAP_TYPE_FAST = 43 /* draft-cam-winget-eap-fast-05.txt */,
    GSN_EAP_TYPE_PAX = 46 /* draft-clancy-eap-pax-11.txt */,
    GSN_EAP_TYPE_PSK = 47 /* draft-bersani-eap-psk-11.txt */,
    GSN_EAP_TYPE_SAKE = 48 /* RFC 4763 */,
    GSN_EAP_TYPE_EXPANDED = 254 /* RFC 3748 */,
    GSN_EAP_TYPE_GPSK = 255 /* EXPERIMENTAL - type not yet allocated
                 * draft-ietf-emu-eap-gpsk-01.txt */
} GSN_EAP_TYPE_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief EAP FAST PAC structure.
 *      This structure defines the EAP FAST PAC structure.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_EAP_FAST_PAC
{
    UINT32 pacLen;
    UINT8* pPac;
} GSN_WDD_SEC_EAP_FAST_PAC_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Group Key update data structure.
 *      This structure defines structure for storing information to update
 * group key used in 2-way handshake.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_GKU_DATA
{
    UINT8 gkuData[32];
}GSN_WDD_SEC_GKU_DATA_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Security EAP FAST Configuration.
 *
 *     This structure defines the EAP-FAST configuration used for configuring
 *     the WDD for connecting to a WLAN with EAP-FAST key mgmt.
 * @see GSN_WDD_SECURITY_CONFIG_T and GSN_WDD_WLAN_CONFIG_T.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_EAP_CONFIG
{
    UINT8  						outerAuthType; 
	UINT8  						innerAuthType; 
    GSN_WDD_SEC_EAP_UNAME_T    	userName;
    GSN_WDD_SEC_EAP_PWD_T      	password;
    UINT8                      	eapFlags;//fastProvisioningStatus; renamed after rom
    GSN_WDD_SEC_EAP_FAST_PAC_T 	pac;
    UINT8                      	pacOverWrite;
    INT8	* 					pCaCert;
	UINT32 						caCertLen;
    INT8 *						pClientCert;
	UINT32						clientCertLen;
    INT8 *			 			pPrivateKey;
	UINT32						privateKeyLen;
} GSN_WDD_SEC_EAP_CONFIG_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief RF Bands used in WPS.
 *      This enum defines the RF band used.
 ******************************************************************************/
typedef enum GSN_WDD_WPS_RF
{
    GSN_WDD_WPS_RF_24GHZ,
    GSN_WDD_WPS_RF_50GHZ
}GSN_WDD_WPS_RF_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief Config Methods used in WPS.
 *      This enum defines the config Methods used in WPS
 ******************************************************************************/
typedef enum GSN_WDD_WPS_CONFIG_METHOD
{
    GSN_WDD_WPS_CONFIG_LABEL = 0x0004,
    GSN_WDD_WPS_CONFIG_DISPLAY = 0x0008,
    GSN_WDD_WPS_CONFIG_PUSHBUTTON = 0x0080,
    GSN_WDD_WPS_CONFIG_KEYPAD = 0x0100,
    GSN_WDD_WPS_CONFIG_VIRT_PUSHBUTTON = 0x0280
}GSN_WDD_WPS_CONFIG_METHOD_T;

/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WPAIF WPS configuration.
 *
 *     This structure defines the WPS configuration. All the pointers should be
 * NULL terminated.
 ******************************************************************************/
typedef struct GSN_WDD_SEC_WPS_CONFIG
{
    UINT8 pin[8]; /* If method used is PBC the pin shoule be all set to 0 */
    UINT8 *pDeviceName; /* String to identify the device */
    UINT8 *pManufacturer; /* String to identify the manufacturer */
    UINT8 *pModelName; /* String to identify the model name */
    UINT8 *pModelNumber; /* String to identify the model number */
    UINT8 *pSerialNumber; /* String to identify the serial number */
    GSN_WDD_WPS_RF_T  rfBands;
    UINT8 *pUuid;
    UINT8 *pFriendlyName; /* Friendly Name (required for UPnP) */
    UINT8 *pManufacturerUrl;/* Manufacturer URL (optional for UPnP) */
    UINT8 *pModelDescription;/* Model Description (recommended for UPnP) */
    UINT8 *pModelUrl; /* Model URL (optional for UPnP) */
    UINT8 *pUpc; /* Universal Product Code (optional for UPnP) */
    GSN_WDD_WPS_CONFIG_METHOD_T configMethods;
}GSN_WDD_SEC_WPS_CONFIG_T;



/**
 *******************************************************************************
 * @ingroup GsnSecurityDefs
 * @brief WLAN Security configuration.
 *     This structure defines the security configuration used by the Wireless
 *     Device Driver (WDD).
 *
 * \verbatim
 *
 * User can select one of the secutiy mode it wants to operate:
 *
 *  These values have the following significance:
 *
 *  GSN_WDD_SEC_MODE_DISABLE - Connects/Forms Network with open security.In
 *  this case user need not provide any of the other information in this
 *  structure.
 *
 *  GSN_WDD_SEC_MODE_ANY - Connects to any network security with the specified
 *  SSID and channel. For this user has to give all the information in this
 *  structure. Based on the security mode of the network, WDD will select
 *  appropriate configuration.
 *
 *  GSN_WDD_SEC_MODE_WEP - Connects/Forms Network with WEP security.In
 *  this case user need to provide WEP field information in this
 *  structure.
 *
 *  GSN_WDD_SEC_MODE_WPA_PERSONAL or GSN_WDD_SEC_MODE_WPA2_PERSONAL -
 *  Connects/Forms Network with WPS PSK security. In this case user need to
 *  provide PSK field information in this structure.
 *
 *  GSN_WDD_SEC_MODE_WPA_ENTERPRISE or GSN_WDD_SEC_MODE_WPA2_ENTERPRISE -
 *  Connects Network with WPS Enterprise security. In this case user need to
 *  provide EAP field information in this structure.
 *
 *
 * \endverbatim
 *
 * @see GSN_WDD_WLAN_CONFIG_T.
 ******************************************************************************/
typedef struct GSN_WDD_SECURITY_CONFIG
{
    GSN_WDD_SEC_MODE_T       mode;
    GSN_WDD_SEC_WEP_KEY_T    wepConfig;
    GSN_WDD_SEC_PSK_CONFIG_T pskConfig;
    GSN_WDD_SEC_EAP_CONFIG_T eapConfig;
    GSN_WDD_SEC_WPS_CONFIG_T wpsConfig;
} GSN_WDD_SECURITY_CONFIG_T;




typedef struct GSN_WDD_STA_CONCTED_INFO
{
	GSN_WLAN_MAC_ADDR_T staAddr; /**< connecting STA addr, valid in AP mode */	 
	UINT8 macFrameLen;
    UINT8 macFrame[GSN_WLAN_MAC_MAX_FRAME_LEN];
}GSN_WDD_STA_CONCTED_INFO_T;
#endif /* _GSN_WDD_SECURITY_H_ */

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

