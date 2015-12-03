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
* $RCSfile: gsn_api_xml_schema.c,v
*/

/*
 * gsn_api_xml_schema.c
 *
 *  Created on: Jun 3, 2011
 *      Author: PViswanathan
 */

#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"

typedef struct http_api_elem
{
    GSN_XML_STRING_T uri;
    GSN_XML_STRING_T methods;
    GSN_XML_STRING_T desc;
} http_api_elem_xml_t;

typedef struct http_api_xml
{
    http_api_elem_xml_t     http_api_elem;
} http_api_xml_t;

//                      *pName      objType                 dataType        maxObjOcc   offset
const GSN_XML_OBJ_T uri   = {"uri",   XML_SIMPLE_ELEMENT,     XML_DT_STR,     1,          offsetof(http_api_elem_xml_t, uri)};
const GSN_XML_OBJ_T methods = {"methods",     XML_SIMPLE_ELEMENT,     XML_DT_STR,     1,          offsetof(http_api_elem_xml_t, methods)};
const GSN_XML_OBJ_T desc = {"description",    XML_SIMPLE_ELEMENT,     XML_DT_STR, 1,          offsetof(http_api_elem_xml_t, desc)};

//                                  *pName          objType                 dataType        maxObjOcc   offset  maxNumOfObj size                *pObj[]
const GSN_XML_COMPLEX_OBJ_T Http_Api_Schema_Start = {"http_api",          XML_COMPLEX_ELEMENT,    XML_DT_NONE,    1,          0,      {3,         sizeof(http_api_xml_t), {&uri, &methods, &desc} }};


