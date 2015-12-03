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
* $RCSfile: gsn_prov_xml_schema.c,v
*/

/*
 * gsn_prov_xml_schema.c
 *
 *  Created on: Jun 3, 2011
 *      Author: PViswanathan
 */
#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"
typedef struct scan_params_elem_xml
{
    UINT32 scan_channel;
    GSN_XML_STRING_T ssid_filter;
    UINT32 scan_time;
    UINT32 scan_delay;
} scan_params_elem_xml_t;

typedef struct scan_parmas_xml
{
    scan_params_elem_xml_t        scan_elem;
} scan_params_xml_t;

//                        *pName        objType                    dataType        maxObjOcc    offset
const GSN_XML_OBJ_T scan_channel = {"channel",        XML_SIMPLE_ELEMENT,    XML_DT_UINT32, 1, offsetof(scan_params_xml_t, scan_elem.scan_channel)};
const GSN_XML_OBJ_T ssid_filter = {"ssid_filter",    XML_SIMPLE_ELEMENT,    XML_DT_STR,    1, offsetof(scan_params_xml_t, scan_elem.ssid_filter)};
const GSN_XML_OBJ_T scan_time    = {"scan_time",    XML_SIMPLE_ELEMENT,    XML_DT_UINT32, 1, offsetof(scan_params_xml_t, scan_elem.scan_time)};
const GSN_XML_OBJ_T scan_delay    = {"scan_delay",    XML_SIMPLE_ELEMENT,    XML_DT_UINT32, 1, offsetof(scan_params_xml_t, scan_elem.scan_delay)};

//                                    *pName            objType                    dataType        maxObjOcc    offset    maxNumOfObj    size                *pObj[]
const GSN_XML_COMPLEX_OBJ_T Scan_Params_Schema_Start = {"scan_params", XML_COMPLEX_ELEMENT, XML_DT_NONE, 1, 0, {4, sizeof(scan_params_xml_t),    {&scan_channel, &ssid_filter, &scan_time, &scan_delay} }};


typedef struct wps_elem_xml
{
    GSN_XML_STRING_T enabled;
    GSN_XML_STRING_T mode;
    GSN_XML_STRING_T pin;
} wps_elem_xml_t;

typedef struct wps_xml
{
    wps_elem_xml_t        wps_elem;
}wps_xml_t;

//                        *pName        objType                    dataType        maxObjOcc    offset
const GSN_XML_OBJ_T wps_enabled = {"enabled",        XML_SIMPLE_ELEMENT,    XML_DT_STR, 1, offsetof(wps_xml_t, wps_elem.enabled)};
const GSN_XML_OBJ_T wps_mode = {"mode",    XML_SIMPLE_ELEMENT,    XML_DT_STR,    1, offsetof(wps_xml_t, wps_elem.mode)};
const GSN_XML_OBJ_T wps_pin    = {"pin",    XML_SIMPLE_ELEMENT,    XML_DT_STR, 1, offsetof(wps_xml_t, wps_elem.pin)};

//                                    *pName            objType                    dataType        maxObjOcc    offset    maxNumOfObj    size                *pObj[]
const GSN_XML_COMPLEX_OBJ_T Wps_Schema_Start = {"wps", XML_COMPLEX_ELEMENT, XML_DT_NONE, 1, 0, {3, sizeof(wps_xml_t),    {&wps_enabled, &wps_mode, &wps_pin} }};



typedef struct ap_complex
{
    UINT32            index;
    GSN_XML_STRING_T    ssid;
    INT32            rssi;
    GSN_XML_STRING_T    nw_type;
    GSN_XML_STRING_T    security;
#ifdef GS1550M
    GSN_XML_STRING_T    band;
#endif
    UINT32            channel;
}ap_complex;

typedef struct ap_list_t
{
    ap_complex        app;
}ap_list_t;

//                        *pName        objType                    dataType        maxObjOcc    offset
const GSN_XML_OBJ_T aindex    = {"index",    XML_SIMPLE_ELEMENT,        XML_DT_UINT32,    1,            offsetof(ap_complex, index)};
const GSN_XML_OBJ_T ssid        = {"ssid",        XML_SIMPLE_ELEMENT,        XML_DT_STR,        1,            offsetof(ap_complex, ssid)};
const GSN_XML_OBJ_T rssi        = {"rssi",        XML_SIMPLE_ELEMENT,        XML_DT_INT32,    1,            offsetof(ap_complex, rssi)};
const GSN_XML_OBJ_T nw_type    = {"nw_type",    XML_SIMPLE_ELEMENT,        XML_DT_STR,        1,            offsetof(ap_complex, nw_type)};
const GSN_XML_OBJ_T security    = {"security",    XML_SIMPLE_ELEMENT,        XML_DT_STR,        1,            offsetof(ap_complex, security)};
#ifdef GS1550M
const GSN_XML_OBJ_T band    = {"band",    XML_SIMPLE_ELEMENT,        XML_DT_STR,        1,            offsetof(ap_complex, band)};
#endif
const GSN_XML_OBJ_T channel    = {"channel",    XML_SIMPLE_ELEMENT,        XML_DT_UINT32,    1,            offsetof(ap_complex, channel)};

//                                    *pName            objType                    dataType        maxObjOcc    offset    maxNumOfObj    size                *pObj[]
#ifdef GS1550M
const GSN_XML_COMPLEX_OBJ_T Schema_Start_1    = {"ap",            XML_COMPLEX_ELEMENT,    XML_DT_NONE,    1,            0,        {7,            sizeof(ap_list_t),    {&aindex, &ssid, &rssi, &nw_type, &security, &band, &channel} }};
#else
const GSN_XML_COMPLEX_OBJ_T Schema_Start_1    = {"ap",            XML_COMPLEX_ELEMENT,    XML_DT_NONE,    1,            0,        {6,            sizeof(ap_list_t),    {&aindex, &ssid, &rssi, &nw_type, &security, &channel} }};
#endif
//xml_obj_complex_t Schema_Start_1    = {"ap_list",        XML_COMPLEX_ELEMENT,    XML_DT_NONE,    1,            0,        {0,            sizeof(ap_list_t),    {&ap_complex1} }};


