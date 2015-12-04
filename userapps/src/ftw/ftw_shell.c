#include "ftw_includes.h"
#include "gsn_includes.h"
#include "drivers/uart/gsn_uart.h"
#include "s2w.h"
#include "app_resource_config.h"
#include "ftw_shell.h"
#include "ftw_uart.h"

VOID FTW_SHELL_task( UINT32 ulParam );
static GSN_OSAL_THREAD_TCB_T    _xTCB;
static UINT8    _pStack[2048];

void    FTW_SHELL_init(void)
{
    FTW_UART_CONFIG xConfig;
#if 0
    FTW_UART_getConfig(FTW_UART0, &xConfig);

    if (FTW_UART_open(FTW_UART0, &xConfig) != FTW_RET_OK)
    {/*ERROR: UART port open failed */
        FTW_ASSERT(0);
    }
#endif
    //AppS2wHal_PrintBanner();
    
    GsnOsal_ThreadCreate(FTW_SHELL_task, 
                         NULL,
                         &_xTCB,
                         "shell",
                         APP_CFG_CONSOLE_THREAD_PRIORITY,
                         _pStack,
                         sizeof(_pStack),
                         GSN_OSAL_THREAD_INITIAL_READY);
}

VOID FTW_SHELL_task( UINT32 address )
{
    while (1)
    {
        S2w_Printf("Hello\n");
        tx_thread_sleep(10);
    }
}

