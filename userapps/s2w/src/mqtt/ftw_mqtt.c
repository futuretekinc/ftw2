#include "ftw_includes.h"
#include "ftw_net.h"
#include "ftw_mqtt.h"
#include "ftw_mem.h"
#include "nxjson.h"
#include "s2w_cert_mgmt.h"

typedef struct
{
    char_ptr    pTopic;
    char_ptr    pMsg;
    int_8       nRetry;
    uint_8      nQoS;
    uint_8      pData[];
}   FTW_MQTT_SEND_MSG, _PTR_ FTW_MQTT_SEND_MSG_PTR;

typedef struct
{
    uint_8      nCmd;
    uint_8      nTarget;
    uint_32     ulDataLen;
    uint_8      pData[];
}   FTW_MQTT_MSG, _PTR_ FTW_MQTT_MSG_PTR;

typedef struct
{
    FTW_MQTT_STATE  xState;
    uint_32         (*callback)(FTW_MQTT_CTX_PTR);
}   FTW_MQTT_STATE_CALLBACK, _PTR_ FTW_MQTT_STATE_CALLBACK_PTR;

typedef struct
{
    uint_32     ulMsgID;
    uint_32     (*callback)(FTW_MQTT_CTX_PTR);
}   FTW_MQTT_MSG_CALLBACK, _PTR_ FTW_MQTT_MSG_CALLBACK_PTR;

typedef struct
{
    uint_16                 nMsgID;
    uint_32                 nMsgType;    
    FTW_TIME                xTime;
    FTW_MQTT_SEND_MSG_PTR   pMsg;
}   FTW_MQTT_TRANS, _PTR_ FTW_MQTT_TRANS_PTR;


static uint_32 FTW_MQTT_publishEP(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_MSG_TYPE xMsgType, FTW_OBJECT_ID xEPID, uint_32 nQoS);

static void     FTW_MQTT_process(uint_32 ulParam);
static void     FTW_MQTT_receiver(uint_32 ulParam);
static void     FTW_MQTT_sender(uint_32 ulParam);
static void     FTW_MQTT_test(uint_32 ulParam);

static uint_32  FTW_MQTT_initSocket(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_connect(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_disconnect(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_recvPacket(FTW_MQTT_CTX_PTR pxCTX, uint_32  ulTimeout);
static int      FTW_MQTT_closeSocket(FTW_MQTT_CTX_PTR pxCTX);

static int      FTW_MQTT_sendPacket(void* pSocketInfo, void const * pBuf, unsigned int ulCount);

static FTW_RET  FTW_MQTT_TRANS_create(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_TRANS_PTR _PTR_ ppTrans);
static FTW_RET  FTW_MQTT_TRANS_destroy(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_TRANS_PTR pTrans);
static FTW_RET  FTW_MQTT_TRANS_push(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_TRANS_PTR pTrans);
static FTW_RET  FTW_MQTT_TRANS_get(FTW_MQTT_CTX_PTR pxCTX, uint_16 nMsgID, FTW_MQTT_TRANS_PTR _PTR_ ppTrans);
       FTW_RET  FTW_MQTT_TRANS_checkTimeout(FTW_MQTT_CTX_PTR pxCTX, uint_32 ulTimeout);

static uint_32  FTW_MQTT_STATE_CB_uninitialized(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_STATE_CB_initialized(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_STATE_CB_connected(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_STATE_CB_disconnected(FTW_MQTT_CTX_PTR pxCTX);

static uint_32  FTW_MQTT_MSG_CB_undefined(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_connectionACK(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_publish(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_publishACK(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_publishReceived(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_publishCompleted(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_subscribe(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_subscribeACK(FTW_MQTT_CTX_PTR pxCTX);
static uint_32  FTW_MQTT_MSG_CB_PINGResponse(FTW_MQTT_CTX_PTR pxCTX);

static uint_32  FTW_MQTT_MSG_create(uint_8 nCmd, uint_8 nTarget, uint_8_ptr pData, uint_32 ulDataLen, FTW_MQTT_MSG_PTR _PTR_ ppMsg);
static uint_32  FTW_MQTT_MSG_processing(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_MSG_PTR pMsg);
static uint_32  FTW_MQTT_MSG_destroy(FTW_MQTT_MSG_PTR pMsg);

static FTW_RET  FTW_MQTT_send(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_SEND_MSG_PTR pMsg);

static uint_32  FTW_MQTT_PING_send(FTW_MQTT_CTX_PTR pxCTX);
static void     FTW_MQTT_PING_timeout(ULONG ulParam);

static char_ptr             FTW_MQTT_MSG_TYPE_string(FTW_MQTT_MSG_TYPE xMsgType);

static FTW_MQTT_METHOD_PTR  FTW_MQTT_METHOD_get(char_ptr pString);

const FTW_MQTT_STATE_CALLBACK _pStateCBs[] =
{
    {   
        .xState     = FTW_MQTT_STATE_UNINITIALIZED,
        .callback   = FTW_MQTT_STATE_CB_uninitialized
    },
    {   
        .xState     = FTW_MQTT_STATE_INITIALIZED,
        .callback   = FTW_MQTT_STATE_CB_initialized
    },
    {   
        .xState     = FTW_MQTT_STATE_CONNECTED,
        .callback   = FTW_MQTT_STATE_CB_connected
    },
    {   
        .xState     = FTW_MQTT_STATE_DISCONNECTED,
        .callback   = FTW_MQTT_STATE_CB_disconnected
    },
    
};
const uint_32   _ulStateCBCount = sizeof(_pStateCBs) / sizeof(FTW_MQTT_STATE_CALLBACK);

const FTW_MQTT_MSG_CALLBACK   _pMsgCBs[] = 
{
    {   .ulMsgID = 0,                   .callback = FTW_MQTT_MSG_CB_undefined       },
    {   .ulMsgID = MQTT_MSG_CONNECT,    .callback = FTW_MQTT_MSG_CB_undefined       },
    {   .ulMsgID = MQTT_MSG_CONNACK,    .callback = FTW_MQTT_MSG_CB_connectionACK   },
    {   .ulMsgID = MQTT_MSG_PUBLISH,    .callback = FTW_MQTT_MSG_CB_publish         },
    {   .ulMsgID = MQTT_MSG_PUBACK,     .callback = FTW_MQTT_MSG_CB_publishACK      },
    {   .ulMsgID = MQTT_MSG_PUBREC,     .callback = FTW_MQTT_MSG_CB_publishReceived },
    {   .ulMsgID = MQTT_MSG_PUBREL,     .callback = FTW_MQTT_MSG_CB_undefined       },
    {   .ulMsgID = MQTT_MSG_PUBCOMP,    .callback = FTW_MQTT_MSG_CB_publishCompleted},
    {   .ulMsgID = MQTT_MSG_SUBSCRIBE,  .callback = FTW_MQTT_MSG_CB_subscribe       },
    {   .ulMsgID = MQTT_MSG_SUBACK,     .callback = FTW_MQTT_MSG_CB_subscribeACK    },
    {   .ulMsgID = MQTT_MSG_UNSUBSCRIBE,.callback = FTW_MQTT_MSG_CB_undefined       },
    {   .ulMsgID = MQTT_MSG_UNSUBACK,   .callback = FTW_MQTT_MSG_CB_undefined       },
    {   .ulMsgID = MQTT_MSG_PINGREQ,    .callback = FTW_MQTT_MSG_CB_undefined       },
    {   .ulMsgID = MQTT_MSG_PINGRESP,   .callback = FTW_MQTT_MSG_CB_PINGResponse    },
    {   .ulMsgID = MQTT_MSG_DISCONNECT, .callback = FTW_MQTT_MSG_CB_undefined       }
};

static FTW_MQTT_METHOD _pThingPlusMethods[];

const uint_32   _ulMsgCBCount = sizeof(_pMsgCBs) / sizeof(FTW_MQTT_MSG_CALLBACK);

uint_32 FTW_MQTT_init(FTW_MQTT_CONFIG_PTR pConfig)
{
    ASSERT(pConfig != NULL);
    int i;
    FTW_MQTT_TRANS_PTR  pTrans; 
    FTW_MQTT_CTX_PTR    pxCTX = NULL;

    pxCTX = (FTW_MQTT_CTX_PTR)FTW_MEM_allocZero(sizeof(FTW_MQTT_CTX));
    if (pxCTX == NULL)
    {
        return  FTW_RET_NOT_ENOUGH_MEMORY;
    }
    
    pxCTX->pxProcessTCB = (GSN_OSAL_THREAD_TCB_T *)FTW_MEM_allocZero(sizeof(GSN_OSAL_THREAD_TCB_T));
    if (pxCTX->pxProcessTCB == NULL)
    {
        goto error;
    }
    
    pxCTX->pProcessStack = (uint_8 *)FTW_MEM_allocZero(FTW_MQTT_CFG_STACK_SIZE);
    if (pxCTX->pProcessStack == NULL)
    {
        goto error;
    }
    
    pxCTX->pxReceiverTCB = (GSN_OSAL_THREAD_TCB_T *)FTW_MEM_allocZero(sizeof(GSN_OSAL_THREAD_TCB_T));
    if (pxCTX->pxReceiverTCB == NULL)
    {
        goto error;
    }
    
    pxCTX->pReceiverStack = (uint_8 *)FTW_MEM_allocZero(FTW_MQTT_CFG_STACK_SIZE);
    if (pxCTX->pReceiverStack == NULL)
    {
        goto error;
    }
    
    pxCTX->pxSenderTCB = (GSN_OSAL_THREAD_TCB_T *)FTW_MEM_allocZero(sizeof(GSN_OSAL_THREAD_TCB_T));
    if (pxCTX->pxSenderTCB == NULL)
    {
        goto error;
    }
    
    pxCTX->pSenderStack = (uint_8 *)FTW_MEM_allocZero(FTW_MQTT_CFG_STACK_SIZE);
    if (pxCTX->pSenderStack == NULL)
    {
        goto error;
    }
    
    pxCTX->pxTestTCB = (GSN_OSAL_THREAD_TCB_T *)FTW_MEM_allocZero(sizeof(GSN_OSAL_THREAD_TCB_T));
    if (pxCTX->pxTestTCB == NULL)
    {
        goto error;
    }
    
    pxCTX->pTestStack = (uint_8 *)FTW_MEM_allocZero(FTW_MQTT_CFG_STACK_SIZE);
    if (pxCTX->pTestStack == NULL)
    {
        goto error;
    }
    
    if (strlen(pConfig->pClientID) == 0)
    {
        snprintf(pConfig->pClientID, FTW_MQTT_CLIENT_ID_LENGTH, "%s", "1234");
    }
    
    GsnOsal_SemCreate(&pxCTX->xLock, 1);
    
    FTW_LIST_init(&pxCTX->xTransList);
    FTW_LIST_init(&pxCTX->xFreeTransList);
    FTW_LIST_init(&pxCTX->xRecvMsgPool);
    FTW_LIST_init(&pxCTX->xSendMsgPool);    
        
    pxCTX->nSocketID = 0;
    pxCTX->xState    = FTW_MQTT_STATE_UNINITIALIZED;
    memcpy(&pxCTX->xConfig, pConfig, sizeof(FTW_MQTT_CONFIG));
    pxCTX->ulBuffSize= FTW_MQTT_RECV_BUFF_SIZE;
    pxCTX->xStatistics.ulTransTimeout = 0;

    mqtt_init(&pxCTX->xBroker, pConfig->pClientID);
    
    if (pConfig->xBroker.xAuth.bEnabled)
    {
        mqtt_init_auth(&pxCTX->xBroker, pConfig->xBroker.xAuth.pUserName, pConfig->xBroker.xAuth.pPassword);
    }

    for(i = 0 ; i < FTW_MQTT_TRANS_COUNT ; i++)
    {
        pTrans = FTW_MEM_allocZero(sizeof(FTW_MQTT_TRANS));
        if (pTrans != NULL)
        {
            FTW_LIST_pushBack(&pxCTX->xFreeTransList, pTrans);
        }
    }
    
    tx_timer_create(&pxCTX->xPingTimer, "mqtt_ping", FTW_MQTT_PING_timeout, (uint_32)pxCTX, 0, 0, TX_NO_ACTIVATE);
    
    GsnOsal_ThreadCreate(FTW_MQTT_process, pxCTX, pxCTX->pxProcessTCB, "MQTT-P", 15, pxCTX->pProcessStack, FTW_MQTT_CFG_STACK_SIZE, GSN_OSAL_THREAD_INITIAL_READY);
    GsnOsal_ThreadCreate(FTW_MQTT_receiver, pxCTX, pxCTX->pxReceiverTCB, "MQTT-R", 15, pxCTX->pReceiverStack, FTW_MQTT_CFG_STACK_SIZE, GSN_OSAL_THREAD_INITIAL_READY);
    GsnOsal_ThreadCreate(FTW_MQTT_sender, pxCTX, pxCTX->pxSenderTCB, "MQTT-S", 15, pxCTX->pSenderStack, FTW_MQTT_CFG_STACK_SIZE, GSN_OSAL_THREAD_INITIAL_READY);
    GsnOsal_ThreadCreate(FTW_MQTT_test, pxCTX, pxCTX->pxTestTCB, "MQTT-T", 15, pxCTX->pTestStack, FTW_MQTT_CFG_STACK_SIZE, GSN_OSAL_THREAD_INITIAL_READY);
    
    return  FTW_RET_OK;
error:
    
    if (pxCTX != NULL)
    {
        if (pxCTX->pxProcessTCB != NULL)
        {
            FTW_MEM_free(pxCTX->pxProcessTCB);
            pxCTX->pxProcessTCB = NULL;
        }

        if (pxCTX->pxReceiverTCB != NULL)
        {
            FTW_MEM_free(pxCTX->pxReceiverTCB);
            pxCTX->pxReceiverTCB = NULL;
        }

        if (pxCTX->pxSenderTCB != NULL)
        {
            FTW_MEM_free(pxCTX->pxSenderTCB);
            pxCTX->pxSenderTCB = NULL;
        }

        if (pxCTX->pxTestTCB != NULL)
        {
            FTW_MEM_free(pxCTX->pxTestTCB);
            pxCTX->pxTestTCB = NULL;
        }

        if (pxCTX->pProcessStack != NULL)
        {
            FTW_MEM_free(pxCTX->pProcessStack);
            pxCTX->pProcessStack = NULL;
        }

        if (pxCTX->pReceiverStack != NULL)
        {
            FTW_MEM_free(pxCTX->pReceiverStack);
            pxCTX->pReceiverStack = NULL;
        }

        if (pxCTX->pSenderStack != NULL)
        {
            FTW_MEM_free(pxCTX->pSenderStack);
            pxCTX->pSenderStack = NULL;
        }

        if (pxCTX->pTestStack != NULL)
        {
            FTW_MEM_free(pxCTX->pTestStack);
            pxCTX->pTestStack = NULL;
        }

        FTW_MEM_free(pxCTX);
    }
    
    return  FTW_RET_ERROR;
}    

void FTW_MQTT_process(uint_32 ulParam)
{
    FTW_MQTT_CTX_PTR    pxCTX = (FTW_MQTT_CTX_PTR)ulParam;
    FTW_MQTT_STATE      xOldState = FTW_MQTT_STATE_UNINITIALIZED;

    xOldState = pxCTX->xState;
    while(1)
    {
        
        if (pxCTX->xState < _ulStateCBCount)
        {   
            _pStateCBs[pxCTX->xState].callback(pxCTX);
            if (pxCTX->xState != xOldState)
            {
                FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "STATE CHANGED : %d -> %d\n", xOldState, pxCTX->xState);
                xOldState = pxCTX->xState;
            }
        }
        
        FTW_TIME_delay(1000);

    }
}

void FTW_MQTT_receiver(uint_32 ulParam)
{
    FTW_MQTT_CTX_PTR    pxCTX = (FTW_MQTT_CTX_PTR)ulParam;

    while(1)
    {
        if (FTW_NET_isConnected() == FTW_RET_OK)
        {        
            if (FTW_LIST_count(&pxCTX->xRecvMsgPool) != 0)
            {
                FTW_MQTT_MSG_PTR    pMsg;
                
                if (FTW_LIST_popFront(&pxCTX->xRecvMsgPool, (pointer _PTR_)&pMsg) == FTW_RET_OK)
                {
                    FTW_MQTT_MSG_processing(pxCTX, pMsg);
                    FTW_MQTT_MSG_destroy(pMsg);
                }
            }

        }
        FTW_TIME_delay(100);
    }
}

void FTW_MQTT_sender(uint_32 ulParam)
{
    FTW_MQTT_CTX_PTR    pxCTX = (FTW_MQTT_CTX_PTR)ulParam;

    while(1)
    {
        if (FTW_NET_isConnected() == FTW_RET_OK)
        {        
            if (FTW_LIST_count(&pxCTX->xSendMsgPool) != 0)
            {
                FTW_MQTT_SEND_MSG_PTR pMsg;
                    
                if (FTW_LIST_popFront(&pxCTX->xSendMsgPool, (pointer _PTR_)&pMsg) == FTW_RET_OK)
                {
                    int_32      nRet;
                    uint_16     nMsgID;
                    
                    switch(pMsg->nQoS)
                    {
                    case    FTW_MQTT_QOS_0:
                        {
                            nRet = mqtt_publish(&pxCTX->xBroker, pMsg->pTopic, pMsg->pMsg, 0);
                            FTW_MEM_free(pMsg);
                            if (nRet == 0)
                            {
                                FTW_MQTT_disconnect(pxCTX);
                                break;
                            }
                        }
                        break;
                        
                    case    FTW_MQTT_QOS_1:
                    case    FTW_MQTT_QOS_2:
                       {
                           FTW_MQTT_TRANS_PTR   pTrans;
                           
                            if (FTW_RET_OK != FTW_MQTT_TRANS_create(pxCTX, &pTrans))
                            {
                                FTW_MEM_free(pMsg);
                                break;
                            }    
                            
                            nRet = mqtt_publish_with_qos(&pxCTX->xBroker, pMsg->pTopic, pMsg->pMsg, 0, pMsg->nQoS, &nMsgID);            
                            if (nRet == 0)
                            {
                                FTW_MQTT_TRANS_destroy(pxCTX, pTrans);
                                FTW_MQTT_disconnect(pxCTX);
                                FTW_MEM_free(pMsg);
                                break;
                            }
                            else if (nRet < 0)
                            {
                                FTW_MQTT_TRANS_destroy(pxCTX, pTrans);
                                FTW_MEM_free(pMsg);
                                break;
                            }
                            
                            pTrans->nMsgID  = nMsgID;
                            pTrans->nMsgType= MQTT_MSG_PUBLISH;
                            pTrans->pMsg    = pMsg;
                            FTW_MQTT_TRANS_push(pxCTX, pTrans);
                        }
                        break;
                    }
                                        
                }
            }
        }
        FTW_TIME_delay(100);
    }
}

uint_32 FTW_MQTT_connect(FTW_MQTT_CTX_PTR pxCTX)
{
    int_32 nRet;
	struct sockaddr_in socket_address;
    int     nFlag = 1;

    ASSERT(pxCTX != NULL);
    
    if (pxCTX->xState != FTW_MQTT_STATE_INITIALIZED)
    {
        return  FTW_RET_OPERATION_NOT_PERMITTED;
    }

    S2W_NETDATA_T       xPeerData;
    
    xPeerData.port      = pxCTX->xConfig.xBroker.xServer.usPort;
    memcpy(xPeerData.ipAddr, pxCTX->xConfig.xBroker.xServer.xIPAddress, sizeof(xPeerData.ipAddr));
    xPeerData.proto = S2W_NETDATA_PROTO_TCP;
    xPeerData.mode  = S2W_NETDATA_MODE_CLIENT;
    
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "Try connection to broker.\n");
    UINT8 xRet = AppS2wHal_NetTcpClient(&xPeerData, &pxCTX->xCID);
    if(xRet != S2W_SUCCESS)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "AppS2wHal_NetTcpClient(...) = %d\n", xRet);
        goto error;
    }

    FTW_TIME_delay(1000);
    
    if (AppS2w_SslClientOpen(pxCTX->xCID, "ca-cert", NULL, NULL) != S2W_SUCCESS)
    {
 /*       
    UINT8   pCID[16];
    sprintf(pCID, "%u", pxCTX->xCID);
    xRet = AppS2wCmd_SSLOpen(pCID);
    if(xRet != S2W_SUCCESS)
	{
    */
        AppS2wHal_NetClose(pxCTX->xCID);
		FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "SSL connection failed.");
		goto error;
	}
    
    // >>>>> CONNECT
    if (mqtt_connect(&pxCTX->xBroker) <= 0)
    {    
        FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "MQTT connection failed\n");
        goto error;
    }
    
    pxCTX->ulPingRetry = 0;
    tx_timer_deactivate(&pxCTX->xPingTimer);
    pxCTX->xState = FTW_MQTT_STATE_CONNECTED;
    
    return  FTW_RET_OK;
    
error:
    return  FTW_RET_ERROR;
    
}


FTW_RET FTW_MQTT_subscribe(FTW_MQTT_CTX_PTR pxCTX, char *pTopic)
{    
    FTW_RET             ulRet;
    int                 nRet;
    uint_16             nMsgID;
    FTW_MQTT_TRANS_PTR  pTrans;
    
    ASSERT(pxCTX != NULL);

    ulRet = FTW_MQTT_TRANS_create(pxCTX, &pTrans);
    if (ulRet != FTW_RET_OK)
    {
        return  ulRet;
    }    
    
    nRet = mqtt_subscribe(&pxCTX->xBroker, pTopic, &nMsgID);
    if (nRet == 0)
    {
        return  FTW_RET_TCP_CONN_ABORTED;
    }
    else if (nRet < 0)
    {
        return  FTW_RET_USBSCRIBE_ERROR;
    }

    pTrans->nMsgID  = nMsgID;
    pTrans->nMsgType= MQTT_MSG_SUBSCRIBE;
    
    FTW_MQTT_TRANS_push(pxCTX, pTrans);    

    return  FTW_RET_OK;
}


uint_32 FTW_MQTT_disconnect(FTW_MQTT_CTX_PTR pxCTX)
{
    tx_timer_deactivate(&pxCTX->xPingTimer);
    mqtt_disconnect(&pxCTX->xBroker);
    
    
    if (pxCTX->nSocketID != 0)
    {
        // XTRA
        //shutdown(pxCTX->nSocketID, 2);
        pxCTX->nSocketID = 0;
    }
    
    pxCTX->xState = FTW_MQTT_STATE_DISCONNECTED;
    
    return  FTW_RET_OK;
}

int FTW_MQTT_sendPacket(void* pSocketInfo, void const * pBuf, unsigned int ulCount)
{
    FTW_MQTT_CTX_PTR    pxCTX = (FTW_MQTT_CTX_PTR)pSocketInfo;
    
    ASSERT((pxCTX != NULL) && (pBuf != NULL));
    
    if (AppS2wHal_NetTx(pxCTX->xCID, NULL, 0, (void *)pBuf, ulCount) == S2W_SUCCESS)
    {
        FTW_TIME_get(&pxCTX->xTime);
        return  ulCount;
    }

    return  0;
}

uint_32     FTW_MQTT_publish(FTW_MQTT_CTX_PTR pxCTX, uint_32 nQoS, char *pTopic, char *pData)
{
    FTW_MQTT_SEND_MSG_PTR   pMsg;
    
    ASSERT (pxCTX != NULL);
    
    if (pxCTX->xState != FTW_MQTT_STATE_CONNECTED)
    {
        return  FTW_RET_NOT_CONNECTED;
    }
    
    pMsg = (FTW_MQTT_SEND_MSG_PTR)FTW_MEM_allocZero(sizeof(FTW_MQTT_SEND_MSG) + strlen(pTopic) + strlen(pData) + 2);
    if (pMsg != NULL)
    {
        
        pMsg->nQoS  = nQoS;
        pMsg->nRetry= 0;
        pMsg->pTopic= (char_ptr)pMsg->pData;
        strcpy(pMsg->pTopic, pTopic);
        
        pMsg->pMsg  = (char_ptr)&pMsg->pData[strlen(pTopic) + 1];                
        strcpy(pMsg->pMsg, pData);
        
        FTW_MQTT_send(pxCTX, pMsg);

    }
    return  FTW_RET_OK;
}

FTW_RET FTW_MQTT_send(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_SEND_MSG_PTR pMsg)
{    
    if (++pMsg->nRetry >= FTW_MQTT_CFG_RESEND_MAX)
    {
        return  FTW_RET_RETRY_EXCEED;
    }
    
    if (FTW_LIST_pushBack(&pxCTX->xSendMsgPool, pMsg) != FTW_RET_OK)
    {
        pxCTX->xStatistics.ulPublishedErrorCount++;
        return  FTW_RET_ERROR;
    }

    pxCTX->xStatistics.ulPublishedCount++;

    return  FTW_RET_OK;
}


uint_32  FTW_MQTT_initSocket(FTW_MQTT_CTX_PTR pxCTX)
{
	// MQTT stuffs
    mqtt_set_alive(&pxCTX->xBroker, pxCTX->xConfig.xBroker.xKeepalive.ulTime);

    pxCTX->xBroker.socket_info = (void*)pxCTX;
    pxCTX->xBroker.send = FTW_MQTT_sendPacket;

    pxCTX->xState = FTW_MQTT_STATE_INITIALIZED;
  
	return FTW_RET_OK;
}


int FTW_MQTT_closeSocket(FTW_MQTT_CTX_PTR pxCTX)
{
    if ((pxCTX->xState != FTW_MQTT_STATE_INITIALIZED) && (pxCTX->xState != FTW_MQTT_STATE_DISCONNECTED))
    {
        FTW_MQTT_disconnect(pxCTX);
    }
    
    pxCTX->xState = FTW_MQTT_STATE_UNINITIALIZED;

    return FTW_RET_OK;
}

uint_32 FTW_MQTT_recvPacket(FTW_MQTT_CTX_PTR pxCTX, uint_32  ulTimeout)
{
    int         nCount = 0;
    FTW_TIME    xStartTime;
    FTW_TIME    xCurrentTime;
    
	memset(pxCTX->pBuff, 0, pxCTX->ulBuffSize);
    pxCTX->ulRcvdLen = 0;
    
    FTW_TIME_get(&xStartTime);
    while(TRUE)
    {
        if(FTW_NET_getPkt(pxCTX->xCID, pxCTX->pBuff, pxCTX->ulBuffSize) > 0) 
        {
            FTW_TIME_get(&pxCTX->xTime);            
            return  FTW_RET_OK;
        }
        
        FTW_TIME_get(&xCurrentTime);
        if (FTW_TIME_diffMilliseconds(&xCurrentTime, &xStartTime) >= ulTimeout)
        {
            break;
        }
        FTW_TIME_delay(0);
    } 

    return FTW_RET_READ_ABOARTED;
}

uint_32 FTW_MQTT_PING_send(FTW_MQTT_CTX_PTR pxCTX)
{   
    FTW_TIME      xCurrentTime;
    
    FTW_TIME_get(&xCurrentTime);
    
    pxCTX->ulPingRetry++;
    tx_timer_change(&pxCTX->xPingTimer, xCurrentTime + pxCTX->ulPingRetry * 1000, 0);
    tx_timer_activate(&pxCTX->xPingTimer);

    mqtt_ping(&pxCTX->xBroker);
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "PING SEND : TIME - %d, TIMEOUT = %d secs\n", xCurrentTime, pxCTX->ulPingRetry);
    
    return  FTW_RET_OK;        
}

static void   FTW_MQTT_PING_timeout(ULONG ulParam)
{
    FTW_MQTT_CTX_PTR pxCTX = (FTW_MQTT_CTX_PTR)ulParam;
    
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "PING TIMEOUT : TIMEOUT = %d secs\n", pxCTX->ulPingRetry);
    if (pxCTX->ulPingRetry < pxCTX->xConfig.xBroker.xKeepalive.ulRetryCount)
    {
        FTW_MQTT_PING_send(pxCTX);
    }
    else
    {
        tx_timer_deactivate(&pxCTX->xPingTimer);
        FTW_MQTT_disconnect(pxCTX);
    }
}

/******************************************************************************
 * MQTT State functions
 ******************************************************************************/
static uint_32  FTW_MQTT_STATE_CB_uninitialized(FTW_MQTT_CTX_PTR pxCTX)
{
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "MQTT STATE : Uninitialized\n");
    FTW_MQTT_initSocket(pxCTX);
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_STATE_CB_initialized(FTW_MQTT_CTX_PTR pxCTX)
{
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "MQTT STATE : Initialized\n");

    if (FTW_NET_isConnected() != FTW_RET_OK)
    {
        return  FTW_RET_NET_IS_NOT_INITIALIZED;
    }
    
    return  FTW_MQTT_connect(pxCTX);
}

static uint_32  FTW_MQTT_STATE_CB_connected(FTW_MQTT_CTX_PTR pxCTX)
{
    char    pTopic[FTW_MQTT_TOPIC_LENGTH+1];
    char    pMessage[256];
    
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "MQTT STATE : Connected\n");
                                   
    sprintf(pTopic, "/v/a/g/%s/req", pxCTX->xConfig.pClientID);
    FTW_MQTT_subscribe(pxCTX, pTopic);
    
    while(pxCTX->xState == FTW_MQTT_STATE_CONNECTED)
    {
        uint_32 ulRet;
            
        ulRet = FTW_MQTT_recvPacket(pxCTX, 1000);
        if (ulRet == FTW_RET_OK)
        {
            uint_32 nMsgType;
            
            nMsgType = MQTTParseMessageType(pxCTX->pBuff) >> 4;   
            if (nMsgType < _ulMsgCBCount)
            {
                _pMsgCBs[nMsgType].callback(pxCTX);                                
            }
        }
        
        if (FTW_NET_isConnected() != FTW_RET_OK)
        {
            FTW_MQTT_disconnect(pxCTX);
            break;
        }
        
        FTW_MQTT_TRANS_checkTimeout(pxCTX, pxCTX->xConfig.ulPubTimeout);

        if (pxCTX->ulPingRetry == 0)
        {
            FTW_TIME        xCurrentTime;
            uint_32         ulTimeDiff;

            FTW_TIME_get(&xCurrentTime);                    
            ulTimeDiff = FTW_TIME_diffSeconds(&xCurrentTime, &pxCTX->xTime);            
            
             if (pxCTX->xConfig.xBroker.xKeepalive.ulTime < (uint_32)(ulTimeDiff * 1.5))
             {
                FTW_MQTT_PING_send(pxCTX);
             }
        }
    }
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_STATE_CB_disconnected(FTW_MQTT_CTX_PTR pxCTX)
{
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "MQTT STATE : Disconnected\n");
    
    FTW_MQTT_closeSocket(pxCTX);
    
    return  FTW_RET_OK;
}

/******************************************************************************
 * MQTT Command Message functions
 ******************************************************************************/
static uint_32  FTW_MQTT_MSG_CB_undefined(FTW_MQTT_CTX_PTR pxCTX)
{
    return  FTW_RET_ERROR;
}
                     
static uint_32  FTW_MQTT_MSG_CB_connectionACK(FTW_MQTT_CTX_PTR pxCTX)
{
    // <<<<< CONNACK
    
    switch(pxCTX->pBuff[3])
    {
    case    0:  break;
    case    1:  return  FTW_RET_UNACCEPTABLE_PROTOCOL_VERSION;
    case    2:  return  FTW_RET_IDENTIFIER_REJECTED;
    case    3:  return  FTW_RET_SERVER_UNAVALIABLE;
    case    4:  return  FTW_RET_BAD_USER_NAME_OR_PASSWORD;
    case    5:  return  FTW_RET_NOT_AUTHORIZED;
    default:    return  FTW_RET_ERROR;
    }

    pxCTX->xState = FTW_MQTT_STATE_CONNECTED;
    
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "MQTT Connected!\n");                        
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_MSG_CB_publish(FTW_MQTT_CTX_PTR pxCTX)
{
    FTW_RET             xRet;
    FTW_MQTT_MSG_PTR    pMsg;
    uint_8              nCmd;
    uint_8              pTopic[FTW_MQTT_TOPIC_LENGTH + 1];
    uint16_t            nTopicLen;
    uint_8 const _PTR_  pData;
    char_ptr            pFields[10];
    uint16_t            nFieldCount;
    uint16_t            nDataLen;    
    
    nTopicLen = mqtt_parse_pub_topic(pxCTX->pBuff, pTopic);
    pTopic[nTopicLen] = '\0';

    nDataLen = mqtt_parse_pub_msg_ptr(pxCTX->pBuff, &pData);

    nFieldCount = 0;
    pFields[nFieldCount] = strtok((char_ptr)pTopic, "/");
    while((pFields[nFieldCount] != NULL) && (nFieldCount < 10))
    {
        pFields[++nFieldCount] = strtok(NULL, "/");
    }

    if ((nFieldCount < 5) ||
        (strcmp(pFields[0], "v") != 0) ||
        (strcmp(pFields[1], "a") != 0) ||
        (strcmp(pFields[2], "g") != 0) ||
        (strcmp(pFields[3], "1234") != 0))
    {
        pxCTX->xStatistics.ulSubscribedErrorCount++;
        return  FTW_RET_INVALID_TOPIC;
    }

    if (strcmp(pFields[4], "req") == 0)
    {
        nCmd = FTW_MQTT_CMD_REQ;
    }
    else
    {
        pxCTX->xStatistics.ulSubscribedErrorCount++;
        return  FTW_RET_INVALID_TOPIC;
    }

    if (FTW_MQTT_MSG_create(nCmd, FTW_MQTT_TARGET_UID, (uint_8_ptr)pData, nDataLen, &pMsg) != FTW_RET_OK)
    {
        return  FTW_RET_ERROR;
    }

    xRet = FTW_LIST_pushBack(&pxCTX->xRecvMsgPool, pMsg);
    if (xRet == FTW_RET_OK)
    {
        pxCTX->xStatistics.ulSubscribedCount++;
    }
    else
    {
        pxCTX->xStatistics.ulSubscribedErrorCount++;
        FTW_MQTT_MSG_destroy(pMsg);    
    }
    
    return  xRet;
}

static uint_32  FTW_MQTT_MSG_CB_publishACK(FTW_MQTT_CTX_PTR pxCTX)
{
    uint_32             ulRet;
    FTW_MQTT_TRANS_PTR  pTrans;
    uint_32             ulMsgID;
   
    ulMsgID = mqtt_parse_msg_id(pxCTX->pBuff);
    ulRet = FTW_MQTT_TRANS_get(pxCTX, ulMsgID, &pTrans);
    if (ulRet != FTW_RET_OK)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%d message id was expected, but it is unknown id !\n", ulMsgID);                    
        return  ulRet;
    }
    
    FTW_MQTT_TRANS_destroy(pxCTX, pTrans);
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_MSG_CB_publishReceived(FTW_MQTT_CTX_PTR pxCTX)
{
    uint_32             ulRet;
    FTW_MQTT_TRANS_PTR  pTrans;
    uint_32             ulMsgID;
    
    ulMsgID = mqtt_parse_msg_id(pxCTX->pBuff);
   
    ulRet = FTW_MQTT_TRANS_get(pxCTX, ulMsgID, &pTrans);
    if (ulRet != FTW_RET_OK)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%d message id was expected, but it is unknown id !\n", ulMsgID);                    
        return  ulRet;
    }
    
    mqtt_pubrel(&pxCTX->xBroker, ulMsgID);
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_MSG_CB_publishCompleted(FTW_MQTT_CTX_PTR pxCTX)
{
    uint_32             ulRet;
    FTW_MQTT_TRANS_PTR  pTrans;
    uint_32             ulMsgID;
    
    ulMsgID = mqtt_parse_msg_id(pxCTX->pBuff);

    ulRet = FTW_MQTT_TRANS_get(pxCTX, ulMsgID, &pTrans);
    if (ulRet != FTW_RET_OK)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%d message id was expected, but it is unknown id !\n", ulMsgID);                    
        return  ulRet;
    }

    FTW_MQTT_TRANS_destroy(pxCTX, pTrans);                
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_MSG_CB_subscribe(FTW_MQTT_CTX_PTR pxCTX)
{

    FTW_MQTT_MSG_CB_subscribeACK(pxCTX);
        
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_MSG_CB_subscribeACK(FTW_MQTT_CTX_PTR pxCTX)
{
    uint_32             ulRet;
    FTW_MQTT_TRANS_PTR  pTrans;
    uint_32             ulMsgID;
    
    ulMsgID = mqtt_parse_msg_id(pxCTX->pBuff);

    ulRet = FTW_MQTT_TRANS_get(pxCTX, ulMsgID, &pTrans);
    if (ulRet != FTW_RET_OK)
    {
        FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%d message id was expected, but it is unknown id !\n", ulMsgID);                    
        return  ulRet;
    }
    
    FTW_MQTT_TRANS_destroy(pxCTX, pTrans);
    
    pxCTX->xState = FTW_MQTT_STATE_CONNECTED;
    
    return  FTW_RET_OK;
}

static uint_32  FTW_MQTT_MSG_CB_PINGResponse(FTW_MQTT_CTX_PTR pxCTX)
{
    tx_timer_deactivate(&pxCTX->xPingTimer);
    pxCTX->ulPingRetry = 0;   
    
    return  FTW_RET_OK;
}


/******************************************************************************
 * Internal functions
 ******************************************************************************/
FTW_RET FTW_MQTT_TRANS_create(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_TRANS_PTR _PTR_ ppTrans)
{
    FTW_RET             ulRet;
    FTW_MQTT_TRANS_PTR  pTrans;
        
    if (FTW_LIST_count(&pxCTX->xFreeTransList) != 0)
    {
        ulRet = FTW_LIST_popFront(&pxCTX->xFreeTransList, (pointer _PTR_)&pTrans);
        if (ulRet != FTW_RET_OK)
        {
            FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "Not enough memory!\n");
            return  FTW_RET_NOT_ENOUGH_MEMORY;
        }
    }
    else
    {
        pTrans = (FTW_MQTT_TRANS_PTR)FTW_MEM_allocZero(sizeof(FTW_MQTT_TRANS));
        if (pTrans == NULL)
        {
            FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "Not enough memory!\n");
            return  FTW_RET_NOT_ENOUGH_MEMORY;
        }
    }
    
    FTW_TIME_get(&pTrans->xTime);

    *ppTrans = pTrans;
    
    return  FTW_RET_OK;
}

FTW_RET FTW_MQTT_TRANS_destroy(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_TRANS_PTR pTrans)
{
    FTW_LIST_remove(&pxCTX->xTransList, pTrans);
    if (pTrans->pMsg != NULL)
    {
        FTW_MEM_free(pTrans->pMsg);
        pTrans->pMsg = NULL;
    }
    
    FTW_LIST_pushBack(&pxCTX->xFreeTransList, pTrans);
    
    return  FTW_RET_OK;
}

FTW_RET FTW_MQTT_TRANS_push(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_TRANS_PTR pTrans)
{
    FTW_LIST_pushBack(&pxCTX->xTransList, pTrans);
    
    return  FTW_RET_OK;
}

uint_32 FTW_MQTT_TRANS_get(FTW_MQTT_CTX_PTR pxCTX, uint_16 nMsgID, FTW_MQTT_TRANS_PTR _PTR_ ppTrans)
{
    FTW_MQTT_TRANS_PTR  pTrans;    

    GsnOsal_SemAcquire(&pxCTX->xLock, TX_WAIT_FOREVER);

    for(int i = 0 ; i < FTW_LIST_count(&pxCTX->xTransList) ; i++)
    {
        pTrans = FTW_LIST_getAt(&pxCTX->xTransList, i);
        if (pTrans->nMsgID == nMsgID)
        {
            *ppTrans = pTrans;
            GsnOsal_SemRelease(&pxCTX->xLock);
            return  FTW_RET_OK;
        }
    }

    GsnOsal_SemRelease(&pxCTX->xLock);
    return  FTW_RET_ERROR;
}

FTW_RET FTW_MQTT_TRANS_checkTimeout(FTW_MQTT_CTX_PTR pxCTX, uint_32 ulTimeout)
{
    FTW_MQTT_TRANS_PTR  pTrans;    
    FTW_TIME            xTime;
    
    FTW_TIME_get(&xTime);
    
    GsnOsal_SemAcquire(&pxCTX->xLock, TX_WAIT_FOREVER);
    for(int i = 0 ; i < FTW_LIST_count(&pxCTX->xTransList) ; i++)
    {
        ULONG   ulDiffTime;
        
        pTrans = FTW_LIST_getAt(&pxCTX->xTransList, i);
        ulDiffTime = FTW_TIME_diffMilliseconds(&xTime, &pTrans->xTime);
        
        if ( ulDiffTime > ulTimeout)
        {
            FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "Transaction timeout - %4d, %4d ms\n", pTrans->nMsgID, ulDiffTime);
            if (FTW_MQTT_send(pxCTX, pTrans->pMsg) != FTW_RET_OK)
            {
                FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "Max retry exceed - %4d\n", pTrans->nMsgID);
            }
            else
            {
                pTrans->pMsg = NULL;
            }
            FTW_MQTT_TRANS_destroy(pxCTX, pTrans);
            break;
        }
    }
    
    GsnOsal_SemRelease(&pxCTX->xLock);

    return  FTW_RET_OK;
}

uint_32 FTW_MQTT_MSG_create
(
    uint_8      nCmd, 
    uint_8      nTarget, 
    uint_8_ptr  pData, 
    uint_32     ulDataLen, 
    FTW_MQTT_MSG_PTR _PTR_ ppMsg
)
{
    FTW_MQTT_MSG_PTR    pMsg;
    
    pMsg = (FTW_MQTT_MSG_PTR)FTW_MEM_allocZero(sizeof(FTW_MQTT_MSG) + ulDataLen + 1);
    if (pMsg == NULL)
    {
        return  FTW_RET_ERROR;
    }
    
    pMsg->nCmd = nCmd;
    pMsg->nTarget = nTarget;
    memcpy(pMsg->pData, pData, ulDataLen);
    pMsg->ulDataLen  = ulDataLen;
    
    *ppMsg = pMsg;
    
    return  FTW_RET_OK;
}

uint_32 FTW_MQTT_MSG_processing(FTW_MQTT_CTX_PTR pxCTX, FTW_MQTT_MSG_PTR pMsg)
{
    const nx_json* pRoot = NULL;
    
    if (pMsg->nCmd == FTW_MQTT_CMD_REQ)
    {
        static char pBuff[2048];
        
        memcpy(pBuff, pMsg->pData, pMsg->ulDataLen);
        pBuff[pMsg->ulDataLen] = '\0';
    }
    else
    {
    
    }

    return  FTW_RET_OK;
    
error:

    return  FTW_RET_ERROR;
}

uint_32 FTW_MQTT_MSG_destroy(FTW_MQTT_MSG_PTR pMsg)
{
    FTW_MEM_free(pMsg);
    
    return  FTW_RET_OK;
}

struct
{
    FTW_MQTT_MSG_TYPE   xType;
    char_ptr            pString;
}   _xMsgTypeString[] =
{
    {   FTW_MQTT_MSG_DEV_INFO,  "MSG_DEV_INFO"  },
    {   FTW_MQTT_MSG_DEV_VALUE, "MSG_DEV_VALUE" },
    {   FTW_MQTT_MSG_EP_INFO,   "MSG_EP_INFO"   },
    {   FTW_MQTT_MSG_EP_VALUE,  "MSG_EP_VALUE"  },
    {   FTW_MQTT_MSG_GET_VALUE, "sensor.get" },
    {   FTW_MQTT_MSG_SET_VALUE, "sensor.set" },
    {   FTW_MQTT_MSG_INVALID,   NULL}
};

/******************************************************************************
 * Thing+ REQ message callback
 ******************************************************************************/
FTW_RET FTW_MQTT_METHOD_CB_setProperty(void _PTR_ pParams)
{
    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "called\n");
    return  FTW_RET_OK;
}

FTW_RET FTW_MQTT_METHOD_CB_controlActuator(void _PTR_ pParams)
{
    return  FTW_RET_OK;
}

FTW_RET FTW_MQTT_METHOD_CB_timeSync(void _PTR_ pParams)
{
    return  FTW_RET_OK;
}

FTW_MQTT_METHOD _pThingPlusMethods[] =
{
    {   FTW_MQTT_METHOD_SET_PROPERTY,       "setProperty",      FTW_MQTT_METHOD_CB_setProperty},
    {   FTW_MQTT_METHOD_CONTROL_ACTUATOR,   "controlActuator",  FTW_MQTT_METHOD_CB_controlActuator},
    {   FTW_MQTT_METHOD_TIME_SYNC,          "timeSync",         FTW_MQTT_METHOD_CB_timeSync},
    {   FTW_MQTT_METHOD_INVALID,            NULL,               NULL}
};



FTW_MQTT_METHOD _pFTLMMethods[] =
{
    {   FTW_MQTT_METHOD_INVALID,    NULL,           NULL}
};

FTW_MQTT_METHOD_PTR   FTW_MQTT_METHOD_get(char_ptr pString)
{
    FTW_MQTT_METHOD_PTR pMethod = _pFTLMMethods;
    
    while(pMethod->xMethod != FTW_MQTT_METHOD_INVALID)
    {
        if (strcmp(pMethod->pString, pString) == 0)
        {
            return  pMethod;
        }
        
        pMethod++;
    }
    
    return  NULL;
}

char_ptr   FTW_MQTT_MSG_TYPE_string(FTW_MQTT_MSG_TYPE xMsgType)
{
    uint_32 i;
    
    for(i = 0 ; _xMsgTypeString[i].xType != FTW_MQTT_MSG_INVALID ; i++)
    {
        if (_xMsgTypeString[i].xType == xMsgType)
        {
            return  _xMsgTypeString[i].pString;
        }
    }
    
    return  NULL;
}



/******************************************************************************
 * publish & subscribe test
 ******************************************************************************/

VOID FTW_MQTT_test(UINT32 ulParam)
{
    FTW_MQTT_CTX_PTR        pxCTX = (FTW_MQTT_CTX_PTR)ulParam;
    FTW_MQTT_TESTER_STATUS  xStatus;
    FTW_MQTT_STATISTICS     xOldStatistics;
    uint_32                 ulTotalSend = 0;
    
    memset(&xOldStatistics, 0, sizeof(FTW_MQTT_STATISTICS));
    
    xStatus.xStatus.xPublishTime = 0;
    for(int i = 0 ; i < pxCTX->xConfig.xTester.ulSensorCount; i++)
    {
        xStatus.xSensors[i].xPublishTime = 0;
    }
    
    while(FTW_NET_isConnected() == TRUE)
    {
        FTW_TIME_delay(1000);
    }
    
    FTW_TIME_delay(pxCTX->xConfig.xTester.ulStartDelay);
    
    while(TRUE)
    {
        if ((xOldStatistics.ulPublishedCount != pxCTX->xStatistics.ulPublishedCount) ||
            (xOldStatistics.ulPublishedErrorCount != pxCTX->xStatistics.ulPublishedErrorCount) ||
            (xOldStatistics.ulSubscribedCount != pxCTX->xStatistics.ulSubscribedCount) ||
            (xOldStatistics.ulSubscribedErrorCount != pxCTX->xStatistics.ulSubscribedErrorCount) ||
            (xOldStatistics.ulTransTimeout != pxCTX->xStatistics.ulTransTimeout))
        {
            FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%6d, %4d, %6d, %4d, %4d\n", 
                      pxCTX->xStatistics.ulPublishedCount,
                      pxCTX->xStatistics.ulPublishedErrorCount,
                      pxCTX->xStatistics.ulSubscribedCount,
                      pxCTX->xStatistics.ulSubscribedErrorCount,
                      pxCTX->xStatistics.ulTransTimeout);
            
            memcpy(&xOldStatistics, &pxCTX->xStatistics, sizeof(FTW_MQTT_STATISTICS));
        }
        
        if (pxCTX->xState == FTW_MQTT_STATE_CONNECTED)
        {            
            char pTopic[128];
            char pMsg[128];
            FTW_TIME    xCurrentTime;
            
            FTW_TIME_get(&xCurrentTime);
            if (FTW_TIME_diffMilliseconds(&xCurrentTime, &xStatus.xStatus.xPublishTime) >= pxCTX->xConfig.xTester.xStatus.ulPeriod)
            {            
                sprintf(pTopic, "v/a/g/%s/status", pxCTX->xConfig.pClientID);
                sprintf(pMsg, "on,90,temperature-%s-1,on,90",pxCTX->xConfig.pClientID);
                FTW_MQTT_publish(pxCTX, 1, pTopic, pMsg);
                FTW_TIME_get(&xStatus.xStatus.xPublishTime);
                FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%s : %s\n", pTopic, pMsg);
            }

            for(int i = 0 ; i < pxCTX->xConfig.xTester.ulSensorCount ; i++)
            {
                FTW_TIME_get(&xCurrentTime);
                if (FTW_TIME_diffMilliseconds(&xCurrentTime, &xStatus.xSensors[i].xPublishTime) >= pxCTX->xConfig.xTester.xSensors[i].ulPeriod)
                {
                    GSN_SYSTEM_TIME_T   xCurrentTime;
                    FTW_SYS_TIME_get(&xCurrentTime);
                    sprintf(pTopic, "v/a/g/%s/s/%s", pxCTX->xConfig.pClientID, pxCTX->xConfig.xTester.xSensors[i].pName);
                    
                    uint_32 ulTemp = 200+(rand() % 100);
                    sprintf(pMsg, "%llu,%d.%d",xCurrentTime, ulTemp/10,ulTemp%10);
                    FTW_MQTT_publish(pxCTX, 1, pTopic, pMsg);
                    FTW_TIME_get(&xStatus.xSensors[i].xPublishTime);
                    FTW_MODULE_TRACE(FTW_DBG_MODULE_MQTT, "%s : %s\n", pTopic, pMsg);
                }
            }
        }

        FTW_TIME_delay(1000);
    }
}
