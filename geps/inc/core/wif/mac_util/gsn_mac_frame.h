/******************************************************************************
 *
 *               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
 * $RCSfile: gsn_mac_frame.h,v $
 *
 * Project: GSN APP Software
 *
 * Description:
 *      Mac header structure
 ****************************************************************************************
 */


/*
 * MAC HEADER length definitions
 ****************************************************************************************
 */
#define GSN_MAC_LONG_QOS_MAC_HDR_LEN       32              /* size without FCS              */
#define GSN_MAC_LONG_MAC_HDR_LEN           30              /* size without FCS              */
#define GSN_MAC_SHORT_QOS_MAC_HDR_LEN      26              /* size without FCS              */
#define GSN_MAC_SHORT_MAC_HDR_LEN          24              /* size without FCS              */

#define GSN_MAC_LONG_CTRLFRAME_LEN         16              /* size without FCS              */
#define GSN_MAC_SHORT_CTRLFRAME_LEN        10              /* size without FCS              */

#define GSN_MAC_ACK_LEN                    GSN_MAC_SHORT_CTRLFRAME_LEN
#define GSN_MAC_CTS_LEN                    GSN_MAC_SHORT_CTRLFRAME_LEN
#define GSN_MAC_RTS_LEN                    GSN_MAC_LONG_CTRLFRAME_LEN
#define GSN_MAC_CFPOLL_LEN                 GSN_MAC_LONG_CTRLFRAME_LEN
#define GSN_MAC_CFACK_LEN                  GSN_MAC_LONG_CTRLFRAME_LEN
#define GSN_MAC_CFEND_LEN                  GSN_MAC_LONG_CTRLFRAME_LEN
#define GSN_MAC_PSPOLL_LEN                 GSN_MAC_LONG_CTRLFRAME_LEN
#define GSN_MAC_ATIM_LEN                   24


/*
 * MAC HEADER definitions and OFFSETS
 ****************************************************************************************
 */
#define GSN_MAC_HEAD_FCTRL_OFT              0
#define GSN_MAC_HEAD_DURATION_OFT           2
    #define GSN_MAC_HEAD_DURATION_CFP  0x8000
#define GSN_MAC_HEAD_ADDR1_OFT              4
#define GSN_MAC_HEAD_ADDR2_OFT             10
#define GSN_MAC_HEAD_ADDR3_OFT             16
#define GSN_MAC_HEAD_CTRL_OFT              22
#define GSN_MAC_HEAD_ADDR4_OFT             24
#define GSN_MAC_HEAD_SHORT_QOS_OFT         24
#define GSN_MAC_HEAD_LONG_QOS_OFT          30

/* SEQUENCE CONTROL MASK                                                                */
#define GSN_MAC_HEAD_CTRL_FRAG_MASK        0x000F
#define GSN_MAC_HEAD_CTRL_SEQNBR_MASK      0xFFF0
#define GSN_MAC_HEAD_CTRL_SEQNBR_INC       0x0010

/* ADDRESS GROUP MASK                                                                   */
#define GSN_MAC_HEAD_ADDR_GROUP_MASK        BIT(0)
    #define GSN_MAC_UNICAST_ADDR            0
    #define GSN_MAC_GROUP_ADDR              1
#define GSN_MAC_HEAD_ADDR_LOCALLY_DEFINED   BIT(1)

/* QoS CONTROL MASK                                                                     */
#define GSN_MAC_HEAD_QOS_UP_MASK            0x07

/* AID MASK                                                                             */
#define GSN_MAC_ASSRSP_AID_MASK             0x3FFF

/* FRAME CONTROL MASK                                                                   */
/* Nomenclatura:
 * The type information in the header of a frame consists of the Type and Subtype fields
 * When using the term "frame type" in the code, we refer to the type field and not to
 * the combined type+subtype information.
 */
#define GSN_MAC_FCTRL_PROTOCOLVERSION_MASK 0x0003
#define GSN_MAC_FCTRL_TYPE_MASK            0x000C
    #define GSN_MAC_FCTRL_MGT_T            0x0000
    #define GSN_MAC_FCTRL_CTRL_T           0x0004
    #define GSN_MAC_FCTRL_DATA_T           0x0008

#define GSN_MAC_FCTRL_SUBT_MASK            0x00F0
    /* Management SubType                                                               */
    #define GSN_MAC_FCTRL_ASSOCREQ_ST      0x0000
    #define GSN_MAC_FCTRL_ASSOCRSP_ST      0x0010
    #define GSN_MAC_FCTRL_REASSOCREQ_ST    0x0020
    #define GSN_MAC_FCTRL_REASSOCRSP_ST    0x0030
    #define GSN_MAC_FCTRL_PROBEREQ_ST      0x0040
    #define GSN_MAC_FCTRL_PROBERSP_ST      0x0050
    #define GSN_MAC_FCTRL_BEACON_ST        0x0080
    #define GSN_MAC_FCTRL_ATIM_ST          0x0090
    #define GSN_MAC_FCTRL_DISASSOC_ST      0x00A0
    #define GSN_MAC_FCTRL_AUTHENT_ST       0x00B0
    #define GSN_MAC_FCTRL_DEAUTHENT_ST     0x00C0
    #define GSN_MAC_FCTRL_ACTION_ST        0x00D0
    /* Control SubTypes                                                                 */
    #define GSN_MAC_FCTRL_PSPOLL_ST        0x00A0
    #define GSN_MAC_FCTRL_RTS_ST           0x00B0
    #define GSN_MAC_FCTRL_CTS_ST           0x00C0
    #define GSN_MAC_FCTRL_ACK_ST           0x00D0
    #define GSN_MAC_FCTRL_CFEND_ST         0x00E0
    #define GSN_MAC_FCTRL_CFEND_CFACK_ST   0x00F0
    /* Data SubTypes                                                                    */
    /* Decoding the subtypes of data type frames can take advantage of the fact that
     * each subtype field bit position is used to indicate a specific modification of
     * the basic data frame (subtype 0). Frame control bit 4 is set to 1 in data
     * subtypes which include +CF-Ack, bit 5 is set to 1 in data subtypes which include
     * +CF-Poll, bit 6 is set to 1 in data subtypes that contain no Frame Body,
     * and bit 7 is set to 1 in the QoS data subtypes, which have QoS Control fields in
     * their MAC headers.
     *
     * Usage: check FrameT and FrameSubT individually. If the FrameT is MAC_FCTRL_DATA_T,
     * check the following bits of the FrameSubT
     */
    #define GSN_MAC_CFACK_ST_BIT           BIT(4)
    #define GSN_MAC_CFPOLL_ST_BIT          BIT(5)
    #define GSN_MAC_NODATA_ST_BIT          BIT(6)
    #define GSN_MAC_QOS_ST_BIT             BIT(7)

    #define GSN_MAC_FCTRL_DATACFACKPOLL_ST (MAC_CFACK_ST_BIT | MAC_CFPOLL_ST_BIT)

#define GSN_MAC_FCTRL_TODS                 0x0100
#define GSN_MAC_FCTRL_FROMDS               0x0200
#define GSN_MAC_FCTRL_MOREFRAG             0x0400
#define GSN_MAC_FCTRL_RETRY                0x0800
#define GSN_MAC_FCTRL_PWRMGT               0x1000
#define GSN_MAC_FCTRL_MOREDATA             0x2000
#define GSN_MAC_FCTRL_PROTECTEDFRAME       0x4000

#define GSN_MAC_FCTRL_ORDER                0x8000

/* FRAME CONTROL : Type information including Type and SubType                          */
#define GSN_MAC_FCTRL_TYPESUBTYPE_MASK      (GSN_MAC_FCTRL_TYPE_MASK | GSN_MAC_FCTRL_SUBT_MASK)
#define GSN_MAC_FCTRL_ASSOCREQ              (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_ASSOCREQ_ST)
#define GSN_MAC_FCTRL_ASSOCRSP              (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_ASSOCRSP_ST)
#define GSN_MAC_FCTRL_REASSOCREQ            (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_REASSOCREQ_ST)
#define GSN_MAC_FCTRL_REASSOCRSP            (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_REASSOCRSP_ST)
#define GSN_MAC_FCTRL_PROBEREQ              (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_PROBEREQ_ST)
#define GSN_MAC_FCTRL_PROBERSP              (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_PROBERSP_ST)
#define GSN_MAC_FCTRL_BEACON                (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_BEACON_ST)
#define GSN_MAC_FCTRL_ATIM                  (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_ATIM_ST)
#define GSN_MAC_FCTRL_DISASSOC              (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_DISASSOC_ST)
#define GSN_MAC_FCTRL_AUTHENT               (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_AUTHENT_ST)
#define GSN_MAC_FCTRL_DEAUTHENT             (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_DEAUTHENT_ST)
#define GSN_MAC_FCTRL_ACTION                (GSN_MAC_FCTRL_MGT_T     | GSN_MAC_FCTRL_ACTION_ST)

#define GSN_MAC_FCTRL_PSPOLL                (GSN_MAC_FCTRL_CTRL_T    | GSN_MAC_FCTRL_PSPOLL_ST)
#define GSN_MAC_FCTRL_RTS                   (GSN_MAC_FCTRL_CTRL_T    | GSN_MAC_FCTRL_RTS_ST)
#define GSN_MAC_FCTRL_CTS                   (GSN_MAC_FCTRL_CTRL_T    | GSN_MAC_FCTRL_CTS_ST)
#define GSN_MAC_FCTRL_ACK                   (GSN_MAC_FCTRL_CTRL_T    | GSN_MAC_FCTRL_ACK_ST)
#define GSN_MAC_FCTRL_CFEND                 (GSN_MAC_FCTRL_CTRL_T    | GSN_MAC_FCTRL_CFEND_ST)
#define GSN_MAC_FCTRL_CFEND_CFACK           (GSN_MAC_FCTRL_CFEND     | GSN_MAC_CFACK_ST_BIT)

#define GSN_MAC_FCTRL_DATA_CFACK            (GSN_MAC_FCTRL_DATA_T    | GSN_MAC_CFACK_ST_BIT)
#define GSN_MAC_FCTRL_DATA_CFPOLL           (GSN_MAC_FCTRL_DATA_T    | GSN_MAC_CFPOLL_ST_BIT)
#define GSN_MAC_FCTRL_DATA_CFACKPOLL        (GSN_MAC_FCTRL_DATA_T    | GSN_MAC_FCTRL_DATACFACKPOLL_ST)
#define GSN_MAC_FCTRL_NULL_FUNCTION         (GSN_MAC_FCTRL_DATA_T    | GSN_MAC_NODATA_ST_BIT)
#define GSN_MAC_FCTRL_NULL_CFACK       (GSN_MAC_FCTRL_NULL_FUNCTION  | GSN_MAC_CFACK_ST_BIT)
#define GSN_MAC_FCTRL_NULL_CFPOLL      (GSN_MAC_FCTRL_NULL_FUNCTION  | GSN_MAC_CFPOLL_ST_BIT)
#define GSN_MAC_FCTRL_NULL_CFACKPOLL   (GSN_MAC_FCTRL_NULL_FUNCTION  | GSN_MAC_FCTRL_DATACFACKPOLL_ST)

#define GSN_MAC_FCTRL_QOS_DATA              ( GSN_MAC_FCTRL_DATA_T   | GSN_MAC_QOS_ST_BIT)
#define GSN_MAC_FCTRL_QOS_DATA_CFACK        (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_CFACK_ST_BIT)
#define GSN_MAC_FCTRL_QOS_DATA_CFPOLL       (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_CFPOLL_ST_BIT)
#define GSN_MAC_FCTRL_QOS_DATA_CFACKPOLL    (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_FCTRL_DATACFACKPOLL_ST)
#define GSN_MAC_FCTRL_QOS_NULL              (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_NODATA_ST_BIT)
#define GSN_MAC_FCTRL_QOS_NULL_CFACK        (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_FCTRL_NULL_CFACK)
#define GSN_MAC_FCTRL_QOS_NULL_CFPOLL       (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_FCTRL_NULL_CFPOLL)
#define GSN_MAC_FCTRL_QOS_NULL_CFACKPOLL    (GSN_MAC_FCTRL_QOS_DATA  | GSN_MAC_FCTRL_NULL_CFACKPOLL)



/*
 * FIELD DESCRIPTION
 ****************************************************************************************
 */
/* CAPABILITY INFORMATION FIELD                                                         */
#define GSN_MAC_CAPA_ESS                            BIT(0)
#define GSN_MAC_CAPA_IBSS                           BIT(1)
#define GSN_MAC_CAPA_CFPOLL                         BIT(2)
#define GSN_MAC_CAPA_CFREQ                          BIT(3)
#define GSN_MAC_CAPA_PRIVA                          BIT(4)
#define GSN_MAC_CAPA_SHORT                          BIT(5)
#define GSN_MAC_CAPA_PBCB                           BIT(6)
#define GSN_MAC_CAPA_AGILITY                        BIT(7)
#define GSN_MAC_CAPA_SPECTRUM                       BIT(8)

#define GSN_MAC_CAPA_RESERVED9                      BIT(9)

#define GSN_MAC_CAPA_G_SHORT_SLOT                   BIT(10)
#define GSN_MAC_CAPA_ROBUST_SECURITY                BIT(11)

#define GSN_MAC_CAPA_RESERVED12                     BIT(12)

#define GSN_MAC_CAPA_DSSS_OFDM                      BIT(13)

/* SSID FIELD                                                                           */
#define GSN_MAC_SSID_ID_OFT                         0
#define GSN_MAC_SSID_LEN_OFT                        1
#define GSN_MAC_SSID_SSID                           2

/* SUPPORTED RATES FIELD                                                                */
#define GSN_MAC_RATES_ID_OFT                        0
#define GSN_MAC_RATES_LEN_OFT                       1
#define GSN_MAC_RATES_RATES_OFT                     2

/* FH PARAM SET FIELD                                                                   */
#define GSN_MAC_FH_ID_OFT                           0
#define GSN_MAC_FH_LEN_OFT                          1
#define GSN_MAC_FH_DWELL_OFT                        2
#define GSN_MAC_FH_HOP_SET_OFT                      4
#define GSN_MAC_FH_HOP_PAT_OFT                      5
#define GSN_MAC_FH_HOP_IDX_OFT                      6

/* DS PARAM SET                                                                         */
#define GSN_MAC_DS_ID_OFT                           0
#define GSN_MAC_DS_LEN_OFT                          1
#define GSN_MAC_DS_CHANNEL_OFT                      2

/* CF PARAM SET                                                                         */
#define GSN_MAC_CF_ID_OFT                           0
#define GSN_MAC_CF_LEN_OFT                          1
#define GSN_MAC_CF_COUNT_OFT                        2
#define GSN_MAC_CF_PERIOD_OFT                       3
#define GSN_MAC_CF_MAX_DUR_OFT                      4
#define GSN_MAC_CF_REM_DUR_OFT                      6

/* TIM                                                                                  */
#define GSN_MAC_TIM_ID_OFT                          0
#define GSN_MAC_TIM_LEN_OFT                         1
#define GSN_MAC_TIM_CNT_OFT                         2
#define GSN_MAC_TIM_PERIOD_OFT                      3
#define GSN_MAC_TIM_BMPC_OFT                        4
#define GSN_MAC_TIM_BMP_OFT                         5

/* IBSS PARAM SET                                                                       */
#define GSN_MAC_IBSS_ID_OFT                         0
#define GSN_MAC_IBSS_LEN_OFT                        1
#define GSN_MAC_IBSSATIM_OFT                        2

/* CHALLENGE PARAM SET                                                                  */
#define GSN_MAC_CHALL_ID_OFT                        0
#define GSN_MAC_CHALL_LEN_OFT                       1
#define GSN_MAC_CHALL_TEXT_OFT                      2

/* ERP BIT FIELD                                                                        */
#define GSN_MAC_ERP_NON_ERP_PRESENT                 BIT(0)
#define GSN_MAC_ERP_USE_PROTECTION                  BIT(1)
#define GSN_MAC_ERP_BARKER_PREAMBLE_MODE            BIT(2)

/* RSN INFORMATION FIELD (WPA Extention)                                                */
#define GSN_MAC_RSNIE_ID_OFT                        0
#define GSN_MAC_RSNIE_LEN_OFT                       1
#define GSN_MAC_RSNIE_ADDITONNAL_WPA_OUI            2
#define GSN_MAC_RSNIE_VERSION_OFT                   6
#define GSN_MAC_RSNIE_GROUP_CIPHER_SUITE            8
#define GSN_MAC_RSNIE_PAIRWISE_CIPHER_SUITE_CNT    12
#define GSN_MAC_RSNIE_PAIRWISE_CIPHER_SUITE_LIST   14
//#define GSN_MAC_RSNIE_KEY_MANAGEMENT_SUITE_CNT
//#define GSN_MAC_RSNIE_KEY_MANAGEMENT_SUITE_LIST
//#define GSN_MAC_RSNIE_RSN_CAPABILITIES

/*
 * MANAGEMENT FRAME DESCRIPTION
 ****************************************************************************************
 */
#define GSN_MAC_BEACON_MAX_LEN              333
#define GSN_MAC_BEACONINFO_SIZE              78   /* size without TIM                       */
#define GSN_MAC_TIM_SIZE                   (4+2)  /* min TIM size (Partial BitMap only)     */
                                              /* Attention, in a non-AP STA the IBSS    */
                                              /* parameter set is stored in place of    */
                                              /* the TIM -> min size 4                  */

#define GSN_MAC_BEACON_HDR_LEN               36

/*
 * Beacon Frame offset (Table 5 p46)
 */
#define GSN_MAC_BEACON_TIMESTAMP_OFT          0   /* Order 1                                */
#define GSN_MAC_BEACON_INTERVAL_OFT           8   /* Order 2                                */
#define GSN_MAC_BEACON_CAPA_OFT              10   /* Order 3                                */
#define GSN_MAC_BEACON_SSID_OFT              12   /* Order 4                                */
/*      MAC_BEACON_RATES_OFT                     Order 5                                */
/*      MAC_BEACON_PHY_OFT                       Order 6                                */
/*      MAC_BEACON_DS_OFT1                       Order 7                                */
/*      MAC_BEACON_CF_OFT1                       Order 8                                */
/*      MAC_BEACON_IBSS_OFT                      Order 9                                */
/*      MAC_BEACON_TIM_OFT                       Order 10                               */
/*      MAC_BEACON_RSNIE_OFT                     Order 14  (WPA extention)              */


/*
 * Probe Request Frame offset
 */
#define GSN_MAC_PROBEREQ_SSID_OFT             0   /* Order 1                                */

/*
 * Probe Response Frame offset (Table 12 p49)
 */
#define GSN_MAC_PROBE_TIMESTAMP_OFT           0   /* Order 1                                */
#define GSN_MAC_PROBE_INTERVAL_OFT            8   /* Order 2                                */
#define GSN_MAC_PROBE_CAPA_OFT               10   /* Order 3                                */
#define GSN_MAC_PROBE_SSID_OFT               12   /* Order 4                                */
/*      MAC_PROBE_RATES_OFT                      Order 5                                */
/*      MAC_PROBE_PHY_OFT                        Order 6                                */
/*      MAC_PROBE_DS_OFT1                        Order 7                                */
/*      MAC_PROBE_CF_OFT1                        Order 8                                */
/*      MAC_PROBE_IBSS_OFT                       Order 9                                */
/*      MAC_PROBE_RSNIE_OFT                      Order 10 (WPA extention)               */


/*
 * Authentication Frame offset (Table 13 p49)
 */
#define GSN_MAC_AUTH_ALGONBR_OFT              0   /* Order 1                                */
#define GSN_MAC_AUTH_SEQNBR_OFT               2   /* Order 2                                */
#define GSN_MAC_AUTH_STATUS_OFT               4   /* Order 3                                */
#define GSN_MAC_AUTH_CHALLENGE_OFT            6   /* Order 4                                */


/*
 * Association Req Frame offset (Table 7 p47)
 */
#define GSN_MAC_ASSO_REQ_CAPA_OFT             0   /* Order 1                                */
#define GSN_MAC_ASSO_REQ_LISTEN_OFT           2   /* Order 2                                */
#define GSN_MAC_ASSO_REQ_SSID_OFT             4   /* Order 3                                */
/*      MAC_ASSO_REQ_RATES_OFT                   Order 4                                */
/*      MAC_ASSO_REQ_RSNIE_OFT                   Order 5  (WPA extention)               */

/*
 * Association Rsp Frame offset (Table 8 p47)
 */
#define GSN_MAC_ASSO_RSP_CAPA_OFT             0   /* Order 1                                */
#define GSN_MAC_ASSO_RSP_STATUS_OFT           2   /* Order 2                                */
#define GSN_MAC_ASSO_RSP_AID_OFT              4   /* Order 3                                */
#define GSN_MAC_ASSO_RSP_RATES_OFT            6   /* Order 4                                */

/*
 * Reassociation Req Frame offset (Table 9 p48)
 */
#define GSN_MAC_REASSO_REQ_CAPA_OFT           0   /* Order 1                                */
#define GSN_MAC_REASSO_REQ_LISTEN_OFT         2   /* Order 2                                */
#define GSN_MAC_REASSO_REQ_AP_ADDR_OFT        4   /* Order 3                                */
#define GSN_MAC_REASSO_REQ_SSID_OFT          10   /* Order 4                                */
/*      MAC_REASSO_REQ_RATES_OFT                 Order 5                                */
/*      MAC_REASSO_REQ_RSNIE_OFT                 Order 6  (WPA extention)               */


/*
 * Deauthentication Req Frame offset
 */

#define GSN_MAC_DEAUTH_REASON_OFT             0

/*
 * Deassociation Req Frame offset
 */

#define GSN_MAC_DISASSOC_REASON_OFT           0

/*
 * Action Req Frame offset
 */

#define GSN_MAC_ACTION_CATEGORY_OFT           0
#define GSN_MAC_ACTION_DETAIL_OFT             1
#define GSN_MAC_ACTION_IE_OFT                 2



/*
 * REASON CODE (Table 18 p53)
 ****************************************************************************************
 */
#define GSN_MAC_RS_RESERVED                   0
#define GSN_MAC_RS_UNSPECIFIED                1
#define GSN_MAC_RS_PREVIOUS_AUTH_NOT_VALID    2
#define GSN_MAC_RS_DEAUTH_SENDER_LEFT_IBSS    3
#define GSN_MAC_RS_DIASSOC_INACTIVITY         4
#define GSN_MAC_RS_DIASSOC_TOO_MANY_STA       5
#define GSN_MAC_RS_CLASS_2_FORBIDDEN          6
#define GSN_MAC_RS_CLASS_3_FORBIDDEN          7
#define GSN_MAC_RS_DEAUTH_SENDER_LEFT_BSS     8
#define GSN_MAC_RS_STA_REQ_ASSOC_NOT_AUTH     9
#define GSN_MAC_RS_DIASSOC_POWER_CAPA        10
#define GSN_MAC_RS_DIASSOC_SUPPORTED_CHANNEL 11


#define GSN_MAC_RS_INVALID_IE                13             /* WPA extention                */
#define GSN_MAC_RS_MIC_FAILURE               14             /* WPA extention                */
#define GSN_MAC_RS_4WAY_HANDSHAKE_TIMEOUT    15             /* WPA extention                */
#define GSN_MAC_RS_GROUP_KEY_UPDATE_TIMEOUT  16             /* WPA extention                */
#define GSN_MAC_RS_BAD_RSNIE                 17             /* WPA extention                */
#define GSN_MAC_RS_GROUP_CIPHER_INVALID      18             /* WPA extention                */
#define GSN_MAC_RS_PAIRWISE_CIPHER_INVALID   19             /* WPA extention                */
#define GSN_MAC_RS_AKMP_INVALID              20             /* WPA extention                */
#define GSN_MAC_RS_UNSUPPORTED_RSNE_VERSION  21             /* WPA extention                */
#define GSN_MAC_RS_INVALID_RSNE_CAPA         22             /* WPA extention                */
#define GSN_MAC_RS_802_1X_AUTH_FAIL          23             /* WPA extention                */
#define GSN_MAC_RS_CIPHER_SUITE_REJECTED     24             /* draft 7.0 extention          */

/*
 * STATUS CODE (Table 19 p54)
 ****************************************************************************************
 */
#define GSN_MAC_ST_SUCCESSFUL                 0
#define GSN_MAC_ST_FAILURE                    1
#define GSN_MAC_ST_RESERVED                   2
#define GSN_MAC_ST_CAPA_NOT_SUPPORTED        10
#define GSN_MAC_ST_REASSOC_NOT_ASSOC         11
#define GSN_MAC_ST_ASSOC_DENIED              12
#define GSN_MAC_ST_AUTH_ALGO_NOT_SUPPORTED   13
#define GSN_MAC_ST_AUTH_FRAME_WRONG_SEQ      14
#define GSN_MAC_ST_AUTH_CHALLENGE_FAILED     15
#define GSN_MAC_ST_AUTH_TIMEOUT              16
#define GSN_MAC_ST_ASSOC_TOO_MANY_STA        17
#define GSN_MAC_ST_ASSOC_RATES_NOT_SUPPORT   18

#define GSN_MAC_ST_ASSOC_SPECTRUM_REQUIRED   22
#define GSN_MAC_ST_ASSOC_POWER_CAPA          23
#define GSN_MAC_ST_ASSOC_SUPPORTED_CHANNEL   24

#define GSN_MAC_ST_INVALID_IE                40             /* draft 7.0 extention          */
#define GSN_MAC_ST_GROUP_CIPHER_INVALID      41             /* draft 7.0 extention          */
#define GSN_MAC_ST_PAIRWISE_CIPHER_INVALID   42             /* draft 7.0 extention          */
#define GSN_MAC_ST_AKMP_INVALID              43             /* draft 7.0 extention          */
#define GSN_MAC_ST_UNSUPPORTED_RSNE_VERSION  44             /* draft 7.0 extention          */
#define GSN_MAC_ST_INVALID_RSNE_CAPA         45             /* draft 7.0 extention          */
#define GSN_MAC_ST_CIPHER_SUITE_REJECTED     46             /* draft 7.0 extention          */



/*
 * ELEMENT ID DEFINITION (Table 20 page 55)
 ****************************************************************************************
 */
#define GSN_MAC_INFOELT_ID_OFT                0
#define GSN_MAC_INFOELT_LEN_OFT               1
#define GSN_MAC_INFOELT_INFO_OFT              2

#define GSN_MAC_ELTID_SSID                    0
#define GSN_MAC_ELTID_RATES                   1
#define GSN_MAC_ELTID_FH                      2
#define GSN_MAC_ELTID_DS                      3
#define GSN_MAC_ELTID_CF                      4
#define GSN_MAC_ELTID_TIM                     5
#define GSN_MAC_ELTID_IBSS                    6
// Future use
//#define GSN_MAC_ELTID_OFDM5
//#define GSN_MAC_ELTID_OFDM24

#define GSN_MAC_ELTID_COUNTRY                 7             /* optional                     */
#define GSN_MAC_ELTID_HOP_PARAM               8             /* optional                     */
#define GSN_MAC_ELTID_HOP_TABLE               9             /* optional                     */
#define GSN_MAC_ELTID_REQUEST                10             /* optional                     */

#define GSN_MAC_ELTID_POWER_CONSTRAINT       32             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_POWER_CAPABILITY       33             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_TPC_REQUEST            34             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_TPC_REPORT             35             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_SUPPORTED_CHANNELS     36             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_CHANNEL_SWITCH         37             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_MEASUREMENT_REQUEST    38             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_MEASUREMENT_REPORT     39             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_QUIET                  40             /* Spectrum & Power Management  */
#define GSN_MAC_ELTID_IBSS_DFS               41             /* Spectrum & Power Management  */

#define GSN_MAC_ELTID_ERP                    42
#define GSN_MAC_ELTID_RSN_IEEE               48
#define GSN_MAC_ELTID_EXT_RATES              50

#define GSN_MAC_ELTID_CHALLENGE              16

#define GSN_MAC_ELTID_OUI                   221            /* Proprietary   (0xDD)          */

#define GSN_MAC_OUI_TYPE_WPA                  1
#define GSN_MAC_OUI_TYPE_WME                  2
#define GSN_MAC_OUI_TYPE_WPS                  4
#define GSN_MAC_OUI_SUBTYPE_WME_INFORMATION   0
#define GSN_MAC_OUI_SUBTYPE_WME_PARAMETER     1

/*
 * WME AC Parameters Record
 ****************************************************************************************
 */
#define GSN_MAC_AC_BK                         1     /* Background (lower priority)          */
#define GSN_MAC_AC_BE                         2     /* Best effort                          */
#define GSN_MAC_AC_VI                         3     /* Video                                */
#define GSN_MAC_AC_VO                         4     /* Voice (highest priority)             */

/* ACI value, used in management frame, page 13, table 5                                */
#define GSN_MAC_ACI_BE                        0     /* Best effort                          */
#define GSN_MAC_ACI_BK                        1     /* Background                           */
#define GSN_MAC_ACI_VI                        2     /* Video                                */
#define GSN_MAC_ACI_VO                        3     /* Voice                                */

#define GSN_MAC_MIN_AIFSN                     2
#define GSN_MAC_AC_MANDATORY_BIT              BIT(4)

#define GSN_MAC_AIFSN           2
#define GSN_MAC_AC_TXOP         0

#define GSN_MAC_ECWMIN_a        4
#define GSN_MAC_ECWMAX_a        10

#define GSN_MAC_ECWMIN_b        5
#define GSN_MAC_ECWMAX_b        10

#define GSN_MAC_ECW_BK_MIN_a                  GSN_MAC_ECWMIN_a
#define GSN_MAC_ECW_BE_MIN_a                  GSN_MAC_ECWMIN_a
#define GSN_MAC_ECW_VI_MIN_a                  ( GSN_MAC_ECWMIN_a - 1 )
#define GSN_MAC_ECW_VO_MIN_a                  ( GSN_MAC_ECWMIN_a - 2 )

#define GSN_MAC_ECW_BK_MAX_a                  GSN_MAC_ECWMAX_a
#define GSN_MAC_ECW_BE_MAX_a                  GSN_MAC_ECWMAX_a
#define GSN_MAC_ECW_VI_MAX_a                  GSN_MAC_ECWMIN_a
#define GSN_MAC_ECW_VO_MAX_a                 ( GSN_MAC_ECWMIN_a - 1 )

#define GSN_MAC_ECW_BK_MIN_b                  GSN_MAC_ECWMIN_b
#define GSN_MAC_ECW_BE_MIN_b                  GSN_MAC_ECWMIN_b
#define GSN_MAC_ECW_VI_MIN_b                 ( GSN_MAC_ECWMIN_b - 1)
#define GSN_MAC_ECW_VO_MIN_b                 ( GSN_MAC_ECWMIN_b - 2)

#define GSN_MAC_ECW_BK_MAX_b                  GSN_MAC_ECWMAX_b
#define GSN_MAC_ECW_BE_MAX_b                  GSN_MAC_ECWMAX_b
#define GSN_MAC_ECW_VI_MAX_b                  GSN_MAC_ECWMIN_b
#define GSN_MAC_ECW_VO_MAX_b                 ( GSN_MAC_ECWMIN_b - 1)

#define GSN_MAC_AIFSN_BK                      7
#define GSN_MAC_AC_BK_TXOP_b                  0L
#define GSN_MAC_AC_BK_TXOP_ag                 0L

#define GSN_MAC_AIFSN_BE                      3
#define GSN_MAC_AC_BE_TXOP_b                  0L
#define GSN_MAC_AC_BE_TXOP_ag                 0L

#define GSN_MAC_AIFSN_VI                      2
#define GSN_MAC_AC_VI_TXOP_b                188L    /* 6016us / 32 us, page 20 for WME spec */
#define GSN_MAC_AC_VI_TXOP_ag                94L    /* 3008us / 32 us, page 20 for WME spec */

#define GSN_MAC_AIFSN_VO                      2
#define GSN_MAC_AC_VO_TXOP_b                102L    /* 3264us / 32 us, page 20 for WME spec */
#define GSN_MAC_AC_VO_TXOP_ag                47L    /* 1504us / 32 us, page 20 for WME spec */


/*
 * Spectrum & Power Management definitions
 ****************************************************************************************
 */

/*
 *  Spectrum & Power Management Frame structure
 *
 *  +--------------------------------------------------+
 *  | Categorie | Action | Dialog Token | Elements ... |
 *  +--------------------------------------------------+
 *     1 Byte     1 Byte     1 Byte        Variable
 *
 */


/*
 *  Spectrum & Power Management Element structure
 *
 *  +----------------------------------------+
 *  | Element ID | Length | Element Data ... |
 *  +----------------------------------------+
 *     1 Byte     1 Byte       Variable
 *
 */


/* Spectrum & Power Management Frame Offset                                             */
#define GSN_MAC_ACTION_FRAME_CATEGORIE_OFT    0
#define GSN_MAC_ACTION_FRAME_ACTION_OFT       1
#define GSN_MAC_ACTION_FRAME_TOKEN_OFT        2
#define GSN_MAC_ACTION_FRAME_INFO_OFT         3

/*
 * Spectrum & Power Management Element Offset
 */

/* Power Constraint Element                                                             */
#define GSN_MAC_INFOELT_POWER_CONSTRAINT_OFT  2

#define GSN_MAC_POWER_CONSTRAINT_ELT_LEN      3

/* Power Capability Element                                                             */
#define GSN_MAC_INFOELT_MIN_TX_POWER_OFT      2
#define GSN_MAC_INFOELT_MAX_TX_POWER_OFT      3

#define GSN_MAC_POWER_CAPABILITY_ELT_LEN      4

/* TPC Report Element                                                                   */
#define GSN_MAC_INFOELT_TX_POWER_OFT          2
#define GSN_MAC_INFOELT_LINK_MARGIN_OFT       3

#define GSN_MAC_TPC_REPORT_ELT_LEN            4

/* Supported Channels Element                                                           */
#define GSN_MAC_INFOELT_FIRST_CHANNEL_OFT     2
#define GSN_MAC_INFOELT_NUMBER_CHANNEL_OFT    3

/* Channel Switch Annoncement Element                                                   */
#define GSN_MAC_INFOELT_SWITCH_MODE_OFT       2
#define GSN_MAC_INFOELT_SWITCH_NEW_CHAN_OFT   3
#define GSN_MAC_INFOELT_SWITCH_COUNT_OFT      4

#define GSN_MAC_CHANNEL_SWITCH_ELT_LEN        5

/* Measurement Request/Report Element                                                   */
#define GSN_MAC_INFOELT_MEASURE_TOKEN_OFT     2
#define GSN_MAC_INFOELT_MEASURE_MODE_OFT      3
#define GSN_MAC_INFOELT_MEASURE_TYPE_OFT      4

#define GSN_MAC_INFOELT_MEASURE_CHANNEL_OFT   5
#define GSN_MAC_INFOELT_MEASURE_START_OFT     6
#define GSN_MAC_INFOELT_MEASURE_DURATION_OFT 14

#define GSN_MAC_INFOELT_MEASURE_INFO_OFT     16

#define GSN_MAC_MEAS_REQ_CNF_ELT_LEN          5
#define GSN_MAC_MEAS_REQ_ELT_LEN             16
#define GSN_MAC_MEAS_REQ_FRAME_LEN           19
#define GSN_MAC_MEAS_REP_BASIC_ELT_LEN       17
#define GSN_MAC_MEAS_REP_BASIC_FRAME_LEN     20
#define GSN_MAC_MEAS_REP_CCA_ELT_LEN         17
#define GSN_MAC_MEAS_REP_CCA_FRAME_LEN       20
#define GSN_MAC_MEAS_REP_RPI_ELT_LEN         24
#define GSN_MAC_MEAS_REP_RPI_FRAME_LEN       27
#define GSN_MAC_MEAS_REP_ERR_ELT_LEN          5
#define GSN_MAC_MEAS_REP_ERR_FRAME_LEN        8

/* Quiet Element                                                                        */
#define GSN_MAC_INFOELT_QUIET_COUNT_OFT       2
#define GSN_MAC_INFOELT_QUIET_PERIOD_OFT      3
#define GSN_MAC_INFOELT_QUIET_DURATION_OFT    4
#define GSN_MAC_INFOELT_QUIET_OFFSET_OFT      6

#define GSN_MAC_QUIET_EMT_LEN                 8

/* IBSS DFS Element                                                                     */
#define GSN_MAC_INFOELT_DFS_OWNER_MAC_OFT     2
#define GSN_MAC_INFOELT_DFS_RECOVERY_OFT      8
#define GSN_MAC_INFOELT_DFS_INFO_OFT          9


/*
 * Spectrum & Power Management values
 */

/* MAC Action Spectrum Categorie                                                        */
#define GSN_MAC_ACTION_CATEGORY_ERROR      0x80
#define GSN_MAC_ACTION_CATEGORY_SPECTRUM      0

/* MAC Action Spectrum Categorie => Sub Action                                          */
#define GSN_MAC_ACTION_MEASURE_REQUEST        0
#define GSN_MAC_ACTION_MEASURE_REPORT         1
#define GSN_MAC_ACTION_TPC_REQUEST            2
#define GSN_MAC_ACTION_TPC_REPORT             3
#define GSN_MAC_ACTION_CHANNEL_SWITCH         4


/* Channel Switch Annoncement Mode                                                      */
#define GSN_MAC_SWITCH_MODE_NORMAL            0
#define GSN_MAC_SWITCH_MODE_SILENT            1

/* Measurement Request Mode                                                             */
#define GSN_MAC_MEASURE_MODE_ENABLE           BIT(1)
#define GSN_MAC_MEASURE_MODE_REQUEST          BIT(2)
#define GSN_MAC_MEASURE_MODE_REPORT           BIT(3)

/* Measurement Report Mode                                                              */
#define GSN_MAC_MEASURE_MODE_LATE             BIT(0)
#define GSN_MAC_MEASURE_MODE_INCAPABLE        BIT(1)
#define GSN_MAC_MEASURE_MODE_REFUSED          BIT(2)

/* Measurement Request Type                                                             */
#define GSN_MAC_MEASURE_TYPE_BASIC            0
#define GSN_MAC_MEASURE_TYPE_CCA              1
#define GSN_MAC_MEASURE_TYPE_RPI              2

/* Measurement Report Map Bits                                                          */
#define GSN_MAC_MEASURE_MAP_FREE           0x00
#define GSN_MAC_MEASURE_MAP_BSS               BIT(0)
#define GSN_MAC_MEASURE_MAP_OFDM              BIT(1)
#define GSN_MAC_MEASURE_MAP_UNIDENTIFIED      BIT(2)
#define GSN_MAC_MEASURE_MAP_RADAR             BIT(3)
#define GSN_MAC_MEASURE_MAP_UNMEASURED        BIT(4)
#define GSN_MAC_MEASURE_MAP_MASK           0x1F

/*
 * Other Mac Frame related definitions
 ****************************************************************************************
 */
#define GSN_MAC_FCS_LEN                       4

/*
 * Regulatory domain (802.11d) definitions
 ****************************************************************************************
 */

/*
 *  Regulatory Domain Element structure
 *
 *  +----------------------------------------+
 *  | Element ID | Length | Element Data ... |
 *  +----------------------------------------+
 *     1 Byte     1 Byte       Variable
 *
 */

/* Country Information Element                                                          */
#define GSN_MAC_INFOELT_COUNTRY_STRING_OFT    2
#define GSN_MAC_INFOELT_CHANNEL_GROUP_OFT     5

