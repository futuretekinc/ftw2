#ifndef _GSN_RING_BUF_FPT_H_
#define _GSN_RING_BUF_FPT_H_

typedef GSN_RING_BUF_HNDL_T
(*GsnRingBuf_Init_FP_T)(GSN_RING_BUF_T *ringBuf,
                        UINT8 entrySize, UINT8 ringSize, VOID *buf);

extern _RPST_ GsnRingBuf_Init_FP_T GsnRingBuf_Init_FP;



typedef GSN_STATUS_T
(*GsnRingBuf_Put_FP_T)(GSN_RING_BUF_HNDL_T ringBuf, VOID *pData);

extern _RPST_ GsnRingBuf_Put_FP_T GsnRingBuf_Put_FP;



typedef BOOL
(*GsnRingBuf_IsMsgQueued_FP_T)(GSN_RING_BUF_HNDL_T ringBuf, VOID *pData);

extern _RPST_ GsnRingBuf_IsMsgQueued_FP_T GsnRingBuf_IsMsgQueued_FP;



typedef GSN_STATUS
(*GsnRingBuf_Get_FP_T)(GSN_RING_BUF_HNDL_T ringBuf, VOID *pData);

extern _RPST_ GsnRingBuf_Get_FP_T GsnRingBuf_Get_FP;


#endif
