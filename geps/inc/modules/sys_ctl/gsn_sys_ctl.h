/*******************************************************************************
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
* $RCSfile: gsn_sys_ctl.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_SYS_CTL_H_
#define _GSN_SYS_CTL_H_


#define WLAN_RF_CALIB_DATA_FILE_NAME    "A:/WlanRfCalibDataFile"

#define WLAN_RF_CALIB_DATA_SIZE_MAX         512

typedef GSN_WIF_SYS_BATT_CHK_IND_T	GSN_SYS_CTL_BATT_CHK_IND_T;

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_SYS_CTL_BOOT_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status);


/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_SYS_CTL_IFSTART_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_SYS_CTL_IFSTOP_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_SYS_CTL_OTPWR_NOTIF_CB_T)(VOID *ctx, GSN_STATUS status, UINT16 writeLen);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef VOID (*GSN_SYS_CTL_BATT_CHK_NOTIF_CB_T)(VOID *ctx, GSN_SYS_CTL_BATT_CHK_IND_T *pBattChkInd);

/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wdd "Connect" Notification call back definition. 
 * @see GsnWdd_Connect.
 ******************************************************************************/	
typedef GSN_STATUS (*GSN_SYS_CTL_CALIB_DATA_WR_IND_CB_T)(VOID *ctx, UINT8 *data, UINT32 size);
/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Notification  CB structure.
 *		Datastructure having various indication call back and respective context.
 *******************************************************************************/
typedef struct GSN_SYS_CTL_NOTIF_CB
{
	GSN_SYS_CTL_BOOT_NOTIF_CB_T		bootIndCb;
	VOID *							bootIndCbCtx;
	GSN_SYS_CTL_IFSTART_NOTIF_CB_T	ifStartIndCb;
	VOID *							ifStartIndCbCtx;
	GSN_SYS_CTL_IFSTOP_NOTIF_CB_T	ifStopIndCb;
	VOID *							ifStopIndCbCtx;
	GSN_SYS_CTL_OTPWR_NOTIF_CB_T	otpWrIndCb;
	VOID * 							otpWrIndCbCtx;	
}GSN_SYS_CTL_NOTIF_CB_T;

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief GSN WDD Notification  CB structure.
 *		Datastructure having various indication call back and respective context.
 *******************************************************************************/
typedef struct GSN_SYS_CTL_NOTIF_EXTN_CB
{
	GSN_SYS_CTL_BATT_CHK_NOTIF_CB_T	battChkIndCb;
	VOID *							battChkIndCbCtx;
    GSN_SYS_CTL_CALIB_DATA_WR_IND_CB_T  calibDataWrIndCb;
    VOID *                              calibDataWrIndCbCtx;
}GSN_SYS_CTL_NOTIF_EXTN_CB_T;


/*******************************************************************************
 * @ingroup GsnWdd
 * @brief Wfi System control module context. 
 ******************************************************************************/	
typedef struct GSN_SYS_CTL_CTX
{
	GSN_OSAL_THREAD_TCB_T   tcb;			/**< Message handler task control block*/
	GSN_OSAL_QUEUE_T 		msgQueue;		/**< message queue handle */
	UINT32 					sysQualTskID;	/**< sys qual task ID for the Message handler task*/
	
	UINT8							macIfNum;
	UINT8							fsDriveNum;/**< File SSystem Drive Number*/
	GSN_SYSIF_CTX_T *				pSysifCtx;
	GSN_SYS_CTL_NOTIF_CB_T			notif;
	GSN_OSAL_SEM_T					blockngApiEntryLock;	/**< Multiple Tasks may pend on thi ssemaphore*/
	GSN_OSAL_SEM_T					blockngApiExitLock;		/**< Only a single task pend on this at a time */
	VOID *							blockngApiUserBuf;	
	UINT32							blockngApiUserBufSize;
	GSN_STATUS						blockngApiStatus;
	GSN_SYS_CTL_NOTIF_EXTN_CB_T		notifExtn;
	
	GSN_SOFT_TMR_T dieTempSendTmr;
	GSN_SOFT_TMR_T *dieTempSendTmrHndl;
} GSN_SYS_CTL_CTX_T;

typedef struct GSN_SYS_CTL_INIT_PARAM
{
	UINT8							macIfNum;
	GSN_SYSIF_CTX_T *				pSysifCtx;	
	UINT8							fsDriveNum;/**< File SSystem Drive Number*/
	UINT32*		pStack;				/**< pointer to message handler task stack*/ 
	UINT32 		stackSize; 			/**< stack size */
	UINT32 		priority; 			/**< priority*/
	UINT8* 		msgQueueBuff;		/**< pointer to message queue buffer*/
	UINT32 		msgQueueBuffSize; 	/**< messsage queue buffer size*/
	UINT8  		msgSize;			/**< message size*/	
	UINT32 		sysQualTskID;		/**< task ID for the message handler task */
	
}GSN_SYS_CTL_INIT_PARAM_T;
typedef enum GSN_SYS_CTL_MSG_TYPE
{
	GSN_SYS_CTL_MSG_TYPE_FILE_OP_REQ,
    GSN_SYS_CTL_MSG_TYPE_RF_CALIB_DATA_WR_REQ,
    GSN_SYS_CTL_MSG_TYPE_SEND_DIE_TEMP,
}GSN_SYS_CTL_MSG_TYPE_T;

typedef struct GSN_SYS_CTL_MESSAGE
{
	UINT8 		msgType;	/**< message of type GSN_SYS_CTL_MSG_TYPE_T */
	UINT16 		msgLen;
	VOID* 		pMsg;
}GSN_SYS_CTL_MESSAGE_T;

/**
 *******************************************************************************
 * @file gsn_sys_ctl.h
 * @brief GSN WIF wlan Control messages send APIs.
 *		This defines the public APIs used to send Wlan control requests
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnWifApi
 * @brief Boot Request Parameter 
 *		This defines the Boot request API parameter structure.
 *****************************************************************************/
typedef struct GSN_SYS_CTL_BOOT_REQ_PARAM
{
	UINT8      	bootReason;			/**< Boot*/
    UINT8      	bootSubreason;		/**< Boot Subreason */
    UINT8      	confLost;			/**< configurartion is lost or not.  0/1 */
    UINT32		numIfs;				/**< Number of interfaces to be supported */	
	UINT8		ifTypes[GSN_WIF_MAX_IF_NUM]; /* Interface type. Not valid for standby wakeup. */
    UINT32      bootTimeLow;		/**< system time at boot - lower 4 bytes*/
    UINT32      bootTimeHigh;		/**< system time at boot - upper 4 bytes */	
    UINT32      fwFlashAddr;    /**< address in flash of fw image */
    UINT8       modType;
    UINT8      modVersion;
	UINT32 		stdbyCtxLen;
	UINT8	   	*pStdbyCtx;
    UINT32      rfCalibDataSize;
    INT8       rfCalibData[512];
}GSN_SYS_CTL_BOOT_REQ_PARAM_T;

typedef GSN_WIF_SYS_IF_START_REQ_T GSN_SYS_CTL_IF_START_REQ_T;

typedef GSN_WIF_SYS_STDBY_REQ_T GN_SYS_CTL_STDBY_REQ_PARAM_T;

typedef GSN_WIF_SYS_STDBY_RDY_IND_T GSN_SYS_CTL_STDBY_RESP_T;

typedef GSN_WIF_SYS_IF_STOP_REQ_T GSN_SYS_CTL_IF_STOP_PARAM_T;

typedef GSN_WIF_SYS_IF_STOP_RSP_T GSN_SYS_CTL_IF_STOP_RESP_T;

typedef GSN_WIF_SYS_TEMP_PAVOLT_IND_T	GSN_SYS_CTL_TEMP_PAVOLT_DATA;

typedef struct 	GSN_SYS_CTL_MEM_WRITE_REQ
{
    UINT32 addr; /**< memory address */
    UINT32 len;  /**< number of bytes to read/write */
    UINT8  *data ;
}GSN_SYS_CTL_MEM_WRITE_REQ_T;

typedef struct 	GSN_SYS_CTL_MEM_READ_REQ
{
    UINT32 addr; /**< memory address */
    UINT32 len;  /**< number of bytes to read/write */
	UINT8  *respBuf ;
}GSN_SYS_CTL_MEM_READ_REQ_T;

typedef enum GSN_SYS_CTL_STA_TYPE
{
    GSN_SYS_CTL_STA_TYPE_LSSTA =  GSN_WIF_SYS_WLAN_STA_TYPE_LSSTA, /* Low speed STA */
    GSN_SYS_CTL_STA_TYPE_HSSTA = GSN_WIF_SYS_WLAN_STA_TYPE_HSSTA, /* High speed STA */
}GSN_SYS_CTL_STA_TYPE_T;

typedef GSN_WIF_SYS_BATT_CHK_REQ_T	GSN_SYS_CTL_BATT_CHK_REQ_PARAM_T;
PUBLIC INLINE VOID
GsnSysCtl_CalibDataWrIndCbReg(GSN_SYS_CTL_CTX_T *pSysCtlCtx, 
                                        GSN_SYS_CTL_CALIB_DATA_WR_IND_CB_T cb, 
                                        VOID *ctx)
{
	pSysCtlCtx->notifExtn.calibDataWrIndCb = cb;
	pSysCtlCtx->notifExtn.calibDataWrIndCbCtx = ctx;
}

PUBLIC GSN_STATUS
GsnSysCtl_Init(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_INIT_PARAM_T *pInitParam);

PUBLIC VOID
GsnSysCtl_BootReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_BOOT_REQ_PARAM_T *pBtReqParm, 
					  GSN_SYS_CTL_BOOT_NOTIF_CB_T btIndCb, VOID * btIndCbCtx);

PUBLIC GSN_STATUS
GsnSysCtl_IfStartReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_IF_START_REQ_T *pReqParam,
							GSN_SYS_CTL_IFSTART_NOTIF_CB_T cb, VOID *cbCtx);

PUBLIC GSN_STATUS
GsnSysCtl_IfStopReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_IF_STOP_PARAM_T *pParam,
							GSN_SYS_CTL_IFSTOP_NOTIF_CB_T cb, VOID *cbCtx);

PUBLIC GSN_STATUS
GsnSysCtl_StandByReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GN_SYS_CTL_STDBY_REQ_PARAM_T *pParam,
							INT8 *pRespBuf, UINT32 respBufSize);

PUBLIC GSN_STATUS
GsnSysCtl_WlanFwVerGet(GSN_SYS_CTL_CTX_T *pSysCtlCtx,  		UINT32 *pWlanVer);

PUBLIC GSN_STATUS
GsnSysCtl_OtpWriteReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, UINT8 otpGrpId, UINT8 otpGrpVer,
								UINT8 *data, UINT16 dataLen,
								GSN_WIF_SYS_OTP_WRITE_RSP_T *pOtpWrResp);
PUBLIC GSN_STATUS
GsnSysCtl_OtpReadReq(GSN_SYS_CTL_CTX_T *pSysCtlCtx, UINT8 otpGrpId, UINT8 otpGrpVer,
								UINT8 *data, UINT16 *dataLen);

PUBLIC GSN_STATUS
GsnSysCtl_BatteryValRead(GSN_SYS_CTL_CTX_T *pSysCtlCtx, UINT32 *pBattVal);

PUBLIC GSN_STATUS
GsnSysCtl_BatteryChkStart(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_BATT_CHK_REQ_PARAM_T* pBattChkReqParam,
								GSN_SYS_CTL_BATT_CHK_NOTIF_CB_T cb, VOID * cbCtx);
PUBLIC GSN_STATUS
GsnSysCtl_BatteryChkStop(GSN_SYS_CTL_CTX_T *pSysCtlCtx);

VOID
GsnActlWwdog_Enable(VOID);

GSN_STATUS
GsnSysCtl_IfStartReq_Patch(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_IF_START_REQ_T *pReqParam,
							GSN_SYS_CTL_IFSTART_NOTIF_CB_T cb, VOID *cbCtx);

PUBLIC GSN_STATUS
GsnSysCtl_WlanFeatureBmapGet(GSN_SYS_CTL_CTX_T *pSysCtlCtx,  		ULONG64 *pFeatureBmap);

GSN_STATUS
GsnSysCtl_TempPaVoltSend(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_TEMP_PAVOLT_DATA *pTempPaVoltData);

GSN_STATUS
GsnSysCtl_DieTempGet(GSN_SYS_CTL_CTX_T *pSysCtlCtx, UINT8 *pDieTempVal);

GSN_STATUS
GsnSysCtl_AppTempSend(GSN_SYS_CTL_CTX_T *pSysCtlCtx);

GSN_STATUS
GsnSysCtl_DieTempSendTimerStart(GSN_SYS_CTL_CTX_T *pSysCtlCtx, UINT32 period);

GSN_STATUS
GsnSysCtl_DieTempSendTimerStop(GSN_SYS_CTL_CTX_T *pSysCtlCtx);

#endif
