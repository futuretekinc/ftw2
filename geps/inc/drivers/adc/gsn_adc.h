/******************************************************************************
 *
 *               COPYRIGHT (c) 2012-2013 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_adc.h,v $
 *
 * Description:
 *      This file contains public functions definitions for ADC Driver
 * 
 ******************************************************************************
 */

/**
******************************************************************************
*  @file gsn_adc.h
*  @brief Public Header Containing ADC Driver Functions.
*
*****************************************************************************/


#ifndef _GSNADC_H_
#define _GSNADC_H_

#ifdef  __cplusplus
extern "C" {
#endif


/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "core/osal/gsn_osal_threadx.h"
#include "drivers/clk_ctl/gsn_clk_ctl.h"


/**
 *****************************************************************************
 * @file gsn_adc.h
 * @brief GSN ADC Public API Implementation.
 *    This file contains the public APIs and structures of ADC module.
 ****************************************************************************/


/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/



/**
 *****************************************************************************
 * @defgroup GsnAdc GSN ADC API
 *    This group contains public definitions and functions providing access
 *    to the GS2000's internal ADC.
 ****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/



/*****************************************************************************
 * Definitions
 ****************************************************************************/

#define NCO_EN 1

#define ENABLE 1
#define DISABLE 0
/**
 ****************************************************************************
 * @ingroup GsnAdc
 * @brief Initial FIFO Threshold Set to 4. FIFO threshold is
 *    dynamically changed internally depending on the number of samples.
 *
 * @note FIFO size for ADC is 12 (it also includes the channel information ).
 *
 ****************************************************************************/
#define GSN_ADC_FIFOTHR_VALUE   4
#define GSN_ADC_CHANNELS 8

/*****************************************************************************
* Type Definitions
****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Callback Function.
 *    This callback function accepts two arguments,
 *    - argument 1 is status
 *    - argument 2 is context pointer
 *
 * @param data    -IN ADC status
 * @param context -IN callback context pointer
 * @see  GSN_ADC_CALLBACK_FUNC_T.
 *
 ****************************************************************************/
typedef VOID ( *GSN_ADC_CALLBACK_FUNC_T )( UINT32 status, VOID *context );


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Power Save Mode Type.
 *    This enum defines ADC power save mode type
 *
 * @see  GSN_ADC_PDMODE_T.
 ****************************************************************************/
typedef enum GSN_ADC_PDPOLARITY
{
    GSN_ADC_PDPOLARITY_L,               /**< Adc power down is low   */
    GSN_ADC_PDPOLARITY_H                 /**< Adc power down is high    */
} GSN_ADC_PDPOLARITY_T;



/**
 ****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Reference Voltage Type.
 *    This enum defines ADC reference voltage
 *
 * @see  GSN_ADC_REF_VOLTAGE_T.
 ****************************************************************************/
typedef enum GSN_ADC_REF_VOLTAGE
{
    GSN_ADC_REF_INTERNAL,      /**< Adc internal voltage reference */
    GSN_ADC_REF_EXTERNAL   	/**< Adc external voltage reference  */
} GSN_ADC_REF_VOLTAGE_T;



/**
 ****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Clock Selection Type.
 *    This enum defines ADC Clock Selection
 *
 * @see  GSN_ADC_CLK_SEL_T.
 ****************************************************************************/
typedef enum GSN_ADC_CLK_SEL
{
    GSN_ADC_CLK_SEL_RC,
    GSN_ADC_CLK_SEL_XTAL,
    GSN_ADC_CLK_SEL_PLL,
    GSN_ADC_CLK_SEL_LP
} GSN_ADC_CLK_SEL_T;


/**
 ****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Source Type.
 *    This enum defines ADC Analog Source Selection
 *
 * @see  GSN_ADC_SOURCE_T.
 ****************************************************************************/
typedef enum GSN_ADC_SOURCE
{
	GSN_ADC_SOURCE_CH_0 = 0x0,
    GSN_ADC_SOURCE_CH_1 = 0x1,
    GSN_ADC_SOURCE_CH_2 = 0x2,
    GSN_ADC_SOURCE_CH_3 = 0x3,
    GSN_ADC_SOURCE_CH_4 = 0x4,
    GSN_ADC_SOURCE_CH_5 = 0x5,
    GSN_ADC_SOURCE_CH_6 = 0x6,
    GSN_ADC_SOURCE_CH_7 = 0x7,
    GSN_ADC_SOURCE_CH_END = 0xF,

	GSN_ADC_SINGLE_SOURCE_CH_0 = 0xF0,
    GSN_ADC_SINGLE_SOURCE_CH_1 = 0xF1,
    GSN_ADC_SINGLE_SOURCE_CH_2 = 0xF2,
    GSN_ADC_SINGLE_SOURCE_CH_3 = 0xF3,
    GSN_ADC_SINGLE_SOURCE_CH_4 = 0xF4,
    GSN_ADC_SINGLE_SOURCE_CH_5 = 0xF5,
    GSN_ADC_SINGLE_SOURCE_CH_6 = 0xF6,
    GSN_ADC_SINGLE_SOURCE_CH_7 = 0xF7

} GSN_ADC_SOURCE_T;
/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Types.
 *    This enum defines ADC return values
 * @see  GSN_ADC_STATUS_T.
 *****************************************************************************/

typedef enum GSN_ADCN_STATUS
{
    GSN_ADCN_STATUS_OK,
    GSN_ADCN_STATUS_BUSY,
    GSN_ADCN_STATUS_ERROR,
    GSN_ADCN_LOCK_UNAVAILABLE,
    GSN_ADCN_FIFO_OVERFLOW,
    GSN_ADCN_FIFO_EMPTY
} GSN_ADCN_STATUS_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Limit Status Type.
 *    This enum defines ADC limit status
 *
 * @see  GSN_ADC_LIMIT_STATUS_T.
 ****************************************************************************/
 /*exact values of fifo limits not known */
typedef enum GSN_ADCN_LIMIT_STATUS
{
    GSN_ADCN_LIMIT1UNDERFLOW,
    GSN_ADCN_LIMIT1OVERFLOW,
    GSN_ADCN_LIMIT2UNDERFLOW,
    GSN_ADCN_LIMIT2OVERFLOW,
    GSN_ADCN_LIMIT3UNDERFLOW,
    GSN_ADCN_LIMIT3OVERFLOW

}GSN_ADCN_LIMIT_STATUS_T;



/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Read Operation Mode Type.
 *    This enum defines an ADC Read Operating Mode
 *
 * @see  GSN_ADC_READ_MODE_T.
 ****************************************************************************/
typedef enum GSN_ADC_READ_MODE
{
    GSN_ADC_MODE_CONTINUOUS,             /**<continous mode */
    GSN_ADC_MODE_SINGLE ,                /**< Single mode  */
    GSN_ADC_MODE_PERIODIC,              /**< Periodic mode  */
} GSN_ADC_READ_MODE_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC SUP1P8 Mode Type.
 *    This enum defines an ADC SUP1P8 Mode
 *
 * @see  GSN_ADC_SUP1P8_T.
 ****************************************************************************/
typedef enum GSN_ADC_SUP1P8
{
    GSN_ADC_AVDD_3Vrange,			       /**< sup1p8 2.5/3.3V range */
    GSN_ADC_AVDD_2Vrange                    /**< sup1p8 1.8V range */
} GSN_ADC_SUP1P8_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC LVL Type.
 *    This enum defines an ADC LVL
 *
 * @see  GSN_ADC_LVL_T.
 ****************************************************************************/
typedef enum GSN_ADC_LVL
{
    GSN_ADC_LVL_DISABLE,
    GSN_ADC_LVL_ENABLE             /**< DVDD reaches 1.2V */
} GSN_ADC_LVL_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC DVDD Type.
 *    This enum defines an ADC external source core supply is used or not
 *
 * @see  GSN_ADC_ENDVDD_T.
 ****************************************************************************/
typedef enum GSN_ADC_ENDVDD
{
	GSN_ADC_DVDD_DISABLE,
      GSN_ADC_DVDD_ENABLE        /* dvdd enabled when external core supply 
                                        is provided */
} GSN_ADC_ENDVDD_T;

/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC PERIODIC COUNTER Type.
 *    This enum defines an ADC PERIODIC COUNTER to enable or not
 *
 * @see  GSN_ADC_PCOUNTER_T.
 ****************************************************************************/
typedef enum GSN_ADC_PCOUNTER
{
	GSN_ADC_PCOUNTER_DISABLE,
    GSN_ADC_PCOUNTER_ENABLE        /* Periodic counter can be enabled 
                                      when periodic mode is enabled */
} GSN_ADC_PCOUNTER_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC EN100K Type.
 *    This enum defines an ADC Enable low frequency mode -> This bit
 *    is used to reduce the power-up time to
 *    15 cycles for Fs<100KHz when internal
 *    reference is being used.
 *
 * @see  GSN_ADC_EN100Khz_T.
 ****************************************************************************/
typedef enum GSN_ADC_EN100Khz
{
    GSN_ADC_EN100K_DISABLE,
    GSN_ADC_EN100K_ENABLE
} GSN_ADC_EN100Khz_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC TRIM Type.
 *    This enum defines Enable trim of Internal Reference.
 *    When EN_TRIM='1', REF_TRIM<3:0>
 *	can be used to trim the reference.
 *
 * @see  GSN_ADC_TRIM_T.
 ****************************************************************************/
typedef enum GSN_ADC_TRIM
{
    GSN_ADC_TRIM_DISABLE,
    GSN_ADC_TRIM_ENABLE
} GSN_ADC_TRIM_T;

/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Types.
 *    This enum defines ADC THRESH select
 * @see  GSN_ADC_THRESHSET_T.
 *****************************************************************************/
typedef enum GSN_ADC_THRESHSELSET
{
	GSN_ADC_NO_THRESH_SEL,
	GSN_ADC_SET0_THRESH_SEL,
	GSN_ADC_SET1_THRESH_SEL,
	GSN_ADC_SET2_THRESH_SEL
}GSN_ADC_THRESHSELSET_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Types.
 *    This enum defines ADC THRESH select
 * @see  GSN_ADC_THRESHSET_T.
 *****************************************************************************/
typedef enum GSN_ADC_THRESHSET
{
	GSN_ADC_SET0_THRESH,
	GSN_ADC_SET1_THRESH,
	GSN_ADC_SET2_THRESH
}GSN_ADC_THRESHSET_T;

/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC  Structure.
 *    This Structure defines ADC thresholds .
 *
 * @see   GSN_ADC_TRESH0_T.
 ****************************************************************************/
typedef struct GSN_ADC_THRESH0
{
    UINT16 lower;
    UINT16 upper;
} GSN_ADC_TRESH0_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Start Polarity Type.
 *    This enum defines ADC start polarity type
 *
 * @see  GSN_ADC_PDMODE_T.
 ****************************************************************************/
typedef enum GSN_ADC_STARTPOLARITY
{
    GSN_ADC_STARTPOLARITY_L,             /**< Adc start polarity  is low   */
    GSN_ADC_STARTPOLARITY_H             /**< Adc start polarity is high    */
} GSN_ADC_STARTPOLARITY_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Configuration Structure.
 *    This structure defines ADC configuration parameters
 *
 *    refVoltage	- the reference voltage for ADC(internal or external)
 *    readMode 	- select the mode of operation
 *	ppCounter	- parameter for periodic measurement
 *	pdPolarity	- power down polarity
 *	sup1p8		- supply range indication
 *	enlvl			- enable level
 *	enDvdd		- enable core supply for ADC
 *	en100khz		- enable low frequency mode
 *	enTrim		- enable trim
 *	chnSel		- channel selection
 *	refVoltageTrim- Trim value to trim the reference voltage
 *	fifoThr		- FIFO threshold value
 *	startCycles	- value of Start cycles
 *	powerCycles	- value of PowerCycles
 *	samplePeriod	-  the clock period, for periodic operation(Periodic Timer Expiry Value)
 *	adcStep		- Step value
 *    clockSelect  - clock selection; refer to GSN_ADC_CLK_SEL_T
 *
 * @see  GSN_ADC_CONFIG_T.
 ****************************************************************************/
typedef struct GSN_ADC_CONFIG
{
    GSN_ADC_REF_VOLTAGE_T      refVoltage;		/*internel or external ref voltage select*/
    GSN_ADC_READ_MODE_T	readMode;		/*single,continous or periodic */
    GSN_ADC_PDPOLARITY_T	pdPolarity;
    GSN_ADC_SUP1P8_T		sup1p8;
    GSN_ADC_LVL_T		enlvl;
    GSN_ADC_ENDVDD_T      	enDvdd;
    GSN_ADC_EN100Khz_T     	en100kHz;
    GSN_ADC_TRIM_T        	enTrim;
    UINT16			refVoltageTrim;
    GSN_ADC_THRESHSELSET_T			threshselect;	/*select threshold set*/
    GSN_ADC_TRESH0_T		thresh0;        /*threshold set0 */
    GSN_ADC_TRESH0_T		thresh1;		/*threshold set1 */
    GSN_ADC_TRESH0_T		thresh2;		/*threshold set2 */
    UINT8			fifoThr;
    UINT8			startCycles;  /*Start cycles*/
    UINT8			powerCycles;  /*Power cycles*/
    UINT32	         	samplePeriod; /*Periodic counter value */
    GSN_ADC_CLK_SEL_T      	adcClk;      /*Clock for adc*/
    LONG64 			inputFreq;
    UINT32			samplingfreq;  /*Sampling frequency*/
   	GSN_ADC_STARTPOLARITY_T    startPolarity;
    UINT8                       singlePolling;

} GSN_ADC_CONFIG_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Read and Write Structure.
 *    This structure defines ADC read and DAC write data.
 *
 * @see  GSN_ADC_RW_ARGS_T.
 ****************************************************************************/
typedef struct GSN_ADC_RW_ARGS_T
{
    BUFFER32    buffer;                 /**< buffer holder  */
    VOID*       contextCB;              /**< context pointer for CallBack*/
    GSN_ADC_CALLBACK_FUNC_T funcCB;     /**< CallBack function */
} GSN_ADC_RW_ARGS_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Structure.
 *    This structure defines an ADC data pointer, base register and
 *    synchronous semaphore.
 *
 * @see  GSN_ADC_T.
 *****************************************************************************/
typedef struct GSN_ADC
{
    UINT32               pReg;         /**< adc base register             */
    GSN_ADC_RW_ARGS_T   adcRWArg;      /**< adc read         */
} GSN_ADC_T;


/**
 *****************************************************************************
 * @ingroup GsnAdc
 * @brief GSN ADC Handle Structure
 *   The handle contains configuration and other parameters for ADC operation
 *
 * @see  GSN_ADC_HANDLE_T.
 *****************************************************************************/
typedef struct GSN_ADC_HANDLE
{
    GSN_ADC_CONFIG_T	adcConfig;				/**adc  configuration parameter **/
    GSN_ADC_T          adc;					/**adc parameter **/
    UINT32              adcStatus;     		/**< adc status */
    UINT8               adcConMeasure;  /**< infinite periodic measurement */
}GSN_ADC_HANDLE_T;


/*****************************************************************************
 * Public variable
 ******************************************************************************/

/*****************************************************************************
 * Public Function
 ******************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Driver Lock Create
 *    This function creates the semaphore for ADC. Use the function
 *    GsnAdc_Lock to reserve the ADC and GsnAdc_Unlock to release the ADC
 *
 * @return none
 *****************************************************************************/
PUBLIC VOID
GsnADC_LockCreate( VOID );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Driver Lock.
 *    This function acquires the semaphore, and blocks access to the ADC by
 *    other tasks.
 *
 * @param waitForEver - IN  Boolean to indicate wait for ever
 *
 * @return none
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_Lock( BOOL waitForEver );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Driver Unlock.
 *    This function releases the semaphore acquired by the GsnAdc_Lock.
 *
 * @return none
 *****************************************************************************/
PUBLIC VOID
GsnADC_Unlock( VOID );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Driver Open.
 *    This function initializes the ADC with specified parameters.
 *
 * @param adcHandle     - IN pointer to handle.
 * @param adcConfig     - IN ADC configuration.
 *
 * @return GSN_SUCCESS   - Initialization successful.
 * @return GSN_FAILURE   - Initialization failed.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_Open( GSN_ADC_HANDLE_T *adcHandle, GSN_ADC_CONFIG_T  *adcConfig );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Driver Close.
 *    This function closes the ADC operation .
 *
 * @param adcHandle     - IN pointer to handle.
 *
 * @return GSN_SUCCESS   Close successful.
 * @return GSN_FAILURE   Close failed.
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_Close( GSN_ADC_HANDLE_T *adcHandle );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Supply power down polarity
 *      This function sets the Power down polarity (initially the Powerdown polarity is high )
 *
 * @param adcHandle             - IN pointer to handle.
 * @param pdPolarity               - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_PowerdownPolaritySet( GSN_ADC_HANDLE_T *adcHandle, 
                                GSN_ADC_PDPOLARITY_T pdPolarity );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Supply indication mode
 *      This function sets the Supply indication-D mode 
 *      (sup1p8 is 1 when I/O supply for ADC is in 1.8v range
 *							& 0 when it is in 2.5v/3.3v range ).
 *
 * @param adcHandle            - IN pointer to handle.
 * @param sup1p8               - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_SupplyIndicationSet( GSN_ADC_HANDLE_T *adcHandle, 
                               GSN_ADC_SUP1P8_T sup1p8 );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Enable DVDD mode(external supply used)
 *      This function sets the DVDD mode indicating external or internal 
 *       supply used(enable DVDD is 1 when external core supply is used
 *	 & 0 when internal core supply is used )
 *
 * @param adcHandle           - IN pointer to handle.
 * @param enDvdd               - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_ExternalSupplyEnable( GSN_ADC_HANDLE_T *adcHandle, 
                                GSN_ADC_ENDVDD_T enDvdd );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Enable or disable 100Khz freq mode
 *      This function sets or clears 100Khz freq mode.
 *	(enable low freq mode is 1 when Fs <100khz and 0 when Fs >100Khz)
 *
 * @param adcHandle           - IN pointer to handle.
 * @param en100kHz               - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_Enable100Khz( GSN_ADC_HANDLE_T *adcHandle, 
                       GSN_ADC_EN100Khz_T en100kHz );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC LVL mode
 *      This function sets or clears LVL mode(enlvl is 1 when DVDD i.e core 
 *        supply for ADC reaches 1.2v )                        
 *
 *
 * @param adcHandle           - IN pointer to handle.
 * @param enlvl                   - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_EnableLVL( GSN_ADC_HANDLE_T *adcHandle, GSN_ADC_LVL_T enlvl );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Internal Reference Trim mode
 *      This function sets or clears Internal Reference Trim mode
 *      (enTrim is 1 indicates Trim is enabled and the internal reference
 *	   voltage can be trimmed )
 *
 * @param aadcHandle           - IN pointer to handle.
 * @param enTrim                - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_EnableTrim( GSN_ADC_HANDLE_T *aadcHandle, GSN_ADC_TRIM_T enTrim );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Internal Reference Trim value
 *      This function sets Internal Reference Trim value(enTrim must be enabled and the value of trim must
 *			be increased in steps of 1 till the adc buffer shows a transition from 12'b111111111110
 * 																	  to 12'b111111111111)
 *
 * @param adcHandle           - IN pointer to handle.
 * @param trimValue           - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_TrimValueSet( GSN_ADC_HANDLE_T *adcHandle, UINT16 trimValue );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC channels
 *      This function sets or clears the channels
 *
 * @param adcHandle           - IN pointer to handle.
 * @param channelSel           - IN Channel selection
 *
 * @return GSN_SUCCESS   Close successful.
 * @return GSN_FAILURE   Close failed.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_ChannelSet( GSN_ADC_HANDLE_T *adcHandle, UINT32 channelSel );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC channels
 *      This function Gets the Channels selected
 *
 * @param adcHandle           - IN pointer to handle.
 *
 * @return UINT32(The value which gives the channels selected).
 *
 *****************************************************************************/
PUBLIC UINT32
GsnADC_ChannelGet( GSN_ADC_HANDLE_T *adcHandle );



/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Get Reference Voltage
 *    This function returns the configured reference voltage. The reference
 *    is either bandgap (1.2V) or 1.8V
 *
 * @param adcHandle           - IN pointer to handle.
 *
 * @return GSN_ADC_REF_VOLTAGE_T     Reference voltage.
 *
 *****************************************************************************/
PUBLIC GSN_ADC_REF_VOLTAGE_T
GsnADC_RefVoltageGet( GSN_ADC_HANDLE_T *adcHandle );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set Reference Voltage
 *     This function sets the reference voltage. 
 *      The reference is either external or internal(This function allows
 *      to select between internal & external reference )
 *
 * @param adcHandle            - IN pointer to handle.
 * @param refVoltage           - IN reference voltage
 *
 * @return GSN_ADC_STATUS_BUSY  If ADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 *
 ****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_RefVoltageSet( GSN_ADC_HANDLE_T *adcHandle,
                      GSN_ADC_REF_VOLTAGE_T  refVoltage );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Get the Periodic counter
 *    This function returns the periodic counter value . The unit for period is
 *    the ADC clock count
 *
 * @param adcHandle           - IN pointer to handle.
 *
 * @return UINT32     interval from ADCPER reg
 *
 ******************************************************************************/
PUBLIC UINT32
GsnADC_PeriodGet( GSN_ADC_HANDLE_T *adcHandle );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set the Interval Between Measurements
 *    This function allows setting the interval between two measurements.
 *    The unit for period is ADC clock count.
 *
 * @param adcHandle             - IN pointer to handle.
 * @param Period             - IN  periodic timer expiry value 
 *                              (The counter runs on the ADC clk)
 *
 * @return GSN_ADC_STATUS_BUSY  If ADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_PeriodSet( GSN_ADC_HANDLE_T *adcHandle, UINT32 Period );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set the number of start cycles.
 *    This function allows setting the number of start cycles .
 *
 * @param adcHandle             - IN pointer to handle.
 * @param startcycles               - IN cyclic interval between two measure
 *
 *
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_StartCycleSet( GSN_ADC_HANDLE_T *adcHandle, UINT8 startcycles );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set the number of power cycles.
 *    This function allows setting the number of power cycles .
 *
 * @param adcHandle             - IN pointer to handle.
 * @param powercycl               - IN cyclic interval between two measure
 *
 *
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_PowerCycleSet( GSN_ADC_HANDLE_T *adcHandle, UINT8 powercycl );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Read
 *    Starts read and returns the result in buffer. The ADC is shut
 *    down after the read is done.
 *
 * @param adcHandle           IN     pointer to handle.
 * @param adcmode             IN     adc mode
 * @param chnSel               IN     channel selection
 * @param adcRW               OUT    pointer to read write structure.
 * @param adcRefVoltage       IN     reference voltage
 *
 * @return GSN_ADC_STATUS_ERROR   - In case of buffer pointer is NULL or
 *                                  data size is zero or data pointer is NULL
 * @return GSN_ADC_STATUS_BUSY    - In case ADC is already in use.
 * @return GSN_SUCCESS            - In case operation is successful.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_Read( GSN_ADC_HANDLE_T *adcHandle,GSN_ADC_READ_MODE_T adcmode,
				 UINT32  chnSel,GSN_ADC_RW_ARGS_T *adcRW,
				 GSN_ADC_REF_VOLTAGE_T adcRefVoltage );



/*limits value and source information is not known */


#if 0
/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Get the Tresh of the ADC Source
 *    This function returns the configured Tresh values of the specified
 *    external source.
 *
 * @note  It is possible to measure the Tresh only for External ADC 1 and
 *    External ADC 2
 *
 * @param adcHandle            IN pointer to handle.
 * @param adcSource            IN adc source
 * @param adcTresh            OUT pointer to limits structure.
 *
 * @return GSN_ADC_STATUS_ERROR  - In case of invalid source.
 * @return GSN_SUCCESS           - In case Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_GsnAdc_TreshGet( GSN_ADC_HANDLE_T *adcHandle,
                  GSN_ADC_SOURCE_T adcSource,
                  GSN_ADC_TRESH_T  *adcLimits );



PUBLIC GSN_STATUS
GsnADC_ThresholdSelectSet(GSN_ADC_HANDLE_T *adcHandle,GSN_ADC_THRESHSELSET_T threshselect,UINT32 ch);

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set the Tresh of the ADC Source
 *     This function sets the Treshold values of the specified
 *     external source.

 *
 * @note The upper limits must be greater than lower limits
 *
 * @param adcHandle            IN pointer to handle.
 * @param adcSource            IN adc source
 * @param adcLimits            IN pointer to limits structure.
 *
 * @return GSN_ADC_STATUS_ERROR  - In case of invalid source or
 *                                 if upper limit <= lower limit
 * @return GSN_ADC_STATUS_BUSY   - In case ADC is already in use
 * @return GSN_SUCCESS           - In case Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_TreshSet( GSN_ADC_HANDLE_T *adcHandle,
                  GSN_ADC_SOURCE_T  adcSource,
                  GSN_ADC_TRESH_T  *adcLimits );

#endif
/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set the value of adc_step parameter.
 *    This function sets the adc_step for the ADC clock.
 *    
 * @param adcHandle      IN pointer to handle
 * @return GSN_ADC_STATUS_ERROR   step value is incorrect or out of range .
 * @return GSN_SUCCESS           - In case Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_AdcStepSet( GSN_ADC_HANDLE_T *adcHandle );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Start Periodic Operation
 *    Starts a continuous periodic read and executes the callback
 *    function after every read. The read value is passed with data.
 *
 * @note Sampling period can be set as part of the GsnAdc_Open or by using
 *    GsnAdc_CyclPeriodSet function. Periodic operation of ADC is possible on
 *    External ADC 1 , External ADC 2 and External ADC 3  only.
 *
 * @param adcHandle       IN     pointer to handle.
 * @param adcmode         IN     mode
 * @param chnSel           IN     channel selected
 * @param adcRW           IN     ADC Read Write Arg
 * @param adcRefVoltage   IN     reference voltage
 *
 * @return GSN_ADC_STATUS_ERROR  - In case callback function pointer is NULL
 * @return GSN_ADC_STATUS_BUSY   - In case adc is already in use
 * @return GSN_SUCCESS           - In case operation is successful
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_Read( GSN_ADC_HANDLE_T *aacHandle,GSN_ADC_READ_MODE_T adcmode,
             UINT32  chnSel, GSN_ADC_RW_ARGS_T *adcRW,
             GSN_ADC_REF_VOLTAGE_T adcRefVoltage );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Stop Periodic Read Operation
 *     Stop the periodic read and power down the ADC
 * @param adcHandle           IN     pointer to handle.
 *
 * @return none
 *
 * @note Handle should not be NULL
 ******************************************************************************/
PUBLIC VOID
GsnADC_StopMeasure( GSN_ADC_HANDLE_T *adcHandle);


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC ISR
 *    This function is called by the interrupt handler whenever
 *    an ADC interrupt occurs.
 *
 * @param adcHandle     IN     pointer to handle.
 * @return none
 ******************************************************************************/
PUBLIC VOID
GsnADC_isr( GSN_ADC_HANDLE_T *adcHandle );


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Main ISR
 *    This function is called by the GsnAdc_isr whenever
 *    an ADC interrupt occurs.
 *
 * @return none
 ******************************************************************************/
PUBLIC VOID
__ADCMainIsr( );


/* function definition*/
/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Start polarity
 *      This function sets the Start polarity
 *                 (initially the Start polarity  )
 *
 * @param adcHandle             - IN pointer to handle.
 * @param startPolarity          - IN start polarity
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_StartPolaritySet( GSN_ADC_HANDLE_T *adcHandle,
                                GSN_ADC_STARTPOLARITY_T startPolarity );



/* function definition*/
/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Sampling Rate
 *      This function sets the Sampling Rate
 *
 * @param adcHandle             - IN pointer to handle.
 * @param samplingRate           - IN supply indication mode settings
 *
 * @return GSN_SUCCESS          Operation is successful
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_AdcSamplingRateSet( GSN_ADC_HANDLE_T *adcHandle, UINT32 samplingRate);


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief Set ADC Threshold
 *      This function sets the Threshold
 *
 * @param adcHandle             - IN pointer to handle.
 * @param thr0                   - IN Threshold for channel 0
 * @param thr1                   - IN Threshold for channel 1
 * @param thr2                   - IN Threshold for channel 2
 *
 * @return GSN_SUCCESS          Operation is successful
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnADC_ThresholdAllSet(GSN_ADC_HANDLE_T *adcHandle,GSN_ADC_TRESH0_T thr0,
                           GSN_ADC_TRESH0_T thr1,GSN_ADC_TRESH0_T thr2);


/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief ADC Polling Read
 *    Starts read by polling method and returns the result in buffer. 
 *    The ADC is shutdown after the read is done.
 *
 * @param adcHandle           IN     pointer to handle.
 * @param adcmode             IN     adc mode
 * @param chnSel               IN     channel selection
 * @param adcRW               OUT    pointer to read write structure.
 * @param adcRefVoltage       IN     reference voltage
 *
 * @return GSN_ADC_STATUS_ERROR   - In case of buffer pointer is NULL or
 *                                  data size is zero or data pointer is NULL
 * @return GSN_ADC_STATUS_BUSY    - In case ADC is already in use.
 * @return GSN_SUCCESS            - In case operation is successful.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnADC_PollRead( GSN_ADC_HANDLE_T *adcHandle,GSN_ADC_READ_MODE_T adcmode,
             UINT32  chnSel, GSN_ADC_RW_ARGS_T *adcRW,
             GSN_ADC_REF_VOLTAGE_T adcRefVoltage );

/**
 *******************************************************************************
 * @ingroup GsnAdc
 * @brief GsnAdc_StartMeasure
 *    Starts continuous read.
 *
 * @param adcHandle            IN     pointer to handle.
 * @param chnSel               IN     channel selection
 * @param adcmode              IN     adc mode
 * @param adcRefVoltage        IN     adc reference voltage
 * @param contextCB            IN     callback context.
 * @param funcCB               IN     function call back
 * @param data                 IN     app data buff
 *
 * @return GSN_ADC_STATUS_ERROR   - In case of buffer pointer is NULL or
 *                                  data size is zero or data pointer is NULL
 * @return GSN_ADC_STATUS_BUSY    - In case ADC is already in use.
 * @return GSN_SUCCESS            - In case operation is successful.
 ******************************************************************************/

GSN_STATUS
GsnADC_StartMeasure( GSN_ADC_HANDLE_T *adcHandle,
                     UINT32 chnSel,GSN_ADC_READ_MODE_T adcmode,
                     GSN_ADC_REF_VOLTAGE_T adcRefVoltage,
                     VOID *contextCB,
                     GSN_ADC_CALLBACK_FUNC_T funcCB,
                     UINT32 *data );

#ifdef  __cplusplus
}
#endif

 #endif /* _GSN_ADC_H_ */


