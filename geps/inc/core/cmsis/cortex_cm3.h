#ifndef _DEVICE_CM3_H_

#define _DEVICE_CM3_H_

typedef enum IRQn
{
	/******  Cortex-M3 Processor Exceptions/Interrupt Numbers ************************************************/
	NonMaskableInt_IRQn             = -14,      /*!< 2 Non Maskable Interrupt                              */
	HardFault_IRQn                  = -13,      /*!< 3 Cortex-M3 Hard Fault Interrupt                      */
	MemoryManagement_IRQn           = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt               */
	BusFault_IRQn                   = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                       */
	UsageFault_IRQn                 = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                     */
	SVCall_IRQn                     = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                        */
	DebugMonitor_IRQn               = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt                  */
	PendSV_IRQn                     = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                        */
	SysTick_IRQn                    = -1,       /*!< 15 Cortex-M3 System Tick Interrupt                    */
	/******  STM32 specific Interrupt Numbers ****************************************************************/
	gpioPosEdge_IRQn                   = 0,       
	gpioNegEdge_IRQn                   = 1,        
	mbReceive0_IRQn,				  
	mbReceive1_IRQn,				  
	mbReceive2_IRQn,				  
	mbReceive3_IRQn,				  
	mbReceive4_IRQn,				  
	mbReceive5_IRQn,				  
	mbReceive6_IRQn,				  
	mbReceive7_IRQn,				  
	otp0StoreComplete_IRQn,			//INT 10	  
	otp1StoreComplete_IRQn,		  
	ssp0Rt_IRQn,					  
	ssp0Ror_IRQn, 				  
	ssp0tx_IRQn,					  
	ssp0Rx_IRQn,					  
	ssp0Main_IRQn,				  
	wdog_IRQn,					  
	uart0ModemStatus_IRQn,		  
	uart0Recv_IRQn,				  
	uart0Transmit_IRQn,				//INT 20	  
	uart0RecvTimeout_IRQn,		  
	uart0CombinedError_IRQn,		  
	uart0Combined_IRQn,			  
	cryptoMpm_IRQn,				  
	cryptoEa_IRQn,				  
	cryptoKep_IRQn,				  
	cryptoRe_IRQn,				  
	cryptoPka_IRQn,				  
	cryptoRng_IRQn,				  
	cryptoSpacc_IRQn, 				//INT 30	  
	cryptoGlbl_IRQn,				  
	timer1_IRQn,					  
	timer2_IRQn,					  
	rtcPcounter_IRQn, 			  
	rtcAlarmWu_IRQn,				  
	fcSwDmaDone_IRQn, 			  
	fcInvalidAccess_IRQn, 		  
	cconStable_IRQn,				  
	gtmrTimer_IRQn,				  
	gtmrAlarm_IRQn,					//INT 40		  
	DmaAcm3ch0Done_IRQn,			  
	DmaCm3ch1Done_IRQn,			  
	DmaSsp0RxdmaDone_IRQn,		  
	DmaSsp0TxdmaDone_IRQn,		  
	DmaUart0RxdmaDone_IRQn,		  
	DmaUart0TxdmaDone_IRQn,		  
	DmaSsp1RxdmaDone_IRQn,		  
	DmaSsp1TxdmaDone_IRQn,		  
	DmaUart1RxdmaDone_IRQn,		  
	DmaUart1TxdmaDone_IRQn,		  //INT 50
	DmaError_IRQn,				  
	uart1ModemStatus_IRQn,		  
	uart1Recv_IRQn,				  
	uart1Transmit_IRQn,			  
	uart1RecvTimeout_IRQn,		  
	uart1CombinedError_IRQn,		  
	uart1Combined_IRQn,			  
	ssp1Rt_IRQn,					  
	ssp1Ror_IRQn, 				  
	ssp1tx_IRQn,				//INT 60				  
	ssp1Rx_IRQn,					  
	ssp1Main_IRQn,				  
	adcMain_IRQn, 				  
	sdioMain_IRQn,				  
	i2cMain_IRQn, 				  
	i2sMain_IRQn, 				  
	pwmMain_IRQn, 				  
	gtmuMain_IRQn,				  
	gspiSfifo_IRQn,				  
	gspiDfifo_IRQn,				//INT 70		  
	actlWwdog_IRQn,				  
	sdadcdacFifoUndrWtrMark_IRQn,   
	sdadcdacFifoOvrWtrMark_IRQn	  
} IRQn_Type;

#define __NVIC_PRIO_BITS 4

#define CM3_SYSTICK_DISABLE() SysTick->CTRL &= ~1
#define CM3_SYSTICK_ENABLE() SysTick->CTRL |= 1

#endif
