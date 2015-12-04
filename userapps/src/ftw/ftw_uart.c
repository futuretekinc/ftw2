#include "ftw_includes.h"
#include "ftw_uart.h"

static FTW_UART pxUART[1];

FTW_RET FTW_UART_open(FTW_UART_ID xID, FTW_UART_CONFIG_PTR pxConfig)
{
    FTW_UART_CONFIG     xConfig;
    GSN_UART_CONFIG_T   xGSNConfig;
    
    GsnOsal_SemCreate  (&pxUART[xID].xWriteSemaphore,1);
    
    FTW_UART_getConfig(FTW_UART0, &xConfig);
    
    switch (pxConfig->xBaudRate)
    {
    case FTW_UART_BAUDRATE_9K6:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_9K6;
        break;
    case FTW_UART_BAUDRATE_19K2:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_19K2;
        break;
    case FTW_UART_BAUDRATE_38K4:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_38K4;
        break;
    case FTW_UART_BAUDRATE_57K6:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_57K6;
        break;
    case FTW_UART_BAUDRATE_115K2:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_115K2;
        break;
    case FTW_UART_BAUDRATE_230K4:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_230K4;
        break;
    case FTW_UART_BAUDRATE_460K8:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_460K8;
        break;
    case FTW_UART_BAUDRATE_921K6:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_921K6;
        break;
    default:
        xGSNConfig.eBaudRate = GSN_UART_BAUDRATE_9K6;
    }

    switch(pxConfig->xDataBits)
    {
    case FTW_UART_DATABITS_5:
        xGSNConfig.eCharFormat = GSN_UART_CHARFORMAT_5;
        break;
    case FTW_UART_DATABITS_6:
        xGSNConfig.eCharFormat = GSN_UART_CHARFORMAT_6;
        break;
    case FTW_UART_DATABITS_7:
        xGSNConfig.eCharFormat = GSN_UART_CHARFORMAT_7;
        break;
    case FTW_UART_DATABITS_8:
        xGSNConfig.eCharFormat = GSN_UART_CHARFORMAT_8;
        break;
    default:
        xGSNConfig.eCharFormat = GSN_UART_CHARFORMAT_8;
    }
    
    switch(pxConfig->xStopBits)
    {
    case FTW_UART_STOPBITS_1:
        xGSNConfig.eStopBits = GSN_UART_STOPBITS_1;
        break;
    case FTW_UART_STOPBITS_2:
        xGSNConfig.eStopBits = GSN_UART_STOPBITS_2;
        break;
    default:
        xGSNConfig.eStopBits = GSN_UART_STOPBITS_1;
    }

    switch(pxConfig->xParityBits)
    {
    case FTW_UART_PARITYBIT_ODD:
        xGSNConfig.eParityBits = GSN_UART_PARITYBIT_ODD;
        break;
    case FTW_UART_PARITYBIT_EVEN:
        xGSNConfig.eParityBits = GSN_UART_PARITYBIT_EVEN;
        break;
    case FTW_UART_PARITYBIT_MARK:
        xGSNConfig.eParityBits = GSN_UART_PARITYBIT_MARK;
        break;
    case FTW_UART_PARITYBIT_SPACE:
        xGSNConfig.eParityBits = GSN_UART_PARITYBIT_SPACE;
        break;
    case FTW_UART_PARITYBIT_NONE:
        xGSNConfig.eParityBits = GSN_UART_PARITYBIT_NONE;
        break;
    default:
        xGSNConfig.eParityBits = GSN_UART_PARITYBIT_NONE;
        break;
    }

    if (pxConfig->bHWFlowCtrl)
    {
        xGSNConfig.HwFlowSupport= GSN_UART_HW_SUPPORT;
    }
    else
    {
        xGSNConfig.HwFlowSupport= GSN_UART_HW_NO_SUPPORT;
    }

    if (pxConfig->bSWFlowCtrl)
    {
        xGSNConfig.swFlowSupport= GSN_UART_SWFLOW_SUPPORT;
    }
    else
    {
        xGSNConfig.swFlowSupport= GSN_UART_SWFLOW_NO_SUPPORT;
    }
    
    xGSNConfig.uartBuffer   = pxUART[xID].pBuffer;
    xGSNConfig.uartBuffSize = sizeof(pxUART[xID].pBuffer);
    xGSNConfig.dmaSupport   = GSN_UART_DMA_NO_SUPPORT;
	xGSNConfig.uartClk      = GSN_UART_CLK_XTAL;
    
	GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AUART0_RXD);
    GsnIoMux_Sel(1, GSN_IOMUX_GPIO_1_AUART0_TXD);
    GsnIoMux_PullDownDisable(1);		// uart tx
    GsnIoMux_PullDownDisable(0);
    
    /* workaround for gpio35 since mux is configured in boot rom as pull down--fixed in C1 bootrom
     */
    GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_AGPIO_35);
    GsnIoMux_PullDownEnable(35);
    
    if(pxConfig->bHWFlowCtrl)
    {
        GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AUART0_CTS_N);
        GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AUART0_RTS_N);
        GsnIoMux_PullDownDisable(25);		// uart rts. These together consume 125uA
        //GsnIoMux_PullDownDisable(24);      // CTS
    }

	if (GsnUart_Open( GSN_UART_0, &pxUART[xID].hGSNUart, &xGSNConfig ) != GSN_UART_STATUS_OK)
    {
        return  FTW_RET_ERROR;
    }

    if (pxConfig->bSWFlowCtrl)
    {
        FTW_UART_setSWFlowCtrl(FTW_UART0, s2wCurrent.serialPortConf.conf.uart.softflow);
    }
    
    return  FTW_RET_OK;
}

FTW_RET FTW_UART_setConfig(FTW_UART_ID xID, FTW_UART_CONFIG_PTR pxConfig)
{
    UINT32  ulBaudRate,ulPrevBaudRate, ulDataBits, ulStopBits;
    GSN_UART_PARITYBIT_T    xParityBit;
    UINT32  ulValue;
    
    switch (pxConfig->xBaudRate)
    {
    case FTW_UART_BAUDRATE_9K6:
        ulBaudRate = GSN_UART_BAUDRATE_9K6;
        break;
    case FTW_UART_BAUDRATE_19K2:
        ulBaudRate = GSN_UART_BAUDRATE_19K2;
        break;
    case FTW_UART_BAUDRATE_38K4:
        ulBaudRate = GSN_UART_BAUDRATE_38K4;
        break;
    case FTW_UART_BAUDRATE_57K6:
        ulBaudRate = GSN_UART_BAUDRATE_57K6;
        break;
    case FTW_UART_BAUDRATE_115K2:
        ulBaudRate = GSN_UART_BAUDRATE_115K2;
        break;
    case FTW_UART_BAUDRATE_230K4:
        ulBaudRate = GSN_UART_BAUDRATE_230K4;
        break;
    case FTW_UART_BAUDRATE_460K8:
        ulBaudRate = GSN_UART_BAUDRATE_460K8;
        break;
    case FTW_UART_BAUDRATE_921K6:
        ulBaudRate = GSN_UART_BAUDRATE_921K6;
        break;
    default:
        return FTW_FAILURE;
    }
    
    ulPrevBaudRate = GsnUart_BaudRateGet(&pxUART[xID].hGSNUart);
    if(ulBaudRate != ulPrevBaudRate)
    {
        AppS2wProcess_StatusNotify(FTW_SUCCESS, 0);
        GsnTaskSleep(10);
    }
    
    switch(pxConfig->xDataBits)
    {
    case    FTW_UART_DATABITS_5:
        ulDataBits = GSN_UART_CHARFORMAT_5;
        break;
    case    FTW_UART_DATABITS_6:
        ulDataBits = GSN_UART_CHARFORMAT_6;
        break;
    case    FTW_UART_DATABITS_7:
        ulDataBits = GSN_UART_CHARFORMAT_7;
        break;
    case    FTW_UART_DATABITS_8:
        ulDataBits = GSN_UART_CHARFORMAT_8;
        break;
    default:
        return  FTW_RET_ERROR;
    }
    
    switch(pxConfig->xStopBits)
    {
    case    FTW_UART_STOPBITS_1:
        ulStopBits = GSN_UART_STOPBITS_1;
        break;
    case    FTW_UART_STOPBITS_2:
        ulStopBits = GSN_UART_STOPBITS_2;
        break;    
    default:
        return  FTW_RET_ERROR;
    }
    
    switch (pxConfig->xParityBits)
    {
    case FTW_UART_PARITYBIT_NONE:
        xParityBit = GSN_UART_PARITYBIT_NONE;
        break;
    case FTW_UART_PARITYBIT_ODD:
        xParityBit = GSN_UART_PARITYBIT_ODD;
        break;
    case FTW_UART_PARITYBIT_EVEN:
        xParityBit = GSN_UART_PARITYBIT_EVEN;
        break;
    default:
        return FTW_RET_ERROR;
    }
    
    GsnUart_HwFlowSupportSet(&pxUART[xID].hGSNUart, (pxConfig->bHWFlowCtrl)?GSN_UART_HW_NO_SUPPORT:GSN_UART_HW_SUPPORT);
    GsnUart_BaudRateSet(&pxUART[xID].hGSNUart, ulBaudRate);
    GsnUart_CharFormatSet(&pxUART[xID].hGSNUart, (GSN_UART_CHARFORMAT_T) ulDataBits);
    GsnUart_StopBitsSet(&pxUART[xID].hGSNUart, (GSN_UART_STOPBITS_T) ulStopBits);
    GsnUart_ParityBitsSet(&pxUART[xID].hGSNUart, xParityBit);
    
    return FTW_RET_OK;
}

FTW_RET FTW_UART_close(FTW_UART_ID xID)
{
    GsnUart_Close(&pxUART[xID].hGSNUart);
    
    return  FTW_RET_OK;
}

FTW_RET FTW_UART_getConfig(FTW_UART_ID xID, FTW_UART_CONFIG_PTR pxConfig)
{
    FTW_UART_BAUDRATE   xBaudRate;
    FTW_UART_PARITYBIT  xParityBits;
    
    switch (s2wCurrent.serialPortConf.conf.uart.baudrate)
    {
    case 9600:
        xBaudRate = FTW_UART_BAUDRATE_9K6;
        break;
    case 19200:
        xBaudRate = FTW_UART_BAUDRATE_19K2;
        break;
    case 38400:
        xBaudRate = FTW_UART_BAUDRATE_38K4;
        break;
    case 57600:
        xBaudRate = FTW_UART_BAUDRATE_57K6;
        break;
    case 115200:
        xBaudRate = FTW_UART_BAUDRATE_115K2;
        break;
    case 230400:
        xBaudRate = FTW_UART_BAUDRATE_230K4;
        break;
    case 460800:
        xBaudRate = FTW_UART_BAUDRATE_460K8;
        break;
    case 921600:
        xBaudRate = FTW_UART_BAUDRATE_921K6;
        break;
    default:
        xBaudRate = FTW_UART_BAUDRATE_9K6;
    }
    pxConfig->xBaudRate = xBaudRate;
    /* set the bits per char of uart
    */
    pxConfig->xDataBits = (FTW_UART_DATABITS) s2wCurrent.serialPortConf.conf.uart.bits;    
    pxConfig->xStopBits = (FTW_UART_STOPBITS)s2wCurrent.serialPortConf.conf.uart.stop;
    
    
    switch (s2wCurrent.serialPortConf.conf.uart.parity)
    {
    case FTW_UARTCONF_PARITY_NONE:
        xParityBits = FTW_UART_PARITYBIT_NONE;
        break;
    case FTW_UARTCONF_PARITY_ODD:
        xParityBits = FTW_UART_PARITYBIT_ODD;
        break;
    case FTW_UARTCONF_PARITY_EVEN:
        xParityBits = FTW_UART_PARITYBIT_EVEN;
        break;
    default:
        xParityBits = FTW_UART_PARITYBIT_NONE;
    }
    pxConfig->xParityBits = xParityBits;
    
    pxConfig->bHWFlowCtrl = s2wCurrent.serialPortConf.conf.uart.hardflow;
    pxConfig->bSWFlowCtrl = s2wCurrent.serialPortConf.conf.uart.softflow;
    
    return  FTW_RET_OK;
}

FTW_RET FTW_UART_setSWFlowCtrl(FTW_UART_ID xID, BOOL bEnable)
{
    s2wCurrent.serialPortConf.conf.uart.softflow = !!bEnable;

    GsnUart_SwFlowSupportSet(&pxUART[xID].hGSNUart, (GSN_UART_SWFLOW_T)bEnable);
    
    return  FTW_RET_OK;
}

FTW_RET FTW_UART_setHWFlowCtrl(FTW_UART_ID xID, BOOL bEnable)
{
    UINT8   bOldFlow;
    
    bOldFlow = s2wCurrent.serialPortConf.conf.uart.hardflow;
    s2wCurrent.serialPortConf.conf.uart.hardflow = bEnable;

    if(s2wCurrent.serialPortConf.conf.uart.hardflow)
    {
        GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AUART0_CTS_N);
        GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AUART0_RTS_N);
        GsnIoMux_PullDownDisable(25);		// uart rts. These together consume 125uA
        //GsnIoMux_PullDownDisable(24);      // CTS
    }
    else
    {
        if(bOldFlow == GSN_UART_HW_SUPPORT)
        {
            GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AGPIO_24);
            GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AGPIO_25);
            GsnIoMux_PullDownEnable(25);
        }
    }

    GsnUart_HwFlowSupportSet(&pxUART[xID].hGSNUart, bEnable);

    return  FTW_RET_OK;
}
    
BOOL FTW_UART_txStatusGet(void)
{
    return GsnUart_TxStatusGet(&pxUART[0].hGSNUart);
}

VOID FTW_UART_putc(FTW_UART_ID xID, UINT8 ch)
{
    GsnOsal_SemAcquire ( &pxUART[xID].xWriteSemaphore, GSN_OSAL_WAIT_FOREVER );
    
    GsnUart_Write(&pxUART[xID].hGSNUart, &ch, 1, NULL,NULL);
    
    GsnOsal_SemRelease(&pxUART[xID].xWriteSemaphore);
}

VOID FTW_UART_put(FTW_UART_ID xID, const VOID *buf, UINT32 len)
{
    
    GsnOsal_SemAcquire ( &pxUART[xID].xWriteSemaphore, GSN_OSAL_WAIT_FOREVER );
    
    GsnUart_Write(&pxUART[xID].hGSNUart, (UINT8 *)buf, len, NULL,NULL);
    
    GsnOsal_SemRelease(&pxUART[xID].xWriteSemaphore);
}

UINT8 FTW_UART_getc(FTW_UART_ID xID, UINT8 *ch)
{
    /* Don't need a semaphore since this is called from only one thread
    */
    return GsnUart_Read(&pxUART[xID].hGSNUart, ch, 1, 1, NULL,NULL);
}

VOID FTW_UART_get(FTW_UART_ID xID, UINT8 *ch, UINT16 dataLen)
{
    UINT32 dataLeft = 0;
    
    while(dataLen)
    {
        GsnUart_Read(&pxUART[xID].hGSNUart, ch, (dataLeft = (dataLen >=500?500:dataLen)), 1, NULL,NULL);
        ch += dataLeft;
        dataLen -= dataLeft;
    }
}