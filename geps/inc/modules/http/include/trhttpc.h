#ifndef _trhttpc_h_

#define _trhttpc_h_

#include "modules/http/include/trmacro.h"
#include "modules/http/include/trsocket.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"


typedef enum GHS_HTTP_TYPE_T
{
    TM_HTTP = 0,
    TM_HTTPS
}GHS_HTTP_TYPE_T;

#define TM_HTTPC_MAX_LINE_LENGTH        1024
/* line buffer length, 5 is the lenght of CRLF + CRLF + '/0' */
#define TM_HTTPC_LINE_BUFF_LEN          TM_HTTPC_MAX_LINE_LENGTH + 5

/* HTTP client connection structure */
typedef struct tsHttpcConEntry
{
    ttHttpcUserEventHandler hconEventHandler;        /* user event handler  */
    ttUserMessage           hconRespBufferMsg;       /* zero copy buffer    */
    ttCharPtr               hconRespBufferStartPtr;  /* buffer start pointer*/
    ttCharPtr               hconRespBufferCurrPtr;   /* resp current pointer*/
    ttCharPtr               hconRespReasonPhrasePtr; /* resp reason phrase  */
    ttCharPtr               hconRespHeaderVals
                            [TM_HTTP_HEADER_COUNT];  /* resp headers array  */
    ttCharPtr               hconLine;                /* line buffer         */
    ttS32Bit                hconReqChunkUnsentLen;   /* chunk len to be sent*/
    ttS32Bit                hconRespBodyUnreadLen;   /* resp body to read   */
    ttS32Bit                hconRespBufferLen;       /* zero copy buffer len*/
    ttS32Bit                hconRespBufferUnreadLen; /* buffer to be read   */
    tt32Bit                 hconLineIndex;           /* line buffer cursor  */
    tt32Bit                 hconRespHeaderMask;      /* resp header mask    */
    tt32Bit                 hconRespBodyLen;         /* resp body total len */
    tt32Bit                 hconLineLen;             /* line buffer data len*/
    ttHttpUserVersion       hconRespVersion;         /* resp HTTP version   */
    ttUserGenericUnion      hconUserVar;             /* user generic union  */
    int                     hconRespStatusCode;      /* resp status code    */
    int                     hconSd;                  /* TCP client socket   */
    tt16Bit                 hconLineMaxSize;         /* size of hconLine buf*/
    tt8Bit                  hconRespHeaderCount;     /* resp header count   */
    tt8Bit                  hconBlockingMode;        /* blocking mode       */
    tt8Bit                  hconState;               /* the client state    */
    tt8Bit                  hconLineState;           /* CRLF detecting state*/
    tt8Bit                  hconChunkState;          /* Chunk state         */
    tt8Bit                  hconFlags;               /* Flags               */
    ttUserMessage           hconRespNextPacket;
    ttVoidPtr            hConSsl;
    tt32Bit               hconHttpType; /* HTTP or HTTPS*/
#if 1//def  GSN_HTTP_CUSTOM_SUPPORT
    ttHttpcCustomHdr        hconCustomHdr;
#endif
} ttHttpcConEntry;

typedef ttHttpcConEntry TM_FAR *    ttHttpcConEntryPtr;

#endif
