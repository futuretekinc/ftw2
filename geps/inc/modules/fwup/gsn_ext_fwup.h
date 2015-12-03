#ifndef _GSN_EXT_FWUP_H_
#define _GSN_EXT_FWUP_H_

typedef struct GSN_EXTFWUP_CTX
{
	GSN_FWUP_CTX_T fwupCtx;
	GSN_EXTFLASH_CTX_T *extFlashCtx;
	GSN_FLASH_SPI_FLAG_T extFwupSpiMode;
	
}GSN_EXTFWUP_CTX_T;

#define GSN_EXT_FLASH_BLOCK_SIZE        0x10000     /* 64KB */
#define GSN_EXT_FLASH_SECTOR_SIZE       0x1000      /* 4KB   */
#define GSN_EXT_FLASH_PAGE_SIZE         0x100       /* 256B */


GSN_STATUS 
GsnExtFwup_Init(GSN_EXTFWUP_CTX_T *pFwupCtx);

GSN_STATUS_T
GsnExtFwup_DownLoadVerify(GSN_EXTFWUP_CTX_T *pExtFwupCtx, UINT8 *pBuf, UINT32 bufSize);

GSN_STATUS_T
GsnExtFwup_DownLoad(GSN_EXTFWUP_CTX_T *pFwupCtx, UINT8 *pBuf, UINT32 bufSize);

GSN_STATUS_T
GsnExtFwup_DownLoadEnd(GSN_EXTFWUP_CTX_T *pFwupCtx);

GSN_STATUS 
GsnExtFwup_DeInit(GSN_EXTFWUP_CTX_T *pFwupCtx);

PUBLIC UINT
GsnExtFlash_FlashErase(GSN_EXTFWUP_CTX_T *pExtFwupCtx, UINT32 addr, UINT32 len, BOOL blocking);

#endif
