#ifndef _FTW_TYPES_H_
#define _FTW_TYPES_H_

#include "gsn_types.h"

typedef UINT32  FTW_RET;
typedef INT8    int_8, * int_8_ptr;
typedef UINT8   uint_8, * uint_8_ptr;
typedef UINT16  uint_16, * uint_16_ptr;
typedef UINT32  uint_32, * uint_32_ptr;
typedef INT32   int_32;
typedef char *  char_ptr;
typedef UINT32  boolean;
typedef UINT32  FTW_OBJECT_ID;
typedef UINT32  _timer_id;
typedef UINT32  FTW_TICKS;
typedef UINT32  BOOLEAN;

#define VOID    void

#define FALSE   0
#define TRUE    (!FALSE)

#define _PTR_   *
#define pointer void *

#define FTW_RET_OK                      GSN_SUCCESS
#define FTW_RET_ERROR                   (GSN_FAILURE | 0x00000000)
#define FTW_RET_NOT_INITIALIZED         (GSN_FAILURE | 0x00000001)
#define FTW_RET_NOT_ENOUGH_MEMORY       (GSN_FAILURE | 0x00000002)
#define FTW_RET_OPERATION_NOT_PERMITTED (GSN_FAILURE | 0x00000003)
#define FTW_RET_TCP_CONN_ABORTED        (GSN_FAILURE | 0x00000004)
#define FTW_RET_USBSCRIBE_ERROR         (GSN_FAILURE | 0x00000005)
#define FTW_RET_NOT_CONNECTED           (GSN_FAILURE | 0x00000006)
#define FTW_RET_READ_ABOARTED           (GSN_FAILURE | 0x00000007)

#define FTW_RET_CONFIG_NOT_EXISTS       (GSN_FAILURE | 0x00000008)
#define FTW_RET_CONFIG_CANT_CREATE      (GSN_FAILURE | 0x00000009)

#define FTE_RET_NET_FAILURE             (GSN_FAILURE | 0x00010000)

#define FTW_RET_UNACCEPTABLE_PROTOCOL_VERSION   (FTE_RET_NET_FAILURE | 0x00000001)
#define FTW_RET_IDENTIFIER_REJECTED             (FTE_RET_NET_FAILURE | 0x00000002)
#define FTW_RET_SERVER_UNAVALIABLE              (FTE_RET_NET_FAILURE | 0x00000003)
#define FTW_RET_BAD_USER_NAME_OR_PASSWORD       (FTE_RET_NET_FAILURE | 0x00000004)
#define FTW_RET_NOT_AUTHORIZED                  (FTE_RET_NET_FAILURE | 0x00000005)
#define FTW_RET_INVALID_TOPIC                   (FTE_RET_NET_FAILURE | 0x00000006)
#define FTW_RET_RETRY_EXCEED                    (FTE_RET_NET_FAILURE | 0x00000007)
#define FTW_RET_NET_IS_NOT_INITIALIZED          (FTE_RET_NET_FAILURE | 0x00000008)

#define FTW_RET_SOCKFAILURE                     (FTE_RET_NET_FAILURE | 0x00000100)

#define FTW_RET_CMD_FAILURE             (GSN_FAILURE | 0x00020000)

#endif
