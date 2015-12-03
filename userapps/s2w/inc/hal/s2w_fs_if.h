#ifndef _N25Q_32MB_3V_65NM_H_
#define _N25Q_32MB_3V_65NM_H_


#include "fs/safe-flash/common/fsf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* functions implemented */

#define CONFIG_FROM_SUPERBLOCK

extern int fs_phy_nor_n25q_32mb_3v_65nm( FS_FLASH * flash );
extern int fs_phy_nor_n25q_32mb_3v_65nm_1( FS_FLASH * flash );

UINT32 s2w_config_fs();
void s2w_config_web_fs(UINT32 fsAddress, UINT32 fsSize);

#ifdef __cplusplus
}
#endif

#endif

