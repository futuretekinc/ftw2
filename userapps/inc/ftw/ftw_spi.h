#ifndef _FTW_SPI_H_
#define _FTW_SPI_H_

#include "ftw_types.h"

typedef UINT32  FTW_SPI_ID;

#define FTW_SPI_ALL 0xFFFFFFFF

VOID    FTW_SPI_flush(FTW_SPI_ID xID);
#endif