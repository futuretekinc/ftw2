#ifndef _GSN_DOT154IF_FPT_H_
#define _GSN_DOT154IF_FPT_H_

typedef GSN_STATUS 
(* GsnDot154if_Init_FP_T)(GSN_DOT154IF_CTX_T *pDot154ifCtx, GSN_DOT154_INIT_PARAM_T *pParam);

extern _RPST_ GsnDot154if_Init_FP_T GsnDot154if_Init_FP;

typedef VOID 
(* GsnDot154if_CtrlCb_FP_T)(VOID * pCtx, GSN_WIF_CTL_TD_T *pCtrlTD);

extern _RPST_ GsnDot154if_CtrlCb_FP_T GsnDot154if_CtrlCb_FP;



typedef VOID 
(* GsnDot154if_DataCb_FP_T)(VOID * pCtx, GSN_WIF_DATA_TD_T *pDataTD);
extern _RPST_ GsnDot154if_DataCb_FP_T GsnDot154if_DataCb_FP;
#endif
