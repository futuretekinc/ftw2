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
* $RCSfile: gsn_wdd_private.h,v $
*
* Description : This file contains public definitions for WDD. WDD( Wireless
* Device Driver ) provides APIs for the wireless drivers. These APIs are scan
* request, connect request,  disconnect request, data request. 
* WDD generates events related to these request. If application has registered
* its callback function, WDD calls it whenever these events happens.
*******************************************************************************/
#ifndef _GSN_WDD_PRIVATE_H_
#define _GSN_WDD_PRIVATE_H_

/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief WDD Messages.
 *    This enum defines the messages posted to the wdd message handler
 ******************************************************************************/
typedef enum GSN_WDD_MESSAGE_TYPE
{
	GSN_WDD_MSG_TYPE_CONNECT_DONE,
    GSN_WDD_MSG_TYPE_DISCONNECT_DONE,
	GSN_WDD_MSG_TYPE_EPOL_RECEIVED,
	GSN_WDD_MSG_TYPE_WPA_TMR_TIME_OUT,
	GSN_WDD_MSG_TYPE_STA_CONNECTED,
	GSN_WDD_MSG_TYPE_STA_DIS_CONNECTED,
}GSN_WDD_MESSAGE_TYPE_T;

/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Connect request parameter
 *    This enum defines the messages posted to the wdd message handler
 ******************************************************************************/
typedef struct GSN_WDD_CONN_REQ_PARAM
{
	UINT32 						flags;
	GSN_WDD_SEC_IE_INFO_T *		pSecIeInfo;
	UINT8 * 					pMacFrame;
	UINT32 						macFrameLen;
}GSN_WDD_CONN_REQ_PARAM_T;

/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Dis connect request parameter
 *    This defines the disconnect request parameter staructure
 ******************************************************************************/
typedef struct GSN_WDD_DISCONN_REQ_PARAM
{
	UINT16 disConReasonCode;
}GSN_WDD_DISCONN_REQ_PARAM_T;
/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Device Init.
 ******************************************************************************/
VOID
GsnWdd_L2DevInit(GSN_L2_DEV_T *pL2Dev);
/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Data send request.
 *    	This function issues data send request to the WLAN . This function is accessed through L2 Dev
 * 		function pointer (l2Dev.send)
 * @param pWdd - IN pointer to WDD object.
 * @param data - IN Pointer to the frame to be send.
 * @param dataLen - IN Size of the frame.
 * @return GSN_SUCCESS Send accepted and will be sent to WLAN for Tx. Callback
 * 					will be called later.
 * @return GSN_FAILURE Send failed.
 * @note
 *    The return from this function doesn't mean that the frame has gone out of
 * the node successfuly but it just means that the WLAN MAC has queued the frame
 * for transmission and will try to transmit it when it gets an opportunity.
 ******************************************************************************/
 GSN_STATUS
 GsnWdd_L2DevSend(GSN_L2_DEV_T *pWdd, VOID *data, UINT32 dataLen);


/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Open L2 Device interface (WDD data interface).
 *
 *    This function opens the data link between L2 and L3.
 * @param pWdd - IN pointer to WDD object.
 * @param l3Hndl - IN pointer to NW L3 instance that is using WDD.
 * @param rxCb - IN receive callback function that should be called upon
 *                  receiving data frames.
 * @param txDoneCb - IN transmit done callback function that should be called 
 *                  upon transmit completion of data frames sent previously.
 * @param sendPktCopyCb - IN send packet copy call back. This function will be called when its required 
 *					to copy data from L3 buffer to L2 buffer during GsnWdd_L2DevSend.
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Initialization failed.
 * @note
 *      The L3 instance pointer is needed for WDD to pass as context in the
 *      above callback functions. This function is called by L3 before start doing any data transfer.
 ******************************************************************************/
GSN_STATUS
GsnWdd_L2DevOpen(GSN_L2_DEV_T *pWdd, VOID *l3Hndl,
            GSN_L2_DEV_RX_CB_T rxCb, GSN_L2_DEV_TX_DONE_CB_T txDoneCb,
            GSN_L2_DEV_SEND_PKT_COPY_CB sendPktCopyCb);


/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief Close WDD data interface.
 *    This function closes the data link between L2 and L3.
 * @param pWdd - IN pointer to WDD object.
 * @return GSN_SUCCESS Operation successful.
 * @return GSN_FAILURE Initialization failed.
 ******************************************************************************/
GSN_STATUS
GsnWdd_L2DevClose(GSN_L2_DEV_T *pWdd);


/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * @brief WDD IOCTL interface.
 *    This function provides the IOCTL interface for changing WDD parameters.
 * @param pWdd - IN pointer to WDD object.
 * @param cmd - IN IOCTL command.
 * @param pData - IN/OUT IOCTL command related data.
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Initialization failed.
 ******************************************************************************/
GSN_STATUS
GsnWdd_L2DevIoctl(GSN_L2_DEV_T *pWdd, UINT32 cmd, void *pData);


VOID
GsnWdd_MsgHdlrNotify(GSN_WDD_MSG_HANDLER_T *pWddMsgHdlr, GSN_WDD_MESSAGE_T *pMsg);

VOID 
GsnWdd_MsgHdlrEntryFun(UINT32 ctx);

BOOL
GsnWdd_MsgHdlr(VOID *pCtx, VOID *pWddMsg);

VOID
GsnWdd_WifWlanCtrlIndReg(GSN_WDD_CTX_T *pWdd);

VOID
GsnWdd_WifCalCtrlIndReg(GSN_WDD_CTX_T *pWdd);

VOID
GsnWdd_WifDataIndReg(GSN_WDD_CTX_T *pWdd);

BOOL
GsnWdd_IsApSecurityEnbld(GSN_WDD_CTX_T *pWdd);

GSN_STATUS
GsnWdd_WlanCtrlMsgIndCb(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
									VOID *pMsg);
GSN_STATUS
GsnWdd_CalCtrlMsgIndCb(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
									VOID *pMsg);

GSN_STATUS
GsnWdd_DataMsgIndCb( VOID *pCtx, UINT16 status, UINT8 dataClass, UINT16 msgLen, VOID *pMsg );

VOID
GsnWdd_WpaSupplicantCb(VOID *ctx);

GSN_STATUS
GsnWdd_PrivateScan(GSN_WDD_CTX_T *pWdd,
   	                     GSN_WDD_SCAN_PARAMS_T *scanParams,
   	                     INT8 *rsltBuff,
   	                     UINT32 rsltBuffLen,
   	                     GSN_WDD_SCAN_NOTIF_CB_T notifyCb,
   	                     VOID *notifyCtxt);


VOID
GsnWdd_ScanOnlyProcess(GSN_WDD_CTX_T *pWdd, UINT8 scanEndFlag, 
								   VOID *pScanInd, UINT32 scanIndLen);

BOOL
GsnWdd_ConnectPolicyCheck(GSN_WDD_CTX_T *pWdd, UINT32 scanEnd, 
									   GSN_WDD_SCAN_ENTRY_T *pScanEntry);

VOID
GsnWdd_ScanAndConctProcess(GSN_WDD_CTX_T *pWdd, UINT8 scanEndFlag, 
										  UINT8 *scanIndBuf, UINT32 bufLen);


GSN_STATUS
GsnWdd_ScanEntryCheck(GSN_WDD_CTX_T *pWdd, GSN_WDD_SCAN_ENTRY_T *pScanEntry, 
							  	  BOOL *pWlanNwFound, GSN_WDD_SEC_IE_INFO_T *pSecIEinfo,
								  GSN_WPAIF_BASIC_CFG_T *pApSecCfg);

BOOL
GsnWdd_CheckCipher(GSN_WDD_WLAN_CFG_T *pWlanCfg, GSN_WPAIF_BASIC_CFG_T *pApSecCfg, 
							 UINT8 *pairwiseCipher, UINT8 *groupCipher);

BOOL
GsnWdd_SecurityCmp(GSN_WDD_WLAN_CFG_T *pWlanCfg, GSN_MAC_FRAME_T *pMacFrame,
							UINT16 macFrameLen, GSN_WDD_SEC_IE_INFO_T *secIEinfo,
							GSN_WPAIF_BASIC_CFG_T *pApSecCfg);

BOOL
GsnWdd_SecCfgGet(GSN_WDD_WLAN_CFG_T *pWlanCfg, UINT8 *pMacFrame,			UINT16 macFrameLen, 
						  GSN_WDD_SEC_IE_INFO_T *secIEinfo, 
						  GSN_WPAIF_BASIC_CFG_T *pWpaBasicCfg);

VOID
GsnWdd_ApModeSecCfgSet(GSN_WDD_WLAN_CFG_T *pWlanCfg, 
									GSN_WPAIF_BASIC_CFG_T *pBasicSecCfg, 
						  			GSN_WDD_SEC_IE_INFO_T *secIEinfo);

GSN_STATUS_T
GsnWdd_WpsStart(GSN_WDD_CTX_T *pWdd);

GSN_WPAIF_MODE_T
GsnWdd_WpaIfModeMap(GSN_WIF_WLAN_NW_TYPE_T wlanNwType);

GSN_STATUS_T
GsnWdd_WpaIfInit(GSN_WDD_CTX_T *pWdd, GSN_WPAIF_BASIC_CFG_T *pBasicSecCfg);

GSN_STATUS_T 
GsnWdd_ConnectReq(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_CFG_T *pWlanCfg,
							GSN_WDD_CONN_REQ_PARAM_T *pParam);

GSN_STATUS_T 
GsnWdd_DisconnectReq(GSN_WDD_CTX_T *pWdd, GSN_WDD_DISCONN_REQ_PARAM_T *pParam);


GSN_STATUS_T
GsnWdd_ScanReq(GSN_WDD_CTX_T *pWdd, GSN_WDD_SCAN_PARAMS_T *pParam);

PUBLIC GSN_STATUS
GsnWdd_SetWepKey( GSN_WDD_CTX_T *pWdd, UINT8 keyIndex, UINT8 keyLen, UINT8 *pKey);

void GsnWdd_SecModeUpdate(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_CFG_T *pWlanConfig);

GSN_STATUS
GsnWdd_MulticastRxSetReq(GSN_WDD_CTX_T *pWdd, GSN_WIF_WLAN_MCST_RX_SET_T *pParam);

VOID
GsnWdd_RadioModeCountrClr(GSN_WDD_CTX_T *pWdd);

VOID
BLOCKING_API_ENTYRY(GSN_WDD_CTX_T *pWdd)			;

VOID
BLOCKING_API_EXIT(GSN_WDD_CTX_T *pWdd)			;

VOID
BLOCKING_API_UNLOCK(GSN_WDD_CTX_T *pWdd)			;

GSN_STATUS
GsnWdd_RadioModeSet(GSN_WDD_CTX_T *pWdd, GSN_WDD_RADIO_MODE_T mode, BOOL enable);

VOID
GsnWdd_PmkCacheInit(GSN_WDD_CTX_T *pWdd, 
                            GSN_WPAIF_PMK_CACHE_ENTRY * pPmkCache,
                            UINT32 pmkCacheSize);

VOID
GsnWdd_PmkCacheEntryAdd(GSN_WDD_CTX_T *pWdd, UINT8 *bssid);

GSN_WPAIF_PMK_CACHE_ENTRY *
GsnWdd_PmkCacheEntryGet(GSN_WDD_CTX_T *pWdd, UINT8 *bssid);

VOID
GsnWdd_PmkCacheEntryDel(GSN_WDD_CTX_T *pWdd, UINT8 *bssid);




/**
 *******************************************************************************
 * @internal
 * @ingroup GsnWdd
 * MACROS and INLINE functions
 ******************************************************************************/
INLINE UINT16
GsnWdd_CapabilityInfoGet(GSN_MAC_FRAME_T *framePtr)
{
	return  GsnMacUtil_ExtractCapaInfo(framePtr);
}

INLINE BOOL
GsnWdd_IsSecurityEanbled(UINT16 capabilitiesInfo)
{
	return (capabilitiesInfo & GSN_MAC_CAPA_PRIVA);
}

INLINE INT32
GsnWdd_IsKeyMgmtWpaPSK(GSN_WPAIF_BASIC_CFG_T *pSecCfg)
{
	return (pSecCfg->keyMgmt == GSN_WDD_SEC_KEY_MGMT_PSK); 
}

INLINE INT32
GsnWdd_IsKeyMgmtWpaIeee8021x(GSN_WPAIF_BASIC_CFG_T *pSecCfg)
{
	return (pSecCfg->keyMgmt == GSN_WDD_SEC_KEY_MGMT_IEEE8021X); 
}

INLINE VOID
GsnWdd_SecIEinfoSet(GSN_WDD_SEC_IE_INFO_T *secIEinfo, UINT8 authtype, 
							 UINT8 pairwiseCrypto, 
							 UINT8 groupCrypto)
{
	secIEinfo->authtype = authtype;
	secIEinfo->pairwiseCrypto = pairwiseCrypto;
	secIEinfo->groupCrypto = groupCrypto;
}

INLINE VOID
GSN_WDD_BLOCKING_API_ENTYRY(GSN_WDD_CTX_T *pWdd)			
{
	GsnOsal_SemAcquire(&pWdd->blockngApiEntryLock, GSN_OSAL_WAIT_FOREVER);
}

INLINE VOID
GSN_WDD_BLOCKING_API_EXIT(GSN_WDD_CTX_T *pWdd)			
{
	GsnOsal_SemAcquire(&pWdd->blockngApiExitLock, GSN_OSAL_WAIT_FOREVER);
	GsnOsal_SemRelease(&pWdd->blockngApiEntryLock);
}

INLINE VOID
GSN_WDD_BLOCKING_API_UNLOCK(GSN_WDD_CTX_T *pWdd)			
{
	GsnOsal_SemRelease(&pWdd->blockngApiExitLock);
}

INLINE VOID
GSN_WDD_BLOCKING_API_ERROR_EXIT(GSN_WDD_CTX_T *pWdd)			
{
	GsnOsal_SemRelease(&pWdd->blockngApiEntryLock);
}

#endif /* _GSN_WDD_H_ */



