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
* $RCSfile: gsn_xml.h,v $
*
* Description : This file contains XML API.
*******************************************************************************/

#ifndef _GSN_XML_H_
#define _GSN_XML_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* File Inclusion
********************************************************************************/

#include "gsn_error.h"
#include "gsn_types.h"
#include "gsn_defines.h"

/**
 *******************************************************************************
 * @file gsn_xml.h
 * @brief GSN XML public header.
 *    This file contains the public APIs and structures of XML module.
 ******************************************************************************/


 /**
  *****************************************************************************
  * @ingroup syssvcdoc
  *
  * @{
  *****************************************************************************/


 /**
  *******************************************************************************
  * @defgroup GsnXml GSN XML API
  *
  ******************************************************************************/

 /**
  *****************************************************************************
  *
  * @}     END of Modules group include
 *****************************************************************************/

 /*******************************************************************************
   * Private Macros and Functions
  ******************************************************************************/

//This buffer is used in the decoder routine, to hold the local conversions of the decoded value
#define Local_Decoder_Buffer  128


/*******************************************************************************
  * Type Definitions
  ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml node structure.
 *******************************************************************************/

typedef struct GSN_XML_NODE
{
    /**< Name of the tag */
    UINT8 *pName;
    /**<Starting address of tag info in XML file */
    UINT8 *pStart;
    /**<End address of tag info in XML file */
    UINT8 *pEnd;
}GSN_XML_NODE_T;


/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml data type enum.
 *******************************************************************************/
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


/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml date structure.
 *******************************************************************************/
typedef struct GSN_XML_DATE
{
    UINT16 year;
    UINT8  month;
    UINT8  day;
    UINT8  hrOffset;
    UINT8  minOffset;
}GSN_XML_DATE_T;

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml time structure.
 *******************************************************************************/
typedef struct GSN_XML_TIME
{
    UINT8  hr;
    UINT8  min;
    UINT8  sec;
    UINT8  hrOffset;
    UINT8  minOffset;
}GSN_XML_TIME_T;

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml date and time structure.
 *******************************************************************************/
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

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml duration structure.
 *******************************************************************************/
typedef struct GSN_XML_DURATION
{
    UINT16 year;
    UINT8  month;
    UINT8  day;
    UINT8  hr;
    UINT8  min;
    UINT8  sec;
}GSN_XML_DURATION_T;


/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml string structure.
 *******************************************************************************/
typedef struct GSN_XML_STRING
{
    /**< Stores the type */
    UINT8   type;
    /**< Stores the length wihtout '/0' */
    UINT16  len;
     /**< Stores the pointer. This will not have '/0' at the end of the string */
    UINT8   *ptr;
}GSN_XML_STRING_T;

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml object type enum.
 *******************************************************************************/
typedef enum GSN_XML_OBJ_TYPE
{
    XML_COMPLEX_ELEMENT,
    XML_SIMPLE_ELEMENT,
    XML_ATTRIBUTE,
    XML_NONE
}GSN_XML_OBJ_TYPE_T;


/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml simple object structure.
 *******************************************************************************/
typedef struct GSN_XML_OBJ
{
    /**< Name of the object with '/0' termination */
    UINT8         *pName;
    /**< Object type */
    GSN_XML_OBJ_TYPE_T   objType;
    /**< Data type */
    GSN_XML_DATA_TYPE_T dataType;
    /**< Maximum occurence of the object */
    UINT8         maxObjOcc;
    /**< Offset of the object from the starting address of its parent structure */
    UINT16        offset;
}GSN_XML_OBJ_T;

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml complex info structure.
 *******************************************************************************/
typedef struct GSN_XML_COMPLEX_INFO
{
    /**< Maximum numbner of objects the complex element has */
    UINT8      maxNumOfObj;
    /**< Structure size of the complex element */
    UINT16     size;
    /**< Pointer to the child elements it contains */
    const GSN_XML_OBJ_T  *pObj[20];
}GSN_XML_COMPLEX_INFO_T;

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Xml complex structure.
 *******************************************************************************/

typedef struct GSN_XML_COMPLEX_OBJ
{
    GSN_XML_OBJ_T        obj;
    GSN_XML_COMPLEX_INFO_T  complexobj;
}GSN_XML_COMPLEX_OBJ_T;




/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Encode API for XML module.
 *
 *    This function create the xml file from the data structure and the xml
 * schema.
 * @param XML_Schema  - IN Xml schema.
 * @param User_Struct - IN The user structure which holds all data to be encoded.
 * @param XML_File_Buffer - IN The user buffer which will be filled with the xml
 * file.
 * @param XML_File_Buffer_Size - IN Total Size of the user buffer.
 * @param Len_Of_XML_Written - IN Size of the user buffer filled with xml file.
 *
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *      None
 *******************************************************************************/

GSN_STATUS_T GsnXml_Encode(GSN_XML_COMPLEX_OBJ_T *XML_Schema,
    UINT8 *User_Struct, UINT8 *XML_File_Buffer,
    UINT32 XML_File_Buffer_Size, UINT32 *Len_Of_XML_Written);

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Decode API for XML module.
 *
 *    This function decode the xml file,extract the data and fill that on user
 * structure.
 * @param ParentStart - IN The starting address of the xml file.
 * @param ParentEnd - IN The Ending address of the xml file.
 * @param XML_Schema - IN Xml schema.
 * @param Return_Struct - IN The user structure buffer to be filled with the data.
 *
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *    None.
 *******************************************************************************/

GSN_STATUS_T GsnXml_Decode(UINT8 *ParentStart, UINT8* ParentEnd,
    GSN_XML_COMPLEX_OBJ_T *XML_Schema, UINT8 *Return_Struct);

/**
 *******************************************************************************
 * @ingroup GsnXml
 * @brief Node get API.
 *
 *    This function gets the node information from the xml file. It fills the
 * pCNode if it finds the tag. The tag name is taken from the pName element in
 * the pCNode.
 *
 * @param ChildNode - IN/OUT Child node structure pointer.
 * @param ParentNodeStart - IN The starting address of the xml file.
 * @param ParentNodeEnd - IN The Ending address of the xml file.
 *
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Operation failed.
 * @note
 *    None.
 *******************************************************************************/
 GSN_STATUS_T GsnXml_NodeGet( GSN_XML_NODE_T *ChildNode, UINT8 *ParentNodeStart,
                              UINT8 *ParentNodeEnd );

 UINT8* GsnXml_StrGet( UINT8 *ChildNodepName, UINT8 *ParentNodeStart,
                        UINT8 *ParentNodeEnd );

UINT8
GsnXml_DecodePreDefEntity(UINT8 * bufferIn,UINT8 len);

UINT16
GsnXml_GetEncodedValueLen(UINT8 * bufferIn,UINT16 len);


#ifdef __cplusplus
}
#endif
#endif /* _GSN_XML_H_ */
