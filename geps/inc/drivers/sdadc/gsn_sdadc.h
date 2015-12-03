/******************************************************************************
 *
 *               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
 */

/**
******************************************************************************
*  @file gsn_sdadc.h
*  @brief Public Header Containing SDADC Driver Functions.
*
*****************************************************************************/


/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnSdadc GSN SDADC API
 *    This group contains public definitions and functions providing access
 *    to the GS2000's SDADC.
 ****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

 
#ifndef _GSNSDADC_H_
#define _GSNSDADC_H_
 
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
//#include "gsn_sdadc_private.h"

/*
 *****************************************************************************************
 * SDADC macros
 *****************************************************************************************
 */

#define  STOP_SDADCDAC 0x00
#define  STOP_ADC 0x11    
#define  ENABLE_BIT 0x01
#define POWER_SHIFT 4   
  
#define CLK_RC_FREQ  80000000 
#define CLK_XTAL_FREQ 40000000
//#define CLK_PLL_FREQ 

#define  MUL_VALUE 250 
#define  DIV_VALUE 67108864   

/*
 ******************************************************************************
 * Type definitions.
 ****************************************************************************/



/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Callback Function.
 *    This callback function accepts two arguments,
 *    - argument 1 is status
 *    - argument 2 is context pointer
 *
 * @param status    -IN SdADC status
 * @param context   -IN callback context pointer
 * @see  GSN_SDADC_CALLBACK_FUNC_T.
 *
 ****************************************************************************/
typedef VOID ( *GSN_SDADC_CALLBACK_FUNC_T )( UINT32 status, VOID *context );

/**
*****************************************************************************
*@ingroup GsnSdadc
* @brief GSN SDADC Continous Callback Function.
 *    This callback function accepts four arguments,
 *    - argument 1,2 and 3 are buffer pointers
 *    - argument 4 is size
 *
 * @param conbuf_0    -IN callback buffer pointer for adc 0
 * @param conbuf_1    -IN callback buffer pointer for adc 1
 * @param conbuf_2    -IN callback buffer pointer for adc 2
 * @param consize     -IN callback samples size
 * @param context -IN callback context pointer
 * @see  GSN_SDADC_CONT_CALLBACK_FUNC_T.
****************************************************************************/

typedef VOID ( *GSN_SDADC_CONT_CALLBACK_FUNC_T )( UINT32 *conbuf_0,
                                                    UINT32 *conbuf_1 ,
                                                    UINT32 *conbuf_2, 
                                                    UINT16 *consize,
                                                    UINT32 status, 
                                                    VOID *context);


/**
*****************************************************************************
*@ingroup GsnSdadc
* @brief GSN SDADC  select Type
*    This enum defines SDADC power down select type
*
* @see  GSN_SDADC_SEL_T
****************************************************************************/
typedef enum GSN_SDADC_PDOWNSEL
{
  GSN_SDADC_PDOWN_DAC = 0x1, 
  GSN_SDADC_PDOWN_ADC = 0xe	
  
}GSN_SDADC_PDOWNSEL_T;

/**
 ****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Power Down Reference Type.
 *    This enum defines  ADC Power Down Reference Type
 *
 * @see  GSN_SDADC_REF_VOLTAGE_T.
 ****************************************************************************/
typedef enum GSN_SDADC_PD_INTERNAL_REF
{
    GSN_SDADC_PDREF_ACTIVE,       /**< Sdadc Power Down Reference is low */
    GSN_SDADC_PDREF_PDOWN        /**< Sdadc Power Down Reference is high  */
} GSN_SDADC_PD_INTERNAL_REF_T;

/**
 ****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Clock Selection Type.
 *    This enum defines ADC Clock Selection
 *
 * @see  GSN_SDADC_CLK_SEL_T.
 ****************************************************************************/

typedef enum GSN_SDADC_CLK_SEL
{
    GSN_SDADC_CLK_SEL_RC,  
    GSN_SDADC_CLK_SEL_XTAL, 
    GSN_SDADC_CLK_SEL_PLL,
    GSN_SDADC_CLK_SEL_LP
    		
} GSN_SDADC_CLK_SEL_T;
/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Types.
 *    This enum defines AADC return values
 * @see  GSN_SDADC_STATUS_T.
 *****************************************************************************/

typedef enum GSN_SDADC_STATUS
{
    GSN_SDADC_STATUS_OK,
    GSN_SDADC_STATUS_BUSY,
    GSN_SDADC_STATUS_ERROR,
    GSN_SDADC_LOCK_UNAVAILABLE,
    GSN_SDADC_ADC_FIFO_FULL,
    GSN_SDADC_ADC_FIFO_EMPTY,
    GSN_SDADC_ADC_FIFO_OVERFLOW,
    GSN_SDADC_DAC_FIFO_FULL,
    GSN_SDADC_DAC_FIFO_EMPTY,
    GSN_SDADC_DAC_FIFO_OVERFLOW
    
} GSN_SDADC_STATUS_T;


/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC SUP1P8 Mode Type.
 *    This enum defines an SDADC SUP1P8 Mode
 *
 * @see  GSN_SDADC_ENA3V_T.
 ****************************************************************************/
typedef enum GSN_SDADC_ENA3V
{
    GSN_SDADC_A3V_DISABLE,             /**< disable a3v */
    GSN_SDADC_A3V_ENABLE	        /**< enable a3v */
} GSN_SDADC_ENA3V_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC SEL0 Mode Type.
 *    This enum defines an SDADC SEL0 Mode
 *
 * @see  GSN_SDADC_SEL0_T.
 ****************************************************************************/
typedef enum GSN_SDADC_SEL0
{
    GSN_SDADC_SEL0_DISABLE,             /**< disable sel0 */
    GSN_SDADC_SEL0_ENABLE	        /**< enable sel0*/
} GSN_SDADC_SEL0_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC SEL1 Mode Type.
 *    This enum defines an SDADC SEL0 Mode
 *
 * @see  GSN_SDADC_SEL1_T.
 ****************************************************************************/
typedef enum GSN_SDADC_SEL1
{
    GSN_SDADC_SEL1_DISABLE,             /**< disable sel1 */
    GSN_SDADC_SEL1_ENABLE	       /**< enable sel1 */
} GSN_SDADC_SEL1_T;


/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC SEL1 Mode Type.
 *    This enum defines an SDADC SEL0 Mode
 *
 * @see  GSN_SDADC_SEL2_T.
 ****************************************************************************/
typedef enum GSN_SDADC_SEL2
{
    GSN_SDADC_SEL2_DISABLE,             /**< disable sel2 */
    GSN_SDADC_SEL2_ENABLE	        /**< enable sel2 */
} GSN_SDADC_SEL2_T;
/**
 *******************************************************************************
 *
 *
 *****************************************************************************/

typedef enum GSN_SDADCDAC_CHANNEL
{
    GSN_SDADCDAC_DAC  = 0x1,
    GSN_SDADCDAC_ADC0 = 0x2,
    GSN_SDADCDAC_ADC1 = 0x4,
    GSN_SDADCDAC_ADC2 = 0x8,
}GSN_SDADCDAC_CHANNEL_T;


/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC FIFO CONTROL Type.
 *    This enum defines an ADC FIFO CONTROL enable or disable.
 *
 * @see  GSN_SDADC_ADC_FIFO_CNTRL_T.
 ****************************************************************************/
typedef enum GSN_SDADC_ADC_FIFO_CNTRL
{
    GSN_SDADC_ADC_FIFO_CNTRL_DISABLE,		      /**< disable sdadc FIFO */ 
    GSN_SDADC_ADC_FIFO_CNTRL_ENABLE             /**< enable sdadc FIFO */
} GSN_SDADC_ADC_FIFO_CNTRL_T;


/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC DAC CONTROL Type.
 *    This enum defines an SDADC DAC CONTROL enable or disable.
 *
 * @see  GSN_SDADC_DACCONTROL_T.
 ****************************************************************************/
typedef enum GSN_SDADC_DAC_FIFO_CNTRL
{
    GSN_SDADC_DAC_FIFO_CNTRL_DISABLE,		      /**< disable DAC FIFO */ 
    GSN_SDADC_DAC_FIFO_CNTRL_ENABLE             /**< enable DAC FIFO */
} GSN_SDADC_DAC_FIFO_CNTRL_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC AVDD Type.
 *    This enum defines an ADC external source core supply is used or not
 *
 * @see  GSN_ADC_ENAVDD_T.
 ****************************************************************************/
typedef enum GSN_SDADC_ENAVDD
{
    GSN_SDADC_AVDD_DISABLE,		   
    GSN_SDADC_AVDD_ENABLE        /**< dvdd enabled when external core supply is provided */
} GSN_ADC_ENAVDD_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC AVDD Type.
 *    This enum defines an ADC external source core supply is used or not
 *
 * @see  GSN_SDADC_ENSEL0_T.
 ****************************************************************************/
typedef enum GSN_SDADC_ENSEL0
{
    GSN_SDADC_ENSEL0_DISABLE,		   
    GSN_SDADC_ENSEL0_ENABLE        /**<enable  SEL0 */
} GSN_SDADC_ENSEL0_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC AVDD Type.
 *    This enum defines an ADC external source core supply is used or not
 *
 * @see  GSN_SDADC_ENSEL1_T.
 ****************************************************************************/
typedef enum GSN_ADC_ENSEL1
{
    GSN_SDADC_ENSEL1_DISABLE,		   
    GSN_SDADC_ENSEL1_ENABLE        /**<enable  SEL1 */
} GSN_SDADC_ENSEL1_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN ADC AVDD Type.
 *    This enum defines an ADC external source core supply is used or not
 *
 * @see  GSN_ADC_ENSEL2_T.
 ****************************************************************************/
typedef enum GSN_SDADC_ENSEL2
{
    GSN_SDADC_ENSEL2_DISABLE,		   
    GSN_SDADC_ENSEL2_ENABLE        /**<enable  SEL2 */
} GSN_SDADC_ENSEL2_T;



/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Configuration Structure.
 *    This structure defines SDADC configuration parameters
 *
 * @see  GSN_SDADC_CONFIG_T.
 ****************************************************************************/
typedef struct GSN_SDADC_CONFIG
{
    GSN_SDADCDAC_CHANNEL_T         channel;	
    GSN_ADC_ENAVDD_T	           avdd;
    GSN_SDADC_ENA3V_T		   	   a3v;
    GSN_SDADC_SEL0_T	           sel0;
    GSN_SDADC_SEL1_T	           sel1;
    GSN_SDADC_SEL2_T	           sel2;
    GSN_SDADC_CLK_SEL_T            sdadcClk;
    UINT8                          bias;
    UINT8                          adcWmark;
    UINT8                          dacWmark;
    UINT8                          gain0;
    UINT8                          gain1;
    UINT8                          gain2;
    UINT8                          phase2;
    UINT8                          phase1;
    UINT8                          tempco;
    UINT8                          ref;
    UINT8                          phaseStep;
    LONG64                         samplingfreq;
} GSN_SDADC_CONFIG_T;


/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Read and Write Structure.
 *    This structure defines SDADC read and SDADCDAC write data.
 *
 * @see  GSN_SDADC_RW_ARGS_T.
 ****************************************************************************/
typedef struct GSN_SDADC_RW_ARGS
{
    UINT16    *adcbuffer0;              /**<  for adc0  */
    UINT16    *adcbuffer1;		/**<  for adc1  */
    UINT16    *adcbuffer2;		/**<  for adc2  */
    BUFFER16   dacbuffer;               /**< for DAC   */
    UINT16     size;                    /**< for adc >**/
    VOID*      contextCB;               /**< context pointer for CallBack*/
    GSN_SDADC_CALLBACK_FUNC_T funcCB;   /**< CallBack function */
    UINT8       enbCont;                /**flag used for continous read*/
    GSN_SDADC_CONT_CALLBACK_FUNC_T	contfuncb;/*continous callback*/
} GSN_SDADC_RW_ARGS_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Structure.
 *    This structure defines an SDADC data pointer, base register and
 *    synchronous semaphore.
 *
 * @see  GSN_SDADC_T.
 *****************************************************************************/
typedef struct GSN_SDADC
{
    UINT32                pReg;         /**< sdadc base register             */
    GSN_SDADC_RW_ARGS_T   sdadcRWArg;      /**< sdadc read and sddac write        */
} GSN_SDADC_T;

/**
 *****************************************************************************
 * @ingroup GsnSdadc
 * @brief GSN SDADC Handle Structure
 *   The handle contains configuration and other parameters for SDADC operation
 *
 * @see  GSN_SDADC_HANDLE_T.
 *****************************************************************************/
typedef struct GSN_SDADC_HANDLE
{
    UINT32              sdadcStatus;      /**< sdadc status */
   // UINT8               enbCont;          /**Flag used for continous read**/
    GSN_SDADC_CONFIG_T	sdadcConfig;	
    GSN_SDADC_T         sdadc;            /**<SDADC parameter*/
}GSN_SDADC_HANDLE_T;


/*****************************************************************************
 * Public variable
 ******************************************************************************/


/*****************************************************************************
 * Public Function
 ******************************************************************************/


/**
 ******************************************************************************
 * @ingroup GsnSdadc
 * @brief ADC Driver Lock Create
 *    This function creates the semaphore for ADC. Use the function 
 *    GsnAdc_Lock to reserve the ADC and GsnAdc_Unlock to release the ADC
 *
 * @return none
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_LockCreate( VOID );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief ADC Driver Lock.
 *    This function acquires the semaphore, and blocks access to the ADC by
 *    other tasks.
 *
 * @param waitForEver - IN  Boolean to indicate wait for ever
 *
 * @return none
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Lock( BOOL waitForEver );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief ADC Driver Unlock.
 *    This function releases the semaphore acquired by the GsnAdc_Lock.
 *
 * @return none
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_Unlock( VOID );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief ADC Driver Open.
 *    This function initializes the ADC with specified parameters.
 *
 * @param sdadcHandle     - IN pointer to handle.
 * @param sdadcConfig     - IN ADC configuration.
 *
 * @return GSN_SUCCESS   - Initialization successful.
 * @return GSN_FAILURE   - Initialization failed.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Open( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_SDADC_CONFIG_T  *sdadcConfig );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief SDADC Driver Close.
 *    This function closes the SDADC operation and puts it in power save mode.
 *
 * @param sdadcHandle     - IN pointer to handle.
 *
 * @return GSN_SUCCESS   Close successful.
 * @return GSN_FAILURE   Close failed.
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Close( GSN_SDADC_HANDLE_T *sdadcHandle );

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief SDADC Power down set.
 *    This function selects the particular adc and takes it out of power down mode.
 *
 * @param sdadcHandle     - IN pointer to handle.
 * @param pdown           - IN power down selection.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_PowerdownSet( GSN_SDADC_HANDLE_T *sdadcHandle,
					GSN_SDADC_PDOWNSEL_T pdown);

/**
 *******************************************************************************
 *
 *
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnSdadc_ChannelSet(GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADCDAC_CHANNEL_T channel);

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set the Interval Between Measurements
 *    This function allows setting the interval between two measurements.
 *    The unit for period is ADC clock count.
 *
 * @param sdadcHandle             - IN pointer to handle.
 * @param phase2                    - IN 
 *
 * @return GSN_SDADC_STATUS_BUSY  If ADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
/* This sets the relative delay between the ADC2 and ADC0 data paths. The adjustment is
           between +/- 63 steps. The step size can be adjusted between 1*Tclk to 16*Tclk, where
           Tclk is the master clock period. D0<15:0> is the reference data path */
PUBLIC GSN_STATUS
GsnSdadc_Phase2set( GSN_SDADC_HANDLE_T *sdadcHandle,  UINT8	phase2);

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set the Interval Between Measurements
 *    This function allows setting the interval between two measurements.
 *    The unit for period is ADC clock count.
 *
 * @param sdadcHandle             - IN pointer to handle.
 * @param phase1                    - IN 
 *
 * @return GSN_SDADC_STATUS_BUSY  If SDADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
/* This sets the relative delay between the ADC1 and ADC0 data paths. The adjustment is
	   between +/- 63 steps. The step size can be adjusted between 1*Tclk to 16*Tclk, where
	   Tclk is the master clock period. D0<15:0> is the reference data path */

PUBLIC GSN_STATUS
GsnSdadc_Phase1set( GSN_SDADC_HANDLE_T *sdadcHandle,  UINT8	phase1);


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set the Interval Between Measurements
 *    This function allows setting the interval between two measurements.
 *    The unit for period is ADC clock count.
 *
 * @param sdadcHandle             - IN pointer to handle.
 * @param bias                    - IN Bias level control. 
 *     This bus sets the power level between 12.5% and 100%, with a relative 
 *     increment of 15% per step (15 steps) 
 *
 * @return GSN_SDADC_STATUS_BUSY  If ADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Bias( GSN_SDADC_HANDLE_T *sdadcHandle,  UINT8 bias);


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set the Power Reference
 *    This function allows setting the interval between two measurements.
 *   
 *
 * @param sdadcHandle             - IN pointer to handle.
 * @param prefsel                    - IN 
 *
 * 
 ******************************************************************************/
PUBLIC VOID
GsnSdadc_ReferenceSet( GSN_SDADC_HANDLE_T *sdadcHandle, 
 
                               GSN_SDADC_PD_INTERNAL_REF_T  prefsel);
#if 0
/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * 
 * @param sdadcHandle             - IN pointer to handle.
 * @param  select                     - IN 
 *
 * @return GSN_SDADC_STATUS_BUSY  If SDADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_SelSet( GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADC_SEL_T select);

#endif
/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * 
 * @param sdadcHandle             - IN pointer to handle.
 * @param  avdd                     - IN 
 *
 * @return GSN_SDADC_STATUS_BUSY  If SDADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC VOID
GsnSdadc_SupIndicationSet( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_ADC_ENAVDD_T  avdd);

/**
 *******************************************************************************
  * @ingroup GsnSdadc
 * 
 * @param sdadcHandle                   - IN pointer to handle.
 * @param  adcWmark                     - IN 
 *
 * @return GSN_SDADC_STATUS_BUSY  If SDADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC VOID
GsnSdadc_AdcWatermarkSet( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 adcWmark);

/**
 *******************************************************************************
   * @ingroup GsnSdadc
 * 
 * @param sdadcHandle                   - IN pointer to handle.
 * @param  dacWmark                     - IN 
 *
 * @return GSN_SDADC_STATUS_BUSY  If SDADC is already in use
 * @return GSN_SUCCESS          Operation is successful
 ******************************************************************************/
PUBLIC VOID
GsnSdadc_DacWatermarkSet( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 dacWmark);

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Phase Step value
 *      This function sets the Phase Step size value(  This sets the relative delay between the ADC1/ADC2 
 *									and ADC0 data paths).
 *
 * @param sdadcHandle           - IN pointer to handle.
 * @param phaseStep             - IN phase step
 *
 * @return none.
 *
 *****************************************************************************/

PUBLIC VOID
GsnSdadc_PhaseStepSet( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 phaseStep );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set gain0 value
 *      This function sets the gain0 value
 *
 * @param sdadcHandle           - IN pointer to handle.
 * @param gain0                 - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_Gain0Set( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 gain0 );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set gain1 value
 *      This function sets Internal Reference Trim value
 *
 * @param sdadcHandle            - IN pointer to handle.
 * @param gain1                  - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_Gain1Set( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 gain1 );


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set gain0 value
 *      This function sets Internal Reference Trim value
 *
 * @param sdadcHandle            - IN pointer to handle.
 * @param gain2                  - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_Gain2Set( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 gain2 );

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set gain0 value
 *      This function sets or resets the pre-amp stage to be bypassed
 *              for adc 0.
 *
 * @param sdadcHandle            - IN pointer to handle.
 * @param sel0                  - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Sel0( GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADC_SEL0_T sel0);

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set gain0 value
 *      This function sets or resets the pre-amp stage to be bypassed
 *              for adc 1.
 *              
 * @param sdadcHandle            - IN pointer to handle.
 * @param sel1                  - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Sel1( GSN_SDADC_HANDLE_T *sdadcHandle,GSN_SDADC_SEL1_T sel1);

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set gain0 value
 *      This function sets or resets the pre-amp stage to be bypassed
 *              for adc 2.
 *              
 * @param sdadcHandle            - IN pointer to handle.
 * @param sel2                  - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_Sel2( GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADC_SEL2_T sel2);

/**
 *******************************************************************************
 *
 *****************************************************************************/

PUBLIC VOID
GsnSdadc_RefSet( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 ref );
/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set ENABLE SDADC FIFO
 *      This function sets or clears ENABLE SDADC FIFO
 *		
 *
 * @param sdadcHandle               - IN pointer to handle.
 * @param enSdadcFifo 			- IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_EnADC_FIFO( GSN_SDADC_HANDLE_T *sdadcHandle,
                      GSN_SDADC_ADC_FIFO_CNTRL_T enSdadcFifo );

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set ENABLE sDDAC FIFO
 *      This function sets or clears ENABLE SDDAC FIFO
 *		
 *
 * @param sdadcHandle             - IN pointer to handle.
 * @param enSddacFifo                - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_EnDAC_FIFO( GSN_SDADC_HANDLE_T *sdadcHandle, 
                        GSN_SDADC_DAC_FIFO_CNTRL_T enSddacFifo );

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set the Step value for SDADC 
 *      This function sets the Step value associated with SDADC clock
 *		
 *
 * @param sdadcHandle             - IN pointer to handle.
 * 
 * @return none.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_SdadcStepSet( GSN_SDADC_HANDLE_T *sdadcHandle );

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set SDADC a3v_en(indicates 3.3v analog power supply is present)
 *      This function sets or clears the a3v_en (if a3v_en is 
 *                              high the typical D/A output level is set to 2.4 
 *				Vdpp, otherwise it is 1.2 Vdpp).
 *												
 *
 * @param sdadcHandle           - IN pointer to handle.
 * @param a3v                   - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_EnableA3v( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_SDADC_ENA3V_T a3v );

/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Set SDADC tempco Value
 * This function sets tempco value(When the A/D is powered down, 
 *      the AINP0/AINP1/AINP2 voltage level can be monitored externally
 *      and the tempco<8:4> trim bits can be used to set the
 *      bandgap/reference level for minimum tempco ).
 *								
 *												
 *
 * @param sdadcHandle           - IN pointer to handle.
 * @param tempco                  - IN supply indication mode settings
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC VOID
Gsn_Sdadc_TempcoSet(GSN_SDADC_HANDLE_T *sdadcHandle ,UINT8 tempco);


/**
 *******************************************************************************
 * @ingroup GsnSdadc
 *****************************************************************************/
PUBLIC VOID
GsnSdadc_StopRead( GSN_SDADC_HANDLE_T *sdadcHandle);
/**
 *******************************************************************************
 * @ingroup GsnSdadc
 * @brief Continous Read 
 * This function continously reads the SDADC values			
 *												
 *
 * @param sdadcHandle             - IN pointer to handle.
 * @param sdadcRW                 - IN pointer to readwrite arguememnt.
 *
 * @return none.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnSdadc_ContinousRead(GSN_SDADC_HANDLE_T *sdadcHandle, 
                          GSN_SDADC_RW_ARGS_T *sdadcRW);

PUBLIC VOID
GsnSdadc_SdadcIsr( GSN_SDADC_HANDLE_T *sdadcHandle );


PUBLIC VOID
GsnSdadc_DacIsr(GSN_SDADC_HANDLE_T *sdadcHandle);


VOID
GsnSdadc_IsrAdcFifoFull(GSN_SDADC_HANDLE_T *sdadcHandle);

UINT16
GsnSdadc_IsrDacFifoEmpty(GSN_SDADC_HANDLE_T *sdadcHandle);

#endif /* _GSNSDADC_H_ */

