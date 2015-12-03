#ifndef _REG_IOMUX_MAC_H
#define _REG_IOMUX_MAC_H

/***************************************************
 *
 *             IOMUX
 *
 ***************************************************/


/*
 *  IOMUX_GPIO_00 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_00_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_00))
#define IOMUX_GPIO_00_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_00, (value))
#define IOMUX_GPIO_00_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_00, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_00) | (value))
#define IOMUX_GPIO_00_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_00, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_00) & (~(value)))

/*
 *  IOMUX_GPIO_00_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_00_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_00_PIN_SEL)
#define IOMUX_GPIO_00_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_00_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_01 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_01_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_01))
#define IOMUX_GPIO_01_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_01, (value))
#define IOMUX_GPIO_01_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_01, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_01) | (value))
#define IOMUX_GPIO_01_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_01, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_01) & (~(value)))

/*
 *  IOMUX_GPIO_01_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_01_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_01_PIN_SEL)
#define IOMUX_GPIO_01_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_01_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_02 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_02_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_02))
#define IOMUX_GPIO_02_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_02, (value))
#define IOMUX_GPIO_02_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_02, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_02) | (value))
#define IOMUX_GPIO_02_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_02, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_02) & (~(value)))

/*
 *  IOMUX_GPIO_02_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_02_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_02_PIN_SEL)
#define IOMUX_GPIO_02_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_02_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_03 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_03_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_03))
#define IOMUX_GPIO_03_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_03, (value))
#define IOMUX_GPIO_03_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_03, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_03) | (value))
#define IOMUX_GPIO_03_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_03, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_03) & (~(value)))

/*
 *  IOMUX_GPIO_03_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_03_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_03_PIN_SEL)
#define IOMUX_GPIO_03_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_03_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_04 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_04_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_04))
#define IOMUX_GPIO_04_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_04, (value))
#define IOMUX_GPIO_04_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_04, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_04) | (value))
#define IOMUX_GPIO_04_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_04, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_04) & (~(value)))

/*
 *  IOMUX_GPIO_04_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_04_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_04_PIN_SEL)
#define IOMUX_GPIO_04_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_04_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_05 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_05_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_05))
#define IOMUX_GPIO_05_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_05, (value))
#define IOMUX_GPIO_05_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_05, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_05) | (value))
#define IOMUX_GPIO_05_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_05, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_05) & (~(value)))

/*
 *  IOMUX_GPIO_05_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_05_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_05_PIN_SEL)
#define IOMUX_GPIO_05_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_05_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_06 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_06_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_06))
#define IOMUX_GPIO_06_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_06, (value))
#define IOMUX_GPIO_06_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_06, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_06) | (value))
#define IOMUX_GPIO_06_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_06, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_06) & (~(value)))

/*
 *  IOMUX_GPIO_06_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_06_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_06_PIN_SEL)
#define IOMUX_GPIO_06_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_06_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_07 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_07_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_07))
#define IOMUX_GPIO_07_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_07, (value))
#define IOMUX_GPIO_07_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_07, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_07) | (value))
#define IOMUX_GPIO_07_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_07, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_07) & (~(value)))

/*
 *  IOMUX_GPIO_07_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_07_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_07_PIN_SEL)
#define IOMUX_GPIO_07_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_07_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_08 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_08_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_08))
#define IOMUX_GPIO_08_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_08, (value))
#define IOMUX_GPIO_08_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_08, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_08) | (value))
#define IOMUX_GPIO_08_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_08, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_08) & (~(value)))

/*
 *  IOMUX_GPIO_08_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_08_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_08_PIN_SEL)
#define IOMUX_GPIO_08_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_08_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_09 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_09_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_09))
#define IOMUX_GPIO_09_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_09, (value))
#define IOMUX_GPIO_09_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_09, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_09) | (value))
#define IOMUX_GPIO_09_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_09, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_09) & (~(value)))

/*
 *  IOMUX_GPIO_09_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_09_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_09_PIN_SEL)
#define IOMUX_GPIO_09_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_09_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_10 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_10_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_10))
#define IOMUX_GPIO_10_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_10, (value))
#define IOMUX_GPIO_10_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_10, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_10) | (value))
#define IOMUX_GPIO_10_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_10, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_10) & (~(value)))

/*
 *  IOMUX_GPIO_10_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_10_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_10_PIN_SEL)
#define IOMUX_GPIO_10_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_10_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_11 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_11_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_11))
#define IOMUX_GPIO_11_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_11, (value))
#define IOMUX_GPIO_11_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_11, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_11) | (value))
#define IOMUX_GPIO_11_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_11, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_11) & (~(value)))

/*
 *  IOMUX_GPIO_11_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_11_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_11_PIN_SEL)
#define IOMUX_GPIO_11_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_11_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_12 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_12_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_12))
#define IOMUX_GPIO_12_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_12, (value))
#define IOMUX_GPIO_12_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_12, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_12) | (value))
#define IOMUX_GPIO_12_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_12, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_12) & (~(value)))

/*
 *  IOMUX_GPIO_12_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_12_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_12_PIN_SEL)
#define IOMUX_GPIO_12_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_12_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_13 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_13_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_13))
#define IOMUX_GPIO_13_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_13, (value))
#define IOMUX_GPIO_13_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_13, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_13) | (value))
#define IOMUX_GPIO_13_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_13, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_13) & (~(value)))

/*
 *  IOMUX_GPIO_13_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_13_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_13_PIN_SEL)
#define IOMUX_GPIO_13_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_13_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_14 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_14_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_14))
#define IOMUX_GPIO_14_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_14, (value))
#define IOMUX_GPIO_14_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_14, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_14) | (value))
#define IOMUX_GPIO_14_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_14, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_14) & (~(value)))

/*
 *  IOMUX_GPIO_14_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_14_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_14_PIN_SEL)
#define IOMUX_GPIO_14_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_14_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_15 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_15_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_15))
#define IOMUX_GPIO_15_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_15, (value))
#define IOMUX_GPIO_15_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_15, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_15) | (value))
#define IOMUX_GPIO_15_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_15, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_15) & (~(value)))

/*
 *  IOMUX_GPIO_15_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_15_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_15_PIN_SEL)
#define IOMUX_GPIO_15_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_15_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_16 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_16_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_16))
#define IOMUX_GPIO_16_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_16, (value))
#define IOMUX_GPIO_16_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_16, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_16) | (value))
#define IOMUX_GPIO_16_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_16, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_16) & (~(value)))

/*
 *  IOMUX_GPIO_16_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_16_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_16_PIN_SEL)
#define IOMUX_GPIO_16_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_16_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_17 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_17_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_17))
#define IOMUX_GPIO_17_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_17, (value))
#define IOMUX_GPIO_17_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_17, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_17) | (value))
#define IOMUX_GPIO_17_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_17, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_17) & (~(value)))

/*
 *  IOMUX_GPIO_17_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_17_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_17_PIN_SEL)
#define IOMUX_GPIO_17_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_17_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_18 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_18_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_18))
#define IOMUX_GPIO_18_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_18, (value))
#define IOMUX_GPIO_18_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_18, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_18) | (value))
#define IOMUX_GPIO_18_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_18, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_18) & (~(value)))

/*
 *  IOMUX_GPIO_18_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_18_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_18_PIN_SEL)
#define IOMUX_GPIO_18_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_18_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_19 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_19_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_19))
#define IOMUX_GPIO_19_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_19, (value))
#define IOMUX_GPIO_19_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_19, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_19) | (value))
#define IOMUX_GPIO_19_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_19, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_19) & (~(value)))

/*
 *  IOMUX_GPIO_19_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_19_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_19_PIN_SEL)
#define IOMUX_GPIO_19_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_19_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_20 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_20_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_20))
#define IOMUX_GPIO_20_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_20, (value))
#define IOMUX_GPIO_20_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_20, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_20) | (value))
#define IOMUX_GPIO_20_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_20, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_20) & (~(value)))

/*
 *  IOMUX_GPIO_20_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_20_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_20_PIN_SEL)
#define IOMUX_GPIO_20_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_20_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_21 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_21_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_21))
#define IOMUX_GPIO_21_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_21, (value))
#define IOMUX_GPIO_21_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_21, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_21) | (value))
#define IOMUX_GPIO_21_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_21, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_21) & (~(value)))

/*
 *  IOMUX_GPIO_21_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_21_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_21_PIN_SEL)
#define IOMUX_GPIO_21_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_21_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_22 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_22_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_22))
#define IOMUX_GPIO_22_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_22, (value))
#define IOMUX_GPIO_22_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_22, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_22) | (value))
#define IOMUX_GPIO_22_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_22, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_22) & (~(value)))

/*
 *  IOMUX_GPIO_22_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_22_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_22_PIN_SEL)
#define IOMUX_GPIO_22_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_22_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_23 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_23_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_23))
#define IOMUX_GPIO_23_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_23, (value))
#define IOMUX_GPIO_23_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_23, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_23) | (value))
#define IOMUX_GPIO_23_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_23, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_23) & (~(value)))

/*
 *  IOMUX_GPIO_23_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_23_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_23_PIN_SEL)
#define IOMUX_GPIO_23_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_23_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_24 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_24_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_24))
#define IOMUX_GPIO_24_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_24, (value))
#define IOMUX_GPIO_24_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_24, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_24) | (value))
#define IOMUX_GPIO_24_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_24, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_24) & (~(value)))

/*
 *  IOMUX_GPIO_24_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_24_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_24_PIN_SEL)
#define IOMUX_GPIO_24_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_24_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_25 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_25_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_25))
#define IOMUX_GPIO_25_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_25, (value))
#define IOMUX_GPIO_25_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_25, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_25) | (value))
#define IOMUX_GPIO_25_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_25, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_25) & (~(value)))

/*
 *  IOMUX_GPIO_25_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_25_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_25_PIN_SEL)
#define IOMUX_GPIO_25_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_25_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_26 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_26_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_26))
#define IOMUX_GPIO_26_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_26, (value))
#define IOMUX_GPIO_26_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_26, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_26) | (value))
#define IOMUX_GPIO_26_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_26, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_26) & (~(value)))

/*
 *  IOMUX_GPIO_26_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_26_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_26_PIN_SEL)
#define IOMUX_GPIO_26_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_26_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_27 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_27_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_27))
#define IOMUX_GPIO_27_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_27, (value))
#define IOMUX_GPIO_27_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_27, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_27) | (value))
#define IOMUX_GPIO_27_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_27, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_27) & (~(value)))

/*
 *  IOMUX_GPIO_27_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_27_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_27_PIN_SEL)
#define IOMUX_GPIO_27_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_27_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_28 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_28_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_28))
#define IOMUX_GPIO_28_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_28, (value))
#define IOMUX_GPIO_28_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_28, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_28) | (value))
#define IOMUX_GPIO_28_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_28, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_28) & (~(value)))

/*
 *  IOMUX_GPIO_28_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_28_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_28_PIN_SEL)
#define IOMUX_GPIO_28_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_28_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_29 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_29_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_29))
#define IOMUX_GPIO_29_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_29, (value))
#define IOMUX_GPIO_29_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_29, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_29) | (value))
#define IOMUX_GPIO_29_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_29, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_29) & (~(value)))

/*
 *  IOMUX_GPIO_29_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_29_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_29_PIN_SEL)
#define IOMUX_GPIO_29_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_29_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_30 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_30_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_30))
#define IOMUX_GPIO_30_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_30, (value))
#define IOMUX_GPIO_30_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_30, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_30) | (value))
#define IOMUX_GPIO_30_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_30, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_30) & (~(value)))

/*
 *  IOMUX_GPIO_30_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_30_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_30_PIN_SEL)
#define IOMUX_GPIO_30_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_30_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_31 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_31_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_31))
#define IOMUX_GPIO_31_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_31, (value))
#define IOMUX_GPIO_31_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_31, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_31) | (value))
#define IOMUX_GPIO_31_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_31, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_31) & (~(value)))

/*
 *  IOMUX_GPIO_31_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_31_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_31_PIN_SEL)
#define IOMUX_GPIO_31_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_31_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_32 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_32_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_32))
#define IOMUX_GPIO_32_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_32, (value))
#define IOMUX_GPIO_32_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_32, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_32) | (value))
#define IOMUX_GPIO_32_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_32, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_32) & (~(value)))

/*
 *  IOMUX_GPIO_32_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_32_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_32_PIN_SEL)
#define IOMUX_GPIO_32_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_32_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_33 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_33_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_33))
#define IOMUX_GPIO_33_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_33, (value))
#define IOMUX_GPIO_33_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_33, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_33) | (value))
#define IOMUX_GPIO_33_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_33, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_33) & (~(value)))

/*
 *  IOMUX_GPIO_33_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_33_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_33_PIN_SEL)
#define IOMUX_GPIO_33_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_33_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_34 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_34_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_34))
#define IOMUX_GPIO_34_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_34, (value))
#define IOMUX_GPIO_34_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_34, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_34) | (value))
#define IOMUX_GPIO_34_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_34, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_34) & (~(value)))

/*
 *  IOMUX_GPIO_34_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_34_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_34_PIN_SEL)
#define IOMUX_GPIO_34_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_34_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_35 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_35_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_35))
#define IOMUX_GPIO_35_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_35, (value))
#define IOMUX_GPIO_35_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_35, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_35) | (value))
#define IOMUX_GPIO_35_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_35, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_35) & (~(value)))

/*
 *  IOMUX_GPIO_35_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_35_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_35_PIN_SEL)
#define IOMUX_GPIO_35_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_35_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_36 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_36_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_36))
#define IOMUX_GPIO_36_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_36, (value))
#define IOMUX_GPIO_36_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_36, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_36) | (value))
#define IOMUX_GPIO_36_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_36, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_36) & (~(value)))

/*
 *  IOMUX_GPIO_36_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_36_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_36_PIN_SEL)
#define IOMUX_GPIO_36_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_36_PIN_SEL, (value))


/*
 *  IOMUX_GPIO_37 register macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_37_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_37))
#define IOMUX_GPIO_37_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_37, (value))
#define IOMUX_GPIO_37_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_37, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_37) | (value))
#define IOMUX_GPIO_37_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_37, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_GPIO_37) & (~(value)))

/*
 *  IOMUX_GPIO_37_PIN_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_GPIO_37_PIN_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_GPIO_37_PIN_SEL)
#define IOMUX_GPIO_37_PIN_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_GPIO_37_PIN_SEL, (value))


/*
 *  IOMUX_EXT_RST_N register macros
 ****************************************************************************************
 */
#define IOMUX_EXT_RST_N_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_EXT_RST_N))
#define IOMUX_EXT_RST_N_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_EXT_RST_N, (value))
#define IOMUX_EXT_RST_N_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_EXT_RST_N, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_EXT_RST_N) | (value))
#define IOMUX_EXT_RST_N_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_EXT_RST_N, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_EXT_RST_N) & (~(value)))

/*
 *  IOMUX_EXT_RST_N_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_EXT_RST_N_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_EXT_RST_N_SEL)
#define IOMUX_EXT_RST_N_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_EXT_RST_N_SEL, (value))


/*
 *  IOMUX_FLASHSPI_CS register macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_CS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_CS))
#define IOMUX_FLASHSPI_CS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_CS, (value))
#define IOMUX_FLASHSPI_CS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_CS, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_CS) | (value))
#define IOMUX_FLASHSPI_CS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_CS, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_CS) & (~(value)))

/*
 *  IOMUX_FLASHSPI_CS_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_CS_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_CS_SEL)
#define IOMUX_FLASHSPI_CS_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_CS_SEL, (value))


/*
 *  IOMUX_FLASHSPI_SCLK register macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SCLK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SCLK))
#define IOMUX_FLASHSPI_SCLK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SCLK, (value))
#define IOMUX_FLASHSPI_SCLK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SCLK, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SCLK) | (value))
#define IOMUX_FLASHSPI_SCLK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SCLK, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SCLK) & (~(value)))

/*
 *  IOMUX_FLASHSPI_SCLK_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SCLK_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SCLK_SEL)
#define IOMUX_FLASHSPI_SCLK_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SCLK_SEL, (value))


/*
 *  IOMUX_FLASHSPI_SIO0 register macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO0))
#define IOMUX_FLASHSPI_SIO0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO0, (value))
#define IOMUX_FLASHSPI_SIO0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO0, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO0) | (value))
#define IOMUX_FLASHSPI_SIO0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO0, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO0) & (~(value)))

/*
 *  IOMUX_FLASHSPI_SIO0_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO0_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO0_SEL)
#define IOMUX_FLASHSPI_SIO0_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO0_SEL, (value))


/*
 *  IOMUX_FLASHSPI_SIO1 register macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO1))
#define IOMUX_FLASHSPI_SIO1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO1, (value))
#define IOMUX_FLASHSPI_SIO1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO1, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO1) | (value))
#define IOMUX_FLASHSPI_SIO1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO1, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO1) & (~(value)))

/*
 *  IOMUX_FLASHSPI_SIO1_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO1_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO1_SEL)
#define IOMUX_FLASHSPI_SIO1_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO1_SEL, (value))


/*
 *  IOMUX_FLASHSPI_SIO2 register macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO2))
#define IOMUX_FLASHSPI_SIO2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO2, (value))
#define IOMUX_FLASHSPI_SIO2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO2, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO2) | (value))
#define IOMUX_FLASHSPI_SIO2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO2, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO2) & (~(value)))

/*
 *  IOMUX_FLASHSPI_SIO2_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO2_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO2_SEL)
#define IOMUX_FLASHSPI_SIO2_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO2_SEL, (value))


/*
 *  IOMUX_FLASHSPI_SIO3 register macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO3_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO3))
#define IOMUX_FLASHSPI_SIO3_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO3, (value))
#define IOMUX_FLASHSPI_SIO3_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO3, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO3) | (value))
#define IOMUX_FLASHSPI_SIO3_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO3, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_FLASHSPI_SIO3) & (~(value)))

/*
 *  IOMUX_FLASHSPI_SIO3_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO3_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO3_SEL)
#define IOMUX_FLASHSPI_SIO3_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO3_SEL, (value))


/*
 *  IOMUX_PULL_DOWN_EN register macros
 ****************************************************************************************
 */
#define IOMUX_PULL_DOWN_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_PULL_DOWN_EN))
#define IOMUX_PULL_DOWN_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_PULL_DOWN_EN, (value))
#define IOMUX_PULL_DOWN_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_PULL_DOWN_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_PULL_DOWN_EN) | (value))
#define IOMUX_PULL_DOWN_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_PULL_DOWN_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_PULL_DOWN_EN) & (~(value)))

/*
 *  IOMUX_BONDOPT_0_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_BONDOPT_0_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_0_PD_EN)
#define IOMUX_BONDOPT_0_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_0_PD_EN, 1)
#define IOMUX_BONDOPT_0_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_0_PD_EN, 0)

/*
 *  IOMUX_BONDOPT_1_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_BONDOPT_1_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_1_PD_EN)
#define IOMUX_BONDOPT_1_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_1_PD_EN, 1)
#define IOMUX_BONDOPT_1_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_1_PD_EN, 0)

/*
 *  IOMUX_BONDOPT_2_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_BONDOPT_2_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_2_PD_EN)
#define IOMUX_BONDOPT_2_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_2_PD_EN, 1)
#define IOMUX_BONDOPT_2_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_BONDOPT_2_PD_EN, 0)

/*
 *  IOMUX_EXT_RST_N_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_EXT_RST_N_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_EXT_RST_N_PD_EN)
#define IOMUX_EXT_RST_N_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_EXT_RST_N_PD_EN, 1)
#define IOMUX_EXT_RST_N_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_EXT_RST_N_PD_EN, 0)

/*
 *  IOMUX_FLASHSPI_CS_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_CS_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_CS_PD_EN)
#define IOMUX_FLASHSPI_CS_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_CS_PD_EN, 1)
#define IOMUX_FLASHSPI_CS_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_CS_PD_EN, 0)

/*
 *  IOMUX_FLASHSPI_SCLK_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SCLK_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SCLK_PD_EN)
#define IOMUX_FLASHSPI_SCLK_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SCLK_PD_EN, 1)
#define IOMUX_FLASHSPI_SCLK_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SCLK_PD_EN, 0)

/*
 *  IOMUX_FLASHSPI_SIO0_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO0_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO0_PD_EN)
#define IOMUX_FLASHSPI_SIO0_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO0_PD_EN, 1)
#define IOMUX_FLASHSPI_SIO0_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO0_PD_EN, 0)

/*
 *  IOMUX_FLASHSPI_SIO1_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO1_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO1_PD_EN)
#define IOMUX_FLASHSPI_SIO1_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO1_PD_EN, 1)
#define IOMUX_FLASHSPI_SIO1_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO1_PD_EN, 0)

/*
 *  IOMUX_FLASHSPI_SIO2_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO2_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO2_PD_EN)
#define IOMUX_FLASHSPI_SIO2_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO2_PD_EN, 1)
#define IOMUX_FLASHSPI_SIO2_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO2_PD_EN, 0)

/*
 *  IOMUX_FLASHSPI_SIO3_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_FLASHSPI_SIO3_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO3_PD_EN)
#define IOMUX_FLASHSPI_SIO3_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO3_PD_EN, 1)
#define IOMUX_FLASHSPI_SIO3_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_FLASHSPI_SIO3_PD_EN, 0)

/*
 *  IOMUX_JTAG_TCK_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_JTAG_TCK_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TCK_PD_EN)
#define IOMUX_JTAG_TCK_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TCK_PD_EN, 1)
#define IOMUX_JTAG_TCK_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TCK_PD_EN, 0)

/*
 *  IOMUX_JTAG_TDI_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_JTAG_TDI_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TDI_PD_EN)
#define IOMUX_JTAG_TDI_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TDI_PD_EN, 1)
#define IOMUX_JTAG_TDI_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TDI_PD_EN, 0)

/*
 *  IOMUX_JTAG_TDO_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_JTAG_TDO_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TDO_PD_EN)
#define IOMUX_JTAG_TDO_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TDO_PD_EN, 1)
#define IOMUX_JTAG_TDO_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TDO_PD_EN, 0)

/*
 *  IOMUX_JTAG_TMS_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_JTAG_TMS_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TMS_PD_EN)
#define IOMUX_JTAG_TMS_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TMS_PD_EN, 1)
#define IOMUX_JTAG_TMS_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_TMS_PD_EN, 0)

/*
 *  IOMUX_JTAG_nTRST_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_JTAG_nTRST_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_JTAG_nTRST_PD_EN)
#define IOMUX_JTAG_nTRST_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_nTRST_PD_EN, 1)
#define IOMUX_JTAG_nTRST_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_JTAG_nTRST_PD_EN, 0)

/*
 *  IOMUX_PROG_MODE120P_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_PROG_MODE120P_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_PROG_MODE120P_PD_EN)
#define IOMUX_PROG_MODE120P_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_PROG_MODE120P_PD_EN, 1)
#define IOMUX_PROG_MODE120P_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_PROG_MODE120P_PD_EN, 0)

/*
 *  IOMUX_PROG_MODE68P_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_PROG_MODE68P_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_PROG_MODE68P_PD_EN)
#define IOMUX_PROG_MODE68P_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_PROG_MODE68P_PD_EN, 1)
#define IOMUX_PROG_MODE68P_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_PROG_MODE68P_PD_EN, 0)

/*
 *  IOMUX_TEST_EN_PD_EN bit field macros
 ****************************************************************************************
 */
#define IOMUX_TEST_EN_PD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_TEST_EN_PD_EN)
#define IOMUX_TEST_EN_PD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_TEST_EN_PD_EN, 1)
#define IOMUX_TEST_EN_PD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_TEST_EN_PD_EN, 0)


/*
 *  IOMUX_DEBUG_CONTROL register macros
 ****************************************************************************************
 */
#define IOMUX_DEBUG_CONTROL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_DEBUG_CONTROL))
#define IOMUX_DEBUG_CONTROL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_DEBUG_CONTROL, (value))
#define IOMUX_DEBUG_CONTROL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_DEBUG_CONTROL, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_DEBUG_CONTROL) | (value))
#define IOMUX_DEBUG_CONTROL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_DEBUG_CONTROL, GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_DEBUG_CONTROL) & (~(value)))

/*
 *  IOMUX_DEBUG_CONTROL_SWAP bit field macros
 ****************************************************************************************
 */
#define IOMUX_DEBUG_CONTROL_SWAP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_SWAP)
#define IOMUX_DEBUG_CONTROL_SWAP_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_SWAP, (value))

/*
 *  IOMUX_DEBUG_CONTROL_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_DEBUG_CONTROL_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_SEL)
#define IOMUX_DEBUG_CONTROL_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_SEL, (value))

/*
 *  IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL bit field macros
 ****************************************************************************************
 */
#define IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL)
#define IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL, 1)
#define IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, IOMUX_DEBUG_CONTROL_TRACE_MUX_SEL, 0)


/*
 *  IOMUX_STRAP_READ register macros
 ****************************************************************************************
 */
#define IOMUX_STRAP_READ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, IOMUX_STRAP_READ))

/*
 *  IOMUX_STRAP_READ_PROG_MODE68P bit field macros
 ****************************************************************************************
 */
#define IOMUX_STRAP_READ_PROG_MODE68P_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_STRAP_READ_PROG_MODE68P)

/*
 *  IOMUX_STRAP_READ_PROG_MODE120P bit field macros
 ****************************************************************************************
 */
#define IOMUX_STRAP_READ_PROG_MODE120P_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_STRAP_READ_PROG_MODE120P)

/*
 *  IOMUX_STRAP_READ_BONDOPT2 bit field macros
 ****************************************************************************************
 */
#define IOMUX_STRAP_READ_BONDOPT2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_STRAP_READ_BONDOPT2)

/*
 *  IOMUX_STRAP_READ_BONDOPT1 bit field macros
 ****************************************************************************************
 */
#define IOMUX_STRAP_READ_BONDOPT1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_STRAP_READ_BONDOPT1)

/*
 *  IOMUX_STRAP_READ_BONDOPT0 bit field macros
 ****************************************************************************************
 */
#define IOMUX_STRAP_READ_BONDOPT0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, IOMUX_STRAP_READ_BONDOPT0)

#endif
