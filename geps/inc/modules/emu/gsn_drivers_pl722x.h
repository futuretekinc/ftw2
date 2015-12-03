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
* $RCSfile: gsn_drivers_pl722x.h,v $
*
* Description : This file defines all the interface configurations needed for 
*               accessing PL722x (prolific) chip .
*******************************************************************************/

#ifndef _PL722X_H_
#define _PL722X_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
  ******************************************************************************
  *
  *  Macros
  *
  *****************************************************************************/
//<Note>: Make sure configure the MuxFn value accordingly

//Enabe debug messages in UART (Choose the UART port accordingly)
//#define PL722X_DEBUG

#ifdef PL722X_DEBUG
#define Pl722x_Printf printf
#else
#define Pl722x_Printf(...)
#endif


/**
  ******************************************************************************
  *
  *  Public data types 
  *
  *****************************************************************************/  
typedef struct PL722X_CONFIG
{
    UINT8 spiChannel;
    UINT32 csGpio;
    UINT32 rstGpio;

}PL722X_CONFIG_T;

typedef struct PL722X_PARAMS
{
    UINT8 vrms[6];
    UINT8 irms[6];
    UINT8 zccCnt[6];
    UINT8 zccStop[6];
    UINT8 zccStart[6];
    UINT8 power[6];
    UINT8 cfCnt[6];
    UINT8 targetPowerCnt[6];
    UINT8 meterConstCnt[6];
    UINT8 sampleCnt[2];
	
}PL722X_PARAMS_T;

typedef struct PL722X_ELECTRIC_UNITS
{
    float vrms;
    float irms;
    float activePower;
    float powerfactor;
    float frequency;
    float accumulateEnergy;

}PL722X_ELECTRIC_UNITS_T;

typedef struct PL722X_FW_VER
{
    UINT8 cfgDataVer[4];
	UINT8 dspCodeVer[4];
}PL722X_FW_VER_T;


typedef struct PL722X_OCP_PARAM
{
        UINT8 iaOffset[5];
	UINT8 iaGain[2];
	UINT8 sampleCnt1[2];
}PL722X_OCP_PARAM_T;

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief This structure defines the status of operation
 *
 *****************************************************************************/
typedef enum PL722X_STATUS
{
    PL722X_SUCCESS = 0,
    PL722X_FAILURE = 1
}PL722X_STATUS;


/**
  ******************************************************************************
  *
  *  Public Functions 
  *
  *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Initialize the prolific chip.
 *    1.Configure SPI mode in pl722x
 *    2.verify the SPI mode in pl722x
 * @return PL721X_STATUS
 * @note
 *****************************************************************************/
//PUBLIC PL722X_STATUS PL722X_Init (VOID);

PUBLIC PL722X_STATUS
PL722X_Init (PL722X_CONFIG_T *cofig);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Read the prolific parameters
 * @param param  - IN Parameter to be read.
 * @return PL722X_STATUS
 * @note
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_ReadParam (PL722X_PARAMS_T* param);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Read the prolific and convert it in to engineering units
 * @param elecUnits  - IN Parameter to be read.
 * @return PL722X_STATUS
 * @note
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_GetElectricUnits(PL722X_ELECTRIC_UNITS_T *elecUnits);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Read the prolific parameters
 * @param param   - IN Pointer where read parameter should be stored
 * @return PL722X_STATUS
 * @note
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_Read_FwVer (PL722X_FW_VER_T *param);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Read the prolific registers
 * @param addr         - IN Address to Read
 * @param bytesToRead  - IN Number of bytes to Read
 * @param ptr          - IN/OUT buffer pointer in which to read
 * @return PL722X_STATUS
 * @note
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_Read(UINT16 addr, UINT8 bytesToRead, UINT8 *ptr);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief write the prolific registers
 * @param addr         - IN Address to Write
 * @param bytesToWrite - IN Number of bytes to Write
 * @param ptr          - IN buffer pointer for data to Write
 * @return PL722X_STATUS
 * @note
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_Write(UINT16 addr, UINT8 bytesToWrite, UINT8 *ptr);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Close the interface
 * @note
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_Close (VOID);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Configure relay (enable/disable)
 * @param status  - enable/disbale the relay connected to pl722x
 * @note Enable/disable CFG5 (bit 5) of OffsetCFG (0x380F)
 *            If OCP happened, MCU will not be able to control the load through pl7223 until 
 *            status flag is cleared
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_ControlLoad(BOOL status);


/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Reset KWH calculation (cumilative value)
 * @note clear (1) CFG6 (bit 6) of OffsetCFG (0x380F)
 *            Set(0) CFG6 (bit 6) of OffsetCFG (0x380F)
 *****************************************************************************/
 PUBLIC PL722X_STATUS
 PL722X_ResetKWH(VOID);

/**
  ******************************************************************************
  *
  *  OCP information
  *
  *****************************************************************************/

/*
How to enable OCP (over current protection:
-------------------------------------
->Read OCP parameters (PL722X_GetOCPParams)
->Compute corresponding values for  loading time and loading current
->Configure loading current (PL722X_SetLoadingCurrent)
->Configure loading time (PL722X_SetLoadingTime)
->Enable OCP function (PL722X_EnableOCP)

when over current happens, PL7223 automatically switches off the relay (load) and set the status
register "OC_Flag (0x3024)"
OC_Flag = 0, Normal Condition
OC_Flag = 1, Over-Current Occurred


MCU shall read "OC_Flag (0x3024)" to understand the occurance periodically.
If OCP occur, the status flag will remain set until MCU clears it up. So the operation may look like
 ->mcu read OC_FLAG (PL722X_GetOCPStatus)
 ->reenable the OCP (PL722X_EnableOCP)

Note: If OCP happened, MCU will not be able to control the load through pl7223 until 
         status flag is cleared
*/

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Disable OCP (over curent protection)
 * @note Disable(0) CFG4 (bit 4) of OffsetCFG (0x380F) 
 *****************************************************************************/
PUBLIC VOID PL722X_DisableOCP(VOID);


/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Enable OCP (over curent protection)
 * @note Enable CFG4 (bit 4) of OffsetCFG (0x380F) 
 *****************************************************************************/
PUBLIC VOID PL722X_EnableOCP(VOID);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Get OCP status will return whether OCP has happened or not
 * @return status
 *               0 - Not occured
 *               1 - occured
 * @note Read register "OC_Flag (0x3024)".
              OC_Flag = 0, Normal Condition
              OC_Flag = 1, Over-Current Occurred
 *****************************************************************************/
PUBLIC BOOL PL722X_GetOCPStatus(VOID);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Get OCP parameters required for setting loading current and loading time
 * @param param     -IN pointer where OCP params read needs to be copied
 * @note please find the formula for computing loading current and time
 *            loading curent: STPUTH rule = {{(IA_rms - IA_offset ) / (IA_gain / 2^20 ) } ^2 } * (SampleCnt_1)
 *            loading time: STTH rule = {{(IA_rms - IA_offset ) / (IA_gain / 2^20 ) } ^2 } *( SampleCnt_ADC_Clock) *( T_sc)
 *     
 *            so parameters needed are
 *            -IA_OFFSET (0x3841 - 0x3845) - 5 Bytes
 *            -IA_GAIN (0x3822 - 0x3823) - 2 Bytes
 *            -SAMPLE_CNT_1 (0x381A - 0x381B) - 2 Bytes
 *            -SampleCnt_ADC_Clock = 4000000/1024 = 3906 (d)
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_GetOCPParams(PL722X_OCP_PARAM_T *param);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Set loading current
 * @param ptr     -IN value which should be passed
 * @note Function copies 5 bytes to address 0x3828. Make sure ptr[0] is the lower order byte
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_SetLoadingCurrent(UINT8 *ptr);

/**
 *****************************************************************************
 * @ingroup prolific
 * @brief Set loading time
 * @param ptr      -IN value which should be passed
 * @note Function copies 6 bytes to address 0x3858. Make sure ptr[0] is the lower order byte
 *****************************************************************************/
PUBLIC PL722X_STATUS PL722X_SetLoadingTime(UINT8 *ptr);

#ifdef  __cplusplus
}
#endif

#endif //_PL722X_H_


