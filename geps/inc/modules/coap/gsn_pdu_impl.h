/*
 * gsn_pdu.h
 *
 *  Created on: 12-Jun-2013
 *      Author: Dhanya Lakshmi
 */

#ifndef GSN_PDU_H_
#define GSN_PDU_H_

#include "modules/coap/libcoap-4.0.1/pdu.h"
#include "gsn_includes.h"

typedef coap_pdu_t GSN_COAP_PDU_T;

#define GSN_COAP_MAX_PDU_SIZE COAP_MAX_PDU_SIZE

/* CoAP option types (be sure to update check_critical when adding options */

#define GSN_COAP_OPTION_IF_MATCH COAP_OPTION_IF_MATCH
#define GSN_COAP_OPTION_URI_HOST COAP_OPTION_URI_HOST
#define GSN_COAP_OPTION_ETAG COAP_OPTION_ETAG
#define GSN_COAP_OPTION_IF_NONE_MATCH COAP_OPTION_IF_NONE_MATCH
#define GSN_COAP_OPTION_URI_PORT COAP_OPTION_URI_PORT
#define GSN_COAP_OPTION_LOCATION_PATH COAP_OPTION_LOCATION_PATH
#define GSN_COAP_OPTION_URI_PATH COAP_OPTION_URI_PATH
#define GSN_COAP_OPTION_CONTENT_FORMAT COAP_OPTION_CONTENT_FORMAT
#define GSN_COAP_OPTION_CONTENT_TYPE GSN_COAP_OPTION_CONTENT_FORMAT
#define GSN_COAP_OPTION_MAXAGE COAP_OPTION_MAXAGE
#define GSN_COAP_OPTION_URI_QUERY COAP_OPTION_URI_QUERY
#define GSN_COAP_OPTION_ACCEPT COAP_OPTION_ACCEPT
#define GSN_COAP_OPTION_LOCATION_QUERY COAP_OPTION_LOCATION_QUERY
#define GSN_COAP_OPTION_PROXY_URI COAP_OPTION_PROXY_URI
#define GSN_COAP_OPTION_PROXY_SCHEME COAP_OPTION_PROXY_SCHEME

/* option types from draft-hartke-coap-observe-07 */

#define GSN_COAP_OPTION_OBSERVE COAP_OPTION_OBSERVE
#define GSN_COAP_OPTION_SUBSCRIPTION  COAP_OPTION_OBSERVE

/* selected option types from draft-core-block-04 */

#define GSN_COAP_OPTION_BLOCK2 COAP_OPTION_BLOCK2
#define GSN_COAP_OPTION_BLOCK1 COAP_OPTION_BLOCK1

#define GSN_COAP_MAX_OPT COAP_MAX_OPT

enum coap_conn_type
{
    GSN_COAP_MESSAGE_CON, /* confirmable message (requires ACK/RST) */
    GSN_COAP_MESSAGE_NON, /* non-confirmable message (one-shot message) */
    GSN_COAP_MESSAGE_ACK, /* used to acknowledge confirmable messages */
    GSN_COAP_MESSAGE_RST  /* indicates error in received messages */
};


/* CoAP request methods */
/* as of coap draft 13, these 4 are the request codes */
/* should we support response codes? since we are only client ? */
/* upon reception of unrecognized option of class critical in a confirmable transaction,the licoap is sending a 4.02 bad option response */
enum coap_conn_method
{
    GSN_COAP_REQUEST_GET = 1,
    GSN_COAP_REQUEST_POST,
    GSN_COAP_REQUEST_PUT,
    GSN_COAP_REQUEST_DELETE
};

typedef struct request_info
{
    enum coap_conn_method method;
    enum coap_conn_type type;
    unsigned short id;
} GSN_COAP_REQUEST_PARAMS_T;

typedef struct GSN_COAP_OPTION
{
    unsigned short key;
    unsigned int dataLength;
    void *data;
    struct GSN_COAP_OPTION * next;
} GSN_COAP_OPTION_LIST_T;

/* Creates a new CoAP PDU of given @p size. The function returns a pointer to
 * the node GSN_COAP_PDU_T object on success, or @c NULL on error. The storage
 * allocated for the result must be released with GsnCoap_Delete_Pdu().
 */
/*
 * internally calls
 * coap_pdu_t *coap_pdu_init(unsigned char type, unsigned char code, unsigned short id, size_t size);
 */
GSN_COAP_PDU_T* GsnCoap_Create_Pdu(GSN_COAP_REQUEST_PARAMS_T info,size_t size);

/*  Clears any contents from @p pdu and resets @c version field, @c
 * length and @c data pointers. @c max_size is set to @p size, any
 * other field is set to @c 0. Note that @p pdu must be a valid
 * pointer to a GSN_COAP_PDU_T object created e.g. by GsnCoap_Create_Pdu()
 */
void GsnCoap_Clear_Pdu(GSN_COAP_PDU_T * pdu, size_t size);

/* Delete the pdu created using GsnCoap_Create_Pdu() */
void GsnCoap_Delete_Pdu(GSN_COAP_PDU_T *);

/* Adds token to pdu that is passed as first parameter. Adding the token destroys
 * any following contents of the pdu. Hence options and data must be
 * added after GsnCoap_Add_Token() has been called
 * on error returns 0, else returns the number of bytes written;
 */
int GsnCoap_Add_Token(GSN_COAP_PDU_T *pdu,  unsigned int len, const unsigned char *data);

GSN_STATUS GsnCoap_Append_OptionList(GSN_COAP_OPTION_LIST_T ** listHead,unsigned short key,
                                     unsigned int dataLength, unsigned char *data );

/* Adds option of given type to pdu that is passed as first parameter. GsnCoap_Add_Option()
 * destroys the PDU's data, so GsnCoap_Add_Data must be called after all options have been
 * added.
 * on error returns 0, else returns the number of bytes written;
 */
GSN_STATUS GsnCoap_Add_Options(GSN_COAP_OPTION_LIST_T ** listHead,
                               GSN_COAP_PDU_T * pdu);


/**
 * Adds given data to the pdu that is passed as first parameter. Note that the PDU's
 * data is destroyed by GsnCoap_Add_Option().
 */
int GsnCoap_Add_Data(GSN_COAP_PDU_T *pdu, unsigned int len, const unsigned char *data);

/**
 * Retrieves the length and data pointer of specified PDU. Returns 0 on error
 * or 1 if *len and *data have correct values. Note that these values are
 * destroyed with the pdu.
 */
int GsnCoap_Get_Data(GSN_COAP_PDU_T *pdu, size_t *len, unsigned char **data);

GSN_STATUS	GsnCoap_Add_Option(unsigned short key,
                               unsigned int dataLength, unsigned char *data);

GSN_STATUS	GsnCoap_AddAll_OptionsTo_Pdu(GSN_COAP_PDU_T * pdu);


#endif /* GSN_PDU_H_ */
