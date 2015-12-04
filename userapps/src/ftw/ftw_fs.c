#ifndef _N25Q_32MB_3V_65NM_C_
#define _N25Q_32MB_3V_65NM_C_

#include "gsn_includes.h"
#include "drivers/dma/gsn_dma.h"
#include "main/gsn_br_flashldr.h"

#include "drivers/reg/gsn_reg_dma_spec.h"
#include "drivers/reg/gsn_reg_dma_op.h"
#include "app_defines_builder.h"
#include "modules/fwup/gsn_fwup.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "app_main_ctx.h"

#include "ftw_fs.h"

/*  physical  */
/*  64x128k blocks  */

#define BLOCKSIZE      0x1000 /*  4K - size of file storage blocks  */
#define BLOCKSTART     0x32       /*  logical number of first file storage block  */
#define MAXBLOCKS      14      /*  number of logical blocks for file storage  */

#define DESCSIZE       0x1000  /*  4k descriptor block size  */
#define DESCBLOCKSTART 0x30        /*  logical number of first descriptor block  */
#define DESCBLOCKS     2        /*  number of descriptor blocks  */
#define DESCCACHE      0x400  /*  1k assigned to write cache for descriptor  */

#define SECTORSIZE     0x400   /* 1k */
#define SECTORPERBLOCK ( BLOCKSIZE / SECTORSIZE )


#ifdef FTW_WEB_FS_AVAILABLE
#define BLOCKSIZE_1      0x1000 /*  4K - size of file storage blocks  */
#define BLOCKSTART_1     0x2       /*  logical number of first file storage block  */
#define MAXBLOCKS_1      14      /*  number of logical blocks for file storage  */

#define DESCSIZE_1       0x1000  /*  4k descriptor block size  */
#define DESCBLOCKSTART_1 0x0        /*  logical number of first descriptor block  */
#define DESCBLOCKS_1     2        /*  number of descriptor blocks  */
#define DESCCACHE_1      0x0  /*  1k assigned to write cache for descriptor  */

#ifndef FTW_WEB_IMAGE_SECTOR_SIZE
#define SECTORSIZE_1     0x200   /* 512 */
#else
#define SECTORSIZE_1     FTW_WEB_IMAGE_SECTOR_SIZE   /*From builder */
#endif

#define SECTORPERBLOCK_1 ( BLOCKSIZE_1 / SECTORSIZE_1 )
#endif

static UINT32   FTW_FS_webAddrGet(UINT32 cbAddr);
static UINT32   FTW_FS_config(void);
static void     FTW_FS_configWeb(UINT32 fsAddress, UINT32 fsSize);

static long     FTW_FS_getBlockAddr ( long block, long relsector );
static int      FTW_FS_eraseFlash ( long block );
static int      FTW_FS_writeFlash ( void * data, long block, long relsector, long size, long relpos );
static int      FTW_FS_verifyFlash ( void * data, long block, long relsector, long size, long relpos );
static int      FTW_FS_readFlash ( void * data, long block, long blockrel, long datalen );

static long     FTW_FS_getBlockAddr_1 ( long block, long relsector );
static int      FTW_FS_eraseFlash_1 ( long block );
static int      FTW_FS_writeFlash_1 ( void * data, long block, long relsector, long size, long relpos );
static int      FTW_FS_verifyFlash_1 ( void * data, long block, long relsector, long size, long relpos );
static int      FTW_FS_readFlash_1 ( void * data, long block, long blockrel, long datalen );

extern int FTW_FS_N25Q32MB3V65NM( FS_FLASH * flash );
extern int FTW_FS_N25Q32MB3V65NM_1( FS_FLASH * flash );

extern GSN_OSAL_BYTE_POOL_T romFreeMemPool;
extern UINT32               webFsOffset;
extern UINT32               romFwImageFlashAddr;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

//static int dmaDoneFlag = 0;
UINT32 webFsOffset;
/* Please check maximum storeable file and used sector number in FSmem.exe */

void FTW_FS_init(void)
{
	UINT32 memsize;
	INT32 rc;
	UINT8 *pFsBuff;
    
    if (s2wappMainTaskCtxt->fsInit == TRUE)
    {
        return;
    }

    FTW_FS_config();
	f_init();
	f_enterFS();
    
	memsize = fs_getmem_flashdrive(FTW_FS_N25Q32MB3V65NM);
	pFsBuff = gsn_malloc(memsize);
    
    if(pFsBuff != NULL)
    {
		rc = f_mountdrive(0, pFsBuff, memsize, (void *)fs_mount_flashdrive,
                          FTW_FS_N25Q32MB3V65NM);
		if(rc == F_ERR_NOTFORMATTED)
		{
			f_format(0);
		}
	}
#ifdef FTW_WEB_FS_AVAILABLE
	webFsOffset = FTW_FS_webAddrGet(romFwImageFlashAddr);
	if(webFsOffset != 0)
	{
		memsize = fs_getmem_flashdrive(FTW_FS_N25Q32MB3V65NM_1);
		pFsBuff = gsn_malloc(memsize);
		if(pFsBuff != NULL)
		{
			rc = f_mountdrive(1, pFsBuff, memsize, (void *)fs_mount_flashdrive,
                              FTW_FS_N25Q32MB3V65NM_1);
		}
	}
#endif	
    
    s2wappMainTaskCtxt->fsInit = TRUE;

}

#ifdef CONFIG_FROM_SUPERBLOCK

UINT32 block_start, desc_block_start, max_blocks;

UINT32 FTW_FS_config(void)
{
	GSN_BRFLASHLDR_SUPERBLOCK_T superBlock;

	GsnFlashCache_BlkFetch(GSN_FWUP_SUPER_BLOCK_ADDR, (UINT32)&superBlock, sizeof(superBlock), NULL);

    if (strncmp((const char*)superBlock.flok, "flok", 4) != 0)
    {
        return 1;
    }
    desc_block_start = superBlock.fsAddress / BLOCKSIZE;
    block_start = desc_block_start + DESCBLOCKS;
    max_blocks = superBlock.fsSize / BLOCKSIZE;
	max_blocks = max_blocks - DESCBLOCKS;
    return 0;
}
#endif

void dmaDoneCb(void *ctx, int channelId)
{
#if 0
	dmaDoneFlag = 1;
#endif
}


long FTW_FS_getBlockAddr ( long block, long relsector )
{
	return ((BLOCKSIZE * block) + (relsector * SECTORSIZE));
}


int FTW_FS_eraseFlash ( long block )
{
	long  addr = FTW_FS_getBlockAddr( block, 0 );
    GsnFlashIf_PioReq();
	GsnFlashIf_FlashErase(addr, BLOCKSIZE, TRUE);
    GsnFlashIf_PioRelease();
	return 0;
}

int FTW_FS_writeFlash ( void * data, long block, long relsector, long size, long relpos )
{
	long  addr = FTW_FS_getBlockAddr( block, relsector ) + relpos;
	
	GsnFlashIf_PioReq();
	if((addr & 0xff))
	{
		/* work around for bug */
		int remBytes = 	0x100 - (addr & 0xff);
		if(remBytes < size)
		{
			GsnFlashIf_FlashProgram(addr, remBytes, data, TRUE);
			size -= remBytes;
			addr = addr + remBytes;
			data = (char*)data + remBytes;
		}
	}
	GsnFlashIf_FlashProgram(addr, size, data, TRUE);
	GsnFlashIf_PioRelease();
    if(size & 3)
    {
        return 0;
    }
	if((int)data & 0x3)
	{
		return 0;
	}
	return 0;
}

int FTW_FS_verifyFlash ( void * data, long block, long relsector, long size, long relpos )
{
#if 1
	long  addr = FTW_FS_getBlockAddr( block, relsector ) + relpos;
	UINT8 *pBuf, *pScr, *pDst;
	UINT32 index;
	pBuf = MALLOC(size);
	GsnFlashCache_BlkFetch(addr, (UINT32)pBuf, size, NULL);
	pScr = data;
	pDst = pBuf;
	for(index = 0; index < size; index++)
	{
		if( *pScr++ != *pDst++)
		{
			FREE(pBuf);
			return 1;
		}
	}
	FREE(pBuf);
#endif	
	return 0;
}

int FTW_FS_readFlash ( void * data, long block, long blockrel, long datalen )
{
	long  addr = FTW_FS_getBlockAddr( block, 0 ) + blockrel;
#if 1	
	void *pActData;
	int remBytes/*, index*/;
	//long actDLen = datalen;
	pActData = data;
	//GSN_DMA_T GsnDma;
	//GSN_DMA_CHANNEL_CONFIG_T ptChannelConfig;
	if((int)data & 0x3)
	{
		remBytes = (4 - (int)data &0x3);
		data = (char *)data + remBytes;
		datalen -= remBytes;
	}
	
	GsnFlashCache_BlkFetch(addr, (UINT32)data, datalen, NULL);
#if 0	
	if(data != pActData)
	{
		unsigned int lastData;
		char *pTmp;
		
		GsnDma_Open (&GsnDma, NULL, 1);
		ptChannelConfig.channelBitField.dmaCycleType   = GSN_DMACYCLE_MSG_ALTERNATE ;
	    ptChannelConfig.channelBitField.nextUserBurst  = 1;
	    ptChannelConfig.channelBitField.nMinusOne      = 0;
	    ptChannelConfig.channelBitField.rPower         = GSN_ARBITRATION_1024_DMATRANSFER;
	    ptChannelConfig.channelBitField.srcPrtCntl     = 7;
	    ptChannelConfig.channelBitField.destPrtCntl    = 7;
	    ptChannelConfig.channelBitField.srcSize        = GSN_DMA_BYTE_SRC_SIZE;
	    ptChannelConfig.channelBitField.srcInc         = GSN_DMA_BYTE_SRC_INC;
	    ptChannelConfig.channelBitField.destSize       = GSN_DMA_BYTE_DEST_SIZE;
	    ptChannelConfig.channelBitField.destInc        = GSN_DMA_BYTE_DEST_INC;

        GsnDma_CallBackRegister((GSN_DMA_T *)(&GsnDma),
	                                        (DMACALLBACK_FP)dmaDoneCb,NULL ,
	                                                    0);
	                                                    
	    GsnDma_CycleControl(&GsnDma,&ptChannelConfig, 0,
	    	datalen, data, pActData);
            
	    GsnDma_ChannelEnable(&GsnDma, 0);

	    GsnDma_Enable(&GsnDma);
	    while (!dmaDoneFlag)
        {
            GsnDma_ChannelSoftwareRequest(&GsnDma,0);
        }
        dmaDoneFlag = 0;
	    addr = addr + datalen;
	    data = (char *)pActData + datalen;
		GsnFlashCache_BlkFetch(addr, (UINT32)&lastData, 4, NULL);
		index = (int)pActData & 0x3;
		pTmp = (char *)&lastData;
		while (remBytes >= index)
		{
			*(char *) data = *(pTmp + index);
			index++;
			data = (char *)data + 1;
		}
		//GsnDma_Disable(&GsnDma);
	    DMA_CPAC_SET(GsnDma.pReg,1); 
		GsnDma_Close(&GsnDma);
	 }
#else	 
	if(data != pActData)
	{
		char lastData[4];
		char *pTmp;
		memcpy(pActData, data, datalen);
		addr = addr + datalen;
		data = (char *)pActData + datalen;
		GsnFlashCache_BlkFetch(addr, (UINT32)lastData, 4, NULL);
								
		pTmp = (char *)lastData;
		while (remBytes)
		{
						*(char *) data = *pTmp++;
						remBytes--;
						data = (char *)data + 1;
		}
	}
#endif	
#else
	GsnFlashIf_PioReq();
	GsnFlashIf_FlashRead(addr, datalen, data);
	GsnFlashIf_PioRelease();
#endif
	return 0;
}

int FTW_FS_blockCopy( long destblock, long soublock )
{
	long  destAddr = FTW_FS_getBlockAddr( destblock, 0 );
	long  souAddr = FTW_FS_getBlockAddr( soublock, 0 );
	UINT8 *pBuf, count;
	int index, copySize = BLOCKSIZE << 1;
	do
	{
		copySize = copySize >> 1;
		pBuf = MALLOC(copySize);
	}while((pBuf == NULL) && copySize);
	if(copySize == 0)
	{
		return 1;
	}
	count = BLOCKSIZE / copySize;
	
	GsnFlashIf_PioReq();
	GsnFlashIf_FlashSectorErase(destAddr, TRUE);
	GsnFlashIf_PioRelease();
	
	for(index = 0; index < count; index++)
	{
		GsnFlashCache_BlkFetch(souAddr, (UINT32)pBuf, copySize, NULL);
		GsnFlashIf_PioReq();
		GsnFlashIf_FlashProgram(destAddr, copySize, pBuf, TRUE);
		GsnFlashIf_PioRelease();
		souAddr += copySize;
		destAddr += copySize;
	}
	FREE(pBuf);
	return 0;
}


int FTW_FS_N25Q32MB3V65NM( FS_FLASH * flash )
{
	flash->ReadFlash    = FTW_FS_readFlash;       /* read content */
	flash->EraseFlash   = FTW_FS_eraseFlash;     /* erase a block */
  	flash->WriteFlash   = FTW_FS_writeFlash;     /* write content */
  	flash->VerifyFlash  = FTW_FS_verifyFlash;   /* verify content */
  	flash->BlockCopy    = FTW_FS_blockCopy;
#ifdef CONFIG_FROM_SUPERBLOCK
  	flash->descblockstart = desc_block_start;
    flash->blockstart = block_start;
    flash->maxblock = max_blocks;
    flash->descblockend = desc_block_start + DESCBLOCKS - 1;
#else
    flash->descblockstart = DESCBLOCKSTART;
  	flash->blockstart = BLOCKSTART;     /* where 1st block starts */
  	flash->maxblock = MAXBLOCKS;
	flash->descblockend = DESCBLOCKSTART + DESCBLOCKS - 1; /*  num of last desc block  */
#endif

    flash->blocksize = BLOCKSIZE;
    flash->sectorsize = SECTORSIZE;
    flash->sectorperblock = SECTORPERBLOCK;
    flash->descsize = DESCSIZE;         
    flash->cacheddescsize = DESCCACHE;                     /*  size of write cache in descriptor  */
    return 0;
}

#ifdef FTW_WEB_FS_AVAILABLE

UINT32 block_start_1, desc_block_start_1, max_blocks_1;

void FTW_FS_configWeb(UINT32 fsAddress, UINT32 fsSize)
{
	//desc_block_start_1 = fsAddress / BLOCKSIZE_1;
    //block_start_1 = desc_block_start_1 + DESCBLOCKS_1;
    max_blocks_1 = fsSize / BLOCKSIZE_1;
    max_blocks_1 = max_blocks_1 - DESCBLOCKS_1;
}

long FTW_FS_getBlockAddr_1 ( long block, long relsector )
{
	return (webFsOffset + (BLOCKSIZE_1 * block) + (relsector * SECTORSIZE_1));
}

int FTW_FS_eraseFlash_1 ( long block )
{
	long  addr = FTW_FS_getBlockAddr_1( block, 0 );
    GsnFlashIf_PioReq();
	GsnFlashIf_FlashErase(addr, BLOCKSIZE_1, TRUE);
    GsnFlashIf_PioRelease();
	return 0;
}

int FTW_FS_writeFlash_1 ( void * data, long block, long relsector, long size, long relpos )
{
	long  addr = FTW_FS_getBlockAddr_1( block, relsector ) + relpos;
	
	GsnFlashIf_PioReq();
#if 0	
	if((addr & 0xff))
	{
		/* work around for bug */
		int remBytes = 	0x100 - (addr & 0xff);
		if(remBytes < size)
		{
			GsnFlashIf_FlashProgram(addr, remBytes, data, TRUE);
			size -= remBytes;
			addr = addr + remBytes;
			data = (char*)data + remBytes;
		}
	}
#endif	
	GsnFlashIf_FlashProgram(addr, size, data, TRUE);
	GsnFlashIf_PioRelease();
    if(size & 3)
    {
        return 0;
    }
	if((int)data & 0x3)
	{
		return 0;
	}
	return 0;
}

int FTW_FS_verifyFlash_1 ( void * data, long block, long relsector, long size, long relpos )
{
#if 1
	long  addr = FTW_FS_getBlockAddr_1( block, relsector ) + relpos;
	UINT8 *pBuf, *pScr, *pDst;
	UINT32 index;
	pBuf = MALLOC(size);
	GsnFlashCache_BlkFetch(addr, (UINT32)pBuf, size, NULL);
	pScr = data;
	pDst = pBuf;
	for(index = 0; index < size; index++)
	{
		if( *pScr++ != *pDst++)
		{
			FREE(pBuf);
			return 1;
		}
	}
	FREE(pBuf);
#endif	
	return 0;
}

int FTW_FS_readFlash_1 ( void * data, long block, long blockrel, long datalen )
{
	long  addr = FTW_FS_getBlockAddr_1( block, 0 ) + blockrel;
#if 1       
	void *pActData;
	int remBytes;
	//long actDLen = datalen;
	pActData = data;
	//GSN_DMA_T GsnDma;
	//GSN_DMA_CHANNEL_CONFIG_T ptChannelConfig;
	if((int)data & 0x3)
	{
					remBytes = (4 - (int)data &0x3);
					data = (char *)data + remBytes;
					datalen -= remBytes;
	}
	
	GsnFlashCache_BlkFetch(addr, (UINT32)data, datalen, NULL);
#if 0       
	if(data != pActData)
	{
					unsigned int lastData;
					char *pTmp;
					
					GsnDma_Open (&GsnDma, NULL, 1);
					ptChannelConfig.channelBitField.dmaCycleType   = GSN_DMACYCLE_MSG_ALTERNATE ;
		ptChannelConfig.channelBitField.nextUserBurst  = 1;
		ptChannelConfig.channelBitField.nMinusOne	   = 0;
		ptChannelConfig.channelBitField.rPower		   = GSN_ARBITRATION_1024_DMATRANSFER;
		ptChannelConfig.channelBitField.srcPrtCntl	   = 7;
		ptChannelConfig.channelBitField.destPrtCntl    = 7;
		ptChannelConfig.channelBitField.srcSize 	   = GSN_DMA_BYTE_SRC_SIZE;
		ptChannelConfig.channelBitField.srcInc		   = GSN_DMA_BYTE_SRC_INC;
		ptChannelConfig.channelBitField.destSize	   = GSN_DMA_BYTE_DEST_SIZE;
		ptChannelConfig.channelBitField.destInc 	   = GSN_DMA_BYTE_DEST_INC;

		GsnDma_CallBackRegister((GSN_DMA_T *)(&GsnDma),
														(DMACALLBACK_FP)dmaDoneCb,NULL ,
																	0);
																	
		GsnDma_CycleControl(&GsnDma,&ptChannelConfig, 0,
					datalen, data, pActData);

		GsnDma_ChannelEnable(&GsnDma, 0);

		GsnDma_Enable(&GsnDma);
		while (!dmaDoneFlag)
		{
			GsnDma_ChannelSoftwareRequest(&GsnDma,0);
		}
		dmaDoneFlag = 0;
		addr = addr + datalen;
		data = (char *)pActData + datalen;
		GsnFlashCache_BlkFetch(addr, (UINT32)&lastData, 4, NULL);
		index = (int)pActData & 0x3;
		pTmp = (char *)&lastData;
		while (remBytes >= index)
		{
						*(char *) data = *(pTmp + index);
						index++;
						data = (char *)data + 1;
		}
		//GsnDma_Disable(&GsnDma);
		DMA_CPAC_SET(GsnDma.pReg,1); 
		GsnDma_Close(&GsnDma);
	}
#else     
	if(data != pActData)
	{
		char lastData[4];
		char *pTmp;
		memcpy(pActData, data, datalen);
		addr = addr + datalen;
		data = (char *)pActData + datalen;
		GsnFlashCache_BlkFetch(addr, (UINT32)lastData, 4, NULL);
								
		pTmp = (char *)lastData;
		while (remBytes)
		{
						*(char *) data = *pTmp++;
						remBytes--;
						data = (char *)data + 1;
		}
	}
#endif   
#else
	GsnFlashIf_PioReq();
	GsnFlashIf_FlashRead(addr, datalen, data);
	GsnFlashIf_PioRelease();
#endif
	return 0;
}


int FTW_FS_blockCopy_1( long destblock, long soublock )
{
	long  destAddr = FTW_FS_getBlockAddr_1( destblock, 0 );
	long  souAddr = FTW_FS_getBlockAddr_1( soublock, 0 );
	UINT8 *pBuf, count;
	int index, copySize = BLOCKSIZE_1 << 1;
	do
	{
		copySize = copySize >> 1;
		pBuf = MALLOC(copySize);
	}while((pBuf == NULL) && copySize);
	if(copySize == 0)
	{
		return 1;
	}
	count = BLOCKSIZE_1 / copySize;
	
	GsnFlashIf_PioReq();
	GsnFlashIf_FlashSectorErase(destAddr, TRUE);
	GsnFlashIf_PioRelease();
	
	for(index = 0; index < count; index++)
	{
		GsnFlashCache_BlkFetch(souAddr, (UINT32)pBuf, copySize, NULL);
		GsnFlashIf_PioReq();
		GsnFlashIf_FlashProgram(destAddr, copySize, pBuf, TRUE);
		GsnFlashIf_PioRelease();
		souAddr += copySize;
		destAddr += copySize;
	}
	GsnOsal_ByteRelease(pBuf);
	return 0;
}

int FTW_FS_N25Q32MB3V65NM_1( FS_FLASH * flash )
{
	flash->ReadFlash    = FTW_FS_readFlash_1;       /* read content */
	flash->EraseFlash   = FTW_FS_eraseFlash_1;     /* erase a block */
  	flash->WriteFlash   = FTW_FS_writeFlash_1;     /* write content */
  	flash->VerifyFlash  = FTW_FS_verifyFlash_1;   /* verify content */
  	flash->BlockCopy    = FTW_FS_blockCopy_1;

	//flash->maxblock = MAXBLOCKS_1;
	flash->maxblock = max_blocks_1;
	flash->blocksize = BLOCKSIZE_1;
	flash->sectorsize = SECTORSIZE_1;
	flash->sectorperblock = SECTORPERBLOCK_1;
	flash->blockstart = BLOCKSTART_1;     /* where 1st block starts */
	//flash->blockstart = block_start_1;
	flash->descsize = DESCSIZE_1;         /* 128K      */
	flash->descblockstart = DESCBLOCKSTART_1;
	//flash->descblockstart = desc_block_start_1;
	flash->descblockend = DESCBLOCKSTART_1 + DESCBLOCKS_1 - 1; /*  num of last desc block  */
	//flash->descblockend = desc_block_start_1 + DESCBLOCKS_1 - 1;
	flash->cacheddescsize = DESCCACHE_1;                     /*  size of write cache in descriptor  */
	return 0;
}

#endif

#endif

#ifdef FTW_WEB_FS_AVAILABLE
UINT32 FTW_FS_webAddrGet(UINT32 cbAddr)
{
	GSN_BRFLASHLDR_CTL_BLOCK_T CtlBlk;
	UINT32 cbSize, /*flashBlkDescAddr,*/ fsAddr, fsSize;
	UINT8 *pControlBlock, *pBlkDesc, *pBlkDescEnd;
	
	GsnFlashCache_BlkFetch(cbAddr, (UINT32)&CtlBlk, sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T), NULL);
	cbSize = CtlBlk.ctlBlockSize + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);
	//S2w_Printf("Cb size %d", cbSize);
	pControlBlock = MALLOC(cbSize);
	if(pControlBlock == NULL)
	{
		return 0;
	}
	GsnFlashCache_BlkFetch(cbAddr, (UINT32)pControlBlock, cbSize, NULL);
	pBlkDesc  = pControlBlock + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);
	pBlkDescEnd = pBlkDesc + CtlBlk.ctlBlockSize;
	while(pBlkDesc < pBlkDescEnd)
	{
		//S2w_Printf("Off %x, size %x", ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->offset, ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->size);
		if((((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->owner == GSN_BRFLASHLDR_BLOCK_OWNER_AFW) && 
           (((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->flags & GSN_BRFLASHLDR_BLOCK_DESC_FLAG_WEBFS))
		{
			fsAddr = (cbAddr + ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->offset);
			fsSize = ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->size;
			FTW_FS_configWeb(fsAddr, fsSize);
			return fsAddr;
		}
		pBlkDesc += sizeof(GSN_BRFLASHLDR_BLOCK_DESC_T);
	}
	return 0;
}

#endif