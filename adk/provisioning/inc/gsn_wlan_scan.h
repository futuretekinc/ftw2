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
* $RCSfile: gsn_wlan_scan.h,v
*/

#ifndef GSN_WLAN_SCAN_H_
#define GSN_WLAN_SCAN_H_

/**
 *******************************************************************************
 * @file gsn_wlan_scan.h
 * @brief GSN WLAN Scan
 *    This file contains declarations of Functions API for performing scan.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max Length of the SSID filter
 *****************************************************************************/
#define SSID_FILTER_SIZE 32

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of WLAN "No Security" string
 *****************************************************************************/
#define GSN_WLAN_SECURITY_NONE_STR "none"
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of WLAN WEP security method string
 *****************************************************************************/
#define GSN_WLAN_WEP_STR "wep"
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of WLAN WPA Personal security method string
 *****************************************************************************/
#define GSN_WLAN_WPA_PERSONAL_STR "wpa-personal"
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of WLAN WPA Enterprise security method string
 *****************************************************************************/
#define GSN_WLAN_WPA_ENTERPRISE_STR "wpa-enterprise"

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Scan time on channel (dwell time) in milliseconds
 *****************************************************************************/
#define GSN_WLAN_SCAN_DWELL_TIME 150

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Delay between switching channels (quiet time) in milliseconds
 *****************************************************************************/
#define GSN_WLAN_SCAN_DELAY_TIME 150

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of Regulatory domains
 *****************************************************************************/
typedef enum GSN_WLAN_REG_DOMAIN
{
    GSN_WLAN_REG_DOMAIN_FCC   =   0,
    GSN_WLAN_REG_DOMAIN_ETSI ,
    GSN_WLAN_REG_DOMAIN_TELEC,
    GSN_WLAN_REG_DOMAIN_ETSI_MEXS,
    GSN_WLAN_REG_DOMAIN_UNKNOWN
} GSN_WLAN_REG_DOMAIN_T;


/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Maximum number of channels specified by FCC
 *****************************************************************************/
#define GSN_WLAN_REG_DOMAIN_FCC_MAX_CH  11
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Maximum number of channels specified by ETSI
 *****************************************************************************/
#define GSN_WLAN_REG_DOMAIN_ETSI_MAX_CH  13
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Maximum number of channels specified by TELEC
 *****************************************************************************/
#define GSN_WLAN_REG_DOMAIN_TELEC_MAX_CH  14

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Maximum number of frequency bands supported
 *****************************************************************************/
#ifdef   GS1500M
#ifdef   GS1550M
#define  GSN_WLAN_SCAN_MAX_BAND   2  /* 2.4Ghz and 5Ghz band */
#else
#define  GSN_WLAN_SCAN_MAX_BAND   1  /* Only 2.4Ghz band  */
#endif   /* GS1550M */
#endif   /* GS1500M */
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Maximum number of channels when no regulatory domain is specified
 *****************************************************************************/
#define GSN_WLAN_REG_DOMAIN_UNKNOWN_MAX_CH  14

#define GSN_WLAN_REG_DOMAIN_FCC_STR  "fcc"
#define GSN_WLAN_REG_DOMAIN_ETSI_STR  "etsi"
#define GSN_WLAN_REG_DOMAIN_ETSI_MEXS_STR  "etsi_mex"
#define GSN_WLAN_REG_DOMAIN_TELEC_STR  "telec"
#define GSN_WLAN_REG_DOMAIN_UNKNOWN_STR  "unknown"

#define GSN_WLAN_2_4_GHZ_BAND "2.4GHz"
#define GSN_WLAN_5_GHZ_BAND "5GHz"

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of security types supported
 ******************************************************************************/
typedef enum
{
    GSN_WLAN_SECURITY_NONE = 1,
    GSN_WLAN_WEP,
    GSN_WLAN_WPA_PERSONAL,
    GSN_WLAN_WPA_ENTERPRISE
} GSN_WLAN_SECURITY_TYPE_T;

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of structure controlling scan
 ******************************************************************************/
typedef struct GSN_WLAN_SCAN_PARAM
{
    UINT8   channel;          /**< channel number to scan. 0 for all channels */
    INT8    ssidFilter[SSID_FILTER_SIZE];    /**< ssid to scan for. (NOT USED)*/
    UINT8   nwType;         /**< nw type - BSS / IBSS (NOT USED) */
    UINT32  scanTime;  /**< Duration to dwell on a channel while scanning */
    UINT32  scanDelay;  /**< Duration to wait before proceeding to next channel*/
    GSN_WLAN_SECURITY_TYPE_T   securityType;  /**< Security type (NOT USED) */
    GSN_WLAN_REG_DOMAIN_T   domain; /**< Regulatory domain */
}GSN_WLAN_SCAN_PARAM_T;

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of structure describing scan results
 ******************************************************************************/
typedef struct GSN_SCAN_RESULT
{
    GSN_MAC_ADDR_T  apMacAddr; /**< Mac Address */
    UINT8   rssi;               /**< rssi */
    UINT8   channel;          /**< channel number */
    GSN_MAC_SSID_T ssid;    /**< ssid */
    UINT8   nwType;         /**< nw type - BSS / IBSS */
    GSN_WLAN_SECURITY_TYPE_T securityType;
}GSN_WLAN_SCAN_RESULT_T;

/**
 ******************************************************************
 * @ingroup GsnWlanScan_ChannelFill
 * @brief To fill valid channel numbers depending on current reg domain and PHY mode
 *   This function shall be called during scan or connect
 *  @param chTable :  Pointer to array to hold the valid channel numbers
 *  @param domain  :  Regulatory domain
 *  @param phyMode : PHY mode. If ZERO passed then currently configured phymode used
 *  @retval none.
 *  Important Note: chTable[] array size must be GSN_WDD_WLAN_MAX_CHNLS+1
 ******************************************************************/
PUBLIC VOID
GsnWlanScan_ChannelFill(UINT8 *chTable,UINT8 domain,UINT8 phyMode);


/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Scan for Networks
 *    This function scans the configured channels for networks
 *    configuration parameter provided
 * @param sParams - IN Pointer to Scan Parameters structure
 * @param pScanResult - OUT Pointer to Scan Results structure
 * @param maxScanElements - IN/OUT Pointer to number of elements in scan results
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnWlanScan_ProvWscan( GSN_WLAN_SCAN_PARAM_T *sParams,GSN_WLAN_SCAN_RESULT_T *pScanResult, INT32 *maxScanElements);

#endif /* GSN_WLAN_SCAN_H_ */
