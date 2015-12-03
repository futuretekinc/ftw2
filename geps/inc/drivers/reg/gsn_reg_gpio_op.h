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
 * $RCSfile: gsn_reg_gpio_op.h,v $
 *
 * Description:
 *      This file contains register macros for GPIO Driver
 *
 ******************************************************************************
 */

#ifndef _REG_GPIO_H
#define _REG_GPIO_H

/***************************************************
 *
 *             GPIO
 *
 ***************************************************/


/*
 *  COMMON_GPIO instance offsets
 ****************************************************************************************
 */
#define COMMON_GPIO 0x40000000

/*
 *  GPIO_GPIO_IN_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_IN_0_OFFSETADDRESS   0x00000000  /* RW */
#define GPIO_GPIO_IN_0_BITOFFSET       0
#define GPIO_GPIO_IN_0_BITFIELDSIZE    32
#define GPIO_GPIO_IN_0_BITMASK         0xFFFFFFFF
#define GPIO_GPIO_IN_0_INIT            0x00000000
/*
 *  GPIO_IN_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_IN_0_OFFSETADDRESS                 GPIO_GPIO_IN_0_OFFSETADDRESS
#define GPIO_IN_0_BITOFFSET                     0
#define GPIO_IN_0_BITFIELDSIZE                 32
#define GPIO_IN_0_BITMASK                       0xffffffff
#define GPIO_IN_0_INIT                          0x0

/*
 *  GPIO_GPIO_OUT_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_OUT_0_OFFSETADDRESS  0x00000004  /* RW */
#define GPIO_GPIO_OUT_0_BITOFFSET      0
#define GPIO_GPIO_OUT_0_BITFIELDSIZE   32
#define GPIO_GPIO_OUT_0_BITMASK        0xFFFFFFFF
#define GPIO_GPIO_OUT_0_INIT           0x00000000
/*
 *  GPIO_OUT_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_OUT_0_OFFSETADDRESS                GPIO_GPIO_OUT_0_OFFSETADDRESS
#define GPIO_OUT_0_BITOFFSET                    0
#define GPIO_OUT_0_BITFIELDSIZE                32
#define GPIO_OUT_0_BITMASK                      0xffffffff
#define GPIO_OUT_0_INIT                         0x0

/*
 *  GPIO_GPIO_CTL_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_CTL_0_OFFSETADDRESS  0x00000008  /* RW */
#define GPIO_GPIO_CTL_0_BITOFFSET      0
#define GPIO_GPIO_CTL_0_BITFIELDSIZE   32
#define GPIO_GPIO_CTL_0_BITMASK        0xFFFFFFFF
#define GPIO_GPIO_CTL_0_INIT           0x00000000
/*
 *  GPIO_CTL_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_CTL_0_OFFSETADDRESS                GPIO_GPIO_CTL_0_OFFSETADDRESS
#define GPIO_CTL_0_BITOFFSET                    0
#define GPIO_CTL_0_BITFIELDSIZE                32
#define GPIO_CTL_0_BITMASK                      0xffffffff
#define GPIO_CTL_0_INIT                         0x0

/*
 *  GPIO_GPIO_IN_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_IN_1_OFFSETADDRESS   0x00000010  /* RW */
#define GPIO_GPIO_IN_1_BITOFFSET       0
#define GPIO_GPIO_IN_1_BITFIELDSIZE    32
#define GPIO_GPIO_IN_1_BITMASK         0xFFFFFFFF
#define GPIO_GPIO_IN_1_INIT            0x00000000
/*
 *  GPIO_IN_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_IN_1_OFFSETADDRESS                 GPIO_GPIO_IN_1_OFFSETADDRESS
#define GPIO_IN_1_BITOFFSET                     0
#define GPIO_IN_1_BITFIELDSIZE                 32
#define GPIO_IN_1_BITMASK                       0xffffffff
#define GPIO_IN_1_INIT                          0x0

/*
 *  GPIO_GPIO_OUT_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_OUT_1_OFFSETADDRESS  0x00000014  /* RW */
#define GPIO_GPIO_OUT_1_BITOFFSET      0
#define GPIO_GPIO_OUT_1_BITFIELDSIZE   32
#define GPIO_GPIO_OUT_1_BITMASK        0xFFFFFFFF
#define GPIO_GPIO_OUT_1_INIT           0x00000000
/*
 *  GPIO_OUT_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_OUT_1_OFFSETADDRESS                GPIO_GPIO_OUT_1_OFFSETADDRESS
#define GPIO_OUT_1_BITOFFSET                    0
#define GPIO_OUT_1_BITFIELDSIZE                32
#define GPIO_OUT_1_BITMASK                      0xffffffff
#define GPIO_OUT_1_INIT                         0x0

/*
 *  GPIO_GPIO_CTL_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_CTL_1_OFFSETADDRESS  0x00000018  /* RW */
#define GPIO_GPIO_CTL_1_BITOFFSET      0
#define GPIO_GPIO_CTL_1_BITFIELDSIZE   32
#define GPIO_GPIO_CTL_1_BITMASK        0xFFFFFFFF
#define GPIO_GPIO_CTL_1_INIT           0x00000000
/*
 *  GPIO_CTL_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_CTL_1_OFFSETADDRESS                GPIO_GPIO_CTL_1_OFFSETADDRESS
#define GPIO_CTL_1_BITOFFSET                    0
#define GPIO_CTL_1_BITFIELDSIZE                32
#define GPIO_CTL_1_BITMASK                      0xffffffff
#define GPIO_CTL_1_INIT                         0x0

/*
 *  GPIO_GPIO_PE_IRQ_STATUS_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_STATUS_0_OFFSETADDRESS 0x00000040  /* RW */
#define GPIO_GPIO_PE_IRQ_STATUS_0_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_STATUS_0_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_STATUS_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_STATUS_0_INIT 0x00000000
/*
 *  GPIO_PE_IRQ_STATUS_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_STATUS_0_OFFSETADDRESS      GPIO_GPIO_PE_IRQ_STATUS_0_OFFSETADDRESS
#define GPIO_PE_IRQ_STATUS_0_BITOFFSET          0
#define GPIO_PE_IRQ_STATUS_0_BITFIELDSIZE      32
#define GPIO_PE_IRQ_STATUS_0_BITMASK            0xffffffff
#define GPIO_PE_IRQ_STATUS_0_INIT               0x0

/*
 *  GPIO_GPIO_PE_IRQ_MASK_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_MASK_0_OFFSETADDRESS 0x00000044  /* RW */
#define GPIO_GPIO_PE_IRQ_MASK_0_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_MASK_0_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_MASK_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_MASK_0_INIT   0x00000000
/*
 *  GPIO_PE_IRQ_MASK_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_MASK_0_OFFSETADDRESS        GPIO_GPIO_PE_IRQ_MASK_0_OFFSETADDRESS
#define GPIO_PE_IRQ_MASK_0_BITOFFSET            0
#define GPIO_PE_IRQ_MASK_0_BITFIELDSIZE        32
#define GPIO_PE_IRQ_MASK_0_BITMASK              0xffffffff
#define GPIO_PE_IRQ_MASK_0_INIT                 0x0

/*
 *  GPIO_GPIO_PE_IRQ_CLEAR_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_CLEAR_0_OFFSETADDRESS 0x00000048  /* RW */
#define GPIO_GPIO_PE_IRQ_CLEAR_0_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_CLEAR_0_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_CLEAR_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_CLEAR_0_INIT  0x00000000
/*
 *  GPIO_PE_IRQ_CLEAR_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_CLEAR_0_OFFSETADDRESS       GPIO_GPIO_PE_IRQ_CLEAR_0_OFFSETADDRESS
#define GPIO_PE_IRQ_CLEAR_0_BITOFFSET           0
#define GPIO_PE_IRQ_CLEAR_0_BITFIELDSIZE       32
#define GPIO_PE_IRQ_CLEAR_0_BITMASK             0xffffffff
#define GPIO_PE_IRQ_CLEAR_0_INIT                0x0

/*
 *  GPIO_GPIO_PE_IRQ_SET_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_SET_0_OFFSETADDRESS 0x0000004c  /* RW */
#define GPIO_GPIO_PE_IRQ_SET_0_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_SET_0_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_SET_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_SET_0_INIT    0xffffff00
/*
 *  GPIO_PE_IRQ_SET_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_SET_0_OFFSETADDRESS         GPIO_GPIO_PE_IRQ_SET_0_OFFSETADDRESS
#define GPIO_PE_IRQ_SET_0_BITOFFSET             0
#define GPIO_PE_IRQ_SET_0_BITFIELDSIZE         32
#define GPIO_PE_IRQ_SET_0_BITMASK               0xffffffff
#define GPIO_PE_IRQ_SET_0_INIT                  0xffffff00

/*
 *  GPIO_GPIO_PE_IRQ_STATUS_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_STATUS_1_OFFSETADDRESS 0x00000050  /* RW */
#define GPIO_GPIO_PE_IRQ_STATUS_1_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_STATUS_1_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_STATUS_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_STATUS_1_INIT 0x00000000
/*
 *  GPIO_PE_IRQ_STATUS_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_STATUS_1_OFFSETADDRESS      GPIO_GPIO_PE_IRQ_STATUS_1_OFFSETADDRESS
#define GPIO_PE_IRQ_STATUS_1_BITOFFSET          0
#define GPIO_PE_IRQ_STATUS_1_BITFIELDSIZE      32
#define GPIO_PE_IRQ_STATUS_1_BITMASK            0xffffffff
#define GPIO_PE_IRQ_STATUS_1_INIT               0x0

/*
 *  GPIO_GPIO_PE_IRQ_MASK_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_MASK_1_OFFSETADDRESS 0x00000054  /* RW */
#define GPIO_GPIO_PE_IRQ_MASK_1_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_MASK_1_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_MASK_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_MASK_1_INIT   0x00000000
/*
 *  GPIO_PE_IRQ_MASK_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_MASK_1_OFFSETADDRESS        GPIO_GPIO_PE_IRQ_MASK_1_OFFSETADDRESS
#define GPIO_PE_IRQ_MASK_1_BITOFFSET            0
#define GPIO_PE_IRQ_MASK_1_BITFIELDSIZE        32
#define GPIO_PE_IRQ_MASK_1_BITMASK              0xffffffff
#define GPIO_PE_IRQ_MASK_1_INIT                 0x0

/*
 *  GPIO_GPIO_PE_IRQ_CLEAR_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_CLEAR_1_OFFSETADDRESS 0x00000058  /* RW */
#define GPIO_GPIO_PE_IRQ_CLEAR_1_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_CLEAR_1_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_CLEAR_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_CLEAR_1_INIT  0x00000000
/*
 *  GPIO_PE_IRQ_CLEAR_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_CLEAR_1_OFFSETADDRESS       GPIO_GPIO_PE_IRQ_CLEAR_1_OFFSETADDRESS
#define GPIO_PE_IRQ_CLEAR_1_BITOFFSET           0
#define GPIO_PE_IRQ_CLEAR_1_BITFIELDSIZE       32
#define GPIO_PE_IRQ_CLEAR_1_BITMASK             0xffffffff
#define GPIO_PE_IRQ_CLEAR_1_INIT                0x0

/*
 *  GPIO_GPIO_PE_IRQ_SET_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_SET_1_OFFSETADDRESS 0x0000005c  /* RW */
#define GPIO_GPIO_PE_IRQ_SET_1_BITOFFSET 0
#define GPIO_GPIO_PE_IRQ_SET_1_BITFIELDSIZE 32
#define GPIO_GPIO_PE_IRQ_SET_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_PE_IRQ_SET_1_INIT    0xffffff00
/*
 *  GPIO_PE_IRQ_SET_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_SET_1_OFFSETADDRESS         GPIO_GPIO_PE_IRQ_SET_1_OFFSETADDRESS
#define GPIO_PE_IRQ_SET_1_BITOFFSET             0
#define GPIO_PE_IRQ_SET_1_BITFIELDSIZE         32
#define GPIO_PE_IRQ_SET_1_BITMASK               0xffffffff
#define GPIO_PE_IRQ_SET_1_INIT                  0xffffff00

/*
 *  GPIO_GPIO_NE_IRQ_STATUS_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_STATUS_0_OFFSETADDRESS 0x00000080  /* RW */
#define GPIO_GPIO_NE_IRQ_STATUS_0_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_STATUS_0_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_STATUS_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_STATUS_0_INIT 0x00000000
/*
 *  GPIO_NE_IRQ_STATUS_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_STATUS_0_OFFSETADDRESS      GPIO_GPIO_NE_IRQ_STATUS_0_OFFSETADDRESS
#define GPIO_NE_IRQ_STATUS_0_BITOFFSET          0
#define GPIO_NE_IRQ_STATUS_0_BITFIELDSIZE      32
#define GPIO_NE_IRQ_STATUS_0_BITMASK            0xffffffff
#define GPIO_NE_IRQ_STATUS_0_INIT               0x0

/*
 *  GPIO_GPIO_NE_IRQ_MASK_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_MASK_0_OFFSETADDRESS 0x00000084  /* RW */
#define GPIO_GPIO_NE_IRQ_MASK_0_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_MASK_0_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_MASK_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_MASK_0_INIT   0x00000000
/*
 *  GPIO_NE_IRQ_MASK_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_MASK_0_OFFSETADDRESS        GPIO_GPIO_NE_IRQ_MASK_0_OFFSETADDRESS
#define GPIO_NE_IRQ_MASK_0_BITOFFSET            0
#define GPIO_NE_IRQ_MASK_0_BITFIELDSIZE        32
#define GPIO_NE_IRQ_MASK_0_BITMASK              0xffffffff
#define GPIO_NE_IRQ_MASK_0_INIT                 0x0

/*
 *  GPIO_GPIO_NE_IRQ_CLEAR_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_CLEAR_0_OFFSETADDRESS 0x00000088  /* RW */
#define GPIO_GPIO_NE_IRQ_CLEAR_0_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_CLEAR_0_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_CLEAR_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_CLEAR_0_INIT  0x00000000
/*
 *  GPIO_NE_IRQ_CLEAR_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_CLEAR_0_OFFSETADDRESS       GPIO_GPIO_NE_IRQ_CLEAR_0_OFFSETADDRESS
#define GPIO_NE_IRQ_CLEAR_0_BITOFFSET           0
#define GPIO_NE_IRQ_CLEAR_0_BITFIELDSIZE       32
#define GPIO_NE_IRQ_CLEAR_0_BITMASK             0xffffffff
#define GPIO_NE_IRQ_CLEAR_0_INIT                0x0

/*
 *  GPIO_GPIO_NE_IRQ_SET_0 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_SET_0_OFFSETADDRESS 0x0000008c  /* RW */
#define GPIO_GPIO_NE_IRQ_SET_0_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_SET_0_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_SET_0_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_SET_0_INIT    0xffffff00
/*
 *  GPIO_NE_IRQ_SET_0 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_SET_0_OFFSETADDRESS         GPIO_GPIO_NE_IRQ_SET_0_OFFSETADDRESS
#define GPIO_NE_IRQ_SET_0_BITOFFSET             0
#define GPIO_NE_IRQ_SET_0_BITFIELDSIZE         32
#define GPIO_NE_IRQ_SET_0_BITMASK               0xffffffff
#define GPIO_NE_IRQ_SET_0_INIT                  0xffffff00

/*
 *  GPIO_GPIO_NE_IRQ_STATUS_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_STATUS_1_OFFSETADDRESS 0x00000090  /* RW */
#define GPIO_GPIO_NE_IRQ_STATUS_1_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_STATUS_1_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_STATUS_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_STATUS_1_INIT 0x00000000
/*
 *  GPIO_NE_IRQ_STATUS_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_STATUS_1_OFFSETADDRESS      GPIO_GPIO_NE_IRQ_STATUS_1_OFFSETADDRESS
#define GPIO_NE_IRQ_STATUS_1_BITOFFSET          0
#define GPIO_NE_IRQ_STATUS_1_BITFIELDSIZE      32
#define GPIO_NE_IRQ_STATUS_1_BITMASK            0xffffffff
#define GPIO_NE_IRQ_STATUS_1_INIT               0x0

/*
 *  GPIO_GPIO_NE_IRQ_MASK_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_MASK_1_OFFSETADDRESS 0x00000094  /* RW */
#define GPIO_GPIO_NE_IRQ_MASK_1_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_MASK_1_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_MASK_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_MASK_1_INIT   0x00000000
/*
 *  GPIO_NE_IRQ_MASK_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_MASK_1_OFFSETADDRESS        GPIO_GPIO_NE_IRQ_MASK_1_OFFSETADDRESS
#define GPIO_NE_IRQ_MASK_1_BITOFFSET            0
#define GPIO_NE_IRQ_MASK_1_BITFIELDSIZE        32
#define GPIO_NE_IRQ_MASK_1_BITMASK              0xffffffff
#define GPIO_NE_IRQ_MASK_1_INIT                 0x0

/*
 *  GPIO_GPIO_NE_IRQ_CLEAR_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_CLEAR_1_OFFSETADDRESS 0x00000098  /* RW */
#define GPIO_GPIO_NE_IRQ_CLEAR_1_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_CLEAR_1_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_CLEAR_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_CLEAR_1_INIT  0x00000000
/*
 *  GPIO_NE_IRQ_CLEAR_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_CLEAR_1_OFFSETADDRESS       GPIO_GPIO_NE_IRQ_CLEAR_1_OFFSETADDRESS
#define GPIO_NE_IRQ_CLEAR_1_BITOFFSET           0
#define GPIO_NE_IRQ_CLEAR_1_BITFIELDSIZE       32
#define GPIO_NE_IRQ_CLEAR_1_BITMASK             0xffffffff
#define GPIO_NE_IRQ_CLEAR_1_INIT                0x0

/*
 *  GPIO_GPIO_NE_IRQ_SET_1 register defines
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_SET_1_OFFSETADDRESS 0x0000009c  /* RW */
#define GPIO_GPIO_NE_IRQ_SET_1_BITOFFSET 0
#define GPIO_GPIO_NE_IRQ_SET_1_BITFIELDSIZE 32
#define GPIO_GPIO_NE_IRQ_SET_1_BITMASK 0xFFFFFFFF
#define GPIO_GPIO_NE_IRQ_SET_1_INIT    0xffffff00
/*
 *  GPIO_NE_IRQ_SET_1 bit field defines
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_SET_1_OFFSETADDRESS         GPIO_GPIO_NE_IRQ_SET_1_OFFSETADDRESS
#define GPIO_NE_IRQ_SET_1_BITOFFSET             0
#define GPIO_NE_IRQ_SET_1_BITFIELDSIZE         32
#define GPIO_NE_IRQ_SET_1_BITMASK               0xffffffff
#define GPIO_NE_IRQ_SET_1_INIT                  0xffffff00
#endif
