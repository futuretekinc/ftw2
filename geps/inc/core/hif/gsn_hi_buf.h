/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: gsn_hi_buf.h,v $
*
* Description : Wif shared memeory buffer management definitions
*****************************************************************************/
#ifndef _GSN_HI_BUF_H_
#define _GSN_HI_BUF_H_
	
/**
 *******************************************************************************
 * @file gsn_hi_buf.h
 * @brief GSN WIF shared memory Tx and Rx buffer management public header.
 *	  This file contains the public APIs and structures of WIF shared memory Tx and Rx buffer 
 * management.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/
 
/**
 *****************************************************************************
 * @defgroup GsnHi GSN WLAN Firmware Interface (HIF) module Message system
 * @brief This group contains the  implementation of message system used for data and control messages
 * 		between the WLAN and APP firmware.
 ******************************************************************************/
/**
 *****************************************************************************
 * @}	END of coresvcdoc.
 *****************************************************************************/
/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief Descriptor Queue definition 
 *****************************************************************************/ 	
/** @{ */

typedef GSN_RING_BUF_T 		GSN_HI_BUF_Q_DESC_T;
typedef GSN_RING_BUF_T * 	GSN_HI_BUF_Q_DESC_HNDL_T;

/** @} */
/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief Buffer type definition
 *****************************************************************************/ 	
typedef enum GSN_HI_BUF_TYPE
{
	GSN_HI_BUF_TYPE_SMALL, 	/**< Small buffer*/
	GSN_HI_BUF_TYPE_LARGE 		/**< Large buffer */
}GSN_HI_BUF_TYPE_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief  Buffer initialisation parameter structure
 * @note
 *	see GsnWif_TxBufInit, GsnWif_RxBufInit
 *****************************************************************************/ 	
typedef struct GSN_HI_RX_BUF_INIT_PARAM
{
	UINT8 *		startAddr;		/**<Start address  for the memory area in  shared RAM */
	UINT16 		numBuf;			/**< Number of buffers*/
	UINT16 		bufSize;		/**< size of buffer*/
	VOID * 		fifoAddr;		/**<Each memory area is managed using a Ring (FIFO ) buffers.*/
	GSN_HI_BUF_TYPE_T bufType;	/**< Type of buffer small/large*/
}GSN_HI_RX_BUF_INIT_PARAM_T;

typedef struct GSN_HI_TX_BUF_INIT_PARAM
{
	UINT8 *		startAddr;		/**<Start address  for the memory area in  shared RAM */
	UINT32 poolSize;
}GSN_HI_TX_BUF_INIT_PARAM_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief  Initialise Tx buffer management system
 *
 * @param pWifBufQdesc - IN pointer to structure of type GSN_HI_BUF_Q_DESC_T.
 * @param params - IN pointer to structure of type GSN_HI_TX_BUF_INIT_PARAM_T.
 *****************************************************************************/ 	
INLINE VOID
GsnHi_TxBufInit(GSN_HI_CTX_T *pHiCtx, GSN_HI_TX_BUF_INIT_PARAM_T *params)
{
	GsnOsal_BytePoolCreate(&pHiCtx->txBytePool,(VOID *) params->startAddr, params->poolSize);
}

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief  Get a free Tx buffer
 *
 * @param size - IN minimum size of the buffer required
 *****************************************************************************/ 	
INLINE VOID *
GsnHi_TxBufGet(GSN_HI_CTX_T *pHiCtx, UINT32 size)
{
	VOID *pMem;
	GSN_OSAL_ERROR_T error;

	error = GsnOsal_ByteAllocate(&pHiCtx->txBytePool, &pMem, size, GSN_OSAL_NO_WAIT);
	if(GSN_OSAL_SUCCESS == error)
	{
		pHiCtx->pStats->txBufAllocSuccess++;
		return pMem;
	}
	else
	{
		pHiCtx->pStats->txBufAllocFail++;
		return NULL;
	}
}

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief  release buffer to Tx buffer pool
 *****************************************************************************/ 	
INLINE VOID
GsnHi_TxBufRelease(GSN_HI_CTX_T *pHiCtx, INT8 *ptr)
{
	pHiCtx->pStats->txBufReleaseCount++;
	GsnOsal_ByteRelease(ptr);
}

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief  Initialise Rx buffer management system
 *
 * @param pWifBufQdesc - IN pointer to structure of type GSN_HI_BUF_Q_DESC_T.
 * @param params - IN pointer to structure of type GSN_HI_RX_BUF_INIT_PARAM_T.
 *****************************************************************************/ 	
PUBLIC VOID
GsnHi_RxBufInit(GSN_HI_BUF_Q_DESC_T *pHiBufQdesc, GSN_HI_RX_BUF_INIT_PARAM_T *params);

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWifMsgSys
 * @brief  release buffer to Rx buffer pool
 *****************************************************************************/ 	
PUBLIC VOID
GsnHi_RxBufRelease(INT8 *ptr);

#endif /* _GSN_HI_BUF_H_ */

