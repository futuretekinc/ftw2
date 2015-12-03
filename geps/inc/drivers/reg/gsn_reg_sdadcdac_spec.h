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
 * $RCSfile: gsn_reg_sdadcdac_spec.h,v $
 *
 * Description:
 *      This file contains register specification for SD_ADC_DAC Driver
 *
 ******************************************************************************
 */

#ifndef _REG_SDADCDAC_H
#define _REG_SDADCDAC_H

/***************************************************
 *
 *             SDADCDAC
 *
 ***************************************************/


/*
 *  COMMON_SDADCDAC instance offsets
 ****************************************************************************************
 */
#define COMMON_SDADCDAC 0x40140000

/*
 *  SDADCDAC_CONTROL register defines
 ****************************************************************************************
 */
#define SDADCDAC_CONTROL_OFFSETADDRESS 0x00000000  /* RW */
#define SDADCDAC_CONTROL_BITOFFSET     0
#define SDADCDAC_CONTROL_BITFIELDSIZE  32
#define SDADCDAC_CONTROL_BITMASK       0xFFFFFFFF
#define SDADCDAC_CONTROL_INIT          0x00000000
/*
 *  SDADCDAC_ENDACFIFO bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ENDACFIFO_OFFSETADDRESS        SDADCDAC_CONTROL_OFFSETADDRESS
#define SDADCDAC_ENDACFIFO_BITOFFSET            0
#define SDADCDAC_ENDACFIFO_BITFIELDSIZE         1
#define SDADCDAC_ENDACFIFO_BITMASK              0x00000001
#define SDADCDAC_ENDACFIFO_INIT                 0x0
/*
 *  SDADCDAC_ENADCFIFO bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ENADCFIFO_OFFSETADDRESS        SDADCDAC_CONTROL_OFFSETADDRESS
#define SDADCDAC_ENADCFIFO_BITOFFSET            1
#define SDADCDAC_ENADCFIFO_BITFIELDSIZE         1
#define SDADCDAC_ENADCFIFO_BITMASK              0x00000002
#define SDADCDAC_ENADCFIFO_INIT                 0x0

/*
 *  SDADCDAC_IRQ_ENDACFIFOWMARK bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_IRQ_ENDACFIFOWMARK_OFFSETADDRESS        SDADCDAC_CONTROL_OFFSETADDRESS
#define SDADCDAC_IRQ_ENDACFIFOWMARK_BITOFFSET            2
#define SDADCDAC_IRQ_ENDACFIFOWMARK_BITFIELDSIZE         1
#define SDADCDAC_IRQ_ENDACFIFOWMARK_BITMASK              0x00000003
#define SDADCDAC_IRQ_ENDACFIFOWMARK_INIT                 0x0

/*
 *  SDADCDAC_IRQ_ENADCFIFOWMARK bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_IRQ_ENADCFIFOWMARK_OFFSETADDRESS        SDADCDAC_CONTROL_OFFSETADDRESS
#define SDADCDAC_IRQ_ENADCFIFOWMARK_BITOFFSET            3
#define SDADCDAC_IRQ_ENADCFIFOWMARK_BITFIELDSIZE         1
#define SDADCDAC_IRQ_ENADCFIFOWMARK_BITMASK              0x00000004
#define SDADCDAC_IRQ_ENADCFIFOWMARK_INIT                 0x0


/*
 *  SDADCDAC_STATUS register defines
 ****************************************************************************************
 */
#define SDADCDAC_STATUS_OFFSETADDRESS  0x00000004  /* RW */
#define SDADCDAC_STATUS_BITOFFSET      0
#define SDADCDAC_STATUS_BITFIELDSIZE   32
#define SDADCDAC_STATUS_BITMASK        0xFFFFFFFF
#define SDADCDAC_STATUS_INIT           0x00000000
/*
 *  SDADCDAC_DACFIFOFULL bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFOFULL_OFFSETADDRESS      SDADCDAC_STATUS_OFFSETADDRESS
#define SDADCDAC_DACFIFOFULL_BITOFFSET          0
#define SDADCDAC_DACFIFOFULL_BITFIELDSIZE       1
#define SDADCDAC_DACFIFOFULL_BITMASK            0x00000001
#define SDADCDAC_DACFIFOFULL_INIT               0x0
/*
 *  SDADCDAC_DACFIFOEMPTY bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFOEMPTY_OFFSETADDRESS     SDADCDAC_STATUS_OFFSETADDRESS
#define SDADCDAC_DACFIFOEMPTY_BITOFFSET         1
#define SDADCDAC_DACFIFOEMPTY_BITFIELDSIZE      1
#define SDADCDAC_DACFIFOEMPTY_BITMASK           0x00000002
#define SDADCDAC_DACFIFOEMPTY_INIT              0x0
/*
 *  SDADCDAC_ADCFIFOFULL bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOFULL_OFFSETADDRESS      SDADCDAC_STATUS_OFFSETADDRESS
#define SDADCDAC_ADCFIFOFULL_BITOFFSET          2
#define SDADCDAC_ADCFIFOFULL_BITFIELDSIZE       1
#define SDADCDAC_ADCFIFOFULL_BITMASK            0x00000004
#define SDADCDAC_ADCFIFOFULL_INIT               0x0
/*
 *  SDADCDAC_ADCFIFOEMPTY bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOEMPTY_OFFSETADDRESS     SDADCDAC_STATUS_OFFSETADDRESS
#define SDADCDAC_ADCFIFOEMPTY_BITOFFSET         3
#define SDADCDAC_ADCFIFOEMPTY_BITFIELDSIZE      1
#define SDADCDAC_ADCFIFOEMPTY_BITMASK           0x00000008
#define SDADCDAC_ADCFIFOEMPTY_INIT              0x0


/*
 *  SDADCDAC_IRQS_DACFIFOUNDERWMARK bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_OFFSETADDRESS     SDADCDAC_STATUS_OFFSETADDRESS
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_BITOFFSET         4
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_BITFIELDSIZE      1
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_BITMASK           0x00000010
#define SDADCDAC_IRQS_DACFIFOUNDERWMARK_INIT              0x0

/*
 *  SDADCDAC_IRQS_ADCFIFOUNDERWMARK bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_OFFSETADDRESS     SDADCDAC_STATUS_OFFSETADDRESS
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_BITOFFSET         5
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_BITFIELDSIZE      1
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_BITMASK           0x00000020
#define SDADCDAC_IRQS_ADCFIFOVERWMARK_INIT              0x0

/*
 *  SDADCDAC_DACFIFO register defines
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFO_OFFSETADDRESS 0x00000008  /* RW */
#define SDADCDAC_DACFIFO_BITOFFSET     0
#define SDADCDAC_DACFIFO_BITFIELDSIZE  32
#define SDADCDAC_DACFIFO_BITMASK       0xFFFFFFFF
#define SDADCDAC_DACFIFO_INIT          0x00000000

/*
 *  SDADCDAC_DATA bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DATA_OFFSETADDRESS             SDADCDAC_DACFIFO_OFFSETADDRESS
#define SDADCDAC_DATA_BITOFFSET                 0
#define SDADCDAC_DATA_BITFIELDSIZE             16
#define SDADCDAC_DATA_BITMASK                   0x0000ffff
#define SDADCDAC_DATA_INIT                      0x0

/*
 *  SDADCDAC_ADCFIFO register defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFO_OFFSETADDRESS 0x0000000c  /* R */
#define SDADCDAC_ADCFIFO_BITOFFSET     0
#define SDADCDAC_ADCFIFO_BITFIELDSIZE  32
#define SDADCDAC_ADCFIFO_BITMASK       0xFFFFFFFF
#define SDADCDAC_ADCFIFO_INIT          0x00000000
/*
 *  SDADCDAC_ADC0FIFO bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC0FIFO_OFFSETADDRESS         SDADCDAC_ADCFIFO_OFFSETADDRESS
#define SDADCDAC_ADC0FIFO_BITOFFSET             0
#define SDADCDAC_ADC0FIFO_BITFIELDSIZE         16
#define SDADCDAC_ADC0FIFO_BITMASK               0x0000ffff
#define SDADCDAC_ADC0FIFO_INIT                  0x0
/*
 *  SDADCDAC_ADC1FIFO bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC1FIFO_OFFSETADDRESS         SDADCDAC_ADCFIFO_OFFSETADDRESS
#define SDADCDAC_ADC1FIFO_BITOFFSET            16
#define SDADCDAC_ADC1FIFO_BITFIELDSIZE         16
#define SDADCDAC_ADC1FIFO_BITMASK               0xffff0000
#define SDADCDAC_ADC1FIFO_INIT                  0x0

/*
 *  SDADCDAC_ADCFIFOMSB register defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOMSB_OFFSETADDRESS 0x00000010  /* RW */
#define SDADCDAC_ADCFIFOMSB_BITOFFSET  0
#define SDADCDAC_ADCFIFOMSB_BITFIELDSIZE 32
#define SDADCDAC_ADCFIFOMSB_BITMASK    0xFFFFFFFF
#define SDADCDAC_ADCFIFOMSB_INIT       0x00000000
/*
 *  SDADCDAC_ADC2FIFO bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC2FIFO_OFFSETADDRESS         SDADCDAC_ADCFIFOMSB_OFFSETADDRESS
#define SDADCDAC_ADC2FIFO_BITOFFSET             0
#define SDADCDAC_ADC2FIFO_BITFIELDSIZE         16
#define SDADCDAC_ADC2FIFO_BITMASK               0x0000ffff
#define SDADCDAC_ADC2FIFO_INIT                  0x0

/*
 *  SDADCDAC_BITDATA register defines
 ****************************************************************************************
 */
#define SDADCDAC_BITDATA_OFFSETADDRESS 0x00000014  /* RW */
#define SDADCDAC_BITDATA_BITOFFSET     0
#define SDADCDAC_BITDATA_BITFIELDSIZE  32
#define SDADCDAC_BITDATA_BITMASK       0xFFFFFFFF
#define SDADCDAC_BITDATA_INIT          0x00000000
/*
 *  SDADCDAC_DACDATA bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DACDATA_OFFSETADDRESS          SDADCDAC_BITDATA_OFFSETADDRESS
#define SDADCDAC_DACDATA_BITOFFSET              0
#define SDADCDAC_DACDATA_BITFIELDSIZE           1
#define SDADCDAC_DACDATA_BITMASK                0x00000001
#define SDADCDAC_DACDATA_INIT                   0x0
/*
 *  SDADCDAC_ADC0DATA bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC0DATA_OFFSETADDRESS         SDADCDAC_BITDATA_OFFSETADDRESS
#define SDADCDAC_ADC0DATA_BITOFFSET             1
#define SDADCDAC_ADC0DATA_BITFIELDSIZE          1
#define SDADCDAC_ADC0DATA_BITMASK               0x00000002
#define SDADCDAC_ADC0DATA_INIT                  0x0
/*
 *  SDADCDAC_ADC1DATA bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC1DATA_OFFSETADDRESS         SDADCDAC_BITDATA_OFFSETADDRESS
#define SDADCDAC_ADC1DATA_BITOFFSET             2
#define SDADCDAC_ADC1DATA_BITFIELDSIZE          1
#define SDADCDAC_ADC1DATA_BITMASK               0x00000004
#define SDADCDAC_ADC1DATA_INIT                  0x0
/*
 *  SDADCDAC_ADC2DATA bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC2DATA_OFFSETADDRESS         SDADCDAC_BITDATA_OFFSETADDRESS
#define SDADCDAC_ADC2DATA_BITOFFSET             3
#define SDADCDAC_ADC2DATA_BITFIELDSIZE          1
#define SDADCDAC_ADC2DATA_BITMASK               0x00000008
#define SDADCDAC_ADC2DATA_INIT                  0x0

/*
 *  SDADCDAC_DACFIFOWMARK register defines
 ****************************************************************************************
 */
#define SDADCDAC_DACFIFOWMARK_OFFSETADDRESS 0x00000018  /* RW */
#define SDADCDAC_DACFIFOWMARK_BITOFFSET     0
#define SDADCDAC_DACFIFOWMARK_BITFIELDSIZE  32
#define SDADCDAC_DACFIFOWMARK_BITMASK       0xFFFFFFFF
#define SDADCDAC_DACFIFOWMARK_INIT          0x00000000
/*
 *  SDADCDAC_DACWMARK bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DACWMARK_OFFSETADDRESS             SDADCDAC_DACFIFOWMARK_OFFSETADDRESS 
#define SDADCDAC_DACWMARK_BITOFFSET                 0
#define SDADCDAC_DACWMARK_BITFIELDSIZE              4
#define SDADCDAC_DACWMARK_BITMASK                   0x0000000f
#define SDADCDAC_DACWMARK_INIT                      0x0

/*
 *  SDADCDAC_ADCFIFOWMARK register defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCFIFOWMARK_OFFSETADDRESS 0x0000001c  /* RW */
#define SDADCDAC_ADCFIFOWMARK_BITOFFSET     0
#define SDADCDAC_ADCFIFOWMARK_BITFIELDSIZE  32
#define SDADCDAC_ADCFIFOWMARK_BITMASK       0xFFFFFFFF
#define SDADCDAC_ADCFIFOWMARK_INIT          0x00000000
/*
 *  SDADCDAC_ADCWMARK bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCWMARK_OFFSETADDRESS             SDADCDAC_ADCFIFOWMARK_OFFSETADDRESS 
#define SDADCDAC_ADCWMARK_BITOFFSET                 0
#define SDADCDAC_ADCWMARK_BITFIELDSIZE              4
#define SDADCDAC_ADCWMARK_BITMASK                   0x0000000f
#define SDADCDAC_ADCWMARK_INIT                      0x0

/*
 *  SDADCDAC_PWRDNCTRL register defines
 ****************************************************************************************
 */
#define SDADCDAC_PWRDNCTRL_OFFSETADDRESS 0x00000400  /* RW */
#define SDADCDAC_PWRDNCTRL_BITOFFSET   0
#define SDADCDAC_PWRDNCTRL_BITFIELDSIZE 32
#define SDADCDAC_PWRDNCTRL_BITMASK     0xFFFFFFFF
#define SDADCDAC_PWRDNCTRL_INIT        0x00000000
/*
 *  SDADCDAC_DAC bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DAC_OFFSETADDRESS              SDADCDAC_PWRDNCTRL_OFFSETADDRESS
#define SDADCDAC_DAC_BITOFFSET                  0
#define SDADCDAC_DAC_BITFIELDSIZE               1
#define SDADCDAC_DAC_BITMASK                    0x00000001
#define SDADCDAC_DAC_INIT                       0x0
/*
 *  SDADCDAC_ADC0 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC0_OFFSETADDRESS             SDADCDAC_PWRDNCTRL_OFFSETADDRESS
#define SDADCDAC_ADC0_BITOFFSET                 1
#define SDADCDAC_ADC0_BITFIELDSIZE              1
#define SDADCDAC_ADC0_BITMASK                   0x00000002
#define SDADCDAC_ADC0_INIT                      0x0
/*
 *  SDADCDAC_ADC1 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC1_OFFSETADDRESS             SDADCDAC_PWRDNCTRL_OFFSETADDRESS
#define SDADCDAC_ADC1_BITOFFSET                 2
#define SDADCDAC_ADC1_BITFIELDSIZE              1
#define SDADCDAC_ADC1_BITMASK                   0x00000004
#define SDADCDAC_ADC1_INIT                      0x0
/*
 *  SDADCDAC_ADC2 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADC2_OFFSETADDRESS             SDADCDAC_PWRDNCTRL_OFFSETADDRESS
#define SDADCDAC_ADC2_BITOFFSET                 3
#define SDADCDAC_ADC2_BITFIELDSIZE              1
#define SDADCDAC_ADC2_BITMASK                   0x00000008
#define SDADCDAC_ADC2_INIT                      0x0
/*
 *  SDADCDAC_REF bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_PREF_OFFSETADDRESS              SDADCDAC_PWRDNCTRL_OFFSETADDRESS
#define SDADCDAC_PREF_BITOFFSET                  4
#define SDADCDAC_PREF_BITFIELDSIZE               1
#define SDADCDAC_PREF_BITMASK                    0x00000010
#define SDADCDAC_PREF_INIT                       0x0

/*
 *  SDADCDAC_ANACTRL1 register defines
 ****************************************************************************************
 */
#define SDADCDAC_ANACTRL1_OFFSETADDRESS 0x00000404  /* RW */
#define SDADCDAC_ANACTRL1_BITOFFSET    0
#define SDADCDAC_ANACTRL1_BITFIELDSIZE 32
#define SDADCDAC_ANACTRL1_BITMASK      0xFFFFFFFF
#define SDADCDAC_ANACTRL1_INIT         0x00000000
/*
 *  SDADCDAC_A3VEN bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_A3VEN_OFFSETADDRESS            SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_A3VEN_BITOFFSET                0
#define SDADCDAC_A3VEN_BITFIELDSIZE             1
#define SDADCDAC_A3VEN_BITMASK                  0x00000001
#define SDADCDAC_A3VEN_INIT                     0x0
/*
 *  SDADCDAC_SEL0 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_SEL0_OFFSETADDRESS             SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_SEL0_BITOFFSET                 1
#define SDADCDAC_SEL0_BITFIELDSIZE              1
#define SDADCDAC_SEL0_BITMASK                   0x00000002
#define SDADCDAC_SEL0_INIT                      0x0
/*
 *  SDADCDAC_GAIN0 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_GAIN0_OFFSETADDRESS            SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_GAIN0_BITOFFSET                2
#define SDADCDAC_GAIN0_BITFIELDSIZE             2
#define SDADCDAC_GAIN0_BITMASK                  0x0000000c
#define SDADCDAC_GAIN0_INIT                     0x0
/*
 *  SDADCDAC_SEL1 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_SEL1_OFFSETADDRESS             SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_SEL1_BITOFFSET                 4
#define SDADCDAC_SEL1_BITFIELDSIZE              1
#define SDADCDAC_SEL1_BITMASK                   0x00000010
#define SDADCDAC_SEL1_INIT                      0x0
/*
 *  SDADCDAC_GAIN1 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_GAIN1_OFFSETADDRESS            SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_GAIN1_BITOFFSET                5
#define SDADCDAC_GAIN1_BITFIELDSIZE             2
#define SDADCDAC_GAIN1_BITMASK                  0x00000060
#define SDADCDAC_GAIN1_INIT                     0x0
/*
 *  SDADCDAC_SEL2 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_SEL2_OFFSETADDRESS             SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_SEL2_BITOFFSET                 7
#define SDADCDAC_SEL2_BITFIELDSIZE              1
#define SDADCDAC_SEL2_BITMASK                   0x00000080
#define SDADCDAC_SEL2_INIT                      0x0
/*
 *  SDADCDAC_GAIN2 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_GAIN2_OFFSETADDRESS            SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_GAIN2_BITOFFSET                8
#define SDADCDAC_GAIN2_BITFIELDSIZE             2
#define SDADCDAC_GAIN2_BITMASK                  0x00000300
#define SDADCDAC_GAIN2_INIT                     0x0
/*
 *  SDADCDAC_AVDDEN bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_AVDDEN_OFFSETADDRESS           SDADCDAC_ANACTRL1_OFFSETADDRESS
#define SDADCDAC_AVDDEN_BITOFFSET              10
#define SDADCDAC_AVDDEN_BITFIELDSIZE            1
#define SDADCDAC_AVDDEN_BITMASK                 0x00000400
#define SDADCDAC_AVDDEN_INIT                    0x0

/*
 *  SDADCDAC_ANACTRL2 register defines
 ****************************************************************************************
 */
#define SDADCDAC_ANACTRL2_OFFSETADDRESS 0x00000408  /* RW */
#define SDADCDAC_ANACTRL2_BITOFFSET    0
#define SDADCDAC_ANACTRL2_BITFIELDSIZE 32
#define SDADCDAC_ANACTRL2_BITMASK      0xFFFFFFFF
#define SDADCDAC_ANACTRL2_INIT         0x00000000
/*
 *  SDADCDAC_BIAS bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_BIAS_OFFSETADDRESS             SDADCDAC_ANACTRL2_OFFSETADDRESS
#define SDADCDAC_BIAS_BITOFFSET                 0
#define SDADCDAC_BIAS_BITFIELDSIZE              3
#define SDADCDAC_BIAS_BITMASK                   0x00000007
#define SDADCDAC_BIAS_INIT                      0x0
/*
 *  SDADCDAC_TMPCO bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_TMPCO_OFFSETADDRESS            SDADCDAC_ANACTRL2_OFFSETADDRESS
#define SDADCDAC_TMPCO_BITOFFSET                4
#define SDADCDAC_TMPCO_BITFIELDSIZE             4
#define SDADCDAC_TMPCO_BITMASK                  0x000000f0
#define SDADCDAC_TMPCO_INIT                     0x0
/*
 *  SDADCDAC_REF bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_REF_OFFSETADDRESS              SDADCDAC_ANACTRL2_OFFSETADDRESS
#define SDADCDAC_REF_BITOFFSET                  9
#define SDADCDAC_REF_BITFIELDSIZE               5
#define SDADCDAC_REF_BITMASK                    0x00003e00
#define SDADCDAC_REF_INIT                       0x0
/*
 *  SDADCDAC_PHASE1 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_PHASE1_OFFSETADDRESS           SDADCDAC_ANACTRL2_OFFSETADDRESS
#define SDADCDAC_PHASE1_BITOFFSET              14
#define SDADCDAC_PHASE1_BITFIELDSIZE            7
#define SDADCDAC_PHASE1_BITMASK                 0x001fc000
#define SDADCDAC_PHASE1_INIT                    0x0
/*
 *  SDADCDAC_PHASE2 bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_PHASE2_OFFSETADDRESS           SDADCDAC_ANACTRL2_OFFSETADDRESS
#define SDADCDAC_PHASE2_BITOFFSET              	21
#define SDADCDAC_PHASE2_BITFIELDSIZE            7
#define SDADCDAC_PHASE2_BITMASK                 0x0fe00000
#define SDADCDAC_PHASE2_INIT                    0x0  
/*
 *  SDADCDAC_PHASESTEP bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_PHASESTEP_OFFSETADDRESS      SDADCDAC_ANACTRL2_OFFSETADDRESS
#define SDADCDAC_PHASESTEP_BITOFFSET          28
#define SDADCDAC_PHASESTEP_BITFIELDSIZE       4
#define SDADCDAC_PHASESTEP_BITMASK            0xf0000000
#define SDADCDAC_PHASESTEP_INIT     		  0x0	   
   

/*
 *  SDADCDAC_ANATEST register defines
 ****************************************************************************************
 */
#define SDADCDAC_ANATEST_OFFSETADDRESS 0x0000040c  /* RW */
#define SDADCDAC_ANATEST_BITOFFSET     0
#define SDADCDAC_ANATEST_BITFIELDSIZE  32
#define SDADCDAC_ANATEST_BITMASK       0xFFFFFFFF
#define SDADCDAC_ANATEST_INIT          0x00000000
/*
 *  SDADCDAC_ADCTEST bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_ADCTEST_OFFSETADDRESS          SDADCDAC_ANATEST_OFFSETADDRESS
#define SDADCDAC_ADCTEST_BITOFFSET              0
#define SDADCDAC_ADCTEST_BITFIELDSIZE           1
#define SDADCDAC_ADCTEST_BITMASK                0x00000001
#define SDADCDAC_ADCTEST_INIT                   0x0
/*
 *  SDADCDAC_DI bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_DI_OFFSETADDRESS               SDADCDAC_ANATEST_OFFSETADDRESS
#define SDADCDAC_DI_BITOFFSET                   1
#define SDADCDAC_DI_BITFIELDSIZE                1
#define SDADCDAC_DI_BITMASK                     0x00000002
#define SDADCDAC_DI_INIT                        0x0
/*
 *  SDADCDAC_RST bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_RST_OFFSETADDRESS              SDADCDAC_ANATEST_OFFSETADDRESS
#define SDADCDAC_RST_BITOFFSET                  2
#define SDADCDAC_RST_BITFIELDSIZE               1
#define SDADCDAC_RST_BITMASK                    0x00000004
#define SDADCDAC_RST_INIT                       0x0
/*
 *  SDADCDAC_TESTREF bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_TESTREF_OFFSETADDRESS          SDADCDAC_ANATEST_OFFSETADDRESS
#define SDADCDAC_TESTREF_BITOFFSET              3
#define SDADCDAC_TESTREF_BITFIELDSIZE           1
#define SDADCDAC_TESTREF_BITMASK                0x00000008
#define SDADCDAC_TESTREF_INIT                   0x0
/*
 *  SDADCDAC_BYPASSEN bit field defines
 ****************************************************************************************
 */
#define SDADCDAC_BYPASSEN_OFFSETADDRESS         SDADCDAC_ANATEST_OFFSETADDRESS
#define SDADCDAC_BYPASSEN_BITOFFSET             4
#define SDADCDAC_BYPASSEN_BITFIELDSIZE          1
#define SDADCDAC_BYPASSEN_BITMASK               0x00000010
#define SDADCDAC_BYPASSEN_INIT                  0x0
#endif
