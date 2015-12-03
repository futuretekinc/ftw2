/******************************************************************************
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
* $RCSfile: version.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _VERSION_H_
#define _VERSION_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 ******************************************************************************
 * @ingroup GsnVersion
 * @brief Major Version.
 *
 *    This macro defines the Major version of the GEPS release in use. The maximum value
 *    can be 255, since this is interpreted as an 8-bit field. The Major version
 *    changes if there is a major design change which is not backward-
 *    compatible with older versions of the code.
 *****************************************************************************/
#define GSN_MAJOR_VERSION 4

/**
 ******************************************************************************
 * @ingroup GsnVersion
 * @brief Minor Version.
 *
 *    This macro defines the Minor version of the GEPS release in use. The maximum value
 *    can be 255, since this is interpreted as an 8-bit field. The Minor version
 *    changes if there are any bug fixes or design changes which are backward-
 *    compatible with the previous GEPS code base.
 *****************************************************************************/
#define GSN_MINOR_VERSION 1

/**
 ******************************************************************************
 * @ingroup GsnVersion
 * @brief Build Version.
 *    This macro defines the Build version of the GEPS release in use. The maximum value
 *    can be 65535, since this is interpreted as a 16-bit field. The Build
 *    version changes if the code is rebuilt and delivered without
 *    any changes in the code having been made.
 *****************************************************************************/
#define GSN_BUILD_VERSION 0

/**
 ******************************************************************************
 * @ingroup GsnVersion
 * @brief GSN Version.
 *    This macro defines the overall GEPS version, to be interpreted as
 *    shown below.
 * \verbatim
 *     | major Version | Minor Version | Build Version |
 *     |    8 bits     |   8 bits      |   16 Bits     |
 *  \endverbatim
 *****************************************************************************/
#define GSN_PLATFORM_VERSION (( GSN_MAJOR_VERSION << 24 ) | \
    ( GSN_MINOR_VERSION << 16 ) | GSN_BUILD_VERSION )

#ifdef __cplusplus
}
#endif

#endif /* _GSN_FLASH_FPT_H_ */


