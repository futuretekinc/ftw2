/******************************************************************************
*
*               COPYRIGHT (c) 2011-2012 GainSpan Corporation
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
*
* $RCSfile: gsn_xml_string_parser.h,v $
*
* Description : This file contains general definitions for XML string Parser.
*****************************************************************************/

#ifndef _GSN_XML_STRING_PARSER_H_
#define _GSN_XML_STRING_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* File Inclusion
********************************************************************************/
#include "gsn_error.h"
#include "gsn_types.h"
#include "gsn_defines.h"


/** Escape character. */
#define XML_TAG_DELIM  ':'		/*Delimitter character used for XML string Encode*/
#define XML_PRAM_NOTFOUND  -1
#define XML_SPLLEN_COMPLEX_TAG_START  9998
#define XML_SPLLEN_COMPLEX_TAG_END	   9997
#define XML_SPLLEN_ATTRIBUTE		   9996
#define XML_SPLLEN_ELEMENT_END		   0	
#define GSNXMLSTR_MAX_NESTED_ELMENTS   10

typedef VOID ( *GSN_XML_STRING_DECODE_CB ) ( ); //UINT8*buf,UINT32 len
typedef enum GSN_XML_SPARSER_STATE
{
    XML_DECODE_ROOT_ELEMENT=0,
    XML_DECODE_SIMPLE_ELEMENT
}GSN_XML_SPARSER_STATE_T;
typedef enum GSN_XML_SPARSER_SUBSTATE
{
    XML_DECODE_TAG=0,
    XML_DECODE_ATTRIBUTE,
    XML_DECODE_VALUE
}GSN_XML_SPARSER_SUBSTATE_T;
typedef struct GSNXMLSTR_CB_PARAM
{
	UINT32 tagLen; 			
	UINT32 attrNameLen; 			
	UINT32 attrvalLen; 			
	UINT32 valueLen;			
	UINT8  *tagPtr;		
	UINT8  *attrNamePtr;
	UINT8  *attrValPtr;	
	UINT8  *valuePtr;
	GSN_STATUS status; 
}  GSNXMLSTR_CB_PARAM_T;
typedef struct GSNXMLSTR_TAG_TBL
{
	INT8 *tagPtr;
	UINT32 tagLen;
}GSNXMLSTR_TAG_TBL_T;
typedef struct GSNXMLSTR_PARSER_CTX
{
	INT8 *attrPtr;
	UINT8 validchars;
	UINT32 xmlBufRdPtr; 			
	UINT32 encodedTagCount;
	UINT32 noOfTags;
	UINT32 status;
	UINT32 moreData;
	UINT32 buffStartIndex;	
	UINT32 tempBufRdPtr;		
	UINT32 tagTblCopiedIndex;			
	INT32 bytesTodecode;
	UINT32 attrLen;
	UINT32 nestedElmIndex;
	UINT8 profName[32];		
	GSNXMLSTR_TAG_TBL_T tagTbl[GSNXMLSTR_MAX_NESTED_ELMENTS];
	GSN_XML_SPARSER_STATE_T XmlparserState;
	GSN_XML_SPARSER_SUBSTATE_T XmlparserSubState;
}  GSNXMLSTR_PARSER_CTX_T;

typedef VOID ( *XML_PARSER_CB ) (void * ,GSNXMLSTR_CB_PARAM_T * );

PUBLIC INT32
GsnXMLStr_NextParamGet(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * temp,UINT8 delim,UINT32 len);


PUBLIC UINT32
GsnXMLStr_GetEncodedValueLen(UINT8 * bufferIn,UINT32 len);

PUBLIC UINT32
GsnXMLStr_EncodePreDefEntity(UINT8 *bufferIn,UINT32 len,INT8 *outBuffer);
PUBLIC GSN_STATUS
GsnXMLStr_Encode(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * inBuffer,UINT32 len,UINT32 elementType,
							INT8 * * outBuffer,UINT32 bufferStartIndex,UINT32 * outLen);

PUBLIC UINT32
GsnXMLStr_DecodePreDefEntity(UINT8 *bufferIn,UINT32 len);

PUBLIC VOID
GsnXMLStr_ParserCtxInit(GSNXMLSTR_PARSER_CTX_T *xmlParserCtx);

PUBLIC VOID
GsnXMLStr_SetTagCount(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT32 totalTagCount);

PUBLIC VOID
GsnXMLStr_SetRootTag( GSNXMLSTR_PARSER_CTX_T *xmlParserCtx,UINT8* rootTag);

PUBLIC VOID
GsnXMLStr_ParserCtxDeInit( GSNXMLSTR_PARSER_CTX_T *xmlParserCtx);

PUBLIC GSN_STATUS
GsnXMLStr_Decode(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * bufferIn,UINT32 len,
						XML_PARSER_CB XmlParserCb,VOID *cbContext);


#endif


