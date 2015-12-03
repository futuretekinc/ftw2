#ifndef _GSN_ISOTXIF_FPT_H_
#define _GSN_ISOTXIF_FPT_H_

typedef PUBLIC GSN_STATUS 
( *GsnIsotxif_Init_FP_T)(GSN_ISOTXIF_CTX_T *pIsotxifCtx, GSN_ISOTXIF_INIT_PARAM_T *pParam);

extern _RPST_  GsnIsotxif_Init_FP_T GsnIsotxif_Init_FP;
typedef VOID 
(* GsnIsotxif_CtrlCb_FP_T)(VOID * pCtx, GSN_WIF_CTL_TD_T *pCtrlTD);
extern _RPST_  GsnIsotxif_CtrlCb_FP_T GsnIsotxif_CtrlCb_FP;

typedef VOID 
(* GsnIsotxif_DataCb_FP_T)(VOID * pCtx, GSN_WIF_DATA_TD_T *pDataTD);
extern _RPST_  GsnIsotxif_DataCb_FP_T GsnIsotxif_DataCb_FP;
#endif
