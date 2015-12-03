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
 * $RCSfile: gsn_reg_aadc_spec.h,v $
 *
 * Description:
 *      This file contains register specification for AADC Driver
 *
 ******************************************************************************
 */

#ifndef _REG_AADC_H
#define _REG_AADC_H

/***************************************************
 *
 *             AADC
 *
 ***************************************************/


/*
 *  COMMON_AADC instance offsets
 ****************************************************************************************
 */
#define COMMON_AADC 0x400B0000

/*
 *  AADC_CONTINUOUS register defines
 ****************************************************************************************
 */
#define AADC_CONTINUOUS_OFFSETADDRESS  0x00000000  /* RW */
#define AADC_CONTINUOUS_BITOFFSET      0
#define AADC_CONTINUOUS_BITFIELDSIZE   32
#define AADC_CONTINUOUS_BITMASK        0xFFFFFFFF
#define AADC_CONTINUOUS_INIT           0x00000000
/*
 *  AADC_ENABLE bit field defines
 ****************************************************************************************
 */
#define AADC_ENABLE_OFFSETADDRESS               AADC_CONTINUOUS_OFFSETADDRESS
#define AADC_ENABLE_BITOFFSET                   0
#define AADC_ENABLE_BITFIELDSIZE                1
#define AADC_ENABLE_BITMASK                     0x00000001
#define AADC_ENABLE_INIT                        0x0

/*
 *  AADC_MODE register defines
 ****************************************************************************************
 */
#define AADC_MODE_OFFSETADDRESS        0x00000004  /* RW */
#define AADC_MODE_BITOFFSET            0
#define AADC_MODE_BITFIELDSIZE         32
#define AADC_MODE_BITMASK              0xFFFFFFFF
#define AADC_MODE_INIT                 0x00000000
/*
 *  AADC_ADC_EN bit field defines
 ****************************************************************************************
 */
#define AADC_ADC_EN_OFFSETADDRESS               AADC_MODE_OFFSETADDRESS
#define AADC_ADC_EN_BITOFFSET                   0
#define AADC_ADC_EN_BITFIELDSIZE                1
#define AADC_ADC_EN_BITMASK                     0x00000001
#define AADC_ADC_EN_INIT                        0x0
/*
 *  AADC_ADCEN_TRIM bit field defines
 ****************************************************************************************
 */
#define AADC_ADCEN_TRIM_OFFSETADDRESS           AADC_MODE_OFFSETADDRESS
#define AADC_ADCEN_TRIM_BITOFFSET               1
#define AADC_ADCEN_TRIM_BITFIELDSIZE            1
#define AADC_ADCEN_TRIM_BITMASK                 0x00000002
#define AADC_ADCEN_TRIM_INIT                    0x0
/*
 *  AADC_ADCEN_100KHZ bit field defines
 ****************************************************************************************
 */
#define AADC_ADCEN_100KHZ_OFFSETADDRESS         AADC_MODE_OFFSETADDRESS
#define AADC_ADCEN_100KHZ_BITOFFSET             2
#define AADC_ADCEN_100KHZ_BITFIELDSIZE          1
#define AADC_ADCEN_100KHZ_BITMASK               0x00000004
#define AADC_ADCEN_100KHZ_INIT                  0x0
/*
 *  AADC_ADCEN_VDD bit field defines
 ****************************************************************************************
 */
#define AADC_ADCEN_VDD_OFFSETADDRESS            AADC_MODE_OFFSETADDRESS
#define AADC_ADCEN_VDD_BITOFFSET                3
#define AADC_ADCEN_VDD_BITFIELDSIZE             1
#define AADC_ADCEN_VDD_BITMASK                  0x00000008
#define AADC_ADCEN_VDD_INIT                     0x0
/*
 *  AADC_ADCEN_LVL bit field defines
 ****************************************************************************************
 */
#define AADC_ADCEN_LVL_OFFSETADDRESS            AADC_MODE_OFFSETADDRESS
#define AADC_ADCEN_LVL_BITOFFSET                4
#define AADC_ADCEN_LVL_BITFIELDSIZE             1
#define AADC_ADCEN_LVL_BITMASK                  0x00000010
#define AADC_ADCEN_LVL_INIT                     0x0
/*
 *  AADC_ADC_SUP1P8 bit field defines
 ****************************************************************************************
 */
#define AADC_ADC_SUP1P8_OFFSETADDRESS           AADC_MODE_OFFSETADDRESS
#define AADC_ADC_SUP1P8_BITOFFSET               5
#define AADC_ADC_SUP1P8_BITFIELDSIZE            1
#define AADC_ADC_SUP1P8_BITMASK                 0x00000020
#define AADC_ADC_SUP1P8_INIT                    0x0
/*
 *  AADC_PD_POL bit field defines
 ****************************************************************************************
 */
#define AADC_PD_POL_OFFSETADDRESS               AADC_MODE_OFFSETADDRESS
#define AADC_PD_POL_BITOFFSET                   6
#define AADC_PD_POL_BITFIELDSIZE                1
#define AADC_PD_POL_BITMASK                     0x00000040
#define AADC_PD_POL_INIT                        0x0
/*
 *  AADC_START_POL bit field defines
 ****************************************************************************************
 */
#define AADC_START_POL_OFFSETADDRESS            AADC_MODE_OFFSETADDRESS
#define AADC_START_POL_BITOFFSET                7
#define AADC_START_POL_BITFIELDSIZE             1
#define AADC_START_POL_BITMASK                  0x00000080
#define AADC_START_POL_INIT                     0x0

/*
 *  AADC_CHSEL register defines
 ****************************************************************************************
 */
#define AADC_CHSEL_OFFSETADDRESS       0x00000008  /* RW */
#define AADC_CHSEL_BITOFFSET           0
#define AADC_CHSEL_BITFIELDSIZE        32
#define AADC_CHSEL_BITMASK             0xFFFFFFFF
#define AADC_CHSEL_INIT                0x00000000
/*
 *  AADC_CHSEL_F bit field defines
 ****************************************************************************************
 */
#define AADC_CHSEL_F_OFFSETADDRESS              AADC_CHSEL_OFFSETADDRESS
#define AADC_CHSEL_F_BITOFFSET                  0
#define AADC_CHSEL_F_BITFIELDSIZE              32
#define AADC_CHSEL_F_BITMASK                    0xffffffff
#define AADC_CHSEL_F_INIT                       0x0

/*
 *  AADC_TRIM register defines
 ****************************************************************************************
 */
#define AADC_TRIM_OFFSETADDRESS        0x0000000c  /* R */
#define AADC_TRIM_BITOFFSET            0
#define AADC_TRIM_BITFIELDSIZE         32
#define AADC_TRIM_BITMASK              0xFFFFFFFF
#define AADC_TRIM_INIT                 0x00000000
/*
 *  AADC_ADC_REFTRIM bit field defines
 ****************************************************************************************
 */
#define AADC_ADC_REFTRIM_OFFSETADDRESS          AADC_TRIM_OFFSETADDRESS
#define AADC_ADC_REFTRIM_BITOFFSET              0
#define AADC_ADC_REFTRIM_BITFIELDSIZE           4
#define AADC_ADC_REFTRIM_BITMASK                0x0000000f
#define AADC_ADC_REFTRIM_INIT                   0x0
/*
 *  AADC_ADC_REFSEL bit field defines
 ****************************************************************************************
 */
#define AADC_ADC_REFSEL_OFFSETADDRESS           AADC_TRIM_OFFSETADDRESS
#define AADC_ADC_REFSEL_BITOFFSET               4
#define AADC_ADC_REFSEL_BITFIELDSIZE            1
#define AADC_ADC_REFSEL_BITMASK                 0x00000010
#define AADC_ADC_REFSEL_INIT                    0x0

/*
 *  AADC_PCYCLES register defines
 ****************************************************************************************
 */
#define AADC_PCYCLES_OFFSETADDRESS     0x00000010  /* RW */
#define AADC_PCYCLES_BITOFFSET         0
#define AADC_PCYCLES_BITFIELDSIZE      32
#define AADC_PCYCLES_BITMASK           0xFFFFFFFF
#define AADC_PCYCLES_INIT              0x00000000
/*
 *  AADC_N_PCYCLES bit field defines
 ****************************************************************************************
 */
#define AADC_N_PCYCLES_OFFSETADDRESS            AADC_PCYCLES_OFFSETADDRESS
#define AADC_N_PCYCLES_BITOFFSET                0
#define AADC_N_PCYCLES_BITFIELDSIZE             8
#define AADC_N_PCYCLES_BITMASK                  0x000000ff
#define AADC_N_PCYCLES_INIT                     0x0

/*
 *  AADC_SCYCLES register defines
 ****************************************************************************************
 */
#define AADC_SCYCLES_OFFSETADDRESS     0x00000014  /* RW */
#define AADC_SCYCLES_BITOFFSET         0
#define AADC_SCYCLES_BITFIELDSIZE      32
#define AADC_SCYCLES_BITMASK           0xFFFFFFFF
#define AADC_SCYCLES_INIT              0x00000000
/*
 *  AADC_N_SCYCLES bit field defines
 ****************************************************************************************
 */
#define AADC_N_SCYCLES_OFFSETADDRESS            AADC_SCYCLES_OFFSETADDRESS
#define AADC_N_SCYCLES_BITOFFSET                0
#define AADC_N_SCYCLES_BITFIELDSIZE             8
#define AADC_N_SCYCLES_BITMASK                  0x000000ff
#define AADC_N_SCYCLES_INIT                     0x0

/*
 *  AADC_TEST register defines
 ****************************************************************************************
 */
#define AADC_TEST_OFFSETADDRESS        0x0000001c  /* RW */
#define AADC_TEST_BITOFFSET            0
#define AADC_TEST_BITFIELDSIZE         32
#define AADC_TEST_BITMASK              0xFFFFFFFF
#define AADC_TEST_INIT                 0x00000000
/*
 *  AADC_TESTBITS bit field defines
 ****************************************************************************************
 */
#define AADC_TESTBITS_OFFSETADDRESS             AADC_TEST_OFFSETADDRESS
#define AADC_TESTBITS_BITOFFSET                 0
#define AADC_TESTBITS_BITFIELDSIZE             24
#define AADC_TESTBITS_BITMASK                   0x00ffffff
#define AADC_TESTBITS_INIT                      0x0

/*
 *  AADC_SINGLE register defines
 ****************************************************************************************
 */
#define AADC_SINGLE_OFFSETADDRESS      0x00000020  /* RW */
#define AADC_SINGLE_BITOFFSET          0
#define AADC_SINGLE_BITFIELDSIZE       32
#define AADC_SINGLE_BITMASK            0xFFFFFFFF
#define AADC_SINGLE_INIT               0x00000000
/*
 *  AADC_GOREQPULSE bit field defines
 ****************************************************************************************
 */
#define AADC_GOREQPULSE_OFFSETADDRESS           AADC_SINGLE_OFFSETADDRESS
#define AADC_GOREQPULSE_BITOFFSET               0
#define AADC_GOREQPULSE_BITFIELDSIZE            1
#define AADC_GOREQPULSE_BITMASK                 0x00000001
#define AADC_GOREQPULSE_INIT                    0x0

/*
 *  AADC_THRESHSELECT register defines
 ****************************************************************************************
 */
#define AADC_THRESHSELECT_OFFSETADDRESS 0x00000024  /* RW */
#define AADC_THRESHSELECT_BITOFFSET    0
#define AADC_THRESHSELECT_BITFIELDSIZE 32
#define AADC_THRESHSELECT_BITMASK      0xFFFFFFFF
#define AADC_THRESHSELECT_INIT         0x00000000
/*
 *  AADC_THRESH_VEC_CH0 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH0_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH0_BITOFFSET           0
#define AADC_THRESH_VEC_CH0_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH0_BITMASK             0x00000003
#define AADC_THRESH_VEC_CH0_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH1 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH1_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH1_BITOFFSET           2
#define AADC_THRESH_VEC_CH1_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH1_BITMASK             0x0000000c
#define AADC_THRESH_VEC_CH1_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH2 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH2_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH2_BITOFFSET           4
#define AADC_THRESH_VEC_CH2_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH2_BITMASK             0x00000030
#define AADC_THRESH_VEC_CH2_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH3 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH3_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH3_BITOFFSET           6
#define AADC_THRESH_VEC_CH3_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH3_BITMASK             0x000000c0
#define AADC_THRESH_VEC_CH3_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH4 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH4_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH4_BITOFFSET           8
#define AADC_THRESH_VEC_CH4_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH4_BITMASK             0x00000300
#define AADC_THRESH_VEC_CH4_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH5 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH5_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH5_BITOFFSET          10
#define AADC_THRESH_VEC_CH5_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH5_BITMASK             0x00000c00
#define AADC_THRESH_VEC_CH5_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH6 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH6_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH6_BITOFFSET          12
#define AADC_THRESH_VEC_CH6_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH6_BITMASK             0x00003000
#define AADC_THRESH_VEC_CH6_INIT                0x0
/*
 *  AADC_THRESH_VEC_CH7 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_VEC_CH7_OFFSETADDRESS       AADC_THRESHSELECT_OFFSETADDRESS
#define AADC_THRESH_VEC_CH7_BITOFFSET          14
#define AADC_THRESH_VEC_CH7_BITFIELDSIZE        2
#define AADC_THRESH_VEC_CH7_BITMASK             0x0000c000
#define AADC_THRESH_VEC_CH7_INIT                0x0

/*
 *  AADC_THRESHLO0 register defines
 ****************************************************************************************
 */
#define AADC_THRESHLO0_OFFSETADDRESS   0x00000028  /* RW */
#define AADC_THRESHLO0_BITOFFSET       0
#define AADC_THRESHLO0_BITFIELDSIZE    32
#define AADC_THRESHLO0_BITMASK         0xFFFFFFFF
#define AADC_THRESHLO0_INIT            0x00000000
/*
 *  AADC_THRESH_LO0 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_LO0_OFFSETADDRESS           AADC_THRESHLO0_OFFSETADDRESS
#define AADC_THRESH_LO0_BITOFFSET               0
#define AADC_THRESH_LO0_BITFIELDSIZE           12
#define AADC_THRESH_LO0_BITMASK                 0x00000fff
#define AADC_THRESH_LO0_INIT                    0x0

/*
 *  AADC_THRESHHI0 register defines
 ****************************************************************************************
 */
#define AADC_THRESHHI0_OFFSETADDRESS   0x0000002c  /* RW */
#define AADC_THRESHHI0_BITOFFSET       0
#define AADC_THRESHHI0_BITFIELDSIZE    32
#define AADC_THRESHHI0_BITMASK         0xFFFFFFFF
#define AADC_THRESHHI0_INIT            0x00000000
/*
 *  AADC_THRESH_HI0 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_HI0_OFFSETADDRESS           AADC_THRESHHI0_OFFSETADDRESS
#define AADC_THRESH_HI0_BITOFFSET               0
#define AADC_THRESH_HI0_BITFIELDSIZE           12
#define AADC_THRESH_HI0_BITMASK                 0x00000fff
#define AADC_THRESH_HI0_INIT                    0x0

/*
 *  AADC_THRESHLO1 register defines
 ****************************************************************************************
 */
#define AADC_THRESHLO1_OFFSETADDRESS   0x00000030  /* RW */
#define AADC_THRESHLO1_BITOFFSET       0
#define AADC_THRESHLO1_BITFIELDSIZE    32
#define AADC_THRESHLO1_BITMASK         0xFFFFFFFF
#define AADC_THRESHLO1_INIT            0x00000000
/*
 *  AADC_THRESH_LO1 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_LO1_OFFSETADDRESS           AADC_THRESHLO1_OFFSETADDRESS
#define AADC_THRESH_LO1_BITOFFSET               0
#define AADC_THRESH_LO1_BITFIELDSIZE           12
#define AADC_THRESH_LO1_BITMASK                 0x00000fff
#define AADC_THRESH_LO1_INIT                    0x0

/*
 *  AADC_THRESHHI1 register defines
 ****************************************************************************************
 */
#define AADC_THRESHHI1_OFFSETADDRESS   0x00000040  /* RW */
#define AADC_THRESHHI1_BITOFFSET       0
#define AADC_THRESHHI1_BITFIELDSIZE    32
#define AADC_THRESHHI1_BITMASK         0xFFFFFFFF
#define AADC_THRESHHI1_INIT            0x00000000
/*
 *  AADC_THRESH_HI1 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_HI1_OFFSETADDRESS           AADC_THRESHHI1_OFFSETADDRESS
#define AADC_THRESH_HI1_BITOFFSET               0
#define AADC_THRESH_HI1_BITFIELDSIZE           12
#define AADC_THRESH_HI1_BITMASK                 0x00000fff
#define AADC_THRESH_HI1_INIT                    0x0

/*
 *  AADC_THRESHLO2 register defines
 ****************************************************************************************
 */
#define AADC_THRESHLO2_OFFSETADDRESS   0x00000044  /* RW */
#define AADC_THRESHLO2_BITOFFSET       0
#define AADC_THRESHLO2_BITFIELDSIZE    32
#define AADC_THRESHLO2_BITMASK         0xFFFFFFFF
#define AADC_THRESHLO2_INIT            0x00000000
/*
 *  AADC_THRESH_LO2 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_LO2_OFFSETADDRESS           AADC_THRESHLO2_OFFSETADDRESS
#define AADC_THRESH_LO2_BITOFFSET               0
#define AADC_THRESH_LO2_BITFIELDSIZE           12
#define AADC_THRESH_LO2_BITMASK                 0x00000fff
#define AADC_THRESH_LO2_INIT                    0x0

/*
 *  AADC_THRESHHI2 register defines
 ****************************************************************************************
 */
#define AADC_THRESHHI2_OFFSETADDRESS   0x00000048  /* RW */
#define AADC_THRESHHI2_BITOFFSET       0
#define AADC_THRESHHI2_BITFIELDSIZE    32
#define AADC_THRESHHI2_BITMASK         0xFFFFFFFF
#define AADC_THRESHHI2_INIT            0x00000000
/*
 *  AADC_THRESH_HI2 bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_HI2_OFFSETADDRESS           AADC_THRESHHI2_OFFSETADDRESS
#define AADC_THRESH_HI2_BITOFFSET               0
#define AADC_THRESH_HI2_BITFIELDSIZE           12
#define AADC_THRESH_HI2_BITMASK                 0x00000fff
#define AADC_THRESH_HI2_INIT                    0x0

/*
 *  AADC_DATA register defines
 ****************************************************************************************
 */
#define AADC_DATA_OFFSETADDRESS        0x00000050  /* RW */
#define AADC_DATA_BITOFFSET            0
#define AADC_DATA_BITFIELDSIZE         32
#define AADC_DATA_BITMASK              0xFFFFFFFF
#define AADC_DATA_INIT                 0x00000000
/*
 *  AADC_BUFF bit field defines
 ****************************************************************************************
 */
#define AADC_BUFF_OFFSETADDRESS                 AADC_DATA_OFFSETADDRESS
#define AADC_BUFF_BITOFFSET                     0
#define AADC_BUFF_BITFIELDSIZE                 12
#define AADC_BUFF_BITMASK                       0x00000fff
#define AADC_BUFF_INIT                          0x0

/*
 *  AADC_FIFOIDLEPTN register defines
 ****************************************************************************************
 */
#define AADC_FIFOIDLEPTN_OFFSETADDRESS 0x00000054  /* RW */
#define AADC_FIFOIDLEPTN_BITOFFSET     0
#define AADC_FIFOIDLEPTN_BITFIELDSIZE  32
#define AADC_FIFOIDLEPTN_BITMASK       0xFFFFFFFF
#define AADC_FIFOIDLEPTN_INIT          0x00000000
/*
 *  AADC_IDL_PTRN bit field defines
 ****************************************************************************************
 */
#define AADC_IDL_PTRN_OFFSETADDRESS             AADC_FIFOIDLEPTN_OFFSETADDRESS
#define AADC_IDL_PTRN_BITOFFSET                 0
#define AADC_IDL_PTRN_BITFIELDSIZE             12
#define AADC_IDL_PTRN_BITMASK                   0x00000fff
#define AADC_IDL_PTRN_INIT                      0x0

/*
 *  AADC_IRQ_FIFO_THRESH register defines
 ****************************************************************************************
 */
#define AADC_IRQ_FIFO_THRESH_OFFSETADDRESS 0x00000058  /* RW */
#define AADC_IRQ_FIFO_THRESH_BITOFFSET 0
#define AADC_IRQ_FIFO_THRESH_BITFIELDSIZE 32
#define AADC_IRQ_FIFO_THRESH_BITMASK   0xFFFFFFFF
#define AADC_IRQ_FIFO_THRESH_INIT      0x00000000
/*
 *  AADC_THRESH bit field defines
 ****************************************************************************************
 */
#define AADC_THRESH_OFFSETADDRESS               AADC_IRQ_FIFO_THRESH_OFFSETADDRESS
#define AADC_THRESH_BITOFFSET                   0
#define AADC_THRESH_BITFIELDSIZE               12
#define AADC_THRESH_BITMASK                     0x00000fff
#define AADC_THRESH_INIT                        0x0

/*
 *  AADC_IRQ_STATUS register defines
 ****************************************************************************************
 */
#define AADC_IRQ_STATUS_OFFSETADDRESS  0x00000060  /* RW */
#define AADC_IRQ_STATUS_BITOFFSET      0
#define AADC_IRQ_STATUS_BITFIELDSIZE   32
#define AADC_IRQ_STATUS_BITMASK        0xFFFFFFFF
#define AADC_IRQ_STATUS_INIT           0x00000000
/*
 *  AADC_NOTEMPTY bit field defines
 ****************************************************************************************
 */
#define AADC_NOTEMPTY_OFFSETADDRESS             AADC_IRQ_STATUS_OFFSETADDRESS
#define AADC_NOTEMPTY_BITOFFSET                 0
#define AADC_NOTEMPTY_BITFIELDSIZE              1
#define AADC_NOTEMPTY_BITMASK                   0x00000001
#define AADC_NOTEMPTY_INIT                      0x0
/*
 *  AADC_OVERTHRESH bit field defines
 ****************************************************************************************
 */
#define AADC_OVERTHRESH_OFFSETADDRESS           AADC_IRQ_STATUS_OFFSETADDRESS
#define AADC_OVERTHRESH_BITOFFSET               1
#define AADC_OVERTHRESH_BITFIELDSIZE            1
#define AADC_OVERTHRESH_BITMASK                 0x00000002
#define AADC_OVERTHRESH_INIT                    0x0

/*
 *  AADC_IRQ_MASK register defines
 ****************************************************************************************
 */
#define AADC_IRQ_MASK_OFFSETADDRESS    0x00000064  /* RW */
#define AADC_IRQ_MASK_BITOFFSET        0
#define AADC_IRQ_MASK_BITFIELDSIZE     32
#define AADC_IRQ_MASK_BITMASK          0xFFFFFFFF
#define AADC_IRQ_MASK_INIT             0x00000000
/*
 *  AADC_MASK bit field defines
 ****************************************************************************************
 */
#define AADC_MASK_OFFSETADDRESS                 AADC_IRQ_MASK_OFFSETADDRESS
#define AADC_MASK_BITOFFSET                     0
#define AADC_MASK_BITFIELDSIZE                  1
#define AADC_MASK_BITMASK                       0x00000001
#define AADC_MASK_INIT                          0x0

/*
 *  AADC_IRQ_CLEAR register defines
 ****************************************************************************************
 */
#define AADC_IRQ_CLEAR_OFFSETADDRESS   0x00000068  /* RW */
#define AADC_IRQ_CLEAR_BITOFFSET       0
#define AADC_IRQ_CLEAR_BITFIELDSIZE    32
#define AADC_IRQ_CLEAR_BITMASK         0xFFFFFFFF
#define AADC_IRQ_CLEAR_INIT            0x00000000
/*
 *  AADC_CLEAR bit field defines
 ****************************************************************************************
 */
#define AADC_CLEAR_OFFSETADDRESS                AADC_IRQ_CLEAR_OFFSETADDRESS
#define AADC_CLEAR_BITOFFSET                    0
#define AADC_CLEAR_BITFIELDSIZE                 1
#define AADC_CLEAR_BITMASK                      0x00000001
#define AADC_CLEAR_INIT                         0x0

/*
 *  AADC_IRQ_SET register defines
 ****************************************************************************************
 */
#define AADC_IRQ_SET_OFFSETADDRESS     0x0000006c  /* RW */
#define AADC_IRQ_SET_BITOFFSET         0
#define AADC_IRQ_SET_BITFIELDSIZE      32
#define AADC_IRQ_SET_BITMASK           0xFFFFFFFF
#define AADC_IRQ_SET_INIT              0x00000000
/*
 *  AADC_SET bit field defines
 ****************************************************************************************
 */
#define AADC_SET_OFFSETADDRESS                  AADC_IRQ_SET_OFFSETADDRESS
#define AADC_SET_BITOFFSET                      0
#define AADC_SET_BITFIELDSIZE                   1
#define AADC_SET_BITMASK                        0x00000001
#define AADC_SET_INIT                           0x0

/*
 *  AADC_PERIODIC_CTL register defines
 ****************************************************************************************
 */
#define AADC_PERIODIC_CTL_OFFSETADDRESS    0x00000070  /* RW */
#define AADC_PERIODIC_CTL_BITOFFSET        0
#define AADC_PERIODIC_CTL_BITFIELDSIZE     32
#define AADC_PERIODIC_CTL_BITMASK          0xFFFFFFFF
#define AADC_PERIODIC_CTL_INIT             0x00000000
/*
 *  AADC_COUNTEREN bit field defines
 ****************************************************************************************
 */
#define AADC_COUNTEREN_OFFSETADDRESS            AADC_PERIODIC_CTL_OFFSETADDRESS
#define AADC_COUNTEREN_BITOFFSET                0
#define AADC_COUNTEREN_BITFIELDSIZE             1
#define AADC_COUNTEREN_BITMASK                  0x00000001
#define AADC_COUNTEREN_INIT                     0x0
/*
 *  AADC_MASKEN bit field defines
 ****************************************************************************************
 */
#define AADC_MASKEN_OFFSETADDRESS               AADC_PERIODIC_CTL_OFFSETADDRESS
#define AADC_MASKEN_BITOFFSET                   1
#define AADC_MASKEN_BITFIELDSIZE                1
#define AADC_MASKEN_BITMASK                     0x00000002
#define AADC_MASKEN_INIT                        0x0

/*
 *  AADC_PERIODIC_VAL register defines
 ****************************************************************************************
 */
#define AADC_PERIODIC_VAL_OFFSETADDRESS 0x00000074  /* RW */
#define AADC_PERIODIC_VAL_BITOFFSET    0
#define AADC_PERIODIC_VAL_BITFIELDSIZE 32
#define AADC_PERIODIC_VAL_BITMASK      0xFFFFFFFF
#define AADC_PERIODIC_VAL_INIT         0x00000000
/*
 *  AADC_LOADVAL bit field defines
 ****************************************************************************************
 */
#define AADC_LOADVAL_OFFSETADDRESS              AADC_PERIODIC_VAL_OFFSETADDRESS
#define AADC_LOADVAL_BITOFFSET                  0
#define AADC_LOADVAL_BITFIELDSIZE              32
#define AADC_LOADVAL_BITMASK                    0xffffffff
#define AADC_LOADVAL_INIT                       0x0
#endif
