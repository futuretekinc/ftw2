#ifndef _FTW_TIME_H_
#define _FTW_TIME_H_

#define FTE_TIME_TICKS_PER_SEC  10

typedef ULONG               FTW_TIME, * FTW_TIME_PTR;
typedef GSN_SYSTEM_TIME_T   FTW_SYS_TIME, * FTW_SYS_TIME_PTR;

void            FTW_TIME_get(FTW_TIME_PTR pxTime);
FTW_TIME        FTW_TIME_diff(FTW_TIME_PTR pTime1, FTW_TIME_PTR pTime2);            
ULONG           FTW_TIME_diffMilliseconds(FTW_TIME_PTR pTime1, FTW_TIME_PTR pTime2);
ULONG           FTW_TIME_diffSeconds(FTW_TIME_PTR pTime1, FTW_TIME_PTR pTime2);
void            FTW_TIME_delay(UINT32   ulMilliSeconds);

FTW_SYS_TIME    FTW_SYS_TIME_get(FTW_SYS_TIME_PTR pSysTime);

#endif
