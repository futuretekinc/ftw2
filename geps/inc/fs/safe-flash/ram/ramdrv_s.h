/****************************************************************************
 *
 *            Copyright (c) 2005-2011 by HCC Embedded
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
 * Vaci ut 110
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/
#ifndef _RAMDRV_S_H_
#define _RAMDRV_S_H_

#include "fs/safe-flash/common/fsf.h"

#include "fs/version/ver_safe_ram.h"
#if VER_SAFE_RAM_MAJOR != 1
 #error "VER_SAFE_RAM_MAJOR invalid"
#endif
#if VER_SAFE_RAM_MINOR != 0
 #error "VER_SAFE_RAM_MINOR invalid"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int fs_mount_ramdrive ( FS_VOLUMEDESC * vd, FS_PHYGETID phyfunc );

#ifdef __cplusplus
}
#endif

#endif  /* _RAMDRV_S_H_ */

