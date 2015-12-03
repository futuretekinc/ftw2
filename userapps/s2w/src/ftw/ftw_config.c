#include "ftw_config.h"

static const char_ptr _pFullPathDir = "config";

static const FTW_CONFIG  _xDefaultConfig = 
{
    .xNet = 
    {
        .pSSID  =   "FTR-01",
        .pWWPA  =   "4rnekd9wkd"
    },
    
    .xMQTT = 
    {
        .pClientID = "001dc914feae",
        .bEnable = TRUE,
        .xBroker = 
        {
            .xServer    =
            {
                .xIPAddress     = { 54, 178, 154, 197},
                .usPort         = 8883,
            },
            .xKeepalive =
            {
                .ulTime         = 30000,    // ms
                .ulRetryCount   = 5,
            },
            .xAuth = 
            {
                .bEnabled = 1,
                .pUserName = "001dc914feae",
                .pPassword = "Sm4ytjGsPEfGvDhSDJ_ZPiBUXyo="
            },
        },    
        .xTester = 
        {
            .ulStartDelay       = 10000,    // ms
            .xStatus    =
            {
                .ulPeriod       = 60000
            },
            .ulSensorCount      = 1,
            .xSensors   =
            {
                {
                    .pName=     "temperature-001dc914feae-1",
                    .ulPeriod   = 5000
                }
            }
        },
        .ulPubTimeout = 10000,              // ms
    }    
};

static FTW_CONFIG_PTR  _pxConfig  = NULL;

FTW_RET FTW_CONFIG_init(char_ptr pFileName)
{
    if (FTW_CONFIG_load(pFileName) != FTW_RET_OK)
    {
        FTW_TRACE("Default configuration loaded.\n");
        FTW_CONFIG_loadDefault();
    }
    
    return  FTW_RET_OK;
}

FTW_RET FTW_CONFIG_loadDefault(void)
{
    FTW_RET         xRet = FTW_RET_OK;

    if (_pxConfig == NULL)
    {
        _pxConfig = FTW_MEM_allocZero(sizeof(FTW_CONFIG));
        if (_pxConfig == NULL)
        {
            return  FTW_RET_NOT_ENOUGH_MEMORY;
        }
    }

    memcpy(_pxConfig, &_xDefaultConfig, sizeof(FTW_CONFIG));        
    
    return  xRet;
}

FTW_RET FTW_CONFIG_load(char_ptr pFileName)
{
    FTW_RET         xRet = FTW_RET_OK;
    char_ptr        pFullPathName = NULL;
    uint_32         ulFullPathNameLen;
    F_FILE          *pFile;
    FTW_CONFIG_PTR  pxConfig;
    
    ulFullPathNameLen = strlen(_pFullPathDir) + 1 + strlen(pFileName);
    pFullPathName = FTW_MEM_allocZero(ulFullPathNameLen + 1);
    if (pFullPathName == NULL)
    {
        FTW_TRACE("Not enough memory.\n");
        xRet = FTW_RET_NOT_ENOUGH_MEMORY;
        goto error;
    }
    
    snprintf(pFullPathName, ulFullPathNameLen, "%s/%s", _pFullPathDir, pFileName);
    
    if (f_filelength(pFullPathName) != sizeof(FTW_CONFIG))
    {
        FTW_TRACE("Invalid configuration file(file size missmatch).\n");
        xRet = FTW_RET_CONFIG_NOT_EXISTS;
        goto error;
    }
    
    pxConfig = FTW_MEM_allocZero(sizeof(FTW_CONFIG));
    if (pxConfig == NULL)
    {
        FTW_TRACE("Not enough memory.\n");
        xRet = FTW_RET_NOT_ENOUGH_MEMORY;
        goto error;
    }
    
    pFile = f_open(pFullPathName, "r");
    if (pFile == NULL)
    {
        FTW_TRACE("Configuration file not exist.\n");
        xRet = FTW_RET_CONFIG_NOT_EXISTS;
        goto error;
    }
        
    f_read(pxConfig, 1, sizeof(FTW_CONFIG), pFile);
    f_close(pFile);

    if (_pxConfig == NULL)
    {
        _pxConfig = FTW_MEM_allocZero(sizeof(FTW_CONFIG));
        if (_pxConfig == NULL)
        {
            FTW_TRACE("Not enough memory.\n");
            xRet = FTW_RET_NOT_ENOUGH_MEMORY;
            goto error;
        }
    }

    memcpy(_pxConfig, pxConfig, sizeof(FTW_CONFIG));        
    
error:    
    if (pxConfig != NULL)
    {
        FTW_MEM_free(pxConfig);
    }
    
    if (pFullPathName != NULL)
    {
        FTW_MEM_free(pFullPathName);
    }
    
    return  xRet;
}

FTW_RET FTW_CONFIG_save(char_ptr pFileName)
{
    FTW_RET         xRet = FTW_RET_OK;
    char_ptr        pFullPathName = NULL;
    uint_32         ulFullPathNameLen;
    F_FILE          *pFile;
    FTW_CONFIG_PTR  pxConfig;
    
    ulFullPathNameLen = strlen(_pFullPathDir) + 1 + strlen(pFileName);
    pFullPathName = FTW_MEM_allocZero(ulFullPathNameLen + 1);
    if (pFullPathName == NULL)
    {
        xRet = FTW_RET_NOT_ENOUGH_MEMORY;
        goto error;
    }
    
    snprintf(pFullPathName, ulFullPathNameLen, "%s/%s", _pFullPathDir, pFileName);    
    if (f_filelength(pFullPathName) != sizeof(FTW_CONFIG))
    {
        xRet = FTW_RET_CONFIG_NOT_EXISTS;
        goto error;
    }
    
    pFile = f_open(pFullPathName, "w");
    if (pFile == NULL)
    {
	    f_mkdir(_pFullPathDir);
        pFile = f_open(pFullPathName, "w");
        if (pFile == NULL)
        {
            xRet = FTW_RET_CONFIG_CANT_CREATE;
            goto error;
        }
    }
        
    f_write(_pxConfig, 1, sizeof(FTW_CONFIG), pFile);
    f_close(pFile);

error:

    if (pFullPathName != NULL)
    {
        FTW_MEM_free(pFullPathName);
    }
    
    return  xRet;
}

FTW_NET_CONFIG_PTR  FTW_CONFIG_getNet(void)
{
    if (_pxConfig != NULL)
    {
        return  &_pxConfig->xNet;
    }
    
    return  NULL;
}
FTW_MQTT_CONFIG_PTR FTW_CONFIG_getMQTT(void)
{
    if (_pxConfig != NULL)
    {
        return  &_pxConfig->xMQTT;
    }
    
    return  NULL;
}
