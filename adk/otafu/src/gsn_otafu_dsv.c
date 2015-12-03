/*******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: gsn_otafu_dsv.c,v
*/

#ifdef ADK_OTAFU_DSV	

#include "gsn_includes.h"
#include "../inc/gsn_ext_otafu.h"
#include "../inc/gsn_otafu_dsv.h"
#include "gsn_ext_otafu_fpt.h"
#include "supplicant/crypto/crypto.h"
#include "supplicant/tls/tlsv1_client.h"
#include "supplicant/tls/tlsv1_common.h"
#include "supplicant/tls/tlsv1_record.h"
#include "supplicant/tls/tlsv1_client_i.h"
#include "supplicant/tls/x509v3.h"
#include "fs/api/api_safe.h"

PUBLIC GSN_STATUS
GsnOtafuDsv_Init (GSN_OTAFU_DSV_CTX_T *otafuDsvCtx)
{	
	otafuDsvCtx->signatureBuf = MALLOC(GSN_OTAFU_DSV_SIGN_LEN);

	if (otafuDsvCtx->signatureBuf == NULL)
	{
		return GSN_FAILURE;
	}
	else
        {
		memset(otafuDsvCtx->signatureBuf, 0, GSN_OTAFU_DSV_SIGN_LEN);
        }
	GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
	return GSN_SUCCESS;
}

PUBLIC VOID
GsnOtafuDsv_DeInit (GSN_OTAFU_DSV_CTX_T *otafuDsvCtx)
{
	if (otafuDsvCtx->signatureBuf != NULL)
	{
		FREE(otafuDsvCtx->signatureBuf);		
	}
	otafuDsvCtx->signatureLen = 0;
	GsnHeIf_DriverSuspend();
	return;
}

PUBLIC VOID
GsnOtafuDsv_Sha1Init(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx)
{
	memset(otafuDsvCtx->sha1Ctx, 0, sizeof(otafuDsvCtx->sha1Ctx));	
	otafuDsvCtx->sha1Ctx = crypto_hash_init(CRYPTO_HASH_ALG_SHA1, NULL, NULL);
}

PUBLIC VOID
GsnOtafuDsv_Sha1Update(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx, INT8 *buffer, UINT32 dataLen)
{
	crypto_hash_update(otafuDsvCtx->sha1Ctx, (unsigned char const*)buffer, dataLen);
}

PUBLIC VOID
GsnOtafuDsv_Sha1Finish(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx)
{
	size_t hashLen = GSN_OTAFU_DSV_HASH_LEN;
	crypto_hash_finish(otafuDsvCtx->sha1Ctx, otafuDsvCtx->dataHash, &hashLen);
}

PUBLIC GSN_STATUS_T
GsnOtafuDsv_SignUpdate(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx, INT8 *buffer, UINT32 bufferLen)
{
	GSN_STATUS_T retVal;

	if(((bufferLen + otafuDsvCtx->signatureLen) > GSN_OTAFU_DSV_SIGN_LEN) || (otafuDsvCtx->signatureBuf == NULL))
	{
		/* The signature is greater than the expected length. It is a case of invalid signature file or
			 corrupted signature file. Return Failure and abort */

		retVal = GSN_FAILURE;
	}
	else
	{
		/* Valid Signature fragment. Copy it to the signature for verification */
		memcpy(otafuDsvCtx->signatureBuf + otafuDsvCtx->signatureLen, buffer, bufferLen);
		otafuDsvCtx->signatureLen += bufferLen;
		retVal = GSN_SUCCESS;
	}
	
	return retVal;

}
PUBLIC INT32 
GsnOtafuDsv_HashVerify(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx, 
									struct tlsv1_client *conn, 
	                                const u8 *in_data, 
	                                size_t *in_len,
	                                const u8 *in_sig, 
	                                size_t *in_siglen,
	                                u8 *in_hash
	                               )
{
    const u8 *pos;
    size_t  cert_len;
    struct x509_certificate *chain = NULL, *last = NULL, *cert;
    int reason;

    const u8 *pSig = in_sig;
    size_t sigLen = *in_siglen, expected_sign_size;

    struct crypto_public_key *pk;
    u8 *data;
    size_t data_len;
    u8 i;
    pos = in_data;
    cert_len = *in_len;

	

    printf("Server Certificate length = %d\n\r",cert_len);
    
    crypto_public_key_free(conn->server_rsa_key);
    if (tls_parse_cert(pos, cert_len,
                       &conn->server_rsa_key)) {
        printf("TLSv1: Failed to parse the certificate\n\r");
                    
        tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
                  TLS_ALERT_BAD_CERTIFICATE);
        x509_certificate_chain_free(chain);
        return -1;
    }
    
    printf("TLSv1: Successfully parsed certificate\n\r");
					
    cert = x509_certificate_parse(pos, cert_len);
    if (cert == NULL) {

			printf("x509_certificate_parse failed :( \n\r");

            tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
                      TLS_ALERT_BAD_CERTIFICATE);
            x509_certificate_chain_free(chain);
            return -1;
    }

    if (last == NULL)
            chain = cert;
    else
            last->next = cert;
    last = cert;
		
    if (conn->cred &&
		x509_certificate_chain_validate(conn->cred->trusted_certs, chain,
						&reason, conn->disable_time_checks) < 0)
    {
        int tls_reason;
        printf("TLSv1: Server certificate chain validation failed (reason=%d)\r\n", reason);
        switch (reason) {
        case X509_VALIDATE_BAD_CERTIFICATE:
                tls_reason = TLS_ALERT_BAD_CERTIFICATE;
                break;
        case X509_VALIDATE_UNSUPPORTED_CERTIFICATE:
                tls_reason = TLS_ALERT_UNSUPPORTED_CERTIFICATE;
                break;
        case X509_VALIDATE_CERTIFICATE_REVOKED:
                tls_reason = TLS_ALERT_CERTIFICATE_REVOKED;
                break;
        case X509_VALIDATE_CERTIFICATE_EXPIRED:
                tls_reason = TLS_ALERT_CERTIFICATE_EXPIRED;
                break;
        case X509_VALIDATE_CERTIFICATE_UNKNOWN:
                tls_reason = TLS_ALERT_CERTIFICATE_UNKNOWN;
                break;
        case X509_VALIDATE_UNKNOWN_CA:
                tls_reason = TLS_ALERT_UNKNOWN_CA;
                break;
        default:
                tls_reason = TLS_ALERT_BAD_CERTIFICATE;
                break;
        }
        tls_alert(conn, TLS_ALERT_LEVEL_FATAL, tls_reason);
        x509_certificate_chain_free(chain);
        return -1;
    }
    else
    {
        printf("TLSv1: Server certificate chain validation Successfull\r\n");	
    }

    printf("TLSv1: Decrypt signature using public key\r\n");

    printf("cert->public_key_len: %d\r\n",cert->public_key_len);

    pk = crypto_public_key_import(cert->public_key, cert->public_key_len);
    if (pk == NULL) 
    {
        printf("Public Key import Failure :(\r\n");	
        x509_certificate_chain_free(chain);
        return -1;
    }

    printf("Public Key import successful :)\r\n");

    expected_sign_size = chain->sign_value_len;
    
    if (expected_sign_size != sigLen)
    {				
        crypto_public_key_free(pk);
        x509_certificate_chain_free(chain);
        return -1;
    }
            
    data_len = sigLen;
    data = MALLOC(data_len);
    if (data == NULL) {
        printf("os_malloc(data_len) failure\r\n");
        crypto_public_key_free(pk);
        x509_certificate_chain_free(chain);
        return -1;
    }

    if (crypto_public_key_decrypt_pkcs1(pk, pSig, sigLen, data, &data_len) < 0) {
        printf("X509: Failed to decrypt signature\r\n");
        crypto_public_key_free(pk);
        FREE(data);
        x509_certificate_chain_free(chain);
        return -1;
    }
    printf("X509: successfully decrypt signature\r\n");

    printf("Signature=%d\r\n",data_len);
    for (i=0; i<data_len; i++)
    {
        printf("%02x:",data[i]);
    }
    printf("\r\n");

    printf("Validate the hash\r\n");

    if(0 != memcmp(in_hash, data , data_len))
    {
        printf("Ooops hash invalid\r\n");
        crypto_public_key_free(pk);
        FREE(data);
        x509_certificate_chain_free(chain);
        return -1;
    }

    printf("Validated the hash successfully\r\n");

    FREE(data);
    crypto_public_key_free(pk);
    x509_certificate_chain_free(chain);

    return 0;
}


PUBLIC GSN_STATUS_T
GsnOtafuDsv_Verify(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx)
{
		//find the certificate
    UINT8 *pCaCert;	
    UINT32 caCertLen = 0;

    UINT8 *pserverCert;
    UINT32 serverCertLen = 0;

    UINT8 *psignature = otafuDsvCtx->signatureBuf;
    UINT32 signatureLen = otafuDsvCtx->signatureLen;
    F_FILE *rootFd;
    F_FILE *serverFd;

    struct tlsv1_client *tlsv1Conn;

    printf("\r\nStep 2: Verify the server cert with root cert\r\n");

    rootFd = f_open(otafuDsvCtx->rootCertName, "r");

    if(NULL == rootFd)
    {			
            printf("Root certificate not found :(\r\n");
            return GSN_FAILURE;
    }
    caCertLen = f_filelength(otafuDsvCtx->rootCertName);
    pCaCert = MALLOC(caCertLen);

    if(NULL == pCaCert)		
      return GSN_FAILURE;
    
    f_read(pCaCert, 1, caCertLen, rootFd);		
    f_close(rootFd);

    serverFd = f_open(otafuDsvCtx->serverCertName, "r");

    if(NULL == serverFd)
    {			
            printf("Server certificate not found :(\r\n");		
            FREE(pCaCert);
            return GSN_FAILURE;
    }
    serverCertLen = f_filelength(otafuDsvCtx->serverCertName);
    pserverCert = MALLOC(serverCertLen);
    
    if(NULL == pserverCert)		
      return GSN_FAILURE;
    
    f_read(pserverCert, 1, serverCertLen, serverFd);
    f_close(serverFd);

    //initialize tlsv1 client
    tlsv1Conn = (struct tlsv1_client *)tlsv1_client_init();
    if (tlsv1Conn == NULL)
    {
            printf("tlsv1_client_init failed :(\r\n");
            tlsv1_client_deinit(tlsv1Conn);
            FREE(pCaCert);
            FREE(pserverCert);
            return(GSN_FAILURE);
    }
    else
    {
            printf("tlsv1_client_init successfull :)\r\n");
    }


    //add ca cert to the connection 
    if(0x00 != tlsv1_set_ca_cert((struct tlsv1_credentials *)tlsv1Conn,
                                                                             NULL,
                                                                             pCaCert,
                                                                             caCertLen,
                                                                             NULL
                                                                            ))
    {
            tlsv1_client_deinit(tlsv1Conn);
            printf("Registration of root certificate failure :(\r\n");
            FREE(pCaCert);
            FREE(pserverCert);
            return(GSN_FAILURE);
    }
    else
    {
            printf("Registration of root certificate successfully :)\r\n");
    }


    //verify the server certificate credentials
    if (0x00 != GsnOtafuDsv_HashVerify(otafuDsvCtx, tlsv1Conn, pserverCert, &serverCertLen, psignature, &signatureLen, otafuDsvCtx->dataHash))
    {
            tlsv1_client_deinit(tlsv1Conn);
            printf("tlsv1_server_cert_verify failure :(\r\n");
            FREE(pCaCert);
            FREE(pserverCert);
            return(GSN_FAILURE);
    }

    //de-initialize tlsv1 client
    tlsv1_client_deinit(tlsv1Conn);
    FREE(pCaCert);
    FREE(pserverCert);
    return GSN_SUCCESS;
	
}

#endif

