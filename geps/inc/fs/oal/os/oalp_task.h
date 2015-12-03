/***************************************************************************
 *
 *            Copyright (c) 2010-2012 by HCC Embedded
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
#ifndef _OALP_TASK_H
#define _OALP_TASK_H

#include <stdint.h>
#include "rtos/tx_api.h"

#include "fs/version/ver_oal_os.h"
#if VER_OAL_THREADX_MAJOR != 1 || VER_OAL_THREADX_MINOR != 1
 #error Incompatible OAL_THREADX version number!
#endif
#include "fs/version/ver_oal.h"
#if VER_OAL_MAJOR != 2 || VER_OAL_MINOR != 1
 #error Incompatible OAL version number!
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef TX_THREAD *   oal_task_id_t;
typedef TX_THREAD     oal_task_t;

#define OAL_TASK_FN( fn ) void( fn ) (unsigned long param)
#define OAL_TASK_PRE

#ifdef __cplusplus
}
#endif

#endif /* ifndef _OALP_TASK_H */

