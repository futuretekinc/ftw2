/******************************************************************************
 *
 *               COPYRIGHT (c) 2006-2010 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_osif_fpt.h,v $
 *
 * Project: GSN APP Software
 *
 * Description : Greenhills OS specific functions
 *
 * Author : ram
 *
 */

#ifndef _GSN_OSIF_FPT_
#define _GSN_OSIF_FPT_

#ifdef OS_UVEL
#include <arm_ghs.h> /* For ARM7 intrinsics */
#endif
#define OS_NO_C_LIB_DEFINES
#include "supplicant/utils/includes.h"
#ifdef OS_UVEL
#include "time.h"
#endif
#include "supplicant/utils/os.h"
#include "gsn_includes.h"

#include "security/hw_engine_if/gsn_hw_engine_if.h"

typedef void (*os_sleep_FP_T)(os_time_t sec, os_time_t usec);
extern _RPST_ os_sleep_FP_T os_sleep_FP;

typedef int (*os_get_time_FP_T)(struct os_time *t);
extern _RPST_ os_get_time_FP_T os_get_time_FP;

typedef int (*os_get_random_FP_T)(unsigned char *buf, size_t len);
extern _RPST_ os_get_random_FP_T os_get_random_FP;

typedef unsigned long (*os_random_FP_T)(void);
extern _RPST_ os_random_FP_T os_random_FP;

typedef void* (*os_zalloc1_FP_T)(size_t size, UINT16 line);
extern _RPST_ os_zalloc1_FP_T os_zalloc1_FP;

typedef void* (*os_malloc1_FP_T)(size_t size, UINT16 line);
extern _RPST_ os_malloc1_FP_T os_malloc1_FP;

typedef void* (*os_realloc1_FP_T)(void *ptr, size_t size, UINT16 line );
extern _RPST_ os_realloc1_FP_T os_realloc1_FP;

typedef void (*os_free1_FP_T)(void *ptr, UINT16 line);
extern _RPST_ os_free1_FP_T os_free1_FP;

typedef char * (*os_strdup_FP_T)(const char *s);
extern _RPST_ os_strdup_FP_T os_strdup_FP;

typedef int (*os_snprintf_FP_T)(char *str, size_t size, const char *format, ...);
extern _RPST_ os_snprintf_FP_T os_snprintf_FP;

typedef int (*os_mktime_FP_T)(int year, int month, int day, int hour, int min, int sec,
          os_time_t *t);
extern _RPST_ os_mktime_FP_T os_mktime_FP;

typedef size_t (*os_strlcpy_FP_T)(char *dest, const char *src, size_t siz);
extern _RPST_ os_strlcpy_FP_T os_strlcpy_FP;

typedef int (*os_strcasecmp_FP_T)(const char *s1, const char *s2);
extern _RPST_ os_strcasecmp_FP_T os_strcasecmp_FP;

#endif /* _GSN_OSIF_FPT_ */