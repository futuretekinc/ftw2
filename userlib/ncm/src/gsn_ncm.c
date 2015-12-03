/*******************************************************************************
*
*               COPYRIGHT (c) 2011-2012 GainSpan Corporation
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
* $RCSfile: gsn_ncm.c,v $
*
* Description : This file contains public definitions for nw connection manager.
* It provides APIs for the nw connection manager
*******************************************************************************/

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_defines.h"
#include "gsn_includes.h"
#include "gsn_ncm.h"
#include "gsn_ncm_roam.h"

#if 0

#define GSN_NCM_PRINTF  AppTls_DbgPrintf
#else
INT32
GSN_NCM_PRINTF  (const char *format, ...)
{        
	return 0;
}
#endif
/**
 *******************************************************************************
 * @file gsn_ncm.c
 * @brief GSN NCM public API implementation.
 *    This file contains the public APIs and structures of NCM module.
 ******************************************************************************/
/*******************************************************************************
* Private    Function Prototypes
******************************************************************************/
VOID
GsnNcm_MsgPost(GSN_NCM_CTX_T* pNcm, UINT32 msgId);

VOID 
GsnNcm_DisassocIndCb(VOID* ctx, GSN_WDD_DISASSOCIATION_CB_INFO *pDisAssocInfo);

VOID 
GsnNcm_BeconMissIndCb(VOID* ctx, UINT32 beaconMissCnt);

VOID
GsnNcm_L2ConnectCb(VOID* ctext, INT32 status);

GSN_STATUS_T
GsnNcm_L2Connect(GSN_NCM_CTX_T* pNcm);

VOID
GsnNcm_L2DisconnectCb(VOID* ctx, INT32 status);

GSN_STATUS_T
GsnNcm_L2Disconnect(GSN_NCM_CTX_T* pNcm);

VOID
GsnNcm_L3ConnectCb(INT32 status, VOID* ctx);

GSN_STATUS_T
GsnNcm_L3Connect(GSN_NCM_CTX_T* pNcm);

GSN_STATUS_T
GsnNcm_L3Disconnect(GSN_NCM_CTX_T* pNcm);

VOID
GsnNcm_L2ConnectFail(GSN_NCM_CTX_T* pNcm);

VOID
GsnNcm_TimerCb( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle );    

VOID 
GsnNcm_FrameTxFailIndCb(VOID* ctx, GSN_WDD_FRAME_TXFAIL_INFO_T *pFrmTxFailureInfo);


/*******************************************************************************
 * Public Functions
 ******************************************************************************/
/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_Init(GSN_NCM_CTX_T* pNcm, GSN_NCM_INIT_PARAM_T *pParam)
{  
	UINT32 msgSize;

	//GSN_NCM_PRINTF("[NCM] Init\r\n");

	/*  memset the object memory */
	memset(pNcm,0,sizeof(GSN_NCM_CTX_T));

	/* Create NCM message queue */          
	msgSize = GsnOsal_QueueMsgSizeInWords(sizeof(GSN_NCM_MSG_T));
	GsnOsal_QueueCreate(&pNcm->msgQueue, msgSize, (UINT8*)pParam->msgQueueBuff,pParam->msgQueueBuffSize);

	/* Initialize object members */
	pNcm->pWdd = pParam->pWdd;
	pNcm->pNwif = pParam->pNwif;

	pNcm->execMsgPostCb = pParam->execMsgPostCb;
	pNcm->execMsgPostCbCtx = pParam->execMsgPostCbCtx;

	/* Initialize connection mgr state */
	pNcm->state= GSN_NCM_STATE_INITIALISED;
	pNcm->ncmStarted=0;

	return GSN_SUCCESS;
}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_ConfigSet(GSN_NCM_CTX_T* pNcm,  GSN_NCM_CONFIG_T* pConfig)
{
    if (pConfig != &pNcm->config)
    {
		memcpy(&pNcm->config, pConfig,  sizeof(GSN_NCM_CONFIG_T));
    }
	return GSN_SUCCESS;
}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_ConfigGet(GSN_NCM_CTX_T* pNcm,  GSN_NCM_CONFIG_T* pConfig)
{
	if((NULL != pConfig) && (pConfig != &pNcm->config))
	{
		/* copy back the config to app pointer */
		memcpy(pConfig, &pNcm->config, sizeof(GSN_NCM_CONFIG_T));
	}
	return GSN_SUCCESS;
}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_NCM_CONFIG_T *
GsnNcm_ConfigPtrGet(GSN_NCM_CTX_T* pNcm)
{    
	return &pNcm->config;
}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_Start(GSN_NCM_CTX_T* pNcm, GSN_NCM_CTX_NOTIF_CB notifCb,	VOID *notifCbCtx)
{
    GSN_STATUS_T retCode = GSN_SUCCESS;
    UINT32 msgId;
    
    /* check the module is in init state */
    if (pNcm->state != GSN_NCM_STATE_INITIALISED)
    {
        retCode = GSN_FAILURE;
        goto GsnNcm_StartExit;
    }

    GSN_NCM_PRINTF("[NCM] Start\r\n");

    /* Register asynchronous notification call backs */
    if(GSN_WIF_WLAN_NW_TYPE_STA == pNcm->pWdd->wlanNwType)
    {
        GsnWdd_DisassocIndCbReg(pNcm->pWdd,GsnNcm_DisassocIndCb, pNcm);        
        GsnWdd_BeaconMissCbReg(pNcm->pWdd, GsnNcm_BeconMissIndCb, pNcm);		
        GsnWdd_FrameTxFailIndCbReg(pNcm->pWdd, GsnNcm_FrameTxFailIndCb, pNcm);
    }
    if(GSN_WIF_WLAN_NW_TYPE_AP == pNcm->pWdd->wlanNwType)
    {
        /* Register NCM callbacks for various L2 events */
        #if 0
        GsnWdd_StaJoinedIndCbReg(pNcm->pWdd,GsnNcm_StaJoinedIndCb, pNcm);
        GsnWdd_StaDisconctedCbReg(pNcm->pWdd,GsnNcm_StaDisconnectedInd, pNcm);
        #endif
        GsnWdd_DisassocIndCbReg(pNcm->pWdd,GsnNcm_DisassocIndCb, pNcm);        
        GsnWdd_BeaconMissCbReg(pNcm->pWdd, GsnNcm_BeconMissIndCb, pNcm);		
        GsnWdd_FrameTxFailIndCbReg(pNcm->pWdd, GsnNcm_FrameTxFailIndCb, pNcm);
    }
    
    /*[TO DO] Register NCM Callbacks for various L3 events */
    /* [TO DO]Register NCM Callbacks for various L4 events */
    
    pNcm->notifCb = notifCb;
    pNcm->notifCbCtx = notifCbCtx;
        
    /* [TO DO]Register the gpio call back for going to provisioning mode if a valid gpio given*/
	msgId = GSN_NCM_CTX_MSG_ID_L2_RESTART;
	//if(TRUE == GsnWdd_AssocStatusGet(pNcm->pWdd))
	//{
	//	msgId = GSN_NCM_CTX_MSG_ID_L2_CONNECTED;
	//}

    GsnNcm_MsgPost(pNcm, msgId);    
	pNcm->ncmStarted=1;

GsnNcm_StartExit:

    return retCode;
}

PUBLIC GSN_STATUS_T
GsnNcm_ProcessStop(GSN_NCM_CTX_T* pNcm)
{
	GSN_NCM_CTX_NOTIF_CB	tmpNotifCb;
	VOID *					tmpNotifCbCtx;
    GSN_NCM_MSG_T msg;
	UINT16 disconResonCode = 8;
	GSN_NCM_PRINTF("[NCM] Process Stop\r\n");

    tmpNotifCb = pNcm->notifCb;
    tmpNotifCbCtx = pNcm->notifCbCtx;

    pNcm->notifCb = NULL;
    pNcm->notifCbCtx = NULL;

	
	/* Stop NCM timer*/
	if(NULL != pNcm->connMgrTmrHndl)
	{
		GsnSoftTmr_Stop(pNcm->connMgrTmrHndl);
		pNcm->connMgrTmrHndl = NULL;
	}

	GsnNcm_L3Disconnect(pNcm);	
	GsnWdd_Disconnect(pNcm->pWdd, disconResonCode, NULL, pNcm);
        memset(&pNcm->config.KnownChnlScanEntry,0,sizeof(GSN_WDD_SCAN_ENTRY_T));
        pNcm->config.scanEntry = FALSE;

	if(!pNcm->config.ipConfig.ipv4.staticIp)
	{
		pNcm->config.ipConfig.ipv4.ipAddr = 0;
	}
	pNcm->scanKnownChCnt = pNcm->config.retryCountsConfig.maxScanKnownChCnt;
	pNcm->scanSpecChCnt = pNcm->config.retryCountsConfig.maxScanSpecChCnt;
	pNcm->scanAllChCnt = pNcm->config.retryCountsConfig.maxScanAllChCnt;
	pNcm->L3ConnectCnt = pNcm->config.retryCountsConfig.maxL3ConnectCnt;
    pNcm->state = GSN_NCM_STATE_INITIALISED;

	while(1)
	{
        if(GSN_OSAL_SUCCESS != 
			GsnOsal_QueueGet(&pNcm->msgQueue, ( UINT8* )&msg, GSN_OSAL_NO_WAIT));  
        {
            break;
        }
	}
    if(tmpNotifCb != NULL)
    {
        (tmpNotifCb)(tmpNotifCbCtx, pNcm, GSN_NCM_NOTIF_ID_STOP);
    }
	pNcm->stopInProgress=0;
	pNcm->ncmStarted=0;
    return GSN_SUCCESS;
}
/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS_T
GsnNcm_Stop(GSN_NCM_CTX_T* pNcm, UINT32 context)
{
    GSN_STATUS_T retValue;

    GSN_NCM_PRINTF("[NCM] Stop\r\n");

	if( 0 == pNcm->ncmStarted)
	{
		return GSN_SUCCESS;
	}
    if (context == 0)
    {
        GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_STOP);    
        retValue = GSN_OPERATION_IN_PROGRESS;
    }
    else
    {
        retValue = GsnNcm_ProcessStop(pNcm);
    }

    return retValue;

}



/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC VOID
GsnNcm_Execute(GSN_NCM_CTX_T* pNcm)
{
    GSN_STATUS retcode = GSN_SUCCESS;
    GSN_OSAL_ERROR_T    errorCode;    
    UINT32 waitTicks;
    GSN_NCM_MSG_T msg;
	UINT8 alreadyConnectedEvent = 0;
    waitTicks = (TRUE == pNcm->blockingOn)?GSN_OSAL_WAIT_FOREVER:GSN_OSAL_NO_WAIT;    
    /* Read message from the NCM message queue*/
    do
    {
        /**< wait on message queue (In Blocking Mode)*/        
        errorCode = GsnOsal_QueueGet(&pNcm->msgQueue, ( UINT8* )&msg, waitTicks);                             
        if(!pNcm->blockingOn &&  GSN_OSAL_SUCCESS != errorCode)
        {
            break;
        }

        GSN_NCM_PRINTF("[NCM] Execute: MsgId = %d, state = %d\r\n", msg.msgId, pNcm->state);

		if(1 == pNcm->stopInProgress )
		{
			GsnNcm_ProcessStop(pNcm);
			break;
		}
        switch (msg.msgId)
        {
            case GSN_NCM_CTX_MSG_ID_STOP:            
            {
				if(GSN_NCM_STATE_INITIALISED      == pNcm->state   || 
				   GSN_NCM_STATE_L3_CONNECTED     == pNcm->state   ||
				   GSN_NCM_STATE_NOT_INITIALISED  == pNcm->state  
				  )
				{			
                GsnNcm_ProcessStop(pNcm);
				}
				else
				{
					pNcm->stopInProgress = 1;
				}                
                break;
            }            
            case GSN_NCM_CTX_MSG_ID_L2_RESTART:                    
            {
                pNcm->scanKnownChCnt = pNcm->config.retryCountsConfig.maxScanKnownChCnt;
                pNcm->scanSpecChCnt = pNcm->config.retryCountsConfig.maxScanSpecChCnt;
                pNcm->scanAllChCnt = pNcm->config.retryCountsConfig.maxScanAllChCnt;
                pNcm->L3ConnectCnt = pNcm->config.retryCountsConfig.maxL3ConnectCnt;
				if( pNcm->config.scanEntry)  /* If Scan entry is present of previous L2 success  */
					pNcm->state=GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP;
				else if(pNcm->config.wlanCfg.channel[0])  /* First time if user gives channel */
					pNcm->state=GSN_NCM_STATE_L2_SCAN_KNOWN_CHNL;
				else
				pNcm->state= GSN_NCM_STATE_L2_DISCONNECTED;              
                GsnNcm_L2Connect(pNcm);
                break;
            }
			case GSN_NCM_CTX_MSG_ID_L2_START:            
            {
				if( pNcm->config.scanEntry)  /* Do onetime If Scan entry is present of previous L2 success */
					pNcm->state=GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP;
                GsnNcm_L3Disconnect(pNcm);                
                GsnNcm_L2Connect (pNcm);
                break;
            }
            case GSN_NCM_CTX_MSG_ID_L2_CONNECT_FAIL:
            {
				GsnNcm_L2ConnectFail(pNcm);
				break;
			}
			case GSN_NCM_CTX_MSG_ID_L2_ALREADY_CONNECTED:
				alreadyConnectedEvent = 1;
				/* No break!!!!*/
            case GSN_NCM_CTX_MSG_ID_L2_CONNECTED:
            {
				GsnNcm_L2ConnectProcess(pNcm,alreadyConnectedEvent);
                break;            
            }
#ifdef S2W_NCM_ROAMING_SUPPORT 					
			case GSN_NCM_CTX_MSG_ID_ROAM_L2DISCONNECTED:
			{
				if(	pNcm->config.roamingCfgParams.maintainL3Con == 0)
				{
					 GsnNwIf_Close(pNcm->pNwif);
				}
				pNcm->config.scanEntry = TRUE;
                pNcm->state=GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP;
                memcpy(&pNcm->config.KnownChnlScanEntry,&pNcm->scanResults,sizeof(GSN_WDD_SCAN_ENTRY_T));


		GsnNcm_L2Connect(pNcm);
		break;	
			}
        case GSN_NCM_CTX_MSG_ID_ROAM_TRIGGER:
			{
				pNcm->roamingParams.roamingTriggered = 1;
				GsnNcm_L2Disconnect(pNcm);
				break;
			}			
#endif            
            case GSN_NCM_CTX_MSG_ID_L2_DISCONNECTED:
            {				
                GsnNcm_L2DisconnectProcess(pNcm);
                break;
            }
            case GSN_NCM_CTX_MSG_ID_L2_SYNC_LOSS:
            {
                if ((pNcm->state == GSN_NCM_STATE_L3_CONNECTED) ||
                    (pNcm->state == GSN_NCM_STATE_L2_CONNECTED))
				{
					/* First do the disconnect*/
					GsnNcm_L2Disconnect(pNcm);
				}
                break;
			}
			case GSN_NCM_CTX_MSG_ID_L3_CONNECT:
			{				
				GSN_NCM_PRINTF("Start L3 connect directly\r\n");
				/* Start L3 Connection */
                retcode = GsnNcm_L3Connect(pNcm);

                if((GSN_OPERATION_IN_PROGRESS != retcode)&&(!pNcm->config.ipConfig.ipv4.staticIp))
                {
                    GsnNcm_L3ConnectCb(retcode, pNcm);
                }
                if(pNcm->config.ipConfig.ipv4.staticIp)
                {
                   GsnNcm_L3ConnectCb(GSN_SUCCESS, pNcm);
                  
                }
				break;
			}
                        

            case GSN_NCM_CTX_MSG_ID_L3_CONNECTED:
			{
                pNcm->state = GSN_NCM_STATE_L3_CONNECTED;

                /* Successfully connected in L3, call the app CB */                
                if(pNcm->notifCb!= NULL)
                {
                    (pNcm->notifCb)(pNcm->notifCbCtx, pNcm, GSN_NCM_NOTIF_ID_L3_CONNECTED);
                } 
                pNcm->L3ConnectCnt = pNcm->config.retryCountsConfig.maxL3ConnectCnt;
                //GsnNwIf_DhcpStop(pNcm->pNwif);
#ifdef S2W_NCM_ROAMING_SUPPORT					
				if(pNcm->roamingParams.roamingTriggered == 1)
					GsnNcm_RoamReInit(pNcm);
#endif	                
                break;
			}
#ifdef S2W_NCM_ROAMING_SUPPORT		
            case GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN:
		{
					/*check whether scan retry count is met or not*/
				if ((pNcm->roamingParams.roamScanRetryCount == pNcm->config.roamingCfgParams.scanRetryCnt)
					&&	(0 != pNcm->config.roamingCfgParams.scanRetryCnt))
				{
					/*start timer for back off*/
					pNcm->roamingParams.roamScanPauseTmrHndl= 
					GsnSoftTmr_Start(&pNcm->roamingParams.roamScanPauseTmr, 
	                                   GSN_SOFT_TMR_ONESHOT,0,
	                                   GSN_SOFT_TMR_MILLISECONDS_TO_TICKS((ULONG64)(pNcm->config.roamingCfgParams.scanPauseTimeMs)),
	                                   ( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanPauseTmrCb,pNcm);
				}
				else
				{
					pNcm->config.scanEntry =0;
					memset(&pNcm->scanResults,0,sizeof(GSN_WDD_SCAN_ENTRY_T));
					pNcm->roamingParams.scaInProgress=1;
			retcode = GsnWdd_Scan(pNcm->pWdd,&pNcm->roamingParams.scanParams,(INT8 *)pNcm->roamingParams.scanUserEntryBuff,
				  (2 * sizeof(GSN_WDD_SCAN_ENTRY_T)),(GSN_WDD_SCAN_NOTIF_CB_T)GsnNcm_RoamScanConfirm,pNcm);
			if(retcode != GSN_OPERATION_IN_PROGRESS)
			{
						pNcm->roamingParams.rssiLevelChkTmrHndl = GsnSoftTmr_Start(&pNcm->roamingParams.rssiLevelChkTmr, GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(pNcm->config.roamingCfgParams.rssiLevelChkInterval),
					  ( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanTmrCb, pNcm );
					}
			}
                }
		break;
		case GSN_NCM_CTX_MSG_ID_ROAM_SCANTMR_PROCESS:
		{
			GsnNcm_RoamScanTmrProcess(pNcm);
			break;
		}
#endif                
            case GSN_NCM_CTX_MSG_ID_L3_DISCONNECTED:
            {
				if((pNcm->L3ConnectCnt == (pNcm->config.retryCountsConfig.maxL3ConnectCnt) - 1) &&
					(pNcm->notifCb!= NULL))
                {
                    (pNcm->notifCb)(pNcm->notifCbCtx, pNcm, GSN_NCM_NOTIF_ID_L3_CONNECT_FAIL);
                }	
				GsnNcm_L3Disconnect(pNcm);
                GsnNcm_L3Connect (pNcm);
            	break;
            }
            case GSN_NCM_CTX_MSG_ID_L2_IDLE:
			{
				pNcm->state = GSN_NCM_STATE_IDLE;/* Initial State*/
                /* start the idle timer */
                pNcm->connMgrTmrHndl = GsnSoftTmr_Start(&pNcm->connMgrTmr, GSN_SOFT_TMR_ONESHOT, 0, 
           									GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(pNcm->config.retryPeriodConfig.cpuWaitPeriod),
                                    		( GSN_SOFT_TMR_CBR_T )GsnNcm_TimerCb, pNcm );
              
                /* also indicate the app that ncm in idle state */
                if(pNcm->notifCb!= NULL)
                {
                    (pNcm->notifCb)(pNcm->notifCbCtx, pNcm, GSN_NCM_NOTIF_ID_L2_CONNECT_FAIL);
                }
                break;
            }
           case GSN_NCM_CTX_MSG_ID_L3_RENEWSUCESS:
               if(pNcm->notifCb!= NULL)
                {
                    (pNcm->notifCb)(pNcm->notifCbCtx, pNcm, GSN_NCM_NOTIF_ID_L3_RENEWSUCCESS);
                } 
			   pNcm->L3ConnectCnt = pNcm->config.retryCountsConfig.maxL3ConnectCnt;
               break;
            default:
			{
                break;
			}
        }        

        GSN_NCM_PRINTF("[NCM] Execute End: MsgId = %d, state = %d\r\n", msg.msgId, pNcm->state);

    } while(pNcm->blockingOn);
}

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

VOID
GsnNcm_MsgPost(GSN_NCM_CTX_T* pNcm, UINT32 msgId)
{
    GSN_NCM_MSG_T msg;

    msg.msgId = (GSN_NCM_MSGID_T)msgId;
    /* Put in the msg queue*/
    GsnOsal_QueuePut(&pNcm->msgQueue, (UINT8 *)&msg);

    /* Call the app Cb*/
    if(pNcm->execMsgPostCb != NULL)
	{
        (pNcm->execMsgPostCb)(pNcm->execMsgPostCbCtx, pNcm);
	}
	return;
}

VOID 
GsnNcm_DisassocIndCb(VOID* ctx, GSN_WDD_DISASSOCIATION_CB_INFO *pDisAssocInfo)
{
    GSN_NCM_CTX_T *pNcm;
	GSN_STATUS retCode=GSN_SUCCESS;
    pNcm = (GSN_NCM_CTX_T*)ctx;

	GSN_NCM_PRINTF("\r\n[NCM] GsnNcm_DisassocIndCb\r\n");
#ifdef S2W_NCM_ROAMING_SUPPORT 	
	
	if(pNcm->config.roamingCfgParams.roamEnable == 1)
	{
		retCode=GsnNcm_RoamStop(pNcm,1);
	}
#endif	
	if(retCode == GSN_SUCCESS)
	{    	
    	GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_L2_DISCONNECTED);
	}
	return;
}

VOID 
GsnNcm_BeconMissIndCb(VOID* ctx, UINT32 beaconMissCnt)
{
    GSN_NCM_CTX_T *pNcm;
	GSN_STATUS retCode=GSN_SUCCESS;
    pNcm = (GSN_NCM_CTX_T*)ctx;

	GSN_NCM_PRINTF("\r\n[NCM] GsnNcm_BeconMissIndCb\r\n");

	/*
		-If roaming is enabled , stop roaming.
		-if roam stop returns failure , disassociation is not processed
	*/

#ifdef S2W_NCM_ROAMING_SUPPORT 		
	if(pNcm->config.roamingCfgParams.roamEnable == 1)
	{
		retCode=GsnNcm_RoamStop(pNcm,0);
	}
#endif

	if(retCode == GSN_SUCCESS)
	{
	    GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_L2_SYNC_LOSS);
	}
	return;
}

VOID 
GsnNcm_FrameTxFailIndCb(VOID* ctx, GSN_WDD_FRAME_TXFAIL_INFO_T *pFrmTxFailureInfo)
{
    GSN_NCM_CTX_T *pNcm;
    pNcm = (GSN_NCM_CTX_T*)ctx;

    GSN_NCM_PRINTF("[NCM] Frame Tx Failure %d\r\n", pNcm->state);

    GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_L2_SYNC_LOSS);

	return;
}

VOID
GsnNcm_L2ConnectFail(GSN_NCM_CTX_T* pNcm)
{
	UINT32 timeout = 0;        
	UINT8  switchToIdleState = 0;
	UINT32 msgId;
	
    GSN_NCM_PRINTF("[NCM] L2ConnectFail\r\n");

	/* L2 failed so start the timer depends on the state */
	if(pNcm->state == GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP)
	{
		memset(&pNcm->config.KnownChnlScanEntry,0,sizeof(GSN_WDD_SCAN_ENTRY_T));
        pNcm->config.scanEntry = FALSE;

		timeout = pNcm->config.retryPeriodConfig.scanKnownChRetryIntrvl;
	
		/*Need to change the state*/
		if(pNcm->scanKnownChCnt)
		{
			pNcm->state = GSN_NCM_STATE_L2_SCAN_KNOWN_CHNL;
		}
        else if(pNcm->scanSpecChCnt)
		{
			pNcm->state = GSN_NCM_STATE_L2_SCAN_SPECIFIC_CHNL;
		}
		else if(pNcm->scanAllChCnt)
		{                            
			pNcm->state = GSN_NCM_STATE_L2_SCAN_ALL_CHNL;
		}
		else
		{
			switchToIdleState = TRUE;
		}
	
	}
	else if ((pNcm->state == GSN_NCM_STATE_L2_DISCONNECTED) || (pNcm->state ==  GSN_NCM_STATE_L2_SCAN_KNOWN_CHNL))
	{
		timeout = pNcm->config.retryPeriodConfig.scanKnownChRetryIntrvl;
		if (pNcm->scanKnownChCnt)
		{
			pNcm->scanKnownChCnt--;
		}
		else/* In Next time out, start with next state*/
		{
			/*Need to change the state*/
            if(pNcm->scanSpecChCnt)
			{
				pNcm->state = GSN_NCM_STATE_L2_SCAN_SPECIFIC_CHNL;
			}
			else if (pNcm->scanAllChCnt)
			{                            
				pNcm->state = GSN_NCM_STATE_L2_SCAN_ALL_CHNL;
			}
			else
			{
				switchToIdleState = TRUE;
			}
		}
	}
	else if (pNcm->state == GSN_NCM_STATE_L2_SCAN_SPECIFIC_CHNL)
	{
		timeout = pNcm->config.retryPeriodConfig.scanSpecChRetryIntrvl;
		if (pNcm->scanSpecChCnt)
		{
			pNcm->scanSpecChCnt--;
		}
		else
		{
			if (pNcm->scanAllChCnt)
			{                            
				pNcm->state = GSN_NCM_STATE_L2_SCAN_ALL_CHNL;
			}
			else
			{				
				switchToIdleState = TRUE;
			}
		}
	}
	else if (pNcm->state == GSN_NCM_STATE_L2_SCAN_ALL_CHNL)
	{
		timeout = pNcm->config.retryPeriodConfig.scanAllChRetryIntrvl;    
		if (pNcm->scanAllChCnt)
		{
			pNcm->scanAllChCnt--;		        
		}
		else
		{
			switchToIdleState = TRUE;
		}
	}        
	if(0 != timeout && !switchToIdleState)/*If switching to idle state, timer is started in Execute()*/
	{
		 pNcm->connMgrTmrHndl = GsnSoftTmr_Start(&pNcm->connMgrTmr, GSN_SOFT_TMR_ONESHOT,
									0, GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(timeout),
									( GSN_SOFT_TMR_CBR_T )GsnNcm_TimerCb, pNcm );
	}
	else
	{
		if(switchToIdleState && pNcm->config.retryPeriodConfig.cpuWaitPeriod)
		{
			msgId = GSN_NCM_CTX_MSG_ID_L2_IDLE;
		}
		else if(switchToIdleState)
		{			
			msgId = GSN_NCM_CTX_MSG_ID_L2_RESTART;
		}
		else
		{
			msgId = GSN_NCM_CTX_MSG_ID_L2_START;
		}				
		GsnNcm_MsgPost(pNcm, msgId);		
	}
	return;
}

VOID
GsnNcm_L2ConnectCb(VOID* ctext, INT32 status)
{
    UINT32 msg;
    GSN_NCM_CTX_T *pNcm = (GSN_NCM_CTX_T *)ctext;

    GSN_NCM_PRINTF("[NCM] L2ConnectCb: Status = %x\r\n", status);

 	msg = (status == GSN_SUCCESS)?
			GSN_NCM_CTX_MSG_ID_L2_CONNECTED: GSN_NCM_CTX_MSG_ID_L2_CONNECT_FAIL;
    GsnNcm_MsgPost(pNcm, msg); 

	return;
}

GSN_STATUS_T
GsnNcm_L2Connect(GSN_NCM_CTX_T* pNcm)
{
    GSN_STATUS_T retCode;
    UINT32 connectFlags =0;
    GSN_WDD_WLAN_CFG_T *pWlanConfig;
    GSN_WDD_SCAN_ENTRY_T *pScanFrame=NULL;
 	UINT32 msg;
    pWlanConfig = GsnWdd_WlanConfigPtrGet(pNcm->pWdd);
    GsnWdd_WlanConfigDefaultInit(pWlanConfig);

    GSN_NCM_PRINTF("[NCM] L2Connect\r\n");

    /*Copy SSID */
    GSN_WDD_SSID_CPY(&pWlanConfig->ssid,&pNcm->config.wlanCfg.ssid); 
        
    if(GSN_WIF_WLAN_NW_TYPE_STA == pNcm->pWdd->wlanNwType)/* STA mode */
    {
         connectFlags = (GSN_WDD_CONNECT_FLAG_T)(GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT | 
													GSN_WDD_CONNECT_FLAG_ACTIVE_SCAN | 
													GSN_WDD_CONNECT_FLAG_HIGHEST_RSSI_NW);
		if(pNcm->config.wlanCfg.ssid.length == 0)
		{	
			connectFlags |=  GSN_WDD_CONNECT_FLAG_USE_BSSID ;
		}
		memcpy(pWlanConfig->bssid.array,pNcm->config.wlanCfg.bssid.array,sizeof(GSN_WLAN_MAC_ADDR_T));
		
        /* scan channels depends on the current state*/
    	if(pNcm->state == GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP)
    	{
			if(pNcm->config.scanEntry)
                  pScanFrame=&pNcm->config.KnownChnlScanEntry;
			connectFlags = 0;
			/* WDD is not extracting BSSID from mac frame */      
			//memcpy(pWlanConfig->bssid.array,&pNcm->config.wlanCfg.bssid.array,sizeof(GSN_WLAN_MAC_ADDR_T));
			 memcpy(pWlanConfig->ssid.array,&pNcm->config.KnownChnlScanEntry.ssid.array,
			 		pNcm->config.KnownChnlScanEntry.ssid.length);
			pWlanConfig->ssid.length=pNcm->config.KnownChnlScanEntry.ssid.length;
            memcpy(pWlanConfig->bssid.array,&pNcm->config.KnownChnlScanEntry.bssid,sizeof(GSN_WLAN_MAC_ADDR_T));
			pWlanConfig->channel[0] = pNcm->config.KnownChnlScanEntry.channel;
			pWlanConfig->channel[1] =0;
		}
        else if ((pNcm->state == GSN_NCM_STATE_L2_SCAN_KNOWN_CHNL)  ||  (pNcm->state == GSN_NCM_STATE_L2_DISCONNECTED))
        {
                pWlanConfig->channel[0]=pNcm->config.wlanCfg.channel[0];
				pWlanConfig->channel[1]= 0;
        }
        else if (pNcm->state == GSN_NCM_STATE_L2_SCAN_SPECIFIC_CHNL)
        {            
            memcpy(pWlanConfig->channel, pNcm->config.specificChnlList, 
                                                sizeof(pNcm->config.specificChnlList));            
        }
        else if(pNcm->state == GSN_NCM_STATE_L2_SCAN_ALL_CHNL)
        {
			GsnNcm_ChannelFill(pNcm->pWdd,&(pWlanConfig->channel[0]),pNcm->config.regDomain);
        }
        else            
        {  
			/* GSN_NCM_STATE_L2_DISCONNECTED */		
            memcpy(pWlanConfig->channel, pNcm->config.wlanCfg.channel,
                                                        sizeof(pWlanConfig->channel));            
        }
		/* Bug FIX [5177] :DUT not able to associate to second AP through NCM in WPA2 security after first
		   AP is disassociated.This was due to bssid of first ap was set in wlanconfig and so the scan results 
		   were null.
		   Reset the bssid if the state is not GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP and
		   connection flag is not set as GSN_WDD_CONNECT_FLAG_USE_BSSID
		*/
		if(pNcm->state != GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP &&
			((connectFlags & GSN_WDD_CONNECT_FLAG_USE_BSSID) != GSN_WDD_CONNECT_FLAG_USE_BSSID) &&
			(GsnWdd_AssocStatusGet(pNcm->pWdd) == FALSE))
		{
			memset(pWlanConfig->bssid.array,0,GSN_WLAN_MAC_ADDR_LEN);
		}

   
    }
    else if(GSN_WIF_WLAN_NW_TYPE_AP == pNcm->pWdd->wlanNwType)/* AP mode */
    {
		memcpy((INT8 *)pWlanConfig->bssid.array, (INT8 *)pNcm->config.wlanCfg.bssid.array, 6);
		pWlanConfig->apSpecificCfg.beaconInterval = pNcm->config.wlanCfg.apSpecificCfg.beaconInterval;
		pWlanConfig->apSpecificCfg.hiddenSsid= pNcm->config.wlanCfg.apSpecificCfg.hiddenSsid;
		if(0 != pNcm->config.wlanCfg.apSpecificCfg.dtimPeriod)
		{
			pWlanConfig->apSpecificCfg.dtimPeriod= pNcm->config.wlanCfg.apSpecificCfg.dtimPeriod;
		}
		else
		{
			pWlanConfig->apSpecificCfg.dtimPeriod = NCM_DFLT_DTIMPERIOD_VALUE;
		}
		if(0 != pNcm->config.inactivityTimeoutInSec)
		{
			pNcm->pWdd->wlanConfigExtn.inactivityTimeoutInSec= pNcm->config.inactivityTimeoutInSec;
		}
		else
		{
			pNcm->pWdd->wlanConfigExtn.inactivityTimeoutInSec = NCM_DFLT_INACTIVITY_TMEOUT_VALUE;
		}
		pNcm->pWdd->groupKeyUpdateTime = pNcm->config.groupKeyUpdateTime;
		connectFlags = GSN_WDD_CONNECT_FLAG_NONE;
		pWlanConfig->channel[0] = pNcm->config.wlanCfg.channel[0];
		pWlanConfig->channel[1] = 0;
    }
        
    /* copy the security configuration */
    memcpy(&pWlanConfig->securityCfg, &pNcm->config.wlanCfg.securityCfg,
                                                sizeof(GSN_WDD_SECURITY_CONFIG_T));             
	
	/* Note : Set this before Nwif init() is done. Initialise mac address*/
	if(GsnWdd_AssocStatusGet(pNcm->pWdd) == TRUE)
	{
		msg = GSN_NCM_CTX_MSG_ID_L2_ALREADY_CONNECTED;
		GsnNcm_MsgPost(pNcm,msg);
		return GSN_SUCCESS;;
	}
        
        
    retCode = GsnWdd_Connect(pNcm->pWdd, (GSN_WDD_CONNECT_FLAG_T)connectFlags, pWlanConfig, pScanFrame, GsnNcm_L2ConnectCb,
                             pNcm);      
    GSN_NCM_PRINTF("[NCM] L2Connect Return Code : %x, Channel = %d, State = %x\r\n", retCode, pWlanConfig->channel[0], pNcm->state);

	if(retCode != GSN_OPERATION_IN_PROGRESS)
	{
		GsnNcm_L2ConnectCb(pNcm, GSN_FAILURE);
	}
    return retCode;
}

VOID
GsnNcm_L2DisconnectCb(VOID* ctx, INT32 status)
{
    GSN_NCM_CTX_T *pNcm = (GSN_NCM_CTX_T *)ctx;
    
    GSN_NCM_PRINTF("[NCM] L2DisconnectCb:%x\r\n", status);

#ifdef S2W_NCM_ROAMING_SUPPORT				
	if(pNcm->roamingParams.roamingTriggered  == 1 && status == GSN_SUCCESS )
	{		
		GsnNcm_MsgPost(pNcm,GSN_NCM_CTX_MSG_ID_ROAM_L2DISCONNECTED);
	}
	else
#endif	
    
    /* Post the message*/
    GsnNcm_MsgPost(pNcm,GSN_NCM_CTX_MSG_ID_L2_DISCONNECTED);
}

GSN_STATUS_T
GsnNcm_L2Disconnect(GSN_NCM_CTX_T* pNcm)
{
    GSN_STATUS_T retCode;    
    UINT16 disconResonCode = 8;

    GSN_NCM_PRINTF("[NCM] L2Disconnect\r\n");

    retCode = GsnWdd_Disconnect(pNcm->pWdd, disconResonCode, GsnNcm_L2DisconnectCb, pNcm);

    pNcm->state = GSN_NCM_STATE_L2_DISCONNECTING;

    return retCode;
}

VOID
GsnNcm_L3ConnectCb(INT32 status, VOID* ctx)
{
    GSN_NCM_CTX_T *pNcm = (GSN_NCM_CTX_T *)ctx;

    GSN_NCM_PRINTF("[NCM] L3ConnectCb: Status = %x\r\n", status);

    if(status == GSN_SUCCESS)
    {
        /* If the dhcp renewal happens successfully then no need to post the msg */
        if (pNcm->state != GSN_NCM_STATE_L3_CONNECTED)
        {
            GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_L3_CONNECTED);
        }
        else if(pNcm->state == GSN_NCM_STATE_L3_CONNECTED)
        {
          /* Always stop DHCP thread , if L3 is success */
          GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_L3_RENEWSUCESS);
        }
    }
    else if(status == GSN_NW_DHCP_LEASE_EXPIRED)
    {
      /* This call back is called in renew timer context */
       GsnNcm_MsgPost(pNcm,GSN_NCM_CTX_MSG_ID_L3_DISCONNECTED);
      
    }
    else
    {   
		pNcm->L3ConnFailed=0;                 
        if(pNcm->L3ConnectCnt && pNcm->config.retryPeriodConfig.l3ConnectRetryIntrvl)
        {                
            pNcm->L3ConnectCnt--;
            pNcm->connMgrTmrHndl = GsnSoftTmr_Start(&pNcm->connMgrTmr, GSN_SOFT_TMR_ONESHOT, 0, 
                              			GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(pNcm->config.retryPeriodConfig.l3ConnectRetryIntrvl),
                              			( GSN_SOFT_TMR_CBR_T )GsnNcm_TimerCb, pNcm );        
        }
        else
        {
	        pNcm->L3ConnFailed =1;
            /*[TO DO]Go to CPU wait state or disconnect and connect again*/                                                
            GsnNcm_MsgPost(pNcm, GSN_NCM_CTX_MSG_ID_L2_SYNC_LOSS);    
        }
    }
}

GSN_STATUS_T
GsnNcm_L3Connect(GSN_NCM_CTX_T* pNcm)
{
    GSN_STATUS_T retVal;
    pNcm->pNwif->notifyCb = GsnNcm_L3ConnectCb;
    pNcm->pNwif->notifyCtxt = pNcm;
#ifdef S2W_NCM_ROAMING_SUPPORT	
	if(pNcm->roamingParams.roamingTriggered == 1 && pNcm->config.roamingCfgParams.maintainL3Con == 0)
	{
		retVal = GsnNwIf_Open(pNcm->pNwif, &pNcm->config.ipConfig,&pNcm->config.dhcpV4Cfg);
	}	
	else
#endif    
        {
    GSN_NCM_PRINTF("[NCM] L3Connect\r\n");
    retVal = GsnNwIf_Open(pNcm->pNwif, &pNcm->config.ipConfig, &pNcm->config.dhcpV4Cfg);
        }
    return retVal;
}

GSN_STATUS_T
GsnNcm_L3Disconnect(GSN_NCM_CTX_T* pNcm)
{    
    GSN_STATUS_T retVal;

    GSN_NCM_PRINTF("[NCM] L3Disconnect\r\n");

    pNcm->pNwif->notifyCb = NULL;
    pNcm->pNwif->notifyCtxt = NULL;
    retVal = GsnNwIf_Close(pNcm->pNwif);

    return retVal;
}

VOID
GsnNcm_TimerCb( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle )
{
    UINT32 msgId = GSN_NCM_CTX_MSG_ID_MAX;
    GSN_NCM_CTX_T *pNcm = (GSN_NCM_CTX_T *)context;

    GSN_NCM_PRINTF("[NCM] Timer Event: %x\r\n", pNcm->state);

    switch(pNcm->state)
    {
        case GSN_NCM_STATE_IDLE:
            msgId = GSN_NCM_CTX_MSG_ID_L2_RESTART;
            break;
        case GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP:  /* Onetime scan with known AP */
        	msgId = GSN_NCM_CTX_MSG_ID_L2_RESTART;
        	break;
        case GSN_NCM_STATE_L2_SCAN_KNOWN_CHNL:
        case GSN_NCM_STATE_L2_DISCONNECTED:
        case GSN_NCM_STATE_L2_SCAN_SPECIFIC_CHNL:
        case GSN_NCM_STATE_L2_SCAN_ALL_CHNL:
            msgId = GSN_NCM_CTX_MSG_ID_L2_START;
            break;
        case GSN_NCM_STATE_L2_CONNECTED:            
            msgId = GSN_NCM_CTX_MSG_ID_L3_DISCONNECTED;
			break;
        case GSN_NCM_STATE_L3_CONNECTED:     /* Timer is started if L3 fails after leasetime expires */
            msgId = GSN_NCM_CTX_MSG_ID_L3_DISCONNECTED;
            break;
    }
	if(msgId < GSN_NCM_CTX_MSG_ID_MAX)
    	GsnNcm_MsgPost(pNcm, msgId);    

	return;
}


/**
 ******************************************************************
 * @ingroup GsnNcm
 * @brief To fill valid channel numbers depending on reg domain 
 *   This function shall be called during scan or connect 
 *  @param pWdd    :  WDD context pointer
 *  @param chTable :  Pointer to array to hold the valid channel numbers
 *  @param domain  :  Regulatory domain
 *  @retval none.
 *  Important Note: chTable[] array size must be GSN_WDD_WLAN_MAX_CHNLS+1
 ******************************************************************/
VOID 
GsnNcm_ChannelFill(GSN_WDD_CTX_T *pWdd,UINT8 *chTable,UINT8 domain)
{
	UINT8 index=0;

	/* fill the channels  */
	for(index=0;index<=13;index++)
    {
    	chTable[index] = index+1;
   	}
   	if(domain == GSN_NCM_REG_DOMAIN_FCC)
  	{/* 1 to 11 are valid */
      index=11;
   	}
   	else if(domain == GSN_NCM_REG_DOMAIN_ETSI)
   	{/* 1 to 13 are valid */
       index=13;
   	}
	else if(domain ==GSN_NCM_REG_DOMAIN_TELEC)
		index=14;
   	for(;index<=14;index++)
   	{
       chTable[index] = 0;  /* Mask channels depending on REG domain and last entry must be ZERO */
   	}
}

/**
 ******************************************************************
 * @ingroup GsnNcm
 * @brief process the l2 connect event
 *   This function shall be called after l2 connect 
 *  @param pNcm    :  NCM context pointer
 *  @param alreadyConnectedEvent :  flag to check whether L2 is already connected
 *  @retval none.
 ******************************************************************/
PRIVATE VOID
GsnNcm_L2ConnectProcess(GSN_NCM_CTX_T* pNcm,UINT8 alreadyConnectedEvent )
{
	GSN_WDD_WLAN_CFG_T *pWlanConfig;
	GSN_STATUS retcode = GSN_SUCCESS;
	
	/* store the wlan config paramteres */
	pWlanConfig = GsnWdd_WlanConfigPtrGet(pNcm->pWdd);
	memcpy(&pNcm->config.wlanCfg, pWlanConfig, sizeof(GSN_WDD_WLAN_CFG_T));
	if((FALSE == pNcm->config.scanEntry)   && (0 != pNcm->pWdd->scanEntry.frameLen ))
	{
		memcpy(&pNcm->config.KnownChnlScanEntry,&pNcm->pWdd->scanEntry,sizeof(GSN_WDD_SCAN_ENTRY_T));
	    pNcm->config.scanEntry = TRUE;
	}
	pNcm->config.wlanCfg.channel[0] = pWlanConfig->channel[0];
	
	/* Change the state to GSN_NCM_STATE_L2_CONNECTED */
	pNcm->state = GSN_NCM_STATE_L2_CONNECTED;

	/* Successfully associated, call the app CB */
	if(pNcm->notifCb != NULL)
	{
		(pNcm->notifCb)(pNcm->notifCbCtx, pNcm, GSN_NCM_NOTIF_ID_L2_CONNECTED);
	}
#ifdef S2W_NCM_ROAMING_SUPPORT			
	if((pNcm->roamingParams.roamingTriggered == TRUE) && (pNcm->config.roamingCfgParams.maintainL3Con == TRUE))				
	{
		GsnNcm_RoamReInit(pNcm);	
		return;
	}
	else
#endif                
	{
		
		/* Start L3 Connection */
		if(!alreadyConnectedEvent && !pNcm->config.ipConfig.ipv4.staticIp)/* Not the NORMAL BOOT connect*/
		{
			pNcm->config.ipConfig.ipv4.ipAddr = 0;
		}
		retcode = GsnNcm_L3Connect(pNcm);

		if((GSN_OPERATION_IN_PROGRESS != retcode)&&(!pNcm->config.ipConfig.ipv4.staticIp))
		{
	    	GsnNcm_L3ConnectCb(retcode, pNcm);
		}
		 	if(pNcm->config.ipConfig.ipv4.staticIp)
		{
	   		GsnNcm_L3ConnectCb(GSN_SUCCESS, pNcm);                  
		}
	}
}

/**
 ******************************************************************
 * @ingroup GsnNcm
 * @brief process the l2 disconnect connect event
 *   This function shall be called after l2 connect 
 *  @param pNcm    :  NCM context pointer
 *  @retval none.
 ******************************************************************/
PRIVATE VOID
GsnNcm_L2DisconnectProcess(GSN_NCM_CTX_T* pNcm)
{
	
	if ((pNcm->state == GSN_NCM_STATE_L2_DISCONNECTING) || 
		(pNcm->state == GSN_NCM_STATE_L2_CONNECTED) ||
		(pNcm->state == GSN_NCM_STATE_L3_CONNECTED))
	{

		/* if state is GSN_NCM_STATE_L3_CONNECTED then use scan entry*/
		if ((pNcm->state == GSN_NCM_STATE_L3_CONNECTED))
		{
			if( pNcm->config.scanEntry)  /* Do onetime If Scan entry is present of previous L2 success */
				pNcm->state=GSN_NCM_STATE_L2_CONCT_TO_KNOWN_AP;
			else
				pNcm->state = GSN_NCM_STATE_L2_DISCONNECTED;
		}
		else
		{
			memset(&pNcm->config.KnownChnlScanEntry,0,sizeof(GSN_WDD_SCAN_ENTRY_T));
			pNcm->config.scanEntry = FALSE;
			pNcm->state = GSN_NCM_STATE_L2_DISCONNECTED;
		}
		if(NULL != pNcm->connMgrTmrHndl)
		{
			GsnSoftTmr_Stop(pNcm->connMgrTmrHndl);
			pNcm->connMgrTmrHndl = NULL;
		}
		/* Notify the app */
		if(pNcm->notifCb != NULL &&  pNcm->L3ConnFailed == 0)
		{
			(pNcm->notifCb )(pNcm->notifCbCtx, pNcm, GSN_NCM_NOTIF_ID_L2_DISCONNECTED);
		}
		pNcm->L3ConnFailed =0;
		GsnNcm_L3Disconnect(pNcm);				  

		/* Reset the IP Address. Handle disassiciation after standby */
		if(!pNcm->config.ipConfig.ipv4.staticIp)
		{
			pNcm->config.ipConfig.ipv4.ipAddr = 0;
		}
		pNcm->scanKnownChCnt = pNcm->config.retryCountsConfig.maxScanKnownChCnt;
		pNcm->scanSpecChCnt = pNcm->config.retryCountsConfig.maxScanSpecChCnt;
		pNcm->scanAllChCnt = pNcm->config.retryCountsConfig.maxScanAllChCnt;
		pNcm->L3ConnectCnt = pNcm->config.retryCountsConfig.maxL3ConnectCnt;
		GsnNcm_L2Connect(pNcm);
	}
}
