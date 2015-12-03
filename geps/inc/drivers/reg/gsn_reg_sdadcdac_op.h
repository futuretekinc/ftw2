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
 * $RCSfile: gsn_reg_sdadcdac_op.h,v $
 *
 * Description:
 *      This file contains register macros for SD_ADC_DAC Driver
 *
 ******************************************************************************
 */

#ifndef _REG_SDADCDAC_MAC_H
#define _REG_SDADCDAC_MAC_H

/***************************************************
 *
 *             SDADCDAC
 *
 ***************************************************/


/*
 *  SDADCDAC_CONTROL register macros
 ****************************************************************************************
 */
#define SDADCDAC_CONTROL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_CONTROL))
#define SDADCDAC_CONTROL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_CONTROL, (value))
#define SDADCDAC_CONTROL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_CONTROL, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_CONTROL) | (value))
#define SDADCDAC_CONTROL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_CONTROL, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_CONTROL) & (~(value)))

/*
 *  SDADCDAC_ENDACFIFO bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ENDACFIFO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ENDACFIFO)
#define SDADCDAC_ENDACFIFO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ENDACFIFO, 1)
#define SDADCDAC_ENDACFIFO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ENDACFIFO, 0)

/*
 *  SDADCDAC_ENADCFIFO bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ENADCFIFO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ENADCFIFO)
#define SDADCDAC_ENADCFIFO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ENADCFIFO, 1)
#define SDADCDAC_ENADCFIFO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ENADCFIFO, 0)

/*
 *  SDADCDAC_IRQ_ENDACFIFOWMARK bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_IRQ_ENDACFIFOWMARK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_IRQ_ENDACFIFOWMARK ))
#define SDADCDAC_IRQ_ENDACFIFOWMARK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQ_ENDACFIFOWMARK, 1)
#define SDADCDAC_IRQ_ENDACFIFOWMARK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQ_ENDACFIFOWMARK, 0)

/*
 *  SDADCDAC_IRQ_ENADCFIFOWMARK bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_IRQ_ENADCFIFOWMARK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_IRQ_ENADCFIFOWMARK ))
#define SDADCDAC_IRQ_ENADCFIFOWMARK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQ_ENADCFIFOWMARK, 1)
#define SDADCDAC_IRQ_ENADCFIFOWMARK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQ_ENADCFIFOWMARK, 0)
 

/*
 *  SDADCDAC_STATUS register macros
 ****************************************************************************************
 */
#define SDADCDAC_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_STATUS))
#define SDADCDAC_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_STATUS, (value))
#define SDADCDAC_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_STATUS) | (value))
#define SDADCDAC_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_STATUS) & (~(value)))

/*
 *  SDADCDAC_DACFIFOFULL bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFOFULL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DACFIFOFULL)
#define SDADCDAC_DACFIFOFULL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACFIFOFULL, 1)
#define SDADCDAC_DACFIFOFULL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACFIFOFULL, 0)

/*
 *  SDADCDAC_DACFIFOEMPTY bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFOEMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DACFIFOEMPTY)
#define SDADCDAC_DACFIFOEMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACFIFOEMPTY, 1)
#define SDADCDAC_DACFIFOEMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACFIFOEMPTY, 0)

/*
 *  SDADCDAC_ADCFIFOFULL bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOFULL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADCFIFOFULL)
#define SDADCDAC_ADCFIFOFULL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCFIFOFULL, 1)
#define SDADCDAC_ADCFIFOFULL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCFIFOFULL, 0)

/*
 *  SDADCDAC_ADCFIFOEMPTY bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOEMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADCFIFOEMPTY)
#define SDADCDAC_ADCFIFOEMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCFIFOEMPTY, 1)
#define SDADCDAC_ADCFIFOEMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCFIFOEMPTY, 0)


/*
 *  SDADCDAC_DACFIFO register macros
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO))
#define SDADCDAC_DACFIFO_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO, (value))
#define SDADCDAC_DACFIFO_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO) | (value))
#define SDADCDAC_DACFIFO_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO) & (~(value)))

/*
 *  SDADCDAC_IRQS_DACFIFOUNDERWMARK bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_IRQS_DACFIFOUNDERWMARK)
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQS_DACFIFOUNDERWMARK, 1)
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQS_DACFIFOUNDERWMARK, 0)
/*
 *  SDADCDAC_IRQS_ADCFIFOUNDERWMARK bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_IRQS_ADCFIFOUNDERWMARK)
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQS_ADCFIFOUNDERWMARK, 1)
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_IRQS_ADCFIFOUNDERWMARK, 0)


/*
 *  SDADCDAC_DATA bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DATA)
#define SDADCDAC_DATA_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DATA, (value))


/*
 *  SDADCDAC_ADCFIFO register macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFO))

/*
 *  SDADCDAC_ADC0FIFO bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC0FIFO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0FIFO)
#define SDADCDAC_ADC0FIFO_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0FIFO, (value))

/*
 *  SDADCDAC_ADC1FIFO bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC1FIFO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1FIFO)
#define SDADCDAC_ADC1FIFO_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1FIFO, (value))


/*
 *  SDADCDAC_ADCFIFOMSB register macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOMSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOMSB))
#define SDADCDAC_ADCFIFOMSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOMSB, (value))
#define SDADCDAC_ADCFIFOMSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOMSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOMSB) | (value))
#define SDADCDAC_ADCFIFOMSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOMSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOMSB) & (~(value)))

/*
 *  SDADCDAC_ADC2FIFO bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC2FIFO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2FIFO)
#define SDADCDAC_ADC2FIFO_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2FIFO, (value))


/*
 *  SDADCDAC_BITDATA register macros
 ****************************************************************************************
 */
#define SDADCDAC_BITDATA_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_BITDATA))
#define SDADCDAC_BITDATA_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_BITDATA, (value))
#define SDADCDAC_BITDATA_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_BITDATA, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_BITDATA) | (value))
#define SDADCDAC_BITDATA_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_BITDATA, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_BITDATA) & (~(value)))

/*
 *  SDADCDAC_DACDATA bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DACDATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DACDATA)
#define SDADCDAC_DACDATA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACDATA, 1)
#define SDADCDAC_DACDATA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACDATA, 0)

/*
 *  SDADCDAC_ADC0DATA bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC0DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0DATA)
#define SDADCDAC_ADC0DATA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0DATA, 1)
#define SDADCDAC_ADC0DATA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0DATA, 0)

/*
 *  SDADCDAC_ADC1DATA bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC1DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1DATA)
#define SDADCDAC_ADC1DATA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1DATA, 1)
#define SDADCDAC_ADC1DATA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1DATA, 0)

/*
 *  SDADCDAC_ADC2DATA bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC2DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2DATA)
#define SDADCDAC_ADC2DATA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2DATA, 1)
#define SDADCDAC_ADC2DATA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2DATA, 0)

/*
 * SDADCDAC_DACFIFOWMARK register macros
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFOWMARK_GET (addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFOWMARK))
#define SDADCDAC_DACFIFOWMARK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFOWMARK, (value))
#define SDADCDAC_DACFIFOWMARK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFOWMARK, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO_WMARK) | (value))
#define SDADCDAC_DACFIFOWMARK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFOWMARK, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO_WMARK) & (~(value)))

/*
 *  SDADCDAC_DACWMARK bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DACWMARK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DACWMARK)
#define SDADCDAC_DACWMARK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DACWMARK, (value))


/*
 *  SDADCDAC_ADCFIFOWMARK register macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOWMARK_GET (addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOWMARK))
#define SDADCDAC_ADCFIFOWMARK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOWMARK, (value))
#define SDADCDAC_ADCFIFOWMARK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOWMARK, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO_WMARK) | (value))
#define SDADCDAC_ADCFIFOWMARK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ADCFIFOWMARK, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_DACFIFO_WMARK) & (~(value)))

/*
 *  SDADCDAC_ADCWMARK bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCWMARK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADCWMARK)
#define SDADCDAC_ADCWMARK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCWMARK , (value))

/*
 *  SDADCDAC_PWRDNCTRL register macros
 ****************************************************************************************
 */
#define SDADCDAC_PWRDNCTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_PWRDNCTRL))
#define SDADCDAC_PWRDNCTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_PWRDNCTRL, (value))
#define SDADCDAC_PWRDNCTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_PWRDNCTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_PWRDNCTRL) | (value))
#define SDADCDAC_PWRDNCTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_PWRDNCTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_PWRDNCTRL) & (~(value)))

/*
 *  SDADCDAC_DAC bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DAC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DAC)
#define SDADCDAC_DAC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DAC, 1)
#define SDADCDAC_DAC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DAC, 0)

/*
 *  SDADCDAC_ADC0 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0)
#define SDADCDAC_ADC0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0, 1)
#define SDADCDAC_ADC0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC0, 0)

/*
 *  SDADCDAC_ADC1 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1)
#define SDADCDAC_ADC1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1, 1)
#define SDADCDAC_ADC1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC1, 0)

/*
 *  SDADCDAC_ADC2 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADC2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2)
#define SDADCDAC_ADC2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2, 1)
#define SDADCDAC_ADC2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADC2, 0)

/*
 *  SDADCDAC_REF bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_PREF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_REF)
#define SDADCDAC_PREF_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_REF, 1)
#define SDADCDAC_PREF_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_REF, 0)


/*
 *  SDADCDAC_ANACTRL1 register macros
 ****************************************************************************************
 */
#define SDADCDAC_ANACTRL1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL1))
#define SDADCDAC_ANACTRL1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL1, (value))
#define SDADCDAC_ANACTRL1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL1, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL1) | (value))
#define SDADCDAC_ANACTRL1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL1, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL1) & (~(value)))

/*
 *  SDADCDAC_A3VEN bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_A3VEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_A3VEN)
#define SDADCDAC_A3VEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_A3VEN, 1)
#define SDADCDAC_A3VEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_A3VEN, 0)

/*
 *  SDADCDAC_SEL0 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_SEL0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_SEL0)
#define SDADCDAC_SEL0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_SEL0, 1)
#define SDADCDAC_SEL0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_SEL0, 0)

/*
 *  SDADCDAC_GAIN0 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_GAIN0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_GAIN0)
#define SDADCDAC_GAIN0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_GAIN0, (value))

/*
 *  SDADCDAC_SEL1 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_SEL1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_SEL1)
#define SDADCDAC_SEL1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_SEL1, 1)
#define SDADCDAC_SEL1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_SEL1, 0)

/*
 *  SDADCDAC_GAIN1 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_GAIN1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_GAIN1)
#define SDADCDAC_GAIN1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_GAIN1, (value))

/*
 *  SDADCDAC_SEL2 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_SEL2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_SEL2)
#define SDADCDAC_SEL2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_SEL2, 1)
#define SDADCDAC_SEL2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_SEL2, 0)

/*
 *  SDADCDAC_GAIN2 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_GAIN2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_GAIN2)
#define SDADCDAC_GAIN2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_GAIN2, (value))

/*
 *  SDADCDAC_AVDDEN bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_AVDDEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_AVDDEN)
#define SDADCDAC_AVDDEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_AVDDEN, 1)
#define SDADCDAC_AVDDEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_AVDDEN, 0)


/*
 *  SDADCDAC_ANACTRL2 register macros
 ****************************************************************************************
 */
#define SDADCDAC_ANACTRL2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL2))
#define SDADCDAC_ANACTRL2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL2, (value))
#define SDADCDAC_ANACTRL2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL2, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL2) | (value))
#define SDADCDAC_ANACTRL2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL2, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANACTRL2) & (~(value)))

/*
 *  SDADCDAC_BIAS bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_BIAS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_BIAS)
#define SDADCDAC_BIAS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_BIAS, (value))

/*
 *  SDADCDAC_TMPCO bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_TMPCO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_TMPCO)
#define SDADCDAC_TMPCO_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_TMPCO, (value))

/*
 *  SDADCDAC_REF bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_REF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_REF)
#define SDADCDAC_REF_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_REF, (value))

/*
 *  SDADCDAC_PHASE1 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_PHASE1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_PHASE1)
#define SDADCDAC_PHASE1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_PHASE1, (value))

/*
 *  SDADCDAC_PHASE2 bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_PHASE2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_PHASE2)
#define SDADCDAC_PHASE2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_PHASE2, (value))

/*
 *  SDADCDAC_PHASESTEP bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_PHASESTEP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_PHASE2)
#define SDADCDAC_PHASESTEP_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_PHASESTEP, (value))

/*
 *  SDADCDAC_ANATEST register macros
 ****************************************************************************************
 */
#define SDADCDAC_ANATEST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANATEST))
#define SDADCDAC_ANATEST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANATEST, (value))
#define SDADCDAC_ANATEST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANATEST, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANATEST) | (value))
#define SDADCDAC_ANATEST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANATEST, GET_WORD_EXCLUSIVE_BITFIELD(addr, SDADCDAC_ANATEST) & (~(value)))

/*
 *  SDADCDAC_ADCTEST bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_ADCTEST_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_ADCTEST)
#define SDADCDAC_ADCTEST_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCTEST, 1)
#define SDADCDAC_ADCTEST_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_ADCTEST, 0)

/*
 *  SDADCDAC_DI bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_DI_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_DI)
#define SDADCDAC_DI_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DI, 1)
#define SDADCDAC_DI_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_DI, 0)

/*
 *  SDADCDAC_RST bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_RST_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_RST)
#define SDADCDAC_RST_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_RST, 1)
#define SDADCDAC_RST_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_RST, 0)

/*
 *  SDADCDAC_TESTREF bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_TESTREF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_TESTREF)
#define SDADCDAC_TESTREF_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_TESTREF, 1)
#define SDADCDAC_TESTREF_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_TESTREF, 0)

/*
 *  SDADCDAC_BYPASSEN bit field macros
 ****************************************************************************************
 */
#define SDADCDAC_BYPASSEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SDADCDAC_BYPASSEN)
#define SDADCDAC_BYPASSEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_BYPASSEN, 1)
#define SDADCDAC_BYPASSEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SDADCDAC_BYPASSEN, 0)

#endif
