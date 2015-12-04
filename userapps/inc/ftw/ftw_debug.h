#ifndef _FTW_DEBUG_H_
#define _FTW_DEBUG_H_


#define FTW_DBG_MODULE_NET  0x00000001
#define FTW_DBG_MODULE_MQTT 0x00000002

#ifndef FTW_DEBUG
    #define FTW_TRACE(...)              FTW_DBG_Trace(NULL, 0, __VA_ARGS__)
    #define FTW_PRINT_ERROR(x)    

    #define FTW_MODULE_TRACE(x, ...)    FTW_DBG_moduleTrace((x), __VA_ARGS__)
    #define FTW_MODULE_TRACE_ON(x)      FTW_DBG_moduleTraceOn((x), TRUE)
#else
    #define FTW_TRACE(...)              FTW_DBG_Trace(__FUNCTION__, __LINE__, __VA_ARGS__)
    #define FTW_PRINT_ERROR(x)    

    #define FTW_MODULE_TRACE(x, ...)    FTW_DBG_moduleTrace((x), __VA_ARGS__)
    #define FTW_MODULE_TRACE_ON(x)      FTW_DBG_moduleTraceOn((x), TRUE)
#endif


void    FTW_DBG_Trace(char const *pFunction, uint_32 ulLine, char *pFormat, ... );
void    FTW_DBG_moduleTrace(uint_32 ulModule, char *pFormat, ... );
void    FTW_DBG_moduleTraceOn(uint_32 ulModule, uint_32 bEnable);
#endif