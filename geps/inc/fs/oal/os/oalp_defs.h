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
#ifndef _OALP_DEFS_H
#define _OALP_DEFS_H

#include "fs/config/config_oal_os.h"

#include "fs/version/ver_oal_os.h"
#if VER_OAL_THREADX_MAJOR != 1 || VER_OAL_THREADX_MINOR != 1
 #error Incompatible OAL_THREADX version number!
#endif
#include "fs/version/ver_oal.h"
#if VER_OAL_MAJOR != 2 || VER_OAL_MINOR != 1
 #error Incompatible OAL version number!
#endif


/* tasks are polled - only set with no OS */
#define OAL_TASK_POLL_MODE    0

/* preemptive system */
#define OAL_PREEMPTIVE        1

/* stack of a task needs to be allocated statically */
#define OAL_STATIC_TASK_STACK 1

/* allow interrupts - can only be unset if no OS */
#define OAL_INTERRUPT_ENABLE  1

/* use platform ISR routines */
#define OAL_USE_PLATFORM_ISR  1


#endif /* ifndef _OALP_DEFS_H */

