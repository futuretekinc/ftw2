/******************************************************************************
 *
 *               COPYRIGHT (c) 2006-2013 GainSpan Corporation
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
 * $RCSfile: gsn_ov788.h,v $
 *
 *****************************************************************************/

#ifndef _GSN_OV788_DRIVER_H_
#define _GSN_OV788_DRIVER_H_

//#define APP_VIDEO_PACKET_TX_TIMINGS
//#define APP_VIDEO_SPI_READ_TIMINGS
//#define APP_VIDEO_PACKET_READ_TIMINGS
//#define APP_VIDEO_PACKET_SEND_TIMINGS


//#define APP_VIDEO_DEBUG_SUCCESS
//#define APP_VIDEO_DEBUG 
#define APP_VIDEO_DEBUG_FAILURE 

//#define VIDEO_TEST_SEQ_DATADROP

#ifdef OV788_GS2000
#define OV788_DMA_MODE
#endif

//#define OV788_DEBUG_INFO    //This enables print for general statictics and flow
//#define OV788_DEBUG_DATA   // This prints 32 bytes of data. Or as required
#define OV788_DEBUG_FAIL     // This enables print in cases of failure only


//#define APP_VIDEO_UDP

/* Which SPI to use */
#ifdef OV780_GS2000_KB
#define SPI_PORT	GSN_SPI_NUM_SSPI
#else
#define SPI_PORT	GSN_SPI_NUM_MSPI
#endif



/* GPIO Numbers */
#ifdef	OV780_GS2000_KB
#define GSN_OV788_GPIO_SPI0_CS 				4
#define GSN_OV788_GPIO_SPI0_DIN 			6
#define GSN_OV788_GPIO_SPI0_CLK				5
#define GSN_OV788_GPIO_SPI0_DOUT			7

#define GSN_OV788_GPIO_GS_TO_OV 			8
#define GSN_OV788_GPIO_OV_TO_GS 			9
#else
#ifdef OV788_GS2000
#define GSN_OV788_GPIO_SPI0_CS 				33
#else
#define GSN_OV788_GPIO_SPI0_CS 				29
#endif

#define GSN_OV788_GPIO_SPI0_DIN 			34
#define GSN_OV788_GPIO_SPI0_CLK				35
#define GSN_OV788_GPIO_SPI0_DOUT			36
#endif

#ifdef OV_BOARD_GS_BOARD
#define GSN_OV788_SPI_CS         			0x10
#define GSN_OV788_GS_TO_OV_INT  			0x100 
#define GSN_OV788_OV_TO_GS_INT  			0x200 
#define GSN_OV788_GPIO_BITMAP				0xfffffeef
#else

#ifdef OV788_GS2000
#define GSN_OV_RESET						0x4000000
#define GSN_OV788_SPI_CS         			0x200000000
#define GSN_OV788_GS_TO_OV_INT  			0x80000 
#define GSN_OV788_OV_TO_GS_INT  			0x100000 
#define GSN_OV788_GPIO_BITMAP				0xfffffffdfff7ffff
#else
#define GSN_OV_RESET						0x100000

#ifdef	OV780_GS2000_KB
#define GSN_OV788_SPI_CS         			(1<<4)
#else
#define GSN_OV788_SPI_CS         			0x20000000
#endif

#define GSN_OV788_GS_TO_OV_INT  			0x100 
#define GSN_OV788_OV_TO_GS_INT  			0x200 

#ifdef	OV780_GS2000_KB
#define GSN_OV788_GPIO_BITMAP				0xdffffeef
#else
#define GSN_OV788_GPIO_BITMAP				0xdffffeff
#endif

#endif
#endif

#define GSN_OV788_HEADER_LEN 				24
#define GSN_OV788_SPI_BUFF_SIZE 			(2048*5)

#define GSN_OV788_READ_MODE_POLL   			0
#define GSN_OV788_READ_MODE_INTR_DMA		1

#define GSN_OV788_BYTE0_SOF					0
#define GSN_OV788_BYTE1_RSD					1
#define GSN_OV788_BYTE2_CKS					2
#define GSN_OV788_BYTE3_TYP					3
#define GSN_OV788_BYTE4_LEN0				4
#define GSN_OV788_BYTE5_LEN1				5
#define GSN_OV788_BYTE6_LEN2				6
#define GSN_OV788_BYTE7_LEN3				7


#define GSN_OV788_MAX_BYTES_PER_DMA 		1024

typedef VOID (*GSN_OV788_CALLBACK_T)(VOID *context, UINT32 status, UINT8 **rxBuf, UINT32 *rxLen);

typedef enum GSN_OV788_STATUS
{
	GSN_OV788_STATUS_SUCCESS,
	GSN_OV788_STATUS_IDLE,
    GSN_OV788_STATUS_READING,
    GSN_OV788_STATUS_READY,
    GSN_OV788_STATUS_FAILURE,
    GSN_OV788_STATUS_IN_PROGRESS,
    GSN_OV788_STATUS_NO_DATA_FROM_OV,

}GSN_OV788_STATUS_E;

typedef struct GSN_OV788_CTX
{
	UINT32				state;
	GSN_OSAL_SEM_T		syncSem;
	GSN_SPI_CONFIG_T  	spiConfig;
	GSN_SPI_HANDLE_T 	spiHandle;
	UINT8 				*rxBuffer;
	GSN_SPI_DMA_MODE_T 	dmaMode;
		
}GSN_OV788_CTX_T;


typedef struct GSN_OV788_CONFIG
{
	GSN_SPI_DMA_MODE_T 	dmaMode;
	GSN_SPI_NUM_T		spiPortNum;
	UINT32				clkRate;
		
}GSN_OV788_CONFIG_T;


PUBLIC GSN_OV788_STATUS_E
gsnOv788_Init(GSN_OV788_CTX_T *pOv788Ctx, GSN_OV788_CONFIG_T *pOv788Config);

PUBLIC INT32
gsnOv788_PacketRead(GSN_OV788_CTX_T *pOv788Ctx, 
                            UINT8 *rxBuff, 
							UINT32 rxLen,
							UINT32 mode,
                            GSN_OV788_CALLBACK_T *pOv788Cb, 
                            VOID *cbCtx);

PUBLIC INT32
gsnOv788_Read(GSN_OV788_CTX_T *pOv788Ctx, 
                    UINT8 *rxBuff, 
                    UINT32 rxLen, 
					UINT32 mode,
					UINT32 dataLen,
                    GSN_OV788_CALLBACK_T *pOv788Cb, 
                    VOID *cbCtx);

PUBLIC GSN_OV788_STATUS_E
gsnOv788_DeInit(GSN_OV788_CTX_T *pOv788Ctx);


#endif

