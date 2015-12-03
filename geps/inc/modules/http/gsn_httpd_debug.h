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
* $RCSfile: gsn_httpd_debug.h,v
*/

#ifndef GSN_HTTPD_DEBUG_H_
#define GSN_HTTPD_DEBUG_H_

/**
 *******************************************************************************
 * @file gsn_httpd.h
 * @brief GSN HTTPD Public header
 *    This file contains definitions that control debugging prints from GSN
 *    HTTPD Server and HTTP API modules
 ******************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Define this flag to enable debug prints
 ******************************************************************************/
//#define HTTPD_DEBUG

extern void App_DebugPrintf(const char *format, ...);

#ifdef HTTPD_DEBUG
#define HTTPD_DEBUG_VAL 1
#else
#define HTTPD_DEBUG_VAL 0
#endif

//#define HTTPD_DEBUG_PRINT(x) do { if (HTTPD_DEBUG_VAL) App_DebugPrintf x; } while (0)
//#define HTTPD_DEBUG_PRINT(x) do { if (HTTPD_DEBUG_VAL) printf x; } while (0)
#define HTTPD_DEBUG_PRINT(x) do { } while (0)

#endif /* GSN_HTTPD_DEBUG_H_ */
