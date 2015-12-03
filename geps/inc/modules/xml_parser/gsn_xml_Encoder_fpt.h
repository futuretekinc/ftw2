#include "modules/xml_parser/test/modules/gsn_xml.h"

typedef GSN_STATUS
(*GsnXml_Decode_FP_T )(UINT8 * ParentStart,UINT8 * ParentEnd,GSN_XML_COMPLEX_OBJ_T * XML_Schema,UINT8 * Return_Struct);

typedef INT32
(*FillValue_FP_T)(GSN_XML_OBJ_T * XML_Schema,UINT8 * User_Struct,UINT8 * buff,UINT32 maxBufSize,UINT32 bytesWritten);

typedef GSN_STATUS
(*GsnXml_Encode_FP_T )(GSN_XML_COMPLEX_OBJ_T * XML_Schema,UINT8 * User_Struct,UINT8 * XML_File_Buffer,\
						UINT32 XML_File_Buffer_Size,UINT32 * Len_Of_XML_Written);
typedef UINT16
(*GsnXml_EncodePreDefEntity_FP_T )(UINT8 * bufferIn,UINT16 len,UINT8 * outBuffer);

typedef UINT8
(*GsnXml_GetEncodedValueLen_FP_T)(UINT8 * bufferIn,UINT16 len);


extern _RPST_ FillValue_FP_T FillValue_FP ;    
extern _RPST_ GsnXml_Encode_FP_T GsnXml_Encode_FP ;
extern _RPST_ GsnXml_EncodePreDefEntity_FP_T GsnXml_EncodePreDefEntity_FP ;
extern _RPST_ GsnXml_GetEncodedValueLen_FP_T GsnXml_GetEncodedValueLen_FP ;

