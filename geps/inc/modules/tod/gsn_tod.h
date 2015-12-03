#ifndef _GSN_TOD_H_
#define _GSN_TOD_H_

VOID 
GsnTod_Init(GSN_SYSTEM_TIME_T *timeOffset);

GSN_SYSTEM_TIME_T 
GsnTod_Get();

VOID
GsnTod_AdjustOffset(BOOL negative, ULONG64 difference);

#endif
