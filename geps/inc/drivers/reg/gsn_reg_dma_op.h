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
 * $RCSfile: gsn_reg_dma_op.h,v $
 *
 * Description:
 *      This file contains register macros for DMA Driver
 *
 ******************************************************************************
 */

#ifndef _REG_DMA_H
#define _REG_DMA_H

/***************************************************
 *
 *             DMA
 *
 ***************************************************/


/*
 *  DMA_CTRL instance offsets
 ****************************************************************************************
 */
#define DMA_CTRL 0x40060000

/*
 *  DMA_STATUS register defines
 ****************************************************************************************
 */
#define DMA_STATUS_OFFSETADDRESS       0x00000000  /* R */
#define DMA_STATUS_BITOFFSET           0
#define DMA_STATUS_BITFIELDSIZE        32
#define DMA_STATUS_BITMASK             0xFFFFFFFF
#define DMA_STATUS_INIT                0x00000000
/*
 *  DMA_TS bit field defines
 ****************************************************************************************
 */
#define DMA_TS_OFFSETADDRESS                    DMA_STATUS_OFFSETADDRESS
#define DMA_TS_BITOFFSET                       28
#define DMA_TS_BITFIELDSIZE                     4
#define DMA_TS_BITMASK                          0xf0000000
#define DMA_TS_INIT                             0x0
/*
 *  DMA_CHS bit field defines
 ****************************************************************************************
 */
#define DMA_CHS_OFFSETADDRESS                   DMA_STATUS_OFFSETADDRESS
#define DMA_CHS_BITOFFSET                      16
#define DMA_CHS_BITFIELDSIZE                    5
#define DMA_CHS_BITMASK                         0x001f0000
#define DMA_CHS_INIT                            0x0
/*
 *  DMA_ST bit field defines
 ****************************************************************************************
 */
#define DMA_ST_OFFSETADDRESS                    DMA_STATUS_OFFSETADDRESS
#define DMA_ST_BITOFFSET                        4
#define DMA_ST_BITFIELDSIZE                     4
#define DMA_ST_BITMASK                          0x000000f0
#define DMA_ST_INIT                             0x0
/*
 *  DMA_ME bit field defines
 ****************************************************************************************
 */
#define DMA_ME_RO_OFFSETADDRESS                 DMA_STATUS_OFFSETADDRESS
#define DMA_ME_RO_BITOFFSET                        0
#define DMA_ME_RO_BITFIELDSIZE                     1
#define DMA_ME_RO_BITMASK                          0x00000001
#define DMA_ME_RO_INIT                             0x0

/*
 *  DMA_CONFIG register defines
 ****************************************************************************************
 */
#define DMA_CONFIG_OFFSETADDRESS       0x00000004  /* RW */
#define DMA_CONFIG_BITOFFSET           0
#define DMA_CONFIG_BITFIELDSIZE        32
#define DMA_CONFIG_BITMASK             0xFFFFFFFF
#define DMA_CONFIG_INIT                0x00000000
/*
 *  DMA_CPC bit field defines
 ****************************************************************************************
 */
#define DMA_CPC_CONFIG_OFFSETADDRESS            DMA_CONFIG_OFFSETADDRESS
#define DMA_CPC_CONFIG_BITOFFSET                5
#define DMA_CPC_CONFIG_BITFIELDSIZE             3
#define DMA_CPC_CONFIG_BITMASK                  0x000000e0
#define DMA_CPC_CONFIG_INIT                     0x0
/*
 *  DMA_ME bit field defines
 ****************************************************************************************
 */
#define DMA_ME_OFFSETADDRESS                    DMA_CONFIG_OFFSETADDRESS
#define DMA_ME_BITOFFSET                        0
#define DMA_ME_BITFIELDSIZE                     1
#define DMA_ME_BITMASK                          0x00000001
#define DMA_ME_INIT                             0x0

/*
 *  DMA_CCDBP register defines
 ****************************************************************************************
 */
#define DMA_CCDBP_OFFSETADDRESS        0x00000008  /* RW */
#define DMA_CCDBP_BITOFFSET            0
#define DMA_CCDBP_BITFIELDSIZE         32
#define DMA_CCDBP_BITMASK              0xFFFFFFFF
#define DMA_CCDBP_INIT                 0x00000000
/*
 *  DMA_ECRVAL bit field defines
 ****************************************************************************************
 */
#define DMA_ECRVAL_OFFSETADDRESS                DMA_CCDBP_OFFSETADDRESS
#define DMA_ECRVAL_BITOFFSET                    0
#define DMA_ECRVAL_BITFIELDSIZE                 8
#define DMA_ECRVAL_BITMASK                      0x000000ff
#define DMA_ECRVAL_INIT                         0x0

/*
 *  DMA_CACDBP register defines
 ****************************************************************************************
 */
#define DMA_CACDBP_OFFSETADDRESS       0x0000000c  /* R */
#define DMA_CACDBP_BITOFFSET           0
#define DMA_CACDBP_BITFIELDSIZE        32
#define DMA_CACDBP_BITMASK             0xFFFFFFFF
#define DMA_CACDBP_INIT                0x00000090
/*
 *  DMA_BP bit field defines
 ****************************************************************************************
 */
#define DMA_BP_OFFSETADDRESS                    DMA_CACDBP_OFFSETADDRESS
#define DMA_BP_BITOFFSET                        0
#define DMA_BP_BITFIELDSIZE                     31
#define DMA_BP_BITMASK                          0x7fffffff
#define DMA_BP_INIT                             0x90

/*
 *  DMA_CWRS register defines
 ****************************************************************************************
 */
#define DMA_CWRS_OFFSETADDRESS         0x00000010  /* RW */
#define DMA_CWRS_BITOFFSET             0
#define DMA_CWRS_BITFIELDSIZE          32
#define DMA_CWRS_BITMASK               0xFFFFFFFF
#define DMA_CWRS_INIT                  0x00000000
/*
 *  DMA_RS2 bit field defines
 ****************************************************************************************
 */
#define DMA_RS2_OFFSETADDRESS                   DMA_CWRS_OFFSETADDRESS
#define DMA_RS2_BITOFFSET                       2
#define DMA_RS2_BITFIELDSIZE                    1
#define DMA_RS2_BITMASK                         0x00000004
#define DMA_RS2_INIT                            0x0
/*
 *  DMA_RS1 bit field defines
 ****************************************************************************************
 */
#define DMA_RS1_OFFSETADDRESS                   DMA_CWRS_OFFSETADDRESS
#define DMA_RS1_BITOFFSET                       1
#define DMA_RS1_BITFIELDSIZE                    1
#define DMA_RS1_BITMASK                         0x00000002
#define DMA_RS1_INIT                            0x0
/*
 *  DMA_RS0 bit field defines
 ****************************************************************************************
 */
#define DMA_RS0_OFFSETADDRESS                   DMA_CWRS_OFFSETADDRESS
#define DMA_RS0_BITOFFSET                       0
#define DMA_RS0_BITFIELDSIZE                    1
#define DMA_RS0_BITMASK                         0x00000001
#define DMA_RS0_INIT                            0x0

/*
 *  DMA_CSR register defines
 ****************************************************************************************
 */
#define DMA_CSR_OFFSETADDRESS          0x00000014  /* RW */
#define DMA_CSR_BITOFFSET              0
#define DMA_CSR_BITFIELDSIZE           32
#define DMA_CSR_BITMASK                0xFFFFFFFF
#define DMA_CSR_INIT                   0x00000000
/*
 *  DMA_SR2 bit field defines
 ****************************************************************************************
 */
#define DMA_SR2_OFFSETADDRESS                   DMA_CSR_OFFSETADDRESS
#define DMA_SR2_BITOFFSET                       2
#define DMA_SR2_BITFIELDSIZE                    1
#define DMA_SR2_BITMASK                         0x00000004
#define DMA_SR2_INIT                            0x0
/*
 *  DMA_SR1 bit field defines
 ****************************************************************************************
 */
#define DMA_SR1_OFFSETADDRESS                   DMA_CSR_OFFSETADDRESS
#define DMA_SR1_BITOFFSET                       1
#define DMA_SR1_BITFIELDSIZE                    1
#define DMA_SR1_BITMASK                         0x00000002
#define DMA_SR1_INIT                            0x0
/*
 *  DMA_SR0 bit field defines
 ****************************************************************************************
 */
#define DMA_SR0_OFFSETADDRESS                   DMA_CSR_OFFSETADDRESS
#define DMA_SR0_BITOFFSET                       0
#define DMA_SR0_BITFIELDSIZE                    1
#define DMA_SR0_BITMASK                         0x00000001
#define DMA_SR0_INIT                            0x0

/*
 *  DMA_CUBS register defines
 ****************************************************************************************
 */
#define DMA_CUBS_OFFSETADDRESS         0x00000018  /* RW */
#define DMA_CUBS_BITOFFSET             0
#define DMA_CUBS_BITFIELDSIZE          32
#define DMA_CUBS_BITMASK               0xFFFFFFFF
#define DMA_CUBS_INIT                  0x00000000
/*
 *  DMA_UBS2 bit field defines
 ****************************************************************************************
 */
#define DMA_UBS2_OFFSETADDRESS                  DMA_CUBS_OFFSETADDRESS
#define DMA_UBS2_BITOFFSET                      2
#define DMA_UBS2_BITFIELDSIZE                   1
#define DMA_UBS2_BITMASK                        0x00000004
#define DMA_UBS2_INIT                           0x0
/*
 *  DMA_UBS1 bit field defines
 ****************************************************************************************
 */
#define DMA_UBS1_OFFSETADDRESS                  DMA_CUBS_OFFSETADDRESS
#define DMA_UBS1_BITOFFSET                      1
#define DMA_UBS1_BITFIELDSIZE                   1
#define DMA_UBS1_BITMASK                        0x00000002
#define DMA_UBS1_INIT                           0x0
/*
 *  DMA_UBS0 bit field defines
 ****************************************************************************************
 */
#define DMA_UBS0_OFFSETADDRESS                  DMA_CUBS_OFFSETADDRESS
#define DMA_UBS0_BITOFFSET                      0
#define DMA_UBS0_BITFIELDSIZE                   1
#define DMA_UBS0_BITMASK                        0x00000001
#define DMA_UBS0_INIT                           0x0

/*
 *  DMA_CUBC register defines
 ****************************************************************************************
 */
#define DMA_CUBC_OFFSETADDRESS         0x0000001c  /* RW */
#define DMA_CUBC_BITOFFSET             0
#define DMA_CUBC_BITFIELDSIZE          32
#define DMA_CUBC_BITMASK               0xFFFFFFFF
#define DMA_CUBC_INIT                  0x00000000
/*
 *  DMA_UBC2 bit field defines
 ****************************************************************************************
 */
#define DMA_UBC2_OFFSETADDRESS                  DMA_CUBC_OFFSETADDRESS
#define DMA_UBC2_BITOFFSET                      2
#define DMA_UBC2_BITFIELDSIZE                   1
#define DMA_UBC2_BITMASK                        0x00000004
#define DMA_UBC2_INIT                           0x0
/*
 *  DMA_UBC1 bit field defines
 ****************************************************************************************
 */
#define DMA_UBC1_OFFSETADDRESS                  DMA_CUBC_OFFSETADDRESS
#define DMA_UBC1_BITOFFSET                      1
#define DMA_UBC1_BITFIELDSIZE                   1
#define DMA_UBC1_BITMASK                        0x00000002
#define DMA_UBC1_INIT                           0x0
/*
 *  DMA_UBC0 bit field defines
 ****************************************************************************************
 */
#define DMA_UBC0_OFFSETADDRESS                  DMA_CUBC_OFFSETADDRESS
#define DMA_UBC0_BITOFFSET                      0
#define DMA_UBC0_BITFIELDSIZE                   1
#define DMA_UBC0_BITMASK                        0x00000001
#define DMA_UBC0_INIT                           0x0

/*
 *  DMA_CRMS register defines
 ****************************************************************************************
 */
#define DMA_CRMS_OFFSETADDRESS         0x00000020  /* RW */
#define DMA_CRMS_BITOFFSET             0
#define DMA_CRMS_BITFIELDSIZE          32
#define DMA_CRMS_BITMASK               0xFFFFFFFF
#define DMA_CRMS_INIT                  0x00000000
/*
 *  DMA_RMS2 bit field defines
 ****************************************************************************************
 */
#define DMA_RMS2_OFFSETADDRESS                  DMA_CRMS_OFFSETADDRESS
#define DMA_RMS2_BITOFFSET                      2
#define DMA_RMS2_BITFIELDSIZE                   1
#define DMA_RMS2_BITMASK                        0x00000004
#define DMA_RMS2_INIT                           0x0
/*
 *  DMA_RMS1 bit field defines
 ****************************************************************************************
 */
#define DMA_RMS1_OFFSETADDRESS                  DMA_CRMS_OFFSETADDRESS
#define DMA_RMS1_BITOFFSET                      1
#define DMA_RMS1_BITFIELDSIZE                   1
#define DMA_RMS1_BITMASK                        0x00000002
#define DMA_RMS1_INIT                           0x0
/*
 *  DMA_RMS0 bit field defines
 ****************************************************************************************
 */
#define DMA_RMS0_OFFSETADDRESS                  DMA_CRMS_OFFSETADDRESS
#define DMA_RMS0_BITOFFSET                      0
#define DMA_RMS0_BITFIELDSIZE                   1
#define DMA_RMS0_BITMASK                        0x00000001
#define DMA_RMS0_INIT                           0x0

/*
 *  DMA_CRMC register defines
 ****************************************************************************************
 */
#define DMA_CRMC_OFFSETADDRESS         0x00000024  /* RW */
#define DMA_CRMC_BITOFFSET             0
#define DMA_CRMC_BITFIELDSIZE          32
#define DMA_CRMC_BITMASK               0xFFFFFFFF
#define DMA_CRMC_INIT                  0x00000000
/*
 *  DMA_RMC2 bit field defines
 ****************************************************************************************
 */
#define DMA_RMC2_OFFSETADDRESS                  DMA_CRMC_OFFSETADDRESS
#define DMA_RMC2_BITOFFSET                      2
#define DMA_RMC2_BITFIELDSIZE                   1
#define DMA_RMC2_BITMASK                        0x00000004
#define DMA_RMC2_INIT                           0x0
/*
 *  DMA_RMC1 bit field defines
 ****************************************************************************************
 */
#define DMA_RMC1_OFFSETADDRESS                  DMA_CRMC_OFFSETADDRESS
#define DMA_RMC1_BITOFFSET                      1
#define DMA_RMC1_BITFIELDSIZE                   1
#define DMA_RMC1_BITMASK                        0x00000002
#define DMA_RMC1_INIT                           0x0
/*
 *  DMA_RMC0 bit field defines
 ****************************************************************************************
 */
#define DMA_RMC0_OFFSETADDRESS                  DMA_CRMC_OFFSETADDRESS
#define DMA_RMC0_BITOFFSET                      0
#define DMA_RMC0_BITFIELDSIZE                   1
#define DMA_RMC0_BITMASK                        0x00000001
#define DMA_RMC0_INIT                           0x0

/*
 *  DMA_CES register defines
 ****************************************************************************************
 */
#define DMA_CES_OFFSETADDRESS          0x00000028  /* RW */
#define DMA_CES_BITOFFSET              0
#define DMA_CES_BITFIELDSIZE           32
#define DMA_CES_BITMASK                0xFFFFFFFF
#define DMA_CES_INIT                   0x00000000
/*
 *  DMA_ENS2 bit field defines
 ****************************************************************************************
 */
#define DMA_ENS2_OFFSETADDRESS                  DMA_CES_OFFSETADDRESS
#define DMA_ENS2_BITOFFSET                      2
#define DMA_ENS2_BITFIELDSIZE                   1
#define DMA_ENS2_BITMASK                        0x00000004
#define DMA_ENS2_INIT                           0x0
/*
 *  DMA_ENS1 bit field defines
 ****************************************************************************************
 */
#define DMA_ENS1_OFFSETADDRESS                  DMA_CES_OFFSETADDRESS
#define DMA_ENS1_BITOFFSET                      1
#define DMA_ENS1_BITFIELDSIZE                   1
#define DMA_ENS1_BITMASK                        0x00000002
#define DMA_ENS1_INIT                           0x0
/*
 *  DMA_ENS0 bit field defines
 ****************************************************************************************
 */
#define DMA_ENS0_OFFSETADDRESS                  DMA_CES_OFFSETADDRESS
#define DMA_ENS0_BITOFFSET                      0
#define DMA_ENS0_BITFIELDSIZE                   1
#define DMA_ENS0_BITMASK                        0x00000001
#define DMA_ENS0_INIT                           0x0

/*
 *  DMA_CEC register defines
 ****************************************************************************************
 */
#define DMA_CEC_OFFSETADDRESS          0x0000002c  /* RW */
#define DMA_CEC_BITOFFSET              0
#define DMA_CEC_BITFIELDSIZE           32
#define DMA_CEC_BITMASK                0xFFFFFFFF
#define DMA_CEC_INIT                   0x00000000
/*
 *  DMA_ENC2 bit field defines
 ****************************************************************************************
 */
#define DMA_ENC2_OFFSETADDRESS                  DMA_CEC_OFFSETADDRESS
#define DMA_ENC2_BITOFFSET                      2
#define DMA_ENC2_BITFIELDSIZE                   1
#define DMA_ENC2_BITMASK                        0x00000004
#define DMA_ENC2_INIT                           0x0
/*
 *  DMA_ENC1 bit field defines
 ****************************************************************************************
 */
#define DMA_ENC1_OFFSETADDRESS                  DMA_CEC_OFFSETADDRESS
#define DMA_ENC1_BITOFFSET                      1
#define DMA_ENC1_BITFIELDSIZE                   1
#define DMA_ENC1_BITMASK                        0x00000002
#define DMA_ENC1_INIT                           0x0
/*
 *  DMA_ENC0 bit field defines
 ****************************************************************************************
 */
#define DMA_ENC0_OFFSETADDRESS                  DMA_CEC_OFFSETADDRESS
#define DMA_ENC0_BITOFFSET                      0
#define DMA_ENC0_BITFIELDSIZE                   1
#define DMA_ENC0_BITMASK                        0x00000001
#define DMA_ENC0_INIT                           0x0

/*
 *  DMA_CPAS register defines
 ****************************************************************************************
 */
#define DMA_CPAS_OFFSETADDRESS         0x00000030  /* RW */
#define DMA_CPAS_BITOFFSET             0
#define DMA_CPAS_BITFIELDSIZE          32
#define DMA_CPAS_BITMASK               0xFFFFFFFF
#define DMA_CPAS_INIT                  0x00000000
/*
 *  DMA_PAS2 bit field defines
 ****************************************************************************************
 */
#define DMA_PAS2_OFFSETADDRESS                  DMA_CPAS_OFFSETADDRESS
#define DMA_PAS2_BITOFFSET                      2
#define DMA_PAS2_BITFIELDSIZE                   1
#define DMA_PAS2_BITMASK                        0x00000004
#define DMA_PAS2_INIT                           0x0
/*
 *  DMA_PAS1 bit field defines
 ****************************************************************************************
 */
#define DMA_PAS1_OFFSETADDRESS                  DMA_CPAS_OFFSETADDRESS
#define DMA_PAS1_BITOFFSET                      1
#define DMA_PAS1_BITFIELDSIZE                   1
#define DMA_PAS1_BITMASK                        0x00000002
#define DMA_PAS1_INIT                           0x0
/*
 *  DMA_PAS0 bit field defines
 ****************************************************************************************
 */
#define DMA_PAS0_OFFSETADDRESS                  DMA_CPAS_OFFSETADDRESS
#define DMA_PAS0_BITOFFSET                      0
#define DMA_PAS0_BITFIELDSIZE                   1
#define DMA_PAS0_BITMASK                        0x00000001
#define DMA_PAS0_INIT                           0x0

/*
 *  DMA_CPAC register defines
 ****************************************************************************************
 */
#define DMA_CPAC_OFFSETADDRESS         0x00000034  /* RW */
#define DMA_CPAC_BITOFFSET             0
#define DMA_CPAC_BITFIELDSIZE          32
#define DMA_CPAC_BITMASK               0xFFFFFFFF
#define DMA_CPAC_INIT                  0x00000000
/*
 *  DMA_PAC2 bit field defines
 ****************************************************************************************
 */
#define DMA_PAC2_OFFSETADDRESS                  DMA_CPAC_OFFSETADDRESS
#define DMA_PAC2_BITOFFSET                      2
#define DMA_PAC2_BITFIELDSIZE                   1
#define DMA_PAC2_BITMASK                        0x00000004
#define DMA_PAC2_INIT                           0x0
/*
 *  DMA_PAC1 bit field defines
 ****************************************************************************************
 */
#define DMA_PAC1_OFFSETADDRESS                  DMA_CPAC_OFFSETADDRESS
#define DMA_PAC1_BITOFFSET                      1
#define DMA_PAC1_BITFIELDSIZE                   1
#define DMA_PAC1_BITMASK                        0x00000002
#define DMA_PAC1_INIT                           0x0
/*
 *  DMA_PAC0 bit field defines
 ****************************************************************************************
 */
#define DMA_PAC0_OFFSETADDRESS                  DMA_CPAC_OFFSETADDRESS
#define DMA_PAC0_BITOFFSET                      0
#define DMA_PAC0_BITFIELDSIZE                   1
#define DMA_PAC0_BITMASK                        0x00000001
#define DMA_PAC0_INIT                           0x0

/*
 *  DMA_CPS register defines
 ****************************************************************************************
 */
#define DMA_CPS_OFFSETADDRESS          0x00000038  /* RW */
#define DMA_CPS_BITOFFSET              0
#define DMA_CPS_BITFIELDSIZE           32
#define DMA_CPS_BITMASK                0xFFFFFFFF
#define DMA_CPS_INIT                   0x00000000
/*
 *  DMA_PS2 bit field defines
 ****************************************************************************************
 */
#define DMA_PS2_OFFSETADDRESS                   DMA_CPS_OFFSETADDRESS
#define DMA_PS2_BITOFFSET                       2
#define DMA_PS2_BITFIELDSIZE                    1
#define DMA_PS2_BITMASK                         0x00000004
#define DMA_PS2_INIT                            0x0
/*
 *  DMA_PS1 bit field defines
 ****************************************************************************************
 */
#define DMA_PS1_OFFSETADDRESS                   DMA_CPS_OFFSETADDRESS
#define DMA_PS1_BITOFFSET                       1
#define DMA_PS1_BITFIELDSIZE                    1
#define DMA_PS1_BITMASK                         0x00000002
#define DMA_PS1_INIT                            0x0
/*
 *  DMA_PS0 bit field defines
 ****************************************************************************************
 */
#define DMA_PS0_OFFSETADDRESS                   DMA_CPS_OFFSETADDRESS
#define DMA_PS0_BITOFFSET                       0
#define DMA_PS0_BITFIELDSIZE                    1
#define DMA_PS0_BITMASK                         0x00000001
#define DMA_PS0_INIT                            0x0

/*
 *  DMA_CPC register defines
 ****************************************************************************************
 */
#define DMA_CPC_OFFSETADDRESS          0x0000003c  /* RW */
#define DMA_CPC_BITOFFSET              0
#define DMA_CPC_BITFIELDSIZE           32
#define DMA_CPC_BITMASK                0xFFFFFFFF
#define DMA_CPC_INIT                   0x00000000
/*
 *  DMA_PC2 bit field defines
 ****************************************************************************************
 */
#define DMA_PC2_OFFSETADDRESS                   DMA_CPC_OFFSETADDRESS
#define DMA_PC2_BITOFFSET                       2
#define DMA_PC2_BITFIELDSIZE                    1
#define DMA_PC2_BITMASK                         0x00000004
#define DMA_PC2_INIT                            0x0
/*
 *  DMA_PC1 bit field defines
 ****************************************************************************************
 */
#define DMA_PC1_OFFSETADDRESS                   DMA_CPC_OFFSETADDRESS
#define DMA_PC1_BITOFFSET                       1
#define DMA_PC1_BITFIELDSIZE                    1
#define DMA_PC1_BITMASK                         0x00000002
#define DMA_PC1_INIT                            0x0
/*
 *  DMA_PC0 bit field defines
 ****************************************************************************************
 */
#define DMA_PC0_OFFSETADDRESS                   DMA_CPC_OFFSETADDRESS
#define DMA_PC0_BITOFFSET                       0
#define DMA_PC0_BITFIELDSIZE                    1
#define DMA_PC0_BITMASK                         0x00000001
#define DMA_PC0_INIT                            0x0

/*
 *  DMA_BEC register defines
 ****************************************************************************************
 */
#define DMA_BEC_OFFSETADDRESS          0x0000004c  /* RW */
#define DMA_BEC_BITOFFSET              0
#define DMA_BEC_BITFIELDSIZE           32
#define DMA_BEC_BITMASK                0xFFFFFFFF
#define DMA_BEC_INIT                   0x00000000
/*
 *  DMA_EC bit field defines
 ****************************************************************************************
 */
#define DMA_EC_OFFSETADDRESS                    DMA_BEC_OFFSETADDRESS
#define DMA_EC_BITOFFSET                        0
#define DMA_EC_BITFIELDSIZE                     1
#define DMA_EC_BITMASK                          0x00000001
#define DMA_EC_INIT                             0x0
#endif
