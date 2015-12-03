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
* $RCSfile: gsn_wpaif.h,v $
*
* Description : This file contains the interfacing APIs and declaration that is
* used to interface with the WPA open source code.
*******************************************************************************/
#ifndef _GSN_WPAIF_H_
#define _GSN_WPAIF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/common/defs.h"
#include "supplicant/common/wpa_common.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/rsn_supp/pmksa_cache.h"
#include "security/hw_engine_if/gsn_hw_engine_if.h"

/**
 *****************************************************************************
 * @ingroup supplicantdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWpaIf GSN WPA Interface
 *****************************************************************************/
	
	
/**
 *****************************************************************************
 * 
 * @}
 *****************************************************************************/


/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF mode.
 *     This enum defines the WPAIF operation mode. This mode specifies the Wi-Fi
 * operating mode.
 *******************************************************************************/
typedef enum GSN_WPAIF_MODE
{
    GSN_WPAIF_MODE_INFRA,
    GSN_WPAIF_MODE_IBSS,
    GSN_WPAIF_MODE_AP,
    /* If the node comes out of standby and it is connected then the WPA IF is 
	initialized with GSN_WPAIF_MODE_INFRA_RESTORE mode to restore the WPA IF
	context. For this grpInfo field hsa to be filled in GSN_WPAIF_SPECFIC_CFG_T.
	User can get grpInfo by calling GsnWpaSuppIf_CfgGet with GSN_WPAIF_OPT_PTK
	before going to standby */
    GSN_WPAIF_MODE_INFRA_RESTORE 
}GSN_WPAIF_MODE_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Passphrase configuration.
 *
 *     This structure defines the WPAIF passphrase configuration. It stores the 
 * length of the passphrase and the pointer to the passphrase. It is assumbed 
 * that	the passphrase pointer will persist the value. WPAIF stores the pointer
 * to reduce the memory requirement.
 ******************************************************************************/
typedef struct GSN_WPAIF_PASSPHRASE
{
    UINT8	length;
    UINT8   *pPs;
}GSN_WPAIF_PASSPHRASE_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF PSK configuration.
 *
 *     This structure defines the WPAIF PSK configuration. It stores either the 
 * passphrase configuration or the pointer to the PMK. User can provide the PMK
 * if it is already calculated to save on the time required to re-calculate it 
 * again. The PMK filed is a pointer and it is assumed that it will persist the 
 * value. WPAIF stores the pointer to reduce the memory requirement.
 ******************************************************************************/
typedef struct GSN_WPAIF_PSK_CFG
{
    GSN_WDD_SEC_PSK_CONFIG_T *pPskCfg;
}GSN_WPAIF_PSK_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF EAP User name configuration.
 *
 *     This structure defines the WPAIF EAP user name configuration. It stores 
 * the length of the user name and the pointer to the user name. 
 * WPAIF stores the pointer to reduce the memory requirement.
 ******************************************************************************/
typedef GSN_WDD_SEC_EAP_UNAME_T GSN_WPAIF_EAP_USER_NAME_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF EAP password configuration.
 *
 *     This structure defines the WPAIF EAP password configuration. It stores 
 * the length of the password and the pointer to the password. 
 * WPAIF stores the pointer to reduce the memory requirement.
 ******************************************************************************/
typedef GSN_WDD_SEC_EAP_PWD_T GSN_WPAIF_EAP_PWD_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF EAP Certificate configuration.
 *
 *     This structure defines the WPAIF EAP certificate configuration. It stores 
 * the length of the certificate and the pointer to the certificate. 
 * WPAIF stores the pointer to reduce the memory requirement.
 ******************************************************************************/
typedef struct GSN_WPAIF_CERT
{
    UINT16 length;
    UINT8 *pCert;
} GSN_WPAIF_CERT_T;

typedef struct GSN_WPAIF_WPS_PRI_DEV
{
    UINT16 catagory;
    UINT16 subCatagory;
}GSN_WPAIF_WPS_PRI_DEV_T;
/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF WPS configuration.
 *
 *     This structure defines the WPAIF WPS configuration. All the pointers 
 * should be NULL terminated.
 ******************************************************************************/
typedef struct GSN_WPAIF_WPS_CFG
{
    UINT8 *pPin;
    UINT8 *pDeviceName;
    UINT8 *pManufacturer;
    UINT8 *pModelName;
    UINT8 *pModelNumber;
    UINT8 *pSerialNumber;
    GSN_WPAIF_WPS_PRI_DEV_T priDevType;
    UINT32 osVersion;
    UINT8  rfBands;
    UINT8 *pUuid;	
    UINT8 *pFriendlyName; /* Friendly Name (required for UPnP) */	
    UINT8 *pManufacturerUrl;/* Manufacturer URL (optional for UPnP) */
    UINT8 *pModelDescription;/* Model Description (recommended for UPnP) */
    UINT8 *pModelUrl; /* Model URL (optional for UPnP) */
    UINT8 *pUpc; /* Universal Product Code (optional for UPnP) */
    UINT16 configMethods;
    UINT8 *channelList; /* List of channel to scan */
	UINT8 chnlIndx;
}GSN_WPAIF_WPS_CFG_T;
/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF EAP configuration.
 *
 *     This structure defines the WPAIF EAP configuration.
 ******************************************************************************/
typedef struct GSN_WPAIF_EAP_CFG
{
    EapType  eapType; 
    EapType  phase2;
    GSN_WPAIF_EAP_USER_NAME_T  *pUserName;
    GSN_WPAIF_EAP_PWD_T  *pPwd;
    UINT8  eapFlags;//fastProvisioningStatus; //- renamed after rom
    GSN_WDD_SEC_EAP_FAST_PAC_T    pac;
    UINT8  pacOverWrite;
    GSN_WPAIF_CERT_T caCert;
    GSN_WPAIF_CERT_T clientCert;
    GSN_WPAIF_CERT_T privateKey;
} GSN_WPAIF_EAP_CFG_T;

#define GSN_WPAIF_WPS_USE_DFLT_PIN 1

#define GSN_WPAIF_EAP_FLAG_FAST_PROV                (1 << 0)
#define GSN_WPAIF_EAP_FLAG_NO_TIME_STAMP_CHECK      (1 << 1)


/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF WPA basic configuration.
 *
 *     This structure defines the WPAIF basic configuration.
 ******************************************************************************/

typedef struct GSN_WPAIF_BASIC_CFG
{
    UINT32 proto;
    UINT32 pairwiseCipher;
    UINT32 groupCipher;
    UINT32 keyMgmt;
    UINT32 capabilities;
    size_t numPmkid;
    UINT8  *pPmkid;
    UINT32 mgmtGroupCipher;

    GSN_WLAN_MAC_SSID_T  *pSsid;
	GSN_WLAN_MAC_ADDR_T  *pBssid;
}GSN_WPAIF_BASIC_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF specific configuration.
 *
 *     This structure defines the WPAIF specific configuration, based on the security selected.
 ******************************************************************************/
typedef union GSN_WPAIF_SPECFIC_CFG
{
    GSN_WPAIF_PSK_CFG_T pskCfg;
    GSN_WPAIF_EAP_CFG_T eapCfg; 
    GSN_WPAIF_WPS_CFG_T wpsCfg;
    UINT8 grpInfo[32];
}GSN_WPAIF_SPECFIC_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF WPA configuration.
 *
 *     This structure defines the WPAIF WPA configuration.
 ******************************************************************************/
typedef struct GSN_WPAIF_CFG
{
    GSN_WPAIF_BASIC_CFG_T    basic;
    GSN_WPAIF_SPECFIC_CFG_T cfg;
}GSN_WPAIF_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF configuration options.
 *
 *     This enum defines the WPAIF configuration options.
 ******************************************************************************/
typedef enum GSN_WPAIF_CFG_OPT
{
    GSN_WPAIF_OPT_SSID_PTR, /* Set/Get SSID of the AP to join */
#if 0
    GSN_WPAIF_OPT_PASSPHRASE, /* Set/Get passphrase */
    GSN_WPAIF_OPT_PMK, /* Set/Get PTK (derived from the passphrase and ssid) */
#endif

    GSN_WPAIF_OPT_PTK, /* Set/Get PTK (derived from the 4-way handshake) */
    GSN_WPAIF_OPT_PMKID, /* Set/Get PMKID using this option */
    GSN_WPAIF_OPT_STATE, /* Set/Get WPA state, after standby we can set to authenticates state */
    GSN_WPAIF_OPT_PSK_CFG,
    GSN_WPAIF_OPT_WPS_CFG, 
    GSN_WPAIF_OPT_EAP_CFG,
    GSN_WPAIF_OPT_PAC, /* Set/Get PAC using this option */
    GSN_WPAIF_OPT_WPS_CRED_GET,
    GSN_WPAIF_OPT_PMK_CACHE_ENTRY,
    GSN_WPAIF_OPT_PMK_CACHE_CURRENT,
    GSN_WPAIF_OPT_WPS_CERTIFICATION,
    GSN_WPAIF_OPT_PAC_LEN
}GSN_WPAIF_CFG_OPT_T;

typedef struct rsn_pmksa_cache_entry    GSN_WPAIF_PMK_CACHE_ENTRY;

#define PMK_CACHE_ENTRY_SIZE  sizeof(GSN_WPAIF_PMK_CACHE_ENTRY)

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Events.
 *
 *     This enum defines the WPAIF events.
 ******************************************************************************/
typedef enum GSN_WPAIF_EVENT
{
    GSN_WPAIF_EVENT_CONNECT_IND, /* Event to indicte L2 level connection is up */

    GSN_WPAIF_EVENT_DISCONNECT_IND, /* Event to indicate, node is disconnected from Network  */
    GSN_WPAIF_EVENT_STA_CONNECTE_IND, /* Event to indicate a STA has joined to the node */
    GSN_WPAIF_EVENT_STA_DISCONNECT_IND, /* Event to indicate a STA has left to the node */	
    GSN_WPAIF_EVENT_EAPOL_RECEIVE_IND, /* Event to indicate an EAPOL frame is received */
}GSN_WPAIF_EVENT_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF EAP Phase2.
 *
 *     This enum defines the Phase 2 authentication in EAP security.
 ******************************************************************************/
enum 
{
    GSN_WPAIF_EAP_CHAP = 250,
    GSN_WPAIF_EAP_MSCHAP = 251,
    GSN_WPAIF_EAP_EAP = 252,
    GSN_WPAIF_EAP_PAP = 253,
};

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Timer notification callback type.
 *
 *     This function type defination defines the WPAIF timer notification
 * callback type.
 ******************************************************************************/
typedef VOID (*GSN_WPAIF_TMR_NITIF_CB_T)( VOID* pCtx);

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Initialize WPA module.
 *    This API initializes the WPA module. To initialize each WPA IF user has 
 * to call GsnWpaIf_Init. This API has to be called only once before calling
 * any of the WPA IF APIs. This API takes a callback pointer which is called
 * when a timer expire event happens. User can post a message to appropriate
 * thread to give an execution context to handle the expire event. To handle 
 * the expire event the user has to call GsnWpaTmrIf_Handler API. 
 * GsnWpaTmrIf_Handler handles time out events for all the interface.
 * @param cb - IN Pointer to the callback function, that has to be called when
 *             WPA timer expire event happens.
 * @param pCtx - IN context to be passed in the cb.
 * @param seed - IN seed
 *******************************************************************************/
PUBLIC VOID
GsnWpa_Init( GSN_WPAIF_TMR_NITIF_CB_T cb, void *pCtx,
    UINT32 seed[TRNG_NONCE_SIZE_WORDS] );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Timer handler API.
 *    API to handle timeout event. This is provided in order to execute the 
 * timeout activity in a thread context to avoid executing it in timer thread 
 * context. 
 *
 *******************************************************************************/
PUBLIC VOID 
GsnWpaTmrIf_Handler( VOID );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Initialize the WPAIF.
 *
 *    This function is called to initialize the WPAIF module. This API has to be
 * called before calling any other APIs of WPAIF. This API is called once the 
 * user has decided to join/create a network. At this point user will have the 
 * basic and the specific configuration of the network. 
 * To derive the basic configuration from the scan response user can call 
 * GsnWpaIf_ExtractCfg API provided. User has to fill the pSsid in the basic
 * configuration.
 *	   In case of WPS connection, the user has to set the "proto" to 
 * "WPA_PROTO_WPS" (defined in defs.h) and has to provide the WPS configuration 
 * in pSpecCfg to initiate WPS joining procedure.
 *     If the node is already connected to a network and decides to join 
 * another network, it can disconnect and then again call this API. To change 
 * the mode, say from IBSS to INFRA or to AP mode it has to call 
 * GsnWpaIf_Deinit and then call GsnWpaIf_Init.
 *
 * @param mode - IN WiFi operation mode.
 * @param pDrvIf - IN Pointer to the WiFi driver interface (WDD).
 * @param pCfg - IN Pointer to basic configuration. This API copies the content 
 *				 of this pointer to its context memory.
 * @param pSpecCfg - IN Pointer to the specific configuration. This field is used
 *                   if user wants to provide WPA, EAP or WPS configuartion. In
 *                   case of WPS, this field is mandatory. Based on the value
 *                   given in proto element of basic configuration, the special
 *                   configuration is interpreted. If this field is not set in 
 *                   this API, then user has to provide this information by 
 *                   calling GsnWpaIf_CfgSet API.
 *******************************************************************************/
PUBLIC VOID* 
GsnWpaIf_Init( GSN_WPAIF_MODE_T mode, VOID *pDrvIf, GSN_WPAIF_BASIC_CFG_T *pCfg, 
	GSN_WPAIF_SPECFIC_CFG_T *pSpecCfg );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief De-initialize the WPAIF.
 *
 * @param pWpaIf - IN Pointer to the WPAIF context, returned in GsnWpaIf_Init 
 * call API.
 *******************************************************************************/
PUBLIC GSN_STATUS 
GsnWpaIf_Deinit( VOID *pWpaIf );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Callback function to notify WPAIF.
 *
 * @param pCtx - IN Pointer to the WPAIF context, returned in GsnWpaIf_Init 
 * call API.
 * @param event - IN event to notify 
 * @param pData - IN Pointer to the data.
 * @param length - IN length of the data. 
 *******************************************************************************/
PUBLIC GSN_STATUS 
GsnWpaIf_Notif( void *pCtx, GSN_WPAIF_EVENT_T event, UINT8 *pData, UINT32 length );


/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF configuration get API.
 *
 * @param pWpaIf - IN Pointer to the WPAIF context, returned in GsnWpaIf_Init 
 * call API.
 * @param cfgOpt - IN Configuration option 
 * @param pData - IN Pointer to the data.
 * @param pLen - IN/OUT Pointer to length of the data. 
 *******************************************************************************/
PUBLIC GSN_STATUS 
GsnWpaIf_CfgGet( void *pWpaIf, GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData, 
               UINT32* pLen );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF configuration set API.
 *
 * @param pWpaIf - IN Pointer to the WPAIF context, returned in GsnWpaIf_Init 
 * call API.
 * @param cfgOpt - IN Configuration option 
 * @param pData - IN Pointer to the data.
 * @param length - IN length of the data. 
 *******************************************************************************/
PUBLIC GSN_STATUS 
GsnWpaIf_CfgSet( void *pWpaIf,  GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData, 
               UINT32 length );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF configuration extract API.
 *    API to extract the basic configuration from the probe response or beacon
 * frame
 * @param framePtr - IN Pointer to the frame.
 * @param frameLen - IN Size of the frame 
 * @param pCfg - OUT Pointer to store the basic configuration.
 * @param pIE - OUT Pointer to store the IE
 * @param pIElen - OUT length of the IE
 *******************************************************************************/
PUBLIC GSN_STATUS
GsnWpaIf_ExtractCfg( GSN_MAC_FRAME_T* framePtr, UINT16 frameLen,
    						GSN_WPAIF_BASIC_CFG_T *pCfg, INT8 *pIE, INT8 *pIElen );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Data receive notification API.
 *    This API notify the WPAIF of data receive. This API copies the data frame
 * and queues the packet to process it later.
 * @param dataLen - IN Size of the frame 
 *******************************************************************************/
INLINE PUBLIC UINT8*
GsnWpaIf_GetBuff( UINT32 dataLen )
{
    return os_malloc( dataLen );
}


#ifdef __cplusplus
}
#endif
#endif /*  _GSN_WPAIF_H_ */
