/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_dtls_common.h,v $
*
* Description : This file contains common public definitions for DTLS. 
*******************************************************************************/
#ifndef _GSN_DTLS_COMMON_H_
#define _GSN_DTLS_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_includes.h"


/**
 *******************************************************************************
 * @file gsn_dtls_common.h
 * @brief GSN DTLS public common API implementation.
 *    This file contains the public APIs and structures of DTLS module.
 ******************************************************************************/


/**
 *******************************************************************************
 * 
 ******************************************************************************/
#define DTLS_MAX_OVERHEAD 72
#define DTLS_HANDSHAKE_HEADER_LEN 12
#define DTLS_HDR_LENGTH ( DTLS_RECORD_HEADER_LEN + \
                DTLS_HANDSHAKE_HEADER_LEN )

#define GSN_DTLS_VERSION 0xFEFF
/**
 *****************************************************************************
 * @ingroup GsnDtls
 * @brief GSN DTLS Structure to define fragment information.
 *    Structure definition fragment information.
 *****************************************************************************/
typedef struct DTLS_FRAG_INFO
{
    UINT16 fragLen; /*< Current Framgement length */
    /*< Offset of the next fragement from the current data pointer */
    UINT16 nextFragOffset; 
}DTLS_FRAG_INFO_T;

/**
 *****************************************************************************
 * @ingroup GsnDtls
 * @brief GSN DTLS Structure to define data info to be send to the other end.
 *    Structure definition for data information to be send to the other end.
 *
 *_____________________________________________________________________________
*|          |           |               |         |                    |
*| numOfFrag| dataOffset| fragInfo .....| GAP     | Fragment data      | .....
*| 2 Bytes  | 2 Bytes   | 4 * numOfFrag | Varibale| fragInof[0].fragLen|
*|          |           |   Bytes       | Bytes   | Bytes              |
*-----------------------------------------------------------------------------
 *****************************************************************************/
typedef struct DTLS_DATA_INFO
{
    UINT16 numOfFrag; /*< Number of fragments the payload contains */
    /*< Offset of the data from the starting address of this structure */
    UINT16 dataOffset; 
    DTLS_FRAG_INFO_T fragInfo[1]; /*< Information about the fragments */
}DTLS_DATA_INFO_T;

typedef struct pkt_info_s
{
    UINT8 *buf;
    UINT8* recHdr; /* Stores the location where the record has to start */
    UINT8  numOfFrag;
    UINT8  curFrag;
    UINT16 bufSize;
}pkt_info_t;

typedef int (*dtls_session_ticket_cb)
(void *ctx, const UINT8 *ticket, size_t len, const UINT8 *client_random,
 const UINT8 *server_random, UINT8 *master_secret);

typedef struct DTLS_CORE 
{
	enum {
		DTLS_CLIENT_HELLO_1 /*0*/, DTLS_SERVER_HELLO_VERIFY/*1*/, 
        DTLS_CLIENT_HELLO_2/*2*/, DTLS_SERVER_HELLO/*3*/, 
        DTLS_SERVER_CERTIFICATE/*4*/, DTLS_SERVER_KEY_EXCHANGE/*5*/, 
        DTLS_SERVER_CERTIFICATE_REQUEST/*6*/,DTLS_SERVER_HELLO_DONE/*7*/, 
        DTLS_CLIENT_CERTIFICATE/*8*/, DTLS_CLIENT_KEY_EXCHANGE/*9*/, 
        DTLS_CLIENT_CHANGE_CIPHER_SPEC/*10*/, DTLS_CERTIFICATE_VERIFY/*11*/, 
        DTLS_SERVER_CHANGE_CIPHER_SPEC/*12*/, DTLS_CLIENT_FINISHED/*13*/, 
        DTLS_SERVER_FINISHED/*14*/, DTLS_ACK_FINISHED/*15*/, DTLS_ESTABLISHED/*16*/,
        DTLS_FAILED/*17*/
	} state;

	struct dtls_record_layer drl;

    u8 session_id[TLS_SESSION_ID_MAX_LEN];
    size_t session_id_len;
    u8 client_random[TLS_RANDOM_LEN];
    u8 server_random[TLS_RANDOM_LEN];
    u8 master_secret[TLS_MASTER_SECRET_LEN];

    u8 alert_level;
    u8 alert_description;
#define MAX_CIPHER_COUNT 30
    u16 cipher_suites[MAX_CIPHER_COUNT];
    size_t num_cipher_suites;
    u16 cipher_suite;
    struct crypto_public_key *server_rsa_key;
    struct tls_verify_hash verify;
    dtls_session_ticket_cb session_ticket_cb;
    void *session_ticket_cb_ctx;

    struct tlsv1_credentials *cred;

    UINT16 readSeq, writeSeq, mtu;

    UINT8 *ressambleMsg;
    UINT16 rmsgLenReceived;
    UINT16 rmsgLen;
    UINT16 rseqNum;
    VOID *dtlsCtx; 

    union
    {
        struct
        {
            unsigned int certificate_requested:1;
            unsigned int session_resumed:1;
            unsigned int session_ticket_included:1;
            unsigned int use_session_ticket:1;
            unsigned int disable_time_checks:1;

            u8 *client_hello_ext;
            size_t client_hello_ext_len;

            /* The prime modulus used for Diffie-Hellman */
            u8 *dh_p;
            size_t dh_p_len;
            /* The generator used for Diffie-Hellman */
            u8 *dh_g;
            size_t dh_g_len;
            /* The server's Diffie-Hellman public value */
            u8 *dh_ys;
            size_t dh_ys_len;

            u8 *cookie;
            u32 cookieLen;
        }client;
        struct
        {
            int verify_peer;
            u16 client_version;
            u8 *session_ticket;
            size_t session_ticket_len;
            int use_session_ticket;

            u8 *dh_secret;
            size_t dh_secret_len;
        }server;
    }specific;
}DTLS_CORE_T;


/*******************************************************************************
 * Private Functions prototype
 ******************************************************************************/

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

typedef int (*DTLS_PROCESS_HANDSHAKE_T)( DTLS_CORE_T *conn, UINT8 ct, UINT8 *buf, 
    size_t *len );
/**
 *******************************************************************************
 * 
 ******************************************************************************/
UINT8 *dtls_reassemble_msg(  DTLS_CORE_T *conn, UINT8* buf,  
    UINT32 *pReassmblLen );

UINT8 *dtls_prepare_flight( GSN_DTLS_CONN_T *conn, pkt_info_t* info, UINT32 datalen );

GSN_STATUS  dtls_fragment_msg( DTLS_CORE_T *conn, pkt_info_t* info, 
    UINT32 datalen, UINT8 content_type );

PUBLIC GSN_STATUS
dtls_send_data( GSN_DTLS_CONN_T *dtlsConn, DTLS_DATA_INFO_T* pData,int sendFlag, UINT8 rData );

PUBLIC GSN_STATUS 
dtls_proicess_hanshake( DTLS_CORE_T *conn, UINT8* pData, int len, 
                       DTLS_PROCESS_HANDSHAKE_T cb );

void dtls_alert( DTLS_CORE_T *conn, u8 level, u8 description);

VOID dtls_retransmit_abort( GSN_DTLS_CONN_T *dtlsConn );

int dtls_decrypt( DTLS_CORE_T *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);

int dtls_encrypt(DTLS_CORE_T *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
/**
 *******************************************************************************
 *
 *******************************************************************************/
/*******************************************************************************
 * Private Functions
 ******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* _GSN_DTLS_COMMON_H_ */ 
/**
 *******************************************************************************
 * \internal
 * @ingroup GsnSdd
 * @brief Send Confirmation, not for application use.
 * 
 ******************************************************************************/
 






