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
#ifndef _OAL_ISR_H
#define _OAL_ISR_H

#include <stdint.h>
#include "fs/oal/oal_common.h"
#include "fs/oal/os/oalp_defs.h"
#include "fs/config/config_oal.h"

#if OAL_USE_PLATFORM_ISR
 #if OAL_ISR_SUPPORTED
  #include "../psp/target/isr/psp_isr.h"
 #endif
#else
#include "fs/oal/os/oalp_isr.h"
#endif

#include "fs/version/ver_oal.h"
#if VER_OAL_MAJOR != 2 || VER_OAL_MINOR != 1
 #error Incompatible OAL version number!
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OAL_USE_PLATFORM_ISR
 #define OAL_ISR_FN PSP_ISR_FN
#endif
typedef  OAL_ISR_FN ( *oal_isr_fn_t );

typedef struct
{
  uint32_t      id;
  uint32_t      pri;
  oal_isr_fn_t  fn;
} oal_isr_dsc_t;


#if OAL_USE_PLATFORM_ISR

 #define oal_isr_id_t psp_isr_id_t

 #define OAL_ISR_PRE  PSP_ISR_PRE
 #define OAL_ISR_POST PSP_ISR_POST

int psp_isr_install ( const oal_isr_dsc_t * isr_dsc, oal_isr_id_t * isr_id );
int psp_isr_enable ( oal_isr_id_t isr_id );
int psp_isr_disable ( oal_isr_id_t isr_id );
int psp_isr_delete ( oal_isr_id_t isr_id );

int psp_int_enable ( void );
int psp_int_disable ( void );

 #define oal_isr_install psp_isr_install
 #define oal_isr_enable  psp_isr_enable
 #define oal_isr_disable psp_isr_disable
 #define oal_isr_delete  psp_isr_delete

 #define oal_int_enable  psp_int_enable
 #define oal_int_disable psp_int_disable

#else /* if OAL_USE_PLATFORM_ISR */

int oal_isr_install ( const oal_isr_dsc_t * isr_dsc, oal_isr_id_t * isr_id );
int oal_isr_enable ( oal_isr_id_t isr_id );
int oal_isr_disable ( oal_isr_id_t isr_id );
int oal_isr_delete ( oal_isr_id_t isr_id );

int oal_int_enable ( void );
int oal_int_disable ( void );

#endif /* if OAL_USE_PLATFORM_ISR */

#ifdef __cplusplus
}
#endif

#endif /* ifndef _OAL_ISR_H */

