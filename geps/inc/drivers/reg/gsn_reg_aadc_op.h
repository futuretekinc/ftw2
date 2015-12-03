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
 * $RCSfile: gsn_reg_aadc_op.h,v $
 *
 * Description:
 *      This file contains register macros for AADC Driver
 *
 ******************************************************************************
 */

#ifndef _REG_AADC_MAC_H
#define _REG_AADC_MAC_H

/***************************************************
 *
 *             AADC
 *
 ***************************************************/


/*
 *  AADC_CONTINUOUS register macros
 ****************************************************************************************
 */
#define AADC_CONTINUOUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CONTINUOUS))
#define AADC_CONTINUOUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CONTINUOUS, (value))
#define AADC_CONTINUOUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CONTINUOUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CONTINUOUS) | (value))
#define AADC_CONTINUOUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CONTINUOUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CONTINUOUS) & (~(value)))

/*
 *  AADC_ENABLE bit field macros
 ****************************************************************************************
 */
#define AADC_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ENABLE)
#define AADC_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ENABLE, 1)
#define AADC_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ENABLE, 0)


/*
 *  AADC_MODE register macros
 ****************************************************************************************
 */
#define AADC_MODE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_MODE))
#define AADC_MODE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_MODE, (value))
#define AADC_MODE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_MODE, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_MODE) | (value))
#define AADC_MODE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_MODE, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_MODE) & (~(value)))

/*
 *  AADC_ADC_EN bit field macros
 ****************************************************************************************
 */
#define AADC_ADC_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADC_EN)
#define AADC_ADC_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_EN, 1)
#define AADC_ADC_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_EN, 0)

/*
 *  AADC_ADCEN_TRIM bit field macros
 ****************************************************************************************
 */
#define AADC_ADCEN_TRIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADCEN_TRIM)
#define AADC_ADCEN_TRIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_TRIM, 1)
#define AADC_ADCEN_TRIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_TRIM, 0)

/*
 *  AADC_ADCEN_100KHZ bit field macros
 ****************************************************************************************
 */
#define AADC_ADCEN_100KHZ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADCEN_100KHZ)
#define AADC_ADCEN_100KHZ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_100KHZ, 1)
#define AADC_ADCEN_100KHZ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_100KHZ, 0)

/*
 *  AADC_ADCEN_VDD bit field macros
 ****************************************************************************************
 */
#define AADC_ADCEN_VDD_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADCEN_VDD)
#define AADC_ADCEN_VDD_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_VDD, 1)
#define AADC_ADCEN_VDD_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_VDD, 0)

/*
 *  AADC_ADCEN_LVL bit field macros
 ****************************************************************************************
 */
#define AADC_ADCEN_LVL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADCEN_LVL)
#define AADC_ADCEN_LVL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_LVL, 1)
#define AADC_ADCEN_LVL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADCEN_LVL, 0)

/*
 *  AADC_ADC_SUP1P8 bit field macros
 ****************************************************************************************
 */
#define AADC_ADC_SUP1P8_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADC_SUP1P8)
#define AADC_ADC_SUP1P8_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_SUP1P8, 1)
#define AADC_ADC_SUP1P8_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_SUP1P8, 0)

/*
 *  AADC_PD_POL bit field macros
 ****************************************************************************************
 */
#define AADC_PD_POL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_PD_POL)
#define AADC_PD_POL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_PD_POL, 1)
#define AADC_PD_POL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_PD_POL, 0)

/*
 *  AADC_START_POL bit field macros
 ****************************************************************************************
 */
#define AADC_START_POL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_START_POL)
#define AADC_START_POL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_START_POL, 1)
#define AADC_START_POL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_START_POL, 0)


/*
 *  AADC_CHSEL register macros
 ****************************************************************************************
 */
#define AADC_CHSEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CHSEL))
#define AADC_CHSEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CHSEL, (value))
#define AADC_CHSEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CHSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CHSEL) | (value))
#define AADC_CHSEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CHSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_CHSEL) & (~(value)))

/*
 *  AADC_CHSEL_F bit field macros
 ****************************************************************************************
 */
#define AADC_CHSEL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_CHSEL_F)
#define AADC_CHSEL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_CHSEL_F, (value))


/*
 *  AADC_TRIM register macros
 ****************************************************************************************
 */
#define AADC_TRIM_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TRIM))

/*
 *  AADC_ADC_REFTRIM bit field macros
 ****************************************************************************************
 */
#define AADC_ADC_REFTRIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADC_REFTRIM)
#define AADC_ADC_REFTRIM_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_REFTRIM, (value))

/*
 *  AADC_ADC_REFSEL bit field macros
 ****************************************************************************************
 */
#define AADC_ADC_REFSEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_ADC_REFSEL)
#define AADC_ADC_REFSEL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_REFSEL, 1)
#define AADC_ADC_REFSEL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_ADC_REFSEL, 0)


/*
 *  AADC_PCYCLES register macros
 ****************************************************************************************
 */
#define AADC_PCYCLES_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PCYCLES))
#define AADC_PCYCLES_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PCYCLES, (value))
#define AADC_PCYCLES_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PCYCLES, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PCYCLES) | (value))
#define AADC_PCYCLES_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PCYCLES, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PCYCLES) & (~(value)))

/*
 *  AADC_N_PCYCLES bit field macros
 ****************************************************************************************
 */
#define AADC_N_PCYCLES_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_N_PCYCLES)
#define AADC_N_PCYCLES_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_N_PCYCLES, (value))


/*
 *  AADC_SCYCLES register macros
 ****************************************************************************************
 */
#define AADC_SCYCLES_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SCYCLES))
#define AADC_SCYCLES_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SCYCLES, (value))
#define AADC_SCYCLES_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SCYCLES, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SCYCLES) | (value))
#define AADC_SCYCLES_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SCYCLES, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SCYCLES) & (~(value)))

/*
 *  AADC_N_SCYCLES bit field macros
 ****************************************************************************************
 */
#define AADC_N_SCYCLES_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_N_SCYCLES)
#define AADC_N_SCYCLES_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_N_SCYCLES, (value))


/*
 *  AADC_TEST register macros
 ****************************************************************************************
 */
#define AADC_TEST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TEST))
#define AADC_TEST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TEST, (value))
#define AADC_TEST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TEST, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TEST) | (value))
#define AADC_TEST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TEST, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_TEST) & (~(value)))

/*
 *  AADC_TESTBITS bit field macros
 ****************************************************************************************
 */
#define AADC_TESTBITS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_TESTBITS)
#define AADC_TESTBITS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_TESTBITS, (value))


/*
 *  AADC_SINGLE register macros
 ****************************************************************************************
 */
#define AADC_SINGLE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SINGLE))
#define AADC_SINGLE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SINGLE, (value))
#define AADC_SINGLE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SINGLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SINGLE) | (value))
#define AADC_SINGLE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SINGLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_SINGLE) & (~(value)))

/*
 *  AADC_GOREQPULSE bit field macros
 ****************************************************************************************
 */
#define AADC_GOREQPULSE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_GOREQPULSE)
#define AADC_GOREQPULSE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_GOREQPULSE, 1)
#define AADC_GOREQPULSE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_GOREQPULSE, 0)


/*
 *  AADC_THRESHSELECT register macros
 ****************************************************************************************
 */
#define AADC_THRESHSELECT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHSELECT))
#define AADC_THRESHSELECT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHSELECT, (value))
#define AADC_THRESHSELECT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHSELECT, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHSELECT) | (value))
#define AADC_THRESHSELECT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHSELECT, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHSELECT) & (~(value)))

/*
 *  AADC_THRESH_VEC_CH0 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH0)
#define AADC_THRESH_VEC_CH0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH0, (value))

/*
 *  AADC_THRESH_VEC_CH1 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH1)
#define AADC_THRESH_VEC_CH1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH1, (value))

/*
 *  AADC_THRESH_VEC_CH2 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH2)
#define AADC_THRESH_VEC_CH2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH2, (value))

/*
 *  AADC_THRESH_VEC_CH3 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH3_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH3)
#define AADC_THRESH_VEC_CH3_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH3, (value))

/*
 *  AADC_THRESH_VEC_CH4 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH4_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH4)
#define AADC_THRESH_VEC_CH4_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH4, (value))

/*
 *  AADC_THRESH_VEC_CH5 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH5_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH5)
#define AADC_THRESH_VEC_CH5_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH5, (value))

/*
 *  AADC_THRESH_VEC_CH6 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH6_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH6)
#define AADC_THRESH_VEC_CH6_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH6, (value))

/*
 *  AADC_THRESH_VEC_CH7 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH7_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH7)
#define AADC_THRESH_VEC_CH7_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_VEC_CH7, (value))


/*
 *  AADC_THRESHLO0 register macros
 ****************************************************************************************
 */
#define AADC_THRESHLO0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO0))
#define AADC_THRESHLO0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO0, (value))
#define AADC_THRESHLO0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO0, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO0) | (value))
#define AADC_THRESHLO0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO0, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO0) & (~(value)))

/*
 *  AADC_THRESH_LO0 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_LO0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_LO0)
#define AADC_THRESH_LO0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_LO0, (value))


/*
 *  AADC_THRESHHI0 register macros
 ****************************************************************************************
 */
#define AADC_THRESHHI0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI0))
#define AADC_THRESHHI0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI0, (value))
#define AADC_THRESHHI0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI0, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI0) | (value))
#define AADC_THRESHHI0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI0, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI0) & (~(value)))

/*
 *  AADC_THRESH_HI0 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_HI0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_HI0)
#define AADC_THRESH_HI0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_HI0, (value))


/*
 *  AADC_THRESHLO1 register macros
 ****************************************************************************************
 */
#define AADC_THRESHLO1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO1))
#define AADC_THRESHLO1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO1, (value))
#define AADC_THRESHLO1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO1, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO1) | (value))
#define AADC_THRESHLO1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO1, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO1) & (~(value)))

/*
 *  AADC_THRESH_LO1 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_LO1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_LO1)
#define AADC_THRESH_LO1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_LO1, (value))


/*
 *  AADC_THRESHHI1 register macros
 ****************************************************************************************
 */
#define AADC_THRESHHI1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI1))
#define AADC_THRESHHI1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI1, (value))
#define AADC_THRESHHI1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI1, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI1) | (value))
#define AADC_THRESHHI1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI1, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI1) & (~(value)))

/*
 *  AADC_THRESH_HI1 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_HI1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_HI1)
#define AADC_THRESH_HI1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_HI1, (value))


/*
 *  AADC_THRESHLO2 register macros
 ****************************************************************************************
 */
#define AADC_THRESHLO2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO2))
#define AADC_THRESHLO2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO2, (value))
#define AADC_THRESHLO2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO2, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO2) | (value))
#define AADC_THRESHLO2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO2, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHLO2) & (~(value)))

/*
 *  AADC_THRESH_LO2 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_LO2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_LO2)
#define AADC_THRESH_LO2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_LO2, (value))


/*
 *  AADC_THRESHHI2 register macros
 ****************************************************************************************
 */
#define AADC_THRESHHI2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI2))
#define AADC_THRESHHI2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI2, (value))
#define AADC_THRESHHI2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI2, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI2) | (value))
#define AADC_THRESHHI2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI2, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_THRESHHI2) & (~(value)))

/*
 *  AADC_THRESH_HI2 bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_HI2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH_HI2)
#define AADC_THRESH_HI2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH_HI2, (value))


/*
 *  AADC_DATA register macros
 ****************************************************************************************
 */
#define AADC_DATA_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_DATA))
#define AADC_DATA_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_DATA, (value))
#define AADC_DATA_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_DATA, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_DATA) | (value))
#define AADC_DATA_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_DATA, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_DATA) & (~(value)))

/*
 *  AADC_BUFF bit field macros
 ****************************************************************************************
 */
#define AADC_BUFF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_BUFF)
#define AADC_BUFF_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_BUFF, (value))


/*
 *  AADC_FIFOIDLEPTN register macros
 ****************************************************************************************
 */
#define AADC_FIFOIDLEPTN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_FIFOIDLEPTN))
#define AADC_FIFOIDLEPTN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_FIFOIDLEPTN, (value))
#define AADC_FIFOIDLEPTN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_FIFOIDLEPTN, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_FIFOIDLEPTN) | (value))
#define AADC_FIFOIDLEPTN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_FIFOIDLEPTN, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_FIFOIDLEPTN) & (~(value)))

/*
 *  AADC_IDL_PTRN bit field macros
 ****************************************************************************************
 */
#define AADC_IDL_PTRN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_IDL_PTRN)
#define AADC_IDL_PTRN_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_IDL_PTRN, (value))


/*
 *  AADC_IRQ_FIFO_THRESH register macros
 ****************************************************************************************
 */
#define AADC_IRQ_FIFO_THRESH_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_FIFO_THRESH))
#define AADC_IRQ_FIFO_THRESH_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_FIFO_THRESH, (value))
#define AADC_IRQ_FIFO_THRESH_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_FIFO_THRESH, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_FIFO_THRESH) | (value))
#define AADC_IRQ_FIFO_THRESH_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_FIFO_THRESH, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_FIFO_THRESH) & (~(value)))

/*
 *  AADC_THRESH bit field macros
 ****************************************************************************************
 */
#define AADC_THRESH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_THRESH)
#define AADC_THRESH_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_THRESH, (value))


/*
 *  AADC_IRQ_STATUS register macros
 ****************************************************************************************
 */
#define AADC_IRQ_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_STATUS))
#define AADC_IRQ_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_STATUS, (value))
#define AADC_IRQ_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_STATUS) | (value))
#define AADC_IRQ_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_STATUS) & (~(value)))

/*
 *  AADC_NOTEMPTY bit field macros
 ****************************************************************************************
 */
#define AADC_NOTEMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_NOTEMPTY)
#define AADC_NOTEMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_NOTEMPTY, 1)
#define AADC_NOTEMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_NOTEMPTY, 0)

/*
 *  AADC_OVERTHRESH bit field macros
 ****************************************************************************************
 */
#define AADC_OVERTHRESH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_OVERTHRESH)
#define AADC_OVERTHRESH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_OVERTHRESH, 1)
#define AADC_OVERTHRESH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_OVERTHRESH, 0)


/*
 *  AADC_IRQ_MASK register macros
 ****************************************************************************************
 */
#define AADC_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_MASK))
#define AADC_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_MASK, (value))
#define AADC_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_MASK) | (value))
#define AADC_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_MASK) & (~(value)))

/*
 *  AADC_MASK bit field macros
 ****************************************************************************************
 */
#define AADC_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_MASK)
#define AADC_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_MASK, 1)
#define AADC_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_MASK, 0)


/*
 *  AADC_IRQ_CLEAR register macros
 ****************************************************************************************
 */
#define AADC_IRQ_CLEAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_CLEAR))
#define AADC_IRQ_CLEAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_CLEAR, (value))
#define AADC_IRQ_CLEAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_CLEAR) | (value))
#define AADC_IRQ_CLEAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_CLEAR) & (~(value)))

/*
 *  AADC_CLEAR bit field macros
 ****************************************************************************************
 */
#define AADC_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_CLEAR)
#define AADC_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_CLEAR, 1)
#define AADC_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_CLEAR, 0)


/*
 *  AADC_IRQ_SET register macros
 ****************************************************************************************
 */
#define AADC_IRQ_SET_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_SET))
#define AADC_IRQ_SET_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_SET, (value))
#define AADC_IRQ_SET_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_SET) | (value))
#define AADC_IRQ_SET_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_IRQ_SET) & (~(value)))

/*
 *  AADC_SET bit field macros
 ****************************************************************************************
 */
#define AADC_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_SET)
#define AADC_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_SET, 1)
#define AADC_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_SET, 0)


/*
 *  AADC_PERIODIC_CTL register macros
 ****************************************************************************************
 */
#define AADC_PERIODIC_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_CTL))
#define AADC_PERIODIC_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_CTL, (value))
#define AADC_PERIODIC_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_CTL) | (value))
#define AADC_PERIODIC_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_CTL) & (~(value)))

/*
 *  AADC_COUNTEREN bit field macros
 ****************************************************************************************
 */
#define AADC_COUNTEREN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_COUNTEREN)
#define AADC_COUNTEREN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_COUNTEREN, 1)
#define AADC_COUNTEREN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_COUNTEREN, 0)

/*
 *  AADC_MASKEN bit field macros
 ****************************************************************************************
 */
#define AADC_MASKEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_MASKEN)
#define AADC_MASKEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_MASKEN, 1)
#define AADC_MASKEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, AADC_MASKEN, 0)


/*
 *  AADC_PERIODIC_VAL register macros
 ****************************************************************************************
 */
#define AADC_PERIODIC_VAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_VAL))
#define AADC_PERIODIC_VAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_VAL, (value))
#define AADC_PERIODIC_VAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_VAL) | (value))
#define AADC_PERIODIC_VAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, AADC_PERIODIC_VAL) & (~(value)))

/*
 *  AADC_LOADVAL bit field macros
 ****************************************************************************************
 */
#define AADC_LOADVAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, AADC_LOADVAL)
#define AADC_LOADVAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, AADC_LOADVAL, (value))

#endif
