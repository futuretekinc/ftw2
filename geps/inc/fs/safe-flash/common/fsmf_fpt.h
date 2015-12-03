#ifndef _FSMF_FPT_H_

#define _FSMF_FPT_H_

typedef int (* _fsm_checksemaphore_FP_T) ( FS_MULTI * fm, FS_VOLUMEINFO * vi );
#if ( !FS_CAPI_USED )
typedef void (* _fsm_releasesemaphore_FP_T) ( FS_MULTI * fm );
typedef int (* _fsm_gettask_FP_T) ( FS_MULTI * * fm );
typedef int (* fsm_enterFS_FP_T) ();
typedef void (* fsm_releaseFS_FP_T) ();
typedef int (* fsm_format_FP_T) ( int drivenum );
typedef int (* fsm_mountdrive_FP_T) ( int drivenum, void * buffer, long buffsize, void * mountfunc, FS_PHYGETID phyfunc );
typedef int (* fsm_unmountdrive_FP_T) ( int drivenum );
typedef int (* fsm_get_drive_list_FP_T) ( int * buf );
typedef int (* fsm_get_drive_count_FP_T) ( void );
typedef int (* fsm_getfreespace_FP_T) ( int drivenum, FS_SPACE * space );
typedef int (* fsm_getdrive_FP_T)( void );
typedef int (* fsm_chdrive_FP_T) ( int drivenum );
typedef int (* fsm_getdcwd_FP_T) ( int drivenum, char * buffer, int maxlen );
typedef int (* fsm_getcwd_FP_T) ( char * buffer, int maxlen );
typedef int (* fsm_mkdir_FP_T) ( const char * dirname );

#ifdef HCC_UNICODE

typedef int (* fsm_wgetcwd_FP_T) ( W_CHAR * buffer, int maxlen );
typedef int (* fsm_wgetdcwd_FP_T) ( int drivenum, W_CHAR * buffer, int maxlen );
typedef int (* fsm_wmkdir_FP_T) ( const W_CHAR * dirname );
typedef int (* fsm_wchdir_FP_T) ( const W_CHAR * dirname );
typedef int (* fsm_wrmdir_FP_T) ( const W_CHAR * dirname );
typedef int (* fsm_wfindfirst_FP_T) ( const W_CHAR * filename, FS_WFIND * find);
typedef int (* fsm_wfindnext_FP_T) ( FS_FIND * find );
typedef int (* fsm_wrename_FP_T) ( const W_CHAR * filename, const W_CHAR * newname );
typedef int (* fsm_wmove_FP_T) ( const W_CHAR * filename, const W_CHAR * newname );
typedef int (* fsm_wdelete_FP_T) ( const W_CHAR * filename );
typedef long (* fsm_wfilelength_FP_T) ( const W_CHAR * filename );
typedef FS_FILE * (* fsm_wopen_FP_T) ( const W_CHAR * filename, const W_CHAR * mode );
typedef int (* fsm_wsettimedate_FP_T) ( const W_CHAR * filename, unsigned short ctime, unsigned short cdate );
typedef int (* fsm_wgettimedate_FP_T) ( const W_CHAR * filename, unsigned short * pctime, unsigned short * pcdate );
typedef int (* fsm_wgetpermission_FP_T) ( const W_CHAR * filename, unsigned long * psecure );
typedef int (* fsm_wsetpermission_FP_T) ( const W_CHAR * filename, unsigned long secure );
typedef FS_FILE * (* fsm_wtruncate_FP_T) ( const W_CHAR * filename, unsigned long length );
typedef int (* fsm_wstat_FP_T) ( const W_CHAR * filename, FS_STAT * stat );

#endif 

typedef int (* fsm_chdir_FP_T) ( const char * dirname );
typedef int (* fsm_rmdir_FP_T) ( const char * dirname );
typedef int (* fsm_findfirst_FP_T) ( const char * filename, FS_FIND * find );
typedef int (* fsm_findnext_FP_T) ( FS_FIND * find );
typedef int (* fsm_rename_FP_T) ( const char * filename, const char * newname );
typedef int (* fsm_move_FP_T) ( const char * filename, const char * newname );
typedef int (* fsm_delete_FP_T) ( const char * filename ) ;
typedef long (* fsm_filelength_FP_T) ( const char * filename );
typedef FS_FILE * (* fsm_open_FP_T) ( const char * filename, const char * mode );
typedef int (* fsm_seek_FP_T) ( FS_FILE * filehandle, long offset, long whence );
typedef long (* fsm_tell_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_eof_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_rewind_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_putc_FP_T) ( int ch, FS_FILE * filehandle );
typedef int (* fsm_getc_FP_T) ( FS_FILE * filehandle );
typedef long (* fsm_read_FP_T) ( void * buf, long size, long size_st, FS_FILE * filehandle );
typedef long (* fsm_write_FP_T) ( const void * buf, long size, long size_st, FS_FILE * filehandle );
typedef int (* fsm_flush_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_abortclose_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_close_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_settimedate_FP_T) ( const char * filename, unsigned short ctime, unsigned short cdate );
typedef int (* fsm_gettimedate_FP_T) ( const char * filename, unsigned short * pctime, unsigned short * pcdate );
typedef int (* fsm_getpermission_FP_T) ( const char * filename, unsigned long * psecure );
typedef int (* fsm_setpermission_FP_T) ( const char * filename, unsigned long secure );
typedef int (* fsm_getlabel_FP_T) ( int drivenum, char * label, long len );
typedef int (* fsm_setlabel_FP_T) ( int drivenum, const char * label );
typedef FS_FILE * (* fsm_truncate_FP_T) ( const char * filename, unsigned long length );
typedef int (* fsm_seteof_FP_T) ( FS_FILE * filehandle );
typedef int (* fsm_stat_FP_T) ( const char * filename, FS_STAT * stat );
typedef int (* fsm_ftruncate_FP_T) ( FS_FILE * filehandle, unsigned long length );
typedef int (* fsm_checkvolume_FP_T) ( int drvnumber );
typedef int (* fsm_get_oem_FP_T) ( int drivenum, char * str, long maxlen );
typedef int (* fsm_getlasterror_FP_T) ();

#endif /* (!FS_CAPI_USED) */

extern _RPST_ _fsm_checksemaphore_FP_T _fsm_checksemaphore_FP ;
#if ( !FS_CAPI_USED )
extern _RPST_ _fsm_releasesemaphore_FP_T _fsm_releasesemaphore_FP ;
extern _RPST_ _fsm_gettask_FP_T _fsm_gettask_FP ;
extern _RPST_ fsm_enterFS_FP_T fsm_enterFS_FP ;
extern _RPST_ fsm_releaseFS_FP_T fsm_releaseFS_FP ;
extern _RPST_ fsm_format_FP_T fsm_format_FP ;
extern _RPST_ fsm_mountdrive_FP_T fsm_mountdrive_FP ;
extern _RPST_ fsm_unmountdrive_FP_T fsm_unmountdrive_FP ;
extern _RPST_ fsm_get_drive_list_FP_T fsm_get_drive_list_FP ;
extern _RPST_ fsm_get_drive_count_FP_T fsm_get_drive_count_FP ;
extern _RPST_ fsm_getfreespace_FP_T fsm_getfreespace_FP ;
extern _RPST_ fsm_getdrive_FP_T fsm_getdrive_FP ;
extern _RPST_ fsm_chdrive_FP_T fsm_chdrive_FP ;
extern _RPST_ fsm_getdcwd_FP_T fsm_getdcwd_FP ;
extern _RPST_ fsm_getcwd_FP_T fsm_getcwd_FP ;
extern _RPST_ fsm_mkdir_FP_T fsm_mkdir_FP ;

#ifdef HCC_UNICODE

extern _RPST_ fsm_wgetcwd_FP_T fsm_wgetcwd_FP ;
extern _RPST_ fsm_wgetdcwd_FP_T fsm_wgetdcwd_FP ;
extern _RPST_ fsm_wmkdir_FP_T fsm_wmkdir_FP ;
extern _RPST_ fsm_wchdir_FP_T fsm_wchdir_FP ;
extern _RPST_ fsm_wrmdir_FP_T fsm_wrmdir_FP ;
extern _RPST_ fsm_wfindfirst_FP_T fsm_wfindfirst_FP ;
extern _RPST_ fsm_wfindnext_FP_T fsm_wfindnext_FP ;
extern _RPST_ fsm_wrename_FP_T fsm_wrename_FP ;
extern _RPST_ fsm_wmove_FP_T fsm_wmove_FP ;
extern _RPST_ fsm_wdelete_FP_T fsm_wdelete_FP ;
extern _RPST_ fsm_wfilelength_FP_T fsm_wfilelength_FP;
extern _RPST_ fsm_wopen_FP_T fsm_wopen_FP ;
extern _RPST_ fsm_wsettimedate_FP_T fsm_wsettimedate_FP ;
extern _RPST_ fsm_wgettimedate_FP_T fsm_wgettimedate_FP ;
extern _RPST_ fsm_wgetpermission_FP_T fsm_wgetpermission_FP ;
extern _RPST_ fsm_wsetpermission_FP_T fsm_wsetpermission_FP ;
extern _RPST_ fsm_wtruncate_FP_T fsm_wtruncate_FP ;
extern _RPST_ fsm_wstat_FP_T fsm_wstat_FP ;
#endif 
extern _RPST_ fsm_chdir_FP_T fsm_chdir_FP ;
extern _RPST_ fsm_rmdir_FP_T fsm_rmdir_FP ;
extern _RPST_ fsm_findfirst_FP_T fsm_findfirst_FP ;
extern _RPST_ fsm_findnext_FP_T fsm_findnext_FP ;
extern _RPST_ fsm_rename_FP_T fsm_rename_FP ;
extern _RPST_ fsm_move_FP_T fsm_move_FP ;
extern _RPST_ fsm_delete_FP_T fsm_delete_FP ;
extern _RPST_ fsm_filelength_FP_T fsm_filelength_FP ;
extern _RPST_ fsm_open_FP_T fsm_open_FP ;
extern _RPST_ fsm_seek_FP_T fsm_seek_FP ;
extern _RPST_ fsm_tell_FP_T fsm_tell_FP ;
extern _RPST_ fsm_eof_FP_T fsm_eof_FP ;
extern _RPST_ fsm_rewind_FP_T fsm_rewind_FP ;
extern _RPST_ fsm_putc_FP_T fsm_putc_FP ;
extern _RPST_ fsm_getc_FP_T fsm_getc_FP ;
extern _RPST_ fsm_read_FP_T fsm_read_FP ;
extern _RPST_ fsm_write_FP_T fsm_write_FP ;
extern _RPST_ fsm_flush_FP_T fsm_flush_FP ;
extern _RPST_ fsm_abortclose_FP_T fsm_abortclose_FP ;
extern _RPST_ fsm_close_FP_T fsm_close_FP ;
extern _RPST_ fsm_settimedate_FP_T fsm_settimedate_FP ;
extern _RPST_ fsm_gettimedate_FP_T fsm_gettimedate_FP ;
extern _RPST_ fsm_getpermission_FP_T fsm_getpermission_FP ;
extern _RPST_ fsm_setpermission_FP_T fsm_setpermission_FP ;
extern _RPST_ fsm_getlabel_FP_T fsm_getlabel_FP ;
extern _RPST_ fsm_setlabel_FP_T fsm_setlabel_FP ;
extern _RPST_ fsm_truncate_FP_T fsm_truncate_FP ;
extern _RPST_ fsm_seteof_FP_T fsm_seteof_FP ;
extern _RPST_ fsm_stat_FP_T fsm_stat_FP ;
extern _RPST_ fsm_ftruncate_FP_T fsm_ftruncate_FP ;
extern _RPST_ fsm_checkvolume_FP_T fsm_checkvolume_FP ;
extern _RPST_ fsm_get_oem_FP_T fsm_get_oem_FP ;
extern _RPST_ fsm_getlasterror_FP_T fsm_getlasterror_FP ;
#endif /* (!FS_CAPI_USED) */
#endif
