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
* $RCSfile: gsn_pwm.h,v $
*
* Description : This file contains private functions of pwm driver.
*******************************************************************************/


#ifndef _GSN_PWM_H_
#define _GSN_PWM_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*******************************************************************************
* File Inclusion
*******************************************************************************/
#include <stdint.h>
#include "drivers/reg/gsn_reg_pwm_spec.h"
#include "drivers/reg/gsn_reg_pwm_op.h"

  
  
  
typedef VOID ( *PWMCALLBACK_FP ) ( VOID*, UINT32 );  


/**
 *******************************************************************************
 * @file gsn_pwm.h
 * @brief GSN PWM public header.
 *    This file contains the public APIs and structures of PWM module.
 ******************************************************************************/
	
	
	
/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/
	
	

/**
 *******************************************************************************
 * @defgroup GsnPwm GSN PWM Device Driver
 * @brief This group contains public definitions for the PWM Device Driver.
 *
 * @details The Pulse Width Modulation (PWM) outputs a signal structured as a series
 * of repeated frames of duration FramePeriod. During each frame, the PWM output signal 
 * is ON (high in normal polarity) for pTimeON and OFF (low in normal polarity) 
 * for the remainder of the frame. <br>
 * 
 * The PWM function blocks can be used in two modes of operations, independent 
 * PWM mode and Synchronized PWM mode.  In the Independent PWM mode, each PWM 
 * output module selects a clock frequency (11 or 44 MHz), and optionally divides 
 * that frequency by a prescale value.   The clock signal 
 * resulting from these choices becomes the time unit for FramePeriod and pTimeON.  
 * In the Synchronized PWM mode, a single timer drives all outputs, with a selectable 
 * phase delay between outputs 0 and 1, and between outputs 1 and 2.
 *
 *
 ******************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

/*******************************************************************************
* public macro
*******************************************************************************/

#define GSN_PWM_MAX_CHANNEL                     3
#define GSN_PWM_NOT_INITIALIZED                 0x0
#define GSN_PWM_CHNL0                           0
#define GSN_PWM_CHNL1                           1
#define GSN_PWM_CHNL2                           2

/*******************************************************************************
* Public Type Definitions
*******************************************************************************/


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm number select.
 *     
 ******************************************************************************/

typedef enum 
{
    GSN_PWM_1   = 0,
    GSN_PWM_2   = 1,
    GSN_PWM_3   = 2,
    GSN_PWM_SYNC = 3
} GSN_PWM_NO;

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm clock source select.
 *     
 ******************************************************************************/

typedef enum GSN_PWM_CLOCKSEL
{
    GSN_PWM_CLOCKSEL_BUSCLOCK,
    GSN_PWM_CLOCKSEL_PRESCALECLOCK
} GSN_PWM_CLOCKSEL;
/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief system clock source select.
 *     
 ******************************************************************************/

typedef enum GSN_PWM_SYSTEM_CLOCKSEL
{
    GSN_PWM_CLK_RC,
    GSN_PWM_CLK_XTAL,
    GSN_PWM_CLK_PLL,
    GSN_PWM_CLK_LP,
}   GSN_PWM_SYSTEM_CLOCKSEL;

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm clock frequency.
 *     
 ******************************************************************************/

typedef enum GSN_PWM_CLOCKFREQ
{
    GSN_PWM_CLOCKFREQ_11MHZ,
    GSN_PWM_CLOCKFREQ_44MHZ
} GSN_PWM_CLOCKFREQ;

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm polarity.
 *     
 ******************************************************************************/

typedef enum GSN_PWM_POLARITY
{
    GSN_PWM_POLARITY_NORMAL,
    GSN_PWM_POLARITY_INVERTED
} GSN_PWM_POLARITY;

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm mode.
 *     
 ******************************************************************************/

typedef enum GSN_PMW_MODE
{
    GSN_PWM_MODE_INDIVIDUAl,
    GSN_PWM_MODE_SYNCHRONIZED
}GSN_PMW_MODE;


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm pattern structure.
 *     
 ******************************************************************************/

typedef struct GSN_PWM_PATTERN
{
    UINT16   timeON;              //<on period in terms of clock cycles                         
    UINT16   framePeriod;         //<frame period in terms of clock cycles 
} GSN_PWM_PATTERN_T;

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm config structure.
 *     
 ******************************************************************************/

typedef struct PWM_INFO
{
    UINT8      channelId;
    UINT32     flagInfinity;  //<set if the number of recurrences is infinity
    UINT32     recurrences;   //<number of pattern repetitions 
    PWMCALLBACK_FP   callback;      //<function to be called when last repetition is done
    VOID             *callBackCtx;
} GSN_PWM_INFO_T;

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm config structure.
 *     
 ******************************************************************************/

typedef struct GSN_PWM_CONFIG
{
    UINT16 phaseDelay01;                 //<delay between pwm0 and pwm1
    UINT16 phaseDelay12;                 //<delay between pwm1 and pwm2
    GSN_PWM_CLOCKSEL eClockSelect;              //<bus clock or prescaled clock
    GSN_PWM_CLOCKFREQ eClockFrequency;              //<clock freq 11 MHz or 44 MHz
    GSN_PWM_POLARITY ePolarity[GSN_PWM_MAX_CHANNEL];//<polarity of each channel
    GSN_PWM_SYSTEM_CLOCKSEL eSystemClkSelect; // pwm clock selection
    UINT8 prescaleValue;                  //<clock prescale value
}GSN_PWM_CONFIG_T;


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief pwm structure.
 *     
 ******************************************************************************/

typedef struct GSN_PWM
{
    GSN_PWM_INFO_T pwmInfo;          ///<pwm information structure
    GSN_PWM_PATTERN_T pwmPattern;    ///<pwm pattern structure
} GSN_PWM_T;


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief handle to pwm module.
 *     
 ******************************************************************************/

typedef struct GSN_PWM_HANDLE
{
    UINT32 *pReg;
    GSN_PMW_MODE pwmMode;
    UINT32 pwmInitialized;
    GSN_PWM_T pwm[GSN_PWM_MAX_CHANNEL];
}GSN_PWM_HANDLE_T;


/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief Open Pwm module.
 *
 *    This function opens pwm module.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pPwmConfig - IN pointer to pwm configuration.
 * @retval GSN_SUCCESS Operation successful.
 * @retval PWM_STATUS_STARTED pwm already started.
 * @note
 *      This function opens the pwm module and installs the irq (interrupt request) handler. 
 ******************************************************************************/

PUBLIC GSN_STATUS 
GsnPwm_Open( GSN_PWM_HANDLE_T *pPwmHandle,GSN_PWM_CONFIG_T *pPwmConfig );


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief start Pwm module.
 *
 *    This function starts the pwm module.
 * @param pPwmHandle - IN pointer to pwm handle. 
 * @param pwmNumber - IN channel number to be started.
 * @param pPwmConfig - IN pointer to configuration structure.
 * @param pPwmPattern - IN pointer to pattern structure.
 * @param pPwmInfo - IN pointer to pwm information structure.
 * @retval GSN_SUCCESS Operation successful.
 * @note
 *      This function starts the pwm module in Individual or syncronous mode.
 ******************************************************************************/

PUBLIC GSN_STATUS 
GsnPwm_Start( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_NO pwmNumber, 
    GSN_PWM_CONFIG_T *pPwmConfig, GSN_PWM_PATTERN_T *pPwmPattern, 
    GSN_PWM_INFO_T *pPwmInfo );

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief Stops Pwm module.
 *
 *    This function Stops pwm output.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pwmNumber - IN channel number to be stopped.
 * @retval GSN_SUCCESS Operation successful.
 * @note
 ******************************************************************************/

PUBLIC GSN_STATUS 
GsnPwm_Stop( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_NO pwmNumber );

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief Closes Pwm module.
 *
 *    This function Closes the pwm module.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @retval GSN_SUCCESS Operation successful.
 * @note 
 *      This functions closes the pwm module and uninstalls the irq handler. 
 ******************************************************************************/

PUBLIC GSN_STATUS 
GsnPwm_Close( GSN_PWM_HANDLE_T *pPwmHandle);

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief updates Pwm output pattern.
 *
 *    This function updates the pwm output pattern.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pwmNumber - IN channel number to be updated. 
 * @param pPwmPattern - IN pointer to pattern structure.
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 *  
 ******************************************************************************/

PUBLIC GSN_STATUS 
GsnPwm_PatternUpdate( GSN_PWM_HANDLE_T *pPwmHandle, 
    GSN_PWM_NO pwmNumber, GSN_PWM_PATTERN_T *pPwmPattern );



/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief clock frequency get.
 *
 *    This function gets the clock frequency being used.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @retval PWM_CLOCKFREQ
 * @note
 *      
 ******************************************************************************/

PUBLIC INLINE GSN_PWM_CLOCKFREQ 
GsnPwm_ClockFreqGet( GSN_PWM_HANDLE_T *pPwmHandle )
{
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );
    return ( GSN_PWM_CLOCKFREQ ) WORD_VALUE_N( PWM_CLKFREQ, pwmCr );
}

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief clock frequency set.
 *
 *    This function sets the clock frequency.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param eClockFreq - IN clock frequency to be set.
 * @note
 *      
 ******************************************************************************/


PUBLIC INLINE void 
GsnPwm_ClockFreqSet( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_CLOCKFREQ eClockFreq )
{
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    pwmCr &= ~WORD_MASK( PWM_CLKFREQ );
    pwmCr |= WORD_VALUE_DN( PWM_CLKFREQ, eClockFreq );
    PWM_PWMCR_SET( pPwmHandle->pReg, pwmCr );
}


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief clock prescale value get.
 *
 *    This function gets the prescale value being used.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @retval returns first 6 bits of PWMCPS register
 * @note
 *      
 ******************************************************************************/

PUBLIC INLINE UINT8 
GsnPwm_PrescaleValueGet( GSN_PWM_HANDLE_T *pPwmHandle )
{
    return PWM_PWMCPS_GET( pPwmHandle->pReg );
}


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief clock prescale value set.
 *
 *    This function sets the prescale value.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param prescaleValue - IN 6 bit prescale value (2 to 63)  .
 * @note
 *      
 ******************************************************************************/

PUBLIC INLINE void 
GsnPwm_PrescaleValueSet( GSN_PWM_HANDLE_T *pPwmHandle, UINT8 prescaleValue)
{
    PWM_PWMCPS_SET( pPwmHandle->pReg, (prescaleValue - 1));
}


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief individual clock get.
 *
 *    This function gets the clock source of a particular pwm output.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pwmNumber - IN channel number.
 * @retval GSN_PWM_CLOCKSEL.
 * @note
 *      
 ******************************************************************************/


PUBLIC INLINE GSN_PWM_CLOCKSEL 
GsnPwm_IndividualClockSelectGet( GSN_PWM_HANDLE_T *pPwmHandle, 
    GSN_PWM_NO pwmNumber )
{
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    return ( GSN_PWM_CLOCKSEL ) WORD_VALUE_N( PWM_CLS0, pwmCr >>
        ( 4 * pwmNumber  ) );
}

/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief individual clock select.
 *
 *    This function sets the clock source of a particular pwm output.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pwmNumber - IN channel number.
 * @param eClockSelect - IN bus clock or prescaled clock.
 * @note
 *      
 ******************************************************************************/

PUBLIC INLINE void 
GsnPwm_IndividualClockSelectSet( GSN_PWM_HANDLE_T *pPwmHandle, 
    GSN_PWM_NO pwmNumber, GSN_PWM_CLOCKSEL eClockSelect)
{
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    pwmCr &= ~( WORD_MASK( PWM_CLS0 ) << ( 4 * pwmNumber ) );
    pwmCr |= WORD_VALUE_DN( PWM_CLS0, eClockSelect ) <<
    ( 4 * pwmNumber );
    PWM_PWMCR_SET( pPwmHandle->pReg, pwmCr );

}



/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief individual polarity get.
 *
 *    This function gets the polarity of a particular pwm output.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pwmNumber - IN channel number.
 * @retval GSN_PWM_POLARITY.
 * @note
 *      
 ******************************************************************************/


PUBLIC INLINE GSN_PWM_POLARITY 
GsnPwm_IndividualPolarityGet( GSN_PWM_HANDLE_T *pPwmHandle, 
    GSN_PWM_NO pwmNumber )
{
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    return(GSN_PWM_POLARITY) WORD_VALUE_N( PWM_POL0, pwmCr >>
    (4 * pwmNumber  ) );
}


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief individual polarity set.
 *
 *    This function sets the polarity of a particular pwm output.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pwmNumber - IN channel number.
 * @param ePolarity - IN polarity.
 * @note
 *      
 ******************************************************************************/

PUBLIC INLINE void 
GsnPwm_IndividualPolaritySet( GSN_PWM_HANDLE_T *pPwmHandle, 
    GSN_PWM_NO pwmNumber, GSN_PWM_POLARITY ePolarity )
{
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    pwmCr &= ~( WORD_MASK( PWM_POL0 ) << ( 4 * pwmNumber ) );
    pwmCr |= WORD_VALUE_DN( PWM_POL0, ePolarity ) << ( 4 * pwmNumber );
    PWM_PWMCR_SET( pPwmHandle->pReg, pwmCr );
}


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief synchronized phase delay get.
 *
 *    This function gets the phase delay between pwm0-pwm1 and pwm1-pwm2.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param pPhase01 - OUT phase delay between pwm0 and pwm1
 * @param pPhase12 - OUT phase delay between pwm1 and pwm2
 * @note
 *      
 ******************************************************************************/

PUBLIC INLINE void 
GsnPwm_SynchronizedPhaseDelayGet( GSN_PWM_HANDLE_T *pPwmHandle, 
    UINT16 *pPhase01, UINT16 *pPhase12)
{
    UINT32 pwmDcr = PWM_PWMDCR_GET( pPwmHandle->pReg );

    *pPhase01 = WORD_VALUE_N( PWM_PDS0, pwmDcr );
    *pPhase12 = WORD_VALUE_N( PWM_PDS1, pwmDcr );
}



/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief synchronized phase delay set.
 *
 *    This function sets the phase delay between pwm0-pwm1 and pwm1-pwm2.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param phase01 - IN phase delay between pwm0 and pwm1
 * @param phase12 - IN phase delay between pwm1 and pwm2
 * @note
 *      
 ******************************************************************************/


PUBLIC INLINE void 
GsnPwm_SynchronizedPhaseDelaySet( GSN_PWM_HANDLE_T *pPwmHandle, 
    UINT16 phase01, UINT16 phase12)
{
    PWM_PWMDCR_SET( pPwmHandle->pReg, WORD_VALUE_DN( PWM_PDS0, phase01 ) |
    WORD_VALUE_DN( PWM_PDS1, phase12 ) );
}


/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief synchronized clock get.
 *
 *    This function gets the clock source.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @retval GSN_PWM_CLOCKSEL_BUSCLOCK
 * @retval GSN_PWM_CLOCKSEL_PRESCALECLOCK
 * @note
 *      
 ******************************************************************************/


PUBLIC INLINE GSN_PWM_CLOCKSEL 
GsnPwm_SynchronizedClockSelectGet( GSN_PWM_HANDLE_T *pPwmHandle )
{   
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    return ( GSN_PWM_CLOCKSEL ) WORD_VALUE_N( PWM_SCLS, pwmCr );
}



/**
 *******************************************************************************
 * @ingroup GsnPwm
 * @brief synchronized clock select.
 *
 *    This function selects the clock source for sync mode.
 * @param pPwmHandle - IN pointer to pwm handle.
 * @param eClockSelect - IN bus clock or prescaled clock.
 * @note
 *      
 ******************************************************************************/


PUBLIC INLINE void 
GsnPwm_SynchronizedClockSelectSet( GSN_PWM_HANDLE_T *pPwmHandle, 
    GSN_PWM_CLOCKSEL eClockSelect )
{
    /* read pwm control register */
    UINT32 pwmCr = PWM_PWMCR_GET( pPwmHandle->pReg );

    pwmCr &= ~WORD_MASK( PWM_SCLS );
    pwmCr |= WORD_VALUE_DN( PWM_SCLS, eClockSelect );
    PWM_PWMCR_SET( pPwmHandle->pReg, pwmCr );
}



PUBLIC VOID
__GsnPwm_Isr();



#ifdef  __cplusplus
    }
#endif

#endif /* _GSN_PWM_H_ */

