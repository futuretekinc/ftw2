typedef void (* _chk_preerase_FP_T) ( const FS_VOLUMEINFO * vi );
typedef int (* StoreFat_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* GetFat_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* StoreSector_FP_T) ( FS_VOLUMEINFO * vi, FS_FILEINT * file, void * data, long len );
typedef int (* GetSector_FP_T) ( const FS_VOLUMEINFO * vi, long secnum, void * data, long offset, long datalen );
typedef int (* Format_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* fs_mount_flashdrive_FP_T) ( FS_VOLUMEDESC * vd, FS_PHYGETID phyfunc );
typedef long (* fs_getmem_flashdrive_FP_T) ( FS_PHYGETID phyfunc );


extern _RPST_ _chk_preerase_FP_T _chk_preerase_FP;
extern _RPST_ StoreFat_FP_T StoreFat_FP;
extern _RPST_ GetFat_FP_T GetFat_FP;
extern _RPST_ StoreSector_FP_T StoreSector_FP;
extern _RPST_ GetSector_FP_T GetSector_FP;
extern _RPST_ Format_FP_T Format_FP;
extern _RPST_ fs_mount_flashdrive_FP_T fs_mount_flashdrive_FP;
extern _RPST_ fs_getmem_flashdrive_FP_T fs_getmem_flashdrive_FP;

