/******************************************************************************
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
* $RCSfile: app_ncm_config.h,v $
*
* Description : This file contains public definitions for inital board specific
*     configuration.
*****************************************************************************/
#ifndef _APP_NCM_CONFIG_H_
#define _APP_NCM_CONFIG_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
/**
 *****************************************************************************
 * @file app_ncm_config.h
 * @brief App NCM configuration public header.
 *    This file contains the public definition for App NCM configuration.
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup AppNCMConfig board specific configuration definitions.
 *    This group contains NCM specific configuration definitions.
 *****************************************************************************/

/**
 ******************************************************************************
 * @ingroup AppNCMConfig
 * @brief MAC address.
 *     device MAC address.
 ****************************************************************************/
#define APP_CFG_DFLT_WIFI_MAC_ADDRESS   \
    { 0x00, 0x1D, 0xC9, 0x01, 0x99, 0x99 }
#ifdef GS1500M
#define S2W_APP_VERSION 0x03030500
#else
#define S2W_APP_VERSION 0x02030500
#endif
#define APP_NCM_CFG_DFLT_NODE_HOST_NAME "GainSpan"
/**
******************************************************************************
* @ingroup AppNCMConfig
* @brief UART config for SDD.
****************************************************************************/
#define APP_NCM_CFG_DFLT_UART_PORT              GSN_UART_0
#define APP_NCM_CFG_DFLT_UART_BAUD_RATE         GSN_UART_BAUDRATE_115K2
#define APP_NCM_CFG_DFLT_UART_CHAR_FORMAT       GSN_UART_CHARFORMAT_8
#define APP_NCM_CFG_DFLT_UART_STOP_BITS         GSN_UART_STOPBITS_1
#define APP_NCM_CFG_DFLT_UART_PARITY            GSN_UART_PARITYBIT_NONE
#define APP_NCM_CFG_DFLT_UART_HW_FLOW_SUPPORT   GSN_UART_HW_NO_SUPPORT

#define APP_NCM_CFG_DFLT_FAST_PROVISIONING_STATUS 1
#define APP_NCM_CFG_DFLT_FLASH_PAC_OVER_WRITE 1



#if defined(GSN_SECURITY_ENTERPRISE_FAST_MSCHAPV2_AVAILABLE) || defined(GSN_SECURITY_ENTERPRISE_FAST_GTC_AVAILABLE)
#define APP_NCM_CFG_DFLT_OUTER_AUTHENTICATION_TYPE GSN_EAP_TYPE_FAST
#else

#ifdef GSN_SECURITY_ENTERPRISE_TTLS_AVAILABLE
    #define APP_NCM_CFG_DFLT_OUTER_AUTHENTICATION_TYPE GSN_EAP_TYPE_TTLS
#else

#if defined(GSN_SECURITY_ENTERPRISE_PEAP_V0_AVAILABLE)|| defined(GSN_SECURITY_ENTERPRISE_PEAP_V1_AVAILABLE)
    #define APP_NCM_CFG_DFLT_OUTER_AUTHENTICATION_TYPE GSN_EAP_TYPE_PEAP
#else
    #define APP_NCM_CFG_DFLT_OUTER_AUTHENTICATION_TYPE GSN_EAP_TYPE_TLS
#endif
#endif
#endif

#if defined(GSN_SECURITY_ENTERPRISE_FAST_MSCHAPV2_AVAILABLE) || defined(GSN_SECURITY_ENTERPRISE_PEAP_V0_AVAILABLE)|| defined(GSN_SECURITY_ENTERPRISE_TTLS_AVAILABLE)

   #define APP_NCM_CFG_DFLT_INNER_AUTHENTICATION_TYPE GSN_EAP_TYPE_MSCHAPV2
#else

#if defined(GSN_SECURITY_ENTERPRISE_FAST_GTC_AVAILABLE)|| defined(GSN_SECURITY_ENTERPRISE_PEAP_V1_AVAILABLE)

    #define APP_NCM_CFG_DFLT_INNER_AUTHENTICATION_TYPE GSN_EAP_TYPE_GTC
#else

    #define APP_NCM_CFG_DFLT_INNER_AUTHENTICATION_TYPE GSN_EAP_TYPE_MSCHAPV2

#endif
#endif

/**
  ******************************************************************************
  * @ingroup AppNCMConfig
  * @brief defaulr fwup settings.
  *     Indicates default fwup settings.
  ****************************************************************************/
 #define APP_CFG_DFLT_FWUP_SERVER_IP    { 192, 168, 37, 200}
 #define APP_CFG_DFLT_FWUP_SERVER_PORT  8355
 #define APP_CFG_DFLT_FWUP_SOURCE_PORT  80
 #define APP_CFG_DFLT_FWUP_RETRY        10


/*****************************************************************************
  * Type Definitions
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup AppNCMConfig
 * @brief Enum for Battery check  coinfiguration Ids.
 *    This enum defines the configuration IDs for battery check.
 *****************************************************************************/
typedef enum APP_NCM_CFG_ID_T
{
    /**< MAC address setting CFG IDs */
    APP_CFG_MAC_ADDR_ID,
    APP_CFG_FWUP_SERVER_IP_ID,
    APP_CFG_FWUP_SERVER_PORT_ID,
    APP_CFG_FWUP_SOURCE_PORT_ID,
    APP_CFG_FWUP_RETRY_ID,

    APP_CFG_REG_DOMAIN_ID,
    APP_NCM_CFG_ARP_TBL_ID,
#ifdef GSN_P2P
    APP_CNFG_P2P_CONFIG_ID,
#endif
//    APP_CFG_AP_GROUP_ID,
    
    /**< L2 setting CFG IDs for WIFI. There are 4 L2 profiles for normal
    joining procedure and one L2 profile for the provisioning mode */
    APP_NCM_CFG_SSID_ESS1_ID,
    APP_NCM_CFG_SSID_ESS2_ID,
    APP_NCM_CFG_SSID_ESS3_ID,
    APP_NCM_CFG_SSID_IBSS_ID,
    APP_NCM_CFG_SSID_PROV_ID,

    APP_NCM_CFG_CHANNEL_ESS1_ID,
    APP_NCM_CFG_CHANNEL_ESS2_ID,
    APP_NCM_CFG_CHANNEL_ESS3_ID,
    APP_NCM_CFG_CHANNEL_IBSS_ID,
    APP_NCM_CFG_CHANNEL_PROV_ID,

    APP_NCM_CFG_SEC_ENC_MODE_ESS1_ID,
    APP_NCM_CFG_SEC_ENC_MODE_ESS2_ID,
    APP_NCM_CFG_SEC_ENC_MODE_ESS3_ID,
    APP_NCM_CFG_SEC_TYPE_IBSS_ID,
    APP_NCM_CFG_SEC_ENC_MODE_PROV_ID,

    APP_NCM_CFG_AUTH_MODE_ESS1_ID,
    APP_NCM_CFG_AUTH_MODE_ESS2_ID,
    APP_NCM_CFG_AUTH_MODE_ESS3_ID,
    APP_NCM_CFG_AUTH_MODE_IBSS_ID,
    APP_NCM_CFG_AUTH_MODE_PROV_ID,

    APP_NCM_CFG_WEP_KEY_ID_ESS1_ID,
    APP_NCM_CFG_WEP_KEY_ID_ESS2_ID,
    APP_NCM_CFG_WEP_KEY_ID_ESS3_ID,
    APP_NCM_CFG_WEP_KEY_ID_IBSS_ID,
    APP_NCM_CFG_WEP_KEY_ID_PROV_ID,

    APP_NCM_CFG_WEP_KEY_LEN_ESS1_ID,
    APP_NCM_CFG_WEP_KEY_LEN_ESS2_ID,
    APP_NCM_CFG_WEP_KEY_LEN_ESS3_ID,
    APP_NCM_CFG_WEP_KEY_LEN_IBSS_ID,
    APP_NCM_CFG_WEP_KEY_LEN_PROV_ID,

    APP_NCM_CFG_WEP_KEY_ESS1_ID,
    APP_NCM_CFG_WEP_KEY_ESS2_ID,
    APP_NCM_CFG_WEP_KEY_ESS3_ID,
    APP_NCM_CFG_WEP_KEY_IBSS_ID,
    APP_NCM_CFG_WEP_KEY_PROV_ID,

    APP_NCM_CFG_PASSPHARASE_ESS1_ID,
    APP_NCM_CFG_PASSPHARASE_ESS2_ID,
    APP_NCM_CFG_PASSPHARASE_ESS3_ID,

    APP_NCM_CFG_PSK_VALID_ESS1_ID,
    APP_NCM_CFG_PSK_VALID_ESS2_ID,
    APP_NCM_CFG_PSK_VALID_ESS3_ID,


    APP_NCM_CFG_PSK_KEY_ESS1_ID,
    APP_NCM_CFG_PSK_KEY_ESS2_ID,
    APP_NCM_CFG_PSK_KEY_ESS3_ID,

    APP_NCM_CFG_EPOL_VERSION_ID,
    APP_NCM_CFG_OUTER_AUTH_TYPE_ID,
    APP_NCM_CFG_INNER_AUTH_TYPE_ID,
    APP_NCM_CFG_USER_NAME_ID,
    APP_NCM_CFG_PASSWORD_ID,
    APP_NCM_CFG_FAST_REAUTH_STATUS_ID,
    APP_NCM_CFG_FAST_PROVISIONING_STATUS_ID,
    APP_NCM_CFG_FAST_PAC_ID,
    APP_NCM_CFG_FLASH_PAC_OVERWRITE_ID,

    /**< L2 setting CFG IDs for SDD, runs over UART using HI frame-format */
    APP_NCM_CFG_UART_PORT_ID,
    APP_NCM_CFG_UART_BAUD_RATE_ID,
    APP_NCM_CFG_UART_CHAR_FORMAT_ID,
    APP_NCM_CFG_UART_STOP_BITS_ID,
    APP_NCM_CFG_UART_PARITY_ID,
    APP_NCM_CFG_UART_HW_FLOW_SUPPORT_ID,

    /**< L3 setting CFG IDs. There is one L3 profiles for normal procedure
    and one L3 profile for the provisioning mode */
    APP_NCM_CFG_STATIC_IP_FLAG_ID,
    APP_NCM_CFG_STATIC_IP_FLAG_PROV_ID,
    APP_NCM_CFG_IP_ID,
    APP_NCM_CFG_IP_PROV_ID,
    APP_NCM_CFG_SUBNET_MASK_ID,
    APP_NCM_CFG_SUBNET_MASK_PROV_ID,
    APP_NCM_CFG_GATEWAY_ID,
    APP_NCM_CFG_GATEWAY_PROV_ID,
    APP_NCM_CFG_MAX_ID
}APP_NCM_CFG_ID_T;



#define S2W_FACTORY_DEFAULT_FALSH_ADDR (UINT8 *)((GSN_FLASH1_BASE_ADDRESS + ( 122 * 1024 )))
typedef struct APP_FACTORY_DEFAULT
{
    UINT8      chksum;
    UINT8    Length;
    UINT8      Macaddr[6];

}APP_FACTORY_DEFAULT_T;

typedef enum APP_FACTORY_DEFAULT_ID_T
{
    FACTORY_DEFAULT_CHKSUM_ID,
    FACTORY_DEFAULT_LEN_ID,
    FACTORY_DEFAULT_MAC_ID,
    FACTORY_DEFAULT_MAX_ID

}APP_FACTORY_DEFAULT_ID_T;


/**
 *****************************************************************************
 * @ingroup AppNcmConfig
 * @brief MAC address group structure
 *    This structure defines MAC address CFG group structure.
 *****************************************************************************/
typedef struct APP_CFG_MAC_ADDR_GROUP
{
    UINT8             wifiMacAddr[ 6 ];
    UINT32            :0;
} APP_CFG_MAC_ADDR_GROUP_T;
/**
 ******************************************************************************
 * @ingroup AppNCMConfig
 * @brief Get Battery check configuration.
 *    This function gives the battery check configuration for the requested
 *    configuration Id.
 * @param id - IN ID of the ocnfiguration.
 * @param pVal - OUT Pointer where the value has to be written.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE. Failure
 *    happens, if id is incorrect or the flash write fails.
 ******************************************************************************/
PUBLIC GSN_STATUS
AppCfg_Get( APP_NCM_CFG_ID_T id, VOID *pVal );

/**
 ******************************************************************************
 * @ingroup AppNCMConfig
 * @brief Set Battery check configuration.
 *    This function sets the battery check configuration for the requested
 *    configuration Id.
 * @param id - IN ID of the ocnfiguration.
 * @param pVal - IN Pointer where the configuration value is written.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE. Failure
 *    happens, if id is incorrect or the flash write fails.
 ******************************************************************************/
PUBLIC GSN_STATUS
AppCfg_Set( APP_NCM_CFG_ID_T id, VOID *pVal );

/**
 ******************************************************************************
 * @ingroup AppNCMConfig
 * @brief Initializes the Battery check configuration.
 *    This function initailizes the battery check configuration to the set
 *    default value.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE.
 ******************************************************************************/
PUBLIC GSN_STATUS
AppCfg_Init( BOOL grpInit );

#ifdef __cplusplus
}
#endif
#endif /* _APP_NCM_CONFIG_H_ */

/*****************************************************************************/


