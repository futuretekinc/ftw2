
#ifndef _GSN_PWR_MGMT_H_

#define _GSN_PWR_MGMT_H_

#include "gsn_includes.h"
#include "core/reg/gsn_reg_rtc_spec.h"
#include "core/reg/gsn_reg_rtc_op.h"
#include "core/reg/gsn_reg_clkctl_spec.h"
#include "core/reg/gsn_reg_clkctl_op.h"

#define GSN_PWR_MGMT_CM3_SLEEP_DEEP_EN() SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk
#define GSN_PWR_MGMT_CM3_SLEEP_DEEP_DISABLE() SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk)
#define GSN_PWR_MGMT_CM3_DP_SLEEP_STATUS_GET() SCB->SCR & SCB_SCR_SLEEPDEEP_Msk

typedef enum GSN_DP_ACTIVITY_BIT_MAP_T
{
    GSN_DP_ACTIVITY_HI_IN_PROCESS      = 1,
}GSN_DP_ACTIVITY_BIT_MAP_T;

typedef struct GSN_PWR_MGMT_CTX
{
    UINT32 stbyReqCount;
	UINT32 dpSlpReqCount;
	UINT32 dpSlpActvtBitMap;
}GSN_PWR_MGMT_CTX_T;


/**
 *****************************************************************************
 * @ingroup GsnPwrMgmt
 * @brief Cortex M3 sleep deep enable.
 *
 * @return GSN_STATUS_T
 *			GSN_SUCCESS -- CM3 deep sleep enabled.
 *			GSN_FAILURE -- CM3 sleep enabled.
 *****************************************************************************/

GSN_STATUS_T 
GsnPwrMgmt_Cm3SleepDeepEn( );

VOID
GsnPwrMgmt_EnterStby(ULONG64 duration);

extern GSN_PWR_MGMT_CTX_T *gPwrCtx;

/**
 ******************************************************************************
 * 
 *****************************************************************************/

INLINE VOID
GsnPwrMgmt_DpSlpDisable( GSN_PWR_MGMT_CTX_T *pPwrCtx )
{

}

INLINE VOID
GsnPwrMgmt_StdbyEnable( GSN_PWR_MGMT_CTX_T *pPwrCtx )
{
	TX_INTERRUPT_SAVE_AREA

	TX_DISABLE 

	if(pPwrCtx->stbyReqCount)
	{
	    pPwrCtx->stbyReqCount--;
    }
	TX_RESTORE
}

/**
 ******************************************************************************
 * 
 *****************************************************************************/

INLINE VOID
GsnPwrMgmt_StdbyDisable( GSN_PWR_MGMT_CTX_T *pPwrCtx )
{
    
	TX_INTERRUPT_SAVE_AREA
	
	TX_DISABLE 
	pPwrCtx->stbyReqCount++;
	TX_RESTORE
}

INLINE UINT32 
GsnPwrMgmt_StbyReady( GSN_PWR_MGMT_CTX_T *pPwrCtx )
{    
    if(pPwrCtx->stbyReqCount == 0)
    {
        return TRUE;
    }
    else
    {   
        return FALSE;
    }
}

VOID GsnPwrMgmt_Init(GSN_PWR_MGMT_CTX_T *pPwrCtx);
VOID
GsnPwrMgmt_DpSlpActivitySet( GSN_DP_ACTIVITY_BIT_MAP_T dpSlpActivity );

VOID
GsnPwrMgmt_DpSlpActivityClr( GSN_DP_ACTIVITY_BIT_MAP_T dpSlpActivity );
UINT32 
GsnPwrMgmt_DpSlpActivityGet( VOID );

#endif
