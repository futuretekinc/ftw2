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
* $RCSfile: gsn_dtls_common_fpt.h,v $
*
* Description : This file contains public definitions for DTLS. 
*******************************************************************************/
#ifndef _GSN_DTLS_COMMON_FPT_H_
#define _GSN_DTLS_COMMON_FPT_H_
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
typedef UINT8 * (*DTLS_REASSEMBLE_MSG_FP_T)(  DTLS_CORE_T *conn, UINT8* buf,  
    UINT32 *pReassmblLen );


typedef UINT8 *
(* DTLS_PREPARE_FLIGHT_FP_T)( GSN_DTLS_CONN_T *dtlsConn,  pkt_info_t* info, 
	UINT32 datalen );

typedef GSN_STATUS (*DTLS_FRAGMENT_MSG_FP_T)( DTLS_CORE_T *conn, pkt_info_t* info, 
    UINT32 datalen, UINT8 content_type );


typedef GSN_STATUS
(*DTLS_SEND_DATA_FP_T)( GSN_DTLS_CONN_T *dtlsConn, DTLS_DATA_INFO_T* pData, 
    int sendFlag, UINT8 rData );

typedef VOID (*DTLS_RETRANSMIT_CB_FP_T)( VOID* context,
    GSN_SOFT_TMR_HANDLE_T  timerHandle );

typedef VOID (*DTLS_RETRANSMIT_ABORT_FP_T)( GSN_DTLS_CONN_T *dtlsConn );


typedef GSN_STATUS (*DTLS_PROICESS_HANSHAKE_FP_T)( DTLS_CORE_T *conn,
	UINT8* pData, int len, DTLS_PROCESS_HANDSHAKE_T cb );

typedef int (*DTLS_DECRYPT_FP_T)( DTLS_CORE_T *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);

typedef int (*DTLS_ENCRYPT_FP_T)(DTLS_CORE_T *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);

typedef void (*DTLS_ALERT_FP_T)( DTLS_CORE_T *conn, u8 level, u8 description);

extern _RPST_ DTLS_REASSEMBLE_MSG_FP_T dtls_reassemble_msg_FP;


extern _RPST_ DTLS_PREPARE_FLIGHT_FP_T dtls_prepare_flight_FP;


extern _RPST_ DTLS_FRAGMENT_MSG_FP_T dtls_fragment_msg_FP;


extern _RPST_ DTLS_SEND_DATA_FP_T dtls_send_data_FP;

extern _RPST_ DTLS_RETRANSMIT_CB_FP_T dtls_retransmit_cb_FP;

extern _RPST_ DTLS_RETRANSMIT_ABORT_FP_T dtls_retransmit_abort_FP;


extern _RPST_ DTLS_PROICESS_HANSHAKE_FP_T dtls_proicess_hanshake_FP;

extern _RPST_ DTLS_DECRYPT_FP_T dtls_decrypt_FP;

extern _RPST_ DTLS_ENCRYPT_FP_T dtls_encrypt_FP;

extern _RPST_ DTLS_ALERT_FP_T dtls_alert_FP;

#ifdef __cplusplus
}
#endif        
#endif /* _GSN_DTLS_COMMON_FPT_H_ */
 






