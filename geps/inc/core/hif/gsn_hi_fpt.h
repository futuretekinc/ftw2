#ifndef _GSN_HI_FPT_H_
#define _GSN_HI_FPT_H_

#include "gsn_includes.h"

typedef VOID (* GsnHiMb_Init_FP_T)(GSN_HI_MB_CTX_T *pHiMbCtx);
extern _RPST_ GsnHiMb_Init_FP_T GsnHiMb_Init_FP;

typedef VOID (* GsnHiMb_RecvCbRegister_FP_T)(GSN_HI_MB_CTX_T *pHiMbCtx, GSN_CB_T *recvCbInfo);
extern _RPST_ GsnHiMb_RecvCbRegister_FP_T GsnHiMb_RecvCbRegister_FP;

typedef GSN_STATUS (* GsnHiMb_MsgSend_FP_T)(GSN_HI_MB_CTX_T *pHiMbCtx, UINT32 *msg);
extern _RPST_ GsnHiMb_MsgSend_FP_T GsnHiMb_MsgSend_FP;

typedef VOID (* GsnHiMb_MsgRcv_FP_T)(VOID *pThis, const VOID *pParam);
extern _RPST_ GsnHiMb_MsgRcv_FP_T GsnHiMb_MsgRcv_FP;

typedef VOID (* GsnHiMb_AckRcv_FP_T)(VOID *pThis, const VOID *pParam);
extern _RPST_ GsnHiMb_AckRcv_FP_T  GsnHiMb_AckRcv_FP;



typedef GSN_STATUS 
(*GsnHi_Init_FP_T)(GSN_HI_CTX_T *pHiCtx, GSN_HI_INIT_PARAM_T *pParam);

extern _RPST_ GsnHi_Init_FP_T GsnHi_Init_FP;

typedef GSN_STATUS_T 
(*GsnHi_CtrlSend_FP_T)(GSN_HI_CTX_T *pHiCtx, GSN_WIF_HI_CLASS_T hiClass, UINT8 devIndex,
					UINT32 reqAPI, VOID *pReq, UINT16 reqSize);
extern _RPST_ GsnHi_CtrlSend_FP_T GsnHi_CtrlSend_FP;

typedef PUBLIC GSN_STATUS 
(*GsnHi_DataSend_FP_T) (GSN_HI_CTX_T *pHiCtx, GSN_WIF_HI_CLASS_T hiClass, UINT8 devIndex, UINT32 msgId,
						INT8* data, UINT32 dataLen, UINT8 pktId);
extern _RPST_ GsnHi_DataSend_FP_T GsnHi_DataSend_FP;

typedef PUBLIC VOID
(*GsnHi_BootReqSend_FP_T)(GSN_HI_CTX_T *pHiCtx, GSN_WIF_SYS_BOOT_REQ_T *pBootReq);
extern _RPST_ GsnHi_BootReqSend_FP_T GsnHi_BootReqSend_FP;

typedef VOID
(*GsnHi_InterfaceRegister_FP_T)(GSN_HI_CTX_T *pHiCtx, GSN_HI_IFC_REG_PARAM_T *pParam);

extern _RPST_ GsnHi_InterfaceRegister_FP_T GsnHi_InterfaceRegister_FP;

typedef VOID
(*GsnHi_InterfaceDeregister_FP_T)(GSN_HI_CTX_T *pHiCtx, UINT8 macIfNum);
extern _RPST_ GsnHi_InterfaceDeregister_FP_T GsnHi_InterfaceDeregister_FP;

typedef VOID 
(*GsnHi_ResetIndCbReg_FP_T)(GSN_HI_CTX_T *pHiCtx,  	   GSN_WIF_RESET_IND_CB_T cb, VOID *ctx);
extern _RPST_ GsnHi_InterfaceDeregister_FP_T GsnHi_InterfaceDeregister_FP;

typedef VOID
(*GsnHi_RecvMbCb_FP_T)(void *pCtx, const void *pMsg);
extern _RPST_ GsnHi_RecvMbCb_FP_T GsnHi_RecvMbCb_FP;

typedef VOID
(*GsnHi_ResetIndRecvMbCb_FP_T)(void *pCtx, const void *pMsg);
extern _RPST_ GsnHi_ResetIndRecvMbCb_FP_T GsnHi_ResetIndRecvMbCb_FP;

typedef VOID
(*GsnHi_RecvThreadEntry_FP_T)(UINT32 ctx);
extern _RPST_ GsnHi_RecvThreadEntry_FP_T GsnHi_RecvThreadEntry_FP;

typedef VOID
(*GsnHi_RecvEvntProcess_FP_T)(GSN_HI_CTX_T *pHiCtx, GSN_OSAL_EVENT_FLAGS_VAL_T evntFlagsVal);
extern _RPST_ GsnHi_RecvEvntProcess_FP_T GsnHi_RecvEvntProcess_FP;

typedef PUBLIC VOID
(*GsnHi_RxBufInit_FP_T)(GSN_HI_BUF_Q_DESC_T *pHiBufQdesc, GSN_HI_RX_BUF_INIT_PARAM_T *params);

extern _RPST_ GsnHi_RxBufInit_FP_T GsnHi_RxBufInit_FP;
typedef  PUBLIC VOID
(*GsnHi_RxBufRelease_FP_T)(INT8 *ptr);;

extern _RPST_ GsnHi_RxBufRelease_FP_T GsnHi_RxBufRelease_FP;

#endif