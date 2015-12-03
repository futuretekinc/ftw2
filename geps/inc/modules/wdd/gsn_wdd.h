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
* $RCSfile: gsn_wdd.h,v $
*
* Description : This file contains public definitions for WDD. WDD( Wireless Device Driver ) provides APIs for 
* the wireless drivers. These APIs are scan request, connect request,  disconnect request, data request. 
* WDD generates events related to these request. If application has registered its callback function, 
* WDD calls it whenever these events happens.
*******************************************************************************/
#ifndef _GSN_WDD_H_
#define _GSN_WDD_H_

/**
 *******************************************************************************
 * @file gsn_wdd.h
 * @brief GSN WDD public header.
 *    This file contains public definitions for WDD. WDD( Wireless Device Driver ) provides APIs for 
 * the wireless drivers. These APIs are scan request, connect request,  disconnect request, data request. 
 * WDD generates events related to these request. If application has registered its callback function, 
 * WDD calls it whenever these events happens.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 * @{
 *****************************************************************************/
 
/**
 *******************************************************************************
 * @defgroup GsnWdd GSN Wireless Device Driver
 * @brief Controls for 802.11 operations.
 *
 *   This group contains public definitions for the Wireless Device Driver (WDD). Functions are provided 
 * to control 802.11 scanning,  connect (associate), disconnect, and transmission and reception of data. 
 * IOCTL functions are provided for modifying some WLAN parameters.
 ******************************************************************************/
	
/**
 ******************************************************************************
 * @} 
 *****************************************************************************/

typedef GSN_WIF_WLAN_DISCONNECT_IND_T			GSN_WDD_DISASSOCIATION_CB_INFO;

typedef GSN_WIF_API_WLAN_RF_TEST_TX_START_REQ_T GSN_WDD_RFTEST_TX_START_PARAM_T;

typedef GSN_WIF_API_WLAN_RF_TEST_TX99_START_REQ_T GSN_WIF_API_WLAN_RF_TEST_TX99_START_PARAM_T;

typedef GSN_WIF_API_WLAN_RF_TEST_TX100_START_REQ_T GSN_WIF_API_WLAN_RF_TEST_TX100_START_PARAM_T;

typedef GSN_WIF_API_WLAN_RF_TEST_CARRIER_WAVE_START_REQ_T GSN_WIF_API_WLAN_RF_TEST_CARRIER_WAVE_START_PARAM_T;

typedef GSN_WIF_API_WLAN_RF_TEST_RX_START_REQ_T	GSN_WIF_API_WLAN_RF_TEST_RX_START_PARAM_T;

typedef GSN_WIF_WLAN_MIC_FAILURE_IND_T	GSN_WDD_MIC_FAILURE_INFO_T;

typedef GSN_WIF_WLAN_RTS_ENABLE_T GSN_WDD_RTS_ENBL_PARAM_T;

typedef GSN_WIF_WLAN_RX_FILTER_SET_T GSN_WDD_WLAN_RECV_FILTR_SET_PARAM_T;

typedef GSN_WIF_WLAN_FRAME_TX_FAIL_COUNT_THRESHOLD_REQ_T GSN_WDD_FRAME_TX_FAIL_CNT_LIMIT_SET_T;

typedef GSN_WIF_WLAN_FRAME_TX_FAIL_IND_T	GSN_WDD_FRAME_TXFAIL_INFO_T;

typedef GSN_WIF_CAL_RUN_RSP_T GSN_WDD_CAL_RUN_RSP_T;

typedef GSN_WIF_CAL_RUN_REQ_T GSN_WDD_CAL_RUN_REQ_T;

typedef GSN_WIF_API_WLAN_UNASSOC_MODE_START_RESP_T GSN_WDD_UAM_START_RESP_T;

typedef GSN_WIF_API_WLAN_UNASSOC_DATA_RX_CONFIG_REQ_T GSN_WDD_UAM_DRX_CONFIG_PARAM_T;

typedef GSN_WIF_API_WLAN_UNASSOC_MODE_STOP_RESP_T GSN_WDD_UAM_STOP_RESP_T;

typedef GSN_WIF_API_WLAN_UNASSOC_DATA_RX_START_REQ_T GSN_WDD_UAM_DRX_START_PARAM;

typedef GSN_WIF_API_WLAN_UNASSOC_DATA_RX_STOP_REQ_T  GSN_WDD_UAM_DRX_STOP_PARAM;

typedef GSN_WIF_API_WLAN_UNASSOC_DATA_RX_START_RESP_T GSN_WDD_UAM_DRX_START_RESP_T;

typedef GSN_WIF_API_WLAN_UNASSOC_DATA_RX_STOP_RESP_T GSN_WDD_UAM_DRX_STOP_RESP_T;

typedef GSN_WIF_API_WLAN_UNASSOC_DATAREQ_HDR_T GSN_WDD_UAM_DATA_HDR_T;

typedef GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_RESP_T GSN_WDD_UAM_CCA_SET_RESP_T;

typedef GSN_WIF_WLAN_TX_POWER_T	GSN_WDD_TX_POW_SET_PARAM_T;

typedef GSN_WIF_WLAN_TX_POWER_T	GSN_WDD_TX_POW_GET_RESP_T;

typedef GSN_WIF_WLAN_TX_RATE_T  GSN_WDD_TX_RATE_SET_PARAM_T;

typedef GSN_WIF_WLAN_TX_RATE_T GSN_WDD_TX_RATE_GET_RESP;

typedef GSN_WIF_WLAN_AP_PS_CFG_T	GSN_WDD_AP_PS_CFG_SET_PARAM;

typedef GSN_WIF_WLAN_STA_PS_CFG_T	GSN_WDD_STA_PS_CFG_SET_PARAM_T;

typedef GSN_WIF_WLAN_MEM_REG_T	GSN_WDD_WLAN_REG_T;

typedef GSN_WIF_WLAN_ALLOW_BA_TID_BITMAP_T	GSN_WDD_ALLOW_BA_BITMAP_SET_PARAM;
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Maximum WLAN channels.
 *	   This macro defines the maximum number of WLAN channels in 2.4GHz band.
 ******************************************************************************/
#define GSN_WDD_WLAN_MAX_CHNLS          GSN_WLAN_MAC_MAX_CHNLS /**< Max WLAN channels in 2.4GHzb band */
	

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Default WLAN Listen interval.
 *     This macro defines the default listen interval. Listen interval is defined in terms of beacon 
 * intervals. Assuming 100ms beacon interval,  listen interval of 60 seconds = 60 * 10 beacon intervals.
 ******************************************************************************/
#define GSN_WDD_WLAN_DEFAULT_LISTEN_INTERVAL     600 /**< Default listen interval */

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Default WLAN Beacon interval.
 *     This macro defines the default beacon interval. Beacon interval is  defined in terms of time units. 
 * 1TU is 1024us (1 mSec). Therefore Beacon interval  of 100ms = 100TU.
 ******************************************************************************/
#define GSN_WDD_WLAN_DEFAULT_BEACON_INTERVAL     100 /**< Default beacon interval */

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Default WLAN DTIM period.
 *     This macro defines the default DTIM period. DTIM period is defined in terms of beacon intervals.
 ******************************************************************************/
#define GSN_WDD_WLAN_DEFAULT_DTIM_PERIOD         1 /**< Default ditim period*/

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Events notified to the wdd module
 *	This defines the events notified to the wdd module using the GsnWdd_Notify() API 
 * @see GsnWdd_Notify API
 ******************************************************************************/                
typedef enum GSN_WDD_EVENT
{
	GSN_WDD_EVENT_WPA_TMR_TIMEOUT, /* [TO DO] This event is not used. remove in next ROM build*/
	GSN_WDD_EVENT_WPA_AUTH_SUCCESS,
	GSN_WDD_EVENT_WPA_AUTH_FAILURE,
	GSN_WDD_EVENT_WPA_WPS_DONE_AUTH_FAILURE
}GSN_WDD_EVENT_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Flags for GSN WDD Connect operation
 *	This defines the wdd connect flags. One or more fo these can be ORed to form a connect flag
 * @see GsnWdd_Connect API   
 ******************************************************************************/                
typedef enum GSN_WDD_CONNECT_FLAG
{
	GSN_WDD_CONNECT_FLAG_NONE,
	GSN_WDD_CONNECT_FLAG_ACTIVE_SCAN 			= BIT(0), /**<Use active scan. Passive scan is by 
																default */
	GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT 	= BIT(1), /**< Scan before connect for finding the
																given wlan network*/
	GSN_WDD_CONNECT_FLAG_HIGHEST_RSSI_NW 		= BIT(2), /**< Connects to NW with highest 
																rssi value. Note: Copalsarily set
																GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT
																for this to work */																
	GSN_WDD_CONNECT_FLAG_WPS_MATHOD 			= BIT(3), /**< Start WPS procedure*/
	GSN_WDD_CONNECT_FLAG_USE_BSSID				= BIT(4), /**< Use configured BSSID for selecting
																BSS. By default configured SSID is used*/
	GSN_WDD_CONNECT_FLAG_WPS_WITH_DFLT_PIN_METHOD = BIT(5),
	
	GSN_WDD_CONNECT_FLAG_WPS_CERTIFICATION      =  BIT(6),
}GSN_WDD_CONNECT_FLAG_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd initialisation enum. 
 *	  This enum describes the wdd module initialisation flags
 ******************************************************************************/    
typedef enum GSN_WDD_INIT_FLAG
{
	GSN_WDD_INIT_FLAG_NONE 			= 0,
	GSN_WDD_INIT_FLAG_FIRST_BOOT 	= BIT(0), /**< First Boot*/
	GSN_WDD_INIT_FLAG_CONF_LOST 	= BIT(1), /**< Wlan Configuration is lost*/
}GSN_WDD_INIT_FLAG_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief flags set used with  scan process  
 ******************************************************************************/
typedef enum GSN_WDD_SCAN_FLAG
{
	GSN_WDD_SCAN_FLAG_HIGHEST_RSSI_NW_FIND = BIT(0), /**< Scans on given channels and provides scan
															entry with highest rssi value. */
}GSN_WDD_SCAN_FLAG_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device I/O control (assumes a wireless L2 device).
 *     
 ******************************************************************************/
typedef enum GSN_WDD_IOCTL_CMD/* !! Note any change here shall be rflected in GSN_L2DEV_IOCTL_CODE_T*/
{
    GSN_WDD_IOCTL_MCAST_RX_ON = 0,
    GSN_WDD_IOCTL_MCAST_RX_OFF,
    GSN_WDD_IOCTL_RX_ACTIVE_MODE_ON,
    GSN_WDD_IOCTL_RX_ACTIVE_MODE_OFF,
    GSN_WDD_IOCTL_RX_PS_MODE_ON,
    GSN_WDD_IOCTL_RX_PS_MODE_OFF,
	GSN_WDD_IOCTL_RX_MODE_COUNTER_CLEAR,
    GSN_WDD_IOCTL_PHY_ADDR_SET,
    GSN_WDD_IOCTL_PHY_ADDR_GET,
	GSN_WDD_IOCTL_RX_IEEEPS_MODE_ON,
	GSN_WDD_IOCTL_RX_IEEEPS_MODE_OFF,

} GSN_WDD_IOCTL_CMD_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief flags set used with  scan process  
 ******************************************************************************/
#define GSN_WDD_ASSOC_STATE_NOT_CONCTED			0
#define GSN_WDD_ASSOC_STATE_CONCTED				1
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief WDD wireless interface management states.
 *    This enum defines the different states the WDD wireless interface is in.
 *    The WDD APIs transition through some or all of these states. After the API
 *    operation is complete, the API is back in idle state.
 ******************************************************************************/
typedef enum GSN_WDD_STATE
{
    GSN_WDD_STATE_IDLE,          			/**< WDD is in idle state and is ready to
                                           			take connect/disconnect request. */
    GSN_WDD_STATE_CONNECTING,    			/**< WDD is connecting */
    GSN_WDD_STATE_SECURED_CONNECTING,		/**< WDD is connecting with a secured Nw. In this case,
    											  once the association is done, wpa supplicant is 
    											  notified and the Authentication procedure is handled by the
    											  supplicant. The user app is notified only after the
    											  authentication process.*/
    GSN_WDD_STATE_WPS_CONNECTING,									
    GSN_WDD_STATE_SCANNING,      			/**< WDD is scanning. */
    GSN_WDD_STATE_DISCONNECTING, 			/**< API is disconnecting. */
} GSN_WDD_STATE_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief WDD module scan state. 
 *	This defines the scan state. This is a secondary state. GSN_WDD_STATE_T is the primary state
 *	 
 ******************************************************************************/
typedef enum GSN_WDD_SCAN_STATE
{
	GSN_WDD_SCN_STATE_IDLE,						/**< No scan being done*/
	GSN_WDD_SCN_STATE_SCANONLY_IN_PROGRESS , 	/**< scan only (scanning by user app) is in progress*/
	GSN_WDD_SCN_STATE_CONCT_SCAN_IN_PROGRESS,	/**< wdd is doing scan to find given wlan nw to 
														connect*/

}GSN_WDD_SCAN_STATE_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Radio mode definition
 ******************************************************************************/
typedef enum GSN_WDD_RADIO_MODE
{
	GSN_WDD_RADIO_MODE_ACTIVE = 1,
	GSN_WDD_RADIO_MODE_POWER_SAVE,
	GSN_WDD_RADIO_MODE_IEEE_POWER_SAVE
}GSN_WDD_RADIO_MODE_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Scan type
 *	This defines the scan type, that is set during scanning.
 ******************************************************************************/
typedef enum GSN_WDD_SCAN_TYPE
{
	GSN_WDD_SCAN_TYPE_PASSIVE 			= GSN_WLAN_MAC_SCAN_TYPE_PASSIVE,      		/**< passive scan */
	GSN_WDD_SCAN_TYPE_ACTIVE 			= GSN_WLAN_MAC_SCAN_TYPE_ACTIVE,           	/**< active scan */ 
	GSN_WDD_SCAN_TYPE_P2P_ONLY 			= GSN_WLAN_MAC_SCAN_TYPE_P2P_ONLY,         	/**< scan for p2p devices only */
	GSN_WDD_SCAN_TYPE_P2P_DEVTYPE 		= GSN_WLAN_MAC_SCAN_TYPE_P2P_DEVTYPE,      	/**< scan for given p2p device type */
	GSN_WDD_SCAN_TYPE_P2P_DEVID 		= GSN_WLAN_MAC_SCAN_TYPE_P2P_DEVID,        	/**< scan for given p2p device Id */
	GSN_WDD_SCAN_TYPE_WLAN_AND_P2PGRPS 	= GSN_WLAN_MAC_SCAN_TYPE_WLAN_AND_P2PGRPS, 	/**< scan for wlan and p2p groups */
	GSN_WDD_SCAN_TYPE_WLAN_AND_P2PDEVS 	= GSN_WLAN_MAC_SCAN_TYPE_WLAN_AND_P2PDEVS, 	/**< scan for wlan and p2p devices */

}GSN_WDD_SCAN_TYPE_T;

typedef struct GSN_WDD_STA_INFO
{
	UINT8 	macAddr[GSN_WLAN_MAC_ADDR_LEN];
	UINT32 	macFrameLen;
	UINT8 *	macFrame;
	
}GSN_WDD_STA_INFO_T;
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD  indication  CB definitions.
 * 		An indication is asychronous in nature. A call back register mechnism is provided for each of the
 * indication supported.
 *******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD "Disassociation " indication  CB definition.
 *******************************************************************************/
typedef VOID (*GSN_WDD_DISASSOC_IND_CB_T)(VOID* ctx, GSN_WDD_DISASSOCIATION_CB_INFO *pDisAssocInfo);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD "Sync loss" indication  CB definition.
 *******************************************************************************/
typedef VOID (*GSN_WDD_BEACON_MISS_IND_CB_T)(VOID* ctx, UINT32 beaconMissCnt);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD STA Connect  indication CB definition. This call back will be called when an sta joins the 
 *	nodes acting as  AP/ Group owner
 *******************************************************************************/
typedef VOID (*GSN_WDD_STA_JOINED_IND_CB_T)(VOID* ctx, GSN_WDD_STA_INFO_T *pStaInfo);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD STA Dis connect  indication CB definition. This call back will be called when an sta joins the 
 *	nodes acting as  AP/ Group owner
 *******************************************************************************/
typedef VOID (*GSN_WDD_STA_DISCONCTED_IND_CB_T)(VOID* ctx, UINT8 *staMacAddr);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD "Battery Level" indication  CB definition.
 *******************************************************************************/
typedef VOID (*GSN_WDD_BATT_LEVL_IND_CB_T)(VOID* ctx,  UINT32 battLevl);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD "Battery Level" indication  CB definition.
 *******************************************************************************/
typedef VOID (*GSN_WDD_MIC_FAILURE_IND_CB_T)(VOID *ctx, GSN_WDD_MIC_FAILURE_INFO_T *pMicFailureInfo);

/**
*******************************************************************************
* @ingroup GsnWdd
* @brief GSN WDD "Battery Level" indication  CB definition.
*******************************************************************************/
typedef VOID (*GSN_WDD_FRAME_TXFAIL__IND_CB_T)(VOID *ctx, GSN_WDD_FRAME_TXFAIL_INFO_T *pMicFailureInfo);
	
/**
*******************************************************************************
* @ingroup GsnWdd
* @brief GSN WDD "Battery Level" indication  CB definition.
*******************************************************************************/
typedef VOID (*GSN_WDD_DAB_DONE_IND_CB_T)(VOID *ctx);


/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_WDD_DATA_IND_CB_T)(VOID *ctx, INT8 *data, UINT16 dataLen);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD indication  CB structure.
 *		Datastructure having various indication call back function pointers and respective context.
 *******************************************************************************/
typedef struct GSN_WDD_IND_CB_INFO
{
	GSN_WDD_DISASSOC_IND_CB_T disassocIndCb;
	VOID * disassocIndCbCtx;

	GSN_WDD_BEACON_MISS_IND_CB_T beaconMissIndCb;
	VOID *beaconMissIndCbCtx;

	GSN_WDD_BATT_LEVL_IND_CB_T battLevlIndCb;
	VOID *battLevlIndCbCtx;

	GSN_WDD_STA_JOINED_IND_CB_T  staJoinedIndCb;
	VOID * staJoinedIndCbCtx;

	GSN_WDD_STA_DISCONCTED_IND_CB_T staDisconctedIndCb;
	VOID * staDisconctedIndCbCtx;

	GSN_WDD_MIC_FAILURE_IND_CB_T micFailureIndCb;
	VOID *micFailureIndCbCtx;

	GSN_WDD_FRAME_TXFAIL__IND_CB_T frameTxFailIndCb;	
	VOID *frameTxFailIndCbCtx;

	GSN_WDD_DAB_DONE_IND_CB_T	dabDoneIndCb;
	VOID *dabDoneIndCbCtx;

	GSN_WDD_DATA_IND_CB_T dataIndCb;
	VOID * dataIndCbCtx;
}GSN_WDD_IND_CB_INFO_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd Notifications call back definitions. 
 *		A Notification is sychronous in nature. That is a notification is called for a given request made earlier. 
 * notification cb and cbCtx are provided as part of the request.
 ******************************************************************************/    

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_WDD_CONNECT_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Disconnect" Notification call back definition. 
 * @see [TO DO]
 ******************************************************************************/	
typedef VOID (*GSN_WDD_DISCONNECT_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Scan Done" Notification call back definition. 
 * @see [TO DO].
 ******************************************************************************/	
typedef VOID (*GSN_WDD_SCAN_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status, 
												   UINT8 *resultBuf, UINT32 numResults);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd Calibration Run response Notification call back definition. 
 * @see [TO DO].
 ******************************************************************************/	
typedef VOID (*GSN_WDD_CAL_NOTIF_CB_T)(VOID *ctx, GSN_WDD_CAL_RUN_RSP_T *resp);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd Message handler message definition.
 *
 *	   This macro defines the Wdd Message handler message.
 ******************************************************************************/
typedef struct GSN_WDD_MESSAGE
{
	UINT32 		msgType;	/**< message of type GSN_WDD_MESSAGE_T */
	VOID *		msgBuf;		/**< pointer to buffer having message Amessage mey not be present in  
						 			message types*/
	UINT32 		msgLen; 	/**< Associated message length*/
	VOID *		ctx; 		/**< Used to hold the pointer to the GSN_WDD_CTX_T wherever required*/
}GSN_WDD_MESSAGE_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Notification  CB structure.
 *		Datastructure having various indication call back and respective context.
 *******************************************************************************/
typedef struct GSN_WDD_NOTIF_CB
{
	GSN_WDD_CONNECT_NOTIF_CB_T	connCb;
	VOID *connCbCtx;

	GSN_WDD_CONNECT_NOTIF_CB_T	wpsConnCb;/*Used by supplicant*/
	VOID *wpsConnCbCtx;

	GSN_WDD_DISCONNECT_NOTIF_CB_T disconnCb;
	VOID *disconnCbCtx;

	GSN_WDD_SCAN_NOTIF_CB_T scanCb;
	VOID *scanCbCtx;

	GSN_WDD_CAL_NOTIF_CB_T calRunRespCb;
	VOID *calRunRespCbCtx;
}GSN_WDD_NOTIF_CB_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Security IE (Information Element) information
 * 	This defines the Security IE information. This information is extracted from the MAC frame during scan 
 * and connect process and stored  for the usage of WLAN/WPA suppicant
 ******************************************************************************/
typedef struct GSN_WDD_SEC_IE_INFO
{	
    UINT8 	dot11authtype;  	/**< GSN_WIF_WLAN_DOT11_AUTH_T. Used for WEP */
    UINT8 	authtype;       	/**< GSN_WIF_WLAN_AUTH_T */
    UINT8 	pairwiseCrypto; 	/**< GSN_WIF_WLAN_CRYPTO_T */
    UINT8 	groupCrypto;    	/**< GSN_WIF_WLAN_CRYPTO_T */
	UINT8 	infoElement[32];	/**< RSN/WPA IE */
	UINT8 	infoElementLen;
}GSN_WDD_SEC_IE_INFO_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief MIC Fail Countermeasure Info.
 *
 *     This structure defines the MIC Failure Countermeasure information that
 *     can be stored in NVRAM to handle MIC failure countermeasures across
 *     standby cycles.
 ******************************************************************************/
typedef struct GSN_WDD_MIC_FAIL_INFO
{
    UINT32  micFailCounterMeasureEndTime    : 31; /**< This uses TSYNC timer 
                                                       value wherein 2^25 cycles
                                                       is 1s. So we just need 
                                                       to store the most 
                                                       significant 31 bits to 
                                                       keep track of seconds. */
    UINT32  micFailCounterMeasureOn         : 1;  /**< If 1, then counter 
                                                       measure is ON and hence 
                                                       association should not be
                                                       allowed. */
    
} GSN_WDD_MIC_FAIL_INFO_T;

typedef enum GSN_WDD_PERSIST_INFP_VALIDITY_FLAG
{
	GSN_WDD_PRST_INFO_VALDTY_FLAG_WPAIF_IFO = BIT(0),
}GSN_WDD_PERSIST_INFP_VALIDITY_FLAG_T;
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Persistent info required by WDD.
 *     This structure defines persistent info needed by WDD and need
 *     to be passed in Init function. Ideally this info should be stored by app
 *     in persistent storage like NVRAM or flash, but if the system does not
 *     go to standby and if app not have persistent storage, it could store this
 *     in RAM as well but with loss of some functionality if a reset happens
 *     and this info is lost.
 ******************************************************************************/
typedef struct GSN_WDD_PERSIST_INFO
{
	UINT8					validityFlag;
    GSN_WDD_MIC_FAIL_INFO_T micFailInfo; /**< pointer to MIC Fail 
                                                   information; this should be
                                                   pointer to MIC fail
                                                   information in non-volatile
                                                   memory like NVRAM so that MIC
                                                   failure can be tracked across
                                                   standby cycles and MIC failure
                                                   countermeasures can be
                                                   initiated */
                                               
    GSN_WDD_SEC_GKU_DATA_T groupKeyData;      /**< Pointer to GKU handling 
                                                   information used to
                                                   initialze supplicant for
                                                   handling GKUs; this should 
                                                   be pointer to GKU information
                                                   in non-volatile memory like
                                                   NVRAM so that GKUs can be
                                                   handled across standby cycles
                                                   without disassociating and
                                                   associating again */
	GSN_WPAIF_BASIC_CFG_T	wpaIfBsicCfg;

    UINT8 lastRssi;	
	UINT8						rxActiveReqCnt;
	UINT8						rxPSPollReqCnt;
	UINT8 						rxPSPollCfgSetFlag;
	UINT8 						rxIeeePSPollCfgSetFlag;
	UINT8 						rxIeeePSPollReqCnt;
	UINT8 						lastPsStateReqsted;
	GSN_WIF_WLAN_STA_PS_CFG_T	rxIeeePSCfg;
	GSN_WLAN_MAC_SSID_T         conctedSsid;/* For the use of supplicant*/
	GSN_WLAN_MAC_ADDR_T         conctedBssid;/* For the use of supplicant*/
	UINT32 						psCfgBeaconWaitDuration; /*PS Poll config - beacon wait duation in ms*/
    UINT8                       multicastRxEnCnt;
} GSN_WDD_PERSIST_INFO_T;

typedef struct GSN_WDD_RADIO_MODE_INFO
{
	UINT8						rxActiveReqCnt;
	UINT8						rxPSPollReqCnt;
	UINT8 						rxPSPollCfgSetFlag;
	UINT8 						rxIeeePSPollCfgSetFlag;
	UINT8 						rxIeeePSPollReqCnt;
	UINT8 						lastPsStateReqsted;
	GSN_WIF_WLAN_STA_PS_CFG_T	rxIeeePSCfg;
}GSN_WDD_RADIO_MODE_INFO_T;

typedef struct GSN_WDD_MSG_HANDLER
{
	GSN_OSAL_THREAD_TCB_T   tcb;			/**< Message handler task control block*/
	GSN_OSAL_QUEUE_T 		msgQueue;		/**< message queue handle */
	UINT32 					sysQualTskID;	/**< sys qual task ID for the Message handler task*/
	UINT32 					sysQualTicks;	/**< sys qual ticks */
}GSN_WDD_MSG_HANDLER_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd initialisation parameter structure.
 *
 ******************************************************************************/    
typedef struct GSN_WDD_INIT_PARAM
{	
	GSN_WIF_WLAN_NW_TYPE_T 		wlanNwType;	/**<Type of wlan Nw - STA/AP/IBSS*/ 
	GSN_WDD_MSG_HANDLER_T *		pWddMsgHdlr;/**< wdd module message handler  Handle*/
	GSN_WIF_CTX_T *				pWifCtx; 	/**< Pointer to the Wif conetxt */
	/**<[TO DO] Pointer to the Power Management  conetxt */
		
	GSN_WDD_PERSIST_INFO_T *	pWddPersistInfo; 	/**< Place Holder for Persistance Info
														to be used across standby Cycles*/
	GSN_WDD_STATS_T * 			pStats;
    GSN_WPAIF_PMK_CACHE_ENTRY * pPmkCache;
    UINT32                      pmkCacheSize;
}GSN_WDD_INIT_PARAM_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd initialisation parameter structure.
 *
 ******************************************************************************/    
typedef struct GSN_WDD_REINIT_PARAM
{	
	GSN_WIF_WLAN_NW_TYPE_T 		wlanNwType;	/**<Type of wlan Nw - STA/AP/IBSS*/ 	
}GSN_WDD_REINIT_PARAM_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd Message Handler initialisation parameter structure.
 *
 ******************************************************************************/    
typedef struct GSN_WDD_MSG_HDLR_INIT_PARAM
{	
	UINT32*		pStack;				/**< pointer to message handler task stack*/ 
	UINT32 		stackSize; 			/**< stack size */
	UINT32 		priority; 			/**< priority*/
	UINT8* 		msgQueueBuff;		/**< pointer to message queue buffer*/
	UINT32 		msgQueueBuffSize; 	/**< messsage queue buffer size*/
	UINT8  		msgSize;			/**< message size*/	
	UINT32 		sysQualTskID;		/**< task ID for the message handler task */
	UINT32 		sysQualTicks;		/**< Sys qual ticks */
}GSN_WDD_MSG_HDLR_INIT_PARAM_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief  Wpa Supplicant initialisation parameter structure.
 *
 ******************************************************************************/    
typedef struct GSN_WDD_WPA_SUP_INIT_PARAM
{
	GSN_WDD_MSG_HANDLER_T *		pWddMsgHdlr; 			/**< wdd module message handler  Handle*/
	UINT32 *					randomNumSeed; 			/**< Random number generated will be stored in
															this array. This stored seed needs to be 
															used in case of standby/wake up 
															cycles*/
}GSN_WDD_WPA_SUP_INIT_PARAM_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief STA Specific WLAN Configuration definition
 *
 *	 
 ******************************************************************************/
typedef struct GSN_WDD_STA_SPCIFIC_CFG
{	
    UINT16 listenInterval;	/**< Listen interval to be set in association request */
}GSN_WDD_STA_SPCIFIC_CFG_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief AP Specific WLAN configuration definition
 *
 *	 
 ******************************************************************************/
typedef struct GSN_WDD_AP_SPCIFIC_CFG
{
	
    UINT8 		hiddenSsid;			/**< indicates if the SSID should be masked out in beacons */
    UINT16 		beaconInterval;		/**< Beacon interval */	
    UINT8 		dtimPeriod;			/**< DTIM period */
}GSN_WDD_AP_SPCIFIC_CFG_T;


/*******************************************************************************
 * @ingroup GsnWdd
 * @brief WDD wlan configuration
 *
 *	 This defines the wlan configuration. These configurations are used during the association. These 
 * configurations MUST be set with proper values before associating to a WLAN network .
 * @note
 * 	check  GsnWdd_WlanConfigDefaultInit(). Call this function before requesting to connect for setting 
 * some of the parameters to default values.
 ******************************************************************************/
typedef struct GSN_WDD_WLAN_CFG
{
	/**< Commom parameters*/
    GSN_WLAN_MAC_SSID_T  	ssid;		/**< SSID to connect to. */
    GSN_WLAN_MAC_ADDR_T  	bssid;		/**< BSSID to connect to. */
	
    UINT8 					channel[GSN_WDD_WLAN_MAX_CHNLS+1]; /**< List of channels to search 
    													SSID/BSSID on. Channels in list must be 
    													contiguous. Channel list ends at first entry in 
    													list containing zero. */
	/**< STA/AP/SECURITY..... specific parameters*/
	GSN_WDD_STA_SPCIFIC_CFG_T 	staSpecificCfg; 	/**< STA specific parameters */
	GSN_WDD_AP_SPCIFIC_CFG_T 	apSpecificCfg; 		/**< AP specific parameters */
	GSN_WDD_SECURITY_CONFIG_T	securityCfg; 		/**< Security configuration */

} GSN_WDD_WLAN_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Scan parameters.
 *	This structure defines the scan configuration used for scanning the WLAN.
 *The scan configuration is filled up and passed to scan API for scanning one or more channels. 
 ******************************************************************************/
typedef struct GSN_WDD_SCAN_PARAMS
{
	UINT8 					flags;
    UINT8					scanType;	/**< GSN_MAC_SCAN_TYPE_T */
    GSN_WLAN_MAC_SSID_T		ssid;		/**< SSID to scan. This can be set to NULL string if
                                  				broadcast SSID is desired. */
    GSN_WLAN_MAC_ADDR_T		bssid;		/**< BSSID to scan. */
												
    UINT8       			channel[GSN_WDD_WLAN_MAX_CHNLS+1]; /**< List of channels to
                                                        search SSID/BSSID on. Channels in list must 
                                                        be contiguous. Channel list ends at first entry
                                                        in list containing zero. */
} GSN_WDD_SCAN_PARAMS_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief  Scan Entry definition.
 *	This defines the Scan entry data structure. One scan entry per wlan naw found is given to the APP by 
 * WLAN during scan process.
 ******************************************************************************/
typedef GSN_WIF_WLAN_SCAN_IND_T GSN_WDD_SCAN_ENTRY_T;

/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Scan information data structure
 *    This defines the Scan Information data structure. This structure holds information related to scan
 * process like the scan parameters provided by the user application, channel being scanned presently etc. 
 ******************************************************************************/
typedef struct GSN_WDD_SCAN_INFO
{
	GSN_WDD_SCAN_PARAMS_T 	params;			/*Scan process will span across two threads context. 
												Need to hold the scan parameters across two 
												threads context*/
										
	UINT8 *					usrRsltBuff; 	/**< pointer to user supplied buffer*/
	UINT16 					usrMaxRslts; 	/**< maximum number of scan results the user supplied 
													buffer can hold */
	
	UINT16 					numRsltCopied;	/**< Number of results copied to user buffer */
	UINT8 					chnlIndx; 		/**< channel index. Index to the channel to be scanned*/

	/*[ TO DO] place holder for storing a scan result for highest RSSI connect*/
	INT8 highestRssi;
}GSN_WDD_SCAN_INFO_T;

/*******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief  Connect Information structure
 *	This defines the Connect information structure. This used by WDD module to hold some information 
 * related to connect process as this process may span across multiple threads.
 ******************************************************************************/
typedef struct GSN_WDD_CONNECT_INFO
{
	GSN_WDD_CONNECT_FLAG_T 	flags;			/* Connect flags */
	UINT8 					channelIndx;	/**< index in to the channel list*/
	GSN_WDD_SEC_IE_INFO_T 	secIEinfo; 		/**< Security Information */
}GSN_WDD_CONNECT_INFO_T;

typedef enum GSN_WDD_ERROR_CODE
{
	GSN_WDD_CONNECT_ERROR_AP_NOT_FOUND = BIT(0),
	GSN_WDD_CONNECT_ERROR_WLAN_FAIL_TO_CONCT = BIT(1),
	GSN_WDD_CONNECT_ERROR_WPA_AUTH_FAILURE = BIT(2),
}GSN_WDD_ERROR_CODE_T;

typedef enum GSN_WDD_ERROR_EXTRA_INFO
{
	GSN_WDD_ERROR_INFO_STA_DISCONNECTED = BIT(16),/**< STA sent deauth*/
	GSN_WDD_ERROR_INFO_AP_DEAUTH = BIT(17),/**< AP deauth/disassosiation*/
}GSN_WDD_ERROR_EXTRA_INFO_T;

typedef struct GSN_WDD_ERROR
{
	UINT32 errorCode;/**< 0-15 -> GSN_WDD_ERROR_CODE_T 16-31*/
	UINT32 deauthReason;
	const INT8 *reasonString;
}GSN_WDD_ERROR_T;

/* Note : to be removed during next ROMing*/
typedef struct GSN_WDD_WLAN_CFG_EXTN
{
    UINT16          inactivityTimeoutInSec; /**< valid in AP mode only.
                                             if connected STA is inactive
                                             for this many seconds, AP will
                                             de-auth that STA. */
}GSN_WDD_WLAN_CFG_EXTN_T;

typedef struct
{
	UINT32                      enableAssocConf;
	UINT32                      assocTimeout;
}	GSN_WDD_ASSOC_CONFIG_T;
/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wireless Device Driver object definition.
 *
 *	 
 ******************************************************************************/
typedef struct GSN_L2_DEV_WLAN
{  
    GSN_L2_DEV_T 				l2Dev;		/**< Mandatory subclass for every L2 device */	
    VOID *						l3Hndl;  	/**< L3 handle. This is passed in call backs like receive 
    												call back */
		
	GSN_WIF_WLAN_NW_TYPE_T 		wlanNwType;	/**<Type of wlan Nw - STA/AP/IBSS*/ 

	/**<Wdd module management data structures */
	GSN_WDD_MSG_HANDLER_T *		pWddMsgHdlr; 	/**< wdd module message handler  Handle. There is only 
										   			one message for all the instances of WDD context*/
	GSN_WDD_STATE_T 			state; 			/**< Holds the state of the Wdd context as defined by 
													GSN_WDD_STATE_T*/
	GSN_WDD_SCAN_STATE_T 		scanState;		/**< State of the scan procedure */

	UINT8 						assocStatus;	/**< associated / not associated */
	/**<Management of Indications and Notifications*/
	GSN_WDD_IND_CB_INFO_T 		ind;		/**<Asynchronous Indication Call back table */
	GSN_WDD_NOTIF_CB_T 			notif;		/**< Notification call back table */

	/**<Pointer to objects used by WDD module*/
	GSN_WIF_CTX_T *				pWifCtx; 	/**< Pointer to the Wif conetxt */
	GSN_WDD_WPAIF_HANDLE_T 		wpaIfHndl;	/**< Pointer to WPA supplicant Interface context. 
													This returned by the GsnWpaIf_Init() API 
													provided by WPA IF module*/

	/**< Wdd module information place holders*/
	GSN_WLAN_MAC_ADDR_T 		macAddr; 		/**< MAC address of the interface*/
	GSN_WDD_WLAN_CFG_T 			wlanConfig; 	/**< wlan cofigurations used during association*/
	GSN_WDD_PERSIST_INFO_T *	pPersistInfo; 	/**< Persistance Information to be used across 
														standby cycles*/
	GSN_WDD_CONNECT_INFO_T 		conectInfo; 	/**< information used during connect process*/ 
	GSN_WDD_SCAN_INFO_T 		scanInfo; 		/**< information used/generated during scan process*/
											
	/**<Miscellaneous data structures */
	UINT8 						txPktId; 		/**< Transmitt packet ID*/
	GSN_OSAL_SEM_T				opLock;			/**< Lock for protecting critical opereations like 
														accessing counters etc*/
	GSN_OSAL_SEM_T				blockngApiEntryLock;	/**< Multiple Tasks may pend on thi ssemaphore*/
	GSN_OSAL_SEM_T				blockngApiExitLock;		/**< Only a single task pend on this at a time */
	VOID *						blockngApiUserBuf;	
	UINT32						blockngApiUserBufSize;
	GSN_STATUS					blockngApiStatus;
	GSN_WDD_SCAN_ENTRY_T		scanEntry;		/**< For, a) storing the scan entry in case of special 
													  connect/scan like highest RSSI e.t.c
													  b) used to store the mac frame while connecting 
													  with security. The mac frame is stored just before 
													  giving the connect request. Whn the Connect
													  Ind conmes, the same frame is given to supplicant.
													  	*/
	GSN_WDD_STATS_T *			pStats;	
													  
	/**< TKIP MIC failure countermeasures info */
	GSN_SOFT_TMR_T micFailCntrMsrTmr;				
	GSN_SOFT_TMR_HANDLE_T micFailCntrMsrTmrHndl; 	
	UINT8 micFailCount;  							
	UINT8 micFailKeyType;  	
	GSN_WDD_ERROR_T	errorInfo;
	UINT8 radioTurnedON;
	GSN_WDD_WLAN_CFG_EXTN_T		wlanConfigExtn;
	UINT32   					groupKeyUpdateTime;
	GSN_WDD_ASSOC_CONFIG_T      assocConfig;
    GSN_WPAIF_PMK_CACHE_ENTRY * pPmkCache;
    GSN_WDD_SEC_EAP_FAST_PAC_T  eapFastPac;/**/
    UINT8                       eapFastPacGetDisable;
} GSN_L2_DEV_WLAN_T;

typedef GSN_L2_DEV_WLAN_T GSN_WDD_CTX_T;

typedef enum GSN_WDD_STA_PS_WAKEUP
{
    GSN_WDD_STA_PS_WAKEUP_DTIM=1,
    GSN_WDD_STA_PS_WAKEUP_LISTEN_INTERVAL,
    GSN_WDD_STA_PS_WAKEUP_CUSTOM
}GSN_WDD_STA_PS_WAKEUP_T;

typedef enum GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE
{
    GSN_WDD_STA_PS_DATA_RX_TYPE_PS_POLL=1,
    GSN_WDD_STA_PS_DATA_RX_TYPE_SWITCH_TO_ACTIVE
}GSN_WDD_STA_PS_DATA_RX_TYPE_T;


/**
Wlan statistics types
*/
#define GSN_WDD_WLAN_STAT_TYPE_TX	GSN_WIF_WLAN_STAT_TYPE_TX
#define GSN_WDD_WLAN_STAT_TYPE_RX	GSN_WIF_WLAN_STAT_TYPE_RX
/*
Frame Aggregation
*/

#define GSN_WDD_ADD_BA	1
#define GSN_WDD_DEL_BA	2

#define GSN_WDD_AMSDU_START 	1		
#define GSN_WDD_AMSDU_END		2	

#define GSN_WDD_AMPDU_START 	1		
#define GSN_WDD_AMPDU_END 		2		

typedef struct GSN_WDD_BLOCKACK_REQ
{
    UINT8 ra[GSN_WLAN_MAC_ADDR_LEN];/**< Receiver's mac address. if the node is station, fill it with BSSID.
										when the node is AP, set the appropriate STA MAC address*/
    UINT8 tid;    /**< tid for which the block ack session needs to be enabled */
	UINT8 action; /**< add/delete Block ack, GSN_WDD_ADD_BA/ GSN_WDD_DEL_BA */										
} GSN_WDD_BLOCKACK_REQ_T;

typedef struct GSN_WDD_AMSDU_REQ
{
    UINT8 ra[GSN_WLAN_MAC_ADDR_LEN];/**< Receiver's mac address. if the node is station, fill it with BSSID.
										when the node is AP, set the appropriate STA MAC address*/
    UINT8 tid;    /**< tid for which the block ack session needs to be enabled */
	UINT8 action; /**< add/delete Block ack, GSN_WDD_AMSDU_START/ GSN_WDD_AMSDU_END */										
} GSN_WDD_AMSDU_REQ_T;

typedef struct GSN_WDD_AMPDU_REQ
{
    UINT8 ra[GSN_WLAN_MAC_ADDR_LEN];/**< Receiver's mac address. if the node is station, fill it with BSSID.
										when the node is AP, set the appropriate STA MAC address*/
    UINT8 tid;    /**< tid for which the block ack session needs to be enabled */
	UINT8 action; /**< add/delete Block ack, GSN_WDD_AMPDU_START/ GSN_WDD_AMPDU_END */										
} GSN_WDD_AMPDU_REQ_T;


/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Get Pionter to WLAN configuration.
 *
 *    This function returns the pointer to WLAN configuration of given WDD instance.
 * @param pWdd - IN pointer to WDD object.
 * @return pointer to WLAN configuration of WDD instance.
 * @note
 *    The WLAN configuration contains the wlan association related information. Before requesting for
 * Association, the user application has to initialise some of the required parameters (like ssid, channels 
 * to be scanned etcetera) with  proper values. After the Association is done, the wdd module 
 * updates some values  like  the computed PSK, encryptionType, authentication type, BSSID etcetera. 
 * These updated values can be then read by higher layers (User application) for any further usage 
 * (like store in NVDS/ NVRAM etcetera)
 ******************************************************************************/
PUBLIC INLINE GSN_WDD_WLAN_CFG_T *
GsnWdd_WlanConfigPtrGet(GSN_WDD_CTX_T *pWdd)
{
    return (&pWdd->wlanConfig);
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Set WLAN configuration.
 * 		This function set the wlan configuration. This needs to be called before calling connect API. 
 * This shall be done if the wlan configuration structure in user application space is different than the one 
 * in wdd context. If the wlan configuration structure in wdd context is  accessed directly using  
 * GsnWdd_WlanConfigPtrGet() and configured, this API shall not be called.
 ******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_WlanConfigSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_CFG_T *pWlanConfig)
{
    if(pWlanConfig != &pWdd->wlanConfig)
	{
		memcpy((INT8 *)&pWdd->wlanConfig, (INT8 *)pWlanConfig, sizeof(GSN_WDD_WLAN_CFG_T));
	}
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Connect indication  CB register.
 *		Register Connect Indication call back. This call back will be called when a station connect to the 
 * node in AP mode
 *******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_StaJoinedIndCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_STA_JOINED_IND_CB_T cb, VOID *ctx)
{
	pWdd->ind.staJoinedIndCb = cb;
	pWdd->ind.staJoinedIndCbCtx = ctx;
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Connect indication  CB register.
 *		Register Connect Indication call back. This call back will be called when a station connect to the 
 * node in AP mode
 *******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_StaDisconctedCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_STA_DISCONCTED_IND_CB_T cb, 
									    VOID *ctx)
{
	pWdd->ind.staDisconctedIndCb = cb;
	pWdd->ind.staDisconctedIndCbCtx = ctx;
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Disassociation indication  CB register.
 *		Register Disassociation Indication call back. This call back will be called when dissociation happen 
 * asychronously( with out issueing the disconnect request)
 *******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_DisassocIndCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_DISASSOC_IND_CB_T cb, VOID *ctx)
{
	pWdd->ind.disassocIndCb= cb;
	pWdd->ind.disassocIndCbCtx = ctx;
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD sync loss indication  CB register.
 *		Register Sync Loss Indication call back. This call back will be called when Syncloss is detected
 *******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_BeaconMissCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_BEACON_MISS_IND_CB_T cb, VOID *ctx)
{
	pWdd->ind.beaconMissIndCb = cb;
	pWdd->ind.beaconMissIndCbCtx = ctx;
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD battery indication  CB register.
 *		Register Battery level Indication call back. This call back will be called when battery level
 * is reported by the wlan.
 *******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_BattLevlIndCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_BATT_LEVL_IND_CB_T cb, VOID *ctx)
{
	pWdd->ind.battLevlIndCb = cb;
	pWdd->ind.battLevlIndCbCtx = ctx;
}

/**
*******************************************************************************
* @ingroup GsnWdd
* @brief GSN WDD battery indication  CB register.
*		Register Battery level Indication call back. This call back will be called when battery level
* is reported by the wlan.
*******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_FrameTxFailIndCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_FRAME_TXFAIL__IND_CB_T cb, VOID *ctx)
{
	pWdd->ind.frameTxFailIndCb = cb;
	pWdd->ind.frameTxFailIndCbCtx = ctx;
}

/**
*******************************************************************************
* @ingroup GsnWdd
* @brief GSN WDD battery indication  CB register.
*		Register Battery level Indication call back. This call back will be called when battery level
* is reported by the wlan.
*******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_DabDoneIndCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_DAB_DONE_IND_CB_T	cb, VOID *ctx)
{
	pWdd->ind.dabDoneIndCb= cb;
	pWdd->ind.dabDoneIndCbCtx= ctx;
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Disassociation indication  CB register.
 *		Register Disassociation Indication call back. This call back will be called when dissociation happen 
 * asychronously( with out issueing the disconnect request)
 *******************************************************************************/
PUBLIC INLINE VOID
GsnWdd_DataIndCbReg(GSN_WDD_CTX_T *pWdd, GSN_WDD_DATA_IND_CB_T cb, VOID *ctx)
{
	pWdd->ind.dataIndCb= cb;
	pWdd->ind.dataIndCbCtx = ctx;
}

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Initialisation of given WDD instance.
 *
 *    This function performs initialization of given WDD instance. It initializes the
 *    WDD object to a known state.
 * @param pWdd - IN pointer to WDD object.
 * @param pInitParam - IN pointer to structure of type GSN_WDD_INIT_PARAM_T.
 * @param flags - IN Init flags. This is one or more flags defined in GSN_WDD_INIT_FLAG_T being ORed
 * @return GSN_SUCCESS Operation successful. GSN_FAILURE Initialization failed.
 * @note
 *    This function must be called as part of interface initialization before doing 
 *    any WDD operation.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnWdd_Init(GSN_WDD_CTX_T *pWdd, GSN_WDD_INIT_PARAM_T *pInitParam, GSN_WDD_INIT_FLAG_T flags);

PUBLIC GSN_STATUS
GsnWdd_Reinit(GSN_WDD_CTX_T *pWdd, GSN_WDD_REINIT_PARAM_T *pInitParam);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Initialisation of WDD message handler.
 *
 *    This function performs initialization of WDD message handler. 
 * @param pWddMsgHdlr - IN pointer to WDD Message Handler
 * @param pParam - IN pointer to structure of type GSN_WDD_MSG_HDLR_INIT_PARAM_T.
 * @note
 *    This function must be called as part of system initialization.before doing 
 * any WDD operation. Although multiple instances of WDD can exist, only one message handler is 
 * present system void.
 ******************************************************************************/
PUBLIC VOID
GsnWdd_MsgHdlrInit(GSN_WDD_MSG_HANDLER_T *pWddMsgHdlr, GSN_WDD_MSG_HDLR_INIT_PARAM_T *pParam);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Function for initializing WLAN config with default values.
 *
 *    This API is called to initialize the WLAN config with default values prior
 *    to preparing the full WLAN config for invoking connect API.
 * @param pWlanConfig - IN Pointer to wlan config to set defaults into.                    
 * @note
 *    This function sets only some of the fields of WLAN config, not all.
 ******************************************************************************/
PUBLIC VOID
GsnWdd_WlanConfigDefaultInit(GSN_WDD_WLAN_CFG_T *pWlanConfig);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief	Send a frame
 * This will send the given frmae over  the wlan Nw
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnWdd_Send(GSN_WDD_CTX_T *pWdd, VOID *data, UINT32 dataLen);
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Notify WDD module
 * This function is used to ntify anm event to the WDD task
 ******************************************************************************/
PUBLIC VOID
GsnWdd_Notify(VOID *pCtx, GSN_WDD_EVENT_T event);
/**
 *******************************************************************************
 * @brief WLAN Connect.
 *
 *    This function connects to WLAN with the given configuration. Once done, 
 *    it calls the user provided callback. The flags can be used to control the
 *    behavior and operation of this API.
 * @param pWdd - IN pointer to WDD object.
 * @param flags - IN One or more connect flags (GSN_WDD_CONNECT_FLAG_T) ORed.
 * @param pWlanCfg - IN WLAN configuration
 * @param pScanEntry - IN Pointer to scan result if WLAN scan was performed earlier  and that will be used 
 *						for WLAN connection. Connection using a scan entry is possible only if the scan 
 *						entry was obtained by performing a scan and that was the last
 *                      scan and no other scan operation was performed after that.
 *                      This restriction exists because the WLAN MAC stores the
 *                      scan entries and can connect only to a WLAN for which it
 *                      has a scan entry in its database.
 * @param notifyCb - IN Function that will be called to indicate the result.
 * @param notifyCtx - IN User context that will be passed back in callback.
 *
 * @return GSN_SUCCESS Connection successful.
 * @return GSN_WDD_BUSY Another request is already being handled.
 * @return GSN_FAILURE Operation failed.
 * @return GSN_OPERATION_IN_PROGRESS Operation in progress. Callback function
                 will be called to indicate the result.
 * @note
 *    If this function returns anything other than GSN_OPERATION_IN_PROGRESS,
 *    then the API execution is complete and callback will not be called. If
 *    GSN_OPERATION_IN_PROGRESS is returned, then the callback will be called
 *    after the operation is complete to indicate the final result.
 * @note
 *    If the WLAN connection already exists and WLAN connection is again 
 *    requested then the connect will fail because the WLAN MAC disassociates if
 *    a association request is given when the association already exists. The
 *    association state must be maintained by the user and used to manage this.
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnWdd_Connect(GSN_WDD_CTX_T *pWdd,
                  		GSN_WDD_CONNECT_FLAG_T flags,
                  		GSN_WDD_WLAN_CFG_T *pWlanCfg,
                  		GSN_WDD_SCAN_ENTRY_T *pScanEntry,
                  		GSN_WDD_CONNECT_NOTIF_CB_T notifyCb,
                  		VOID *notifyCtx);
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief WLAN disconnect.
 *
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnWdd_Disconnect(GSN_WDD_CTX_T *pWdd,
						   UINT16 disconResonCode,
                           GSN_WDD_DISCONNECT_NOTIF_CB_T notifyCb,
                           VOID *notifyCtx);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Get physical address of the L2 interface
 *
 *    This API is called to get the physical address of the given L2 interface.
 * @param pWdd - IN Pointer to Wdd object    
 * @param macAddr - OUT Physical address.
 ******************************************************************************/
PUBLIC VOID
GsnWdd_PhyAddrGet(GSN_WDD_CTX_T *pWdd, INT8 *macAddr);
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Set physical address of the L2 interface
 *	This API is called to set the physical address of the given L2 interface.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnWdd_PhyAddrSet(GSN_WDD_CTX_T *pWdd, INT8 *macAddr, BOOL updateWfw);

PUBLIC BOOL
GsnWdd_AssocStatusGet(GSN_WDD_CTX_T *pWdd);

PUBLIC BOOL
GsnWdd_AssocStatusSet(GSN_WDD_CTX_T *pWdd);

PUBLIC VOID
GsnWdd_WpaSupplicantInit(GSN_WDD_WPA_SUP_INIT_PARAM_T *pParam);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Set Group key
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnWdd_SetGroupKey( GSN_WDD_CTX_T *pWdd, UINT8 keyIndex, UINT8 algo, 
							  UINT8	authRole, UINT8 keyLen, INT8 *pKey, ULONG64 rsc);

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Set Pairwise key
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnWdd_SetPairKey( GSN_WDD_CTX_T *pWdd, UINT8 keyIndex, UINT8 algo, UINT8 authRole, 
						   UINT8 keyLen, UINT8 *pKey, ULONG64 rsc, UINT8 *pStaAddr);

PUBLIC GSN_STATUS
GsnWdd_WpsScan(GSN_WDD_CTX_T *pWdd,
   	                     GSN_WDD_SCAN_PARAMS_T *scanParams,
   	                     INT8 *rsltBuff,
   	                     UINT32 rsltBuffLen,
   	                     GSN_WDD_SCAN_NOTIF_CB_T notifyCb,
   	                     VOID *notifyCtxt);

PUBLIC GSN_STATUS
GsnWdd_WpsConnect(GSN_WDD_CTX_T *pWdd,
                  		GSN_WDD_CONNECT_FLAG_T flags,                  		
                  		GSN_WDD_SCAN_ENTRY_T *pScanEntry,
                  		GSN_WDD_CONNECT_NOTIF_CB_T notifyCb,
                  		VOID *notifyCtx);


PUBLIC GSN_STATUS
GsnWdd_ProbeReqPropIeSet( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, 
                                 UINT32 ieLength );

PUBLIC GSN_STATUS
GsnWdd_AssocReqPropIeSet( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, 
                                 UINT32 ieLength );

PUBLIC GSN_STATUS
GsnWdd_ProbeRspPropIeSet( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, UINT32 ieLength );

PUBLIC GSN_STATUS
GsnWdd_BeaconPropIeSet( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, UINT32 ieLength );

PUBLIC GSN_STATUS 
GsnWdd_RfTestModeStart(GSN_WDD_CTX_T *pWdd);

PUBLIC GSN_STATUS 
GsnWdd_RfTestModeStop(GSN_WDD_CTX_T *pWdd);

PUBLIC GSN_STATUS 
GsnWdd_RfTestTxStart(GSN_WDD_CTX_T *pWdd, GSN_WDD_RFTEST_TX_START_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWdd_RfTestTx99Start(GSN_WDD_CTX_T *pWdd, 
										GSN_WIF_API_WLAN_RF_TEST_TX99_START_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWdd_RfTestTx100Start(GSN_WDD_CTX_T *pWdd, 
										GSN_WIF_API_WLAN_RF_TEST_TX100_START_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWdd_RfTestTxStop(GSN_WDD_CTX_T *pWdd);

PUBLIC GSN_STATUS 
GsnWdd_RfTestCarrierWaveStart(GSN_WDD_CTX_T *pWdd,
										  GSN_WIF_API_WLAN_RF_TEST_CARRIER_WAVE_START_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWdd_RfTestRxStart(GSN_WDD_CTX_T *pWdd, GSN_WIF_API_WLAN_RF_TEST_RX_START_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWdd_RfTestRxStop(GSN_WDD_CTX_T *pWdd, GSN_WLAN_RF_TEST_RX_STATS_T *rxStats);

PUBLIC GSN_STATUS
GsnWdd_ScanParamSet(GSN_WDD_CTX_T *pWdd, UINT16 minActivScnTime, UINT16 maxActivScnTime,
								UINT16 passiveScnTime);

PUBLIC GSN_STATUS
GsnWdd_BeaconMissThresholdSet(GSN_WDD_CTX_T *pWdd, UINT32 thresholdTime,
											UINT32 thresholdNo);

PUBLIC GSN_STATUS 
GsnWdd_UAMStart(GSN_WDD_CTX_T *pWdd, UINT32 ifNum, GSN_WDD_UAM_START_RESP_T *pResp);

PUBLIC GSN_STATUS 
GsnWdd_UAMStop(GSN_WDD_CTX_T *pWdd, UINT32 ifNum, GSN_WDD_UAM_STOP_RESP_T *pResp);

PUBLIC GSN_STATUS 
GsnWdd_UAMDataRxConfig(GSN_WDD_CTX_T *pWdd, GSN_WDD_UAM_DRX_CONFIG_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWdd_UamDataRxStart(GSN_WDD_CTX_T *pWdd, GSN_WDD_UAM_DRX_START_PARAM *pParam, 
								GSN_WDD_UAM_DRX_START_RESP_T*pResp);

PUBLIC GSN_STATUS 
GsnWdd_UAMDataRxStop(GSN_WDD_CTX_T *pWdd, GSN_WDD_UAM_DRX_STOP_PARAM *pParam, 
								GSN_WDD_UAM_DRX_STOP_RESP_T *pResp);

PUBLIC GSN_STATUS
GsnWdd_UamDataSend(GSN_WDD_CTX_T *pWdd, GSN_WDD_UAM_DATA_HDR_T *dataHdr, VOID *data, 
							UINT32 dataLen);

PUBLIC GSN_STATUS
GsnWdd_TxPowerSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_TX_POW_SET_PARAM_T *pParam);

GSN_STATUS
GsnWdd_TxNumRetrySet(GSN_WDD_CTX_T *pWdd, UINT16 numRetries);

PUBLIC GSN_STATUS
GsnWdd_ConctedStaListGet(GSN_WDD_CTX_T *pWdd, INT8 *outBuf, UINT32 outBufSize);

PUBLIC GSN_STATUS
GsnWdd_ApPowerSaveCfgSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_AP_PS_CFG_SET_PARAM *pParam);

GSN_STATUS
GsnWdd_TxRateSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_TX_RATE_SET_PARAM_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_TxRateGet(GSN_WDD_CTX_T *pWdd, GSN_WDD_TX_RATE_GET_RESP *outBuf);

PUBLIC GSN_STATUS
GsnWdd_CalibrnRun(GSN_WDD_CTX_T *pWdd,
						   GSN_WDD_CAL_RUN_REQ_T *pCalRunReq,
                           GSN_WDD_CAL_NOTIF_CB_T notifyCb,
                           VOID *notifyCtx);

PUBLIC GSN_STATUS
GsnWdd_TkipContrMsrStart(GSN_WDD_CTX_T *pWdd);

PUBLIC GSN_STATUS
GsnWdd_TkipSeqNumGet(GSN_WDD_CTX_T *pWdd, GSN_WIF_WLAN_TKIP_COUNTER_GET_RSP_T *pResp);

PUBLIC GSN_STATUS
GsnWdd_WlanStatsGet(GSN_WDD_CTX_T *pWdd, UINT8 reset, UINT8 statType,INT8 *outBuf, UINT32 outBufSize);

PUBLIC GSN_STATUS
GsnWdd_WlanRecvFiltrSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_RECV_FILTR_SET_PARAM_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_RtsEnable(GSN_WDD_CTX_T *pWdd, GSN_WDD_RTS_ENBL_PARAM_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_BlockAckReq(GSN_WDD_CTX_T *pWdd, GSN_WDD_BLOCKACK_REQ_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_AmsduReq(GSN_WDD_CTX_T *pWdd, GSN_WDD_AMSDU_REQ_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_AmpduReq(GSN_WDD_CTX_T *pWdd, GSN_WDD_AMPDU_REQ_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_FrameTxFailCntLmitSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_FRAME_TX_FAIL_CNT_LIMIT_SET_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_Scan(GSN_WDD_CTX_T *pWdd,
	                 GSN_WDD_SCAN_PARAMS_T *scanParams,
	                 INT8 *rsltBuff,
	                 UINT32 rsltBuffLen,
	                 GSN_WDD_SCAN_NOTIF_CB_T notifyCb,
	                 VOID *notifyCtxt);

PUBLIC GSN_STATUS
GsnWdd_ScanStop(GSN_WDD_CTX_T *pWdd);

PUBLIC GSN_STATUS
GsnWdd_RSSIGet(GSN_WDD_CTX_T *pWdd, INT8 *outBuf, UINT32 outBufSize);

PUBLIC GSN_STATUS
GsnWdd_Ioctl(GSN_WDD_CTX_T *pWdd, GSN_WDD_IOCTL_CMD_T command, void *pData);

PUBLIC GSN_STATUS
GsnWdd_RadioPowerSaveCfgSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_STA_PS_CFG_SET_PARAM_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_DABindEnable(GSN_WDD_CTX_T *pWdd, UINT8 enable);

PUBLIC GSN_STATUS
GsnWdd_KeepAliveTimeOutSet(GSN_WDD_CTX_T *pWdd, UINT8 timeOut);

PUBLIC GSN_WDD_ERROR_T * 
GsnWdd_ErrorGet(GSN_WDD_CTX_T *pWdd);

PUBLIC GSN_STATUS
GsnWdd_BlockAckEnable(GSN_WDD_CTX_T *pWdd, GSN_WDD_ALLOW_BA_BITMAP_SET_PARAM * pParam);

PUBLIC GSN_STATUS
GsnWdd_UamDataSend_Patch(GSN_WDD_CTX_T *pWdd, GSN_WDD_UAM_DATA_HDR_T *dataHdr, VOID *data, 
							UINT32 dataLen, GSN_WIF_WLAN_UNASSOCIATED_DATACFM_T *pDataTxCfm);

PUBLIC GSN_STATUS
GsnWdd_RadioStateGet(GSN_WDD_CTX_T * pWdd,UINT32 * radioState);
PUBLIC GSN_STATUS 
GsnWdd_RadioModeInfoGet(GSN_WDD_CTX_T *pWdd, GSN_WDD_RADIO_MODE_INFO_T *pRadioModeInfo);
/**
 *******************************************************************************
 * INLINE functions and MACROS
 *
 *******************************************************************************/
INLINE VOID 
GsnWdd_BssidGet( GSN_WDD_CTX_T *pCtx, UINT8 *pBssid )
{
	/*[TO DO] Remove this function*/
}

PUBLIC INLINE GSN_STATUS
GsnWdd_ActiveScanTimeSet(GSN_WDD_CTX_T *pWdd, UINT16 minScanTime, UINT16 maxScanTime)
{
	return GsnWdd_ScanParamSet(pWdd, minScanTime, maxScanTime, 0);
}

PUBLIC INLINE GSN_STATUS
GsnWdd_MinActiveScanTimeSet(GSN_WDD_CTX_T *pWdd, UINT16 minScanTime)
{
	return GsnWdd_ScanParamSet(pWdd, minScanTime, 0, 0);
}

PUBLIC INLINE GSN_STATUS
GsnWdd_MaxActiveScanTimeSet(GSN_WDD_CTX_T *pWdd, UINT16 maxScanTime)
{
	return GsnWdd_ScanParamSet(pWdd, 0, maxScanTime, 0);
}

PUBLIC INLINE GSN_STATUS
GsnWdd_PassiveScanTimeSet(GSN_WDD_CTX_T *pWdd, UINT16 passiveScanTime)
{
	return GsnWdd_ScanParamSet(pWdd, 0, 0, passiveScanTime);
}

PUBLIC INLINE VOID
GsnWdd_PsCfgBeaconWaitDurSet(GSN_WDD_CTX_T *pWdd, UINT32 beaconWaitDur)
{
	pWdd->pPersistInfo->psCfgBeaconWaitDuration = beaconWaitDur;
}

PUBLIC GSN_STATUS
GsnWdd_SetAssocTimeout(GSN_WDD_CTX_T *pWdd, GSN_WDD_ASSOC_CONFIG_T *config);

PUBLIC GSN_STATUS
GsnWdd_UamCcaConfigSet(GSN_WDD_CTX_T *pWdd, UINT32 ifNum,INT8 threshold,UINT16 timeout,
                      GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_RESP_T *pResp);
/**
 *******************************************************************************
 * Some utility MACROS
 *
 *******************************************************************************/
#define GSN_WDD_BZERO(a, b) memset((INT8 *)(a), 0, (b))

inline void GSN_WDD_SSID_CPY( GSN_WLAN_MAC_SSID_T *const dstSsidPtr, 
    const GSN_WLAN_MAC_SSID_T *const srcSsidPtr )
{
    memcpy(( dstSsidPtr)->array, ( srcSsidPtr)->array, 
        ( size_t )(( srcSsidPtr)->length));
    dstSsidPtr->length = srcSsidPtr->length;
}

inline void GSN_WDD_PHY_ADDR_CPY( void *const DstAddrPtr,
    const void *const SrcAddrPtr)
{
	memcpy(DstAddrPtr, SrcAddrPtr, GSN_WLAN_MAC_ADDR_LEN);
}

INLINE VOID* GsnWdd_GetFrmPtrForConnect( GSN_WDD_CTX_T *pWdd )
{
	return &pWdd->scanEntry;
}

INLINE GSN_WDD_SECURITY_CONFIG_T* GsnWdd_GetSecCfgPtr( GSN_WDD_CTX_T *pWdd )
{
	return &pWdd->wlanConfig.securityCfg;
}


void 
GsnWdd_SetGrpKeyUpdateTime(GSN_WDD_CTX_T * pWdd,UINT32 updateTime);
PUBLIC VOID
GsnWdd_SkipSuppSrvValidation(BOOL mode);
PUBLIC GSN_STATUS
GsnWdd_PhyModeSet(GSN_WDD_CTX_T *pWdd, UINT8 phyMode);
PUBLIC VOID
GsnWdd_SkipSuppSrvValidation(BOOL mode);
PUBLIC GSN_STATUS
GsnWdd_PhyModeSet(GSN_WDD_CTX_T * pWdd,UINT8 phyMode);
#endif /* _GSN_WDD_H_ */



