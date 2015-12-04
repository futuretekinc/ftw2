/*****************************************************************
* File Inclusions
*****************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "gsn_includes.h"
#include "app_defines_builder.h"
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
#include "parser/s2w_process.h"
#include "clk_tune/app_clk_tune.h"

#include "ftw_includes.h"
#include "ftw_net.h"

extern UINT8 curCid;
extern S2W_CID_T s2wCidList[];

PRIVATE S2W_IPADDR_T destAddr;
PRIVATE UINT16 destPort;

PUBLIC GSN_OSAL_QUEUE_T appS2wNetRxQueue;
PRIVATE UINT32 appS2wNetRxQueueBuf[ APP_CFG_NET_RX_QUEUE_MAX ];

/**
************************************************************************
* @ingroup S2w-Application.
* @brief Receive data from a network connection.
* @param cid - IN connection identifier on which the data is received.
* @param buf - IN Pointer to data buffer.
* @param len - IN Total number of bytes.
* @param ip  - IN IP address of the client from which the data was received
*                    (only for UDP servers)
* @param port- IN Port of the client from which the data was received (only
*                 for UDP servers)
* @retval VOID - none.
************************************************************************/
PUBLIC VOID
AppS2wProcess_NetRx(UINT8 cid, void *buf, UINT32 len, UINT8 *ip, UINT16 port)
{
    static  int  bQueueCreated = 0;
    s2wRxBytes += len;
    FTW_TRACE("AppS2wProcess_NetRx(%d, pBuff, %d,..) \n", cid, len);
    
    if (!bQueueCreated)
    {
		GsnOsal_QueueCreate( &appS2wNetRxQueue, 1,
								( UINT8* )appS2wNetRxQueueBuf,
								sizeof( appS2wNetRxQueueBuf ));
    
    }

    FTW_NET_MSG_PTR pMsg;
    
    pMsg = (FTW_NET_MSG_PTR)FTW_MEM_allocZero(sizeof(FTW_NET_MSG) + len);
    if (pMsg != NULL)
    {
        pMsg->ulLen = len;
        memcpy(pMsg->pBuff, buf, len);        
        
        GsnOsal_QueuePut(&appS2wNetRxQueue, (UINT8 *)pMsg);
    }
}

uint_32
FTW_NET_getPacket(UINT8 cid, void *pBuf, uint_32 ulBuffLen)
{
    FTW_NET_MSG_PTR pMsg;
    uint_32 ulPktLen = 0;
    
    if (GsnOsal_QueueGet( &appS2wNetRxQueue, ( UINT8* )&pMsg, GSN_OSAL_NO_WAIT ) == GSN_SUCCESS)
    {
        if (ulBuffLen > pMsg->ulLen)
        {
            memcpy(pBuf, pMsg->pBuff, pMsg->ulLen);
            ulPktLen = pMsg->ulLen;
        }
        else
        {
            memcpy(pBuf, pMsg->pBuff, ulBuffLen);
            ulPktLen = ulBuffLen;
        }
        
        FTW_MEM_free(pMsg);
    }
    
    return  ulPktLen;

}


