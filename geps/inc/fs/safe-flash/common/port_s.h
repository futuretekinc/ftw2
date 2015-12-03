/****************************************************************************
 *
 *            Copyright (c) 2005-2012 by HCC Embedded
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
 * Vaci ut 76
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/

#ifndef _PORT_S_H_
#define _PORT_S_H_

#include <stdint.h>
#include "fs/config/config_safe.h"

#include "fs/version/ver_safe.h"
#if VER_SAFE_MAJOR != 4
 #error "VER_SAFE_MAJOR invalid"
#endif

#if VER_SAFE_MINOR != 2
 #error "VER_SAFE_MINOR invalid"
#endif

#if FS_CAPI_USED
 #include "../../capi/common/fw_multi.h"
#else

 #if FS_MAXTASK != 1

#include "fs/oal/oal_mutex.h"
#include "fs/oal/oal_task.h"

  #ifdef __cplusplus
extern "C" {
  #endif

  #define FS_MUTEX_TYPE oal_mutex_t
  #define FS_MUTEX_CREATE( pmutex ) oal_mutex_create( pmutex )
  #define FS_MUTEX_DELETE( pmutex ) oal_mutex_delete( pmutex )
  #define FS_MUTEX_GET( pmutex )    oal_mutex_get( pmutex )
  #define FS_MUTEX_PUT( pmutex )    oal_mutex_put( pmutex )

  #define F_TASKID_TYPE oal_task_id_t
  #define F_GETTASK_ID()            oal_task_get_id()

  #ifdef __cplusplus
}
  #endif


 #else /* #if FS_MAXTASK != 1 */


  #ifdef __cplusplus
extern "C" {
  #endif

  #define FS_MUTEX_TYPE uint32_t
  #define FS_MUTEX_CREATE( pmutex ) ( 0 )
  #define FS_MUTEX_DELETE( pmutex ) ( 0 )
  #define FS_MUTEX_GET( pmutex )    ( 0 )
  #define FS_MUTEX_PUT( pmutex )    ( 0 )

  #define F_TASKID_TYPE uint32_t
  #define F_GETTASK_ID()            ( 1u )

  #ifdef __cplusplus
}
  #endif

 #endif /* #elif FS_MAXTASK != 1 */


#endif /* #elif FS_CAPI_USED */

#endif /* _PORT_S_H_ */


