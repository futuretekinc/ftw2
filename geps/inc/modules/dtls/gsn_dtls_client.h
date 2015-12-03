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
* $RCSfile: gsn_dtls_client.h,v $
*
* Description : This file contains public definitions for SDD. SDD( Serial
* Device Driver ) provides APIs for the serial drivers. SDD enabls IP  
* connectivity over serial HI-over-UART communications with an external device.
*******************************************************************************/

#ifndef _GSN_DTLS_CLIENT_H_
#define _GSN_DTLS_CLIENT_H_

/*****************************************************************************
* File Inclusion
*****************************************************************************/


/**
 *******************************************************************************
 * @file gsn_sdd.h
 * @brief GSN SDD public API implementation.
 *    This file contains the public APIs and structures of SDD module.
 ******************************************************************************/


/**
 *******************************************************************************
 * 
 ******************************************************************************/
 

/*******************************************************************************
 * Private Functions prototype
 ******************************************************************************/


/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 *******************************************************************************
 * 
 ******************************************************************************/

DTLS_CORE_T *dtls_client_init( void* );
int dtls_client_set_cred( DTLS_CORE_T *conn, struct tlsv1_credentials* );

int dtls_client_established( DTLS_CORE_T *conn);
int dtls_client_hello_ext( DTLS_CORE_T  *conn, int ext_type,
			   const u8 *data, size_t data_len);
UINT8 * dtls_client_handshake( DTLS_CORE_T  *conn,
			    const UINT8 *in_data, size_t in_len,
			    size_t *out_len );
void dtls_client_deinit( DTLS_CORE_T *conn);

/**
 *******************************************************************************
 *
 *******************************************************************************/
/*******************************************************************************
 * Private Functions
 ******************************************************************************/
 
#endif /* _GSN_DTLS_CLIENT_H_ */
/**
 *******************************************************************************
 * \internal
 * @ingroup GsnDtls
 * @brief Send Confirmation, not for application use.
 * 
 ******************************************************************************/
 






