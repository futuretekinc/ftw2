/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: s2w_hal_specific.h,v $
*
* Description : This file defines HAL specific macros.
*****************************************************************************/

#ifndef S2W_HAL_SPECIFIC_H
#define S2W_HAL_SPECIFIC_H

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"

#ifndef SINT8
#define SINT8 signed char
#endif

#ifndef SINT32
#define SINT32 int
#endif

/** Size of the buffer passed to the UART and SPI driver. */
#define S2W_HAL_GAINSPAN_SERIAL_BUFFER_SIZE 4096

/** Default channels to scan */
#define S2W_HAL_GAINSPAN_DEFAULT_CHANNELS MAC_CHANNELDOMAIN_X10_24GHZ

/** Default channel to start ad-hoc network on */
#define S2W_HAL_GAINSPAN_DEFAULT_ADHOC_CHANNEL 6

#endif
