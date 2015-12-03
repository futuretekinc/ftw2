#ifndef _N25Q_32MB_3V_65NM_C_
#define _N25Q_32MB_3V_65NM_C_

#include "gsn_includes.h"
#include "app_fsIf.h"
#include "dma\gsn_dma.h"
#include "gsn_br_flashldr.h"
#include "safe-flash\nor\flashdrv.h"
#include "drivers\reg\gsn_reg_dma_spec.h"
#include "drivers\reg\gsn_reg_dma_op.h"
#include "app_debug.h"
#include "modules/fwup/gsn_fwup.h"

#define CONFIG_FROM_SUPERBLOCK
#define CONFIG_FROM_IMAGE_BLOCK_DESC

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


#ifdef ADK_PROV_ENABLE
#define BLOCKSIZE_1      0x1000 /*  4K - size of file storage blocks  */
#define BLOCKSTART_1     0x2       /*  logical number of first file storage block  */
#define MAXBLOCKS_1      14      /*  number of logical blocks for file storage  */

#define DESCSIZE_1       0x1000  /*  4k descriptor block size  */
#define DESCBLOCKSTART_1 0x0        /*  logical number of first descriptor block  */
#define DESCBLOCKS_1     2        /*  number of descriptor blocks  */
#define DESCCACHE_1      0x0  /*  1k assigned to write cache for descriptor  */

#ifndef WEB_IMAGE_SIZE_1MB
#define SECTORSIZE_1     0x200   /* 512 */
#else
#define SECTORSIZE_1     0x800   /*2k */
#endif

#define SECTORPERBLOCK_1 ( BLOCKSIZE_1 / SECTORSIZE_1 )
#endif

#ifdef ADK_PROV_ENABLE/* Initialise Appropriate Web Pages Partition */

UINT32 App_WebPagesPartnInfoSet(APP_FS_T *pAppFs);
#endif

UINT32 App_ConfigPartnInfoSet(APP_FS_T *pAppFs);

int fs_phy_nor_n25q_32mb_3v_65nm_1( FS_FLASH * flash );
int fs_phy_nor_n25q_32mb_3v_65nm_0(FS_FLASH * flash );

extern 	UINT32 romFwImageFlashAddr;

#ifdef USE_DMA
static int dmaDoneFlag = 0;
#endif
/* Please check maximum storeable file and used sector number in FSmem.exe */

/*These globals are used in  "fs_phy_nor_n25q_32mb_3v_65nm_xx() "functions */
static APP_FS_PARTITION_INFO_T *pPartn_0_Info;
static APP_FS_PARTITION_INFO_T *pPartn_1_Info;

UINT32 max_blocks_1  = 0;
VOID App_ConfigWebFs(UINT32 fsSize);

GSN_STATUS
App_FsInit(APP_FS_T *pFsCtx)
{
	UINT32 memsize, memsize1;
	INT32 rc;
	UINT8 *pFsBuff, *pFsBuff1;
	
	pPartn_0_Info = &pFsCtx->partn[APP_FS_PARTN_CONFIG];
	pPartn_1_Info = &pFsCtx->partn[APP_FS_PARTN_WEB_PAGES];

	f_init();
	f_enterFS();
    App_ConfigPartnInfoSet(pFsCtx);
	/*Initialise Partition 0 (used cof storing configuration)*/
	memsize = fs_getmem_flashdrive(fs_phy_nor_n25q_32mb_3v_65nm_0);
	pFsBuff = gsn_malloc(memsize);
    if(pFsBuff != NULL)
    {
		rc = f_mountdrive(0, pFsBuff, memsize, (void *)fs_mount_flashdrive,
							fs_phy_nor_n25q_32mb_3v_65nm_0);
		if(rc == F_ERR_NOTFORMATTED)
		{
			f_format(0);
		}
	}
	else
	{
		while(1);
	}
	
#ifdef ADK_PROV_ENABLE/* Initialise Appropriate Web Pages Partition */

	App_WebPagesPartnInfoSet(pFsCtx);

	memsize1 = fs_getmem_flashdrive(fs_phy_nor_n25q_32mb_3v_65nm_1);
	pFsBuff1 = gsn_malloc(memsize1);
	if(pFsBuff != NULL)
	{
		rc = f_mountdrive(1, pFsBuff1, memsize1, (void *)fs_mount_flashdrive,
				fs_phy_nor_n25q_32mb_3v_65nm_1);
        if(rc == F_ERR_NOTFORMATTED)
		{
			return GSN_FAILURE;
		}
	}
	else
	{
		while(1);
	}

#endif	
    return GSN_SUCCESS;
}

UINT32 App_ConfigPartnInfoSet(APP_FS_T *pAppFs)
{
	GSN_BRFLASHLDR_SUPERBLOCK_T superBlock;
	APP_FS_PARTITION_INFO_T *pConfigPartn = &pAppFs->partn[APP_FS_PARTN_CONFIG];
	
#ifdef CONFIG_FROM_SUPERBLOCK	
	GsnFlashCache_BlkFetch(GSN_FWUP_SUPER_BLOCK_ADDR, (UINT32)&superBlock, sizeof(superBlock), NULL);

	if (strncmp((const char*)superBlock.flok, "flok", 4) != 0)
	{
		return 1;
	}
	
	if(0xFFFFFFFF != superBlock.fsAddress)
	{
		pConfigPartn->desc_block_start = superBlock.fsAddress / BLOCKSIZE;
		pConfigPartn->block_start = pConfigPartn->desc_block_start + DESCBLOCKS;
		pConfigPartn->max_blocks = superBlock.fsSize / BLOCKSIZE;
		pConfigPartn->max_blocks = pConfigPartn->max_blocks - DESCBLOCKS;
	}
	else
			
	{		
	    pConfigPartn->desc_block_start = DESCBLOCKSTART;
	    pConfigPartn->block_start = DESCBLOCKSTART + DESCBLOCKS;
		pConfigPartn->max_blocks = MAXBLOCKS - DESCBLOCKS;
	}
#else
	pConfigPartn->desc_block_start = DESCBLOCKSTART;
	pConfigPartn->block_start = DESCBLOCKSTART + DESCBLOCKS;
	pConfigPartn->max_blocks = MAXBLOCKS - DESCBLOCKS;
#endif	

   return 1;
}

void dmaDoneCb(void *ctx, int channelId)
{
#ifdef USE_DMA

	dmaDoneFlag = 1;
#endif
}

static long GetBlockAddr ( long block, long relsector )
{
	return ((BLOCKSIZE * block) + (relsector * SECTORSIZE));
}

static int EraseFlash ( long block )
{
	long  addr = GetBlockAddr( block, 0 );
    GsnFlashIf_PioReq();	
	GsnFlashIf_FlashErase(addr, BLOCKSIZE, TRUE);
    GsnFlashIf_PioRelease();
	return 0;
}

static int WriteFlash ( void * data, long block, long relsector, long size, long relpos )
{
	long  addr = GetBlockAddr( block, relsector ) + relpos;
	
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

static int VerifyFlash ( void * data, long block, long relsector, long size, long relpos )
{

	long  addr = GetBlockAddr( block, relsector ) + relpos;
	UINT8 *pBuf, *pScr, *pDst;
	UINT32 index/*, sectors, rem*/;
	pBuf = gsn_malloc(size);
	if(NULL == pBuf)
	{
		while(1);
	}
	/*GsnFlashIf_PioReq();*/
	/*GsnFlashIf_FlashRead(addr, size, pBuf);*/
	GsnFlashCache_BlkFetch(addr, (UINT32)pBuf, size, NULL);
	/*GsnFlashIf_PioRelease(); */
	pScr = data;
	pDst = pBuf;
	for(index = 0; index < size; index++)
	{
		if( *pScr++ != *pDst++)
		{
			GsnOsal_ByteRelease(pBuf);
			return 1;
		}
	}
	GsnOsal_ByteRelease(pBuf);
	return 0;
}

static int ReadFlash ( void * data, long block, long blockrel, long datalen )
{
	long  addr = GetBlockAddr( block, 0 ) + blockrel;
#if 1	
	void *pActData;
	int remBytes/*, index*/;
	pActData = data;
	/*long actDLen = datalen;
	GSN_DMA_T GsnDma;
	GSN_DMA_CHANNEL_CONFIG_T ptChannelConfig; */
	
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

int BlockCopy( long destblock, long soublock )
{
	long  destAddr = GetBlockAddr( destblock, 0 );
	long  souAddr = GetBlockAddr( soublock, 0 );
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

int fs_phy_nor_n25q_32mb_3v_65nm_0(FS_FLASH * flash )
{	
	flash->ReadFlash = ReadFlash;       /* read content */
	flash->EraseFlash = EraseFlash;     /* erase a block */
  	flash->WriteFlash = WriteFlash;     /* write content */
  	flash->VerifyFlash = VerifyFlash;   /* verify content */
  	flash->BlockCopy = BlockCopy;

  	flash->descblockstart = pPartn_0_Info->desc_block_start;
    flash->blockstart = pPartn_0_Info->block_start;
    flash->maxblock = pPartn_0_Info->max_blocks;
    flash->descblockend = pPartn_0_Info->desc_block_start + DESCBLOCKS - 1;

    flash->blocksize = BLOCKSIZE;
    flash->sectorsize = SECTORSIZE;
    flash->sectorperblock = SECTORPERBLOCK;
    flash->descsize = DESCSIZE;         
    flash->cacheddescsize = DESCCACHE;                     /*  size of write cache in descriptor  */

	return 0;
}


#ifdef ADK_PROV_ENABLE

/*Get the Web pages partition Address from the control block */
UINT32 App_WebPagesPartnAddrGet(UINT32 cbAddr, UINT32 *startAddr, UINT32 *size)
{
	GSN_BRFLASHLDR_CTL_BLOCK_T CtlBlk;
	UINT32 cbSize, fsAddr, fsSize;
	UINT8 *pControlBlock, *pBlkDesc, *pBlkDescEnd;

	*startAddr = *size = 0;
	GsnFlashCache_BlkFetch(cbAddr, (UINT32)&CtlBlk, sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T), NULL);
	cbSize = CtlBlk.ctlBlockSize + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);
	
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
		if((((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->owner == GSN_BRFLASHLDR_BLOCK_OWNER_AFW) && 
				(((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->flags & GSN_BRFLASHLDR_BLOCK_DESC_FLAG_WEBFS))
		{
			fsAddr = (cbAddr + ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->offset);
			fsSize = ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->size;
			*startAddr = fsAddr;
			*size = fsSize;
			return fsAddr;
		}
		pBlkDesc += sizeof(GSN_BRFLASHLDR_BLOCK_DESC_T);
	}
	return 0;
}

UINT32 App_WebPagesPartnInfoSet(APP_FS_T *pAppFs)
{
#ifdef CONFIG_FROM_IMAGE_BLOCK_DESC
	APP_FS_PARTITION_INFO_T *pWebPgPartn = &pAppFs->partn[APP_FS_PARTN_WEB_PAGES];
	UINT32 startAddr, size;
#endif	
#ifdef CONFIG_FROM_IMAGE_BLOCK_DESC

	App_WebPagesPartnAddrGet(romFwImageFlashAddr, &startAddr, &size);

    pWebPgPartn->desc_block_start = startAddr / BLOCKSIZE_1;
    pWebPgPartn->block_start = pWebPgPartn->desc_block_start + DESCBLOCKS_1;
    pWebPgPartn->max_blocks = size / BLOCKSIZE_1;
	pWebPgPartn->max_blocks = pWebPgPartn->max_blocks - DESCBLOCKS_1;

	App_ConfigWebFs(size);
#else	
	/* Default values*/
#endif
    return 0;
}

static long GetBlockAddr_1 ( long block, long relsector )
{
	return ((BLOCKSIZE_1 * block) + (relsector * SECTORSIZE_1));
}

static int EraseFlash_1 ( long block )
{
	long  addr = GetBlockAddr_1( block, 0 );
    GsnFlashIf_PioReq();
	GsnFlashIf_FlashErase(addr, BLOCKSIZE, TRUE);
    GsnFlashIf_PioRelease();
	return 0;
}

static int WriteFlash_1 ( void * data, long block, long relsector, long size, long relpos )
{
	long  addr = GetBlockAddr_1( block, relsector ) + relpos;
	
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

static int VerifyFlash_1 ( void * data, long block, long relsector, long size, long relpos )
{
#if 1
	long  addr = GetBlockAddr_1( block, relsector ) + relpos;
	UINT8 *pBuf, *pScr, *pDst;
	UINT32 index;
	pBuf = gsn_malloc(size);
	/*GsnFlashIf_PioReq();*/
	/*GsnFlashIf_FlashRead(addr, size, pBuf); */
	GsnFlashCache_BlkFetch(addr, (UINT32)pBuf, size, NULL);
	/*GsnFlashIf_PioRelease(); */
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

static int ReadFlash_1 ( void * data, long block, long blockrel, long datalen )
{
	long  addr = GetBlockAddr_1( block, 0 ) + blockrel;
#if 1       
	void *pActData;
	int remBytes;
	pActData = data;
	/*GSN_DMA_T GsnDma;*/
	/*GSN_DMA_CHANNEL_CONFIG_T ptChannelConfig;*/
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

int BlockCopy_1( long destblock, long soublock )
{
	long  destAddr = GetBlockAddr_1( destblock, 0 );
	long  souAddr = GetBlockAddr_1( soublock, 0 );
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
	GsnOsal_ByteRelease(pBuf);
	return 0;
}

#if 1
int fs_phy_nor_n25q_32mb_3v_65nm_1( FS_FLASH * flash )
{
	flash->ReadFlash = ReadFlash_1;       /* read content */
	flash->EraseFlash = EraseFlash_1;     /* erase a block */
  	flash->WriteFlash = WriteFlash_1;     /* write content */
  	flash->VerifyFlash = VerifyFlash_1;   /* verify content */
  	flash->BlockCopy = BlockCopy_1;
	
  	flash->descblockstart = pPartn_1_Info->desc_block_start;
    flash->blockstart = pPartn_1_Info->block_start;
    flash->maxblock = pPartn_1_Info->max_blocks;
    flash->descblockend = pPartn_1_Info->desc_block_start + DESCBLOCKS_1 - 1;

    flash->blocksize = BLOCKSIZE_1;
    flash->sectorsize = SECTORSIZE_1;
    flash->sectorperblock = SECTORPERBLOCK_1;
    flash->descsize = DESCSIZE_1;         
    flash->cacheddescsize = DESCCACHE_1;/*  size of write cache in descriptor  */
    
    return 0;
}

VOID App_ConfigWebFs(UINT32 fsSize)
{
    max_blocks_1 = fsSize / BLOCKSIZE_1;
    max_blocks_1 = max_blocks_1 - DESCBLOCKS_1;
}

#else

int fs_phy_nor_n25q_32mb_3v_65nm_1( FS_FLASH * flash )
{
	flash->ReadFlash = ReadFlash_1;       /* read content */
	flash->EraseFlash = EraseFlash_1;     /* erase a block */
  	flash->WriteFlash = WriteFlash_1;     /* write content */
  	flash->VerifyFlash = VerifyFlash_1;   /* verify content */
  	flash->BlockCopy = BlockCopy_1;

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
#endif/* ADK_PROV_ENABLE */

#endif

