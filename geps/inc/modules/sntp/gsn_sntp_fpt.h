#include "gsn_includes.h"
#ifndef _GSN_SNTP_FPT_H_
#define _GSN_SNTP_FPT_H_

typedef GSN_STATUS
(* GsnSntp_TimeSync_FP_T)(GSN_SNTP_CTX_T *sntpCtx, UINT32 serverIpAddr,
                    UINT8 serverTimeout, GSN_NOTIFICATION_FUNC_T cb,
                    VOID *cbCtx);
extern _RPST_ GsnSntp_TimeSync_FP_T GsnSntp_TimeSync_FP;

typedef GSN_STATUS
(* GsnSntp_Send_FP_T)(GSN_SNTP_CTX_T * pSntpCtx,struct sockaddr_in * ntpServerAddr,\
				UINT8 timeout);

typedef VOID
(* GsnSntp_ServerRespTmrCb_FP_T)(VOID * pCtx,UINT32 tmrHndl);

typedef VOID
(* GsnSntp_SocketCb_FP_T)(INT32 sockDesc,NX_BSD_CB_EVENT_TYPE_T flags,VOID * pCtx);


extern _RPST_ GsnSntp_Send_FP_T GsnSntp_Send_FP ;
extern _RPST_ GsnSntp_ServerRespTmrCb_FP_T GsnSntp_ServerRespTmrCb_FP ;
extern _RPST_ GsnSntp_SocketCb_FP_T GsnSntp_SocketCb_FP ;

#endif
