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
* $RCSfile: s2w_general_parse.c,v $
*
* Description : s2w parser file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/

#include <ctype.h>
#include <string.h>
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "parser/s2w_parse.h"
#include "parser/s2w_process.h"
#include "main/app_main_ctx.h"
//#include "config\app_ncm_config.h"

extern S2W_PROFILE_T s2wCurrent;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

/**
 ******************************************************************************
 * @file s2w_general_parse.c
 * @brief S2W Application command process routines.
 *      This file contains the s2w application specific implimentation for
 *      command processing.
******************************************************************************/

/*****************************************************************************
  *  Private Variables
  *****************************************************************************/

 /*****************************************************************************
  *  Public Variables
  *****************************************************************************/


/*****************************************************************************
  *  Private Functions
  *****************************************************************************/
PRIVATE UINT8
AppS2wParse_Number(UINT8 *ptr, UINT32 *val, UINT8 hex);

PUBLIC UINT8
AppS2wParse_ToHex(UINT8 c);

PRIVATE UINT32
AppS2wParse_KeyValueGet(UINT8 *str, UINT8 *key);

PRIVATE UINT32
AppS2wParse_PskValueGet(UINT8 *str, UINT8 *key);


/*****************************************************************************
  *  Public Functions
  *****************************************************************************/

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Returns a pointer to the next parameter in the string.
 *        This function finds the next parameter of the string by checking the
 *        ',' character.
 * @param temp - IN Point to a char pointer which must initially point
 *                  to the string to be parsed.  This will be modified.
 * @return Pointer to the next parameter.
 ************************************************************************/
PUBLIC UINT8 *
AppS2wParse_NextParamGet(UINT8 **temp)
{
    char *str = (char *)*temp;
    char prev = '\0';
    int quoted = 0;
    int done = 0;
    char *p;

    if (!*str)
    {
        return NULL;
    }

    p = str;
    while (isspace(*p))
    {
        p++;
    }

    if (*p == '"')
    {
        quoted = 1;
        str = p + 1;
    }

    for (p = str; *p; p++)
    {
        if (*p == ',' && (!quoted || done))
        {
            break;
        }
        else if (*p == '"' && quoted && prev != '\\')
        {
            if (done)
            {
                /* Misquoted parameter */
                return NULL;
            }

            prev = *p = '\0';
            done = 1;
        }

        prev = *p;
    }

    if (*p)
    {
        *p = '\0';
        *temp = (UINT8 *) (p + 1);
    }
    else
    {
        *temp = (UINT8 *) p;
    }

    return (UINT8 *) str;
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Convert the ASCII string to integer value.
 *        This function convert the string to integer.
 * @param ptr- IN ASCII string.
 * @param val Pointer to a variable to hold the resulting value.
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Int(UINT8 *ptr, UINT32 *val)
{
    return AppS2wParse_Number(ptr, val, 0);
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Convert the ASCII string to hexadecimal value.
 * @param ptr ASCII string.
 * @param val Pointer to a variable to hold the resulting value.
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Hex(UINT8 *ptr, UINT32 *val)
{
    return AppS2wParse_Number(ptr, val, 1);
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the command parameter value and convert to boolean.
 * @param ptr Pointer which points to string to be parsed.
 * @param val Pointer to hold the value.
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Boolean(UINT8 *ptr, UINT8 *val)
{
    while (isspace(*ptr))
    {
        ptr++;
    }

    if ((*ptr != '0' && *ptr != '1') || *(ptr + 1) != '\0')
    {
        return S2W_EINVAL;
    }

    *val = (*ptr == '1');
    return S2W_SUCCESS;
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the input string, convert the dotted IP string to IP address.
 * @param p Pointer which points to string to be parsed.
 * @param ip Pointer to the buffer which holds the IP address.
 * @return S2W_SUCCESS on success, S2W_EINVAL on failure.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Ip(UINT8 *p, UINT8 *ip)
{
    UINT32 val;
    int digits;
    int quad;

    memset(ip, 0, 4);

    while (isspace(*p))
    {
        p++;
    }

    for (quad = 0; quad < 4; quad++)
    {
        val = 0;
        digits = 0;

        while (*p)
        {
            if (!isdigit(*p))
            {
                break;
            }

            val = val * 10 + (*p - '0');

            p++;
            digits++;
        }

        if (!digits || val > 255 || (quad < 3 && *p != '.'))
        {
            return S2W_EINVAL;
        }

        ip[quad] = val;

        if (quad < 3)
        {
            p++;
        }
    }

    while (isspace(*p))
    {
        p++;
    }

    if (*p)
    {
        return S2W_EINVAL;
    }

    return S2W_SUCCESS;
}

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the command parameter value and convert to MAC Address.
 * @param s Pointer which points to string to be parsed.
 * @param mac_addr Pointer to hold buffer which holds the resulting mac address.
 *
 * @return S2W_SUCCESS on success, S2W_EINVAL if the address is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Mac(UINT8 *s, UINT8 *mac_addr)
{
    UINT32 i, val;
   // UINT8 dummy[6]={0x00,0x00,0x00,0x00,0x00,0x00}; // 0 mac
   // UINT8 dummy1[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; // broadcast mac
    memset(mac_addr, 0, S2W_MAC_ADDR_SIZE);

    for (i = 0; *s != '\0' && i < 7; i++, s++)
    {
        int digits = 0;

        val = 0;
        while (*s != ':' && *s != '\0' && *s != ' ')
        {
            if (!isxdigit(*s))
            {
                return S2W_EINVAL;
            }

            val = val * 16 + AppS2wParse_ToHex(*s);
            s++;
            digits++;
        }

        if (!digits || digits > 2)
        {
            return S2W_EINVAL;
        }

        if(i<6)
        {
        mac_addr[i] = val;
    }
        if(*s == '\0')
		{
			i++;
			break;
		}
    }
//    if((memcmp(mac_addr,dummy,6)== 0) || (memcmp(mac_addr,dummy1,6) == 0))
//    {
//        return S2W_EINVAL;
//    }
    return i == 6 ? S2W_SUCCESS : S2W_EINVAL;
}

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the IP address and port number from the user input string.
 * @param temp Pointer to a char pointer which must initially point
 *            to the string to be parsed.
 * @param peer_data Pointer to structure which holds the IP address and port
 *          number.
 *
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_AddrPort(UINT8 **temp, S2W_NETDATA_T *peer_data)
{
    UINT8 *p;
    UINT32 port;//,len;
    UINT8 status;
	ULONG hostIpAddress;

    p = AppS2wParse_NextParamGet(temp);
    if (!p)
    {
        return S2W_EINVAL;
    }

	if(inet_addr((const char *)p) != -1)
    {
    status = AppS2wParse_Ip(p, (UINT8 *) & peer_data->ipAddr);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
	}
	else
	{
        //len = strlen((char *)p);
		status = GsnNwIf_DnsHostByNameGet(&s2wappMainTaskCtxt->if0.nwifCtx, (UINT8*)p, &hostIpAddress , 5);
		if (hostIpAddress == 0)
			return S2W_FAILURE;
		peer_data->ipAddr[0] = (hostIpAddress & 0xff000000)>>24 ;			
		peer_data->ipAddr[1] = (hostIpAddress & 0x00ff0000)>>16;
		peer_data->ipAddr[2] = (hostIpAddress & 0x0000ff00)>>8;
		peer_data->ipAddr[3] = (hostIpAddress & 0x000000ff);
        S2w_Printf("\r\nIP:%d.%d.%d.%d",peer_data->ipAddr[0],peer_data->ipAddr[1],
                   peer_data->ipAddr[2],peer_data->ipAddr[3]);
	}

    p = AppS2wParse_NextParamGet(temp);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Int(p, &port);
    if (status != S2W_SUCCESS || !is_valid_port(port))
    {
        return S2W_EINVAL;
    }

    peer_data->port = port;

    return S2W_SUCCESS;
}

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the SSID from the input string.
 * @param p Pointer which points to the string to be parsed.
 * @param ssid Pointer to the buffer which holds the SSID.
 * @param lenp Pointer to a variable in which to store the length on the parsed
 *         SSID
 * @return status
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Ssid(UINT8 *p, UINT8 *ssid, UINT8 *lenp)
{
    UINT8 len = 0;

    memset(ssid, 0, S2W_MAX_SSID_LEN);

    while (*p)
    {
        if (*p == '\\' && *(p + 1) == '"')
        {
            *ssid = '"';
            p++;
        }
        else
        {
            *ssid = *p;
        }

        p++;
        len++;
        ssid++;

        if (len >= S2W_MAX_SSID_LEN)
        {
            break;
        }
    }
    *lenp = len;
    if (*p)
    {
        return S2W_EINVAL;
    }

    if (len == 0)
    {
        return S2W_EINVAL;
    }

    return S2W_SUCCESS;
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the WEP key from user input string.
 * @param ptr Pointer which points to string to be parsed.
 * @param wep Pointer to the WEP structure to store the key in
 * @param idx WEP key index.
 * @return Key type on success, 0 if key is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_WepKey(UINT8 *ptr, S2W_WEPDATA_T *wep, UINT8 idx)
{
    UINT8 temp[13];
    UINT32 len;

    S2W_ASSERT(idx >= 1 && idx <= 4);

    len = strlen ((const INT8*)ptr);
    if (len > 26)
    {
        return S2W_EINVAL;
    }

    len = AppS2wParse_KeyValueGet(ptr, temp);
    if (len != 5 && len != 13)
    {
        return S2W_EINVAL;
    }
    idx--;

    memcpy(wep->key[idx], temp, len);
    wep->keyLen[idx] = len;

    return S2W_SUCCESS;
}

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the user input string for SSID, BSSID, channel and
 *        scan time values.
 * @param ptr Pointer which points to string to be parsed.
 * @param params Pointer to structure which will hold the resulting parameters.
 * @param cmd Specifies the command for which the parameters
 *             are to be parsed (SCAN/ASSOC/WAUTO).
 *
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Wcmd(UINT8 *ptr, S2W_WLANDATA_T *params, enum pwc_command cmd)
{
    UINT8 *pt = ptr;
    UINT8 *temp = ptr;
    UINT32 tempint;
    UINT8 status,domain,chMax=0;
	UINT32 mode=0;

    if (!*pt)
    {
        return S2W_EINVAL;
    }

    if (cmd == pwc_wauto)
    {
        /* WAUTO has mode first */
        pt = AppS2wParse_NextParamGet(&temp);
        if (!pt)
        {
            return S2W_EINVAL;
        }

        status = AppS2wParse_Int(pt, &mode);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        params->mode = mode;
    }
	else
		mode = s2wCurrent.mode;

    pt = AppS2wParse_NextParamGet(&temp);
    if (!pt)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Ssid(pt, params->ssid, &params->ssidLen);
    if (status != S2W_SUCCESS)
    {
        if(((cmd != pwc_scan) && (params->ssidLen > 0))|| ((cmd == pwc_scan) && (params->ssidLen > 0)))
        {
        return status;
        }

    }

    params->validBssid = 0;

    pt = AppS2wParse_NextParamGet(&temp);
    if (!pt)
    {
        if((cmd != pwc_scan)&&(params->ssidLen == 0))
        {
            return S2W_EINVAL;
        }
        else
        {
            return S2W_SUCCESS;
        }
        //return (cmd == pwc_wauto) ? S2W_SUCCESS/*S2W_EINVAL*/ : S2W_SUCCESS;
    }

    if (*pt != '\0')
    {
        status = AppS2wParse_Mac(pt, params->bssid);
        if (status != S2W_SUCCESS)
        {
            return status;
        }
        params->validBssid = 1;
    }
    else
    {
       if((cmd != pwc_scan) && (params->ssidLen == 0))
       {
          return S2W_EINVAL;
       }
    }

    pt = AppS2wParse_NextParamGet(&temp);
    if (!pt)
    {
        return S2W_SUCCESS;
    }

    status = AppS2wParse_Int(pt, &tempint);
    /* Allow 0 to mean default channel */
    if (status != S2W_SUCCESS)
    {
       return S2W_EINVAL;
    }
	if(mode == S2W_WLANDATA_MODE_AP)
	{
		domain = s2wCurrent.lmtdApConf.regDomain;
	}
	else
	{
   		 domain= s2wCurrent.regDomain;
	}
    switch(domain)
    {
       case S2W_DOMAIN_FCC:
           chMax=11;
       break;

       case S2W_DOMAIN_ETSI:
           chMax=13;
       break;
       case S2W_DOMAIN_TELEC:
           chMax=14;
       break;

       default:
           chMax=11;
       break;

    }
     if (tempint && (tempint < S2W_WLANDATA_CHANNEL_MIN
                || tempint > chMax))
    {
        return S2W_EINVAL;
    }
    params->channel = tempint;

    if (cmd == pwc_scan)
    {
        /* SCAN can also have scan time */
        pt = AppS2wParse_NextParamGet(&temp);
        if (pt)
        {
            status = AppS2wParse_Int(pt, &tempint);
            if (status != S2W_SUCCESS || tempint > 10000)// maximum 10 seconds
            {
                return S2W_EINVAL;
            }

            params->scanTime = tempint;
        }
    }
	else
	{	/* optional argument for wa cmd*/
		if (cmd == pwc_assoc)
		{
			pt = AppS2wParse_NextParamGet(&temp);
   			if (!pt)
    		{
        		return S2W_SUCCESS;
    		}
			if(AppS2wParse_Boolean(pt,&globalUseHRssi) != S2W_SUCCESS)
			    return S2W_EINVAL;
		}
	}
    return S2W_SUCCESS;
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the network config command parameters.
 * @param temp Pointer to a char pointer which must initially point
 *             to the string to be parsed.
 * @param config Pointer to structure which will hold the resulting
 *               configuration values.
 *
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Nset(UINT8 **temp, S2W_NETCONF_T *config)
{
    UINT8 status;
    UINT8 *p;
    /* 1st parameter ip address */
    p = AppS2wParse_NextParamGet(temp);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Ip(p, (UINT8 *) & config->ipAddr);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* 2nd parameter subnet mask address */
    p = AppS2wParse_NextParamGet(temp);
    if (!p)
    {
        return S2W_EINVAL;
    }

    status = AppS2wParse_Ip(p, (UINT8 *) & config->netMask);
    if (status != S2W_SUCCESS)
    {
        return S2W_EINVAL;
    }

    /* 3rd parameter gateway address */
    p = AppS2wParse_NextParamGet(temp);
    if (!p)
    {
        return S2W_EINVAL;
    }

    return AppS2wParse_Ip(p, (UINT8 *) & config->gateway);
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the fwup command parameters.
 * @param temp Pointer to a char pointer which must initially point
 *             to the string to be parsed.
 * @param params Pointer to structure which will hold the resulting
 *               configuration values.
 *
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Fwup(UINT8 *temp, S2W_FWUP_CONF_T* params)
{
    UINT8 status;
    UINT8 *p;

    /* 1st parameter server ip address  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Ip(p, (UINT8 *) &params->fwSrvIp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* 2nd parameter dst port  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&params->dstPort);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* 3rd parameter source port  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Int(p,&params->srcPort);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* 4th parameter retry count  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
#ifndef S2W_IP2WIFI_SUPPORT
        return S2W_SUCCESS;
#else
        return S2W_EINVAL;
#endif
    }
    if (*p != '\0')
    {
       status = AppS2wParse_Int(p,&params->retry);
       if (status != S2W_SUCCESS)
       {
           return status;
       }
    }
    else
    {
       params->retry = 10;// default retry 10
    }
#ifdef S2W_IP2WIFI_SUPPORT
    /* 5th parameter node ip  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Ip(p, (UINT8 *) &params->nodeIp);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

    /* 6th parameter node mask  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Ip(p, (UINT8 *) &params->nodMask);
    if (status != S2W_SUCCESS)
    {
        return status;
    }

     /* 7th parameter node gateway  */
    p = AppS2wParse_NextParamGet(&temp);
    if (!p)
    {
        return S2W_EINVAL;
    }
    status = AppS2wParse_Ip(p, (UINT8 *) &params->nodeGateway);
    if (status != S2W_SUCCESS)
    {
        return status;
    }
#endif
    return S2W_SUCCESS;

}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the psk set command parameters.
 * @param temp Pointer to a char pointer which must initially point
 *             to the string to be parsed.
 * @param psk Pointer to which will hold the resulting
 *               configuration values.
 *
 * @return S2W_SUCCESS on success, S2W_EINVAL if the parameter is invalid.
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_Psk(UINT8 *temp, UINT8 *psk)
{
    UINT8 key[32];
    UINT32 len=0;
    /* parse the psk  */
    len = AppS2wParse_PskValueGet(temp,key);
    if(len!= 32)
    {
        return S2W_EINVAL;
    }
    memcpy(psk, key, 32);
    return S2W_SUCCESS;
}






#ifndef S2W_HAVE_STRNCASECMP
/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Compare specified number of characters in two input strings
 *    irrespective of the alphabetical case.
 * @param s1 Input string 1.
 * @param s2 Input string 2.
 * @param n Number of bytes to be compared.
 ************************************************************************/
PUBLIC INT32
AppS2wParse_StrnCaseCmp(const char *s1, const char *s2, unsigned int n)
{
    int diff;

    while (n--)
    {
        if (!*s1 && !*s2)
        {
            break;
        }

        diff = toupper(*s1) - toupper(*s2);
        if (diff)
        {
            return diff;
        }
        s1++;
        s2++;
    }

    return 0;
}
#endif


/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Gets the value of a single ASCII hex character.
 *   Doesn't validate the character.  Validation must be done before with
 *   isxidigit() or something similar.
 * @param -IN  Character
 *
 * @return Value of the character
 ************************************************************************/
PUBLIC UINT8
AppS2wParse_ToHex(UINT8 c)
{
    UINT8 val = 0;

    if (c >= '0' && c <= '9')
    {
        val = c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        val = c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        val = c - 'a' + 10;
    }

    return val;
}

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the string and convert it to integer,
 * @param ptr Pointer to user input string.
 * @param val Pointer to buffer to hold the resulting value.
 * @param hex Value represents whether the string to be converted to
 *            decimal or hexadecimal.
 *
 * @return S2W_SUCCESS, S2W_EINVAL.
 *************************************************************************/
PRIVATE UINT8
AppS2wParse_Number(UINT8 *ptr, UINT32 *val, UINT8 hex)
{
    UINT32 temp = 0;

    *val = 0;

    while (isspace(*ptr))
    {
        ptr++;
    }

    if (hex)
    {
        while (*ptr)
        {
            if (!isxdigit(*ptr))
            {
                break;
            }
            temp = temp * 16 + AppS2wParse_ToHex(*ptr);
            ptr++;
        }
    }
    else
    {
        for (; *ptr >= '0' && *ptr <= '9'; ptr++)
        {
            temp = temp * 10 + (*ptr - '0');
        }
    }

    if (*ptr)
    {
        while (isspace(*ptr))
        {
            ptr++;
        }

        if (*ptr)
        {
            return S2W_EINVAL;
        }
    }

    *val = temp;
    return S2W_SUCCESS;
}



/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the string and convert it to 64 bit integer,
 * @param ptr Pointer to user input string.
 * @param val Pointer to buffer to hold the resulting value.
 *
 * @return S2W_SUCCESS, S2W_EINVAL.
 *************************************************************************/

PUBLIC UINT8
AppS2wParse_64BitNumber(UINT8 *ptr, ULONG64 *val)
{
    ULONG64 temp = 0;

    *val = 0;

    while (isspace(*ptr))
    {
        ptr++;
    }


    {
        for (; *ptr >= '0' && *ptr <= '9'; ptr++)
        {
            temp = temp * 10 + (*ptr - '0');
        }
    }

    if (*ptr)
    {
        while (isspace(*ptr))
        {
            ptr++;
        }

        if (*ptr)
        {
            return S2W_EINVAL;
        }
    }

    *val = temp;
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wParse_HexString(UINT8 *ptr, UINT8 *val, UINT32 len)
{
    UINT8 status;
    UINT32 i=0,/*j=0,*/ value=0, v = 0;
    UINT8 indata[5];
    for(i=0;i<len;(i+=2))
    {
        memcpy(indata,ptr,2);
        indata[2]='\0';
        status = AppS2wParse_Hex(indata, &value);
        if(status != GSN_SUCCESS)
        {
            return S2W_EINVAL;
        }
        //S2w_Printf("\r\nVal:%x\r\n",value);
        v = ((v << 8) | value);
        //val[j++] = value;
        ptr += 2;
    }
    *((UINT32*)val) = v;
    return status;
}

/**
 ***************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the command parameter and convert to ascii string to WEP key
 * @param str pointer which points to string to be parsed.
 * @param key pointer to buffer which holds the resulting key.
 *
 * @return length of key.
 ****************************************************************************/
PRIVATE UINT32
AppS2wParse_PskValueGet(UINT8 *str, UINT8 *key)
{
    UINT32 val = 0, i, j;

    memset(key, 0, 32);

    while (isspace(*str))
    {
        str++;
    }

    for (j = 0; *str != '\0' && j < 33; j++)
    {
        for (val = 0, i = 0; i < 2 && *str != '\0'; str++, i++)
        {
            if (!isxdigit(*str))
            {
                return 0;

            }

            val = val * 16 + AppS2wParse_ToHex(*str);
        }

        if (i != 2)
        {
            return 0;
        }

        key[j] = val;
    }
    return j;
}


/**
 ***************************************************************************
 * @ingroup S2w-Application
 * @brief Parse the command parameter and convert to ascii string to WEP key
 * @param str pointer which points to string to be parsed.
 * @param key pointer to buffer which holds the resulting key.
 *
 * @return length of key.
 ****************************************************************************/
PRIVATE UINT32
AppS2wParse_KeyValueGet(UINT8 *str, UINT8 *key)
{
    UINT32 val = 0, i, j;

    memset(key, 0, 13);

    while (isspace(*str))
    {
        str++;
    }

    for (j = 0; *str != '\0' && j < 13; j++)
    {
        for (val = 0, i = 0; i < 2 && *str != '\0'; str++, i++)
        {
            if (!isxdigit(*str))
            {
                return 0;
            }

            val = val * 16 + AppS2wParse_ToHex(*str);
        }

        if (i != 2)
        {
            return 0;
        }

        key[j] = val;
    }
    return j;
}

PUBLIC BOOL
AppS2wParse_MdnsKeyValidate(UINT8 *str, UINT32 len)
{
	UINT32 i;
	for(i=0;i<len;i++)
	{
		if(*(str + i) == '=')		
			return TRUE;
	}
	return FALSE;
}
PUBLIC UINT8
AppS2wParse_IntToChar(UINT8 c)
{
    UINT8 val = 0;

    if (c <= 9)
    {
        val = c + '0';
    }
    else if (c >= 0xA && c <= 0xF)
    {
        val = c + 'A' -0xA;
    }
    else if (c >= 0xa && c <= 0xf)
    {
        val = c + 'a' - 0xa;
    }
    return val;
}

PUBLIC VOID
AppS2wParse_IntToStr(UINT8 *inPtr ,UINT8 *val, UINT32 len)
{
	UINT8 i;	
	for(i = 0 ; i<len ; i++)
	{
		val[i*2]	   = AppS2wParse_IntToChar((inPtr[i]>>4 ) & 0x0f);
		val[(2*i) + 1] = AppS2wParse_IntToChar((inPtr[i] ) & 0x0f);
	}
}


