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
* $RCSfile: gsn_ncm_roam.c,v $
*
* Description : This file contains public definitions for nw connection manager.
* It provides APIs for the nw connection manager
*******************************************************************************/
#if defined(S2W_NCM_ROAMING_SUPPORT) && defined(S2W_NCM_SUPPORT_ENABLE)			
#if 0
#define ncmDbg_Printf S2w_Printf
#else
int ncmDbg_Printf(const char *format, ...)
{
	return 0;
}
#endif
/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_defines.h"
#include "gsn_includes.h"
#include "gsn_ncm.h"
#include "gsn_ncm_roam.h"


PUBLIC VOID
GsnNcm_RoamScanParamInit(GSN_NCM_CTX_T* pNcm)
{

	 GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(pNcm->pWdd);
         UINT8 chIndex;
	
	memset(&pNcm->roamingParams.scanParams,0,sizeof(GSN_WDD_SCAN_PARAMS_T));
	memcpy(pNcm->roamingParams.scanParams.ssid.array,pWlanConfig->ssid.array,pWlanConfig->ssid.length);
	pNcm->roamingParams.scanParams.ssid.length = pWlanConfig->ssid.length;	
	pNcm->roamingParams.scanParams.channel[0] = pWlanConfig->channel[0];
	pNcm->roamingParams.scanParams.channel[1] =  pWlanConfig->channel[1];
	pNcm->roamingParams.scanParams.scanType = GSN_WDD_SCAN_TYPE_ACTIVE;
	pNcm->roamingParams.currentChIndex=0;
    pNcm->roamingParams.scanParams.flags |= GSN_WDD_SCAN_FLAG_HIGHEST_RSSI_NW_FIND;
	for(chIndex=0;chIndex<= GSN_WDD_WLAN_MAX_CHNLS;chIndex++)
	{
		if(pNcm->roamingParams.channelList[chIndex] == pNcm->roamingParams.scanParams.channel[0] )
		{
			/*locate the current channel */
			pNcm->roamingParams.currentChIndex= chIndex;
			break;
		}
	}
	ncmDbg_Printf("\r\n chIndex:%d",pNcm->roamingParams.currentChIndex);
}
PUBLIC VOID
GsnNcm_RoamScanParamUpdate(GSN_NCM_CTX_T* pNcm)
{
 	GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(pNcm->pWdd);	
	memset(&pNcm->roamingParams.scanParams,0,sizeof(GSN_WDD_SCAN_PARAMS_T));
	memcpy(pNcm->roamingParams.scanParams.ssid.array,pWlanConfig->ssid.array,pWlanConfig->ssid.length);
	pNcm->roamingParams.scanParams.ssid.length = pWlanConfig->ssid.length;	
		
	if(0 == pNcm->roamingParams.channelList[pNcm->roamingParams.currentChIndex])
    {
		pNcm->roamingParams.currentChIndex=0;
    }
	if(pNcm->roamingParams.channelList[pNcm->roamingParams.currentChIndex] != 0)
	{
		pNcm->roamingParams.scanParams.channel[0] = pNcm->roamingParams.channelList[pNcm->roamingParams.currentChIndex];
	}
	else
	{
		pNcm->roamingParams.scanParams.channel[0] = pNcm->roamingParams.channelList[0];
	}
        
	pNcm->roamingParams.scanParams.channel[1] =  0;
	pNcm->roamingParams.scanParams.scanType = GSN_WDD_SCAN_TYPE_ACTIVE;
	
}
PUBLIC VOID
GsnNcm_RoamScanParamReInit(GSN_NCM_CTX_T* pNcm)
{


	pNcm->roamingParams.currentChIndex++;
	/* finished all channel scan ,then increment retry count*/
    if(pNcm->pWdd->wlanConfig.channel[0] == pNcm->roamingParams.currentChIndex)
    {
        pNcm->roamingParams.roamScanRetryCount++;
    }
   	GsnNcm_RoamScanParamUpdate(pNcm);
}

UINT8
GsnNcm_RoamRssiStatusGet(GSN_NCM_CTX_T* pNcm,UINT8 rssiLvl)
{
	UINT8 RoamState=0;
        /* change state to below lower threshold */
	if(rssiLvl < pNcm->config.roamingCfgParams.rssiLowerTh)
	{
		RoamState = RSSI_BELOW_LOWER_TH;
		ncmDbg_Printf("\r\n[NCM_ROAM]:RSSILVL:%d:%d:%d:%d:%d:%d:%d",rssiLvl,pNcm->config.roamingCfgParams.rssiHigherTh,
		pNcm->config.roamingCfgParams.rssiLowerTh,(signed char)rssiLvl,(signed char)pNcm->config.roamingCfgParams.rssiHigherTh,
		(signed char)pNcm->config.roamingCfgParams.rssiLowerTh,pNcm->roamingParams.rssiTrendcnt);
	
	}	
	/* change state to above higher threshold */
	else if((rssiLvl > pNcm->config.roamingCfgParams.rssiHigherTh) &&
			pNcm->roamingParams.lastRssi < pNcm->config.roamingCfgParams.rssiHigherTh )
	{
		RoamState = RSSI_ABOVE_HIGHER_TH;
	}
	/* change state to crossed Lower threshold */
	else if((rssiLvl > pNcm->config.roamingCfgParams.rssiLowerTh) && (pNcm->roamingParams.lastRssi < pNcm->config.roamingCfgParams.rssiLowerTh))
	{

		RoamState = RSSI_ABOVE_LOWER_TH;
	}
	else
    {
		RoamState = RSSI_LEVEL_CONSTANT_TH;	
    }
	pNcm->roamingParams.lastRssi = rssiLvl;
	return RoamState;
}
PRIVATE VOID
GsnNcm_RoamLowerThProcess(GSN_NCM_CTX_T* pNcm)
{
	GSN_STATUS retCode = GSN_SUCCESS;
	
	pNcm->roamingParams.rssiTrendcnt++;
	if(pNcm->roamingParams.rssiTrendcnt > pNcm->config.roamingCfgParams.thresholdCrossedCnt)
	{
		GsnSoftTmr_Stop(pNcm->roamingParams.rssiLevelChkTmrHndl);
		pNcm->roamingParams.rssiTrendcnt=0;
		memset(pNcm->roamingParams.roamAp.array,0,GSN_MAC_SSID_LEN);
		memset(&pNcm->scanResults,0,sizeof(GSN_WDD_SCAN_ENTRY_T));
		GsnNcm_RoamScanParamInit(pNcm);
		ncmDbg_Printf("\r\n[NCM_ROAM]:Scan Start");
		pNcm->roamingParams.scanParams.flags |= GSN_WDD_SCAN_FLAG_HIGHEST_RSSI_NW_FIND;
		pNcm->roamingParams.scaInProgress = 1;		
		retCode = GsnWdd_Scan(pNcm->pWdd,&pNcm->roamingParams.scanParams,(INT8 *)pNcm->roamingParams.scanUserEntryBuff,
				  (2 * sizeof(GSN_WDD_SCAN_ENTRY_T)),(GSN_WDD_SCAN_NOTIF_CB_T)GsnNcm_RoamScanConfirm,pNcm);
		if(retCode == GSN_OPERATION_IN_PROGRESS)
		{
			pNcm->roamingParams.roamState = GSN_ROAM_INIT;
		}
		else
		{
			ncmDbg_Printf("\r\n[NCM_ROAM]:Scan Failed1:%x",retCode);
			pNcm->roamingParams.rssiLevelChkTmrHndl = GsnSoftTmr_Start(&pNcm->roamingParams.rssiLevelChkTmr, GSN_SOFT_TMR_ONESHOT,
					0,(ULONG64)(pNcm->config.roamingCfgParams.rssiLevelChkInterval),( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanTmrCb, pNcm );
		}		
	}
	else
	{
		pNcm->roamingParams.rssiLevelChkTmrHndl = GsnSoftTmr_Start(&pNcm->roamingParams.rssiLevelChkTmr, GSN_SOFT_TMR_ONESHOT,
			0,(ULONG64)(pNcm->config.roamingCfgParams.rssiLevelChkInterval),( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanTmrCb, pNcm );
	}
}


PUBLIC VOID
GsnNcm_RoamScanConfirm(VOID *cText,INT32 status,INT8 *rsltBuff,UINT32 rsltCount)
{
	UINT8 higherTh;
	GSN_NCM_CTX_T *NcmCtx = (GSN_NCM_CTX_T *)cText;
	UINT32 msg,i=0;
    GSN_WDD_WLAN_CFG_T *wlanConfig = GsnWdd_WlanConfigPtrGet(NcmCtx->pWdd);
	NcmCtx->roamingParams.scaInProgress=0;
    switch(NcmCtx->roamingParams.roamState)
    {
	    case GSN_ROAM_INIT:
		case GSN_ROAM_REINIT:
		{
			/* 	
					The first Scan confirmation
				- Check whether the rssi level of scanned ap is above highest rssi
				- if yes then assign the ap as roam ap .
				- initiate scan to check rssi level iof  roam ap
			*/			
			GSN_WDD_SCAN_ENTRY_T* scanEntryBuff = (GSN_WDD_SCAN_ENTRY_T*)(rsltBuff + (i*sizeof(GSN_WDD_SCAN_ENTRY_T))) ;
			memcpy(&NcmCtx->scanResults,scanEntryBuff,sizeof(GSN_WDD_SCAN_ENTRY_T));
			higherTh= NcmCtx->config.roamingCfgParams.rssiHigherTh;

			if(NcmCtx->roamingParams.rssiTrendRoamAp == 0 )
			{
			    if((NcmCtx->scanResults.rssi > higherTh))	
			    {
			    
					GsnMacUtil_ExtractSsid((GSN_MAC_FRAME_T*)NcmCtx->scanResults.frame,
					NcmCtx->scanResults.frameLen,&NcmCtx->roamingParams.roamAp);
					memcpy((void *)NcmCtx->roamingParams.roamApBssID.array,NcmCtx->scanResults.bssid,GSN_MAC_ADDR_LEN);

					/* If the roamAP is same as connected one, de init the roaming.
					this will reset the states and other variables . Also reset the WDD state */
	                if(memcmp(wlanConfig->bssid.array,NcmCtx->roamingParams.roamApBssID.array,GSN_MAC_ADDR_LEN) == 0)
	                {
	                    ncmDbg_Printf("\r\n[NCM_ROAM]:Roaming Not required");
						GsnNcm_RoamReInit(NcmCtx);
	                    break;
	                }

					/* 
					Update ROAM AP params.The next scan will be check for stable rsssi level of same AP.
				
					*/
					NcmCtx->roamingParams.rssiTrendRoamAp++;
	                NcmCtx->roamingParams.roamApCh= GsnMacUtil_ExtractChannel((GSN_MAC_FRAME_T*)NcmCtx->scanResults.frame,NcmCtx->scanResults.frameLen);
	                ncmDbg_Printf("\r\n[NCM_ROAM]:Roam Ap Ch:%d\r\n",NcmCtx->roamingParams.roamApCh);
	                NcmCtx->roamingParams.scanParams.channel[0] = NcmCtx->roamingParams.roamApCh;
	                NcmCtx->roamingParams.scanParams.channel[1] =0;
	                NcmCtx->config.wlanCfg.channel[0] =  NcmCtx->roamingParams.roamApCh;
	                NcmCtx->config.wlanCfg.channel[1] = 0;
	                memcpy(NcmCtx->roamingParams.scanParams.ssid.array,NcmCtx->roamingParams.roamAp.array,NcmCtx->roamingParams.roamAp.length);
				    memcpy(NcmCtx->roamingParams.scanParams.bssid.array,NcmCtx->scanResults.bssid,GSN_MAC_ADDR_LEN);
	                                    NcmCtx->roamingParams.scanParams.ssid.length = NcmCtx->roamingParams.roamAp.length;
					NcmCtx->roamingParams.scanFlag = 0;

					msg=GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN;
					GsnNcm_MsgPost(NcmCtx, msg);
				}
				else 
				{
					/*
						san will continue ,if we donot get the ap with rssi level 
						which is higher than higest rssi threshold
					*/
					GsnNcm_RoamScanParamReInit(NcmCtx);	
					NcmCtx->roamingParams.scanFlag = GSN_WDD_SCAN_FLAG_HIGHEST_RSSI_NW_FIND;
					msg=GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN;
					GsnNcm_MsgPost(NcmCtx, msg);
				}
			}
			else
			{			
				/* 	
			    			 Scan confirmation
						- Check whether the rssi level of scanned ap is above highest rssi
						- if yes then incremet the rssi trending count.
						- if count reached the maximum level then trigger roaming by disconnecting L2
						- if the rssi level is below highest rssi level then find the new roam AP by triggering the scan.				
				*/
				if((NcmCtx->scanResults.rssi > higherTh))	
				{
				    NcmCtx->roamingParams.rssiTrendRoamAp++;					
					if(NcmCtx->roamingParams.rssiTrendRoamAp > NcmCtx->config.roamingCfgParams.thresholdCrossedCnt)
	                {
	                	ncmDbg_Printf("\r\n[NCM_ROAM]:GsnNcm_L2Disconnect");
						msg=GSN_NCM_CTX_MSG_ID_ROAM_TRIGGER;
						GsnWdd_ScanStop(NcmCtx->pWdd);
						GsnNcm_MsgPost(NcmCtx, msg);
						break;
	                }
					else
	                {
						//GsnNcm_RoamScanParamUpdate(NcmCtx);
						NcmCtx->roamingParams.scanFlag = 0;
						msg=GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN;
						GsnNcm_MsgPost(NcmCtx, msg);
					}
				}
				else 
				{
	               
					NcmCtx->roamingParams.rssiTrendRoamAp = 0;
					memset(NcmCtx->roamingParams.roamAp.array,0,GSN_MAC_ADDR_LEN);
					memset(NcmCtx->roamingParams.roamApBssID.array,0,GSN_MAC_ADDR_LEN);
					NcmCtx->roamingParams.roamAp.length=0;
					GsnNcm_RoamScanParamInit(NcmCtx);		
					NcmCtx->roamingParams.scanFlag = GSN_WDD_SCAN_FLAG_HIGHEST_RSSI_NW_FIND;
					msg=GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN;
					GsnNcm_MsgPost(NcmCtx, msg);
				}              
			}				
			break;
		}
		case GSN_ROAM_STOP:
		{
			ncmDbg_Printf("\r\n[NCM_ROAM]:GSN_ROAM_STOP");
			GsnWdd_ScanStop(NcmCtx->pWdd);
			if(NcmCtx->roamingParams.cbPending == 1)
			{
				GsnNcm_DisassocIndCb(NcmCtx,NULL);
			}
			else
			{
				GsnNcm_BeconMissIndCb(NcmCtx,0);		
			}
			break;
		}
		default:
		{
			GsnWdd_ScanStop(NcmCtx->pWdd);
			break;
		}
	}
}


PUBLIC VOID
GsnNcm_RoamScanTmrCb( VOID* context,GSN_SOFT_TMR_HANDLE_T timerHandle )
{
	GSN_NCM_CTX_T *NcmCtx = (GSN_NCM_CTX_T *)context;
	GsnSoftTmr_Stop(NcmCtx->roamingParams.rssiLevelChkTmrHndl);
	GsnNcm_MsgPost(NcmCtx, GSN_NCM_CTX_MSG_ID_ROAM_SCANTMR_PROCESS);
}
PUBLIC VOID
GsnNcm_RoamScanTmrProcess( GSN_NCM_CTX_T *NcmCtx)
{
	UINT8 rssiStatus;
	GSN_WIF_WLAN_RSSI_T    wRssi;
	if(NcmCtx->state == GSN_NCM_STATE_L3_CONNECTED && NcmCtx->config.roamingCfgParams.roamEnable== 0)
	{

	}
	switch(NcmCtx->roamingParams.roamState)
	{
		case GSN_ROAM_REINIT:
		case GSN_ROAM_NOT_REQUIRED:
		{
          
			GsnWdd_RSSIGet(NcmCtx->pWdd, (INT8*)&wRssi, sizeof(GSN_WIF_WLAN_RSSI_T));
            rssiStatus = GsnNcm_RoamRssiStatusGet(NcmCtx,wRssi.rssi);

			if(rssiStatus == RSSI_BELOW_LOWER_TH)
			{
				GsnNcm_RoamLowerThProcess(NcmCtx);
			}
			else
			{
				/* Reset the counter and Restart the scan timer*/
				NcmCtx->roamingParams.rssiTrendcnt=0;
				NcmCtx->roamingParams.rssiLevelChkTmrHndl = GsnSoftTmr_Start(&NcmCtx->roamingParams.rssiLevelChkTmr, GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(NcmCtx->config.roamingCfgParams.rssiLevelChkInterval),
				  ( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanTmrCb, NcmCtx );
			}
			break;
		}
		case GSN_ROAM_INIT:
			break;
		default:
			break;
	}
}
/**
 ******************************************************************
 * @ingroup  GsnRoam
 * @This function starts the Roaming.
 *  This function initiate the Roaming.
 * @param ctx- IN Pointer to NCM context.
 * @return None.
 ******************************************************************/
PUBLIC VOID
GsnNcm_RoamStart(GSN_NCM_CTX_T *pNcm,UINT8 domain)
{
	ncmDbg_Printf("\r\n[NCM_ROAM]: ROAMING started \r\n");
	ncmDbg_Printf("\r\n[NCM_ROAM]: Enable:%d",pNcm->config.roamingCfgParams.roamEnable);
	ncmDbg_Printf("\r\n[NCM_ROAM]: HTH:%d",(signed char)pNcm->config.roamingCfgParams.rssiHigherTh);
	ncmDbg_Printf("\r\n[NCM_ROAM]: LTH:%d",(signed char)pNcm->config.roamingCfgParams.rssiLowerTh);
	ncmDbg_Printf("\r\n[NCM_ROAM]: rssiChkInterval:%d",pNcm->config.roamingCfgParams.rssiLevelChkInterval);
	ncmDbg_Printf("\r\n[NCM_ROAM]: THCRSSCNT:%x",pNcm->config.roamingCfgParams.thresholdCrossedCnt);
	ncmDbg_Printf("\r\n[NCM_ROAM]: L3KEEP:%x",pNcm->config.roamingCfgParams.maintainL3Con);
	ncmDbg_Printf("\r\n[NCM_ROAM]: L4KEEP:%x",pNcm->config.roamingCfgParams.maintainL4Con);
	ncmDbg_Printf("\r\n[NCM_ROAM]: scanRetryCnt:%d",pNcm->config.roamingCfgParams.scanRetryCnt);	
	ncmDbg_Printf("\r\n[NCM_ROAM]: scanPauseTimeMs:%d",pNcm->config.roamingCfgParams.scanPauseTimeMs);

	
	GsnNcm_ChannelFill(pNcm->pWdd,&(pNcm->roamingParams.channelList[0]),domain);
	pNcm->roamingParams.roamState = GSN_ROAM_NOT_REQUIRED;
	GsnSoftTmr_Start(&pNcm->roamingParams.rssiLevelChkTmr, GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(pNcm->config.roamingCfgParams.rssiLevelChkInterval),
					  ( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanTmrCb, pNcm );

	
}

/******************************************************************
* @ingroup  GsnRoam
* @This function Stops the Roaming.
*  This function initiate the Roaming.
* @param ctx- IN Pointer to NCM context.
* @return None.
******************************************************************/
PUBLIC GSN_STATUS
GsnNcm_RoamStop(GSN_NCM_CTX_T* ctx,UINT8 cbflg)
{
	ncmDbg_Printf("\r\n ROAMING stopped :%x:%x\r\n",ctx->roamingParams.roamState ,ctx->roamingParams.scaInProgress);
	if(ctx->roamingParams.roamState == GSN_ROAM_INIT && ctx->roamingParams.scaInProgress == 1)		
	{
		ctx->roamingParams.roamState = GSN_ROAM_STOP;
		ctx->roamingParams.cbPending = cbflg;
		return GSN_OPERATION_IN_PROGRESS;
	}
	else
	{
		ctx->roamingParams.roamState = GSN_ROAM_NOT_REQUIRED;
		GsnSoftTmr_Stop(ctx->roamingParams.rssiLevelChkTmrHndl);
		memset(&ctx->roamingParams.roamAp.array,0,GSN_MAC_SSID_LEN);
		memset(&ctx->roamingParams.roamApBssID.array,0,GSN_MAC_ADDR_LEN);
		ctx->roamingParams.roamAp.length = 0;
		ctx->roamingParams.rssiTrendcnt = 0;
		ctx->roamingParams.rssiTrendRoamAp=0;
		ctx->roamingParams.roamingTriggered = 0;
		ctx->roamingParams.roamScanRetryCount=0;
		
		return GSN_SUCCESS;
	}
}
PUBLIC VOID
GsnNcm_RoamInit(GSN_NCM_CTX_T* pNcm)
{
 	pNcm->roamingParams.roamState = GSN_ROAM_NOT_REQUIRED;
	pNcm->roamingParams.roamingTriggered = FALSE;
	pNcm->roamingParams.rssiTrendRoamAp = 0;
	pNcm->roamingParams.rssiTrendcnt = 0;
	pNcm->roamingParams.currentChIndex = 0;
	pNcm->roamingParams.roamScanRetryCount=0;
}
/**
 ******************************************************************
 * @ingroup  GsnRoam
 * @This function de-initialise the Roaming parameters.
 *  This function de-initialise the Roaming parameters.
 * @param ctx- IN Pointer to NCM context.
 * @return None.
 ******************************************************************/
PUBLIC VOID
GsnNcm_RoamReInit(GSN_NCM_CTX_T* ctx)
{


	memset(&ctx->roamingParams.roamAp.array,0,GSN_MAC_SSID_LEN);
	memset(&ctx->roamingParams.roamApBssID.array,0,GSN_MAC_ADDR_LEN);
	ctx->roamingParams.roamAp.length = 0;
	ctx->roamingParams.roamState=GSN_ROAM_NOT_REQUIRED;
	ctx->roamingParams.rssiTrendcnt = 0;
	ctx->roamingParams.rssiTrendRoamAp=0;
	ctx->roamingParams.roamingTriggered = 0;
	ctx->roamingParams.roamScanRetryCount=0;
	
	GsnSoftTmr_Start(&ctx->roamingParams.rssiLevelChkTmr, GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(ctx->config.roamingCfgParams.rssiLevelChkInterval),
					  ( GSN_SOFT_TMR_CBR_T )GsnNcm_RoamScanTmrCb, ctx );
}

PUBLIC VOID
GsnNcm_RoamScanPauseTmrCb( VOID* context,GSN_SOFT_TMR_HANDLE_T timerHandle )
{
	UINT32 msg;
	GSN_NCM_CTX_T *NcmCtx = (GSN_NCM_CTX_T *)context;

	/*Reset the 'scan retry count' and 'scan back off timer' */
	
	/*This is done pro-actively from following places  in scan call back (scan confirm)*/
	/*1:Same AP found*/
	/*2:Found AP to roam, but need to confirm*/
	/*3:Found AP to roam, confirming that its not a false alarm*/
	/*4:Confirmed the ap to roam, go ahead and dis-associate*/
	/*5:Earlier found ap to roam didnt got confirmed, find a new one*/

	/*Only condition for not doing this is as follows*/
	/*1:No ap found, continue scan*/
	
	NcmCtx->roamingParams.roamScanRetryCount = 0;
	/*post message to restart the scan*/
	msg = GSN_NCM_CTX_MSG_ID_ROAM_STARTSCAN;
	GsnNcm_MsgPost(NcmCtx, msg);
}

#endif
