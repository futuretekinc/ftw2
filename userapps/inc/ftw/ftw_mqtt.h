#ifndef _FTW_MQTT_H__
#define _FTW_MQTT_H__

#include "ftw_types.h"
#include "ftw_list.h"
#include "ftw_time.h"
#include <libemqtt.h>

#ifndef FTW_MQTT_CFG_STACK_SIZE
    #define FTW_MQTT_CFG_STACK_SIZE         2048
#endif

#ifndef FTW_MQTT_CFG_MSG_QUEUE_SIZE
    #define FTW_MQTT_CFG_MSG_QUEUE_SIZE     32
#endif

#ifndef FTW_MQTT_CFG_RESEND_MAX
    #define FTW_MQTT_CFG_RESEND_MAX         5
#endif

#ifndef FTW_MQTT_CFG_RESEND_MAX     
    #define FTW_MQTT_CFG_RESEND_MAX     5
#endif

#ifndef FTW_MQTT_DEFAULT_PORT   
#define FTW_MQTT_DEFAULT_PORT       1883
#endif

#ifndef FTW_MQTT_DEFAULT_KEEPALIVE
#define FTW_MQTT_DEFAULT_KEEPALIVE  180
#endif

#define FTW_MQTT_CLIENT_ID_LENGTH   64
#define FTW_MQTT_USERNAME_LENGTH    MQTT_CONF_USERNAME_LENGTH
#define FTW_MQTT_PASSWORD_LENGTH    32  // MQTT_CONF_PASSWORD_LENGTH
#define FTW_MQTT_TOPIC_LENGTH       128
#define FTW_MQTT_IP_LENGTH          128
#define FTW_MQTT_RECV_BUFF_SIZE     1024
#define FTW_MQTT_TRANS_COUNT        10

#define FTW_MQTT_RET_OK                             (MQX_OK)
#define FTW_MQTT_RET_ERROR                          (RTCS_ERROR_BASE|0xF00)
#define FTW_MQTT_RET_NOT_CONNECTED                  (RTCS_ERROR_BASE|0xF01)
#define FTW_MQTT_RET_READ_ABOARTED                  (RTCS_ERROR_BASE|0xF02)
#define FTW_MQTT_RET_UNACCEPTABLE_PROTOCOL_VERSION  (RTCS_ERROR_BASE|0xF03)
#define FTW_MQTT_RET_IDENTIFIER_REJECTED            (RTCS_ERROR_BASE|0xF04)
#define FTW_MQTT_RET_SERVER_UNAVALIABLE             (RTCS_ERROR_BASE|0xF05)
#define FTW_MQTT_RET_BAD_USER_NAME_OR_PASSWORD      (RTCS_ERROR_BASE|0xF06)
#define FTW_MQTT_RET_NOT_AUTHORIZED                 (RTCS_ERROR_BASE|0xF07)
#define FTW_MQTT_RET_OPERATION_NOT_PERMITTED        (RTCS_ERROR_BASE|0xF08)
#define FTW_MQTT_RET_USBSCRIBE_ERROR                (RTCS_ERROR_BASE|0xF09)
#define FTW_MQTT_RET_INVALID_TOPIC                  (RTCS_ERROR_BASE|0xF0A)
#define FTW_MQTT_RET_INVALID_PARAMS                 (RTCS_ERROR_BASE|0xF0B)
#define FTW_MQTT_RET_NOT_ENOUGH_MEMORY              (RTCS_ERROR_BASE|0xF0C)
#define FTW_MQTT_RET_TCP_CONN_ABORTED               (RTCS_ERROR_BASE|0xF0D)
#define FTW_MQTT_RET_NOT_INITIALIZED                (RTCS_ERROR_BASE|0xF0E)

#define FTW_MQTT_QOS_0              0
#define FTW_MQTT_QOS_1              1
#define FTW_MQTT_QOS_2              2

#define FTW_MQTT_CMD_REQ            1
#define FTW_MQTT_CMD_INFO           2

#define FTW_MQTT_TARGET_SERVER      1
#define FTW_MQTT_TARGET_GATEWAY     2
#define FTW_MQTT_TARGET_LID         3
#define FTW_MQTT_TARGET_UID         4
#define FTW_MQTT_TARGET_BROADCAST   5

typedef enum
{
    FTW_MQTT_MSG_INVALID  = 0,
    FTW_MQTT_MSG_DEV_INFO,
    FTW_MQTT_MSG_DEV_VALUE,
    FTW_MQTT_MSG_EP_INFO,
    FTW_MQTT_MSG_EP_VALUE,
    FTW_MQTT_MSG_GET_VALUE,
    FTW_MQTT_MSG_SET_VALUE,
}   FTW_MQTT_MSG_TYPE, _PTR_ FTW_MQTT_MSG_TYPE_PTR;

typedef enum
{
    FTW_MQTT_METHOD_INVALID,
    FTW_MQTT_METHOD_SET_PROPERTY,
    FTW_MQTT_METHOD_CONTROL_ACTUATOR,
    FTW_MQTT_METHOD_TIME_SYNC,
    FTW_MQTT_METHOD_FTLM_DEVICE_GET,
    FTW_MQTT_METHOD_FTLM_DEVICE_SET,
    FTW_MQTT_METHOD_FTLM_GROUP_GET,
    FTW_MQTT_METHOD_FTLM_GROUP_SET
}   FTW_MQTT_METHOD_TYPE, _PTR_ FTW_MQTT_METHOD_TYPE_PTR;

typedef enum
{
    FTW_MQTT_STATE_UNINITIALIZED = 0,
    FTW_MQTT_STATE_INITIALIZED,
    FTW_MQTT_STATE_CONNECTED,
    FTW_MQTT_STATE_DISCONNECTED
}   FTW_MQTT_STATE, _PTR_ FTW_MQTT_STATE_PTR;

typedef struct
{
    struct
    {
        FTW_IPADDR_T    xIPAddress;
        uint_16         usPort;
    }   xServer;

    struct
    {
        uint_32         ulTime;
        uint_32         ulRetryCount;
    }   xKeepalive;
    // Autorization Information
    struct
    {
        uint_32     bEnabled;
        char        pUserName[FTW_MQTT_USERNAME_LENGTH];
        char        pPassword[FTW_MQTT_PASSWORD_LENGTH];
    }   xAuth; 
}   FTW_MQTT_BROKER_CONFIG, _PTR_ FTW_MQTT_BROKER_CONFIG_PTR;

typedef struct
{
    uint_32         ulStartDelay;
    struct
    {
        uint_32     ulPeriod;
    }   xStatus;
    
    uint_32         ulSensorCount;
    
    struct
    {
        char        pName[32];
        uint_32     ulPeriod;
    }   xSensors[16];
}   FTW_MQTT_TESTER_CONFIG, _PTR_ FTW_MQTT_TESTER_CONFIG_PTR;

typedef struct FTW_MQTT_TESTER_STATUS_STRUCT
{
    struct
    {
        FTW_TIME    xPublishTime;
    }   xStatus;
    
    struct
    {
        FTW_TIME    xPublishTime;
    }   xSensors[16];
}   FTW_MQTT_TESTER_STATUS, _PTR_ FTW_MQTT_TESTER_STATUS_PTR;

typedef struct
{
    char                    pClientID[FTW_MQTT_CLIENT_ID_LENGTH+1];
    boolean                 bEnable;
    // Broker Information
    FTW_MQTT_BROKER_CONFIG  xBroker;
    FTW_MQTT_TESTER_CONFIG  xTester;
//    FTW_SSL_CONFIG          xSSL;
    uint_32                 ulPubTimeout;
}   FTW_MQTT_CONFIG, _PTR_ FTW_MQTT_CONFIG_PTR;

typedef  struct FTW_MQTT_STATISTICS_STRUCT
{
    uint_32             ulPublishedCount;
    uint_32             ulPublishedErrorCount;
    uint_32             ulSubscribedCount;
    uint_32             ulSubscribedErrorCount;
    uint_32             ulTransTimeout;
} FTW_MQTT_STATISTICS, _PTR_ FTW_MQTT_STATISTICS_PTR;

typedef struct
{
    int_32                  nSocketID;
    FTW_MQTT_STATE          xState;
    FTW_MQTT_CONFIG         xConfig;
	mqtt_broker_handle_t    xBroker;
    
    GSN_OSAL_SEM_T          xLock;
    FTW_LIST                xTransList;
    FTW_LIST                xFreeTransList;
    FTW_LIST                xRecvMsgPool;
    FTW_LIST                xSendMsgPool;
    uint_8                  pBuff[FTW_MQTT_RECV_BUFF_SIZE];
    uint_32                 ulBuffSize;
    uint_32                 ulRcvdLen;
    FTW_TIME                xTime;
    TX_TIMER                xPingTimer;
    uint_32                 ulPingRetry;
    
    FTW_MQTT_STATISTICS     xStatistics;
    //FTW_SSL_CONTEXT_PTR     pxSSL;
    
    uint_8                  xCID;
    GSN_OSAL_THREAD_TCB_T   *pxProcessTCB;
    uint_8                  *pProcessStack;
    GSN_OSAL_THREAD_TCB_T   *pxReceiverTCB;
    uint_8                  *pReceiverStack;
    GSN_OSAL_THREAD_TCB_T   *pxSenderTCB;
    uint_8                  *pSenderStack;
    GSN_OSAL_THREAD_TCB_T   *pxTestTCB;
    uint_8                  *pTestStack;
}   FTW_MQTT_CTX, _PTR_ FTW_MQTT_CTX_PTR;

typedef FTW_RET (*FTW_MQTT_METHOD_CALLBACK)(void _PTR_ pParams);

typedef struct
{
    FTW_MQTT_METHOD_TYPE        xMethod;
    char_ptr                    pString;
    FTW_MQTT_METHOD_CALLBACK    fCallback;
}   FTW_MQTT_METHOD, _PTR_ FTW_MQTT_METHOD_PTR;

uint_32 FTW_MQTT_init(FTW_MQTT_CONFIG_PTR pxConfig);

uint_32 FTW_MQTT_subscribe(FTW_MQTT_CTX_PTR pxCTX, char_ptr pTopic);
uint_32 FTW_MQTT_publish(FTW_MQTT_CTX_PTR pxCTX, uint_32 nQoS, char *pTopic, char *pMsg);

int_32  FTW_MQTT_SHELL_cmd(int_32 argc, char_ptr argv[]);

#endif
