#ifndef _GSN_OTP_FPT_H_
#define _GSN_OTP_FPT_H_

#include "drivers/otp/gsn_otp.h"

typedef GSN_STATUS (* GsnOtp_Write_FP_T)(GSN_OTP_T *pOtp, UINT8 *addr, UINT32 len, UINT8 *data);
typedef GSN_STATUS (* GsnOtp_Read_FP_T)(GSN_OTP_T *pOtp, UINT8 *addr, UINT32 len, UINT8 *data);
typedef GSN_STATUS (* GsnOtp_Init_FP_T)(GSN_OTP_T *pOtp, GSN_OTP_CTX_USES_OBJS_S *pUsesObjs, GSN_OTP_CTX_USES_INFO_T *pUsesInfo);
typedef GSN_STATUS (*GsnOtp_OtpMemRead_FP_T)(GSN_OTP_T *pOtp, UINT32 otpBlk, UINT32 addr, ULONG64 *data);
typedef VOID (*GsnOtp_Isr_FP_T)(void);
typedef GSN_STATUS (*GsnOtp_OtpMemWrite_FP_T)(GSN_OTP_T *pOtp, UINT32 otpBlk, UINT32 addr, ULONG64 data);
typedef void (*GsnOtp_ClkDisable_FP_T)(GSN_OTP_T *pOtp, UINT32 otpBlk);
typedef void (*GsnOtp_ClkEnable_FP_T)(GSN_OTP_T *pOtp, UINT32 otpBlk);
typedef void (*GsnOtp_Wait_FP_T)(GSN_OTP_T *pOtp);

extern _RPST_ GsnOtp_Write_FP_T GsnOtp_Write_FP;
extern _RPST_ GsnOtp_Read_FP_T GsnOtp_Read_FP;
extern _RPST_ GsnOtp_Init_FP_T GsnOtp_Init_FP;
extern _RPST_ GsnOtp_OtpMemRead_FP_T GsnOtp_OtpMemRead_FP;
extern _RPST_ GsnOtp_Isr_FP_T GsnOtp_Isr_FP;
extern _RPST_ GsnOtp_OtpMemWrite_FP_T GsnOtp_OtpMemWrite_FP;
extern _RPST_ GsnOtp_ClkDisable_FP_T GsnOtp_ClkDisable_FP;
extern _RPST_ GsnOtp_ClkEnable_FP_T GsnOtp_ClkEnable_FP;
extern _RPST_ GsnOtp_Wait_FP_T GsnOtp_Wait_FP;
#endif
