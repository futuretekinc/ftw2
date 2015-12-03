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
* $RCSfile: gsn_ext_otafu.c,v
*/


#include "gsn_includes.h"
#include "../inc/gsn_ext_otafu.h"
#include "gsn_ext_otafu_fpt.h"
#include "../inc/gsn_dsv_httpd.h"

#include "supplicant/crypto/crypto.h"
#include "supplicant/crypto/tls.h"
#include "supplicant/tls/tlsv1_client.h"

#include "supplicant/tls/tlsv1_common.h"
#include "supplicant/tls/tlsv1_record.h"

#include "supplicant/tls/tlsv1_client_i.h"
#include "supplicant/tls/x509v3.h"


UINT8 *errMsgExtOtafu [] = {
	"SUCCESS",
	"Init Fail",
	"Tag Name Invalid",
	"Write Fail",
	"CB Update Fail"
};
GSN_EXTOTAFU_CTX_T *pExtOtafuCtx;

PRIVATE GSN_STATUS
GsnExtOtafu_DeInit(GSN_EXTOTAFU_CTX_T *pCtx);

/**
 *****************************************************************************
 * @ingroup GsnFileUpload
 * @brief Finding Bin file.
 *    This function finds the type of bin file
 *    This will be called whenever data arrives
 * @param name - IN This is the name element
 *
 * @retval it returns GSN_FWUP_ID_T if file is correct
 * @retval it returns 0 if file is incorrect
 *****************************************************************************/

PRIVATE INT32
GsnExtOtafu_BinIndexGet(char* pTagName, INT32 tagNameLength)
{
    {
        if(GsnExtOtafu_BinIndexGet_FP)
        {
            return GsnExtOtafu_BinIndexGet_FP(pTagName, tagNameLength);
        }
    }
	int retVal = 0;

	if (memcmp(pTagName, "fw_image", GSN_OTAFU_FW_TAG_LEN) == 0)
		retVal = 1;
	
#ifdef ADK_OTAFU_DSV	
	else if (memcmp(pTagName, "digital_sign", GSN_OTAFU_SIGN_TAG_LEN) == 0)
		retVal = 2;
#endif

	return retVal;
}


/**
 *****************************************************************************
 * @ingroup GsnFileUpload
 * @brief firmware upgrade starts
 *    This function is use to initialise before writing content to ext flash
 *    This will be called whenever firmware upload starts
 * @param pAppSm - IN App statemachine structure
 *
 * @retval it returns GSN_SUCCESS if it is success
 * @retval it returns GSN_FAILURE if it is failed
 *****************************************************************************/

PUBLIC GSN_STATUS
GsnExtOtafu_FwupInit(GSN_EXTOTAFU_CTX_T *pCtx)
{
    UINT32 factFlag;
    {
        if(GsnExtOtafu_FwupInit_FP)
        {
            return GsnExtOtafu_FwupInit_FP(pCtx);
        }
    }

    GSN_STATUS retVal = GSN_SUCCESS;
    factFlag = pCtx->extFwupCtx.fwupCtx.factImgReq;
//    memset(&pCtx->extFwupCtx.fwupCtx, 0, sizeof(GSN_FWUP_CTX_T));

    pCtx->extFwupCtx.fwupCtx.factImgReq = factFlag;
	retVal = GsnExtFwup_Init(&pCtx->extFwupCtx);

#ifdef ADK_OTAFU_DSV	

	if (retVal == GSN_SUCCESS)
	{
		retVal = GsnOtafuDsv_Init(&pCtx->otafuDsvCtx);
		if (retVal == GSN_SUCCESS)
		{
			GsnOtafuDsv_Sha1Init(&pCtx->otafuDsvCtx);
		}
	}
	
#endif

   	return retVal;
}


/**
 *****************************************************************************
 * @ingroup GsnFileUpload
 * @brief write to ext flash
 *    This function is to write content to external flash
 *    This will be called whenever binary data is recieved
 * @param pAppSm - IN App statemachine structure
 * @param buffer - IN This is the pointer to buffer, where actual data starts
 * @param bufferLen - IN Length of the buffer
 * @param firmware - IN Type of binary
 *
 * @retval it returns GSN_SUCCESS if it is success
 * @retval it returns GSN_FAILURE if it is failed
 *****************************************************************************/

PRIVATE GSN_STATUS
GsnExtOtafu_FwupContinue(GSN_EXTOTAFU_CTX_T *pCtx, INT8 *buffer, UINT32 bufferLen)
{
    {
        if(GsnExtOtafu_FwupContinue_FP)
        {
            return GsnExtOtafu_FwupContinue_FP(pCtx, buffer, bufferLen);
        }
    }
	
	GSN_STATUS retVal = GSN_SUCCESS;
	INT8 *bufferptr =  buffer;
	UINT32 dataLen = bufferLen;

	if (NULL != buffer)
	{		
#ifdef ADK_OTAFU_DSV	
		GsnOtafuDsv_Sha1Update(&pCtx->otafuDsvCtx, bufferptr, dataLen);
#endif
   		/* Write recieved chunk to external flash */
   		retVal = GsnExtFwup_DownLoad(&pCtx->extFwupCtx, (UINT8 *)buffer, bufferLen);

   		if (retVal != GSN_SUCCESS)
   		{
       		(*pCtx->otafuCtx.cbFn)(pCtx->otafuCtx.cbFnCtx, GSN_OTAFU_EVENT_FWUP_FAIL);
      		GsnExtOtafu_DeInit(pCtx);
			printf("[File_upload_App_fwuploc] AppFileUpload_PushContinue - Failure\r\n");
       		return retVal;
   		}
   	}

	return retVal;
}


/**
 *****************************************************************************
 * @ingroup GsnFileUpload
 * @brief Deintialise.
 *    This function is used end writing data, if end of the file reached
 *    This will be called whenever file ends
 * @param pAppSm - IN App statemachine structure
 *
 * @retval it returns GSN_SUCCESS if it is success
 * @retval it returns GSN_FAILURE if it is failed
 *****************************************************************************/

PRIVATE GSN_STATUS
GsnExtOtafu_FwupEnd(GSN_EXTOTAFU_CTX_T *pCtx)
{
    {
        if(GsnExtOtafu_FwupEnd_FP)
        {
            return GsnExtOtafu_FwupEnd_FP(pCtx);
        }
    }

	GSN_STATUS retVal = GSN_SUCCESS;

	retVal = GsnExtFwup_DownLoadEnd(&pCtx->extFwupCtx);
	if (retVal != GSN_SUCCESS)
	{
        (*pCtx->otafuCtx.cbFn)(pCtx->otafuCtx.cbFnCtx, GSN_OTAFU_EVENT_FWUP_FAIL);
		GsnExtOtafu_DeInit(pCtx);
		return retVal;
	}
	(*pCtx->otafuCtx.cbFn)(pCtx->otafuCtx.cbFnCtx, GSN_OTAFU_EVENT_FWUP_SUCCESS);


	return retVal;

}

/**
 *****************************************************************************
 * @ingroup GsnFileUpload
 * @brief De-intialising.
 *    This function is for de-intialising whenever connection is end in the middle or
 *    when wrong binaries are posted
 * @param pAppSm - IN App statemachine structure
 *
 * @retval it returns GSN_SUCCESS if it is success
 * @retval it returns GSN_FAILURE if it is failed
 *****************************************************************************/

PRIVATE GSN_STATUS
GsnExtOtafu_DeInit(GSN_EXTOTAFU_CTX_T *pCtx)
{
    {
        if(GsnExtOtafu_DeInit_FP)
        {
            return GsnExtOtafu_DeInit_FP(pCtx);
        }
    }

    GSN_STATUS retVal = GSN_SUCCESS;

#ifdef ADK_OTAFU_DSV

	GsnOtafuDsv_DeInit (&pCtx->otafuDsvCtx);
	GsnDsvHttpd_DeInit();

#endif

	GsnExtFwup_DeInit(&pCtx->extFwupCtx);
    (*pCtx->otafuCtx.cbFn)(pCtx->otafuCtx.cbFnCtx, GSN_OTAFU_EVENT_DEINIT);

	return retVal;

}

/**
 *****************************************************************************
 * @ingroup GsnFileUpload
 * @brief firmware upgrade of uploaded binaries.
 *    This function handles the event of the file upload for the firmware upgrade locally
 *    This will be called whenever file event happens
 * @param inputElementInfo - IN File attributes of uploaded file for firmware upgrade
 * @param buffer - IN This is the pointer to buffer, where actual data starts
 * @param bufferLen - IN Length of the buffer
 * @param event - IN event of the file
 * @param statusMsg - OUT Information Log
 *
 * @retVal it returns TRUE, if it is success
 * @retVal it returns FALSE, if it is fail
 *****************************************************************************/
PRIVATE BOOL
GsnExtOtafu_Cb(GSN_HTTPD_ELEMENT_INFO_T inputElementInfo, INT8 *buffer, UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event, GSN_HTTPD_STATUS_INFO_T *statusMsg)
{
    {
        if(GsnExtOtafu_Cb_FP)
        {
            return GsnExtOtafu_Cb_FP(inputElementInfo, buffer, bufferLen, event, statusMsg);
        }
    }

	static INT8 inputElement = 0;
	BOOL retVal = TRUE;
	GSN_STATUS retStatus = GSN_SUCCESS;
	int index = 0;
	UINT32 dsvStatus = 0;

	switch (event)
	{
		case START_UPLOAD:
			pExtOtafuCtx->otafuCtx.status = GSN_OTAFU_SUCCESS;
			retStatus = GsnExtOtafu_FwupInit(pExtOtafuCtx);
			if (retStatus != GSN_SUCCESS)
			{
				retVal = FALSE;
				pExtOtafuCtx->otafuCtx.status = GSN_OTAFU_INIT_FAIL;
			}
			printf("[File_upload_App_fwuploc] Writing to External Flash starts \r\n");
			break;

		case START_FILE:
			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				retVal = FALSE;
				break;
			}
			inputElement = GsnExtOtafu_BinIndexGet(inputElementInfo.name, inputElementInfo.nameLen);
			if(!inputElement)
			{
				printf("[File_upload_App_fwuploc] firmware = %d\r\n",inputElement);
				retStatus = GSN_FAILURE;
				retVal = FALSE;
				pExtOtafuCtx->otafuCtx.status = GSN_OTAFU_INVALID_TAG;

#ifdef ADK_OTAFU_DSV

				GsnOtafuDsv_DeInit (&pExtOtafuCtx->otafuDsvCtx);
				GsnDsvHttpd_DeInit();

#endif
			}
			break;

		case CONTINUE_FILE:
			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				retVal = FALSE;
				break;
			}
			printf("*");
			if (inputElement==GSN_EXT_FLASH_OTAFU_FW)
			{
				retStatus = GsnExtOtafu_FwupContinue(pExtOtafuCtx, buffer, bufferLen);
				if (retStatus != GSN_SUCCESS)
				{
					retVal = FALSE;
					pExtOtafuCtx->otafuCtx.status = GSN_OTAFU_WRITE_FAIL;
				}
			}
			
#ifdef ADK_OTAFU_DSV				
			if(inputElement==GSN_EXT_FLASH_OTAFU_SIGN)
			{
				printf("Signature Upload in process...\r\n");	
				
				GsnOtafuDsv_SignUpdate(&pExtOtafuCtx->otafuDsvCtx, buffer, bufferLen);
			}
#endif			
			break;

		case END_FILE:
			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				retVal = FALSE;
				break;
			}
#ifdef ADK_OTAFU_DSV
			if (inputElement == GSN_EXT_FLASH_OTAFU_FW)
			{
 				GsnOtafuDsv_Sha1Finish(&pExtOtafuCtx->otafuDsvCtx);
			}
#else
			retStatus = GsnExtOtafu_FwupEnd(pExtOtafuCtx);
			if (retStatus != GSN_SUCCESS)
			{
				retVal = FALSE;
				pExtOtafuCtx->otafuCtx.status = GSN_OTAFU_CB_UPDATE_FAIL;
			}
#endif

			printf("\r\n[File_upload_App_fwuploc] firmware = %d\r\n", inputElement);
			inputElement = 0;
			break;

		case START_NON_FILE:
			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				retVal = FALSE;
				break;
			}
			inputElement = GsnExtOtafu_BinIndexGet(inputElementInfo.name, inputElementInfo.nameLen);
			//printf("[File_upload_App] Name is = %s \r\n", inputElementInfo.name);
			printf("[File_upload_App] Its a Non file Input Element \r\n");
			printf("[File_upload_App]**************************\r\n");
			break;

		case CONTINUE_NON_FILE:
			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				retVal = FALSE;
				break;
			}
			if (!inputElement)
				inputElement = GsnExtOtafu_BinIndexGet(inputElementInfo.name, inputElementInfo.nameLen);
			if (bufferLen)
			{
				printf("[File_upload_App] BufferLength in App = %d\r\n", bufferLen);
			}
			
			while (index < bufferLen)
			{
				printf("%c", buffer[index]);
				index++;
			}
			break;

		case END_NON_FILE:
			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				retVal = FALSE;
				break;
			}
			printf("\r\n[File_upload_App] backupDataCount %d\r\n", backupDataCount);
			printf("\r\n[File_upload_App]**************************");
			printf("\r\n[File_upload_App] Its end of Non file Input Element\r\n");
			break;

		case END_UPLOAD:
			printf("\r\n[File_upload_App_fwuploc] Writing to External Flash Ends \r\n");


			sprintf(statusMsg->pMsg,"<html><body><div><h1>Firmware Upgrade</h1></div><div id=\"fwupmsg\">");

			if (GSN_OTAFU_SUCCESS != pExtOtafuCtx->otafuCtx.status)
			{
				/* DeInit is done inline where the error happened */
				strcpy(statusMsg->pMsg + strlen(statusMsg->pMsg), "Upload Failed: ");
				sprintf(statusMsg->pMsg,"%s %s", statusMsg->pMsg, errMsgExtOtafu [pExtOtafuCtx->otafuCtx.status]);
				sprintf(statusMsg->pMsg, "%s </div><div><a href=\"javascript:self.close()\">Close the browser window</a></div></body></html>", statusMsg->pMsg);

				(*pExtOtafuCtx->otafuCtx.cbFn)(pExtOtafuCtx->otafuCtx.cbFnCtx, GSN_OTAFU_EVENT_FWUP_FAIL);
			}
			else
			{
#ifdef ADK_OTAFU_DSV				

				//Point the Buffer to the start of Signature data
				dsvStatus = GsnOtafuDsv_Verify(&pExtOtafuCtx->otafuDsvCtx);	
                if(dsvStatus)
                {
					GsnExtOtafu_DeInit(pExtOtafuCtx);
					strcpy(statusMsg->pMsg + strlen(statusMsg->pMsg), "Upload Failed: ");
					sprintf(statusMsg->pMsg,"%s Signature Mismatch", statusMsg->pMsg);
					sprintf(statusMsg->pMsg, "%s </div><div><a href=\"javascript:self.close()\">Close the browser window</a></div></body></html>", statusMsg->pMsg);

					retVal = FALSE;	
					(*pExtOtafuCtx->otafuCtx.cbFn)(pExtOtafuCtx->otafuCtx.cbFnCtx, GSN_OTAFU_EVENT_FWUP_FAIL);
                }
				else
				{
					retVal = GsnExtOtafu_FwupEnd(pExtOtafuCtx);

					if (retVal == GSN_SUCCESS)
					{						
						GsnOtafuDsv_DeInit (&pExtOtafuCtx->otafuDsvCtx);
					strcpy(statusMsg->pMsg + strlen(statusMsg->pMsg), "Upload Success: ");
					sprintf(statusMsg->pMsg,"%s Signature Verification Passed", statusMsg->pMsg);
					sprintf(statusMsg->pMsg, "%s. Device will reboot Now</div><div><a href=\"javascript:self.close()\">Close the browser window</a></div></body></html>", statusMsg->pMsg);
						retVal = TRUE;
					}
					else
					{
						/* Do not call DeInit since it is already called as part of FwupEnd */
						strcpy(statusMsg->pMsg + strlen(statusMsg->pMsg), "Upload Failed: ");
						sprintf(statusMsg->pMsg,"%s Updating Control Block Failed", statusMsg->pMsg);
						sprintf(statusMsg->pMsg, "%s </div><div><a href=\"javascript:self.close()\">Close the browser window</a></div></body></html>", statusMsg->pMsg);

						retVal = FALSE;
					}					
				}					
#else
			strcpy(statusMsg->pMsg + strlen(statusMsg->pMsg), "Upload Success: ");
			sprintf(statusMsg->pMsg,"%s No Signature Verification", statusMsg->pMsg);
			sprintf(statusMsg->pMsg, "%s. Device will reboot Now</div><div><a href=\"javascript:self.close()\">Close the browser window</a></div></body></html>", statusMsg->pMsg);
#endif			
			}

			statusMsg->msgLength = strlen(statusMsg->pMsg);
			//printf("[File_upload_App_fwuploc] statusMsg->msgLength = %d\r\n", statusMsg->msgLength);

			inputElement = 0;
			break;
		case CONNEC_LOST:
			printf("\r\n[File_upload_App_fwuploc] Connection lost in the Middle of data transfer\r\n");
			inputElement = 0;	
			GsnExtOtafu_DeInit(pExtOtafuCtx);
			retVal = FALSE;
			break;

		default:
			printf("[File_upload_App_fwuploc] Default Case in App \r\n");
			break;

	}

	return retVal;

}


PUBLIC VOID
GsnExtOtafu_Init(GSN_EXTOTAFU_CTX_T* pCtx)
{
    {
        if(GsnExtOtafu_Init_FP)
        {
            GsnExtOtafu_Init_FP(pExtOtafuCtx);
            return;
        }
    }
    pExtOtafuCtx = pCtx;
	pCtx->otafuCtx.status  = GSN_OTAFU_SUCCESS;
    GsnHttpd_FileApiConfig(GSN_HTTP_EXT_OTAFU_API_PATH, GsnExtOtafu_Cb, GSN_HTTPD_URI_METHOD_POST);
#ifdef ADK_OTAFU_DSV				
	GsnDsvHttpd_Init();

#endif
}



