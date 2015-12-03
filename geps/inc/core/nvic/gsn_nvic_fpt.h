/******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by GainSpan
* Corporation or its licensors.  Title to the Material remains
* with GainSpan Corporation or its suppliers and licensors.
*
* The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used,
* copied, reproduced, modified, published, uploaded, posted, transmitted,
* distributed, or disclosed in any way except in accordance with the
* applicable license agreement.
*
* No license under any patent, copyright, trade secret or other
* intellectual property right is granted to or conferred upon you by
* disclosure or delivery of the Materials, either expressly, by
* implication, inducement, estoppel, except in accordance with the
* applicable license agreement.
*
* Unless otherwise agreed by GainSpan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by GainSpan
* or GainSpan's suppliers or licensors in any way.
*
* $RCSfile: gsn_nvic_fpt.h,v $
*
* Description :
*****************************************************************************/
#ifndef _GSN_NVIC_FPT_H_
#define _GSN_NVIC_FPT_H_

typedef VOID (* __gpioPosEdgeISR_FP_T)(VOID);
extern _RPST_ __gpioPosEdgeISR_FP_T __gpioPosEdgeISR_FP;

typedef VOID (* __gpioNegEdgeISR_FP_T)(VOID);
extern _RPST_ __gpioNegEdgeISR_FP_T __gpioNegEdgeISR_FP;

typedef VOID (* __mbReceive0ISR_FP_T)(VOID);
extern _RPST_ __mbReceive0ISR_FP_T __mbReceive0ISR_FP;

typedef VOID (* __mbReceive1ISR_FP_T)(VOID);
extern _RPST_ __mbReceive1ISR_FP_T __mbReceive1ISR_FP;

typedef VOID (* __mbReceive2ISR_FP_T)(VOID);
extern _RPST_   __mbReceive2ISR_FP_T __mbReceive2ISR_FP;

typedef VOID (* __mbReceive3ISR_FP_T)(VOID);
extern _RPST_  __mbReceive3ISR_FP_T __mbReceive3ISR_FP;

typedef VOID (* __mbReceive4ISR_FP_T)(VOID);
extern _RPST_  __mbReceive4ISR_FP_T __mbReceive4ISR_FP;

typedef VOID (* __mbReceive5ISR_FP_T)(VOID);
extern _RPST_  __mbReceive5ISR_FP_T __mbReceive5ISR_FP;

typedef VOID (* __mbReceive6ISR_FP_T)(VOID);
extern _RPST_  __mbReceive6ISR_FP_T __mbReceive6ISR_FP;

typedef VOID (* __mbReceive7ISR_FP_T)(VOID);
extern _RPST_  __mbReceive7ISR_FP_T __mbReceive7ISR_FP;

typedef VOID (* __otp0StoreCompleteISR_FP_T)(VOID);
extern _RPST_  __otp0StoreCompleteISR_FP_T __otp0StoreCompleteISR_FP;

typedef VOID (* __otp1StoreCompleteISR_FP_T)(VOID);
extern _RPST_  __otp1StoreCompleteISR_FP_T __otp1StoreCompleteISR_FP;

/* SSP - Serial Perripheral*/
typedef VOID (* __ssp0RtISR_FP_T)(VOID);
extern _RPST_  __ssp0RtISR_FP_T __ssp0RtISR_FP;

typedef VOID (* __ssp0RorISR_FP_T)(VOID);
extern _RPST_  __ssp0RorISR_FP_T __ssp0RorISR_FP;

typedef VOID (* __ssp0txISR_FP_T)(VOID);
extern _RPST_  __ssp0txISR_FP_T __ssp0txISR_FP;

typedef VOID (* __ssp0RxISR_FP_T)(VOID);
extern _RPST_  __ssp0RxISR_FP_T __ssp0RxISR_FP;

typedef VOID (* __ssp0MainISR_FP_T)(VOID);
extern _RPST_  __ssp0MainISR_FP_T __ssp0MainISR_FP;

typedef VOID (* __wdogISR_FP_T)(VOID);
extern _RPST_  __wdogISR_FP_T __wdogISR_FP;

typedef VOID (* __uart0ModemStatusISR_FP_T)(VOID);
extern _RPST_  __uart0ModemStatusISR_FP_T __uart0ModemStatusISR_FP;

typedef VOID (* __uart0RecvISR_FP_T)(VOID);
extern _RPST_  __uart0RecvISR_FP_T __uart0RecvISR_FP;

typedef VOID (* __uart0TransmitISR_FP_T)(VOID);
extern _RPST_  __uart0TransmitISR_FP_T __uart0TransmitISR_FP;

typedef VOID (* __uart0RecvTimeoutISR_FP_T)(VOID);
extern _RPST_  __uart0RecvTimeoutISR_FP_T __uart0RecvTimeoutISR_FP;

typedef VOID (* __uart0CombinedErrorISR_FP_T)(VOID);
extern _RPST_  __uart0CombinedErrorISR_FP_T __uart0CombinedErrorISR_FP;

typedef VOID (* __uart0CombinedISR_FP_T)(VOID);
extern _RPST_  __uart0CombinedISR_FP_T __uart0CombinedISR_FP;

typedef VOID (* __cryptoMpmISR_FP_T)(VOID);
extern _RPST_  __cryptoMpmISR_FP_T __cryptoMpmISR_FP;

typedef VOID (* __cryptoEaISR_FP_T)(VOID);
extern _RPST_  __cryptoEaISR_FP_T __cryptoEaISR_FP;

typedef VOID (* __cryptoKepISR_FP_T)(VOID);
extern _RPST_  __cryptoKepISR_FP_T __cryptoKepISR_FP;

typedef VOID (* __cryptoReISR_FP_T)(VOID);
extern _RPST_  __cryptoReISR_FP_T __cryptoReISR_FP;

typedef VOID (* __cryptoPkaISR_FP_T)(VOID);
extern _RPST_  __cryptoPkaISR_FP_T __cryptoPkaISR_FP;

typedef VOID (* __cryptoRngISR_FP_T)(VOID);
extern _RPST_  __cryptoRngISR_FP_T __cryptoRngISR_FP;

typedef VOID (* __cryptoSpaccISR_FP_T)(VOID);
extern _RPST_  __cryptoSpaccISR_FP_T __cryptoSpaccISR_FP;

typedef VOID (* __cryptoGlblISR_FP_T)(VOID);
extern _RPST_  __cryptoGlblISR_FP_T __cryptoGlblISR_FP;

typedef VOID (* __timer1ISR_FP_T)(VOID);
extern _RPST_  __timer1ISR_FP_T __timer1ISR_FP;

typedef VOID (* __timer2ISR_FP_T)(VOID);
extern _RPST_  __timer2ISR_FP_T __timer2ISR_FP;

typedef VOID (* __rtcPcounterISR_FP_T)(VOID);
extern _RPST_  __rtcPcounterISR_FP_T __rtcPcounterISR_FP;

typedef VOID (* __rtcAlarmWuISR_FP_T)(VOID);
extern _RPST_  __rtcAlarmWuISR_FP_T __rtcAlarmWuISR_FP;

/* Flash Cache*/
typedef VOID (* __fcSwDmaDoneISR_FP_T)(VOID);
extern _RPST_  __fcSwDmaDoneISR_FP_T __fcSwDmaDoneISR_FP;

typedef VOID (* __fcInvalidAccessISR_FP_T)(VOID);
extern _RPST_  __fcInvalidAccessISR_FP_T __fcInvalidAccessISR_FP;


/* Clock COntrol*/
typedef VOID (* __cconStableISR_FP_T)(VOID);
extern _RPST_  __cconStableISR_FP_T __cconStableISR_FP;

typedef VOID (* __gtmrTimerISR_FP_T)(VOID);
extern _RPST_  __gtmrTimerISR_FP_T __gtmrTimerISR_FP;

typedef VOID (* __gtmrAlarmISR_FP_T)(VOID);
extern _RPST_  __gtmrAlarmISR_FP_T __gtmrAlarmISR_FP;

typedef VOID (* __DmaAcm3ch0DoneISR_FP_T)(VOID);
extern _RPST_  __DmaAcm3ch0DoneISR_FP_T __DmaAcm3ch0DoneISR_FP;

typedef VOID (* __DmaCm3ch1DoneISR_FP_T)(VOID);
extern _RPST_  __DmaCm3ch1DoneISR_FP_T __DmaCm3ch1DoneISR_FP;

typedef VOID (* __DmaSsp0RxdmaDoneISR_FP_T)(VOID);
extern _RPST_ __DmaSsp0RxdmaDoneISR_FP_T __DmaSsp0RxdmaDoneISR_FP;

typedef VOID (* __DmaSsp0TxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaSsp0TxdmaDoneISR_FP_T __DmaSsp0TxdmaDoneISR_FP;

typedef VOID (* __DmaUart0RxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaUart0RxdmaDoneISR_FP_T __DmaUart0RxdmaDoneISR_FP;


typedef VOID (* __DmaUart0TxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaUart0TxdmaDoneISR_FP_T __DmaUart0TxdmaDoneISR_FP;

typedef VOID (* __DmaSsp1RxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaSsp1RxdmaDoneISR_FP_T __DmaSsp1RxdmaDoneISR_FP;

typedef VOID (* __DmaSsp1TxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaSsp1TxdmaDoneISR_FP_T __DmaSsp1TxdmaDoneISR_FP;

typedef VOID (* __DmaUart1RxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaUart1RxdmaDoneISR_FP_T __DmaUart1RxdmaDoneISR_FP;

typedef VOID (* __DmaUart1TxdmaDoneISR_FP_T)(VOID);
extern _RPST_  __DmaUart1TxdmaDoneISR_FP_T __DmaUart1TxdmaDoneISR_FP;

typedef VOID (* __DmaErrorISR_FP_T)(VOID);
extern _RPST_  __DmaErrorISR_FP_T __DmaErrorISR_FP;

typedef VOID (* __uart1ModemStatusISR_FP_T)(VOID);
extern _RPST_  __uart1ModemStatusISR_FP_T __uart1ModemStatusISR_FP;

typedef VOID (* __uart1RecvISR_FP_T)(VOID);
extern _RPST_  __uart1RecvISR_FP_T __uart1RecvISR_FP;

typedef VOID (* __uart1TransmitISR_FP_T)(VOID);
extern _RPST_  __uart1TransmitISR_FP_T __uart1TransmitISR_FP;

typedef VOID (* __uart1RecvTimeoutISR_FP_T)(VOID);
extern _RPST_  __uart1RecvTimeoutISR_FP_T __uart1RecvTimeoutISR_FP;

typedef VOID (* __uart1CombinedErrorISR_FP_T)(VOID);
extern _RPST_  __uart1CombinedErrorISR_FP_T __uart1CombinedErrorISR_FP;

typedef VOID (* __uart1CombinedISR_FP_T)(VOID);
extern _RPST_  __uart1CombinedISR_FP_T __uart1CombinedISR_FP;

typedef VOID (* __ssp1RtISR_FP_T)(VOID);
extern _RPST_  __ssp1RtISR_FP_T __ssp1RtISR_FP;

typedef VOID (* __ssp1RorISR_FP_T)(VOID);
extern _RPST_  __ssp1RorISR_FP_T __ssp1RorISR_FP;

typedef VOID (* __ssp1txISR_FP_T)(VOID);
extern _RPST_  __ssp1txISR_FP_T __ssp1txISR_FP;

typedef VOID (* __ssp1RxISR_FP_T)(VOID);
extern _RPST_  __ssp1RxISR_FP_T __ssp1RxISR_FP;

typedef VOID (* __ssp1MainISR_FP_T)(VOID);
extern _RPST_  __ssp1MainISR_FP_T __ssp1MainISR_FP;

typedef VOID (* __adcMainISR_FP_T)(VOID);
extern _RPST_  __adcMainISR_FP_T __adcMainISR_FP;

typedef VOID (* __sdioMainISR_FP_T)(VOID);
extern _RPST_  __sdioMainISR_FP_T __sdioMainISR_FP;

typedef VOID (* __i2cMainISR_FP_T)(VOID);
extern _RPST_  __i2cMainISR_FP_T __i2cMainISR_FP;

typedef VOID (* __i2sMainISR_FP_T)(VOID);
extern _RPST_  __i2sMainISR_FP_T __i2sMainISR_FP;

typedef VOID (* __pwmMainISR_FP_T)(VOID);
extern _RPST_  __pwmMainISR_FP_T __pwmMainISR_FP;

typedef VOID (* __gtmuMainISR_FP_T)(VOID);
extern _RPST_  __gtmuMainISR_FP_T __gtmuMainISR_FP;

typedef VOID (* __gspiSfifoISR_FP_T)(VOID);
extern _RPST_  __gspiSfifoISR_FP_T __gspiSfifoISR_FP;

typedef VOID (* __gspiDfifoISR_FP_T)(VOID);
extern _RPST_  __gspiDfifoISR_FP_T __gspiDfifoISR_FP;

typedef VOID (* __actlWwdogISR_FP_T)(VOID);
extern _RPST_  __actlWwdogISR_FP_T __actlWwdogISR_FP;

typedef VOID (* __sdadcdacFifoUndrWtrMarkISR_FP_T)(VOID);
extern _RPST_  __sdadcdacFifoUndrWtrMarkISR_FP_T __sdadcdacFifoUndrWtrMarkISR_FP;

typedef VOID (* __sdadcdacFifoOvrWtrMarkISR_FP_T)(VOID);
extern _RPST_  __sdadcdacFifoOvrWtrMarkISR_FP_T __sdadcdacFifoOvrWtrMarkISR_FP;

#endif