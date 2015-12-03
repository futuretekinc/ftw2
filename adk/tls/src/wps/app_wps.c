/*******************************************************************************
 *
 *               COPYRIGHT (c) 2009-2010 GainSpan Corporation

 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by GainSpan
 * Corporation or its licensors.  Title to the Material remains
 * with GainSpan Corporation or its suppliers and licensors.
 *
 * The Material is protected by worldwide copyright and trade secret
 * laws and treaty provisions. No part of the Material may be used,
 * copied, reproduced, modified, published, uploaded, posted, transmitted,
 * distributed, or disclosed in any way except in accordance with the
 * applicable license agreement.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel, except in accordance with the
 * applicable license agreement.
 *
 * Unless otherwise agreed by GainSpan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by GainSpan
 * or GainSpan's suppliers or licensors in any way.
 *
 * $RCSfile: app_wps.c,v $
 *
 * Description : ADK WPS file
 *******************************************************************************/
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "app_net_svcs_priv.h"
#include "wps/app_wps.h"
 
#ifdef ADK_PROV_WPS_ENABLE
#define GPIO_10_WPS_10  	10
#define LOAD_BUTTON_INTERVAL	200
/* used to determine length of button push */
PRIVATE UINT8   flags    = TRUE;
PRIVATE GSN_SYSTEM_TIME_T h2lTime  = 0;

/*
 * Callback function for WPS handling
 */
void AppWps_CbFn(char* mode, char* pin)
{
    UINT8 i, wpsPin[GSN_WDD_SEC_WPS_PIN_LEN];
    UINT8* p = &wpsPin[0];
    APP_MAIN_CTX_T * appctx = globalAppCtxPtr;
    UINT32 msg = APP_EVENT_STA_WPS_INITIATE;


    memset((INT8 *)&appctx->wpsapSsid, 0, sizeof(globalAppCtxPtr->wpsapSsid));
    if (!strcmp(mode, "pbc"))
    {
    	//AppDbg_Printf("AppWps_CbFn pbc mode\r\n");
    	memset(appctx->wpsParams.pin,0x00,GSN_WDD_SEC_WPS_PIN_LEN);
    	appctx->wpsParams.type = APP_WPS_TYPE_PB;
    }
    else if (!strcmp(mode, "pin"))
    {
    	appctx->wpsParams.type = APP_WPS_TYPE_PIN;
        if (GSN_WDD_SEC_WPS_PIN_LEN != strlen((const char*) pin))
        {
            return;
        }
        for (i = 0; i < GSN_WDD_SEC_WPS_PIN_LEN; i++)
        {
            if (*(pin + i) < '0' || *(pin + i) > '9')
            {
                return;
            }
            *(p+i)= *(pin+i); /* convert to integer */
        }

        memcpy(appctx->wpsParams.pin, p, GSN_WDD_SEC_WPS_PIN_LEN);
    }
    /* Notify APP */
    AppMainCtx_TaskNotify(msg,0);
}

void App_WpsLoadButtonCB(UINT8 gpioNumber, void *pCtx)
{
	ULONG64 diffTime=0, l2hTime=0;
	//AppDbg_Printf("\r\nA\r\n");
	if(flags)
	{
		/* got H2L:  re-register for low to high */
		flags = FALSE;
		h2lTime = GsnSoftTmr_CurrentSystemTime();
		GsnGpio_NEIntEnable((1 << GPIO_10_WPS_10));
		
	}
	else
	{
		/* got L2H: re-register for high to low  */
		flags = TRUE;
		GsnGpio_PEIntEnable((1 << GPIO_10_WPS_10));
		l2hTime = GsnSoftTmr_CurrentSystemTime();
		diffTime = (ULONG64)((l2hTime - h2lTime)/(TIMER_INTERRUPT_1_MS));
		/* WPS push button should be handled based on the push duration*/
		if (diffTime >= LOAD_BUTTON_INTERVAL)
		{
			AppWps_CbFn("pbc","");// push button
		}

		/* reset time interval variables */
		diffTime = 0;
		l2hTime  = 0;
		h2lTime  = 0;
	}
}

void App_WpsGPIOInit(APP_MAIN_CTX_T *pAppCtx)
{
	//AppDbg_Printf("App_WpsGPIOInit\r\n");
	GsnGpio_NEIntClear((1 << GPIO_10_WPS_10));
	GsnGpio_PEIntClear((1 << GPIO_10_WPS_10));
	GsnGpio_IntCbRegister(GPIO_10_WPS_10, App_WpsLoadButtonCB,  (void *)pAppCtx);
	GsnGpio_PEIntEnable((1 << GPIO_10_WPS_10));
	//GsnGpio_NEIntEnable((1 << GPIO_10_WPS_10));
	//AppDbg_Printf("App_WpsGPIOInit - \r\n");
}
#endif
