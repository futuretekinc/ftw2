#include "modules/xml_string_parser/gsn_xml_string_parser.h"

typedef GSN_STATUS
(*GsnXMLStr_AttributeDecode_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx, \
									GSNXMLSTR_CB_PARAM_T * xmlParserCbParam,UINT32 len);
extern _RPST_ GsnXMLStr_AttributeDecode_FP_T GsnXMLStr_AttributeDecode_FP ;

typedef GSN_STATUS
(*GsnXMLStr_Decode_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * bufferIn,\
						 UINT32 len,XML_PARSER_CB XmlParserCb,void * cbContext);
typedef UINT32
(*GsnXMLStr_DecodePreDefEntity_FP_T )(UINT8 * bufferIn,UINT32 len);

typedef GSN_STATUS
(*GsnXMLStr_DecodeSimpleElement_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,\
										 UINT8 * bufferIn,UINT32 len,GSNXMLSTR_CB_PARAM_T * xmlParserCbParam);
typedef GSN_STATUS
(*GsnXMLStr_Encode_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * inBuffer, \
						UINT32 len,UINT32 elementType,INT8 * * outBuffer,UINT32 bufferStartIndex,UINT32 * outLen);
typedef UINT32
(*GsnXMLStr_EncodePreDefEntity_FP_T)(UINT8 * bufferIn,UINT32 len,INT8 * outBuffer);

typedef UINT32
(*GsnXMLStr_FillElements_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,GSNXMLSTR_CB_PARAM_T * Elements, \
								INT8 * buffer,UINT32 startIndex);
typedef UINT32
(*GsnXMLStr_GetEncodedValueLen_FP_T)(UINT8 * bufferIn,UINT32 len);

typedef INT32
(*GsnXMLStr_NextParamGet_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * temp,\
								UINT8 delim,UINT32 len);
typedef PUBLIC VOID
(*GsnXMLStr_ParserCtxDeInit_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx);

typedef PUBLIC VOID
(*GsnXMLStr_ParserCtxInit_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx);

typedef PUBLIC VOID
(*GsnXMLStr_SetRootTag_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT8 * rootTag);

typedef PUBLIC VOID
(*GsnXMLStr_SetTagCount_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,UINT32 totalTagCount);

typedef GSN_STATUS
(*GsnXMLStr_TagWithAttrubute_FP_T)(GSNXMLSTR_PARSER_CTX_T * xmlParserCtx,\
								   UINT8 * bufferIn,UINT32 * len);
  
extern _RPST_ GsnXMLStr_Decode_FP_T GsnXMLStr_Decode_FP ; 
extern _RPST_ GsnXMLStr_DecodePreDefEntity_FP_T GsnXMLStr_DecodePreDefEntity_FP ;
extern _RPST_ GsnXMLStr_DecodeSimpleElement_FP_T GsnXMLStr_DecodeSimpleElement_FP ; 
extern _RPST_ GsnXMLStr_Encode_FP_T GsnXMLStr_Encode_FP ; 
extern _RPST_ GsnXMLStr_EncodePreDefEntity_FP_T GsnXMLStr_EncodePreDefEntity_FP ;
extern _RPST_ GsnXMLStr_FillElements_FP_T GsnXMLStr_FillElements_FP ;
extern _RPST_ GsnXMLStr_GetEncodedValueLen_FP_T GsnXMLStr_GetEncodedValueLen_FP ;
extern _RPST_ GsnXMLStr_NextParamGet_FP_T GsnXMLStr_NextParamGet_FP ;
extern _RPST_ GsnXMLStr_ParserCtxDeInit_FP_T GsnXMLStr_ParserCtxDeInit_FP ;
extern _RPST_ GsnXMLStr_ParserCtxInit_FP_T GsnXMLStr_ParserCtxInit_FP ;
extern _RPST_ GsnXMLStr_SetRootTag_FP_T  GsnXMLStr_SetRootTag_FP ;
extern _RPST_ GsnXMLStr_SetTagCount_FP_T GsnXMLStr_SetTagCount_FP ;
extern _RPST_ GsnXMLStr_TagWithAttrubute_FP_T GsnXMLStr_TagWithAttrubute_FP ;

