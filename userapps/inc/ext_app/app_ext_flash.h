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
* $RCSfile: app_ext_flash.h,v
*/

#ifndef _APP_EXTFLASH_H_
#define _APP_EXTFLASH_H_


/*  physical  */
#define BLOCKSIZE_EF      0x1000    /*  4K - size of file storage blocks  */
#define BLOCKSTART_EF     0x2       /*  logical number of first file storage block  */
#define MAXBLOCKS_EF      30   /*  number of logical blocks for file storage  */

#define DESCSIZE_EF       0x800     /*  2k descriptor block size  */
#define DESCBLOCKSTART_EF 0x0       /*  logical number of first descriptor block  */
#define DESCBLOCKS_EF     2         /*  number of descriptor blocks  */
#define DESCCACHE_EF      0x0       /*  1k assigned to write cache for descriptor  */

#define SECTORSIZE_EF     0x100     /* 256 */
#define SECTORPERBLOCK_EF ( BLOCKSIZE_EF / SECTORSIZE_EF )

#define APP_EXT_FLASH_DRIVE_NUM_2	2
#define APP_EXT_FLASH_DRIVE_NUM_3	3

#define APP_SPI_DIN			0x01
#define APP_SPI_DOUT		0x02
#define APP_SPI_CS			0x04
#define APP_SPI_CLK			0x08

#define APP_SPI_ALL_PIN_CONF  (APP_SPI_DIN|APP_SPI_DOUT|APP_SPI_CS|APP_SPI_CLK)


#ifdef GS2011M_EVB2_0
#define GS2011_SPI_CS 		 0x400
#define GS2011_SPI_CS_DIRMAP 	 0xfffffBff
#else
#define GS2011_SPI_CS 			 0x2000
#define GS2011_SPI_CS_DIRMAP 	 0xffffDfff
#endif	
#define APP_ALL_GPIO_SET     0xffffffff

UINT32 
AppExtFlash_FsConfig();

int
AppExtFlash_FsMount ( FS_FLASH * flash );

VOID
AppExtFlash_Init(GSN_FLASH_SPI_FLAG_T spiFlag);

VOID
AppExtFlash_FsInit();

UINT32
AppExtFlash_DataFsConfig();

int
AppExtFlash_DataFsMount ( FS_FLASH * flash );

VOID
AppExtFlash_DataFsInit();

#ifdef __cplusplus
}
#endif

#endif


