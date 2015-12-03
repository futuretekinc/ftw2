#ifndef _FSF_FPT_H_

#define _FSF_FPT_H_

#include "fs/safe-flash/common/fsf.h"

typedef int (* fg_init_FP_T) ( void );
typedef void (* _fg_setdiscsectors_FP_T) ( FS_VOLUMEINFO * vi, unsigned short sector );
typedef int (* _fg_copychainintomirror_FP_T) ( const FS_VOLUMEINFO * vi, FS_FILEINT * f, FS_DIRENTRY * de );
typedef void (* _fg_copymirrorchainnoremove_FP_T) ( FS_VOLUMEINFO * vi, unsigned short sector );
typedef void (* _fg_copymirrorchain_FP_T) ( FS_VOLUMEINFO * vi, unsigned short sector, int noremove );
typedef void (* _fg_copydiscmirrorchain_FP_T) ( FS_VOLUMEINFO * vi, unsigned short sector );
typedef void (* _fg_removemirrorchain_FP_T) ( const FS_VOLUMEINFO * vi, unsigned short sector );
typedef void (* _fg_cleanupfile_FP_T) ( const FS_VOLUMEINFO * vi, FS_FILEINT * f );
#if F_FILE_CHANGED_EVENT
typedef unsigned char (* _fg_getcompatibleattr_FP_T) ( FS_DIRENTRY * de );
#endif /* if F_FILE_CHANGED_EVENT */
typedef void (* _fg_removediscsectors_FP_T) ( const FS_VOLUMEINFO * vi );
typedef void (* _fg_getdename_FP_T) ( W_CHAR * s, const FS_VOLUMEINFO * vi, const FS_DIRENTRY * de );
typedef void (* _fg_removedename_FP_T) ( FS_VOLUMEINFO * vi, FS_DIRENTRY * de );
typedef int (* _fg_setdename_FP_T) ( const W_CHAR * s, FS_VOLUMEINFO * vi, FS_DIRENTRY * de );
typedef int (* _fg_flush_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* fg_mountdrive_FP_T) ( FS_MULTI * fm, int drivenum, void * buffer, long buffsize, FS_DRVMOUNT mountfunc, FS_PHYGETID phyfunc );
typedef int (* fg_unmountdrive_FP_T) ( FS_MULTI * fm, int drivenum );
typedef int (* fg_get_drive_count_FP_T) ();
typedef int (* fg_get_drive_list_FP_T) ( int * buf );
typedef int (* _fg_getvolumeinfo_FP_T) ( FS_MULTI * fm, int drivenum, FS_VOLUMEINFO * * pvi );
typedef int (* _fg_setfsname_FP_T) ( FS_MULTI * fm, const W_CHAR * name, FS_NAME * fsname );
typedef int (* _fg_findfile_FP_T) ( const FS_VOLUMEINFO * vi, const W_CHAR * name, unsigned short dirnum, unsigned short * pdirnum );
typedef int (* _fg_namecheckwc_FP_T) ( const W_CHAR * wname, const W_CHAR * name );
typedef int (* _fg_findfilewc_FP_T) ( const FS_VOLUMEINFO * vi, const W_CHAR * name, unsigned short dirnum, unsigned short * pdirnum, unsigned short startpos );
typedef int (* _fg_findpath_FP_T) ( const FS_VOLUMEINFO * vi, FS_NAME * fsname );
typedef int (* _fg_find_FP_T) ( const FS_VOLUMEINFO * vi, FS_NAME * fsname, FS_DIRENTRY * * pde, unsigned short * pdirnum );
typedef int (* _fg_isnamedots_FP_T) ( const W_CHAR * name );
typedef void (* get_currenttimedate_FP_T) ( uint16_t * pi_time, uint16_t * pi_date );
typedef int (* _fg_addentry_FP_T) ( FS_VOLUMEINFO * vi, const FS_NAME * fsname, FS_DIRENTRY * * pde );
typedef int (* _fg_storesector_FP_T) ( FS_VOLUMEINFO * vi, FS_FILEINT * file, void * data, long len );
typedef int (* _fg_getsector_FP_T) ( const FS_VOLUMEINFO * vi, long secnum, void * data, long offset, long datalen );
typedef int (* fg_getdrive_FP_T) ( const FS_MULTI * fm );
typedef int (* fg_chdrive_FP_T) ( FS_MULTI * fm, int drivenum );
typedef int (* fg_getdcwd_FP_T) ( FS_MULTI * fm, int drivenum, char * buffer, int maxlen );
#ifdef HCC_UNICODE
typedef int (* fg_wgetdcwd_FP_T) ( FS_MULTI * fm, int drivenum, W_CHAR * buffer, int maxlen );
#endif /* ifdef HCC_UNICODE */
typedef int (* fg_getcwd_FP_T) ( FS_MULTI * fm, char * buffer, int maxlen );
#ifdef HCC_UNICODE
typedef int (* fg_wgetcwd_FP_T) ( FS_MULTI * fm, W_CHAR * buffer, int maxlen );
#endif
typedef int (* fg_mkdir_FP_T) ( FS_MULTI * fm, const char * dirname );
typedef int (* fg_wmkdir_FP_T) ( FS_MULTI * fm, const W_CHAR * dirname );
typedef int (* fg_rmdir_FP_T) ( FS_MULTI * fm, const char * dirname );
#ifdef HCC_UNICODE
typedef int (* fg_wrmdir_FP_T) ( FS_MULTI * fm, const W_CHAR * dirname );
#endif
typedef int (* fg_chdir_FP_T) ( FS_MULTI * fm, const char * dirname );
#ifdef HCC_UNICODE
typedef int (* fg_wchdir_FP_T) ( FS_MULTI * fm, const W_CHAR * dirname );
#endif
typedef int (* fg_rename_FP_T) ( FS_MULTI * fm, const char * filename, const char * newname );
#ifdef HCC_UNICODE
typedef int (* fg_wrename_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, const W_CHAR * newname );
#endif
typedef int (* fg_move_FP_T) ( FS_MULTI * fm, const char * filename, const char * newname );
#ifdef HCC_UNICODE
typedef int (* fg_wmove_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, const W_CHAR * newname );
#endif
typedef long (* fg_filelength_FP_T) ( FS_MULTI * fm, const char * filename );
#ifdef HCC_UNICODE
typedef long (* fg_wfilelength_FP_T) ( FS_MULTI * fm, const W_CHAR * filename );
#endif
typedef int (* fg_delete_FP_T) ( FS_MULTI * fm, const char * filename );
#ifdef HCC_UNICODE
typedef int (* fg_wdelete_FP_T) ( FS_MULTI * fm, const W_CHAR * filename );
#endif
typedef int (* _fg_storefilebuffer_FP_T) ( FS_VOLUMEINFO * vi, FS_FILEINT * f );
#if ( !TI_COMPRESS )
typedef int (* _fg_fseek_FP_T) ( FS_VOLUMEINFO * vi, FS_MULTI * fm, FS_FILEINT * f, long offset );
#endif
typedef FS_FILEINT * (* _fg_check_handle_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_seek_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle, long offset, long whence );
typedef long (* fg_tell_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_eof_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_rewind_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_putc_FP_T) ( FS_MULTI * fm, int ch, FS_FILE * filehandle );
typedef int (* fg_getc_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* _fg_checkfilelock_FP_T) ( const FS_VOLUMEINFO * vi, const FS_DIRENTRY * de, long m_mode );
typedef FS_FILEINT * (* _fg_checkappend_FP_T) ( const FS_VOLUMEINFO * vi, const FS_DIRENTRY * de, long m_mode );
typedef int (* _fg_checksyncpos_FP_T) ( const FS_VOLUMEINFO * vi, FS_FILEINT * f, int remove );
typedef int (* _fg_checkapwithr_FP_T) ( const FS_VOLUMEINFO * vi, FS_FILEINT * f );
#if ( CRCONFILES )
typedef unsigned (* f_calcfilecrc_FP_T) ( FS_VOLUMEINFO * vi, FS_FILEINT * f, unsigned long * pcrc32 );
#endif
#if ( !TI_COMPRESS )
typedef FS_FILE * (* fg_open_FP_T) ( FS_MULTI * fm, const char * filename, const char * mode );
#ifdef HCC_UNICODE
typedef FS_FILE * (* fg_wopen_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, const W_CHAR * mode );
#endif
#endif
typedef int (* fg_abortclose_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_close_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_flush_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_settimedate_FP_T) ( FS_MULTI * fm, const char * filename, unsigned short ctime, unsigned short cdate );
#ifdef HCC_UNICODE
typedef int (* fg_wsettimedate_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, unsigned short ctime, unsigned short cdate );
#endif
typedef int (* fg_gettimedate_FP_T) ( FS_MULTI * fm, const char * filename, unsigned short * pctime, unsigned short * pcdate );
#ifdef HCC_UNICODE
typedef int (* fg_wgettimedate_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, unsigned short * pctime, unsigned short * pcdate );
#endif
#if ( !TI_COMPRESS )
typedef long (* fg_write_FP_T) ( FS_MULTI * fm, const void * buf, long size, long size_st, FS_FILE * filehandle );
typedef long (* fg_read_FP_T) ( FS_MULTI * fm, void * buf, long size, long size_st, FS_FILE * filehandle );
#endif
typedef int (* fg_getfreespace_FP_T) ( FS_MULTI * fm, int drivenum, FS_SPACE * space );
typedef int (* fg_format_FP_T) ( FS_MULTI * fm, int drivenum );
typedef int (* fg_findfirst_FP_T) ( FS_MULTI * fm, const char * filename, FS_FIND * find );
#ifdef HCC_UNICODE
typedef int (* fg_wfindfirst_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, FS_WFIND * find );
#endif /* ifdef HCC_UNICODE */
typedef int (* fg_findnext_FP_T) ( FS_MULTI * fm, FS_FIND * find );
#ifdef HCC_UNICODE
typedef int (* fg_wfindnext_FP_T) ( FS_MULTI * fm, FS_WFIND * find );
#endif /* ifdef HCC_UNICODE */
typedef int (* fg_getpermission_FP_T) ( FS_MULTI * fm, const char * filename, unsigned long * psecure );
#ifdef HCC_UNICODE
typedef int (* fg_wgetpermission_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, unsigned long * psecure );
#endif /* ifdef HCC_UNICODE */
typedef int (* fg_setpermission_FP_T) ( FS_MULTI * fm, const char * filename, unsigned long secure );
#ifdef HCC_UNICODE
typedef int (* fg_wsetpermission_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, unsigned long secure );
#endif /* ifdef HCC_UNICODE */
typedef int (* fg_getlabel_FP_T) ( FS_MULTI * fm, int drivenum, char * label, long len );
typedef int (* fg_setlabel_FP_T) ( FS_MULTI * fm, int drivenum, const char * label );
typedef FS_FILE * (* fg_truncate_FP_T) ( FS_MULTI * fm, const char * filename, unsigned long length );
#ifdef HCC_UNICODE
typedef FS_FILE * (* fg_wtruncate_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, unsigned long length );
#endif
typedef int (* fg_seteof_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle );
typedef int (* fg_stat_FP_T) ( FS_MULTI * fm, const char * filename, FS_STAT * stat );
#ifdef HCC_UNICODE
typedef int (* fg_wstat_FP_T) ( FS_MULTI * fm, const W_CHAR * filename, FS_STAT * stat );
#endif
typedef int (* fg_ftruncate_FP_T) ( FS_MULTI * fm, FS_FILE * filehandle, unsigned long length );
typedef int (* fg_checkvolume_FP_T) ( FS_MULTI * fm, int drvnumber );
typedef int (* fg_get_oem_FP_T) ( FS_MULTI * fm, int drivenum, char * str, long maxlen ); 

extern _RPST_ fg_init_FP_T fg_init_FP;
extern _RPST_ _fg_setdiscsectors_FP_T _fg_setdiscsectors_FP;
extern _RPST_ _fg_copychainintomirror_FP_T _fg_copychainintomirror_FP;
extern _RPST_ _fg_copymirrorchain_FP_T _fg_copymirrorchain_FP;
extern _RPST_ _fg_copymirrorchainnoremove_FP_T _fg_copymirrorchainnoremove_FP;
extern _RPST_ _fg_copydiscmirrorchain_FP_T _fg_copydiscmirrorchain_FP;
extern _RPST_ _fg_removemirrorchain_FP_T _fg_removemirrorchain_FP;
extern _RPST_ _fg_cleanupfile_FP_T _fg_cleanupfile_FP;
#if F_FILE_CHANGED_EVENT
extern _RPST_ _fg_getcompatibleattr_FP_T _fg_getcompatibleattr_FP;
#endif /* if F_FILE_CHANGED_EVENT */
extern _RPST_ _fg_removediscsectors_FP_T _fg_removediscsectors_FP;
extern _RPST_ _fg_getdename_FP_T _fg_getdename_FP;
extern _RPST_ _fg_removedename_FP_T _fg_removedename_FP;
extern _RPST_ _fg_setdename_FP_T _fg_setdename_FP;
extern _RPST_ _fg_flush_FP_T _fg_flush_FP;
extern _RPST_ fg_mountdrive_FP_T fg_mountdrive_FP;
extern _RPST_ fg_unmountdrive_FP_T fg_unmountdrive_FP;
extern _RPST_ fg_get_drive_count_FP_T fg_get_drive_count_FP;
extern _RPST_ fg_get_drive_list_FP_T fg_get_drive_list_FP;
extern _RPST_ _fg_getvolumeinfo_FP_T _fg_getvolumeinfo_FP;
extern _RPST_ _fg_setfsname_FP_T _fg_setfsname_FP;
extern _RPST_ _fg_findfile_FP_T _fg_findfile_FP;
extern _RPST_ _fg_namecheckwc_FP_T _fg_namecheckwc_FP;
extern _RPST_ _fg_findfilewc_FP_T _fg_findfilewc_FP;
extern _RPST_ _fg_findpath_FP_T _fg_findpath_FP; 
extern _RPST_ _fg_find_FP_T _fg_find_FP; 
extern _RPST_ _fg_isnamedots_FP_T _fg_isnamedots_FP;
extern _RPST_ get_currenttimedate_FP_T get_currenttimedate_FP;
extern _RPST_ _fg_addentry_FP_T _fg_addentry_FP;
extern _RPST_ _fg_storesector_FP_T _fg_storesector_FP;
extern _RPST_ _fg_getsector_FP_T _fg_getsector_FP;
extern _RPST_ fg_getdrive_FP_T fg_getdrive_FP;
extern _RPST_ fg_chdrive_FP_T fg_chdrive_FP;
extern _RPST_ fg_getdcwd_FP_T fg_getdcwd_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wgetdcwd_FP_T fg_wgetdcwd_FP;
#endif /* ifdef HCC_UNICODE */
extern _RPST_ fg_getcwd_FP_T fg_getcwd_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wgetcwd_FP_T fg_wgetcwd_FP;
#endif
extern _RPST_ fg_mkdir_FP_T fg_mkdir_FP;
extern _RPST_ fg_wmkdir_FP_T fg_wmkdir_FP;
extern _RPST_ fg_rmdir_FP_T fg_rmdir_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wrmdir_FP_T fg_wrmdir_FP;
#endif
extern _RPST_ fg_chdir_FP_T fg_chdir_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wchdir_FP_T fg_wchdir_FP;
#endif
extern _RPST_ fg_rename_FP_T fg_rename_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wrename_FP_T fg_wrename_FP; 
#endif
extern _RPST_ fg_move_FP_T fg_move_FP; 
#ifdef HCC_UNICODE
extern _RPST_ fg_wmove_FP_T fg_wmove_FP;
#endif
extern _RPST_ fg_filelength_FP_T fg_filelength_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wfilelength_FP_T fg_wfilelength_FP;
#endif
extern _RPST_ fg_delete_FP_T fg_delete_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wdelete_FP_T fg_wdelete_FP;
#endif
extern _RPST_ _fg_storefilebuffer_FP_T _fg_storefilebuffer_FP;
#if ( !TI_COMPRESS )
extern _RPST_ _fg_fseek_FP_T _fg_fseek_FP;
#endif
extern _RPST_ _fg_check_handle_FP_T _fg_check_handle_FP;
extern _RPST_ fg_seek_FP_T fg_seek_FP;
extern _RPST_ fg_tell_FP_T fg_tell_FP;
extern _RPST_ fg_eof_FP_T fg_eof_FP;
extern _RPST_ fg_rewind_FP_T fg_rewind_FP;
extern _RPST_ fg_putc_FP_T fg_putc_FP;
extern _RPST_ fg_getc_FP_T fg_getc_FP;
extern _RPST_ _fg_checkfilelock_FP_T _fg_checkfilelock_FP;
extern _RPST_ _fg_checkappend_FP_T _fg_checkappend_FP;
extern _RPST_ _fg_checksyncpos_FP_T _fg_checksyncpos_FP;
extern _RPST_ _fg_checkapwithr_FP_T _fg_checkapwithr_FP; 
#if ( CRCONFILES )
extern _RPST_ f_calcfilecrc_FP_T f_calcfilecrc_FP; 
#endif
#if ( !TI_COMPRESS )
extern _RPST_ fg_open_FP_T fg_open_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wopen_FP_T fg_wopen_FP;
#endif
#endif
extern 	_RPST_ fg_abortclose_FP_T fg_abortclose_FP;
extern _RPST_ fg_close_FP_T fg_close_FP;
extern _RPST_ fg_flush_FP_T fg_flush_FP;
extern _RPST_ fg_settimedate_FP_T fg_settimedate_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wsettimedate_FP_T fg_wsettimedate_FP;
#endif
extern _RPST_ fg_gettimedate_FP_T fg_gettimedate_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wgettimedate_FP_T fg_wgettimedate_FP;
#endif
#if ( !TI_COMPRESS )
extern _RPST_ fg_write_FP_T fg_write_FP;
extern _RPST_ fg_read_FP_T fg_read_FP;
#endif
extern _RPST_ fg_getfreespace_FP_T fg_getfreespace_FP;
extern _RPST_ fg_format_FP_T fg_format_FP;
extern _RPST_ fg_findfirst_FP_T fg_findfirst_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wfindfirst_FP_T fg_wfindfirst_FP;
#endif /* ifdef HCC_UNICODE */
extern _RPST_ fg_findnext_FP_T fg_findnext_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wfindnext_FP_T fg_wfindnext_FP;
#endif /* ifdef HCC_UNICODE */
extern _RPST_ fg_getpermission_FP_T fg_getpermission_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wgetpermission_FP_T fg_wgetpermission_FP; 
#endif /* ifdef HCC_UNICODE */
extern _RPST_ fg_setpermission_FP_T fg_setpermission_FP; 
#ifdef HCC_UNICODE
extern _RPST_ fg_wsetpermission_FP_T fg_wsetpermission_FP;
#endif /* ifdef HCC_UNICODE */
extern _RPST_ fg_getlabel_FP_T fg_getlabel_FP;
extern _RPST_ fg_setlabel_FP_T fg_setlabel_FP;
extern _RPST_ fg_truncate_FP_T fg_truncate_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wtruncate_FP_T fg_wtruncate_FP;
#endif
extern _RPST_ fg_seteof_FP_T fg_seteof_FP;
extern _RPST_ fg_stat_FP_T fg_stat_FP;
#ifdef HCC_UNICODE
extern _RPST_ fg_wstat_FP_T fg_wstat_FP;
#endif
extern _RPST_ fg_ftruncate_FP_T fg_ftruncate_FP;
extern _RPST_ fg_checkvolume_FP_T fg_checkvolume_FP;
extern _RPST_ fg_get_oem_FP_T fg_get_oem_FP;

#endif
