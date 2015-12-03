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
* $RCSfile: gsn_sysif.h,v $
*
* Description : This file contains public function prototypes and data structure definitions for wlan interface 
* module.
*
******************************************************************************/
#ifndef _GSN_SYSIF_H_
#define _GSN_SYSIF_H_

/**
 *******************************************************************************
 * @file gsn_SYSIF.h
 * @brief GSN SYSIF public header.
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
 * @defgroup GsnSYSIF GSN WLAN Firmware Interface (SYSIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *    
 *		Whole GsnSYSIF module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
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
 * @ingroup GsnSYSIF
 * @{
 *****************************************************************************/
 
/**
 *****************************************************************************
 * @defgroup GsnSYSIFApi GSN WLAN Firmware Interface (SYSIF) module APIs
 * @brief This group contains the  the APIs provided by the SYSIF module. 
 ******************************************************************************/

/**
 *****************************************************************************
 * @}	END of GsnSYSIF.
 *****************************************************************************/
#define GSN_SYS_MACIF_NUM	0xFF
/*****************************************************************************
 * Private	Definitions
 ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnSYSIF
 * @brief GSN WLAN Interface context.
 * 		This defines the Data structure to store the information for the WLAN interface module. Each 
 * instance of the SYSIF interface will have its own context defined here
 * @note 
 *****************************************************************************/
typedef struct GSN_SYSIF_CTX
{
	UINT8			macIfNum; 	/**< device index mapped to this SYSIF context*/
	/**< Pointer to context of other modules used by SYSIF*/
	GSN_HI_CTX_T *	pHiCtx;	/* SYSIF message system context*/		
	GSN_WIF_SYS_CTRL_IND_CB_INFO_T sysCtrlIndCbTbl[GSN_WIF_SYS_CTRL_MAX_IND]; /* device independent sys ctrl indication handling*/ 
}GSN_SYSIF_CTX_T;

/**
 *****************************************************************************
 * @ingroup GsnSYSIF
 * @brief SYSIF context init function parameter data structure.
 *****************************************************************************/
typedef struct GSN_SYSIF_INIT_PARAM
{
	UINT8			macIfNum;
	GSN_HI_CTX_T *	pHiCtx;
}GSN_SYSIF_INIT_PARAM_T;

/*****************************************************************************
 * Public function prototypes
 ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnSYSIF
 * @brief Initialize WLAN IF.
 *    This function initializes the WLAN IF instance. 
 * @param pSysifCtx -IN  pointer to data structure of type GSN_SYSIF_CTX_T. This the context memory of a 
 *					   WLAN IF instance.
 * @param pParam  - IN  pointer to data structure of type GSN_SYSIF_INIT_PARAM_T.
 * @return GSN_SUCCESS if operation is successful else GSN_FAILURE.
 * @note
 *		All the memeres of "pParam" shall be properly initialised before callling this function 
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnSysif_Init(GSN_SYSIF_CTX_T *pSysifCtx, GSN_SYSIF_INIT_PARAM_T *pParam);

/*****************************************************************************
 * Public Inlines
 ****************************************************************************/
/* 
Register Wlan control inidication Call back with SYSIF module
*/
INLINE VOID 
GsnSysif_SysCtrlIndCbReg(GSN_SYSIF_CTX_T *pSysifCtx, GSN_WIF_SYS_CTRL_IND_CB_T cb, VOID *ctx,
								UINT16 ind)
{	
	UINT16 indNum;

	/*The first 10 bits of defined indication gives the indication Number. All the indications
	 starts from 0x200 i.e. GSN_SYSIF_IND_RSP_MSG_TYPE*/	 
	indNum = (ind  & GSN_WIF_MSG_API_MASK) - GSN_WIF_IND_RSP_MSG_TYPE; 	
	pSysifCtx->sysCtrlIndCbTbl[indNum].cb = cb;
	pSysifCtx->sysCtrlIndCbTbl[indNum].ctx = ctx;
}

/* 
Register Wlan control inidication Call back with SYSIF module
*/
INLINE VOID 
GsnSysif_ResetIndCbReg(GSN_SYSIF_CTX_T *pSysifCtx, GSN_WIF_RESET_IND_CB_T cb, VOID *ctx)
{	
	GsnHi_ResetIndCbReg(pSysifCtx->pHiCtx, cb, ctx);
}

/*
Get Buffer for sending request
*/
INLINE VOID *
GsnSysif_ReqBuffGet(GSN_SYSIF_CTX_T *pSysifCtx, UINT32 reqSize)
{
	return (VOID *)GsnHi_TxBufGet(pSysifCtx->pHiCtx, reqSize);
}

INLINE GSN_STATUS
GsnSysif_SysCtrlSend(GSN_SYSIF_CTX_T *pSysifCtx, UINT32 reqAPI, VOID *pReq, UINT16 reqSize)
{	
	return	GsnHi_CtrlSend(pSysifCtx->pHiCtx, GSN_WIF_HI_CLASS_SYS_CTRL, pSysifCtx->macIfNum,
							reqAPI, pReq, reqSize);
}

INLINE VOID
GsnSysif_BootReqSend(GSN_SYSIF_CTX_T *pSysifCtx, GSN_WIF_SYS_BOOT_REQ_T *pBootReq)
{		
	GsnHi_BootReqSend(pSysifCtx->pHiCtx, pBootReq);	
}

#endif /* _GSN_SYSIF_H_ */

