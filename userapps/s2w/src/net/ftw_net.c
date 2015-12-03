/*****************************************************************
* File Inclusions
*****************************************************************/
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "main/app_main_ctx.h"

#include "ftw_includes.h"
#include "ftw_net.h"
#include "ftw_mem.h"
#include "ftw_time.h"

#define AP_SSID "FTR-01"
#define AP_WWPA "4rnekd9wkd"

typedef struct  FTW_NET_TASK_CTX_STRUCT
{
    FTW_NET_CONFIG          xConfig;
    GSN_OSAL_THREAD_TCB_T   xTCB;
} FTW_NET_TASK_CTX;

static void     FTW_NET_task(UINT32 ulParam);
static FTW_RET  FTW_NET_connect(char_ptr pSSID, char_ptr pWWPA);

static FTW_NET_STAT     _xNetState = FTW_NET_STAT_UNINITIALIZED;
static GSN_OSAL_QUEUE_T _xNetRxQueue;
static UINT32           _xNetRxQueueBuf[ APP_CFG_NET_RX_QUEUE_MAX ];


FTW_RET FTW_NET_init(FTW_NET_CONFIG_PTR pxConfig)
{
    void                *pStack;
    FTW_NET_TASK_CTX    *pxCTX;

    pxCTX = FTW_MEM_alloc(sizeof(FTW_NET_TASK_CTX));
    if (pxCTX == NULL)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_NET, "FTW_NET_TASK_CTX creating error(Not enough memory)!\n");
        goto error;
    }
    
    pStack = FTW_MEM_alloc(FTW_NET_CFG_STACK_SIZE);
    if (pStack == NULL)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_NET, "malloc error!\n");
        goto error;
    }

    memcpy(&pxCTX->xConfig, pxConfig, sizeof(FTW_NET_CONFIG));
    
    if (GsnOsal_QueueCreate( &_xNetRxQueue, sizeof(UINT8 *), ( UINT8* )_xNetRxQueueBuf, sizeof( _xNetRxQueueBuf )) != GSN_OSAL_SUCCESS)
    {
        goto error;
    }
    
    if (GsnOsal_ThreadCreate(FTW_NET_task, pxCTX, &pxCTX->xTCB, "net", 15, pStack, FTW_NET_CFG_STACK_SIZE, GSN_OSAL_THREAD_INITIAL_READY) != GSN_OSAL_SUCCESS)
    {
        goto error;
    }

    return  FTW_RET_OK;
    
error:
    if (pxCTX != NULL)
    {
        FTW_MEM_free(pxCTX);
    }
    
    if (pStack != NULL)
    {
        FTW_MEM_free(pStack);
    }
    
    return  FTW_RET_ERROR;
}

void FTW_NET_task(UINT32 ulParam)
{
    FTW_NET_TASK_CTX  *pxCTX = (FTW_NET_TASK_CTX *)ulParam;
    UINT8               xStatus;
    
    _xNetState = FTW_NET_STAT_INITIALIZED;
    
    while(TRUE)
    {
        switch(_xNetState)
        {
        case    FTW_NET_STAT_INITIALIZED:
            {
                if (FTW_NET_connect(pxCTX->xConfig.pSSID, pxCTX->xConfig.pWWPA) == FTW_RET_OK)
                {
                    FTW_MODULE_TRACE(FTW_DBG_MODULE_NET, "connected\n");
                    _xNetState = FTW_NET_STAT_CONNECTED;
                    break;
                }
                else
                {
                    FTW_TIME_delay(5000);
                }
            }
            break;
            
        case    FTW_NET_STAT_CONNECTED:
            {
            }
            break;
            
        case    FTW_NET_STAT_STAY_CONNECTED:
            {
                S2W_WLANINFO_T xInfo;

                xStatus = AppS2wHal_InfoGet(&xInfo);
                if (xStatus != S2W_SUCCESS)
                {
                    FTW_MODULE_TRACE(FTW_DBG_MODULE_NET, "disconnected\n");
                    _xNetState = FTW_NET_STAT_DISCONNECTED;
                    break;
                }
                else
                {
                
                }
            }
            break;
            
        case    FTW_NET_STAT_DISCONNECTED:
            {
            }
            break;
            
        case    FTW_NET_STAT_CONNECTION_RETRY:
            {
            }
            break;
        }
        
        FTW_TIME_delay(0);
    }
}

FTW_NET_STAT    FTW_NET_getStat(void)
{
    return  _xNetState;
}

FTW_RET FTW_NET_connect(char_ptr pSSID, char_ptr pWWPA)
{
    UINT8   pCmdString[128];
    UINT8   xStatus;
    
    sprintf((char *)pCmdString, "AT+WWPA=%s", pWWPA);
    xStatus = AppS2wCommand_Process(pCmdString);
    if (xStatus != S2W_SUCCESS)
    {
        return  FTW_RET_CMD_FAILURE | xStatus;
    }
    
    sprintf((char *)pCmdString, "AT+WA=%s", pSSID);
    xStatus = AppS2wCommand_Process(pCmdString);
    if (xStatus != S2W_SUCCESS)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_NET, "AP connection error!\n");
        return  FTW_RET_CMD_FAILURE | xStatus;
    }
    
	return FTW_RET_OK;
}

FTW_RET FTW_NET_isConnected(void)
{
    if ((_xNetState == FTW_NET_STAT_CONNECTED) || (_xNetState == FTW_NET_STAT_STAY_CONNECTED))
    {
        return  FTW_RET_OK;
    }
    
    return  FTW_RET_ERROR;
}

/**
************************************************************************
* @ingroup FutureTek Wireless Sensor.
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
VOID    FTW_NET_rx(UINT8 cid, void *buf, UINT32 len, UINT8 *ip, UINT16 port)
{
    FTW_NET_MSG_PTR pMsg;

    s2wRxBytes += len;
    
    pMsg = (FTW_NET_MSG_PTR)FTW_MEM_allocZero(sizeof(FTW_NET_MSG) + len);
    if (pMsg != NULL)
    {
        pMsg->ulLen = len;
        memcpy(pMsg->pBuff, buf, len);        
        
        GsnOsal_QueuePut(&_xNetRxQueue, (UINT8 *)&pMsg);
    }
}

uint_32 FTW_NET_getPkt(UINT8 cid, void *pBuf, uint_32 ulBuffLen)
{
    FTW_NET_MSG_PTR     pMsg;
    uint_32             ulPktLen = 0;
    
    if (GsnOsal_QueueGet( &_xNetRxQueue, ( UINT8* )&pMsg, GSN_OSAL_NO_WAIT ) == GSN_SUCCESS)
    {
        if (ulBuffLen > pMsg->ulLen)
        {
            ulPktLen = pMsg->ulLen;
        }
        else
        {
            ulPktLen = ulBuffLen;
        }
        
        memcpy(pBuf, pMsg->pBuff, ulPktLen);
        
        FTW_MEM_free(pMsg);
    }
        
    return  ulPktLen;

}


