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
* $RCSfile: gsn_assert.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_ASSERT_H_
#define _GSN_ASSERT_H_

//#define SYSTEM_DEBUG
#ifndef SYSTEM_DEBUG  /* For production, do software reset */
#define GSN_ASSERT(c)                                                			\
{                                                                           	\
	if(!(c))																	\
	{																			\
		GSN_SYS_RESET_INFO_T *pResetInfo= (GSN_SYS_RESET_INFO_T *)GSN_SYS_RESET_INFO_LOCATION_GET();	\
		UINT32 filenameLen = strlen(__FILE__);                             		\
        UINT8 *filename = __FILE__;                                        		\
        if(filenameLen > 32)                                                    \
        	filename = filename + (filenameLen - 32);                          	\
		memcpy(&(pResetInfo->app.resetInfo[0]), filename, 32);                  \
		pResetInfo->app.resetInfo[8] = __LINE__;                                \
		pResetInfo->app.resetType = GSN_RESET_TYPE_SYSTEM;           			\
		pResetInfo->app.resetReason = GSN_RESET_REASON_APP_ASSERT;       		\
		pResetInfo->app.resetInfoSize = 16;                                     \
    	GsnSys_Reset(GSN_RESET_REASON_APP_ASSERT);                     			\
	}																			\
}
#else /* For debugging, just loop */
#define GSN_ASSERT(c)                                                          \
{                                                                              \
    {                                                                          \
        if (!(c))                                                              \
        {                                                                      \
            GsnSq_DeInit();                                                    \
            /* Disable all interrupts */                                       \
            __disable_irq();                                                   \
            /* [TO DO]disable WD */                                            \
            while (1);                                                         \
        }                                                                      \
    }                                                                          \
}
#endif /*SYSTEM_DEBUG*/
#endif /*_GSN_ASSERT_H_*/
