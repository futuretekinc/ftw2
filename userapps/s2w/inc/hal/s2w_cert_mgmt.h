#ifndef S2W_CERT_MGMT_H
#define S2W_CERT_MGMT_H

#define S2W_INVALID_CERT_INDEX 0xFFFFFFFF
#define S2W_MAX_NUM_CERT        8
#define S2W_CERT_NAME_CA        "TLS_CA"
#define S2W_CERT_NAME_CLIENT    "TLS_CLIENT"
#define S2W_CERT_NAME_KEY       "TLS_KEY"

#define S2W_SSL_CERT_NAME_CA        "SSL_CA"
#define S2W_SSL_CERT_NAME_SERVER    "SSL_SERVER"
#define S2W_SSL_CERT_NAME_KEY       "SSL_KEY"

typedef enum S2W_CERT_LOCATION
{
	CERT_IN_FLASH,
	CERT_IN_RAM
}S2W_CERT_LOCATION_T;

/* The Entry for the SRAM Certificate Table */
typedef struct S2W_SSL_CERT_SRAM_TABLE
{
    /* The Actual 32bit address for the certificate */
    UINT8 *certAddress;
    /* Pinter to name of the certificate */
    UINT8 *name;
    S2W_CERT_LOCATION_T location;
}S2W_SSL_CERT_SRAM_TABLE_T;

PUBLIC INT32
S2wCert_SearchRamTable(char *ptr);

PUBLIC INT32
S2wCert_FlashFileLoad(char *fileName);

INT32
S2wCert_findFile(char *name);

PUBLIC INT32
S2wCert_MemAlloc (UINT16 size);

PUBLIC UINT8
AppS2w_CertDelete(UINT8 * certName);
#endif
