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
* $RCSfile: s2w_154_command.c,v $
*
* Description : s2w 802.15.4 command processor file
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
#include "app_defines_builder.h"
#include "hal/s2w_config.h"
#include "parser/s2w_command.h"
#include "main/app_main_ctx.h"
#include "config/app_resource_config.h"
#include "config/app_ncm_config.h"
#include "app_events.h"
#include "hal/s2w_config.h"

#include "config/app_stat_config.h"
#include "app_rtc_mem.h"

/**
 ******************************************************************************
 * @file s2w_154_command.c
 * @brief S2W Application 802.15.4 command process routines.
 *      This file contains the s2w application specific implimentation for
 *      802.15.4 command processing.
******************************************************************************/


/*****************************************************************************
  *  Public Variables
  *****************************************************************************/
#define S2W_154_ASSOC_STAT_FREE       0
#define S2W_154_ASSOC_STAT_NOT_ASSOC  1
#define S2W_154_ASSOC_STAT_ASSOC      2
#define S2W_154_ASSOC_STAT_DONT_ASSOC 3

#define S2W_154_MAX_ASSOC_LIST   8
#define GSN_WLP_MAX_SEC_ENTRIES 10

UINT8 semRelease = FALSE;      
      
typedef struct S2W_154_ASSOC_LIST
{
    UINT16 shortAddr;
    UINT8 extendedAddr[8];
    UINT8  status;
}S2W_154_ASSOC_LIST_T;
typedef struct S2W_154
{
    UINT8 devType;
    UINT8 assocState;
    UINT8 operationStatus;
    GSN_OSAL_SEM_T blockingSem;
    S2W_154_ASSOC_LIST_T assocChild[ S2W_154_MAX_ASSOC_LIST ];
    
    GSN_DOT154IF_CTX_T dot154ifCtx;
    GSN_WLRPAN_T wlrpanCtx;
    
    UINT8 CoordAddrMode;
    UINT16 CoordPANId;    
    GSN_WLRPAN_ADDR_T  CoordAddress;
}S2W_154_T;

GSN_STATUS 
AppS2w_WLRPANCb( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS
AppS2w_WLRPANAssocCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANAssocInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANDisassocCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANDisassocInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANBeaconNotifyInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANGTSInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANGTSCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANOrphanInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANResetCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANRxEnableCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANScanCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANCommStatusInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANSetCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg);
GSN_STATUS
AppS2w_WLRPANStartCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS
AppS2w_WLRPANSyncLossInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS
AppS2w_WLRPANPollCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS 
AppS2w_WLRPANGetCfg( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );


GSN_STATUS 
AppS2w_WLRPANDataCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS 
AppS2w_WLRPANDataInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS 
AppS2w_WLRPANDataPurgeCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS 
AppS2w_WLRPANData6LoWPANCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS 
AppS2w_WLRPANData6LoWPANInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );


GSN_STATUS 
AppS2w_WLRPANTmrCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS 
AppS2w_WLRPANTmrInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS
AppS2w_WLRPANGenCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );
GSN_STATUS
AppS2w_WLRPANGenInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );


/** Current state of the serial handler
 */
const GSN_WLRPAN_APP_CB_T wlrpanMgmtCbTbl[] = 
{
    AppS2w_WLRPANAssocCfm, //assocCfm;
    AppS2w_WLRPANAssocInd,//assocInd;
    AppS2w_WLRPANDisassocCfm,//disassocCfm;
    AppS2w_WLRPANDisassocInd,//disassocInd;
    AppS2w_WLRPANBeaconNotifyInd,//beaconNotifInd;
    AppS2w_WLRPANGetCfg,//getCfm;
    AppS2w_WLRPANGTSCfm,//gtsCfm;
    AppS2w_WLRPANGTSInd,//gtsInd; 
    AppS2w_WLRPANOrphanInd,//orphanInd;
    AppS2w_WLRPANResetCfm,//resetCfm;
    AppS2w_WLRPANRxEnableCfm,//rxEnableCfm;
    AppS2w_WLRPANScanCfm,//scanCfm;
    AppS2w_WLRPANCommStatusInd,//commStatusInd;
    AppS2w_WLRPANSetCfm,//setCfm;
    AppS2w_WLRPANStartCfm,//startCfm; 
    AppS2w_WLRPANSyncLossInd,//syncLossInd;
    AppS2w_WLRPANPollCfm,//pollCfm   
    AppS2w_WLRPANTmrCfm,//tmrCfm
    AppS2w_WLRPANTmrInd,//tmrInd
    AppS2w_WLRPANGenCfm,//generic cfm
    AppS2w_WLRPANGenInd//generic ind
};
const GSN_WLRPAN_APP_CB_T wlrpanDataCbTbl[] = 
{
    AppS2w_WLRPANDataCfm,//dataCfm;
    AppS2w_WLRPANDataInd,//dataInd;
    AppS2w_WLRPANDataPurgeCfm,//dataPurgeCfm;
    AppS2w_WLRPANData6LoWPANCfm,//data6LoWPANCfm;
    AppS2w_WLRPANData6LoWPANInd//data6LoWPANInd
};

S2W_154_T s2w154Ctx;

/**
********************************************************************************
*  Private functions
*******************************************************************************/
#if 0
GSN_STATUS AppS2w_WLRPANInit( GSN_HI_CTX_T *pHiCtx, UINT8 ifNum )
{
    GSN_WIF_INIT_PARAM_T wifInitParam;
    GSN_SYS_CTL_IF_START_REQ_T ifcStartReq;
    /**< Memset all the field including the child list */
    memset( &s2w154Ctx, 0, sizeof( s2w154Ctx ));
    
    /**< Initialize the semaphore */
    GsnOsal_SemCreate( &s2w154Ctx.blockingSem, 0 ); 
    
    /*Initialise wif module*/
    wifInitParam.macIfNum = ifNum;
    wifInitParam.macIfType = GSN_WIF_WLAN_NW_TYPE_15_4;
    wifInitParam.pHiCtx = pHiCtx;
    
    /*Register for interface init*/
    GsnWif_Init( &s2w154Ctx.wifCtx, &wifInitParam);
    
    /**< Initialize the WIF callabcks */
    GsnWLRPAN_Init( &s2w154Ctx.wlrpanCtx, &s2w154Ctx.wifCtx, 
        ( GSN_WLRPAN_MGMT_CB_TABLE_T * )wlrpanMgmtCb, &s2w154Ctx, 
        ( GSN_WLRPAN_DATA_CB_TABLE_T * )wlrpanDataCb, &s2w154Ctx );

    

    ifcStartReq.macIfNum = ifNum;
    ifcStartReq.macIfType = GSN_WIF_WLAN_NW_TYPE_15_4;
    ifcStartReq.dTxRdyQFrameTO = 0;
VOID App_CreateLock(VOID);
    App_CreateLock();
VOID App_InterfaceStartCb(VOID* ctx, GSN_STATUS status);    
    GsnSysCtl_IfStartReq(&appCtx.sysCtlCtx, &ifcStartReq, App_InterfaceStartCb, NULL);
VOID App_WaitOnLock(VOID);
    App_WaitOnLock();
        
    return GSN_SUCCESS;
}
#else

VOID 
App_WLRPANinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_DOT154_INIT_PARAM_T dot54IfInitParam;
	/* Initialise 15.4 interface*/
	dot54IfInitParam.macIfNum = pIfInfo->macIfNum;
	dot54IfInitParam.pHiCtx = &pAppCtx->hiCtx;
	GsnDot154if_Init(&s2w154Ctx.dot154ifCtx, &dot54IfInitParam);
	/* Initialise WLRPAN Driver*/
	GsnWLRPAN_Init(&s2w154Ctx.wlrpanCtx,&s2w154Ctx.dot154ifCtx,
		( GSN_WLRPAN_MGMT_CB_TABLE_T * )&wlrpanMgmtCbTbl[0], NULL, 
		( GSN_WLRPAN_DATA_CB_TABLE_T * )&wlrpanDataCbTbl[0], NULL);
}
#endif

UINT8
AppS2wCmd_154Channel(UINT8 *ptr)
{
    /**< PCH    Operating channel   0x0C - 0x17 Get 
    Hex 8 bit value, witihout 0x
    */
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        if( S2W_154_ASSOC_STAT_ASSOC != s2w154Ctx.assocState )
        {
            return S2W_EINVAL;
        }
        else
        {
            GSN_WLRPAN_GET_REQ_T getReq;
            GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;
        }
    }
    return S2W_EINVAL;
}

UINT8
AppS2wCmd_154PanId(UINT8 *ptr)
{
    /**< PAN ID 0 - 0xFFFF  Get 
    Hex 16 bit value, witihout 0x
    */
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        if( S2W_154_ASSOC_STAT_ASSOC != s2w154Ctx.assocState )
        {
            return S2W_EINVAL;
        }
        else
        {
            GSN_WLRPAN_GET_REQ_T getReq;
            getReq.Attribute = macPANId;
            
            GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;
        }
    }
    return S2W_EINVAL;
}

UINT8
AppS2wCmd_154ShortAddr(UINT8 *ptr)
{
    /**< My short address.  0 - 0xFFFF  Get 
    Hex 16 bit value, witihout 0x
    */
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        if( S2W_154_ASSOC_STAT_ASSOC != s2w154Ctx.assocState )
        {
            return S2W_EINVAL;
        }
        else
        {
            GSN_WLRPAN_GET_REQ_T getReq;
            getReq.Attribute = macShortAddress;
            GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;
        }
    }
    return S2W_EINVAL;
}

PUBLIC UINT8
AppS2wParse_Mac64(UINT8 *s, UINT8 *mac_addr)
{
    UINT32 i, val;
    UINT8 dummy[8]={0x00,0x00,0x00,0x00,0x00,0x00, 0x00, 0x00}; // 0 mac
    UINT8 dummy1[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; // broadcast mac
    memset(mac_addr, 0, 8);

    for (i = 0; *s != '\0' && i < 9; i++, s++)
    {
        int digits = 0;

        val = 0;
        while (*s != '-' && *s != '\0' && *s != ' ')
        {
            if(!isxdigit(*s))
            {
                return S2W_EINVAL;
            }

            val = val * 16 + AppS2wParse_ToHex(*s);
            s++;
            digits++;
        }

        if((!digits) || (digits > 2))
        {
            return S2W_EINVAL;
        }

        if(i<8)
        {
            mac_addr[i] = val;
        }
        if(*s == '\0')
        {
            i++;
            break;
        }
    }
    if((memcmp(mac_addr,dummy,8)== 0) || (memcmp(mac_addr,dummy1,8) == 0))
    {
        return S2W_EINVAL;
    }
    return i == 8 ? S2W_SUCCESS : S2W_EINVAL;
}
PUBLIC UINT8
AppS2wParse_LookupData( UINT8 *s, UINT8 *data, UINT8 length)
{
    UINT32 i, val;
    UINT8 dummy[9]={0x00,0x00,0x00,0x00,0x00,0x00, 0x00, 0x00, 0x00}; // 0 mac
    UINT8 dummy1[9]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF}; // broadcast mac
    memset(data, 0, 9);

    for (i = 0; *s != '\0' && i < length; i++, s++)
    {
        int digits = 0;

        val = 0;
        while (*s != '-' && *s != '\0' && *s != ' ')
        {
            if(!isxdigit(*s))
            {
                return S2W_EINVAL;
            }

            val = val * 16 + AppS2wParse_ToHex(*s);
            s++;
            digits++;
        }

        if((!digits) || (digits > 2))
        {
            return S2W_EINVAL;
        }

        if(i<length)
        {
            data[i] = val;
        }
        if(*s == '\0')
        {
            i++;
            break;
        }
    }
    if((memcmp(data,dummy,length)== 0) || 
		(memcmp(data,dummy1,length) == 0))
    {
        return S2W_EINVAL;
    }
    return i == length ? S2W_SUCCESS : S2W_EINVAL;
}
PUBLIC UINT8
AppS2wParse_Key( UINT8 *s, UINT8 *data )
{
    UINT32 i, val;
 
    memset( data, 0, 16 );

    for (i = 0; *s != '\0' && i < 16; i++, s++)
    {
        int digits = 0;

        val = 0;
        while (*s != '-' && *s != '\0' && *s != ' ')
        {
            if(!isxdigit(*s))
            {
                return S2W_EINVAL;
            }

            val = val * 16 + AppS2wParse_ToHex(*s);
            s++;
            digits++;
        }

        if((!digits) || (digits > 2))
        {
            return S2W_EINVAL;
        }

        if(i<16)
        {
            data[i] = val;
        }
        if(*s == '\0')
        {
            i++;
            break;
        }
    }

    return ((i == 16) ? S2W_SUCCESS : S2W_EINVAL);
}

PUBLIC UINT8
AppS2wParse_SecI( UINT8 *ptr, GSN_WLRPAN_SEC_I_T *pSecI )
{
	UINT32 param;
	UINT8 status;
	UINT8 *p = AppS2wParse_NextParamGet(&ptr);
	if(!p)      return S2W_EINVAL;

	status = AppS2wParse_Hex(p, &param);
	if( ( S2W_SUCCESS != status )||( param > 7 ) ) 
		return S2W_EINVAL;
	pSecI->SecILevel = ( UINT8 )param;
	if( pSecI->SecILevel == 0 )
	{
		return S2W_SUCCESS;
	}
	
	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)      return S2W_EINVAL;
	status = AppS2wParse_Hex(p, &param);
	if( ( S2W_SUCCESS != status )||( param > 3 ) ) 
		return S2W_EINVAL;
	pSecI->KeyIdMode = ( UINT8 )param;

	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)		return S2W_EINVAL;
	status = AppS2wParse_Hex(p, &param);
	if( ( S2W_SUCCESS != status )||( param == 0 ) ) 
		return S2W_EINVAL;
	pSecI->KeyIndex = ( UINT8 )param;

	param = 0;
	
	if( pSecI->KeyIdMode == 2 )
	{
		param = 4;
	}
	else if( pSecI->KeyIdMode == 3 )
	{
		param = 8;
	}

	if( param )
	{
		p = AppS2wParse_NextParamGet(&ptr);
		if(!p)      return S2W_EINVAL;

		if( S2W_SUCCESS != 	
				AppS2wParse_LookupData( p, pSecI->KeySource, param )) 
			return S2W_EINVAL;
	}
	return S2W_SUCCESS;
}
UINT8
AppS2wCmd_154ExtendedAddr(UINT8 *ptr)
{
    /**< My long address        Get/Set 
    aa-bb-cc-dd-ee-ff-gg-hh
    */    
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        GSN_WLRPAN_GET_REQ_T getReq;
        getReq.Attribute = macCoordExtendedAddress; //should be my extended address
        GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        return s2w154Ctx.operationStatus;
    }
    else
    {
        GSN_WLRPAN_SET_REQ_T setReq;
        if( S2W_SUCCESS != AppS2wParse_Mac64( ptr, setReq.Value )) 
            return S2W_EINVAL;
        setReq.Attribute = macCoordExtendedAddress;
        setReq.AttributeIdx = 0;
        
        GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        return s2w154Ctx.operationStatus;  

    }    
}

UINT8
AppS2wCmd_154RetryCount(UINT8 *ptr)
{
    /**< MAC retry  0-6 Get/Set 
    Hex 8 bit value, witihout 0x
    */
    UINT32 param, maxparam = 7 ;
    
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        GSN_WLRPAN_GET_REQ_T getReq;
        getReq.Attribute = macMaxFrameRetries;
        GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        return s2w154Ctx.operationStatus;
    }
    else
    {
        UINT8 *p = AppS2wParse_NextParamGet(&ptr);
        if( p != NULL )
        {
            GSN_WLRPAN_SET_REQ_T setReq;
            if( S2W_SUCCESS != AppS2wParse_Hex(p, &param)) return S2W_EINVAL;
            
            if(param >maxparam)
                return S2W_EINVAL;
            setReq.Attribute = macMaxFrameRetries;
            setReq.AttributeIdx = 0;
            setReq.Value[ 0 ] = ( UINT8 )param;
            GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;        
        }
    }
    return S2W_EINVAL;
}

UINT8
AppS2wCmd_154JoinPermit(UINT8 *ptr)
{
    /**< Join permit, Allow node to join. If a node gives a join request to a 
    coordinator where PAN command for a joining node is not given and PJP is 
    set to TRUE, the MAC will allow the node to join with extended address. 
    0-1 
    Get/Set
    */
    UINT32 param;
    
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        GSN_WLRPAN_GET_REQ_T getReq;
        getReq.Attribute = macAssociationPermit;
        GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        return s2w154Ctx.operationStatus;
    }
    else
    {
        UINT8 *p = AppS2wParse_NextParamGet(&ptr);
        if( p != NULL )
        {
            GSN_WLRPAN_SET_REQ_T setReq;
            if( S2W_SUCCESS != AppS2wParse_Hex(p, &param) ) return S2W_EINVAL;
            if( param > 1 ) return S2W_EINVAL;
            setReq.Attribute = macAssociationPermit;
            setReq.AttributeIdx = 0;
            setReq.Value[ 0 ] = ( UINT8 )param;
            GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;        
        }
    }
    return S2W_EINVAL;
}

UINT8
AppS2wCmd_154SupreFrmCfg(UINT8 *ptr)
{
    /**< Super frame configuration. Gives value of BO and SO    Get
    */
        
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        GSN_WLRPAN_GET_REQ_T getReq;
        getReq.Attribute = macSuperframeOrder;
        GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        getReq.Attribute = macBeaconOrder;
        GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        return s2w154Ctx.operationStatus;
    }
#if 0
    else
    {
        GSN_WLRPAN_SET_REQ_T setReq;
        UINT8 *p = AppS2wParse_NextParamGet(&ptr);
        if( p != NULL && ( p[0] != '\0') )
        {           
            if( S2W_SUCCESS != AppS2wParse_Hex(p, &param1))return S2W_EINVAL;
            s = TRUE;
            p = AppS2wParse_NextParamGet(&ptr);
            if( p != NULL && ( p[0] != '\0'))
            {
                if( S2W_SUCCESS != AppS2wParse_Hex(p, &param2) ) 
                    return S2W_EINVAL;
                b = TRUE;
            }
        }
        else 
        {
            p = AppS2wParse_NextParamGet(&ptr);
            if( p != NULL && ( p[0] != '\0'))
            {
                if( S2W_SUCCESS != AppS2wParse_Hex(p, &param2) ) 
                    return S2W_EINVAL;
                b = TRUE;
            }
            else
                return S2W_EINVAL;
        }
        if( s )
        {
            setReq.Attribute = macSuperframeOrder;
            setReq.AttributeIdx = 0;
            setReq.Value[ 0 ] = ( UINT8 )param1;
            GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq );
        }
        if( b )
        {
            setReq.Attribute = macBeaconOrder;
            setReq.AttributeIdx = 0;
            setReq.Value[ 0 ] = ( UINT8 )param2;
            GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq );
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );             
        }
        return s2w154Ctx.operationStatus; 
    }
#endif
    return S2W_EINVAL;    
}

UINT8
AppS2wCmd_154CoordExtndedAddr(UINT8 *ptr)
{
    /**< Coordinator Extended address       Get
    */
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        if( S2W_154_ASSOC_STAT_ASSOC != s2w154Ctx.assocState )
        {
            return S2W_EINVAL;
        }
        else
        {
            GSN_WLRPAN_GET_REQ_T getReq;
            getReq.Attribute = macCoordExtendedAddress; 
            GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;
        }
    }
#if 0
    else
    {
        GSN_WLRPAN_SET_REQ_T setReq;
        if( S2W_SUCCESS != AppS2wParse_Mac64( ptr, setReq.Value )) 
            return S2W_EINVAL;
        setReq.Attribute = macCoordExtendedAddress;
        setReq.AttributeIdx = 0;
        
        GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq ); 
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
        return s2w154Ctx.operationStatus;  

    }
#endif
        return S2W_EINVAL;  
}

UINT8
AppS2wCmd_154CoordShortAddr(UINT8 *ptr)
{
    /**< Coordinator Short address      Get
    */
    if(ptr[0] == '?' && ( ptr[1] == '\0'))
    {
        if( S2W_154_ASSOC_STAT_ASSOC != s2w154Ctx.assocState )
        {
            return S2W_EINVAL;
        }
        else
        {
            GSN_WLRPAN_GET_REQ_T getReq;
            getReq.Attribute = macCoordShortAddress;
            GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq ); 
            GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
            return s2w154Ctx.operationStatus;
        }
    }
    return S2W_EINVAL;
}

UINT8
AppS2wCmd_154ScanNetwork(UINT8 *ptr)
{
    /**< Scan Network: User can scan all channel at once, by giving 0x0. 
    Scan duration is calculated using as per the specification. Scan type has 
    value
    0x00 = ED scan (optional for RFD).
    0x01 = active scan (optional for RFD).
    0x02 = passive scan.
    0x03 = orphan scan.
    
    Scan channel    0x0, 0x0C - 0x17    
    scan type       0-3 
    scan duration   0-0xE   
    
    Set
    
    */
    GSN_WLRPAN_SCAN_REQ_T scanReq = {0};
    UINT32 param;
    UINT8 status;
    UINT8 *p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS || param > 0x3 )
    {
        return S2W_EINVAL;
    }    
    scanReq.ScanType = param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if(( status != S2W_SUCCESS ) || 
            (( param != 0 ) && (( param < 0xc ) || ( param > 0x17 ))))
        {
            return S2W_EINVAL;
        }
        
        
        scanReq.ScanChannels = ( param == 0 ) ? 0x1FFF000 : ( 1 << param ); 
    }
    else
    {
        scanReq.ScanChannels = 0x1FFF000; //All the channel
        scanReq.ScanDuration = 0xE;
    }
    p = AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if(( status != S2W_SUCCESS ) || ( param > 0xE ))
        {
            return S2W_EINVAL;
        }
        scanReq.ScanDuration = param; 
            
    }
    scanReq.ChannelPage = 0;
    status = AppS2wParse_SecI( ptr, &scanReq.SecI );
	if( status != S2W_SUCCESS )
	{
		return S2W_EINVAL;
	}   
    GsnWLRPAN_ScanReq( &s2w154Ctx.wlrpanCtx, &scanReq);   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;
}

UINT8
AppS2wCmd_154JoinNetwork(UINT8 *ptr)
{
    /**< Associate request.     Set
    Channel 0x0C - 0x17 
    Join network    "0-0xFFFE or MAC Address"   
    PAN ID  0-0xFFFF    
    Capability info     
    */
    GSN_WLRPAN_ASSOCIATE_REQ_T assocReq;
    UINT32 param, addr[2];
    UINT8 status;
    UINT8 *p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS || param < 0xc || param > 0x17 )
    {
        return S2W_EINVAL;
    }
    memset( &assocReq, 0, sizeof( assocReq ));
    assocReq.LogicalChannel = param;
    assocReq.ChannelPage = 0;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if( status != S2W_SUCCESS )
        {
            if( S2W_SUCCESS != AppS2wParse_Mac64( p, (UINT8*)addr ))
                return S2W_EINVAL;
            else
            {
                assocReq.CoordAddrMode = GSN_WLRPAN_ADDR_MODE_EXTND;
                memcpy( &assocReq.CoordAddress.LongAddr, addr, 8 ); 
            }
        }
        else
        {
            if( param < 0xFFFE )
            {
               assocReq.CoordAddrMode = GSN_WLRPAN_ADDR_MODE_SHORT;
               assocReq.CoordAddress.ShortAddr = ( UINT16 )param; 
            }
            else 
                return S2W_EINVAL;
        }
    }
    
    p = AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if( status != S2W_SUCCESS )return S2W_EINVAL;
        else
            assocReq.CoordPANId = ( UINT16 )param;
    }
    
    p = AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if( status != S2W_SUCCESS )return S2W_EINVAL;
        else
            assocReq.CapabilityInformation = ( UINT8 )param;
    }
    status = AppS2wParse_SecI( ptr, &assocReq.SecI );
	if( status != S2W_SUCCESS )
	{
		return S2W_EINVAL;
	}
    GsnWLRPAN_AssociateReq( &s2w154Ctx.wlrpanCtx, &assocReq);   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    if( s2w154Ctx.operationStatus == S2W_SUCCESS )
    {
        s2w154Ctx.CoordAddrMode = assocReq.CoordAddrMode;
        s2w154Ctx.CoordPANId = assocReq.CoordPANId;
        s2w154Ctx.CoordAddress = assocReq.CoordAddress;
    }
    return s2w154Ctx.operationStatus;
}

UINT8
AppS2wCmd_154AddNode(UINT8 *ptr)
{
    /**< Add Node to network-This caommnd is issued by a coordinator, to allow 
    a node to join. Before a node gives a request to join the node this 
    coordinator has to issue this command.      
    Set
    Device address  MAC Address 
    Short address   0 - 0xFFFE  
    */
    UINT8 status, i, freeIdx = S2W_154_MAX_ASSOC_LIST;
    UINT32 eaddr[2], param;
    UINT16 saddr;
    UINT8 *p = AppS2wParse_NextParamGet(&ptr);
    if(!p)return S2W_EINVAL;
        if( S2W_SUCCESS != AppS2wParse_Mac64( p, (UINT8*)eaddr ))
            return S2W_EINVAL;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)return S2W_EINVAL;
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0xFFFE )
        return S2W_EINVAL;
    
    saddr = ( UINT16 )param;
    
    /**< Check if we have this address listed */
    for( i = 0; i < S2W_154_MAX_ASSOC_LIST; i++ )
    {
        if( s2w154Ctx.assocChild[ i ].status == S2W_154_ASSOC_STAT_FREE )
        {
            freeIdx = i;
            break;
        }
        else if( memcmp(&s2w154Ctx.assocChild[i].extendedAddr,&eaddr,8) == 0 )
        {
            /**< It is present */
            if( s2w154Ctx.assocChild[ i ].status == S2W_154_ASSOC_STAT_ASSOC )
            {
                return S2W_EINVAL;
            }
            else
            {
                s2w154Ctx.assocChild[ i ].shortAddr = saddr;
                return S2W_SUCCESS;
            }
        }        
    }
    if( freeIdx < S2W_154_MAX_ASSOC_LIST )
    {
        s2w154Ctx.assocChild[ freeIdx ].shortAddr = saddr;
        memcpy( &s2w154Ctx.assocChild[ freeIdx ].extendedAddr, (UINT8*)eaddr, 8 );
        s2w154Ctx.assocChild[ i ].status = S2W_154_ASSOC_STAT_NOT_ASSOC;
        return S2W_SUCCESS;
    }
    return S2W_EINVAL;
}

UINT8
AppS2wCmd_154StartNetwork(UINT8 *ptr)
{
    /**< Start network. This command is issued to start the network.        
    Set
    Channel 0x0C - 0x17 
    PAN ID  0-0xFFFF    
    Beacon Order    0-0xF   
    Superframe Order    0-0xF   
    PAN Coordinator 0-1 
    Battery realignment 0-1 
    */
    GSN_WLRPAN_START_REQ_T startReq= {0};
    UINT32 param;
    UINT8 status;
    UINT8 *p = AppS2wParse_NextParamGet(&ptr);
    if(!p)  return S2W_EINVAL;
    
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS ||  (param < 0x0c) || (param > 0x17) )
        return S2W_EINVAL;

    memset( &startReq, 0, sizeof( startReq ));

    startReq.LogicalChannel = param;
    startReq.ChannelPage = 0;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if( !p )    return S2W_EINVAL;
    
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS || param > 0xFFFE )
    {
        return S2W_EINVAL;
    }    
    startReq.PANId = (UINT16 )param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0xF )
    {
        return S2W_EINVAL;
    }    
    startReq.BeaconOrder = ( UINT8 )param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0xF )
    {
        return S2W_EINVAL;
    }    
    startReq.SuperframeOrder = ( UINT8 )param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0x1 )
    {
        return S2W_EINVAL;
    }    
    startReq.PANCoordinator = ( UINT8 )param;
    
     p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0x1 )
    {
        return S2W_EINVAL;
    }    
    startReq.CoordRealignment = ( UINT8 )param;
    
	if( startReq.CoordRealignment == 1 )
	{
	    status = AppS2wParse_SecI( ptr, &startReq.CoordRealignSecI );
		if( status != S2W_SUCCESS )
		{
			return S2W_EINVAL;
		}
	}

	status = AppS2wParse_SecI( ptr, &startReq.BeaconSecI );
	if( status != S2W_SUCCESS )
	{
		return S2W_EINVAL;
	}
    
    startReq.StartTime = 0;
    startReq.BatteryLifeExtension = 0;
    
    GsnWLRPAN_StartReq( &s2w154Ctx.wlrpanCtx, &startReq);   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;    
    
}

UINT8
AppS2wCmd_154LeaveNetwork(UINT8 *ptr)
{
    /**< Leave Netowrk. A coordinator can command a node to leave netowrk or a 
    node can leave the network by issuing this command.     
    Set
    Device address  "0-0xFFFF or  MAC Address"    
    Reason  "0-0xFF"  
    TxIndirect "TRUE or FALSE"
    Device PAN Id  "0 - 0xFFFF"
    */
    GSN_WLP_DISASSOCIATE_REQ_T disassocReq;
    UINT32 param, addr[2];
    UINT8 status;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);

    memset( &disassocReq, 0, sizeof( disassocReq ));
	/**< Address Mode and Address */
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if ( status != S2W_SUCCESS )
        {
            if( S2W_SUCCESS != AppS2wParse_Mac64( p, (UINT8*)addr ))
                return S2W_EINVAL;
            else
            {
                disassocReq.DeviceAddrMode = GSN_WLRPAN_ADDR_MODE_EXTND;
                memcpy( &disassocReq.DeviceAddress.LongAddr, addr, 8 ); 
            }
        }
        else
        {
            if( param < 0xFFFE )
            {
               disassocReq.DeviceAddrMode = GSN_WLRPAN_ADDR_MODE_SHORT;
               disassocReq.DeviceAddress.ShortAddr = ( UINT16 )param; 
            }
            else 
                return S2W_EINVAL;
        }
    }
	/**< DisAssoc Reason */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( (status != S2W_SUCCESS) || (param < 0x01) || (param > 0x02) )
    {
        return S2W_EINVAL;
    }    
    disassocReq.DisAssocReason = ( UINT8 )param;

	/**< TxIndirect */
	p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
	if( status != S2W_SUCCESS || param > 0x01 )
    {
        return S2W_EINVAL;
    } 
    disassocReq.TxIndirect = param;

	/**< Device PAN Id */
	p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
	if( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    } 

    disassocReq.DevicePANId = param; //s2w154Ctx.CoordPANId;

	status = AppS2wParse_SecI( ptr, &disassocReq.SecI );
	if( status != S2W_SUCCESS )
	{
		return S2W_EINVAL;
	}

    GsnWLRPAN_DisAssociateReq( &s2w154Ctx.wlrpanCtx, &disassocReq );  
	
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;   
}

UINT8
AppS2wCmd_154PollData(UINT8 *ptr)
{
    /**< Poll for data  NA  Set
    */
    UINT8 status;
    GSN_WLRPAN_POLL_REQ_T pollReq = {0};

    //memset( &pollReq, 0, sizeof( pollReq ));

    pollReq.CoordAddrMode = s2w154Ctx.CoordAddrMode;
    pollReq.CoordPANId = s2w154Ctx.CoordPANId;    
    pollReq.CoordAddress = s2w154Ctx.CoordAddress;
    //pollReq.SecI.SecILevel = NULL;

	status = AppS2wParse_SecI( ptr, &pollReq.SecI );
	if( status != S2W_SUCCESS )
	{
		return S2W_EINVAL;
	}

    GsnWLRPAN_PsPollReq( &s2w154Ctx.wlrpanCtx, &pollReq );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;   

}

const UINT8 KeyIdLenLookUp_Patch[] = { 0, 0x1, 0x5, 0x9 };

UINT8 
AppS2wCmd_DataLenCheck( GSN_WLRPAN_DATA_REQ_T *pDataReq )
{
	UINT8 len = 7;	//FRM CTL, DSN, DST PAN, SRC PAN,

	len += ( pDataReq->DstMode == GSN_WLRPAN_ADDR_MODE_EXTND )? 8 : 2;
	len += ( pDataReq->SrcMode == GSN_WLRPAN_ADDR_MODE_EXTND )? 8 : 2;
	
    if( pDataReq->SecI.SecILevel != 0 )
    {
        len += ( 1 /*Sec Ctrl*/ + 4 /*Frm Cntr*/ + 
            KeyIdLenLookUp_Patch[ pDataReq->SecI.SecILevel ] /*Key Id*/);
    }

	if(( len + pDataReq->MsduLen ) < 127 )
	{
		return S2W_SUCCESS;
	}
	else
	{
		return S2W_EINVAL;
	}
}


UINT8
AppS2wCmd_154DataSend(UINT8 *ptr)
{
    /**< Send data  
    destination address "0-0xFFFF or MAC Address"
    Handle  0-0xFF
    Tx option(as per spec)  0-7
    Data format (0-bin, 1-hex)  0-1
    frame length    0-100
    Frame   
    */
    GSN_WLRPAN_DATA_REQ_T dataReq;

    UINT32 param, addr[2];
    UINT8 status, format;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);
    
    memset( &dataReq, 0, sizeof( dataReq ));

    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if ( status != S2W_SUCCESS )
        {
            if( S2W_SUCCESS != AppS2wParse_Mac64( p, (UINT8*)addr ))
                return S2W_EINVAL;
            else
            {
                dataReq.DstMode = GSN_WLRPAN_ADDR_MODE_EXTND;
                memcpy( &dataReq.DstAddr.LongAddr, addr, 8 ); 
            }
        }
        else
        {
            if( param <= 0xFFFF )
            {
               dataReq.DstMode = GSN_WLRPAN_ADDR_MODE_SHORT;
               dataReq.DstAddr.ShortAddr = ( UINT16 )param; 
            }
            else 
                return S2W_EINVAL;
        }
    }

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS )
    {
        return S2W_EINVAL;
    }    
    dataReq.DstPanId = ( UINT16 )param;

    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0xFF )
    {
        return S2W_EINVAL;
    }    
    dataReq.MsduHandle = ( UINT8 )param;

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0x7 )
    {
        return S2W_EINVAL;
    }    
    dataReq.TxOption = ( UINT8 )param;

    dataReq.SrcMode = GSN_WLRPAN_ADDR_MODE_EXTND; //TODO

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 2 )
    {
        return S2W_EINVAL;
    }    
    format = ( UINT8 )param;
    (void)format;//TODO

    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS || param > 127 )
    {
        return S2W_EINVAL;
    }    
    dataReq.MsduLen = ( UINT8 )param;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

	status = AppS2wParse_SecI( ptr, &dataReq.SecI );
	if( status != S2W_SUCCESS )
	{
		return S2W_EINVAL;
	}
	status = AppS2wCmd_DataLenCheck( &dataReq );
	if( status == S2W_EINVAL )
	{
		return S2W_EINVAL;
	}
    /**< Copy the MSDU */
    memcpy( (VOID *)dataReq.Msdu, (VOID *)p, dataReq.MsduLen );
    
    GsnWLRPAN_DataReq( &s2w154Ctx.wlrpanCtx, &dataReq );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;
}

UINT8
AppS2wCmd_154DataPurge(UINT8 *ptr)
{
    /**< Purge data 
    Handle  0-0xFF
    */
    GSN_WLRPAN_PURGE_REQ_T purgReq;
    UINT32 param;
    UINT8 status;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    memset( &purgReq, 0, sizeof( purgReq ));

    status = AppS2wParse_Hex(p, &param);
    if ( status != S2W_SUCCESS || param > 0xFF )
    {
        return S2W_EINVAL;
    } 
    purgReq.MsduHandle = ( UINT8 )param;

    GsnWLRPAN_PurgeReq( &s2w154Ctx.wlrpanCtx, &purgReq );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;
}
UINT8 
AppS2wCmd_154RxEnable(UINT8 *ptr)
{
    GSN_WLRPAN_RXENABLE_REQ_T rxenreq;
    UINT32 param;
    UINT8 status;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);

    memset( &rxenreq, 0, sizeof( rxenreq ));

    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if( ( status != S2W_SUCCESS )||( param > 0x00FFFFFF ) )
        {
            return S2W_EINVAL;
        }
        rxenreq.RxOnTime = param;
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if( ( status != S2W_SUCCESS )||( param > 0x00FFFFFF ) )
        {
            return S2W_EINVAL;
        }
        rxenreq.RxOnDuration = param;
        p = AppS2wParse_NextParamGet(&ptr);
        if (!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if ( status != S2W_SUCCESS || param > 1 )
        {
            return S2W_EINVAL;
        }
        rxenreq.DeferPermit = param;
    }
    else
    {
        return S2W_EINVAL;
    }
    GsnWLRPAN_RXEnReq( &s2w154Ctx.wlrpanCtx, &rxenreq );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    return s2w154Ctx.operationStatus;
}
#if 0
UINT8 
AppS2wCmd_154OrphanRsp(UINT8 *ptr)
{
    GSN_WLRPAN_ORPHAN_RSP_T Rsp;
    UINT32 param,addr[2];
    UINT8 status;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);
    if ((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if ( status != S2W_SUCCESS )
        {
            return S2W_EINVAL;
        }
        if( S2W_SUCCESS != AppS2wParse_Mac64( ptr, (UINT8*)addr ))
                return S2W_EINVAL;
        else
            memcpy(&Rsp.OrphanAddr,(UINT8*)addr, 8);
        p = AppS2wParse_NextParamGet(&ptr);
        if(!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if( status != S2W_SUCCESS )
        {
            return S2W_EINVAL;
        }
        Rsp.ShortAddr = param;
        p = AppS2wParse_NextParamGet(&ptr);
        if(!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if( status != S2W_SUCCESS )
        {
            return S2W_EINVAL;
        }
        if( param > 1)
        {
            return S2W_EINVAL;
        }
        Rsp.AssociatedMember = param;
        Rsp.SecI = NULL;
    }
    else
    {
        return S2W_EINVAL;
    }
    GsnWLRPAN_OrphanRsp( &s2w154Ctx.wlrpanCtx, &Rsp );   
    return GSN_SUCCESS;
}
#endif
UINT8 
AppS2wCmd_154GTSReq(UINT8 *ptr)
{
    UINT32 param;
    UINT8 status;
    GSN_WLRPAN_GTS_REQ_T GTSReq;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);

    memset( &GTSReq, 0, sizeof( GTSReq ));

    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if (( status != S2W_SUCCESS ) || ( param == 0 ) || ( param > 7 ) )
        {
            return S2W_EINVAL;
        }
        GTSReq.Char.Length = param;
        p = AppS2wParse_NextParamGet(&ptr);
        if(!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if(( status != S2W_SUCCESS ) && ( param > 1 ) )
        {
            return S2W_EINVAL;
        }
        GTSReq.Char.Dir = param;
        p =AppS2wParse_NextParamGet(&ptr);
        if(!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if(( status != S2W_SUCCESS ) && ( param > 1 ) )
        {
            return S2W_EINVAL;
        }
        GTSReq.Char.CharType = param;
	    status = AppS2wParse_SecI( ptr, &GTSReq.SecI );
		if( status != S2W_SUCCESS )
		{
			return S2W_EINVAL;
		}
        
    }
    else
    {
        return S2W_EINVAL;
    }
    GsnWLRPAN_GTSReq( &s2w154Ctx.wlrpanCtx, &GTSReq );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    return s2w154Ctx.operationStatus;
}
UINT8 
AppS2wCmd_154SyncReq(UINT8 *ptr)
{
    UINT32 param;
    UINT8 status;
    GSN_WLRPAN_SYNC_REQ_T Req;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);

    memset( &Req, 0, sizeof( Req ));

    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Hex(p, &param);
        if(( status != S2W_SUCCESS ) || ( param < 0x0C ) || ( param > 0x17 ) )
        {
            return S2W_EINVAL;
        }
        Req.LogicalChannel = param;
        p = AppS2wParse_NextParamGet(&ptr);
        if(!p)
        {
            return S2W_EINVAL;
        }
        status = AppS2wParse_Hex(p, &param);
        if(( status != S2W_SUCCESS ) || ( param > 1 ) )
        {
            return S2W_EINVAL;
        }
        Req.TrackBeacon = param;
        Req.ChannelPage = 0;
    }
    else
    {
        return S2W_EINVAL;
    }
    GsnWLRPAN_SyncReq( &s2w154Ctx.wlrpanCtx, &Req );   
    return s2w154Ctx.operationStatus;
}
#ifdef GSN_802_15_4_TEST_SUPPORT
UINT8 AppS2wCmd_154TmrReq(UINT8 *ptr)
{
    UINT32 param;
    UINT8 status;
    GSN_WLP_TMR_REQ_T tmrReq;
    UINT8* p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS || param > 0xFFFFFF )
    {
        return S2W_EINVAL;
    } 
    tmrReq.NumOfSymbol = param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Hex(p, &param);
    if( status != S2W_SUCCESS || param > 0x1 )
    {
        return S2W_EINVAL;
    } 
    tmrReq.IsPeriodic = ( UINT8 )param;
    
    GsnWLRPAN_TmrReq( &s2w154Ctx.wlrpanCtx, &tmrReq );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    
    return s2w154Ctx.operationStatus;
}
#if 0
UINT8
AppS2wCmd_154GenericTest(UINT8 *ptr)
{
    UINT32 array[10];
    UINT8* p, i, status;
    for( i = 0; i < 10; i++ )
    {
        p = AppS2wParse_NextParamGet(&ptr);
        if((!p) || (*p == '\0'))
        {
            break;
        }

        status = AppS2wParse_Hex(p, &array[i]);
    }
    if(array[0] == 6 )semRelease = TRUE;
    GsnWLRPAN_GenericReq( &s2w154Ctx.wlrpanCtx, array );   
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    return s2w154Ctx.operationStatus;
}
#endif
#endif
UINT32 size[6];
UINT8
AppS2wCmd_154SetReq(UINT8 *ptr)
{
    GSN_WLRPAN_SET_REQ_T setReq;
    UINT32 param;
    UINT8 status;
    UINT8 *p = AppS2wParse_NextParamGet(&ptr);

    memset( &setReq, 0, sizeof( setReq ));

    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &param);
    if( ( status != S2W_SUCCESS ) || ( param > macKey ) )
    {
        return S2W_EINVAL;
    }    
    setReq.Attribute = param;
    
    p = AppS2wParse_NextParamGet(&ptr);
    if( !p )    return S2W_EINVAL;
    
    switch( setReq.Attribute )
    {
        case macAssociatedPANCoord:
        case macAssociationPermit:
        case macAutoRequest:
        case macBattLifeExt:
        case macGTSPermit:
        case macPromiscuousMode:
        case macRxOnWhenIdle:
        case macSecurityEnabled:
        case macTimestampSupported:
            
        case macAckWaitDuration:
        case macBattLifeExtPeriods:
        case macBeaconPayloadLength:
        case macBeaconOrder:  
        case macSuperframeOrder:
        case macBSN:
        case macDSN:
        case macMinBE:
        case macMaxBE:
        case macMaxCSMABackoffs:
        case macMaxFrameRetries:
        case macMinLIFSPeriod:
        case macMinSIFSPeriod:
        case macResponseWaitTime:
        case phyCurrentChannel:
        case phyTransmitPower:
        case phyCCAMode:
        case phyCurrentPage:
        case phySHRDuration:
        case phySymbolsPerOctet:
            status = AppS2wParse_Hex(p, &param);
            if( status != S2W_SUCCESS )  return S2W_EINVAL;
            setReq.Value[0] = param;
            break;
        case macAutoReqSeurityLevel:
			status = AppS2wParse_Hex( p, &param );
			if( ( status != S2W_SUCCESS ) || ( param > 7 ) )
				return S2W_EINVAL;
			setReq.Value[0] = param;
			break;
        case macAutoReqKeyIdMode:
			status = AppS2wParse_Hex( p, &param );
			if( ( status != S2W_SUCCESS ) || ( param > 3 ) )
				return S2W_EINVAL;
			setReq.Value[0] = param;
			break;
		case macAutoReqKeyIndex:
			status = AppS2wParse_Hex( p, &param );
			if( ( status != S2W_SUCCESS ) || ( param == 0 ) )
				return S2W_EINVAL;
			setReq.Value[0] = param;
			break;

		case macKeyTableEntries:
		case macDeviceTableEntries:
		case macSecurityLevelTableEntries:
		case macKeyIdLookupListEntries:
		case macKeyDeviceListEntries:
		case macKeyUsageListEntries:
            status = AppS2wParse_Hex( p, &param );
			if( ( status != S2W_SUCCESS )||( param > GSN_WLP_MAX_SEC_ENTRIES ) )
				return S2W_EINVAL;
			setReq.Value[0] = param;
			break;
		
        case macKeyUsageListIndex:		
        case macKeyTableIndex:
		case macKeyDeviceListIndex:
		case macKeyIdLookupListIndex:
			status = AppS2wParse_Hex( p, &param );
			if( ( status != S2W_SUCCESS )||( param >= GSN_WLP_MAX_SEC_ENTRIES ) )
                return S2W_EINVAL;
            setReq.Value[0] = param;
            break;
        
        case macPANId:
        case macCoordShortAddress:
        case macShortAddress:
        case macSyncSymbolOffset:
        case macTransactionPersistenceTime:
		case macPANCoordShortAddress:
        case phyMaxFrameDuration:
            status = AppS2wParse_Hex(p, &param);
            if ( status != S2W_SUCCESS )  
                return S2W_EINVAL;
            memcpy(setReq.Value, &param, sizeof(UINT16) );
            break;
       
        case macBeaconTxTime:
        case macMaxFrameTotalWaitTime:
        case phyChannelsSupported:
		case macFrameCounter:
            status = AppS2wParse_Hex(p, &param);
            if ( status != S2W_SUCCESS )  
                return S2W_EINVAL;
            memcpy(setReq.Value, &param, sizeof(UINT32) );
            break;    
       
        case macExtendedAddress:
        case macCoordExtendedAddress:
		case macPANCoordExtendedAddress:
            if( S2W_SUCCESS != AppS2wParse_Mac64( p, (UINT8*)setReq.Value ))
                return S2W_EINVAL;
            break;

		case macDefaultKeySource:
		case macAutoReqKeySource:
			status = AppS2wParse_Hex(p, &param);
            if(( status != S2W_SUCCESS )||( param >= GSN_WLP_MAX_SEC_ENTRIES ) )  
                return S2W_EINVAL;
        	setReq.AttributeIdx = ( UINT16 )param;

			p = AppS2wParse_NextParamGet(&ptr);
			if( !p )	return S2W_EINVAL;
			if( S2W_SUCCESS != AppS2wParse_Mac64( p, (UINT8*)setReq.Value ))
                return S2W_EINVAL;
			break;

		case macDeviceTable:
			{
				GSN_WLRPAN_DEVICE_DESC_T DeviceTable;

				status = AppS2wParse_Hex(p, &param);
	            if(( status != S2W_SUCCESS )||
					( param >= GSN_WLP_MAX_SEC_ENTRIES ) )  
	                return S2W_EINVAL;
				setReq.AttributeIdx = ( UINT16 )param; 

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if( status != S2W_SUCCESS )  
					return S2W_EINVAL;
				DeviceTable.PANId = (UINT16)param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if( status != S2W_SUCCESS )		return S2W_EINVAL;
				DeviceTable.ShortAddress = (UINT16)param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				if( S2W_SUCCESS != 
						AppS2wParse_Mac64( p, (UINT8*)&DeviceTable.ExtAddress))
	                return S2W_EINVAL;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if( status != S2W_SUCCESS )		return S2W_EINVAL;
				DeviceTable.FrameCounter = param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 1 ) )  
					return S2W_EINVAL;
				DeviceTable.Exempt = ( UINT8 )param;

				memcpy( setReq.Value, &DeviceTable, 
					sizeof( GSN_WLRPAN_DEVICE_DESC_T ));

	            break;				
			}
		case macSecurityLevelTable:
			{
				GSN_WLRPAN_SECURITY_LEVEL_DESC_T SecILevelTable;
				status = AppS2wParse_Hex(p, &param);
	            if(( status != S2W_SUCCESS )||
					( param >= GSN_WLP_MAX_SEC_ENTRIES ) )  
	                return S2W_EINVAL;
				setReq.AttributeIdx = ( UINT16 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);				
				if(( status != S2W_SUCCESS )||( param > 3 ) )  
					return S2W_EINVAL;
				SecILevelTable.FrameType = ( UINT8 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 9 ) )  
					return S2W_EINVAL;
				SecILevelTable.CmdFrmIdentifier = ( UINT8 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 7 ) )  
					return S2W_EINVAL;
				SecILevelTable.SecIMinimum = ( UINT8 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 1 ) )  
					return S2W_EINVAL;
				SecILevelTable.DeviceOverrideSecIMinimum = ( UINT8 )param;

				memcpy( setReq.Value, &SecILevelTable,
					sizeof( GSN_WLRPAN_SECURITY_LEVEL_DESC_T ));
				break;
				
			}
		case macKeyIdLookupList:
			{
				GSN_WLRPAN_KEYID_LOOKUP_DESC_T LookupDesc;
				status = AppS2wParse_Hex( p, &param );
				if( ( status != S2W_SUCCESS ) || ( param > 1 ) )
					return S2W_EINVAL;
				LookupDesc.LookupDataSize = ( param == 0 ) ? 5 : 9 ;
				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_LookupData( p, LookupDesc.LookupData, 
							LookupDesc.LookupDataSize );
				if( status != S2W_SUCCESS )  
					return S2W_EINVAL;
				memcpy( setReq.Value, &LookupDesc, 
					sizeof( GSN_WLRPAN_KEYID_LOOKUP_DESC_T ));
				break;
			}
		case macKeyDeviceList:
			{
				GSN_WLRPAN_KEY_DEVICE_DESC_T DevDesc;
				status = AppS2wParse_Hex( p, &param );
				if( status != S2W_SUCCESS ) 
					return S2W_EINVAL;
				DevDesc.DeviceDescHandle = ( UINT8 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 1 ) )  
					return S2W_EINVAL;
				DevDesc.UniqueDevice = ( UINT8 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 1 ) )  
					return S2W_EINVAL;
				DevDesc.Blacklisted = ( UINT8 )param;
				
				memcpy( setReq.Value, &DevDesc, 
					sizeof( GSN_WLRPAN_KEY_DEVICE_DESC_T ));
				break;
			}
		case macKeyUsageList:
			{
				GSN_WLRPAN_KEY_USAGE_DESC_T UsageDesc;
				status = AppS2wParse_Hex( p, &param );
				if(( status != S2W_SUCCESS )||( param > 3 )) 
					return S2W_EINVAL;
				UsageDesc.FrameType = ( UINT8 )param;

				p = AppS2wParse_NextParamGet(&ptr);
				if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Hex(p, &param);
				if(( status != S2W_SUCCESS )||( param > 9 ) )  
					return S2W_EINVAL;
				UsageDesc.CmdFrmIdentifier = ( UINT8 )param;

				memcpy( setReq.Value, &UsageDesc,
					sizeof( GSN_WLRPAN_KEY_USAGE_DESC_T ) );
				break;
			}
		case macKey:
	    		{
				status = AppS2wParse_Key( p, setReq.Value );
				if( status != S2W_SUCCESS )
	        		return S2W_EINVAL;
				setReq.AttributeLength = 16;
				break;
	    		}
		case macBeaconPayload:
			{
				UINT8 *pPtr = p;
				p = AppS2wParse_NextParamGet(&ptr);
	    		if( !p )	return S2W_EINVAL;
				status = AppS2wParse_Int( p, (UINT32 *)(&setReq.AttributeLength));
				memcpy( setReq.Value, pPtr, setReq.AttributeLength );
				break;
			}
           
        default:
            s2w154Ctx.operationStatus = S2W_FAILURE;
            return S2W_EINVAL;
            
    }
    
    GsnWLRPAN_SetReq( &s2w154Ctx.wlrpanCtx, &setReq );
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    return s2w154Ctx.operationStatus;
}

UINT8
AppS2wCmd_154GetReq(UINT8 *ptr)
{
    GSN_WLRPAN_GET_REQ_T getReq;
    UINT32 param;
    UINT8 status;
    UINT8 *p = AppS2wParse_NextParamGet(&ptr);

    memset( &getReq, 0, sizeof( getReq ));

    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &param);
    if( status != S2W_SUCCESS || ( param > macKey ) )
  		return S2W_EINVAL;
  
    getReq.Attribute = param;
	getReq.AttributeIdx = 0; // TODO: Fix
	if(( getReq.Attribute == macDeviceTable )||
		( getReq.Attribute == macSecurityLevelTable ))
    {
		p = AppS2wParse_NextParamGet(&ptr);
		if( !p )	return S2W_EINVAL;
		status = AppS2wParse_Int( p, &param );
		if( (status != S2W_SUCCESS) || ( param >= GSN_WLP_MAX_SEC_ENTRIES ) )
        return S2W_EINVAL;
		getReq.AttributeIdx = ( UINT16 )param;
		
    }    
    GsnWLRPAN_GetReq( &s2w154Ctx.wlrpanCtx, &getReq );
    GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    return s2w154Ctx.operationStatus;
}


UINT8 *pWlrpanStatusMsg[] = {
   "COUNTER_ERROR" ,
   "IMPROPER_KEY_TYPE",
   "IMPROPER_SECURITY_LEVEL",
   "UNSUPPORTED_LEGACY",
   "UNSUPPORTED_SECURITY",
   "BEACON_LOSS",
   "CHANNEL_ACCESS_FAILURE",
   "DENIED",
   "DISABLE_TRX_FAILURE",
   "SECURITY_ERROR",
   "FRAME_TOO_LONG",
   "INVALID_GTS",
   "INVALID_HANDLE",
   "INVALID_PARAMETER",
   "NO_ACK",
   "NO_BEACON",
   "NO_DATA",
   "NO_SHORT_ADDRESS",
   "OUT_OF_CAP",
   "PAN_ID_CONFLICT",
   "REALIGNMENT",
   "TRANSACTION_EXPIRED",
   "TRANSACTION_OVERFLOW",
   "TX_ACTIVE",
   "UNAVAILABLE_KEY",
   "UNSUPPORTED_ATTRIBUTE",
   "INVALID_ADDRESS",
   "ON_TIME_TOO_LONG",
   "PAST_TIME",
   "TRACKING_OFF",
   "INVALID_INDEX",
   "LIMIT_REACHED",
   "READ_ONLY",
   "SCAN_IN_PROGRESS",
   "SUPERFRAME_OVERLAP",   
   "CONDITIONAL_PASS"
};

UINT32 WlrpanStatusOffset = 0x9000A0DB;

GSN_STATUS
AppS2w_WLRPANAssocCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_ASSOCIATE_CFM_T *pCfm = (GSN_WLRPAN_ASSOCIATE_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    if(pCfm->Status == GSN_SUCCESS)
    {
        s2w154Ctx.assocState = S2W_154_ASSOC_STAT_ASSOC;
    }
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->Status;
}

GSN_STATUS
AppS2w_WLRPANAssocInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    UINT8 i;
    GSN_WLRPAN_ASSOCIATE_IND_T *pInd = (GSN_WLRPAN_ASSOCIATE_IND_T *)pMsg;
    GSN_WLRPAN_ASSOCIATE_RSP_T pRsp ;
    for(i=0;i<S2W_154_MAX_ASSOC_LIST ;i++)
    {
        if(memcmp(&pInd->DeviceAddress.LongAddr,
                  s2w154Ctx.assocChild[i].extendedAddr,8)==0)
            break;
    }
    memcpy(&pRsp.DeviceAddress.LongAddr, &pInd->DeviceAddress.LongAddr,8);
    memcpy( &pRsp.SecI, &pInd->SecI, sizeof(GSN_WLRPAN_SEC_I_T ));
    if( i != S2W_154_MAX_ASSOC_LIST )
    {   /* Match found*/
        /**< Allocate the ShortAddress based on request in CapabilityInfo */
        if( pInd->CapabilityInformation & ( 1 << 7 ) )
        {
            pRsp.AssocShortAddress = s2w154Ctx.assocChild[i].shortAddr;
        }
        else
        {
            pRsp.AssocShortAddress = 0xFFFF;
        }
        pRsp.Status = GSN_SUCCESS;
		GsnWLRPAN_AssociateRsp(&s2w154Ctx.wlrpanCtx,  &pRsp );
    }
    else
    {
        pRsp.Status = GSN_FAILURE;
    }
    return pRsp.Status;
}

GSN_STATUS
AppS2w_WLRPANDisassocCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLP_DISASSOCIATE_CFM_T *pCfm = (GSN_WLP_DISASSOCIATE_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->Status;
}

GSN_STATUS
AppS2w_WLRPANDisassocInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
	s2w154Ctx.assocState = S2W_154_ASSOC_STAT_NOT_ASSOC; 
	
    S2w_Printf("\r\nDevice Disassociated\r\n");		

	GsnOsal_SemRelease( &s2w154Ctx.blockingSem );

	return GSN_SUCCESS;
 }

GSN_STATUS
AppS2w_WLRPANBeaconNotifyInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLP_BEACON_NOTIFY_T *pNotify = (GSN_WLP_BEACON_NOTIFY_T *)pMsg;
	UINT8 i = 0;
    S2w_Printf("\r\nBeacon Notification\r\n");
	
	S2w_Printf("%x  %02d  ",pNotify->PANDescriptor.CoordPANId, 
		pNotify->PANDescriptor.LogicalChannel);
	if( pNotify->PANDescriptor.CoordAddrMode == GSN_WLRPAN_ADDR_MODE_EXTND )
	{
		UINT8 *pAddr = pNotify->PANDescriptor.CoordAddress.addr;
        S2w_Printf(" %02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x ",
            pAddr[0], pAddr[1], pAddr[2], pAddr[3], pAddr[4], 
            pAddr[5], pAddr[6], pAddr[7]);		
	}
    else
	{
		S2w_Printf(" %x ", pNotify->PANDescriptor.CoordAddress.ShortAddr );
	}
	S2w_Printf(" %d ",pNotify->sduLength);
	while( i < pNotify->sduLength )
	{
		S2w_Printf(" %02x ",pNotify->sdu[i]);
		i++;
	}
    S2w_Printf("\r\n");

    return GSN_SUCCESS;
}

GSN_STATUS
AppS2w_WLRPANGTSInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    //GSN_WLRPAN_GTS_IND_T *pInd = (GSN_WLRPAN_GTS_IND_T *)pMsg;
    S2w_Printf("\r\nGTS Indiacation\r\n");
    return GSN_SUCCESS;
}

GSN_STATUS
AppS2w_WLRPANGTSCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLRPAN_GTS_CFM_T *pCfm = (GSN_WLRPAN_GTS_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->Status;
}

GSN_STATUS
AppS2w_WLRPANOrphanInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    UINT8 i;
    GSN_WLRPAN_ORPHAN_IND_T *pInd = (GSN_WLRPAN_ORPHAN_IND_T *)pMsg;
    GSN_WLRPAN_ORPHAN_RSP_T Rsp;
    s2w154Ctx.operationStatus = S2W_SUCCESS; 
    for(i=0;i<S2W_154_MAX_ASSOC_LIST ;i++)
    {
        if(memcmp(&pInd->OrphanAddr,
                  &s2w154Ctx.assocChild[i].extendedAddr,8)==0)
            break;
    }
    memcpy(&Rsp.OrphanAddr, &pInd->OrphanAddr,8);
    memcpy( &Rsp.SecI, &pInd->SecI, sizeof(GSN_WLRPAN_SEC_I_T ));
    if( i != S2W_154_MAX_ASSOC_LIST )
    {   /* Match found*/
        Rsp.ShortAddr = s2w154Ctx.assocChild[i].shortAddr;
        Rsp.AssociatedMember = TRUE;
    }
    GsnWLRPAN_OrphanRsp(&s2w154Ctx.wlrpanCtx,&Rsp);
    return GSN_SUCCESS;
}

GSN_STATUS
AppS2w_WLRPANResetCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLRPAN_RESET_CFM_T *pCfm = (GSN_WLRPAN_RESET_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->status;
}
GSN_STATUS
AppS2w_WLRPANRxEnableCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLRPAN_RXENABLE_CFM_T *pCfm = (GSN_WLRPAN_RXENABLE_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->status;
}
GSN_STATUS
AppS2w_WLRPANScanCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLRPAN_SCAN_CFM_T *pCfm = (GSN_WLRPAN_SCAN_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    if(pCfm->Status == GSN_SUCCESS)
    {
        UINT8 i;
        if( pCfm->ScanType == 0 )   // ED Scan
        {
            S2w_Printf("\r\nChannel Index\tEnergy Reading");
            for(i = 0x0C; i < 0x17; i++)
            {
                S2w_Printf("\r\n\t%d\t\t%d",i,pCfm->Result.EnergyDetectList[i]);
            }
        }
    }
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
	if( pCfm->Status == GSN_SUCCESS )
	{
		if(( pCfm->ScanType == 0x01 )||(pCfm->ScanType == 0x02 ))
    {
			UINT8 i = 0;
			GSN_WLRPAN_PAN_DESC_T pDesc;
			GSN_WLRPAN_SUPFRM_SPEC_T  *pSpec;
    	    S2w_Printf("\r\n\nPANID BO  SO  BLE   PAN-CRD  AssocPermit\r\n");
			for( i = 0; i < pCfm->ResultListSize; i++ )
			{
				pDesc = pCfm->Result.PANDescriptorList[i];
				pSpec = ( GSN_WLRPAN_SUPFRM_SPEC_T *)( &pDesc.SuperframeSpec );
				S2w_Printf("%04x  ",pDesc.CoordPANId );
				S2w_Printf("%02d  ",pSpec->BO );
				S2w_Printf("%02d  ",pSpec->SO);
				S2w_Printf("%02d     ",pSpec->BLE );
				if( pSpec->PANCRD )         S2w_Printf("TRUE     ");
			    else				        S2w_Printf("FALSE    ");

			    if( pSpec->AssocPermit )    S2w_Printf("TRUE");
			    else						S2w_Printf("FALSE");
				S2w_Printf("\r\n");
			}
		}
    }
    return pCfm->Status;
}
GSN_STATUS
AppS2w_WLRPANCommStatusInd(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLRPAN_COMM_STATUS_IND_T *pInd = (GSN_WLRPAN_COMM_STATUS_IND_T *)pMsg;
    
	S2w_Printf("\r\nComm Status Indication");
	S2w_Printf("\r\nStatus - ");
	if( pInd->status == 0 )
    {
		S2w_Printf("Success");
    }
    else
    {
        S2w_Printf("%s", pWlrpanStatusMsg[pInd->status - WlrpanStatusOffset] );
    }
    S2w_Printf("\r\nPAN Id - %x", pInd->PANId );
    S2w_Printf("\r\nSrc Address - ");
    if( pInd->SrcMode == 0x02 )
    {
        S2w_Printf("%x",pInd->SrcAddr.ShortAddr);
}
    else
{
        S2w_Printf("%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
            pInd->SrcAddr.addr[0], pInd->SrcAddr.addr[1], pInd->SrcAddr.addr[2], 
            pInd->SrcAddr.addr[3], pInd->SrcAddr.addr[4], pInd->SrcAddr.addr[5], 
            pInd->SrcAddr.addr[6], pInd->SrcAddr.addr[7]);
    }
    S2w_Printf("\r\nDst Address - ");
    if( pInd->SrcMode == 0x02 )
    {
        S2w_Printf("%x",pInd->DstAddr.ShortAddr);
    }
    else
    {
        S2w_Printf("%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x\r\n",
            pInd->DstAddr.addr[0], pInd->DstAddr.addr[1], pInd->DstAddr.addr[2],
            pInd->DstAddr.addr[3], pInd->DstAddr.addr[4], pInd->DstAddr.addr[5],
            pInd->DstAddr.addr[6], pInd->DstAddr.addr[7]);
    }
	return pInd->status;
    }
GSN_STATUS
AppS2w_WLRPANSetCfm(VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg)
{
    GSN_WLRPAN_SET_CFM_T *pCfm = (GSN_WLRPAN_SET_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->status;
}
GSN_STATUS
AppS2w_WLRPANStartCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_START_CFM_T *pCfm = (GSN_WLRPAN_START_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    if(pCfm->Status == GSN_SUCCESS)
    {
		s2w154Ctx.assocState = S2W_154_ASSOC_STAT_ASSOC;
    }
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->Status;
}
GSN_STATUS
AppS2w_WLRPANSyncLossInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    //GSN_WLRPAN_SYNCLOSS_IND_T *pInd = (GSN_WLRPAN_SYNCLOSS_IND_T *)pMsg;
    S2w_Printf("\r\nSyncLoss\r\n");
    return GSN_SUCCESS;
}
GSN_STATUS
AppS2w_WLRPANPollCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_POLL_CFM_T *pCfm = (GSN_WLRPAN_POLL_CFM_T *)pMsg;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pCfm->status;
}





GSN_STATUS 
AppS2w_WLRPANGetCfg( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_GET_CFM_T *pCfm = ( GSN_WLRPAN_GET_CFM_T* )pMsg;
    UINT32 value;
    UINT8 i;
    s2w154Ctx.operationStatus = S2W_SUCCESS;
    value = *(( UINT32* )pCfm->Value);
    switch( pCfm->Attribute )
    {
    case macAssociatedPANCoord:
    case macAssociationPermit:
    case macAutoRequest:
    case macBattLifeExt:
    case macGTSPermit:
    case macPromiscuousMode:
    case macRxOnWhenIdle:
    case macSecurityEnabled:
    case macTimestampSupported:
        
    case macAckWaitDuration:
    case macBattLifeExtPeriods:
    case macBeaconPayloadLength:
    case macBeaconOrder:  
    case macSuperframeOrder:
    case macBSN:
    case macDSN:
    case macMinBE:
    case macMaxBE:
    case macMaxCSMABackoffs:
    case macMaxFrameRetries:
    case macMinLIFSPeriod:
    case macMinSIFSPeriod:
    case macResponseWaitTime:
    case phyCurrentChannel:
    case phyTransmitPower:
    case phyCCAMode:
    case phyCurrentPage:
    case phySHRDuration:
    case phySymbolsPerOctet:
	case macKeyTableEntries:
	case macDeviceTableEntries:
	case macSecurityLevelTableEntries:
		
	case macKeyTableIndex:
	case macKeyIdLookupListEntries:
	case macKeyIdLookupListIndex:
	case macKeyDeviceListEntries:
	case macKeyDeviceListIndex:
	case macKeyUsageListEntries:
	case macKeyUsageListIndex:		
        S2w_Printf("\r\n%02x\r\n", pCfm->Value[0] );
        break;
    
    case macPANId:
    case macCoordShortAddress:
    case macShortAddress:
    case macSyncSymbolOffset:
    case macTransactionPersistenceTime:
    case phyMaxFrameDuration:
        S2w_Printf("\r\n%04x\r\n", value );
        break;
   
    case macBeaconTxTime:
    case macMaxFrameTotalWaitTime:
    case phyChannelsSupported:
	case macFrameCounter:
        S2w_Printf("\r\n%08x\r\n" , (UINT32 )value );
        break;    
   
    case macExtendedAddress:
    case macCoordExtendedAddress:
        S2w_Printf("\r\n%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
            pCfm->Value[0], pCfm->Value[1], pCfm->Value[2], pCfm->Value[3],
            pCfm->Value[4], pCfm->Value[5], pCfm->Value[6], pCfm->Value[7]);
        break;    
        
    case macBeaconPayload:
        S2w_Printf("\r\n");
        for(i=0;i<128;i++)
        {
            S2w_Printf("%02x ");
        }
        S2w_Printf("\r\n");

	case macDeviceTable:
	{					
		GSN_WLRPAN_DEVICE_DESC_T DeviceTable;
		UINT8 ExtAddr[8];
		memcpy( &DeviceTable, pCfm->Value, sizeof(GSN_WLRPAN_DEVICE_DESC_T));
		memcpy( ExtAddr, &DeviceTable.ExtAddress, 8);
		S2w_Printf("\r\nPAN Id       :%04x",DeviceTable.PANId);
		S2w_Printf("\r\nShort Addr   :%04x",DeviceTable.ShortAddress);
		S2w_Printf("\r\nLong Addr    :");
		S2w_Printf("%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
            ExtAddr[0], ExtAddr[1], ExtAddr[2], ExtAddr[3],
            ExtAddr[4], ExtAddr[5], ExtAddr[6], ExtAddr[7]);
		S2w_Printf("\r\nFrame Counter:%08x",DeviceTable.FrameCounter);
		S2w_Printf("\r\nExempt       :");
		if( DeviceTable.Exempt )
			S2w_Printf("TRUE");
		else
			S2w_Printf("FALSE");
		
		break;
		
	}
	case macSecurityLevelTable:
	{
		GSN_WLRPAN_SECURITY_LEVEL_DESC_T SecILevelTable;
		memcpy( &SecILevelTable, pCfm->Value, sizeof(SecILevelTable));
		S2w_Printf("\r\nFrame Type   :%02x",SecILevelTable.FrameType);
		S2w_Printf("\r\nCmd Frame Id :%02x",SecILevelTable.CmdFrmIdentifier);
		S2w_Printf("\r\nSecurity Min :%02x",SecILevelTable.SecIMinimum);
		S2w_Printf("\r\nDeviceOverrideSecIMinimum:");
		if( SecILevelTable.DeviceOverrideSecIMinimum )
			S2w_Printf("TRUE");
		else
			S2w_Printf("FALSE");
		break;
	}
	case macKeyIdLookupList:
	{
		GSN_WLRPAN_KEYID_LOOKUP_DESC_T LookupDesc;
		UINT8 i = 0;
		memcpy( &LookupDesc, pCfm->Value, sizeof( LookupDesc ));
		S2w_Printf("\r\nLookupData      :");
		while( i < LookupDesc.LookupDataSize )
		{
			S2w_Printf("%02x ",LookupDesc.LookupData[i]);
			i++;
		}
		S2w_Printf("\r\nLookupData Size :%02x",LookupDesc.LookupDataSize);
		break;
	}
	case macKeyDeviceList:
	{
		GSN_WLRPAN_KEY_DEVICE_DESC_T DeviceDesc;
		memcpy( &DeviceDesc, pCfm->Value, sizeof( DeviceDesc ));
		S2w_Printf("\r\nDeviceDescHandle :%02x",DeviceDesc.DeviceDescHandle);
		S2w_Printf("\r\nUniqueDevice     :");
		if( DeviceDesc.UniqueDevice )
			S2w_Printf("TRUE");
		else
			S2w_Printf("FALSE");
		S2w_Printf("\r\nBlacklisted      :");
		if( DeviceDesc.Blacklisted )
			S2w_Printf("TRUE");
		else
			S2w_Printf("FALSE");
		break;
	}
	case macKeyUsageList:
	{
		GSN_WLRPAN_KEY_USAGE_DESC_T UsageDesc;
		memcpy( &UsageDesc, pCfm->Value, sizeof(UsageDesc));
		S2w_Printf("\r\nFrame Type   :%02x",UsageDesc.FrameType);
		S2w_Printf("\r\nCmd Frame Id :%02x",UsageDesc.CmdFrmIdentifier);
		break;
	}
	case macKey:
	{
		S2w_Printf("\r\n%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
            pCfm->Value[0], pCfm->Value[1], pCfm->Value[2], pCfm->Value[3],
            pCfm->Value[4], pCfm->Value[5], pCfm->Value[6], pCfm->Value[7],
            pCfm->Value[8], pCfm->Value[9], pCfm->Value[10], pCfm->Value[11],
            pCfm->Value[12], pCfm->Value[13], pCfm->Value[14], pCfm->Value[15]);
		break;
	}

    default:
        s2w154Ctx.operationStatus = S2W_FAILURE;
        break;
    }
    
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    
    return GSN_SUCCESS;
}


GSN_STATUS 
AppS2w_WLRPANDataCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_DATA_CFM_T *pDataCfm = (GSN_WLRPAN_DATA_CFM_T *)pMsg;
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
	S2w_Printf("\r\nData Cfm Status - ");
	if( pDataCfm->Status == 0 )
    {
		S2w_Printf("Success");
    }
    else
    {
        S2w_Printf("%s", pWlrpanStatusMsg[pDataCfm->Status - WlrpanStatusOffset] );
    }
	S2w_Printf("\r\n");
    return pDataCfm->Status;
}

GSN_STATUS 
AppS2w_WLRPANDataInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_DATA_IND_T *pInd = (GSN_WLRPAN_DATA_IND_T * )pMsg;
	UINT8 len = pInd->MsduLength;
	UINT8 i = 0;
    S2w_Printf("\r\nSrc PAN Id - %x", pInd->SrcPanId );
    S2w_Printf("\r\nSrc Address - ");
    if( pInd->SrcMode == 0x02 )
    {
        S2w_Printf("%x",pInd->SrcAddr.ShortAddr);
    }
    else
    {
        S2w_Printf("%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x\r\n",
            pInd->SrcAddr.addr[0], pInd->SrcAddr.addr[1], pInd->SrcAddr.addr[2], 
            pInd->SrcAddr.addr[3], pInd->SrcAddr.addr[4], pInd->SrcAddr.addr[5], 
            pInd->SrcAddr.addr[6], pInd->SrcAddr.addr[7]);
    }
	while( i < len )
	{
		S2w_Printf("%c",pInd->Msdu[i]);
		i++;
	}
    S2w_Printf("\r\n");
	
    return GSN_SUCCESS;
}

GSN_STATUS 
AppS2w_WLRPANDataPurgeCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLRPAN_PURGE_CFM_T *pCfm = ( GSN_WLRPAN_PURGE_CFM_T *)pMsg;
	S2w_Printf("\r\nPurge Cfm Status - ");
	if( pCfm ->Status == 0 )
    {
		S2w_Printf("Success");
    }
    else
    {
        S2w_Printf("%s", pWlrpanStatusMsg[pCfm ->Status - WlrpanStatusOffset] );
    }
	S2w_Printf("\r\n");
    return pCfm->Status;
}

GSN_STATUS 
AppS2w_WLRPANData6LoWPANCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
	//GSN_6LOWPAN_DATA_IND_T *pInd = (GSN_6LOWPAN_DATA_IND_T *)pMsg;
    //if( pInd->)
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return GSN_SUCCESS;
}
GSN_STATUS 
AppS2w_WLRPANData6LoWPANInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    return GSN_SUCCESS;
}


GSN_STATUS 
AppS2w_WLRPANTmrCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLP_TMR_CFM_T *pTmrCfm = ( GSN_WLP_TMR_CFM_T *)pMsg;
    if( pTmrCfm->status == 0 )
    {
        S2w_Printf("\r\n%02x, OK\r\n", pTmrCfm->tmrNum );
    }
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return pTmrCfm->status;
}
GSN_STATUS 
AppS2w_WLRPANTmrInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    GSN_WLP_TMR_IND_T *pTmrInd = ( GSN_WLP_TMR_IND_T *)pMsg;
    S2w_Printf("\r\n%02x, EXPIRED\r\n", pTmrInd->tmrNum );    
    return GSN_SUCCESS;
}
GSN_STATUS 
AppS2w_WLRPANCb( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    S2w_Printf("\r\nCB CALLED\r\n");
    if( magId )
    {
        //S2w_Printf("\r\n%02x\r\n", s2w154Ctx.channel );
    }
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return GSN_SUCCESS;
}


PUBLIC UINT8 AppS2wCmd_I154RxTest (UINT8 *ptr)
{
    UINT8 status;
    GSN_WLP_RF_TEST_RX_START_T req;
    GSN_WLRPAN_T *pWlrpan = &s2w154Ctx.wlrpanCtx;
    UINT8 *p;
    UINT32 temp = 0;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.channel = temp;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);	
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.filter = temp;
    
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);	
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.frmLen = temp;

    status = GsnWLRPAN_GenericReq( pWlrpan, GSN_WLP_GEN_RF_TEST_RX_START, &req );
    /* [TO DO] : Print the stat values*/
    return status;

}

PUBLIC UINT8 AppS2wCmd_I154RxTestStop (UINT8 *ptr)
{
    UINT8 status;
    GSN_WLP_RF_TEST_RX_STAT_T stat;
    GSN_WLRPAN_T *pWlrpan = &s2w154Ctx.wlrpanCtx;    
    status = GsnWLRPAN_GenericReq( pWlrpan, GSN_WLP_GEN_RF_TEST_RX_STOP, &stat );

    if( status == GSN_SUCCESS )
    {
        semRelease = TRUE;
        GsnOsal_SemAcquire( &s2w154Ctx.blockingSem, GSN_OSAL_WAIT_FOREVER );
    }
    return status;
}

PUBLIC UINT8 AppS2wCmd_I154TxTest (UINT8 *ptr)
{
    UINT8 status;
    GSN_WLP_RF_TEST_TX_T req;
    GSN_WLRPAN_T *pWlrpan = &s2w154Ctx.wlrpanCtx;
    UINT8 *p;
    UINT32 temp = 0;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.channel = temp;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.numOfFrm = temp;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.frmLen = temp;

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.txPwr = temp;
    
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    status = AppS2wParse_Int(p, &temp);
    if(status != S2W_SUCCESS)
    {
        return status;
    }
    req.delay = temp;
    
    status = GsnWLRPAN_GenericReq( pWlrpan, GSN_WLP_GEN_RF_TEST_TX, &req );
    /* [TO DO] : Print the stat values*/

    return status;
}
GSN_STATUS
AppS2w_WLRPANGenCfm( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    UINT32 *pTmp = pMsg;
    UINT32 i = 0, j = msgLen >> 2;
    
    GSN_WLP_GEN_TEST_T *pCfm = (GSN_WLP_GEN_TEST_T *)pMsg;
    
    S2w_Printf("\r\nCmd Id = %02x\r\n", pTmp[0]);
    i++;
    
    /**< Check the Message Id here */
    if( pCfm->msgId == GSN_WLP_GEN_RF_TEST_RX_STOP_CFM )
    {
        /**< Print the Rx Stats */
        S2w_Printf("Pkts Received - %d\r\nBytes Received - %d",pCfm->testParam.rxStat.pktRecv,pCfm->testParam.rxStat.byteRecv);
    }
    if( pTmp[0] == 5 )
    {
        i = 2;
        while( j >= i )
        {
            S2w_Printf("Offset - %02x : %08x\r\n", (( i - 2 ) << 2 ), pTmp[i] );
            i++;
        }
    }
    GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
    return GSN_SUCCESS;
}

GSN_STATUS
AppS2w_WLRPANGenInd( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg )
{
    //UINT32 *pTmp = pMsg;
    GSN_WLP_GEN_TEST_T *pData = pMsg;
    
    switch( pData->msgId )
    {
        case GSN_WLP_GEN_RF_TEST_RX_STOP_CFM:
            S2w_Printf("No of packets received = %d\r\n", 
                pData->testParam.rxStat.pktRecv );
            S2w_Printf("No of bytes received = %d\r\n", 
                pData->testParam.rxStat.byteRecv );            
            break;            
        default:
            break;
    }
        
    
    if( semRelease == TRUE )
    {
        GsnOsal_SemRelease( &s2w154Ctx.blockingSem );
        semRelease = FALSE;
    }
    return GSN_SUCCESS;
}
