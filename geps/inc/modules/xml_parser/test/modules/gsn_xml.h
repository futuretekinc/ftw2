/*******************************************************************************
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
* Description : This file contains XML API.
*******************************************************************************/

#ifndef _GSN_XML_H_
#define _GSN_XML_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "gsn_error.h"
#include "gsn_types.h"
#include "gsn_defines.h"


#define Local_Decoder_Buffer  128


typedef struct GSN_XML_NODE
{
    /**< Name of the tag */
    UINT8 *pName;
    /**<Starting address of tag info in XML file */
    UINT8 *pStart;
    /**<End address of tag info in XML file */
    UINT8 *pEnd;
}GSN_XML_NODE_T;


typedef enum GSN_XML_DATA_TYPE
{
   XML_DT_NONE,
   XML_DT_UINT8,
   XML_DT_INT8,
   XML_DT_UINT16,
   XML_DT_INT16,
   XML_DT_UINT32,
   XML_DT_INT32,
   XML_DT_UINT64,
   XML_DT_INT64,
   XML_DT_FLOAT,
   XML_DT_DOUBLE,
   XML_DT_STR,
   XML_DT_TOKEN,
   XML_DT_BASE64BIN,
   XML_DT_HEXBIN,
   XML_DT_DATE,
   XML_DT_TIME,
   XML_DT_DATE_TIME,
   XML_DT_DURATION
}GSN_XML_DATA_TYPE_T;

typedef struct GSN_XML_DATE
{
    UINT16 year;
    UINT8  month;
    UINT8  day;
    UINT8  hrOffset;
    UINT8  minOffset;
}GSN_XML_DATE_T;


typedef struct GSN_XML_TIME
{
    UINT8  hr;
    UINT8  min;
    UINT8  sec;
    UINT8  hrOffset;
    UINT8  minOffset;
}GSN_XML_TIME_T;

typedef struct GSN_XML_DATE_TIME
{
    UINT16 year;
    UINT8  month;
    UINT8  day;
    UINT8  hr;
    UINT8  min;
    UINT8  sec;
    UINT8  hrOffset;
    UINT8  minOffset;
}GSN_XML_DATE_TIME_T;

typedef struct GSN_XML_DURATION
{
    UINT16 year;
    UINT8  month;
    UINT8  day;
    UINT8  hr;
    UINT8  min;
    UINT8  sec;
}GSN_XML_DURATION_T;


typedef struct GSN_XML_STRING
{

    UINT8   type;

    UINT16  len;

    UINT8   *ptr;
}GSN_XML_STRING_T;


typedef enum GSN_XML_OBJ_TYPE
{
    XML_COMPLEX_ELEMENT,
    XML_SIMPLE_ELEMENT,
    XML_ATTRIBUTE,
    XML_NONE
}GSN_XML_OBJ_TYPE_T;


typedef struct GSN_XML_OBJ
{

    UINT8         *pName;

    GSN_XML_OBJ_TYPE_T   objType;

    GSN_XML_DATA_TYPE_T dataType;

    UINT8         maxObjOcc;

    UINT16        offset;
}GSN_XML_OBJ_T;

typedef struct GSN_XML_COMPLEX_INFO
{

    UINT8      maxNumOfObj;

    UINT16     size;

    const GSN_XML_OBJ_T  *pObj[20];
}GSN_XML_COMPLEX_INFO_T;

typedef struct GSN_XML_COMPLEX_OBJ
{
    GSN_XML_OBJ_T        obj;
    GSN_XML_COMPLEX_INFO_T  complexobj;
}GSN_XML_COMPLEX_OBJ_T;




GSN_STATUS_T GsnXml_Encode(GSN_XML_COMPLEX_OBJ_T *XML_Schema,
                           UINT8 *User_Struct, UINT8 *XML_File_Buffer,
                           UINT32 XML_File_Buffer_Size, UINT32 *Len_Of_XML_Written);



GSN_STATUS_T GsnXml_Decode(UINT8 *ParentStart, UINT8* ParentEnd,
                           GSN_XML_COMPLEX_OBJ_T *XML_Schema, UINT8 *Return_Struct);

GSN_STATUS_T
GsnXml_NodeGet( GSN_XML_NODE_T *pCNode, UINT8 *pPNStart, UINT8 *pPNEnd,
    UINT8 *pTagEnd );
UINT8
GsnXml_NodeOccGet( UINT8 *pTName, UINT8 *pPNStart, UINT8 *pPNEnd );
void TestEncoder(void);

void TestDecoder(void);


#ifdef __cplusplus
}
#endif
#endif
