/*
 * trhttpd.h
 *
 *  Created on: 18-Feb-2013
 *      Author: B LOHAWALA
 */

#ifndef _TRHTTPD_H_
#define _TRHTTPD_H_


#include "gsn_includes.h"
#include "modules/http/include/trsocket.h"
#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"
#include "modules/http/include/trcommon.h"

/*
 * Local macros
 */

/* Timeout waiting for the end of headers in milliseconds */
#define TM_HTTPD_HEADERS_TIMEOUT        TM_UL(10000) /* 10 seconds */
/*
 * Try and allocate room for pointers to CGI arguments, and values at the
 * end of the connection entry to reduce fragmentation.
 */


/*
 * public types, the enum types below will be moved to trsocket.h
 * when the HTTP common code is ready to be released.
 */
#define GSN_HTTPD_USE_EVENTS

#ifdef GSN_HTTPD_USE_EVENTS
#define GSN_HTTPD_EVENT_SHUTDOWN   (1)
#define GSN_HTTPD_EVENT_ACCEPT     (2)
#define GSN_HTTPD_EVENT_QUEUE      (4)

#define GSN_HTTPD_EVENTS_ALL       (GSN_HTTPD_EVENT_SHUTDOWN | GSN_HTTPD_EVENT_ACCEPT | GSN_HTTPD_EVENT_QUEUE)


#define TM_HTTPD_CHECK_SERVER_THREAD

#endif

#define TM_HTTPD_FIRST_ARG_IN_CONENTRY

#define TM_SSI_ERROR_BAD_RETURN         0
#define TM_SSI_ERROR_NO_BUFS            1
#define TM_SSI_ERROR_TAG_TOO_LONG       2

#define TM_SSI_STATE_MATCHING_PREFIX    0
#define TM_SSI_STATE_MATCHING_END       1
#define TM_SSI_STATE_SENDING_CACHE      2
#define TM_SSI_STATE_SENDING_PART_MATCH 3
#define TM_SSI_STATE_CALLING_HANDLER    4

#define TM_HTTPD_CONTENT_TEXT_HTML      0
#define TM_HTTPD_CONTENT_TEXT_XML       1
#define TM_HTTPD_CONTENT_TEXT_PLAIN     2
#define TM_HTTPD_CONTENT_IMAGE_JPEG     3
#define TM_HTTPD_CONTENT_IMAGE_GIF      4
#define TM_HTTPD_CONTENT_APP_OCTET      5
#if 1
#define TM_HTTPD_CONTENT_TEXT_CSS       6
#define TM_HTTPD_CONTENT_TEXT_JS        7
#define TM_HTTPD_CONTENT_TYPES_MAX      (TM_HTTPD_CONTENT_TEXT_JS+1)
#endif

#define TM_TEMP_RECV_BUF_SIZE           256
#define TM_CMD_LINE_SIZE                384

#ifndef TM_NOT_USE_BASIC_AUTH
#define TM_HTTPD_USE_BAA
#endif /* !TM_NOT_USE_BASIC_AUTH */

/* macros for characters in RFC 822 */
#define TM_SP                       ' '  /* 32 */
#define TM_CR                       '\r' /* 13 */
#define TM_LF                       '\n' /* 10 */
#define TM_HT                       9 /* Horizontal tab */
#define TM_ASCII_0                  0x30
#define TM_ASCII_A                  0x37 /* (0x41 - 0x37 == 10) */
#define TM_ASCII_a                  0x57 /* (0x61 - 0x57 == 10) */

#define TM_STATUS_LINE_DELIM_LEN    3 /* 1 SPACE + \r\n at the end */
#define TM_HEADER_LINE_DELIM_LEN    4 /* : SPACE + \r\n at the end */
#define TM_HTTP_CODE_STR_LEN        3 /* 3 decimal digits */
#define TM_HTTP_VERSION_STR_LEN     8
#define TM_INT_STRING_LEN           10

#define tm_dec_digit(curChar) \
    ( (curChar >= '0') && (curChar <= '9') )
#define tm_hex_digit(curChar) \
    ( (curChar >= 'A') && (curChar <= 'F') )
#define tm_hex_lower_case_digit(curChar) \
    ( (curChar >= 'a') && (curChar <= 'f') )


/* response flags, more */
/* response header flags */
#define TM_HTTPD_CGI                    (tt16Bit)0x0001
#define TM_HTTPD_FILE                   (tt16Bit)0x0002
#define TM_HTTPD_CGI_PARM_URL           (tt16Bit)0x0004
#define TM_HTTPD_SSI                    (tt16Bit)0x0008
#define TM_HTTPD_RESPONSE_CHUNKED       (tt16Bit)0x0010
#define TM_HTTPD_REQUEST_CHUNKED        (tt16Bit)0x0020
#define TM_HTTPD_IFMODIFIED_SINCE       (tt16Bit)0x0040
#define TM_HTTPD_CLOSE_CONNECTION       (tt16Bit)0x0080
#define TM_HTTPD_KEEPALIVE_CONNECTION   (tt16Bit)0x0100

/* Close flags */
/* User has called tfHttpdUserClose() */
#define TM_HTTPD_USER_CLOSE         (tt8Bit)0x01
/* User has been notified of open call */
#define TM_HTTPD_USER_OPEN          (tt8Bit)0x02
/* User has told us to discard the body */
#define TM_HTTPD_USER_DISCARD       (tt8Bit)0x04
/* User has told us to not copy the body */
#define TM_HTTPD_USER_NO_COPY       (tt8Bit)0x08

/*
 * Buffer size for zero copy network recv buffer.
 * Use TM_SOC_RECV_Q_BYTES to prevent truncation.
 */
#define TM_BUF_RECV_SIZE            TM_SOC_RECV_Q_BYTES

#ifndef TM_HTTPD_BODY_POLL
/* User signal body process (same as TM_CB_SSL_RECV_CLOSE unused here. */
#define TM_CB_PROCESS_BODY          0x1000
#endif /* !TM_HTTPD_BODY_POLL */
/* Close signal. Note same as TM_CB_HANDSHK_FAILURE unused here. */
#define TM_CB_CLOSE                 0x2000
/* Timeout call back. Note same as TM_CB_BADCERTIFICATE unused here. */
#define TM_CB_TIMEOUT               0x4000

/* chunked size len, 4HEX CRLF e.g. 4ABC\r\n */
#define TM_HTTPD_CHUNK_HEAD_LEN     6
/* chunk tail (CR, LF) */
#define TM_HTTPD_CHUNK_TAIL_LEN     2
/* Last Chunk ('0', CR, LF, CR, LF) */
#define TM_HTTPD_LAST_CHUNK_LEN     5


#define TM_HTTPD_WRITE_EOL              1
#define TM_HTTPD_WRITE_HEADER           2
#define TM_HTTPD_WRITE_SPACE            3
#define TM_HTTPD_WRITE_BACK_SLASH       4
#define TM_HTTPD_WRITE_BACK_SLASH_EOL   5

/* maximum ENV in server, num in ttHttpdEnvVar */
#define TM_MAX_CONN_ENV             20

/* default HTTPD port */
#define TM_HTTPD_DEF_PORT           80

#if 1//def GSN_SSL_SERVER_SUPPORT
#define TM_HTTPS_DEF_PORT           443
#endif

/* States to detect <CR><LF> end of line indicators */
#define TM_CMDLN_STATE_END_OF_LN    (tt8Bit)1
#define TM_CMDLN_STATE_CR           (tt8Bit)2

/* States to detect %xx in arg, value */
#define TM_CGI_STATE_IDLE           (tt8Bit)0x00
#define TM_CGI_STATE_HEX_1          (tt8Bit)0x01
#define TM_CGI_STATE_HEX_2          (tt8Bit)0x02
#define TM_CGI_STATE_ARG_NAME       (tt8Bit)0x04
#define TM_CGI_STATE_ARG_VALUE      (tt8Bit)0x08

#define TM_CGI_STATE_HEX \
        (TM_CGI_STATE_HEX_1 | TM_CGI_STATE_HEX_2)
#define TM_CGI_STATE_ARG \
        (TM_CGI_STATE_ARG_NAME | TM_CGI_STATE_ARG_VALUE)

/* Duration after which malloc will be retried */
#define TM_HTTPD_MALLOC_RETRY_TIME   100
#define TM_HTTPD_MALLOC_MAX_RETRIES  65535

#define tm_high_nibble(dataChar, asciiValue) \
                        (char)((((dataChar) - asciiValue)<<4) & 0xF0)
#define tm_low_nibble(dataChar, asciiValue) \
                        (char)((((dataChar) - asciiValue)) & 0x0F)

/* scan till to the CRLF */
#define tm_scan_crlf(a)                     \
    while ((*a != TM_CR)&&(*a!= TM_LF))     \
    {                                       \
        a++;                                \
    }

/* skip CR, LF or CRLF */
#define tm_skip_crlf(a)                     \
    if (*a == TM_CR)                        \
    {                                       \
        a++;                                \
    }                                       \
    if ( *a == TM_LF )                      \
    {                                       \
        a++;                                \
    }

/* skip space, only one space */
#define tm_skip_one_space(a)    a++

/* add a string to the buffer */
#define tm_add_string(destPtrPtr, srcPtr, lenPtr)  \
 tfHttpdAddString(destPtrPtr, (ttCharPtr)srcPtr, lenPtr, 0)

/* add a string to the buffer and a space */
#define tm_add_string_space(destPtrPtr, srcPtr, lenPtr)  \
 tfHttpdAddString(destPtrPtr, (ttCharPtr)srcPtr, lenPtr, TM_HTTPD_WRITE_SPACE)

/* add a string to the buffer and a back slash */
#define tm_add_string_back_slash(destPtrPtr, srcPtr, lenPtr)  \
 tfHttpdAddString(destPtrPtr, (ttCharPtr)srcPtr, lenPtr,  \
                  TM_HTTPD_WRITE_BACK_SLASH)

/* add the string to the buffer and CRLF */
#define tm_add_string_eol(destPtrPtr, srcPtr, lenPtr)  \
 tfHttpdAddString(destPtrPtr, (ttCharPtr)srcPtr, lenPtr, TM_HTTPD_WRITE_EOL)

/* add the string to the buffer, back slash, and  CRLF */
#define tm_add_string_back_slash_eol(destPtrPtr, srcPtr, lenPtr)  \
 tfHttpdAddString(destPtrPtr, (ttCharPtr)srcPtr, lenPtr,  \
                  TM_HTTPD_WRITE_BACK_SLASH_EOL)

/* add the string to the buffer and ':'*/
#define tm_add_string_header(destPtrPtr, srcPtr, lenPtr)           \
 tfHttpdAddString(destPtrPtr, (ttCharPtr)srcPtr, lenPtr, TM_HTTPD_WRITE_HEADER)

/* Queue not empty */
#define tm_httpd_q_not_empty(srvEntryPtr, i)                        \
  (srvEntryPtr->hsrvConQHead.servQHeadCount[i] != 0 )

/* Is the given httpd connection, the only entry in a queue? */
#define tm_httpd_single_in_q(srvEntryPtr, conEntryPtr, i)               \
  (    (srvEntryPtr->hsrvConQHead.servQHeadCount[i] == 1 )              \
    && (conEntryPtr == (ttHttpdConEntryPtr)                             \
               (srvEntryPtr->hsrvConQHead.servHeadNextQEntryPtr(i))) )

#define tm_httpd_not_single_in_q(srvEntryPtr, conEntryPtr, i)            \
  (    (srvEntryPtr->hsrvConQHead.servQHeadCount[i] != 1 )              \
    || (conEntryPtr != (ttHttpdConEntryPtr)                             \
               (srvEntryPtr->hsrvConQHead.servHeadNextQEntryPtr(i))) )

#ifdef TM_USE_FS_PARAMETER
/* Fetch File System parameter */
#define tm_httpd_fs_param(conEntryPtr) \
    ((conEntryPtr)->hconSrvHandlePtr->hdlSrvFSparamPtr)
#else /* !TM_USE_FS_PARAMETER */
/* File System parameter not required */
#define tm_httpd_fs_param(entryp) ((ttVoidPtr)0)
#endif /* TM_USE_FS_PARAMETER */

#if 1
#define TM_HTTPD_GZ_EXTN_LEN 4  /* Space for ".gz" */
#endif

/*
 * Local types
 */

/*
 * HTTP status code current used and supported by the web server
 * 20x: success
 * 300x: Redirection, further action need be taken by user agent
 * 400x: Client error
 * 500x: Server error
 */
typedef enum teHttpUserStatusCode
{
    TM_HTTPD_STATUS_INVAL,       /* special value for invalid status */
    TM_HTTPD_STATUS_200,         /* OK, request succeeded            */
    TM_HTTPD_STATUS_206,         /* Partial Content                  */
    TM_HTTPD_STATUS_302,         /* Redirection */
    TM_HTTPD_STATUS_304,         /* Document has not been modified   */
    TM_HTTPD_STATUS_400,         /* Bad Request                      */
    TM_HTTPD_STATUS_401,         /* Unauthorized,                    */
    TM_HTTPD_STATUS_404,         /* Not found                        */
    TM_HTTPD_STATUS_416,         /* Requested range not satisfiable  */
    TM_HTTPD_STATUS_501,         /* Not implemented                  */
    TM_HTTPD_STATUS_503,         /* Out of resources                 */
    TM_HTTPD_STATUS_COUNT        /* Total number of status above     */
} ttHttpdUserStatusCode;

/* authorization entry structure */
typedef struct    tsHttpdAuthEntry
{
    ttNode              authNode;           /* to link all entries together */
    ttCharPtr           authObjectNamePtr;  /* Prefix of file or dir name   */
    ttCharPtr           authRealmPtr;       /* realm string                 */
    ttCharPtr           authUserPassPtr;    /* user:pass                    */
    ttCharPtr           authHashPtr;        /* hash value                   */
} ttHttpdAuthEntry;
typedef ttHttpdAuthEntry TM_FAR *     ttHttpdAuthEntryPtr;

/* Strucutre used to walk the authenticalition list to find the best match */
typedef struct tsHttpdAuthFinder
{
    ttHttpdAuthEntryPtr  hafAuthPtr;
    ttConstCharPtr       hafObjectNamePtr;
} ttHttpdAuthFinder;
typedef ttHttpdAuthFinder TM_FAR * ttHttpdAuthFinderPtr;

/* User connection handle is index in array of this data type */
typedef struct tsHttpdConHandle
{
/* Httpd connection entry pointer */
    ttVoidPtr hchConEntryPtr;
    tt16Bit   hchUserSrvHandle;
#if 1//def GSN_SSL_SERVER_SUPPORT
	int requestedFlag; /*Stored the socket cb flag HTTPD requested for */
#endif
} ttHttpdConHandle;
typedef ttHttpdConHandle TM_FAR *  ttHttpdConHandlePtr;

#ifdef TM_USE_HTTPD_SSI
typedef struct tsHttpdSsiTag
{
    ttCharPtr               ssiTagPtr;  /* SSI tag string */
    ttHttpdUserSsiHandler   ssiHandler; /* SSI hander function pointer */
    tt16Bit                 ssiTagLen; /* SSI tag Length */
} ttHttpdSsiTag;
typedef ttHttpdSsiTag TM_FAR * ttHttpdSsiTagPtr;
#endif /* TM_USE_HTTPD_SSI */

/* File match filter structure, for matching file quickly */
typedef struct ttFileFilter
{
/* List Node to link them all together. */
    ttNode     matchNode;
/* File matching type, one of the following :
 * TM_FS_MATCH_FILE_NAME
 * TM_FS_MATCH_FILE_EXT
 * TM_FS_MATCH_FILE_PATH
 * TM_FS_MATCH_DIR_NAME
 * TM_FS_MATCH_DIR_PATH
 */
    int         matchType;
/* A pointer to a null terminated string that has a file name, file extension,
 * full path to a file, directory name, or full path to a directory depending
 *  on the value of the parameter matchType
 */
    ttCharPtr   matchNamePtr;
} ttFileFilter;
typedef ttFileFilter TM_FAR * ttFileFilterPtr;

/* server entry structure */
typedef struct    tsHttpdSrvEntry
{
#ifdef TM_USE_HTTPD_CGI
/* User CGI ID function */
    ttHttpdUserCgiIdCBPtr       hsrvCgiIdFunc;
#endif /* TM_USE_HTTPD_CGI */
/* User Content Type function */
    ttHttpdUserContentTypeCBPtr hsrvContentTypeFunc;
/* server run/connection queue */
    ttServerQueueHead           hsrvConQHead;
/* Httpd list of connections on a server known to the user */
    ttHttpdConHandlePtr         hsrvConHandleList;
/* root string */
    ttCharPtr                   hsrvRootPtr;
/* default page */
    ttConstCharPtr              hsrvDefaultPagePtr;
/* Redirect URL */
    ttConstCharPtr              hsrvRedirectUrl;

/* Number of malloc iterations */
    int                         hsrvMallocIterations;
/* CGI directory */
    ttConstCharPtr              hsrvCgiDirPtr;
#ifdef TM_USE_HTTPD_SSI
/* Points to a pair of SSI tag string and handler function */
    ttHttpdSsiTagPtr            hsrvSsiTagPtr;
#endif /* TM_USE_HTTPD_SSI */
#ifdef TM_PEND_POST_NEEDED
/* Pend entry */
    ttPendEntry                 hsrvPendSem;
#endif /* TM_PEND_POST_NEEDED */
/* timeout seconds */
    tt32Bit                     hsrvIdleTimeOut;
/* Bitmap of headers registered to be saved */
    tt32Bit                     hsrvRegisteredHeaderMask;
    ttHttpdUserSrvHandle        hsrvUserHandle;
#ifdef TM_USE_HTTPD_SSI
/* File system filter structure for specifying SSI files */
    ttList                      hsrvSsiFilterList;
#endif /* TM_USE_HTTPD_SSI */
/* CGI authorization strucutre list */
    ttList                      hsrvAuthList;
/* Event handler array */
    ttHttpdUserEventHandler     hsrvEventHandler;
#ifdef TM_USE_HTTPD_SSI
/* Number of SSI tags registered so far */
    int                         hsrvSsiTagCount;
#endif /* TM_USE_HTTPD_SSI */
/* listen socket */
    int                         hsrvListenSd;
/* length of buffer to be used for user-defined content types */
    int                         hsrvUserContentTypeLen;
/* Flags for user content type usage */
    int                         hsrvUserContentTypeFlags;
#ifdef TM_USE_HTTPD_SSI
/* File system filter structure for specifying SSI files */
    int                         hsrvFileBlockSize;
#endif /* TM_USE_HTTPD_SSI */
/* maximum connections */
    tt16Bit                     hsrvMaxConnections;
/* maximum connections Per IP address*/
    tt16Bit                     hsrvMaxConnectionsPerIp;
/* pending connections */
    tt16Bit                     hsrvPendingConnections;
/* Start index in search for an empty slot for a new connection */
    tt16Bit                     hsrvStartIndex;
/* Server flags */
    tt16Bit                     hsrvServerFlags;
/* Maxinum header line length */
    tt16Bit                     hsrvHeaderBufLen;
/* indicate if tfHttpdExecute() is running */
    tt8Bit                      hsrvExecuting;
/* shutdown indication */
    tt8Bit                      hsrvShutDown;
/* Listen has been called */
    tt8Bit                      hsrvListening;
/* Reject incoming requests with headers too long for our header buffer */
    tt8Bit                      hsrvRejectLongHeaders;
#if 1//def GSN_SSL_SERVER_SUPPORT
    void *sslCertCredentials;
    //tfHttpdSslRecvCbPtr sslRecvCb;
#endif
    void *pool_hdl;
    GSN_OSAL_MUTEX_T        *hsrvlock;
	/* GainSpan defined */
	ULONG		sysQualTskID;	/**< sys qual task ID for the IP task*/
	ULONG		sysQualTicks;	/**< sys qual ticks */
#ifdef GSN_HTTPD_USE_EVENTS
    GSN_OSAL_EVENT_FLAGS_T   tdQevntFlags;
    ULONG                    evntFlagsVal;
#endif
} ttHttpdSrvEntry;

typedef ttHttpdSrvEntry TM_FAR *     ttHttpdSrvEntryPtr;

/* User server handle is index in array of this data type */
typedef struct tsHttpdSrvHandle
{
    ttHttpdSrvEntryPtr       hdlSrvEntryPtr;   /* Httpd server pointer */
#ifdef TM_USE_FS_PARAMETER
    ttUserVoidPtr            hdlSrvFSparamPtr; /* File system parameter */
#endif /* TM_USE_FS_PARAMETER */
#ifdef TM_LOCK_NEEDED
/* Lock entry */
    ttLockEntry              hdlSrvLock; /* Httpd server lock */
#else
    GSN_OSAL_MUTEX_T        *hdlSrvLock;
#endif /* TM_LOCK_NEEDED */
} ttHttpdSrvHandle;

typedef ttHttpdSrvHandle    TM_FAR * ttHttpdSrvHandlePtr;
typedef ttHttpdSrvHandlePtr TM_FAR * ttHttpdSrvHandlePtrPtr;

typedef int (TM_CODE_FAR * ttHttpdSendFuncPtr)(ttVoidPtr conEntryPtr, int flag);

/*
 * HTTPD
 * From RFC1945 HTTPD Message Types
 * HTTP messages consist of requests from client to server and responses
 *  from server to client.
 *
 *      HTTP-message   = Simple-Request           ; HTTP/0.9 messages
 *                     | Simple-Response
 *                     | Full-Request             ; HTTP/1.0 messages
 *                     | Full-Response
 *
 *  Full-Request and Full-Response use the generic message format of RFC
 *  822 [7] for transferring entities. Both messages may include optional
 *  header fields (also known as "headers") and an entity body. The
 *  entity body is separated from the headers by a null line (i.e., a
 *  line with nothing preceding the CRLF).
 *
 *      Full-Request   = Request-Line             ; Section 5.1
 *                       *( General-Header        ; Section 4.3
 *                        | Request-Header        ; Section 5.2
 *                        | Entity-Header )       ; Section 7.1
 *                       CRLF
 *                       [ Entity-Body ]          ; Section 7.2
 *
 *       Full-Response  = Status-Line              ; Section 6.1
 *                       *( General-Header        ; Section 4.3
 *                        | Response-Header       ; Section 6.2
 *                         | Entity-Header )       ; Section 7.1
 *                        CRLF
 *                       [ Entity-Body ]          ; Section 7.2
 *
 *  Simple-Request and Simple-Response do not allow the use of any header
 *  information and are limited to a single request method (GET).
 *
 *      Simple-Request  = "GET" SP Request-URI CRLF
 *
 *      Simple-Response = [ Entity-Body ]
 *
 *   Use of the Simple-Request format is discouraged because it prevents
 *   the server from identifying the media type of the returned entity.
 */

#define TM_HTTPD_STATE_METHOD           0x01     /* receiving nethod line   */
#define TM_HTTPD_STATE_HEADER           0x02     /* receiving headers       */
#define TM_HTTPD_STATE_BODY             0x04     /* receiving body          */
#define TM_HTTPD_STATE_RESPONSE         0x08     /* Sending response        */

/* ORable flag, valid in TM_HTTPD_STATE_BODY state only */
#define TM_HTTPD_STATE_PARTIAL_BODY     0x10
/* ORable flag, valid in TM_HTTPD_STATE_BODY state only */
#define TM_HTTPD_STATE_SCATTERED_BODY   0x20

#define TM_HTTPD_HEADERS     (TM_HTTPD_STATE_METHOD | TM_HTTPD_STATE_HEADER)

#define TM_HTTPD_IDLE_TIMER 0

typedef struct tsHttpdFile
{
    struct tsHttpdFile *
                hfileNextFilePtr;       /* Next ttHttpdSsiFile              */
    ttVoidPtr   hfileFilePtr;           /* file pointers, from tfFsOpenFile */
#ifdef TM_HTTPD_SSI_DEBUG
    ttCharPtr   hfilePathPtr;           /* file name for debugging purpose  */
#endif /* TM_HTTPD_SSI_DEBUG */
    tt16Bit     hfileReadLen;           /* Length of the read from file     */
    tt8Bit      hfileEof;               /* reached the file end             */
#ifdef TM_USE_HTTPD_SSI
    ttCharPtr   hfileSsiMatchPtr;       /* The matching tag string          */
    tt8Bit      hfileIsSsi;             /* is this a SSI file               */
    tt8Bit      hfileOutputControl;     /* output enable/disable, abort page*/
    ttCharPtr   hfileReadBufferPtr;     /* read buffer              */
    tt16Bit     hfileReadPos;           /* read position            */
    tt16Bit     hfileSendPos;           /* send position            */
    tt16Bit     hfileEndPos;            /* end of the read buffer   */
    tt16Bit     hfileOverPos;           /* Overlapped position      */
    tt16Bit     hfileTagStartPos;       /* tag start position       */
    tt16Bit     hfileTagEndPos;         /* tag end position         */
    tt8Bit      hfileDoneBuffer;        /* done with a buffer       */
#endif /* TM_USE_HTTPD_SSI */
} ttHttpdFile;
typedef ttHttpdFile * ttHttpdFilePtr;

#define uconUReqMethod          hconUserConEntry.uconReqMethod
#define uconUReqVersion         hconUserConEntry.uconReqVersion
#define hconUReqPathPtr         hconUserConEntry.uconReqPathPtr
#define uconUReqHeaders         hconUserConEntry.uconReqHeaders
#define uconUReqContentLen      hconUserConEntry.uconReqContentLen
#define uconUReqBodyPtr         hconUserConEntry.uconReqBodyPtr
#define hconUPeerSockAddr       hconUserConEntry.uconPeerSockAddr
#define hconULocalSockAddr      hconUserConEntry.uconLocalSockAddr
#define uconUCredentials        hconUserConEntry.uconCredentials
#define uconUHdrTooLong         hconUserConEntry.uconHdrTooLong
#ifdef TM_USE_HTTPD_CGI
#define hconUCgiArgNamesPtrPtr  hconUserConEntry.uconCgiArgNames
#define hconUCgiArgValuesPtrPtr hconUserConEntry.uconCgiArgValues
#define hconUCgiArgCnt          hconUserConEntry.uconCgiArgCnt
#endif /* TM_USE_HTTPD_CGI */

typedef struct tsHttpdRange
{
    ttNode  hrsNode;        /* To link the ranges all together              */
    tt32Bit hrsFirstByte;   /* The first byte position of this range        */
    tt32Bit hrsLastByte;    /* The last byte position of this range         */
    tt32Bit hrsCurrByte;    /* The current sending position of this range   */
} ttHttpdRange;
typedef ttHttpdRange TM_FAR * ttHttpdRangePtr;

#define hconIdleTimerPtr hconTimerPtr[TM_HTTPD_IDLE_TIMER]
/* Run queue and list of FTP connections */
#define TM_HTTPD_RUN_Q           0
#define TM_HTTPD_CON_LIST        1
/* HTTPD connection entry */
typedef struct    tsHttpdConEntry
{
#define hconNextQEntryPtr(qIndex)     \
 hconQueueEntry.servQEntry[qIndex].qNextEntryPtr
/* #define hconPrevQEntryPtr(qIndex)     \
 hconQueueEntry.servQEntry[qIndex].qPrevEntryPtr */
/* Run q, and open connection list */
    ttServerQueue           hconQueueEntry;
/* back pointer to the server */
    ttHttpdSrvHandlePtr     hconSrvHandlePtr;
/* request message not yet handled */
    ttCharPtr               hconPrevReqDataPtr;
    ttUserMessage           hconPrevReqMessage;
/* Keep track whether the body buffer has been received by the user */
    ttCharPtr               hconBodyCurBufPtr;
    tt32Bit                 hconCurrChunkLen;
    tt32Bit                 hconRecvChunkLen;
    tt32Bit                 hconBodyCurBufLen;
#ifdef TM_HTTPD_SSI_DEBUG
    tt32Bit                 hconTotalBytesSent;
    tt32Bit                 hconRespBytesSent;
#endif /* TM_HTTPD_SSI_DEBUG */
#ifdef TM_LOCK_NEEDED
/*
 * Lock use when sending data since send could be called either from a
 * user task, or the HTTP server execute task.
 * hconSendLock protects the following fields:
 * hconRespStartPtr;
 * hconRespCurPtr;
 * hconRespStatusCode;
 * hconFilePtr;
 * hconSendFuncPtr;
 */
    ttLockEntry             hconSendLock;
#else
    GSN_OSAL_MUTEX_T  conSendLock;
    GSN_OSAL_MUTEX_T *hconSendLock;
#endif /* TM_LOCK_NEEDED */
    ttHttpdConHandlePtr     hconConHandlePtr;
/* send buffer */
    ttUserMessage           hconRespMsgPtr;
/* current response buffer pointer */
    ttCharPtr               hconRespCurPtr;
/* response buffer start pointer */
    ttCharPtr               hconRespStartPtr;
/*
 * response chunk start data pointer (usually same as hconRespStartPtr except
 * in first buffer which contains the HTTP response
 */
    ttCharPtr               hconRespChunkStartPtr;
/* Idle timer pointer */
    ttTimerPtr              hconTimerPtr[1];
/* file path pointer for the response */
    ttCharPtr               hconFilePathPtr;
/* Stack of SSI file Structures */
    ttHttpdFilePtr          hconFilePtr;
/* Authentication entry Pointer */
    ttHttpdAuthEntryPtr     hconAuthPtr;
    ttHttpdSendFuncPtr      hconSendFuncPtr;
#ifdef TM_USE_HTTPD_CGI
#ifdef TM_HTTPD_FIRST_ARG_IN_CONENTRY
    ttCharPtrPtr            hconCgiArgCntPtr;
#endif /* TM_HTTPD_FIRST_ARG_IN_CONENTRY */
/* Arguments point into received message */
#endif /* TM_USE_HTTPD_CGI */
/* Body copied into allocated buffer */
    ttCharPtr               hconBodyAllocBufPtr;
    ttUserMessage           hconBodyMessage;
/* Content type set by the user */
    ttCharPtr               hconUserContentTypePtr;
/* Pointer to buffer for storing header lines */
    ttCharPtr               hconCmdLinePtr;
/* Pointer to buffer for storing request URI */
    ttCharPtr               hconUrlPtr;
/* Pointer to buffer for storing chunked data */
    ttCharPtr               hconChunkPtr;
    ttHttpdUserConHandle    hconUserConHandle;
    ttHttpdUserConEntry     hconUserConEntry;
    tt32Bit                 hconRecvdBodyLen;
/* Index in buffer where we can copy the next scattered buffer  */
    tt32Bit                 hconBodyBufWriteIndex;
#ifndef TM_OPTIMIZE_SIZE
/* Size of allocated buffer to store data not yet handled */
    int                     hconPrevReqAllocLen;
#endif /* !TM_OPTIMIZE_SIZE */
/* parsed result of the RANGE header */
    ttList                  hconRangeList;
    int                     hconCmdLineIndex;
    int                     hconCmdLineLen;
    int                     hconChunkBufLen;
/* the request if-modified since time*/
    int                     hconSinceTime;
/* request len not yet handled */
    int                     hconPrevReqLen;
/* accept socket descriptor*/
    int                     hconSd;
    int                     hconStatusCode;
    int                     hconErrorCode;
/* request URI len */
    int                     hconUrlLen;
/* response status code */
/* size of the zero copy buffer */
    int                     hconZeroBufLen;
    int                     hconRespStatusCode;
    int                     hconBytesSent;
#ifdef TM_USE_HTTPD_CGI
/* Number of entries in Array of argument pointers to names, and values */
    tt16Bit                 hconCgiArgAllocCnt;
#ifdef TM_HTTPD_FIRST_ARG_IN_CONENTRY
/* Initial allocation for above */
    tt16Bit                 hconCgiInitialArgAllocCnt;
#endif /* TM_HTTPD_FIRST_ARG_IN_CONENTRY */
/* Maximum allocation for above */
    tt16Bit                 hconCgiMaxArgAllocCnt;
#endif /* TM_USE_HTTPD_CGI */
/* Size of buffer allocation to store the body  */
    tt16Bit                 hconBodyBufAllocLen;
/* file path buffer len */
    tt16Bit                 hconFilePathLen;
/* response headers flags */
    tt16Bit                 hconHeaderFlags;
    tt16Bit                 hconCbFlags;
    tt16Bit                 hconOwnerCount;
/* length of header line buffer for this connection */
    tt16Bit                 hconHeaderBufLen;
    tt8Bit                  hconUserFlags;
    tt8Bit                  hconCmdLineState;
#ifdef TM_USE_HTTPD_CGI
    tt8Bit                  hconCgiArgBufState;
#endif /* TM_USE_HTTPD_CGI */
    tt8Bit                  hconState;
    tt8Bit                  hconVerify;
/* send response completely and successfully */
    tt8Bit                  hconRespComplete;
/* need to post one more request not yet handled */
    tt8Bit                  hconNeedReadPost;
/* indicate if it is first frame ( with headers) in CGI response */
    tt8Bit                  hconFirstFrame;
/* Characters in %xx state machine */
    tt8Bit                  hconHexaChar; /* high nibble of hexa character */
    tt8Bit                  hconPrevChar; /* previous character read */
    tt8Bit                  hconStatusSent;
    tt8Bit                  hconHeadersSent;
    tt8Bit                  hconContentLengthSent;
#ifdef TM_USE_HTTPD_CGI
    tt8Bit                  hconNeedHeaders;
#endif /* TM_USE_HTTPD_CGI */
#ifndef TM_OPTIMIZE_SIZE
/* If we received data beyond our current HTTPD request, store it here */
    char                    hconTempBuf[TM_TEMP_RECV_BUF_SIZE];
#endif /* !TM_OPTIMIZE_SIZE */
#if 1//def GSN_SSL_SERVER_SUPPORT
    GSN_SSL_SERVER_CONN_T *sslServerConn;
#endif

#if 1
    /* pointer to pool handle, used for zero copy buffers */
    void *pool_hdl;
    char         *hconBodyNextPktPtr;
    ttUserMessage hconPktPtr;
#endif
} ttHttpdConEntry;
typedef ttHttpdConEntry TM_FAR *     ttHttpdConEntryPtr;

/*
 * Call back functions.
 */
/* Signal the HTTP server process with call back events */
void tfHttpdSignalServer(
    int             socketDesciptor,
    ttVoidPtr       conHandle,
    int             CBFlags );

/* Signal the HTTP server process with browser connection request */
void tfHttpdSignalServerAccept(
    int                      socketDescriptor,
    ttVoidPtr                userSrvHandle,
    int                      flags);

/* Idle connection timeout HTTP function */
void tfHttpdIdleTimeout (
    ttVoidPtr       timerBlockPtr,
    ttGenericUnion  userParm1,
    ttGenericUnion  userParm2);


/*
 * Local functions
 */

/* Implements redirect (location) , cookie, chunk-encoding, client pull,
   connection, and content-disposition headers. */
int tfHttpdHeaderOption(
                    int              hdrName,
                    char TM_FAR *    hdrObjPtr,
                    void TM_FAR *    hdrHttpsrvHandle,
                    char TM_FAR *    hdrValue1Ptr,
                    int              hdrValue1Length,
                    char TM_FAR *    hdrValue2Ptr,
                    int              hdrValue2Length,
                    int              hdrFlags );

#ifdef TM_USE_HTTPD_SSI
/* Find a tag in BufferPtr, beweeen startPos and currFilePtr->hfileEndPos,
 * Put the result in tagStartPtr and tagEndPtr
 * allocate memory for matchPtrPtr if needed and copy in, null terminate
 * If not found, set *tagStartPosPtr = 0; *tagEndPosPtr = 0
 */
int tfHttpdSearchSsiTag(
    ttHttpdSrvEntryPtr  srvEntryPtr,
    ttCharPtr           bufferPtr,
    tt16Bit             startPos,
    tt16Bit             endPos,
    tt16BitPtr          tagStartPosPtr,
    tt16BitPtr          tagEndPosPtr,
    ttCharPtrPtr        matchPtrPtr,
    tt16BitPtr          overlapTagPosPtr);
#endif /* TM_USE_HTTPD_SSI */

/* put chunk header, tail, and append last chunk if it is the last packet */
void tfHttpdChunkEncode(ttHttpdConEntryPtr  conEntryPtr, tt8Bit isLastPacket);

/* Find the content-type to be used for this outgoing page*/
ttConstCharPtr tfHttpdFindContentType(ttHttpdConEntryPtr conEntryPtr);

/* Find the best authenticator for an given object*/
ttHttpdAuthEntryPtr tfHttpdFindAuth(
    ttHttpdSrvEntryPtr  srvEntryPtr,
    ttConstCharPtr      objectNamePtr);

/* List call back function to match authenticator */
int tfHttpdFindAuthCb(ttNodePtr nodePtr, ttGenericUnion  genParam);

/* main execute function */
int tfHttpdExecute(ttHttpdSrvHandlePtr  srvHandlePtr);

/* accept connection request */
void tfHttpdAccept(ttHttpdSrvHandlePtr  srvHandlePtr,
                          ttHttpdSrvEntryPtr   srvEntryPtr);

/* close socket */
void tfHttpdCloseSocket(int socketDesc);

/* close connection entry */
void tfHttpdCloseConnection(ttHttpdConEntryPtr   conEntryPtr,
                                   tt8Bit               needServerLock);

/* request and response handler */
int tfHttpdHandler(ttHttpdConEntryPtr    conEntryPtr);

/* Queue excess data or record partial body */
ttUserMessage tfHttpdQueueData(ttHttpdConEntryPtr conEntryPtr,
                                      ttUserMessage      recvDataMessage,
                                      ttCharPtr          dataPtr,
                                      ttIntPtr           dataLenPtr);

/* config authentication option in HTTP server */
int tfHttpdAuthConfig(ttHttpdSrvEntryPtr  srvEntryPtr,
                             const char TM_FAR * objectNamePtr,
                             const char TM_FAR * realmPtr,
                             const char TM_FAR * userNamePtr,
                             const char TM_FAR * passwordPtr,
                             int                 authType );

#ifdef TM_USE_HTTPD_CGI
/* Collect CGI arguments from incoming data */
int tfHttpdCgiArgCollect(ttHttpdConEntryPtr conEntryPtr,
                                ttCharPtr          dataPtr,
                                tt32Bit            dataLen,
                                int                flags
                               );
#endif /* TM_USE_HTTPD_CGI */

/*
 * Map %xx to corresponding ASCII character
 * For CGI parse a sentense such as: /mycgi1?arg1=val1&arg2=val2&arg3=val3
 */
int tfHttpdConvert(ttHttpdConEntryPtr conEntryPtr,
                          ttCharPtr          dataPtr,
                          tt32Bit            dataLen,
                          tt8Bit             state);

#ifdef TM_USE_HTTPD_CGI
/*
 * Allocate/reallocate array of pointers to point to CGI argument names,
 * and values.
 */
int tfHttpdAllocCgiArgs(ttHttpdConEntryPtr conEntryPtr);
#endif /* TM_USE_HTTPD_CGI */

/*
 * Allocate/reallocate buffer to hold body data.
 */
int tfHttpdAllocBodyBuf(ttHttpdConEntryPtr conEntryPtr,
                               tt32Bit            allocLen,
                               ttDeviceEntryPtr   devPtr);
/* free body buffer if any */
void tfHttpdFreeBodyBuf(ttHttpdConEntryPtr conEntryPtr);

#ifdef TM_USE_HTTPD_CGI
#ifdef TM_HTTPD_FIRST_ARG_IN_CONENTRY
/*
 * Initialize size of array of argument pointers to names
 * and values with allocated count, and initialize user pointers to it.
 */
void tfHttpdCgiInitArgCnt(ttHttpdConEntryPtr conEntryPtr);
#endif /* TM_HTTPD_FIRST_ARG_IN_CONENTRY */
#endif /* TM_USE_HTTPD_CGI */

#ifdef TM_USE_HTTPD_CGI
/*
 * Free all buffers associated with CGI names, and values receptions.
 */
void tfHttpdFreeCgiArgs(ttHttpdConEntryPtr conEntryPtr);
#endif /* TM_USE_HTTPD_CGI */

/* Signal the server of an event with the server already locked */
void tfHttpdSignalLockedServer(
                ttHttpdSrvHandlePtr     srvHandlePtr,
                ttHttpdConEntryPtr      conEntryPtr,
                int                     flags
#ifdef TM_HTTPD_CHECK_SERVER_THREAD
              , tt8Bit                  serverThread
#endif /* TM_HTTPD_CHECK_SERVER_THREAD */
                );

#ifdef TM_USE_HTTPD_CGI
/* Signal user so that user sends more data */
int tfHttpdSendData(ttHttpdConEntryPtr conEntryPtr, int socketFlag);
#endif /* TM_USE_HTTPD_CGI */

/* Send a buffer to the zero copy cache */
int tfHttpdSendBuffer(
    ttHttpdConEntryPtr      conEntryPtr,
    const char TM_FAR *     bufferPtr,
    int                     bufferLen,
    ttHttpdSendFuncPtr      sendFuncPtr,
    int                     flag,
    int TM_FAR *            errorCodePtr);

/* Send the current zero copy buffer and end the connection */
void tfHttpdSendEnd(ttHttpdConEntryPtr conEntryPtr, int socketFlag);

int tfHttpdSendSsiError(
    ttHttpdConEntryPtr  conEntryPtr,
    int                 ssiErrorCode,
    ttCharPtr           tagPtr,
    int                 tagLen,
    int                 socketFlag);

/* send out the zero copy buffer  */
int tfHttpdSendPacket(ttHttpdConEntryPtr conEntryPtr, int socketFlag);

int    tfHttpdProcessMethodLine(ttHttpdConEntryPtr conEntryPtr);
void   tfHttpdProcessUrl(ttHttpdConEntryPtr conEntryPtr);
int    tfHttpdProcessHeaderLine (ttHttpdConEntryPtr conEntryPtr);
tt8Bit tfHttpdProcessRequestBody(ttHttpdConEntryPtr conEntryPtr);
/* Send Response enabling socket cal backs. */
void   tfHttpdProcessResponse(ttHttpdConEntryPtr conEntryPtr);

#ifdef TM_HTTPD_USE_BAA
/* verify the authorization */
int tfHttpdAuthVerify(
    ttHttpdConEntryPtr     conEntryPtr,
    ttCharPtr               bufferPtr);

/* We are done with the response. Signal the user for end of CGI data. */
void tfHttpdRespFinishFromSend(ttHttpdConEntryPtr    conEntryPtr,
                                      tt16Bit               flags);

#endif /* TM_HTTPD_USE_BAA */

/* find the header index */
ttHttpUserHeaderType tfHttpdFindHeaders(ttCharPtrPtr dataPtrPtr);

/* add a string to the buffer */
int tfHttpdAddString(ttCharPtrPtr bufferPtrPtr, ttCharPtr stringPtr,
                            ttIntPtr bufferLenPtr, int flags);

/* Send the file(s) on the stack on the connection entry to the HTTPD client */
int tfHttpdSendFile(ttHttpdConEntryPtr  conEntryPtr, int socketFlag);

#ifdef TM_USE_TEST_POINTS
void tfxHttpdRange(ttHttpdConEntryPtr conEntryPtr);
#endif /* TM_USE_TEST_POINTS */

/*
 * . We save the tfHttpdSendFile as the connection send function.
 * . We signal the locked server to come back and continue sending
 *   the current file on the connection entry later if we did not block
 */
void tfHttpdSignalSendFile(ttHttpdConEntryPtr conEntryPtr,
                                  int                errorCode
#ifdef TM_HTTPD_CHECK_SERVER_THREAD
/* From server thread? */
                                  ,tt8Bit            serverThread
#endif /* TM_HTTPD_CHECK_SERVER_THREAD */
                                 );

#ifdef TM_USE_HTTPD_SSI
/* Try send a buffer from the file read buffer and update the send position
 * handle partial send and TM_EWOUNDBLOCK,  returns bytes sent,
 * if bytes send < lenToSend, this function would signal the server
 * to send again later, the caller should exit tfHttpdSendFile
 */
int tfHttpdTrySendBuffer(
    ttHttpdConEntryPtr  conEntryPtr,
    ttHttpdFilePtr      currFilePtr,
    int                 lenToSend,
    int TM_FAR *        errorCodePtr,
    int                 socketFlag);
#endif /* TM_USE_HTTPD_SSI */

/* Free the buffers allocated and pointed by the members of a file structure
 * as well as the file structure itself.
 * close the file if open
 */
void tfHttpdFreeFile(
#ifdef TM_USE_FS_PARAMETER
    ttHttpdConEntryPtr  conEntryPtr,
#endif /* TM_USE_FS_PARAMETER */
    ttHttpdFilePtr      httpdFilePtr);

/* Add a file to the stack of files ont he connection entry */
int tfHttpdAddFileToSend(
    ttHttpdConEntryPtr  conEntryPtr,
    ttConstCharPtr      filePathPtr);

int tfHttpdSendResponse(ttHttpdConEntryPtr conEntryPtr, int socketFlag);

/*
 * Remove server entry from a server handle slot. Free allocated server
 * memory.
 */
void tfHttpdServerFree(
    ttHttpdSrvEntryPtr   srvEntryPtr,
    tt8Bit               locked);

/* Store server entry into a free slot, returning the index */
ttHttpdSrvHandlePtr tfHttpdServerStore(ttHttpdSrvEntryPtr srvEntryPtr);

/*
 * Given a handle (slot index), return the corresponding server handle
 * pointer
 */
ttHttpdSrvHandlePtr tfHttpdGetLockedServerHandle(
    ttHttpdUserSrvHandle userSrvHandle );

/*
 * Given a connection handle (slot index), return the corresponding
 * connection handle pointer with the server lock on.
 */
ttHttpdConEntryPtr tfHttpdGetLockedConHandle(
    ttHttpdUserConHandle        userConHandle,
    ttHttpdSrvHandlePtrPtr      srvHandlePtrPtr );

/*
 * Unlock a connection entry locked by the user (using the server lock),
 * and free it if its owner count has reached 0.
 */
#ifdef TM_LOCK_NEEDED
void tfHttpdReturnConHandle(
    ttHttpdConEntryPtr  conEntryPtr,
    ttHttpdSrvHandlePtr srvHandlePtr,
    int                 unlockFlag);
#define tm_httpd_return_con_handle(conEntryPtr, srvHandlePtr, unlockFlag) \
    tfHttpdReturnConHandle(conEntryPtr, srvHandlePtr, unlockFlag)
#else /* !TM_LOCK_NEEDED */
void tfHttpdReturnConHandle(ttHttpdConEntryPtr         conEntryPtr);
#define tm_httpd_return_con_handle(conEntryPtr, srvHandlePtr, unlockFlag) \
    tfHttpdReturnConHandle(conEntryPtr)
#endif /* !TM_LOCK_NEEDED */
/* Add HTTPD idle timer */
void tfHttpdTimerAdd(ttHttpdConEntryPtr conEntryPtr,
                            tt32Bit            timeout );
/* Remove HTTPD idle timer */
void tfHttpdTimerRemove(ttHttpdConEntryPtr conEntryPtr);
/*
 * Store new user connection (connection, server handle) pair for user
 * call validation
 */
int tfHttpdNewUserConnection(
    ttHttpdSrvEntryPtr  srvEntryPtr,
    ttHttpdConEntryPtr  conEntryPtr);

int tfHttpdGetZeroCopyBuffer(
    ttHttpdConEntryPtr  conEntryPtr,
    int                 socketFlag);
/*
 * Copy CR,LF terminated line in incoming buffer into a connection internal
 * input line buffer mapping <CR><LF> to '\0'.
 * Returns line len if a full line has been buffered, -1 otherwise.
 */
int tfHttpdGetLine(
    ttHttpdConEntryPtr  conEntryPtr,
    ttCharPtrPtr        srcPtrPtr,
    tt32BitPtr          srcLengthPtr);

/*
 * Buffer the chunked data until an entire chunk is received. Preserve <CR><LF>.
 */
int tfHttpdGetChunkLine(
    ttHttpdConEntryPtr conEntryPtr,
    ttCharPtrPtr       srcPtrPtr,
    tt32BitPtr         srcLengthPtr,
    ttIntPtr           lineLenPtr);

/* Count the connections from a given IP address, v4 or v6 */
int tfHttpdGetConCountByIp(
    ttHttpdSrvHandlePtr  srvHandlePtr,
    ttSockAddrStoragePtr sockAddrPtr);

/* Get the available bytes in the send zero coy buffer */
int tfHttpdGetAvailSendBufferSize(ttHttpdConEntryPtr conEntryPtr);

/* Process the range header specifications in the passed in string */
void tfHttpdProcessRangeHeader(
    ttHttpdConEntryPtr  conEntryPtr,
    ttCharPtr           rangeSpecPtr);

void
tm_call_unlock(GSN_OSAL_MUTEX_T **mutexptrptr);

void
tm_call_lock_wait(GSN_OSAL_MUTEX_T **mutexptrptr);

int tfHttpdUserSetRedirectUrl(
    ttHttpdUserSrvHandle        userSrvHandle,
    char*      redirectUrl);

int tfHttpdUserSetMallocTimeout(
    ttHttpdUserSrvHandle        userSrvHandle,
    int      mallocTimeout);

int tfHttpdUserSetRedirectUrl(
    ttHttpdUserSrvHandle        userSrvHandle,
    char*      redirectUrl);

int tfHttpdIsGzipFile(ttCharPtr fileName);

ttCharPtr tfHttpdUserGetURI();
int tfHttpdUserGetSockDesc(
    ttHttpdUserConHandle    userConHandle);

#endif /* _TRHTTPD_H_ */
