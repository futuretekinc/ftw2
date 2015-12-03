/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_cloud_updater.c
*
*  Created on: 16-May-2013
*      Author: Dhanya Lakshmi
*/

#include "gsn_cloud_updater.h"
#include "gsn_cloud_api.h"
#include "gsn_cloud_exosite.h"


BOOL continueRunning = FALSE;

UINT32 updateInterval;

PRIVATE GSN_OSAL_THREAD_TCB_T httpClientTask;
PRIVATE GSN_OSAL_SEM_T cloudStopWaitSem;

UINT8* threadStack = NULL;

VOID Gsn_CloudRunLoop()
{
    GSN_STATUS retVal;
    printf("Gsn_CloudRunLoop + \r\n");

    // Activate the device in the exosite cloud.
    // ON successfull activation , A CIK is returned in"X-Exosite_CIK" header
    // which is used for further transactions
    // If device is already activated, lookup the CIK in the flash memory
    retVal = Gsn_CloudActivateDevice();
    if(retVal == GSN_FAILURE)
    {
        // case where the device is already acivated once and the device is re-flashed.
        // re try activation in a loop
        GsnTaskSleep(updateInterval);
        return;
    }
    while(continueRunning)
    {
        if(continueRunning == FALSE)
        return;

        if ((Gsn_cloudPostUdpates()) == GSN_FAILURE)
        {
            printf("Cloud update failed\r\n");
        }
        GsnCloud_GetConfig(updateInterval);

     }
     printf("Gsn_CloudRunLoop - \r\n");
}


VOID Gsn_CloudSend(GSN_OSAL_SEM_T *cloudStopWaitSem)
{
	while(1)
	{

		while(continueRunning)
		{
			Gsn_CloudRunLoop();
			if(!continueRunning)
				break;
		}
		printf("Gsn_CloudSend before sem release\r\n");

		GsnOsal_SemRelease( cloudStopWaitSem);
		GsnOsal_ThreadSuspend(&httpClientTask);
		//GsnOsal_SemAcquire( &cloudSuspendSem, GSN_OSAL_WAIT_FOREVER );
		printf("Gsn_CloudSend -\r\n");
	}
}
// note stop returns immediately,

VOID Gsn_CloudUpdaterStop()
{
	// set the cloud_updater.continueRunning flag to false
	// and wait until the updater has stopped
	printf("stopping exosite cloud\r\n");
	if(continueRunning == TRUE)
	{
		continueRunning = FALSE;
		GsnOsal_SemAcquire( &cloudStopWaitSem, GSN_OSAL_WAIT_FOREVER );
		printf("Gsn_CloudUpdaterStop after sem release\r\n");

	}

	printf("after stopping exosite cloud\r\n");

}

VOID Gsn_CloudUpdaterResume()
{
	printf("Gsn_CloudUpdaterResume +\r\n");
	if(continueRunning == FALSE)
	{
		continueRunning = TRUE;
		//GsnOsal_SemRelease(& cloudSuspendSem);
		GsnOsal_ThreadResume(&httpClientTask);
	}
	printf("Gsn_CloudUpdaterResume -\r\n");

}
GSN_STATUS_T Gsn_CloudUpdaterStart( GSN_APP_CLOUD_CONTEXT_T* appContext,BOOL separateThread)
{
	
	GSN_STATUS_T retVal;
    UINT16 stackSize = STACK_5K;
    UINT16 allocatesStackSize;

	continueRunning = TRUE;
	updateInterval = appContext->updateInterval;

    printf("Gsn_CloudUpdaterStart +\n");

    Gsn_CloudApiInit( appContext);
    GsnOsal_SemCreate ( &cloudStopWaitSem, 0 );
    //GsnOsal_SemCreate ( &cloudSuspendSem, 0 );
    if(separateThread == TRUE)
    {
    if ((retVal = Gsn_CloudStackAlloc(&threadStack, STACK_5K,&allocatesStackSize)) == GSN_FAILURE)
    {
        printf("[GsnCloudUpdaterStart] Unable to allocate stack\r\n");
        return GSN_FAILURE;
    }
    else
    {
    	// create a new thread and start posting data in
    	// the new thread context
    	retVal = GsnOsal_ThreadCreate((GSN_OSAL_THREAD_ENTRY_T)Gsn_CloudSend,
    			    (VOID *)&cloudStopWaitSem, /* This is the thread parameter */
                    &httpClientTask,
                    "Gsn_CloudSend",
                    CLOUD_UPDATER_THREAD_PRIORITY,
                    threadStack,
                    stackSize ,
                    GSN_OSAL_THREAD_INITIAL_READY);

    	if(retVal != GSN_SUCCESS)
    	{
        	printf("[Gsn_CloudUpdaterStart] Thread creation Failed\r\n");
        	if (threadStack)
        	{
            	gsn_free(threadStack);
        	}
    	}
    }
    }
    else
    {
    // case : tls low power, post in same thread and return
        if(GSN_BOOT_REASON_GET() == GSN_WIF_SYS_BOOT_FIRST_BOOT)
        {
            AppDbg_Printf("Gsn_CloudUpdaterStart before activate\n");
            retVal = Gsn_CloudActivateDevice();
        }  
        AppDbg_Printf("Gsn_CloudUpdaterStart before post\n");
        Gsn_cloudPostUdpates();
    }
    printf("Gsn_CloudUpdaterStart -\r\n");
    return GSN_SUCCESS;
}



