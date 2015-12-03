#include "modules/xml_parser/test/modules/gsn_xml.h"

typedef GSN_STATUS
(*GsnXml_Decode_FP_T )(UINT8 * ParentStart,UINT8 * ParentEnd,GSN_XML_COMPLEX_OBJ_T * XML_Schema,UINT8 * Return_Struct);

typedef UINT8
(*GsnXml_DecodePreDefEntity_FP_T)(UINT8 * bufferIn,UINT8 len);

typedef GSN_STATUS_T
(*GsnXml_NodeGet_FP_T)(GSN_XML_NODE_T * ChildNode,UINT8 * ParentNodeStart,UINT8 * ParentNodeEnd);

typedef UINT8 *
(*GsnXml_StrGet_FP_T )(UINT8 * ChildNodepName,UINT8 * ParentNodeStart,UINT8 * ParentNodeEnd);

extern _RPST_ GsnXml_Decode_FP_T GsnXml_Decode_FP;
extern _RPST_ GsnXml_DecodePreDefEntity_FP_T GsnXml_DecodePreDefEntity_FP ;
extern _RPST_ GsnXml_NodeGet_FP_T GsnXml_NodeGet_FP  ; 
extern _RPST_ GsnXml_StrGet_FP_T GsnXml_StrGet_FP ;


