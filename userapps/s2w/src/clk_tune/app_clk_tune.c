#include "gsn_includes.h"
#include "drivers/clk_ctl/gsn_clk_ctl.h"
#include "clk_tune/app_clk_tune.h"
#include "main/app_main_ctx.h"

LP_XTAL_DELTA_T lpXtalDelta[10] = 
{
    { 85, 0x80, -2457},
    { 70, 0xA4, -4027},
    { 55, 0xDF, -2798},
    { 40, 0x08, 0},
    { 25, 0x08, 819},
    { 15, 0x00, 2594},
    { 0 , 0xDA, 2662},
    {-15, 0xB3, 2935},
    {-30, 0x88, 819},
    {-40, 0x80, 0}
};

LP_RC_DELTA_T lpRcDelta[10] = 
{
    {85, -1, -68},
    {70, 0, 0},
    {55, 0, 0},
    {40, 0, 0},
    {25, 0, 0},
    {15, 0, 0},
    {0, 0, 136},
    {-15, (INT8)-2, 68},
    {-30, (INT8)-3, 204},
    {-40, (INT8)-5, 0}
};

HS_XTAL_DELTA_T hsXtalDelta[11] = 
{
    {-40, 0x20, -1228},
    {-35, 0x26, -614},
    {-25, 0x2c, 409},
    {-15, 0x2a, 614},
    {-5, 0x24, 1228},
    {5, 0x18, 1228},
    {15, 0x0c,1126},
    {25, 0x01, 921},
    {35, 0xf8, 614},
    {45, 0xf2, 102},
    {55, 0xf1, 0}
};

HS_RC_DELTA_T hsRcDlta[6] = 
{
	{85, 0xfffb, 34},
	{55, 0xfffa, -204},
	{25, 0x0, -450},
	{0, 0x00b, -655},
	{-25, 0x01b, -1024},
	{-40, 0x02a, 0}
};

extern UINT32 app_adc_data[];
extern APP_MAIN_CTX_T appCtx;
extern GSN_CLK_CTL_CM3_CLK_CFG_T cm3ClkCfg;

UINT32 App_AdcOpen()
{
    GSN_CLK_CTL_CTX_T *pClkCtlCtx = GsnClkCtl_CtxGet();

    GsnClkCtl_ClkSrcEnable(pClkCtlCtx, GSN_CLK_CTL_CLK_SRC_HS_XTAL);

    CLKCTL_ADC_CLK_SEL_VAL_SET(CLKCTL,1);
    CLKCTL_ADC_STEP_SET(CLKCTL,0x333333);
    CLKCTL_GTMU_NCO_EN_SET(CLKCTL,0x01);
    CLKCTL_ADC_NCO_EN_SET(CLKCTL, NCO_EN);

    for(UINT8 ik=0;ik<250;ik++);

    AADC_IRQ_FIFO_THRESH_SET(COMMON_AADC,1);

    AADC_PCYCLES_SET(COMMON_AADC,200);

    AADC_SCYCLES_SET(COMMON_AADC,1);

    *(int *)(0x40140404) = (1 << 10);
    
    AADC_PD_POL_SET(COMMON_AADC);
    AADC_ADC_EN_SET(COMMON_AADC);
    return 0;
}



UINT32 App_AdcClose()
{
    GSN_CLK_CTL_CTX_T *pClkCtlCtx = GsnClkCtl_CtxGet();

    AADC_ADC_EN_CLEAR(COMMON_AADC);
    GsnClkCtl_ClkSrcDisable(pClkCtlCtx, GSN_CLK_CTL_CLK_SRC_HS_XTAL);
    CLKCTL_ADC_CLK_SEL_VAL_SET(CLKCTL,0);
    CLKCTL_GTMU_NCO_EN_SET(CLKCTL,0);
    CLKCTL_ADC_NCO_EN_SET(CLKCTL, 0);
    return 0;
}

UINT32
Adc_Value_Get(UINT8 channel, BOOL avg)
{
    UINT32 data=0, i;
    
    if(avg)
    {
        for(i = 0; i < 8; i++)
        {
            AADC_CHSEL_SET( COMMON_AADC, channel );
            AADC_SINGLE_SET( COMMON_AADC,1 );
            while( AADC_SINGLE_GET(COMMON_AADC) == 1);
            data += AADC_DATA_GET(COMMON_AADC) & 0xFFF;
        }
        return data/8;
    }
    else
    {
        AADC_CHSEL_SET( COMMON_AADC, channel );
        AADC_SINGLE_SET( COMMON_AADC,1 );
        while( AADC_SINGLE_GET(COMMON_AADC) == 1);
        data = AADC_DATA_GET(COMMON_AADC) & 0xFFF;
        return data;
    }
}


INT32
App_TemperatureGet()
{
    UINT8 data[8] ={0};
    UINT16 dataLen=0;
    INT32 Do_ref= 0, slope = 0x1c;    //Default values
    INT32 TsOut, Tref = 25, delta, Tm;
    UINT32 nCoarse, nFine, trim;
    INT32 buf[32], i, j, buf_temp, sum = 0;
    if(GSN_SUCCESS == GsnOtpMm_Read(GSN_OTP_MM_ID_ATE_CAL_DATA,GSN_OTP_MM_VER_UNKNOWN,
                                  &dataLen, data))
    {
        ULONG64 otpData = *(ULONG64 *)data;
        Do_ref = (otpData & APP_PTAT_SAR_ADC_SET0_MASK) >> APP_PTAT_SAR_ADC_SET0_BITOFFSET;
        Do_ref = Do_ref << 22;
        Do_ref = Do_ref >> 22;
        slope = (otpData & APP_PTAT_SAR_SLOPE_MASK) >> APP_PTAT_SAR_SLOPE_BITOFFSET;
        trim = (otpData & APP_ATE_CAL_DX_REF_TRIM_MASK) >> APP_ATE_CAL_DX_REF_TRIM_BIT_OFFSET;
        nFine = (otpData & APP_ATE_CAL_N_FINE_MASK) >> APP_ATE_CAL_N_FINE_BIT_OFFSET;
        nCoarse = (otpData & APP_ATE_CAL_N_COURSE_MASK) >> APP_ATE_CAL_N_COURSE_BIT_OFFSET;
        //S2w_Printf("Do_ref: %d, slope: %d, nFine %d, nCoarse %d, Trim %d\n\r", Do_ref, slope, nFine, nCoarse, trim);
    } 

    RTC_SX_EN_BIAS_F_SET(RTC);
    RTC_SX_EN_U_LDO_F_SET (RTC);
    RTC_SX_EN_TS_F_SET(RTC);

    AADC_ADCEN_TRIM_SET( COMMON_AADC );
    AADC_ADC_REFTRIM_SET( COMMON_AADC, trim );
    CLKCTL_ACM3_BUS_FORCE_SET(CLKCTL);
    App_AdcOpen();
	
	RTC_SX_TS_GAIN_SET(RTC,0);
	RTC_SX_TSADJ_SET(RTC,(nCoarse << 4) | nFine);

    /* read 16 samples */
    for(UINT8 count=0;count<16;count++)
    {
	    UINT32 temp=0,temp1=0;

        RTC_SX_OFFSET_SNS_CLEAR(RTC);
        while(RTC_SX_OFFSET_SNS_GET(RTC));
        temp =Adc_Value_Get(0xf7, TRUE);
        //S2w_Printf("\n\rSNS0: %d", temp); 

        RTC_SX_OFFSET_SNS_SET(RTC);
        while(!RTC_SX_OFFSET_SNS_GET(RTC));
        temp1=Adc_Value_Get(0xf7, TRUE);
        //S2w_Printf(" SNS1: %d", temp1); 
        //S2w_Printf(" Diff:%d",temp1-temp);
        buf[count] = temp1-temp;
#if 0
		TsOut = (temp1-temp) - Do_ref;
		delta = (-TsOut * slope) >> 9;
		S2w_Printf(" Delta: % d", delta);
                Tm = delta + Tref;
		S2w_Printf(" Tm: %d\n\r", Tm);
#endif
   }

   /* Sort readings */
   for( i=0; i<15 ; i++ )
   { 
      for( j=15; j>i; j-- )
      {
        if(buf[j] > buf[j-1])
        {
          buf_temp = buf[j];
          buf[j] = buf[j-1];
          buf[j-1] = buf_temp;
        }
      }
    }

    /* Discard 4 lower and 4 upper readings. Take avg of midle 8 samples */
    for( i=4;i<12;i++)
    {
      sum+=buf[i];
    }  
    TsOut = sum/8;
    //S2w_Printf("\n\rAfter taking average of middle 8 samples %d\n\r", TsOut);
    TsOut = TsOut - Do_ref;
    delta = (-TsOut * slope) >> 9;
    //S2w_Printf("Delta %d\n\r", delta);
    Tm = delta + Tref;
    //S2w_Printf("Tm: %d\n\r", Tm);

    RTC_SX_EN_BIAS_F_CLEAR(RTC);
    RTC_SX_EN_U_LDO_F_CLEAR (RTC);
    RTC_SX_EN_TS_F_CLEAR(RTC);
    
    App_AdcClose();
    CLKCTL_ACM3_BUS_FORCE_CLEAR(CLKCTL);
    return Tm;
}

UINT16 App_PaVoltGet()
{
	UINT16 adcVal;

    RTC_SX_SX_EN_BO_SAR_SET(RTC);
    App_AdcOpen();
    Adc_Value_Get(0xf6, FALSE);
    adcVal = Adc_Value_Get(0xf6, FALSE);
	//S2w_Printf("\n\rraw val: %x\n\r", adcVal);
	App_AdcClose();
	RTC_SX_SX_EN_BO_SAR_CLEAR(RTC);
	return (3300 * adcVal) >> 12;
}
INT32 App_TuneLpXtal(int temp)
{
    INT32 temperature;
    UINT8 data[255] ={0};
    UINT16 dataLen=0;
    INT32 xTalC1 = 0, xTalC2 = 0;
    if(GSN_SUCCESS == GsnOtpMm_Read(GSN_OTP_MM_ID_MODULE_CAL_DATA, GSN_OTP_MM_VER_UNKNOWN,
                                  &dataLen, data))
    {
        ULONG64 otpData = *(ULONG64 *)data;
        xTalC1 = (otpData & APP_XTAL_C1_MASK) >> APP_XTAL_C1_BITOFFSET;
        xTalC2 = (otpData & APP_XTAL_C2_MASK) >> APP_XTAL_C2_BITOFFSET;
    } 

    temperature = temp;

    /* get delta from lookup table and write that into SX_Cx_1_ctrl and SX_Cx_2 */
    
    for( INT32 i = 0; i < 9; i++)
    {
        if((temperature <= lpXtalDelta[i].temperature) && (temperature >= lpXtalDelta[i + 1].temperature))
        {
            //float deltaPerDegreee = (float)(lpXtalDelta[i].delta - lpXtalDelta[i + 1].delta) / (float)( lpXtalDelta[i].temperature - lpXtalDelta[i + 1].temperature);
            int tempDiff = temperature - lpXtalDelta[i + 1].temperature;
            if(tempDiff < 0)
                tempDiff = (~tempDiff + 1);
            //INT8 delta = (tempDiff * deltaPerDegreee) + lpXtalDelta[i + 1].delta;
            INT8 delta = ((tempDiff * lpXtalDelta[i].perDegreeAdj) >> 10) + lpXtalDelta[i + 1].delta;
            RTC_SX_CX_1_CTRL_SET(RTC, xTalC1 + delta);
            RTC_SX_CX_2_CTRL_SET(RTC, xTalC2 + delta);
            //S2w_Printf("\n\ri LpXtal: %d, %x", i + 1, delta);
            return 0;
        }
    }
    return 0;
}






INT32 App_TuneLpRc(int temp)
{
    INT32 temperature;
    UINT8 data[255] ={0};
    UINT16 dataLen=0;
    INT32 lpRcCL = 0x20, lpRcRL = 0xE0;    //Default values
    if(GSN_SUCCESS == GsnOtpMm_Read(GSN_OTP_MM_ID_ATE_CAL_DATA,GSN_OTP_MM_VER_UNKNOWN,
                                  &dataLen, data))
    {
        ULONG64 otpData = *(ULONG64 *)data;
        lpRcCL = (otpData & APP_LP_RC_CL_MASK) >> APP_LP_RC_CL_BITOFFSET;
        lpRcRL = (otpData & APP_LP_RC_RL_MASK) >> APP_LP_RC_RL_BITOFFSET;
    } 

    temperature = temp;
    /* get delta from lookup table and write that into (CL+ delta) -> SX_CL_ctrl  and (RL+ delta) -> SX_RL_ctrl  */
    
    for( INT32 i = 0; i < 9; i++)
    {
        if((temperature <= lpRcDelta[i].temperature) && (temperature >= lpRcDelta[i + 1].temperature))
        {
            //float deltaPerDegreee = (float)(lpRcDelta[i].delta - lpRcDelta[i + 1].delta) / (float)( lpRcDelta[i].temperature - lpRcDelta[i + 1].temperature);
            int tempDiff = temperature - lpRcDelta[i + 1].temperature;
            if(tempDiff < 0)
                tempDiff = (~tempDiff + 1);
            //INT8 delta = (tempDiff * deltaPerDegreee) + lpRcDelta[i + 1].delta;
            INT8 delta = ((tempDiff * lpRcDelta[i].perDegreeAdj) >> 10) + lpRcDelta[i + 1].delta;
            
            RTC_SX_CL_CTRL_SET(RTC, (lpRcCL + delta));
            RTC_SX_RL_CTRL_SET(RTC, (lpRcRL + delta));
            //S2w_Printf("\n\ri LpRc: %d, %x", i + 1, delta);
            return 0;
        }
    }
    return 0;
}

INT32 App_TuneHsXtal(int temp)
{
	INT32 temperature;
	UINT8 data[255] ={0};
	UINT16 dataLen=0;
	INT32 C1 = 0, C2 = 0;    //Default values
	if(GSN_SUCCESS == GsnOtpMm_Read(GSN_OTP_MM_ID_MODULE_CAL_DATA, GSN_OTP_MM_VER_UNKNOWN,
								  &dataLen, data))
	{
		ULONG64 otpData = *(ULONG64 *)data;
		C1 = (otpData & APP_HS_XTAL_C1_MASK) >> APP_HS_XTAL_C1_BITOFFSET;
		C2 = (otpData & APP_HS_XTAL_C2_MASK) >> APP_HS_XTAL_C2_BITOFFSET;
	} 

	temperature = temp;
	/* get delta from lookup table and write that into (C1+ delta) -> RTC_CX_C1_ctrl   and (C1+ delta) -> RTC_CX_C2_ctrl  */
	
	for(INT32 i = 0; i < 10; i++)
	{
	    if( (temperature >= hsXtalDelta[i].temperature) && (temperature <= hsXtalDelta[i + 1].temperature))
	    {
	        //float deltaPerDegreee = (float)(hsXtalDelta[i].delta - hsXtalDelta[i + 1].delta) / (float)( hsXtalDelta[i].temperature - hsXtalDelta[i + 1].temperature);
            int tempDiff = temperature - hsXtalDelta[i + 1].temperature;
            if(tempDiff < 0)
                tempDiff = (~tempDiff + 1);
            //INT8 delta = (tempDiff * deltaPerDegreee) + hsXtalDelta[i + 1].delta;
            INT8 delta = ((tempDiff * hsXtalDelta[i].perDegreeAdj) >> 10) + hsXtalDelta[i + 1].delta;
	        RTC_CX_C1_CTRL_SET(RTC, (C1 + delta));
            RTC_CX_C2_CTRL_SET(RTC, (C2 + delta));
            //S2w_Printf("\n\ri HsXtal: %d, %x", i + 1, delta);
            return 0;
	    }
	}
	RTC_CX_C1_CTRL_SET(RTC, (C1 + hsXtalDelta[10].delta));
    RTC_CX_C2_CTRL_SET(RTC, (C2 + hsXtalDelta[10].delta));
	return 0;
}





INT32 App_TuneHsRc(INT32 temp)
{ 
    INT32 temperature;
    RTC_CX_CAL_OFF_VALUE_SET(RTC, 0);
    GsnClkCtl_HsRcCal(&cm3ClkCfg);
    //S2w_Printf("\n\rCalOut: %d", RTC_CX_CAL_EXT_INPUT_GET(RTC));
    temperature = temp;

    if(temperature >= 85)
    {
        RTC_CX_CAL_OFF_VALUE_SET(RTC, hsRcDlta[0].delta);
    }
    for(INT32 i = 0; i < 5; i++)
    {
        if((temperature <= hsRcDlta[i].temperature) && (temperature >= hsRcDlta[i + 1].temperature))
        {
            //float deltaPerDegreee = (float)(hsRcDlta[i].delta - hsRcDlta[i + 1].delta) / (float)( hsRcDlta[i].temperature - hsRcDlta[i + 1].temperature);
            int tempDiff = temperature - hsRcDlta[i + 1].temperature;
            if(tempDiff < 0)
                tempDiff = (~tempDiff + 1);
            //INT16 delta = (tempDiff * deltaPerDegreee) + hsRcDlta[i + 1].delta;
            INT16 delta = ((tempDiff * hsRcDlta[i].perDegreeAdj) >> 10) + hsRcDlta[i + 1].delta;
            
            RTC_CX_CAL_OFF_VALUE_SET(RTC, delta);
            //S2w_Printf("\n\ri HsRc: %d, %x", i + 1, delta);
            return 0;
        }
    }
    RTC_CX_CAL_OFF_VALUE_SET(RTC, hsRcDlta[5].delta);
    return 0;
}

VOID AppS2w_ClkCalibCb(VOID* context,
    GSN_SOFT_TMR_HANDLE_T  timerHandle)
{
    INT32 temperature;

    temperature = App_TemperatureGet();
    App_TuneLpXtal(temperature);
    App_TuneLpRc(temperature);
    App_TuneHsXtal(temperature);
    App_TuneHsRc(temperature);
}

