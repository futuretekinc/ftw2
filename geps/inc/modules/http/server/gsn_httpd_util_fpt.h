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
* $RCSfile: gsn_httpd_util_fpt.h,v $
*
* Description : This file contains the function pointers definitions.
*******************************************************************************/

#ifndef GSN_HTTPD_UTIL_FPT_H_
#define GSN_HTTPD_UTIL_FPT_H_

typedef INT32 (*GsnHttpd_SendBuffer_FP_T) (ttHttpdUserConHandle  conHandle,
		                  const   INT8         *bufferPtr,
                          INT32                 bufferLen,
                          INT32                 flag,
                          INT32                *errorCodePtr);

typedef INT32 (*GsnHttpd_SendLastChunk_FP_T) (ttHttpdUserConHandle conHandle, INT32 *errorCodePtr);

typedef INT32 (*GsnHttpd_SendBufferAndLastChunk_FP_T) (ttHttpdUserConHandle conHandle,
        const INT8 *bufferPtr, INT32 bufferLen, INT32 flag, INT32 *errorCodePtr);

typedef ttHttpUserMethod (*GsnHttpd_GetHttpMethod_FP_T) (ttHttpdUserConHandle conHandle);

typedef INT8* (*GsnHttpd_GetBuffer_FP_T) ();

typedef void (*GsnHttpd_ReleaseBuffer_FP_T) (INT8 *bufPtr);

extern _RPST_ GsnHttpd_SendBuffer_FP_T GsnHttpd_SendBuffer_FP;

extern _RPST_ GsnHttpd_SendLastChunk_FP_T GsnHttpd_SendLastChunk_FP;

extern _RPST_ GsnHttpd_SendBufferAndLastChunk_FP_T GsnHttpd_SendBufferAndLastChunk_FP;

extern _RPST_ GsnHttpd_GetHttpMethod_FP_T GsnHttpd_GetHttpMethod_FP;

extern _RPST_ GsnHttpd_GetBuffer_FP_T GsnHttpd_GetBuffer_FP;

extern _RPST_ GsnHttpd_ReleaseBuffer_FP_T GsnHttpd_ReleaseBuffer_FP;

#endif /* GSN_HTTPD_UTIL_FPT_H_ */
