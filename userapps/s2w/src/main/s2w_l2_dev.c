/******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: s2w_l2_dev.c,v $
*
*******************************************************************************/


/*******************************************************************************
  * File Inclusions
  *****************************************************************************/

#include "gsn_includes.h"
#include "main/app_main_ctx.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"


#ifdef S2W_IP2WIFI_SUPPORT
extern UINT8 fwupStart;
#endif
extern GSN_OSAL_QUEUE_T s2wNetQueue;

#define S2W_RAW_BUFF_SIZE 1600
/**
 *******************************************************************************
 * @file s2w_l2_dev.h
 * @brief S2W l2 dev public API implementation.
 *    This file contains the public APIs and structures of l2 dev module.
 ******************************************************************************/

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

typedef enum S2W_L2DEV_FILTER
{
    S2W_L2DEV_SEND_NONE,
    S2W_L2DEV_SEND_STACK,
    S2W_L2DEV_SEND_UART,
    S2W_L2DEV_SEND_BOTH,
}S2W_L2DEV_FILTER_T;



/*******************************************************************************
 * Extern Definitions
 ******************************************************************************/
#ifdef S2W_SEPARATE_NET_RX_TASK
extern GH_QUEUE s2wNetQueue;
#endif
extern UINT8 s2wNRAWState;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
UINT8 webProvFlag = 0;

UINT8 s2wRawBuffAlloc=0;
/*******************************************************************************
 * Global Definitions
 ******************************************************************************/
#ifdef S2W_IP2WIFI_SUPPORT
UINT8 s2wRawBufs[S2W_NUM_RAW_BUFS][S2W_RAW_BUFF_SIZE];
#endif


#ifdef S2W_IP2WIFI_SUPPORT

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
s2wL2Dev_Close(struct GSN_L2_DEV * pL2Dev)
{
    S2W_L2_DEV_T *ps2wL2Dev;

    ps2wL2Dev = (S2W_L2_DEV_T *)pL2Dev;

    ps2wL2Dev->pL2Dev->close(ps2wL2Dev->pL2Dev);
    return GSN_SUCCESS;
}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
s2wL2Dev_ioctl(struct GSN_L2_DEV * pL2Dev, UINT32 cmd, void *pData)
{
    S2W_L2_DEV_T *ps2wL2Dev;

    ps2wL2Dev = (S2W_L2_DEV_T *)pL2Dev;

    ps2wL2Dev->pL2Dev->ioctl (ps2wL2Dev->pL2Dev, cmd, pData);

    return GSN_SUCCESS;

}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
s2wL2Dev_Send(struct GSN_L2_DEV * pL2Dev, GSN_ETHERNET_FRAME_T *pFrame,
                        UINT32 frameLen)
{
    S2W_L2_DEV_T *ps2wL2Dev;
    GSN_STATUS retCode;

    ps2wL2Dev = (S2W_L2_DEV_T *)pL2Dev;

    retCode = ps2wL2Dev->pL2Dev->send(ps2wL2Dev->pL2Dev,
                (GSN_ETHERNET_FRAME_T *)pFrame,  frameLen);

    return retCode;
}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
s2wL2Dev_Init(S2W_L2_DEV_T *ps2wL2Dev,
                 char *nwIfName,
                 GSN_L2_DEV_T *pwdd)
{
    GSN_STATUS retCode = GSN_SUCCESS;
    int i =0;
    UINT8 *pBuf;


    ps2wL2Dev->pL2Dev = pwdd;
        ps2wL2Dev->s2wL2Dev.open = s2wL2Dev_Open;
	    ps2wL2Dev->s2wL2Dev.close = s2wL2Dev_Close;
	    ps2wL2Dev->s2wL2Dev.send = (GSN_L2_DEV_SEND_T)s2wL2Dev_Send;
    ps2wL2Dev->s2wL2Dev.ioctl = s2wL2Dev_ioctl;

    GsnRingBuf_Init( &ps2wL2Dev->s2wRawBufQ, sizeof(UINT32), S2W_NUM_RAW_BUFS+1,
        ps2wL2Dev->s2wRawBufQBuf);
    for (i = 0; i  < S2W_NUM_RAW_BUFS; i++)
    {
        pBuf = s2wRawBufs[i];
        GsnRingBuf_Put( &ps2wL2Dev->s2wRawBufQ, &pBuf);
    }
    return retCode;
}



PUBLIC GSN_STATUS
AppS2wHal_NrawSet(UINT32 mode)
{
    GSN_STATUS retCode = GSN_SUCCESS;
    INT32 i=0, j=0;
    UINT8 *pBuf[S2W_NUM_RAW_BUFS];
    s2wNRAWState = mode;
    if((mode > S2W_NRAW_NONE) && ( !s2wRawBuffAlloc))
    {
        GsnRingBuf_Init( &s2wappMainTaskCtxt->s2wL2Dev.s2wRawBufQ, sizeof(UINT32), S2W_NUM_RAW_BUFS+1,
             &s2wappMainTaskCtxt->s2wL2Dev.s2wRawBufQBuf);
        for (i = 0; i  < S2W_NUM_RAW_BUFS; i++)
        {

            pBuf[i] = gsn_malloc(S2W_RAW_BUFF_SIZE);
            if(pBuf[i] == NULL)
            {

                for(j=i;j >= 0;j--)
                {
                    gsn_free(pBuf[j]);
                }
                return S2W_FAILURE;
            }
        }
        for (i = 0; i  < S2W_NUM_RAW_BUFS; i++)
        {
            GsnRingBuf_Put( &s2wappMainTaskCtxt->s2wL2Dev.s2wRawBufQ, &pBuf[i]);
            s2wRawBuffAlloc = 1;
        }
    }
    return retCode;
}

#ifndef S2W_IP2WIFI_SUPPORT
/**
 *******************************************************************************
 *
 ******************************************************************************/
PRIVATE INLINE UINT16
GsnNwIf_U16FieldGet(UINT8 *pPkt)
{
    UINT16 val = 0;
    memcpy(&val, pPkt, sizeof(UINT16));
    return val;
}
#endif
/**
 *******************************************************************************
 *
 ******************************************************************************/
PRIVATE UINT8
s2wL2Dev_CheckFilter (INT32 pktLen, GSN_ETHERNET_FRAME_T *ethernetFrame)
{
    UINT8 status = S2W_L2DEV_SEND_NONE;
#ifndef S2W_IP2WIFI_SUPPORT
    UINT16 protocol;
    UINT8 l3protocol;
    UINT16 udpport;

    l3protocol = *(ethernetFrame->Data + GSN_NW_IP_PROTO_OFFSET);
    udpport = htons(GsnNwIf_U16FieldGet(ethernetFrame->Data
                + GSN_NW_IP_HEADER_LEN + GSN_NW_UDP_DST_PORT_OFFSET));

    protocol = swap_16(ethernetFrame->UpperProtocolType);

    switch (s2wNRAWState)
    {
        case S2W_NRAW_NONE:
            {
                if (protocol == 0x0000)
                {
                    status = S2W_L2DEV_SEND_NONE;
                }
                else
                {
                    if ((l3protocol == GSN_NW_UDP_PROTO) &&
                        ((0xBAC0 <= udpport) && (udpport <= 0xBACF)))
                    {
                        status = S2W_L2DEV_SEND_NONE;
                    }
                    else
                    {
                        status = S2W_L2DEV_SEND_STACK;
                    }
                }
            }
            break;
        case S2W_NRAW_NONSNAP:
            {
                if (protocol == 0x0000)
                {
                    status = S2W_L2DEV_SEND_UART;
                }
                else
                {
                    if ((l3protocol == GSN_NW_UDP_PROTO) &&
                        ((0xBAC0 <= udpport) && (udpport <= 0xBACF)))
                    {
                        status = S2W_L2DEV_SEND_NONE;
                    }
                    else
                    {
                        status = S2W_L2DEV_SEND_STACK;
                    }
                }
            }
            break;
        case S2W_NRAW_ALL:
            {
                if (protocol == 0x0000)
                {
                    status = S2W_L2DEV_SEND_UART;
                }
                else
                {
                    if ((l3protocol == GSN_NW_UDP_PROTO) &&
                        ((0xBAC0 <= udpport) && (udpport <= 0xBACF)))
                    {
                        status = S2W_L2DEV_SEND_UART;
                    }
                    else
                    {
                        status = S2W_L2DEV_SEND_STACK;
                    }
                }
            }
            break;
    }

#else

    if( !webProvFlag)
    {
        status = S2W_L2DEV_SEND_UART;
    }
    else
    {
	    status = S2W_L2DEV_SEND_STACK;
	}

#endif

    return status;
}


/**
 *******************************************************************************
 *
 ******************************************************************************/
PRIVATE VOID
s2wL2Dev_RecvProcess(S2W_L2_DEV_T *ps2wL2Dev, INT32 pktLen, VOID *pFrame)
{
    UINT8 status;
    S2W_MSG_T recvMsg;
    UINT8 *rawbuf;

    status = s2wL2Dev_CheckFilter(pktLen, pFrame);

    switch (status)
    {
        case S2W_L2DEV_SEND_STACK:
            /**< Send to network stack*/
            if(ps2wL2Dev->s2wL2Dev.rxCb != NULL)
            ps2wL2Dev->s2wL2Dev.rxCb (ps2wL2Dev->l3Hndl, pktLen, pFrame);
        break;
        case S2W_L2DEV_SEND_UART:
        {
            if (GSN_SUCCESS == GsnRingBuf_Get( &ps2wL2Dev->s2wRawBufQ, &rawbuf))
            {
               /* Buffer allocation successful, copy frame. This buffer is
               freed in S2W recv task */
               memcpy(rawbuf, pFrame, pktLen);
               recvMsg.msgType = S2W_RECV_TYPE_RAWDATA;
               recvMsg.rData.dataPtr = rawbuf;
               recvMsg.msgLen = (INT16)pktLen;

               if( GSN_OSAL_SUCCESS != GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg))
               {
                    GsnRingBuf_Put(&ps2wL2Dev->s2wRawBufQ,  &rawbuf);
               }
            }
        }
        break;
        case S2W_L2DEV_SEND_BOTH:
        {
           if(ps2wL2Dev->s2wL2Dev.rxCb != NULL)
            /**< Send to network stack*/
            ps2wL2Dev->s2wL2Dev.rxCb (ps2wL2Dev->l3Hndl, pktLen, pFrame);

            if (GSN_SUCCESS == GsnRingBuf_Get( &ps2wL2Dev->s2wRawBufQ, &rawbuf))
            {
                /* Buffer allocation successful, copy frame. This buffer is
                freed in S2W recv task */
                memcpy(rawbuf, pFrame, pktLen);
                recvMsg.msgType = S2W_RECV_TYPE_RAWDATA;
                recvMsg.rData.dataPtr = rawbuf;
                recvMsg.msgLen = (INT16)pktLen;

                if( GSN_OSAL_SUCCESS != GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg))
                {
                    GsnRingBuf_Put(&ps2wL2Dev->s2wRawBufQ,  &rawbuf);
                }
            }
        }
        break;
        default:
        break;
    }

}

/**
 *******************************************************************************
 *
 ******************************************************************************/
PRIVATE VOID
s2wL2Dev_TxCompleteProcess(INT32 sendStatus, VOID *pCtxt)
{
}

VOID
s2wL2Dev_SendPktCopyCb(GSN_NWIF_CTX_T *pNwIf, VOID *inBuf, UINT32 inLen, VOID *outBuf)
{
	memcpy(outBuf,inBuf,inLen);

}



/**
 *******************************************************************************
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
s2wL2Dev_Open(struct GSN_L2_DEV * pL2Dev,
                        VOID *l3Hndl,
                        GSN_L2_DEV_RX_CB_T rxCb,
                        GSN_L2_DEV_TX_DONE_CB_T txDoneCb,GSN_L2_DEV_SEND_PKT_COPY_CB sendPktCopyCb)
{
    S2W_L2_DEV_T *ps2wL2Dev;
    ps2wL2Dev = (S2W_L2_DEV_T *)pL2Dev;

    ps2wL2Dev->l3Hndl = l3Hndl;

    ps2wL2Dev->s2wL2Dev.rxCb = rxCb;
    ps2wL2Dev->s2wL2Dev.txDoneCb = txDoneCb;

    ps2wL2Dev->pL2Dev->open(ps2wL2Dev->pL2Dev, ps2wL2Dev,
            (GSN_L2_DEV_RX_CB_T)s2wL2Dev_RecvProcess,
            (GSN_L2_DEV_TX_DONE_CB_T)s2wL2Dev_TxCompleteProcess,(GSN_L2_DEV_SEND_PKT_COPY_CB)s2wL2Dev_SendPktCopyCb);
    return GSN_SUCCESS;
}
#endif


