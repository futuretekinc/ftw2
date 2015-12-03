/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: trhttpd_fpt.h,v $
*
* Description : This file contains the patch type defination.
*******************************************************************************/

#ifndef _TRHTTPD_FPT_
#define _TRHTTPD_FPT_

#include "modules/http/include/trsocket.h"
#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_includes.h"

typedef int (*tfHttpdUserInit_FP_T) (ttUser16Bit maxNumberServers);
extern _RPST_ tfHttpdUserInit_FP_T tfHttpdUserInit_FP;

typedef ttHttpdUserSrvHandle (*tfHttpdUserStart_FP_T) (
	    int                         maxConnections,
	    int                         maxConnectionsPerIp,
	    int                         idleTimeOut,
	    int                         flags,
	    const char TM_FAR *         rootNamePtr,
	    const char TM_FAR *         defaultPagePtr,
	    const char TM_FAR *         cgiDirPtr,
	    ttConstSockAddrStoragePtr   sockAddrPtr,
	    int TM_FAR *                errorCodePtr,
	    void					 	*pCert,
	    void 						*pool_ptr,	    
		unsigned int				 sysQualTskID,
		unsigned int				 sysQualTicks
	     );
extern _RPST_ tfHttpdUserStart_FP_T tfHttpdUserStart_FP;

typedef int (*tfHttpdUserSetSockopt_FP_T) (
	    ttHttpdUserSrvHandle    userSrvHandle,
	    int                     levelOfLayer,
	    int                     optionName,
	    const char TM_FAR *     optionValuePtr,
	    int                     optionLength);
extern _RPST_ tfHttpdUserSetSockopt_FP_T tfHttpdUserSetSockopt_FP;

typedef int (*tfHttpdUserExecute_FP_T) (ttHttpdUserSrvHandle userSrvHandle );
extern _RPST_ tfHttpdUserExecute_FP_T tfHttpdUserExecute_FP;

typedef int (*tfHttpdUserStop_FP_T) (ttHttpdUserSrvHandle userSrvHandle);
extern _RPST_ tfHttpdUserStop_FP_T tfHttpdUserStop_FP;

typedef int (*tfHttpdUserClose_FP_T) (
	    ttHttpdUserConHandle    userConHandle,
	    const int               errorCode);
extern _RPST_ tfHttpdUserClose_FP_T tfHttpdUserClose_FP;

typedef int (*tfHttpdHeaderOption_FP_T) (
        int              hdrName,
        char TM_FAR *    hdrObjPtr,
        void TM_FAR *    hdrHttpsrvHandle,
        char TM_FAR *    hdrValue1Ptr,
        int              hdrValue1Length,
        char TM_FAR *    hdrValue2Ptr,
        int              hdrValue2Length,
        int              hdrFlags );
extern _RPST_ tfHttpdHeaderOption_FP_T tfHttpdHeaderOption_FP;

typedef int (*tfHttpdUserAuthConfig_FP_T) (
    ttHttpdUserSrvHandle    userSrvHandle,
    const char TM_FAR *     objectNamePtr,
    const char TM_FAR *     realmPtr,
    const char TM_FAR *     userNamePtr,
    const char TM_FAR *     passwordPtr,
    int                     authType );
extern _RPST_ tfHttpdUserAuthConfig_FP_T tfHttpdUserAuthConfig_FP;

typedef int (*tfHttpdAuthConfig_FP_T) (ttHttpdSrvEntryPtr  srvEntryPtr,
                             const char TM_FAR * objectNamePtr,
                             const char TM_FAR * realmPtr,
                             const char TM_FAR * userNamePtr,
                             const char TM_FAR * passwordPtr,
                             int                 authType );
extern _RPST_ tfHttpdAuthConfig_FP_T tfHttpdAuthConfig_FP;

typedef ttHttpdUserConEntryPtr (*tfHttpdUserGetConInfo_FP_T) (
	    ttHttpdUserConHandle    userConHandle);
extern _RPST_ tfHttpdUserGetConInfo_FP_T tfHttpdUserGetConInfo_FP;

#ifdef TM_USE_HTTPD_CGI
typedef int (*tfHttpdUserSetCgiIdFunc_FP_T) (
	    ttHttpdUserSrvHandle  userSrvHandle,
	    ttHttpdUserCgiIdCBPtr funcPtr);
extern _RPST_ tfHttpdUserSetCgiIdFunc_FP_T tfHttpdUserSetCgiIdFunc_FP;
#endif

typedef int (*tfHttpdUserSetContentTypeFunc_FP_T) (
    ttHttpdUserSrvHandle        userSrvHandle,
    ttHttpdUserContentTypeCBPtr funcPtr,
    int                         length,
    int                         flags);
extern _RPST_ tfHttpdUserSetContentTypeFunc_FP_T tfHttpdUserSetContentTypeFunc_FP;

typedef void (*tfHttpdSignalServerAccept_FP_T) (
	    int                      socketDescriptor,
	    ttVoidPtr                srvVoidHandlePtr,
	    int                      flags);
extern _RPST_ tfHttpdSignalServerAccept_FP_T tfHttpdSignalServerAccept_FP;

typedef void (*tfHttpdSignalServer_FP_T) ( int               socketDescriptor,
                          ttVoidPtr         conHandle,
                          int               flags );
extern _RPST_ tfHttpdSignalServer_FP_T tfHttpdSignalServer_FP;

typedef void (*tfHttpdSignalLockedServer_FP_T) (
        ttHttpdSrvHandlePtr     srvHandlePtr,
        ttHttpdConEntryPtr      conEntryPtr,
        int                     flags
#ifdef TM_HTTPD_CHECK_SERVER_THREAD
      , tt8Bit                  serverThread
#endif /* TM_HTTPD_CHECK_SERVER_THREAD */
               );
extern _RPST_ tfHttpdSignalLockedServer_FP_T tfHttpdSignalLockedServer_FP;

typedef void (*tfHttpdIdleTimeout_FP_T) (ttVoidPtr     timerBlockPtr,
                        ttGenericUnion userParm1,
                        ttGenericUnion userParm2);
extern _RPST_ tfHttpdIdleTimeout_FP_T tfHttpdIdleTimeout_FP;

typedef int (*tfHttpdExecute_FP_T) (ttHttpdSrvHandlePtr   srvHandlePtr);
extern _RPST_ tfHttpdExecute_FP_T tfHttpdExecute_FP;

typedef void (*tfHttpdAccept_FP_T) (ttHttpdSrvHandlePtr  srvHandlePtr,
                          ttHttpdSrvEntryPtr   srvEntryPtr);
extern _RPST_ tfHttpdAccept_FP_T tfHttpdAccept_FP;

typedef void (*tfHttpdTimerAdd_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                             tt32Bit            timeout );
extern _RPST_  tfHttpdTimerAdd_FP_T tfHttpdTimerAdd_FP;

typedef void (*tfHttpdTimerRemove_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdTimerRemove_FP_T tfHttpdTimerRemove_FP;

typedef int (*tfHttpdNewUserConnection_FP_T) ( ttHttpdSrvEntryPtr  srvEntryPtr,
                                     ttHttpdConEntryPtr  conEntryPtr );
extern _RPST_ tfHttpdNewUserConnection_FP_T tfHttpdNewUserConnection_FP;

typedef void (*tfHttpdCloseSocket_FP_T) (int socketDesc);
extern _RPST_  tfHttpdCloseSocket_FP_T tfHttpdCloseSocket_FP;


typedef void (*tfHttpdCloseConnection_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                                   tt8Bit             needServerLock);
extern _RPST_ tfHttpdCloseConnection_FP_T tfHttpdCloseConnection_FP;

typedef int (*tfHttpdHandler_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfHttpdHandler_FP_T tfHttpdHandler_FP;

typedef ttUserMessage (*tfHttpdQueueData_FP_T) (ttHttpdConEntryPtr conEntryPtr,
        ttUserMessage      recvDataMessage,
        ttCharPtr          dataPtr,
        ttIntPtr           dataLenPtr);
extern _RPST_ tfHttpdQueueData_FP_T tfHttpdQueueData_FP;

typedef int (*tfHttpdCgiArgCollect_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                                ttCharPtr          dataPtr,
                                tt32Bit            dataLen,
                                int                flags
                               );
extern _RPST_ tfHttpdCgiArgCollect_FP_T tfHttpdCgiArgCollect_FP;

typedef int (*tfHttpdConvert_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                           ttCharPtr          dataPtr,
                           tt32Bit            dataLen,
                           tt8Bit             state);
extern _RPST_ tfHttpdConvert_FP_T tfHttpdConvert_FP;

typedef int (*tfHttpdAllocBodyBuf_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                               tt32Bit            allocLen,
                               ttDeviceEntryPtr   devPtr);
extern _RPST_ tfHttpdAllocBodyBuf_FP_T tfHttpdAllocBodyBuf_FP;

typedef int (*tfHttpdAllocCgiArgs_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfHttpdAllocCgiArgs_FP_T tfHttpdAllocCgiArgs_FP;

typedef void (*tfHttpdFreeCgiArgs_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfHttpdFreeCgiArgs_FP_T tfHttpdFreeCgiArgs_FP;

typedef int (*tfHttpdCreateHeaders_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdCreateHeaders_FP_T tfHttpdCreateHeaders_FP;

typedef int (*tfHttpdSendResponse_FP_T) (ttHttpdConEntryPtr  conEntryPtr,
        int                 socketFlag);
extern _RPST_  tfHttpdSendResponse_FP_T tfHttpdSendResponse_FP;

typedef int (*tfHttpdUserSendBuffer_FP_T) (
    ttHttpdUserConHandle    userConHandle,
    const char TM_FAR *     bufferPtr,
    int                     bufferLen,
    int                     flag,
    int TM_FAR *            errorCodePtr);
extern _RPST_ tfHttpdUserSendBuffer_FP_T tfHttpdUserSendBuffer_FP;

typedef int (*tfHttpdSendData_FP_T) (ttHttpdConEntryPtr conEntryPtr, int socketFlag);
extern _RPST_  tfHttpdSendData_FP_T tfHttpdSendData_FP;

typedef int (*tfHttpdSendBuffer_FP_T) (
    ttHttpdConEntryPtr      conEntryPtr,
    const char TM_FAR *     bufferPtr,
    int                     bufferLen,
    ttHttpdSendFuncPtr      sendFuncPtr,
    int                     flag,
    int TM_FAR *            errorCodePtr);
extern _RPST_ tfHttpdSendBuffer_FP_T tfHttpdSendBuffer_FP;

typedef int (*tfHttpdAuthVerify_FP_T) (
    ttHttpdConEntryPtr  conEntryPtr,
    ttCharPtr           authKeyPtr);
extern _RPST_ tfHttpdAuthVerify_FP_T tfHttpdAuthVerify_FP;

typedef void (*tfHttpdProcessUrl_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdProcessUrl_FP_T tfHttpdProcessUrl_FP;

typedef ttHttpUserHeaderType (*tfHttpdFindHeaders_FP_T) (ttCharPtrPtr dataPtrPtr);
extern _RPST_ tfHttpdFindHeaders_FP_T tfHttpdFindHeaders_FP;

typedef int (*tfHttpdAddString_FP_T) (ttCharPtrPtr   bufferPtrPtr,
                            ttCharPtr      stringPtr,
                            ttIntPtr       bufferLenPtr,
                            int            flags );
extern _RPST_ tfHttpdAddString_FP_T tfHttpdAddString_FP;

typedef ttHttpdSrvHandlePtr
                    (*tfHttpdServerStore_FP_T) (ttHttpdSrvEntryPtr srvEntryPtr);
extern _RPST_  tfHttpdServerStore_FP_T tfHttpdServerStore_FP;

typedef void (*tfHttpdServerFree_FP_T) ( ttHttpdSrvEntryPtr   srvEntryPtr,
                               tt8Bit               locked );
extern _RPST_ tfHttpdServerFree_FP_T tfHttpdServerFree_FP;

typedef ttHttpdSrvHandlePtr (*tfHttpdGetLockedServerHandle_FP_T) (
                             ttHttpdUserSrvHandle userSrvHandle );
extern _RPST_ tfHttpdGetLockedServerHandle_FP_T tfHttpdGetLockedServerHandle_FP;

typedef ttHttpdConEntryPtr (*tfHttpdGetLockedConHandle_FP_T) (
    ttHttpdUserConHandle        userConHandle,
    ttHttpdSrvHandlePtrPtr      srvHandlePtrPtr );
extern _RPST_ tfHttpdGetLockedConHandle_FP_T tfHttpdGetLockedConHandle_FP;

#ifdef TM_LOCK_NEEDED
typedef void (*tfHttpdReturnConHandle_FP_T) ( ttHttpdConEntryPtr         conEntryPtr,
                                    ttHttpdSrvHandlePtr        srvHandlePtr,
                                    int                        unlockFlag );
#else /* !TM_LOCK_NEEDED */
typedef void (*tfHttpdReturnConHandle_FP_T) ( ttHttpdConEntryPtr         conEntryPtr);
#endif /* !TM_LOCK_NEEDED */
extern _RPST_ tfHttpdReturnConHandle_FP_T tfHttpdReturnConHandle_FP;

typedef int (*tfHttpdSendPacket_FP_T) (ttHttpdConEntryPtr conEntryPtr, int socketFlag);
extern _RPST_ tfHttpdSendPacket_FP_T tfHttpdSendPacket_FP;

typedef int (*tfHttpdGetZeroCopyBuffer_FP_T) (ttHttpdConEntryPtr conEntryPtr,
        int                socketFlag);
extern _RPST_  tfHttpdGetZeroCopyBuffer_FP_T tfHttpdGetZeroCopyBuffer_FP;

typedef void (*tfHttpdRespFinishFromSend_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                                      tt16Bit            flags);
extern _RPST_ tfHttpdRespFinishFromSend_FP_T tfHttpdRespFinishFromSend_FP;

typedef void (*tfHttpdFreeBodyBuf_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfHttpdFreeBodyBuf_FP_T tfHttpdFreeBodyBuf_FP;

typedef int (*tfHttpdGetLine_FP_T) (ttHttpdConEntryPtr conEntryPtr,
                          ttCharPtrPtr       srcPtrPtr,
                          tt32BitPtr         srcLengthPtr);
extern _RPST_ tfHttpdGetLine_FP_T tfHttpdGetLine_FP;

typedef int (*tfHttpdGetChunkLine_FP_T) (ttHttpdConEntryPtr conEntryPtr,
        ttCharPtrPtr       srcPtrPtr,
        tt32BitPtr         srcLengthPtr,
        ttIntPtr           lineLenPtr);
extern _RPST_  tfHttpdGetChunkLine_FP_T tfHttpdGetChunkLine_FP;

typedef int (*tfHttpdProcessMethodLine_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdProcessMethodLine_FP_T tfHttpdProcessMethodLine_FP;

typedef int (*tfHttpdProcessHeaderLine_FP_T)  (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfHttpdProcessHeaderLine_FP_T tfHttpdProcessHeaderLine_FP;

typedef int (*tfHttpdGetConCountByIp_FP_T) (
	    ttHttpdSrvHandlePtr  srvHandlePtr,
	    ttSockAddrStoragePtr sockAddrPtr);
extern _RPST_ tfHttpdGetConCountByIp_FP_T tfHttpdGetConCountByIp_FP;

typedef ttHttpdAuthEntryPtr (*tfHttpdFindAuth_FP_T) (
	    ttHttpdSrvEntryPtr  srvEntryPtr,
	    ttConstCharPtr      objectNamePtr);
extern _RPST_ tfHttpdFindAuth_FP_T tfHttpdFindAuth_FP;

typedef int (*tfHttpdFindAuthCb_FP_T) (
	    ttNodePtr       nodePtr,
	    ttGenericUnion  genParam);
extern _RPST_ tfHttpdFindAuthCb_FP_T tfHttpdFindAuthCb_FP;

typedef ttConstCharPtr (*tfHttpdGetUserContentType_FP_T) (
	    ttHttpdConEntryPtr conEntryPtr,
	    ttConstCharPtr     pathPtr,
	    int                flag);
extern _RPST_ tfHttpdGetUserContentType_FP_T tfHttpdGetUserContentType_FP;

typedef ttConstCharPtr (*tfHttpdFindContentType_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdFindContentType_FP_T tfHttpdFindContentType_FP;

typedef int (*tfHttpdIsGzipFile_FP_T) (ttCharPtr fileName);
extern _RPST_ tfHttpdIsGzipFile_FP_T tfHttpdIsGzipFile_FP;

typedef void (*tfHttpdChunkEncode_FP_T) (ttHttpdConEntryPtr  conEntryPtr, tt8Bit isLastPacket);
extern _RPST_ tfHttpdChunkEncode_FP_T tfHttpdChunkEncode_FP;

#ifdef TM_USE_HTTPD_SS
typedef int (*tfHttpdUserSetSsiFileFilter_FP_T)  (
	    ttHttpdUserSrvHandle    userSrvHandle,
	    ttUserConstCharPtr      matchNamePtr,
	    int                     matchType);
extern _RPST_ tfHttpdUserSetSsiFileFilter_FP_T tfHttpdUserSetSsiFileFilter_FP;

typedef int (*tfHttpdUserRegisterSsiTag_FP_T)  (
	    ttHttpdUserSrvHandle    userSrvHandle,
	    ttUserConstCharPtr      tagPtr,
	    ttHttpdUserSsiHandler   handler);
extern _RPST_ tfHttpdUserRegisterSsiTag_FP_T tfHttpdUserRegisterSsiTag_FP;

typedef int (*tfHttpdSendSsiError_FP_T) (
	    ttHttpdConEntryPtr  conEntryPtr,
	    int                 ssiErrorCode,
	    ttCharPtr           tagPtr,
	    int                 tagLen,
	    int                 socketFlag);
extern _RPST_ tfHttpdSendSsiError_FP_T tfHttpdSendSsiError_FP;

#endif /* TM_USE_HTTPD_SSI*/

typedef int (*tfHttpdUserSendFile_FP_T)  (
	    ttHttpdUserConHandle    userConHandle,
	    const char TM_FAR *     fileNamePtr,
	    int                     flags);
extern _RPST_ tfHttpdUserSendFile_FP_T tfHttpdUserSendFile_FP;

typedef int (*tfMatchFile_FP_T)  (
    ttUserConstCharPtr  filePathPtr,
    ttListPtr           filterListPtr);
extern _RPST_ tfMatchFile_FP_T tfMatchFile_FP;

typedef int (*tfHttpdAddFileToSend_FP_T) (
	    ttHttpdConEntryPtr  conEntryPtr,
	    ttConstCharPtr      filePathPtr);
extern _RPST_ tfHttpdAddFileToSend_FP_T tfHttpdAddFileToSend_FP;

typedef void (*tfHttpdFreeFile_FP_T) (
#ifdef TM_USE_FS_PARAMETER
    ttHttpdConEntryPtr  conEntryPtr,
#endif /* TM_USE_FS_PARAMETER */
    ttHttpdFilePtr      httpdFilePtr);
extern _RPST_ tfHttpdFreeFile_FP_T tfHttpdFreeFile_FP;

typedef int (*tfHttpdSendFile_FP_T) (ttHttpdConEntryPtr  conEntryPtr,
        int                 socketFlag);
extern _RPST_ tfHttpdSendFile_FP_T tfHttpdSendFile_FP;

typedef int (*tfHttpdSearchSsiTag_FP_T) (
	    ttHttpdSrvEntryPtr  srvEntryPtr,
	    ttCharPtr           bufferPtr,
	    tt16Bit             startPos,
	    tt16Bit             endPos,
	    tt16BitPtr          tagStartPosPtr,
	    tt16BitPtr          tagEndPosPtr,
	    ttCharPtrPtr        matchPtrPtr,
	    tt16BitPtr          overlapTagPosPtr);
extern _RPST_ tfHttpdSearchSsiTag_FP_T tfHttpdSearchSsiTag_FP;

typedef int (*tfHttpdTrySendBuffer_FP_T) (
	    ttHttpdConEntryPtr  conEntryPtr,
	    ttHttpdFilePtr      currFilePtr,
	    int                 lenToSend,
	    int TM_FAR *        errorCodePtr,
	    int                 socketFlag);
extern _RPST_ tfHttpdTrySendBuffer_FP_T tfHttpdTrySendBuffer_FP;

typedef void (*tfHttpdSignalSendFile_FP_T) (ttHttpdConEntryPtr conEntryPtr, int errorCode
#ifdef TM_HTTPD_CHECK_SERVER_THREAD
                                 ,tt8Bit serverThread /* from server thread? */
#endif /* TM_HTTPD_CHECK_SERVER_THREAD  */
                                 );
extern _RPST_ tfHttpdSignalSendFile_FP_T tfHttpdSignalSendFile_FP;

typedef void (*tfHttpdCgiInitArgCnt_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdCgiInitArgCnt_FP_T tfHttpdCgiInitArgCnt_FP;

typedef ttListPtr (*tfHttpdGetSsiFilterList_FP_T) (ttHttpdUserSrvHandle userSrvHandle);
extern _RPST_  tfHttpdGetSsiFilterList_FP_T tfHttpdGetSsiFilterList_FP;

typedef int (*tfHttpdUserRegisterRequestHeader_FP_T) (
	    ttHttpdUserSrvHandle    userSrvHandle,
	    ttHttpUserHeaderType    headerType);
extern _RPST_ tfHttpdUserRegisterRequestHeader_FP_T tfHttpdUserRegisterRequestHeader_FP;

typedef int (*tfHttpdUserSetEventHandler_FP_T) (
	    ttHttpdUserSrvHandle        userSrvHandle,
	    ttHttpdUserEventHandler     handler);
extern _RPST_ tfHttpdUserSetEventHandler_FP_T tfHttpdUserSetEventHandler_FP;

typedef int (*tfHttpdUserSetMallocTimeout_FP_T)(
        ttHttpdUserSrvHandle        userSrvHandle,
        int      mallocTimeout);
extern _RPST_ tfHttpdUserSetMallocTimeout_FP_T tfHttpdUserSetMallocTimeout_FP;

typedef int (*tfHttpdUserSetRedirectUrl_FP_T)(
    ttHttpdUserSrvHandle        userSrvHandle,
    char*      redirectUrl);
extern _RPST_ tfHttpdUserSetRedirectUrl_FP_T tfHttpdUserSetRedirectUrl_FP;

typedef int (*tfHttpdGetAvailSendBufferSize_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdGetAvailSendBufferSize_FP_T tfHttpdGetAvailSendBufferSize_FP;

typedef int (*tfHttpdUserSendResponseStatusLine_FP_T)  (
	    ttHttpdUserConHandle    userConHandle,
	    ttHttpUserVersion       version,
	    int                     statusCode,
	    ttUserConstCharPtr      reasonPhrasePtr,
	    int                     flags);
extern _RPST_ tfHttpdUserSendResponseStatusLine_FP_T tfHttpdUserSendResponseStatusLine_FP;

typedef int (*tfHttpdUserSendResponseHeaders_FP_T) (
    ttHttpdUserConHandle    userConHandle,
    ttUserIntPtr            headerCountPtr,
    ttHttpUserHeaderTypePtr headerTypes,
    ttUserConstCharPtrPtr   headerValues,
    int                     flags

    ,ttUserConstCharPtrPtr  headerName

    );
extern _RPST_ tfHttpdUserSendResponseHeaders_FP_T tfHttpdUserSendResponseHeaders_FP;

typedef int (*tfHttpdUserSendResponseBody_FP_T) (
	    ttHttpdUserConHandle    userConHandle,
	    ttUserConstCharPtr      bufferPtr,
	    ttUserIntPtr            bufferLenPtr,
	    int                     flags);
extern _RPST_ tfHttpdUserSendResponseBody_FP_T tfHttpdUserSendResponseBody_FP;

typedef int (*tfHttpdUserGetRequestBody_FP_T) (
	    ttHttpdUserConHandle    userConHandle,
	    ttUserCharPtr           bufferPtr,
	    ttUserIntPtr            bufferLenPtr,
	    int                     flags);
extern _RPST_ tfHttpdUserGetRequestBody_FP_T tfHttpdUserGetRequestBody_FP;

typedef void (*tfHttpdSendEnd_FP_T) (ttHttpdConEntryPtr conEntryPtr, int socketFlag);
extern _RPST_ tfHttpdSendEnd_FP_T tfHttpdSendEnd_FP;

typedef tt8Bit (*tfHttpdProcessRequestBody_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_ tfHttpdProcessRequestBody_FP_T tfHttpdProcessRequestBody_FP;

typedef void (*tfHttpdProcessResponse_FP_T)  (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfHttpdProcessResponse_FP_T tfHttpdProcessResponse_FP;

typedef void (*tfHttpdProcessRangeHeader_FP_T) (
	    ttHttpdConEntryPtr  conEntryPtr,
	    ttCharPtr           rangeSpecPtr);
extern _RPST_ tfHttpdProcessRangeHeader_FP_T tfHttpdProcessRangeHeader_FP;

typedef int (*tfHttpdUserSetFSparam_FP_T) (
	    ttHttpdUserSrvHandle    userSrvHandle,
	    ttUserVoidPtr           userFSparamPtr);
extern _RPST_ tfHttpdUserSetFSparam_FP_T tfHttpdUserSetFSparam_FP;

typedef void (*tfxHttpdRange_FP_T) (ttHttpdConEntryPtr conEntryPtr);
extern _RPST_  tfxHttpdRange_FP_T tfxHttpdRange_FP;

typedef int (*tfHttpdUserSetOptions_FP_T) (ttHttpdUserSrvHandle userSrvHandle,
        int                  optName,
        const char TM_FAR   *optVal,
        int                  optLen);
extern _RPST_  tfHttpdUserSetOptions_FP_T tfHttpdUserSetOptions_FP;

//#ifdef TM_USE_STOP_TRECK
typedef	void (*tfHttpdDeInit_FP_T)  (
		#ifdef TM_MULTIPLE_CONTEXT
		                ttUserContext contextHandle
		#else /* !TM_MULTIPLE_CONTEXT */
		                void
		#endif /* !TM_MULTIPLE_CONTEXT */
		                );
extern _RPST_ tfHttpdDeInit_FP_T tfHttpdDeInit_FP;

typedef int (*tfHttpdUserIsAuthSuccess_FP_T) (
	    ttHttpdUserConHandle    userConHandle);
extern _RPST_  tfHttpdUserIsAuthSuccess_FP_T tfHttpdUserIsAuthSuccess_FP;

typedef int (*tfHttpdUserGetSockDesc_FP_T) (
	    ttHttpdUserConHandle    userConHandle);
extern _RPST_   tfHttpdUserGetSockDesc_FP_T tfHttpdUserGetSockDesc_FP;

#if 1//def GSN_SSL_SERVER_SUPPORT
typedef void (*tfHttpdSendSemTmrCb_FP_T) (void * tmrBlockPtr, ttGenericUnion usrParm1,
                   ttGenericUnion  usrParm2);
extern _RPST_ tfHttpdSendSemTmrCb_FP_T tfHttpdSendSemTmrCb_FP;

typedef int (*tfHttpdUserAddResponseLineHdrs_FP_T) (
    ttHttpdUserConHandle    userConHandle,
    ttUserConstCharPtr      reasonPhrasePtr,
    ttUser32Bit             reasonPhraseLen,
    ttUser32Bit             uconCustomHdrcount,
    ttUserConstCharPtr      *uconCustomHeaderstype,
    ttUserConstCharPtr      *uconCustomHeadersval);
extern _RPST_ tfHttpdUserAddResponseLineHdrs_FP_T tfHttpdUserAddResponseLineHdrs_FP;

#endif
#endif   /*_TRHTTPD_FPT_*/
