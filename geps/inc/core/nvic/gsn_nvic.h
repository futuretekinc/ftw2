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
* $RCSfile: gsn_nvic.h,v $
*
* Description : ISR entry functions prototypes.
*****************************************************************************/
VOID __gpioPosEdgeISR(VOID);

VOID __gpioNegEdgeISR(VOID);

VOID __mbReceive0ISR(VOID);

VOID __mbReceive1ISR(VOID);

VOID __mbReceive2ISR(VOID);

VOID __mbReceive3ISR(VOID);

VOID __mbReceive4ISR(VOID);

VOID __mbReceive5ISR(VOID);

VOID __mbReceive6ISR(VOID);

VOID __mbReceive7ISR(VOID);

VOID __otp0StoreCompleteISR(VOID);

VOID __otp1StoreCompleteISR(VOID);

/* SSP - Serial Perripheral*/
VOID __ssp0RtISR(VOID);

VOID __ssp0RorISR(VOID);

VOID __ssp0txISR(VOID);

VOID __ssp0RxISR(VOID);

VOID __ssp0MainISR(VOID);

VOID __wdogISR(VOID);

VOID __uart0ModemStatusISR(VOID);

VOID __uart0RecvISR(VOID);

VOID __uart0TransmitISR(VOID);

VOID __uart0RecvTimeoutISR(VOID);

VOID __uart0CombinedErrorISR(VOID);

VOID __uart0CombinedISR(VOID);

VOID __cryptoMpmISR(VOID);

VOID __cryptoEaISR(VOID);

VOID __cryptoKepISR(VOID);

VOID __cryptoReISR(VOID);

VOID __cryptoPkaISR(VOID);

VOID __cryptoRngISR(VOID);

VOID __cryptoSpaccISR(VOID);

VOID __cryptoGlblISR(VOID);

VOID __timer1ISR(VOID);

VOID __timer2ISR(VOID);

VOID __rtcPcounterISR(VOID);

VOID __rtcAlarmWuISR(VOID);

/* Flash Cache*/
VOID __fcSwDmaDoneISR(VOID);

VOID __fcInvalidAccessISR(VOID);

/* Clock COntrol*/
VOID __cconStableISR(VOID);

VOID __gtmrTimerISR(VOID);

VOID __gtmrAlarmISR(VOID);

VOID __DmaAcm3ch0DoneISR(VOID);

VOID __DmaCm3ch1DoneISR(VOID);

VOID __DmaSsp0RxdmaDoneISR(VOID);

VOID __DmaSsp0TxdmaDoneISR(VOID);

VOID __DmaUart0RxdmaDoneISR(VOID);

VOID __DmaUart0TxdmaDoneISR(VOID);

VOID __DmaSsp1RxdmaDoneISR(VOID);

VOID __DmaSsp1TxdmaDoneISR(VOID);

VOID __DmaUart1RxdmaDoneISR(VOID);

VOID __DmaUart1TxdmaDoneISR(VOID);

VOID __DmaErrorISR(VOID);

VOID __uart1ModemStatusISR(VOID);

VOID __uart1RecvISR(VOID);

VOID __uart1TransmitISR(VOID);

VOID __uart1RecvTimeoutISR(VOID);

VOID __uart1CombinedErrorISR(VOID);

VOID __uart1CombinedISR(VOID);

VOID __ssp1RtISR(VOID);

VOID __ssp1RorISR(VOID);

VOID __ssp1txISR(VOID);

VOID __ssp1RxISR(VOID);

VOID __ssp1MainISR(VOID);

VOID __adcMainISR(VOID);

VOID __sdioMainISR(VOID);

VOID __i2cMainISR(VOID);

VOID __i2sMainISR(VOID);

VOID __pwmMainISR(VOID);

VOID __gtmuMainISR(VOID);

VOID __gspiSfifoISR(VOID);

VOID __gspiDfifoISR(VOID);

VOID __actlWwdogISR(VOID);

VOID __sdadcdacFifoUndrWtrMarkISR(VOID);

VOID __sdadcdacFifoOvrWtrMarkISR(VOID);

