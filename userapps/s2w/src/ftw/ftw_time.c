#include "ftw_includes.h"
#include "ftw_time.h"

void    FTW_TIME_get(FTW_TIME_PTR pxTime)
{
    ASSERT(pxTime != NULL);
    
    *pxTime = tx_time_get();
}

ULONG   FTW_TIME_diffMilliseconds(FTW_TIME_PTR pTime1, FTW_TIME_PTR pTime2)
{
    ASSERT((pTime1 != NULL) && (pTime2 != NULL));
    
    return  ((*pTime1) - (*pTime2)) * (1000 / FTE_TIME_TICKS_PER_SEC);
}

ULONG   FTW_TIME_diffSeconds(FTW_TIME_PTR pTime1, FTW_TIME_PTR pTime2)
{
    ASSERT((pTime1 != NULL) && (pTime2 != NULL));
    
    return  ((*pTime1) - (*pTime2)) / FTE_TIME_TICKS_PER_SEC;
}

FTW_TIME    FTW_TIME_diff(FTW_TIME_PTR pTime1, FTW_TIME_PTR pTime2)
{
    ASSERT((pTime1 != NULL) && (pTime2 != NULL));
    
    return  ((*pTime1) - (*pTime2));
}

void    FTW_TIME_delay(UINT32   ulMilliSeconds)
{
    ULONG   ulTicks = 1;
    
    if (ulMilliSeconds >= (1000 / FTE_TIME_TICKS_PER_SEC))
    {
        ulTicks = ulMilliSeconds / (1000 / FTE_TIME_TICKS_PER_SEC);
    }
    tx_thread_sleep(ulTicks);
}

FTW_SYS_TIME FTW_SYS_TIME_get(FTW_SYS_TIME_PTR pSysTime)
{
    GSN_SYSTEM_TIME_T   xCurrentTime;
    FTW_SYS_TIME        xSysTime;
    
    xCurrentTime= GsnTod_Get();
    xSysTime = SYSTIME_TO_MSEC(xCurrentTime);
    
    if (pSysTime != NULL)
    {
        *pSysTime = xSysTime;
    }

    return  xSysTime;
}
        

