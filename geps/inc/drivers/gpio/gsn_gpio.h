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
 * $RCSfile: gsn_gpio.h,v $
 *
 * Description:
 *      This file contains public functions definitions for GPIO Driver
 * 
 ******************************************************************************
 */

/**
 *****************************************************************************
*  @file gsn_gpio.h
 * @brief GSN GPIO API.
 *    This file contains routines for GPIO use and configuration.
 *****************************************************************************/



/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnGpio GSN GPIO API
 * @brief This module configures, reads from, and writes to GPIO pins.
 *****************************************************************************/

/**
 *****************************************************************************
*
 * @} 
*****************************************************************************/
#ifndef _GSN_GPIO_H_
#define _GSN_GPIO_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */

# include"gsn_includes.h"
 
/*
 *****************************************************************************************
 * GPIO macros
 *****************************************************************************************
 */

 #define GPIO_SHIFT_HIGHER            32
 #define GPIOBITMAP_32         0xffffffff 
 #define TOTAL_GPIO  38 


/**
 ****************************************************************************
 * @ingroup GsnGpio
 * @brief The Callback Function Prototype.
 *
 *    The callback function takes two arguments:
 *    - argument 1 is gpio number,
 *    - argument 2 is the context pointer which is passed when
 *    the callback is registered.
 * @see  GSN_GPIO_CALLBACK_FUNC_T.
 *
 ****************************************************************************/
typedef VOID ( * GSN_GPIO_CALLBACK_FUNC_T )(UINT8 gpioNum, VOID *context );

/*****************************************************************************/
 
/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief GPIO interrupt trigger enum.
 ****************************************************************************/
typedef enum
{
    GSN_GPIO_INT_PE_TRIG,
    GSN_GPIO_INT_NE_TRIG 
		
} GSN_GPIO_INT_TRIG_T;

/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief GPIO callback structure.
 ****************************************************************************/

typedef struct GPIO_CALLBACK
{
    VOID* context;                    /**< context pointer for callback */
    GSN_GPIO_CALLBACK_FUNC_T cb;        /**< call back function           */
    UINT8 gpioNum ;             
} GPIO_CALLBACK_T;


/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief This Function Initializes the GPIO
 *
 *    The gpioBitMap provides a list of GPIO pins which are to be
 *    initialized as a bit map. The "Bit n" refers to  "GPIO n" e.g. Bit 0
 *    refers to GPIO 0.
 *
 *    The gpioDirBitMap provides the list of GPIO pins as a bit map for which
 *    direction may be set. The value of a particular bit in this corresponds
 *    to the value desired for that particular GPIO. E.g., if Bit 3 is
 *    set to 0 then it refers to GPIO 3 being set as output direction, and
 *    if Bit 3 is set to 1 then it refers to GPIO 3 being set as
 *    input direction.
 *
 * @param gpioBitMap             - IN gpio bit number.
 * @param gpioDirBitMap             - IN The direction (input or output)
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_Init( LONG64 gpioBitMap, LONG64 gpioDirBitMap );
        
      
 /**
 ****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Read Function
 *
 *    This function allows reading the values from input gpio(s).
 *    gpioBitMap accepts a map of gpio values to be read, and
 *    gpioBitMapValue contains a map of the values.
 *
 * @param gpioBitMapValue       - OUT pointer to gpio read value.
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 ***************************************************************************/
PUBLIC VOID
GsnGpio_Read( LONG64 *gpioBitMapValue,LONG64 gpioBitMap );
              

/**
*****************************************************************************
* @ingroup GsnGpio
* @brief Gpio Direction Set
*
*     This function sets the direction of GPIO specified by gpioBitMap.
*     gpioBitMap accepts GPIO map, 0 is to set the specific GPIO
*     direction to output; 1 is to set the specific GPIO direction to input.
*     This API gets the current setting from the register and changes the values of
*     bits indicated by gpioBitmap and writes them back into the register.
*
* @param gpioBitMap         - IN  gpio bit map.
* @param gpioDirBitMap   - IN gpio bitmap specifying the direction for each gpio.
* @return none
*
****************************************************************************/
PUBLIC VOID
GsnGpio_DirSet(LONG64 gpioBitMap,LONG64 gpioDirBitMap) ;


/**
*****************************************************************************
* @ingroup GsnGpio
* @brief Gpio Out Set
*
*     This function sets the  of GPIO specified by gpioBitMap abd reset others.
*     gpioBitMap accepts GPIO map, 1 is to set the specific GPIO
*     to make high ; 0 is to set the specific GPIO to make low .
*     This API gets the current setting from the register and changes the values of
*     bits indicated by gpioBitmap and writes them back into the register.
*
* @param gpioBitMap         - IN  gpio bit map.
* @return none
*
****************************************************************************/
PUBLIC VOID
GsnGpio_OutSet( LONG64 gpioBitMap );

/**
 *****************************************************************************
 * @ingroup GsnGpio
* @brief Gpio Out Set
*
*     This function sets only the GPIO specified by gpioBitMap and not touch others.
*     gpioBitMap accepts GPIO map, 1 is to set the specific GPIO
*     to make high ; 0 is to set the specific GPIO to make low .
*     This API gets the current setting from the register and changes the values of
*     bits indicated by gpioBitmap and writes them back into the register.
*
* @param gpioBitMap         - IN  gpio bit map.
* @return none
 *
****************************************************************************/

PUBLIC VOID
GsnGpio_OutIndvidualSet( LONG64 gpioBitMap );


/**
*****************************************************************************
* @ingroup GsnGpio
* @brief Gpio Out Clear
 *
*     This function clears the  of GPIO specified by gpioBitMap.
*     gpioBitMap accepts GPIO map, 1 is to clear the specific GPIO
*     to make it low .
*     This API gets the current setting from the register and changes the values of
*     bits indicated by gpioBitmap and writes them back into the register.
 *
* @param gpioBitMap         - IN  gpio bit map.
 * @return none
 *
****************************************************************************/
PUBLIC VOID
GsnGpio_OutClear( LONG64 gpioBitMap );
/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Possitive Edge Interrupt Enable
 *
 *     This function enables the given Possitive Edge GPIO interrupts.
 *
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_PEIntEnable(LONG64 gpioBitMap);

/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Interrupt Enable
 *
 *     This function enables the given Negative Edge GPIO interrupts.
 *
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_NEIntEnable(LONG64 gpioBitMap);
        

/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Possitive Edge Interrupt Enable
 *
 *     This function Disables the given Possitive Edge GPIO interrupts.
 *
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_PEIntDisable(LONG64 gpioBitMap);

/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Interrupt Enable
 *
 *     This function disables the given Negative Edge GPIO interrupts.
 *
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_NEIntDisable(LONG64 gpioBitMap);

/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Possitive edge Interrupt clear
 *
 *     This function Clears the given Possitive Edge GPIO interrupts.
 *
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_PEIntClear(LONG64 gpioBitMap);


/**
 *****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio Interrupt Disable
 *
 *     This function Clears the given  Negative edge GPIO interrupts.
 *
 * @param gpioBitMap         - IN  gpio bit map
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnGpio_NEIntClear(LONG64 gpioBitMap);

 

/*
 ****************************************************************************
 * @ingroup GsnGpio
 * @brief Gpio callback register for ISR
 *    This function allows setting the type of interrupt along with
 *    registering the callback function and context pointer for
 *    callback function. This function allow to register only one function
 *    for all GPIO.
 *    This function activates the interrupt, so before calling this function
 *    user must set the respective GPIO in input direction.
 *
 * @param gpioNum         -IN gpio number for which the
 *                                    callback is being registered.
 * @param intType         - IN gpio interrupt type (Pedge or Nedge) for which the
 *                                callback is being registered.
 * @param gpioIntCb       - IN ISR call back function.
 * @param context         - IN context pointer for callback function. 
*******************************************************************************/
PUBLIC VOID
GsnGpio_IntCbRegister(UINT8 gpioNum ,GSN_GPIO_CALLBACK_FUNC_T gpioIntCb
                                                            ,VOID *context);
                  

/*GPIO global Patch Functions*/
PUBLIC VOID
GsnGpio_PEIntDisable_Patch(LONG64 gpioBitMap);

PUBLIC VOID
GsnGpio_NEIntDisable_Patch(LONG64 gpioBitMap);


#ifdef  __cplusplus
}
#endif

#endif /* _GSN_GPIO_H_   */
                        