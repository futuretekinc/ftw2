/***************************************************************************
 *
 *            Copyright (c) 2010-2011 by HCC Embedded
 *
 * This software is copyrighted by and is the sole property of
 * HCC.  All rights, title, ownership, or other interests
 * in the software remain the property of HCC.  This
 * software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 *
 * This Copyright notice may not be removed or modified without prior
 * written consent of HCC.
 *
 * HCC reserves the right to modify this software without notice.
 *
 * HCC Embedded
 * Budapest 1133
 * Vaci Ut 76
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/
#ifndef _OAL_TASK_H
#define _OAL_TASK_H

#include <stdint.h>
#include "fs/config/config_oal.h"
#include "fs/oal/oal_common.h"
#include "fs/oal/os/oalp_defs.h"
#include "fs/oal/os/oalp_task.h"

#if OAL_TASK_POLL_MODE
 #if OAL_TASK_SLEEP_SUPPORTED
  #include "../psp/include/psp_sleep.h"
 #endif
#endif

#include "fs/version/ver_oal.h"
#if VER_OAL_MAJOR != 2 || VER_OAL_MINOR != 1
 #error Incompatible OAL version number!
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef  OAL_TASK_FN ( *oal_task_fn_t );

typedef struct
{
  const char   * name;
  oal_task_fn_t  entry;
  uint32_t       priority;
  uint32_t       stack_size;
#if OAL_STATIC_TASK_STACK
  uint32_t     * stack_ptr;
#endif
} oal_task_dsc_t;

#if OAL_STATIC_TASK_STACK
 #define OAL_TASK_DSC( name, entry, priority, stack_size ) \
  static uint32_t entry##_stack[( ( stack_size ) + sizeof( uint32_t ) - 1 ) / sizeof( uint32_t )]; \
  static const oal_task_dsc_t  entry##_dsc = \
  { \
    ( name ) \
    , ( entry ) \
    , ( priority ) \
    , ( stack_size ) \
    , &entry##_stack[0] \
  }
#else
 #define OAL_TASK_DSC( name, entry, priority, stack_size ) \
  static const oal_task_dsc_t entry##_dsc = \
  { \
    ( name ) \
    , ( entry ) \
    , ( priority ) \
    , ( stack_size ) \
  }
#endif /* if OAL_STATIC_TASK_STACK */

int oal_task_create ( oal_task_t * p_task, const oal_task_dsc_t * task_dsc, oal_task_id_t * task_id );
int oal_task_delete ( oal_task_t * p_task );
void oal_task_yield ( void );
oal_task_id_t oal_task_get_id ( void );
#if OAL_TASK_POLL_MODE
 #define oal_task_sleep psp_sleep
#else
void oal_task_sleep ( uint32_t ms );
#endif

#ifdef __cplusplus
}
#endif

#endif /* ifndef _OAL_TASK_H */

