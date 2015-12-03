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

#ifndef _FSF_H_
#define _FSF_H_


#include "../../api/api_fs_err.h"   /* we use common error codes in FAT, SAFE and CAPI */

#include "fs/config/config_safe.h"

#if FS_CAPI_USED
 #include "../../config/config_capi.h"
#endif

#include "fs/api/api_safe.h"
#include "fs/safe-flash/common/port_s.h"
#include "fs/safe-flash/common/fsm.h"

#include "fs/version/ver_safe.h"
#if VER_SAFE_MAJOR != 4
 #error "VER_SAFE_MAJOR invalid"
#endif
#if VER_SAFE_MINOR != 2
 #error "VER_SAFE_MINOR invalid"
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _RPST_
#define _RPST_
#endif

/****************************************************************************
 *
 *  Init Functions
 *
 ***************************************************************************/

extern int fg_init ( void );
extern int fg_mountdrive ( FS_MULTI * fm, int drivenum, void * buffer, long buffsize, FS_DRVMOUNT mountfunc, FS_PHYGETID phyfunc );
extern int fg_unmountdrive ( FS_MULTI * fm, int drvnum );
extern int fg_format ( FS_MULTI * fm, int drivenum );
extern int fg_getfreespace ( FS_MULTI * fm, int drivenum, FS_SPACE * space );
extern int fg_get_drive_list ( int * buf );
extern int fg_get_drive_count ( void );


/****************************************************************************
 *
 *  Directory handler functions
 *
 ***************************************************************************/

extern int fg_getdrive ( const FS_MULTI * fm );
extern int fg_chdrive ( FS_MULTI * fm, int drivenum );

extern int fg_getcwd ( FS_MULTI * fm, char * buffer, int maxlen );
extern int fg_getdcwd ( FS_MULTI * fm, int drivenum, char * buffer, int maxlen );

extern int fg_mkdir ( FS_MULTI * fm, const char * dirname );
extern int fg_chdir ( FS_MULTI * fm, const char * dirname );
extern int fg_rmdir ( FS_MULTI * fm, const char * dirname );

extern int fg_setlabel ( FS_MULTI * fm, int drivenum, const char * label );
extern int fg_getlabel ( FS_MULTI * fm, int drivenum, char * label, long len );


/****************************************************************************
 *
 *  files functions
 *
 ***************************************************************************/

extern int fg_rename ( FS_MULTI * fm, const char * filename, const char * newname );
extern int fg_move ( FS_MULTI * fm, const char * filename, const char * newname );
extern int fg_delete ( FS_MULTI * fm, const char * filename );

extern long fg_filelength ( FS_MULTI * fm, const char * filename );

extern int fg_findfirst ( FS_MULTI * fm, const char * filename, FS_FIND * find );
extern int fg_findnext ( FS_MULTI * fm, FS_FIND * find );


/****************************************************************************
 *
 *  file read/write functions
 *
 ***************************************************************************/

extern FS_FILE * fg_open ( FS_MULTI * fm, const char * filename, const char * mode );
extern int fg_close ( FS_MULTI * fm, FS_FILE * filehandle );
extern int fg_abortclose ( FS_MULTI * fm, FS_FILE * file );
extern long fg_write ( FS_MULTI * fm, const void * buf, long size, long size_st, FS_FILE * filehandle );
extern long fg_read ( FS_MULTI * fm, void * buf, long size, long size_st, FS_FILE * filehandle );
extern int fg_seek ( FS_MULTI * fm, FS_FILE * filehandle, long offset, long whence );
extern long fg_tell ( FS_MULTI * fm, FS_FILE * filehandle );
extern int fg_eof ( FS_MULTI * fm, FS_FILE * filehandle );
extern int fg_rewind ( FS_MULTI * fm, FS_FILE * filehandle );
extern int fg_putc ( FS_MULTI * fm, int ch, FS_FILE * filehandle );
extern int fg_getc ( FS_MULTI * fm, FS_FILE * filehandle );
extern int fg_flush ( FS_MULTI * fm, FS_FILE * filehandle );
extern int fg_seteof ( FS_MULTI * fm, FS_FILE * filehandle );

extern int fg_settimedate ( FS_MULTI * fm, const char * filename, unsigned short ctime, unsigned short cdate );
extern int fg_gettimedate ( FS_MULTI * fm, const char * filename, unsigned short * ctime, unsigned short * cdate );
extern int fg_getpermission ( FS_MULTI * fm, const char * filename, unsigned long * psecure );
extern int fg_setpermission ( FS_MULTI * fm, const char * filename, unsigned long secure );

extern FS_FILE * fg_truncate ( FS_MULTI * fm, const char * filename, unsigned long length );
extern int fg_stat ( FS_MULTI * fm, const char * filename, FS_STAT * stat );
extern int fg_ftruncate ( FS_MULTI * fm, FS_FILE * filehandle, unsigned long length );
extern int fg_checkvolume ( FS_MULTI * fm, int drvnumber );
extern int fg_get_oem ( FS_MULTI * fm, int drivenum, char * str, long maxlen );

#ifdef HCC_UNICODE
extern int fg_wgetcwd ( FS_MULTI * fm, W_CHAR * buffer, int maxlen );
extern int fg_wgetdcwd ( FS_MULTI * fm, int drivenum, W_CHAR * buffer, int maxlen );
extern int fg_wmkdir ( FS_MULTI * fm, const W_CHAR * dirname );
extern int fg_wchdir ( FS_MULTI * fm, const W_CHAR * dirname );
extern int fg_wrmdir ( FS_MULTI * fm, const W_CHAR * dirname );
extern int fg_wrename ( FS_MULTI * fm, const W_CHAR * filename, const W_CHAR * newname );
extern int fg_wmove ( FS_MULTI * fm, const W_CHAR * filename, const W_CHAR * newname );
extern int fg_wdelete ( FS_MULTI * fm, const W_CHAR * filename );
extern long fg_wfilelength ( FS_MULTI * fm, const W_CHAR * filename );
extern int fg_wfindfirst ( FS_MULTI * fm, const W_CHAR * filename, FS_WFIND * find );
extern int fg_wfindnext ( FS_MULTI * fm, FS_WFIND * find );
extern FS_FILE * fg_wopen ( FS_MULTI * fm, const W_CHAR * filename, const W_CHAR * mode );
extern int fg_wsettimedate ( FS_MULTI * fm, const W_CHAR * filename, unsigned short ctime, unsigned short cdate );
extern int fg_wgettimedate ( FS_MULTI * fm, const W_CHAR * filename, unsigned short * ctime, unsigned short * cdate );
extern int fg_wgetpermission ( FS_MULTI * fm, const W_CHAR * filename, unsigned long * psecure );
extern int fg_wsetpermission ( FS_MULTI * fm, const W_CHAR * filename, unsigned long secure );
extern FS_FILE * fg_wtruncate ( FS_MULTI * fm, const W_CHAR * filename, unsigned long length );
extern int fg_wstat ( FS_MULTI * fm, const W_CHAR * filename, FS_STAT * stat );
#endif /* ifdef HCC_UNICODE */


/****************************************************************************
 *
 *  internal common functions for secure parts
 *
 ***************************************************************************/

extern int _fg_flush ( FS_VOLUMEINFO * vi );
extern int _fg_getvolumeinfo ( FS_MULTI * fm, int drivenum, FS_VOLUMEINFO * * pvi );
extern int _fg_findpath ( const FS_VOLUMEINFO * vi, FS_NAME * fsname );
extern int _fg_findfile ( const FS_VOLUMEINFO * vi, const W_CHAR * name, unsigned short dirnum, unsigned short * pdirnum );
extern int _fg_addentry ( FS_VOLUMEINFO * vi, const FS_NAME * fsname, FS_DIRENTRY * * pde );
extern int _fg_find ( const FS_VOLUMEINFO * vi, FS_NAME * fsname, FS_DIRENTRY * * pde, unsigned short * pdirnum );
extern int _fg_findfilewc ( const FS_VOLUMEINFO * vi, const W_CHAR * name, unsigned short dirnum, unsigned short * pdirnum, unsigned short startpos );
extern void _fg_setdiscsectors ( FS_VOLUMEINFO * vi, unsigned short sector );
extern int _fg_getsector ( const FS_VOLUMEINFO * vi, long secnum, void * data, long offset, long datalen );
extern void _fg_removedename ( FS_VOLUMEINFO * vi, FS_DIRENTRY * de );
extern int _fg_setdename ( const W_CHAR * s, FS_VOLUMEINFO * vi, FS_DIRENTRY * de );
extern void _fg_getdename ( W_CHAR * s, const FS_VOLUMEINFO * vi, const FS_DIRENTRY * de );
extern int _fg_namecheckwc ( const W_CHAR * name, const W_CHAR * s );
extern int _fg_copychainintomirror ( const FS_VOLUMEINFO * vi, FS_FILEINT * f, FS_DIRENTRY * de );
extern void _fg_cleanupfile ( const FS_VOLUMEINFO * vi, FS_FILEINT * f );
extern int _fg_fseek ( FS_VOLUMEINFO * vi, FS_MULTI * fm, FS_FILEINT * f, long offset );
extern int _fg_checkfilelock ( const FS_VOLUMEINFO * vi, const FS_DIRENTRY * de, long m_mode );
extern int _fg_checksyncpos ( const FS_VOLUMEINFO * vi, FS_FILEINT * f, int remove );
extern int _fg_storesector ( FS_VOLUMEINFO * vi, FS_FILEINT * file, void * data, long len );
extern FS_FILEINT * _fg_check_handle ( FS_MULTI * fm, FS_FILE * filehandle );
extern int _fg_storefilebuffer ( FS_VOLUMEINFO * vi, FS_FILEINT * f );
extern int _fg_setfsname ( FS_MULTI * fm, const W_CHAR * name, FS_NAME * fsname );
extern FS_FILEINT * _fg_checkappend ( const FS_VOLUMEINFO * vi, const FS_DIRENTRY * de, long m_mode );
extern int _fg_checkapwithr ( const FS_VOLUMEINFO * vi, FS_FILEINT * f );

extern char           truncate_tmp[ 512 ];
extern FS_FILESYSTEM  fg_filesystem;
extern FS_MUTEX_TYPE  effs_gmutex;

#ifdef __cplusplus
}
#endif

#include "fs/safe-flash/common/fsmf.h"

#if !FS_CAPI_USED
#include "fs/api/api_safe.h"
#endif


/****************************************************************************
 *
 * End of fsf.h
 *
 ***************************************************************************/

#endif /* _FSF_H_ */

