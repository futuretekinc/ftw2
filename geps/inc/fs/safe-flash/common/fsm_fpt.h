#ifndef _FSM_FPT_H_

#define _FSM_FPT_H_

typedef hcc_u32 (* fsm_calccrc32_FP_T) ( hcc_u32  dwcrc, const void * vbuf, unsigned long  dwlen );
typedef void (* fsm_memcpy_FP_T) ( void * d, void * s, long len );
typedef void (* fsm_memset_FP_T) ( void * d, unsigned char fill, long len );
typedef long (* fsm_allocdatasize_FP_T) ( long size );
typedef void * (* fsm_allocdata_FP_T) ( FS_VOLUMEINFO * vi, long size );
#ifdef HCC_UNICODE
typedef W_CHAR * (* _fsm_towchar_FP_T) ( W_CHAR * nconv, const char * s );
#endif /* ifdef HCC_UNICODE */
#if F_FILE_CHANGED_EVENT
typedef int (* _fsm_createfullname_FP_T) ( char * buffer, int buffersize, int drivenum, char * path, char * filename );
#endif /* if F_FILE_CHANGED_EVENT */
#ifdef HCC_UNICODE
typedef void (* _fsm_fromwchar_FP_T) ( char * d, W_CHAR * s );
#endif
typedef int (* fsm_checkname_FP_T) ( const W_CHAR * lname );
typedef int (* fsm_checknamewc_FP_T) ( const W_CHAR * lname );
typedef int (* fsm_setsectorsize_FP_T) ( FS_VOLUMEINFO * vi, long sectorsize );
typedef int (* fsm_setmaxfile_FP_T) ( FS_VOLUMEINFO * vi, int maxfile );
typedef int (* fsm_findfreeblock_FP_T) ( const FS_VOLUMEINFO * vi, unsigned short * psector );
typedef unsigned long (* _fs_checkfreeblocks_FP_T) ( const FS_VOLUMEINFO * vi, unsigned long sbnum );
typedef void (* fsm_swapbadblock_FP_T) ( FS_VOLUMEINFO * vi, unsigned short badsector );
typedef int (* _fsm_swapbadphy_FP_T) ( FS_VOLUMEINFO * vi, long signdata, long block );
typedef int (* _fsm_writenextsector_FP_T) ( FS_VOLUMEINFO * vi, FS_FILEINT * file, long relsector, void * data, long signdata );
typedef void (* fsm_wearleveling_FP_T) ( FS_VOLUMEINFO * vi );
typedef void (* fsm_addsectorchain_FP_T) ( const FS_VOLUMEINFO * vi, FS_FILEINT * file, unsigned short sector );
typedef int (* fsm_checksectorfree_FP_T) ( const FS_VOLUMEINFO * vi, long sector );
typedef int (* fsm_checksectorbad_FP_T) ( const FS_VOLUMEINFO * vi, long sector );
typedef W_CHAR (* _fsm_toupper_FP_T) ( W_CHAR ch );
typedef void (* _fsm_cacheaddvptr_FP_T) ( FS_VOLUMEINFO * vi, void * ptr );
typedef void (* _fsm_cacheaddsptr_FP_T) ( FS_VOLUMEINFO * vi, unsigned short * ptr, unsigned short value );
typedef void (* _fsm_cacheaddlptr_FP_T) ( FS_VOLUMEINFO * vi, hcc_32 * ptr );
typedef void (* _fsm_cacheaddde_FP_T) ( FS_VOLUMEINFO * vi, void * de );
typedef void (* _fsm_cachede_FP_T) ( FS_VOLUMEINFO * vi, void * de );
typedef void (* _fsm_cacheupdate_FP_T) ( FS_VOLUMEINFO * vi );
typedef void (* _fsm_cachepagecheck_FP_T) ( FS_VOLUMEINFO * vi );
typedef void (* _fsm_cachenext_FP_T) ( FS_VOLUMEINFO * vi );
typedef void (* _fsm_cachereset_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* _fsm_chacheupdatechanges_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* fsm_strlen_FP_T) ( char * string );
typedef int (* fg_setlasterror_FP_T) ( FS_MULTI * fm, int errorcode );
typedef void (* fg_setlasterror_noret_FP_T) ( FS_MULTI * fm, int errorcode );
typedef int (* fsm_readflash_FP_T) ( const FS_VOLUMEINFO * vi, void * data, long block, long blockrel, long datalen );
typedef int (* fsm_writeverifyflash_FP_T) ( const FS_VOLUMEINFO * vi, void * data, long block, long relsector, long size, long signdata );


extern _RPST_ fsm_calccrc32_FP_T fsm_calccrc32_FP;
extern _RPST_ fsm_memcpy_FP_T fsm_memcpy_FP;
extern _RPST_ fsm_memset_FP_T fsm_memset_FP;
extern _RPST_ fsm_allocdatasize_FP_T fsm_allocdatasize_FP;
extern _RPST_ fsm_allocdata_FP_T fsm_allocdata_FP;
#ifdef HCC_UNICODE
extern _RPST_ _fsm_towchar_FP_T _fsm_towchar_FP;
#endif /* ifdef HCC_UNICODE */
#if F_FILE_CHANGED_EVENT
extern _RPST_ _fsm_createfullname_FP_T _fsm_createfullname_FP;
#endif /* if F_FILE_CHANGED_EVENT */
#ifdef HCC_UNICODE
extern _RPST_ _fsm_fromwchar_FP_T _fsm_fromwchar_FP;
#endif
extern _RPST_ fsm_checkname_FP_T fsm_checkname_FP;
extern _RPST_ fsm_checknamewc_FP_T fsm_checknamewc_FP;
extern _RPST_ fsm_setsectorsize_FP_T fsm_setsectorsize_FP;
extern _RPST_ fsm_setmaxfile_FP_T fsm_setmaxfile_FP;
extern _RPST_ fsm_findfreeblock_FP_T fsm_findfreeblock_FP;
extern _RPST_ _fs_checkfreeblocks_FP_T _fs_checkfreeblocks_FP;
extern _RPST_ fsm_swapbadblock_FP_T fsm_swapbadblock_FP;
extern _RPST_ _fsm_swapbadphy_FP_T _fsm_swapbadphy_FP;
extern _RPST_ _fsm_writenextsector_FP_T _fsm_writenextsector_FP;
extern _RPST_ fsm_wearleveling_FP_T fsm_wearleveling_FP;
extern _RPST_ fsm_addsectorchain_FP_T fsm_addsectorchain_FP;
extern _RPST_ fsm_checksectorfree_FP_T fsm_checksectorfree_FP;
extern _RPST_ fsm_checksectorbad_FP_T fsm_checksectorbad_FP;
extern _RPST_ _fsm_toupper_FP_T _fsm_toupper_FP;
extern _RPST_ _fsm_cacheaddvptr_FP_T _fsm_cacheaddvptr_FP;
extern _RPST_ _fsm_cacheaddsptr_FP_T _fsm_cacheaddsptr_FP;
extern _RPST_ _fsm_cacheaddlptr_FP_T _fsm_cacheaddlptr_FP;
extern _RPST_ _fsm_cacheaddde_FP_T _fsm_cacheaddde_FP;
extern _RPST_ _fsm_cachede_FP_T _fsm_cachede_FP;
extern _RPST_ _fsm_cacheupdate_FP_T _fsm_cacheupdate_FP;
extern _RPST_ _fsm_cachepagecheck_FP_T _fsm_cachepagecheck_FP;
extern _RPST_ _fsm_cachenext_FP_T _fsm_cachenext_FP;
extern _RPST_ _fsm_cachereset_FP_T _fsm_cachereset_FP;
extern _RPST_ _fsm_chacheupdatechanges_FP_T _fsm_chacheupdatechanges_FP;
extern _RPST_ fsm_strlen_FP_T fsm_strlen_FP;
extern _RPST_ fg_setlasterror_FP_T fg_setlasterror_FP;
extern _RPST_ fg_setlasterror_noret_FP_T fg_setlasterror_noret_FP;
extern _RPST_ fsm_readflash_FP_T fsm_readflash_FP;
extern _RPST_ fsm_writeverifyflash_FP_T fsm_writeverifyflash_FP;

#endif
