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
* $RCSfile: gsn_hi.h,v $
*
* Description : This file contains HI APIs and definitions.
******************************************************************************/
#ifndef _GSN_HI_H_
#define _GSN_HI_H_

/**
 *******************************************************************************
 * @file gsn_hi.h
 * @brief wif message system header file
 		This file contains wif message system APIs and definitions.
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
	
typedef GSN_WIF_Q_DESC_T		GSN_HI_Q_DESC_T;
typedef GSN_WIF_Q_DESC_HNDL_T	GSN_HI_Q_DESC_HNDL_T;

typedef GSN_WIF_DATA_TD_T		GSN_HI_DATA_TD_T;
typedef GSN_WIF_CTL_TD_T		GSN_HI_CTL_TD_T;

#define DP_RAM_SIZE					0x10000
#define DP_RAM_START_ADDR			0x20200000
#define RESET_IND_RESRVD_SIZE		68
#define DP_RAM_END_ADDR				((DP_RAM_START_ADDR + DP_RAM_SIZE) - RESET_IND_RESRVD_SIZE)

#define RESET_IND_LOCATION()		DP_RAM_END_ADDR

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief This enum defines the queue size of various TD queues
 *****************************************************************************/ 
typedef enum GSN_HI_TD_Q_SIZE
{
	GSN_HI_DTX_RDY_Q_SIZE = 8,
	GSN_HI_DTX_DONE_Q_SIZE = 8,
	GSN_HI_DRX_SBUF_RDY_Q_SIZE = 8,
	GSN_HI_DRX_LBUF_RDY_Q_SIZE = 8,
	GSN_HI_DRX_DONE_Q_SIZE = 8,

	GSN_HI_CTX_RDY_Q_SIZE = 8,
	GSN_HI_CTX_DONE_Q_SIZE = 8,
	GSN_HI_CRX_SBUF_RDY_Q_SIZE = 8,
	GSN_HI_CRX_LBUF_RDY_Q_SIZE = 8,
	GSN_HI_CRX_DONE_Q_SIZE = 8,
}GSN_HI_TD_Q_SIZE_T;
		
/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief Rx and Tx buffers size
 *		This defines the sizeof big and small buffers used for RX and Tx
 *****************************************************************************/ 	
typedef enum GSN_HI_BUFF_SIZE
{	/*Rx area buffers*/
	GSN_HI_DRX_SBUFF_SIZE = 128,	
	GSN_HI_DRX_LBUFF_SIZE = 1600,	
	GSN_HI_CRX_SBUFF_SIZE = 128,	
	GSN_HI_CRX_LBUFF_SIZE = 1600,
}GSN_HI_BUFF_SIZE_T;
	
/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief Message size of the TD queue
 *****************************************************************************/ 														
#define GSN_TD_Q_MSG_SIZE	16 /*4 words*/

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief Device Index
 *****************************************************************************/ 														 
typedef enum GSN_HI_DEV_INDX
{
	GSN_HI_DEV_INDX_0,
	GSN_Hi_DEV_INDX_1,
	GSN_Hi_DEV_INDX_2,
	GSN_HI_DEV_INDX_MAX,
}GSN_HI_DEV_INDX_T;

typedef VOID (*GSN_HI_CTRL_CB_T)(VOID * pCtx, GSN_WIF_CTL_TD_T *pCtrlTD);

typedef VOID (*GSN_HI_DATA_CB_T)(VOID * pCtx, GSN_WIF_DATA_TD_T *pDataTD);

typedef struct GSN_HI_IFC_INFO
{
	GSN_HI_CTRL_CB_T ctrlCb;
	VOID *pCtrlCbCtx;

	GSN_HI_DATA_CB_T dataCb;
	VOID *pDataCbCtx;
}GSN_HI_IFC_INFO_T;

typedef struct GSN_HI_IFC_REG_PARAM
{
	UINT32 macIfNum;
	GSN_HI_CTRL_CB_T ctrlCb;
	VOID *pCtrlCbCtx;
	GSN_HI_DATA_CB_T dataCb;
	VOID *pDataCbCtx;
}GSN_HI_IFC_REG_PARAM_T;

/**
 *****************************************************************************
 * @ingroup GsnHi
 * @brief Shared Memory address
 *	  Shared RAM (64 K) is used for trnsferring data and control messages between the WLAN and APP
 *	firmware. This defines the Address of the shared RAM 
 *****************************************************************************/
typedef struct GSN_HI_CTX
{
	/**< Data  Tx and Rx path Queues*/
	GSN_HI_Q_DESC_T *pDTxRdyQ;
	GSN_HI_Q_DESC_T *pDTxDoneQ;
	GSN_HI_Q_DESC_T *pDRxSbuffRdyQ;
	GSN_HI_Q_DESC_T *pDRxLbuffRdyQ;
	GSN_HI_Q_DESC_T *pDRxDoneQ;

	/**< Control Tx and Rx path Queues*/
	GSN_HI_Q_DESC_T *pCTxRdyQ;
	GSN_HI_Q_DESC_T *pCTxDoneQ;
	GSN_HI_Q_DESC_T *pCRxSbuffRdyQ;
	GSN_HI_Q_DESC_T *pCRxLbuffRdyQ;
	GSN_HI_Q_DESC_T *pCRxDoneQ;
	
	/**< Pointer to HI mail box context */
	GSN_HI_MB_CTX_T 		hiMbCtx;
	GSN_OSAL_BYTE_POOL_T	txBytePool; 	/**< Byte Handle  used manage Tx path Memory in DP RAM*/	
	GSN_OSAL_MUTEX_T 		dTxTdQLock;		/**<Rx and Tx buffer management queues */
	GSN_OSAL_MUTEX_T 		cTxTdQLock;

	
	GSN_OSAL_THREAD_TCB_T 	recvThreadHndl;	/**< wif message receive thread control block*/
	GSN_OSAL_EVENT_FLAGS_T 	evntFlags;		/**< Used to notify the message handler task 
														about messages in TD queues*/
    GSN_HI_IFC_INFO_T		interfaceTbl[GSN_HI_DEV_INDX_MAX+1];	/**< One elemnt for each device 
    																	index. Note each device 
    																	(logical) can be of any of 
    																	the type  
    																	GSN_WIF_IF_TYPE_T*/
	GSN_WIF_RESET_IND_CB_INFO  	resetIndCb;
	UINT32						sysQualTaskId;	/**<SysQual Task ID */
	GSN_HIF_STATS_T *			pStats;
	UINT32 						dTxRdyQSize;
	GSN_OSAL_SEM_T				dTxRdyQSem;	
	GSN_OSAL_BYTE_POOL_T		dataTxBytePool; 	/**< Byte Handle  used manage Tx path Memory in DP RAM
													NOTE !!!! only for C1 !!!!*/
	
	GSN_OSAL_SEM_T				cTxRdyQSem; 
}GSN_HI_CTX_T;

typedef struct GSN_HI_INIT_PARAM
{
	UINT16 dTxRdyQSize;		/*< Data Tx Ready Queue Size (max number of Queue Elements)*/
	UINT16 dTxDoneQSize;	/*< Data Tx Done Queue Size (max number of Queue Elements)*/
	UINT16 dRxSbufRdyQSize;	/*< Data Rx Sbuf Ready Queue Size (max number of Queue Elements)*/
	UINT16 dRxLbufRdyQSize;	/*< Data Rx Lbuf Ready Queue Size (max number of Queue Elements)*/
	UINT16 dRxDoneQsize;	/*< Data Rx Done Queue Size (max number of Queue Elements)*/
	
	UINT16 cTxRdyQSize;		/*< Control Tx Ready Queue Size (max number of Queue Elements)*/
	UINT16 cTxDoneQSize;	/*< Control Tx Ready Queue Size (max number of Queue Elements)*/
	UINT16 cRxSbufRdyQSize;	/*< Control Rx Sbuf Ready Queue Size (max number of Queue Elements)*/
	UINT16 cRxLbufRdyQsize;	/*< Control Rx Lbuf Ready Queue Size (max number of Queue Elements)*/
	UINT16 cRxDoneQsize;	/*< Control Rx Done Queue Size (max number of Queue Elements)*/

    UINT8 hiRecvTskPrio; 	/*< wif receive thread priority*/
    UINT8 *pHiRecvTskStack; /*< wif receive thread stack pointer*/
	UINT32 hiRecvTskStackSize;	/*< wif receive thread stack size*/	
	UINT32 sysQualTicks;	/**<SysQual ticks */
	UINT32 sysQualTaskId;	/**<SysQual Task ID */
	GSN_HIF_STATS_T *pStats;
}GSN_HI_INIT_PARAM_T;

/**
 ******************************************************************************
 * @ingroup GsnHi
 * @brief Initialise Message System.
 * 		This function initialises the Wif Message system. This wif message system contains the mailbox 
 * and the shared memory for message exchange between the WLAN and the APP Fw. All the messages
 * data and Control, are exchanged using the shared RAM. The Hw mail box itself is used for indicating the
 * messages available. 
 @note
 *	This function shall be called during system initilisation. The wif message system should be initilised 
 * before any message is sent to WLAN Fw.
 *****************************************************************************/ 	
GSN_STATUS 
GsnHi_Init(GSN_HI_CTX_T *pHiCtx, GSN_HI_INIT_PARAM_T *pParam);

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief Data Tx
 *
 * @param pDataTD - IN pointer to structure of type GSN_HI_DATA_TD_T. 
 * @return GSN_SUCCESS if succcess.
 *****************************************************************************/ 	
GSN_STATUS_T 
GsnHi_CtrlSend(GSN_HI_CTX_T *pHiCtx, GSN_WIF_HI_CLASS_T hiClass, UINT8 devIndex,
					UINT32 reqAPI, VOID *pReq, UINT16 reqSize);

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief Control Tx
 *
 * @param pCtrlTD - IN pointer to structure of type GSN_HI_CTL_TD_T. 
 * @return GSN_SUCCESS if succcess.
 *****************************************************************************/ 	
PUBLIC GSN_STATUS 
GsnHi_DataSend (GSN_HI_CTX_T *pHiCtx, GSN_WIF_HI_CLASS_T hiClass, UINT8 devIndex,UINT32 msgId,
						INT8* data, UINT32 dataLen, UINT8 pktId);


/**
 *****************************************************************************
 * @internal
 * @ingroup GsnHi
 * @brief Send Boot Request
 *
 * @param pBootReq - IN pointer to structure of type GSN_HI_SYS_BOOT_REQ_T. 
 *****************************************************************************/ 	
PUBLIC VOID
GsnHi_BootReqSend(GSN_HI_CTX_T *pHiCtx, GSN_WIF_SYS_BOOT_REQ_T *pBootReq);

VOID
GsnHi_InterfaceRegister(GSN_HI_CTX_T *pHiCtx, GSN_HI_IFC_REG_PARAM_T *pParam);

VOID
GsnHi_InterfaceDeregister(GSN_HI_CTX_T *pHiCtx, UINT8 macIfNum);

VOID 
GsnHi_ResetIndCbReg(GSN_HI_CTX_T *pHiCtx,  	   GSN_WIF_RESET_IND_CB_T cb, VOID *ctx);


INLINE VOID 
GsnHi_ResetIndCbReg(GSN_HI_CTX_T *pHiCtx, GSN_WIF_RESET_IND_CB_T cb, VOID *ctx)
{
	pHiCtx->resetIndCb.cb = cb;
	pHiCtx->resetIndCb.ctx = ctx;
}

VOID *
GsnHi_DataTxBufGet(GSN_HI_CTX_T *pHiCtx, UINT32 size);

#endif /* _GSN_HI_MSG_SYS_H_ */

