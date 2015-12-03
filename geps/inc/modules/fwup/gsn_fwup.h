#ifndef _GSN_FWUP_H_
#define _GSN_FWUP_H_

#define GSN_BRFLASHLDR_FWIMAGES_MAX  3
#define GSN_FWUP_SUPER_BLOCK_ADDR 0x1000
//#define GSN_FWUP_RESTORE_FACTORY_REQUIRED

typedef struct GSN_BRFLASHLDR_FWIMAGE_INFO_S
{
    UINT32 index;
    UINT32 rev;
    UINT32 cb1Addr; /* also FW image base address */
    UINT32 cb2Addr;
} GSN_BRFLASHLDR_FWIMAGE_INFO_T;

typedef struct GSN_BRFLASHLDR_FWINFO_S
{
    UINT32 numFwValid;
    GSN_BRFLASHLDR_FWIMAGE_INFO_T fwImageInfo[GSN_BRFLASHLDR_FWIMAGES_MAX];
    
} GSN_BRFLASHLDR_FWINFO_T;

typedef struct GSN_FWUP_CTX
{
	UINT32 	revision;			/* revision number of current FW */
	UINT32 	downloadedSize;
    UINT32  flashAddr;
    UINT32 	cb1Addr;			/*CB1 address of free slot */
    UINT32	cb2Addr;			/*CB2 address of free slot */
    UINT32	startedFlag;
    GSN_BRFLASHLDR_FWINFO_T fwInfo;
	GSN_BRFLASHLDR_CTL_BLOCK_T controlBlock;
	UINT32 factImgReq;
}GSN_FWUP_CTX_T;

GSN_STATUS 
GsnFwup_Init(GSN_FWUP_CTX_T *pFwupCtx);

GSN_STATUS_T
GsnFwup_DownLoad(GSN_FWUP_CTX_T *pFwupCtx, UINT8 *pBuf, UINT32 bufSize);

GSN_STATUS_T
GsnFwup_DownLoadEnd(GSN_FWUP_CTX_T *pFwupCtx);

GSN_STATUS 
GsnFwup_DeInit(GSN_FWUP_CTX_T *pFwupCtx);

INLINE VOID GsnFwup_FactImgReqSet(GSN_FWUP_CTX_T *pFwupCtx)
{
    pFwupCtx->factImgReq = TRUE;
}

INLINE VOID GsnFwup_FactImgReqClear(GSN_FWUP_CTX_T *pFwupCtx)
{
    pFwupCtx->factImgReq = FALSE;
}

GSN_STATUS_T
GsnFwup_RollBackOtafu();

#endif
