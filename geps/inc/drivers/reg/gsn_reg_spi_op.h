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
 * $RCSfile: gsn_reg_spi_op.h,v $
 *
 * Description:
 *      This file contains register macros for SPI Driver
 *
 ******************************************************************************
 */

#ifndef _REG_SPI_MAC_H
#define _REG_SPI_MAC_H

/***************************************************
 *
 *             SPI
 *
 ***************************************************/


/*
 *  SPI_SPICR0 register macros
 ****************************************************************************************
 */
#define SPI_SPICR0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR0))
#define SPI_SPICR0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR0, (value))
#define SPI_SPICR0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR0, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR0) | (value))
#define SPI_SPICR0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR0, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR0) & (~(value)))

/*
 *  SPI_SCR bit field macros
 ****************************************************************************************
 */
#define SPI_SCR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_SCR)
#define SPI_SCR_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SPI_SCR, (value))

/*
 *  SPI_SPH bit field macros
 ****************************************************************************************
 */
#define SPI_SPH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_SPH)
#define SPI_SPH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SPH, 1)
#define SPI_SPH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SPH, 0)

/*
 *  SPI_SPO bit field macros
 ****************************************************************************************
 */
#define SPI_SPO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_SPO)
#define SPI_SPO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SPO, 1)
#define SPI_SPO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SPO, 0)

/*
 *  SPI_FRF bit field macros
 ****************************************************************************************
 */
#define SPI_FRF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_FRF)
#define SPI_FRF_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SPI_FRF, (value))

/*
 *  SPI_DSS bit field macros
 ****************************************************************************************
 */
#define SPI_DSS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_DSS)
#define SPI_DSS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SPI_DSS, (value))


/*
 *  SPI_SPICR1 register macros
 ****************************************************************************************
 */
#define SPI_SPICR1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR1))
#define SPI_SPICR1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR1, (value))
#define SPI_SPICR1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR1, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR1) | (value))
#define SPI_SPICR1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR1, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICR1) & (~(value)))

/*
 *  SPI_SOD bit field macros
 ****************************************************************************************
 */
#define SPI_SOD_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_SOD)
#define SPI_SOD_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SOD, 1)
#define SPI_SOD_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SOD, 0)

/*
 *  SPI_MS bit field macros
 ****************************************************************************************
 */
#define SPI_MS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_MS)
#define SPI_MS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_MS, 1)
#define SPI_MS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_MS, 0)

/*
 *  SPI_SSE bit field macros
 ****************************************************************************************
 */
#define SPI_SSE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_SSE)
#define SPI_SSE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SSE, 1)
#define SPI_SSE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_SSE, 0)

/*
 *  SPI_LBM bit field macros
 ****************************************************************************************
 */
#define SPI_LBM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_LBM)
#define SPI_LBM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_LBM, 1)
#define SPI_LBM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_LBM, 0)


/*
 *  SPI_SPIDR register macros
 ****************************************************************************************
 */
#define SPI_SPIDR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDR))
#define SPI_SPIDR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDR, (value))
#define SPI_SPIDR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDR) | (value))
#define SPI_SPIDR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDR) & (~(value)))

/*
 *  SPI_DATA bit field macros
 ****************************************************************************************
 */
#define SPI_DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_DATA)
#define SPI_DATA_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SPI_DATA, (value))


/*
 *  SPI_SPISR register macros
 ****************************************************************************************
 */
#define SPI_SPISR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPISR))

/*
 *  SPI_BSY bit field macros
 ****************************************************************************************
 */
#define SPI_BSY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_BSY)

/*
 *  SPI_RFF bit field macros
 ****************************************************************************************
 */
#define SPI_RFF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RFF)

/*
 *  SPI_RNE bit field macros
 ****************************************************************************************
 */
#define SPI_RNE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RNE)

/*
 *  SPI_TNF bit field macros
 ****************************************************************************************
 */
#define SPI_TNF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_TNF)

/*
 *  SPI_TFE bit field macros
 ****************************************************************************************
 */
#define SPI_TFE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_TFE)


/*
 *  SPI_SPICPSR register macros
 ****************************************************************************************
 */
#define SPI_SPICPSR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICPSR))
#define SPI_SPICPSR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICPSR, (value))
#define SPI_SPICPSR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICPSR, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICPSR) | (value))
#define SPI_SPICPSR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICPSR, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPICPSR) & (~(value)))

/*
 *  SPI_CPSDVSR bit field macros
 ****************************************************************************************
 */
#define SPI_CPSDVSR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_CPSDVSR)
#define SPI_CPSDVSR_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, SPI_CPSDVSR, (value))


/*
 *  SPI_SPIMSC register macros
 ****************************************************************************************
 */
#define SPI_SPIMSC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMSC))
#define SPI_SPIMSC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMSC, (value))
#define SPI_SPIMSC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMSC, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMSC) | (value))
#define SPI_SPIMSC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMSC, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMSC) & (~(value)))

/*
 *  SPI_TXIM bit field macros
 ****************************************************************************************
 */
#define SPI_TXIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_TXIM)
#define SPI_TXIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_TXIM, 1)
#define SPI_TXIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_TXIM, 0)

/*
 *  SPI_RXIM bit field macros
 ****************************************************************************************
 */
#define SPI_RXIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RXIM)
#define SPI_RXIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RXIM, 1)
#define SPI_RXIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RXIM, 0)

/*
 *  SPI_RTIM bit field macros
 ****************************************************************************************
 */
#define SPI_RTIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RTIM)
#define SPI_RTIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RTIM, 1)
#define SPI_RTIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RTIM, 0)

/*
 *  SPI_RORIM bit field macros
 ****************************************************************************************
 */
#define SPI_RORIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RORIM)
#define SPI_RORIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RORIM, 1)
#define SPI_RORIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RORIM, 0)
          

/*
 *  SPI_SPIMIS register macros
 ****************************************************************************************
 */
#define SPI_SPIMIS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIMIS))

/*
 *  SPI_TXMIS bit field macros
 ****************************************************************************************
 */
#define SPI_TXMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_TXMIS)

/*
 *  SPI_RXMIS bit field macros
 ****************************************************************************************
 */
#define SPI_RXMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RXMIS)

/*
 *  SPI_RTMIS bit field macros
 ****************************************************************************************
 */
#define SPI_RTMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RTMIS)

/*
 *  SPI_RORMIS bit field macros
 ****************************************************************************************
 */
#define SPI_RORMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RORMIS)


/*
 *  SPI_SPIICR register macros
 ****************************************************************************************
 */
#define SPI_SPIICR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIICR, (value))

/*
 *  SPI_RTIC bit field macros
 ****************************************************************************************
 */
#define SPI_RTIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RTIC, 1)
#define SPI_RTIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RTIC, 0)

/*
 *  SPI_RORIC bit field macros
 ****************************************************************************************
 */
#define SPI_RORIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RORIC, 1)
#define SPI_RORIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RORIC, 0)


/*
 *  SPI_SPIDMACR register macros
 ****************************************************************************************
 */
#define SPI_SPIDMACR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDMACR))
#define SPI_SPIDMACR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDMACR, (value))
#define SPI_SPIDMACR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDMACR, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDMACR) | (value))
#define SPI_SPIDMACR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDMACR, GET_WORD_EXCLUSIVE_BITFIELD(addr, SPI_SPIDMACR) & (~(value)))

/*
 *  SPI_TXDMAE bit field macros
 ****************************************************************************************
 */
#define SPI_TXDMAE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_TXDMAE)
#define SPI_TXDMAE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_TXDMAE, 1)
#define SPI_TXDMAE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_TXDMAE, 0)

/*
 *  SPI_RXDMAE bit field macros
 ****************************************************************************************
 */
#define SPI_RXDMAE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SPI_RXDMAE)
#define SPI_RXDMAE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RXDMAE, 1)
#define SPI_RXDMAE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SPI_RXDMAE, 0)
          
#endif
