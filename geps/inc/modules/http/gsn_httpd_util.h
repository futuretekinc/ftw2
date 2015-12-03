/*******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: gsn_httpd_util.h,v $
*
* Description : Header file for gsn httpd public functions and data structures
*******************************************************************************/
#ifndef _GSN_HTTPD_UTIL_H
#define _GSN_HTTPD_UTIL_H

//#ifdef GSN_WEB_SERVER

//#include <trsocket.h>
#include "gsn_types.h"
#include "modules/http/gsn_httpd.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"

/**
 *******************************************************************************
 * @file gsn_httpd_util.h
 * @brief GSN HTTPD Utility Functions Public header
 *    This file contains definitions for some HTTPD Utility functions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Send Buffer
 *
 *    This function sends the buffer on the HTTP connection
 * @param conHandle - IN Pointer to connection handle
 * @param bufferPtr - IN Pointer to buffer
 * @param bufferLen - IN Length of Buffer
 * @param flag - IN Flags determining send behavior
 * @param errorCodePtr - OUT Indicates error code, if any
 * @retval Number of bytes sent
 ******************************************************************************/
INT32 GsnHttpd_SendBuffer(ttHttpdUserConHandle   conHandle,
                            const char *bufferPtr, INT32 bufferLen,
                            INT32 flag, INT32 *errorCodePtr);

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Send Buffer and indicate terminating chunk
 *
 *    This function sends the buffer and also sends information indicating that
 *    it is the terminating chunk
 * @param conHandle - IN Pointer to connection handle
 * @param bufferPtr - IN Pointer to buffer
 * @param bufferLen - IN Length of Buffer
 * @param flag - IN Flags determining send behavior
 * @param errorCodePtr - OUT Indicates error code, if any
 * @retval Number of bytes sent
 ******************************************************************************/
INT32 GsnHttpd_SendBufferAndLastChunk(ttHttpdUserConHandle   conHandle,
                            const INT8 *bufferPtr, INT32 bufferLen,
                            INT32 flag, INT32 *errorCodePtr);

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Sends terminating chunk
 *
 *    This function sends the terminating chunk on the HTTP connection
 * @param conHandle - IN Pointer to connection handle
 * @param errorCodePtr - OUT Indicates error code, if any
 * @retval GSN_HTTPD_FAILURE Failure to Send
 * @retval GSN_HTTPD_SUCCESS Sent successfully
 ******************************************************************************/
INT32 GsnHttpd_SendLastChunk(ttHttpdUserConHandle conHandle, INT32 *errorCodePtr);

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Get a buffer to use for sending HTTP response
 *
 *    This function returns a buffer that can be used for sending HTTP response
 * @retval buffer Pointer to buffer
 ******************************************************************************/
INT8* GsnHttpd_GetBuffer();

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Release the buffer that was allocated by HTTPD
 *
 * @retval None
 ******************************************************************************/
void
GsnHttpd_ReleaseBuffer(INT8 *bufPtr);

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Gets the HTTP method invoked on the connection handle
 *
 *    This function returns the HTTP  method invoked by the client on the HTTP
 *    connection handle.
 * @retval  ttHttpUserMethod HTTP Method invoked
 ******************************************************************************/
ttHttpUserMethod GsnHttpd_GetHttpMethod(ttHttpdUserConHandle conHandle);

/**
 *******************************************************************************
 * @ingroup GsnHttpd
 * @brief Extracts the string from xml_str
 *    This function extracts the string from a xml_str representation.
 * @param str - IN/OUT Pointer to str which will be populated
 * @param xml_str - IN GSN_XML_STRING_T representation
 * @param str_len - IN Length of str
 ******************************************************************************/
void GsnHttpd_SetStrFromXmlStr(UINT8* str, GSN_XML_STRING_T xml_str, int str_len);

//#endif
#endif
