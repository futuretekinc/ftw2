#ifndef _FTW_CERT_H_
#define _FTW_CERT_H_

#include "ftw_types.h"

#define FTW_CERT_INVALID_INDEX      0xFFFFFFFF
#define FTW_CERT_MAX_NUM            8
#define FTW_CERT_NAME_CA            "TLS_CA"
#define FTW_CERT_NAME_CLIENT        "TLS_CLIENT"
#define FTW_CERT_NAME_KEY           "TLS_KEY"

#define FTW_SSL_CERT_NAME_CA        "SSL_CA"
#define FTW_SSL_CERT_NAME_SERVER    "SSL_SERVER"
#define FTW_SSL_CERT_NAME_KEY       "SSL_KEY"

typedef enum FTW_CERT_LOCATION_ENUM
{
	FTW_CERT_IN_FLASH,
	FTW_CERT_IN_RAM
} FTW_CERT_LOCATION;

/* The Entry for the SRAM Certificate Table */
typedef struct FTW_SSL_CERT_SRAM_TABLE_STRUCT
{
    /* The Actual 32bit address for the certificate */
    UINT8 *             pCertAddress;
    /* Pinter to name of the certificate */
    UINT8 *             pName;
    FTW_CERT_LOCATION   xLocation;
} FTW_SSL_CERT_SRAM_TABLE, _PTR_ FTW_SSL_CERT_SRAM_TABLE_PTR;

FTW_SSL_CERT_SRAM_TABLE_PTR FTW_CERT_searchRamTable(char *ptr);
FTW_SSL_CERT_SRAM_TABLE_PTR FTW_CERT_flashFileLoad(char *fileName);
INT32   FTW_CERT_findFile(char *name);
FTW_SSL_CERT_SRAM_TABLE_PTR FTW_CERT_create(UINT16 size);
FTW_RET FTW_CERT_delete(UINT8 * certName);
#endif

