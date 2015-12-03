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
#ifndef _OAL_MUTEX_H
#define _OAL_MUTEX_H

#include "fs/oal/oal_common.h"
#include "fs/oal/os/oalp_defs.h"
#include "fs/oal/os/oalp_mutex.h"

#include "fs/version/ver_oal.h"
#if VER_OAL_MAJOR != 2 || VER_OAL_MINOR != 1
 #error Incompatible OAL version number!
#endif

#ifdef __cplusplus
extern "C" {
#endif

int oal_mutex_create ( oal_mutex_t * p_mutex );
int oal_mutex_delete ( oal_mutex_t * p_mutex );
int oal_mutex_get ( oal_mutex_t * p_mutex );
int oal_mutex_put ( oal_mutex_t * p_mutex );

#ifdef __cplusplus
}
#endif

#endif /* ifndef _OAL_MUTEX_H */

