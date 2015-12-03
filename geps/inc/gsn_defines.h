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
* $RCSfile: gsn_defines.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

#ifndef _GSN_DEFINES_H_
#define _GSN_DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_types.h"

/**
 *****************************************************************************
 * @file gsn_defines.h
 * @brief GSN General Definitions.
 *    This file contains general definitions.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnDefines GSN Definitions
 * @brief This module Contains General Definitions.
 *
 * \verbatim
 * PUBLIC is actually defined as blank.
 * PRIVATE is replaced with the "static" descriptor.
 * TRUE is replaced with 1, FALSE with 0
 * Compile-dependent definitions are provided for INLINE
 * BIT(n) provides n-bit offsets
 * A UINT32 with all bits = 1 is defined.
 *
 *\endverbatim
 *****************************************************************************/
/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

/*****************************************************************************
  *  Definitions
  ****************************************************************************/

#ifndef PUBLIC
#define PUBLIC
#endif

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef VOID
#define VOID void
#endif

#if !defined(NULL)
#define NULL ((void *)0)
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef INLINE
#ifdef __cplusplus
#define INLINE inline
//#error "defined INLINE as inline"
#else
#define INLINE inline
//#error "defined INLINE as __inline"
#endif  /* __cplusplus */
#endif /*INLINE */

#ifndef BIT
#define BIT(n) (1 << (n))
#endif

#define GSN_UINT32_ALL_BITS_SET     (UINT32)0xFFFFFFFF

/*
Notification callback type 
*/

typedef VOID (* GSN_NOTIFICATION_FUNC_T)(INT32 arg1, VOID *arg2);

typedef VOID (* GSN_NOTIFICATION_FUNC_PARAM_T)(INT32 arg1, VOID *arg2, VOID * arg3);

/* 
Rom Patch function pointer storage type
When the ROM Patch lib is generated for application the storage type used there
is const but when it is generated for ROM project it is defined to nothing, so
that it occupies in RAM.
*/
#ifndef _RPST_
#define _RPST_
#endif

#ifdef __cplusplus

}
#endif

#endif /* _GSN_DEFINES_H_ */





