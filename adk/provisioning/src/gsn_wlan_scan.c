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
* $RCSfile: gsn_prov_scan.c,v
*
*  Description : GEPS scan helper
*/

/*
 * gsn_prov_scan.c
 *
 *  Created on: Jun 3, 2011
 *      Author: PViswanathan
 */

#include "gsn_includes.h"
#include "gsn_wlan_scan.h"
#include "modules/http/gsn_httpd_debug.h"
#include "gsn_wlan_scan_fpt.h"


#define GSN_HTTPD_MAX_SCAN_ELEMENTS 10

GSN_OSAL_SEM_T wlanScanSem;
__no_init GSN_WDD_SCAN_ENTRY_T scanUserEntryBuff[2];

/* static memory for each scan entry during scan */
// /GSN_SCAN_ENTRY_T* nwAppScanEntry;

 PRIVATE GSN_WDD_CTX_T* pWddCtx;

 UINT32 scanElemIndex=0;


PUBLIC VOID
GsnWlanScan_Init(GSN_WDD_CTX_T* pWdd)
{
	if(GsnWlanScan_Init_FP)
	{
		GsnWlanScan_Init_FP(pWdd);
        return;
	}
	GSN_STATUS status;
    status = GsnOsal_SemCreate  ( &wlanScanSem, 0 );
    HTTPD_DEBUG_PRINT(("GsnOsal_SemCreate return = %d\r\n",status));
    pWddCtx = pWdd;
}

PUBLIC VOID
GsnWlanScan_DeInit()
{
	if(GsnWlanScan_DeInit_FP)
	{
		GsnWlanScan_DeInit_FP();
        return;
	}
      	GsnOsal_SemDelete( &wlanScanSem );
}



PRIVATE VOID
GsnWlanScan_SecurityTypeSet(UINT16 capabilityInfo,UINT8 encryptionType,UINT8 authType,
                     GSN_WLAN_SECURITY_TYPE_T *securityType)
{
	if(GsnWlanScan_SecurityTypeSet_FP)
	{
		GsnWlanScan_SecurityTypeSet_FP(capabilityInfo,encryptionType,authType,securityType);
        return;
	}
    if(capabilityInfo & GSN_MAC_CAPA_PRIVA)
    {
        if (encryptionType & GSN_MAC_ENC_WPA2)
        {
            if (GSN_MAC_RSNIE_KEYMGT_PSK  == authType)
            {
                *securityType = GSN_WLAN_WPA_PERSONAL;
            }
            else if (authType == GSN_MAC_RSNIE_KEYMGT_8021X)
            {
                *securityType = GSN_WLAN_WPA_ENTERPRISE;
            }
        }
        else if (encryptionType & GSN_MAC_ENC_WPA)
        {
            if (GSN_MAC_RSNIE_KEYMGT_PSK  == authType)
            {
                *securityType = GSN_WLAN_WPA_PERSONAL;
            }
            else if (authType == GSN_MAC_RSNIE_KEYMGT_8021X)
            {
                *securityType = GSN_WLAN_WPA_ENTERPRISE;
            }
        }
        else
        {
            /* Open with WEP cannot be identified from capabilities */
            *securityType = GSN_WLAN_WEP;
        }
    }
    else
        *securityType = GSN_WLAN_SECURITY_NONE;
}

#ifdef GS1500M
PUBLIC UINT8 
GsnWlanScan_PhyModeGet(VOID)
{
   UINT8 phyMode;
   GsnWdd_PhyModeGet(pWddCtx,&phyMode);
   return phyMode;
}
#endif /* GS1500M */


PUBLIC VOID
GsnWlanScan_ChannelFill(UINT8 *chTable,UINT8 domain,UINT8 phyMode)
{
	if(GsnWlanScan_ChannelFill_FP)
	{
		GsnWlanScan_ChannelFill_FP(chTable,domain,phyMode);
        return;
	}
UINT8 Index=0;

if(!phyMode)
{
    #ifdef GS1500M
          GsnWdd_PhyModeGet(pWddCtx,&phyMode); /* Get the current phy mode  */
    #endif
}

   /* fill the channels
  */
   for(Index=0;Index<=12;Index++)
   {
       chTable[Index] = Index+1;
   }

   if(domain == GSN_WLAN_REG_DOMAIN_FCC)
  {/* 1 to 11 are valid */
      Index=11;
   }
   else if((domain == GSN_WLAN_REG_DOMAIN_ETSI) || (domain == GSN_WLAN_REG_DOMAIN_ETSI_MEXS))
   {/* 1 to 13 are valid */
       Index=13;
   }

   for(;Index<=14;Index++)
   {
       chTable[Index] = 0;  /* Mask channels depending on REG domain and last entry must be ZERO */
   }


}


PUBLIC VOID
GsnWlanScan_Notification( VOID* pScanResult,INT32 status, INT8 *rsltBuff,
   	                     UINT32 rsltCount )
{
	if(GsnWlanScan_Notification_FP)
	{
		GsnWlanScan_Notification_FP(pScanResult,status,rsltBuff,rsltCount);
        return;
	}
	/* copy the data to user buffer and return
	 */
    UINT8 encryptionType,i=0,authType;
    UINT16 CapabilityInfo;
    GSN_WLAN_SCAN_RESULT_T * scanResult = (GSN_WLAN_SCAN_RESULT_T*)pScanResult;
    HTTPD_DEBUG_PRINT(("GsnWlanScan_Notification +\r\n"));

    for(i=0;i<rsltCount;i++)
    {
    	GSN_WDD_SCAN_ENTRY_T* scanEntryBuff = (GSN_WDD_SCAN_ENTRY_T*)(rsltBuff + (i*sizeof(GSN_WDD_SCAN_ENTRY_T))) ;
    	HTTPD_DEBUG_PRINT(("GsnProvScan_Notification rsltCount for channel[%d] = %d ",scanEntryBuff->channel,rsltCount));
		if(scanEntryBuff->channel > 0)
		{
			if(scanElemIndex < GSN_HTTPD_MAX_SCAN_ELEMENTS) // copy max 10 entries for each channel
			{
				scanResult[scanElemIndex].channel= scanEntryBuff->channel;
				scanResult[scanElemIndex].rssi = scanEntryBuff->rssi;
				memcpy(&scanResult[scanElemIndex].ssid,&scanEntryBuff->ssid,sizeof(GSN_WLAN_MAC_SSID_T));
				encryptionType = GsnMacUtil_ExtractEncryptionStatus((GSN_MAC_FRAME_T*)scanEntryBuff->frame,
						scanEntryBuff->frameLen,GSN_MAC_BEACON_SSID_OFT,&authType);
				CapabilityInfo = GsnMacUtil_ExtractCapaInfo((GSN_MAC_FRAME_T*)scanEntryBuff->frame);
				GsnWlanScan_SecurityTypeSet(CapabilityInfo,encryptionType,
															authType,
															&scanResult[scanElemIndex].securityType);
				scanElemIndex++;
			}
		}
    }
    // if the scan finished release the scan wait semaphore
    if(status == GSN_WDD_SCAN_COMPLETE)
    {

    	GsnOsal_SemRelease ( &wlanScanSem );

	}
}

PUBLIC GSN_STATUS
GsnWlanScan_ProvWscan( GSN_WLAN_SCAN_PARAM_T *sParams,GSN_WLAN_SCAN_RESULT_T *pScanResult, INT32 *maxScanElements)
{
	if(GsnWlanScan_ProvWscan_FP)
	{
		return GsnWlanScan_ProvWscan_FP(sParams,pScanResult,maxScanElements);
	}
    UINT32 status = GSN_SUCCESS;
    GSN_WDD_SCAN_PARAMS_T scanParams;

    /* start the scan
     */


    memset(&scanParams,0,sizeof(GSN_WDD_SCAN_PARAMS_T));
    scanParams.scanType = GSN_MAC_SCAN_TYPE_ACTIVE;
    scanParams.channel[1] = 0;

    HTTPD_DEBUG_PRINT(("\r\n       BSSID              SSID                     Channel  Type  RSSI Security\r\n"));

	scanParams.channel[0] = sParams->channel;
	HTTPD_DEBUG_PRINT(("scanning channel %d\r\n",scanParams.channel[0]));

	scanElemIndex = 0;
	status = GsnWdd_Scan(pWddCtx,&scanParams,(INT8 *)scanUserEntryBuff,
					 (2 * sizeof(GSN_WDD_SCAN_ENTRY_T)),(GSN_WDD_SCAN_NOTIF_CB_T)GsnWlanScan_Notification,pScanResult);
	if(status == GSN_OPERATION_IN_PROGRESS)
	{
		// wait on a semaphore to finish the scan
		HTTPD_DEBUG_PRINT(("waiting on semaphore until scan completes\r\n"));
		GsnOsal_SemAcquire ( &wlanScanSem, GSN_OSAL_WAIT_FOREVER );
		HTTPD_DEBUG_PRINT(("semaphore released after scan complete\r\n"));

	}

	// break the loop if scan for only one channel or finished
	/*if(((scanParams.channel[0] == 11) && (s2wCurrent.regDomain == 0))
		   ||((scanParams.channel[0] == (11+2)) && (s2wCurrent.regDomain == S2W_DOMAIN_ETSI)) ||
		     ((scanParams.channel[0] == (11+3)) && (s2wCurrent.regDomain == S2W_DOMAIN_TELEC)))
		{
				break;
		}
*/

    HTTPD_DEBUG_PRINT(("\r\nNo.Of Acess points Found:%d\r\n",scanElemIndex));

    status = GSN_SUCCESS;
    *maxScanElements = scanElemIndex;
    return status;
}


#ifdef GS1500M
PUBLIC BOOL
GsnWlanScan_IsItApMode(void)
{//Returns TRUE if wlan mode is set configured to AP mode else FALSE.
   return  (( 2 == pWddCtx->wMode)? (TRUE):(FALSE));
   
}
#endif //GS1500M

