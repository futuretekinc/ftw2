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
#ifndef _CONFIG_SAFE_H_
#define _CONFIG_SAFE_H_

#include "fs/version/ver_safe.h"
#if VER_SAFE_MAJOR != 4
 #error "VER_SAFE_MAJOR invalid"
#endif
#if VER_SAFE_MINOR != 2
 #error "VER_SAFE_MINOR invalid"
#endif


/****************************************************************************
 *
 * Open bracket for C++ Compatibility
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#define FS_MAXDENAME 13     /* maximum direntry name */


/****************************************************************************
 *
 * if Common Interface is used then set CAPI_USED to 1
 *
 ***************************************************************************/

#define FS_CAPI_USED 0


/****************************************************************************
 *
 * Open bracket for CAPI
 *
 ***************************************************************************/

#if FS_CAPI_USED

 #ifdef __cplusplus
}
 #endif


/****************************************************************************
 *
 * Set FS_CASE_SENSITIVE to 1 if you want a case sensitive file system
 *
 ***************************************************************************/

 #define FS_SAFE_CASE_SENSITIVE 1


/****************************************************************************
 *
 * Open bracket for non CAPI
 *
 ***************************************************************************/

#else


/****************************************************************************
 *
 * volumes definitions
 *
 ***************************************************************************/

 #define FS_MAXVOLUME   4   /* maximum number of volumes */
 #define FS_MAXTASK     4   /* maximum number of task */

 #define FS_MAXPATHNAME 128 /* maximum lenght for path */
 #define FS_CURRDRIVE   0   /* setting the current drive at startup (-1 means no default current drive)*/


/****************************************************************************
 *
 * Set FS_CASE_SENSITIVE to 1 if you want a case sensitive file system
 *
 ***************************************************************************/

 #define FS_SAFE_CASE_SENSITIVE 1


/****************************************************************************
 *
 * Set HCC_16BIT_CHAR to 1 if a char is 16bit length (e.g. on DSPs)
 *
 ***************************************************************************/

 #define HCC_16BIT_CHAR 0


/****************************************************************************
 *
 * Set TI_COMPRESS to 1 if a char is 16bit length (e.g. on DSPs)
 * and character compression (2 times 8 bit byte into one 16 bit byte)
 * is selected
 *
 ***************************************************************************/

 #define TI_COMPRESS 0


/****************************************************************************
 *
 * Set CRCONFILES to 1 if files need crc protection at open and calculation
 * at close. Default state is 0.
 *
 ***************************************************************************/

 #define CRCONFILES 0


/****************************************************************************
 *
 * Set F_FILE_CHANGED_EVENT to 1 if want event about file state changed
 *
 ***************************************************************************/

 #define F_FILE_CHANGED_EVENT 0


/****************************************************************************
 *
 * set USE_TASK_SEPARATED_CWD to 1 (default) if every task need separated
 * current working folder.
 *
 ***************************************************************************/

 #define USE_TASK_SEPARATED_CWD 1


/****************************************************************************
 *
 *  if Unicode is used then comment in HCC_UNICODE define
 *
 ***************************************************************************/

/* #define HCC_UNICODE */ /* enable this line for unicode compatibility */

typedef unsigned short  wchar; /* typedef for wide char */

/* define W_CHAR type according to HCC_UNICODE */

 #ifdef HCC_UNICODE
  #define W_CHAR wchar
 #else
  #define W_CHAR char
 #endif

/* select system directory separator char */
/* the system will use it as default, but */
/* it also recognizes both incoming parameter */

 #if 0
  #define FS_SEPARATORCHAR '/'
 #else
  #define FS_SEPARATORCHAR '\\'
 #endif

/* this define is needed for compatibility of CAPI */

 #define F_SEPARATOR FS_SEPARATORCHAR


/****************************************************************************
 *
 * Last error usage
 *
 ***************************************************************************/

 #if 1

/* simple asignment */
  #define F_SETLASTERROR( ec )       ( fm->lasterror = ( ec ) )
  #define F_SETLASTERROR_NORET( ec ) ( fm->lasterror = ( ec ) )
 #elif 0

/* function calls used for it */
  #define F_SETLASTERROR( ec )       fg_setlasterror( fm, ec )
  #define F_SETLASTERROR_NORET( ec ) fg_setlasterror_noret( fm, ec )
 #elif 0

/* no last error is used (save code space) */
  #define F_SETLASTERROR( ec )       ( ec )
  #define F_SETLASTERROR_NORET( ec )
 #endif


/****************************************************************************
 *
 * Close bracket for non CAPI
 *
 ***************************************************************************/

#endif /* FS_CAPI_USED */


/****************************************************************************
 *
 * Set FSF_MOST_FREE_ALLOC to 1 if most free block allocation is used <default>
 * in flash drivers for allocating a new sector.
 *
 ***************************************************************************/

#define FSF_MOST_FREE_ALLOC 1

#if FS_CAPI_USED

 #ifdef __cplusplus
extern "C" {
 #endif

#endif /* FS_CAPI_USED */


/****************************************************************************
 *
 * typedef for 32 bit long variable type, this is for processors
 * where 'long' type is longer than 32 bit (e.g. 40bit) but 'int' is 32.
 * Then this typedef can be set to 'int'.
 *
 ***************************************************************************/

typedef long           hcc_32;
#ifndef _HCC_TYPES_H_
typedef unsigned long  hcc_u32;
#endif


/****************************************************************************
 *
 * Close bracket for C++
 *
 ***************************************************************************/

#ifdef __cplusplus
}
#endif


/****************************************************************************
 *
 * end of config_safe.h
 *
 ***************************************************************************/

#endif /* _CONFIG_SAFE_H_ */

