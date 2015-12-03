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
* $RCSfile: gsn_httpd_logo.h,v
*/

#ifndef GSN_HTTPD_LOGO_H_
#define GSN_HTTPD_LOGO_H_
/**
 *******************************************************************************
 * @file gsn_httpd_logo.h
 * @brief GSN HTTPD API for fetching Logo
 ******************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of structure containing logo information
 ******************************************************************************/
typedef struct GSN_HTTPD_LOGO_INFO
{
    UINT16 size; /**< Size of logo */
    INT8* location; /**< Address (locaiton) of logo */
} GSN_HTTPD_LOGO_INFO_T;

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of callback Logo callback API.
 ******************************************************************************/
typedef void (*GSN_HTTPD_LOGO_INFO_CB_T)(GSN_HTTPD_LOGO_INFO_T* pInfo);

/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Initialize HTTP Logo API module
 *    This function initializes the Log API module taking a callback function
 *    as paramter
 * @param cbFn - IN Pointer to callback function
 ******************************************************************************/
UINT8 GsnHttpdApi_LogoInit(GSN_HTTPD_LOGO_INFO_CB_T cbFn);

/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief UnInitialize HTTP Logo API module
 *    This function uninitializes the Logo API module
 *    
 ******************************************************************************/
VOID GsnHttpdApi_LogoDeInit();


#endif /* GSN_HTTPD_LOGO_H_ */
