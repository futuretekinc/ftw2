#ifndef GSN_SYS_RESET_FPT_H_
#define GSN_SYS_RESET_FPT_H_

typedef VOID
(*GsnSys_Reset_FP_T)(GSN_RESET_REASON_T resetReason);
extern _RPST_ GsnSys_Reset_FP_T GsnSys_Reset_FP;

#endif