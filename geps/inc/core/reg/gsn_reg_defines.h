/******************************************************************************
 *
 *               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
 * $RCSfile: gsn_reg_defines.h,v $
 *
 * Description : This file contains the definitions for Register operations
 *****************************************************************************/

/**
 ******************************************************************************
 * @file gsn_reg_defines.h
 * @brief GSN Register Definitions.
 *    This file contains macro definitions for accessing various GS101x registers,
 * flash memory, and related operations.
 *****************************************************************************/


/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/

/**
 ******************************************************************************
 * @defgroup GsnRegisters GSN Register Information
 * @brief This group contains a variety of register-related information.
 *
 * files include:<br>
 * gsn_reg_defines.h
 *
 * \verbatim
 *
 * File					Contents
 * ====					========
 * gsn_reg_defines.h	bitfields BIT0 to BIT31
 *                      base memory addresses for APP platform (shared RAM, mailbox, etc.)
 *                      base memory addresses for shared peripherals
 *                      mailbox info register bits
 *                      app reset bits
 *                      watchdog bits
 *                      clock control bits
 *                      GPIO control
 *                      ADC/DAC control
 *
 * \endverbatim
 * 
 *****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/





#ifndef _GSN_APP_REG_ACCESS_H_
#define _GSN_APP_REG_ACCESS_H_


#define BIT0	(0x1)
#define BIT1	(0x2)
#define BIT2	(0x4)
#define BIT3	(0x8)
#define BIT4	(0x10)
#define BIT5	(0x20)
#define BIT6	(0x40)
#define BIT7	(0x80)
#define BIT8	(0x100)
#define BIT9	(0x200)
#define BIT10	(0x400)
#define BIT11	(0x800)
#define BIT12	(0x1000)
#define BIT13	(0x2000)
#define BIT14	(0x4000)
#define BIT15	(0x8000)
#define BIT16	(0x10000)
#define BIT17	(0x20000)
#define BIT18	(0x40000)
#define BIT19	(0x80000)
#define BIT20	(0x100000)
#define BIT21	(0x200000)
#define BIT22	(0x400000)
#define BIT23	(0x800000)
#define BIT24	(0x1000000)
#define BIT25	(0x2000000)
#define BIT26	(0x4000000)
#define BIT27	(0x8000000)
#define BIT28	(0x10000000)
#define BIT29	(0x20000000)
#define BIT30	(0x40000000)
#define BIT31	(0x80000000)


/* BASE ADDRESS of APP Platform */
#define GSN_SHARED_RAM_REG_BASE				0x04000000 /* Based Address of SRAM */
#define GSN_SYSTEM_CONTROLLER_REG_BASE		0x05000000 /* SYSTEM Controller	*/
#define GSN_TIMER1_REG_BASE					0x05000160 /* TIMER-1			*/
#define GSN_TIMER2_REG_BASE					0x05000170 /* TIMER-2			*/
#define GSN_INT_CONTROLLER_REG_BASE			0x05000200 /* INT Controller	*/
#define GSN_APP_MAILBOX_REG_BASE			0x05000C00 /* MailBox			*/
#define GSN_LOCATION_AWARENESS_REG_BASE		0x05001400 /* Location Awareness*/

/* BASE Address of Shared Peripherals */
#define GSN_FLASH0_BASE_ADDRESS				0x06000000 /* FLASH1            */
#define GSN_FLASH1_BASE_ADDRESS				0x08000000 /* FLASH2            */

#define GSN_UART0_REG_BASE					0x07000000 /* UART0				*/
#define GSN_UART1_REG_BASE					0x07000100 /* UART1				*/
#define GSN_GPIO_REG_BASE					0x07000200 /* GPIO				*/
#define GSN_APP_FLASH0_REG_BASE				0x07000300 /* FLASH1			*/
#define GSN_APP_FLASH1_REG_BASE				0x07000400 /* FLASH2			*/
#define GSN_PWM_REG_BASE					0x07000600 /* PWM				*/
#define GSN_ADC_REG_BASE					0x07000700 /* ADC				*/
#define GSN_SPI_MASTER_REG_BASE				0x07000800 /* SPI MASTER		*/
#define GSN_I2C_REG_BASE					0x07000A00 /* I2C				*/
#define GSN_SPI_SLAVE_REG_BASE				0x07000B00 /* SPI SLAVE			*/
#define GSN_TSYNC_REG_BASE					0x40130000 /* TSYNC/ 1588		*/
#define GSN_RTC_REG_BASE					0x07001000 /* RTC				*/

#define GSN_INT_ENABLE_REG GSN_INT_CONTROLLER_REG_BASE + 0x8

/* Mailbox Info Register Bits */
#define GSN_FW_UPDATE_MASK (BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27)


#ifdef GSN_NOT_REQUIRED
#define GSN_WLAN_FLASH_DOWNLOADED			BIT16
#define GSN_APP_FLASH0_DOWNLOADED			BIT17
#define GSN_APP_FLASH1_DOWNLOADED			BIT18

#define GSN_WLAN_FLASH_DWNLD_MASK			(BIT19|BIT20|BIT21)
#define GSN_WLAN_FLASH_DWNLD_SUCCESS		(0)
#define GSN_WLAN_FLASH_DWNLD_CHKSUM_ERROR	(BIT19)
#define GSN_WLAN_FLASH_DWNLD_TIMEOUT		(BIT20)

#define GSN_APP_FLASH0_DWNLD_MASK			(BIT22|BIT23|BIT24)
#define GSN_APP_FLASH0_DWNLD_SUCCESS		(0)
#define GSN_APP_FLASH0_DWNLD_CHKSUM_ERROR	(BIT22)
#define GSN_APP_FLASH0_DWNLD_TIMEOUT		(BIT23)

#define GSN_APP_FLASH1_DWNLD_MASK			(BIT25|BIT26|BIT27)
#define GSN_APP_FLASH1_DWNLD_SUCCESS		(0)
#define GSN_APP_FLASH1_DWNLD_CHKSUM_ERROR	(BIT25)
#define GSN_APP_FLASH1_DWNLD_TIMEOUT		(BIT26)
#endif


#define GSN_APP_MB_LAST_WAKEUP_M1_D0_TIME_MASK	0xFFFF0000

/* @@@@ End APP Reset Registers and Bits @@@@ */


/* #### Begin APP Reset Register Bits #### */

/* APP Reset Register Bits */
#define GSN_APP_RESET_WD_BIT				(BIT0)
#define GSN_APP_RESET_SW_BIT				(BIT2)
#define GSN_APP_RESET_WLAN_BIT				(BIT3)
/* @@@@ End APP Reset Registers and Bits @@@@ */


/* #### Begin APP SHARED Control Register Bits #### */

/* WD Config Register Bits */
#define GSN_APP_SHARED_PERI_UART0_BIT		(BIT0)
#define GSN_APP_SHARED_PERI_UART1_BIT		(BIT1)
#define GSN_APP_SHARED_PERI_SPIMA_BIT		(BIT2)
#define GSN_APP_SHARED_PERI_SPISL_BIT		(BIT3)
#define GSN_APP_SHARED_PERI_I2C_BIT			(BIT4)
#define GSN_APP_SHARED_PERI_PWM_BIT			(BIT5)
#define GSN_APP_SHARED_PERI_ADC_BIT			(BIT6)
#define GSN_APP_SHARED_PERI_FLASH0_BIT		(BIT7)
#define GSN_APP_SHARED_PERI_FLASH1_BIT		(BIT8)

/* @@@@ End APP SHARED Control Registers and Bits @@@@ */


/* #### Begin APP DEVICE Conf (Memory) Register Bits #### */

/* DEV Congfig Bits */
#define GSN_APP_DEV_CONFIG_SRAM_SIZE_BIT	(BIT0|BIT1)
#define GSN_APP_CPU_ENABLE_BIT				(BIT8)

/* @@@@ End APP DEVICE Conf (Memory) Registers and Bits @@@@ */



/* #### Begin APP SHARED GPIO Register Bits #### */

/* #### Begin APP WatchDog Registers and Bits #### */
/* WD Config Register Bits */
#define GSN_APP_WD_CONFIG_WDENABLE_BIT		(BIT15)
#define GSN_APP_WD_CONFIG_WDDIV_BIT			(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6)

/* WD Stroke Register Bits */
#define GSN_APP_WD_ENABLE					(0x1234)
#define GSN_APP_WD_DISABLE					(0x5678)

/* @@@@ End APP WatchDog Registers and Bits @@@@ */

/* APP CPU GSN_CLOCK_CNTL_REG Bits */
#define GSN_CLOCK_CNTL_BITS					(BIT1 | BIT0)
#define GSN_CLOCK_DEEPSLEEP_REQ_BIT			(BIT4)

#define APP_CLK_CNTL_APP_FREQ11	(0)
#define APP_CLK_CNTL_APP_FREQ22	(BIT8)
#define APP_CLK_CNTL_APP_FREQ44	(BIT9)


#define GSN_CLOCK_MANWKUP_BIT				(BIT12)
#define GSN_CLOCK_LP_FREQ_BIT				(BIT24)
#define GSN_CLOCK_PREP_SLEEP_BIT			(BIT28)


/* Bits for GPIO CNTL */
#define GSN_GPIO_SEL_LOW_BIT				(BIT0)
#define GSN_GPIO_SEL_HIGH_BIT				(BIT1)
#define GSN_MUX_FN0_UART0_TXRX_BIT			(BIT8)
#define GSN_MUX_FN1_UART0_CTSRTS_BIT		(BIT9)
#define GSN_MUX_FN2_UART1_TXRX_BIT			(BIT10)
#define GSN_MUX_FN3_UART1_CTSRTS_BIT		(BIT11)
#define GSN_MUX_FN4_PWM0_BIT				(BIT12)
#define GSN_MUX_FN5_PWM1_BIT				(BIT13)
#define GSN_MUX_FN6_PWM2_BIT				(BIT14)
#define GSN_MUX_FN7_I2C_BIT					(BIT15)
#define GSN_MUX_FN8_MSPI_BIT				(BIT16)
#define GSN_MUX_FN9_MSPICS1_BIT				(BIT17)
#define GSN_MUX_FN10_MSPICS2_BIT			(BIT18)
#define GSN_MUX_FN11_MSPICS3_BIT			(BIT19)
#define GSN_MUX_FN12_44MHZ_BIT				(BIT20)
#define GSN_MUX_FN13_22MHZ_BIT				(BIT21)
#define GSN_MUX_FN14_11MHZ_BIT				(BIT22)
#define GSN_MUX_FN15_32KHZ_BIT				(BIT23)
#define GSN_MUX_FN16_AUXSNAP0_BIT			(BIT24)
#define GSN_MUX_FN17_AUXSNAP1_BIT			(BIT25)
#define GSN_MUX_FN18_AUXTRGT_BIT			(BIT26)
#define GSN_MUX_FN19_PPS_BIT				(BIT27)
#define GSN_MUX_FN20_RFADCIN_BIT			(BIT28)
#define GSN_MUX_FN21_RFDACIN_BIT			(BIT29)
#define GSN_MUX_FN22_BIT					(BIT29)
#define GSN_MUX_FN23_BIT					(BIT29)

/* @@@@ End GPIO/ MUX Function Register @@@@ */

/* Bits for ADC CNTL */
#define GSN_ADC_CNTRL_OPRTNG_MODE_BIT		(BIT0|BIT1|BIT2|BIT3)
#define GSN_ADC_CNTRL_POWER_MODE_BIT		(BIT4)
#define GSN_ADC_CNTRL_REFNC_VOLT_BIT		(BIT5)
#define GSN_ADC_CNTRL_CLS_SELECT_BIT		(BIT6)
#define GSN_ADC_CNTRL_ADC_EN_BIT			(BIT8)
#define GSN_ADC_CNTRL_DAC_EN_BIT			(BIT9)
#define GSN_ADC_CNTRL_FIFO_THRS_BIT			(BIT16|BIT17|BIT18)
#define GSN_ADC_CNTRL_A0_TEST_BIT			(BIT26)
#define GSN_ADC_CNTRL_RESET_BIT				(BIT27)
#define GSN_ADC_CNTRL_PWRDN_BANDGAP_BIT		(BIT28)
#define GSN_ADC_CNTRL_PWRDN_BUFF_BIT		(BIT29)
#define GSN_ADC_CNTRL_PWRDN_CMPTR_BIT		(BIT30)
#define GSN_ADC_CNTRL_TEST_ADC_BIT			(BIT31)

/* ADC Stat Register */
#define GSN_ADC_STAT_RUN_BIT				(BIT0)
#define GSN_ADC_STAT_FIFO_VALS_BIT			(BIT16|BIT17|BIT18)

/* ADC RAW Int RawStat/ Mask/ Status/ Clear Register */
#define GSN_ADC_FIFO_NE_BIT					(BIT0)
#define GSN_ADC_FIFO_OVRFLOW_BIT			(BIT1)
#define GSN_ADC_LIMIT1_UFLOW_BIT			(BIT8)
#define GSN_ADC_LIMIT1_OFLOW_BIT			(BIT9)
#define GSN_ADC_LIMIT2_UFLOW_BIT			(BIT12)
#define GSN_ADC_LIMIT2_OFLOW_BIT			(BIT13)

/* ADC LIMITS Register */
#define GSN_LOWER_LIMIT_MEASUREMENTS_BIT	(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7|BIT8|BIT9)
#define GSN_UPPER_LIMIT_MEASUREMENTS_BIT	(BIT16|BIT17|BIT18|BIT19|BIT20|BIT21|BIT22|BIT23|BIT24|BIT25)
/* @@@@ End ADC Register, Bits @@@@ */

/* ADC DATA Register */
#define GSN_ADC_DATA_BIT					(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7|BIT8|BIT9)
#define GSN_ADC_DATA_SRC_BIT				(BIT16|BIT17)

/* DAC DATA Register */
#define GSN_DAC_DATA_BIT					(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7|BIT8|BIT9)

/* POD DATA Register */
#define GSN_POD_DATA_BIT					(BIT0|BIT1|BIT2|BIT3|BIT4)

/* @@@@ End ADC Register, Bits @@@@ */


#endif /* _GSN_APP_REG_ACCESS_H_ */

