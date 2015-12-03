#ifndef _GSN_MSG_HANDLER_FPT_H_
#define _GSN_MSG_HANDLER_FPT_H_

#include "gsn_includes.h"
#include "core/msg_handler/gsn_msg_handler.h"

typedef VOID
(*GsnMsgHandler_Create_FP_T)( GSN_MSG_HANDLER_CTX_T* pCtx, GSN_MSG_HANDLER_CFG_T *pCfg,
    VOID *pMsg, GSN_MSG_HANDLER_CB_T handlerCb, VOID *pHandlerCtx );

extern _RPST_ GsnMsgHandler_Create_FP_T GsnMsgHandler_Create_FP;

#endif
