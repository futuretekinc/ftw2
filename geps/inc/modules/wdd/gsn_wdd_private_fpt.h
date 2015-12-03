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
* $RCSfile: gsn_wdd_private_fpt.h,v $
*
* Description : Patch header file for gsn_wif.c
*****************************************************************************/
#ifndef _GSN_WDD_PRIVATE_FPT_H_
#define _GSN_WDD_PRIVATE_FPT_H_

typedef VOID
(* GsnWdd_L2DevInit_FP_T)(GSN_L2_DEV_T *pL2Dev);

extern _RPST_  GsnWdd_L2DevInit_FP_T GsnWdd_L2DevInit_FP;

typedef GSN_STATUS
(* GsnWdd_L2DevOpen_FP_T)(GSN_L2_DEV_T *pL2Dev, VOID *l3Hndl, 
					GSN_L2_DEV_RX_CB_T rxCb, 
					GSN_L2_DEV_TX_DONE_CB_T txDoneCb,
					GSN_L2_DEV_SEND_PKT_COPY_CB sendPktCopyCb);

extern _RPST_  GsnWdd_L2DevOpen_FP_T GsnWdd_L2DevOpen_FP;

typedef GSN_STATUS
(* GsnWdd_L2DevClose_FP_T)(GSN_L2_DEV_T *pL2Dev);

extern _RPST_  GsnWdd_L2DevClose_FP_T GsnWdd_L2DevClose_FP;

typedef GSN_STATUS
(* GsnWdd_L2DevSend_FP_T)(GSN_L2_DEV_T *pL2Dev, VOID *data, UINT32 dataLen);

extern _RPST_  GsnWdd_L2DevSend_FP_T GsnWdd_L2DevSend_FP; 

typedef GSN_STATUS
(* GsnWdd_L2DevIoctl_FP_T)(GSN_L2_DEV_T *pL2Dev, UINT32 cmd, void *pData);

extern _RPST_  GsnWdd_L2DevIoctl_FP_T GsnWdd_L2DevIoctl_FP;


typedef VOID
(*GsnWdd_MsgHdlrNotify_FP_T)(GSN_WDD_MSG_HANDLER_T *pWddMsgHdlr, GSN_WDD_MESSAGE_T *pMsg);

extern _RPST_ GsnWdd_MsgHdlrNotify_FP_T GsnWdd_MsgHdlrNotify_FP;

typedef VOID 
(*GsnWdd_MsgHdlrEntryFun_FP_T)(UINT32 ctx);
extern _RPST_ GsnWdd_MsgHdlrEntryFun_FP_T GsnWdd_MsgHdlrEntryFun_FP;

typedef BOOL
(*GsnWdd_MsgHdlr_FP_T)(VOID *pCtx, VOID *pWddMsg);
extern _RPST_ GsnWdd_MsgHdlr_FP_T GsnWdd_MsgHdlr_FP;


typedef VOID
(* GsnWdd_WifWlanCtrlIndReg_FP_T)(GSN_WDD_CTX_T *pWdd);

extern _RPST_  GsnWdd_WifWlanCtrlIndReg_FP_T GsnWdd_WifWlanCtrlIndReg_FP;

typedef VOID
(* GsnWdd_WifCalCtrlIndReg_FP_T)(GSN_WDD_CTX_T *pWdd);

extern _RPST_  GsnWdd_WifCalCtrlIndReg_FP_T GsnWdd_WifCalCtrlIndReg_FP;

typedef VOID
(* GsnWdd_WifDataIndReg_FP_T)(GSN_WDD_CTX_T *pWdd);

extern _RPST_  GsnWdd_WifDataIndReg_FP_T GsnWdd_WifDataIndReg_FP;

typedef GSN_STATUS
(* GsnWdd_WlanCtrlMsgIndCb_FP_T)(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
							 VOID *pMsg);

extern _RPST_  GsnWdd_WlanCtrlMsgIndCb_FP_T GsnWdd_WlanCtrlMsgIndCb_FP;

typedef GSN_STATUS
(*GsnWdd_CalCtrlMsgIndCb_FP_T)(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
									VOID *pMsg);
extern _RPST_ GsnWdd_CalCtrlMsgIndCb_FP_T GsnWdd_CalCtrlMsgIndCb_FP;

typedef GSN_STATUS
(* GsnWdd_DataMsgIndCb_FP_T)( VOID *pCtx, UINT16 status, UINT8 dataClass, UINT16 msgLen, VOID *pMsg );

extern _RPST_  GsnWdd_DataMsgIndCb_FP_T GsnWdd_DataMsgIndCb_FP;

typedef BOOL
(*GsnWdd_IsApSecurityEnbld_FP_T)(GSN_WDD_CTX_T *pWdd);

extern _RPST_ GsnWdd_IsApSecurityEnbld_FP_T GsnWdd_IsApSecurityEnbld_FP;

typedef VOID
(* GsnWdd_WpaSupplicantCb_FP_T)(VOID *ctx);
extern _RPST_  GsnWdd_WpaSupplicantCb_FP_T GsnWdd_WpaSupplicantCb_FP;

typedef  GSN_STATUS
(* GsnWdd_PrivateScan_FP_T)(GSN_WDD_CTX_T *pWdd,
   	                     GSN_WDD_SCAN_PARAMS_T *scanParams,
   	                     INT8 *rsltBuff,
   	                     UINT32 rsltBuffLen,
   	                     GSN_WDD_SCAN_NOTIF_CB_T notifyCb,
   	                     VOID *notifyCtxt);
extern _RPST_  GsnWdd_PrivateScan_FP_T GsnWdd_PrivateScan_FP;

typedef VOID
(* GsnWdd_ScanOnlyProcess_FP_T)(GSN_WDD_CTX_T *pWdd, UINT8 scanEndFlag, 
								   VOID *pScanInd, UINT32 scanIndLen);
extern _RPST_  GsnWdd_ScanOnlyProcess_FP_T GsnWdd_ScanOnlyProcess_FP;

typedef BOOL
(*GsnWdd_ConnectPolicyCheck_FP_T)(GSN_WDD_CTX_T *pWdd, UINT32 scanEnd, 
									   GSN_WDD_SCAN_ENTRY_T *pScanEntry);
extern _RPST_ GsnWdd_ConnectPolicyCheck_FP_T GsnWdd_ConnectPolicyCheck_FP;

typedef VOID
(* GsnWdd_ScanAndConctProcess_FP_T)(GSN_WDD_CTX_T * pWdd,UINT8 scanEndFlag,
										   UINT8 * scanIndBuf,UINT32 bufLen);
extern _RPST_  GsnWdd_ScanAndConctProcess_FP_T GsnWdd_ScanAndConctProcess_FP;

typedef GSN_STATUS
(* GsnWdd_ScanEntryCheck_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_SCAN_ENTRY_T *pScanEntry, 
							  	  BOOL *pWlanNwFound, GSN_WDD_SEC_IE_INFO_T *pSecIEinfo,
								  GSN_WPAIF_BASIC_CFG_T *pApSecCfg);
extern _RPST_  GsnWdd_ScanEntryCheck_FP_T GsnWdd_ScanEntryCheck_FP;

typedef BOOL
(* GsnWdd_CheckCipher_FP_T)(GSN_WDD_WLAN_CFG_T *pWlanCfg, GSN_WPAIF_BASIC_CFG_T *pApSecCfg, 
							 UINT8 *pairwiseCipher, UINT8 *groupCipher);
extern _RPST_  GsnWdd_CheckCipher_FP_T GsnWdd_CheckCipher_FP;

typedef BOOL
(* GsnWdd_SecurityCmp_FP_T)(GSN_WDD_WLAN_CFG_T *pWlanCfg, GSN_MAC_FRAME_T *pMacFrame,
							UINT16 macFrameLen, GSN_WDD_SEC_IE_INFO_T *secIEinfo,
							GSN_WPAIF_BASIC_CFG_T *pApSecCfg);
extern _RPST_  GsnWdd_SecurityCmp_FP_T GsnWdd_SecurityCmp_FP;


typedef BOOL
(*GsnWdd_SecCfgGet_FP_T)(GSN_WDD_WLAN_CFG_T *pWlanCfg, UINT8 *pMacFrame,			UINT16 macFrameLen, 
						  GSN_WDD_SEC_IE_INFO_T *secIEinfo, 
						  GSN_WPAIF_BASIC_CFG_T *pWpaBasicCfg);

extern _RPST_ GsnWdd_SecCfgGet_FP_T GsnWdd_SecCfgGet_FP;

typedef VOID
(*GsnWdd_ApModeSecCfgSet_FP_T)(GSN_WDD_WLAN_CFG_T *pWlanCfg, 
									GSN_WPAIF_BASIC_CFG_T *pBasicSecCfg, 
						  			GSN_WDD_SEC_IE_INFO_T *secIEinfo);
extern _RPST_ GsnWdd_ApModeSecCfgSet_FP_T GsnWdd_ApModeSecCfgSet_FP;

typedef GSN_STATUS_T
(* GsnWdd_WpsStart_FP_T)(GSN_WDD_CTX_T *pWdd);
extern _RPST_  GsnWdd_WpsStart_FP_T GsnWdd_WpsStart_FP;

typedef GSN_WPAIF_MODE_T
(*GsnWdd_WpaIfModeMap_FP_T)(GSN_WIF_WLAN_NW_TYPE_T wlanNwType);
extern _RPST_ GsnWdd_WpaIfModeMap_FP_T GsnWdd_WpaIfModeMap_FP;

typedef GSN_STATUS_T
( *GsnWdd_WpaIfInit_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WPAIF_BASIC_CFG_T *pBasicSecCfg);
extern _RPST_  GsnWdd_WpaIfInit_FP_T GsnWdd_WpaIfInit_FP;


typedef GSN_STATUS_T 
(* GsnWdd_ConnectReq_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_CFG_T *pWlanCfg,
					  GSN_WDD_CONN_REQ_PARAM_T *pParam);

extern _RPST_  GsnWdd_ConnectReq_FP_T GsnWdd_ConnectReq_FP;

typedef GSN_STATUS_T 
(* GsnWdd_DisconnectReq_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_DISCONN_REQ_PARAM_T *pParam);

extern _RPST_  GsnWdd_DisconnectReq_FP_T GsnWdd_DisconnectReq_FP;

typedef GSN_STATUS_T
(* GsnWdd_ScanReq_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_SCAN_PARAMS_T *pParam);
extern _RPST_  GsnWdd_ScanReq_FP_T GsnWdd_ScanReq_FP;

/*************************/
typedef VOID 
(* GsnWdd_SecModeUpdate_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_CFG_T *pWlanConfig);
extern _RPST_ GsnWdd_SecModeUpdate_FP_T GsnWdd_SecModeUpdate_FP;

typedef VOID
(* GsnWdd_RadioModeCountrClr_FP_T)(GSN_WDD_CTX_T *pWdd);
extern _RPST_ GsnWdd_RadioModeCountrClr_FP_T GsnWdd_RadioModeCountrClr_FP;

typedef GSN_STATUS
(* GsnWdd_WlanCtrlMsgIndCbExtension_FP_T)(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
							 VOID *pMsg);

extern _RPST_  GsnWdd_WlanCtrlMsgIndCbExtension_FP_T GsnWdd_WlanCtrlMsgIndCbExtension_FP;




#endif /*_GSN_WDD_PRIVATE_FPT_H_*/



