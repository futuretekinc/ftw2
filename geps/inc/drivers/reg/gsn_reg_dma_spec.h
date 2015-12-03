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
 * $RCSfile: gsn_reg_dma_spec.h,v $
 *
 * Description:
 *      This file contains register specification for DMA Driver
 *
 ******************************************************************************
 */

#ifndef _REG_DMA_MAC_H
#define _REG_DMA_MAC_H

/***************************************************
 *
 *             DMA
 *
 ***************************************************/


/*
 *  DMA_STATUS register macros
 ****************************************************************************************
 */
#define DMA_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_STATUS))

/*
 *  DMA_TS bit field macros
 ****************************************************************************************
 */
#define DMA_TS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_TS)
#define DMA_TS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, DMA_TS, (value))

/*
 *  DMA_CHS bit field macros
 ****************************************************************************************
 */
#define DMA_CHS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_CHS)
#define DMA_CHS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, DMA_CHS, (value))

/*
 *  DMA_ST bit field macros
 ****************************************************************************************
 */
#define DMA_ST_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ST)
#define DMA_ST_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, DMA_ST, (value))

/*
 *  DMA_ME bit field macros
 ****************************************************************************************
 */
#define DMA_ME_RO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ME)


/*
 *  DMA_CONFIG register macros
 ****************************************************************************************
 */
#define DMA_CONFIG_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CONFIG))
#define DMA_CONFIG_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CONFIG, (value))
#define DMA_CONFIG_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CONFIG, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CONFIG) | (value))
#define DMA_CONFIG_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CONFIG, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CONFIG) & (~(value)))

/*
 *  DMA_CPC bit field macros
 ****************************************************************************************
 */
#define DMA_CPC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_CPC)
#define DMA_CPC_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, DMA_CPC, (value))

/*
 *  DMA_ME bit field macros
 ****************************************************************************************
 */
#define DMA_ME_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ME)
#define DMA_ME_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ME, 1)
#define DMA_ME_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ME, 0)


/*
 *  DMA_CCDBP register macros
 ****************************************************************************************
 */
#define DMA_CCDBP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CCDBP))
#define DMA_CCDBP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CCDBP, (value))
#define DMA_CCDBP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CCDBP, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CCDBP) | (value))
#define DMA_CCDBP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CCDBP, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CCDBP) & (~(value)))

/*
 *  DMA_ECRVAL bit field macros
 ****************************************************************************************
 */
#define DMA_ECRVAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ECRVAL)
#define DMA_ECRVAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, DMA_ECRVAL, (value))


/*
 *  DMA_CACDBP register macros
 ****************************************************************************************
 */
#define DMA_CACDBP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CACDBP))

/*
 *  DMA_BP bit field macros
 ****************************************************************************************
 */
#define DMA_BP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_BP)
#define DMA_BP_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, DMA_BP, (value))


/*
 *  DMA_CWRS register macros
 ****************************************************************************************
 */
#define DMA_CWRS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CWRS))
#define DMA_CWRS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CWRS, (value))
#define DMA_CWRS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CWRS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CWRS) | (value))
#define DMA_CWRS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CWRS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CWRS) & (~(value)))

/*
 *  DMA_RS2 bit field macros
 ****************************************************************************************
 */
#define DMA_RS2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RS2)
#define DMA_RS2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RS2, 1)
#define DMA_RS2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RS2, 0)

/*
 *  DMA_RS1 bit field macros
 ****************************************************************************************
 */
#define DMA_RS1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RS1)
#define DMA_RS1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RS1, 1)
#define DMA_RS1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RS1, 0)

/*
 *  DMA_RS0 bit field macros
 ****************************************************************************************
 */
#define DMA_RS0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RS0)
#define DMA_RS0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RS0, 1)
#define DMA_RS0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RS0, 0)


/*
 *  DMA_CSR register macros
 ****************************************************************************************
 */
#define DMA_CSR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CSR))
#define DMA_CSR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CSR, (value))
#define DMA_CSR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CSR, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CSR) | (value))
#define DMA_CSR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CSR, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CSR) & (~(value)))

/*
 *  DMA_SR2 bit field macros
 ****************************************************************************************
 */
#define DMA_SR2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_SR2)
#define DMA_SR2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_SR2, 1)
#define DMA_SR2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_SR2, 0)

/*
 *  DMA_SR1 bit field macros
 ****************************************************************************************
 */
#define DMA_SR1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_SR1)
#define DMA_SR1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_SR1, 1)
#define DMA_SR1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_SR1, 0)

/*
 *  DMA_SR0 bit field macros
 ****************************************************************************************
 */
#define DMA_SR0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_SR0)
#define DMA_SR0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_SR0, 1)
#define DMA_SR0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_SR0, 0)


/*
 *  DMA_CUBS register macros
 ****************************************************************************************
 */
#define DMA_CUBS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBS))
#define DMA_CUBS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBS, (value))
#define DMA_CUBS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBS) | (value))
#define DMA_CUBS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBS) & (~(value)))

/*
 *  DMA_UBS2 bit field macros
 ****************************************************************************************
 */
#define DMA_UBS2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_UBS2)
#define DMA_UBS2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBS2, 1)
#define DMA_UBS2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBS2, 0)

/*
 *  DMA_UBS1 bit field macros
 ****************************************************************************************
 */
#define DMA_UBS1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_UBS1)
#define DMA_UBS1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBS1, 1)
#define DMA_UBS1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBS1, 0)

/*
 *  DMA_UBS0 bit field macros
 ****************************************************************************************
 */
#define DMA_UBS0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_UBS0)
#define DMA_UBS0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBS0, 1)
#define DMA_UBS0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBS0, 0)


/*
 *  DMA_CUBC register macros
 ****************************************************************************************
 */
#define DMA_CUBC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBC))
#define DMA_CUBC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBC, (value))
#define DMA_CUBC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBC) | (value))
#define DMA_CUBC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CUBC) & (~(value)))

/*
 *  DMA_UBC2 bit field macros
 ****************************************************************************************
 */
#define DMA_UBC2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_UBC2)
#define DMA_UBC2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBC2, 1)
#define DMA_UBC2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBC2, 0)

/*
 *  DMA_UBC1 bit field macros
 ****************************************************************************************
 */
#define DMA_UBC1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_UBC1)
#define DMA_UBC1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBC1, 1)
#define DMA_UBC1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBC1, 0)

/*
 *  DMA_UBC0 bit field macros
 ****************************************************************************************
 */
#define DMA_UBC0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_UBC0)
#define DMA_UBC0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBC0, 1)
#define DMA_UBC0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_UBC0, 0)


/*
 *  DMA_CRMS register macros
 ****************************************************************************************
 */
#define DMA_CRMS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMS))
#define DMA_CRMS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMS, (value))
#define DMA_CRMS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMS) | (value))
#define DMA_CRMS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMS) & (~(value)))

/*
 *  DMA_RMS2 bit field macros
 ****************************************************************************************
 */
#define DMA_RMS2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RMS2)
#define DMA_RMS2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMS2, 1)
#define DMA_RMS2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMS2, 0)

/*
 *  DMA_RMS1 bit field macros
 ****************************************************************************************
 */
#define DMA_RMS1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RMS1)
#define DMA_RMS1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMS1, 1)
#define DMA_RMS1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMS1, 0)

/*
 *  DMA_RMS0 bit field macros
 ****************************************************************************************
 */
#define DMA_RMS0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RMS0)
#define DMA_RMS0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMS0, 1)
#define DMA_RMS0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMS0, 0)


/*
 *  DMA_CRMC register macros
 ****************************************************************************************
 */
#define DMA_CRMC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMC))
#define DMA_CRMC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMC, (value))
#define DMA_CRMC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMC) | (value))
#define DMA_CRMC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CRMC) & (~(value)))

/*
 *  DMA_RMC2 bit field macros
 ****************************************************************************************
 */
#define DMA_RMC2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RMC2)
#define DMA_RMC2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMC2, 1)
#define DMA_RMC2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMC2, 0)

/*
 *  DMA_RMC1 bit field macros
 ****************************************************************************************
 */
#define DMA_RMC1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RMC1)
#define DMA_RMC1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMC1, 1)
#define DMA_RMC1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMC1, 0)

/*
 *  DMA_RMC0 bit field macros
 ****************************************************************************************
 */
#define DMA_RMC0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_RMC0)
#define DMA_RMC0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMC0, 1)
#define DMA_RMC0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_RMC0, 0)


/*
 *  DMA_CES register macros
 ****************************************************************************************
 */
#define DMA_CES_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CES))
#define DMA_CES_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CES, (value))
#define DMA_CES_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CES, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CES) | (value))
#define DMA_CES_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CES, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CES) & (~(value)))

/*
 *  DMA_ENS2 bit field macros
 ****************************************************************************************
 */
#define DMA_ENS2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ENS2)
#define DMA_ENS2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENS2, 1)
#define DMA_ENS2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENS2, 0)

/*
 *  DMA_ENS1 bit field macros
 ****************************************************************************************
 */
#define DMA_ENS1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ENS1)
#define DMA_ENS1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENS1, 1)
#define DMA_ENS1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENS1, 0)

/*
 *  DMA_ENS0 bit field macros
 ****************************************************************************************
 */
#define DMA_ENS0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ENS0)
#define DMA_ENS0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENS0, 1)
#define DMA_ENS0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENS0, 0)


/*
 *  DMA_CEC register macros
 ****************************************************************************************
 */
#define DMA_CEC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CEC))
#define DMA_CEC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CEC, (value))
#define DMA_CEC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CEC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CEC) | (value))
#define DMA_CEC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CEC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CEC) & (~(value)))

/*
 *  DMA_ENC2 bit field macros
 ****************************************************************************************
 */
#define DMA_ENC2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ENC2)
#define DMA_ENC2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENC2, 1)
#define DMA_ENC2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENC2, 0)

/*
 *  DMA_ENC1 bit field macros
 ****************************************************************************************
 */
#define DMA_ENC1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ENC1)
#define DMA_ENC1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENC1, 1)
#define DMA_ENC1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENC1, 0)

/*
 *  DMA_ENC0 bit field macros
 ****************************************************************************************
 */
#define DMA_ENC0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_ENC0)
#define DMA_ENC0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENC0, 1)
#define DMA_ENC0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_ENC0, 0)


/*
 *  DMA_CPAS register macros
 ****************************************************************************************
 */
#define DMA_CPAS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAS))
#define DMA_CPAS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAS, (value))
#define DMA_CPAS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAS) | (value))
#define DMA_CPAS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAS) & (~(value)))

/*
 *  DMA_PAS2 bit field macros
 ****************************************************************************************
 */
#define DMA_PAS2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PAS2)
#define DMA_PAS2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAS2, 1)
#define DMA_PAS2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAS2, 0)

/*
 *  DMA_PAS1 bit field macros
 ****************************************************************************************
 */
#define DMA_PAS1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PAS1)
#define DMA_PAS1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAS1, 1)
#define DMA_PAS1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAS1, 0)

/*
 *  DMA_PAS0 bit field macros
 ****************************************************************************************
 */
#define DMA_PAS0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PAS0)
#define DMA_PAS0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAS0, 1)
#define DMA_PAS0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAS0, 0)


/*
 *  DMA_CPAC register macros
 ****************************************************************************************
 */
#define DMA_CPAC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAC))
#define DMA_CPAC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAC, (value))
#define DMA_CPAC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAC) | (value))
#define DMA_CPAC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPAC) & (~(value)))

/*
 *  DMA_PAC2 bit field macros
 ****************************************************************************************
 */
#define DMA_PAC2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PAC2)
#define DMA_PAC2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAC2, 1)
#define DMA_PAC2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAC2, 0)

/*
 *  DMA_PAC1 bit field macros
 ****************************************************************************************
 */
#define DMA_PAC1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PAC1)
#define DMA_PAC1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAC1, 1)
#define DMA_PAC1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAC1, 0)

/*
 *  DMA_PAC0 bit field macros
 ****************************************************************************************
 */
#define DMA_PAC0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PAC0)
#define DMA_PAC0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAC0, 1)
#define DMA_PAC0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PAC0, 0)


/*
 *  DMA_CPS register macros
 ****************************************************************************************
 */
#define DMA_CPS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPS))
#define DMA_CPS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPS, (value))
#define DMA_CPS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPS) | (value))
#define DMA_CPS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPS, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPS) & (~(value)))

/*
 *  DMA_PS2 bit field macros
 ****************************************************************************************
 */
#define DMA_PS2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PS2)
#define DMA_PS2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PS2, 1)
#define DMA_PS2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PS2, 0)

/*
 *  DMA_PS1 bit field macros
 ****************************************************************************************
 */
#define DMA_PS1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PS1)
#define DMA_PS1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PS1, 1)
#define DMA_PS1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PS1, 0)

/*
 *  DMA_PS0 bit field macros
 ****************************************************************************************
 */
#define DMA_PS0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PS0)
#define DMA_PS0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PS0, 1)
#define DMA_PS0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PS0, 0)


/*
 *  DMA_CPC register macros
 ****************************************************************************************
 */
#define DMA_CPRC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPC))
#define DMA_CPRC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPC, (value))
#define DMA_CPRC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPC) | (value))
#define DMA_CPRC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_CPC) & (~(value)))

/*
 *  DMA_PC2 bit field macros
 ****************************************************************************************
 */
#define DMA_PC2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PC2)
#define DMA_PC2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PC2, 1)
#define DMA_PC2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PC2, 0)

/*
 *  DMA_PC1 bit field macros
 ****************************************************************************************
 */
#define DMA_PC1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PC1)
#define DMA_PC1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PC1, 1)
#define DMA_PC1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PC1, 0)

/*
 *  DMA_PC0 bit field macros
 ****************************************************************************************
 */
#define DMA_PC0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_PC0)
#define DMA_PC0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PC0, 1)
#define DMA_PC0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_PC0, 0)


/*
 *  DMA_BEC register macros
 ****************************************************************************************
 */
#define DMA_BEC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_BEC))
#define DMA_BEC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_BEC, (value))
#define DMA_BEC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_BEC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_BEC) | (value))
#define DMA_BEC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_BEC, GET_WORD_EXCLUSIVE_BITFIELD(addr, DMA_BEC) & (~(value)))

/*
 *  DMA_EC bit field macros
 ****************************************************************************************
 */
#define DMA_EC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, DMA_EC)
#define DMA_EC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_EC, 1)
#define DMA_EC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, DMA_EC, 0)

#endif
