/******************************************************************************
*
*               COPYRIGHT (c) 2013 GainSpan Corporation
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
* $RCSfile: gsn_zigbee_ip.h,v $
*
* Description : This file contains function and structure declaration for 
* ZigBee IP.
*****************************************************************************/

#ifndef _GSN_ZIGBEE_IP_H_
#define _GSN_ZIGBEE_IP_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* File inclusion
******************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wlrpan_driver.h
 * @brief GSN WLARPN Driver public header.
 *    This file contains the public APIs and structures of WLARPAN Driver.
 *
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWlrPAN
 * @brief 
 *
 *    
******************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
PUBLIC INT32 S2w_Printf(const char *format, ...);

//#define ZIP_DBG S2w_Printf
#define ZIP_DBG(...)

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  Node type.
 *	This defines Node type for ZigBee-IP.
 ******************************************************************************/
#define GSN_ZIP_COORDINATOR 0
#define GSN_ZIP_ROUTER      1 
#define GSN_ZIP_HOST        2

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  Event type.
 *	This defines Event type raised by ZigBee-IP module.
 ******************************************************************************/
typedef enum GSN_ZIP_EVENT
{
    GSN_ZIP_EVENT_SCAN_CFM,
    GSN_ZIP_EVENT_START_CFM,
    GSN_ZIP_EVENT_MAC_ADDR_SET_CFM,
    GSN_ZIP_EVENT_MAC_ADDR_GET_CFM
}GSN_ZIP_EVENT_T;

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  ZigBee-IP Network Name.
 *	This defines ZigBee-IP Network name.
 ******************************************************************************/
typedef struct GSN_ZIP_NWK_ID
{
    UINT8 networkIdLen;
    UINT8 networkId[17];
}GSN_ZIP_NWK_ID_T;


/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  User callback for event notification.
 *	This defines the user callback for the event notification expected fron 
 * ZigBee-IP module.
 ******************************************************************************/
typedef VOID (*GSN_ZIP_CB_T)( VOID* pAppCtx, UINT32 event, UINT8* pData, 
    UINT32 dataLen );

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  Delay process API.
 *	This defines the the prototype of the delay process API provided by the 
 * ZigBee-IP user. All the timer expire event used in ZigBee-IP calls this API
 * to process the expire in a thread context instead of processing it in timer
 * thread context.
 ******************************************************************************/
typedef VOID ( *GSN_ZIP_DELAY_PROCESS_T )( VOID *pUsrCtx );

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  Constant configuration.
 *	This defines the constant configuration needed by the ZigBee-IP. This struct 
 * can be defined as a const and passed to the ZigBee-IP module.
 ******************************************************************************/
typedef struct GSN_ZIP_CONST_CFG
{
    GSN_ZIP_DELAY_PROCESS_T  delayEventPost;
    UINT8  maxNbE; /**< Max number of Neighbour entries */
    UINT8  maxParents; /**< Max number of Parents entries */
    UINT16 maxRtE; /**< Max number of Routing entries */    
}GSN_ZIP_CONST_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  ZigBee-IP configuration information
 *	This defines the ZigBee-IP configuration details.
 ******************************************************************************/
typedef struct GSN_ZIP_CFG
{
    GSN_NW_CTX_T *pNwCtx;
    VOID *pDelayEventPostCtx;
    GSN_DOT154IF_CTX_T *pDot154ifCtx;
    GSN_WLRPAN_T *pWlrpanCtx;
    GSN_NWIF_CTX_T *pNwIf;
    UINT8 macIfNum;
    GSN_HI_CTX_T * pHiCtx;
    GSN_ZIP_CB_T cb;
    VOID *pAppCtx;
    UINT32 macAdd[2];
}GSN_ZIP_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  ZigBee-IP scan information.
 *	This defines the ZigBee-IP scan information.
 ******************************************************************************/
typedef struct GSN_ZIP_SCAN_INFO
{
    UINT8 channel;
    UINT8 ctrlFld;
    GSN_ZIP_NWK_ID_T nwkId;
}GSN_ZIP_SCAN_INFO_T;

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief  ZigBee-IP context.
 *	This defines the ZigBee-IP context. User has to provide the context to 
 * the init function of ZigBee-IP module.
 ******************************************************************************/
 typedef struct GSN_ZIP_CTX
{
    GSN_6LOWPAN_CTX_T lowpanCtx;

    GSN_RPL_T rplCtx;   
    const GSN_ZIP_CONST_CFG_T *pCstCfg;
    GSN_ZIP_CFG_T nwkCfg;
    GSN_MLE_CTX_T mle;
    VOID* pDodagCtx;
	
    
    GSN_ZIP_DELAY_PROCESS_T  delayEventPost;
    VOID *pDelayEventPostCtx;
    UINT32 delayEvent;
    
    UINT8 state;
    UINT8 mode;
    UINT16 shortAddr;
    UINT16 panId;        
    UINT16 ParentAddress;
    UINT8  LinkQuality;
    UINT8 opChannel;

    GSN_ZIP_NWK_ID_T nwkId;
    UINT8 bcnPldOptFldLen;
    UINT8* bcnPldOptField;
    UINT32 reqChannelMask; /**< Stores the channels requested by user */
    UINT32 channelSelMask; /**< Stores the shortlisted channels from the user requested channels */

    UINT32 scanIndex;
    GSN_ZIP_SCAN_INFO_T *pScanBuf;
    UINT32 numOfScanBuf;

    UINT32 macExtendedAddr[2];
    UINT8 externalReq; /**< Set to TRUE if the Set/Get request is generated by user */

    /**< Assoc Dev Address */
    UINT32 longAddr[2];
}GSN_ZIP_CTX_T;

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief Function for initializing ZigBee-IP module.
 *
 *    This API is called to initialize the ZigBee-IP module.
 * @param pZipCtx - IN Pointer to ZigBee-IP context.
 * @param pCstCfg - IN Pointer to constant configuration.                    
 * @param pCfg - IN Pointer to rest of the configuration.                    
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnZIP_Init( GSN_ZIP_CTX_T *pZipCtx, const GSN_ZIP_CONST_CFG_T *pCstCfg,
    GSN_ZIP_CFG_T *pCfg );

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief Function to handle delay processing for ZigBee-IP module.
 *
 *    This API is called to in response to GSN_ZIP_DELAY_PROCESS_T API in user
 * thread context.
 * @param pZipCtx - IN Pointer to ZigBee-IP context.                  
 * @note
 *    
 ******************************************************************************/
VOID GsnZIP_DelayHandler( GSN_ZIP_CTX_T *pZipCtx );

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief Function to handle scan request.
 *
 *    This API is called to scan ZigBee-IP netwrok.
 * @param pZipCtx - IN Pointer to ZigBee-IP context.                  
 * @param channelMask - IN List of channel to scan. The list is bitmap as per 
 * the standard 802.15.4-2006 specification.                  
 * @param scanDuration - IN scan duration. The scan duration is as per 
 * the standard 802.15.4-2006 specification.
 * @param scanBuf - IN Pointer to the buffer where the scan result will be 
 * stored. 
 * @param numOfScanBuf - IN Number of scan result can be stored inteh buffer 
 * pointed by scanBuf.  
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnZIP_Scan( GSN_ZIP_CTX_T *pZipCtx, UINT32 channelMask, 
    UINT8 scanDuration, GSN_ZIP_SCAN_INFO_T scanBuf[], UINT32 numOfScanBuf );

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief Function to handle scan request.
 *
 *    This API is called to start ZigBee-IP operation.
 * @param pZipCtx - IN Pointer to ZigBee-IP context.                  
 * @param channelMask - IN List of channel to scan. The list is bitmap as per 
 * the standard 802.15.4-2006 specification.                  
 * @param mode - IN mode of operation i.e. GSN_ZIP_COORDINATOR, GSN_ZIP_ROUTER 
 * or GSN_ZIP_HOST.
 * @param pNWKId - IN Network ID to use or to join. 
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnZIP_Start( GSN_ZIP_CTX_T *pZipCtx, UINT8 mode, UINT32 channelMask, 
    GSN_ZIP_NWK_ID_T *pNWKId );

/**
 *******************************************************************************
 * @ingroup GsnZIP
 * @brief Function to handle scan request.
 *
 *    This API is called to stop ZigBee-IP operation.
 * @param pZipCtx - IN Pointer to ZigBee-IP context.                  
 * @note
 *    
 ******************************************************************************/
VOID GsnZIP_Stop( GSN_ZIP_CTX_T *pZipCtx );

VOID GsnZip_PhyAddrGet( GSN_ZIP_CTX_T *pZipCtx, ULONG64 *pAddr );


//#define DBG_LOG_ENABLED

#ifdef DBG_LOG_ENABLED
#define DBG_LOG_SIZE 200
extern UINT8 dbgLog[DBG_LOG_SIZE];
extern UINT32 dbgLogCnt;
#define DBG_LOG(val) if(dbgLogCnt>=DBG_LOG_SIZE) dbgLogCnt= 0; dbgLog[dbgLogCnt++]=val;
#else
#define DBG_LOG(val)
#endif



#ifdef __cplusplus
}
#endif
#endif /* _GSN_ZIGBEE_IP_H_ */
