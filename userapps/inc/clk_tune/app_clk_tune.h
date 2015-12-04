#define APP_PTAT_SAR_ADC_SET0_MASK 0x000003ff00000000
#define APP_PTAT_SAR_ADC_SET0_BITOFFSET 32
#define APP_PTAT_SAR_SLOPE_MASK 0x0000FC0000000000
#define APP_PTAT_SAR_SLOPE_BITOFFSET 42

#define APP_XTAL_C1_MASK 0x00000000000000ff
#define APP_XTAL_C1_BITOFFSET 0
#define APP_XTAL_C2_MASK 0x000000000000ff00
#define APP_XTAL_C2_BITOFFSET 8

#define APP_LP_RC_CL_MASK 0x0000000000ff0000
#define APP_LP_RC_CL_BITOFFSET 16
#define APP_LP_RC_RL_MASK 0x00000000ff000000
#define APP_LP_RC_RL_BITOFFSET 24

#define APP_HS_XTAL_C1_MASK 0x0000000000ff0000
#define APP_HS_XTAL_C1_BITOFFSET 16
#define APP_HS_XTAL_C2_MASK 0x00000000ff000000
#define APP_HS_XTAL_C2_BITOFFSET 24

#define APP_ATE_CAL_DX_REF_TRIM_MASK 0x000000000000000f
#define APP_ATE_CAL_DX_REF_TRIM_BIT_OFFSET 0

#define APP_ATE_CAL_N_FINE_MASK 0x0000000000000f00
#define APP_ATE_CAL_N_FINE_BIT_OFFSET 8

#define APP_ATE_CAL_N_COURSE_MASK 0x000000000000f000
#define APP_ATE_CAL_N_COURSE_BIT_OFFSET 12





typedef struct LP_XTAL_DELTA
{
    INT32 temperature;
    INT8 delta;
    INT32 perDegreeAdj;
}LP_XTAL_DELTA_T;

typedef struct LP_RC_DELTA
{
    INT32 temperature;
    INT8 delta;
    INT32 perDegreeAdj;
}LP_RC_DELTA_T;

typedef struct HS_XTAL_DELTA
{
    INT32 temperature;
    INT8 delta;
    INT32 perDegreeAdj;
}HS_XTAL_DELTA_T;

typedef struct HS_RC_DELTA
{
    INT32 temperature;
    INT16 delta;
    INT32 perDegreeAdj;
}HS_RC_DELTA_T;


UINT32 App_AdcOpen();

UINT32 App_AdcClose();

INT32
App_TemperatureGet();

INT32 App_TuneLpXtal(int temp);

INT32 App_TuneLpRc(int temp);

INT32 App_TuneHsXtal(int temp);

INT32 App_TuneHsRc(INT32 temp);

INT32
App_TemperatureGet();

UINT16 App_PaVoltGet();

VOID AppS2w_ClkCalibCb(VOID* context,
    GSN_SOFT_TMR_HANDLE_T  timerHandle);

