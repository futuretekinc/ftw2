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
* $RCSfile: gsn_isotx.h,v $
*
* Description : This file contains public function prototypes and data structure definitions for wlan interface 
* module.
*
******************************************************************************/
#ifndef _GSN_ISOTX_H_
#define _GSN_ISOTX_H_

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

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_ISOTX_CTL_NOTIF_CB_T)(VOID *ctx, UINT16 msgId, UINT16 msgLen,	VOID *pMsg);

typedef GSN_STATUS ( *GSN_ISOTX_DATA_NOTIF_CB_T )( VOID *pCtx, UINT16 msgLen, VOID *pMsg );

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Notification  CB structure.
 *		Datastructure having various indication call back and respective context.
 *******************************************************************************/
typedef struct GSN_ISOTX_CTL_NOTIF
{
	GSN_ISOTX_CTL_NOTIF_CB_T	cb;
	VOID *						cbCtx;
}GSN_ISOTX_CTL_NOTIF_T;

typedef struct GSN_ISOTX_DATA_NOTIF
{
	GSN_ISOTX_DATA_NOTIF_CB_T	cb;
	VOID *						cbCtx;
}GSN_ISOTX_DATA_NOTIF_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wfi System control module context. 
 ******************************************************************************/	
typedef struct GSN_ISOTX_CTX
{	
	UINT8							macIfNum;
	GSN_ISOTXIF_CTX_T *				pIsotxifCtx;
	GSN_ISOTX_CTL_NOTIF_T			ctrlNotif;
	GSN_ISOTX_DATA_NOTIF_T			dataNotif;
	GSN_OSAL_SEM_T					blockngApiEntryLock;	/**< Multiple Tasks may pend on thi ssemaphore*/
	GSN_OSAL_SEM_T					blockngApiExitLock;		/**< Only a single task pend on this at a time */
	VOID *							blockngApiUserBuf;	
	UINT32							blockngApiUserBufSize;
	GSN_STATUS						blockngApiStatus;
} GSN_ISOTX_CTX_T;

typedef struct GSN_ISOTX_INIT_PARAM
{
	UINT8							macIfNum;
	GSN_ISOTXIF_CTX_T *				pIsotxifCtx;
	GSN_ISOTX_CTL_NOTIF_CB_T		ctrlNotifCb;
	VOID *							ctrlNotifCbCtx;
	GSN_ISOTX_DATA_NOTIF_CB_T		dataNotifCb;
	VOID *							dataNotifCbCtx;
}GSN_ISOTX_INIT_PARAM_T;

typedef GSN_WIF_WLAN_ISOTX_BLINK_T	GSN_ISOTX_BLINK_REQ_PARAM;

typedef GSN_WIF_WLAN_REG_WRITE_T GSN_ISOTX_REG_WRITE_REQ_PARAM;

#endif
