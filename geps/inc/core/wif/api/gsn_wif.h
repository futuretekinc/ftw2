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
* $RCSfile: gsn_wif.h,v $
*
* Description : This file contains public function prototypes and data structure definitions for wlan interface 
* module.
*
******************************************************************************/
#ifndef _GSN_WIF_H_
#define _GSN_WIF_H_

/**
 *******************************************************************************
 * @file gsn_wif.h
 * @brief GSN WIF public header.
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
 * @defgroup GsnWif GSN WLAN Firmware Interface (WIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *    
 *		Whole GsnWif module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}   END of coresvcdoc.
 *****************************************************************************/

/*****************************************************************************
 * Private	Definitions
 ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN Interface context.
 * 		This defines the Data structure to store the information for the WLAN interface module. Each 
 * instance of the wif interface will have its own context defined here
 * @note 
 *****************************************************************************/
typedef struct GSN_WIF_CTX
{
	GSN_WIF_WLAN_NW_TYPE_T 		macIfType;	/**<Type of wlan Nw - STA/AP/IBSS*/ 
	GSN_WIF_IF_STATE_T 			state; 		/**<Wlan interface state */
	UINT8 						macIfNum; 	/**< device index mapped to this wif context*/

	/**< Pointer to context of other modules used by Wif*/
	GSN_HI_CTX_T *		pHiCtx;	/* Wif message system context*/	
	/**<Wlan control indication call back table*/
	GSN_WIF_WLAN_CTRL_IND_CB_INFO_T 	wlanCtrlIndCbTbl[GSN_WIF_WLAN_CTRL_MAX_IND];
	/**< Calibration Control Indication call back table*/
	GSN_WIF_CAL_CTRL_IND_CB_INFO_T 		calCtrlIndCbTbl[GSN_WIF_CAL_CTRL_MAX_IND];
	/**<Data indication call back */
	GSN_WIF_DATA_IND_CB_INFO_T 			dataIndCb;
}GSN_WIF_CTX_T;

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief Wif context init function parameter data structure.
 *****************************************************************************/
typedef struct GSN_WIF_INIT_PARAM
{
	UINT32 						macIfNum;		/**< Device Index 0-4*/
	GSN_WIF_WLAN_NW_TYPE_T 		macIfType;		/**< Wlan Network Type*/	
	GSN_HI_CTX_T *				pHiCtx;
}GSN_WIF_INIT_PARAM_T;

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief Wif context init function parameter data structure.
 *****************************************************************************/
typedef struct GSN_WIF_RE_INIT_PARAM
{
	UINT32 						macIfNum;		/**< Device Index 0-4*/
	GSN_WIF_WLAN_NW_TYPE_T 		macIfType;		/**< Wlan Network Type*/	
}GSN_WIF_RE_INIT_PARAM_T;

/*****************************************************************************
 * Public MACROs
 ****************************************************************************/
 
/*****************************************************************************
 * Public function prototypes
 ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief Initialize WLAN IF.
 *    This function initializes the WLAN IF instance. 
 * @param pWifCtx -IN  pointer to data structure of type GSN_WIF_CTX_T. This the context memory of a 
 *					   WLAN IF instance.
 * @param pParam  - IN  pointer to data structure of type GSN_WIF_INIT_PARAM_T.
 * @return GSN_SUCCESS if operation is successful else GSN_FAILURE.
 * @note
 *		All the memeres of "pParam" shall be properly initialised before callling this function 
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnWif_Init(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_INIT_PARAM_T *pParam);

PUBLIC GSN_STATUS 
GsnWif_Reinit(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_RE_INIT_PARAM_T *pParam);

/*****************************************************************************
 * Public Inlines
 ****************************************************************************/
/* 
Register Wlan control inidication Call back with wif module
*/
INLINE VOID 
GsnWif_WlanCtrlIndCbReg(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_WLAN_CTRL_IND_CB_T cb, VOID *ctx,
								UINT16 ind)
{	
	UINT16 indNum;

	/*The first 10 bits of defined indication gives the indication Number. All the indications
	 starts from 0x200 i.e. GSN_WIF_IND_RSP_MSG_TYPE*/	 
	indNum = (ind  & GSN_WIF_MSG_API_MASK) - GSN_WIF_IND_RSP_MSG_TYPE; 	
	pWifCtx->wlanCtrlIndCbTbl[indNum].cb = cb;
	pWifCtx->wlanCtrlIndCbTbl[indNum].ctx = ctx;
}

/* 
Register Wlan control inidication Call back with wif module
*/
INLINE VOID 
GsnWif_CalCtrlIndCbReg(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_WLAN_CTRL_IND_CB_T cb, VOID *ctx,
								UINT16 ind)
{	
	UINT16 indNum;

	/*The first 10 bits of defined indication gives the indication Number. All the indications
	 starts from 0x200 i.e. GSN_WIF_IND_RSP_MSG_TYPE*/	 
	indNum = (ind  & GSN_WIF_MSG_API_MASK) - GSN_WIF_IND_RSP_MSG_TYPE; 	
	pWifCtx->calCtrlIndCbTbl[indNum].cb = cb;
	pWifCtx->calCtrlIndCbTbl[indNum].ctx = ctx;
}

/*
Register Data Indication call back with wif module
*/
INLINE VOID 
GsnWif_DataIndCbReg(GSN_WIF_CTX_T *pWifCtx, GSN_WIF_DATA_IND_CB_T cb, VOID *ctx)
{
	pWifCtx->dataIndCb.cb = cb;
	pWifCtx->dataIndCb.ctx = ctx;
}

/*
Get Buffer for sending request
*/
INLINE VOID *
GsnWif_ReqBuffGet(GSN_WIF_CTX_T *pWifCtx, UINT32 reqSize)
{
	return (VOID *)GsnHi_TxBufGet(pWifCtx->pHiCtx, reqSize);
}

/*
Get Buffer for sending data
*/
INLINE VOID *
GsnWif_DataTxBuffGet(GSN_WIF_CTX_T *pWifCtx, UINT32 dataSize)
{
	return (VOID *)GsnHi_DataTxBufGet(pWifCtx->pHiCtx, dataSize);
}
 
INLINE GSN_STATUS_T
GsnWif_WlanCtrlSend(GSN_WIF_CTX_T *pWifCtx, UINT32 reqAPI, VOID *pReq, UINT16 reqSize)
{	
	return	GsnHi_CtrlSend(pWifCtx->pHiCtx, GSN_WIF_HI_CLASS_WLAN_CTRL, pWifCtx->macIfNum, 
							reqAPI, pReq, reqSize);
}

INLINE GSN_STATUS
GsnWif_CalCtrlSend(GSN_WIF_CTX_T *pWifCtx, UINT32 reqAPI, VOID *pReq, UINT16 reqSize)
{	
	return	GsnHi_CtrlSend(pWifCtx->pHiCtx, GSN_WIF_HI_CLASS_CAL_CTL, pWifCtx->macIfNum,
							reqAPI, pReq, reqSize);
}

INLINE GSN_STATUS
GsnWif_DataSend(GSN_WIF_CTX_T *pWifCtx,      INT8* data, UINT32 sizeOfData, UINT8 pktId)
{
	return GsnHi_DataSend(pWifCtx->pHiCtx, GSN_WIF_HI_CLASS_DATA, pWifCtx->macIfNum, 0, data,							sizeOfData, pktId);
}

INLINE GSN_STATUS
GsnWif_154DataSend(GSN_WIF_CTX_T *pWifCtx,      INT8* data, UINT32 sizeOfData, UINT8 pktId)
{
	return GSN_SUCCESS;
}

INLINE GSN_STATUS
GsnWif_UnassocDataSend(GSN_WIF_CTX_T *pWifCtx,      INT8* data, UINT32 sizeOfData, UINT8 pktId)
{
	return GsnHi_DataSend(pWifCtx->pHiCtx, GSN_WIF_HI_CLASS_UNASSOC_DATA, pWifCtx->macIfNum, 0,
							data, sizeOfData, pktId);
}

#endif /* _GSN_WIF_H_ */
