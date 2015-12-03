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
* $RCSfile: gsn_wif_api.h,v $
*
* Description : This file contains WIF CTL API definitions.
******************************************************************************/
#ifndef _GSN_WIF_API_H_
#define _GSN_WIF_API_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wif_api.h
 * @brief GSN WIF API public header.
 * 
 *    This file contains the public APIs of WLAN control
 *    interface.
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
 * @defgroup GsnWifApi GSN WIF WLAN Control API
 *    This group of APIs provides WLAN control path.
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/	
	
/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief API type identifier definition.
 * 
 *    This defines the API type identifier format. The upper 6 bits are for
 *    API type and lower 10 bits are for subtype.
*****************************************************************************/
#define GSN_WIF_API_TYPE_SHIFT  10
#define GSN_WIF_API_TYPE_SIZE   6



/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief API types.
 * 
 *    API type identifier
*****************************************************************************/
#define GSN_WIF_API_TYPE_SYS_CTL     0x0
#define GSN_WIF_API_TYPE_WLAN_CTL    0x1
#define GSN_WIF_API_TYPE_154_CTL     0x2
#define GSN_WIF_API_TYPE_ISOTX_CTL   0x3
#define GSN_WIF_API_TYPE_CAL_CTL     0x4
#define GSN_WIF_API_TYPE_UNUSED      0x10 /* can be used for something */
#define GSN_WIF_API_TYPE_DATA        0x20
#define GSN_WIF_API_TYPE_154_DATA    0x21
#define GSN_WIF_API_TYPE_WLAN_UNASSOC_DATA      0x22 
#define GSN_WIF_API_TYPE_DBG         0x30 /* only 6 bits, so dont go to 0x40 after this */


#define GSN_WIF_API_SYS_CTL         (GSN_WIF_API_TYPE_SYS_CTL << GSN_WIF_API_TYPE_SHIFT)
#define GSN_WIF_API_WLAN_CTL        (GSN_WIF_API_TYPE_WLAN_CTL << GSN_WIF_API_TYPE_SHIFT)
#define GSN_WIF_API_154_CTL         (GSN_WIF_API_TYPE_154_CTL << GSN_WIF_API_TYPE_SHIFT)
#define GSN_WIF_API_ISOTX_CTL       (GSN_WIF_API_TYPE_ISOTX_CTL << GSN_WIF_API_TYPE_SHIFT)
#define GSN_WIF_API_CAL_CTL         (GSN_WIF_API_TYPE_CAL_CTL << GSN_WIF_API_TYPE_SHIFT)

#define GSN_WIF_API_DBG             (GSN_WIF_API_TYPE_DBG << GSN_WIF_API_TYPE_SHIFT)


#define GSN_WIF_IND_RSP_MSG_TYPE    0x200
#define GSN_WIF_MSG_TYPE_END        (GSN_WIF_IND_RSP_MSG_TYPE - 1)
/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief System Control API.
 * 
 *    System Control APIs
*****************************************************************************/
#define GSN_WIF_API_SYS_BOOT_REQ        (GSN_WIF_API_SYS_CTL | 0)
#define GSN_WIF_API_SYS_STDBY_REQ       (GSN_WIF_API_SYS_CTL | 1)
#define GSN_WIF_API_SYS_IF_START_REQ    (GSN_WIF_API_SYS_CTL | 2)
#define GSN_WIF_API_SYS_IF_STOP_REQ     (GSN_WIF_API_SYS_CTL | 3)
#define GSN_WIF_API_SYS_IF_PAUSE_REQ    (GSN_WIF_API_SYS_CTL | 4)
#define GSN_WIF_API_SYS_FW_VERSION_REQ  (GSN_WIF_API_SYS_CTL | 5)
#define GSN_WIF_API_SYS_FILE_OP_RSP     (GSN_WIF_API_SYS_CTL | 6)
#define GSN_WIF_API_SYS_STDBY_CANCEL_REQ (GSN_WIF_API_SYS_CTL | 7)
#define GSN_WIF_API_SYS_OTP_WRITE_REQ    (GSN_WIF_API_SYS_CTL | 8)
#define GSN_WIF_API_SYS_OTP_READ_REQ     (GSN_WIF_API_SYS_CTL | 9)
#define GSN_WIF_API_SYS_MEM_READ_REQ     (GSN_WIF_API_SYS_CTL | 10)
#define GSN_WIF_API_SYS_MEM_WRITE_REQ    (GSN_WIF_API_SYS_CTL | 11)
#define GSN_WIF_API_SYS_BATT_CHK_REQ     (GSN_WIF_API_SYS_CTL | 12)
#define GSN_WIF_API_SYS_CM_START_REQ     (GSN_WIF_API_SYS_CTL | 13)
#define GSN_WIF_API_SYS_FEATURE_BMAP_REQ (GSN_WIF_API_SYS_CTL | 14)
#define GSN_WIF_API_SYS_TEMP_GET_REQ     (GSN_WIF_API_SYS_CTL | 15)
#define GSN_WIF_API_SYS_TEMP_SET_REQ     (GSN_WIF_API_SYS_CTL | 16)

#define GSN_WIF_SYS_API_REQ_START       (GSN_WIF_API_SYS_BOOT_REQ)
#define GSN_WIF_SYS_API_REQ_END         (GSN_WIF_API_SYS_CTL | GSN_WIF_MSG_TYPE_END)


#define GSN_WIF_API_SYS_BOOT_IND                (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 0)
#define GSN_WIF_API_SYS_STDBY_RDY_IND           (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 1)
#define GSN_WIF_API_SYS_IF_START_RSP            (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 2)
#define GSN_WIF_API_SYS_IF_STOP_RSP             (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 3)
#define GSN_WIF_API_SYS_IF_RESUME_REQ           (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 4)
#define GSN_WIF_API_SYS_FW_VERSION_RSP          (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 5)
#define GSN_WIF_API_SYS_RESET_REQ               (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 6)
#define GSN_WIF_API_SYS_FILE_OP_REQ             (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 7)
#define GSN_WIF_API_SYS_OTP_WRITE_RSP           (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 8)
#define GSN_WIF_API_SYS_OTP_READ_RSP            (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 9)
#define GSN_WIF_API_SYS_MEM_WRITE_RSP           (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 10)
#define GSN_WIF_API_SYS_MEM_READ_RSP            (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 11)
#define GSN_WIF_API_SYS_BATT_CHK_IND            (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 12)
#define GSN_WIF_API_SYS_CM_START_IND            (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 13)
#define GSN_WIF_API_SYS_FEATURE_BMAP_RSP        (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 14)
#define GSN_WIF_API_SYS_RF_CALIB_DATA_WR_REQ    (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 15)
#define GSN_WIF_API_SYS_TEMP_GET_RSP    (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 16)

#define GSN_WIF_SYS_API_IND_START       (GSN_WIF_API_SYS_BOOT_IND)
#define GSN_WIF_SYS_API_IND_END         (GSN_WIF_API_SYS_CTL | GSN_WIF_IND_RSP_MSG_TYPE | GSN_WIF_MSG_TYPE_END)

/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief WLAN Control API.
 * 
 *    WLAN Control APIs
*****************************************************************************/
#define GSN_WIF_API_WLAN_CONNECT_REQ                    (GSN_WIF_API_WLAN_CTL | 0)
#define GSN_WIF_API_WLAN_DISCONNECT_REQ                 (GSN_WIF_API_WLAN_CTL | 1)
/* RF test APIs */
#define GSN_WIF_API_WLAN_RF_TEST_FRAME_TX_START_REQ     (GSN_WIF_API_WLAN_CTL | 2)
#define GSN_WIF_API_WLAN_RF_TEST_TX_TEST_STOP_REQ       (GSN_WIF_API_WLAN_CTL | 3)
#define GSN_WIF_API_WLAN_RF_TEST_FRAME_RX_START_REQ     (GSN_WIF_API_WLAN_CTL | 4)
#define GSN_WIF_API_WLAN_RF_TEST_FRAME_RX_STOP_REQ      (GSN_WIF_API_WLAN_CTL | 5)
#define GSN_WIF_API_WLAN_RF_TEST_TX99_START_REQ         (GSN_WIF_API_WLAN_CTL | 6)
#define GSN_WIF_API_WLAN_RF_TEST_TX100_START_REQ        (GSN_WIF_API_WLAN_CTL | 7)
#define GSN_WIF_API_WLAN_RF_TEST_CARRIER_WAVE_START_REQ (GSN_WIF_API_WLAN_CTL | 8)
#define GSN_WIF_API_WLAN_TEST_MODE_START_REQ            (GSN_WIF_API_WLAN_CTL | 9)
#define GSN_WIF_API_WLAN_TEST_MODE_STOP_REQ             (GSN_WIF_API_WLAN_CTL | 10)
#define GSN_WIF_API_WLAN_SCAN_REQ                       (GSN_WIF_API_WLAN_CTL | 11)
#define GSN_WIF_API_WLAN_INSTALL_KEY_REQ                (GSN_WIF_API_WLAN_CTL | 12)
#define GSN_WIF_API_WLAN_REMOVE_KEY_REQ                 (GSN_WIF_API_WLAN_CTL | 13)
#define GSN_WIF_API_WLAN_MAC_ADDR_SET_REQ               (GSN_WIF_API_WLAN_CTL | 14)
#define GSN_WIF_API_WLAN_MAC_ADDR_GET_REQ               (GSN_WIF_API_WLAN_CTL | 15)
#define GSN_WIF_API_WLAN_PROBE_REQ_IE_SET_REQ           (GSN_WIF_API_WLAN_CTL | 16)
#define GSN_WIF_API_WLAN_ASS0C_REQ_IE_SET_REQ           (GSN_WIF_API_WLAN_CTL | 17)
#define GSN_WIF_API_WLAN_SCAN_PARAMS_SET_REQ            (GSN_WIF_API_WLAN_CTL | 18)
#define GSN_WIF_API_BEACON_MISS_THRESHOLD_SET_REQ       (GSN_WIF_API_WLAN_CTL | 19)
#define GSN_WIF_API_SET_COUNTER_MSR_START_REQ           (GSN_WIF_API_WLAN_CTL | 20)
#define GSN_WIF_API_CONNECTED_STA_LIST_GET_REQ          (GSN_WIF_API_WLAN_CTL | 21)
#define GSN_WIF_API_TKIP_SEQ_NUM_GET_REQ                (GSN_WIF_API_WLAN_CTL | 22)
#define GSN_WIF_API_WLAN_STATISTICS_GET_REQ             (GSN_WIF_API_WLAN_CTL | 23)
#define GSN_WIF_API_WLAN_RECV_FILTER_SET_REQ            (GSN_WIF_API_WLAN_CTL | 24)
#define GSN_WIF_API_WLAN_RTS_ENABLE_REQ                 (GSN_WIF_API_WLAN_CTL | 25)
#define GSN_WIF_API_WLAN_ADDBA_REQ                      (GSN_WIF_API_WLAN_CTL | 26)
#define GSN_WIF_API_WLAN_DELBA_REQ                      (GSN_WIF_API_WLAN_CTL | 27)
#define GSN_WIF_API_WLAN_AMSDU_START_REQ                (GSN_WIF_API_WLAN_CTL | 28)
#define GSN_WIF_API_WLAN_AMSDU_END_REQ                  (GSN_WIF_API_WLAN_CTL | 29)
#define GSN_WIF_API_WLAN_AMPDU_START_REQ                (GSN_WIF_API_WLAN_CTL | 30)
#define GSN_WIF_API_WLAN_AMPDU_END_REQ                  (GSN_WIF_API_WLAN_CTL | 31)
#define GSN_WIF_API_WLAN_FRAME_TX_FAIL_COUNT_SET_REQ    (GSN_WIF_API_WLAN_CTL | 32)
#define GSN_WIF_API_WLAN_PHY_MODE_SET_REQ               (GSN_WIF_API_WLAN_CTL | 33)
#define GSN_WIF_API_WLAN_PHY_MODE_GET_REQ               (GSN_WIF_API_WLAN_CTL | 34)
#define GSN_WIF_API_WLAN_TXPOWER_SET_REQ                (GSN_WIF_API_WLAN_CTL | 35)
#define GSN_WIF_API_WLAN_TXPOWER_GET_REQ                (GSN_WIF_API_WLAN_CTL | 36)
#define GSN_WIF_API_WLAN_RSSI_GET_REQ                   (GSN_WIF_API_WLAN_CTL | 37)
#define GSN_WIF_API_WLAN_STA_PS_CFG_REQ                 (GSN_WIF_API_WLAN_CTL | 38)
#define GSN_WIF_API_WLAN_STA_PS_STATE_SET_REQ           (GSN_WIF_API_WLAN_CTL | 39)
#define GSN_WIF_API_WLAN_STA_PS_DAB_DONE_IND_EN_REQ     (GSN_WIF_API_WLAN_CTL | 40)

#define GSN_WIF_API_WLAN_NUM_RETRY_SET_REQ              (GSN_WIF_API_WLAN_CTL | 41)
#define GSN_WIF_API_WLAN_NUM_RETRY_GET_REQ              (GSN_WIF_API_WLAN_CTL | 42)
#define GSN_WIF_API_WLAN_STATE_GET_REQ                  (GSN_WIF_API_WLAN_CTL | 43)
#define GSN_WIF_API_WLAN_WLAN_TX_POW_SET_REQ            (GSN_WIF_API_WLAN_CTL | 44)
#define GSN_WIF_API_WLAN_WLAN_TX_POW_GET_REQ            (GSN_WIF_API_WLAN_CTL | 45)
#define GSN_WIF_API_WLAN_UNASSOC_MODE_START_REQ         (GSN_WIF_API_WLAN_CTL | 46)
#define GSN_WIF_API_WLAN_UNASSOC_MODE_STOP_REQ          (GSN_WIF_API_WLAN_CTL | 47)
#define GSN_WIF_API_WLAN_UNASSOC_RX_CONFIG_REQ          (GSN_WIF_API_WLAN_CTL | 48)
#define GSN_WIF_API_WLAN_UNASSOC_RX_START_REQ           (GSN_WIF_API_WLAN_CTL | 49)
#define GSN_WIF_API_WLAN_UNASSOC_RX_STOP_REQ            (GSN_WIF_API_WLAN_CTL | 50)
#define GSN_WIF_API_WLAN_AP_PS_CFG_REQ                  (GSN_WIF_API_WLAN_CTL | 51)
#define GSN_WIF_API_WLAN_TX_WAIT_ALL_REQ                (GSN_WIF_API_WLAN_CTL | 52)
#define GSN_WIF_API_WLAN_TX_RATE_SET_REQ                (GSN_WIF_API_WLAN_CTL | 53)
#define GSN_WIF_API_WLAN_TX_RATE_GET_REQ                (GSN_WIF_API_WLAN_CTL | 54)
#define GSN_WIF_API_WLAN_KEEP_ALIVE_SET_REQ             (GSN_WIF_API_WLAN_CTL | 55)
#define GSN_WIF_API_WLAN_MCST_RX_SET_REQ                (GSN_WIF_API_WLAN_CTL | 56)
#define GSN_WIF_API_WLAN_MEM_REG_POKE_REQ               (GSN_WIF_API_WLAN_CTL | 57)
#define GSN_WIF_API_WLAN_MEM_REG_PEEK_REQ               (GSN_WIF_API_WLAN_CTL | 58)
#define GSN_WIF_API_WLAN_STA_PS_STATE_GET_REQ           (GSN_WIF_API_WLAN_CTL | 59)
#define GSN_WIF_API_WLAN_ALLOW_BA                       (GSN_WIF_API_WLAN_CTL | 60)
#define GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_REQ       (GSN_WIF_API_WLAN_CTL | 61)
#define GSN_WIF_API_WLAN_VS_IE_SET_REQ            		(GSN_WIF_API_WLAN_CTL | 62)                        

#define GSN_WIF_WLAN_API_REQ_START                  (GSN_WIF_API_WLAN_CONNECT_REQ)
#define GSN_WIF_WLAN_API_REQ_END                    (GSN_WIF_API_WLAN_CTL | GSN_WIF_MSG_TYPE_END)


#define GSN_WIF_API_WLAN_CONNECT_IND                (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 0)
#define GSN_WIF_API_WLAN_DISCONNECT_IND             (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 1)
#define GSN_WIF_API_WLAN_SCAN_IND              		(GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 2)
#define GSN_WIF_API_WLAN_SCAN_COMPLETE_IND          (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 3)
#define GSN_WIF_API_WLAN_MAC_ADDR_GET_RESP          (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 4)
#define GSN_WIF_API_WLAN_RF_TEST_FRAME_RX_STOP_RESP (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 5)
#define GSN_WIF_API_WLAN_RF_TEST_FRAME_TX_DONE_IND  (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 6)
#define GSN_WIF_API_WLAN_BCN_MISS_IND               (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 7)
#define GSN_WIF_API_WLAN_STA_CONNECTED_IND          (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 8)
#define GSN_WIF_API_WLAN_STA_DISCONNECTED_IND       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 9)
#define GSN_WIF_API_WLAN_MIC_FAILURE_IND            (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 10)
#define GSN_WIF_API_WLAN_CONNECTED_STA_LIST_GET_RSP (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 11)
#define GSN_WIF_API_WLAN_TKIP_COUNTER_GET_RSP       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 12)
#define GSN_WIF_API_WLAN_STATS_GET_RSP              (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 13)
#define GSN_WIF_API_WLAN_FRAME_TX_FAIL_IND          (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 14)
#define GSN_WIF_API_WLAN_PHY_MODE_GET_RSP          (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 15)
#define GSN_WIF_API_WLAN_TXPOWER_GET_RSP            (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 16)
#define GSN_WIF_API_WLAN_RSSI_GET_RSP               (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 17)
#define GSN_WIF_API_WLAN_AP_TIMESTAMP_RST_IND       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 18)
#define GSN_WIF_API_WLAN_CONT_DECRYPT_FAIL_IND      (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 19)
#define GSN_WIF_API_WLAN_DAB_DONE_IND               (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 20)
#define GSN_WIF_API_WLAN_NUM_RETRY_GET_RSP          (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 21)
#define GSN_WIF_API_MAC_STATE_GET_RSP               (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 22)
#define GSN_WIF_API_WLAN_TX_POW_GET_RSP             (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 23)
#define GSN_WIF_API_WLAN_UNASSOC_MODE_START_RSP     (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 24)
#define GSN_WIF_API_WLAN_UNASSOC_MODE_STOP_RSP      (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 25)
#define GSN_WIF_API_WLAN_UNASSOC_RX_START_RSP       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 26)
#define GSN_WIF_API_WLAN_UNASSOC_RX_STOP_RSP        (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 27)
#define GSN_WIF_API_WLAN_UNASSOC_TX_CFM_IND         (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 28)
#define GSN_WIF_API_WLAN_UNASSOC_RX_CONFIG_RSP       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 29)
#define GSN_WIF_API_WLAN_TX_WAIT_ALL_RSP            (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 30)
#define GSN_WIF_API_WLAN_TX_RATE_GET_RSP            (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 31)
#define GSN_WIF_API_WLAN_MEM_REG_PEEK_RSP           (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 32)
#define GSN_WIF_API_WLAN_STA_PS_STATE_GET_RSP       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 33)
#define GSN_WIF_API_WLAN_ASYNC_DISCONNECT_IND       (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 34)
#define GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_RSP   (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 35)

#define GSN_WIF_WLAN_API_IND_START                  (GSN_WIF_API_WLAN_CONNECT_IND)
#define GSN_WIF_WLAN_API_IND_END                    (GSN_WIF_API_WLAN_CTL | GSN_WIF_IND_RSP_MSG_TYPE | GSN_WIF_MSG_TYPE_END)




/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief ISOTX Control API.
 * 
 *    ISOTX Control APIs
*****************************************************************************/
/* Requests */
#define GSN_WIF_API_ISOTX_BLINK_REQ       (GSN_WIF_API_ISOTX_CTL | 0)
#define GSN_WIF_API_ISOTX_STOP_REQ        (GSN_WIF_API_ISOTX_CTL | 1)
#define GSN_WIF_API_ISOTX_REGWRITE_REQ    (GSN_WIF_API_ISOTX_CTL | 2)

#define GSN_WIF_ISOTX_API_REQ_START    GSN_WIF_API_ISOTX_BLINK_REQ
#define GSN_WIF_ISOTX_API_REQ_END      (GSN_WIF_API_ISOTX_CTL | GSN_WIF_MSG_TYPE_END)


/* Indications */
//#define GSN_WIF_API_ISOTX_EXT_APP     (GSN_WIF_API_ISOTX_CTL | 1) // this API to be provided by Gainspan framework 
#define GSN_WIF_API_ISOTX_BDAT_IND    (GSN_WIF_API_ISOTX_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 0)

#define GSN_WIF_ISOTX_API_IND_START    GSN_WIF_API_ISOTX_BDAT_IND
#define GSN_WIF_ISOTX_API_IND_END      (GSN_WIF_API_ISOTX_CTL | GSN_WIF_IND_RSP_MSG_TYPE | GSN_WIF_MSG_TYPE_END)

/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief CAL Control API.
 *
 *    CAL Control APIs
*****************************************************************************/
/* Requests */
#define GSN_WIF_API_CAL_RUN       (GSN_WIF_API_CAL_CTL | 0)

/* These define the range of API - useful for checking */
#define GSN_WIF_CAL_API_REQ_START    GSN_WIF_API_CAL_RUN
#define GSN_WIF_CAL_API_REQ_END      (GSN_WIF_API_CAL_CTL | GSN_WIF_MSG_TYPE_END)

/* Responses/Indications */
#define GSN_WIF_API_CAL_RUN_RSP    (GSN_WIF_API_CAL_CTL | GSN_WIF_IND_RSP_MSG_TYPE | 0)

/* These define the range of API - useful for checking */
#define GSN_WIF_CAL_API_IND_START    GSN_WIF_API_CAL_RUN_RSP
#define GSN_WIF_CAL_API_IND_END      (GSN_WIF_API_CAL_CTL | GSN_WIF_IND_RSP_MSG_TYPE | GSN_WIF_MSG_TYPE_END)


/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief Debug API.
 * 
 *    Debug APIs
*****************************************************************************/
/* Requests */
#define GSN_WIF_API_DBG_REG_PEEK_REQ        (GSN_WIF_API_DBG | 0)
#define GSN_WIF_API_DBG_REG_POKE_REQ        (GSN_WIF_API_DBG | 1)
#define GSN_WIF_API_DBG_MEM_READ_REQ        (GSN_WIF_API_DBG | 2)
#define GSN_WIF_API_DBG_MEM_WRITE_REQ       (GSN_WIF_API_DBG | 3)
#define GSN_WIF_API_DBG_EXEC_REQ            (GSN_WIF_API_DBG | 4)
#define GSN_WIF_API_DBG_FLASH_READ_REQ      (GSN_WIF_API_DBG | 5)
#define GSN_WIF_API_DBG_OTP_WRITE_REQ       (GSN_WIF_API_DBG | 6)
#define GSN_WIF_API_DBG_OTP_READ_REQ        (GSN_WIF_API_DBG | 7)

#define GSN_WIF_DBG_API_REQ_START    GSN_WIF_API_DBG_REG_PEEK_REQ
#define GSN_WIF_DBG_API_REQ_END      (GSN_WIF_API_DBG | GSN_WIF_MSG_TYPE_END)


#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_API_H_ */






