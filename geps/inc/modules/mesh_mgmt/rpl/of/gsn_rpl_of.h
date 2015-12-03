/******************************************************************************
*
*               COPYRIGHT (c) 2013 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by GainSpan
* Corporation or its licensors.  Title to the Material remains
* with GainSpan Corporation or its suppliers and licensors.
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
* Unless otherwise agreed by GainSpan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by GainSpan
* or GainSpan's suppliers or licensors in any way.
*
* $RCSfile: gsn_rpl_of.h,v $
*
* Description : This file contains function declaration for RPL OF(Objective
* Function).
*******************************************************************************/

/*******************************************************************************
* File inclusion
*******************************************************************************/
#ifndef _GSN_RPL_OF_H_
#define _GSN_RPL_OF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**< All the below OF are described in RFC 6551 */
#define GSN_RPL_OF_TYPE_NSA 1 /**< Node State and Attribute */
#define GSN_RPL_OF_TYPE_NE  2 /**< Node Energy */
#define GSN_RPL_OF_TYPE_HC  3 /**< Hop Count */
#define GSN_RPL_OF_TYPE_LT  4 /**< Link Throughput */
#define GSN_RPL_OF_TYPE_LL  5 /**< Link Latency */
#define GSN_RPL_OF_TYPE_LQ  6 /**< Link Quality Level */
#define GSN_RPL_OF_TYPE_ETX 7 /**< Link ETX */
#define GSN_RPL_OF_TYPE_LC  8 /**< Link Color */


#define GSN_RPL_OF_FLAG_RA  8 /**< Recorded/Aggregated */
#define GSN_RPL_OF_FLAG_OC  7 /**< Optional Constraint */
#define GSN_RPL_OF_FLAG_CM  6 /**< Constraint/Metric */
#define GSN_RPL_OF_FLAG_P   5 /**< P (Partial) */

#define GSN_RPL_OF_A_ADD    0 /**< Routing metric is additive */
#define GSN_RPL_OF_A_MAX    1 /**< Routing metric reports a maximum */
#define GSN_RPL_OF_A_MIN    2 /**< Routing metric reports a minimum */
#define GSN_RPL_OF_A_MUL    3 /**< Routing metric is multiplicative */

/**< NSA Object Flags Field */
#define GSN_RPL_OF_NSA_FLAG_AGGR  ( 1 << 6 ) /**< Aggregator */
#define GSN_RPL_OF_NSA_FLAG_OL    ( 1 << 7 ) /**< Overloaded */

/**< Node Type Field */
#define GSN_RPL_OF_NA_TYPE_MAINS  0 /**< a mains-powered node */
#define GSN_RPL_OF_NA_TYPE_BATT   1 /**< a battery-powered node */
#define GSN_RPL_OF_NA_TYPE_ES     2 /**< a node powered by an energy scavenger */


#define GSN_RPL_MC_BUILD_HDR( pos, MCType, P, C, O, R, A, Prec, Len )   \
    *(pos)++ = (MCType); *(pos)++ = (P) << 5 | (C) << 6 | (O) << 7;     \
    *(pos)++ = (R) | ((A) << 1 ) | ((Prec) << 4);                       \
    *(pos)++ = (Len);

/**<
I (Included): the ’I’ bit is only relevant when the node type is used as a
constraint. For example, the path must only traverse mains-powered nodes.

T (node Type): 2-bit field indicating the node type. T=0 designates a
mains-powered node, T=1 a battery-powered node, and T=2 a node powered by an
energy scavenger.

E (Estimation): when the ’E’ bit is set for a metric, the
estimated percentage of remaining energy on the node is indicated
in the E_E 8-bit field.
*/
#define GSN_RPL_MC_BUILD_NE_HDR( pos, I, T, E, E_E )   \
    *(pos)++ = ((I) << 4) | ((T) << 5) | ((E) << 7);   \
    *(pos)++ = (E_E);

/**< Hop Count Header */
#define GSN_RPL_MC_BUILD_HC_HDR( pos, HC )   \
    *(pos)++ = 0; *(pos)++ = (HC);

/**< Link Throughput Header 
#define GSN_RPL_MC_BUILD_HC_HDR( pos, TH )   \
    WRITE_32( pos, TH ); */

/**< Link Latency Header 
#define GSN_RPL_MC_BUILD_HC_HDR( pos, L )   \
    WRITE_32( pos, L ); */

/**< Link Latency Header, Built by ROOT */
#define GSN_RPL_MC_BUILD_LQ_HDR( pos, LQ )   \
    *(pos)++ = 0; *(pos)++ = 0;

/**< Link Latency Header, Built by ROOT */
#define GSN_RPL_MC_UPDATE_LQ_HDR( pos, len, LQ )   \
    {                                              \
        int i = len;                               \
        while(i != 0 )                             \
        {                                          \
            if( LQ == (*( pos + i + 1 ) & 0x7 ))   \
            {                                      \
                *(pos) += 8;                       \
                break;                             \
            }                                      \
            pos++;                                 \
            i--;                                   \
        }                                          \
        if( i == 0 )                               \
        {                                          \
            *(pos + len ) = LQ + 8;                \
            pos++;                                 \
        }                                          \
    }

#define GSN_RPL_MC_CALC_ETX_OBJ_VALUE( ETX ) (UINT16)(((ETX) * 128) + 0.5 ))

VOID* GsnRplOf_GetOFCtx( UINT16 OF, GSN_RPL_DODAG_CTX_T *pDCtx, VOID **pCtxPtr );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_OF_H_ */