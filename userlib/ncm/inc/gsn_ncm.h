/*******************************************************************************
*
*               COPYRIGHT (c) 2011-2012 GainSpan Corporation
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
* $RCSfile: gsn_ncm.h,v $
*
* Description : This file contains nw connection manager APIs.
*******************************************************************************/

#ifndef _GSN_NCM_H_
#define _GSN_NCM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* File Inclusion
********************************************************************************/

#include "gsn_error.h"
#include "gsn_types.h"
#include "gsn_defines.h"

/**
 *******************************************************************************
 * @file gsn_ncm.h
 * @brief GSN NCM public header.
 *    This file contains the public APIs and structures of NCM module.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/

/**
 *******************************************************************************
 * @defgroup GsnNcm GSN NCM API
 *
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @}     END of Modules group include
 *****************************************************************************/

/*******************************************************************************
 * Private Macros and Functions
 ******************************************************************************/

/*******************************************************************************
 * Type Definitions
******************************************************************************/

#ifndef NCM_DFLT_HIDDENSSID_VALUE
#define NCM_DFLT_HIDDENSSID_VALUE   0
#endif
#ifndef NCM_DFLT_DTIMPERIOD_VALUE
#define NCM_DFLT_DTIMPERIOD_VALUE   3
#endif
#ifndef NCM_DFLT_INACTIVITY_TMEOUT_VALUE
#define NCM_DFLT_INACTIVITY_TMEOUT_VALUE   360
#endif
#ifndef NCM_DFLT_GRP_KEY_UPDATE_INTERVAL
#define NCM_DFLT_GRP_KEY_UPDATE_INTERVAL   3600
#endif


#ifdef S2W_NCM_ROAMING_SUPPORT
#define RSSI_LEVEL_CONSTANT_TH 	 0
#define RSSI_BELOW_LOWER_TH 	 	 1
#define RSSI_ABOVE_LOWER_TH    	 2
#define RSSI_ABOVE_HIGHER_TH   	 3

typedef enum GSN_ROAM_STATE
{
    GSN_ROAM_NOT_REQUIRED=0, 
    GSN_ROAM_INIT =   1,
    GSN_ROAM_REINIT = 2,
    GSN_ROAM_STOP=3
}GSN_ROAM_STATE_T;
/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm Roaming configuration structure.
 *******************************************************************************/
typedef struct GSN_NCM_ROAMCONFIG
{
	UINT8 roamEnable;	  /** Roaming Enable **/
	UINT8 rssiLowerTh;	  /** Lowe RSSI threshold **/
	UINT8 rssiHigherTh;	  /** Higher RSSI threshold **/
	UINT8 thresholdCrossedCnt;
	UINT8 maintainL3Con;
	UINT8 maintainL4Con;
	UINT32 rssiLevelChkInterval;	
	UINT32 scanRetryCnt;
	UINT32 scanPauseTimeMs;
}GSN_NCM_ROAMCONFIG_T;

typedef struct GSN_NCM_ROAMDATA
{
	UINT8 roamApCh;
	UINT8 roamingTriggered;	
	UINT8 rssiTrendRoamAp;
	UINT8 rssiTrendcnt;
	UINT8 lastRssi;
	UINT8 rssiStatus; 
	UINT8 scaInProgress;
	UINT8 cbPending; 
	UINT32 scanFlag;
	UINT32 roamScanRetryCount;
	GSN_ROAM_STATE_T roamState; /** Roaming state **/
	GSN_MAC_SSID_T roamAp;
	GSN_MAC_ADDR_T roamApBssID;
	GSN_WDD_SCAN_PARAMS_T scanParams;
	GSN_SOFT_TMR_T	rssiLevelChkTmr;
	GSN_SOFT_TMR_HANDLE_T  rssiLevelChkTmrHndl;
	GSN_SOFT_TMR_T roamScanPauseTmr;	
	GSN_SOFT_TMR_HANDLE_T roamScanPauseTmrHndl;
	UINT8       currentChIndex;
	UINT8       channelList[GSN_WDD_WLAN_MAX_CHNLS+1]; 
	GSN_WDD_SCAN_ENTRY_T scanUserEntryBuff[2]; 
}GSN_NCM_ROAMDATA_T;
#endif


/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief NCM states.
 *    This enum defines the different states the NCM module in.
 *    The NCM APIs transition through some or all of these states. After the API
 *    operation is complete, the API is back in init state.
 ******************************************************************************/
typedef enum GSN_NCM_CTX_STATES
{	
    GSN_NCM_STATE_NOT_INITIALISED,		/**<The NCM is not initialized */
    GSN_NCM_STATE_INITIALISED,			/**< The NCM is initialized and ready */
    GSN_NCM_STATE_L2_DISCONNECTING,		/**< The NCM has initiated the L2 disconnect with the WLAN and waiting for
											the disconnect indication from the WLAN. The disconnect is initiated
											by the NCM when
											- Sync Loss is detected */    
    GSN_NCM_STATE_L2_DISCONNECTED,		/**< The NCM has L2 disconnected. 
									       This happens 
									       - At Start
									       - The Disassociation triggered by NCM and confirmed by WLAN
									       - The Disassociation indication from the WLAN */    
	GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP,		/**< scanning known AP with previously saned MAC frame */
	GSN_NCM_STATE_L2_SCAN_KNOWN_CHNL,   /**< sacnning known channel */
    GSN_NCM_STATE_L2_SCAN_SPECIFIC_CHNL,/**< scanning specific channels */
    GSN_NCM_STATE_L2_SCAN_ALL_CHNL,     /**< Scanning All channels */    
    GSN_NCM_STATE_L2_CONNECTED,			/**< L2 Connected.  L3 is not connected yet */
    GSN_NCM_STATE_L3_CONNECTED,			/**< and L3 both are Connected */    
	GSN_NCM_STATE_IDLE,					/**< Wait/idle state*/
} GSN_NCM_CTX_STATES_T;

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm Notifications enum.
 *     This enum describes all notifications from the ncm module to applications.
 ******************************************************************************/
typedef enum GSN_NCM_NOTIF_ID
{
    GSN_NCM_NOTIF_ID_L2_CONNECTED,
    GSN_NCM_NOTIF_ID_L2_DISCONNECTED,
    GSN_NCM_NOTIF_ID_L3_CONNECTED,
    GSN_NCM_NOTIF_ID_L3_DISCONNECTED,
    GSN_NCM_NOTIF_ID_L2_CONNECT_FAIL,
    GSN_NCM_NOTIF_ID_STOP,
    GSN_NCM_NOTIF_ID_DHCP_STOP,
    GSN_NCM_NOTIF_ID_L3_RENEWSUCCESS,
    GSN_NCM_NOTIF_ID_L3_CONNECT_FAIL,
    GSN_NCM_NOTIF_ID_MAX_EVENTS
    

} GSN_NCM_NOTIF_ID_T;

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm Notifications enum.
 *     Defines mesage IDs internally used by NCM module.
 ******************************************************************************/
typedef enum GSN_NCM_MSGID
{
    GSN_NCM_CTX_MSG_ID_STOP,
    GSN_NCM_CTX_MSG_ID_L2_START,
    GSN_NCM_CTX_MSG_ID_L2_CONNECTED,
    GSN_NCM_CTX_MSG_ID_L2_CONNECT_FAIL,
    GSN_NCM_CTX_MSG_ID_L2_DISCONNECTED,
    GSN_NCM_CTX_MSG_ID_L2_SYNC_LOSS,
    GSN_NCM_CTX_MSG_ID_L2_RESTART,
    GSN_NCM_CTX_MSG_ID_L3_CONNECT,/*Used during standby wakeup*/
    GSN_NCM_CTX_MSG_ID_L3_CONNECTED,
    GSN_NCM_CTX_MSG_ID_L3_DISCONNECTED,
    GSN_NCM_CTX_MSG_ID_L2_IDLE,
#ifdef S2W_NCM_ROAMING_SUPPORT    
    GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN,
    GSN_NCM_CTX_MSG_ID_ROAM_SCANTMR_PROCESS,
    GSN_NCM_CTX_MSG_ID_ROAM_L2DISCONNECTED,   
    GSN_NCM_CTX_MSG_ID_ROAM_TRIGGER,
#endif   
    GSN_NCM_CTX_MSG_ID_DHCP_STOP,
    GSN_NCM_CTX_MSG_ID_L2_ALREADY_CONNECTED,/* NORMA BOOT handling*/
    GSN_NCM_CTX_MSG_ID_L3_RENEWSUCESS,
    GSN_NCM_CTX_MSG_ID_L3_RENEWFAILED,
    GSN_NCM_CTX_MSG_ID_MAX
} GSN_NCM_MSGID_T;

typedef struct GSN_NCM_MSG
{
    GSN_NCM_MSGID_T     msgId;

}GSN_NCM_MSG_T;


/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm provisioning config structure.
 *******************************************************************************/
typedef struct GSN_NCM_AP_CONFIG
{
    GSN_MAC_SSID_T  ssid;
    GSN_MAC_SSID_T  bssid;
    UINT8           channel;
    UINT16          beaconIntrvl;
    GSN_NWIF_IP_CONFIG_T     ipConfig;
    UINT8 gpio;
    UINT8 security_type;
}GSN_NCM_AP_CONFIG_T;


/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm config retry count structure.
 *******************************************************************************/
typedef struct GSN_NCM_RETRY_COUNTS
{
    /**< count for the known channel scan */
    UINT32 maxScanKnownChCnt;
    /**< count for the specific channel scan */
    UINT32 maxScanSpecChCnt;
    /**< count for the all channel scan */
    UINT32 maxScanAllChCnt;
    /**< count for the l3 recoonect count */
    UINT32 maxL3ConnectCnt;
}GSN_NCM_RETRY_COUNTS_T;

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm config retry period structure.
 *******************************************************************************/
typedef struct GSN_NCM_RETRY_PERIOD
{
    /**< period for the cpu wait state retry */
    UINT32 cpuWaitPeriod;
    /**< period for the known channel scan retry */
    UINT32 scanKnownChRetryIntrvl;
    /**< period for the specific channel scan retry */
    UINT32 scanSpecChRetryIntrvl;
    /**< period for the all channel scan retry */
    UINT32 scanAllChRetryIntrvl;
    /**< period for the l3 recoonect retry */
    UINT32 l3ConnectRetryIntrvl;
}GSN_NCM_RETRY_PERIOD_T;

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm configuration structure.
 *******************************************************************************/
typedef struct GSN_NCM_CONFIG
{
	GSN_WDD_WLAN_CFG_T 				wlanCfg;
	GSN_NWIF_IP_CONFIG_T			ipConfig;
	GSN_NWIF_DHCP_PARAMS_T			dhcpV4Cfg;	
	GSN_NWIF_DHCP_PARAMS_T			dhcpV6Cfg;
	GSN_NCM_RETRY_COUNTS_T  		retryCountsConfig;
	GSN_NCM_RETRY_PERIOD_T  		retryPeriodConfig;
	UINT8 							scanMode; 		/**<0-->only know ch, 1--> scan known and specific, 
													2--> scan known and all ch */
	UINT8							specificChnlList[GSN_WDD_WLAN_MAX_CHNLS+1]; 
												/**< List of specific channel to be scanned*/
	UINT8 							powersaveMode; 	/**< 0-->disable, 1--> stby , 2-->dpsleep*/
	UINT8                           regDomain;
	GSN_WDD_SCAN_ENTRY_T			KnownChnlScanEntry;
	BOOL							scanEntry;
	UINT16 							inactivityTimeoutInSec;
	UINT32                          groupKeyUpdateTime;
#ifdef S2W_NCM_ROAMING_SUPPORT 	
	GSN_NCM_ROAMCONFIG_T roamingCfgParams;	
#endif
}GSN_NCM_CONFIG_T;



/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief call back to be called for posting message to an application task. This is to indicate 
 * GsnNcm_Execute() to be called in an application task context.
 ******************************************************************************/
typedef VOID (*GSN_NCM_CTX_EXECUTE_MSG_POST_CB)(VOID *cbCtx, VOID* pNcm);

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief call back to be called for posting message to an application task.
 *
 ******************************************************************************/
typedef VOID (*GSN_NCM_CTX_NOTIF_CB)(VOID *cbCtx, VOID* pNcm, GSN_NCM_NOTIF_ID_T notifId);


/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Ncm object structure.
 *******************************************************************************/
typedef struct GSN_NCM_CTX
{	
	UINT8 					state;
	GSN_SOFT_TMR_T  		connMgrTmr;
	GSN_SOFT_TMR_HANDLE_T	connMgrTmrHndl;
	UINT8 					blockingOn;
	GSN_OSAL_QUEUE_T 		msgQueue;		/**< message queue handle */
	GSN_NCM_CTX_EXECUTE_MSG_POST_CB 	execMsgPostCb;
	VOID *					execMsgPostCbCtx;
	GSN_WDD_CTX_T *			pWdd; /**< Pointer to WDD L2 context */
	GSN_NWIF_CTX_T  * 		pNwif;
	GSN_NCM_CONFIG_T 		config;
	GSN_NCM_CTX_NOTIF_CB	notifCb;
	VOID *					notifCbCtx;
		
	UINT32 					scanKnownChCnt;
	UINT32 					scanSpecChCnt;
	UINT32 					scanAllChCnt;
	UINT32 					L3ConnectCnt;
	UINT8 					L3ConnFailed;
#ifdef GSN_NCM_AUTO_CHANNEL_SWITCH	
	UINT32					currentChannel;
#endif	
#ifdef S2W_NCM_ROAMING_SUPPORT	
	GSN_NCM_ROAMDATA_T roamingParams;
#endif    
        GSN_WDD_SCAN_ENTRY_T                    scanResults;
	UINT8 					stopInProgress;
	UINT8 					ncmStarted;
}GSN_NCM_CTX_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief mDns module init param
 *
 ******************************************************************************/
typedef struct GSN_NCM_INIT_PARAM
{	
	GSN_WDD_CTX_T *			pWdd; /**< Pointer to WDD L2 context */
	GSN_NWIF_CTX_T *		pNwif;
	UINT8* 					msgQueueBuff;	    	/**< pointer to message queue buffer*/
	UINT32 					msgQueueBuffSize;   	/**< messsage queue buffer size*/					
	GSN_NCM_CTX_EXECUTE_MSG_POST_CB 	execMsgPostCb;
	VOID *								execMsgPostCbCtx;	
	GSN_NCM_CTX_NOTIF_CB	notifCb;
	VOID *					notifCbCtx;
}GSN_NCM_INIT_PARAM_T;
typedef enum GSN_NCM_REG_DOMAIN_T
{
    GSN_NCM_REG_DOMAIN_FCC   =   0,
    GSN_NCM_REG_DOMAIN_ETSI  =   1,
    GSN_NCM_REG_DOMAIN_TELEC =   2,
} GSN_NCM_REG_DOMAIN_T;

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Initialization API for NCM module.
 *
 *    This function performs initialization of NCM module. It initializes the
 *    NCM object to a known state.
 * @param pNcm - IN pointer to NCM object.
 * @param pParam - IN pointer to the initialization parameters
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Initialization failed.
 *******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_Init(GSN_NCM_CTX_T* pNcm, GSN_NCM_INIT_PARAM_T *pParam);


/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Configuration Set API for NCM module.
 *
 *    This function performs the configuration set from the data structure
 *    provided by the caller to the NCM object.
 * @param pNcm - IN pointer to NCM object.
 * @param pConfig - IN pointer to NCM config structure.
 *
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *      None
 *******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_ConfigSet(GSN_NCM_CTX_T* pNcm,  GSN_NCM_CONFIG_T* pConfig);

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Configuration Get API for NCM module.
 *
 *    This function performs the configuration get from the NCM object
 *    to the user provided config structure.
 * @param pNcm - IN pointer to NCM object.
 * @param pConfig - IN pointer to NCM config structure.
 *
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *      None
 *******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_ConfigGet(GSN_NCM_CTX_T* pNcm,  GSN_NCM_CONFIG_T* pConfig);

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Get NCM module config structure Address.
 *
 *    This function returns pointer to ncm context configuration structure.
 *******************************************************************************/
PUBLIC GSN_NCM_CONFIG_T *
GsnNcm_ConfigPtrGet(GSN_NCM_CTX_T* pNcm);


/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Start API for NCM module.
 *
 *    This function starts the NCM module by associating to the AP which configured.
 * @param pNcm - IN pointer to NCM object.
 * @param notifCb - IN pointer to user callback function.
 * @param notifCbCtx - IN pointer to user callback context.
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *      None
 *******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_Start(GSN_NCM_CTX_T* pNcm, GSN_NCM_CTX_NOTIF_CB notifCb, VOID *notifCbCtx);

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Stop API for NCM module.
 *    This function stops the NCM module. .
 * @param pNcm - IN pointer to NCM object.
 * @param context - IN context from which it is called
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *      None
 *******************************************************************************/

PUBLIC GSN_STATUS_T
GsnNcm_Stop(GSN_NCM_CTX_T* pNcm, UINT32 context);

/**
 *******************************************************************************
 * @ingroup GsnNcm
 * @brief Execute API for NCM module.
 *
 *    This function should be called from an application Task context .
 * @param pNcm - IN pointer to NCM object.
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *      None
 *******************************************************************************/

PUBLIC VOID
GsnNcm_Execute(GSN_NCM_CTX_T* pNcm);

VOID
GsnNcm_MsgPost(GSN_NCM_CTX_T* pNcm, UINT32 msgId);

GSN_STATUS_T
GsnNcm_L2Disconnect(GSN_NCM_CTX_T* pNcm);

VOID 
GsnNcm_BeconMissIndCb(VOID * ctx,UINT32 beaconMissCnt);

VOID 
GsnNcm_DisassocIndCb(VOID * ctx,GSN_WDD_DISASSOCIATION_CB_INFO * pDisAssocInfo);

VOID 
GsnNcm_ChannelFill(GSN_WDD_CTX_T *pWdd,UINT8 *chTable,UINT8 domain);

PRIVATE VOID
GsnNcm_L2ConnectProcess(GSN_NCM_CTX_T * pNcm,UINT8 alreadyConnectedEvent);

PRIVATE VOID
GsnNcm_L2DisconnectProcess(GSN_NCM_CTX_T* pNcm);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_NCM_CTX_H_ */
