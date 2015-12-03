#include "gsn_includes.h"

typedef GSN_STATUS
(* GsnDnsSrvr_Start_FP_T)(GSN_DNS_SERVER_T *pDnsSrvr, UINT8 *dnsName,GSN_DNS_INIT_PARAM_T *pDnsInitParams);
extern _RPST_ GsnDnsSrvr_Start_FP_T GsnDnsSrvr_Start_FP;

typedef GSN_STATUS
(* GsnDnsSrvr_Stop_FP_T)(GSN_DNS_SERVER_T *pDnsSrvr);
extern _RPST_ GsnDnsSrvr_Stop_FP_T GsnDnsSrvr_Stop_FP;

