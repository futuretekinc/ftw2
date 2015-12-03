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
* $RCSfile: trcommon_fpt.h,v $
*
* Description : This file contains the function pointers definitions.
*******************************************************************************/
#ifndef _TRCOMMON_FPT_H_

#define _TRCOMMON_FPT_H_

#include <string.h>
#include "netx/netx_bsd_layer/nxd_bsd.h"
#include "modules/http/include/trsocket.h"

#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"
//#include "trhttpc.h"

typedef int (* tfZeroCopyRecv_FP_T)(int                   socketDescriptor, 
                   ttUserMessage TM_FAR *bufferHandlePtr, 
                   char TM_FAR * TM_FAR *dataPtrPtr,
                   int                   maxDataLength,
                   int                   flags,
                   ttUserMessage TM_FAR *nextPacketPtr,
                   int *errorCode);

typedef int (* tfNextPacketGet_FP_T)(NX_PACKET *nx_packet_next, char TM_FAR * TM_FAR *dataPtrPtr,
                   NX_PACKET **nextPacketPtr);

typedef int (* tfBlockingState_FP_T)(int socketDescriptor, int blockingState);                   

typedef int (* tfGetSocketError_FP_T)(int socketDescriptor);

typedef int (* tfFreeZeroCopyBuffer_FP_T)(ttUserMessage Buff);


typedef ttUserMessage (*tfGetZeroCopyBuffer_FP_T) (
		                                  void                 * poolHndl,
		                                  int                  * sizePtr,
		                                  char TM_FAR * TM_FAR * dataPtrPtr,
		                                  int                    timeout,
		                                  int                  * errorCodePtr);

typedef void (*gsn_bsd_cb_wrapper_FP_T)(int socket_id, NX_BSD_CB_EVENT_TYPE_T event, VOID *cbCtx1, VOID *cbCtx2);

typedef int (* tfRegisterSocketCBParam_FP_T) (
        int                         socketDescriptor,
        ttUserSocketCBParamFuncPtr  socketCBParamFuncPtr,
        void                      * socketUserPtr,
        int                         flags );

typedef int (* tfClose_FP_T) (int socketDescriptor);

typedef int (* tfResetConnection_FP_T) (int socketDescriptor);

typedef int (* tfZeroCopySend_FP_T) (
        int           socketDescriptor,
        ttUserMessage bufferHandle,
        int           bufferLength,
        int           flags );

typedef int (* tfGetMssLen_FP_T) (int socketDescriptor);

typedef void * (* tfTimerAdd_FP_T) ( ttTmCBFuncPtr  callBackFunctionPtr,
                   ttGenericUnion userParm1,
                   ttGenericUnion userParm2,
                   tt32Bit        timerMilliSec,
                   tt8Bit         timerFlags);

typedef void (* gsnhttpd_timer_expiration_fn_FP_T) (unsigned long info);

typedef void (* tfTimerRemove_FP_T) (ttTimerPtr timerBlockPtr);

typedef void (* tfTimerSuspend_FP_T) (ttTimerPtr timerBlockPtr);

typedef void (* tfTimerNewTime_FP_T) (ttTimerPtr tmrPtr, tt32Bit timeParam);

typedef void (* tfKernelError_FP_T) (
	    const char TM_FAR * functionName,
	    const char TM_FAR * errorMessage);

typedef int (* tfFSCloseFile_FP_T) (ttVoidPtr userDataPtr,
                   ttVoidPtr fileDataPtr);

typedef ttUser32Bit (* tfFSGetFileLen_FP_T) (
        ttConstVoidPtr userDataPtr,
        ttConstCharPtr pathNamePtr );

typedef int (* tfFSFileExists_FP_T) (
	    ttConstVoidPtr userDataPtr, ttConstCharPtr pathNamePtr );

typedef int (* tfFSSeekFile_FP_T) (
	    void TM_FAR *       userDataPtr,
	    void TM_FAR *       fileDataPtr,
	    long                offset,
	    int                 whence);

typedef int (* tfFSReadFile_FP_T) (
	    void TM_FAR * userDataPtr,
	    void TM_FAR * fileDataPtr,
	    char TM_FAR * bufferPtr,
	    int           bytes );

typedef void TM_FAR * (* tfFSOpenFile_FP_T) (
	    const void TM_FAR * userDataPtr,
	    const char TM_FAR * pathNamePtr,
	    int                 flag,
	    int                 type,
	    int                 structure );

typedef int (* tfKernelGetSystemTime_FP_T) (ttUser32BitPtr daysPtr, ttUser32BitPtr secondsPtr);

typedef int (* tfGetUtcTime_FP_T) (
	    ttConst32BitPtr daysPtr,
	    ttConst32BitPtr secondsPtr,
	    ttTimePtr       timePtr);

typedef ttCharPtr (* tfCopyString_FP_T) (ttCharPtr destPtr, ttConstCharPtr stringPtr);

typedef ttCharPtr (* tfGetTimeString_FP_T) (ttTimePtr timePtr, ttCharPtr timeStrPtr,
                          int timeStrLen, int format);

typedef ttCharPtr (* tfUlongDecimalToString_FP_T) (ttCharPtr destPtr, tt32Bit ulongDecNum);

typedef int (* tfBase64Decode_FP_T) (ttCharPtr inPtr,
        int       inLen,
        ttCharPtr outPtr,
        int       outLen,
        tt8Bit    bypassNewlines);

typedef int (* tfBase64DecodedLen_FP_T) (ttCharPtr encodedPtr, int encodedLen);

typedef void (* tfServerRemoveFromQueue_FP_T) ( ttServerQueueHeadPtr  servQueueHeadPtr,
        ttServerQueuePtr      servQueuePtr,
        int                   queueIndex);

typedef void (* tfServerAppendToQueue_FP_T) ( ttServerQueueHeadPtr  servQueueHeadPtr,
        ttServerQueuePtr      servQueuePtr,
        int                   queueIndex );

typedef void (* tfListInit_FP_T) (ttListPtr listPtr);

typedef ttNodePtr (* tfListWalk_FP_T) (
	    ttListPtr               listPtr,
	    ttListCBFuncPtr         listCBFuncPtr,
	    ttGenericUnion          genParam);

typedef void (* tfListAddToTail_FP_T) (ttListPtr listPtr, ttNodePtr nodePtr);

typedef void (* tfListFree_FP_T) (ttListPtr listPtr);

typedef void (* tfBcopy_FP_T) ( const void   TM_FAR * sourcePtr,
        void         TM_FAR * destinationPtr,
        unsigned int length );

typedef void (* tfListRemove_FP_T) (ttListPtr listPtr, ttNodePtr nodePtr);

typedef int (* tfBase64Encode_FP_T) (ttCharPtr inPtr, int inLen, ttCharPtr outPtr, int outLen);

typedef int (* tfBase64OutputLen_FP_T) (ttCharPtr inPtr, int inLen);

typedef char TM_FAR * (* tfLongToString_FP_T) (ttUserS32Bit  number,
        char TM_FAR * string,
        unsigned int  stringLength,
        unsigned int  base);

extern _RPST_ tfZeroCopyRecv_FP_T tfZeroCopyRecv_FP;
extern _RPST_ tfNextPacketGet_FP_T tfNextPacketGet_FP;
extern _RPST_ tfBlockingState_FP_T tfBlockingState_FP;
extern _RPST_ tfGetSocketError_FP_T tfGetSocketError_FP;
extern _RPST_ tfFreeZeroCopyBuffer_FP_T tfFreeZeroCopyBuffer_FP;
extern _RPST_ tfGetZeroCopyBuffer_FP_T tfGetZeroCopyBuffer_FP;
extern _RPST_ gsn_bsd_cb_wrapper_FP_T gsn_bsd_cb_wrapper_FP;
extern _RPST_ tfRegisterSocketCBParam_FP_T tfRegisterSocketCBParam_FP;
extern _RPST_ tfClose_FP_T tfClose_FP;
extern _RPST_ tfResetConnection_FP_T tfResetConnection_FP;
extern _RPST_ tfZeroCopySend_FP_T tfZeroCopySend_FP;
extern _RPST_ tfGetMssLen_FP_T tfGetMssLen_FP;
extern _RPST_ tfTimerAdd_FP_T tfTimerAdd_FP;
extern _RPST_ gsnhttpd_timer_expiration_fn_FP_T gsnhttpd_timer_expiration_fn_FP;
extern _RPST_ tfTimerRemove_FP_T tfTimerRemove_FP;
extern _RPST_ tfTimerSuspend_FP_T tfTimerSuspend_FP;
extern _RPST_ tfTimerNewTime_FP_T tfTimerNewTime_FP;
extern _RPST_ tfKernelError_FP_T tfKernelError_FP;
extern _RPST_ tfFSCloseFile_FP_T tfFSCloseFile_FP;
extern _RPST_ tfFSGetFileLen_FP_T tfFSGetFileLen_FP;
extern _RPST_ tfFSFileExists_FP_T tfFSFileExists_FP;
extern _RPST_ tfFSSeekFile_FP_T tfFSSeekFile_FP;
extern _RPST_ tfFSReadFile_FP_T tfFSReadFile_FP;
extern _RPST_ tfFSOpenFile_FP_T tfFSOpenFile_FP;
extern _RPST_ tfKernelGetSystemTime_FP_T tfKernelGetSystemTime_FP;
extern _RPST_ tfCopyString_FP_T tfCopyString_FP;
extern _RPST_ tfGetUtcTime_FP_T tfGetUtcTime_FP;
extern _RPST_ tfGetTimeString_FP_T tfGetTimeString_FP;
extern _RPST_ tfUlongDecimalToString_FP_T tfUlongDecimalToString_FP;
extern _RPST_ tfBase64Decode_FP_T tfBase64Decode_FP;
extern _RPST_ tfBase64DecodedLen_FP_T tfBase64DecodedLen_FP;
extern _RPST_ tfServerRemoveFromQueue_FP_T tfServerRemoveFromQueue_FP;
extern _RPST_ tfServerAppendToQueue_FP_T tfServerAppendToQueue_FP;
extern _RPST_ tfListInit_FP_T tfListInit_FP;
extern _RPST_ tfListWalk_FP_T tfListWalk_FP;
extern _RPST_ tfListAddToTail_FP_T tfListAddToTail_FP;
extern _RPST_ tfListFree_FP_T tfListFree_FP;
extern _RPST_ tfBcopy_FP_T tfBcopy_FP;
extern _RPST_ tfListRemove_FP_T tfListRemove_FP;
extern _RPST_ tfBase64Encode_FP_T tfBase64Encode_FP;
extern _RPST_ tfBase64OutputLen_FP_T tfBase64OutputLen_FP;
extern _RPST_ tfLongToString_FP_T tfLongToString_FP;

#endif
