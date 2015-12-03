#ifndef _GSN_SYSIF_FPT_H_
#define _GSN_SYSIF_FPT_H_

typedef  GSN_STATUS 
(* GsnSysif_Init_FP_T)(GSN_SYSIF_CTX_T *pSysifCtx, GSN_SYSIF_INIT_PARAM_T *pParam);
extern _RPST_ GsnSysif_Init_FP_T GsnSysif_Init_FP;

typedef  VOID 
(* GsnSysif_CtrlCb_FP_T)(VOID * pCtx, GSN_WIF_CTL_TD_T *pCtrlTD);
extern _RPST_ GsnSysif_CtrlCb_FP_T GsnSysif_CtrlCb_FP;

#endif
