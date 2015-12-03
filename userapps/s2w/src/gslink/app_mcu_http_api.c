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
* $RCSfile: app_mcu__http_api.c,v
*/

/*
 * app_mcu__http_api.c
 *
 *  Created on: Nov 9, 2011
 *      Author: PViswanathan
 */
/*
#include "modules/http/include/trsocket.h"
#include "modules/http/include/trmacro.h"

#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
//#include <trglobal.h>
*/
#include <string.h>
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
#include "modules/http/gsn_httpd_debug.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"

#include "modules/xml_string_parser/gsn_xml_string_parser.h"

#include "hal/s2w.h"
#include "hal/s2w_net.h"

#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"

#include "app_mcu_def.h"
//#include "app_mcu_driver.h"

//#include "app_mcu_xml_schema.c"
#include "main/app_main_ctx.h"
//#include <trhttpc.h>
#include <parser\S2w_command.h>
#include"app_defines_builder.h"
#include "hal/s2w_config.h"
#include "parser/s2w_process.h"


extern S2W_CID_T s2wCidList[];
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

VOID
AppS2w_RawDataSend(UINT8 cid, UINT8 *buffer,UINT32 httpRxDataLen);

#ifdef 	S2W_GSLINK_SEND_FULL_URI
UINT8 *
App_McuUserURIGet();
#endif
/*******************************************************************************
 *  Private Definitions
 ******************************************************************************/
#if defined(S2W_GSLINK)
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process de initialise the xml and httpd context.
 *   This function deinit the htppd and xml parser context and free the cid
 * @param cid - connectio identifier
 * @param invalidateFlag - falg to invalidate the socket descriptor
 * @return None
 ******************************************************************/
VOID
AppS2w_GslinkDeInit(UINT8 cid,UINT8 invalidateFlag)
{

#ifdef S2W_GSLINK_XML
	GsnXMLStr_ParserCtxDeInit(s2wCidList[cid].xmlParserCtx);
	gsn_free(s2wCidList[cid].xmlParserCtx); 						
	s2wCidList[cid].xmlParserCtx  = NULL;
#endif
	AppS2w_HttpdSemDelete(cid);
	AppS2w_HttpdCtxDeInit(&s2wCidList[cid].httpdCtx);			
	/* If the node is client then no need to invalidate the cid*/
	if(invalidateFlag == 1)
		s2wCidList[cid].sd=CID_NOTINUSE;
	s2wCidList[cid].allocatedTo = 0;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process initialise the xml and http context.
 *   This function initialise the xml parser ,httpd context.
 * @param cid - connectio identifier
 * @return S2W_SUCESS - on suceesful initialisation
 ********************************************************************/
UINT8
AppS2w_GslinkInit(UINT8 cid)
{
	UINT8 status;
	#ifdef S2W_GSLINK_XML	
	  	s2wCidList[cid].xmlParserCtx = gsn_malloc(sizeof(GSNXMLSTR_PARSER_CTX_T));			
	  	if(s2wCidList[cid].xmlParserCtx  == NULL)
	    	 return S2W_FAILURE;
		memset(s2wCidList[cid].xmlParserCtx,0,sizeof(GSNXMLSTR_PARSER_CTX_T));
		  /* init XML Parser Context*/
		GsnXMLStr_ParserCtxInit(s2wCidList[cid].xmlParserCtx);					
	#endif
	status = AppS2w_HttpdCtxInit(&s2wCidList[cid].httpdCtx,0);		
	AppS2w_HttpdSemCreate(cid);	
	return status;
}
#ifdef S2W_GSLINK_XML
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the xml decode call back.
 *   This function encodes the xml data .
 * @param status - status of xml decode operation
 * @param buffer - data buffer
  * @param bufferLen - data buffer length
  * @param context - s2w context.
 * @return None
 ******************************************************************/
PUBLIC VOID
App_XmlParserCb(VOID *cbContext,GSNXMLSTR_CB_PARAM_T *xmlCbparams)
{
	INT8 header[10],headerLen;
	UINT8 websrvrStarted; 
	INT8 delim = ':';
	websrvrStarted = GsnHttpd_IsRunning();
//	if(TRUE == websrvrStarted)
//		GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
	if(xmlCbparams->status == GSN_XML_ATTRIBUTE_PRESENT)
	{
		headerLen=sprintf((char *)header,"%cG%d%04d", S2W_ESC,S2W_XML_ATTRIBUTE_ID,(xmlCbparams->attrNameLen+xmlCbparams->attrvalLen+ 1));
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(header, headerLen);
		AppS2wHal_CharNPut(xmlCbparams->attrNamePtr, xmlCbparams->attrNameLen);					
		AppS2wHal_CharNPut(&delim,1);
		AppS2wHal_CharNPut(xmlCbparams->attrValPtr, xmlCbparams->attrvalLen);			
#else
		AppS2wHal_CharNPut1(header, headerLen);
		AppS2wHal_CharNPut1(xmlCbparams->attrNamePtr, xmlCbparams->attrNameLen);
		AppS2wHal_CharNPut1(&delim,1);
		AppS2wHal_CharNPut1(xmlCbparams->attrValPtr, xmlCbparams->attrvalLen);
#endif
	}
	else if(xmlCbparams->status == GSN_XML_COMPLEX_ELEMENT)
	{
		headerLen=sprintf((char *)header,"%cG%d%04d", S2W_ESC,S2W_XML_COMPLEX_TAG_START_ID,xmlCbparams->tagLen);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(header, headerLen);
		AppS2wHal_CharNPut(xmlCbparams->tagPtr, xmlCbparams->tagLen);
#else
		AppS2wHal_CharNPut1(header, headerLen);
		AppS2wHal_CharNPut1(xmlCbparams->tagPtr, xmlCbparams->tagLen);
#endif
	}
	else if(xmlCbparams->status == GSN_OPERATION_IN_PROGRESS)
	{
		headerLen=sprintf((char *)header,"%cG%04d", S2W_ESC,(xmlCbparams->tagLen+xmlCbparams->valueLen + 1));
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(header, headerLen);
		AppS2wHal_CharNPut(xmlCbparams->tagPtr, xmlCbparams->tagLen);
		AppS2wHal_CharNPut(&delim,1);
		AppS2wHal_CharNPut(xmlCbparams->valuePtr, xmlCbparams->valueLen);	
#else
		AppS2wHal_CharNPut1(header, headerLen);
		AppS2wHal_CharNPut1(xmlCbparams->tagPtr, xmlCbparams->tagLen);
		AppS2wHal_CharNPut1(&delim,1);
		AppS2wHal_CharNPut1(xmlCbparams->valuePtr, xmlCbparams->valueLen);
#endif
	}
	else if(xmlCbparams->status == GSN_XML_COMPLEX_ELEMENT_END)
	{
		headerLen=sprintf((char *)header,"%cG%d", S2W_ESC,S2W_XML_COMPLEX_TAG_END_ID);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(header, headerLen);
#else
		AppS2wHal_CharNPut1(header, headerLen);
#endif
	}
	else if(xmlCbparams->status == GSN_SUCCESS)
	{
		headerLen=sprintf((char *)header,"%cG", S2W_ESC);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		AppS2wHal_CharNPut(header, headerLen);
		S2w_Printf("0000");
#else
		AppS2wHal_CharNPut1(header, headerLen);
		S2w_Printf1("0000");
#endif
		if(TRUE == websrvrStarted)
		{
#ifndef S2W_DUAL_INTERFACE_SUPPORT
			GsnOsal_SemRelease(&s2wSyncSemID);
#else
			GsnOsal_SemRelease(&s2wSyncSemID1);
#endif
        }
	}
	// flush the data for spi-dma interface
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif

}
#endif
#endif
#if defined(S2W_GSLINK) && defined(S2W_WEB_SERVER)
PUBLIC VOID
AppMcu_RespTimeoutCb( VOID* context,GSN_SOFT_TMR_HANDLE_T timerHandle );
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process the sends the uri and other info to host.
 *   This function sends the cid,len,uri and type to host
 * @param cid - connectio identifier
 * @param type - httpd method
  * @param uri -  URI
 * @return None
 ******************************************************************/
VOID
AppMcu_SendUri(UINT8 cid,UINT8 type, const char *uri)
{
	
	UINT32 len=0,headerLen=0;
	UINT8 header[130];
	
	if(s2wappMainTaskCtxt->dpSleep )
    {
		AppS2w_ExitDpSleep();
    }
#ifndef S2W_DUAL_INTERFACE_SUPPORT
	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);	
#else
	GsnOsal_SemAcquire(&s2wSyncSemID1, GSN_OSAL_WAIT_FOREVER);
#endif
	memset(header,0,75);
	len = strlen(uri)+ sizeof(type); 	
	headerLen=sprintf((char *)header,"%cK%x%04d%x%s",S2W_ESC,cid,len,type,uri);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
	AppS2wHal_CharNPut(header, headerLen);
#else
	AppS2wHal_CharNPut1(header, headerLen);
#endif
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
	if ((GSN_HTTP_METHOD_POST == type) && (1 == s2wappMainTaskCtxt ->xmlParseEn ))
	{
		return;
	}
	else
	{
		
#ifndef S2W_DUAL_INTERFACE_SUPPORT
		GsnOsal_SemRelease(&s2wSyncSemID);
#else
		GsnOsal_SemRelease(&s2wSyncSemID1);
#endif
	}

}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @ingroup S2w-Application
 * @brief Process allocate the cid.
 *   This function allocates the cid
 * @param cid - connectio identifier
 * @return validCid if the allocation is successful else S2WS2W_FAILURE 
 ********************************************************************/
UINT8
AppS2w_AllocateCid(ttHttpdUserConHandle conHandle,UINT8 method,const char* uri)
{
	UINT8 validCid=INVALID_CID;
	UINT8 status;
	INT32 sockDesc;
	ttHttpdUserConEntryPtr conEntryPtr;
#ifdef 	S2W_GSLINK_SEND_FULL_URI
	UINT8* compUri;
#endif
#ifdef USE_V6
    UINT8  ipAddr[16];
#else
	unsigned long ipAddr;
#endif
#if 0
	if(GSN_OSAL_RESOURCE_NOT_AVAILABLE == GsnOsal_SemAcquire(&s2wappMainTaskCtxt->gslinkSync, GSN_OSAL_NO_WAIT))
	{
		/* close this new connection here itself to avoid race conditions */
		return INVALID_CID;
	}
#endif
	
	sockDesc = tfHttpdUserGetSockDesc(conHandle);
	validCid = AppS2wHal_CidFind(sockDesc);
	if(validCid == INVALID_CID)
	{
	
		validCid = AppS2wHal_CidGet();	
		if(validCid == INVALID_CID)
			return S2W_FAILURE;
		s2wCidList[validCid].httpflag=1;
		conEntryPtr = tfHttpdUserGetConInfo(conHandle);
#ifdef USE_V6
		memcpy(ipAddr, &(conEntryPtr->uconPeerSockAddr.addr.ipv6.sin6_addr), 16);
		s2wCidList[validCid].remotePort =  (conEntryPtr->uconPeerSockAddr.addr.ipv6.sin6_port);
#else
		ipAddr = (conEntryPtr->uconPeerSockAddr.addr.ipv4.sin_addr.s_addr);
		s2wCidList[validCid].remotePort =  (conEntryPtr->uconPeerSockAddr.addr.ipv4.sin_port);
#endif
#ifdef USE_V6
                memcpy(s2wCidList[validCid].remoteIpv6 ,(UINT8*)&ipAddr,sizeof(s2wCidList[validCid].remoteIpv6));
#else
                memcpy(s2wCidList[validCid].remoteIp ,(UINT8*)&ipAddr,sizeof(s2wCidList[validCid].remoteIp));
#endif
		//memcpy(s2wCidList[validCid].remoteIp ,(UINT8*)&ipAddr,4);
		status = AppS2w_GslinkInit(validCid);
		if(status == S2W_FAILURE)
			return INVALID_CID;		
		s2wCidList[validCid].sd = sockDesc;
		s2wCidList[validCid].allocatedTo = 1;
#ifdef 	S2W_GSLINK_SEND_FULL_URI	
		compUri = App_McuUserURIGet();
		AppMcu_SendUri(validCid,method,(const char *)compUri);
#else
		AppMcu_SendUri(validCid,method,uri);
#endif
	}	
	return validCid;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process wait for data from host.
 *   This function waits for the data from host
 * @param cid - connectio identifier
 * @return None
 ******************************************************************/
VOID
AppMcu_Wait_Data(UINT8 cid)
{
	AppS2w_HttpSemAquire(cid);
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process Send the httpd data.
 *   This function Send the data to remote client
 * @param conHandle - connection handle
 * @param cid - connection identifier
 * @return S2W_FAILURE -send failed
 * @return S2W_SUCCESS -send success
 ******************************************************************/
UINT8
AppS2w_HttpdSendData(ttHttpdUserConHandle conHandle,UINT8 cid)
{
	INT8* buffer;
	UINT8 status,moreData=0;	
	int errorCode;
	if(s2wappMainTaskCtxt->respTimeOut !=0)
	{
		s2wappMainTaskCtxt->respTimeOutTmrHndl = GsnSoftTmr_Start(&s2wappMainTaskCtxt->respTimeOutTmr, GSN_SOFT_TMR_ONESHOT,0, (ULONG64)(s2wappMainTaskCtxt->respTimeOut),
				  ( GSN_SOFT_TMR_CBR_T )AppMcu_RespTimeoutCb, &s2wCidList[cid].sd);
	}

	do
	{
		AppMcu_Wait_Data(cid);
		if(s2wappMainTaskCtxt->respTimeOutTmr.status == GSN_SOFT_TMR_STATUS_EXPIRED)
		{

			GsnHttpd_SendBufferAndLastChunk(conHandle, NULL,
	      	     	0, TM_BLOCKING_ON, &errorCode);
			AppS2w_GslinkDeInit(cid,1);
			return S2W_FAILURE;
		}
#ifdef  S2W_HTTP_CUSTOM_SUPPORT
        if((0 != s2wCidList[cid].httpdCtx.headercount) && (0 != s2wCidList[cid].httpdCtx.statusline))
        {
            /* Send the HTTP response status line */
            tfHttpdUserSendResponseStatusLine (
            conHandle,
            TM_HTTP_VERSION_1_1,
            s2wCidList[cid].httpdCtx.statuscode,
            s2wCidList[cid].httpdCtx.respphrase,
            TM_BLOCKING_OFF);

            /* Send the HTTP response headers */
            tfHttpdUserSendResponseHeaders (
                conHandle,
                &s2wCidList[cid].httpdCtx.headercount,
                s2wCidList[cid].httpdCtx.httphdrtypeptr,
                s2wCidList[cid].httpdCtx.httphdrvalptrptr,
                TM_BLOCKING_OFF | TM_HTTPD_FLUSH
                ,s2wCidList[cid].httpdCtx.httphdrnameptrptr
                );

            tfHttpdUserSetHeaderEndInd(conHandle , 0);
            if(TM_HTTP_METHOD_HEAD == (GsnHttpd_GetHttpMethod(conHandle)))
            {
            	/* no need to send anything after this in case of HEAD method */
            	GsnHttpd_SendLastChunk(conHandle,&errorCode);
            	break;
            }
        }
#endif

		buffer = s2wCidList[cid].httpdCtx.httpdBuffer;
	#ifdef S2W_GSLINK_XML
		if(s2wappMainTaskCtxt->xmlParseEn == 1)
	 	{											
			moreData = s2wCidList[cid].xmlParserCtx->moreData;
		}
		else
	#endif	
		{
			 moreData = s2wCidList[cid].httpdCtx.moreData;
		}
		if(moreData)
		{
			GsnHttpd_SendBuffer(conHandle, buffer,
    	   			(INT32)(s2wCidList[cid].httpdCtx.httpdBufferLenUsed), TM_BLOCKING_ON, &errorCode);
		}
		else
		{
			GsnHttpd_SendBufferAndLastChunk(conHandle, buffer,
	      	      	(INT32)(s2wCidList[cid].httpdCtx.httpdBufferLenUsed), TM_BLOCKING_ON, &errorCode);						
		}
		if(errorCode != TM_ENOERROR)
		{	
			//S2w_Printf("\r\n$$$ errorCode: %d", errorCode);
			s2wappMainTaskCtxt->gsLinkSendStatus = S2W_FAILURE;
			GsnOsal_SemRelease(&s2wCidList[cid].httpdCtx.httpdSendSem);
			AppS2w_GslinkDeInit(cid,1);
			return S2W_FAILURE;
		}
		s2wappMainTaskCtxt->gsLinkSendStatus  = S2W_SUCCESS;	
  		status = AppS2w_HttpdCtxInit(&s2wCidList[cid].httpdCtx,1);
		if(status == S2W_FAILURE)
		{
			//GSN_ASSERT(c)						
		}		
		GsnOsal_SemRelease(&s2wCidList[cid].httpdCtx.httpdSendSem);	
	}while(moreData);
	return S2W_SUCCESS;
}

#ifdef  S2W_HTTP_CUSTOM_SUPPORT
UINT8
AppS2w_HttpPassHdr(ttHttpdUserConEntryPtr conEntryPtr, UINT8 cid)
{
    INT8 header[15],headerLen;
    UINT32  len, hdr, i, bitmap, count;
	UINT8 delim = ':';

    if((INVALID_CID == cid) || (NULL == conEntryPtr))
    {
        return S2W_FAILURE;
    }
    bitmap = s2wappMainTaskCtxt->WebServerCfg.httpdHdrBmap;
    count = 1;
    /* Parse all the headers given by Http server */
    for(i = 1; i < TM_HTTP_HEADER_COUNT ; i++)
    {
         if((NULL != conEntryPtr->uconReqHeaders[i]) && (bitmap & count))
         {
             /* hdr_len should be 2 chars of hdr_type number + hdr_val + 1 char of delim ':' */
             len = strlen(tvHttpHeaderNames[i]) + strlen(conEntryPtr->uconReqHeaders[i]) + 1;
             headerLen = sprintf((char *)header,"%cG%d%d%04d", S2W_ESC, cid, S2W_HTTP_HEADER, len);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
             AppS2wHal_CharNPut(header, headerLen);
             AppS2wHal_CharNPut(tvHttpHeaderNames[i], strlen(tvHttpHeaderNames[i]));
             AppS2wHal_CharNPut(&delim,1);
             AppS2wHal_CharNPut(conEntryPtr->uconReqHeaders[i], strlen(conEntryPtr->uconReqHeaders[i]));
#else
             AppS2wHal_CharNPut1(header, headerLen);
             AppS2wHal_CharNPut1(tvHttpHeaderNames[i], strlen(tvHttpHeaderNames[i]));
             AppS2wHal_CharNPut1(&delim,1);
             AppS2wHal_CharNPut1(conEntryPtr->uconReqHeaders[i], strlen(conEntryPtr->uconReqHeaders[i]));
#endif
         }
         count = (count << 1);
    }
    /* If user has registered for custom headers and custom headers are present, pass it */
    bitmap = bitmap >> 31;
    if((0 != conEntryPtr->uconCustomHdrRecvcount) && (bitmap))
    {
        for(i = 0; i < conEntryPtr->uconCustomHdrRecvcount ; i++)
        {
            len = strlen(conEntryPtr->uconCustomHeaderstype[i]) + strlen(conEntryPtr->uconCustomHeadersval[i] + 1);
            headerLen = sprintf((char *)header,"%cG%d%d%04d", S2W_ESC, cid, S2W_HTTP_HEADER, len);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
            AppS2wHal_CharNPut(header, headerLen);
            AppS2wHal_CharNPut(conEntryPtr->uconCustomHeaderstype[i], strlen(conEntryPtr->uconCustomHeaderstype[i]));
            AppS2wHal_CharNPut(&delim,1);
            AppS2wHal_CharNPut(conEntryPtr->uconCustomHeadersval[i], strlen(conEntryPtr->uconCustomHeadersval[i]));
#else
            AppS2wHal_CharNPut1(header, headerLen);
            AppS2wHal_CharNPut1(conEntryPtr->uconCustomHeaderstype[i], strlen(conEntryPtr->uconCustomHeaderstype[i]));
            AppS2wHal_CharNPut1(&delim,1);
            AppS2wHal_CharNPut1(conEntryPtr->uconCustomHeadersval[i], strlen(conEntryPtr->uconCustomHeadersval[i]));
#endif
        }
        /* set it to 0 again to be further used in sending response*/
        conEntryPtr->uconCustomHdrRecvcount = 0;
    }
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
    return S2W_SUCCESS;
}

UINT8
AppS2w_HttpPassData(ttHttpdUserConHandle conHandle, UINT8 cid)
{
    INT8 header[15],headerLen;
    UINT32  len, i;
    ttHttpdUserConEntryPtr conEntryPtr = NULL;
	UINT8 delim = ':';

    conEntryPtr = tfHttpdUserGetConInfo(conHandle);
    if((INVALID_CID == cid) || (NULL == conEntryPtr))
    {
        return S2W_FAILURE;
    }


    if((1 == s2wappMainTaskCtxt->WebServerCfg.sendReq) && (NULL != conEntryPtr->uconReqMethod))
    {
        /* arg_len should be request uri length + 1 char of method + 1 char of delim ':' */
        len = strlen(conEntryPtr->uconReqPathPtr) + 2;
        headerLen = sprintf((char *)header,"%cG%d%d%04d%d%c", S2W_ESC, cid, S2W_HTTP_REQUEST_LINE, len, conEntryPtr->uconReqMethod, S2W_COLON);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
        AppS2wHal_CharNPut(header, headerLen);
        AppS2wHal_CharNPut(conEntryPtr->uconReqPathPtr, (len - 2));
#else
        AppS2wHal_CharNPut1(header, headerLen);
        AppS2wHal_CharNPut1(conEntryPtr->uconReqPathPtr, (len - 2));
#endif
    }
    if((1 == s2wappMainTaskCtxt->WebServerCfg.sendCgi) && (0 != conEntryPtr->uconCgiArgCnt))
    {
        for(i = 0; i < conEntryPtr->uconCgiArgCnt; i++)
        {
            /* arg_len = length of arg + arg_val + delimiter':' */
            len = strlen(conEntryPtr->uconCgiArgNames[i]) + strlen(conEntryPtr->uconCgiArgValues[i]) + 1;
            headerLen = sprintf((char *)header,"%cG%d%d%04d", S2W_ESC, cid, S2W_HTTP_CGI_PARAMS, len);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
            AppS2wHal_CharNPut(header, headerLen);
            AppS2wHal_CharNPut(conEntryPtr->uconCgiArgNames[i], strlen(conEntryPtr->uconCgiArgNames[i]));
            AppS2wHal_CharNPut(&delim,1);
            AppS2wHal_CharNPut(conEntryPtr->uconCgiArgValues[i], strlen(conEntryPtr->uconCgiArgValues[i]));
#else
            AppS2wHal_CharNPut1(header, headerLen);
            AppS2wHal_CharNPut1(conEntryPtr->uconCgiArgNames[i], strlen(conEntryPtr->uconCgiArgNames[i]));
            AppS2wHal_CharNPut1(&delim,1);
            AppS2wHal_CharNPut1(conEntryPtr->uconCgiArgValues[i], strlen(conEntryPtr->uconCgiArgValues[i]));
#endif
        }
        /* put the end of cgi args list sequence */
        len = 0;
        headerLen = sprintf((char *)header,"%cG%d%d%04d", S2W_ESC, cid, S2W_HTTP_CGI_PARAMS, len);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
        AppS2wHal_CharNPut(header, headerLen);
#else
        AppS2wHal_CharNPut1(header, headerLen);
#endif
    }
    if(0 != s2wappMainTaskCtxt->WebServerCfg.httpdHdrBmap)
    {
        AppS2w_HttpPassHdr(conEntryPtr, cid);
    }
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
    return S2W_SUCCESS;
}
#endif




	
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process GSlink URI handler.
 *   This URI call back.
 * @param event - HTTPD event
 * @param uri - URI
 * @param conHandle - connection handler
 * @return None
 ******************************************************************/
GSN_HTTPD_STATUS_T McuHttpCb(ttHttpdUserEvent event, const char* uri,
        ttHttpdUserConHandle conHandle)
{
    //INT32 respLen,validCid;
    //int errorCode;
    UINT32 bufferLen;
	UINT8 status,cid=INVALID_CID;
	INT8* buffer;
	int sockDesc;
	GSN_STATUS decodeStatus = GSN_SUCCESS;
    //GSNXMLSTR_CB_PARAM_T  xmlDecodeParms;
	UINT32 bufferStartIndex=0;	
    switch (event)
    {
		case TM_HTTPD_EVENT_BODY_RECV:
    	{
		    cid = AppS2w_AllocateCid(conHandle,TM_HTTP_METHOD_POST,uri);   			
			if(cid == INVALID_CID)
				return GSN_HTTPD_FAILURE;			 		    
			buffer = s2wCidList[cid].httpdCtx.httpdBuffer;
			bufferLen = TM_BODY_BUFFER_LEN;
#ifdef S2W_HTTP_CUSTOM_SUPPORT
            /* Send headers only for the first time */
            if(0 == s2wCidList[cid].httpdCtx.httpdHdrsSent)
            {
                AppS2w_HttpPassData(conHandle, cid);
                s2wCidList[cid].httpdCtx.httpdHdrsSent = 1;
            }
#endif
			do
			{	
#ifdef S2W_GSLINK_XML
				if(s2wappMainTaskCtxt->xmlParseEn == 1)
				{
					bufferStartIndex = (s2wCidList[cid].xmlParserCtx->bytesTodecode);
					bufferLen = TM_BODY_BUFFER_LEN - bufferStartIndex;
				}
#endif				
	            tfHttpdUserGetRequestBody(conHandle, (buffer + bufferStartIndex ),
                    (ttUserIntPtr) &(bufferLen), 0/*  TM_HTTPD_NO_COPY*/);				
				if (bufferLen )
				{
#ifdef S2W_GSLINK_XML
					if(s2wappMainTaskCtxt->xmlParseEn == 1)
					{
						bufferLen = bufferLen + bufferStartIndex;
						decodeStatus = GsnXMLStr_Decode(s2wCidList[cid].xmlParserCtx,(UINT8 *)buffer,bufferLen,App_XmlParserCb,s2wappMainTaskCtxt);
						if(decodeStatus == GSN_XML_PARTIAL_ELEMENT)
						{
							bufferStartIndex  = s2wCidList[cid].xmlParserCtx->bytesTodecode;
						}
						else if((decodeStatus == GSN_INVALID_PARAM) || (decodeStatus == GSN_FAILURE))
						{				
#ifdef S2W_ASYNC_MSG
						    if(s2wCurrent.asyncMsgFormat)
				   		    {
					   		    AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_ECIDCLOSE, cid);
				   		    }
				   		    else
#endif
                		    {
		                        AppS2wProcess_StatusNotify(S2W_ECIDCLOSE, cid);
        		            }
							AppS2w_GslinkDeInit(cid,1);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
							GsnOsal_SemRelease(&s2wSyncSemID);
#else
                            GsnOsal_SemRelease(&s2wSyncSemID1);
#endif
						}
					}
#endif
			#ifdef S2W_GSLINK_RAW		
					if(s2wappMainTaskCtxt->xmlParseEn == 0)					
						AppS2w_RawDataSend(cid,(UINT8*)buffer,bufferLen);
			#endif
           			 HTTPD_DEBUG_PRINT((
                    "[soc-mcu-http] Got MCU state POST/PUT (SET)\r\n"));			
				}
			}while(bufferLen);											
        	break;
   		}
	    //case TM_HTTPD_EVENT_SEND_READY:
		case TM_HTTPD_EVENT_SEND_USER_DATA:
		{
			if (GsnHttpd_GetHttpMethod(conHandle) ==  TM_HTTP_METHOD_GET)
        	{
        		cid = AppS2w_AllocateCid(conHandle,TM_HTTP_METHOD_GET,uri); 		
				if(cid == INVALID_CID)
					return GSN_HTTPD_FAILURE;
	    		HTTPD_DEBUG_PRINT((
                  "[soc-mcu-http] Got MCU state GET \r\n" ));
#ifdef S2W_HTTP_CUSTOM_SUPPORT
                if(0 == s2wCidList[cid].httpdCtx.httpdHdrsSent)
                {
                    AppS2w_HttpPassData(conHandle, cid);
                    s2wCidList[cid].httpdCtx.httpdHdrsSent = 1;
                }
#endif
				status = AppS2w_HttpdSendData(conHandle,cid);
				if(status == S2W_FAILURE)
					return GSN_HTTPD_FAILURE;
		    }
	        else
    	    {
    	    	sockDesc= tfHttpdUserGetSockDesc(conHandle);	
				cid = AppS2wHal_CidFind(sockDesc);				
				if(cid == INVALID_CID)
					return GSN_HTTPD_FAILURE;
#ifdef S2W_GSLINK_RAW	
			  	if(s2wappMainTaskCtxt->xmlParseEn == 0)		
			  	{
					AppS2w_RawDataSend(cid,NULL,0);
			  	}
#endif		
		  		status = AppS2w_HttpdSendData(conHandle,cid);
				if(status == S2W_FAILURE)
					return GSN_HTTPD_FAILURE;
	        }
			AppS2w_GslinkDeInit(cid,1);
		    break;
	    }
		case TM_HTTPD_EVENT_CON_CLOSE:
		{			
			sockDesc= tfHttpdUserGetSockDesc(conHandle);				
			cid = AppS2wHal_CidFind(sockDesc);				
			if(cid != INVALID_CID)
			{
				if(GsnHttpd_GetHttpMethod(conHandle) ==TM_HTTP_METHOD_POST && 
					s2wCidList[cid].xmlParserCtx->moreData == 1 )
					GsnOsal_SemRelease(&s2wSyncSemID);
				AppS2w_GslinkDeInit(cid,1);
			}
			break;
		}
		 case TM_HTTPD_EVENT_ALL_RECV:
		 {
			sockDesc= tfHttpdUserGetSockDesc(conHandle);	
			cid = AppS2wHal_CidFind(sockDesc);
			if(cid != INVALID_CID)
			{
#ifdef S2W_GSLINK_XML			
				if(s2wCidList[cid].xmlParserCtx->moreData == 1 &&  (s2wappMainTaskCtxt->xmlParseEn == 1))
				{
           #ifdef S2W_ASYNC_MSG
					if(s2wCurrent.asyncMsgFormat)
				    {
					   	AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_ECIDCLOSE, cid);
				   	}
				   	else
           #endif
                	{
		                AppS2wProcess_StatusNotify(S2W_ECIDCLOSE, cid);
        		    }
					AppS2w_GslinkDeInit(cid,1);
				}
#endif				
			}
#ifdef S2W_HTTP_CUSTOM_SUPPORT
			else if(GsnHttpd_GetHttpMethod(conHandle) ==  TM_HTTP_METHOD_HEAD)
			{
			    cid = AppS2w_AllocateCid(conHandle,TM_HTTP_METHOD_HEAD,uri);
				if(cid == INVALID_CID)
					return GSN_HTTPD_FAILURE;
				buffer = s2wCidList[cid].httpdCtx.httpdBuffer;
				bufferLen = TM_BODY_BUFFER_LEN;
	            /* Send headers only for the first time */
	            if(0 == s2wCidList[cid].httpdCtx.httpdHdrsSent)
	            {
	                AppS2w_HttpPassData(conHandle, cid);
	                s2wCidList[cid].httpdCtx.httpdHdrsSent = 1;
	            }
				status = AppS2w_HttpdSendData(conHandle,cid);
				if(status == S2W_FAILURE)
					return GSN_HTTPD_FAILURE;
				AppS2w_GslinkDeInit(cid,1);
				tfHttpdUserClose(conHandle, TM_ENOERROR);
			}
#endif
			break;
		}
    }	
	return GSN_HTTPD_SUCCESS;
}
/*******************************************************************************
 *  Public Functions
 ******************************************************************************/

PUBLIC GSN_HTTPD_STATUS_T
App_McuHttpApiInit()
{
	GSN_HTTPD_STATUS_T status;
	if(TRUE == GsnHttpd_IsRunning())
	{
		status = GsnHttpd_UriHandlerConfig((char *)s2wappMainTaskCtxt->currenturi,0, NULL,NULL, 0);		
	}

    /*status = GsnHttpd_UriHandlerConfig((char *)APP_MCU_PROFILE_URI,
            GSN_HTTPD_URI_METHOD_GET_POST, APP_MCU_PROFILE_DESC,
            McuHttpCb, GSN_HTTPD_CONTENT_APP_XML);*/
    status = GsnHttpd_UriHandlerConfig((char *)S2W_DFLT_HTTP_SRVR_URI,
    		GSN_HTTPD_URI_METHOD_GET_POST_PUT_DEL, APP_MCU_PROFILE_DESC,
            McuHttpCb, S2W_DFLT_HTTP_SRVR_CONTENT_TYPE);
	memset(s2wappMainTaskCtxt->currenturi,0,GSN_HTTPD_MAX_URI_LENGTH);	
	memcpy(s2wappMainTaskCtxt->currenturi,S2W_DFLT_HTTP_SRVR_URI,strlen(S2W_DFLT_HTTP_SRVR_URI)  );
#if 0
	GsnOsal_SemCreate(&s2wappMainTaskCtxt->gslinkSync, 1);
#endif
	return status;
}
PUBLIC VOID
AppMcu_RespTimeoutCb( VOID* context,GSN_SOFT_TMR_HANDLE_T timerHandle )
{
	INT32 *sd;
	UINT8 validCid ;
	sd = 	(INT32 *)(context);
	validCid = AppS2wHal_CidFind(*sd);
	if(validCid != INVALID_CID)
	{
		AppS2w_HttpSemRelease(validCid);
		
	}
}
#endif
#ifdef S2W_WEB_SERVER

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process sets the timeout for the socket.
 *   This function allocates the cid
 * @param cid - connectio identifier
 * @param timeOut - Timeout value
 * @return S2W_SUCCESS if timeout value is set else S2W_FAILURE
 ********************************************************************/
PUBLIC UINT8
AppS2w_HttpdSetTimeOut(UINT8 cid,UINT32 timeOut)
{
	INT32 sockDesc,errorCode/*,optValue*/;
	sockDesc = s2wCidList[cid].sd;
	errorCode = setsockopt( sockDesc,
                                IP_PROTOTCP,
                                TCP_MAXRT,
                                (const char TM_FAR *)&timeOut,
                                sizeof(INT32) );	
	if(errorCode != TM_ENOERROR)
		return S2W_FAILURE;
	return S2W_SUCCESS;
}
VOID
App_McuHttpApiDeInit()
{
	if(TRUE == GsnHttpd_IsRunning())
	{
		GsnHttpd_UriHandlerConfig((char *)s2wappMainTaskCtxt->currenturi,0, NULL,NULL, 0); 	
		memset(s2wappMainTaskCtxt->currenturi,0,GSN_HTTPD_MAX_URI_LENGTH);
		s2wappMainTaskCtxt->webServerStatus = IDLE;
	}
}
#ifdef 	S2W_GSLINK_SEND_FULL_URI
extern char UrlBuf[128];
UINT8 *
App_McuUserURIGet()
{
	return (UINT8 *)UrlBuf;
}
#endif
#endif
