#ifndef _GSN_SYS_RESET_H_
#define _GSN_SYS_RESET_H_

typedef enum GSN_RESET_REASON
{
	/*!!!NOTE: Do not change the order. The same order is used in GsnSys_Reset()*/
	/* APP */
	GSN_RESET_REASON_APP_EXCP = 1,
	GSN_RESET_REASON_APP_ASSERT,
	GSN_RESET_REASON_APP_SYSQUAL,
	GSN_RESET_REASON_APP_SW_RESET,
	GSN_RESET_REASON_APP_WATCHDOG,
	GSN_RESET_REASON_APP_FWUP,
	/*WLAN*/
	GSN_RESET_REASON_WLAN_EXCP,
	GSN_RESET_REASON_WLAN_ASSERT,
	GSN_RESET_REASON_WLAN_SYSQUAL,
	GSN_RESET_REASON_WLAN_SW_RESET,
	GSN_RESET_REASON_WLAN_WATCHDOG,
	GSN_RESET_REASON_MAX,
}GSN_RESET_REASON_T;

typedef enum GSN_RESET_TYPE
{
	GSN_RESET_TYPE_WLAN_ONLY = 0x1,
	GSN_RESET_TYPE_SYSTEM = 0x2,
	GSN_RESET_TYPE_FULL_CHIP = 0x3, /**< including RTC */
	GSN_RESET_TYPE_APP_ONLY		= 0x4,
} GSN_RESET_TYPE_T;

typedef struct GSN_SYS_RESET_WLAN_INFO
{	
    UINT8 resetType; 
    UINT8 resetReason; 
    UINT8 resetInfoSize; 
    UINT8 resetAddlInfo;
    UINT32 resetInfo[16];	
}GSN_SYS_RESET_WLAN_INFO_T;

typedef struct GSN_SYS_RESET_APP_INFO
{	
    UINT8 resetType; 
    UINT8 resetReason; 
    UINT8 resetInfoSize; 
    UINT8 resetAddlInfo;
    UINT32 resetInfo[16];	
}GSN_SYS_RESET_APP_INFO_T;

/*  !!!NOTE: Format is same for APP Reset Info and WLAN Reset info. The Interpretation should be
based on the king of reset.

GSN_SYS_RESET_APP_INFO_T and GSN_SYS_RESET_WLAN_INFO_T are same. However defined separately 
for providing inforamtion about interpretation each field*/
typedef struct GSN_SYS_RESET_INFO
{	
	union
	{
		GSN_SYS_RESET_APP_INFO_T app;
		GSN_SYS_RESET_WLAN_INFO_T wlan;
	};
}GSN_SYS_RESET_INFO_T;


VOID
GsnSys_Reset(GSN_RESET_REASON_T resetReason);

INLINE UINT32 
GSN_RESET_INFO_LOCATION_GET()
{
	GSN_SYS_RESET_INFO_T *pSysResetInfo = (GSN_SYS_RESET_INFO_T *)GSN_SYS_RESET_INFO_LOCATION_GET();
	return (UINT32)pSysResetInfo->app.resetInfo;
}
#endif
