/******************************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: app_mib.h,v $
*
* Description : This file contains public definitions for MIB management.
*****************************************************************************/
#ifndef _GSN_MIB_APP_H_
#define _GSN_MIB_APP_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

#include "hal/s2w_types.h"


/**
 *****************************************************************************
 * @file gsn_mib_app.h
 * @brief GSN APP MIB public header.
 *    This file contains the public definitions for APP MIBs.
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnAppMib GSN APP MIB definitions.
 *    This group contains APP MIB definitions.
 *****************************************************************************/



/*****************************************************************************
  * Type Definitions
  ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnAppMib
 * @brief GSN APP MIB IDs.
 *    enum for APP MIB IDs. MIB users use the ID to perform read and write operations on their
 *    MIB groups. APP MIB ID space ranges from 64 to 127.
 * @see  GSN_NVDS_ID_T and GSN_MIB_ID_T.
 *****************************************************************************/
typedef enum S2W_APP_MIB_ID
{
    APPMIB_ID_FIRST = 64,
    APPMIB_ID_PROFILE  = APPMIB_ID_FIRST,

    /* Add applcation MIB IDs here */
    APPMIB_ID_MAX = 127
} S2W_APP_MIB_ID_T;



/**
 *****************************************************************************
 * @ingroup S2wAppMib-profile
 * @brief APP MIB group structure.
 *    This structure defines the APP profile MIB group structure.
 *****************************************************************************/

typedef struct S2W_MIB_PROFILE
{
    S2W_FLASH_PARAMS_T params;
} S2W_MIB_PROFILE_T;




#endif /* _GSN_MIB_APP_H_ */

/*****************************************************************************/

