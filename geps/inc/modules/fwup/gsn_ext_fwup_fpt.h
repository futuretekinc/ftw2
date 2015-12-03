#include "main/gsn_br_flashldr.h"
#include "modules/fwup/gsn_fwup.h"
#include "modules/fwup/gsn_ext_fwup.h"

typedef PUBLIC UINT
(*GsnExtFlash_FlashErase_FP_T)(GSN_EXTFWUP_CTX_T *pExtFwupCtx, UINT32 addr, UINT32 len, BOOL blocking);

typedef GSN_STATUS
(*GsnExtFwup_DeInit_FP_T)(GSN_EXTFWUP_CTX_T *pExtFwupCtx);

typedef GSN_STATUS_T
(*GsnExtFwup_DownLoad_FP_T)(GSN_EXTFWUP_CTX_T *pExtFwupCtx, UINT8 *pBuf, UINT32 bufSize);

typedef GSN_STATUS_T
(*GsnExtFwup_DownLoadEnd_FP_T)(GSN_EXTFWUP_CTX_T *pExtFwupCtx);

typedef VOID
(*GsnExtFwup_FwInfoParse_FP_T)(GSN_BRFLASHLDR_SUPERBLOCK_T *pSuperBlock,
                        GSN_BRFLASHLDR_CTL_BLOCK_T *pFw0CtlBlk,
                        GSN_BRFLASHLDR_CTL_BLOCK_T *pFw1CtlBlk,
                        GSN_BRFLASHLDR_CTL_BLOCK_T *pFw2CtlBlk,
                        GSN_EXTFWUP_CTX_T *pExtFwupCtx);
typedef BOOL
(*GsnExtFwup_FwValidCheck_FP_T)( UINT32 cb1Addr, UINT32 cb2Addr,
                            GSN_BRFLASHLDR_CTL_BLOCK_T *pFwCtlBlk, 
                            GSN_EXTFWUP_CTX_T *pExtFwupCtx);

typedef GSN_STATUS
(*GsnExtFwup_Init_FP_T)(GSN_EXTFWUP_CTX_T *pExtFwupCtx);

extern _RPST_ GsnExtFwup_DeInit_FP_T GsnExtFwup_DeInit_FP ;
extern _RPST_ GsnExtFwup_DownLoad_FP_T GsnExtFwup_DownLoad_FP ;
extern _RPST_ GsnExtFwup_DownLoadEnd_FP_T GsnExtFwup_DownLoadEnd_FP ;
extern _RPST_ GsnExtFwup_FwInfoParse_FP_T GsnExtFwup_FwInfoParse_FP ;
extern _RPST_ GsnExtFwup_FwValidCheck_FP_T GsnExtFwup_FwValidCheck_FP ;
extern _RPST_ GsnExtFwup_Init_FP_T GsnExtFwup_Init_FP ;
extern _RPST_ GsnExtFlash_FlashErase_FP_T GsnExtFlash_FlashErase_FP ;


