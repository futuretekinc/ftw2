#ifndef _FTW_HTTPD_H_
#define _FTW_HTTPD_H_

VOID  FTW_NET_HTTPD_stop(VOID);

#ifdef FTW_GSLINK
UINT8 FTW_NET_HTTPD_contentDataGet(UINT32 dataLen, UINT8 hCid);
UINT8 FTW_NET_HTTPD_rawContentGet(UINT32 dataLen, UINT8 hCid);

#endif

#endif