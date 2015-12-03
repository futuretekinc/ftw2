#ifndef _FTW_NET_H_
#define _FTW_NET_H_

#include "ftw_types.h"

#ifndef FTW_NET_CFG_STACK_SIZE
    #define FTW_NET_CFG_STACK_SIZE  2048
#endif

#ifndef FTW_NET_CFG_SSID_LENGTH
    #define FTW_NET_CFG_SSID_LENGTH 32
#endif

#ifndef FTW_NET_CFG_WWPA_LENGTH
    #define FTW_NET_CFG_WWPA_LENGTH 32
#endif

typedef enum
{
    FTW_NET_STAT_UNINITIALIZED,
    FTW_NET_STAT_INITIALIZED,
    FTW_NET_STAT_CONNECTED,
    FTW_NET_STAT_STAY_CONNECTED,
    FTW_NET_STAT_CONNECTION_RETRY,
    FTW_NET_STAT_DISCONNECTED,
    FTW_NET_STAT_WAITING,
}   FTW_NET_STAT;

typedef struct  FTW_NET_CONFIG_STRUCT
{
    char    pSSID[FTW_NET_CFG_SSID_LENGTH+1];
    char    pWWPA[FTW_NET_CFG_WWPA_LENGTH+1];
}   FTW_NET_CONFIG, _PTR_ FTW_NET_CONFIG_PTR;

typedef struct  FTW_NET_MSG_STRUCT
{
    uint_32 ulLen;
    uint_8  pBuff[];
} FTW_NET_MSG, * FTW_NET_MSG_PTR;

FTW_RET         FTW_NET_init(FTW_NET_CONFIG_PTR pConfig);
FTW_NET_STAT    FTW_NET_getStat(void);
FTW_RET         FTW_NET_isConnected(void);

VOID            FTW_NET_rx(UINT8 cid, void *buf, UINT32 len, UINT8 *ip, UINT16 port);
uint_32         FTW_NET_getPkt(UINT8 cid, void *pBuf, uint_32 ulBuffLen);
#endif
