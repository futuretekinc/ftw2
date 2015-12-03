#ifndef _GSN_WIF_COMMON_H_
#define _GSN_WIF_COMMON_H_

/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnWif GSN WLAN Firmware Interface (WIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *    
 *		Whole GsnWif module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}   END of coresvcdoc.
 *****************************************************************************/

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief HI Class Definition
 *****************************************************************************/
typedef enum GSN_WIF_HI_CLASS
{
	GSN_WIF_HI_CLASS_DCNF/*Not defined yet*/,
	GSN_WIF_HI_CLASS_WLAN_CTRL 	= GSN_WIF_API_TYPE_WLAN_CTL,
	GSN_WIF_HI_CLASS_SYS_CTRL 	= GSN_WIF_API_TYPE_SYS_CTL,	
	GSN_WIF_HI_CLASS_154_CTRL 	= GSN_WIF_API_TYPE_154_CTL,
	GSN_WIF_HI_CLASS_CAL_CTL 	= GSN_WIF_API_TYPE_CAL_CTL,
	GSN_WIF_HI_CLASS_ISOTX_CTL	= GSN_WIF_API_TYPE_ISOTX_CTL,
	GSN_WIF_HI_CLASS_DATA 		= GSN_WIF_API_TYPE_DATA,
	GSN_WIF_HI_CLASS_154_DATA 	= GSN_WIF_API_TYPE_154_DATA,
	GSN_WIF_HI_CLASS_UNASSOC_DATA = GSN_WIF_API_TYPE_WLAN_UNASSOC_DATA,
}GSN_WIF_HI_CLASS_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief Mask used to extract API type and API from message ID
 * 
 *	  Message ID is a 16 bit object. The first 10 bits indicates the WIF API and the next 6 bits indicate the
 * WIF API type
*****************************************************************************/
/** @{ */

#define GSN_WIF_MSG_API_TYPE_MASK		0xF600 /**< 6 MSB bits indicates the API type*/
#define GSN_WIF_MSG_API_MASK			0x03FF /**<Last 10 LSB bits indicates the API*/
#define GSN_WIF_HI_MSG_LEN_MASK			0x7FF /**< 11 bits of the length filed indicates the length of
													the message*/

/** @} */

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief maximum SYS and WLAN indication Number
 * 
 *****************************************************************************/
/** @{ */

#define GSN_WIF_SYS_CTRL_MAX_IND 	64/*((GSN_WIF_API_SYS_OTP_READ_RSP & GSN_WIF_MSG_API_MASK) - 	\
									  GSN_WIF_IND_RSP_MSG_TYPE + 1)*/
									  
#define GSN_WIF_WLAN_CTRL_MAX_IND	128/*((GSN_WIF_API_WLAN_UNASSOC_RX_CONFIG_RSP & GSN_WIF_MSG_API_MASK) -	\
									  GSN_WIF_IND_RSP_MSG_TYPE + 1)*/

#define GSN_WIF_CAL_CTRL_MAX_IND	32/*((GSN_WIF_API_CAL_RUN_RSP & GSN_WIF_MSG_API_MASK) -	\
									  GSN_WIF_IND_RSP_MSG_TYPE + 1)		*/							  

#define GSN_WIF_ISOTX_CTRL_MAX_IND	32/*((GSN_WIF_API_ISOTX_BDAT_IND & GSN_WIF_MSG_API_MASK) -	\
									  GSN_WIF_IND_RSP_MSG_TYPE + 1)	*/

/** @} */


/*****************************************************************************
 * Public	Definitions
 ****************************************************************************/
 
/**
 *******************************************************************************
 * @ingroup GsnWifApi
 * @brief Boot indication  CB definition.
 *******************************************************************************/
typedef VOID (*GSN_WIF_INIT_CB_T)(VOID* ctx, GSN_STATUS status);

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF "Sys Control " indication Cb.
 *	  Callback definition for the Sys Control indication callback. 
 * @note 
 * 	  see GsnWif_SysCtrlIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_SYS_CTRL_IND_CB_T )(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
													    VOID *pMsg);

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF "Sys Control " indication Cb.
 *	  Callback definition for the Sys Control indication callback. 
 * @note 
 * 	  see GsnWif_SysCtrlIndCbReg
 *****************************************************************************/
typedef VOID ( *GSN_WIF_RESET_IND_CB_T )(VOID *pCtx, UINT16 msgLen, VOID *pMsg);

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF "Wlan Control " indication Cb.
 *	  Callback definition for the Wlan Control indication callback. 
 * @note 
 *	  see GsnWif_WlanCtrlIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_WLAN_CTRL_IND_CB_T )(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
													    VOID *pMsg);
/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF "Wlan Control " indication Cb.
 *	  Callback definition for the Wlan Control indication callback. 
 * @note 
 *	  see GsnWif_WlanCtrlIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_CAL_CTRL_IND_CB_T )(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
													    VOID *pMsg);

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF "Wlan Control " indication Cb.
 *	  Callback definition for the Wlan Control indication callback. 
 * @note 
 *	  see GsnWif_WlanCtrlIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_ISOTX_CTRL_IND_CB_T )(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
													    VOID *pMsg);

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF "Wlan Control " indication Cb.
 *	  Callback definition for the Wlan Control indication callback. 
 * @note 
 *	  see GsnWif_WlanCtrlIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_DOT154_CTRL_IND_CB_T )(VOID *pCtx, UINT16 msgId, UINT16 msgLen,
													    VOID *pMsg);

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF Data	indication Cb.
 *		Callback definition for the Data indication callback. 
 * @note
 *		see GsnWif_DataIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_DATA_IND_CB_T )( VOID *pCtx, UINT16 status, UINT8 dataClass,
												UINT16 msgLen, VOID *pMsg );

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF Data	indication Cb.
 *		Callback definition for the Data indication callback. 
 * @note
 *		see GsnWif_DataIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_ISOTX_DATA_IND_CB_T )( VOID *pCtx, UINT16 status, UINT16 msgLen, 
														VOID *pMsg );

/**
 *****************************************************************************
 * @ingroup GsnWif
 * @brief GSN WLAN IF Data	indication Cb.
 *		Callback definition for the Data indication callback. 
 * @note
 *		see GsnWif_DataIndCbReg
 *****************************************************************************/
typedef GSN_STATUS ( *GSN_WIF_DOT154_DATA_IND_CB_T )( VOID *pCtx, UINT32 msgId, UINT16 msgLen, 
															VOID *pMsg );

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief System control indication call back info structure
 *		This structure has the systen control indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/
typedef struct GSN_WIF_SYS_CTRL_IND_CB_INFO
{
	GSN_WIF_SYS_CTRL_IND_CB_T cb;
	VOID * ctx;
}GSN_WIF_SYS_CTRL_IND_CB_INFO_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief System control indication call back info structure
 *		This structure has the systen control indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/
typedef struct GSN_WIF_RESET_IND_CB_INFO
{
	GSN_WIF_RESET_IND_CB_T cb;
	VOID * ctx;
}GSN_WIF_RESET_IND_CB_INFO;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief Wlan control indication call back info structure
 *		This structure has the wlan control indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/	
typedef struct GSN_WIF_WLAN_CTRL_IND_CB_INFO
{
	GSN_WIF_WLAN_CTRL_IND_CB_T cb;
	VOID *ctx;
}GSN_WIF_WLAN_CTRL_IND_CB_INFO_T;

/**
*****************************************************************************
* @internal
* @ingroup GsnWif
* @brief Calibration control indication call back info structure
*		This structure has the Calibration control indication call back and the ponter to to context to be passed 
* to call back.
* @note
*****************************************************************************/ 
typedef struct GSN_WIF_CAL_CTRL_IND_CB_INFO
{
	GSN_WIF_CAL_CTRL_IND_CB_T cb;
	VOID *ctx;
}GSN_WIF_CAL_CTRL_IND_CB_INFO_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief System control indication call back info structure
 *		This structure has the systen control indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/
typedef struct GSN_WIF_ISOTX_CTRL_IND_CB_INFO
{
	GSN_WIF_ISOTX_CTRL_IND_CB_T cb;
	VOID * ctx;
}GSN_WIF_ISOTX_CTRL_IND_CB_INFO_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief System control indication call back info structure
 *		This structure has the systen control indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/
typedef struct GSN_WIF_DOT154_CTRL_IND_CB_INFO
{
	GSN_WIF_DOT154_CTRL_IND_CB_T cb;
	VOID * ctx;
}GSN_WIF_DOT154_CTRL_IND_CB_INFO_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief Data indication call back info structure
 *		This structure has the Data indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/	
typedef struct GSN_WIF_DATA_IND_CB_INFO
{
	GSN_WIF_DATA_IND_CB_T cb;
	VOID *ctx;
}GSN_WIF_DATA_IND_CB_INFO_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief Data indication call back info structure
 *		This structure has the Data indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/	
typedef struct GSN_WIF_ISOTX_DATA_IND_CB_INFO
{
	GSN_WIF_ISOTX_DATA_IND_CB_T cb;
	VOID *ctx;
}GSN_WIF_ISOTX_DATA_IND_CB_INFO_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWif
 * @brief Data indication call back info structure
 *		This structure has the Data indication call back and the ponter to to context to be passed 
 * to call back.
 * @note
 *****************************************************************************/	
typedef struct GSN_WIF_DOT154_DATA_IND_CB_INFO
{
	GSN_WIF_DOT154_DATA_IND_CB_T cb;
	VOID *ctx;
}GSN_WIF_DOT154_DATA_IND_CB_INFO_T;


#endif
