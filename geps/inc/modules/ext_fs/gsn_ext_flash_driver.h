/****************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by Gainspan
* Corporation or its licensors.  Title to the Material remains
* with Gainspan Corporation or its suppliers and licensors.
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
* Unless otherwise agreed by Gainspan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by Gainspan
* or Gainspan's suppliers or licensors in any way.
*
* $RCSfile: gsn_ext_flash_driver.h,v $
*
* Description : This file contains macros and functions prototypes for External Flash.
******************************************************************************
*/


#ifndef GSN_SERIALFLASH_H
#define GSN_SERIALFLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnExtFlash GSN EXTERNAL FLASH API
 *    This group contains public definitions and functions providing access
 *    to the GS2000's SPI.
 ****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/


/*****************************************************************************
  *  Public Variables
  *****************************************************************************/


/*******************************************************************************
*                          Type & Macro Declarations
*******************************************************************************/

#define GSN_SERIAL_FLASH_APP_START_LOCATION 0x00060000

#define GSN_EXT_FLASH_MAX_READ_SIZE 1024
#define GSN_EXT_FLASH_MAX_WRITE_SIZE 256

#define WIP 0x01

#define OPCODE_WREN      0x06 /* write enable         */
#define OPCODE_WRDI      0x04 /* */
#define OPCODE_RDSR      0x05 /* read status register */
#define OPCODE_WRSR      0x01 /* */
#define OPCODE_READ      0x03 /* opcode for read operation */
#define OPCODE_FAST_READ 0x0B
#define OPCODE_PP        0x02
#define OPCODE_SE        0x20
#define OPCODE_32BE      0x52
#define OPCODE_64BE      0xD8
#define OPCODE_CE		 0x60
#define OPCODE_DP        0xb9
#define OPCODE_RES       0xab
#define OPCODE_RDID      0x9f

#define GSN_EXTFLASH_FLASH_PAGE_SIZE 0x100

#define GSN_EXTFLASH_FAILURE -1
#define GSN_EXTFLASH_SUCCESS 0

typedef enum GSN_FLASH_SPI_FLAG
{
    GSN_FLASH_SPI_POLL,
    GSN_FLASH_SPI_DMA
} GSN_FLASH_SPI_FLAG_T;

typedef enum GSN_EXTFLASH_STATUS
{
    EXTFLASH_NOT_INITIALIZED,
    EXTFLASH_INITIALIZED
} GSN_EXTFLASH_STATUS_T;

typedef struct GSN_EXTFLASH_CTX
{	
	GSN_SPI_CONFIG_T  	    spiConfig;
	GSN_SPI_HANDLE_T 	    spiHandle;
	UINT8 				    extFlashBuff[1024];
	GSN_SPI_DMA_MODE_T 	    dmaMode;	
	UINT32 blockStart;
	UINT32 descBlockStart;
	UINT32 maxBlocks;
	UINT32 blockStart_D;
	UINT32 descBlockStart_D;
	UINT32 maxBlocks_D;
	UINT32 blockSize;
	UINT32 sectorSize;
	GSN_FLASH_SPI_FLAG_T spiFlagFs;
	LONG64 spiCsGpio;
	GSN_EXTFLASH_STATUS_T  extFlashStatus;
	UINT8  spiPinConf;
	UINT32 eraseTime;       //in milli secondss
}GSN_EXTFLASH_CTX_T;

typedef VOID (*GSN_EXTFLASH_CALLBACK_T)(VOID *context, UINT32 status);



/*******************************************************************************
*                          Extern Data Declarations
*******************************************************************************/

/*******************************************************************************
*                          Extern Function Prototypes
*******************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief serial flash config init.
 *
 *    This function performs the initilization of GSN_SPI_CONFIG_T structure required to 
 *	access the serial flash in poll mode. API calls GsnSpi_PollOpen() to 
 *	set the GSN_SPI_CONFIG_T structure values. 
 * @param   gsExtFlashCtx          - IN  external flash context
 * @param   spiPortNumber		 - IN spi port number
 * @param   *spiConfig      		 - IN GSN_SPI_CONFIG_T updated strcuture  
 * @param	spiFlag			 - IN spi Polling or DMA flag
 * @retval    status			 - IN returns GSN_EXTFLASH_SUCCESS or GSN_EXTFLASH_FAILURE
 * @note
 * This function is to demonstrate the serial flash application access in polling mode
 *                                                                            
 *****************************************************************************/
PUBLIC INT32 
GsnExtFlash_Init(GSN_EXTFLASH_CTX_T *gsExtFlashCtx,
					GSN_SPI_NUM_T spiPortNumber,
					GSN_SPI_CONFIG_T *spiConfig,
					GSN_FLASH_SPI_FLAG_T spiFlag);

/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief read the external flash memory using poll and DMA.
 *
 *	  This API reads the data from external flash starting from address readAddr to dataLen.
 *	  Read data from flash will be updated in dataBuf.
 * @param	gsExtFlashCtx  - IN  external flash context
 * @param	dataLen		 - IN  number of bytes to read
 * @param	readAddr		 - IN  serial flash read address
 * @param	*dataBuf		 - IN  user specified buffer to store the read data from flash
 * @param	spiFlag			 - IN spi Polling or DMA flag
 * @param	extFlashCallBack	- IN callback
 * @param	cbCtx			 - IN callback context
 * @retval	UINT32		returns the total number of bytes read
 * @note
 *																			  
 *****************************************************************************/
PUBLIC UINT32
GsnExtFlash_Read(GSN_EXTFLASH_CTX_T *gsExtFlashCtx, UINT32 dataLen, 
					UINT32 readAddr, UINT8 *dataBuf,GSN_FLASH_SPI_FLAG_T spiFlag,
					GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, VOID *cbCtx);


/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief page boundary calculation to write data on the external flash memory.
 *
 *	  To write the data , page boundary caluclations are required. For one write cycle its possible to 
 *       to write 256 bytes of data. Because of this limitation page boundary 
 * 	   calculations are done before writing the data to the flash.
 *
 * @param	gsExtFlashCtx  - IN  external flash context
 * @param	dataLen		 - IN  number of bytes to read
 * @param	writeAddr	 - IN  serial flash write address
 * @param	dataBuf		 - IN  user specified buffer to store the read data from flash 
 * @param	spiFlag		 - IN spi Polling or DMA flag
 * @param	extFlashCallBack	- IN callback
 * @param	cbCtx			 - IN callback context
 * @retval	UINT32		returns the total number of bytes written
 * @note
 *																			  
 *****************************************************************************/

PUBLIC UINT32
GsnExtFlash_Write(GSN_EXTFLASH_CTX_T *gsExtFlashCtx, 
								UINT32 dataLen, 
								UINT32 writeAddr, 
								UINT8 *dataBuf,
								GSN_FLASH_SPI_FLAG_T spiFlag,
								GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, 
								VOID *cbCtx);

/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief Erase the external flash memory using poll.
 *
 *	  This API erases the contents of external flash sector for the given sector address.
 *
 * @param	gsExtFlashCtx        - IN  external flash context
 * @param	eraseSectorAddr	 - IN  serial flash sector erase address 
 * @param	spiFlag		 	 - IN spi Polling or DMA flag
 * @param	extFlashCallBack	 - IN callback
 * @param	cbCtx			 - IN callback context
 * @retval	NA
 * @note
 *																			  
 *****************************************************************************/
PUBLIC VOID
GsnExtFlash_Erase(GSN_EXTFLASH_CTX_T *gsExtFlashCtx,UINT32 eraseSectorAddr,GSN_FLASH_SPI_FLAG_T spiFlag,
							GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, VOID *cbCtx);


/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief Erase the external flash memory using poll.
 *
 *	  This API erases the contents of external flash chip.
 *
 * @param	gsExtFlashCtx        - IN  external flash context
 * @param	spiFlag		 	 - IN spi Polling or DMA flag
 * @param	extFlashCallBack	 - IN callback
 * @param	cbCtx			 - IN callback context
 * @retval	NA
 * @note
 *																			  
 *****************************************************************************/
PUBLIC VOID
GsnExtFlash_ChipErase(GSN_EXTFLASH_CTX_T *gsExtFlashCtx,GSN_FLASH_SPI_FLAG_T spiFlag,
							GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, VOID *cbCtx);

/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief Erase the external flash memory using poll.
 *
 *	  This API erases the contents of external flash 32k block for the given block address.
 *
 * @param	gsExtFlashCtx        - IN  external flash context
 * @param	eraseBlockAddr	 - IN  serial flash sector erase address
 * @param	spiFlag		 	 - IN spi Polling or DMA flag
 * @param	extFlashCallBack	- IN callback
 * @param	cbCtx			 - IN callback context
 * @retval	NA
 * @note
 *																			  
 *****************************************************************************/
PUBLIC VOID
GsnExtFlash_32KErase(GSN_EXTFLASH_CTX_T *gsExtFlashCtx,UINT32 eraseBlockAddr,GSN_FLASH_SPI_FLAG_T spiFlag,
							GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, VOID *cbCtx);


/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief Erase the external flash memory using poll.
 *
 *	  This API erases the contents of external flash 64k block for the given block address.
 *
 * @param	gsExtFlashCtx        - IN  external flash context
 * @param	eraseBlockAddr	 - IN  serial flash sector erase address
 * @param	spiFlag		 	 - IN spi Polling or DMA flag
 * @param	extFlashCallBack	- IN callback
 * @param	cbCtx			 - IN callback context
 * @retval	NA
 * @note
 *																			  
 *****************************************************************************/
PUBLIC VOID
GsnExtFlash_64KErase(GSN_EXTFLASH_CTX_T *gsExtFlashCtx,UINT32 eraseBlockAddr,GSN_FLASH_SPI_FLAG_T spiFlag,
							GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, VOID *cbCtx);


/**
 *****************************************************************************
 * @ingroup GsnExtFlash
 * @brief SPI Read Write of data with respect to size.
 *
 *	  This function performs the SPI Read Write operation for the given size depending on the SPI flag set
 * for DMA or POLLING method
 * @param	spiHandle 	 - IN  spi handle
 * @param	dataLen 		 - IN number of data to write and read.
 * @param	*rxBuf		 - IN  user specified buffer to store the read data from flash 
 * @param	*txBuf		 - IN  user specified buffer which has data to be written to flash  
 * @param	spiFlag		 - IN spi Polling or DMA flag 
 * @param	extFlashCallBack	- IN callback
 * @param	cbCtx			 - IN callback context
 * @retval 	INT32	returns success or failure
 * @note
 *																			  
 *****************************************************************************/
PUBLIC INT32
GsnExtFlash_SpiReadWrite( GSN_SPI_HANDLE_T *spiHandle,
							UINT32 dataLen,
							UINT8 *rxBuf,
							UINT8 *txBuf,
							GSN_FLASH_SPI_FLAG_T spiFlag,
							GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, 
							VOID *cbCtx);



PUBLIC UINT32
GsnExtFlash_IdRead(GSN_EXTFLASH_CTX_T *gsExtFlashCtx, UINT32 dataLen, 
						UINT32 readAddr, UINT8 *dataBuf,GSN_FLASH_SPI_FLAG_T spiFlag,
						GSN_EXTFLASH_CALLBACK_T *extFlashCallBack, VOID *cbCtx);
#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
*                          End of File
*******************************************************************************/
