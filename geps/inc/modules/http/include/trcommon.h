#include "gsn_includes.h"
#include "modules/http/include/trsocket.h"
#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"

int tfGetMssLen(int socketDescriptor);

int tfNextPacketGet(NX_PACKET *nx_packet_next, char TM_FAR * TM_FAR *dataPtrPtr,
                   NX_PACKET **nextPacketPtr);

int tfZeroCopyRecv(int                   socketDescriptor,
                   ttUserMessage TM_FAR *bufferHandlePtr,
                   char TM_FAR * TM_FAR *dataPtrPtr,
                   int                   maxDataLength,
                   int                   flags,
                   ttUserMessage TM_FAR *nextPacketPtr,
                   int *errorCode);