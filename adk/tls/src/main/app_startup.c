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
* $RCSfile: app_startup.c,v $
*******************************************************************************/
/*
Different memory section placed in SRAM is given below
	  _________________________________________ 0x20000000	
	|										|
	|	16KB reserved for ROM PATCH AUTO	|
	|										|
	|---------------------------------------|
	|										|	 
	|	8KB reserved for ROM PATCH FPT		|
	|										|
	|---------------------------------------|
	|										|
	|	8KB reserved for predefined heap	|
	|			  ( Heap 1) 				|
	|---------------------------------------|
	|										|
	|										|
	|	CSTACK, 							|
	|										|
	|	(APP + ROM )data section			|
	|										|
	|---------------------------------------|
	|										|
	|	Heap 2								|
	|										|
	|---------------------------------------|
	|										|
	|	App Code							|
	|										|
	|---------------------------------------|
	|										|
	|	Heap 3								|
	|										|
	|---------------------------------------| 0x2007FFFF
	
*/
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

#include "gsn_includes.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "battery/app_batt_chk.h"
#include "app_main_ctx.h"
/*****************************************************************************
* Private Definitions
****************************************************************************/
#pragma section = "BSS_SECTION"       /* Points to the BSS segment of FLASH code */
#pragma section = "DATA_SECTION"      /* Points to the DATA section of FLASH code */
#pragma section = "APP_READWRITE_SECTION"      /* Points to the readwrite section of FLASH code */
#pragma section = "DATA_INIT_SECTION" /* Points to the DATA INIT section of FLASH code */

#pragma section = "ROM_PATCH_FPT_SECTION" /* Points to the ROM PATCH FPT section in FLASH code */
#pragma section = "APP_CODE_SECTION" /* Points to the APP CODE section in FLASH code */
#pragma section = "ROM_PATCH_AUTO" /* Points to the ROM PATCH section in FLASH code */
#pragma section = "FREE_MEM" /* Points to the ROM PATCH section in FLASH code */

/*****************************************************************************
 *NO FLASH FETCH
 ****************************************************************************/
#ifdef NO_FLASH_FETCH 
/* Download the code directly in to SRAM using the debugger and run
This Mathod will be used during development phase */


#define GSN_ROM_PATCH_FPT_LOCATION 0x20004000 /* 0x20004000 Location in RAM where the ROM
                                              function pointers has to be copied */
#define START_OF_SRAM 					0x20000000
#define END_OF_SRAM   					0x2007FFFF
#define APP_CODE_START          		0x20040000
#define ROM_PATCH_AUTO_SECTION_LENGTH 	0x2000
#define CONTROL_BLOCK_SIZE 				0x1000

/* These two varibales are part of ROM code */
#define APP_STARTUP_COPY_PROG( src, len, dst ) memcpy((char*)dst, (char*)src, len);
/*Get word aligned address*/
#define WORD_ALIGNED_ADDR(a)	(((a) & (~0x3)) + 0x4)

/* This marks the start of free memory available for byte-pool creation */
__no_init int GsnSramFreeMem @ "FREE_MEM";

/* Used for cerating Byte Memory pools to be used as heap*/
GSN_BYTE_POOL_LINK_T bytePool[3];

extern INT32 App_Main( void );
unsigned int GsnStartup_ClosestPowerOf2( unsigned int value );

/*****************************************************************************
 *Function definitions
 ****************************************************************************/
void GsnStartup_Main( void ) 
{
    unsigned int* bssEnd = __section_end("BSS_SECTION");
    unsigned int* bssStart = __section_begin("BSS_SECTION");
    unsigned int* dataEnd = __section_end("DATA_SECTION");
    unsigned int* dataStart = __section_begin("DATA_SECTION");
    unsigned int* dataInitStart = __section_begin("DATA_INIT_SECTION");
    unsigned int* romPatchFptEnd = __section_end("ROM_PATCH_FPT_SECTION");
    unsigned int* romPatchFptStart = __section_begin("ROM_PATCH_FPT_SECTION");
    unsigned int* appCodeEnd = __section_end("APP_CODE_SECTION");
    unsigned int* appCodeStart = (unsigned int*)APP_CODE_START;
	
    unsigned int length, src, dst, heap1Start, heap2Start;
    int heap1Length, heap2Length;


	/* 1. Copy from SRAM to initialize the "initialised data" in data	segment. */
	length = (unsigned int)( dataEnd )- (unsigned int)(dataStart);
	src = (unsigned int)dataInitStart; /* Location in Flash */
	dst = (unsigned int)dataStart; /* RAM location to copy, i.e. the DATA section */   
    APP_STARTUP_COPY_PROG(src, length, dst);


	/*
     * 2. Copy patch function pointers from the flash to the SRAM.
     */
    length = (unsigned int)( romPatchFptEnd )- (unsigned int)(romPatchFptStart);
    src = (unsigned int)romPatchFptStart;/* Location in Flash for ROM PATCH FPT */
    dst = GSN_ROM_PATCH_FPT_LOCATION;/* RAM location to copy */  
    APP_STARTUP_COPY_PROG(src, length,  dst );    
	
	/* 3. Won't be copying the APP code. Calculate the heap at the end*/
	heap1Start = (((unsigned int)&GsnSramFreeMem) & ~0x3) + 0x8;
	heap1Length = (unsigned int)(appCodeStart)  - heap1Start;
	if( heap1Length < 0 )
	{
		/* ERROR APP CODE Section is more than what it can fit in the SRAM. */
		while(1);
	}
	heap2Start = (((unsigned int)appCodeEnd) & ~0x3) + 0x8;
	heap2Length = END_OF_SRAM - heap2Start;
    

	/*
	* 4. Initialize BSS segment. memset uninitailize data.
	*/
    
    src = (unsigned int)bssStart;
    length = (unsigned int)( bssEnd )- (unsigned int)( bssStart );    
    memset((void*) src, 0, length );
    
    /*5.  Initialize the free memory section to use tx byte pool for dynamic memory
       allocation */
    tx_byte_pool_create(&bytePool[0].bPool, NULL, (void*)heap1Start, 
                               (UINT32)heap1Length );
    
    tx_byte_pool_create(&bytePool[1].bPool, NULL, (void*)heap2Start, 
                               (UINT32)heap2Length );    
	pGsnBytePoolHead =  ( heap2Length > heap1Length ) ? 
					&bytePool[1] : &bytePool[0];
	pGsnBytePoolHead->pNext = ( heap2Length > heap1Length ) ? 
					&bytePool[0] : &bytePool[1];

	pGsnBytePoolHead->pNext->pNext = NULL;
		
   
	/* Assign 3 SRAM blocks to wlan*/
	 *((volatile UINT32 *)(0x40080008)) = (UINT32)0x1C;
	
	/* Call APP MAIN */
    App_Main();
    while(1);
}

unsigned int GsnStartup_ClosestPowerOf2( unsigned int value )
{
    unsigned int ret = 1;
    while( ret < 0x80000000 )
    {
        if( value < ret )break;
        ret <<= 1;
    }
    return ret;
}


#else /*Store code in to FLASH. prefetch/flash cache during run time*/
/*****************************************************************************
 *FLASH FETCH
 ****************************************************************************/

/*****************************************************************************
 *Function prototypes
 ****************************************************************************/
extern GSN_BYTE_POOL_LINK_T *pGsnBytePoolHead;

extern UINT32 romFwImageFlashAddr;/* This holds the starting address of the App Fw*/

extern INT32 App_Main( void );

UINT32 GsnStartup_ClosestPowerOf2( unsigned int value );

BOOL
App_FlashIfFlashCheckAndConfigure();
/*****************************************************************************
 *Private definitions
 ****************************************************************************/
#define APP_STARTUP_COPY_PROG( dst, src, len) GsnFlashCache_BlkFetch( src, dst, len, NULL );

#define CB1_RESERVED_SIZE			0x1000
#define FPT_RESERVED_SIZE			0x2000
#define GSN_STARTUP_RESERVED_SIZE	0x800

#define SRAM_START_ADDR				0x20000000
#define SRAM_END_ADDR				0x2007FFFF /* 512 */

#define FPT_LOCATION 				0x20004000 /* 0x20004000 Location in RAM where the ROM
                                             	 function pointers has to be copied */
#define APP_CODE_SRAM_BLOCK1_ADDR	0x20040000 /* at 256KB */
#define APP_CODE_SRAM_BLOCK1_SIZE	0x40000 /* 256KB */

#define APP_CODE_SRAM_BLOCK2_ADDR	0x20080000 /* at 512KB */
#define APP_CODE_SRAM_BLOCK2_SIZE	0x10000 /* 16KB */

GSN_BYTE_POOL_LINK_T heapBytePool[4];/* create up to 4 byte poola to be used as heap*/

#define WORD_ALIGNED_ADDR(a)         (((a) & (~0x3)) + 0x4)

typedef struct HEAP_INFO
{
	UINT32 start;
	UINT32 size;
}HEAP_INFO_T;

extern APP_MAIN_CTX_T appCtx;
VOID
AppSm_GotoStandby(APP_MAIN_CTX_T *pAppCtx);
VOID 
App_IdleHandler();

/*****************************************************************************
 *Function definitions
 ****************************************************************************/
void GsnStartup_Main( void )
{
	UINT32 appFwImageFlashAddr;
	UINT32 sectionFlshAddr,sectionSize;
	HEAP_INFO_T heap[4] = {0};
	UINT32 appCodeSize, appCodeSramEnd;
    GSN_FLASHCACHE_BLK_REMAP_T remap;
	UINT32 remapIndx = 1;

	/* Program address space - Address assigned in icf file*/
	UINT32 *autoPatchStart = __section_begin("ROM_PATCH_AUTO");
	UINT32 *autoPatchEnd = __section_end("ROM_PATCH_AUTO");
	UINT32 *fptStart = __section_begin("ROM_PATCH_FPT_SECTION");
	UINT32 *fptEnd = __section_end("ROM_PATCH_FPT_SECTION");
    UINT32 *bssStart = __section_begin("BSS_SECTION");
    UINT32 *bssEnd = __section_end("BSS_SECTION");
    UINT32 *dataStart = __section_begin("DATA_SECTION");
    /*UINT32 *dataEnd = __section_end("DATA_SECTION");*/
	UINT32 *appCodeStart = __section_begin("APP_CODE_SECTION");
	UINT32 *appCodeEnd = __section_end("APP_CODE_SECTION");
	UINT32 *dataInitStart = __section_begin("DATA_INIT_SECTION");
	UINT32 *dataInitEnd = __section_end("DATA_INIT_SECTION");
	UINT32 *freeMemStart = __section_begin("FREE_MEM");

	//App_FlashIfFlashCheckAndConfigure();
	appFwImageFlashAddr = romFwImageFlashAddr;
	/* Copy data init section. "dataStart" gives absolute SRAM location*/
	sectionFlshAddr = appFwImageFlashAddr + CB1_RESERVED_SIZE +
						((UINT32)autoPatchEnd - (UINT32)autoPatchStart ) +
						FPT_RESERVED_SIZE + GSN_STARTUP_RESERVED_SIZE +
						((UINT32)dataInitStart - (UINT32)appCodeStart);

	sectionSize = (UINT32)dataInitEnd - (UINT32)dataInitStart;
	APP_STARTUP_COPY_PROG( (UINT32)dataStart, sectionFlshAddr, sectionSize);

	/* Copy Function Pointer Table (FPT)*/
	sectionFlshAddr = appFwImageFlashAddr + CB1_RESERVED_SIZE +
						((UINT32)autoPatchEnd - (UINT32)autoPatchStart );
	sectionSize = (UINT32)fptEnd - (UINT32)fptStart;
	APP_STARTUP_COPY_PROG( (UINT32)FPT_LOCATION, sectionFlshAddr, sectionSize);

	/*Copy App code*/
	appCodeSize = sectionSize = (UINT32)appCodeEnd - (UINT32)appCodeStart;
	if(appCodeSize > APP_CODE_SRAM_BLOCK1_SIZE) sectionSize = APP_CODE_SRAM_BLOCK1_SIZE;

	sectionFlshAddr = appFwImageFlashAddr + CB1_RESERVED_SIZE +
						((UINT32)autoPatchEnd - (UINT32)autoPatchStart ) +
						FPT_RESERVED_SIZE + GSN_STARTUP_RESERVED_SIZE;

	APP_STARTUP_COPY_PROG((UINT32)APP_CODE_SRAM_BLOCK1_ADDR, sectionFlshAddr, sectionSize);
	/*remap*/
	remap.codeAddr = (UINT32)appCodeStart + 1;
    remap.remapIndex = remapIndx++;
    remap.remapSize = APP_CODE_SRAM_BLOCK1_SIZE;
    remap.sramAddr = APP_CODE_SRAM_BLOCK1_ADDR;
    GsnFlashCache_BlkRemapSet(&remap);

	appCodeStart += (sectionSize >> 2); /* devide the size by 4 as the pointer is of type "UINT32 *"  */
	sectionFlshAddr += sectionSize;
    appCodeSramEnd = APP_CODE_SRAM_BLOCK1_ADDR + sectionSize;/* Used to calculate the heapat the end*/
	if(appCodeStart < appCodeEnd)
	{
		appCodeSize = sectionSize = (UINT32)appCodeEnd - (UINT32)appCodeStart;
		if(appCodeSize > APP_CODE_SRAM_BLOCK2_SIZE) sectionSize = APP_CODE_SRAM_BLOCK2_SIZE;
		appCodeSramEnd += sectionSize + 1024;
		APP_STARTUP_COPY_PROG((UINT32)APP_CODE_SRAM_BLOCK2_ADDR, sectionFlshAddr, sectionSize);
		/*remap*/
		remap.codeAddr = (UINT32)appCodeStart + 1;
		remap.remapIndex = remapIndx++;
		remap.remapSize = APP_CODE_SRAM_BLOCK2_SIZE;
		remap.sramAddr = APP_CODE_SRAM_BLOCK2_ADDR;
		GsnFlashCache_BlkRemapSet(&remap);
	}

	
	/* Set uninitialised data section to zero*/
	memset((void *)bssStart, 0, ((UINT32)bssEnd- (UINT32)bssStart));

	/* Calculate the heap */
	heap[0].start = (((UINT32)freeMemStart & ~3 ) + 8 );
	heap[0].size = APP_CODE_SRAM_BLOCK1_ADDR - heap[0].start;

    tx_byte_pool_create(&heapBytePool[0].bPool, NULL, (void*)heap[0].start,
    					(UINT32)heap[0].size);

    appCodeSramEnd = ( appCodeSramEnd & ~3 ) + 8;
	heap[1].start  = appCodeSramEnd;
	heap[1].size  = SRAM_END_ADDR - heap[1].start;
    tx_byte_pool_create(&heapBytePool[1].bPool, NULL, (void*)heap[1].start,
						(UINT32)heap[1].size);

    pGsnBytePoolHead =  ( heap[1].size >= heap[0].size) ?
      &heapBytePool[1] : &heapBytePool[0];
    pGsnBytePoolHead->pNext = ( heap[1].size >= heap[0].size) ?
      &heapBytePool[0] : &heapBytePool[1];

	/* 3 blocks of 64K SRAM is released to wlan - Temporary*/
	*((volatile UINT32 *)(0x40080008)) = (UINT32)0x1c;

	/* Call APP MAIN */
    App_Main();
    /* This is the idle loop */
    App_IdleHandler();
}

unsigned int GsnStartup_ClosestPowerOf2( unsigned int value )
{
    unsigned int ret = 1;
    while( ret < 0x80000000 )
    {
        if( value < ret )break;
        ret <<= 1;
    }
    return ret;
}
PUBLIC UINT
App_FlashIfDmaCtlSet(UINT32 dmaReadCtlWord, UINT32 dmaCmd, BOOL blocking)
{
	GSN_STATUS_T status = GSN_SUCCESS;

	/* setup dma control word register */
    FLASHIF_DMACTL_SET(FLASHIF, dmaReadCtlWord);
    /* setup dma command */
    FLASHIF_DMACMD_SET(FLASHIF, dmaCmd);
    return status;
}

BOOL
App_FlashIfFlashCheckAndConfigure()
{
    UINT32 flashId = 0, mfgId;
    BOOL flashExists;

    /* request PIO control */
    GsnFlashIf_PioReq();

    /* reset flash HPM mode */
    GsnFlashIf_HpmReset();
    GsnFlashIf_HpmReset();

    flashId = GsnFlashIf_FlashIdRead() & 0xFFFF;
    if (flashId == 0x0000)
    {
        flashExists = FALSE;
        goto GsnFlashIfStartup_FlashCheckAndConfigure_Exit;
    }

    flashExists = TRUE;

    /* Release flash from deep power down mode */
    GsnFlashIf_DeepPowerDownRelease();

    /* enable quad mode for known flash devices */
    if (
            (flashId == 0xba20) /* micron */
        ||  (flashId == 0x20c2) /* macronix mx25l3235e(4MB) 3.3v */
        ||  (flashId == 0x24c2) /* macronix mx25l1633e(2MB) 3.3v */
        ||  (flashId == 0x25c2) /* macronix mx25u3235f(4MB), mx25u1635e(2MB) 1.8v */
        ||  (flashId == 0x60c8) /* gigadevice gd25lq32(4MB), gd25lq16(2MB) 1.8v */
        ||  (flashId == 0x40c8) /* gigadevice gd25q16b(2MB), gd25q32b(4MB) 3.3v */
        ||  (flashId == 0x151c) /* eon en25qh16(2MB) 3.3v */
        ||  (flashId == 0x301c) /* eon en25qh32(2MB) 3.3v */
       )
    {
        mfgId = flashId & 0xff;

        if ((mfgId == 0xc2) || (mfgId == 0xc8) || (mfgId == 0x1c))
        {
            /* switch to quad mode */
            App_FlashIfDmaCtlSet(GSN_FLASHIF_DMA_QUADREAD_CTL_WORD_6DUMMYCYCLES,
                                GSN_FLASHIF_FLASH_QUADIO_FAST_READ, TRUE);

            /* For macronix, enable quad mode in status register */
            if (mfgId == 0xc2)
            {
                UINT32 statusReg = 0;
                statusReg = GsnFlashIf_FlashStatusRead();
                statusReg |= 0x40;
                GsnFlashIf_FlashStatusWrite(statusReg, 1);
            }

            /* For gigadevice, enable quad mode in status register */
            if (mfgId == 0xc8)
            {
                UINT32 statusReg = 0;
                statusReg = GsnFlashIf_FlashStatusRead();
                statusReg |= 0x200;
                GsnFlashIf_FlashStatusWrite(statusReg, 2);
            }
        }

        if (flashId == 0xba20) /* micron also needs this for quad setting */
        {
            /* switch to quad mode */
            App_FlashIfDmaCtlSet(GSN_FLASHIF_DMA_QUADREAD_CTL_WORD,
                                    GSN_FLASHIF_FLASH_QUADIO_FAST_READ, TRUE);
            /* required for quad mode read/dma */
            /* write dummy cycles in volatile config: XIP=1, WRAP=Disable */
            GsnFlashIf_FlashRegWrite(GSN_FLASHIF_FLASH_VOLCFG, 0xAB,TRUE);
        }
    }

    /* release PIO control */
    GsnFlashIf_PioRelease();

GsnFlashIfStartup_FlashCheckAndConfigure_Exit:
    return flashExists;
}
#endif/*NO_FLASH_FETCH*/
