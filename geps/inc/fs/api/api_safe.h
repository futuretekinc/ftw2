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
 * Vaci ut 76
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/
#ifndef _API_SAFE_H_
#define _API_SAFE_H_


/* include configuration settings */
#include "fs/config/config_safe.h"

#include "fs/version/ver_safe.h"
#if VER_SAFE_MAJOR != 4
 #error "VER_SAFE_MAJOR invalid"
#endif
#if VER_SAFE_MINOR != 2
 #error "VER_SAFE_MINOR invalid"
#endif

#if !( FS_CAPI_USED )
#include "fs/api/api_fs_err.h"
#endif


/****************************************************************************
 *
 * open bracket for C++ compatibility
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/*  definitions for ctime  */
#define FS_CTIME_SEC_SHIFT   0
#define FS_CTIME_SEC_MASK    0x001f /* 0-30 in 2seconds */
#define FS_CTIME_MIN_SHIFT   5
#define FS_CTIME_MIN_MASK    0x07e0 /* 0-59  */
#define FS_CTIME_HOUR_SHIFT  11
#define FS_CTIME_HOUR_MASK   0xf800 /* 0-23 */

/*  definitions for cdate  */
#define FS_CDATE_DAY_SHIFT   0
#define FS_CDATE_DAY_MASK    0x001f     /* 0-31 */
#define FS_CDATE_MONTH_SHIFT 5
#define FS_CDATE_MONTH_MASK  0x01e0     /* 1-12 */
#define FS_CDATE_YEAR_SHIFT  9
#define FS_CDATE_YEAR_MASK   0xfe00     /* 0-119 (1980+value) */


/*  definitions for file/entry attribute  */
#define FS_ATTR_DE           0x01   /* entry is used for direntry */
#define FS_ATTR_DIR          0x02   /* directory */
#define FS_ATTR_LFN1         0x04   /* structure holds long file name in the 1st half */
#define FS_ATTR_LFN2         0x08   /* structure holds long file name in the 2nd half */
#define FS_ATTR_LFN1NXT      0x10   /* there is next entry of 1 on next bottom */
#define FS_ATTR_LFN1NXTTOP   0x20   /* there is next entry of 1 on next top */
#define FS_ATTR_LFN2NXT      0x40   /* there is next entry of 2 on next bottom */
#define FS_ATTR_LFN2NXTTOP   0x80   /* there is next entry of 2 on next top */

#define FSSEC_ATTR_ARC       ( 0x20UL << ( 31 - 6 ) )
#define FSSEC_ATTR_DIR       ( 0x10UL << ( 31 - 6 ) )
#define FSSEC_ATTR_VOLUME    ( 0x08UL << ( 31 - 6 ) )
#define FSSEC_ATTR_SYSTEM    ( 0x04UL << ( 31 - 6 ) )
#define FSSEC_ATTR_HIDDEN    ( 0x02UL << ( 31 - 6 ) )
#define FSSEC_ATTR_READONLY  ( 0x01UL << ( 31 - 6 ) )
#define FSSEC_ATTR_USER \
  ( 0xffffffffUL \
   ^ ( FSSEC_ATTR_ARC | FSSEC_ATTR_DIR | FSSEC_ATTR_VOLUME | FSSEC_ATTR_SYSTEM | FSSEC_ATTR_HIDDEN | FSSEC_ATTR_READONLY ) )


#if ( !FS_CAPI_USED )
 #define F_FILE        FS_FILE
 #define F_FIND        FS_FIND
 #define F_SPACE       FS_SPACE
 #define F_MAXPATHNAME FS_MAXPATHNAME
 #define F_SEEK_SET    FS_SEEK_SET
 #define F_SEEK_END    FS_SEEK_END
 #define F_SEEK_CUR    FS_SEEK_CUR
 #define F_ATTR_DIR    FS_ATTR_DIR
 #define F_STAT        FS_STAT
#endif


/*  struct for FS_NAME  */
typedef struct
{
  int             drivenum;               /*  0-A 1-B 2-C  */
  W_CHAR          path[ F_MAXPATHNAME ];  /*   /directory1/dir2/   */
  W_CHAR          lname[ F_MAXPATHNAME ]; /*  filename  */
  unsigned short  dirnum;                 /*  0xffff-root other case in subdir n  */
} FS_NAME;

/*  struct for find file  */

typedef struct
{
  char            attr;                      /* attribute of the file/entry */
  char            filename[ F_MAXPATHNAME ]; /* file name+ext */

  unsigned short  ctime;            /* creation time */
  unsigned short  cdate;            /* creation date */

  unsigned long   filesize;         /* length of file */

  unsigned long   secure;           /* secure */

  FS_NAME         findfsname;       /* find properties */
  unsigned short  findpos;          /* find position */
} FS_FIND;

#ifdef HCC_UNICODE
typedef struct
{
  char            attr;                      /* attribute of the file/entry */
  W_CHAR          filename[ F_MAXPATHNAME ]; /* file name+ext */

  unsigned short  ctime;            /* creation time */
  unsigned short  cdate;            /* creation date */

  unsigned long   filesize;         /* length of file */

  unsigned long   secure;           /* secure */

  FS_NAME         findfsname;       /* find properties */
  unsigned short  findpos;          /* find position */
} FS_WFIND;
#endif


/* definition for fs_stat*/
typedef struct
{
  unsigned long   filesize;
  unsigned short  createdate;
  unsigned short  createtime;
  unsigned long   secure;
  int             drivenum;
} FS_STAT;


/*  definitions for FS_FILE  */
typedef struct
{
  long  reference;              /* reference which fileint used */
} FS_FILE;


/*  Directory entry definition  */
typedef struct
{
  unsigned char   attr;         /* attribute of the file */

  W_CHAR          lname[ FS_MAXDENAME ]; /* file name */

  unsigned short  nlfn;         /* next lfn entry */

  unsigned short  ctime;        /* creation time */
  unsigned short  cdate;        /* creation date */

  unsigned short  sector;       /* start sector */
  unsigned short  dirnum;       /* directory relative number */

  long            len;          /* length of file */

  unsigned long   secure;       /* security code */
#if ( CRCONFILES )
  hcc_u32         crc32;        /* crc32 for file protection */
#endif
} FS_DIRENTRY;


/*  definitions for FS_FILE internally used  */
typedef struct FS_FILEINT  FS_FILEINT;

typedef struct FS_FILEINT
{
  FS_FILE          file;
  FS_DIRENTRY    * direntry;        /* link to directory list */
  long             pos;             /* current position for read, file size for write */
  long             relpos;          /*  relative position in a sector  */
  int              mode;            /* mode to open 0-close, 1-read, 2-write/append */
  int              drivenum;        /* drive number */
  char           * buffer;          /* rd/write buffer */

  unsigned short * sector;          /*  this points where to write/read next sector info  */
  unsigned short * discard;         /*  this points where to write/read last discard sector is  */
  unsigned short   sectorstart;     /* after file is closed this has to be copied into direntry */
  unsigned short   discardstart;    /* after file is closed this has to be set as discardable */

  long             len;             /* file size, this is copied after fs_close */
  int              state;           /* file status  */
  int              modified;        /* if write buffer is modified */
  FS_FILEINT     * appsync;         /* for append sync */

#if F_FILE_CHANGED_EVENT
  char  filename[ F_MAXPATHNAME ];
#endif
} _FS_FILEINT;


/*  definitions for fat descriptor  */
typedef struct
{
  hcc_u32  crc32;           /* crc of this structure */
  hcc_u32  reference;       /* reference counter */
  long     nextdesc;        /* which desc needs to be written */
  hcc_u32  dircrc32;        /* directory crc32 */
  /*  FAT + Direntries + Block index is allocated here, the extra's size is flash->descsize  */
} FS_FATDESC;


#define FS_MAXCACHEDE 32    /* max cacheable de */

typedef struct
{
  hcc_u32 * desc;               /* NOR+NAND */
  hcc_u32 * sptr;               /* start ptr of current changes */
  hcc_u32 * ptr;                /* current position */
  hcc_u32   status;             /* status of cache */

  hcc_u32   reference;          /* reference counter NAND+NOR */
  hcc_32    free;               /* free space in cache NAND+NOR */
  hcc_32    size;               /* size of cache NAND+NOR */

  int       maxde;                /* number of de entry in des */
  void    * des[ FS_MAXCACHEDE ]; /* de entries here */

  long      currdescnum;        /* current descriptor block for NOR */
} FS_WRCACHE;


typedef struct FS_FLASH  FS_FLASH;



/*  definitions for FLASH physical functions   */

typedef int  ( *FS_PHYREAD )( void * data, long block, long blockrel, long datalen );
typedef int  ( *FS_PHYERASE )( long block );
typedef int  ( *FS_PHYWRITE )( void * data, long block, long relsector, long size, long signdata );
typedef int  ( *FS_PHYVERIFY )( void * data, long block, long relsector, long size, long signdata );
typedef int  ( *FS_PHYCHECK )( long block );
typedef long ( *FS_PHYSIGN )( long block );
typedef int  ( *FS_PHYCACHE )( void * data, long block, long page, long pagenum, long signdata );
typedef int  ( *FS_PHYBLKCPY )( long destblock, long soublock );

/*  definitions for FLASH info and phy  */

typedef struct FS_FLASH
{
  long            maxblock;          /* maximum number of block can be used */
  long            blocksize;         /* block size in bytes */
  long            sectorsize;        /* sector size wanted to use (less than block size */
  long            sectorperblock;    /* sector per block (block size/sector size); */
  long            blockstart;        /* where relative physically block start */
  long            descsize;          /* max size of fat+directory+block index */
  long            descblockstart;    /* 1st block which is used for descriptor above (NOR) */
  long            descblockend;      /* last block which is used for descriptor above (NOR) */
  long            separatedir;       /* if directory used separatelly from FAT (NAND) */
  long            cacheddescsize;    /* cached descriptor size in descriptor < descsize (NOR) */
  long            cachedpagenum;     /* cached pagenum (page/block NAND) */
  long            cachedpagesize;    /* cached page size (page size. cachedpagenum*cachedpagesize=blocksize */
  FS_PHYREAD      ReadFlash;         /* read content */
  FS_PHYERASE     EraseFlash;        /* erase a block */
  FS_PHYWRITE     WriteFlash;        /* write content */
  FS_PHYVERIFY    VerifyFlash;       /* verify content */
  FS_PHYCHECK     CheckBadBlock;     /* check if block is bad block (NAND) */
  FS_PHYSIGN      GetBlockSignature; /* get block signature data (NAND) */
  FS_PHYCACHE     WriteVerifyPage;   /* Write and verify page (NAND) */
  FS_PHYBLKCPY    BlockCopy;         /* HW/SW accelerated block copy in physical (NAND/NOR) optional */
  unsigned char * chkeraseblk;       /* buffer for preerasing blocks optional request to erase */
  unsigned char * erasedblk;         /* buffer for preerasing blocks optional set to erased */
} _FS_FLASH;

typedef int ( *FS_PHYGETID )( FS_FLASH * flash );

typedef struct
{
  unsigned long  total;
  unsigned long  free;
  unsigned long  used;
  unsigned long  bad;
} FS_SPACE;


/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/*  Init Functions   */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */
extern int fg_init ( void );

extern int fsm_mountdrive ( int drivenum, void * buffer, long buffsize, void * mountfunc, FS_PHYGETID phyfunc );
extern int fsm_unmountdrive ( int drivenum );
extern int fsm_getfreespace ( int drivenum, FS_SPACE * space );
extern int fsm_enterFS ( void );
extern void fsm_releaseFS ( void );

extern int fsm_format ( int drivenum );
extern int fsm_get_drive_list ( int * buf );
extern int fsm_get_drive_count ( void );

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/*  Directory handler functions  */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fsm_getdrive ( void );
extern int fsm_chdrive ( int drivenum );

extern int fsm_getcwd ( char * buffer, int maxlen );
extern int fsm_getdcwd ( int drivenum, char * buffer, int maxlen );

extern int fsm_mkdir ( const char * dirname );
extern int fsm_chdir ( const char * dirname );
extern int fsm_rmdir ( const char * dirname );

/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/*  files functions  */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */

extern int fsm_rename ( const char * filename, const char * newname );
extern int fsm_move ( const char * filename, const char * newname );
extern int fsm_delete ( const char * filename );

extern long fsm_filelength ( const char * filename );

extern int fsm_findfirst ( const char * filename, FS_FIND * find );
extern int fsm_findnext ( FS_FIND * find );

extern int fsm_getpermission ( const char * filename, unsigned long * psecure );
extern int fsm_setpermission ( const char * filename, unsigned long secure );


/* Beginning of file */
#ifdef SEEK_SET
 #define FS_SEEK_SET SEEK_SET
#else
 #define FS_SEEK_SET 0
#endif

/* Current position of file pointer */
#ifdef SEEK_CUR
 #define FS_SEEK_CUR SEEK_CUR
#else
 #define FS_SEEK_CUR 1
#endif

/* End of file */
#ifdef SEEK_END
 #define FS_SEEK_END SEEK_END
#else
 #define FS_SEEK_END 2
#endif


/* //////////////////////////////////////////////////////////////////////////////////// */
/*  */
/*  file read/write functions    */
/*  */
/* //////////////////////////////////////////////////////////////////////////////////// */
extern FS_FILE * fsm_open ( const char * filename, const char * mode );
extern int fsm_close ( FS_FILE * filehandle );
extern int fsm_abortclose ( FS_FILE * filehandle );
extern long fsm_write ( const void * buf, long size, long size_st, FS_FILE * filehandle );
extern long fsm_read ( void * buf, long size, long size_st, FS_FILE * filehandle );
extern int fsm_seek ( FS_FILE * filehandle, long offset, long whence );
extern long fsm_tell ( FS_FILE * filehandle );
extern int fsm_eof ( FS_FILE * filehandle );
extern int fsm_rewind ( FS_FILE * filehandle );
extern int fsm_putc ( int ch, FS_FILE * filehandle );
extern int fsm_getc ( FS_FILE * filehandle );
extern int fsm_flush ( FS_FILE * filehandle );
extern int fsm_seteof ( FS_FILE * filehandle );


extern int fsm_settimedate ( const char * filename, unsigned short ctime, unsigned short cdate );
extern int fsm_gettimedate ( const char * filename, unsigned short * ctime, unsigned short * cdate );
extern int fsm_getlabel ( int drivenum, char * label, long len );
extern int fsm_setlabel ( int drivenum, const char * label );
extern FS_FILE * fsm_truncate ( const char * filename, unsigned long length );
extern int fsm_stat ( const char * filename, FS_STAT * stat );
extern int fsm_ftruncate ( FS_FILE * filehandle, unsigned long length );
extern int fsm_checkvolume ( int drvnumber );
extern int fsm_get_oem ( int drivenum, char * str, long maxlen );
extern int fsm_getlasterror ( void );


#ifdef HCC_UNICODE
extern int fsm_wgetcwd ( W_CHAR * buffer, int maxlen );
extern int fsm_wgetdcwd ( int drivenum, W_CHAR * buffer, int maxlen );
extern int fsm_wmkdir ( const W_CHAR * dirname );
extern int fsm_wchdir ( const W_CHAR * dirname );
extern int fsm_wrmdir ( const W_CHAR * dirname );
extern int fsm_wrename ( const W_CHAR * filename, const W_CHAR * newname );
extern int fsm_wmove ( const W_CHAR * filename, const W_CHAR * newname );
extern int fsm_wdelete ( const W_CHAR * filename );
extern long fsm_wfilelength ( const W_CHAR * filename );
extern int fsm_wfindfirst ( const W_CHAR * filename, FS_WFIND * find );
extern int fsm_wfindnext ( FS_WFIND * find );
extern int fsm_wgetpermission ( const W_CHAR * filename, unsigned long * psecure );
extern int fsm_wsetpermission ( const W_CHAR * filename, unsigned long secure );
extern FS_FILE * fsm_wopen ( const W_CHAR * filename, const W_CHAR * mode );
extern int fsm_wsettimedate ( const W_CHAR * filename, unsigned short ctime, unsigned short cdate );
extern int fsm_wgettimedate ( const W_CHAR * filename, unsigned short * ctime, unsigned short * cdate );
extern FS_FILE * fsm_wtruncate ( const W_CHAR * filename, unsigned long length );
extern int fsm_wstat ( const W_CHAR * filename, FS_STAT * stat );
#endif /* ifdef HCC_UNICODE */

#if ( !FS_CAPI_USED )
 #define f_init fg_init
 #define f_mountdrive( drivenum, buffer, buffsize, mountfunc, phyfunc ) fsm_mountdrive( drivenum, buffer, buffsize, mountfunc, phyfunc )
 #define f_unmountdrive( drvnum )                                       fsm_unmountdrive( drvnum )
 #define f_format( drivenum )                                           fsm_format( drivenum )
 #define f_getfreespace( drivenum, space )                              fsm_getfreespace( drivenum, space )
 #define f_enterFS         fsm_enterFS
 #define f_releaseFS()                                                  fsm_releaseFS()
 #define f_get_drive_list( buf )                                        fsm_get_drive_list( buf )
 #define f_get_drive_count fsm_get_drive_count
 #define f_getdrive        fsm_getdrive
 #define f_chdrive( drivenum )                                          fsm_chdrive( drivenum )
 #define f_getcwd( buffer, maxlen )                                     fsm_getcwd( buffer, maxlen )
 #define f_getdcwd( drivenum, buffer, maxlen )                          fsm_getdcwd( drivenum, buffer, maxlen )
 #define f_mkdir( dirname )                                             fsm_mkdir( dirname )
 #define f_chdir( dirname )                                             fsm_chdir( dirname )
 #define f_rmdir( dirname )                                             fsm_rmdir( dirname )
 #define f_setlabel( drivenum, label )                                  fsm_setlabel( drivenum, label )
 #define f_getlabel( drivenum, label, len )                             fsm_getlabel( drivenum, label, len )
 #define f_rename( filename, newname )                                  fsm_rename( filename, newname )
 #define f_move( filename, newname )                                    fsm_move( filename, newname )
 #define f_delete( filename )                                           fsm_delete( filename )
 #define f_filelength( filename )                                       fsm_filelength( filename )
 #define f_findfirst( filename, find )                                  fsm_findfirst( filename, find )
 #define f_findnext( find )                                             fsm_findnext( find )
 #define f_open( filename, mode )                                       fsm_open( filename, mode )
 #define f_close( filehandle )                                          fsm_close( filehandle )
 #define f_abortclose( filehandle )                                     fsm_abortclose( filehandle )
 #define f_write( buf, size, size_st, filehandle )                      fsm_write( buf, size, size_st, filehandle )
 #define f_read( buf, size, size_st, filehandle )                       fsm_read( buf, size, size_st, filehandle )
 #define f_seek( filehandle, offset, whence )                           fsm_seek( filehandle, offset, whence )
 #define f_tell( filehandle )                                           fsm_tell( filehandle )
 #define f_eof( filehandle )                                            fsm_eof( filehandle )
 #define f_seteof( filehandle )                                         fsm_seteof( filehandle )
 #define f_rewind( filehandle )                                         fsm_rewind( filehandle )
 #define f_putc( ch, filehandle )                                       fsm_putc( ch, filehandle )
 #define f_getc( filehandle )                                           fsm_getc( filehandle )
 #define f_flush( filehandle )                                          fsm_flush( filehandle )
 #define f_settimedate( filename, ctime, cdate )                        fsm_settimedate( filename, ctime, cdate )
 #define f_gettimedate( filename, pctime, pcdate )                      fsm_gettimedate( filename, pctime, pcdate )
 #define f_getpermission( filename, psecure )                           fsm_getpermission( filename, psecure )
 #define f_setpermission( filename, secure )                            fsm_setpermission( filename, secure )
 #define f_truncate( filename, length )                                 fsm_truncate( filename, length )
 #define f_stat( filename, stat )                                       fsm_stat( filename, stat )
 #define f_ftruncate( filehandle, length )                              fsm_ftruncate( filehandle, length )
 #define f_checkvolume( drvnumber )                                     fsm_checkvolume( drvnumber )
 #define f_get_oem( drivenum, str, maxlen )                             fsm_get_oem( drivenum, str, maxlen )
 #define f_getlasterror fsm_getlasterror
#endif /* !FS_CAPI_USED */

#ifdef HCC_UNICODE
 #if ( !FS_CAPI_USED )
  #define F_WFIND FS_WFIND
  #define f_wgetcwd( buffer, maxlen )              fsm_wgetcwd( buffer, maxlen )
  #define f_wgetdcwd( drivenum, buffer, maxlen )   fsm_wgetdcwd( drivenum, buffer, maxlen )
  #define f_wmkdir( dirname )                      fsm_wmkdir( dirname )
  #define f_wchdir( dirname )                      fsm_wchdir( dirname )
  #define f_wrmdir( dirname )                      fsm_wrmdir( dirname )
  #define f_wrename( filename, newname )           fsm_wrename( filename, newname )
  #define f_wmove( filename, newname )             fsm_wmove( filename, newname )
  #define f_wdelete( filename )                    fsm_wdelete( filename )
  #define f_wfilelength( filename )                fsm_wfilelength( filename )
  #define f_wfindfirst( filename, find )           fsm_wfindfirst( filename, find )
  #define f_wfindnext( find )                      fsm_wfindnext( find )
  #define f_wopen( filename, mode )                fsm_wopen( filename, mode )
  #define f_wsettimedate( filename, ctime, cdate ) fsm_wsettimedate( filename, ctime, cdate )
  #define f_wgettimedate( filename, ctime, cdate ) fsm_wgettimedate( filename, ctime, cdate )
  #define f_wgetpermission( filename, psecure )    fsm_wgetpermission( filename, psecure )
  #define f_wsetpermission( filename, secure )     fsm_wsetpermission( filename, secure )
  #define f_wtruncate( filename, length )          fsm_wtruncate( filename, length )
  #define f_wstat( filename, stat )                fsm_wstat( filename, stat )
 #endif /* if ( !FS_CAPI_USED ) */
#endif  /* ifdef HCC_UNICODE */

#ifdef __cplusplus
}
#endif


/****************************************************************************
 *
 * End of api_safe.h
 *
 ***************************************************************************/

#endif /* _API_SAFE_H_ */
