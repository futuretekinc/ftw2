#ifndef _N25Q_32MB_3V_65NM_H_
#define _N25Q_32MB_3V_65NM_H_


#include <safe-flash\common\fsf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* functions implemented */
extern int fs_phy_nor_n25q_32mb_3v_65nm( FS_FLASH * flash );

typedef struct APP_FS_PARTITION_INFO
{
	UINT32 block_start; 
	UINT32 desc_block_start; 
	UINT32 max_blocks;
}APP_FS_PARTITION_INFO_T;

typedef enum APP_FS_PARTITITON
{
	APP_FS_PARTN_CONFIG,
	APP_FS_PARTN_WEB_PAGES,
	APP_FS_MAX_PARTITION
}APP_FS_PARTITITON_T;

typedef struct APP_FS
{
	APP_FS_PARTITION_INFO_T partn[APP_FS_MAX_PARTITION];

}APP_FS_T;

GSN_STATUS
App_FsInit(APP_FS_T *pFsCtx);

#ifdef __cplusplus
}
#endif

#endif

