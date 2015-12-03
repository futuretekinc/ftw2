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
* $RCSfile: gsn_dot154if.h,v $
*
* Description : This file contains public function prototypes and data structure definitions for wlan interface 
* module.
*
******************************************************************************/
#ifndef _GSN_DOT154_H_
#define _GSN_DOT154_H_

/**
 *******************************************************************************
 * @file gsn_DOT154.h
 * @brief GSN Dot154if public header.
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
 * @defgroup GsnDOT154 GSN WLAN Firmware Interface (Dot154if) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *    
 *		Whole GsnDOT154 module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
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
 * @ingroup GsnDOT154
 * @{
 *****************************************************************************/
 
/**
 *****************************************************************************
 * @defgroup GsnDOT154Api GSN WLAN Firmware Interface (Dot154if) module APIs
 * @brief This group contains the  the APIs provided by the Dot154if module. 
 ******************************************************************************/

/**
 *****************************************************************************
 * @}	END of GsnDOT154.
 *****************************************************************************/

/*****************************************************************************
 * Private	Definitions
 ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnDOT154
 * @brief GSN WLAN Interface context.
 * 		This defines the Data structure to store the information for the WLAN interface module. Each 
 * instance of the Dot154if interface will have its own context defined here
 * @note 
 *****************************************************************************/
typedef struct GSN_DOT154IF_CTX
{
	UINT8			macIfNum; 	/**< device index mapped to this Dot154if context*/
	/**< Pointer to context of other modules used by Dot154if*/
	GSN_HI_CTX_T *	pHiCtx;	/* Dot154if message system context*/		
	GSN_WIF_DOT154_CTRL_IND_CB_INFO_T ctrlIndCb;
	GSN_WIF_DOT154_DATA_IND_CB_INFO_T dataIndCb;
}GSN_DOT154IF_CTX_T;


#define GSN_DOT154IF_MODE_802_15_4 0
#define GSN_DOT154IF_MODE_6LOWPAN  1

typedef struct GSN_DOT154IF_START_DATA
{
    UINT8 NumOfKeyTableEntries;
    UINT8 NumOfDeviceTableEntries;
    UINT8 NumOfSecurityLevelEntries;
    UINT8 modeOfOp; /**< one of the value from the above MACROs*/    
}GSN_DOT154IF_START_DATA_T;

/**
 *****************************************************************************
 * @ingroup GsnDOT154
 * @brief Dot154if context init function parameter data structure.
 *****************************************************************************/
typedef struct GSN_DOT154_INIT_PARAM
{
	UINT8			macIfNum;
	GSN_HI_CTX_T *	pHiCtx;
}GSN_DOT154_INIT_PARAM_T;

/*****************************************************************************
 * Public function prototypes
 ****************************************************************************/
PUBLIC GSN_STATUS 
GsnDot154if_Init(GSN_DOT154IF_CTX_T *pDot154ifCtx, GSN_DOT154_INIT_PARAM_T *pParam);

/*****************************************************************************
 * Public Inlines
 ****************************************************************************/
/* 
Register Wlan control inidication Call back with SYSIF module
*/
INLINE VOID 
GsnDot154if_CtrlIndCbReg(GSN_DOT154IF_CTX_T *pDot154ifCtx, GSN_WIF_DOT154_CTRL_IND_CB_T cb, VOID *ctx)
{	
	/*The first 10 bits of defined indication gives the indication Number. All the indications
	 starts from 0x200 i.e. GSN_SYSIF_IND_RSP_MSG_TYPE*/	 
	pDot154ifCtx->ctrlIndCb.cb = cb;
	pDot154ifCtx->ctrlIndCb.ctx = ctx;
}

/*
Register Data Indication call back with wif module
*/
INLINE VOID 
GsnDot154if_DataIndCbReg(GSN_DOT154IF_CTX_T *pDot154ifCtx, GSN_WIF_DOT154_DATA_IND_CB_T cb, VOID *ctx)
{
	pDot154ifCtx->dataIndCb.cb = cb;
	pDot154ifCtx->dataIndCb.ctx = ctx;
}

/*
Get Buffer for sending request
*/
INLINE VOID *
GsnDot154if_ReqBuffGet(GSN_DOT154IF_CTX_T *pDot154ifCtx, UINT32 reqSize)
{
	return (VOID *)GsnHi_TxBufGet(pDot154ifCtx->pHiCtx, reqSize);
}

/*
Get Buffer for sending data
*/
INLINE VOID *
GsnDot154if_DataTxBuffGet(GSN_DOT154IF_CTX_T *pDot154ifCtx, UINT32 dataSize)
{
	return (VOID *)GsnHi_TxBufGet(pDot154ifCtx->pHiCtx, dataSize);
}

INLINE GSN_STATUS
GsnDot154if_CtrlSend(GSN_DOT154IF_CTX_T *pDot154ifCtx, UINT32 reqAPI, VOID *pReq, UINT16 reqSize)
{	
	return	GsnHi_CtrlSend(pDot154ifCtx->pHiCtx, GSN_WIF_HI_CLASS_154_CTRL, pDot154ifCtx->macIfNum,
							reqAPI, pReq, reqSize);
}

INLINE GSN_STATUS
GsnDot154if_DataSend(GSN_DOT154IF_CTX_T *pDot154ifCtx, UINT32 msgId,       INT8* data, UINT32 sizeOfData, UINT8 pktId)
{
	return GsnHi_DataSend(pDot154ifCtx->pHiCtx, GSN_WIF_HI_CLASS_154_DATA, pDot154ifCtx->macIfNum, 
							msgId, data, sizeOfData, pktId);
}

#endif /* _GSN_DOT154_H_ */


