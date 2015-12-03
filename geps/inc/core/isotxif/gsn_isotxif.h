/******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: gsn_isotxif.h,v $
*
* Description : This file contains public function prototypes and data structure definitions for wlan interface 
* module.
*
******************************************************************************/
#ifndef _GSN_ISOTXIF_H_
#define _GSN_ISOTXIF_H_

/**
 *******************************************************************************
 * @file gsn_ISOTXIF.h
 * @brief GSN ISOTXIF public header.
 *		This file contains public function prototypes and data structure definitions for wlan interface 
 *		 module.
 * @note
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnISOTXIF GSN WLAN Firmware Interface (ISOTXIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *    
 *		Whole GsnISOTXIF module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}   END of coresvcdoc.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnISOTXIF
 * @{
 *****************************************************************************/
 
/**
 *****************************************************************************
 * @defgroup GsnISOTXIFApi GSN WLAN Firmware Interface (ISOTXIF) module APIs
 * @brief This group contains the  the APIs provided by the ISOTXIF module. 
 ******************************************************************************/

/**
 *****************************************************************************
 * @}	END of GsnISOTXIF.
 *****************************************************************************/

/*****************************************************************************
 * Private	Definitions
 ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnISOTXIF
 * @brief GSN WLAN Interface context.
 * 		This defines the Data structure to store the information for the WLAN interface module. Each 
 * instance of the ISOTXIF interface will have its own context defined here
 * @note 
 *****************************************************************************/
typedef struct GSN_ISOTXIF_CTX
{
	UINT8			macIfNum; 	/**< device index mapped to this ISOTXIF context*/
	/**< Pointer to context of other modules used by ISOTXIF*/
	GSN_HI_CTX_T *	pHiCtx;	/* ISOTXIF message system context*/		
	GSN_WIF_ISOTX_CTRL_IND_CB_INFO_T isotxCtrlIndCbTbl[GSN_WIF_ISOTX_CTRL_MAX_IND];
	GSN_WIF_ISOTX_DATA_IND_CB_INFO_T dataIndCb;
}GSN_ISOTXIF_CTX_T;

/**
 *****************************************************************************
 * @ingroup GsnISOTXIF
 * @brief ISOTXIF context init function parameter data structure.
 *****************************************************************************/
typedef struct GSN_ISOTXIF_INIT_PARAM
{
	UINT8			macIfNum;
	GSN_HI_CTX_T *	pHiCtx;
}GSN_ISOTXIF_INIT_PARAM_T;

/*****************************************************************************
 * Public function prototypes
 ****************************************************************************/
PUBLIC GSN_STATUS 
GsnIsotxif_Init(GSN_ISOTXIF_CTX_T *pIsotxifCtx, GSN_ISOTXIF_INIT_PARAM_T *pParam);

/*****************************************************************************
 * Public Inlines
 ****************************************************************************/
/* 
Register Wlan control inidication Call back with SYSIF module
*/
INLINE VOID 
GsnIsotxif_CtrlIndCbReg(GSN_ISOTXIF_CTX_T *pIsotxifCtx, GSN_WIF_ISOTX_CTRL_IND_CB_T cb, VOID *ctx,
								UINT16 ind)
{	
	UINT16 indNum;

	/*The first 10 bits of defined indication gives the indication Number. All the indications
	 starts from 0x200 i.e. GSN_SYSIF_IND_RSP_MSG_TYPE*/	 
	indNum = (ind  & GSN_WIF_MSG_API_MASK) - GSN_WIF_IND_RSP_MSG_TYPE; 	
	pIsotxifCtx->isotxCtrlIndCbTbl[indNum].cb = cb;
	pIsotxifCtx->isotxCtrlIndCbTbl[indNum].ctx = ctx;
}

/*
Register Data Indication call back with wif module
*/
INLINE VOID 
GsnIsotxif_DataIndCbReg(GSN_ISOTXIF_CTX_T *pIsotxifCtx, GSN_WIF_ISOTX_DATA_IND_CB_T cb, VOID *ctx)
{
	pIsotxifCtx->dataIndCb.cb = cb;
	pIsotxifCtx->dataIndCb.ctx = ctx;
}

/*
Get Buffer for sending request
*/
INLINE VOID *
GsnIsotxif_ReqBuffGet(GSN_ISOTXIF_CTX_T *pIsotxifCtx, UINT32 reqSize)
{
	return (VOID *)GsnHi_TxBufGet(pIsotxifCtx->pHiCtx, reqSize);
}

/*
Get Buffer for sending data
*/
INLINE VOID *
GsnIsotxif_DataTxBuffGet(GSN_ISOTXIF_CTX_T *pIsotxifCtx, UINT32 dataSize)
{
	return (VOID *)GsnHi_TxBufGet(pIsotxifCtx->pHiCtx, dataSize);
}

INLINE GSN_STATUS
GsnIsotxif_CtrlSend(GSN_ISOTXIF_CTX_T *pIsotxifCtx, UINT32 reqAPI, VOID *pReq, UINT16 reqSize)
{	
	return	GsnHi_CtrlSend(pIsotxifCtx->pHiCtx, GSN_WIF_HI_CLASS_ISOTX_CTL, pIsotxifCtx->macIfNum,
							reqAPI, pReq, reqSize);
}

INLINE GSN_STATUS
GsnIsotxif_DataSend(GSN_ISOTXIF_CTX_T *pIsotxifCtx,      INT8* data, UINT32 sizeOfData, UINT8 pktId)
{
	return GsnHi_DataSend(pIsotxifCtx->pHiCtx, GSN_WIF_HI_CLASS_DATA, pIsotxifCtx->macIfNum, 0, 
							data, sizeOfData, pktId);
}

#endif /* _GSN_ISOTXIF_H_ */

