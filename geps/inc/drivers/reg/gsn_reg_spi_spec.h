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
 * $RCSfile: gsn_reg_spi_spec.h,v $
 *
 * Description:
 *      This file contains register specification for SPI Driver
 *
 ******************************************************************************
 */

#ifndef _REG_SPI_H
#define _REG_SPI_H

/***************************************************
 *
 *             SPI
 *
 ***************************************************/


/*
 *  COMMON_SPI_MASTER instance offsets
 ****************************************************************************************
 */
#define GSN_SPI_NUM_0 0x40030000
#define GSN_SPI_NUM_1 0x40040000

/*
 *  SPI_SPICR0 register defines
 ****************************************************************************************
 */
#define SPI_SPICR0_OFFSETADDRESS       0x00000000  /* RW */
#define SPI_SPICR0_BITOFFSET           0
#define SPI_SPICR0_BITFIELDSIZE        32
#define SPI_SPICR0_BITMASK             0xFFFFFFFF
#define SPI_SPICR0_INIT                0x00000000
/*
 *  SPI_SCR bit field defines
 ****************************************************************************************
 */
#define SPI_SCR_OFFSETADDRESS                   SPI_SPICR0_OFFSETADDRESS
#define SPI_SCR_BITOFFSET                       8
#define SPI_SCR_BITFIELDSIZE                    8
#define SPI_SCR_BITMASK                         0x0000ff00
#define SPI_SCR_INIT                            0x0
/*
 *  SPI_SPH bit field defines
 ****************************************************************************************
 */
#define SPI_SPH_OFFSETADDRESS                   SPI_SPICR0_OFFSETADDRESS
#define SPI_SPH_BITOFFSET                       7
#define SPI_SPH_BITFIELDSIZE                    1
#define SPI_SPH_BITMASK                         0x00000080
#define SPI_SPH_INIT                            0x0
/*
 *  SPI_SPO bit field defines
 ****************************************************************************************
 */
#define SPI_SPO_OFFSETADDRESS                   SPI_SPICR0_OFFSETADDRESS
#define SPI_SPO_BITOFFSET                       6
#define SPI_SPO_BITFIELDSIZE                    1
#define SPI_SPO_BITMASK                         0x00000040
#define SPI_SPO_INIT                            0x0
/*
 *  SPI_FRF bit field defines
 ****************************************************************************************
 */
#define SPI_FRF_OFFSETADDRESS                   SPI_SPICR0_OFFSETADDRESS
#define SPI_FRF_BITOFFSET                       4
#define SPI_FRF_BITFIELDSIZE                    2
#define SPI_FRF_BITMASK                         0x00000030
#define SPI_FRF_INIT                            0x0
/*
 *  SPI_DSS bit field defines
 ****************************************************************************************
 */
#define SPI_DSS_OFFSETADDRESS                   SPI_SPICR0_OFFSETADDRESS
#define SPI_DSS_BITOFFSET                       0
#define SPI_DSS_BITFIELDSIZE                    4
#define SPI_DSS_BITMASK                         0x0000000f
#define SPI_DSS_INIT                            0x0

/*
 *  SPI_SPICR1 register defines
 ****************************************************************************************
 */
#define SPI_SPICR1_OFFSETADDRESS       0x00000004  /* RW */
#define SPI_SPICR1_BITOFFSET           0
#define SPI_SPICR1_BITFIELDSIZE        32
#define SPI_SPICR1_BITMASK             0xFFFFFFFF
#define SPI_SPICR1_INIT                0x00000000
/*
 *  SPI_SOD bit field defines
 ****************************************************************************************
 */
#define SPI_SOD_OFFSETADDRESS                   SPI_SPICR1_OFFSETADDRESS
#define SPI_SOD_BITOFFSET                       3
#define SPI_SOD_BITFIELDSIZE                    1
#define SPI_SOD_BITMASK                         0x00000008
#define SPI_SOD_INIT                            0x0
/*
 *  SPI_MS bit field defines
 ****************************************************************************************
 */
#define SPI_MS_OFFSETADDRESS                    SPI_SPICR1_OFFSETADDRESS
#define SPI_MS_BITOFFSET                        2
#define SPI_MS_BITFIELDSIZE                     1
#define SPI_MS_BITMASK                          0x00000004
#define SPI_MS_INIT                             0x0
/*
 *  SPI_SSE bit field defines
 ****************************************************************************************
 */
#define SPI_SSE_OFFSETADDRESS                   SPI_SPICR1_OFFSETADDRESS
#define SPI_SSE_BITOFFSET                       1
#define SPI_SSE_BITFIELDSIZE                    1
#define SPI_SSE_BITMASK                         0x00000002
#define SPI_SSE_INIT                            0x0
/*
 *  SPI_LBM bit field defines
 ****************************************************************************************
 */
#define SPI_LBM_OFFSETADDRESS                   SPI_SPICR1_OFFSETADDRESS
#define SPI_LBM_BITOFFSET                       0
#define SPI_LBM_BITFIELDSIZE                    1
#define SPI_LBM_BITMASK                         0x00000001
#define SPI_LBM_INIT                            0x0

/*
 *  SPI_SPIDR register defines
 ****************************************************************************************
 */
#define SPI_SPIDR_OFFSETADDRESS        0x00000008  /* RW */
#define SPI_SPIDR_BITOFFSET            0
#define SPI_SPIDR_BITFIELDSIZE         32
#define SPI_SPIDR_BITMASK              0xFFFFFFFF
#define SPI_SPIDR_INIT                 0x00000000
/*
 *  SPI_DATA bit field defines
 ****************************************************************************************
 */
#define SPI_DATA_OFFSETADDRESS                  SPI_SPIDR_OFFSETADDRESS
#define SPI_DATA_BITOFFSET                      0
#define SPI_DATA_BITFIELDSIZE                  16
#define SPI_DATA_BITMASK                        0x0000ffff
#define SPI_DATA_INIT                           0x0

/*
 *  SPI_SPISR register defines
 ****************************************************************************************
 */
#define SPI_SPISR_OFFSETADDRESS        0x0000000c  /* R */
#define SPI_SPISR_BITOFFSET            0
#define SPI_SPISR_BITFIELDSIZE         32
#define SPI_SPISR_BITMASK              0xFFFFFFFF
#define SPI_SPISR_INIT                 0x00000000
/*
 *  SPI_BSY bit field defines
 ****************************************************************************************
 */
#define SPI_BSY_OFFSETADDRESS                   SPI_SPISR_OFFSETADDRESS
#define SPI_BSY_BITOFFSET                       4
#define SPI_BSY_BITFIELDSIZE                    1
#define SPI_BSY_BITMASK                         0x00000010
#define SPI_BSY_INIT                            0x0
/*
 *  SPI_RFF bit field defines
 ****************************************************************************************
 */
#define SPI_RFF_OFFSETADDRESS                   SPI_SPISR_OFFSETADDRESS
#define SPI_RFF_BITOFFSET                       3
#define SPI_RFF_BITFIELDSIZE                    1
#define SPI_RFF_BITMASK                         0x00000008
#define SPI_RFF_INIT                            0x0
/*
 *  SPI_RNE bit field defines
 ****************************************************************************************
 */
#define SPI_RNE_OFFSETADDRESS                   SPI_SPISR_OFFSETADDRESS
#define SPI_RNE_BITOFFSET                       2
#define SPI_RNE_BITFIELDSIZE                    1
#define SPI_RNE_BITMASK                         0x00000004
#define SPI_RNE_INIT                            0x0
/*
 *  SPI_TNF bit field defines
 ****************************************************************************************
 */
#define SPI_TNF_OFFSETADDRESS                   SPI_SPISR_OFFSETADDRESS
#define SPI_TNF_BITOFFSET                       1
#define SPI_TNF_BITFIELDSIZE                    1
#define SPI_TNF_BITMASK                         0x00000002
#define SPI_TNF_INIT                            0x0
/*
 *  SPI_TFE bit field defines
 ****************************************************************************************
 */
#define SPI_TFE_OFFSETADDRESS                   SPI_SPISR_OFFSETADDRESS
#define SPI_TFE_BITOFFSET                       0
#define SPI_TFE_BITFIELDSIZE                    1
#define SPI_TFE_BITMASK                         0x00000001
#define SPI_TFE_INIT                            0x0

/*
 *  SPI_SPICPSR register defines
 ****************************************************************************************
 */
#define SPI_SPICPSR_OFFSETADDRESS      0x00000010  /* RW */
#define SPI_SPICPSR_BITOFFSET          0
#define SPI_SPICPSR_BITFIELDSIZE       32
#define SPI_SPICPSR_BITMASK            0xFFFFFFFF
#define SPI_SPICPSR_INIT               0x00000000
/*
 *  SPI_CPSDVSR bit field defines
 ****************************************************************************************
 */
#define SPI_CPSDVSR_OFFSETADDRESS               SPI_SPICPSR_OFFSETADDRESS
#define SPI_CPSDVSR_BITOFFSET                   0
#define SPI_CPSDVSR_BITFIELDSIZE                8
#define SPI_CPSDVSR_BITMASK                     0x000000ff
#define SPI_CPSDVSR_INIT                        0x0

/*
 *  SPI_SPIMSC register defines
 ****************************************************************************************
 */
#define SPI_SPIMSC_OFFSETADDRESS       0x00000014  /* RW */
#define SPI_SPIMSC_BITOFFSET           0
#define SPI_SPIMSC_BITFIELDSIZE        32
#define SPI_SPIMSC_BITMASK             0xFFFFFFFF
#define SPI_SPIMSC_INIT                0x00000000
/*
 *  SPI_TXIM bit field defines
 ****************************************************************************************
 */
#define SPI_TXIM_OFFSETADDRESS                  SPI_SPIMSC_OFFSETADDRESS
#define SPI_TXIM_BITOFFSET                      3
#define SPI_TXIM_BITFIELDSIZE                   1
#define SPI_TXIM_BITMASK                        0x00000008
#define SPI_TXIM_INIT                           0x0
/*
 *  SPI_RXIM bit field defines
 ****************************************************************************************
 */
#define SPI_RXIM_OFFSETADDRESS                  SPI_SPIMSC_OFFSETADDRESS
#define SPI_RXIM_BITOFFSET                      2
#define SPI_RXIM_BITFIELDSIZE                   1
#define SPI_RXIM_BITMASK                        0x00000004
#define SPI_RXIM_INIT                           0x0
/*
 *  SPI_RTIM bit field defines
 ****************************************************************************************
 */
#define SPI_RTIM_OFFSETADDRESS                  SPI_SPIMSC_OFFSETADDRESS
#define SPI_RTIM_BITOFFSET                      1
#define SPI_RTIM_BITFIELDSIZE                   1
#define SPI_RTIM_BITMASK                        0x00000002
#define SPI_RTIM_INIT                           0x0
/*
 *  SPI_RORIM bit field defines
 ****************************************************************************************
 */
#define SPI_RORIM_OFFSETADDRESS                 SPI_SPIMSC_OFFSETADDRESS
#define SPI_RORIM_BITOFFSET                     0
#define SPI_RORIM_BITFIELDSIZE                  1
#define SPI_RORIM_BITMASK                       0x00000001
#define SPI_RORIM_INIT                          0x0
/**************************************************************************************/
/*
 *  SPI_SPIMIS register defines
 ****************************************************************************************
 */
#define SPI_SPIMIS_OFFSETADDRESS       0x0000001c  /* R */
#define SPI_SPIMIS_BITOFFSET           0
#define SPI_SPIMIS_BITFIELDSIZE        32
#define SPI_SPIMIS_BITMASK             0xFFFFFFFF
#define SPI_SPIMIS_INIT                0x00000000
/*
 *  SPI_TXMIS bit field defines
 ****************************************************************************************
 */
#define SPI_TXMIS_OFFSETADDRESS                 SPI_SPIMIS_OFFSETADDRESS
#define SPI_TXMIS_BITOFFSET                     3
#define SPI_TXMIS_BITFIELDSIZE                  1
#define SPI_TXMIS_BITMASK                       0x00000008
#define SPI_TXMIS_INIT                          0x0
/*
 *  SPI_RXMIS bit field defines
 ****************************************************************************************
 */
#define SPI_RXMIS_OFFSETADDRESS                 SPI_SPIMIS_OFFSETADDRESS
#define SPI_RXMIS_BITOFFSET                     2
#define SPI_RXMIS_BITFIELDSIZE                  1
#define SPI_RXMIS_BITMASK                       0x00000004
#define SPI_RXMIS_INIT                          0x0
/*
 *  SPI_RTMIS bit field defines
 ****************************************************************************************
 */
#define SPI_RTMIS_OFFSETADDRESS                 SPI_SPIMIS_OFFSETADDRESS
#define SPI_RTMIS_BITOFFSET                     1
#define SPI_RTMIS_BITFIELDSIZE                  1
#define SPI_RTMIS_BITMASK                       0x00000002
#define SPI_RTMIS_INIT                          0x0
/*
 *  SPI_RORMIS bit field defines
 ****************************************************************************************
 */
#define SPI_RORMIS_OFFSETADDRESS                SPI_SPIMIS_OFFSETADDRESS
#define SPI_RORMIS_BITOFFSET                    0
#define SPI_RORMIS_BITFIELDSIZE                 1
#define SPI_RORMIS_BITMASK                      0x00000001
#define SPI_RORMIS_INIT                         0x0

/*
 *  SPI_SPIICR register defines
 ****************************************************************************************
 */
#define SPI_SPIICR_OFFSETADDRESS       0x00000020  /* W */
#define SPI_SPIICR_BITOFFSET           0
#define SPI_SPIICR_BITFIELDSIZE        32
#define SPI_SPIICR_BITMASK             0xFFFFFFFF
#define SPI_SPIICR_INIT                0x00000000
/*
 *  SPI_RTIC bit field defines
 ****************************************************************************************
 */
#define SPI_RTIC_OFFSETADDRESS                  SPI_SPIICR_OFFSETADDRESS
#define SPI_RTIC_BITOFFSET                      1
#define SPI_RTIC_BITFIELDSIZE                   1
#define SPI_RTIC_BITMASK                        0x00000002
#define SPI_RTIC_INIT                           0x0
/*
 *  SPI_RORIC bit field defines
 ****************************************************************************************
 */
#define SPI_RORIC_OFFSETADDRESS                 SPI_SPIICR_OFFSETADDRESS
#define SPI_RORIC_BITOFFSET                     0
#define SPI_RORIC_BITFIELDSIZE                  1
#define SPI_RORIC_BITMASK                       0x00000001
#define SPI_RORIC_INIT                          0x0

/*
 *  SPI_SPIDMACR register defines
 ****************************************************************************************
 */
#define SPI_SPIDMACR_OFFSETADDRESS     0x00000024  /* RW */
#define SPI_SPIDMACR_BITOFFSET         0
#define SPI_SPIDMACR_BITFIELDSIZE      32
#define SPI_SPIDMACR_BITMASK           0xFFFFFFFF
#define SPI_SPIDMACR_INIT              0x00000000
/*
 *  SPI_TXDMAE bit field defines
 ****************************************************************************************
 */
#define SPI_TXDMAE_OFFSETADDRESS                SPI_SPIDMACR_OFFSETADDRESS
#define SPI_TXDMAE_BITOFFSET                    1
#define SPI_TXDMAE_BITFIELDSIZE                 1
#define SPI_TXDMAE_BITMASK                      0x00000002
#define SPI_TXDMAE_INIT                         0x0
/*
 *  SPI_RXDMAE bit field defines
 ****************************************************************************************
 */
#define SPI_RXDMAE_OFFSETADDRESS                SPI_SPIDMACR_OFFSETADDRESS
#define SPI_RXDMAE_BITOFFSET                    0
#define SPI_RXDMAE_BITFIELDSIZE                 1
#define SPI_RXDMAE_BITMASK                      0x00000001
#define SPI_RXDMAE_INIT                         0x0
   
#endif