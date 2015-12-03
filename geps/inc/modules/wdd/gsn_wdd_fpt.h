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
* $RCSfile: gsn_wdd_fpt.h,v $
*
* Description : Patch header file for gsn_wdd.c
*****************************************************************************/
#ifndef _GSN_WDD_FPT_H_
#define _GSN_WDD_FPT_H_

typedef GSN_STATUS
(* GsnWdd_Init_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_INIT_PARAM_T *pInitParam, GSN_WDD_INIT_FLAG_T flags);

extern _RPST_  GsnWdd_Init_FP_T GsnWdd_Init_FP;

typedef PUBLIC VOID
(* GsnWdd_WpaSupplicantInit_FP_T)(GSN_WDD_WPA_SUP_INIT_PARAM_T *pParam);

extern _RPST_  GsnWdd_WpaSupplicantInit_FP_T GsnWdd_WpaSupplicantInit_FP;


typedef VOID
(*GsnWdd_MsgHdlrInit_FP_T)(GSN_WDD_MSG_HANDLER_T *pWddMsgHdlr, GSN_WDD_MSG_HDLR_INIT_PARAM_T *pParam);

extern _RPST_ GsnWdd_MsgHdlrInit_FP_T GsnWdd_MsgHdlrInit_FP;


typedef GSN_STATUS
(* GsnWdd_MulticastRecvSet_FP_T)(GSN_WDD_CTX_T *pWdd, BOOL recvEnable);

extern _RPST_  GsnWdd_MulticastRecvSet_FP_T GsnWdd_MulticastRecvSet_FP;

typedef GSN_STATUS
(* GsnWdd_RadioModeSet_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_RADIO_MODE_T mode, BOOL enable);

extern _RPST_  GsnWdd_RadioModeSet_FP_T GsnWdd_RadioModeSet_FP;

typedef GSN_STATUS
(* GsnWdd_PhyAddrSet_FP_T)(GSN_WDD_CTX_T *pWdd, INT8 *macAddr, BOOL updateWfw);

extern _RPST_  GsnWdd_PhyAddrSet_FP_T GsnWdd_PhyAddrSet_FP;

typedef VOID
(* GsnWdd_PhyAddrGet_FP_T)(GSN_WDD_CTX_T *pWdd, INT8 *macAddr);

extern _RPST_  GsnWdd_PhyAddrGet_FP_T GsnWdd_PhyAddrGet_FP;


typedef VOID
(* GsnWdd_Notify_FP_T)(VOID *pCtx, GSN_WDD_EVENT_T event);

extern _RPST_  GsnWdd_Notify_FP_T GsnWdd_Notify_FP;


typedef VOID
(* GsnWdd_WlanConfigDefaultInit_FP_T)(GSN_WDD_WLAN_CFG_T *pWlanConfig);

extern _RPST_  GsnWdd_WlanConfigDefaultInit_FP_T GsnWdd_WlanConfigDefaultInit_FP;

typedef GSN_STATUS_T
(* GsnWdd_Connect_FP_T)(GSN_WDD_CTX_T *pWdd,
							GSN_WDD_CONNECT_FLAG_T flags,
							GSN_WDD_WLAN_CFG_T *pWlanCfg,
							GSN_WDD_SCAN_ENTRY_T *pScanEntry,
							GSN_WDD_CONNECT_NOTIF_CB_T notifyCb,
							VOID *notifyCtx);

extern _RPST_  GsnWdd_Connect_FP_T GsnWdd_Connect_FP;

typedef GSN_STATUS_T
(*GsnWdd_Disconnect_FP_T)(GSN_WDD_CTX_T *pWdd,
						   UINT16 disconResonCode,
                           GSN_WDD_DISCONNECT_NOTIF_CB_T notifyCb,
                           VOID *notifyCtx);
extern _RPST_  GsnWdd_Disconnect_FP_T GsnWdd_Disconnect_FP;

typedef GSN_STATUS
(* GsnWdd_Scan_FP_T)(GSN_WDD_CTX_T *pWdd,
   	                     GSN_WDD_SCAN_PARAMS_T *scanParams,
   	                     INT8 *rsltBuff,
   	                     UINT32 rsltBuffLen,
   	                     GSN_WDD_SCAN_NOTIF_CB_T notifyCb,
   	                     VOID *notifyCtxt);
extern _RPST_   GsnWdd_Scan_FP_T GsnWdd_Scan_FP;

typedef GSN_STATUS
(* GsnWdd_WpsScan_FP_T)(GSN_WDD_CTX_T *pWdd,
   	                     		  GSN_WDD_SCAN_PARAMS_T *scanParams,
   	                     		  INT8 *rsltBuff,
	   	   	                      UINT32 rsltBuffLen,
	   	   	                      GSN_WDD_SCAN_NOTIF_CB_T notifyCb,
	   	   	                      VOID *notifyCtxt);

typedef GSN_STATUS
(*GsnWdd_ScanStop_FP_T)(GSN_WDD_CTX_T *pWdd);
extern _RPST_ GsnWdd_ScanStop_FP_T GsnWdd_ScanStop_FP;

typedef GSN_STATUS
(* GsnWdd_Send_FP_T)(GSN_WDD_CTX_T *pWdd, VOID *data, UINT32 dataLen);
extern _RPST_  GsnWdd_Send_FP_T GsnWdd_Send_FP;

extern _RPST_  GsnWdd_WpsScan_FP_T GsnWdd_WpsScan_FP;


typedef GSN_STATUS
(* GsnWdd_SetGroupKey_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 keyIndex, UINT8 algo, 
							  UINT8	authRole, UINT8 keyLen, INT8 *pKey, ULONG64 rsc);
extern _RPST_ GsnWdd_SetGroupKey_FP_T GsnWdd_SetGroupKey_FP;

typedef GSN_STATUS
(* GsnWdd_SetPairKey_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 keyIndex, UINT8 algo, UINT8 authRole, 
						   UINT8 keyLen, UINT8 *pKey, ULONG64 rsc, UINT8 *pStaAddr);
extern _RPST_ GsnWdd_SetPairKey_FP_T GsnWdd_SetPairKey_FP;

typedef GSN_STATUS
(*GsnWdd_SetWepKey_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 keyIndex, UINT8 keyLen, UINT8 *pKey);

extern  _RPST_ GsnWdd_SetWepKey_FP_T GsnWdd_SetWepKey_FP;

typedef PUBLIC GSN_STATUS
(*GsnWdd_WpsConnect_FP_T)(GSN_WDD_CTX_T *pWdd,
                  		GSN_WDD_CONNECT_FLAG_T flags,                  		
                  		GSN_WDD_SCAN_ENTRY_T *pScanEntry,
                  		GSN_WDD_CONNECT_NOTIF_CB_T notifyCb,
                  		VOID *notifyCtx);
extern _RPST_ GsnWdd_WpsConnect_FP_T GsnWdd_WpsConnect_FP;

typedef PUBLIC GSN_STATUS
(*GsnWdd_ProbeReqPropIeSet_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, 
                                 UINT32 ieLength );
extern _RPST_ GsnWdd_ProbeReqPropIeSet_FP_T GsnWdd_ProbeReqPropIeSet_FP;

typedef PUBLIC GSN_STATUS
(*GsnWdd_AssocReqPropIeSet_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, 
                                 UINT32 ieLength );
extern _RPST_ GsnWdd_AssocReqPropIeSet_FP_T GsnWdd_AssocReqPropIeSet_FP;

typedef GSN_STATUS
(*GsnWdd_ScanParamSet_FP_T)(GSN_WDD_CTX_T *pWdd, UINT16 minActivScnTime, UINT16 maxActivScnTime,
								UINT16 passiveScnTime);
extern  _RPST_ GsnWdd_ScanParamSet_FP_T GsnWdd_ScanParamSet_FP;


typedef  GSN_STATUS
(*GsnWdd_BeaconMissThresholdSet_FP_T)(GSN_WDD_CTX_T *pWdd, UINT32 thresholdTime,
											UINT32 thresholdNo);
extern  _RPST_ GsnWdd_BeaconMissThresholdSet_FP_T GsnWdd_BeaconMissThresholdSet_FP;


typedef GSN_STATUS
(* GsnWdd_TkipContrMsrStart_FP_T)(GSN_WDD_CTX_T *pWdd);
extern _RPST_ GsnWdd_TkipContrMsrStart_FP_T GsnWdd_TkipContrMsrStart_FP;

typedef GSN_STATUS
( *GsnWdd_ConctedStaListGet_FP_T)(GSN_WDD_CTX_T *pWdd, INT8 *outBuf, UINT32 outBufSize);

extern _RPST_ GsnWdd_ConctedStaListGet_FP_T GsnWdd_ConctedStaListGet_FP;

typedef GSN_STATUS
( *GsnWdd_TkipSeqNumGet_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WIF_WLAN_TKIP_COUNTER_GET_RSP_T *pResp);
extern _RPST_ GsnWdd_TkipSeqNumGet_FP_T GsnWdd_TkipSeqNumGet_FP;

typedef GSN_STATUS
( *GsnWdd_WlanStatsGet_FP_T)(GSN_WDD_CTX_T *pWdd, UINT8 reset, UINT8 statType, 
							   INT8 *outBuf, UINT32 outBufSize);
extern _RPST_ GsnWdd_WlanStatsGet_FP_T GsnWdd_WlanStatsGet_FP;

typedef GSN_STATUS
(* GsnWdd_WlanRecvFiltrSet_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_WLAN_RECV_FILTR_SET_PARAM_T *pParam);
extern _RPST_ GsnWdd_WlanRecvFiltrSet_FP_T GsnWdd_WlanRecvFiltrSet_FP;

typedef GSN_STATUS
( *GsnWdd_RtsEnable_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_RTS_ENBL_PARAM_T *pParam);
extern _RPST_ GsnWdd_RtsEnable_FP_T GsnWdd_RtsEnable_FP;

typedef GSN_STATUS
( *GsnWdd_BlockAckReq_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_BLOCKACK_REQ_T *pParam);
extern _RPST_ GsnWdd_BlockAckReq_FP_T GsnWdd_BlockAckReq_FP;

typedef GSN_STATUS
( *GsnWdd_AmsduReq_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_AMSDU_REQ_T *pParam);
extern _RPST_ GsnWdd_AmsduReq_FP_T GsnWdd_AmsduReq_FP;

typedef GSN_STATUS
(* GsnWdd_AmpduReq_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_AMPDU_REQ_T *pParam);
extern _RPST_ GsnWdd_AmpduReq_FP_T GsnWdd_AmpduReq_FP;

typedef GSN_STATUS
(* GsnWdd_FrameTxFailCntLmitSet_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_FRAME_TX_FAIL_CNT_LIMIT_SET_T *pParam);
extern _RPST_ GsnWdd_FrameTxFailCntLmitSet_FP_T GsnWdd_FrameTxFailCntLmitSet_FP;

typedef GSN_STATUS
( *GsnWdd_CalibrnRun_FP_T)(GSN_WDD_CTX_T *pWdd,
						   GSN_WDD_CAL_RUN_REQ_T *pCalRunReq,
                           GSN_WDD_CAL_NOTIF_CB_T notifyCb,
                           VOID *notifyCtx);
extern _RPST_ GsnWdd_CalibrnRun_FP_T GsnWdd_CalibrnRun_FP;

typedef GSN_STATUS
(*GsnWdd_Reinit_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_REINIT_PARAM_T *pParam);

extern _RPST_ GsnWdd_Reinit_FP_T GsnWdd_Reinit_FP;

typedef BOOL
(*GsnWdd_AssocStatusGet_FP_T)(GSN_WDD_CTX_T *pWdd);

extern _RPST_ GsnWdd_AssocStatusGet_FP_T GsnWdd_AssocStatusGet_FP;

typedef GSN_STATUS
(* GsnWdd_RSSIGet_FP_T)(GSN_WDD_CTX_T *pWdd, INT8 *outBuf, UINT32 outBufSize);

extern _RPST_ GsnWdd_RSSIGet_FP_T GsnWdd_RSSIGet_FP;

typedef GSN_STATUS
(*GsnWdd_TxPowerSet_FP_T)(GSN_WDD_CTX_T *pWdd, UINT8 txPower);

extern _RPST_ GsnWdd_TxPowerSet_FP_T GsnWdd_TxPowerSet_FP;

typedef  GSN_STATUS
(* GsnWdd_RadioPowerSaveCfgSet_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_STA_PS_CFG_SET_PARAM_T *pParam);

extern _RPST_ GsnWdd_RadioPowerSaveCfgSet_FP_T GsnWdd_RadioPowerSaveCfgSet_FP;

typedef GSN_STATUS
(*GsnWdd_Ioctl_FP_T)(GSN_WDD_CTX_T *pWdd, GSN_WDD_IOCTL_CMD_T command, void *pData);

extern _RPST_ GsnWdd_Ioctl_FP_T GsnWdd_Ioctl_FP;

typedef GSN_STATUS
(*GsnWdd_DABindEnable_FP_T)(GSN_WDD_CTX_T *pWdd, UINT8 enable);

extern _RPST_ GsnWdd_DABindEnable_FP_T GsnWdd_DABindEnable_FP;
 
typedef GSN_STATUS
(* GsnWdd_ProbeRspPropIeSet_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, UINT32 ieLength );

extern _RPST_ GsnWdd_ProbeRspPropIeSet_FP_T GsnWdd_ProbeRspPropIeSet_FP;

typedef GSN_STATUS
( *GsnWdd_BeaconPropIeSet_FP_T)( GSN_WDD_CTX_T *pWdd, UINT8 *pIe, UINT32 ieLength );

extern _RPST_ GsnWdd_BeaconPropIeSet_FP_T GsnWdd_BeaconPropIeSet_FP;

#endif /*_GSN_WDD_FPT_H_*/
