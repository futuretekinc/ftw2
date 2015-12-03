#ifndef _GSN_ISOTX_FPT_H_
#define _GSN_ISOTX_FPT_H_

typedef GSN_STATUS
(*GsnIsotx_CtrlMsgIndCb_FP_T)(VOID *pCtx, UINT16 msgId, UINT16 msgLen,	VOID *pMsg);
extern _RPST_ GsnIsotx_CtrlMsgIndCb_FP_T GsnIsotx_CtrlMsgIndCb_FP;

typedef GSN_STATUS
(*GsnIsotx_DataMsgIndCb_FP_T)( VOID *pCtx, UINT16 status, UINT16 msgLen, VOID *pMsg );
extern _RPST_ GsnIsotx_DataMsgIndCb_FP_T GsnIsotx_DataMsgIndCb_FP;
#endif
