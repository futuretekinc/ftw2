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

#ifndef _FSM_H_
#define _FSM_H_

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

typedef struct
{
  unsigned char   attr;         /* attribute of the file */
  unsigned short  nlfn1;        /* next lfn entry */
  unsigned short  nlfn2;        /* next lfn entry */
} FS_DIRENTRY_LFN;

#if HCC_16BIT_CHAR
 #define FS_MAXLFN          ( ( sizeof( FS_DIRENTRY ) - sizeof( FS_DIRENTRY_LFN ) ) >> 1 )
#else
 #define FS_MAXLFN          ( ( sizeof( FS_DIRENTRY ) - sizeof( FS_DIRENTRY_LFN ) ) >> 1 )
#endif

#define FS_MAXLNAME         ( FS_MAXDENAME + 4 * FS_MAXLFN ) /*  maximum name length -> 13+4*13 => 65  */

/*  definitions for file/entry attribute  */
#define FS_ATTR_ALLLFN1     ( FS_ATTR_LFN1 | FS_ATTR_LFN1NXT | FS_ATTR_LFN1NXTTOP )
#define FS_ATTR_ALLLFN2     ( FS_ATTR_LFN2 | FS_ATTR_LFN2NXT | FS_ATTR_LFN2NXTTOP )

#if TI_COMPRESS
 #define FS_ATTR_COMPRESSED 0x100   /* file is compressed */
#endif


/****************************************************************************
 *
 * for file changed events
 *
 ***************************************************************************/

#if F_FILE_CHANGED_EVENT && ( !FS_CAPI_USED )

typedef struct
{
  unsigned char   action;
  unsigned char   flags;
  unsigned char   attr;
  unsigned short  ctime;
  unsigned short  cdate;
  unsigned long   filesize;
  char            filename[ FS_MAXPATHNAME ];
} ST_FILE_CHANGED;

typedef void ( *F_FILE_CHANGED_EVENTFUNC )( ST_FILE_CHANGED * fc );

extern F_FILE_CHANGED_EVENTFUNC  f_filechangedevent;

 #define f_setfilechangedevent( filechangeevent ) f_filechangedevent = filechangeevent

/* flags */

 #define FFLAGS_NONE              0x00000000

 #define FFLAGS_FILE_NAME         0x00000001
 #define FFLAGS_DIR_NAME          0x00000002
 #define FFLAGS_NAME              0x00000003
 #define FFLAGS_ATTRIBUTES        0x00000004
 #define FFLAGS_SIZE              0x00000008
 #define FFLAGS_LAST_WRITE        0x00000010

/* actions */

 #define FACTION_ADDED            0x00000001
 #define FACTION_REMOVED          0x00000002
 #define FACTION_MODIFIED         0x00000003
 #define FACTION_RENAMED_OLD_NAME 0x00000004
 #define FACTION_RENAMED_NEW_NAME 0x00000005

#endif /* if F_FILE_CHANGED_EVENT && ( !FS_CAPI_USED ) */


/*  definitions for dirnum variable  */

#define FS_DIR_ROOT      ( (unsigned short)0xffff )
#define FS_DIR_LABEL     ( (unsigned short)0xfff0 )

/*  definitions for fs_file state  */

#define ST_FILE_LOADED   0x01
#define ST_FILE_SYNC     0x02
#define ST_FILE_NEXTPROH 0x04
#define ST_FILE_CRCON    0x08

/*  definitions for fs_file mode  */

enum
{
  FS_FILE_CLOSE
  , FS_FILE_RD
  , FS_FILE_RDP
  , FS_FILE_WR
  , FS_FILE_WRP
  , FS_FILE_A
  , FS_FILE_AP
  , FS_FILE_ABORT
  , FS_FILE_LOCKED
};


/* distance for preerased blk selection */
#define FS_MAXPREDISTANCE     128

#define FS_CHACHETYPE_DESC    0x8001
#define FS_CHACHETYPE_DIR     0x8002

#define FS_STCACHE_DESCCHANGE 0x01 /* descriptor change */
#define FS_STCACHE_DIRCHANGE  0x02 /* direntry change */
#define FS_STCACHE_FULL       0x04 /* cache full */
#define FS_STCACHE_ENTRY      0x08 /* cache has entry */

/*  definitions for multicwd   */

#if ( !FS_CAPI_USED )
typedef struct
{
  uint32_t       i_used;            /* this entry is used */
  F_TASKID_TYPE  ID;                /* task id */
 #if USE_TASK_SEPARATED_CWD
  int            fs_curdrive;          /* current drive */
  struct
  {
    W_CHAR  cwd[ FS_MAXPATHNAME ];      /* current working folder in this volume */
  } fs_vols[ FS_MAXVOLUME ];
 #endif

  FS_MUTEX_TYPE * pmutex;        /* for multitasking */
  int             lasterror;     /* last error in this task */
} FS_MULTI;

extern FS_MULTI  gl_multi[ FS_MAXTASK ]; /* array for multitask users */

#endif /* if ( !FS_CAPI_USED ) */


/*  definitions for volume info   */
typedef struct
{
  int              drivenum;     /* which drive is to belong 0-a, 1-b, ... */
  char           * buffer;       /* next alloc pointer for alloc data function */
  long             freemem;      /* free memory space on alloc */
  long             usedmem;      /* used memory */
  long             maxsectornum; /* maximum sector used */
  unsigned short * _fat;         /* pointer to memory FAT (data found after volumeinfo) */
  unsigned short * fatmirror;    /* pointer to memory FAT (data found after volumeinfo) */

#if USE_TASK_SEPARATED_CWD
  W_CHAR * cwd;                 /* current working folder in this volume, points to task cwd */
#else
  W_CHAR   cwd[ FS_MAXPATHNAME ];   /* current working folder in this volume */
#endif

  unsigned int     maxdirentry;    /* directory entry used */
  FS_DIRENTRY    * direntries;     /* pointer to dirinfo */
  long             sectorsize;     /* sector size */
  int              maxfile;        /* maximum number of used file */
  FS_FILEINT     * files;          /* s_fileint pointers */
  FS_FLASH       * flash;          /* flash device properties */
  FS_FATDESC     * fatdesc;        /* user driver data 1 */
  char           * ramdrivedata;   /* ramdrive data pointer */
  unsigned char  * zerosector;     /* nandflash zero sector */
  hcc_32         * _wearlevel;     /* used for wear leveling */
  long             resetwear;      /* signal if wear leveling useable or need resetting */
  long             maxfat;         /* maximum number of fat */
  long             currfat;        /* current fat */
  unsigned long  * fatbits;        /* preerased blocks sectors state */
  unsigned short   fatbitsblock;   /* preerased blocks logical number */
  unsigned short   prevbitsblock;  /* previously block have contained sectors */
  unsigned short   lockblock;      /* lock block for previous stored block */
  unsigned long  * copybits;       /* previous block sector copy needed state */
  unsigned short * _blockindex;    /* block orders (maxblock used size); */
  char           * rdbuffer;       /* temporary block reading then writing (block size) */
  FS_WRCACHE       cache;          /* descriptor cache */
  long             laststaticwear; /* last static weared block */
  long             staticcou;      /* static counter for period counter */
  FS_MUTEX_TYPE    mutex;          /* for multitasking */
  long           * version;        /* pointer to stored data driver version */
  int              stoperr;        /* flag for stop using filesystem */
  unsigned long    reserved;       /* reserved size */
  int              dobadblock;     /* endif */
  long             desc1;          /* descriptor 1 physical */
  long             desc2;          /* descriptor 2 physical */
  long           * pnextdesc;      /* pointer to next descriptor */
} FS_VOLUMEINFO;


/*  definitions for driver functions   */

typedef int ( *FS_DRVFUNC1 )( FS_VOLUMEINFO * vi );
typedef int ( *FS_DRVFUNC2 )( FS_VOLUMEINFO * vi, FS_FILEINT * file, void * data, long datalen );
typedef int ( *FS_DRVFUNC4 )( const FS_VOLUMEINFO * vi, long secnum, void * data, long offset, long datalen );

/*  definitions for volume descriptor  */


typedef struct
{
  FS_DRVFUNC1     storefat;     /* function pointer */
  FS_DRVFUNC2     storesector;  /* function pointer */
  FS_DRVFUNC4     getsector;    /* function pointer */
  FS_DRVFUNC1     format;       /* function pointer */
  FS_VOLUMEINFO * vi;           /* volumeinfo pointer */
  int             state;        /* state of this volume  */
} FS_VOLUMEDESC;

typedef int ( *FS_DRVMOUNT )( FS_VOLUMEDESC * vd, FS_PHYGETID phyfunc );


/*  definitions for volumedesc state  */

#define FS_VOL_OK            0                   /* mounted, formatted */
#define FS_VOL_NOTMOUNT      1                   /* not mounted (init value) */
#define FS_VOL_NOTFORMATTED  2                   /* not formatted must be same as F_ERR_NOTFORMATTED */
#define FS_VOL_NOMEMORY      3                   /* not enougth memory */
#define FS_VOL_NOMORE        4                   /* no more drive availabale */
#define FS_VOL_DRVERROR      5                   /* driver error */
#define FS_VOL_DRVALREADYMNT F_ERR_DRVALREADYMNT /* definitions for drive function mount  */
#define FS_VOL_ALLOCATION    F_ERR_ALLOCATION    /* invalid address of memory (odd)*/
#define FS_VOL_TASKNOTFOUND  F_ERR_TASKNOTFOUND  /* task not found in the list */

/*  definitions for file system  */

typedef struct
{
  FS_VOLUMEDESC  vd[ FS_MAXVOLUME ]; /* volumes */
#if ( !USE_TASK_SEPARATED_CWD )
  int            fs_curdrive;              /* current drive */
#endif
} FS_FILESYSTEM;

/* define fat entries */

#define FS_FAT_FREE    ( (unsigned short)0x0FFFF ) /* - free of used */
#define FS_FAT_EOF     ( (unsigned short)0x0FFF0 ) /* - end of file */
#define FS_FAT_NOTUSED ( (unsigned short)0x0FFF1 ) /* - not useable (maybe bad block or reserved) */
#define FS_FAT_DISCARD ( (unsigned short)0x0FFF2 ) /* - needs to be discard */
#define FS_FAT_CHBLK   ( (unsigned short)0x0FFF3 ) /* - cache block */
#define FS_FAT_LCKBLK  ( (unsigned short)0x0FFF4 ) /* - lock block */
#define FS_FAT_DIR     ( (unsigned short)0x0FFF8 ) /* - directory entry, if separated */

/*  crc defs  */

#define FS_CRCINIT     0xffffffffL

/*  functions for middle layer file system  */

extern long fsm_allocdatasize ( long size );
extern void * fsm_allocdata ( FS_VOLUMEINFO * vi, long size );
extern int fsm_checkname ( const W_CHAR * lname );
extern int fsm_checknamewc ( const W_CHAR * lname );
extern long fsm_setnameext ( char * s, char * name, char * ext );
extern int  fsm_setmaxfile ( FS_VOLUMEINFO * vi, int maxfile );
extern int  fsm_setsectorsize ( FS_VOLUMEINFO * vi, long sectorsize );
extern void fsm_memcpy ( void * d, void * s, long len );
extern hcc_u32 fsm_calccrc32 ( hcc_u32  dwcrc, const void * vbuf, unsigned long  dwlen );
extern int fsm_findfreeblock ( const FS_VOLUMEINFO * vi, unsigned short * sector );
extern void fsm_memset ( void * d, unsigned char fill, long len );
extern int fsm_findfreesector ( FS_VOLUMEINFO * vi, unsigned short * badsector );
extern void fsm_swapbadblock ( FS_VOLUMEINFO * vi, unsigned short badsector );
extern void fsm_wearleveling ( FS_VOLUMEINFO * vi );
extern void fsm_addsectorchain ( const FS_VOLUMEINFO * vi, FS_FILEINT * file, unsigned short sector );
extern int fsm_checksectorfree ( const FS_VOLUMEINFO * vi, long sector );
extern int fsm_checksectorbad ( const FS_VOLUMEINFO * vi, long sector );
extern unsigned long _fs_checkfreeblocks ( const FS_VOLUMEINFO * vi, unsigned long sbnum );
extern W_CHAR _fsm_toupper ( W_CHAR ch );
extern void _fsm_cacheaddlptr ( FS_VOLUMEINFO * vi, hcc_32 * ptr );
extern void _fsm_cacheaddsptr ( FS_VOLUMEINFO * vi, unsigned short * ptr, unsigned short value );
extern void _fsm_cacheaddde ( FS_VOLUMEINFO * vi, void * de );
extern void _fsm_cachepagecheck ( FS_VOLUMEINFO * vi );
extern void _fsm_cachenext ( FS_VOLUMEINFO * vi );
extern void _fsm_cachereset ( FS_VOLUMEINFO * vi );
extern int _fsm_chacheupdatechanges ( FS_VOLUMEINFO * vi );
extern void _fsm_cacheupdate ( FS_VOLUMEINFO * vi );
extern int _fsm_writenextsector ( FS_VOLUMEINFO * vi, FS_FILEINT * file, long relsector, void * data, long signdata );
extern void fg_setlasterror_noret ( FS_MULTI * fm, int errorcode );
extern int fg_setlasterror ( FS_MULTI * fm, int errorcode );
extern int fsm_strlen ( char * string );
extern int fsm_writeverifyflash ( const FS_VOLUMEINFO * vi, void * data, long block, long relsector, long size, long signdata );
extern int fsm_readflash ( const FS_VOLUMEINFO * vi, void * data, long block, long blockrel, long datalen );

#if F_FILE_CHANGED_EVENT
int _fsm_createfullname ( char * buffer, int buffersize, int drivenum, char * path, char * filename );
#endif

#ifdef HCC_UNICODE
extern W_CHAR * _fsm_towchar ( W_CHAR * nconv, const char * s );
extern void _fsm_fromwchar ( char * d, W_CHAR * s );
#endif
#ifdef __cplusplus
}
#endif


/****************************************************************************
 *
 * End of fsm.h
 *
 ***************************************************************************/

#endif   /* _FSM_H_ */

