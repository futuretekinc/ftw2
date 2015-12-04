#include "ftw_battery.h"

/******************************************************************************
  * File Inclusions
  *****************************************************************************/

#include "gsn_includes.h"

//#include "config\app_stat_config.h"
#include "hal/s2w_types.h"
#include "main/app_main_ctx.h"
#include "hal/s2w.h"

#include "app_rtc_mem.h"
#include "app_events.h"


/**
 ******************************************************************************
 * @file s2w_app_batt_chk.c
 * @brief GSN Application Battery check routines.
 *      This file contains the application specific Battery check implimentation.
******************************************************************************/

/**
 ******************************************************************************
 * @defgroup GsnAppBattCheck
 *    This group contains the application specific battery check implimenation.
******************************************************************************/
/******************************************************************************
  *  Private Definitions
  *
******************************************************************************/
static VOID FTW_BAT_CHECK_indicationCB(VOID* ctx,GSN_SYS_CTL_BATT_CHK_IND_T *battChkInd);


#define  APP_BATT_MAX_VALS_STORED   	4

/* max change limit between consecutive readings. 0.2V*/
#define APP_BATT_CHK_MAX_CHNG_LIMIT     200 

extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;


/******************************************************************************
  *  Public Functions
  *
******************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Handling the battery check start operation.
 *    This function handle the battery check start operation.
 *    This function initialize the battery check module and registers the
 *    call back function for indication and condition check
 * @param data - IN  Battery check frequency
 * @retval FTW_SUCCESS.
******************************************************************************/
FTW_RET FTW_BAT_CHECK_start(UINT32 data)
{ 
	GSN_STATUS status;
	GSN_SYS_CTL_BATT_CHK_REQ_PARAM_T battChkReqParam;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();


	battChkReqParam.repeatNumTx = data;
	pAppRtcLtchInfo->battchkinfo.chkFreq = data;

    /*register with WLAN Interface */
	status = GsnSysCtl_BatteryChkStart(&s2wappMainTaskCtxt->sysCtlCtx,&battChkReqParam,
							   FTW_BAT_CHECK_indicationCB,NULL);	 
    if(GSN_SUCCESS == status)
		return FTW_RET_OK;
	else
		return FTW_RET_ERROR;
}


/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Handling the battery check stop operation.
 *    This function handle the battery check stop operation.
 *    This function modify the call back function registers with battery check
 *    module to NULL so that the battery check will not happen.
 * @retval FTW_SUCCESS.
******************************************************************************/
FTW_RET FTW_BAT_CHECK_stop(VOID)
{
	GSN_STATUS status;
	status = GsnSysCtl_BatteryChkStop(&s2wappMainTaskCtxt->sysCtlCtx);
	
	if(GSN_SUCCESS == status)
		  return FTW_RET_OK;
	  else
		  return FTW_RET_ERROR;
}


/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Handling the battery check set param.
 *    This function handle the battery check param set operation.
 *    This function modify the battery check frequeny stored in RTC memory.
 * @param data - IN  Battery check frequency
 * @retval FTW_SUCCESS.
******************************************************************************/
FTW_RET FTW_BAT_CHECK_set(UINT32 data)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    pAppRtcLtchInfo->battchkinfo.chkFreq = data ;
    
    return FTW_RET_OK;

}

/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Handling the battery check set param.
 *    This function handle the battery check param set operation.
 *    This function modify the battery check frequeny stored in RTC memory.
 * @param data - IN  Battery check frequency
 * @retval FTW_SUCCESS.
******************************************************************************/
FTW_RET FTW_BAT_CHECK_levelSet(UINT32 warningLvl, UINT8 warningFreq, UINT32 stdByLvl)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();

    pAppRtcLtchInfo->battchkinfo.warningLvl = warningLvl ;
    pAppRtcLtchInfo->battchkinfo.warngFreq = warningFreq;
    pAppRtcLtchInfo->battchkinfo.stdByLvl = stdByLvl;
    
    return FTW_RET_OK;

}

/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Get the latest battery value stored in RTC memory.
 *    This function getting called from application to get the latest battery
 *    Value stored in RTC memory.
 * @param val   - IN pointer to user memory to which the battery value is getting
 *                   copied.
 * @retval FTW_SUCCESS or FTW_FAILURE.
******************************************************************************/
FTW_RET FTW_BAT_CHECK_valueGet(UINT16* val)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	*val= pAppRtcLtchInfo->battchkinfo.latestVal;
	return FTW_RET_OK;
}

/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Handling the battery check param get.
 *    This function handle the battery check param get operation.
 *    This function return the battery check freqency to the caller.
 * @param data - IN  Address to which the Batt chk param store.
 * @retval FTW_SUCCESS.
******************************************************************************/
FTW_RET FTW_BAT_CHECK_param(UINT32* data)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    *data = pAppRtcLtchInfo->battchkinfo.chkFreq;
    
    return FTW_RET_OK;

}


/**
 ******************************************************************************
 * @ingroup GsnAppBattCheck
 * @brief Battery check condition.
 *      This function handle the battery check condition. It decides whether to
 *      trigger battery check or not, depending on the number of packet sent
 *      and freq of battery read parameters
 * @param ctx    - IN pointer to the context.
 * @param ctrl   - IN control.
 * @param pData  - IN user data.
 * @retval VOID.
******************************************************************************/
VOID 
FTW_BAT_CHECK_indicationCB(VOID* ctx,GSN_SYS_CTL_BATT_CHK_IND_T *battChkInd)
{
	UINT32 message;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();

	pAppRtcLtchInfo->battchkinfo.latestVal = battChkInd->batteryMeasure;
	if((0 != pAppRtcLtchInfo->battchkinfo.warningLvl) || (0 != pAppRtcLtchInfo->battchkinfo.stdByLvl))
  	{
		message = APP_NOTIFICATION_BATT_INDICATION;
		(s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
	}	
}
/**
 *****************************************************************************
 * @ingroup GsnBattCheck
 * @brief Sends a low battery trap.
 *    This function sends a low battery trap.
 * @param BatteryValue
 * @retval VOID.
 * @note
 *    This function is called to sends a low battery trap.
 *****************************************************************************/
PRIVATE VOID
AppS2wHal_BattChkDeadLevelProcess()
{
	ULONG64 duration;

    S2w_Printf("\r\nBattery Dead\r\n");
	
    /* delay to make sure that betty dead message totally goes out*/
    GsnTaskSleep(100);
	/* request for long stand by */
	duration = GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(APP_BATT_CHK_LONG_STANDBY_WAKEUP_TIME);	
	GsnPwrMgmt_EnterStby(duration);	
}

PRIVATE UINT16
AppS2wHal_BattChkAvgValueGet(VOID)
{
    UINT8 count;
    UINT32 avgBattValue;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();	
    APP_BATTCHK_INFO_T *pBattChkInfo = &pAppRtcLtchInfo->battchkinfo;
	
    /*
    	    Find out the Average batt Value of the previous   APP_BATT_CHK_MVNG_AVG_SIZE    battery reading

    	*/
    avgBattValue = 0;	
    for( count =0; count < APP_BATT_MAX_VALS_STORED; count++ )
    {
        if ( 0 == pBattChkInfo->prevReadings[ count ] )
        {
            break;
        }
        avgBattValue += pBattChkInfo->prevReadings[ count ];
    }
    if( 0 != count )
    {
        avgBattValue = avgBattValue/count;
    }
    return avgBattValue;
}


/**
 ******************************************************************************
 * @ingroup AppBattCheck
 * @brief Take action based on the  the Battery Value received.
 *    This function is called when application gets battery value indication
 *    from Wlan. This function takes appropriate decision depending on the
 *    battery vale received.
 * @param pAppBattChk - IN pointer to battery chk context.
 ******************************************************************************/
VOID FTW_BAT_CHECK_process(VOID)
{

	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    APP_BATTCHK_INFO_T *pBattChkInfo = &pAppRtcLtchInfo->battchkinfo;
    UINT32 avgBattValue = 0;
    UINT32 currentBattVal;
    UINT32 maxChangeLimit = APP_BATT_CHK_MAX_CHNG_LIMIT;
    currentBattVal = pBattChkInfo->latestVal;
	
    if ( currentBattVal > 3700 ) /**< Value cannot be more than 3.7Volt */
    {
        goto AppBattChk_ProcessExit;
    }

    /*Find out the Average batt Value of the previous  battery reading*/
    avgBattValue = AppS2wHal_BattChkAvgValueGet();
    if ( 0 != avgBattValue )
    {
        /*
        		If the new reading is a sudden dip or a sudden rise  apply correction
		        before storing in to rtc
	       */
        if ( currentBattVal > ( avgBattValue + maxChangeLimit ))
        {
            currentBattVal = ( avgBattValue + maxChangeLimit);
        }
        else if( currentBattVal < ( avgBattValue - maxChangeLimit ))
        {
            currentBattVal = ( avgBattValue - maxChangeLimit);
        }
    }
	
    /* Store the current Batt Value in the RTC Array*/
    pBattChkInfo->prevReadings[pBattChkInfo->indx] = currentBattVal;
    pBattChkInfo->indx++;
	
    if (APP_BATT_MAX_VALS_STORED == pBattChkInfo->indx)
    {
        pBattChkInfo->indx = 0;
    }

    /*Find out the Average batt Value */
    avgBattValue = AppS2wHal_BattChkAvgValueGet();

	    switch(pBattChkInfo->battState)
    {
        case APP_BATT_CHK_BATT_STATE_DEAD:
            /* 
            			battery is bellow stand by level during previous measurements,
			       go to long standby*/
            AppS2wHal_BattChkDeadLevelProcess();
            break;
        case APP_BATT_CHK_BATT_STATE_GOOD:
            if(avgBattValue < pBattChkInfo->stdByLvl)
            {
                pBattChkInfo->battState = APP_BATT_CHK_BATT_STATE_DEAD;
                AppS2wHal_BattChkDeadLevelProcess();
                break;/* this really will not be executed */
            }
            else if (avgBattValue < pBattChkInfo->warningLvl)
            {
                pBattChkInfo->battState = APP_BATT_CHK_BATT_STATE_LOW;
                /* intentional follow through. break is in else condition */
            }
            else
            {
                /* Battery level is OK. no action taken */
                break;
            }
        case APP_BATT_CHK_BATT_STATE_LOW:
            /*Increment the Battery val warning counter*/
            pBattChkInfo->warngsCnt++;
            if(pBattChkInfo->lowestAvgVal > avgBattValue)
                    pBattChkInfo->lowestAvgVal = avgBattValue;

            if (avgBattValue < pBattChkInfo->stdByLvl)
            {
                pBattChkInfo->battState = APP_BATT_CHK_BATT_STATE_DEAD;
                AppS2wHal_BattChkDeadLevelProcess();

            }
            else if (avgBattValue < pBattChkInfo->warningLvl)
            {

                if ( pBattChkInfo->warngsCnt >=  pBattChkInfo->warngFreq )
                {
                    /*Reset the Battery check counter*/
                    pBattChkInfo->warngsCnt = 0;
                    /* indicate to host about low battery */
                    S2w_Printf("\r\nBattery Low\r\n");
                }
            }
            else
            {
                /* dip bellow warning level was temporary and now it is in
                GOOD condition */
                pBattChkInfo->battState = APP_BATT_CHK_BATT_STATE_GOOD;
                pBattChkInfo->warngsCnt = 0;
            }

            break;

        default:
            break;
    }


AppBattChk_ProcessExit:		
    return;
}


#ifdef IOT_APP_ENABLE

void AppS2wHal_IotBattChkInit(UINT32 data)
{

    BOOL sarAdcPresent;
    GSN_BATTCHK_USES_OBJS_T battChkUsesObjs;
    GSN_BATTCHK_USES_INFO_T battChkUsesInfo;

    appRtcMemData.battchkinfo.latestVal =0;
    appRtcMemData.battchkinfo.chkFreq = data ;

#ifdef GS1010
    {
        sarAdcPresent = FALSE;
    }
#else
    {
        sarAdcPresent = TRUE;
    }
#endif

    battChkUsesObjs.pWifCtx = &appMainTaskCtxt->wifCtx;
    battChkUsesObjs.pWlanSys = &appMainTaskCtxt->wlanSys;

    battChkUsesInfo.notifyCb = AppS2wHal_BattChkIndication;
    battChkUsesInfo.pNotifyCtx = &appMainTaskCtxt->battChk;
    battChkUsesInfo.sarAdcPresent = sarAdcPresent;

    GsnBattChk_Init(&appMainTaskCtxt->battChk.gsnBattChk, NULL,
                    &battChkUsesObjs, NULL, &battChkUsesInfo);


}



UINT32  
AppS2wHal_IotBattChkValueGet(void)
{
   UINT32 battValue=0;

   GsnBattChk_LevelGet(&appMainTaskCtxt->battChk.gsnBattChk,&battValue);

   return battValue;
}


/**
 ******************************************************************************
 * @ingroup app_iot
 * @brief Register the battery check/temp monitor with S2w application .
 *    This function assign the IOT context
 * @param notifier - IN Application notification function.
 * @param context  - IN Application context.
 * @retval VOID.
 * Note:
 *          GsnDieTemp_Get() requires this initialisation
******************************************************************************/
PUBLIC VOID
AppIot_Register( GSN_NOTIFICATION_FUNC_T notifier,  VOID *context)
{
 appMainTaskCtxt = context;
}

PUBLIC GSN_STATUS
AppIot_DieTemp_Get(INT32 *pTemp)
{
   GSN_STATUS returnValue=GSN_SUCCESS;
   GSN_WIF_SYS_BOOT_REASON_T bootReason=GSN_WIF_SYS_BOOT_FIRST_BOOT;

returnValue= GsnDieTemp_Get( &appMainTaskCtxt->wifCtx, pTemp,
                             bootReason );

return returnValue;

}

#endif

