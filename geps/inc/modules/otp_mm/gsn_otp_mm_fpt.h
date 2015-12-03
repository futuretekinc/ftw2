
#ifndef _GSN_OTP_MM_FPT_H_

#define _GSN_OTP_MM_FPT_H_


/*****************************************************************************
* File Inclusion
*****************************************************************************/

#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "gsn_bitfield_macros.h"

#include "core/osal/gsn_osal.h"

#include "drivers/otp/gsn_otp.h"

#include "modules/otp_mm/gsn_otp_mm.h"
#include "modules/otp_mm/gsn_otp_mm_grps.h"



typedef PUBLIC GSN_STATUS
(*GsnOtpMm_Init_FP_T)(GSN_OTP_MM_CTX_T *otpMm,
                GSN_OTP_MM_USES_OBJS_T *usesObjs, GSN_OTP_MM_USES_INFO_T *usesInfo);

extern _RPST_ GsnOtpMm_Init_FP_T GsnOtpMm_Init_FP;



typedef PUBLIC GSN_STATUS
(*GsnOtpMm_Write_FP_T)(UINT8 id, UINT8 ver, UINT16 len, UINT8 *data);

extern _RPST_ GsnOtpMm_Write_FP_T GsnOtpMm_Write_FP;



typedef PUBLIC GSN_STATUS
(*GsnOtpMm_Read_FP_T)(UINT8 id, UINT8 ver, UINT16 *len, UINT8 *data);

extern _RPST_ GsnOtpMm_Read_FP_T GsnOtpMm_Read_FP;



typedef GSN_STATUS
(*GsnOtpMm_NextFreeLocFind_FP_T)(VOID);

extern _RPST_ GsnOtpMm_NextFreeLocFind_FP_T GsnOtpMm_NextFreeLocFind_FP;



typedef BOOL
(*GsnOtpMm_HdrValid_FP_T)(GSN_OTP_MM_DATA_T *otpHdr);

extern _RPST_ GsnOtpMm_HdrValid_FP_T GsnOtpMm_HdrValid_FP;

#endif /* _GSN_OTP_MM_FPT_H_ */

