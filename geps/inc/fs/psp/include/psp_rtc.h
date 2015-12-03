/****************************************************************************
 *
 *            Copyright (c) 2011 by HCC Embedded
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
#ifndef _PSP_RTC_H
#define _PSP_RTC_H

#include <stdint.h>

#include "fs/version/ver_psp_rtc.h"
#if VER_PSP_RTC_MAJOR != 1
 #error "VER_PSP_RTC_MAJOR invalid"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  uint8_t   sec;
  uint8_t   min;
  uint8_t   hour;
  uint8_t   day;
  uint8_t   month;
  uint16_t  year;
} t_psp_timedate;

void psp_getcurrenttimedate ( t_psp_timedate * p_timedate );

#ifdef __cplusplus
}
#endif


#endif /* _PSP_RTC_H */

