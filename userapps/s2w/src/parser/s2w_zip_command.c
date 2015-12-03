/*****************************************************************
 *
*               COPYRIGHT (c) 2013-2014 GainSpan Corporation
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
* $RCSfile: s2w_zip_command.c,v $
*
* Description : s2w ZigBee-IP command processor file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "hal/s2w_net.h"
#include "hal/s2w_timer.h"
#include "parser/s2w_parse.h"
#include "hal/s2w_config.h"
#include "parser/s2w_command.h"
#include "main/app_main_ctx.h"
#include "config/app_resource_config.h"
#include "config/app_ncm_config.h"
#include "app_events.h"
#include "hal/s2w_config.h"

#include "config/app_stat_config.h"
#include "app_rtc_mem.h"
#ifdef S2W_15DOT4_SUPPORT
/**
 ******************************************************************************
 * @file s2w_zip_command.c
 * @brief S2W Application ZigBee-IP command process routines.
 *      This file contains the s2w application specific implimentation for
 *      ZigBee-IP command processing.
******************************************************************************/
typedef struct S2W_ZIP
{
    GSN_OSAL_SEM_T blockingSem;
    GSN_ZIP_CTX_T  zipCtx;
    UINT32 opStatus;
}S2W_ZIP_T;

S2W_ZIP_T s2wZipCtx;

PUBLIC UINT8 AppS2wParse_ZipNWKId(UINT8 *p, GSN_ZIP_NWK_ID_T *pNWKId );
extern INT8 ipStack[APP_NWIF_IP_THREAD_STACK_SIZE];
extern  INT8 arpCache[APP_NWIF_IP_THREAD_ARP_CACHE_SIZE];
extern GSN_NWIF_STATS_T gsnNwifStats;
VOID App_ZipNwIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

static const UINT8 S2W_DEFAULT_154_MAC_ADDR[8] =
    {0x00, 0x1d, 0xc9, 0x00, 0x00, 0x00, 0x00, 0x00};


/*****************************************************************************
  *  Public Variables
  *****************************************************************************/
VOID AppMainCtx_ZipTaskNotify( VOID *pUsrCtx )
{
    AppMainCtx_TaskNotify( APP_ZIP_DELAY_PROCESS_EVENT );
}



const GSN_ZIP_CONST_CFG_T zipConstCfg = 
{
    .delayEventPost = AppMainCtx_ZipTaskNotify,
    .maxNbE = S2W_MAX_NUM_OF_NEIGHBOR_SUPPORTED,
    .maxParents = S2W_MAX_NUM_OF_PARENT_SUPPORTED,
    .maxRtE = S2W_MAX_NUM_OF_NODE_SUPPORTED   
};

VOID App_ZipCb( VOID* pAppCtx, UINT32 event, UINT8* pData, 
    UINT32 dataLen )
{
    APP_MAIN_CTX_T *pApp = pAppCtx;
    DBG_LOG(52);
    switch( event )
    {
    case GSN_ZIP_EVENT_SCAN_CFM:
        {
            GSN_ZIP_SCAN_INFO_T *pScanInfo = ( GSN_ZIP_SCAN_INFO_T* )pData;
            UINT32 numOfInfo = dataLen / sizeof( GSN_ZIP_SCAN_INFO_T );
            S2w_Printf("\r\nNumber of Scan Result = %d", numOfInfo );
            if( numOfInfo > 0 )
            {
                UINT8 i;
                S2w_Printf("\r\nChannel\tControl Field\tNetwork Id");
                for( i = 0; i < numOfInfo; i++ )
                {
                    /**< Terminate with NULL character to print it as string */
                    pScanInfo[i].nwkId.networkId[pScanInfo[i].nwkId.networkIdLen + 1 ] = '\0';
                    S2w_Printf("\r\n%d\t%d\t%s", pScanInfo[i].channel, pScanInfo[i].ctrlFld,
                        pScanInfo[i].nwkId.networkId );
                }
            }
        }                
        break;
    case GSN_ZIP_EVENT_START_CFM:
        s2wZipCtx.opStatus = *(( UINT32*)pData );
        if( GSN_SUCCESS == s2wZipCtx.opStatus )
        {
            INT8 ipv6str[INET6_ADDRSTRLEN];
            GSN_NWIF_IP_CONFIG_T nwParams;
     
            GsnNwIf_IpConfigGet(&pApp->if0.nwifCtx,&nwParams);

            S2w_ntop(nwParams.ipv6.linkLocalAddr,ipv6str);
            S2w_Printf("\r\nIPv6-Linklocal=%s\r\n",ipv6str );
            S2w_ntop(nwParams.ipv6.globalAddr,ipv6str );
            S2w_Printf("\nIPv6-Global=%s\r\n",ipv6str );
                   
        }
        break;
    case GSN_ZIP_EVENT_MAC_ADDR_SET_CFM:
        break;    
    case GSN_ZIP_EVENT_MAC_ADDR_GET_CFM:
        S2w_Printf("\r\n%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
            pData[0], pData[1], pData[2], pData[3],
            pData[4], pData[5], pData[6], pData[7] );
                
        break;          
    }
    
    GsnOsal_SemRelease( &s2wZipCtx.blockingSem );
}

VOID App_ZipInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
    GSN_ZIP_CFG_T zipCfg;
    zipCfg.pNwCtx = &pAppCtx->nwCtx;
    zipCfg.pDelayEventPostCtx = pAppCtx;
    zipCfg.pDot154ifCtx = &pAppCtx->dot154ifCtx;
    zipCfg.pWlrpanCtx = &pAppCtx->wlrpanCtx;
    zipCfg.pNwIf = &pAppCtx->if0.nwifCtx;
    zipCfg.macIfNum = pIfInfo->macIfNum;
    zipCfg.pHiCtx = &pAppCtx->hiCtx;
    zipCfg.cb = App_ZipCb;
    zipCfg.pAppCtx = pAppCtx;

    DBG_LOG(53);

    if(otpMac_Read(( UINT8* )zipCfg.macAdd, GSN_OTP_MM_ID_MAC_ID2 ) != S2W_SUCCESS )
    {
        memcpy(( UINT8* )zipCfg.macAdd, S2W_DEFAULT_154_MAC_ADDR, 
            sizeof(zipCfg.macAdd));
    }

    /**< Initialize the semaphore */
    GsnOsal_SemCreate( &s2wZipCtx.blockingSem, 0 ); 

    GsnZIP_Init( &s2wZipCtx.zipCtx, &zipConstCfg, &zipCfg );
	App_ZipNwIfInit( pAppCtx, pIfInfo );

}

VOID App_ZipDelayHandler( VOID )
{
    DBG_LOG(54);
    GsnZIP_DelayHandler( &s2wZipCtx.zipCtx );
}
UINT8 AppS2wCmd_ZipScan( UINT8 *ptr )
{
    UINT32 channelMask, scanDuration;
    UINT8 status;
    GSN_ZIP_SCAN_INFO_T *pScanBuf;
    UINT8 *p;
    DBG_LOG(55);
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &channelMask);
    if ( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }    
    p = AppS2wParse_NextParamGet(&ptr);
	if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &scanDuration );
    if ( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    } 
    pScanBuf = malloc( sizeof(GSN_ZIP_SCAN_INFO_T) * 10);
    if( pScanBuf == NULL )return S2W_EINVAL;
    GsnZIP_Scan( &s2wZipCtx.zipCtx, channelMask, scanDuration, pScanBuf, 10 );

    /**< Take lock */
    GsnOsal_SemAcquire( &s2wZipCtx.blockingSem, GSN_OSAL_WAIT_FOREVER );

    free( pScanBuf );
}

UINT8 AppS2wCmd_ZipStart( UINT8 *ptr )
{
    UINT32 channelMask, mode;
    UINT8 status;
    GSN_ZIP_NWK_ID_T NWKId;
    UINT8 *p;
    DBG_LOG(56);
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &mode);
    if ( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }    
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &channelMask);
    if ( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }    
	p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_ZipNWKId(p, &NWKId);
    if ( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }    
    GsnZIP_Start( &s2wZipCtx.zipCtx, mode, channelMask, &NWKId );

    /**< Take lock */
    GsnOsal_SemAcquire( &s2wZipCtx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    if( s2wZipCtx.opStatus == 0 )
        return S2W_SUCCESS;
    else 
        return S2W_FAILURE;
}


UINT8 AppS2wCmd_ZipStop( UINT8 *ptr )
{
    DBG_LOG(57);
    GsnZIP_Stop( &s2wZipCtx.zipCtx );
    /**< Take lock */
    return S2W_SUCCESS;
}

UINT8 AppS2wCmd_ZipSetMacAddr( UINT8 *ptr )
{

    UINT32 macAddr[2];
    UINT8 status;

    if (ptr[0] == '?' && ptr[1] == '\0')
    {
        /* get the mac address and send it on serial interface
        */
        GsnZIP_GetExtMacAddr( &s2wZipCtx.zipCtx );
        
        /**< Take lock */
        GsnOsal_SemAcquire( &s2wZipCtx.blockingSem, GSN_OSAL_WAIT_FOREVER );

        return S2W_SUCCESS;
    }

    /* check the mac address passed is valid
    */
    status = AppS2wParse_Mac64(ptr, (UINT8*)macAddr);
    if (status != S2W_SUCCESS)
    {
      return status;
    }

    macAddr[0] = macAddr[0];
    macAddr[1] = macAddr[1];
    /* Call the hal function to configure the mac address
    */    
    GsnZIP_SetExtMacAddr( &s2wZipCtx.zipCtx, (UINT8*)macAddr );
            
    /**< Take lock */
    GsnOsal_SemAcquire( &s2wZipCtx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wParse_ZipNWKId(UINT8 *p, GSN_ZIP_NWK_ID_T *pNWKId )
{
    UINT8 *ssid = pNWKId->networkId, *lenp = &pNWKId->networkIdLen;
    UINT8 len = 0;
    DBG_LOG(58);
    memset(ssid, 0, 17);

    while (*p)
    {
        if (*p == '\\' && *(p + 1) == '"')
        {
            *ssid = '"';
            p++;
        }
        else
        {
            *ssid = *p;
        }

        p++;
        len++;
        ssid++;

        if (len >= 16)
        {
            break;
        }
    }
    *lenp = len;
    if (*p)
    {
        return S2W_EINVAL;
    }

    if (len == 0)
    {
        return S2W_EINVAL;
    }

    return S2W_SUCCESS;
}


VOID App_ZipNwIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
    GSN_NWIF_INIT_PARAMS_T param;
    /*Big time initialization :( */
    DBG_LOG(59);
    param.flags = (GSN_NWIF_FLAGS_T)( GSN_NWIF_FLG_RPL_ENABLE | GSN_NWIF_FLG_ARP_ENABLE |	
        GSN_NWIF_FLG_DHCP_CLIENT_ENABLE | GSN_NWIF_FLG_DNS_CLIENT_ENABLE | 
        GSN_NWIF_FLG_ICMP_ENABLE | GSN_NWIF_FLG_IGMP_ENABLE );
    param.nwIfName = "zip";
    param.pNwCtx = &pAppCtx->nwCtx;
    param.pL2Dev = &s2wZipCtx.zipCtx.lowpanCtx.l2Dev;

    /*[TO DO]*/ 			/**< Power management object for power save */
    param.mtu = 1280;
    param.ipRecvFilter = NULL;
    param.ipTskStackSize = APP_NWIF_IP_THREAD_STACK_SIZE;
    param.ipTskStack = &ipStack[0];
    param.ipTskPrio = APP_NWIF_IP_THREAD_PRIORITY;
    param.ipTskSysQualID = 20;
    param.ipTskSysQualTicks = 0;//APP_CFG_SQ_TICKS_FOR_IP_TASK;
    /* Using pre created packet pool. A new paket pool can be created using
    GsnNw_PktPoolCreate() and its handle can be given*/
    param.pIpPktPoolHndl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_SBUF_PKT_POOL);


    param.arpCacheSize = APP_NWIF_IP_THREAD_ARP_CACHE_SIZE;
    param.arpCache = &arpCache[0];
    param.pStats = &gsnNwifStats;

    param.pIpHndl = GsnNwif_IpInstanceHndlGet();
    
    GsnNwIf_Init(&pIfInfo->nwifCtx, &param);

    GsnNwif_IPv6Init(&pIfInfo->nwifCtx, NULL);

    /* register the s2w filter */
    GsnNwIf_RecvFilterRegister( &pIfInfo->nwifCtx, NULL );

}



#endif
