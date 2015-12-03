/******************************************************************************
*
*               COPYRIGHT (c) 20012-2014 GainSpan Corporation
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
* $RCSfile: gsn_wlan_defs.h,v $
*
* Description : This file contains WLAN definitions.
******************************************************************************/
#ifndef _GSN_WLAN_DEFS_H_
#define _GSN_WLAN_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wlan_defs.h
 * @brief GSN WLAN definitions public header.
 * 
 *    This file contains the public WLAN MAC definitions.
 *****************************************************************************/
/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnWif GSN WLAN Firmware Interface (WIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *	  
 *		Whole GsnWif module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}	END of coresvcdoc.
 *****************************************************************************/
	


/**
 *****************************************************************************
 * @ingroup GsnWif
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWlanDefs GSN WLAN Definitions
 *    This group contains WLAN definitions.
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/	
/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief default value of the length of a MAC address.
 *
 *****************************************************************************/
#define GSN_WLAN_MAC_ADDR_LEN       6


/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief SSID length options (broadcast or standard).
 * @{
 *****************************************************************************/
#define GSN_WLAN_MAC_BROADCAST_SSID_LEN     0
#define GSN_WLAN_MAC_SSID_LEN              32


/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief Maximum number of channels.
 *
 *****************************************************************************/
#define GSN_WLAN_MAC_MAX_CHNLS          14

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief Max MAC frame length.
 *
 *****************************************************************************/
#define GSN_WLAN_MAC_MAX_FRAME_LEN          512

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief MCS supported.
 *
 *****************************************************************************/
#define GSN_WLAN_MAX_MCS_SUPPORTED      7

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief enum definig the scan types.
 *
 *****************************************************************************/
typedef enum GSN_WLAN_MAC_SCAN_TYPE
{
    GSN_WLAN_MAC_SCAN_TYPE_PASSIVE = 0,      /**< passive scan */
    GSN_WLAN_MAC_SCAN_TYPE_ACTIVE,           /**< active scan */
    GSN_WLAN_MAC_SCAN_TYPE_P2P_ONLY,         /**< scan for p2p devices only */
    GSN_WLAN_MAC_SCAN_TYPE_P2P_DEVTYPE,      /**< scan for given p2p device type */
    GSN_WLAN_MAC_SCAN_TYPE_P2P_DEVID,        /**< scan for given p2p device Id */
    GSN_WLAN_MAC_SCAN_TYPE_WLAN_AND_P2PGRPS, /**< scan for wlan and p2p groups */
    GSN_WLAN_MAC_SCAN_TYPE_WLAN_AND_P2PDEVS, /**< scan for wlan and p2p devices */
} GSN_WLAN_MAC_SCAN_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief structured type for holding MAC address.
 *
 *****************************************************************************/
typedef struct GSN_WLAN_MAC_ADDR_S
{
    UINT8 array[GSN_WLAN_MAC_ADDR_LEN];
} GSN_WLAN_MAC_ADDR_T;

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief scan response frame type
 *
 *****************************************************************************/
typedef enum GSN_WLAN_SCAN_RESP_FRAME_TYPE_S
{
      GSN_WLAN_SCAN_RESP_FRAME_TYPE_PROBE_RSP             = 0x50,
      GSN_WLAN_SCAN_RESP_FRAME_TYPE_BEACON                = 0x80,
}GSN_WLAN_SCAN_RESP_FRAME_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief GSN WLAN MAC SSID.
 * 
 *    Structure defining SSID type.
 *****************************************************************************/
typedef struct GSN_WLAN_MAC_SSID_S
{
    UINT8 length; /**< Length of the SSID */
    UINT8 array[GSN_WLAN_MAC_SSID_LEN];/**< SSID, max length can be as of now 32 */
} GSN_WLAN_MAC_SSID_T;

typedef enum GSN_WIF_WLAN_PHY_MODE_E
{
    GSN_WLAN_PHY_MODE_B_ONLY,
    GSN_WLAN_PHY_MODE_G_ONLY,
    GSN_WLAN_PHY_MODE_BG_MIXED,
    GSN_WLAN_PHY_MODE_BGN_MIXED,
    GSN_WLAN_PHY_MODE_N_ONLY,
	GSN_WLAN_PHY_MODE_N_2040,
    GSN_WLAN_PHY_MODE_MAX,
} GSN_WIF_WLAN_PHY_MODE_T;

/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief GSN WIF control transfer descriptor.
 * 
 *    Structure defining the control interface transfer descriptor.
 *****************************************************************************/



/**
 *****************************************************************************
 * @ingroup GsnWlanDefs
 * @brief GSN WIF data transfer descriptor.
 * 
 *    Structure defining the data interface transfer descriptor.
 *****************************************************************************/




#ifdef __cplusplus
}
#endif
#endif /* _GSN_WLAN_DEFS_H_ */






