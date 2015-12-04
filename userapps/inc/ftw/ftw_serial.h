#ifndef _FTW_SERIAL_H_
#define _FTW_SERIAL_H_

#include "ftw_types.h"

typedef uint_32 FTW_SERIAL_ID;

#define FTW_SERIAL_0    0
#define FTW_SERIAL_1    0

void    FTW_SERIAL_init(void);

VOID    FTW_SERIAL_putc(FTW_SERIAL_ID xID, UINT8 ch);
VOID    FTW_SERIAL_put(FTW_SERIAL_ID xID, const void *buf, UINT32 len);
VOID    FTW_SERIAL_get(FTW_SERIAL_ID xID, UINT8*buf, UINT32 len);
UINT8   FTW_SERIAL_getc(FTW_SERIAL_ID xID, UINT8*buf);

#endif