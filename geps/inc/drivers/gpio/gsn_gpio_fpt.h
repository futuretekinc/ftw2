/******************************************************************************
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
* $RCSfile: gsn_gpio_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_GPIO_FPT_H_
#define _GSN_GPIO_FPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"




/*****************************************************************************
  *  Definitions
  ****************************************************************************/
  
typedef VOID 
(* GsnGpio_Init_FP_T)( LONG64 gpioBitMap, LONG64 gpioDirBitMap );
 extern  _RPST_ GsnGpio_Init_FP_T GsnGpio_Init_FP;
  
typedef VOID
(* GsnGpio_Read_FP_T)( LONG64 *gpioBitMapValue,LONG64 gpioBitMap );
extern _RPST_ GsnGpio_Read_FP_T GsnGpio_Read_FP;

typedef  VOID
(* GsnGpio_OutSet_FP_T)( LONG64 gpioBitMap );
extern _RPST_ GsnGpio_OutSet_FP_T GsnGpio_OutSet_FP;

typedef  VOID
(* GsnGpio_DirSet_FP_T)(LONG64 gpioBitMap,LONG64 gpioDirBitMap);
extern  _RPST_ GsnGpio_DirSet_FP_T GsnGpio_DirSet_FP;

typedef  VOID
(* GsnGpio_PEIntEnable_FP_T)(LONG64 gpioBitMap);
extern _RPST_ GsnGpio_PEIntEnable_FP_T GsnGpio_PEIntEnable_FP;

typedef VOID
(* GsnGpio_NEIntEnable_FP_T)(LONG64 gpioBitMap);
extern _RPST_ GsnGpio_NEIntEnable_FP_T GsnGpio_NEIntEnable_FP;

typedef  VOID
(* GsnGpio_PEIntClear_FP_T)(LONG64 gpioBitMap);
extern _RPST_ GsnGpio_PEIntClear_FP_T GsnGpio_PEIntClear_FP;

typedef VOID
(* GsnGpio_NEIntClear_FP_T)(LONG64 gpioBitMap);
extern _RPST_ GsnGpio_NEIntClear_FP_T GsnGpio_NEIntClear_FP;


typedef PUBLIC VOID
(* GsnGpio_IntCbRegister_FP_T)(UINT8 gpioNum,GSN_GPIO_CALLBACK_FUNC_T gpioIntCb,
                  VOID *context );
extern _RPST_ GsnGpio_IntCbRegister_FP_T GsnGpio_IntCbRegister_FP;


typedef PUBLIC VOID
(* __GsnGpio_PEIsr_FP_T)();
extern _RPST_ __GsnGpio_PEIsr_FP_T __GsnGpio_PEIsr_FP;

typedef PUBLIC VOID
(* __GsnGpio_NEIsr_FP_T)();
extern _RPST_ __GsnGpio_NEIsr_FP_T __GsnGpio_NEIsr_FP;


#ifdef __cplusplus
}
#endif

#endif /* _GSN_GPIO_FPT_H_ */

