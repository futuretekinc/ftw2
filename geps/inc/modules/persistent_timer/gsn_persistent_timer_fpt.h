typedef VOID 
(* GsnPersistTmr_Init_FP_T)( VOID* pNvRamLoc, VOID *pNvdsLoc, UINT32 numOfVarTimer, 
    UINT8 numOfConstTimer, GSN_SOFT_TMR_T *pSoftTmrStructTbl );

typedef VOID 
( *GsnPersistTmr_Restore_FP_T)( VOID );    

typedef BOOL 
( *GsnPersistTmr_Store_FP_T)( VOID );

typedef GSN_STATUS 
( *GsnPersistTmr_Create_FP_T)( UINT32 timerId, GSN_P_TIMER_TYPE_T type, ULONG64 period, 
    GSN_SOFT_TMR_CBR_T cb, VOID* context, BOOL autoStart );

typedef GSN_STATUS 
(* GsnPersistTmr_Delete_FP_T)( UINT32 timerId );

typedef GSN_STATUS 
( * GsnPersistTmr_Start_FP_T)( UINT32 timerId );

typedef GSN_STATUS 
( *GsnPersistTmr_Stop_FP_T)( UINT32 timerId );

typedef GSN_STATUS 
( *GsnPersistTmr_ReStart_FP_T)( UINT32 timerId, ULONG64 period,
    GSN_P_TMR_REF_TIME_T refTime );

typedef ULONG64
(*GsnPersistTmr_SystemTimeAtExpire_FP_T)( UINT32 timerId );    

typedef ULONG64
( *GsnPersistTmr_RemainingTimeGet_FP_T)( UINT32 timerId );

typedef ULONG64
( *GsnPersistTmr_MinExpireTime_FP_T)();

typedef BOOL
(*GsnPersistTmr_IsActive_FP_T)( UINT32 timerId );

typedef ULONG64
(*GsnPersistTmr_PeriodGet_FP_T)( UINT32 timerId );

typedef ULONG64
(*GsnPersistTmr_DfltPeriodGet_FP_T)( UINT32 timerId );

typedef VOID
( *GsnPersistTmr_DfltPeriodSet_FP_T)( UINT32 timerId, ULONG64 period );

extern _RPST_ GsnPersistTmr_Init_FP_T GsnPersistTmr_Init_FP;
extern _RPST_ GsnPersistTmr_Restore_FP_T GsnPersistTmr_Restore_FP;
extern _RPST_ GsnPersistTmr_Store_FP_T GsnPersistTmr_Store_FP;
extern _RPST_ GsnPersistTmr_Create_FP_T GsnPersistTmr_Create_FP;
extern _RPST_ GsnPersistTmr_Delete_FP_T GsnPersistTmr_Delete_FP;
extern _RPST_ GsnPersistTmr_Start_FP_T GsnPersistTmr_Start_FP;
extern _RPST_ GsnPersistTmr_Stop_FP_T GsnPersistTmr_Stop_FP;
extern _RPST_ GsnPersistTmr_ReStart_FP_T GsnPersistTmr_ReStart_FP;
extern _RPST_ GsnPersistTmr_SystemTimeAtExpire_FP_T GsnPersistTmr_SystemTimeAtExpire_FP;
extern _RPST_ GsnPersistTmr_RemainingTimeGet_FP_T GsnPersistTmr_RemainingTimeGet_FP;
extern _RPST_ GsnPersistTmr_MinExpireTime_FP_T GsnPersistTmr_MinExpireTime_FP;
extern _RPST_ GsnPersistTmr_PeriodGet_FP_T GsnPersistTmr_PeriodGet_FP;
extern _RPST_ GsnPersistTmr_IsActive_FP_T GsnPersistTmr_IsActive_FP;
extern _RPST_ GsnPersistTmr_DfltPeriodGet_FP_T GsnPersistTmr_DfltPeriodGet_FP;
extern _RPST_ GsnPersistTmr_DfltPeriodSet_FP_T GsnPersistTmr_DfltPeriodSet_FP;
