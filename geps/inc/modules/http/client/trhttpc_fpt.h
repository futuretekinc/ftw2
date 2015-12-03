#ifndef _TRHTTPC_FPT_H_

#define _TRHTTPC_FPT_H_

#include <string.h>
#include "netx/netx_bsd_layer/nxd_bsd.h"
#include "modules/http/include/trsocket.h"

#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"
#include "modules/http/include/trhttpc.h"

typedef ttHttpcUserConHandle 
(* tfHttpcUserOpen_FP_T)( int  addrFamily,ttHttpcUserEventHandler handlerPtr,
     ttUserIntPtr errorCodePtr, int  flags);

typedef int 
(* tfHttpcUserConnect_FP_T)(ttHttpcUserConHandle        conHandle,
    ttConstSockAddrStoragePtr   sockAddrPtr, int flags );

typedef int 
(* tfHttpcUserClose_FP_T)(
    ttHttpcUserConHandle    conHandle,
    int                     flags);    

typedef int 
(* tfHttpcUserStoreVariable_FP_T) (
    ttHttpcUserConHandle    conHandle,
    ttUserGenericUnion      genParam,
    int                     flags );    

typedef int 
(* tfHttpcUserRetrieveVariable_FP_T)(
    ttHttpcUserConHandle    conHandle,
    ttUserGenericUnionPtr   genParamPtr,
    int                     flags);    

typedef int 
(* tfHttpcUserSetSockOpt_FP_T)(
    ttHttpcUserConHandle    conHandle,
    int                     protocolLevel,
    int                     optionName,
    ttUserCharPtr           optionValuePtr,
    int                     optionLen,
    int                     flags);    

 typedef int 
 (* tfHttpcUserBind_FP_T)(
    ttHttpcUserConHandle    conHandle,
    const struct sockaddr * addressPtr,
    int                     addressLength,
    int                     flags);  

typedef int 
(* tfHttpcUserRegisterResponseHeader_FP_T)(
    ttHttpcUserConHandle    conHandle,
    ttHttpUserHeaderType    headerType,
    int                     flags );    

typedef int 
(* tfHttpcUserSendRequestMethodLine_FP_T)(
    ttHttpcUserConHandle    conHandle,
    ttHttpUserVersion       version,
    ttHttpUserMethod        method,
    ttUserConstCharPtr      pathPtr,
    int                     flags);  

typedef int 
(* tfHttpcUserSendRequestHeaders_FP_T)(
    ttHttpcUserConHandle    conHandle,
    ttUserIntPtr            headerCountPtr,
    ttHttpUserHeaderType    headerTypes[],
    ttUserConstCharPtr      headerValues[],
    int                     flags);    

typedef int 
(* tfHttpcUserSendRequestBody_FP_T)(
    ttHttpcUserConHandle    conHandle,
    int                     contentLength,
    ttUserConstCharPtr      bufferPtr,
    ttUserIntPtr            bufferLenPtr,
    int                     flags);    

typedef int 
(* tfHttpcUserGetResponseStatusLine_FP_T)(
    ttHttpcUserConHandle        conHandle,
    ttHttpUserVersion TM_FAR *  versionPtr,
    ttUserIntPtr                statusCodePtr,
    ttUserCharPtrPtr            reasonPhrasePtr,
    int                         timeOut,
    int                         flags);   

typedef int 
(* tfHttpcUserGetResponseHeaders_FP_T)(
    ttHttpcUserConHandle    conHandle,
    ttUserCharPtrPtrPtr     headerValPtr,
    int                     timeOut,
    int                     flags
#if 1//def GSN_HTTP_CUSTOM_SUPPORT
    ,ttHttpcCustomHdr      **customHdrPtrPtr
#endif
    );

typedef int
(* tfHttpcUserGetResponseBody_FP_T)(
    ttHttpcUserConHandle    conHandle,
    ttUserCharPtr           bufferPtr,
    ttUserIntPtr            bufferLenPtr,
    int                     timeOut,
    int                     flags);   

 typedef int 
 (* tfHttpcUserExecute_FP_T) (ttHttpcUserConHandle    conHandle,
                        int                     flags); 

 typedef int  
 (* tfHttpcSendLine_FP_T) (ttHttpcConEntryPtr conEntryPtr); 

 typedef int  
 (* tfHttpcGetResponse_FP_T) (ttHttpcConEntryPtr  conEntryPtr,
                                int                 timeOut);
typedef int 
(* tfHttpcZeroCopyRecv_FP_T) (ttHttpcConEntryPtr  conEntryPtr,
									int 				timeOut );

typedef int  
(* tfHttpcGetLine_FP_T) ( ttHttpcConEntryPtr conEntryPtr); 									

typedef int  
(* tfHttpcParseResponse_FP_T) (ttHttpcConEntryPtr    conEntryPtr);                                

typedef int 
(* tfHttpcStr2Int_FP_T)(ttConstCharPtr strPtr, tt32BitPtr numberPtr);

typedef int  
(* tfHttpcParseStatusLine_FP_T) (ttHttpcConEntryPtr  conEntryPtr);

typedef int  
(* tfHttpcParseHeader_FP_T)(ttHttpcConEntryPtr   conEntryPtr);

typedef int 
(* tfHttpcCheckSocket_FP_T)(int sd, int direction, ttIntPtr errorCodePtr);

typedef int 
(* tfHttpcSendRequestEnd_FP_T)(ttHttpcConEntryPtr conEntryPtr);

extern _RPST_ tfHttpcUserOpen_FP_T tfHttpcUserOpen_FP;						
extern _RPST_ tfHttpcUserConnect_FP_T tfHttpcUserConnect_FP;
extern _RPST_ tfHttpcUserClose_FP_T tfHttpcUserClose_FP;
extern _RPST_ tfHttpcUserStoreVariable_FP_T tfHttpcUserStoreVariable_FP;
extern _RPST_ tfHttpcUserRetrieveVariable_FP_T tfHttpcUserRetrieveVariable_FP;
extern _RPST_ tfHttpcUserSetSockOpt_FP_T tfHttpcUserSetSockOpt_FP;
extern _RPST_ tfHttpcUserBind_FP_T tfHttpcUserBind_FP;
extern _RPST_ tfHttpcUserRegisterResponseHeader_FP_T tfHttpcUserRegisterResponseHeader_FP;
extern _RPST_ tfHttpcUserSendRequestMethodLine_FP_T tfHttpcUserSendRequestMethodLine_FP;
extern _RPST_ tfHttpcUserSendRequestHeaders_FP_T tfHttpcUserSendRequestHeaders_FP;
extern _RPST_ tfHttpcUserSendRequestBody_FP_T tfHttpcUserSendRequestBody_FP;
extern _RPST_ tfHttpcUserGetResponseStatusLine_FP_T tfHttpcUserGetResponseStatusLine_FP;
extern _RPST_ tfHttpcUserGetResponseHeaders_FP_T tfHttpcUserGetResponseHeaders_FP;
extern _RPST_ tfHttpcUserGetResponseBody_FP_T tfHttpcUserGetResponseBody_FP;
extern _RPST_ tfHttpcUserExecute_FP_T tfHttpcUserExecute_FP;
extern _RPST_ tfHttpcSendLine_FP_T tfHttpcSendLine_FP;
extern _RPST_ tfHttpcGetResponse_FP_T tfHttpcGetResponse_FP;
extern _RPST_ tfHttpcZeroCopyRecv_FP_T tfHttpcZeroCopyRecv_FP;
extern _RPST_ tfHttpcGetLine_FP_T tfHttpcGetLine_FP;
extern _RPST_ tfHttpcParseResponse_FP_T tfHttpcParseResponse_FP;
extern _RPST_ tfHttpcStr2Int_FP_T tfHttpcStr2Int_FP;
extern _RPST_ tfHttpcParseStatusLine_FP_T tfHttpcParseStatusLine_FP;
extern _RPST_ tfHttpcParseHeader_FP_T tfHttpcParseHeader_FP;
extern _RPST_ tfHttpcCheckSocket_FP_T tfHttpcCheckSocket_FP;
extern _RPST_ tfHttpcSendRequestEnd_FP_T tfHttpcSendRequestEnd_FP;

#endif