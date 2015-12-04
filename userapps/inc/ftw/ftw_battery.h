#ifndef _FTW_BATTERY_H_
#define _FTW_BATTERY_H_

#include "ftw_types.h"

/*******Battery check******************************************************************************************/
UINT32  FTW_BAT_chkAvgValueGet(void);
FTW_RET FTW_BAT_CHECK_levelSet(UINT32 warningLvl,UINT8 warningFreq,UINT32 stdByLvl);
FTW_RET FTW_BAT_CHECK_param(UINT32 * data);
void    FTW_BAT_CHECK_process(void);
FTW_RET FTW_BAT_CHECK_set(UINT32 data);
FTW_RET FTW_BAT_CHECK_start(UINT32 data);
FTW_RET FTW_BAT_CHECK_stop(void);
FTW_RET FTW_BAT_CHECK_valueGet(UINT16 * val);
/*******Battery check******************************************************************************************/

#endif