#include "gsn_includes.h"
#include "modules/fact_dflt/gsn_factory_dflt.h"
#include "drivers/otp/gsn_otp.h"

typedef VOID ( * GsnFactDflt_Init_FP_T) (GSN_OTP_T *pOtp);
typedef GSN_FACT_DFLT_ELEMENT_T * (* GsnFactDflt_ElementGet_FP_T)(GSN_FACT_DFLT_ID_T id);
typedef VOID (* GsnFactDflt_Deinit_FP_T)();

extern _RPST_ GsnFactDflt_Init_FP_T GsnFactDflt_Init_FP;
extern _RPST_ GsnFactDflt_ElementGet_FP_T GsnFactDflt_ElementGet_FP;
extern _RPST_ GsnFactDflt_Deinit_FP_T GsnFactDflt_Deinit_FP;