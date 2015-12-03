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
* $RCSfile: gsn_httpd_file_api.h,v $
*
* Description : HTTPD API for upload/download a file
*
*******************************************************************************/

#ifndef _GSN_HTTPD_FILE_API_H_
#define _GSN_HTTPD_FILE_API_H_

//#ifdef GSN_FILE_UPLOAD_API


/**
 ****************************************************************************
 * @ingroup GsnFileUpload
 * 
 * @brief This structure describes file parameters, contents.
 *   
 ****************************************************************************/

typedef struct USER_INPUT_ELEMENT_STRUCTURE
{
	BOOL   fileElement;					/**< File input element Flag */
	INT8*  filename;                    /**< Name of the File */
	INT32  filenameLen;					/**< Length of File name */
	INT8*  name;						/**< Name parameter which describes the file */
	INT32  nameLen;						/**< Length of Tag name */
	INT8*  contentType;					/**< Content Type of the file */
	INT32  contentTypeLen;				/**< Length of contentType of the file */
}GSN_HTTPD_ELEMENT_INFO_T;  

/**
 ****************************************************************************
 * @ingroup GsnFileUpload
 * 
 * @brief This structure describes file parameters, contents.
 *   
 ****************************************************************************/

typedef struct STATUS_MSG_STRUCTURE
{
	INT32 msgLength;
	char *pMsg;
}GSN_HTTPD_STATUS_INFO_T;

/**
****************************************************************************
* @ingroup GsnFileUpload
* 
* @brief This enum is collection of file upload events
*   
****************************************************************************/


typedef enum {
	START_FILE        =1,      	   /* START OF THE FILE   */
	CONTINUE_FILE     =2,	       /* CONTINUE_FILE        */ 
	END_FILE          =4,	       /* END_FILE                 */
	START_NON_FILE    =8,          /* START OF THE FILE   */
	CONTINUE_NON_FILE =16,		   /* CONTINUE_FILE        */
	END_NON_FILE      =32,         /* END_FILE                 */
	START_UPLOAD      =64,         /* START_UPLOAD        */
	END_UPLOAD        =128,        /* END_UPLOAD           */
	CONNEC_LOST		  =256		   /* CONNEC_LOST         */
} GSN_HTTPD_ELEMENT_EVENTS_T;

/**
****************************************************************************
* @ingroup GsnFileUpload
* 
* @brief This is user call back prototype.
*   
****************************************************************************/

typedef BOOL (*GSN_HTTPD_APP_HANDLER_FN_T)(GSN_HTTPD_ELEMENT_INFO_T inputElementInfo, INT8 *buffer, UINT32 bufferLen, GSN_HTTPD_ELEMENT_EVENTS_T event, GSN_HTTPD_STATUS_INFO_T *statusInfo);

/**
****************************************************************************
* @ingroup GsnFileUpload
* 
* @brief This is user app structure for registration.
*   
****************************************************************************/

UINT8
GsnHttpd_FileApiConfig(char* uri, GSN_HTTPD_APP_HANDLER_FN_T user_app_cb, UINT8 methods);

VOID 
GsnHttpd_FileApiInit();

//#endif

#endif   /* _GSN_HTTPD_FILE_API_H_ */

