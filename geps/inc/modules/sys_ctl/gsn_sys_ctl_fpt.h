#ifndef _GSN_SYS_CTL_FPT_H_
#define _GSN_SYS_CTL_FPT_H_
typedef VOID 
(*GsnSysCtl_MsgHdlrEntryFun_FP_T)(UINT32 ctx);
extern _RPST_ GsnSysCtl_MsgHdlrEntryFun_FP_T GsnSysCtl_MsgHdlrEntryFun_FP;

typedef 	GSN_STATUS
(*GsnSysCtl_SysCtrlMsgIndCb_FP_T)(VOID *pCtx, UINT16 msgId, UINT16 msgLen,	VOID *pMsg);
extern _RPST_ GsnSysCtl_SysCtrlMsgIndCb_FP_T GsnSysCtl_SysCtrlMsgIndCb_FP;

typedef VOID
(*GsnSysCtl_SysResetIndCb_FP_T)(VOID *pCtx, UINT16 msgLen,	VOID *pMsg);
extern _RPST_ GsnSysCtl_SysResetIndCb_FP_T GsnSysCtl_SysResetIndCb_FP;

typedef VOID
(*GsnSysCtl_FileOpReqProcess_FP_T)(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_WIF_SYS_FILE_OP_REQ_T *pReq);
extern _RPST_ GsnSysCtl_FileOpReqProcess_FP_T GsnSysCtl_FileOpReqProcess_FP;


typedef 	GSN_STATUS
(*GsnSysCtl_SysCtrlMsgIndCbExtension_FP_T)(VOID *pCtx, UINT16 msgId, UINT16 msgLen,	VOID *pMsg);
extern _RPST_ GsnSysCtl_SysCtrlMsgIndCbExtension_FP_T GsnSysCtl_SysCtrlMsgIndCbExtension_FP;

#endif
