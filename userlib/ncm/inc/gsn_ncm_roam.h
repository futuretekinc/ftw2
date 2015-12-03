

/* Public definitions for gsn_ncm_roam.c */

PUBLIC VOID
GsnNcm_RoamDeInit(GSN_NCM_CTX_T* ctx);

PUBLIC VOID
GsnNcm_RoamScanTmrProcess( GSN_NCM_CTX_T *NcmCtx);

PUBLIC VOID
GsnNcm_RoamScanTmrCb( VOID* context,GSN_SOFT_TMR_HANDLE_T timerHandle );

PUBLIC VOID
GsnNcm_RoamScanConfirm(VOID *cText,INT32 status,INT8 *rsltBuff,UINT32 rsltCount);

PUBLIC VOID
GsnNcm_RoamStart(GSN_NCM_CTX_T *pNcm,UINT8 domain);

PUBLIC VOID
GsnNcm_RoamInit(GSN_NCM_CTX_T* pNcm);

PUBLIC VOID
GsnNcm_RoamReInit(GSN_NCM_CTX_T * ctx);


PUBLIC VOID
GsnNcm_RoamScanPauseTmrCb(VOID * context,GSN_SOFT_TMR_HANDLE_T timerHandle);

PUBLIC GSN_STATUS
GsnNcm_RoamStop(GSN_NCM_CTX_T * ctx,UINT8 cbflg);


