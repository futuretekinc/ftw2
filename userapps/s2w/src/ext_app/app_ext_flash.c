/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by GainSpan
* Corporation or its licensors.  Title to the Material remains
* with GainSpan Corporation or its suppliers and licensors.
*
* The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used,
* copied, reproduced, modified, published, uploaded, posted, transmitted,
* distributed, or disclosed in any way except in accordance with the
* applicable license agreement.
*
* No license under any patent, copyright, trade secret or other
* intellectual property right is granted to or conferred upon you by
* disclosure or delivery of the Materials, either expressly, by
* implication, inducement, estoppel, except in accordance with the
* applicable license agreement.
*
* Unless otherwise agreed by GainSpan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by GainSpan
* or GainSpan's suppliers or licensors in any way.
*
* $RCSfile: app_ext_flash.c,v
*/

#include "gsn_includes.h"
#include "safe-flash\nor\flashdrv.h"
#include "ext_app\app_ext_flash.h"

#include "gsn_br_flashldr.h"
#include "main\app_main_ctx.h"


/* Please check maximum storeable file and used sector number in FSmem.exe */
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

VOID
AppExtFlash_Init(GSN_FLASH_SPI_FLAG_T spiFlag)
{
	if(s2wappMainTaskCtxt->extFlashCtx.extFlashStatus == EXTFLASH_INITIALIZED)
	{
		return ;
	}
	if (s2wappMainTaskCtxt->extFlashCtx.spiPinConf != APP_SPI_ALL_PIN_CONF)
	{
		/*    GPIO Mux enable for SPI Port-1	   */
#ifdef GS2100MS_EVB
		GsnIoMux_Sel(6, 3); // DIN
		GsnIoMux_PullDownEnable (6);
	    GsnIoMux_Sel(5, 3); // CLK
		GsnIoMux_PullDownEnable (5);
		GsnIoMux_Sel(10, 0); // CS
		GsnIoMux_PullDownDisable (10);
		GsnIoMux_Sel(31, 4); // DOUT
		GsnIoMux_PullDownEnable (31);
#elif GS2100M_EVB
		GsnIoMux_Sel(30, 4); // DIN
		GsnIoMux_PullDownEnable (30);
		GsnIoMux_Sel(28, 4); // CLK
		GsnIoMux_PullDownEnable (28);

		GsnIoMux_Sel(10, 0); // CS
		GsnIoMux_PullDownDisable (10);
		GsnIoMux_Sel(31, 4); // DOUT
		GsnIoMux_PullDownEnable (31);		
#elif GS2011M_EVB2_0
		/* by default GS2011M_EVB GPIO Mux enable */
		GsnIoMux_Sel(30, 4); // DIN
		GsnIoMux_PullDownEnable (30);
		GsnIoMux_Sel(5, 3); // CLK
		GsnIoMux_PullDownEnable (5);

		GsnIoMux_Sel(10, 0); // CS
		GsnIoMux_PullDownDisable (10);

		GsnIoMux_Sel(31, 4); // DOUT
		GsnIoMux_PullDownEnable (31);
#else
		GsnIoMux_Sel(6, GSN_IOMUX_GPIO_6_ASSP1_DIN); // DIN
		GsnIoMux_PullDownEnable (6);
		GsnIoMux_Sel(5, GSN_IOMUX_GPIO_5_ASSP1_CLK); // CLK
		GsnIoMux_PullDownEnable (5);

		GsnIoMux_Sel(13, GSN_IOMUX_GPIO_13_AGPIO_13); // CS
		GsnIoMux_PullDownDisable (13);
		GsnIoMux_Sel(7, GSN_IOMUX_GPIO_7_ASSP1_DOUT); // DOUT
		GsnIoMux_PullDownEnable (7);
#endif	
		/* Use SPI CS pin10 as GPIO to control from driver */
		GsnGpio_Init(GS2011_SPI_CS, GS2011_SPI_CS_DIRMAP);
		s2wappMainTaskCtxt->extFlashCtx.spiCsGpio = GS2011_SPI_CS;
	}
	
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.spiMode			= GSN_SPI_OPERATION_MODE_MASTER;
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.clockDivider 		= 2; 
		
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.spiProtocol		= GSN_SPI_PROTOCOL_MOTOROLA;
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.clockSelect		= GSN_SPI_CLK_XTAL; //GSN_SPI_CLK_XTAL;GSN_SPI_CLK_HSRC
	
	/*	  SPI Mode-1	*/
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.clockPolarity		= GSN_SPI_CLK_POL_INACTIVEHIGH;
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.clockPhase		= GSN_SPI_CLK_PHASE_180;
	s2wappMainTaskCtxt->extFlashCtx.spiConfig.dataWordSize 		= GSN_SPI_DATAWORDSIZE_8;
	s2wappMainTaskCtxt->extFlashCtx.spiFlagFs					= spiFlag;


	if(spiFlag == GSN_FLASH_SPI_POLL)
		s2wappMainTaskCtxt->extFlashCtx.spiConfig.dmaMode		= GSN_SPI_DMA_CLEAR;
	else
		s2wappMainTaskCtxt->extFlashCtx.spiConfig.dmaMode		= GSN_SPI_DMA_SET;

	
	GsnExtFlash_Init(&s2wappMainTaskCtxt->extFlashCtx,SPI_NUM_1,&s2wappMainTaskCtxt->extFlashCtx.spiConfig,s2wappMainTaskCtxt->extFlashCtx.spiFlagFs);

	s2wappMainTaskCtxt->extFlashCtx.extFlashStatus = EXTFLASH_INITIALIZED;
	
}


#ifdef S2W_EXT_FLASH_FS_SUPPORT

UINT32 AppExtFlash_FsConfig()
{
	GSN_BRFLASHLDR_SUPERBLOCK_T superBlock;
    GSN_BRFLASHLDR_CTL_BLOCK_T fwCtlBlk, fw0CtlBlk, fw1CtlBlk, fw2CtlBlk;
	UINT32 cbAddress = 0, descOffset = 0, descSize = 0;        
        
    UINT32 cbSize;
	UINT8 *pControlBlock, *pBlkDesc;
        
	GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx,sizeof(superBlock),0,(UINT8 *)&superBlock,GSN_FLASH_SPI_POLL,NULL,NULL);

    if (strncmp((const char*)superBlock.flok, "flok", 4) != 0)
    {
    	s2wappMainTaskCtxt->extFlashCtx.descBlockStart = DESCBLOCKSTART_EF;
		s2wappMainTaskCtxt->extFlashCtx.blockStart		= BLOCKSTART_EF;
		s2wappMainTaskCtxt->extFlashCtx.maxBlocks		= MAXBLOCKS_EF;
        return 1;
    }
	
    /* read control blocks of all fw images */
    GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx, sizeof(fw0CtlBlk), superBlock.fw0Cb1Addr, (UINT8 *)&fw0CtlBlk, GSN_FLASH_SPI_POLL, NULL, NULL);
    GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx, sizeof(fw1CtlBlk), superBlock.fw1Cb1Addr, (UINT8 *)&fw1CtlBlk, GSN_FLASH_SPI_POLL, NULL, NULL);
    GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx, sizeof(fw2CtlBlk), superBlock.fw2Cb1Addr, (UINT8 *)&fw2CtlBlk, GSN_FLASH_SPI_POLL, NULL, NULL);

	if((fw0CtlBlk.rev)>(fw1CtlBlk.rev)&&(fw0CtlBlk.rev)>(fw2CtlBlk.rev))
	{
    	fwCtlBlk = fw0CtlBlk;
		cbAddress = superBlock.fw0Cb1Addr;
	}
   else if((fw1CtlBlk.rev)>(fw2CtlBlk.rev))
    {
    	fwCtlBlk = fw1CtlBlk;
		cbAddress = superBlock.fw1Cb1Addr;
   	}
   else
   	{
    	fwCtlBlk = fw2CtlBlk;
		cbAddress = superBlock.fw2Cb1Addr;
   	}

    cbSize = fwCtlBlk.ctlBlockSize + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);

    pControlBlock = MALLOC(cbSize);
    if(pControlBlock == NULL)
    {
	return 2;
    }
    
    GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx, cbSize, cbAddress, (UINT8 *)pControlBlock, GSN_FLASH_SPI_POLL, NULL, NULL);
    pBlkDesc  = pControlBlock + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);
        
    descOffset = ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->offset;
    descSize = ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->size;
    
    s2wappMainTaskCtxt->extFlashCtx.descBlockStart = (descOffset + cbAddress)/BLOCKSIZE_EF; 
    s2wappMainTaskCtxt->extFlashCtx.blockStart = DESCBLOCKS_EF + s2wappMainTaskCtxt->extFlashCtx.descBlockStart;
    s2wappMainTaskCtxt->extFlashCtx.maxBlocks = descSize / BLOCKSIZE_EF; 
	s2wappMainTaskCtxt->extFlashCtx.maxBlocks = s2wappMainTaskCtxt->extFlashCtx.maxBlocks - DESCBLOCKS_EF;

	FREE(pControlBlock);
	return 0;
}


int AppExtFlash_FsMount ( FS_FLASH * flash )
{
	flash->ReadFlash = GsnExtFlash_FsRead;       /* read content */
	flash->EraseFlash = GsnExtFlash_FsErase;     /* erase a block */
  	flash->WriteFlash = GsnExtFlash_FsWrite;     /* write content */
  	flash->VerifyFlash = GsnExtFlash_FsVerifyFlash;   /* verify content */
  	flash->BlockCopy = GsnExtFlash_FsBlockCopy;

	flash->maxblock = s2wappMainTaskCtxt->extFlashCtx.maxBlocks;
	flash->blocksize = BLOCKSIZE_EF;
	flash->sectorsize = SECTORSIZE_EF;
	flash->sectorperblock = SECTORPERBLOCK_EF;
	flash->blockstart = s2wappMainTaskCtxt->extFlashCtx.blockStart;	   /* where 1st block starts */
	flash->descsize = DESCSIZE_EF;		   /* 128K		*/
	flash->descblockstart = s2wappMainTaskCtxt->extFlashCtx.descBlockStart;
	flash->descblockend = s2wappMainTaskCtxt->extFlashCtx.descBlockStart + DESCBLOCKS_EF - 1; /*  num of last desc block  */
	flash->cacheddescsize = DESCCACHE_EF;					  /*  size of write cache in descriptor  */
	return 0;
}

VOID
AppExtFlash_FsInit()
{
	UINT32 memsize;
	INT32 rc;
	UINT8 *pFsBuff;

	if(s2wappMainTaskCtxt->extFlashCtx.extFlashStatus == EXTFLASH_NOT_INITIALIZED)
	{
		AppExtFlash_Init(GSN_FLASH_SPI_POLL);
	}
	
	GsnExtFlash_FsInit(&s2wappMainTaskCtxt->extFlashCtx);

	AppExtFlash_FsConfig();

	memsize = fs_getmem_flashdrive(AppExtFlash_FsMount);
	pFsBuff = gsn_malloc(memsize);

    if(pFsBuff != NULL)
    {
		rc = f_mountdrive(APP_EXT_FLASH_DRIVE_NUM_2, pFsBuff, memsize, (void *)fs_mount_flashdrive,
			AppExtFlash_FsMount);
                
		if(rc == F_ERR_NOTFORMATTED)
		{
                    f_format(APP_EXT_FLASH_DRIVE_NUM_2);
		}

	}
}


UINT32 AppExtFlash_DataFsConfig()
{
	GSN_BRFLASHLDR_SUPERBLOCK_T superBlock_D;
	
	GsnExtFlash_Read(&s2wappMainTaskCtxt->extFlashCtx,sizeof(superBlock_D),0,(UINT8 *)&superBlock_D,GSN_FLASH_SPI_POLL,NULL,NULL);

    if (strncmp((const char*)superBlock_D.flok, "flok", 4) != 0)
    {
    	s2wappMainTaskCtxt->extFlashCtx.descBlockStart_D = DESCBLOCKSTART_EF;
		s2wappMainTaskCtxt->extFlashCtx.blockStart_D	  = BLOCKSTART_EF;
		s2wappMainTaskCtxt->extFlashCtx.maxBlocks_D	  = MAXBLOCKS_EF;
        return 1;
    }
	
    s2wappMainTaskCtxt->extFlashCtx.descBlockStart_D = superBlock_D.fsAddress / BLOCKSIZE_EF;
    s2wappMainTaskCtxt->extFlashCtx.blockStart_D = DESCBLOCKS_EF + s2wappMainTaskCtxt->extFlashCtx.descBlockStart_D;
    s2wappMainTaskCtxt->extFlashCtx.maxBlocks_D = superBlock_D.fsSize / BLOCKSIZE_EF;
	s2wappMainTaskCtxt->extFlashCtx.maxBlocks_D = s2wappMainTaskCtxt->extFlashCtx.maxBlocks_D - DESCBLOCKS_EF;
    return 0;
}


int AppExtFlash_DataFsMount ( FS_FLASH * flash )
{
	flash->ReadFlash = GsnExtFlash_FsRead;       /* read content */
	flash->EraseFlash = GsnExtFlash_FsErase;     /* erase a block */
  	flash->WriteFlash = GsnExtFlash_FsWrite;     /* write content */
  	flash->VerifyFlash = GsnExtFlash_FsVerifyFlash;   /* verify content */
  	flash->BlockCopy = GsnExtFlash_FsBlockCopy;

	flash->maxblock = s2wappMainTaskCtxt->extFlashCtx.maxBlocks_D;
	flash->blocksize = BLOCKSIZE_EF;
	flash->sectorsize = SECTORSIZE_EF;
	flash->sectorperblock = SECTORPERBLOCK_EF;
	flash->blockstart = s2wappMainTaskCtxt->extFlashCtx.blockStart_D;	   /* where 1st block starts */
	flash->descsize = DESCSIZE_EF;		   /* 128K		*/
	flash->descblockstart = s2wappMainTaskCtxt->extFlashCtx.descBlockStart_D;
	flash->descblockend = s2wappMainTaskCtxt->extFlashCtx.descBlockStart_D + DESCBLOCKS_EF - 1; /*  num of last desc block  */
	flash->cacheddescsize = DESCCACHE_EF;					  /*  size of write cache in descriptor  */
	return 0;
}


VOID
AppExtFlash_DataFsInit()
{
	UINT32 memsize;
	INT32 rc;
	UINT8 *pFsBuff;

	if(s2wappMainTaskCtxt->extFlashCtx.extFlashStatus == EXTFLASH_NOT_INITIALIZED)
	{
		AppExtFlash_Init(GSN_FLASH_SPI_POLL);
	}
		
	GsnExtFlash_FsInit(&s2wappMainTaskCtxt->extFlashCtx);

	AppExtFlash_DataFsConfig();

	memsize = fs_getmem_flashdrive(AppExtFlash_DataFsMount);
	pFsBuff = gsn_malloc(memsize);

    if(pFsBuff != NULL)
    {
		rc = f_mountdrive(APP_EXT_FLASH_DRIVE_NUM_3, pFsBuff, memsize, (void *)fs_mount_flashdrive,
			AppExtFlash_DataFsMount);
                
		if(rc == F_ERR_NOTFORMATTED)
		{
                    f_format(APP_EXT_FLASH_DRIVE_NUM_3);
		}

	}
}

#endif

