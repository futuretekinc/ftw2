#include "ftw_includes.h"

static  uint_32 _ulTraceModules = 0;
static  boolean bPrintFunction = FALSE;

void    FTW_DBG_Trace(char const *pFunction, uint_32 ulLine, char *pFormat, ... )
{
    static  uint_32 ulOutputLine = 0;
    va_list     xAP;
    uint_32     ulLen = 0, ulSubLen;
    static char pBuff[2048];
    
    ulLen = sprintf(pBuff,"[%4d] ", ++ulOutputLine);
    
    if ((bPrintFunction) && (pFunction != NULL))
    {
        ulSubLen = sprintf(&pBuff[ulLen], "%-24s ", pFunction);
        if (ulSubLen > 25)
        {
            ulLen += 25;
        }
        else
        {
            ulLen += ulSubLen;
        }
        ulLen += sprintf(&pBuff[ulLen], "[%4d] : ", ulLine);
    }
    
    va_start(xAP, pFormat);
    ulLen += vsnprintf(&pBuff[ulLen], sizeof(pBuff) - ulLen,  pFormat, xAP );
    va_end(xAP);
   
    if (pBuff[ulLen-1] == '\n')
    {
        pBuff[ulLen - 1] = '\r';
        pBuff[ulLen++] = '\n';
        pBuff[ulLen] = '\0';
    }
    
    S2w_Printf(pBuff);
}

void    FTW_DBG_moduleTrace(uint_32 ulModule, char *pFormat, ... )
{
    if (_ulTraceModules & ulModule)
    {
        static  uint_32 ulOutputLine = 0;
        va_list     xAP;
        uint_32     ulLen = 0, ulSubLen;
        static char pBuff[2048];
        
        ulLen = sprintf(pBuff,"[%4d] ", ++ulOutputLine);
        
        va_start(xAP, pFormat);
        ulLen += vsnprintf(&pBuff[ulLen], sizeof(pBuff) - ulLen,  pFormat, xAP );
        va_end(xAP);
       
        if (pBuff[ulLen-1] == '\n')
        {
            pBuff[ulLen - 1] = '\r';
            pBuff[ulLen++] = '\n';
            pBuff[ulLen] = '\0';
        }
        
        S2w_Printf(pBuff);
    }
}

void    FTW_DBG_moduleTraceOn(uint_32 ulModule, uint_32 bEnable)
{
    if (bEnable)
    {
        _ulTraceModules |= ulModule;
    }
    else
    {
        _ulTraceModules &= ~ulModule;
    }
}
