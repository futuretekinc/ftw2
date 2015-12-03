#include "main/gsn_br_flashldr.h"
#include "modules/fwup/gsn_fwup.h"


typedef GSN_STATUS
(*GsnFwup_DeInit_FP_T)(GSN_FWUP_CTX_T * pFwupCtx);

typedef GSN_STATUS_T
(*GsnFwup_DownLoad_FP_T)(GSN_FWUP_CTX_T * pFwupCtx,UINT8 * pBuf,UINT32 bufSize);

typedef GSN_STATUS_T
(*GsnFwup_DownLoadEnd_FP_T)(GSN_FWUP_CTX_T * pFwupCtx);

typedef VOID
(*GsnFwup_FwInfoParse_FP_T)(GSN_BRFLASHLDR_SUPERBLOCK_T * pSuperBlock,GSN_BRFLASHLDR_CTL_BLOCK_T * pFw0CtlBlk,\
					  GSN_BRFLASHLDR_CTL_BLOCK_T * pFw1CtlBlk,\
					  GSN_BRFLASHLDR_CTL_BLOCK_T * pFw2CtlBlk,GSN_FWUP_CTX_T * pFwupCtx);
typedef BOOL
(*GsnFwup_FwValidCheck_FP_T)(UINT32 cb1Addr,UINT32 cb2Addr,GSN_BRFLASHLDR_CTL_BLOCK_T * pFwCtlBlk);

typedef GSN_STATUS
(*GsnFwup_Init_FP_T)(GSN_FWUP_CTX_T * pFwupCtx);

extern _RPST_ GsnFwup_DeInit_FP_T GsnFwup_DeInit_FP ;
extern _RPST_ GsnFwup_DownLoad_FP_T GsnFwup_DownLoad_FP ;
extern _RPST_ GsnFwup_DownLoadEnd_FP_T GsnFwup_DownLoadEnd_FP ;
extern _RPST_ GsnFwup_FwInfoParse_FP_T GsnFwup_FwInfoParse_FP ;
extern _RPST_ GsnFwup_FwValidCheck_FP_T GsnFwup_FwValidCheck_FP ;
extern _RPST_ GsnFwup_Init_FP_T GsnFwup_Init_FP ;

