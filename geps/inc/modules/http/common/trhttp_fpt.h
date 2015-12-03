#ifndef _TRHTTP_FPT_H_
#define _TRHTTP_FPT_H_

typedef ttCharPtr (* tfHttpGetCurrentTime_FP_T)(ttCharPtr timeBufferPtr, int timeBufferLen);
typedef int (* tfHttpGetChunkLen_FP_T)(ttCharPtr  chunkLine, int lineLen, tt32BitPtr valPtr);
typedef int  (* tfHttpFindHeaderIndex_FP_T) (ttCharPtr	headerTypeStrPtr);

extern _RPST_ tfHttpGetCurrentTime_FP_T tfHttpGetCurrentTime_FP;
extern _RPST_ tfHttpGetChunkLen_FP_T tfHttpGetChunkLen_FP;
extern _RPST_ tfHttpFindHeaderIndex_FP_T tfHttpFindHeaderIndex_FP;

#endif
