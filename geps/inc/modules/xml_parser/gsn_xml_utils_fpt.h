#include "modules/xml_parser/test/modules/gsn_xml.h"
typedef UINT8
(*CountTabsAndSpaces_FP_T)(UINT8 * String,UINT8 Till,UINT8 ParentNodeLength);
	
typedef UINT8
(*length_return_type_FP_T)(GSN_XML_OBJ_T * schema);


extern _RPST_ CountTabsAndSpaces_FP_T CountTabsAndSpaces_FP ;
extern _RPST_ length_return_type_FP_T length_return_type_FP;


