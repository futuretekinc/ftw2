/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2006 IAR Systems. All rights reserved.
 *
 * $Revision: 1.1.4.2 $
 *
 **************************************************/
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; Cortex-M3 version
;

       ; MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)


        SECTION .intvec:CODE:NOROOT(2)
        
                EXTERN  _tx_timer_interrupt
        EXTERN  __iar_program_start
        //EXTERN  __tx_NMIHandler                     
        ;EXTERN  __tx_BadHandler
        EXTERN 	GsnExcpHdlr_HardFault
        EXTERN	GsnExcpHdlr_MemManageFault
        EXTERN	GsnExcpHdlr_BusFault
        EXTERN	GsnExcpHdlr_UsageFault
        EXTERN  __tx_SVCallHandler                  
        //EXTERN  __tx_DBGHandler                     
        EXTERN  __tx_PendSVHandler                  
        //EXTERN  __tx_SysTickHandler                 
        //EXTERN  __tx_IntHandler                     
        EXTERN __gpioPosEdgeISR

        EXTERN __gpioNegEdgeISR
        EXTERN __mbReceive0ISR
        EXTERN __mbReceive1ISR
        EXTERN __mbReceive2ISR
        EXTERN __mbReceive3ISR
        EXTERN __mbReceive4ISR
        EXTERN __mbReceive5ISR
        EXTERN __mbReceive6ISR
        EXTERN __mbReceive7ISR
        EXTERN __otp0StoreCompleteISR
        EXTERN __otp1StoreCompleteISR
        EXTERN __ssp0RtISR
        EXTERN __ssp0RorISR
        EXTERN __ssp0txISR
        EXTERN __ssp0RxISR
        EXTERN __ssp0MainISR
        EXTERN __wdogISR
        EXTERN __uart0ModemStatusISR
        EXTERN __uart0RecvISR
        EXTERN __uart0TransmitISR
        EXTERN __uart0RecvTimeoutISR
        EXTERN __uart0CombinedErrorISR
        EXTERN __uart0CombinedISR
        EXTERN __cryptoMpmISR
        EXTERN __cryptoEaISR
        EXTERN __cryptoKepISR
        EXTERN __cryptoReISR
        EXTERN __cryptoPkaISR
        EXTERN __cryptoRngISR
        EXTERN __cryptoSpaccISR
        EXTERN __cryptoGlblISR
        EXTERN __timer1ISR
        EXTERN __timer2ISR
        EXTERN __rtcPcounterISR
        EXTERN __rtcAlarmWuISR
        EXTERN __fcSwDmaDoneISR
        EXTERN __fcInvalidAccessISR
        EXTERN __cconStableISR
        EXTERN __gtmrTimerISR
        EXTERN __gtmrAlarmISR
        EXTERN __DmaAcm3ch0DoneISR
        EXTERN __DmaCm3ch1DoneISR
        EXTERN __DmaSsp0RxdmaDoneISR
        EXTERN __DmaSsp0TxdmaDoneISR
        EXTERN __DmaUart0RxdmaDoneISR
        EXTERN __DmaUart0TxdmaDoneISR
        EXTERN __DmaSsp1RxdmaDoneISR
        EXTERN __DmaSsp1TxdmaDoneISR
        EXTERN __DmaUart1RxdmaDoneISR
        EXTERN __DmaUart1TxdmaDoneISR
        EXTERN __DmaErrorISR
        EXTERN __uart1ModemStatusISR
        EXTERN __uart1RecvISR
        EXTERN __uart1TransmitISR
        EXTERN __uart1RecvTimeoutISR
        EXTERN __uart1CombinedErrorISR
        EXTERN __uart1CombinedISR
        EXTERN __ssp1RtISR
        EXTERN __ssp1RorISR
        EXTERN __ssp1txISR
        EXTERN __ssp1RxISR
        EXTERN __ssp1MainISR
        EXTERN __adcMainISR
        EXTERN __sdioMainISR
        EXTERN __i2cMainISR
        EXTERN __i2sMainISR
        EXTERN __pwmMainISR
        EXTERN __gtmuMainISR
        EXTERN __gspiSfifoISR
        EXTERN __gspiDfifoISR
        EXTERN __actlWwdogISR
        EXTERN __sdadcdacFifoUndrWtrMarkISR
        EXTERN __sdadcdacFifoOvrWtrMarkISR
       
        ;PUBLIC  __vector_table
        PUBLIC  __new_tx_vectors

        DATA
;__vector_table
;#pragma location=0x20040000
#pragma data_alignment=512
__new_tx_vectors
        DC32	0;sfe(CSTACK)
        DC32    0
        DC32    __tx_NMIHandler                 	; NMI
        DC32    _tx_Hard_fault_handler				; HardFault
        DC32    _tx_memManage_fault_handler			; MemManage
        DC32    _tx_bus_fault_handler				; BusFault
        DC32    _tx_usage_fault_handler				; UsageFault
        DC32    0				; 7
        DC32    0				; 8
        DC32    0				; 9
        DC32    0				; 10
        DC32    __tx_SVCallHandler		; SVCall
        DC32    __tx_DBGHandler			; Monitor
        DC32    0				; 13
        DC32    __tx_PendSVHandler		; PendSV
        DC32    __tx_SysTickHandler		; SysTick
        
        DC32    _tx_gpioPosEdge_ISR                     ;Int  0
        DC32    _tx_gpioNegEdge_ISR                     ;Int  1
        DC32    _tx_mbReceive0_ISR                      ;Int  2 - MailBox Msg Recv Intr
        DC32    _tx_mbReceive1_ISR                      ;Int  3 - MailBox Ack Intr
        DC32    _tx_mbReceive2_ISR                      ;Int  4
        DC32    _tx_mbReceive3_ISR                      ;Int  5
        DC32    _tx_mbReceive4_ISR                      ;Int  6
        DC32    _tx_mbReceive5_ISR                      ;Int  7
        DC32    _tx_mbReceive6_ISR                      ;Int  8
        DC32    _tx_mbReceive7_ISR                      ;Int  9
        DC32    _tx_otp0StoreComplete_ISR               ;Int  10
        DC32    _tx_otp1StoreComplete_ISR               ;Int  11
        DC32    _tx_ssp0Rt_ISR                          ;Int  12
        DC32    _tx_ssp0Ror_ISR                         ;Int  13
        DC32    _tx_ssp0tx_ISR                          ;Int  14
        DC32    _tx_ssp0Rx_ISR                          ;Int  15
        DC32    _tx_ssp0Main_ISR                        ;Int  16
        DC32    _tx_wdog_ISR                            ;Int  17
        DC32    _tx_uart0ModemStatus_ISR                ;Int  18
        DC32    _tx_uart0Recv_ISR                       ;Int  19
        DC32    _tx_uart0Transmit_ISR                   ;Int  20
        DC32    _tx_uart0RecvTimeout_ISR                ;Int  21
        DC32    _tx_uart0CombinedError_ISR              ;Int  22
        DC32    _tx_uart0Combined_ISR                   ;Int  23
        DC32    _tx_cryptoMpm_ISR                       ;Int  24
        DC32    _tx_cryptoEa_ISR                        ;Int  25
        DC32    _tx_cryptoKep_ISR                       ;Int  26
        DC32    _tx_cryptoRe_ISR                        ;Int  27
        DC32    _tx_cryptoPka_ISR                       ;Int  28
        DC32    _tx_cryptoRng_ISR                       ;Int  29
        DC32    _tx_cryptoSpacc_ISR                     ;Int  30
        DC32    _tx_cryptoGlbl_ISR                      ;Int  31
        DC32    _tx_timer1_ISR                          ;Int  32
        DC32    _tx_timer2_ISR                          ;Int  33
        DC32    _tx_rtcPcounter_ISR                     ;Int  34
        DC32    _tx_rtcAlarmWu_ISR                      ;Int  35
        DC32    _tx_fcSwDmaDone_ISR                     ;Int  36
        DC32    _tx_fcInvalidAccess_ISR                 ;Int  37
        DC32    _tx_cconStable_ISR                      ;Int  38
        DC32    _tx_gtmrTimer_ISR                       ;Int  39
        DC32    _tx_gtmrAlarm_ISR                       ;Int  40
        DC32    _tx_DmaAcm3ch0Done_ISR                  ;Int  41
        DC32    _tx_DmaCm3ch1Done_ISR                   ;Int  42
        DC32    _tx_DmaSsp0RxdmaDone_ISR                ;Int  43
        DC32    _tx_DmaSsp0TxdmaDone_ISR                ;Int  44
        DC32    _tx_DmaUart0RxdmaDone_ISR               ;Int  45
        DC32    _tx_DmaUart0TxdmaDone_ISR               ;Int  46
        DC32    _tx_DmaSsp1RxdmaDone_ISR                ;Int  47
        DC32    _tx_DmaSsp1TxdmaDone_ISR                ;Int  48
        DC32    _tx_DmaUart1RxdmaDone_ISR               ;Int  49
        DC32    _tx_DmaUart1TxdmaDone_ISR               ;Int  50
        DC32    _tx_DmaError_ISR                        ;Int  51
        DC32    _tx_uart1ModemStatus_ISR                ;Int  52
        DC32    _tx_uart1Recv_ISR                       ;Int  53
        DC32    _tx_uart1Transmit_ISR                   ;Int  54
        DC32    _tx_uart1RecvTimeout_ISR                ;Int  55
        DC32    _tx_uart1CombinedError_ISR              ;Int  56
        DC32    _tx_uart1Combined_ISR                   ;Int  57
        DC32    _tx_ssp1Rt_ISR                          ;Int  58
        DC32    _tx_ssp1Ror_ISR                         ;Int  59
        DC32    _tx_ssp1tx_ISR                          ;Int  60
        DC32    _tx_ssp1Rx_ISR                          ;Int  61
        DC32    _tx_ssp1Main_ISR                        ;Int  62
        DC32    _tx_adcMain_ISR                         ;Int  63
        DC32    _tx_sdioMain_ISR                        ;Int  64
        DC32    _tx_i2cMain_ISR                         ;Int  65
        DC32    _tx_i2sMain_ISR                         ;Int  66
        DC32    _tx_pwmMain_ISR                         ;Int  67
        DC32    _tx_gtmuMain_ISR                        ;Int  68
        DC32    _tx_gspiSfifo_ISR                       ;Int  69
        DC32    _tx_gspiDfifo_ISR                       ;Int  70
        DC32    _tx_actlWwdog_ISR                       ;Int  71
        DC32    _tx_sdadcdacFifoUndrWtrMark_ISR         ;Int  72
        DC32    _tx_sdadcdacFifoOvrWtrMark_ISR          ;Int  73

        THUMB
     ;   SECTION .text:CODE:REORDER(2)
        ;PUBLIC Reset_Handler
;Reset_Handler
 ;       CPSID   i
  ;      LDR     R0, =sfe(CSTACK)          ; restore original stack pointer
   ;     MSR     MSP, R0 
        ;LDR     R0, =__iar_program_start  ; Jump to IAR startup code
    ;    BX      R0
        
        
        SECTION `.text`:CODE:NOROOT(2)
        
        EXTERN  _tx_thread_context_save
        EXTERN  _tx_thread_context_restore


// hard fault handler wrapper in assembly
// it extract the location of stack frame and pass it
// to handler in C as pointer.
_tx_Hard_fault_handler:
	TST 	LR, #4
	ITE 	EQ
	MRSEQ	R0, MSP
	MRSNE	R0, PSP
	B		GsnExcpHdlr_MemManageFault

_tx_memManage_fault_handler:
	TST     LR, #4
	ITE     EQ
	MRSEQ   R0, MSP
	MRSNE   R0, PSP
	B       GsnExcpHdlr_MemManageFault

_tx_bus_fault_handler:
	TST     LR, #4
	ITE     EQ
	MRSEQ   R0, MSP
	MRSNE   R0, PSP
	B       GsnExcpHdlr_BusFault

_tx_usage_fault_handler:
	TST     LR, #4
	ITE     EQ
	MRSEQ   R0, MSP
	MRSNE   R0, PSP
	B       GsnExcpHdlr_UsageFault

_tx_gpioPosEdge_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gpioPosEdgeISR
        B       _tx_thread_context_restore
        
 _tx_gpioNegEdge_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gpioNegEdgeISR
        B       _tx_thread_context_restore  
              
_tx_mbReceive0_ISR:
        PUSH    {lr}
        BL         _tx_thread_context_save
        BL        __mbReceive0ISR
        B         _tx_thread_context_restore  
        
        
_tx_mbReceive1_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive1ISR
        B       _tx_thread_context_restore  
        
_tx_mbReceive2_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive2ISR
        B       _tx_thread_context_restore  
        
_tx_mbReceive3_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive3ISR
        B       _tx_thread_context_restore  
        
_tx_mbReceive4_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive4ISR
        B       _tx_thread_context_restore  
        
_tx_mbReceive5_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive5ISR
        B       _tx_thread_context_restore  
        
_tx_mbReceive6_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive6ISR
        B       _tx_thread_context_restore  
        
_tx_mbReceive7_ISR
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __mbReceive7ISR
        B       _tx_thread_context_restore  
        
_tx_otp0StoreComplete_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __otp0StoreCompleteISR 
        B       _tx_thread_context_restore  
        
_tx_otp1StoreComplete_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __otp1StoreCompleteISR
        B       _tx_thread_context_restore  
        
_tx_ssp0Rt_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp0RtISR
        B       _tx_thread_context_restore  
        
_tx_ssp0Ror_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp0RorISR
        B       _tx_thread_context_restore  
        
_tx_ssp0tx_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp0txISR
        B       _tx_thread_context_restore  
        
_tx_ssp0Rx_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp0RxISR
        B       _tx_thread_context_restore  
        
_tx_ssp0Main_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp0MainISR
        B       _tx_thread_context_restore  
        
_tx_wdog_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __wdogISR
        B       _tx_thread_context_restore  
        
_tx_uart0ModemStatus_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart0ModemStatusISR
        B       _tx_thread_context_restore  
        
_tx_uart0Recv_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart0RecvISR
        B       _tx_thread_context_restore  
        
_tx_uart0Transmit_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart0TransmitISR
        B       _tx_thread_context_restore  
        
_tx_uart0RecvTimeout_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart0RecvTimeoutISR
        B       _tx_thread_context_restore  
        
_tx_uart0CombinedError_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart0CombinedErrorISR
        B       _tx_thread_context_restore  
        
_tx_uart0Combined_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart0CombinedISR
        B       _tx_thread_context_restore  
        
_tx_cryptoMpm_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoMpmISR
        B       _tx_thread_context_restore  
        
_tx_cryptoEa_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoEaISR
        B       _tx_thread_context_restore  
        
_tx_cryptoKep_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoKepISR
        B       _tx_thread_context_restore  
        
_tx_cryptoRe_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoReISR
        B       _tx_thread_context_restore  
        
_tx_cryptoPka_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoPkaISR
        B       _tx_thread_context_restore  
        
_tx_cryptoRng_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoRngISR
        B       _tx_thread_context_restore  
        
_tx_cryptoSpacc_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoSpaccISR
        B       _tx_thread_context_restore  
        
_tx_cryptoGlbl_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cryptoGlblISR
        B       _tx_thread_context_restore  
        
_tx_timer1_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __timer1ISR
        B       _tx_thread_context_restore  
        
_tx_timer2_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __timer2ISR
        B       _tx_thread_context_restore  
        
_tx_rtcPcounter_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __rtcPcounterISR
        B       _tx_thread_context_restore  
        
_tx_rtcAlarmWu_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __rtcAlarmWuISR
        B       _tx_thread_context_restore  
        
_tx_fcSwDmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __fcSwDmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_fcInvalidAccess_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __fcInvalidAccessISR
        B       _tx_thread_context_restore  
        
_tx_cconStable_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __cconStableISR
        B       _tx_thread_context_restore  
        
_tx_gtmrTimer_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gtmrTimerISR
        B       _tx_thread_context_restore  
        
_tx_gtmrAlarm_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gtmrAlarmISR
        B       _tx_thread_context_restore  
        
_tx_DmaAcm3ch0Done_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaAcm3ch0DoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaCm3ch1Done_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaCm3ch1DoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaSsp0RxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaSsp0RxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaSsp0TxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaSsp0TxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaUart0RxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaUart0RxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaUart0TxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaUart0TxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaSsp1RxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaSsp1RxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaSsp1TxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaSsp1TxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaUart1RxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaUart1RxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaUart1TxdmaDone_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaUart1TxdmaDoneISR
        B       _tx_thread_context_restore  
        
_tx_DmaError_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __DmaErrorISR
        B       _tx_thread_context_restore  
        
_tx_uart1ModemStatus_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart1ModemStatusISR
        B       _tx_thread_context_restore  
        
_tx_uart1Recv_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart1RecvISR
        B       _tx_thread_context_restore  
        
_tx_uart1Transmit_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart1TransmitISR
        B       _tx_thread_context_restore  
        
_tx_uart1RecvTimeout_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart1RecvTimeoutISR
        B       _tx_thread_context_restore  
        
_tx_uart1CombinedError_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart1CombinedErrorISR
        B       _tx_thread_context_restore  
        
_tx_uart1Combined_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __uart1CombinedISR
        B       _tx_thread_context_restore  
        
_tx_ssp1Rt_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp1RtISR
        B       _tx_thread_context_restore  
        
_tx_ssp1Ror_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp1RorISR
        B       _tx_thread_context_restore  
        
_tx_ssp1tx_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp1txISR
        B       _tx_thread_context_restore  
        
_tx_ssp1Rx_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp1RxISR
        B       _tx_thread_context_restore  
        
_tx_ssp1Main_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __ssp1MainISR
        B       _tx_thread_context_restore  
        
_tx_adcMain_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __adcMainISR
        B       _tx_thread_context_restore  
        
_tx_sdioMain_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL     __sdioMainISR 
        B       _tx_thread_context_restore  
        
_tx_i2cMain_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __i2cMainISR
        B       _tx_thread_context_restore  
        
_tx_i2sMain_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __i2sMainISR
        B       _tx_thread_context_restore  
        
_tx_pwmMain_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __pwmMainISR
        B       _tx_thread_context_restore  
        
_tx_gtmuMain_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gtmuMainISR
        B       _tx_thread_context_restore  
        
_tx_gspiSfifo_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gspiSfifoISR
        B       _tx_thread_context_restore  
        
_tx_gspiDfifo_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __gspiDfifoISR
        B       _tx_thread_context_restore  
        
_tx_actlWwdog_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __actlWwdogISR
        B       _tx_thread_context_restore  
        
_tx_sdadcdacFifoUndrWtrMark_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __sdadcdacFifoUndrWtrMarkISR
        B       _tx_thread_context_restore  
        
_tx_sdadcdacFifoOvrWtrMark_ISR:
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      __sdadcdacFifoOvrWtrMarkISR
        B       _tx_thread_context_restore  
        
;/* Define shells for each of the unused vectors.  */
;
__tx_BadHandler:
        B   __tx_BadHandler

__tx_IntHandler:
; VOID InterruptHandler (VOID)
; {
        PUSH    {lr}
        BL  _tx_thread_context_save
        
;    /* Do interrupt handler work here */
;    /* .... */

        B       _tx_thread_context_restore
; }

__tx_SysTickHandler:
; VOID TimerInterruptHandler (VOID)
; {
;
        PUSH    {lr}
        BL      _tx_thread_context_save
        BL      _tx_timer_interrupt
        B       _tx_thread_context_restore
; }

__tx_NMIHandler:
        B   __tx_NMIHandler

__tx_DBGHandler:
        B   __tx_DBGHandler
	END
