/******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_mb.h,v $
*
* Description : This file contains public definitions for MBOX driver.
******************************************************************************/
#ifndef _GSN_MB_H_
#define _GSN_MB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/


/**
 *****************************************************************************
 * @file gsn_mb.h
 * @brief GSN mailbox public header.
 *    This file contains the public APIs and structures of mailbox driver module.
 *****************************************************************************/
/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnMb GSN MB API.
 *    This group of APIs implements the mailbox driver features. 
*****************************************************************************/
/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnMb
 * @brief Number of Recv and Send Mail boxes defined.
 *****************************************************************************/
/** @{ */
#define GSN_MB_RB_NUM 3 /* Two HW Receive mailboxes */
#define GSN_MB_SB_NUM 2 /* Two HW Send mailboxes */

/** @} */
/**
 *****************************************************************************
 * @internal
 * @ingroup GsnMb
 * @brief Recv and Send Box Index defined.
 *****************************************************************************/
/** @{ */

#define GSN_MB_MSG_SB 0      /* MSG send box is SB#1 */
#define GSN_MB_ACK_SB 1      /* ACK send box is SB#0 */

#define GSN_MB_MSG_RB 1      		/* MSG rcv box is RB#0 */
#define GSN_MB_ACK_RB 0      		/* ACK rcv box is RB#1 */
#define GSN_MB_RESET_REQ_MSG_RB 2   /* ACK rcv box is RB#1 */

/** @} */

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief GSN MBOX Context.
 *    Structure to store the MBOX context.
 *****************************************************************************/
typedef struct GSN_MB_S 
{
    GSN_CB_T cb[GSN_MB_RB_NUM];
} GSN_MB_T;

/*****************************************************************************
  * Public Variables
  ****************************************************************************/

/*****************************************************************************
  * Public function
  ****************************************************************************/

#define GSN_MB_SB_INT_CONF(sb, en) \
    MB_MB_SB_CONF_SETBIT(MAILBOX, ((en) << (sb)))
    
#define GSN_MB_RB_INT_CONF(rb, en) \
    MB_MB_RB_MASK_SETBIT(MAILBOX, ((en) << (rb)))

#define GSN_MB_SB_INT_SET(sb) \
    MB_MB_SB_INT_SET(MAILBOX, (1 << (sb)))

#define GSN_MB_RB_INT_CLR(rb) \
    MB_MB_RB_CLEAR_SET(MAILBOX, (1 << (rb)))


/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief mailbox open.
 *    opens mail box.
 * @return VOID
 * @note
 *    
 *****************************************************************************/
PUBLIC VOID
GsnMb_Open(VOID);

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief Send mailbox message.
 *    Send a message through send box.
 * @param sb - IN send box number
 * @param msg - IN message to be put into send box
 * @return VOID
 * @note
 *    
 *****************************************************************************/
PUBLIC VOID
GsnMb_SbMsgPut(UINT32 sb, UINT32 msg);

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief Read mailbox message.
 *    Read a message from read box.
 * @param rb - IN read box number
 * @return UINT32 - return the data read
 * @note
 *    
 *****************************************************************************/
PUBLIC UINT32
GsnMb_RbMsgGet(UINT32 rb);

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief Read mailbox interrupt register.
 *    Registers the Read Mailbox Interrupt.
 * @param rb - IN read box number
 * @param pCb - IN callback
 * @return VOID
 * @note
 *    
 *****************************************************************************/
PUBLIC VOID
GsnMb_RbIntRegister(UINT32 rb, GSN_CB_T *pCb);

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief Read mailbox interrupt unregister.
 *    Unregisters the Read Mailbox Interrupt.
 * @param rb - IN read box number
 * @return VOID
 * @note
 *    
 *****************************************************************************/
PUBLIC VOID
GsnMb_RbIntUnregister(UINT32 rb);

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief Read mailbox ISR.
 *    Read Mailbox ISR.
 * @return VOID
 * @note
 *    
 *****************************************************************************/
PUBLIC VOID
GsnMb_RbIsr();

/**
 *****************************************************************************
 * @ingroup GsnMb
 * @brief mailbox ISR.
 *     Mailbox ISR.
 * @return VOID
 * @note
 *    
 *****************************************************************************/
PUBLIC VOID 
GsnMB_Isr(VOID);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_MB_H_ */
