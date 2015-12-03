#ifndef _RAMDRV_S_FPT_H_

#define _RAMDRV_S_FPT_H_

typedef void (* ram_memcpy_FP_T) ( void * dest, void * sou, long len );
typedef int (* StoreFat_Ram_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* StoreSector_Ram_FP_T) ( FS_VOLUMEINFO * vi, FS_FILEINT * file, void * data, long len );
typedef int (* GetSector_Ram_FP_T) ( const FS_VOLUMEINFO * vi, long secnum, void * data, long offset, long datalen );
typedef int (* Format_Ram_FP_T) ( FS_VOLUMEINFO * vi );
typedef int (* fs_mount_ramdrive_FP_T) ( FS_VOLUMEDESC * vd, FS_PHYGETID phyfunc );

extern _RPST_ ram_memcpy_FP_T ram_memcpy_FP;
extern _RPST_ StoreFat_Ram_FP_T StoreFat_Ram_FP;
extern _RPST_ StoreSector_Ram_FP_T StoreSector_Ram_FP;
extern _RPST_ GetSector_Ram_FP_T GetSector_Ram_FP;
extern _RPST_ Format_Ram_FP_T Format_Ram_FP;
extern _RPST_ fs_mount_ramdrive_FP_T fs_mount_ramdrive_FP;

#endif
