/*****************************************************************
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
* $RCSfile: s2w_otp.c,v $
*
* Description : s2w command interprter file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include "time.h"
#include <ctype.h>
#include <string.h>
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "hal/s2w_timer.h"
#include "parser/s2w_parse.h"
#include "parser/s2w_process.h"
#include "parser/s2w_command.h"
#include "hal/s2w_net.h"
#include "app_defines_builder.h"
#include "hal/s2w_config.h"

#include "main/app_main_ctx.h"
#include "config/app_stat_config.h"
#include "app_rtc_mem.h"
#include "app_events.h"

#include "config/app_resource_config.h"
#include "config/app_httpd_config.h"

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern S2W_PROFILE_PARAMS_T profile_params;


#ifdef S2W_OTP_RDWR_SUPPORT

UINT8
AppS2wCmd_WlanOtpWrite (UINT8 *ptr)
{
    UINT8 status;;
    UINT32 temp = 0;
    UINT8 *p;
        UINT8 otpGrpId, otpGrpVer;
    UINT8 data[16] ={0};
    UINT8 data1[256] ={0};
        UINT16 dataLen=0;
    GSN_WIF_SYS_OTP_WRITE_RSP_T writeRsp;
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
       return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &temp);
    if ((status != S2W_SUCCESS) ||(temp > 255))
    {
        return S2W_EINVAL;
    }
    otpGrpId = temp;

    // version
    otpGrpVer = GSN_OTP_MM_VER_UNKNOWN ;
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);

    if((p) && (*p != '\0'))
    {
    status = AppS2wParse_Int(p, &temp);
    if ((status != S2W_SUCCESS) ||(temp > 255))
    {
            return S2W_EINVAL;
    }
    otpGrpVer = temp;
    }

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Int(p, &temp);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        dataLen = temp;
        UINT8 k=0;
        for(k=0;k<dataLen;k++)
        {
            UINT8 i=0,j=0,m=0;
            p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
        
        // convert the length to bytes
        // data comming as hex so convert it
            p = p+2;// skip the 0x
            UINT32 val = 0;
            while (isspace(*p))
            {
                p++;
            }

            for (j = (0); *p != '\0'; j++)
            {
                for (val = 0, i = 0; i < 2 && *p != '\0'; p++, i++)
                {
                    if (!isxdigit(*p))
                    {
                        break;
                    }
                    val = val * 16 + AppS2wParse_ToHex(*p);
                }
                if (i != 2)
                {
                    break;
                }

                data[j] = val;

            }
            // reverse the string
            for((i=k*8),m=8;m>0;i++,m--)
            {
                data1[i] = data[m-1];
            }
        }

    }
    status = GsnSysCtl_OtpWriteReq(&s2wappMainTaskCtxt->sysCtlCtx, otpGrpId, otpGrpVer,
                           data1, (dataLen*GSN_OTP_NUM_BYTES_PER_WORD) ,&writeRsp);
    if((status != GSN_SUCCESS)|| (writeRsp.status != GSN_SUCCESS))
    {
        return S2W_FAILURE;
    }
    return S2W_SUCCESS;
}



UINT8
AppS2wCmd_AppOtpWrite (UINT8 *ptr)
{
    GSN_STATUS status;;
    UINT32 temp = 0;
    UINT8 *p;
    UINT8 otpGrpId, otpGrpVer;
    UINT8 data[16] ={0};
    UINT8 data1[256] ={0};
    UINT16 dataLen=0;
    UINT8 mac[6];
    // id
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if(!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p, &temp);
    if ((status != S2W_SUCCESS) ||(temp > 255))
    {
        return S2W_EINVAL;
    }
    otpGrpId = temp;
    // version
    otpGrpVer = GSN_OTP_MM_VER_UNKNOWN ;
    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);

    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Int(p, &temp);
        if ((status != S2W_SUCCESS) ||(temp > 255))
        {
                return S2W_EINVAL;
        }
        otpGrpVer = temp;
    }

    p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
    if((p) && (*p != '\0'))
    {
        status = AppS2wParse_Int(p, &temp);
	    if (status != S2W_SUCCESS)
	    {
		    return status;
	    }
        dataLen = temp;
        UINT8 k=0;
        for(k=0;k<dataLen;k++)
        {
            UINT8 i=0,j=0,m=0;
            p=(UINT8*)AppS2wParse_NextParamGet(&ptr);
            // convert the length to bytes
            // data comming as hex so convert it
            p = p+2;// skip the 0x
            UINT32 val = 0;
            while (isspace(*p))
            {
                p++;
            }

            for (j = (0); *p != '\0'; j++)
            {
                for (val = 0, i = 0; i < 2 && *p != '\0'; p++, i++)
                {
                    if (!isxdigit(*p))
                    {
                        break;
                    }
                    val = val * 16 + AppS2wParse_ToHex(*p);
                }
                if (i != 2)
                {
                    break;
                }

                data[j] = val;

            }
            // reverse the string
            for((i=k*8),m=8;m>0;i++,m--)
            {
                data1[i] = data[m-1];
            }
        }
    }
    status = GsnOtpMm_Write( otpGrpId, otpGrpVer,
                             (dataLen*GSN_OTP_NUM_BYTES_PER_WORD),data1);
    if(status != GSN_SUCCESS)
    {
        return S2W_FAILURE;
    }
    // if it success update the nvds mac
    memcpy(mac,data,6);
    if(otpGrpId == GSN_OTP_MM_ID_MAC_ID0)
    {
         S2w_SaveMacAddr(mac);
         S2w_macAddrRTCSet(mac); // set in the rtc also
    }
    else if(otpGrpId == GSN_OTP_MM_ID_MAC_ID1)
    {
         S2w_SaveApMacAddr(mac);
         memcpy(s2wCurrent.lmtdApConf.macAddr.array, mac,6);
    }
    return S2W_SUCCESS;
}



#endif




