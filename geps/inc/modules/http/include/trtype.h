/*
 * Copyright Notice:
 * Copyright Treck Incorporated  1997 - 2012
 * Copyright Elmic Systems Japan 1997 - 2012
 * No portions or the complete contents of this file may be copied or
 * distributed in any form (including but not limited to printed or electronic
 * forms) without the expressed written consent of Treck Incorporated OR
 * Elmic Systems.  Copyright laws and International Treaties protect the
 * contents of this file.  Unauthorized use is prohibited.
 * All rights reserved.
 *
 * Description: Type Definitions
 * Filename: trtype.h
 * Author: Odile & Paul
 * Date Created: 9/23/97
 * $Source: /home/cvsroot/gs2000_app_sw/afw/system/gsn/src/modules/http/include/trtype.h,v $
 *
 * Modification History
 * $Revision: 1.1 $
 * $Date: 2013/02/26 09:28:54 $
 * $Author: aravind $
 * $ProjectName: /home/mks/proj/tcpip.pj $
 * $ProjectRevision: 6.0.1.29 $
 */

#ifndef _TRTYPE_H_

#define _TRTYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Standard "C" Types
 */
typedef unsigned char  ttUChar;
typedef unsigned char  tt8Bit;
typedef signed   char  ttSChar;
typedef unsigned short ttUShort;
typedef unsigned short tt16Bit;
typedef signed   short ttS16Bit;
typedef signed   short ttSShort;
typedef ttUser32Bit    ttULong;
typedef ttUser32Bit    tt32Bit;
typedef ttUserS32Bit   ttS32Bit;
typedef ttUserS32Bit   ttSLong;
typedef void           ttVoid;


typedef const tt8Bit   TM_FAR  * ttConst8BitPtr;
typedef tt8Bit         TM_FAR  * tt8BitPtr;
typedef ttSChar        TM_FAR  * ttSCharPtr;
typedef tt16Bit        TM_FAR  * tt16BitPtr;
typedef const tt16Bit  TM_FAR  * ttConst16BitPtr;
typedef tt32Bit        TM_FAR  * tt32BitPtr;
typedef const tt32Bit  TM_FAR  * ttConst32BitPtr;
typedef tt8BitPtr      TM_FAR  * tt8BitPtrPtr;
typedef tt16BitPtr     TM_FAR  * tt16BitPtrPtr;
typedef tt32BitPtr     TM_FAR  * tt32BitPtrPtr;

typedef union tuPtr
{
    tt16BitPtr      u16Ptr;
    tt32BitPtr      u32Ptr;
    tt8BitPtr       u8Ptr;
    tt8BitPtrPtr    u8PtrPtr;
    tt16BitPtrPtr   u16PtrPtr;
    tt32BitPtrPtr   u32PtrPtr;
} ttPtrUnion;

#ifdef TM_USER_64BIT_TYPE
typedef ttUser64Bit tt64Bit;
#else /* !TM_USER_64BIT_TYPE */
typedef struct ts64Bit
{
#ifdef TM_LITTLE_ENDIAN
    tt32Bit  u64low;
    tt32Bit  u64high;
#else /* !TM_LITTLE_ENDIAN */
    tt32Bit  u64high;
    tt32Bit  u64low;
#endif /* !TM_LITTLE_ENDIAN */
} tt64Bit;
#endif /* !TM_USER_64BIT_TYPE */

typedef struct {
#ifdef TM_LITTLE_ENDIAN
     tt32Bit lo;
     tt32Bit hi;
#else
     tt32Bit hi;
     tt32Bit lo;
#endif
} ttSHAint64;

typedef tt64Bit         TM_FAR  * tt64BitPtr;
typedef const tt64Bit   TM_FAR  * ttConst64BitPtr;
typedef tt64BitPtr      TM_FAR  * tt64BitPtrPtr;

#ifdef TM_USER_64BIT_TYPE
typedef ttUserS64Bit ttS64Bit;
#else /* !TM_USER_64BIT_TYPE */
typedef struct tsS64Bit
{
#ifdef TM_LITTLE_ENDIAN
    tt32Bit  s64low;
    ttS32Bit s64high;
#else /* !TM_LITTLE_ENDIAN */
    ttS32Bit s64high;
    tt32Bit  s64low;
#endif /* !TM_LITTLE_ENDIAN */
} ttS64Bit;
#endif /* !TM_USER_64BIT_TYPE */

typedef ttS64Bit        TM_FAR  * ttS64BitPtr;
typedef const ttS64Bit  TM_FAR  * ttConstS64BitPtr;
typedef ttS64BitPtr     TM_FAR  * ttS64BitPtrPtr;

typedef struct ts96Bit
{
#ifdef TM_LITTLE_ENDIAN
    tt32Bit  u96low;
    tt32Bit  u96mid;
    tt32Bit  u96high;
#else /* !TM_LITTLE_ENDIAN */
    tt32Bit  u96high;
    tt32Bit  u96mid;
    tt32Bit  u96low;
#endif /* !TM_LITTLE_ENDIAN */
} tt96Bit;

typedef tt96Bit         TM_FAR  * tt96BitPtr;
typedef const tt96Bit   TM_FAR  * ttConst96BitPtr;
typedef tt96BitPtr      TM_FAR  * tt96BitPtrPtr;

typedef struct tsS96Bit
{
#ifdef TM_LITTLE_ENDIAN
    tt32Bit  s96low;
    tt32Bit  s96mid;
    ttS32Bit s96high;
#else /* !TM_LITTLE_ENDIAN */
    ttS32Bit s96high;
    tt32Bit  s96mid;
    tt32Bit  s96low;
#endif /* !TM_LITTLE_ENDIAN */
} ttS96Bit;

typedef ttS96Bit        TM_FAR  * ttS96BitPtr;
typedef const ttS96Bit  TM_FAR  * ttConstS96BitPtr;
typedef ttS96BitPtr     TM_FAR  * ttS96BitPtrPtr;

typedef ttULong        TM_FAR  * ttULongPtr;
typedef const ttULong  TM_FAR  * ttConstULongPtr;
typedef void           TM_FAR  * ttVoidPtr;
typedef const void     TM_FAR  * ttConstVoidPtr;
typedef char           TM_FAR  * ttCharPtr;
typedef const char     TM_FAR  * ttConstCharPtr;
typedef const unsigned char  TM_FAR  * ttConstUCharPtr;
typedef int            TM_FAR  * ttIntPtr;
typedef const int      TM_FAR  * ttConstIntPtr;
typedef unsigned int   TM_FAR  * ttUIntPtr;
typedef const unsigned int   TM_FAR  * ttConstUIntPtr;
typedef ttConstCharPtr const TM_FAR  * ttConstCharPtrConstPtr;

typedef ttIntPtr       TM_FAR  * ttIntPtrPtr;
typedef ttVoidPtr      TM_FAR  * ttVoidPtrPtr;
typedef ttCharPtr      TM_FAR  * ttCharPtrPtr;

/*
 * Generic Parameter Passing Union Typedef
 */
typedef union tuGenericUnion
{
    tt32Bit         gen32bitParm;
    ttS32Bit        genSlongParm;
    ttVoidPtr       genVoidParmPtr;
    tt16Bit         gen16BitParm;
    int             genIntParm;
    tt8Bit          gen8BitParm;
    char            genCharParm;
} ttGenericUnion;

typedef ttGenericUnion TM_FAR * ttGenericUnionPtr;

/* Node descriptor for Generic linked list */
typedef struct  tsNode
{
    struct tsNode TM_FAR * nodePrevPtr;
    struct tsNode TM_FAR * nodeNextPtr;
} ttNode;
typedef ttNode TM_FAR * ttNodePtr;
#define TM_NODE_NULL_PTR (ttNodePtr)0

/* Generic linked list, with count */
typedef struct  tsList
{
    ttNode          listHeadNode;
    unsigned int    listCount;
} ttList;
typedef ttList TM_FAR * ttListPtr;
#define TM_LIST_NULL_PTR (ttListPtr)0

/* List iterator object.
 * Keeps track of next item and count of remaining items. */
typedef struct tsIterator
{
    ttListPtr       itListPtr;
    ttNodePtr       itNextPtr;
    unsigned int    itCount;
} ttIterator;
typedef ttIterator TM_FAR * ttIteratorPtr;

/*
 * function type for the list call back function
 * return TM_8BIT_NO  to ask the Traverser to continue,
 * return TM_8BIT_YES to ask the Traverser to stop
 * and return the current node
 */
typedef int (TM_CODE_FAR * ttListCBFuncPtr)(
    ttNodePtr       nodePtr,
    ttGenericUnion  genParam1);

typedef tt32Bit tt4IpAddress;
#ifdef TM_USE_IPV6
/*
 * tt6IpAddress should NOT be used in network header structures
 * (e.g. tt6IpHeader) as this may cause alignment issues.  tt6IpAddrArr
 * should be used instead.
 */
typedef struct in6_addr tt6IpAddress;
typedef tt6IpAddress ttIpAddress;
typedef tt32Bit tt6IpAddrArr[4];
#else /* ! TM_USE_IPV6 */
typedef tt4IpAddress ttIpAddress;
#endif /* ! TM_USE_IPV6 */

typedef tt16Bit ttIpPort;
typedef tt8Bit  ttEnetAddress[6];

/* Define IpAdress union for suppress the pointer cast error(error 740). */
typedef union tu4IpAddress
{
    tt4IpAddress    addrLong;
    tt16Bit         addrShort[2];
    tt8Bit          addrChar[4];
} tt4IpAddressUnion;

typedef union tuEnetAddress
{
    tt16Bit        enuShort[3]; /* to force 16-bit alignment */
    tt8Bit         enuAddress[6]; /* Ethernet address */
} ttEnetAddressUnion;

typedef ttEnetAddress TM_FAR * ttEnetAddressPtr;

/* Shortened sockaddr_in (with unused part removed) */
typedef struct tsSockAddrIn
{
    u_char          ssin_len;    /* Total Length */
    u_char          ssin_family; /* Address Family AF_xxx */
    u_short         ssin_port;   /* 16bit Port Number in network byte order */
    struct  in_addr ssin_addr;   /* 32bit netid/hostid in network byte order */
} ttSockAddrIn;

typedef  ttSockAddrIn TM_FAR * ttSockAddrInPtr;

typedef struct tsSockTuple
{
#define TM_REMOTE   0
#define TM_LOCAL    1
#define TM_PEERS    2
#if defined(TM_USE_IPV6) && defined(TM_USER_64BIT_TYPE)
/*
 * Position the IP addresses ahead of the port numbers for this case because
 * ttIpAddress is mapped to struct in6_addr, which contains a 64-bit type.
 * This should cause a compiler to align sotIpAddress (and ttSockTuple) on
 * a 64-bit boundary.
 * SotIpPort is only 32 bits in size (2 x tt16Bit). If sotIpPort is ahead
 * of sotIpAddress, the compiler would likely create 32 bits of unused
 * padding between sotIpPort and sotIpAddress to get 64-bit alignment of
 * the ttIpAddress array, which would affect tuple comparison.
 */
    ttIpAddress             sotIpAddress[TM_PEERS];
    ttIpPort                sotIpPort[TM_PEERS];
    tt32Bit                 sotReserved;    /* Fill to 64-bit multiple */
#define tm_zero_socktupleptr_rsv(ptr)  ((ptr)->sotReserved = TM_32BIT_ZERO)
#elif defined(TM_USE_FAST_TUPLE_CMP64)
/*
 * Position the IP addresses ahead of the port numbers for this case because
 * we are doing 64-bit reads on sotIpAddress for fast tuple comparison.
 * Some CPUs will generate a fault on an unaligned 64-bit memory access.
 * If TM_USE_IPV6 is not defined, IP addresses are 32-bits each.
 * One 64-bit read will get the IP addresses for both peers.
 * In this case, we must unionize the tuple data with ttUser64Bit to get
 * sotIpAddress and the ttSockTuple structure properly aligned to avoid
 * the potential for a memory alignment fault.
 */
    union {
        struct {
            ttIpAddress     stsIpAddress[TM_PEERS];
            ttIpPort        stsIpPort[TM_PEERS];
            tt32Bit         stsReserved;    /* Fill to 64-bit multiple */
        } stuSockTupleStruct;
        ttUser64Bit         stuReserved64;   /* Force 64-bit alignment */
    } sotSockTupleUnion;
#define sotIpAddress sotSockTupleUnion.stuSockTupleStruct.stsIpAddress
#define sotIpPort    sotSockTupleUnion.stuSockTupleStruct.stsIpPort
#define tm_zero_socktupleptr_rsv(ptr)  \
    ((ptr)->sotSockTupleUnion.stuSockTupleStruct.stsReserved = TM_32BIT_ZERO)
#else /* !(TM_USE_IPV6 && TM_USER_64BIT_TYPE) && !TM_USE_FAST_TUPLE_CMP64 */
/*
 * Position sotIpPort ahead of sotIpAddress to speed up tuple comparison
 * for tm_memcmp() (if the port numbers match, it is likely the entire
 * socket tuple will match).
 */
    ttIpPort                sotIpPort[TM_PEERS];
    ttIpAddress             sotIpAddress[TM_PEERS];
#define tm_zero_socktupleptr_rsv(ptr)
#endif /* !TM_USE_IPV6 || !TM_USER_64BIT_TYPE */
#define sotRemoteIpAddress sotIpAddress[TM_REMOTE]
#define sotLocalIpAddress  sotIpAddress[TM_LOCAL]
#define sotRemoteIpPort    sotIpPort[TM_REMOTE]
#define sotLocalIpPort     sotIpPort[TM_LOCAL]
} ttSockTuple;

typedef ttSockTuple TM_FAR * ttSockTuplePtr;

typedef ttIpAddress             TM_FAR * ttIpAddressPtr;
typedef tt4IpAddress            TM_FAR * tt4IpAddressPtr;
typedef const tt4IpAddress      TM_FAR * tt4ConstIpAddressPtr;
#ifdef TM_USE_IPV6
typedef tt6IpAddress            TM_FAR * tt6IpAddressPtr;
typedef const tt6IpAddress      TM_FAR * tt6ConstIpAddressPtr;
#endif /* TM_USE_IPV6 */
typedef ttIpPort                TM_FAR * ttIpPortPtr;

/*
 * Socket address union
 */
typedef union tuSockAddrPtr
{
    ttSockAddrIn TM_FAR                 *sockTInPtr;
    struct sockaddr_in TM_FAR           *sockInPtr;
    struct sockaddr TM_FAR              *sockPtr;
    struct sockaddr_storage TM_FAR      *sockNgPtr;
#ifdef TM_USE_IPV6
    struct sockaddr_in6 TM_FAR          *sockIn6Ptr;

/* NOTE: the following pointer type is NOT compatible with sockaddr! */
    tt6IpAddressPtr                     sockPeerAddr6Ptr;
#endif /* TM_USE_IPV6 */
} ttSockAddrPtrUnion;

typedef ttSockAddrPtrUnion TM_FAR * ttSockAddrPtrUnionPtr;


typedef struct tsAncHdr
{
/* a ttNode to link multiple ancillary header together */
    ttNode      ancNode;
/* length of the ansData buffer that follows*/
    tt32Bit     ancDataLen;
/* ancillary data, may have one or more cmsghdr (ttAncillaryData) in it
 * the actuall length of this filed is determined by ancDataLen
 */
    tt8Bit      ancData[4];
} ttAncHdr;
typedef ttAncHdr TM_FAR * ttAncHdrPtr;

/*
 * Counting Semaphore List
 */
typedef struct tsCountSem
{
    ttGenericUnion            couCountSem;
    struct tsCountSem TM_FAR *couNext;
} ttCountSem;

typedef ttCountSem TM_FAR * ttCountSemPtr;

/*
 * Lock Entry
 */
typedef struct tsLockEntry
{
    ttCountSemPtr      locCountSemPtr;
    tt16Bit            locCount;
/* Flag to see if Counting Semaphore is Valid */
    tt8Bit             locCountSemValid;
    tt8Bit             locFiller[1];
} ttLockEntry;

typedef ttLockEntry TM_FAR * ttLockEntryPtr;

#ifdef TM_ERROR_CHECKING
/* Entry containing a lock entry, and a flag */
struct tsLockCheck
{
    ttLockEntry lckLockEntry;
    int         lckFlag;
    int         lckFiller;
};

typedef struct tsLockCheck TM_FAR * ttLockCheckPtr;

#endif /* TM_ERROR_CHECKING */


/*
 * Pend Entry
 */
typedef struct tsPendEntry
{
    ttCountSemPtr      pendSemaphorePtr;
    tt16Bit            pendStatus;
    tt8Bit             pendCount;
    tt8Bit             pendPostCount;
} ttPendEntry;
typedef ttPendEntry TM_FAR * ttPendEntryPtr;

/*
 * Event Entry
 */
typedef struct tsEventEntry
{
    ttUserGenericUnion eventUnion;
    tt16Bit            eventCount;
    tt8Bit             eventPending;
    tt8Bit             eventFiller[1];
} ttEventEntry;
typedef ttEventEntry TM_FAR * ttEventEntryPtr;

/*
 * Raw buffer types
 */
typedef struct tsRawMemory
{
    struct tsRawMemory TM_FAR * rawNextPtr;
}ttRawMemory;

typedef ttRawMemory     TM_FAR * ttRawMemoryPtr;
typedef ttRawMemoryPtr  TM_FAR * ttRawMemoryPtrPtr;


typedef tt8Bit                   ttRawBuffer;
typedef ttRawBuffer     TM_FAR * ttRawBufferPtr;

/*
 * Generic recycle entry
 */
typedef struct tsRecycleEntry
{
    struct tsRecycleEntry TM_FAR * rcylNextPtr;
} ttRecycleEntry;

typedef ttRecycleEntry  TM_FAR * ttRcylPtr;
typedef ttRcylPtr       TM_FAR * ttRcylPtrPtr;


#ifdef TM_USE_IPV6
/* Network header: IPv6 Header */
typedef struct ts6IpHeader
{
    union {
        struct {
/* The low-order 20 bits are the Flow Label, the next more significant 8
bits are the Traffic Class. */
#define iph6Flow        iph6Hdr1Union.iph6Hdr1Struct.iphus6Flow
            tt32Bit iphus6Flow;

/* Payload Length: 16-bit unsigned integer length of the IPv6
payload (i.e the rest of the packet following this IPv6 packet header) in
bytes. */
#define iph6Plen        iph6Hdr1Union.iph6Hdr1Struct.iphus6Plen
            tt16Bit iphus6Plen;
/* Next Header: protocol ID of the IPv6 extension header or ULP header
 immediately following this IPv6 packet header. */
#define iph6Nxt         iph6Hdr1Union.iph6Hdr1Struct.iphus6Nxt
            tt8Bit  iphus6Nxt;
/* Hop Limit: the number of hops left for this packet */
#define iph6Hops        iph6Hdr1Union.iph6Hdr1Struct.iphus6Hops
            tt8Bit  iphus6Hops;
/* IPv6 source address */
#define iph6SrcAddr     iph6Hdr1Union.iph6Hdr1Struct.iphus6SrcAddr
            tt6IpAddrArr iphus6SrcAddr;
/* IPv6 destination address */
#define iph6DestAddr    iph6Hdr1Union.iph6Hdr1Struct.iphus6DestAddr
            tt6IpAddrArr iphus6DestAddr;
        } iph6Hdr1Struct;

/* 4 bit IP Version, plus high-order 4 bits of Traffic Class. */
#define iph6Vfc         iph6Hdr1Union.iph6VerClass
        tt8Bit iph6VerClass;
    } iph6Hdr1Union;
/* compiler-added pad bytes at the end are OK */
} tt6IpHeader;

typedef tt6IpHeader TM_FAR * tt6IpHeaderPtr;

/* Network header: TCP/UDP/ICMPv6 Pseudo-header */
/* tt6PseudoHeader is used to compute the UDP, TCP and ICMPv6 checksums when
   the ULP is running over IPv6. tt6PseudoHeader is intended to be mapped
   over the IPv6 packet header. */
#define psh6ZeroArr         psh6Union1.psh6UnStruct1.psh6UnZeroArr
#define psh6Protocol        psh6Union1.psh6UnStruct1.psh6UnProtocol
#define psh6Layer4Len       psh6Union1.psh6UnLayer4Len
#define psh616BitLayer4Len  psh6Union1.psh6UnStruct1.psh6UnLayer4LenArr[1]
#define psh616Bit0Layer4Len psh6Union1.psh6UnStruct1.psh6UnLayer4LenArr[0]
#define psh6SrcIpAddr       psh6Union1.psh6UnStruct1.psh6UnSrcIpAddr
#define psh6DstIpAddr       psh6Union1.psh6UnStruct1.psh6UnDstIpAddr
typedef struct ts6PseudoHeader
{
    union
    {
        tt32Bit      psh6UnLayer4Len;
        struct
        {
            tt16Bit       psh6UnLayer4LenArr[2];
            tt8Bit        psh6UnZeroArr[3];
            tt8Bit        psh6UnProtocol;
            tt6IpAddress  psh6UnSrcIpAddr;
            tt6IpAddress  psh6UnDstIpAddr;
        } psh6UnStruct1;
    } psh6Union1;
} tt6PseudoHeader;
typedef tt6PseudoHeader TM_FAR * tt6PseudoHeaderPtr;

#endif /* TM_USE_IPV6 */

/* Network header: IP Header */
typedef struct  tsIpHeader
{
    tt8Bit          iphVersLen;         /* IP header version and length */
    tt8Bit          iphTos;             /* Type of service */
    tt16Bit         iphTotalLength;     /* IP datagram length */
    tt16Bit         iphId;              /* IP header Identifaction field */
    tt16Bit         iphFlagsFragOff;    /* IP Fragmentation flags & offset */
    tt8Bit          iphTtl;             /* IP time to live */
    tt8Bit          iphUlp;             /* ULP (17 for UDP, 6 for TCP..) */
    tt16Bit         iphChecksum;        /* IP header checksum */
    tt4IpAddress    iphSrcAddr;         /* IP source address */
    tt4IpAddress    iphDestAddr;         /* Ip destination address */
} ttIpHeader;

typedef ttIpHeader TM_FAR * ttIpHeaderPtr;

/* END of IP network header */

#define pktRtePtr             pktSharedDataPtr->dataRtePtr
#define pktDestDevPtr         pktSharedDataPtr->dataDestDevPtr
#define pktTcpUnscaledWnd     pktSharedDataPtr->dataTcpUnscaledWnd
#define pktPppAccm            pktSharedDataPtr->dataPppAccm
/* packet source IP address */
#define pktSrcIpAddress       pktSharedDataPtr->dataSrcIpAddress
/* packet destination IP address */
#define pktDestIpAddress      pktSharedDataPtr->dataDestIpAddress
/* packet specific destination IP address */
#define pktSpecDestIpAddress  pktSharedDataPtr->dataSpecDestIpAddress
#define pktTcpUrgentOffset    pktSharedDataPtr->dataTcpUrgentOffset
#define pktEthernetAddress    pktSharedDataPtr->dataEthernetAddress
#define pkt6PhysAddr          pktSharedDataPtr->data6PhysAddr
#define pkt6PhysAddrLen       pktSharedDataPtr->data6PhysAddrLength
#define pktTcpHdrLen          pktSharedDataPtr->dataTcpHdrLen
/* Not last fragment */
#define pktFragMore           pktSharedDataPtr->dataFragMore
/* TCP Time stamp echo reply */
#define pktTcpTsEcr           pktSharedDataPtr->dataTcpTsEcr
/* Begin byte offset of fragment in fragmented IP datagram */
#define pktFragBBOffset       pktSharedDataPtr->dataFragBBOffset
/* End byte offset of fragment in fragmented IP datagram */
#define pktFragEBOffset       pktSharedDataPtr->dataFragEBOffset
#define pktIpTos              pktSharedDataPtr->dataIpTos
#define pktIpTosSet           pktSharedDataPtr->dataIpTosSet

/*
 * structure allocated each time a Treck buffer is allocated. At least one
 * ttPacket points to the ttSharedData structure. This structure and data
 * associated with it can be shared among different ttPacket. See ttPacket
 * definition below.
 */
typedef struct  tsSharedData
{
/*
 * For send TCP recycle queue, or for UDP/ICMP send datagrams
 */
    struct tsSocketEntry TM_FAR *dataSocketEntryPtr;
/*
 * For User device driver free data routine. Pointer to device which
 * allocated the device user data.
 */
    struct tsDeviceEntry TM_FAR *dataDeviceEntryPtr;
/*
 * For User device driver free routine. Pointer to user device driver
 * data pointer.
 */
    ttCharPtr                    dataDeviceUserDataPtr;
/* Pointer to routing entry for outgoing packet */
    struct tsRteEntry    TM_FAR *dataRtePtr;
/* Pointer to ARP entry for outgoing packet */
    struct tsRteEntry    TM_FAR *dataRteClonedPtr;

    union
    {
        ttEnetAddress dataUnEthernetAddress;

#ifdef TM_USE_IPV6
        tt8Bit        data6UnPhysAddr[tm_align(TM_MAX_PHYS_ADDR)];
#else /* !TM_USE_IPV6 */
        tt16Bit       dataPadding;
#endif /* !TM_USE_IPV6 */

#define dataEthernetAddress  dataEthPhysAddrUnion.dataUnEthernetAddress
#define data6PhysAddr        dataEthPhysAddrUnion.data6UnPhysAddr

    } dataEthPhysAddrUnion;

#ifdef TM_USE_IPV6
    tt8Bit                       data6PhysAddrLength;
    tt8Bit                       data6Padding[3];
#endif /* TM_USE_IPV6 */

/*
 * Pointer to the beginnning of the allocated data buffer.  This pointer
 * is used by tfDeviceSend(), tfTcpGetTcpRecycledHeader()
 * to determine the beginning of the buffer.
 */
    tt8BitPtr                    dataBufFirstPtr;
/*
 * Pointer to the end of the data buffer, prior to the trailer.  This pointer
 * is used by tfSendAppend, tfTcpGetTcpHeader and tfSocketIncomingPacket
 * to determine the total size of the buffer.
 */
    tt8BitPtr                    dataBufLastPtr;
/*
 * TCP received packet socket 4-tuple lookup.
 */
    ttSockTuplePtr               dataSockTuplePtr;
    unsigned int                 dataOwnerCount;
    tt16Bit                      dataPeerPortNumber;
#define dataLinkLayerProtocol    dataPeerPortNumber
    tt16Bit                      dataLocalPortNumber;
    tt16Bit                      dataFlags;

    tt8Bit                       dataTcpHdrLen;
    tt8Bit                       dataReserved;

/* Not last fragment */
#define dataFragMore             dataTcpHdrLen
    union
    {
/* 32-bit TCP unscaled window in host byte order (incoming packet) */
#define dataTcpUnscaledWnd       dataFirstUnion.dataUnTcpUnscaledWnd
        tt32Bit                      dataUnTcpUnscaledWnd;
/* PPP accm for outgoing packet */
#define dataPppAccm              dataFirstUnion.dataUnPppAccm
        tt32Bit                      dataUnPppAccm;
/*
 * packet destination IP address (copied from IP header) (incoming packet).
 * Not used with the TCP protocol
 */
#define dataDestIpAddress         dataFirstUnion.dataUnDestIpAddress
        tt4IpAddress                 dataUnDestIpAddress;
    } dataFirstUnion;
    union
    {
/* TCP Time stamp echo reply (incoming packet) */
#define dataTcpTsEcr             dataSecondUnion.dataUnTcpTsEcr
        tt32Bit                      dataUnTcpTsEcr;
/* To keep track of user application send data (for UDP, ICMP) */
#define dataUserDataLength dataSecondUnion.dataUnUserDataLength
        ttPktLen                     dataUnUserDataLength;
    } dataSecondUnion;
    union
    {
/*
 * packet source IP address (incoming packet). Stored after IP reassembly
 * if any.
 */
#define dataSrcIpAddress         dataThirdUnion.dataUnSrcIpAddress
        tt4IpAddress                 dataUnSrcIpAddress;
/*
 * Begin byte offset of fragment in fragmented IP datagram (incoming packet)
 * NOTE that it is OK to overlay with dataUnSrcIpAddress, since the
 * IP incoming code will store the source IP address after IP reassembly.
 */
#define dataFragBBOffset         dataThirdUnion.dataUnFragBBOffset
        ttPktLen                     dataUnFragBBOffset;
/*
 * Packet destination IP address as specified by the user in tfSendTo
 * (outgoing packet).
 */
#define dataToIpAddress          dataThirdUnion.dataUnToIpAddress
        ttIpAddress                  dataUnToIpAddress;

    } dataThirdUnion;
    union
    {
/*
 * packet specific destination IP address (incoming packet). Stored after
 * IP reassembly if any.
 * packet specific destination IP address for ARP resolution (outgoing
 * packet).
 * Packet source IP address as specified by the user in tfSendToFrom (outgoing
 * packet).
 */
#define dataSpecDestIpAddress    dataFourthUnion.dataUnSpecDestIpAddress
#define dataFromIpAddress        dataFourthUnion.dataUnSpecDestIpAddress
        ttIpAddress                  dataUnSpecDestIpAddress;
/*
 * End byte offset of fragment in fragmented IP datagram (incoming packet)
 * NOTE that it is OK to overlay with dataUnSpecDestIpAddress, since the
 * IP incoming code will store the specific destination IP address after
 * IP reassembly if any.
 */
#define dataFragEBOffset         dataFourthUnion.dataUnFragEBOffset
        ttPktLen                     dataUnFragEBOffset;
    } dataFourthUnion;
    union
    {
#ifndef TM_USE_IPV6
/*
 * Device corresponding to IP destination address in incoming packet
 * This is a computed value based on the IP destination address of
 * the packet in the IP incoming code. It may (or may not) match the
 * incoming device.
 */
#define dataDestDevPtr      dataFifthUnion.dataUnDestDevPtr
        struct tsDeviceEntry TM_FAR * dataUnDestDevPtr;
#endif /* !TM_USE_IPV6 */
/*
 * The TCP header pointer overlays
 * this field for temporary storage while going through the state machine
 * while processing an incoming TCP packet.
 */
#define dataTcpHdrPtr       dataFifthUnion.dataUnTcpHdrPtr
        struct tsTcpHeader   TM_FAR * dataUnTcpHdrPtr;
/*
 * Pointer to user free function used with the User scattered send.
 */
#define dataUserFreeFuncPtr dataFifthUnion.dataUnUserFreeFuncPtr
        ttUserFreeFuncPtr             dataUnUserFreeFuncPtr;
    } dataFifthUnion;
#ifdef TM_USE_IPV6
/*
 * For IPv6 cannot overlay with TCP header pointer since device information
 * is needed to add the scope ID.
 */
    union
    {
/*
 * Device corresponding to IP destination address in incoming packet
 * This is a computed value based on the IP destination address of
 * the packet in the IP incoming code. It may (or may not) match the
 * incoming device.
 */
#define dataDestDevPtr      dataSixthUnion.dataUnDestDevPtr
        struct tsDeviceEntry TM_FAR * dataUnDestDevPtr;
    } dataSixthUnion;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_IPV6
/* list of ttAncHdr strucures, each of them may have multiple cmsghdr
 * inside, use TM_ANC_GET_FIRSTHDR and TM_ANC_GET_NXTHDR  to access them
 */
    ttList                  data6AncHdrList;
#endif /* TM_USE_IPV6 */
#if defined (TM_DEV_SEND_OFFLOAD) && defined (TM_DEV_RECV_OFFLOAD)
#define dataDevSendOffload  dataSendRecvOffloadUnion.dataUnDevSendOffload
#define dataDevRecvOffload  dataSendRecvOffloadUnion.dataUnDevRecvOffload
    union
    {
        ttDevSendOffloadStruct      dataUnDevSendOffload;
        ttDevRecvOffloadStruct      dataUnDevRecvOffload;
    } dataSendRecvOffloadUnion;
#else /* ! (defined (TM_DEV_SEND_OFFLOAD && defined (TM_DEV_RECV_OFFLOAD))*/
#ifdef TM_DEV_SEND_OFFLOAD
    ttDevSendOffloadStruct          dataDevSendOffload;
#endif /* TM_DEV_SEND_OFFLOAD */
#ifdef TM_DEV_RECV_OFFLOAD
    ttDevRecvOffloadStruct          dataDevRecvOffload;
#endif /* TM_DEV_SEND_OFFLOAD */
#endif /* ! (defined (TM_DEV_SEND_OFFLOAD) && defined (TM_DEV_RECV_OFFLOAD))*/
#ifdef TM_USE_QOS
    tt8Bit                          dataIpTos; /* IP Tos */
    tt8Bit                          dataIpTosSet;
#endif /* TM_USE_QOS */
} ttSharedData;

typedef ttSharedData TM_FAR * ttSharedDataPtr;

typedef struct tsIpReassemblyTaskData
{
    tt32Bit itdPortToReinsertOn;
    tt32Bit itdPort;
    tt8Bit  itdAction;
    tt8Bit  itdFlags;
} ttIpReassemblyTaskData;
typedef ttIpReassemblyTaskData TM_FAR * ttIpReassemblyTaskDataPtr;

typedef struct tsIpReassemblyTaskListEntry
{
    ttNode                 irlListNode;
    ttVoidPtr              irlPktPtr;
    int                    irlMemUsed;
#ifdef TM_USE_IPV6
    ttPktLen               irlFragHdrOffset;
    ttPktLen               irlPreFragHdrOffset;
#endif /* TM_USE_IPV6 */
    ttPktLen               irlUlpHdrOffset;
#define irlPortToReinsertOn irlData.itdPortToReinsertOn
#define irlPort             irlData.itdPort
#define irlAction           irlData.itdAction
#define irlFlags            irlData.itdFlags
    ttIpReassemblyTaskData irlData;
    tt8Bit                 irlUlp;
    tt8Bit                 irlLayer2Hdr[14];
} ttIpReassemblyTaskListEntry;
typedef ttIpReassemblyTaskListEntry TM_FAR * ttIpReassemblyTaskListEntryPtr;

/* Treck buffer to convey information about a protocol packet.
 * Only one owner for a tsPacket. Always associated with a ttSharedData
 * structure. Passed as a parameter between different protocol layers. Used
 * to queue packets in different queues (such as send queues receive queues,
 * reassemble (TCP or IP) queues, arp resolution queues).
 */

typedef struct  tsPacket
{
    ttUserPacket                    pktUserStruct;
/* Next tsPacket for scattered data, recycle list  */
#define pktLinkNextPtr              pktUserStruct.pktuLinkNextPtr
/* Data in ttSharedData */
#define pktLinkDataPtr              pktUserStruct.pktuLinkDataPtr
/* Size of data in the corresponding ttSharedData structure */
#define pktLinkDataLength           pktUserStruct.pktuLinkDataLength
/* Total packet length (of chained scattered data)*/
#define pktChainDataLength          pktUserStruct.pktuChainDataLength
/*
 * Number of links linked to this one (not including this one). Used
 * for Scattered send, to limit the number of scattered buffers to
 * what the device driver can support.
 */
#define pktLinkExtraCount           pktUserStruct.pktuLinkExtraCount
#if defined(TM_DEV_SEND_OFFLOAD) || defined(TM_DEV_RECV_OFFLOAD)
#define pktDevOffloadPtr            pktUserStruct.pktuDevOffloadPtr
#endif /* TM_DEV_SEND_OFFLOAD || TM_DEV_RECV_OFFLOAD */
/* Point to corresponding sharable ttSharedData */
    ttSharedDataPtr                 pktSharedDataPtr;
/* Next packet (head of a new datagram in a queue) */
    struct tsPacket TM_FAR *        pktChainNextPtr;
#ifndef TM_INDRV_INLINE_SEND_RECV
/* For non in-line intramachine device driver recv queue */
    struct tsPacket TM_FAR *        pktRecvNextPtr;
#endif /* TM_INDRV_INLINE_SEND_RECV */
/* Device packet came in from or got out */
    struct tsDeviceEntry TM_FAR *   pktDeviceEntryPtr;
#ifndef TM_LOOP_TO_DRIVER
    struct tsDeviceEntry TM_FAR *   pktOrigDevPtr;
#endif /* !TM_LOOP_TO_DRIVER */

#ifdef TM_USE_IPV6
    union {
/*
 * Used in the receive-path by the first ttPacket in the packet.
 * For IPV6 Points to the pseudo-header/Ip header for the received packet.
 * For IPV4 Points to the IP header for the received packet.
 */
#define pkt6RxPseudoHdrPtr          pktPtrUnion.pkt6UnRxPseudoHdrPtr
#define pkt6RxIphPtr                pktPtrUnion.pkt6UnRxIphPtr
#define pkt6TxPseudoHdrPtr          pktPtrUnion.pkt6UnRxPseudoHdrPtr
#define pkt6TxIphPtr                pktPtrUnion.pkt6UnRxIphPtr
        tt6PseudoHeaderPtr          pkt6UnRxPseudoHdrPtr;
        tt6IpHeaderPtr              pkt6UnRxIphPtr;
    } pktPtrUnion;
#endif /* TM_USE_IPV6 */

/* TCP Time of transmission (Vegas) (sent packet) */
    tt32Bit                         pktTcpXmitTime;
/* User flags: i.e. TM_PKTF_USER_OWNS (for user owned buffers) */
/*
 * User flags: i.e. TM_PKTF_USER_OWNS, TM_PKTF_USER_DEV_OWNS
 * (for user owned buffers)
 */
    tt16Bit                         pktUserFlags;
/* Packet flags one of TM_LL_UNICAST, TM_LL_BROADCAST, TM_LL_UNICAST
 * , plus one of TM_IP_UNICAST_FLAG, TM_IP_BROADCAST_FLAG
 * TM_IP_MULTICAST_FLAG, TM_IP_FORWARD_FLAG, TM_IP_MCAST_FORWARD_FLAG
 * TM_IP_LOCAL_FLAG
 * plus TM_OUTPUT_DEVICE_FLAG, TM_ETHERNET_ADDRESS_FLAG, TM_IP_RTE_FLAG
 */
    tt16Bit                         pktFlags;
/*
 * packet TCP flags for packets in the TCP send queue.
 */
    tt16Bit                         pktFlags2;
    tt16Bit                         pktMhomeIndex;
/* Number of times this packet has been decapsulated. Initially set to zero. */
    tt8Bit                          pktTunnelCount;
    tt8Bit                          pktIpHdrLen;

/*
 * Specifies the network layer type of this packet (IPv4, IPv6, ARP, etc).
 * This replaces the TM_NETWORK_LAYER flags in pktFlags
 */
    tt8Bit                          pktNetworkLayer;

    tt8Bit                          pktFiller[1];




} ttPacket;
typedef ttPacket TM_FAR *       ttPacketPtr;
typedef ttPacketPtr TM_FAR *    ttPacketPtrPtr;


typedef void (TM_CODE_FAR * ttTmCBFuncPtr)(
    ttVoidPtr       timerBlockPtr,
    ttGenericUnion  userParm1,
    ttGenericUnion  userParm2);

typedef void (TM_CODE_FAR * ttTmCUFuncPtr)(
    ttVoidPtr       timerBlockPtr,
    tt8Bit          flags);

typedef struct tsTimeStruct
{
#ifdef TM_USE_TIM_ROLLOVER
    tt32Bit         timRollover;
#endif /* TM_USE_TIM_ROLLOVER */
    tt32Bit         timMsecs;
} ttTimeStruct;

typedef ttTimeStruct TM_FAR * ttTimeStructPtr;

/*
 * Timer Entry Typedef
 */
typedef struct tsTimer
{
    ttNode                 tmrNode;
    ttTmCBFuncPtr          tmrCallBackFunctionPtr;
/* Clean up function, after timer has been removed */
    ttTmCUFuncPtr          tmrCleanUpFunctionPtr;
    ttGenericUnion         tmrUserParm1;
    ttGenericUnion         tmrUserParm2;
    ttTimeStruct           tmrStopTime;
    tt32Bit                tmrInterval;
    tt16Bit                tmrWheelSlot;
/* task, and timer thread owner count */
    tt8Bit                 tmrOwnerCount;
    tt8Bit                 tmrListNo;
    tt8Bit                 tmrFlags;
    tt8Bit                 tmrCallBackFlag;
} ttTimer;

typedef ttTimer    TM_FAR * ttTimerPtr;
typedef ttTimerPtr TM_FAR * ttTimerPtrPtr;

typedef struct tsTimerList
{
    ttList          tmlList;
#ifdef TM_USE_TIMER_CACHE
    tt32Bit         tmlMinInterval;
/* Next time to run this list */
    ttTimeStruct    tmlNextRunTime;
#endif /* TM_USE_TIMER_CACHE */
} ttTimerList;

#ifdef TM_USE_TIMER_WHEEL
typedef struct tsTimerWheel
{
/* Array of timer wheel lists */
    ttListPtr       twlListPtr;
/* Current slot run time */
    ttTimeStruct    twlCurSlotRunTime;
/* Number of timers on the wheel */
    tt32Bit         twlNumberTimers;
/* Current timer wheel slot to execute */
    tt16Bit         twlCurSlotNo;
/* Number of timer wheel slots */
    tt16Bit         twlNumberSlots;
} ttTimerWheel;
#endif /* TM_USE_TIMER_WHEEL */

/* Control block for managing timer queues */
typedef struct tsTimerCtrl
{
    ttTimerList     timerList[TM_TIMER_LISTS];
/* Next timerPtr in the execute loop */
    ttNodePtr       timerExecNextNodePtr;
#ifdef TM_LOCK_NEEDED
/* Timer Execute Lock */
    ttLockEntry     timerExecuteLockEntry;
/* Timer list Lock */
    ttLockEntry     timerListLockEntry;
#endif /* TM_LOCK_NEEDED */
#ifdef TM_USE_TIMER_WHEEL
    ttTimerWheel    timerWheel;
#endif /* TM_USE_TIMER_WHEEL */
#ifdef TM_USE_TIMER_CB
    ttTimeStruct    timerCBTime;
    tt8Bit          timerCBPending;
#endif /* TM_USE_TIMER_CB */
} ttTimerCtrl;

/*
 * NOTE:
 * The message data pointer points to the IP or ARP header
 * For Arp resolved packets:
 * 8 Bytes prior contains the following fields
 * EtherDestination and TYPE when calling lnkSendFuncPtr
 */
typedef int  (TM_CODE_FAR *ttLnkOpenFuncPtr)(void TM_FAR * deviceEntryPtr,
                                             tt16Bit       multiHomeIndex,
                                             int           protocolFamily);
typedef int  (TM_CODE_FAR *ttLnkCloseFuncPtr)(void TM_FAR *deviceEntryPtr);
typedef int  (TM_CODE_FAR *ttLnkSendFuncPtr)(ttPacketPtr packetPtr);
typedef int  (TM_CODE_FAR *ttLnkRecvFuncPtr)(void TM_FAR *deviceEntryPtr,
                                             void TM_FAR *bufferHandle);
typedef int  (TM_CODE_FAR *ttLnkIoctlFuncPtr)(int operation);
typedef int  (TM_CODE_FAR *ttLnkErrorFuncPtr)(int type);
typedef int  (TM_CODE_FAR *ttLnkResolveFuncPtr)(ttPacketPtr packetPtr);
typedef void (TM_CODE_FAR *ttLnkResolveCleanFuncPtr)(
                                    ttVoidPtr               interfaceHandle,
                                    tt4IpAddress            ipAddress,
                                    tt4IpAddress            netMask);
typedef int  (TM_CODE_FAR *ttLnkSendRequestFuncPtr)(
                                    ttVoidPtr               deviceEntryPtr,
                                    tt16Bit                 mhomeIndex,
                                    tt4IpAddress            ipAddress,
                                    ttVoidPtr               rteEntryPtr);
typedef int  (TM_CODE_FAR *ttLnkPostFuncPtr)(ttPacketPtr packetPtr);
typedef void (TM_CODE_FAR *ttLnkNotifyFuncPtr)
    (ttVoidPtr deviceEntryPtr, unsigned int event);
typedef int  (TM_CODE_FAR *ttLnkMcastFuncPtr)(ttVoidPtr     deviceEntryPtr,
                                              tt4IpAddress  ipAddress,
                                              int           command);
typedef int  (TM_CODE_FAR *ttLnkHdrCompressFuncPtr)(ttPacketPtr  packetPtr,
                                                    tt32BitPtr   pktTypePtr,
                                                    ttVoidPtrPtr optPtrPtr,
                                                    tt32Bit      opcode);
#ifdef TM_USE_IPV6
typedef int  (TM_CODE_FAR *tt6LnkMcastFuncPtr)(
    ttVoidPtr                   deviceEntryPtr,
    tt6ConstIpAddressPtr        ipAddress,
    int                         command);
typedef void (TM_CODE_FAR *tt6LnkResIncomingFuncPtr)(
                                    ttPacketPtr             packetPtr,
                                    tt8BitPtr               targLinkAddrPtr,
                                    tt8Bit                  targLinkAddrLen);
typedef void (TM_CODE_FAR *tt6LnkResolveCleanFuncPtr)(
                                    ttVoidPtr               interfaceHandle,
                                    ttIpAddressPtr          ipAddrPtr,
                                    int                     prefixLength);
#endif /* TM_USE_IPV6 */

/*
 * Link Layer Entry Typedef
 */
typedef struct tsLinkLayerEntry
{
    ttLnkOpenFuncPtr                lnkOpenFuncPtr;
    ttLnkCloseFuncPtr               lnkCloseFuncPtr;
    ttLnkSendFuncPtr                lnkSendFuncPtr;
    ttLnkRecvFuncPtr                lnkRecvFuncPtr;
    ttLnkIoctlFuncPtr               lnkIoctlFuncPtr;
    ttLnkErrorFuncPtr               lnkErrorFuncPtr;
    ttLnkResolveFuncPtr             lnkResolveFuncPtr;
    ttLnkResolveCleanFuncPtr        lnkResolveCleanFuncPtr;

#ifdef TM_USE_IPV6
    ttLnkResolveFuncPtr             lnk6ResolveFuncPtr;
    tt6LnkResolveCleanFuncPtr       lnk6ResolveCleanFuncPtr;
    tt6LnkMcastFuncPtr              lnk6McastFuncPtr;
    tt6LnkResIncomingFuncPtr        lnk6ResIncomingFuncPtr;
#endif /* TM_USE_IPV6 */

    ttLnkSendRequestFuncPtr         lnkSendRequestFuncPtr;
    ttLnkMcastFuncPtr               lnkMcastFuncPtr;
    ttLnkPostFuncPtr                lnkPostFuncPtr;
    ttLnkNotifyFuncPtr              lnkNotifyFuncPtr;
    ttLnkHdrCompressFuncPtr         lnkHdrCompressFuncPtr;
    struct tsLinkLayerEntry TM_FAR *lnkNextPtr;
    tt16Bit                         lnkLinkLayerProtocol;
    tt8Bit                          lnkPhysBroadAddr
                                        [tm_align(TM_MAX_PHYS_ADDR)];
    tt8Bit                          lnkNameArray
                                        [tm_align(TM_MAX_LINK_LAYER_NAME)];
    tt16Bit                         lnkMtu;  /* Default for the Link Layer */
    tt8Bit                          lnkHeaderLength;
    tt8Bit                          lnkPhysAddrLen;
    tt8Bit                          lnkMode;
    tt8Bit                          lnkFiller;
} ttLinkLayerEntry;

typedef ttLinkLayerEntry TM_FAR * ttLinkLayerEntryPtr;

/* Network header: Ethernet Header */
typedef struct tsEtherHeader
{
    ttEnetAddress ethDstAddr;
    ttEnetAddress ethSrcAddr;
    tt16Bit       ethType;
} ttEtherHeader;

typedef ttEtherHeader TM_FAR * ttEtherHeaderPtr;

/* Network header: Ethernet Header with VLAN tag fields */
typedef struct tsTaggedEtherHeader
{
    ttEnetAddress ethDstAddr;
    ttEnetAddress ethSrcAddr;
    tt16Bit       ethQTagLengthType;
    tt16Bit       ethQTagControlInfo;
    tt16Bit       ethType;
} ttTaggedEtherHeader;

typedef ttTaggedEtherHeader TM_FAR * ttTaggedEtherHeaderPtr;

/* END of Ethernet network headers */

/* Information structure for dialer, corresponding to one send-expect pair */
typedef struct tsDialerInfo
{

/* pointer to the next entry in the linked list of send-expect pairs */
    struct tsDialerInfo TM_FAR * dialiNextEntryPtr;

/* transmit timeout timer */
    ttTimerPtr                   dialiTimerPtr;

/* string to send to the device  */
    tt8BitPtr                    dialiSendStringPtr;

/* string to expect from the device, indicates sucess */
    tt8BitPtr                    dialiExpectStringPtr;

/* string recieved from device that would indicate error */
    tt8BitPtr                    dialiErrorStringPtr;

/* number of times to retry transmission of sendString */
    tt8Bit                       dialiNumRetries;

/* amount of time in seconds to wait before retransmitting */
    tt8Bit                       dialiTimeout;

    tt8Bit                       dialiFlags;

/* current number of characters matched in the expect string */
    tt8Bit                       dialiExpectMatch;

/* current number of characters match in the error string */
    tt8Bit                       dialiErrorMatch;

    tt8Bit                       dialiPadding[3];

} ttDialerInfo;

typedef ttDialerInfo TM_FAR * ttDialerInfoPtr;

#define TM_DIALER_INFO_NULL_PTR (ttDialerInfoPtr)0

/* Dialer entry structure */
typedef struct tsDialerEntry
{

/*
 * Pointer to old link layer recieve routine.  This is needed because the
 * dialer temporarily overwrites the link layer recieve function pointer so
 * all incoming data on this device is directed at the dialer, not the LL.
 */
    ttLnkRecvFuncPtr             dialLinkRecvFuncPtr;

/* Pointer to old link layer close routine */
    ttLnkCloseFuncPtr            dialLinkCloseFuncPtr;

/* Pointer to user's dialer notification function */
    ttUserLnkNotifyFuncPtr       dialNotifyFuncPtr;

/* Pointer to linked list of send-expect pairs */
    ttDialerInfoPtr              dialInfoPtr;

/* Pointer to dialer open routine */
    ttLnkOpenFuncPtr             dialOpenFuncPtr;

/* The protocol family (IPv6, IPv4) for the link layer (PPP) being opened */
    int                          dialProtocolFamily;

/* Flag indicating success or failure of dialing attempt */
    tt8Bit                       dialSuccess;

/* Flag indicating if the dialer is in the process of closing */
    tt8Bit                       dialCloseFlag;

/* Padding to a multiple of 4-bytes */
    tt8Bit                       dialFiller[2];

} ttDialerEntry;

typedef ttDialerEntry TM_FAR * ttDialerEntryPtr;

#define TM_DIALER_ENTRY_NULL_PTR (ttDialerEntryPtr)0

/* ARP resolution */
typedef struct tsResEntry
{
/* Note: NextPtr need to be first for recycle list */
    struct tsResEntry    TM_FAR *resNextPtr;
    struct tsResEntry    TM_FAR *resPrevPtr;
    ttPacketPtr                  resPacketPtr;
    ttTimerPtr                   resTimerPtr;
    struct tsDeviceEntry TM_FAR *resDeviceEntryPtr;
    tt32Bit                      resRequestTries;
    ttTimer                      resTimeOutTimer;
    tt16Bit                      resMhomeIndex;
    tt8Bit                       resOwnerCount;
    tt8Bit                       resFlags;
} ttResEntry;

typedef ttResEntry TM_FAR * ttResEntryPtr;

/* PROXY ARP entry */
typedef struct tsProxyEntry
{
/* Note: NextPtr need to be first for recycle list */
    struct tsProxyEntry    TM_FAR *proxNextPtr;
    struct tsProxyEntry    TM_FAR *proxPrevPtr;
/* Ip address of proxy entry */
    tt4IpAddress                   proxIpAddress;
} ttProxyEntry;

typedef ttProxyEntry TM_FAR * ttProxyEntryPtr;


#ifdef TM_USE_IPV4
/*
 * BOOTP/DHCP header
 */
typedef struct tsBootHeader
{
/* packet op code / message type. '1' = BOOTREQUEST, '2' = BOOTREPLY */
        tt8Bit      bootOp;
/*
 * hardware address type, see ARP section in "Assigned Numbers" RFC1700.
 * '1' = Ethernet (10 Mb)
 */
        tt8Bit      bootHtype;
/* hardware address length ('6' for 10mb ethernet).*/
        tt8Bit      bootHlen;
/*
 * client sets to zero, optionally used by gateways in cross-gateway
 * booting
 */
        tt8Bit      bootHops;
/*
 * transaction ID, a random number, used to match this boot request with the
 * responses it generates.
 */
        tt32Bit     bootXid;
/* filled in by client, seconds elapsed since client started trying to boot.*/
        tt16Bit     bootSecs;
/* Broadcast bit. */
        tt16Bit     bootFlags;
/* client IP address: should be set to zero */
        tt4IpAddress bootCiaddr;
/*
 * 'your' (client) IP address; filled by server if client doesn't
 * know its own address (ciaddr was 0).
 */
        tt4IpAddress bootYiaddr;
/*
 * server IP address; returned in BOOTREPLY by server.
 * DHCP clarifies the interpretation of the 'siaddr' field as the
 * address of the server to use in the next step of the client's
 * bootstrap process.  A DHCP server may return its own address in the
 * 'siaddr' field, if the server is prepared to supply the next
 * bootstrap service (e.g., delivery of an operating system executable
 * image), in DHCPOFFER, DHCPACK packets.  A DHCP server always returns
 * its own address in the 'server identifier' option.
 */
        tt4IpAddress bootSiaddr;
/* gateway IP address, used in optional BOOTP relay agent booting. */
        tt4IpAddress bootGiaddr;
/* client hardware address, filled in by client (16 bytes). */
        tt8Bit      bootChaddr[TM_BOOTHADDR_SIZE];
/* optional TFTP server host name, null terminated string (64 bytes). */
        tt8Bit      bootSname[TM_BOOTSNAME_SIZE];
/*
 * boot file name, null terminated string; 'generic' name or null in
 * BOOTREQUEST/DHCPDISCOVER, fully qualified directory-path name in
 * BOOTREPLY/DHCPOFFER. (128 bytes)
 */
        tt8Bit      bootFile[TM_BOOTFILENAME_SIZE];
/*
 * optional vendor-specific area, e.g. could be hardware type/serial on
 * request, or 'capability' / remote file system handle on reply.  This
 * info may be set aside for use by a third phase bootstrap or kernel.
 * Called options with DHCP protocol. (64 bytes for BOOTP, 312 bytes
 * for DHCP).
 */
        struct
        {
            tt32Bit     optMagic;
#define optFields    optFieldsUnion.optUnFields
#define optDhcpMsg   optFieldsUnion.optUnDhcpMsg
            union
            {
                tt8Bit      optUnFields[
                                TM_4PAK_DHCP_OPTIONS_LEN - sizeof(tt32Bit)];
/* 4-byte aligned DHCP message */
                tt32Bit     optUnDhcpMsg; /* DHCP message */
            } optFieldsUnion;
        } bootOptions;
} ttBootHeader;

typedef ttBootHeader TM_FAR * ttBootHeaderPtr;

/*
 * Data type for collecting DHCP offers during selecting state.
 * We need at least one of these to hold the BOOTP/DHCP user data.
 */
typedef struct tsBtOfferEntry
{
    ttNode                      btNext;
    struct tsBtEntry TM_FAR *   btEntryPtr;
    ttUserBtEntry               btUserEntry;
/* List of unknown options from the DHCP or BOOTP server */
    ttList                      btUserServCustOpts;
} ttBtOfferEntry;

typedef ttBtOfferEntry TM_FAR * ttBtOfferEntryPtr;

/*
 * Boot entry type. To store information collected from the BOOPT/DHCP
 * server. Also to keep track of DHCP timers. This can grow as needed when
 * we add more features.
 */
typedef struct tsBtEntry
{
/* Back pointer to the device */
    struct tsDeviceEntry TM_FAR * btDevEntryPtr;
#define TM_BT_RETRY_TIMER_INDX          0
#define TM_BT_DHCP_LEASE_TIMER_INDX     1
#define TM_BT_DHCP_RESTART_TIMER_INDX   2
#define TM_BT_DHCP_RENEW_TIMER_INDX     3
#ifndef TM_USE_DHCP_COLLECT
#define TM_BT_NUM_TIMERS                (TM_BT_DHCP_RENEW_TIMER_INDX + 1)
#else /* TM_USE_DHCP_COLLECT */
#define TM_BT_DHCP_COLLECT_TIMER_INDX   4
#define TM_BT_NUM_TIMERS                (TM_BT_DHCP_COLLECT_TIMER_INDX + 1)
#endif /* TM_USE_DHCP_COLLECT */
/* For BOOTP requests /DHCP discover/request retransmissions */
#define btRetryTimerPtr       btTimerPtr[TM_BT_RETRY_TIMER_INDX]
/* For DHCP lease */
#define btDhcpLeaseTimerPtr   btTimerPtr[TM_BT_DHCP_LEASE_TIMER_INDX]
/* For DHCP delay send, and restart after decline */
#define btDhcpRestartTimerPtr btTimerPtr[TM_BT_DHCP_RESTART_TIMER_INDX]
/* For DHCP manual renew */
#define btDhcpRenewTimerPtr   btTimerPtr[TM_BT_DHCP_RENEW_TIMER_INDX]
#ifdef TM_USE_DHCP_COLLECT
/* For collecting/selecting multiple DHCP offers */
#define btDhcpCollectTimerPtr btTimerPtr[TM_BT_DHCP_COLLECT_TIMER_INDX]
#endif /* TM_USE_DHCP_COLLECT */
    ttTimerPtr                    btTimerPtr[TM_BT_NUM_TIMERS];
#ifdef TM_USE_DHCP_FQDN
    ttCharPtr                     btUserFqdnPtr;
#endif /* TM_USE_DHCP_FQDN */
    ttUserDhcpNotifyFuncPtr       btDhcpNotifyFuncPtr;
    ttList                        btOfferEntryList;
    ttBtOfferEntryPtr             btOfferEntryPtr;
/* 2nd phase BOOT Server (TFTP server) */
#define btBootSIpAddress          btOfferEntryPtr->btUserEntry.btuBootSIpAddress
/* Domain name server (for DNS) */
#define btDns1ServerIpAddress     btOfferEntryPtr->btUserEntry.btuDns1ServerIpAddress
/* Second domain name server (for DNS) */
#define btDns2ServerIpAddress     btOfferEntryPtr->btUserEntry.btuDns2ServerIpAddress
/* Our (leased) IP address */
#define btYiaddr                  btOfferEntryPtr->btUserEntry.btuYiaddr
/* Our subnet mask */
#define btNetMask                 btOfferEntryPtr->btUserEntry.btuNetMask
/* Default router */
#define btDefRouter               btOfferEntryPtr->btUserEntry.btuDefRouter
/* Default router after lease renewal if different */
#define btLeaseDefRouter          btOfferEntryPtr->btUserEntry.btuLeaseDefRouter
/* DHCP selected server IP address */
#define btDhcpServerId            btOfferEntryPtr->btUserEntry.btuDhcpServerId
/* Time stamp of DHCP request */
#define btDhcpRequestTimeStamp    btOfferEntryPtr->btUserEntry.btuDhcpRequestTimeStamp
/* DHCP Address lease time */
#define btDhcpLeaseTime           btOfferEntryPtr->btUserEntry.btuDhcpLeaseTime
/* DHCP T1 time */
#define btDhcpT1                  btOfferEntryPtr->btUserEntry.btuDhcpT1
/* DHCP T2 time */
#define btDhcpT2                  btOfferEntryPtr->btUserEntry.btuDhcpT2
/* Domain name (64 bytes) (for DNS) */
#define btDomainName              btOfferEntryPtr->btUserEntry.btuDomainName
/* TFTP server name (64 bytes) (for TFTP download) */
#define btBootSname               btOfferEntryPtr->btUserEntry.btuBootSname
/* Boot file name (128 bytes) (for TFTP download) */
#define btBootFileName            btOfferEntryPtr->btUserEntry.btuBootFileName
/* Boot file size (in 512-bytes blocks) (for TFTP download) */
#define btBootFileSize            btOfferEntryPtr->btUserEntry.btuBootFileSize
/* NBNS name servers (array of IP addresses) */
#define btNetBiosNameServers      btOfferEntryPtr->btUserEntry.btuNetBiosNameServers
#define btNetBiosNumNameServers   btOfferEntryPtr->btUserEntry.btuNetBiosNumNameServers
/* seconds since we started sending a BOOTP request/DHCP discover*/
#define btSeconds                 btOfferEntryPtr->btUserEntry.btuSeconds
#define btDhcpClientIdLength      btOfferEntryPtr->btUserEntry.btuDhcpClientIdLength
#define btDhcpClientIdPtr         btOfferEntryPtr->btUserEntry.btuDhcpClientIDPtr
#define btDhcpHostNameLength      btOfferEntryPtr->btUserEntry.btuDhcpHostNameLength
#define btDhcpHostNamePtr         btOfferEntryPtr->btUserEntry.btuDhcpHostNamePtr
#define btDhcpRxHostNameLength    btOfferEntryPtr->btUserEntry.btuDhcpRxHostNameLength
#define btDhcpRxHostNamePtr       btOfferEntryPtr->btUserEntry.btuDhcpRxHostNamePtr
/* Unique ID that indicates BT_CONF or BT_USER, and indicates index */
    tt32Bit                       btXid;
/* List of custom user options for DHCP or BOOTP */
    ttList                        btUserSetCustOpts;
/* User passed parameters */
    ttUserIpAddress               btUserSetDhcpIpAddress;
    tt8Bit                        btUserSetDhcpClientIdPtr[
                                        ((TM_DHCP_CLIENTID_SIZE + 3) /4) * 4];
    tt8Bit                        btUserSetDhcpHostNamePtr[
                                        ((TM_DHCP_HOSTNAME_SIZE + 3) /4) * 4];
#define btRetryTimer       btTimer[TM_BT_RETRY_TIMER_INDX]
#define btDhcpLeaseTimer   btTimer[TM_BT_DHCP_LEASE_TIMER_INDX]
#define btDhcpRestartTimer btTimer[TM_BT_DHCP_RESTART_TIMER_INDX]
#define btDhcpRenewTimer   btTimer[TM_BT_DHCP_RENEW_TIMER_INDX]
#ifdef TM_USE_DHCP_COLLECT
#define btDhcpCollectTimer btTimer[TM_BT_DHCP_COLLECT_TIMER_INDX]
#endif /* TM_USE_DHCP_COLLECT */
/* Pre-allocated timers, pointed to by btRetryTimerPtr,
 * btDhcpLeaseTimerPtr, btDhcpRestartTimerPtr, btDhcpRenewTimerPtr
 */
    ttTimer                       btTimer[TM_BT_NUM_TIMERS];
/*
 * index (in either multi-home array (btType == TM_BT_CONF), or
 * user table (btType == TM_BT_USER)
 */
    tt16Bit                       btIndex;
    tt8Bit                        btUserSetDhcpClientIdLength;
    tt8Bit                        btUserSetDhcpHostNameLength;
/* Indicate which parameters the user set */
    tt8Bit                        btUserSetFlags;
    tt8Bit                        btLeaseFlags;
/* DHCP state machine state */
    tt8Bit                        btDhcpState;
/* number of retries */
    tt8Bit                        btRetries;
/* multi-home entry (TM_BT_CONF) or User entry (TM_BT_USER) */
    tt8Bit                        btType;
/* Manual lease renewal retries */
    tt8Bit                        btDhcpRenewRetries;
    tt8Bit                        btBootIndex; /* BOOTP, or DHCP */
/* General bt entry flags. Used for open socket indication */
    tt8Bit                        btFlags;
#ifdef TM_USE_DHCP_FQDN
    tt16Bit                       btUserFqdnLen;
    tt8Bit                        btFqdnFlags;
#define btFqdnStatus              btOfferEntryPtr->btUserEntry.btuFqdnStatus
#define btFqdnRCode1              btOfferEntryPtr->btUserEntry.btuFqdnRCode1
#define btFqdnRCode2              btOfferEntryPtr->btUserEntry.btuFqdnRCode2
/* FQDN received from the server Ascii format */
#define btServerAFqdn             btOfferEntryPtr->btUserEntry.btuServerFqdn
/* FQDN received from the server Binary format */
#define btServerBFqdn             btOfferEntryPtr->btUserEntry.btuServerBFqdn
/*
 * Length of FQDN received from the server, stored as an int for user
 * consumption
 */
#define btServerFqdnLen           btOfferEntryPtr->btUserEntry.btuServerFqdnLen
/* Length of FQDN received from the server Ascii format */
#define btServerFqdnALen          btOfferEntryPtr->btUserEntry.btuDhcpFqdnALength
/* Length of FQDN received from the server Binary format */
#define btServerFqdnBLen          btOfferEntryPtr->btUserEntry.btuDhcpFqdnBLength
#endif /* TM_USE_DHCP_FQDN */
#ifdef TM_USE_DHCP_COLLECT
/*
 * Support for DHCP offer collection and selection.
 */
/* User's preferred IP address */
    tt4IpAddress                  btPrefAddr;
/* Maximum number of offers in the cache */
    unsigned int                  btCollectSize;
/* Maximum time (seconds) to collect offers after the first offer arrives. */
    unsigned int                  btCollectTime;
#endif /* TM_USE_DHCP_COLLECT */

} ttBtEntry;

typedef  ttBtEntry    TM_FAR   * ttBtEntryPtr;
typedef  ttBtEntryPtr TM_FAR   * ttBtEntryPtrPtr;

typedef int (TM_CODE_FAR * ttDevBootFuncPtr)( void TM_FAR * deviceEntryPtr,
                                              int           flag,
                                              tt16Bit       multiHomeIndex );

typedef void (TM_CODE_FAR * ttDevBootRecvFuncPtr)(ttPacketPtr  packetPtr,
                                                  ttBtEntryPtr bootEntryPtr);

/* Concurrent BootP/DHCP structure for array in device entry structure */
typedef struct tsBootProtoInfo
{     
/* BOOTP or DHCP configure entry point */
    ttDevBootFuncPtr        bootFuncPtr;
/* BOOTP or DHCP recv call back function */
    ttDevBootRecvFuncPtr    bootRecvFuncPtr;
/* User notify function for BOOTP/DHCP configuration completion */
    ttDevNotifyFuncPtr      bootNotifyFuncPtr;
} ttBootProtoInfo;
typedef  ttBootProtoInfo    TM_FAR   * ttBootProtoInfoPtr;
typedef  ttBootProtoInfoPtr TM_FAR   * ttBootProtoInfoPtrPtr;

typedef struct tsBtPktData
{
/* Pointer to the current option */
    tt8BitPtr       bpdBootOptionPtr;
#ifdef TM_USE_DHCP_SEND_OVERLOAD
/* Pointer to the BOOTP/DHCP header */
    ttBootHeaderPtr bpdBootHdrPtr;
/* Byte offset of current "sname" field option */
    ttPktLen        bpdSnameOffset;
/* Byte offset of current "file" field option */
    ttPktLen        bpdFileOffset;
#endif /* TM_USE_DHCP_SEND_OVERLOAD */
} ttBtPktData;
typedef ttBtPktData TM_FAR * ttBtPktDataPtr;

#endif /* TM_USE_IPV4 */

#ifdef TM_USE_DHCP_FQDN
/* Hold the FQDN main information */
typedef struct tsFqdn
{
    char            domainName[TM_FQDN_MAX_LEN + 1];
    tt8Bit          domainNameLen;
    tt8Bit          domainFlags;
} ttFqdn;
#endif /* TM_USE_DHCP_FQDN */

typedef struct tsBtUserCustOpt
{
/* List header */
    ttNode               buoListNode;
/* Pointer to buffer containing option data */
    ttCharPtr            buoDataPtr;
/* Length of option data */
    tt16Bit              buoDataLen;
/* Option */
    tt8Bit               buoBootOption;
/* Pad length to a multiple of 32 bits (option data follows structure) */
    tt8Bit               buoReserved;
} ttBtUserCustOpt;
typedef ttBtUserCustOpt TM_FAR * ttBtUserCustOptPtr;

typedef int (TM_CODE_FAR * ttDevRefillPoolFuncPtr)(
                                        ttUserInterface interfaceHandle );

typedef int (TM_CODE_FAR * ttDevEmptyXmitFuncPtr)(
                                        ttUserInterface interfaceHandle );

/*
 * One element in the ring of queued transmit buffers
 */
typedef struct tsRingEntry
{
#ifdef TM_USE_DRV_ONE_SCAT_SEND
    ttUserPacketPtr ringPacketUPtr;
#endif /* TM_USE_DRV_ONE_SCAT_SEND */
    ttCharPtr       ringDataPtr; /* Buffer pointer */
    tt16Bit         ringDataLength;  /* Buffer length */
/* Buffer flag (TM_USER_BUFFER_MORE or TM_USER_BUFFER_LAST) */
    tt16Bit         ringDataFlag;
} ttRingEntry;

typedef ttRingEntry TM_FAR * ttRingEntryPtr;

/*
 * Device driver transmit queue structure
 */
typedef struct tsDevXmitEntry
{
/* Number of slots in the device driver transmit ring of queued buffers */
    tt16Bit            xmitSlots;
/* Number of transmitted bytes in the current packet */
    tt16Bit            xmitBytes;
/* First element in device driver transmit queue */
    ttS16Bit           xmitReadIndex;
/* End (one past last) element in device driver transmit queue */
    ttS16Bit           xmitWriteIndex;
/* TM_RING_EMPTY, TM_RING_FULL, TM_RING_OTHER */
    tt8Bit             xmitFlag;

/* Transmission error in current packet */
    tt8Bit             xmitErrorFlag;
    tt8Bit             xmitFiller[2];
/* Device driver transmit ring of queued buffers */
    ttRingEntry        xmitRing[1]; /* variable length */
} ttDevXmitEntry;

/* device driver transmit queue pointer */
typedef ttDevXmitEntry  TM_FAR * ttDevXmitEntryPtr;


/*
 * TCP sequence numbering (used in ttNatTrigger and ttTcpHeader)
 */

typedef tt32Bit  ttSqn; /* 32-bit sequence number */

#ifdef TM_USE_TCP_IO
/*
 * TCP types common between trtcp.c and trtcpio.c
 */
/* ALigned TCP Time stamp option */
typedef struct tsTcpAlgnTsOpt
{
    tt32Bit  tcpoAFirstWord; /* NOOP, NOOP, Kind, Length */
    tt32Bit  tcpoAVal;       /* time stamp value */
    tt32Bit  tcpoAEchoRpl;   /* time stamp echo reply */
} ttTcpAlgnTsOpt;

typedef ttTcpAlgnTsOpt     TM_FAR * ttTcpAlgnTsOptPtr;
#endif /* TM_USE_TCP_IO */


/*
 * NAT
 *
 */
typedef struct tsNatTrigger    /* interceptor of inbound or outbound packets */
{
    struct tsNatTrigger TM_FAR  *ntrNextPtr;    /* device's list of triggers */
    struct tsNatTrigger TM_FAR  *ntrSpawnPtr;   /* type SESSION -> type NAPT */
    tt4IpAddress                 ntrIpPrivate;
    tt4IpAddress                 ntrIpPublic;
    tt4IpAddress                 ntrIpRemote;
    tt32Bit                      ntrTtl;             /* TM_NTRTTL_... seconds*/
    ttSqn                        ntrOutSeqDeltaOld;  /* host order           */
    ttSqn                        ntrOutSeqThreshold; /* Private, host order  */
    ttSqn                        ntrOutSeqDeltaNew;  /* host order           */
    ttIpPort                     ntrPortPrivate;     /* aka ntrPortPublicNext*/
    ttIpPort                     ntrPortPublic;      /* aka ntrPortPublicMin */
    ttIpPort                     ntrPortRemote;      /* aka ntrPortPublicMax */
    tt16Bit                      ntrIpIdPrivate;     /* IP ID for fragments  */
    tt16Bit                      ntrIpIdPublic;      /* IP ID for fragments  */
    tt8Bit                       ntrType;            /* TM_NTRTYPE_...       */
    tt8Bit                       ntrFlag;            /* TM_NTRFLAG_...       */
} ttNatTrigger;
typedef ttNatTrigger TM_FAR *ttNatTriggerPtr;

/* Double-duty members of ttNatTrigger:         */
/*                                              */
/*      when ntrType is    when ntrType is      */
/*      NTRTYPE_NAPT       NTRTYPE_...SESSION   */
/*      (host byte order)  (network byte order) */
/*      -----------------  -----------------    */
#define ntrPortPublicNext  ntrPortPrivate
#define ntrPortPublicMin   ntrPortPublic
#define ntrPortPublicMax   ntrPortRemote

typedef int ( TM_CODE_FAR * ttNatFuncPtr)( ttPacketPtrPtr packetPtrPtr,
                                           int            flag );

#if 0
/*
 * Crypto library, used by IPsec or SSL
 */
typedef struct tsCryptoLibGlobal
{
    ttCryptoEngineListPtr       clgCryptoEngineHeadPtr;
}
ttCryptoLibGlobal;
typedef ttCryptoLibGlobal TM_FAR * ttCryptoLibGlobalPtr;
#endif


#if (defined(TM_SNMP_MIB) || defined(TM_PPP_LQM))
/* IPv6 SNMP MIB, implemented per interface when TM_SNMP_MIB is #define'd. */
typedef struct tsIfStatMib
{
    tt64Bit ipIfStatsHCInReceives;
    tt64Bit ipIfStatsHCInOctets;
    tt32Bit ipIfStatsInHdrErrors;
    tt32Bit ipIfStatsInNoRoutes;
    tt32Bit ipIfStatsInAddrErrors;
    tt32Bit ipIfStatsInUnknownProtos;
    tt32Bit ipIfStatsInTruncatedPkts;
    tt64Bit ipIfStatsHCInForwDatagrams;
    tt32Bit ipIfStatsReasmReqds;
    tt32Bit ipIfStatsReasmOKs;
    tt32Bit ipIfStatsReasmFails;
    tt32Bit ipIfStatsInDiscards;
    tt64Bit ipIfStatsHCInDelivers;
    tt64Bit ipIfStatsHCOutRequests;
    tt32Bit ipIfStatsOutNoRoutes;
    tt64Bit ipIfStatsHCOutForwDatagrams;
    tt32Bit ipIfStatsOutDiscards;
    tt32Bit ipIfStatsOutFragReqds;
    tt32Bit ipIfStatsOutFragOKs;
    tt32Bit ipIfStatsOutFragFails;
    tt32Bit ipIfStatsOutFragCreates;
    tt64Bit ipIfStatsHCOutTransmits;
    tt64Bit ipIfStatsHCOutOctets;
    tt64Bit ipIfStatsHCInMcastPkts;
    tt64Bit ipIfStatsHCInMcastOctets;
    tt64Bit ipIfStatsHCOutMcastPkts;
    tt64Bit ipIfStatsHCOutMcastOctets;
    tt64Bit ipIfStatsHCInBcastPkts;
    tt64Bit ipIfStatsHCOutBcastPkts;
} ttIfStatMib;
typedef ttIfStatMib TM_FAR * ttIfStatMibPtr;
typedef const ttIfStatMib TM_FAR * ttConstIfStatMibPtr;
#endif /* TM_SNMP_MIB or TM_PPP_LQM */


#if (defined(TM_SNMP_MIB) && defined(TM_USE_IPV6))
/* ICMPv6 SNMP MIB, when TM_SNMP_MIB is #define'd. */
typedef struct ts6Icmpv6Mib
{
    tt32Bit icmpv6InDestUnreachs;
    tt32Bit icmpv6InEchos;
    tt32Bit icmpv6InEchoReplies;
    tt32Bit icmpv6InErrors;
    tt32Bit icmpv6InMcastLstnrDone;
    tt32Bit icmpv6InMcastLstnrQuery;
    tt32Bit icmpv6InMcastLstnrResp;
    tt32Bit icmpv6InMsgs;
    tt32Bit icmpv6InNeighborAdvertisements;
    tt32Bit icmpv6InNeighborSolicits;
    tt32Bit icmpv6InParmProblems;
    tt32Bit icmpv6InPktTooBigs;
    tt32Bit icmpv6InRedirects;
    tt32Bit icmpv6InRouterAdvertisements;
    tt32Bit icmpv6InRouterSolicits;
    tt32Bit icmpv6InTimeExcds;
    tt32Bit icmpv6OutDestUnreachs;
    tt32Bit icmpv6OutEchos;
    tt32Bit icmpv6OutEchoReplies;
    tt32Bit icmpv6OutErrors;
    tt32Bit icmpv6OutMcastLstnrDone;
    tt32Bit icmpv6OutMcastLstnrQuery;
    tt32Bit icmpv6OutMcastLstnrResp;
    tt32Bit icmpv6OutMsgs;
    tt32Bit icmpv6OutNeighborAdvertisements;
    tt32Bit icmpv6OutNeighborSolicits;
    tt32Bit icmpv6OutParmProblems;
    tt32Bit icmpv6OutPktTooBigs;
    tt32Bit icmpv6OutRedirects;
    tt32Bit icmpv6OutRouterAdvertisements;
    tt32Bit icmpv6OutRouterSolicits;
    tt32Bit icmpv6OutTimeExcds;
    tt32Bit icmpv6InAdminProhibs;
} tt6Icmpv6Mib;
typedef tt6Icmpv6Mib TM_FAR * tt6Icmpv6MibPtr;
typedef const tt6Icmpv6Mib TM_FAR * ttConst6Icmpv6MibPtr;
#endif /* TM_SNMP_MIB and TM_USE_IPV6 */

#if (defined(TM_OPTIMIZE_MANY_MHOMES) && !defined(TM_SINGLE_INTERFACE_HOME))
/* used to sort IP addresses to improve performance of IP address lookup in the
   receive-path when many IP aliases are configured on a single interface.
   The SNMP Agent can use this to speed up non-exact match processing
   in tfIpAddrTableEntryGet. */

typedef struct tsIpAddrEntry
{
    unsigned int devIndex;
    unsigned int mHomeIndex;
} ttIpAddrEntry;
typedef ttIpAddrEntry TM_FAR * ttIpAddrEntryPtr;

typedef struct tsSortedIpAddrCache
{
#ifdef TM_LOCK_NEEDED
    ttLockEntry         sipcLockEntry;  /* lock for this structure */
#endif /* TM_LOCK_NEEDED */
/* IP address cache */
    ttIpAddrEntryPtr    sipcIpAddrArray;
/* Count of IP address entries in cache */
    tt32Bit             sipcIpAddrArrayCount;
/* Pointer to entry last read in the cache */
    ttIpAddrEntryPtr    sipcLastReadPtr;
/* Current Serial number to keep track of cache updates */
    tt32Bit             sipcSerialNum;
/* Copy of Serial number at last cache reading */
    tt32Bit             sipcSerialNumAtLastRead;
} ttSortedIpAddrCache;

typedef ttSortedIpAddrCache TM_FAR * ttSortedIpAddrCachePtr;
#endif /* TM_OPTIMIZE_MANY_MHOMES and not TM_SINGLE_INTERFACE_HOME */


#ifdef TM_USE_IPV6
typedef struct ts6RtDefaulRouterHead
{
/* IPv6 Default Router Lists.
 * List index 0 populated by ICMPv6 router discovery, and non temporary
 * user added gateways.
 * List index 1 populated by the user gateways added as temporary.
 */
#if 0
    ttList                  drh6RouterList[TM_6_NUM_DEF_ROUTER_LISTS]; 
#endif
    ttTimerPtr              drh6RouterTimerPtr;
/* The number of entries in the IPv6 Default Router Lists */
    tt16Bit                 drh6RouterCount;
    tt16Bit                 drh6Pad;
} tt6RtDefRouterHead;

typedef tt6RtDefRouterHead TM_FAR * tt6RtDefRouterHeadPtr;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_RFC3484
/*
 * keep track of configured IPv6 addresses in scope index list.
 */
typedef struct ts6AddrCacheInfo {
    ttNode                  aciNode;
    tt16Bit                 aciMhomeIndex;
/* Address label (per policy table) */
    tt8Bit                  aciScopeIndex;
/* Address scope index (link local, global, etc) */
    tt8Bit                  aciLabel;
} tt6AddrCacheInfo;

typedef tt6AddrCacheInfo TM_FAR * tt6AddrCacheInfoPtr;
#endif /* TM_USE_RFC3484 */

/*
 * Device Entry Typedef
 */
typedef struct tsDeviceEntry
{
#ifndef TM_SINGLE_INTERFACE_HOME
    ttNode                  devNodeEntry;
    ttListPtr               devListPtr;
#endif /* !TM_SINGLE_INTERFACE_HOME */
#ifndef TM_LOOP_TO_DRIVER
    struct tsDeviceEntry TM_FAR * devOrigDevPtr;
#endif /* !TM_LOOP_TO_DRIVER */
#ifdef TM_MULTIPLE_CONTEXT
    ttUserContext           devContextPtr;
#endif /* TM_MULTIPLE_CONTEXT */
/* Device Function Entries */
    ttDevOpenCloseFuncPtr   devOpenFuncPtr;
    ttDevOpenCloseFuncPtr   devCloseFuncPtr;
    ttDevSendFuncPtr        devSendFuncPtr;
    ttDevSendFuncPtr        devSavedSendFuncPtr;
#ifdef TM_USE_DRV_ONE_SCAT_SEND
    ttDevOneScatSendFuncPtr devOneScatSendFuncPtr;
    ttDevOneScatSendFuncPtr devSavedOneScatSendFuncPtr;
#endif /* TM_USE_DRV_ONE_SCAT_SEND */
#ifdef TM_USE_DRV_SCAT_RECV
    ttDevScatRecvFuncPtr    devScatRecvFuncPtr;
#endif /* TM_USE_DRV_SCAT_RECV */
#ifdef TM_USE_DCACHE_MANAGEMENT
/* Driver function to invalidate the dcache */
    ttDevCacheMgmtFuncPtr   devCacheInvalFuncPtr;
/* User data to pass to dcache invalidation driver function */
    ttUserGenericUnion      devCacheInvalUserData;
/* Driver function to flush the dcache */
    ttDevCacheMgmtFuncPtr   devCacheFlushFuncPtr;
/* User data to pass to dcache flush driver function */
    ttUserGenericUnion      devCacheFlushUserData;
/* The original driver send function. */
    ttDevSendFuncPtr        devCacheSavedSendFuncPtr;
#ifdef TM_USE_DRV_ONE_SCAT_SEND
/* The original driver one-scatter-send function */
    ttDevOneScatSendFuncPtr devCacheSavedOneScatSendFuncPtr;
#endif /* TM_USE_DRV_ONE_SCAT_SEND */
#endif /* TM_USE_DCACHE_MANAGEMENT */
    ttDevRecvFuncPtr        devRecvFuncPtr;
    ttDevFreeRecvFuncPtr    devFreeRecvFuncPtr;
    ttDevIoctlFuncPtr       devIoctlFuncPtr;
    ttDevEmptyXmitFuncPtr   devEmptyXmitFuncPtr;
    ttDevRefillPoolFuncPtr  devRefillPoolFuncPtr;
    ttDevGetPhysAddrFuncPtr devGetPhysAddrFuncPtr;
#ifdef TM_USE_IPV4
/*
 * Bootp/Dhcp boot info structure (config entry point, recv call back function,
 * use notify function
 */
#define devBootInfoBootp    devBootInfo[TM_BOOT_BOOTP]
#define devBootInfoDhcp     devBootInfo[TM_BOOT_DHCP]
    ttBootProtoInfo         devBootInfo[TM_BOOT_MAX_TYPES];
#endif /* TM_USE_IPV4 */

/* Head of recv queue (Intra machine, or loop back only) */
    ttPacketPtr             devReceiveQueuePtr;
/* Pointer to last packet in recv queue (Intra machine, or loop back only) */
    ttPacketPtr             devRcvLastQueuePtr;
/* Head of send queue (for packets waiting to be sent) */
    ttPacketPtr             devSendQueuePtr;
/* Last packet in the send queue */
    ttPacketPtr             devSendQueueLastPtr;
/* Current packet being sent in the device driver */
    ttPacketPtr             devSendQueueCurPtr;
/*
 * Pointer to next packet in the send queue, that the transmit task need
 * to send. Used only if transmit task option is set.
 */
    ttPacketPtr             devXmitTaskPacketPtr;
/*
 * Pointer to device driver transmit queue (for buffers waiting for room)
 * Non null only if user set the corresponding device option.
 */
    ttDevXmitEntryPtr       devXmitEntryPtr;
/* Current pointer to incoming data in interface loop back driver */
    tt8BitPtr               devReceiveDataPtr;
/* Pointer to device receive pool, if user created one */
    ttVoidPtr               devPoolHeadPtr;
/* ARP resolution */
    ttResEntryPtr           devResEntryPtr;
#ifdef TM_USE_STRONG_ESL
    struct tsRteEntry TM_FAR * dev4RejectDefaultGatewayPtr;
    struct tsRteEntry TM_FAR * dev4DefaultGatewayPtr;
#ifdef TM_USE_IPV6
    tt6RtDefRouterHead      dev6DefaultRouterHead;
#endif /* TM_USE_IPV6 */
#endif /* TM_USE_STRONG_ESL */

#ifdef TM_USE_IPV4
    ttBtEntryPtrPtr         devBtEntryTablePtr[TM_BT_USER + 1][TM_BOOT_MAX_TYPES];
/*
 * For BOOTP, DHCP. First slot is reserved to configure the device in
 * slot 0.
 */
#define devBootpEntryPtr            devBtConfEntryTablePtr[TM_BOOT_BOOTP][0]
#define devDhcpEntryPtr             devBtConfEntryTablePtr[TM_BOOT_DHCP][0]
/* Automatic DHCP/BOOTP configuration entries */
#define devBtConfEntryTablePtr      devBtEntryTablePtr[TM_BT_CONF]
#define devBootpConfEntryTablePtr   devBtConfEntryTablePtr[TM_BOOT_BOOTP]
#define devDhcpConfEntryTablePtr    devBtConfEntryTablePtr[TM_BOOT_DHCP]
/*
 * Pointer to a table containing pointers for user Bootp/DHCP requests.
 * To be used by the user (either to obtain IP addresses for its own
 * use or for non automatic configuration of the device.)
 */
#define devBtUserEntryTablePtr      devBtEntryTablePtr[TM_BT_USER]
#define devBootpUserEntryTablePtr   devBtUserEntryTablePtr[TM_BOOT_BOOTP]
#define devDhcpUserEntryTablePtr    devBtUserEntryTablePtr[TM_BOOT_DHCP]
#ifdef TM_IGMP
/* Pointer to list of IP multicast addresses joined on this interface */
    ttVoidPtr               devIgmpPtr;
#define devIgmpV1TmrPtr devIgmpVTmrPtr[TM_IGMP_V1]
/* Timer activated when an IGMP V1/V2 query is received */
    ttTimerPtr              devIgmpVTmrPtr[TM_IGMP_MAX_VERSION - 1];
#endif /* TM_IGMP */
#endif /* TM_USE_IPV4 */

#if (defined(TM_IGMP) || defined(TM_USE_IPV6))
/* Pointer to array of owner counts for Ethernet mcast entries */
    tt16BitPtr              devLnkMcastOwnerCountPtr;
#endif /* TM_IGMP || TM_USE_IPV6 */

    ttLinkLayerEntryPtr     devLinkLayerProtocolPtr;

#ifdef TM_USE_IPV6
/* Neighbor Discovery address resolution */
    ttResEntryPtr           dev6ResEntryPtr;
/* user-specified callback function for IPv6-specific address configuration
   events */
    tt6DevAddrNotifyFuncPtr dev6AddrNotifyFuncPtr;
/* list of IPv6 multicast addresses joined on this interface */
    ttVoidPtr               dev6MldPtr; /* tt6MldEntryPtr */
#ifdef TM_6_USE_MLDV2
/* list of IPv6 multicast addresses actively leaving this interface */
    ttVoidPtr               dev6MldLeavePtr; /* tt6MldEntryPtr */
#endif /* TM_6_USE_MLDV2 */
#ifdef TM_6_USE_DAD
/* list of IPv6 tentative addresses stored on this interface on which we are
   performing Duplicate Address Detection */
    ttVoidPtr               dev6DadPtr; /* tt6DadEntryPtr */
#endif /* TM_6_USE_DAD */
#ifdef TM_6_USE_MLDV2
/* Keep track of MLDv1 routers on network */
    ttTimerPtr              dev6MldV1TmrPtr;
/* General query timer */
    ttTimerPtr              dev6MldQueryTmrPtr;
#endif /* TM_6_USE_MLDV2 */
/* timer used for router solicitation retransmissions */
    ttTimerPtr              dev6RtrSolTimerPtr;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_IPV4
/* NAT fields, used by trnat.c */
    ttNatFuncPtr            devNatFuncPtr;
    ttNatTriggerPtr         devNatTriggerHead;
    ttTimerPtr              devNatTimer;

#endif /* TM_USE_IPV4 */

/*
 * Only used in a virtual tunnel device.  Pointer to the original device
 * entry.  Currently used for source address selection.
 */
    struct tsDeviceEntry TM_FAR * devTunnelEntryPtDevPtr;
#define devStateVectorPtr   devLinkUnion.devuStateVectorPtr
#define devLnkMcastPtr      devLinkUnion.devuLnkMcastPtr
    union
    {
/*
 * State vector Used by PPP or SLIP
 */
        ttVoidPtr           devuStateVectorPtr;
/* Pointer to list of ethernet multicast addresses */
        ttVoidPtr           devuLnkMcastPtr;
    } devLinkUnion;
/*
 * Pointer to dialer structure:  if this pointer is non null, the
 * dialer is enabled.
 */
    ttDialerEntryPtr        devDialerEntryPtr;
    ttVoidPtr               devDriverPtr;
    tt32Bit                 devBytesNotified;
    tt32Bit                 devPacketsNotified;
#ifdef TM_FORWARDING_STATS
    tt32Bit                 devForwRxPkts;
    ttIntfStatBignum        devForwRxBytes;
    tt32Bit                 devForwTxPkts;
    ttIntfStatBignum        devForwTxBytes;
#endif /* TM_FORWARDING_STATS */
#if (defined(TM_SNMP_MIB) || defined(TM_PPP_LQM))
    ttIfStatMib             dev4Ipv4Mib;
#endif /* TM_SNMP_MIB */

#ifdef TM_SNMP_MIB
    tt32Bit                 devLastChange;
#define devInOctets         tm_get_64bit_low(dev4Ipv4Mib.ipIfStatsHCInOctets)
#define devInUnknownProtos  dev4Ipv4Mib.ipIfStatsInUnknownProtos
#define devOutDiscards      dev4Ipv4Mib.ipIfStatsOutDiscards
    tt32Bit                 devOutErrors;
    tt32Bit                 devOutQLen;
#define devOutOctets        tm_get_64bit_low(dev4Ipv4Mib.ipIfStatsHCOutOctets)
#endif /* TM_SNMP_MIB */

#if (defined(TM_SNMP_MIB) || defined(TM_PPP_LQM))
    tt32Bit                 devInUcastPkts;
#define devInMulticastPkts  tm_get_64bit_low(dev4Ipv4Mib.ipIfStatsHCInMcastPkts)
#define devInBroadcastPkts  tm_get_64bit_low(dev4Ipv4Mib.ipIfStatsHCInBcastPkts)
#define devInDiscards       dev4Ipv4Mib.ipIfStatsInDiscards
    tt32Bit                 devInErrors;
    tt32Bit                 devOutUcastPkts;
#define devOutMulticastPkts tm_get_64bit_low(dev4Ipv4Mib.ipIfStatsHCOutMcastPkts)
#define devOutBroadcastPkts tm_get_64bit_low(dev4Ipv4Mib.ipIfStatsHCOutBcastPkts)
#endif /* (TM_SNMP_MIB or TM_PPP_LQM) */

#ifdef TM_PPP_LQM
    tt32Bit         devLqmOutLqrs;      /* RFC-1989: OutLQRs counter */
    tt32Bit         devLqmInLqrs;       /* RFC-1989: InLQRs counter */
    tt32Bit         devLqmInGoodOctets; /* RFC-1989: InGoodOctets counter */
    tt32Bit         devLqmOutOctets;    /* RFC-1989: ifOutOctets counter */
#endif /* TM_PPP_LQM */

#if (defined(TM_SNMP_MIB) && defined(TM_USE_IPV6))
    ttIfStatMib             dev6Ipv6Mib;
#endif /* TM_SNMP_MIB and TM_USE_IPV6 */

/* IP address/netMask (multihoming) */
#ifdef TM_SINGLE_INTERFACE_HOME
    tt4IpAddress            devIpAddr;
    tt4IpAddress            devNetMask;
    tt4IpAddress            devDestIpAddr; /* for SLIP/PPP */

#ifdef TM_USE_VCHAN
#ifdef TM_USE_IPV4
/* Virtual channel */
    tt32Bit                 devVChan;
#endif /* TM_USE_IPV4 */
#endif /* TM_USE_VCHAN */

#define devDBroadIpAddr     devDestIpAddr   /* for LAN, directed broadcast */
#define devPt2PtPeerIpAddr  devDestIpAddr   /* for PPP or SLIP */
#else /* ! TM_SINGLE_INTERFACE_HOME */
#ifdef TM_USE_IPV4
    tt4IpAddress            devIpAddrArray[TM_MAX_IPS_PER_IF];
    tt4IpAddress            devNetMaskArray[TM_MAX_IPS_PER_IF];
    tt8Bit                  dev4PrefixLenArray[tm_align(TM_MAX_IPS_PER_IF)];
/* Flag per IP address. Ip address configured or not. */
    tt8Bit                  devIpConfFlagArray[tm_align(TM_MAX_IPS_PER_IF)];
/* for SLIP/PPP, other side's IP address in slot 0. See below. IPv4 uses
   this to precalculate/cache the directed broadcast address associated with
   each unicast IP address configured on the interface. */
    tt4IpAddress            devDestIpAddrArray[TM_MAX_IPS_PER_IF];
#if (defined(TM_OPTIMIZE_MANY_MHOMES) && !defined(TM_SINGLE_INTERFACE_HOME))
    ttSortedIpAddrCache     devSortedDBroadIpAddrCache;
#endif /* TM_OPTIMIZE_MANY_MHOMES and not TM_SINGLE_INTERFACE_HOME */
/* For LAN, directed broadcast for the interface */
#define devDBroadIpAddrArray devDestIpAddrArray
/* for PPP */
#define devPt2PtPeerIpAddr   devDestIpAddrArray[0]
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
/* timer used for delaying initial messages after opening a device */
#if 0
    ttTimerPtr              dev6InitDelayTimerPtrArr[TM_6_MAX_MHOME];
#endif
/* for SLIP/PPP, other side's IPv6 address */
    tt6IpAddress            dev6Pt2PtPeerIpAddr;
/* Multi-homed IPv6 address list containing both manually configured as well
   as auto-configured IPv6 addresses assigned to the interface. Note that
   local scope IPv6 addresses are stored on the interface without the
   embedded scope ID. */
#if 0
    tt6IpAddress            dev6IpAddrArray[TM_6_MAX_MHOME];
/* prefix length for each IPv6 addresses configured on the interface. */
    tt8Bit                  dev6PrefixLenArray[tm_align(TM_6_MAX_MHOME)];
/* Flags for each IPv6 address configured on the interface. Indicates if the
   address is preferred, deprecated or invalid. */
    tt8Bit                  dev6IpAddrFlagsArray[tm_align(TM_6_MAX_MHOME)];
#endif
/* IPv6 64-bit interface ID. */
    tt32Bit                 dev6InterfaceId[2];
/* IPv6 site ID assigned to the interface, defaults to 0. Used as the scope
   ID for site-local unicast IPv6 addresses. */
    tt32Bit                 dev6SiteId;
#ifdef TM_6_USE_TEMPADDR
/* Timer for temporary address is valid */
    ttTimer                 dev6TempTimer;
/* Timestamp (seconds, milliseconds) used for aging temporary addresses */
    tt32Bit                 dev6TempTimestamp;
    tt32Bit                 dev6TempTimestampMs;
/* IPv6 64-bit temporary interface ID + partial hash for next iteration */
    tt32Bit                 dev6TempInterfaceId[TM_MD5_HASH_SIZE / 4];
/* Creation timestamp for latest temporary interface ID */
    tt32Bit                 dev6TempTsIfId;
/* Creation timestamp for each autoconfigured temporary address */
    tt32Bit                 dev6TempTsAddr[TM_6_MAX_TEMP_IPS_PER_IF];
/* Multihome index of each autoconfigured temporary address */
    tt16Bit                 dev6TempAddrIndex[TM_6_MAX_TEMP_IPS_PER_IF];
/* List of prefixes to selectively enable/disable temporary addresses */
    ttList                  dev6TempPrefixFilter;
/* Interval (seconds) that a temporary address is valid */
    tt32Bit                 dev6TempValidLifetime;
/* Interval (seconds) that a temporary address is preferred */
    tt32Bit                 dev6TempPreferLifetime;
/* Maximum desynchronizing factor (seconds) */
    tt32Bit                 dev6TempMaxDesyncFactor;
/* Desynchronizing factor (seconds) */
    tt32Bit                 dev6TempDesyncFactor;
/* Maximum attempts to generate a valid address */
    unsigned int            dev6TempRegenMaxRetry;
/* Current attempt to generate a valid address */
    unsigned int            dev6TempRegenRetry;
#endif /* TM_6_USE_TEMPADDR */
/* BaseReachableTime specified by RFC-2461. */
    tt32Bit                 dev6BaseReachableTime;
/* ReachableTime specified by RFC-2461. */
    tt32Bit                 dev6ReachableTime;
/* Timestamp latched from when ReachableTime was last randomized. */
    tt32Bit                 dev6LastReachRndTime;
/* RetransTimer specified by RFC-2461. */
    tt32Bit                 dev6NeighSolicitReTxPeriod;
/* Maximum amount of time (in milliseconds) to delay before sending initial
   router solicitation when an interface is opened. */
    tt32Bit                 dev6RtrSolInitDelay;
/* Amount of time (in milliseconds) to wait between retransmitting router
   solicitations. */
    tt32Bit                 dev6RtrSolTimeout;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_VCHAN
#ifdef TM_USE_IPV4
/* Per mhome virtual channel IDs for IPv4 */
    tt32Bit                 devVChanArray[TM_MAX_IPS_PER_IF];
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
/* Per mhome virtual channel IDs for IPv6, includes slot for auto-configured
   link-local scope address */
    tt32Bit                 dev6VChanArray[TM_6_MAX_MHOME];
#endif /* TM_USE_IPV6 */
#endif /* TM_USE_VCHAN */
#endif /* ! TM_SINGLE_INTERFACE_HOME */

/*
 * Interval in milliseconds between ARP probes to send before configuring
 * an IPv4 DHCP/BOOTP address
 */
    tt32Bit                 devBtArpIntv;

    ttEventEntry            devRecvEvent;
    ttEventEntry            devSentEvent;
    ttEventEntry            devXmitEvent;

#ifdef TM_LOCK_NEEDED
    ttLockEntry             devLockEntry;
    ttLockEntry             devDriverLockEntry;

#ifdef TM_USE_IPV4
/* NAT fields, used by trnat.c */
    ttLockEntry             devNatLockEntry;
#endif /* TM_USE_IPV4 */
#endif /* TM_LOCK_NEEDED */

    int                     devScatterExtraCount;
    int                     devErrorCode;
/* Size of devBtUserEntryTablePtr */
    int                     devBtUserMaxEntries;
#ifdef TM_USE_STRONG_ESL
/* BOOTP/DHCP client socket */
    int                     devBootSocketDescriptor;
/* BOOTP/DHCP client socket open count */
    int                     devBootSocketOpenCount;
/* BOOTP/DHCP relay agent socket */
    int                     devBootRelayAgentDescriptor;
#endif /* TM_USE_STRONG_ESL */
/*
 * Number of ARP probes to send before configuring an IPv4
 * DHCP/BOOTP address
 */
    int                     devBtArpProbes;
/*
 * devIndex: one unique value per added interface (tfAddInterface).
 * devIndex used to identify the interface (for SNMP). The SNMP ifIndex
 * will be computed as (devIndex * TM_MAX_IPS_PER_IF) + mHomeIndex
 */
    unsigned int            devIndex;
/* number of postponed tfSendCompleteInterface() */
    int                     devSendCompltCount;
#ifdef TM_USE_DRV_ONE_SCAT_SEND
/* number of postponed tfSendCompletePacketInterface() */
    int                          devSendCompltPacketCount;
#endif /* TM_USE_DRV_ONE_SCAT_SEND */
#ifdef TM_USE_STRONG_ESL
    int                     devPhysPort;
#endif /* TM_USE_STRONG_ESL */
/*
 * default hop limit to use when sending unicast IP packets.
 * Can be overridden by Parameter Discovery via Router Advertisments.
 */
    int                     dev6HopLimit;

    tt8Bit                  devPhysAddrArr[tm_align(TM_MAX_PHYS_ADDR)];
    tt8Bit                  devNameArray[tm_align(TM_MAX_DEVICE_NAME)];

/*
 * Device open, Multicast enabled, IP Forwarding enabled, IP Directed
 * broadcast forwarding enabled, IP Mcast forwarding enabled, write
 * scattered enabled. BOOTP, DHCP configurations.
 */
    tt16Bit                 devFlag;
#ifdef TM_USE_IPV4
    tt16Bit                 devMtu; /*Setable by the User */
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
/* IPv6 interface flags: interface ID set, physical address set, link-local
   scope address configured or in progress, site-local scope address
   configured, etc., link-layer connected or in progress, IPv6 forwarding
   enabled, IPv6 multicast forwarding enabled, hardware loops back its own
   multicasts, optimize Duplicate Address Detection, MLDv1 compatibility
   mode. */
    tt16Bit                 dev6Flags;
#ifndef TM_USE_RFC3484
/* having to do with IPv6 addresses configured on the interface, 
 * and address caching
 */
    tt16Bit                 dev6AddrCacheFlags; 
#endif /* ! TM_USE_RFC3484 */
/* The MTU of the IPv6 link. */
    tt16Bit                 dev6Mtu;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_IPV4
/* NAT fields, used by trnat.c */
    tt16Bit                 devNatOpt;
    tt16Bit                 devNatNumTriggers;
#endif /* TM_USE_IPV4 */
/* Fields for TCP segmentation/checksum offload */
#if defined(TM_DEV_SEND_OFFLOAD) || defined(TM_DEV_RECV_OFFLOAD)
    tt16Bit                 devOffloadFlags;
    tt16Bit                 devOffloadPadding;
#endif /* TM_DEV_SEND_OFFLOAD || TM_DEV_RECV_OFFLOAD */
#ifdef TM_DEV_SEND_OFFLOAD
    tt32Bit                 devOffloadMaxSize;
#endif /* TM_DEV_SEND_OFFLOAD */

    tt16Bit                 devTxAlign;

/*
 * Settable by the user with tfInterfaceSetOptions. Copy incoming packet
 * from the network whose sizes are below this configurable threshold
 */
    tt16Bit                 devRecvCopyThreshHold;
/*
 * Receive data length for loopback interfaces (trloop.c, trindrv.c)
 * when not using one single call driver send, and not using driver
 * scattered recv.
 */
#define devReceiveDataLength          devFirstUnion.devUnReceiveDataLength
/*
 * Settable by the user with tfInterfaceSetOptions, when using device
 * driver scattered recv.
 * Partially copy incoming packet up to this value, if that much data
 * is not contiguous at the head of the packet.
 * Default value is TM_DEV_DEF_RECV_CONT_HDR_LENGTH
 */
#define devRecvContiguousHdrLength  \
                             devFirstUnion.devUnRecvContHdrLength
    union
    {
        tt16Bit                      devUnReceiveDataLength;
        tt16Bit                      devUnRecvContHdrLength;
    } devFirstUnion;
#if (defined(TM_IGMP) || defined(TM_USE_IPV6))
/*
 * Number of Ethernet multicast entries used for specific multicast IP
 * addresses
 */
    tt16Bit                 devLnkMcastEntries;
/* Number of multicast entries that are currently allocated */
    tt16Bit                 devLnkMcastAllocEntries;

/*
 * Enable temporary address auto-configuration, source address selection:
 * prefer temporary or public address.
 */
    tt16Bit                 dev6Flags2;
#endif /* TM_IGMP || TM_USE_IPV6 */

/*
 * Multihome index of the tunnel entry point. Only used in a virtual tunnel
 * device.
 */
    tt16Bit                 devTunnelEntryPtMhome;
    tt16Bit                 devFlag2;
/*
 * added devLinkLayerProtocol, so that we do not have to derefence link
 * layer entry to get this info.
 */
    tt16Bit                 devLinkLayerProtocol;

#ifdef TM_SINGLE_INTERFACE_HOME
    tt8Bit                  devIpConfFlag;
    tt8Bit                  dev4PrefixLen;
#else /* ! TM_SINGLE_INTERFACE_HOME */

#ifdef TM_USE_IPV4
/*
 * Biggest index + 1 of configured multihome entries:  between 0 and
 * TM_MAX_IPS_PER_IF
 */
    tt16Bit                 devMhomeUsedEntries;
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
/* biggest index + 1 of configured IPv6 multihome entries: between 0 and
   TM_MAX_IPS_PER_IF */
    tt16Bit                 dev6MhomeUsedEntries;
/* biggest index + 1 of auto-configured IPv6 multihome entries: between
   TM_MAX_IPS_PER_IF and (TM_MAX_IPS_PER_IF + TM_6_MAX_AUTOCONF_IPS_PER_IF) */
    tt16Bit                 dev6MhomeUsedAutoEntries;


#ifdef TM_USE_RFC3484
/*
 * IPv6 address cache lists used to optimize source address selection in the
 * send path 
 */
#if 0
    ttList                  dev6AddrCacheList[TM_6_ADDR_GLOBAL_INDEX];
/* Pre-allocated nodes (to be inserted in IPv6 address cache lists) */
    tt6AddrCacheInfo        dev6IpAddrCacheArray[TM_6_MAX_MHOME];
#endif
#ifdef TM_LOCK_NEEDED
/* Lock for IPv6 address cache lists */
    ttLockEntry             devAddrCacheListLock;
#endif /* TM_LOCK_NEEDED */
#else /* ! TM_USE_RFC3484 */
/* multihome indexes of IPv6 address of specific scope, etc. configured on the
   interface, used to optimize source address selection in the send path */
    tt16Bit                 dev6SiteLocalMhomeIndex;
    tt16Bit                 dev6LocalMhomeIndex;
    tt16Bit                 dev6Ipv6NativeMhomeIndex;
    tt16Bit                 dev6Ipv4CompatMhomeIndex;
    tt16Bit                 dev66to4MhomeIndex;
#endif /* ! TM_USE_RFC3484 */
    tt16Bit                 dev6LinkLocalMhomeIndex;

#ifdef TM_6_USE_MLD
/* Default Query Interval in seconds ([RFC2710]R7.2) */
    tt16Bit                 dev6MldQqi;
/* Default MLD Robustness Variable ([RFC2710]R7.1) */
    tt8Bit                  dev6MldRobustness;
#endif /* TM_6_USE_MLD */

/* number of consecutive Neighbor Solicitation messages sent while
   performing Duplicate Address Detection on a tentative address. Set to 0
   to disable Duplicate Address Detection. */
    tt8Bit                  dev6DupAddrDetectTransmits;
/* Initial number of times to retransmit router solicitations when an
   interface is opened. */
    tt8Bit                  dev6RtrSolInitRetry;
/* Number of router solicitation retries remaining. */
    tt8Bit                  dev6RtrSolSendCount;
#endif /* TM_USE_IPV6 */
#endif /* ! TM_SINGLE_INTERFACE_HOME */

    tt8Bit                  devPhysAddrLength;
/*
 * added devLinkHeaderLength, so that we do not have to derefence link
 * layer entry to get this info.
 */
    tt8Bit                  devLinkHeaderLength;
/* Initial BOOTP/DHCP request timeout value. */
    tt8Bit                  devBtInitTimeoutIntv;
/* Maximum number of BOOTP/DHCP retries */
    tt8Bit                  devBtMaxRetries;
/*
 * number of seconds to wait before configuring an IPv4 DHCP/BOOTP address
 * after starting to send ARP probes.
 */
    tt8Bit                  devBtArpTimeout;
#if (defined(TM_IGMP) || defined(TM_USE_IPV6))
/* Number of increasing allocations */
    tt8Bit                  devLnkMcastAllocations;
/* Number of requests to add all multicast addresses */
    tt8Bit                  devLnkMcastAllAddresses;
/*
 * Which version (v1, v2, v3) IGMP should use through that interface
 * (Not used for IPv6, but needed for padding)
 */
    tt8Bit                  devIgmpVFlag;
#endif /* TM_IGMP || TM_USE_IPV6 */
#ifdef TM_MULTIPLE_CONTEXT
    tt32Bit                 devNetworkId;
#endif /* TM_MULTIPLE_CONTEXT */
#ifdef TM_USE_DHCP_COLLECT
/*
 * DHCP offer collection parameters inherited by all DHCP entries:
 *  - Collection cache size: maximum number of DHCP offers to retain.
 *  - Collection time: maximum seconds to collect offers after the
 *      first offer arrives.
 */
    unsigned int                devDhcpCollectSize;
    unsigned int                devDhcpCollectTime;
/* User's DHCP offer notification callback function and parameter */
    ttUserDhcpOfferCBFuncPtr    devOfferFuncPtr;
    ttUserGenericUnion          devOfferParam;
#endif /* TM_USE_DHCP_COLLECT */
} ttDeviceEntry;

typedef  ttDeviceEntry TM_FAR   * ttDeviceEntryPtr;
typedef  ttDeviceEntryPtr TM_FAR   * ttDeviceEntryPtrPtr;

/* Network header: ARP Header */
typedef struct tsArpHeader
{
    tt16Bit     arpHardware;
    tt16Bit     arpProtocol;
    tt8Bit      arpHardwareLength;
    tt8Bit      arpProtocolLength;
    tt16Bit     arpOperation;
    tt8Bit      arpSendPhyAddress[TM_ETHER_ADDRESS_LENGTH];
    tt8Bit      arpSendNetAddress[TM_IP_ADDRESS_LENGTH];
    tt8Bit      arpTargetPhyAddress[TM_ETHER_ADDRESS_LENGTH];
    tt8Bit      arpTargetNetAddress[TM_IP_ADDRESS_LENGTH];
} ttArpHeader;

typedef ttArpHeader TM_FAR *ttArpHeaderPtr;

/* END of ARP network header */


/* Network header: UDP Header */
typedef struct  tsUdpHeader
{
    ttIpPort udpSrcPort; /* Source port of the UDP datagram */
    ttIpPort udpDstPort; /* Destination port of the UDP datagram */
    tt16Bit  udpLength; /* length in bytes of the UDP datagram */
/* One's complement checksum of UDP datagram+ pseudo_header */
    tt16Bit  udpChecksum;
} ttUdpHeader;

typedef ttUdpHeader TM_FAR * ttUdpHeaderPtr;

/* END of UDP network header */

/* Network header: ICMP Header */
typedef struct  tsIcmpHeader
{
    tt8Bit  icmType; /* ICMP type field */
    tt8Bit  icmCode; /* ICMP code field */
    tt16Bit icmChecksum; /* ICMP checksum */
    union
    {
        tt32Bit icmUnused32; /* ICMP Header unused second 32-bit word */
        tt32Bit icmRedirectRouterAddress; /* REDIRECT router address */
        tt8Bit  icmParamProblemOffset; /* ICMP parameter problem offset */
        struct
        {
            tt16Bit icmIdent; /* ICMP header request/reply identifier */
            tt16Bit icmSeqno; /* ICMP header request/reply sequence number */
        } icmRequestReplyStruct; /* for Request/Reply ICMP packets */
        struct
        {
            tt16Bit icmUnused16;
            tt16Bit icmNxtHopMtu; /* Next Hop MTU for path MTU discovery */
        } icmPathMtuStruct; /* Path MTU discovery structure */
        struct
        {
/* Number of router entries (in data portion) */
            tt8Bit  icmNumAddrs;
            tt8Bit  icmAddrEntrySize; /* Address entry size in 32-bit words */
            tt16Bit icmLifetime; /* TTL of the route, 1800 in seconds (30mn)*/
        } icmRtrDiscStruct1; /* Router discovery structure */
    } icmSecondLongWordUnion; /* ICMP header second 32-bit word */
    union
    {
        tt4IpAddress    icmAddressMask; /* ICMP address mask reply */
        struct
        {
            tt32Bit icmOriginate; /* ICMP originate timestamp */
            tt32Bit icmReceive; /* ICMP receive timestamp */
            tt32Bit icmTransmit; /* ICMP transmit timestamp */
        } icmTimeStampStruct; /* ICMP time stamp structure */
        struct
        {
/* router address. Overlays icmAddressMask */
            tt4IpAddress    icmRouterAddress;
            tt32Bit         icmRouterPrefLevel; /* rtr preference level (0) */
        } icmRtrDiscStruct2; /* ICMP router discovery structure (data) */
        ttIpHeader  icmIpHeader; /* ICMP error packet data: IP header */
        tt8Bit      icmpOptionalData[8]; /* Echo request/reply data */
    } icmDataUnion; /* ICMP Packet data (after first two 32-bit words) */
} ttIcmpHeader;

typedef ttIcmpHeader TM_FAR * ttIcmpHeaderPtr;

/* Second word union defines */
/* Unused second word */
#define icmSUUnused     icmSecondLongWordUnion.icmUnused32
/* Identification field */
#define icmSUIdent      icmSecondLongWordUnion.icmRequestReplyStruct.icmIdent
/* Sequence number field */
#define icmSUSeqno      icmSecondLongWordUnion.icmRequestReplyStruct.icmSeqno
/* REDIRECT router address */
#define icmSURedGwy     icmSecondLongWordUnion.icmRedirectRouterAddress
/* ICMP Parameter problem offset */
#define icmSUParmProbl  icmSecondLongWordUnion.icmParamProblemOffset
/* Router discovery number of addresses*/
#define icmSURdiscNumAddrs \
                    icmSecondLongWordUnion.icmRtrDiscStruct1.icmNumAddrs
/* Router discovery address size (in short words) */
#define icmSURdiscAddrSiz \
                    icmSecondLongWordUnion.icmRtrDiscStruct1.icmAddrEntrySize
/* Router discovery Time to live */
#define icmSURdiscLife   icmSecondLongWordUnion.icmRtrDiscStruct1.icmLifetime
/* Next hop MTU for path MTU discovery */
#define icmSUNxtHopMtu  icmSecondLongWordUnion.icmPathMtuStruct.icmNxtHopMtu
/* Data union defines */
/* Address mask */
#define icmDUAddrMask   icmDataUnion.icmAddressMask
/* Ip header in ICMP error packets */
#define icmDUIpHeader   icmDataUnion.icmIpHeader
#define icmDURdiscGwy   icmDataUnion.icmRtrDiscStruct2.icmRouterAddress
#define icmDURdiscPref  icmDataUnion.icmRtrDiscStruct2.icmRouterPrefLevel
/* Optional data for echo replies */
#define icmDUData       icmDataUnion.icmpOptionalData

/* END of ICMP network header */

/* tlHeader overlays transport layer header. Icmp header */

typedef struct tsTlHeader
{
    union
    {
        struct
        {
#define tlSport                 tlHeaderUnion.tlUdpTcpPortStruct.tluSport
            ttIpPort tluSport;    /* UDP/TCP source port */
#define tlDport                 tlHeaderUnion.tlUdpTcpPortStruct.tluDport
            ttIpPort tluDport;    /* UDP/TCP destination port */
        } tlUdpTcpPortStruct;
        struct
        {
#define tlIcmType               tlHeaderUnion.tlIcmpStruct.tluIcmType
            tt8Bit  tluIcmType; /* ICMP type field */
#define tlIcmCode               tlHeaderUnion.tlIcmpStruct.tluIcmCode
            tt8Bit  tluIcmCode; /* ICMP code field */
            tt16Bit tluIcmChecksum; /* ICMP checksum */
#define tlIcmIdent              tlHeaderUnion.tlIcmpStruct.tluIcmIdent
            tt16Bit tluIcmIdent; /* ICMP header request/reply identifier */
#define tlIcmSeqno              tlHeaderUnion.tlIcmpStruct.tluIcmSeqno
            tt16Bit tluIcmSeqno; /* ICMP header request/reply sequence number */
        } tlIcmpStruct;
    } tlHeaderUnion;
} ttTlHeader;

typedef ttTlHeader TM_FAR * ttTlHeaderPtr;


/*
 * ttIpFHEntry is a fragment head. IP fragment packets belonging to the
 * same IP datagram are queued to this list via the ipfPacketNextPtr
 * A fragment head is linked to the list of all fragments heads via the
 * ipfHeadNextPtr.
 */
typedef struct  tsIpFHEntry
{
    struct tsIpFHEntry              TM_FAR * ipfHeadNextPtr;
    ttPacketPtr                              ipfPacketNextPtr;
    tt4IpAddress                             ipfSrcAddr;
    tt4IpAddress                             ipfDestAddr;
/* Size withoug IP headers of queued IP datagram */
    tt32Bit                                  ipfSize;
    tt16Bit                                  ipfId;
    tt8Bit                                   ipfTtl;
    tt8Bit                                   ipfUlp;
/* This packet is too large to reassemble */
    tt8Bit                                   ipfTooBig;
} ttIpFHEntry;

typedef ttIpFHEntry TM_FAR * ttIpFHEntryPtr;

/* Multi home function pointer. Used in all interface matching functions */
typedef  int  (*ttMhomeFunctPtr)(ttDeviceEntryPtr devPtr,
                                 tt4IpAddress     ipAddr,
                                 tt16BitPtr       mhomeIndexPtr);

/*
 * This is the UDP/TCP pseudo-header structure used to compute the UDP/TCP
 * checksum. We have changed order of entries so as to overlay the IP
 * header exactly, since changing the order of 16-bit quantities in a
 * header will not affect checksum computation. This way we avoid
 * copying the source and destination addresses, and protocol field.
 * (We can use them right from the IP header.)
 */
/* Network header: TCP/UDP Pseudo-header */
typedef struct  tsPseudoHeader
{
    tt8Bit       pshZero; /* Must be zero for checksum computation */
    tt8Bit       pshProtocol; /* ULP protocol (17 for UDP, 6 for TCP) */
    tt16Bit      pshLayer4Len;/* UDP datagram or TCP segment length in bytes */
    tt4IpAddress pshSrcIpAddr; /* IP source address */
    tt4IpAddress pshDstIpAddr; /* IP destination address */
} ttPseudoHeader;
/* END of TCP/UDP network header */

typedef ttPseudoHeader TM_FAR * ttPseudoHeaderPtr;

/* Radix node structure
 * rtnNextPtr   Pointer to next leaf in the list of non host leaves (for
 *              network match searches)
 * rtnParentPtr Pointer to parent node.
 * rtnFlags     Flag indicating whether this is a leaf or a node, whether
 *              this is the root node, whether this node is in the tree,
 *              and whether a leaf node is a host leaf. TM_RTN_NODE,
 *              TM_RTN_ROOT, TM_RTN_IN, TM_RTN_HOST.
 * rtnFiller    padding for alignment
 * rtnBitOffset Bit offset of the bit to be tested for an internal Node.
 *              For a normal leaf it is the length of the network mask
 *              (number of non zero bits)
 * rtnLeafNodeUnion    Union of a leaf and internal node structures
 *   rtnLeafStruct   Leaf specific fields
 *     rtnKey             key (destination IP address) of a leaf
 *     rtnMask            network mask of a leaf
 *     rtnDuplicateKeyPtr Pointer to a leaf that has a duplicate key
 *     rtnPrevPtr         Pointer to a previous leaf in the list of non host
 *                        leaves (for network match searches)
 *   rtnNodeStruct   Internal Node specific fields
 *     rtnBitMask  IP address mask of the bit to be tested (to go left or
 *                 right).  For example to test the 0 bit offset of the IP
 *                 address, the mask would be 0x80000000, to test the 31 bit
 *                 offset of the IP address, the mask would be 0x1.
 *     rtnLeftPtr  Left child for an internal node
 *     rtnRightPtr Right child for an internal node
 */
typedef struct  tsRtRadixNode
{
/* Note: NextPtr need to be first for recycle list */
    struct tsRtRadixNode         TM_FAR *rtnNextPtr; /* need to be first */
    struct tsRtRadixNode         TM_FAR *rtnParentPtr;
/* Bit offset for a node structure (0-127 for IPV6, 0-31 for IPV4 */
    tt16Bit                              rtnBitOffset;
/* Mask prefix length for a leaf structure (0-128 for IPV6, 0-32 for IPV4) */
#define rtnPrefixLength rtnBitOffset
    tt8Bit                               rtnFlags;
    tt8Bit                               rtnFiller1;
    union
    {
        struct
        {
            ttIpAddress                  rtnKey;
#ifdef TM_USE_IPV6
/*
 * For IPV6, or dual mode, store the index in the array of 4 words, where the
 * prefixlength ends.
 * It is computed as follows:
 * This is zero if prefixLength == 0, or
 * (prefixLength - 1) / 32) otherwise. (value range 0-3.)
 * This is stored, so that we do not have to recompute it for each search.
 */
            tt16Bit                      rtn6MaskIndex;
/*
 * sub-prefixLength of netmask in 32-bit word .
 * It is computed as (prefixLength - (rtn6MaskIndex * 32))
 * (value range 0-32).
 * This is stored, so that we do not have to recompute it for each search.
 * We can use this prefix to retrieve
 * the corresponding 32-bit mask from the tvRt32ContiguousBitsPtr array.
 */
            tt16Bit                      rtn6MaskPrefix;
#else /* !TM_USE_IPV6 */
/*
 * For IPV4 mode only, just the 32-bit mask of the IP address.
 */
            tt4IpAddress                 rtnMask;
#endif /* !TM_USE_IPV6 */
            struct tsRtRadixNode TM_FAR *rtnDuplicateKeyPtr;
            struct tsRtRadixNode TM_FAR *rtnPrevPtr;
        } rtnLeafStruct;
        struct
        {
            tt4IpAddress                 rtnBitMask;
#ifdef TM_USE_IPV6
/*
 * rtnBitMask is a 32-bit mask, with one bit set. In a node we use that
 * bit to make left or right tree search decisions.
 * The offset of that bit in an IP address is given by rtnBitOffset, as stated
 * above. (For IPV6 value range of rtnBitOffset is 0-127; for IPV4, value
 * range of rtnBitOffset is 0-31).
 * For IPV6 only:
 * . The offset of that bit in the 32-bit mask is given by rtn6LongBitOffset
 *   (value range 0-31).
 * . The index of that mask in the IPV6 4-long word array is given by
 *   rtn6LongIndex (value range 0-3).
 */
            tt16Bit                       rtn6LongIndex;
            tt16Bit                       rtn6LongBitOffset;
#endif /* TM_USE_IPV6 */
            struct tsRtRadixNode TM_FAR *rtnLeftPtr;
            struct tsRtRadixNode TM_FAR *rtnRightPtr;
        } rtnNodeStruct;
    } rtnLeafNodeUnion;
} ttRtRadixNode;

typedef ttRtRadixNode TM_FAR * ttRtRadixNodePtr;

/* Shorthands into tsRtRadixNode sub-unions/sub-structures */
#define rtnLSKey            rtnLeafNodeUnion.rtnLeafStruct.rtnKey
#define rtnLSMask           rtnLeafNodeUnion.rtnLeafStruct.rtnMask
#define rtnLS6MaskIndex     rtnLeafNodeUnion.rtnLeafStruct.rtn6MaskIndex
#define rtnLS6MaskPrefix    rtnLeafNodeUnion.rtnLeafStruct.rtn6MaskPrefix
#define rtnLSDupKeyPtr      rtnLeafNodeUnion.rtnLeafStruct.rtnDuplicateKeyPtr
#define rtnLSPrevPtr        rtnLeafNodeUnion.rtnLeafStruct.rtnPrevPtr
#define rtnNSBitMask        rtnLeafNodeUnion.rtnNodeStruct.rtnBitMask
#define rtnNS6LIndex        rtnLeafNodeUnion.rtnNodeStruct.rtn6LongIndex
#define rtnNS6LBitOffset    rtnLeafNodeUnion.rtnNodeStruct.rtn6LongBitOffset
#define rtnNSLeftPtr        rtnLeafNodeUnion.rtnNodeStruct.rtnLeftPtr
#define rtnNSRightPtr       rtnLeafNodeUnion.rtnNodeStruct.rtnRightPtr

/*
 * Routing entry host gateway union. Used to store either:
 * . the device IP address for a local route,
 * . the Ethernet address for an ARP entry, or multicast route, or broadcast
 *   route
 * . the gateway (next hop) IP address for an indirect route.
 */
typedef union tuRteHostGway
{
    struct
    {
/* device IP address for Local routing entry */
        ttIpAddress         rteDevIpAddress;
#ifdef TM_USE_IPV6
#ifdef TM_6_USE_PREFIX_DISCOVERY
        tt32Bit             rte6PreferredLifetime;
#endif /* TM_6_USE_PREFIX_DISCOVERY */
#endif /* TM_USE_IPV6 */
    } rteLocalNetStruct;
    struct
    {
/* the physical address MUST be the first field */
        union {
/* device Ethernet address for ARP entry, multicast route */
            ttEnetAddress   rteEnetAddress; /* Ethernet host route */
            tt8Bit          rtePhysAddr[
                (((TM_MAX_PHYS_ADDR + 5) / 4) * 4) - 2];
            ttIpAddress     rtePhysIpAddress; /* this is trash-proof */
        }   rtePhysAddrUnion;
#ifdef TM_USE_IPV4
#ifdef TM_PMTU_DISC
        tt32Bit             rtePmtuTimeout;
#endif /* TM_PMTU_DISC */
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
#ifdef TM_6_USE_NUD
        tt32Bit             rte6NsTries;
        ttTimerPtr          rte6NudTimerPtr;
#endif /* TM_6_USE_NUD */
#ifdef TM_6_PMTU_DISC
        tt32Bit             rte6LastPmtuTickCount;
#endif /* TM_6_PMTU_DISC */
        tt32Bit             rteLastReachedTickCount;
        tt8Bit              rte6NudState;
        tt8Bit              rtePhysAddrLen;
        tt8Bit              rte6Filler1[2];
#else /* ! TM_USE_IPV6 */
        tt8Bit              rteFiller1;
        tt8Bit              rtePhysAddrLen;
#endif /* ! TM_USE_IPV6 */
    } rteLanArpStruct;
    struct
    {
        ttIpAddress         rteGatewayAddress; /* indirect route */
        tt16Bit             rteTag;            /* Route tag */
        tt16Bit             rteFiller2;        /* Multiple of 4 bytes */
    } rteGatewayStruct;

    struct
    {
        ttIpAddress         rteTunnelExitAddr; /* rteGatewayAddress */
/*
 * No room for rteTunnelEntryAddr, as the cloned PATH MTU rteLanArpStruct
 * could clobber the entry. rteTunnelExitAddr is safe because we do not
 * actually ARP on the virtual device, so rtePhysAddrUnion does not get
 * changed.
 */
    } rteTunnelStruct;

#ifdef TM_USE_IPV6
#endif /* TM_USE_IPV6 */

} ttRteHostGwayUnion;

/* Shorthands into host gateway union */
#define GSGateway              rteGatewayStruct.rteGatewayAddress
#define GSTag                  rteGatewayStruct.rteTag
#define HSDevIpAdd             rteLocalNetStruct.rteDevIpAddress
#define HSEnetAdd              rteLanArpStruct.rtePhysAddrUnion.rteEnetAddress
#define HSPhysAddr             rteLanArpStruct.rtePhysAddrUnion.rtePhysAddr
#define HSPhysAddrLen          rteLanArpStruct.rtePhysAddrLen
#define HSTunnelExitAddr       rteTunnelStruct.rteTunnelExitAddr
#define HSLastReachedTickCount rteLanArpStruct.rteLastReachedTickCount
#ifdef TM_USE_IPV4
#ifdef TM_PMTU_DISC
#define HSPmtuTimeout          rteLanArpStruct.rtePmtuTimeout 
#endif /* TM_PMTU_DISC */
#endif /* TM_USE_IPV4 */

#ifdef TM_USE_IPV6
#define HS6PreferredLifetime    rteLocalNetStruct.rte6PreferredLifetime
#define HS6NsTries              rteLanArpStruct.rte6NsTries
#define HS6NudTimerPtr          rteLanArpStruct.rte6NudTimerPtr
#define HS6NudState             rteLanArpStruct.rte6NudState
#ifdef TM_6_PMTU_DISC
#define HS6LastPmtuTickCount    rteLanArpStruct.rte6LastPmtuTickCount
#endif /* TM_6_PMTU_DISC */
#endif /* TM_USE_IPV6 */

typedef ttRteHostGwayUnion TM_FAR * ttRteHostGwayUnionPtr;

#ifdef TM_SNMP_CACHE
typedef struct tsSnmpCacheEntry
{
    ttNode              sceNode;
/* Pointer to entry in the table (socketPtr, rtePtr, tcpVectPtr, or tcpTmWtVectPtr */
    ttVoidPtr           sceTableEntryPtr;
/* Pointer to tupledev for socketPtr/tcpVectPtr/tcpTmWtVectPtr */
    ttVoidPtr           sceParmPtr;
/* SNMPD/NSTAT cache index */
    tt8Bit              sceTableIndex;
/* Table entry pointer type (only needed for Time Wait) */
    tt8Bit              sceTableEntryType;
} ttSnmpCacheEntry;

typedef ttSnmpCacheEntry TM_FAR * ttSnmpCacheEntryPtr;

#endif /* TM_SNMP_CACHE */


/* Router entry structure:
 * rteLeafNode      Leaf node for a routing entry
 * rteInternalNode  Internal node corresponding to the added leaf node (it
 *                  is the routing entry leaf node's parent)
 * rteFlags         16-bit flag for routing entry.
 * rteFlags2        extra 16-bit flag for routing entry.
 * rteOwnerCount    Number of owners for this routing entry
 * rteMhomeIndex    Multihome index in device entry
 * rteDevPtr        Pointer to device entry corresponding to the route
 * rteHostGwayUnion Host gateway union. (See above.)
 * rteClonedPtr     Pointer to ARP entry for route or pointer to loop back
 *                  entry for local route
 * rteCloneMask     Ip network address mask for cloned routes (ARP) (IPV4)
 * rteMtu           IP Mtu for the route
 * rteHops          Number of hops for the route
 * rteTtl           Time to live in seconds for this entry (for redirect, RIP)
 * rteDelay;        Delay for the route
 * rteRtt           Round trip time for the route
 * rteClonePrefixLength (IPV6)
 *                  Ip network address prefix length for cloned routes (ARP)
 * rteRefresh       ARP cache need to be refreshed soon. Makes the IP
 *                  layer send an ARP request in the send path.
 */

typedef struct  tsRteEntry
{
    struct tsRtRadixNode    rteLeafNode;
    struct tsRtRadixNode    rteInternalNode;
    ttDeviceEntryPtr        rteDevPtr; /* devPtr or loop back devPtr */
    ttDeviceEntryPtr        rteOrigDevPtr; /* devPtr of real route */
    ttRteHostGwayUnion      rteHostGwayUnion;
#ifdef TM_USE_IPDUAL
    tt4IpAddress            rteTunnelEntryAddr;
#endif /* TM_USE_IPDUAL */
/* Pointer to ARP entry for this route or to Loop back entry for local route */
    struct tsRteEntry TM_FAR *rteClonedPtr;
/* Pointer to next routing entry on the remove list */
    struct tsRteEntry TM_FAR *rteNextRemPtr;
#ifdef TM_SNMP_CACHE
    ttSnmpCacheEntry         rteSnmpCacheEntry;
#endif /* TM_SNMP_CACHE */
    tt4IpAddress             rteCloneMask; /* IPV4 */
    tt32Bit                  rteHops;
    tt32Bit                  rteTtl;
    unsigned int             rteOwnerCount;
    tt16Bit                  rteMtu;
    tt16Bit                  rteFlags;
    tt16Bit                  rteFlags2; /* Because rteFlags is full */
/* mhome index for origDev, or loopback */
    tt16Bit                  rteMhomeIndex;
/* mhome index of the real route */
    tt16Bit                  rteOrigMhomeIndex;
#ifdef TM_USE_IPV6
    tt16Bit                  rte6Flags;
    tt8Bit                   rteClonePrefixLength; /* IPV6 */
#endif /* TM_USE_IPV6 */
    tt8Bit                   rteRefresh;
} ttRteEntry;


typedef ttRteEntry    TM_FAR * ttRteEntryPtr;
typedef ttRteEntryPtr TM_FAR * ttRteEntryPtrPtr;

typedef int (*ttIntRtFuncPtr)(ttRteEntryPtr rtePtr, ttVoidPtr arg2Ptr);

#define rteGSGateway                rteHostGwayUnion.GSGateway
#define rteGSTag                    rteHostGwayUnion.GSTag
#define rteHSDevIpAdd               rteHostGwayUnion.HSDevIpAdd
#define rteHSEnetAdd                rteHostGwayUnion.HSEnetAdd
#define rteHSPhysAddr               rteHostGwayUnion.HSPhysAddr
#define rteHSPhysAddrLen            rteHostGwayUnion.HSPhysAddrLen
#define rteHSTunnelExitAddr         rteHostGwayUnion.HSTunnelExitAddr
#ifdef TM_USE_IPDUAL
#define rteHSTunnelEntryAddr        rteTunnelEntryAddr
#endif /* TM_USE_IPDUAL */
#define rteHSLastReachedTickCount   rteHostGwayUnion.HSLastReachedTickCount
#ifdef TM_USE_IPV4
#ifdef TM_PMTU_DISC
#define rteHSPmtuTimeout            rteHostGwayUnion.HSPmtuTimeout
#endif /* TM_PMTU_DISC */
#endif /* TM_USE_IPV4 */

#ifdef TM_USE_IPV6
#define rte6HSPreferredLifetime     rteHostGwayUnion.HS6PreferredLifetime
#define rte6HSNudState              rteHostGwayUnion.HS6NudState
#define rte6HSNsTries               rteHostGwayUnion.HS6NsTries
#define rte6HSNudTimerPtr           rteHostGwayUnion.HS6NudTimerPtr
#define rte6HSCoAddr                rteHostGwayUnion.HS6CoAddr
#ifdef TM_6_PMTU_DISC
#define rte6HSLastPmtuTickCount     rteHostGwayUnion.HS6LastPmtuTickCount
#endif /* TM_6_PMTU_DISC */
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_IPV6
/*
 * Default router entry structure. Inserted in the list of IPV6 default
 * routers at the head of the Patricia tree (rth6DefaultRouterList)
 */
typedef struct ts6RtDefRouterEntry
{
/* Circular list */
    ttNode                              drt6Node;
/* Pointer to associated device entry */
    ttDeviceEntryPtr                    drt6DevPtr;
/* When non null, this default router is inserted in the tree */
    ttRteEntryPtr                       drt6RtePtr;
/* Default gateway IP address */
    ttIpAddress                         drt6IpAddr;
/* Default gateway time to live */
    tt32Bit                             drt6Ttl;
#define TM_DRT6_INSERT_FAILED ((tt16Bit)0x1)
#define TM_DRT6_V4_TUNNEL     ((tt16Bit)0x2)
#define TM_DRT6_TEMPORARY     ((tt16Bit)0x4)
    tt16Bit                             drt6Flags;
    tt8Bit                              drt6ListIndex;
    tt8Bit                              drt6Filler;
} tt6RtDefRouterEntry;

typedef tt6RtDefRouterEntry TM_FAR * tt6RtDefRouterEntryPtr;

#endif /* TM_USE_IPV6 */

/*
 * This structure is used in the tfIpSendPacket(), tfIpForwardPacket(),
 * tf6IpSendPacket(), tf6IpForwardPacket() routines to cache the last accessed
 * routing entry in the routing table.
 * We have one such cache per socket to be used by the ICMP/UDP/TCP socket
 * send code.
 * For all other protocols, we have two context global variables in the IP
 * code of type ttRtCacheEntry: tvRtSendCache and tvRtForwardCache.
 * Similarly, in the IPv6 code we have two context global variables of type
 * ttRtCacheEntry: tv6RtSendCache, and tv6RtForwardCache.
 */
typedef struct  tsRtCacheEntry
{
    ttIpAddress       rtcDestIpAddr;   /* Destination IP Address */
#ifdef TM_USE_STRONG_ESL
    ttDeviceEntryPtr  rtcDevPtr;       /* Destination device */
#endif /* TM_USE_STRONG_ESL */
    ttRteEntryPtr     rtcRtePtr;       /* Pointer to a routing entry */
    ttRteEntryPtr     rtcRteClonedPtr; /* Pointer to ARP entry */


#ifdef TM_USE_IPV6
    ttDeviceEntryPtr  rtcSrcDevPtr;      /* device of source address */
    tt16Bit           rtcSrcMhomeIndex;  /* Multihome index of source address */
    tt8Bit            rtcDestIpAddrType; /* see tf6SelectSourceAddress */
    tt8Bit            rtcRtoFlag; /* 0 == route optimzation, 0xFF == no */
    tt8Bit            rtcSrcMhomeSet;    /* 1 rtcSrcMhomeIndex initialized */
#endif /* TM_USE_IPV6 */
} ttRtCacheEntry;

typedef ttRtCacheEntry TM_FAR * ttRtCacheEntryPtr;


/*
 * rthLeftEndNode  Left end root leaf of the tree (rtnKey is all 0) (invalid
 *  route entry), but default gateway stored as duplicate of this leaf.
 * rthHeadNode Head node of the tree.
 * rthRightEndNode Right end leaf of the tree (rtnKey is all 1)
 *  (invalid route entry)
 */
typedef struct  tsRtRadixHeadEntry
{
    ttRtRadixNode           rthLeftEndNode;
    ttRtRadixNode           rthHeadNode;
    ttRtRadixNode           rthRightEndNode;

/* List of routing entries to be removed when it is safe to do so */
    ttRteEntryPtr           rthRteRemListPtr;
#ifdef TM_USE_IPV6
#ifdef TM_6_USE_PREFIX_DISCOVERY
/* List of non-on-link IPv6 prefixes. Populated by ICMPv6 parameter
   discovery. These routing entries can't be stored in the routing tree
   because they can't be used for on-link determination. A site-local
   scope prefix is a good example of a non-on-link prefix, because IPv6
   addresses having that prefix could exist on multiple links. */
    ttRtRadixNodePtr        rth6NonOnLinkPrefixList;
#endif /* TM_6_USE_PREFIX_DISCOVERY */
#ifndef TM_USE_STRONG_ESL
    tt6RtDefRouterHead      rth6DefaultRouterHead;
#endif /* TM_USE_STRONG_ESL */
#ifdef TM_USE_IPV4
#ifndef TM_USE_STRONG_ESL
/*
 * Pointer to the IPv4 default gateway, which must always exist in the
 * routing tree when the stack is being used in dual IP layer mode.
 */
    ttRteEntryPtr           rth4DefaultGatewayPtr;
/*
 * If no IPv4 default gateway has been configured, then rt4DefaultGatewayPtr
 * will point to this default gateway which has the TM_RTE_REJECT bit set,
 * so that output through this route is rejected.
 */
    ttRteEntry              rth4RejectDefaultGateway;
#endif /* TM_USE_STRONG_ESL */
#endif /* dual IP layer */
#endif /* TM_USE_IPV6 */
/* Parameters to delayed (until tree is unlocked) tfRtResetCaches() function */
    tt16Bit                 rthResetCachesFlags;
    tt16Bit                 rthResetCachesAf;
    tt16Bit                 rthTreeWalkCount;
    tt16Bit                 rthRteWalkFiller;
} ttRtRadixHeadEntry;

/*
 * Short cuts used by SNMP.
 */
/* Route Destination IP address */
#define rteDest         rteLeafNode.rtnLSKey
/* Route Destination Network Mask */
#define rteMask         rteLeafNode.rtnLSMask
/* Route Next Hop */
#define rteNextHop      rteGSGateway
/* Device Index of outgoing interface */
#define rteDevIndex     rteOrigDevPtr->devIndex


typedef struct tsArpMapping
{
#ifdef TM_USE_STRONG_ESL
    ttDeviceEntryPtr arpmDevPtr;
#endif /* TM_USE_STRONG_ESL */
    union
    {
        ttEnetAddress arpmUnEnetAddress;
#define arpmEnetAddress arpmEthPhysAddrUnion.arpmUnEnetAddress
        tt8Bit        arpmUnPhysAddr[(((TM_MAX_PHYS_ADDR + 5) / 4) * 4) - 2];
#define arpmPhysAddr  arpmEthPhysAddrUnion.arpmUnPhysAddr
    } arpmEthPhysAddrUnion;
    tt8Bit         arpmPhysAddrLen;
/* the arpmCommand field must come before arpmIpAddress */
    tt8Bit         arpmCommand;

    union
    {
#ifdef TM_USE_IPV4
        tt4IpAddress arpm4UnIpAddress;
#define arpm4IpAddress arpmIpAddressUnion.arpm4UnIpAddress
/* arpmIpAddress is for backwards compatibility with SNMP Agent code */
#define arpmIpAddress arpm4IpAddress
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
        tt6IpAddress arpm6UnIpAddress;
#define arpm6IpAddress arpmIpAddressUnion.arpm6UnIpAddress
#endif /* TM_USE_IPV6 */
    } arpmIpAddressUnion;
    tt32Bit        arpmTtl;
    int            arpmDevIndex;
} ttArpMapping;

typedef ttArpMapping TM_FAR * ttArpMappingPtr;

/* ICMP info from the last ICMP error received for this socket */
typedef struct tsIcmpInfo
{
/* Source IP address of the ICMP error message in network byte order */
    ttIpAddress                 icmSrcIPAddr;
/*
 * Set to 1 by ICMP, when ICMP stores a new ICMP error message info,
 * to indicate to the user that new info has been stored.
 * Set to 0 by application, when application has read the ICMP info.
 */
    tt16Bit                     icmCtrlW;
/* ICMP type of ICMP error message */
    tt8Bit                      icmTypeB;
/* ICMP code of ICMP error message */
    tt8Bit                      icmCodeB;
} ttIcmpInfo;

#ifdef TM_USE_SOCKET_RB_TREE
/*
 * Red-black tree node.
 */
typedef struct tsRedBlackNode {
/* RB tree right, left, and parent */
    struct tsRedBlackNode TM_FAR *  rbnLinkPtr[3];
#define TM_RB_LINK_LEFT     0
#define TM_RB_LINK_RIGHT    1
#define TM_RB_LINK_UP       2
#define rbnLeftPtr       rbnLinkPtr[TM_RB_LINK_LEFT]
#define rbnRightPtr      rbnLinkPtr[TM_RB_LINK_RIGHT]
#define rbnParentPtr     rbnLinkPtr[TM_RB_LINK_UP]
    tt8Bit                          rbnTreeColor;
} ttRedBlackNode;
typedef ttRedBlackNode    TM_FAR * ttRedBlackNodePtr;
typedef ttRedBlackNodePtr TM_FAR * ttRedBlackNodePtrPtr;
#endif /* TM_USE_SOCKET_RB_TREE */

#ifdef TM_SOTB_MCAST_ENABLE
/*
 * Multicast information linkage blocks.
 * Sockets may be chained in a linked list for fast distribution of
 * broadcast and multicast packets.
 * A socket may appear on more than one list.
 * The ttSockMcastList block is an entry in the TM_SOTB_MCAST socket table.
 * The block also forms the head of the list of ttSockMcastNode blocks for
 * sockets that are bound to a particular port and IP address.
 */
typedef struct tsSockMcastList {
#ifdef TM_USE_SOCKET_RB_TREE
    ttRedBlackNode          smhRbNode;
#define smhRbLeftPtr    smhRbNode.rbnLeftPtr
#define smhRbRightPtr   smhRbNode.rbnRightPtr
#define smhRbParentPtr  smhRbNode.rbnParentPtr
#define smhRbTreeColor  smhRbNode.rbnTreeColor
#else /* !TM_USE_SOCKET_RB_TREE */
/* Doubly linked list linkage */
    ttNode                  smhNode;
#endif /* !TM_USE_SOCKET_RB_TREE */
    ttList                  smhSocketList;
    ttIpAddress             smhIpAddress;
#ifdef TM_USE_SOCKET_HASH_LIST
    unsigned int            smhHashIndex;
#endif /* TM_USE_SOCKET_HASH_LIST */
    ttIpPort                smhPort;
    tt8Bit                  smhProtocolNumber;
} ttSockMcastList;
typedef ttSockMcastList    TM_FAR * ttSockMcastListPtr;
typedef ttSockMcastListPtr TM_FAR * ttSockMcastListPtrPtr;

/*
 * Multicast information linkage block.
 * Sockets may be chained in a linked list for fast distribution of
 * broadcast and multicast packets.
 * A socket may appear on more than one such list.
 * This structure links the socket to any given list.
 */
struct tsSocketEntry;
typedef struct tsSockMcastNode {
/* Doubly linked list linkage */
    ttNode                          smnNode;
    ttSockMcastListPtr              smnListPtr;
    struct tsSocketEntry TM_FAR *   smnSocketPtr;
    tt8Bit                          smnType;
} ttSockMcastNode;
typedef ttSockMcastNode    TM_FAR * ttSockMcastNodePtr;
typedef ttSockMcastNodePtr TM_FAR * ttSockMcastNodePtrPtr;
#endif /* TM_SOTB_MCAST_ENABLE */

#ifdef TM_IGMP


/*
 * keep track of socket IGMP group joins, and source lists so that we can
 * update the source lists, and leave these groups when the socket is closed
 */
typedef struct tsSockIgmpInfo {
    ttNode                  siiNode;
#ifdef TM_SOTB_MCAST_ENABLE
/* For receiving IPv4 multicast packets */
    ttSockMcastNode         siiMcNode;
#endif /* TM_SOTB_MCAST_ENABLE */
    ttDeviceEntryPtr        siiDevicePtr;
    tt4IpAddress            siiMcastAddr;
} ttSockIgmpInfo;

typedef ttSockIgmpInfo TM_FAR * ttSockIgmpInfoPtr;

#endif /* TM_IGMP */

#ifdef TM_6_USE_MLD
#ifdef TM_6_USE_MLDV2
/* IPv6 Multicast Source List */
typedef struct ts6SourceList
{
/* List of IPv6 addresses and owner counts (see tt6SourceListEntry) */
    ttList                  src6List;
/* Number of source addresses used */
#define src6Count src6List.listCount
/* Source list mode: TM_MODE_IS_INCLUDE or TM_MODE_IS_EXCLUDE */
    tt8Bit                  src6Mode;
} tt6SourceList;
typedef tt6SourceList TM_FAR * tt6SourceListPtr;

/* IPv6 Multicast Source List Entry */
typedef struct ts6SourceListEntry
{
/* Source list linkage */
    ttNode                  sle6Node;
/* Source address */
    tt6IpAddress            sle6Addr;
/* Owner count */
    unsigned int            sle6OwnerCount;
/* Retransmission downcount for this source in a change report */
    tt8Bit                  sle6ReportCount;
} tt6SourceListEntry;
typedef tt6SourceListEntry TM_FAR * tt6SourceListEntryPtr;
#endif /* TM_6_USE_MLDV2 */

/* keep track of socket IPv6 MLD group joins so that we can leave these
   groups when the socket is closed */
typedef struct ts6SockMldInfo {
    ttNode              smi6Node;
#ifdef TM_SOTB_MCAST_ENABLE
/* For receiving IPv6 multicast packets */
    ttSockMcastNode     smi6McNode;
#endif /* TM_SOTB_MCAST_ENABLE */
#define smi6SocketPtr smi6McNode.smnSocketPtr
    ttDeviceEntryPtr    smi6DevicePtr;
    tt6IpAddress        smi6McastAddr;
#ifdef TM_6_USE_MLDV2
/* Multicast Source List */
    tt6SourceList       smi6SourceList;
#endif /* TM_6_USE_MLDV2 */
} tt6SockMldInfo;
typedef tt6SockMldInfo TM_FAR *tt6SockMldInfoPtr;
#endif /* TM_6_USE_MLD */

typedef struct tsTupleDev
{
#define tudRemoteIpAddress  tudTuple.sotRemoteIpAddress
#define tudLocalIpAddress   tudTuple.sotLocalIpAddress
#define tudRemoteIpPort     tudTuple.sotRemoteIpPort
#define tudLocalIpPort      tudTuple.sotLocalIpPort
    ttSockTuple         tudTuple;
#if (defined(TM_USE_STRONG_ESL) || defined(TM_IGMP) || defined(TM_6_USE_MLD))
    ttDeviceEntryPtr    tudDevPtr;
#endif /* TM_USE_STRONG_ESL || TM_IGMP || TM_6_USE_MLD */
    tt8Bit              tudProtocolNumber;
    tt8Bit              tudAddressFamily; /* AF_INET or AF_INET6 */
    tt8Bit              tudAddressFamilyMask;
    tt8Bit              tudFiller;
} ttTupleDev;

typedef ttTupleDev TM_FAR * ttTupleDevPtr;


/*
 * Socket Entry Typedef
 * Defined as a red black binary tree
 * Search key is (protocolNumber<<16)|ourLayer4Port
 * Size of Each Entry is 144Bytes
 */
typedef struct tsSocketEntry
{
/* NOTE: a pointer has to be first for recycling, and queuing */
#ifdef TM_USE_SOCKET_RB_TREE
/* RB tree right, left, and parent */
    ttRedBlackNode          socRbNode;
#define socRbLeftSocketPtr    socRbNode.rbnLeftPtr
#define socRbRightSocketPtr   socRbNode.rbnRightPtr
#define socRbParentSocketPtr  socRbNode.rbnParentPtr
#define socRbTreeColor        socRbNode.rbnTreeColor
#else /* !TM_USE_SOCKET_RB_TREE */
/* Doubly linked list linkage */
    ttNode                      socTableNode;
#endif /* !TM_USE_SOCKET_RB_TREE */
/*
 * Queue of sockets using the same local port number.
 */
    struct tsSocketEntry TM_FAR *socReuseAddrNextPtr;
    struct tsSocketEntry TM_FAR *socReuseAddrPrevPtr;
/*
 * For a connection request/accepted vector/socket: pointer to the
 * listening socket.
 */
    struct tsSocketEntry TM_FAR *socListenSocketPtr;
    ttLockEntry                 socLockEntry;
    ttRtCacheEntry              socRteCacheStruct;
    unsigned int                socOwnerCount;
    tt16Bit                     socFlags;
    tt16Bit                     socOptions;
    ttTupleDev                  socTupleDev;
#define socTuple    socTupleDev.tudTuple
#define socPeerIpAddress    socTuple.sotRemoteIpAddress
#define socOurIfIpAddress   socTuple.sotLocalIpAddress
#define socPeerLayer4Port   socTuple.sotRemoteIpPort
#define socOurLayer4Port    socTuple.sotLocalIpPort
#define socProtocolNumber   socTupleDev.tudProtocolNumber
#define socProtocolFamily   socTupleDev.tudAddressFamily
#define socProtocolFamilyMask  socTupleDev.tudAddressFamilyMask
#ifndef TM_USE_UDP_LOOKUP_PERF
    tt32Bit                     socRedBlackKey;
#endif /* !TM_USE_UDP_LOOKUP_PERF */
#ifdef TM_USE_SOCKET_HASH_LIST
/* Hash bucket */
    tt32Bit                     socHash;
#endif /* TM_USE_SOCKET_HASH_LIST */
#ifdef TM_SOTB_MCAST_ENABLE
/* TM_SOTB_MCAST list linkage for receiving IPv4 broadcast and local
 * multicast packets */
    ttSockMcastNode             socBcastNode;
#endif /* TM_SOTB_MCAST_ENABLE */
/*
 * Tree type flag for TCP sockets:
 * (TM_SOC_TREE_CL_FLAG, or TM_SOC_TREE_CO_FLAG)
 * Also whether the socket cannot be found as a
 * match in the tree (TM_SOC_TREE_NO_MATCH_FLAG).
 */
    tt16Bit                     socCoFlags;
    tt8Bit                      socFlags2;
    tt8Bit                      socInReuseAddrList;
    ttDeviceEntryPtr            socMcastDevPtr;
    tt32Bit                     socSendQueueBytes;
    tt32Bit                     socMaxSendQueueBytes;
    tt32Bit                     socLowSendQueueBytes;
    tt16Bit                     socMaxSendQueueDgrams;  /* non-TCP */
    tt16Bit                     socSendQueueDgrams;     /* non-TCP */
    tt32Bit                     socRecvQueueBytes;
    tt32Bit                     socMaxRecvQueueBytes;
    tt32Bit                     socLowRecvQueueBytes;
    tt16Bit                     socMaxRecvQueueDgrams;  /* non-TCP */
    tt16Bit                     socRecvQueueDgrams;     /* non-TCP */
    tt32Bit                     socOobMark;
    ttPacketPtr                 socReceiveQueueNextPtr;
    ttPacketPtr                 socReceiveQueueLastPtr;
    ttPacketPtr                 socSendQueueNextPtr;
    ttPacketPtr                 socSendQueueLastPtr;
#ifdef TM_SNMP_CACHE
    ttSnmpCacheEntry            socSnmpCacheEntry;
#endif /* TM_SNMP_CACHE */
/* Socket call back function without a user parameter */
    ttUserSocketCBFuncPtr       socUserCBFuncPtr;
/* Socket call back function with a user parameter */
    ttUserSocketCBParamFuncPtr  socUserCBParamFuncPtr;
#ifdef TM_USE_TCP_INCOMING_CB
/* Socket call back function for valid incoming packets */
    ttUserSocketCBPacketFuncPtr socUserCBPacketFuncPtr;
#endif /* TM_USE_TCP_INCOMING_CB */
/* User API parameter to socUserCBParamFuncPtr, or PING API entry pointer */
    ttVoidPtr                   socApiEntryPtr;
#ifdef TM_IGMP
/* keep track of socket IGMP group joins, and source lists so that we can
 * update the source lists, and leave these groups when the socket is closed
 */
    ttList                      socIgmpInfoList;
#endif /* TM_IGMP */
#ifdef TM_6_USE_MLD
/* keep track of socket IPv6 MLD group joins so that we can leave these
   groups when the socket is closed */
    ttList                      soc6MldInfoList;
#endif /* TM_6_USE_MLD */
#ifdef TM_USE_IPV6
/* Socket-level option IPV6_MULTICAST_IF.([IPV6REQ].R2.18:10) */
    ttDeviceEntryPtr            soc6McastDevPtr;
#endif /* TM_USE_IPV6 */
#ifdef TM_PEND_POST_NEEDED
    ttPendEntryPtr              socSelectPendEntryPtr; /* for select */
    ttPendEntry                 socSendPendEntry; /* Send Q or connect */
    ttPendEntry                 socRecvPendEntry; /* Recv Q or accept */
    ttPendEntry                 socClosePendEntry; /* linger on close */
#endif /* TM_PEND_POST_NEEDED */
/* ICMP info from the last ICMP error message received for this socket */
    ttIcmpInfo                  socIcmpInfo;
#ifdef TM_USE_IPV6
/* Set to the value of sockaddr_in6.sin6_flowinfo when a local IPv6 address
   is bound to the socket. The high-order 4-bits (corresponding to the IP
   header Version field) are set to 0. Stored in network byte order. */
    tt32Bit                     soc6FlowInfo;
#endif /* TM_USE_IPV6 */
#ifdef TM_SNMP_MIB
    tt64Bit                     socHCInDatagrams;
    tt64Bit                     socHCOutDatagrams;
    tt64Bit                     socHCInOctets;
    tt64Bit                     socHCOutOctets;
    tt32Bit                     socStartTime;
#endif /* TM_SNMP_MIB */
    unsigned int                socIndex;
#ifdef TM_USE_IPV6
/* Socket-level option IPV6_UNICAST_HOPS.([IPV6REQ].R2.18:10) */
    int                         soc6HopLimit;
/* Socket-level option IPV6_MULTICAST_HOPS.([IPV6REQ].R2.18:10) */
    int                         soc6McastHopLimit;
#endif /* TM_USE_IPV6 */

#ifdef TM_6_USE_RAW_SOCKET
/* Byte offset indicating the locating of the ULP checksum field for raw
   packets. Checksum computation is disabled if offset is negative. */
    int                         soc6RawChecksumOffset;
#endif /* TM_6_USE_RAW_SOCKET */
#ifdef TM_IGMP
/* Number of socket IGMP user API calls pending */
    tt16Bit                     socIgmpJoinsPending;
#endif /* TM_IGMP */
#ifdef TM_6_USE_MLD
/* Number of socket MLD user API calls pending */
    tt16Bit                     soc6MldJoinsPending;
#endif /* TM_6_USE_MLD */
    tt16Bit                     socMaxBackLog;
    tt16Bit                     socBackLog;
    tt16Bit                     socLingerTime; /* in seconds */
    tt16Bit                     socSelectFlags;
    tt16Bit                     socRecvError;
    tt16Bit                     socSendError;
    tt16Bit                     socCBFlags; /* socket call back flags */
    tt16Bit                     socSendAppendThreshold;
    tt16Bit                     socRecvCopyFraction;
    tt16Bit                     socMcastMhomeIndex;
#ifdef TM_USE_IPV6
/* IPv6 socket flags (TM_6_SOCF_... defined in t6macro.h) */
    tt16Bit                     soc6Flags;
#endif /* TM_USE_IPV6 */
#ifdef TM_USE_TCP_INCOMING_CB
/* Flags registered with socUserCBPacketFuncPtr above */
    tt16Bit                     socCBPacketFlags;
#endif /* TM_USE_TCP_INCOMING_CB */
#ifdef TM_USE_IPV4
    tt8Bit                      socIpTtl;
    tt8Bit                      socIpMcastTtl;
    tt8Bit                      socIpTos;
    tt8Bit                      socIpConTos;
#endif /* TM_USE_IPV4 */
    tt8Bit                      socUdpCountFlags;
    tt8Bit                      socFiller[3];
} ttSocketEntry;

typedef ttSocketEntry TM_FAR * ttSocketEntryPtr;
typedef ttSocketEntryPtr TM_FAR * ttSocketEntryPtrPtr;


typedef int (*ttIntSocFuncPtr)(ttSocketEntryPtr socketPtr, ttVoidPtr arg2Ptr);

/*
 * Common structure for IGMPV1/2/3 to convey user APIs' parameters.
 */
typedef struct tsIpMreqSrc
{
/*
 * Socket on which the user called the IGMP user API
 * setsockopt/setipv4sourcefilter(), etc..
 */
    ttSocketEntryPtr        imrSocketPtr;
/* Device associated with the IGMP user API */
    ttDeviceEntryPtr        imrDevPtr;
/* IPv4 Class D multicast address */
    tt4IpAddress            imrMcastAddr;
/* IPv4 interface address */
    tt4IpAddress            imrIfAddr;
/* Interface index (see ttDeviceEntry.devIndex) */
    tt32Bit                 imrIfIndex;
/* setsockopt option name */
    int                     imrOptionName;
/* multi home index associated with the IGMP user API */
    tt16Bit                 imrMhomeIndex;
} ttIpMreqSrc;

/* Pointer to ttIpMreqSrc structure */
typedef ttIpMreqSrc TM_FAR * ttIpMreqSrcPtr;

#ifdef TM_USE_IPV6
/*
 * Common structure for MLDv1/2 to convey user APIs' parameters.
 */
typedef struct ts6IpMreqSrc
{
/*
 * Socket on which the user called the MLD user API
 * setsockopt/setsourcefilter(), etc..
 */
    ttSocketEntryPtr        imr6SocketPtr;
/* Device associated with the MLD user API */
    ttDeviceEntryPtr        imr6DevPtr;
#ifdef TM_6_USE_MLDV2
/* peers' source list */
    ttSockAddrStoragePtr    imr6SrcAddrPtr;
/* peers' original source list */
    tt6SourceListPtr        imr6OldSrcListPtr;
#endif /* TM_6_USE_MLDV2 */
/* Unchecked multicast address */
    ttSockAddrStoragePtr    imr6McastSockAddrPtr;
/* IPv6 multicast address */
    tt6IpAddressPtr         imr6McastAddrPtr;
/* Interface index (see ttDeviceEntry.devIndex) */
    tt32Bit                 imr6IfIndex;
/* setsockopt option name */
    int                     imr6OptionName;
#ifdef TM_6_USE_MLDV2
    int                     imr6SrcCommand; /* ADD_SRC or DROP_SRC */
    tt32Bit                 imr6FilterMode; /* Include or Exclude */
/* Number of source addresses in the list */
    unsigned int            imr6NumSrc;
/* Change in the number of sockets/entities which have joined in
 * exclude mode */
    int                     imr6DeltaExclJoin;
/* Change in the number of sockets/entities which have joined in
 * exclude mode with no source filter list */
    int                     imr6DeltaEmptyExclJoin;
#endif /* TM_6_USE_MLDV2 */
/* multi home index associated with the MLD user API */
    tt16Bit                 imr6MhomeIndex;
} tt6IpMreqSrc;

/* Pointer to tt6IpMreqSrc structure */
typedef tt6IpMreqSrc TM_FAR * tt6IpMreqSrcPtr;
#endif /* TM_USE_IPV6 */


/*
 * TCP
 */

typedef tt32Bit  ttTs;  /* 32-bit time stamp */

/* Network header: TCP Header */
typedef struct tsTcpHeader
{
    ttIpPort tcpSrcPort;    /* Source port of the TCP segment */
    ttIpPort tcpDstPort;    /* Destination port of the TCP segment */
    ttSqn    tcpSeqNo;      /* 32-bit TCP sequence number */
    ttSqn    tcpAckNo;      /* 32-bit TCP acknowledgment number */
    tt8Bit   tcpDataOffset; /* 4-bit Data Offset/4-bit reserved bits */
    tt8Bit   tcpControlBits;/* 2-bit reserved bits/6-bit Control bits */
    tt16Bit  tcpWindowSize; /* 16-bit TCP window size */
/* One's complement checksum of TCP segment + pseudo_header */
    tt16Bit  tcpChecksum;
    tt16Bit  tcpUrgentPtr;  /* 16-bit Urgent pointer */
} ttTcpHeader;

typedef ttTcpHeader TM_FAR * ttTcpHeaderPtr;

/* END of TCP network header */

/*
 * TCP SEL ACK Block queue entry structure with Left Edge and Right Edge
 * sequence numbers
 */
typedef struct tsSackEntry
{
    struct tsSackEntry TM_FAR * blocQNextPtr;
    struct tsSackEntry TM_FAR * blocQPrevPtr;
           ttSqn                blocQLeftEdge;
           ttSqn                blocQRightEdge;
} ttSackEntry;

typedef ttSackEntry TM_FAR * ttSackEntryPtr;

typedef union tuTcpConnHeaderPtr
{
    ttSockAddrPtrUnionPtr       tcpuSockAddrUPtr;
    ttPacketPtr                 tcpuPacketPtr;
} ttTcpConnHeaderPtrUnion;

/*
 * Tcp State vector.
 */

typedef struct tsTcpVect
{
    ttSocketEntry               tcpsSocketEntry;
/* for queuing out of order packets */
    ttPacketPtr                 tcpsReassemblePtr;
/* for queuing recycled headers */
    ttPacketPtr                 tcpsRecycleHdrPtr;
/*
 * Outgoing TCP header (SYN, RST, or Keep Alive), or sockaddr pointer
 * for connect call.
 */
    ttTcpConnHeaderPtrUnion     tcpsConnHeaderPtrU;
#define tcpsSockAddrUPtr     tcpsConnHeaderPtrU.tcpuSockAddrUPtr
#define tcpsHeaderPacketPtr  tcpsConnHeaderPtrU.tcpuPacketPtr
#define tcpsSockAddrInPtr    tcpsSockAddrUPtr->sockInPtr
#define tcpsSockAddrIn6Ptr   tcpsSockAddrUPtr->sockIn6Ptr
#define tcpsSockAddrPeer6Ptr tcpsSockAddrUPtr->sockPeerAddr6Ptr
/*
 * For an listening/connection request vector/socket: pointer to next
 * and previous connection request vector/socket.
 * Note 2 queues:
 * . for half connected TCP vectors
 * . for fully connected but not yet accepted TCP vectors.
 */
#define TM_TCP_SYN_QUEUE    0
#define TM_TCP_ACCEPT_QUEUE 1
#define tcpsAcceptQueue tcpsConQueue[TM_TCP_ACCEPT_QUEUE]
#define tcpsSynQueue    tcpsConQueue[TM_TCP_SYN_QUEUE]
    struct
    {
        struct tsTcpVect TM_FAR   * tcpConReqNextPtr;
        struct tsTcpVect TM_FAR   * tcpConReqPrevPtr;
    }                           tcpsConQueue[TM_TCP_ACCEPT_QUEUE+1];
#ifdef TM_TCP_SACK
/* For queueing SEL ACK blocks */
    ttSackEntryPtr              tcpsSackBlockPtr[2];
#endif /* TM_TCP_SACK */
#ifdef TM_USE_TCP_KEEPALIVE
/* Do not pre-allocate keep alive timer. Only add it, if user sets the option */
    ttTimerPtr                  tcpsKeepAliveTmrPtr;
#endif /* TM_USE_TCP_KEEPALIVE */
#ifdef TM_OPTIMIZE_SPEED
/* Cache the send queue packet that we are currently sending */
    ttPacketPtr                 tcpsSendQPacketPtr;
/* Cache the sequence number of that packet */
    ttSqn                       tcpsSendQSqn;
#endif /* TM_OPTIMIZE_SPEED */
/* Keep track of send complete bytes for socket CB function */
    tt32Bit                     tcpsSendCompltBytes;
/* Delay ACK time for connection */
    tt32Bit                     tcpsDelayAckTime;
    ttS32Bit                    tcpsScSmRtt;  /* Scaled Smooth RTT */
    ttS32Bit                    tcpsScRttVar; /* Scaled Rtt variance */
    tt32Bit                     tcpsRtoDef;  /* default RTO */
/* Minimum Retransmission timeout*/
    tt32Bit                     tcpsRtoMin;
/* Maximum Retransmission timeout*/
    tt32Bit                     tcpsRtoMax;
    tt32Bit                     tcpsRto;    /* Retransmission timeout*/
/* Tcp maximum retransmition time, before connection is broken */
    tt32Bit                     tcpsMaxRt;
/* Minimum Zero window probe time */
    tt32Bit                     tcpsProbeMin;
/* Maximum Zero window probe time */
    tt32Bit                     tcpsProbeMax;
#ifdef TM_TCP_RFC2581
/* Time when last packet was transmitted */
    tt32Bit                     tcpsLastXmitTime;
#endif /* TM_TCP_RFC2581 */
/*
 * Send sequence variables
 */
/* Initial send sequence number (host byte order) */
    ttSqn                       tcpsIss;
/* send unacknowledge (host byte order) */
    ttSqn                       tcpsSndUna;
/* send next(host byte order)  */
    ttSqn                       tcpsSndNxt;
/* Highest sequence number sent (used because of retransmit) */
    ttSqn                       tcpsMaxSndNxt;
/* send urgent pointer (host byte order) */
    ttSqn                       tcpsSndUp;
/* Highest send next prior to retransmission */
    ttSqn                       tcpsRecover;
#ifdef TM_TCP_SACK
/* Forward-most sequence number + 1 held by the receiver */
    ttSqn                       tcpsSndFack;
/* Highest send next when starting recovery */
    ttSqn                       tcpsCongSndNxt;
/* Highest send next when retransmitting */
    ttSqn                       tcpsRexmitSndNxt;
/* Retransmitted data while in recovery mode */
    tt32Bit                     tcpsRetranData;
/* Data smoothing */
    ttS32Bit                    tcpsWinTrim;
#endif /* TM_TCP_SACK */
/* Initial Send Congestion Window */
    tt32Bit                     tcpsInitialCwnd;
/* Send congestion window */
    tt32Bit                     tcpsCwnd;
/* Send slow start threshold size */
    tt32Bit                     tcpsSsthresh;
/* send window (host byte order) */
    tt32Bit                     tcpsSndWnd;
/* Maximum send window seen so far (host byte order) */
    tt32Bit                     tcpsMaxSndWnd;
/* sequence number used for last window update */
    ttSqn                       tcpsSndWL1;
/* acknowledgment number used for last window update */
    ttSqn                       tcpsSndWL2;
/*
 * Receive sequence variables
 */
/* receive next (host byte order) */
    ttSqn                       tcpsRcvNxt;
/* receive window (host byte order) */
    tt32Bit                     tcpsRcvWnd;
    tt32Bit                     tcpsLastRcvTime;
/*
 * Pre-accept maximum recv window size (before receving the fist SYN),
 * and saved real maximum recv window size after that.
 */
    tt32Bit                     tcpsMaxRecvQueueBytes;
#ifdef TM_DEV_SEND_OFFLOAD
/* Offload data size (without TCP/IP header size) */
    tt32Bit                     tcpsOffloadDataSize;
#else /* !TM_DEV_SEND_OFFLOAD */
#define tcpsOffloadDataSize tcpsEffSndMss
#endif /* !TM_DEV_SEND_OFFLOAD */

#ifdef TM_USE_TCP_REXMIT_CONTROL
    tt32Bit                     tcpsConnTmLeftAtPause;
#endif /* TM_USE_TCP_REXMIT_CONTROL */

/* receive urgent pointer (host byte order) */
    ttSqn                       tcpsRcvUp;
/*
 * Sequence number of right edge of advertized window. (Could be smaller
 * than Rcv.Nxt+Rcv.Wnd to avoid silly window syndrome. Also used to
 * prevent shrinkage of our receive window.)
 */
    ttSqn                       tcpsRcvAdv;
/* initial receive sequence number (host byte order) */
    ttSqn                       tcpsIrs;
/* Congestion window decrease time stamp */
    ttTs                        tcpsCwndAge;
/*
 * Time stamp option support fields: TS.Recent and Last.ACK.sent
 * TS.Recent (tsVal's peer): holds a timestamp to be echoed in TSecr
 * whenever a segment is sent by us.
 */
    ttTs                        tcpsTsRecent;
/* host time of last TS.Recent*/
    ttTs                        tcpsTsRecentAge;
#ifdef TM_USE_SOCKET_IMPORT
    ttS32Bit                    tcpsTsCurrentFixup;
#endif /* TM_USE_SOCKET_IMPORT */
/* Last.ACK.sent: ACK field from the last segment sent by us.*/
    ttSqn                       tcpsLastAckSent;
    ttTimer                     tcpsTm[TM_TCPTM_LINGER+1];
/* Used to avoid race conditions on listening socket back pointer */
    unsigned int                tcpsThreadCount;
    int                         tcpsSoftError; /* ICMP soft error */
    int                         tcpsAbortError; /* abort connection error */
/* number of retransmitted seg*/
    int                         tcpsReXmitCnt;
/* Maximum number of retransmitted seg*/
    int                         tcpsMaxReXmitCnt;
#ifdef TM_USE_TCP_KEEPALIVE
/* Keep alive timer (2 hours) in seconds */
    int                         tcpsKeepAliveTime;
/* Keep alive timer interval in seconds / Idle timer */
    int                         tcpsIdleIntvTime;
    int                         tcpsKeepAliveProbeCnt;
#endif /* TM_USE_TCP_KEEPALIVE */
/*
 * Amount of time to stay in FIN WAIT 2 when socket has been closed
 * (10 minutes) in seconds.
 */
    int                         tcpsFinWt2Time;
/*
 * 2*Maximum segment life time (2*30 seconds) (TIME WAIT time) in
 * seconds
 */
    int                         tcps2MSLTime;
    tt16Bit                     tcpsSelectFlags; /* events to post on */
    tt16Bit                     tcpsSocketCBFlags; /* CB functions */
    tt16Bit                     tcpsMSS;        /* TCP MSS (RFC793)*/
    tt16Bit                     tcpsPeerMss;    /* TCP Peer MSS */
    tt16Bit                     tcpsEffSndMss;  /* TCP MSS without options */
/* TCP header size on recycle list*/
    tt16Bit                     tcpsHeaderSize;
/* Number of recycled headers on the socket */
    tt16Bit                     tcpsRecycleHdrCount;
/* Maximum number of recycled headers allowed on the socket */
    tt16Bit                     tcpsMaxRecycleHdrCount;
    tt16Bit                     tcpsFlags;      /* TCP flags */
    tt16Bit                     tcpsFlags2;     /* additional flag bits */
    tt16Bit                     tcpsFlags3;     /* additional flag bits */
    tt16Bit                     tcpsTmrFlags;   /* Timer flags */
/* Cached partial checksum */
    tt16Bit                     tcpsPseudoXsum;
/* Offload flags */
    tt16Bit                     tcpsOffloadFlags;
    tt16Bit                     tcpsSynFloodCount;
    tt8Bit                      tcpsSndWndScale;/* window scale option */
    tt8Bit                      tcpsRcvWndScale;/* window scale option */
    tt8Bit                      tcpsState;      /* TCP vector state */
    tt8Bit                      tcpsDupAcks;    /* Duplicate ACKs */
    tt8Bit                      tcpsPartialAcks;/* Partial ACKs */
/* number of non duplicate acks after duplicate ACK(s) */
    tt8Bit                      tcpsAcksAfterRexmit;
/* Out of band byte */
    tt8Bit                      tcpsOobByte;
/*
 * Maximum number of SQN in SACK option that will fit in the TCP header
 * (6, or 8)
 */
    tt8Bit                      tcpsMaxSackSqns;
#ifdef TM_USE_IPV6
/*
 * Specifies the network layer type for this socket ( TM_NETWORK_IPV4_LAYER,
 * TM_NETWORK_IPV6_LAYER ). Initialized in tfTcpSendSyn() for clients, and
 * tfTcpConReq for servers.
 */
    tt8Bit                      tcpsNetworkLayer;
    tt8Bit                      tcpsFiller[3];
#endif /* TM_USE_IPV6 */
#ifdef TM_USE_USER_PARAM
/* User-defined data */
    ttUserGenericUnion          tcpsUserParam;
#endif /* TM_USE_USER_PARAM */
#ifdef TM_USE_SOCKET_IMPORT
/* Pointer to the TCP state information provided by the user for creating
 * a connected socket in the established state.
 * The pointer is non-zero while the socket is nudged through a mock
 * TCP open and handshaking sequence.
 * Once established, the pointer is set to zero. */
    ttUserTcpConPtr             tcpsUserTcpConPtr;
#endif /* TM_USE_SOCKET_IMPORT */
} ttTcpVect;

typedef ttTcpVect TM_FAR * ttTcpVectPtr;

/* TCP state vector in Time Wait state */
typedef struct tsTcpTmWtVect
{
/* Linked list */
    ttNode              twsNode;
#ifdef TM_SNMP_CACHE
    ttSnmpCacheEntry    twsSnmpCacheEntry;
#endif /* TM_SNMP_CACHE */
/* Socket 4-tuple + device entry pointer */
    ttTupleDev          twsTupleDev;
/* Time wait timer */
    ttTimer             tws2MslTm;
/* Next Seq no (== SND.UNA == MaxSndNxt) */
    ttSqn               twsMaxSndNxt;
/* Next expected peer seq no */
    ttSqn               twsRcvNxt;
/*
 * Time stamp option support fields: TS.Recent and Last.ACK.sent
 * TS.Recent (tsVal's peer): holds a timestamp to be echoed in TSecr
 * whenever a segment is sent by us.
 */
    ttTs                twsTsRecent;
/* host time of last TS.Recent*/
    ttTs                twsTsRecentAge;
/* Last.ACK.sent: ACK field from the last segment sent by us is RCV.NXT. */
/* IPv4 or IPv6 network layer */
    tt8Bit              twsNetworkLayer;
    tt8Bit              twsFlags;
} ttTcpTmWtVect;

typedef ttTcpTmWtVect TM_FAR * ttTcpTmWtVectPtr;

/*
 * SLIP State vector.
 */
typedef struct tsSlipVect
{
/* The packet we are working on now for receive */
    ttPacketPtr                slipsPacketPtr;
/* Where are we in the packet data we are creating with receive */
    tt8BitPtr                  slipsWorkingPtr;
    tt8BitPtr                  slipsSendDataPtr;
    ttS16Bit                   slipsSendBufSize;
/* For input Processing (where are we in unstuffing) */
    tt8Bit                     slipsLastByteStuffState;
    tt8Bit                     slipsFiller[1];
    tt8Bit                     slipsSendBuf[TM_SLIP_DEF_BUF_SIZE];
} ttSlipVect;

typedef ttSlipVect TM_FAR * ttSlipVectPtr;

/*
 * MD2
 * See Copyright Information in trmd2.c
 */
typedef struct tsMd2Ctx {
    int      md2Num;
    tt8Bit   md2Data[16];
    tt32Bit  md2Cksm[16];
    tt32Bit  md2State[16];
} ttMd2Ctx;
typedef ttMd2Ctx TM_FAR * ttMd2CtxPtr;

/*
 * MD4
 * See Copyright Information from RSA in trmd4.c
 */
typedef struct tsMd4Ctx {
    tt32Bit md4State[4];
    tt32Bit md4Count[2];
    tt8Bit  md4Buffer[64];
} ttMd4Ctx;
typedef ttMd4Ctx TM_FAR * ttMd4CtxPtr;

/*
 * MD5
 * See Copyright Information from RSA in trmd5.c
 */

typedef struct tsMd5Ctx
{
/* number of _bits_ handled mod 2^64 */
  tt32Bit md5I[2];
/* scratch buffer */
  tt32Bit md5Buf[4];
/* input buffer */
  tt8Bit  md5In[64];
} ttMd5Ctx;
typedef ttMd5Ctx TM_FAR * ttMd5CtxPtr;

typedef struct
{
    tt32Bit TM_FAR shaDigest[ 5 ];     /* Message digest */
    tt32Bit shaCountLo;
    tt32Bit shaCountHi;                /* 64-bit bit count */
    tt32Bit TM_FAR shaData[ 16 ];      /* SHS data buffer */
} ttSha1Ctx;
typedef ttSha1Ctx TM_FAR * ttSha1CtxPtr;

typedef struct
{
    tt32Bit TM_FAR shaDigest[ 8 ];     /* Message digest */
    tt32Bit shaCountLo;
    tt32Bit shaCountHi;
    tt32Bit TM_FAR shaData[ 16 ];      /* SHS data buffer */
/* 16*32 = 512, it's acutally just 64, the block size *8 = 512 bits. 
 * so SHA384/512 will need a shaData length of 1024, somehow 
 */    
} ttSha256Ctx;
typedef ttSha256Ctx TM_FAR * ttSha256CtxPtr;

typedef struct 
{
    union 
    {
        ttSHAint64 w[ 80 ];        /* message schedule, input buffer, plus 64 words */   
        tt8Bit     shaData[ 640 ]; /* appears to be the same as shaData */
    } u;
    ttSHAint64 shaDigest[ 8 ];    /* 8 state variables, filled with initial values */
    ttSHAint64 sizeLo;            /* 64-bit count of hashed bytes. */
} ttSha512Ctx;
typedef ttSha512Ctx TM_FAR * ttSha384CtxPtr;
typedef ttSha512Ctx TM_FAR * ttSha512CtxPtr;
#if 0
typedef struct
{
    ttEspAlgorithmPtr   algPtr;
    ttGenericKey        genKey;
    tt8BitPtr           keyPtr;    
    tt8Bit              buffer[16];
    tt8Bit              iv[16];
/* number of bytes in the buffer */
    tt8Bit              size;    
} ttAesXcbcCtx;
typedef ttAesXcbcCtx TM_FAR * ttAesXcbcCtxPtr;
#endif
typedef struct
{
    tt8BitPtr keyPtr;
    ttVoidPtr contextPtr;
} ttGenericCmacCtx;
typedef ttGenericCmacCtx TM_FAR * ttGenericCmacCtxPtr;


/*
 * RFC-2507 IP header compression.
 */

/*
 * Parameters for IP header compression operation.
 */
typedef struct tsIphcOptions
{

/*
 * Maximum amount of time between sending full non-TCP headers.
 *      Default: TM_IPHC_MAX_TIME_DEF
 *      Limits: 1 - 255
 */
    tt16Bit iphcoMaxTime;

/*
 * Largest number of compressed non-TCP headers that may be sent without
 * sending a full header.
 *      Default: TM_IPHC_MAX_PERIOD_DEF
 *      Limits: 1 - 65535
 */
    tt16Bit iphcoMaxPeriod;

/*
 * Maximum number of outgoing non-TCP contexts.
 *      Default: TM_IPHC_CONTEXT_SPACE_DEF
 *      Limits: 3 - 65535
 */
    tt16Bit iphcoOutUdpSpace;

/*
 * Maximum number of incoming non-TCP contexts.
 *      Default: TM_IPHC_CONTEXT_SPACE_DEF
 *      Limits: 3 - 65535
 */
    tt16Bit iphcoInUdpSpace;

    tt16Bit iphcoMaxHeader;

/*
 * Maximum number of outgoing TCP contexts.
 *      Default: TM_IPHC_CONTEXT_SPACE_DEF
 *      Limits: 3 - 255
 */
    tt8Bit  iphcoOutTcpSpace;

/*
 * Maximum number of incoming TCP contexts.
 *      Default: TM_IPHC_CONTEXT_SPACE_DEF
 *      Limits: 3 - 255
 */
    tt8Bit  iphcoInTcpSpace;

/*
 * Flag indicating whether the IPHC decompressor should attempt to recover
 * from TCP errors.  This involves computing the TCP checksum (at least
 * one additional time) upon decompression of the packet to verify that
 * decompression was successful.  This is required to use the 'twice'
 * algorithm or header request error recovery.  If this flag is not set, the
 * checksum is not verified and will be validated only at the TCP layer.
 * The error will be corrected when the TCP peer retransmits this frame.
 *      Default: TM_IPHC_TCP_ERR_REC_DEF
 *      Limits: 1 or 0
 */
    tt8Bit  iphcoTcpErrRec;

/* Pad structure to 32-bit alignment */
    tt8Bit  iphcoPadding;

} ttIphcOptions;

typedef ttIphcOptions TM_FAR * ttIphcOptionsPtr;

/*
 * A UDP compression/decompression context.  Allocated for each UDP packet
 * stream.
 */
#ifdef TM_LINT
LINT_UNREF_MEMBER_BEGIN
#endif /* TM_LINT */

typedef struct tsIphcCtxInfo
{
/* Source address of the outer IP header. */
    ttIpAddress     ctxOuterSrcAddr;
/* Destination address of the outer IP header. */
    ttIpAddress     ctxOuterDestAddr;
/* Source address of the inner (tunneled) IP header. */
    ttIpAddress     ctxInnerSrcAddr;
/* Destination address of the inner (tunneled) IP header. */
    ttIpAddress     ctxInnerDestAddr;
/* Upper layer source port. */
    tt16Bit         ctxSourcePort;
/* Upper layer destination port. */
    tt16Bit         ctxDestPort;
/* Upper layer protocol type. */
    tt8Bit          ctxUpperLayerProto;
/* Protocol family (IPv4, IPv6) of outer IP header. */
    tt8Bit          ctxOuterProtoFamily;
/* Protocol family (IPv4, IPv6) of inner (tunneled) IP header.  */
    tt8Bit          ctxInnerProtoFamily;
    tt8Bit          ctxPaddingp[1];
} ttIphcCtxInfo;

typedef ttIphcCtxInfo TM_FAR * ttIphcCtxInfoPtr;

typedef struct tsIphcUdpContext
{
/* Information used to select this context for compression. */
    ttIphcCtxInfo                    uctxContextInfo;

/* Pointer to next context in list. */
    struct tsIphcUdpContext TM_FAR * uctxNextPtr;

/* Current full IP Header. */
    tt8BitPtr                        uctxIpHeaderPtr;

/* Current full UDP Header. */
    ttUdpHeader                      uctxUdpHeader;

/*
 * Timestamp indicating the last time a full header was sent from this
 * context.
 */
    tt32Bit                          uctxLastFullHdrTime;

/* Total length of the current IP header saved in uctxIpHeaderPtr. */
    ttPktLen                         uctxIpHeaderLength;

/*
 * The number of compressed headers that have been sent since the last full
 * header.
 */
    tt16Bit                          uctxCompHdrCount;

/* Current full header time period. */
    tt16Bit                          uctxPeriod;

/* Context ID. */
    tt16Bit                          uctxCid;


/* Context Generation */
    tt8Bit                           uctxGeneration;

/* Pad structure to 32-bit alignment */
    tt8Bit                           uctxPadding[1];
} ttIphcUdpContext;

typedef ttIphcUdpContext TM_FAR * ttIphcUdpContextPtr;
typedef ttIphcUdpContextPtr TM_FAR * ttIphcUdpContextPtrPtr;

/*
 * A TCP compression/decompression context.  Allocated for each TCP packet
 * stream.
 */
typedef struct tsIphcTcpContext
{
/* Information used to select this context for compression. */
    ttIphcCtxInfo                    tctxContextInfo;

/* Pointer to the next context in the list */
    struct tsIphcTcpContext TM_FAR * tctxNextPtr;

/* Current full IP header */
    tt8BitPtr                        tctxIpHeaderPtr;

/* Current full TCP header */
    ttTcpHeader                      tctxTcpHeader;

/* Length of payload in last compressed TCP packet. */
    ttPktLen                         tctxLastPayloadLen;

/* Total length of the current IP header saved in tctxIpHeaderPtr. */
    ttPktLen                         tctxIpHeaderLength;

/* Socket descriptor defining the packet stream for this context. */
    unsigned int                     tctxSocketDesc;

/* Context ID */
    tt16Bit                          tctxCid;

/* Boolean flag indicating if this context is valid. */
    tt8Bit                           tctxValid;

/* Pad structure to 32-bit alignment */
    tt8Bit                           tctxPadding[3];
} ttIphcTcpContext;
#ifdef TM_LINT
LINT_UNREF_MEMBER_END
#endif /* TM_LINT */

typedef ttIphcTcpContext TM_FAR * ttIphcTcpContextPtr;
typedef ttIphcTcpContextPtr TM_FAR * ttIphcTcpContextPtrPtr;

/*
 * Vector containing information about the current state of IP header
 * compression for this link.
 */
typedef struct tsIphcVect
{

/*
 * Must be the first element in the structure!  Contains the options used for
 * IPHC on this link.  Initialized to defaults by IPHC, modified by the link
 * layer.
 */
    ttIphcOptions       iphcOpts;

/* List of outgoing UDP contexts. */
    ttIphcUdpContextPtr iphcUdpOutCtxPtr;

/* List of incoming UDP contexts. */
    ttIphcUdpContextPtr iphcUdpInCtxPtr;

/* List of outgoing TCP contexts. */
    ttIphcTcpContextPtr iphcTcpOutCtxPtr;

/* List of incoming TCP contexts. */
    ttIphcTcpContextPtr iphcTcpInCtxPtr;

} ttIphcVect;

typedef ttIphcVect TM_FAR * ttIphcVectPtr;
typedef ttIphcVectPtr TM_FAR * ttIphcVectPtrPtr;


/*
 * PPP Options
 */
typedef struct tsLcpOptions
{
#ifdef TM_USE_PPP_CALLBACK
/* Callback operations as a collection of bits; bit # = operation #. */
    tt32Bit     lcpCallbackOpFlags;
#endif /* TM_USE_PPP_CALLBACK */
    tt32Bit lcpMagicNumber;
    tt32Bit lcpAccm;
#ifdef TM_PPP_LQM
    tt32Bit     lqmReportingPeriod;
#endif /* TM_PPP_LQM */
    tt16Bit lcpMaxReceiveUnit;
    tt16Bit lcpQualityProtocol;
    union
    {
/* in localwant struture, each bit represents an auth method */
        tt8Bit  lcpuAuthProtocolBits;
/* in localGot, localNeg strutures, the whole 8 bit represents
 * an auth method
 */
        tt8Bit  lcpuAuthMethod;
    }lcpAuthUnion;
#define lcpAuthProtocolBits   lcpAuthUnion.lcpuAuthProtocolBits
#define lcpAuthMethod         lcpAuthUnion.lcpuAuthMethod
    tt8Bit  lcpFiller[3];
} ttLcpOptions;

typedef ttLcpOptions TM_FAR * ttLcpOptionsPtr;

typedef struct tsIpcpOptions
{
    tt4IpAddress    ipcpIpAddress;
    tt4IpAddress    ipcpDnsPriAddress;
    tt4IpAddress    ipcpDnsSecAddress;
/* IPHC: Maximum value of TCP context identifier. */
    tt16Bit         ipcpCompTcpSpace;
/* IPHC: Maximum value of non-TCP context identifier. */
    tt16Bit         ipcpCompNonTcpSpace;
/* IPHC: Maximum interval between sending full headers. */
    tt16Bit         ipcpCompMaxPeriod;
/* IPHC: Maximum time, in seconds, between sending full headers. */
    tt16Bit         ipcpCompMaxTime;
/* IPHC: Largest header size that may be compressed, in bytes. */
    tt16Bit         ipcpCompMaxHeader;
/* IPv4 compression protocol.  Set to zero if compression is disabled (default).
   Otherwise, supported types are TM_PPP_COMP_TCP_PROTOCOL (Van Jacobson) and
   TM_PPP_IPHC_COMP_TCP. (RFC-2507 style IP header compression) */
    tt16Bit         ipcpCompressProtocol;
    tt8Bit          ipcpVjMaxSlots;
    tt8Bit          ipcpVjConnComp;
    tt8Bit          ipcpPadding[2];
} ttIpcpOptions;

typedef ttIpcpOptions TM_FAR * ttIpcpOptionsPtr;

typedef struct tsPapOptions
{
/* Function to call when we get an authentication request */
    ttPapAuthenticateFunctPtr papAuthenticatePtr;
    tt8BitPtr                 papUserNamePtr;
    tt8BitPtr                 papPasswordPtr;
} ttPapOptions;

typedef ttPapOptions TM_FAR * ttPapOptionsPtr;

typedef struct tsChapOptions
{
/* Function to call when we get an authentication request */
    ttChapAuthenticateFunctPtr   chapAuthenticatePtr;
    tt8BitPtr                    chapUserNamePtr;
    tt8BitPtr                    chapSecretPtr;
    tt8Bit                     chapValue[TM_CHAP_MAX_VALUE_SIZE];
} ttChapOptions;

typedef  ttChapOptions  TM_FAR * ttChapOptionsPtr;

/* PPP state function pointer */
typedef int (*ttPppStateFunctPtr)(ttVoidPtr    pppVectPtr,
                                  ttPacketPtr  packetPtr);

/* PPP state function pointer */
/* This gives a compiler warning */
/*typedef int (*ttPppStateFunctPtr)(struct tsPppVect TM_FAR * pppVectPtr,
                                  ttPacketPtr               packetPtr);
*/
typedef struct tsCpState
{
/* For config and terminate */
    ttTimerPtr                cpsTmrPtr;
/* The state functions to be associated with the layer we are in */
    ttPppStateFunctPtr        TM_FAR *cpsStateFuncList;
/* A counter of how many times that we have left to try this send */
    tt8Bit                    cpsRetryCounter;
/* The initial value for our retry counter */
    tt8Bit                    cpsRetryInitialValue;
/* The number of seconds between retry attempts */
    tt8Bit                    cpsRetryTimeoutSeconds;
/* The state that we are currently working in */
    tt8Bit                    cpsState;
/* Identifier used for this packet */
    tt8Bit                    cpsIdentifier;
/* Max number of terminate requests before giving up */
    tt8Bit                    cpsInitTrmRetryCnt;
/* Max number of configuration requests before giving up */
    tt8Bit                    cpsInitCfgRetryCnt;
/* Max number of NAKs to be sent before rejecting an option (max-failures) */
    tt8Bit                    cpsInitMaxFailures;
/* Current number of NAK failures */
    tt8Bit                    cpsFailures;
/* Numbers of times this layer has negotiated */
    tt8Bit                    cpsNegotiateCounter;
    tt8Bit                    cpsMagicNumberFailures;
/* Number of LCP requests sent by the peer in the opened state */
    tt8Bit                    cpsPeerReq;
} ttCpState;

typedef ttCpState TM_FAR *ttCpStatePtr;

typedef struct tsLcpState
{
/* State Information MUST BE FIRST */
    ttCpState                 lcpsStateInfo;
/* Flag to tell us which LCP option to negotiate for us */
    tt32Bit                   lcpsLocalNegotiateOption;
/* Flag to tell us which LCP option to allow the remote to use */
    tt32Bit                   lcpsRemoteNegotiateOption;
/* Flag to tell us which LCP options that we ACKed for the remote */
    tt32Bit                   lcpsRemoteAckedOptions;
/* LCP Option Values we want to use for our side */
    ttLcpOptions              lcpsLocalWantOptions;
/* LCP Option Values the remote will let us use */
    ttLcpOptions              lcpsLocalNegOptions;
/* LCP Option Values we are using (ACKed) */
    ttLcpOptions              lcpsLocalGotOptions;
/* LCP Option Values that we let the remote side use */
    ttLcpOptions              lcpsRemoteAllowOptions;
/* LCP Option Values that other side is using (WE ACKed)*/
    ttLcpOptions              lcpsRemoteSetOptions;
} ttLcpState;

typedef ttLcpState TM_FAR * ttLcpStatePtr;

typedef struct tsIpcpState
{
/* State Information MUST BE FIRST */
    ttCpState                 ipcpsStateInfo;
/* Flag to tell us which IPCP option to negotiate for us */
    tt32Bit                   ipcpsLocalNegotiateOption;
/* Flag to tell us which IPCP option to allow the remote to use */
    tt32Bit                   ipcpsRemoteNegotiateOption;
/* Flag to tell us which IPCP options that we ACKed for the remote */
    tt32Bit                   ipcpsRemoteAckedOptions;
/* IPCP Option Values we want to use for our side */
    ttIpcpOptions             ipcpsLocalWantOptions;
/* IPCP Option Values the remote will let us use */
    ttIpcpOptions             ipcpsLocalNegOptions;
/* IPCP Option Values the remote side will let us use */
    ttIpcpOptions             ipcpsLocalGotOptions;
/* IPCP Option Values that we let the remote side use */
    ttIpcpOptions             ipcpsRemoteAllowOptions;
/* IPCP Option Values that other side is using */
    ttIpcpOptions             ipcpsRemoteSetOptions;
} ttIpcpState;

typedef ttIpcpState TM_FAR * ttIpcpStatePtr;

typedef struct tsPapState
{
/* State Information MUST BE FIRST */
    ttCpState                 papsStateInfo;
/* The info we will send when the peer requests PAP */
    ttPapOptions              papsLocalOurInfo;
/* The info we expect when we request PAP */
    ttPapOptions              papsRemoteAllowInfo;
/* Timer to close the connection if the peer does not send Auth-Reqs */
    ttTimerPtr                papsRemoteReqTimerPtr;

} ttPapState;

typedef ttPapState TM_FAR * ttPapStatePtr;

typedef struct tsChapState
{
/* State Information MUST BE FIRST */
    ttCpState                  chapsStateInfo;
/* The info we will send when the peer requests CHAP */
    ttChapOptions              chapsLocalOurInfo;
/* The info we expect when we request CHAP */
    ttChapOptions              chapsRemoteAllowInfo;
    ttPacketPtr                chapsResponsePacketPtr;
/* Extra timer for CHAP responses */
    ttTimerPtr                 chapsResponseTimerPtr;
/* Extra counter for CHAP responses */
    tt8Bit                     chapsResponseCounter;
    tt8Bit                     chapsFiller[3];
} ttChapState;

typedef ttChapState TM_FAR * ttChapStatePtr;

#ifdef TM_USE_IPV6
/* ttIp6cpOptions contains all of the IPV6CP options to be negotiated. */
typedef struct tsIp6cpOptions
{
/* IPv6 interface identifier */
    tt32Bit ip6cpInterfaceId[2];
/* IPv6 compression protocol.  Set to zero if compression is disabled (default).
   Otherwise, the only supported type is TM_PPP_IPHC_COMP_TCP. */
    tt16Bit ip6cpCompressProtocol;
/* IPHC: Maximum value of TCP context identifier. */
    tt16Bit ip6cpCompTcpSpace;
/* IPHC: Maximum value of non-TCP context identifier. */
    tt16Bit ip6cpCompNonTcpSpace;
/* IPHC: Maximum interval between sending full headers. */
    tt16Bit ip6cpCompMaxPeriod;
/* IPHC: Maximum time, in seconds, between sending full headers. */
    tt16Bit ip6cpCompMaxTime;
/* IPHC: Largest header size that may be compressed, in bytes. */
    tt16Bit ip6cpCompMaxHeader;

} ttIp6cpOptions;
typedef ttIp6cpOptions TM_FAR * ttIp6cpOptionsPtr;

typedef struct tsIp6cpState
{
/* State Information MUST BE FIRST */
    ttCpState ip6cpsStateInfo;
/* Flag to tell us which IPV6CP option to negotiate for us */
    tt32Bit ip6cpsLocalNegotiateOption;
/* Flag to tell us which IPV6CP option to allow the remote to use */
    tt32Bit ip6cpsRemoteNegotiateOption;
/* Flag to tell us which IPV6CP options that we ACKed for the remote */
    tt32Bit ip6cpsRemoteAckedOptions;
/* IPV6CP Option Values we want to use for our side */
    ttIp6cpOptions ip6cpsLocalWantOptions;
/* IPV6CP Option Values the remote will let us use */
    ttIp6cpOptions ip6cpsLocalNegOptions;
/* IPV6CP Option Values the remote side will let us use */
    ttIp6cpOptions ip6cpsLocalGotOptions;
/* IPV6CP Option Values that we let the remote side use */
    ttIp6cpOptions ip6cpsRemoteAllowOptions;
/* IPV6CP Option Values that other side is using */
    ttIp6cpOptions ip6cpsRemoteSetOptions;
/* Count of the number of times we sent a Conf-Nak to the peer in response to
   receiving a Conf-Req without the Interface-Identifier option set.  This
   count should never exceed 1. */
    tt8Bit ip6cpsIfIdentNakCount;
    tt8Bit ip6cpsFiller[3];
} ttIp6cpState;
typedef ttIp6cpState TM_FAR * ttIp6cpStatePtr;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_PPP_CALLBACK
typedef struct tsCallbackState
{
/* User callback function. */
    ttPppCallbackUserFunctPtr   cbcpsUserFuncPtr;
/* State timer. */
    ttTimerPtr                  cbcpsTmrPtr;
/* User specified address (TM_CBCP_OP_ADDRESS). */
    tt8BitPtr                   cbcpsAddressSetPtr;
/* Protocol configured address. */
    tt8BitPtr                   cbcpsAddressCfgPtr;
/* Data sent in configuration response. */
    tt8BitPtr                   cbcpsResponseDataPtr;
/* Data sent in configuration acknowledge. */
    tt8BitPtr                   cbcpsAckDataPtr;
/* User specified address length. */
    tt16Bit                     cbcpsAddressSetLength;
/* Protocol configured address length. */
    tt16Bit                     cbcpsAddressCfgLength;
/* Length of data sent in configuration response. */
    tt16Bit                     cbcpsResponseDataLength;
/* Length of data sent in configuration acknowledge. */
    tt16Bit                     cbcpsAckDataLength;
/* User specified Callback type values that we will allow. */
    tt8Bit                      cbcpsTypeSet[4];
/* Number of items in cbcpsTypeSet. */
    tt8Bit                      cbcpsTypeSetCount;
/* The Callback type that we will send in config response. */
    tt8Bit                      cbcpsTypeRespond;
/* The Callback type that we will send in config ack. */
    tt8Bit                      cbcpsTypeAck;
/* Maximum number of send attempts. */
    tt8Bit                      cbcpsMaxRetry;
/* Time between sends attempts (seconds). */
    tt8Bit                      cbcpsRetryTimeout;
/* Delay before disconnecting (seconds). */
    tt8Bit                      cbcpsDisconnectDelay;
/* State retry counter. */
    tt8Bit                      cbcpsRetryCounter;
/* State retry timer reload value. */
    tt8Bit                      cbcpsRetryTimeoutSeconds;
/* Current state. */
    tt8Bit                      cbcpsState;
/* Latest configuration request identifier. */
    tt8Bit                      cbcpsRequestId;
/* Identifier to send in configuration response. */
    tt8Bit                      cbcpsRespondId;
/* Role of the local machine: caller or answerer. */
    tt8Bit                      cbcpsRole;
/* User specified callback delay. */
    tt8Bit                      cbcpsDelaySet;
/* Protocol configured callback delay. */
    tt8Bit                      cbcpsDelayCfg;
/* Is this protocol manditory? (currently not used.) */
    tt8Bit                      cbcpsMandatory;
/* Is PPP going down/up because of callback? */
    tt8Bit                      cbcpsIsActive;
} ttCallbackState;
typedef ttCallbackState TM_FAR * ttCallbackStatePtr;
#endif /* TM_USE_PPP_CALLBACK */

/*
 * VJ Header Compression data structure
 */

typedef struct tsVjCompData
{
    struct tsVjCompData TM_FAR * vjsNextPtr;
#define vjsIpHeader vjsUnion.vjsuIpHeader
    union
    {
        ttIpHeader               vjsuIpHeader;
        tt8Bit                   vjsuMaxHeader[
            TM_4PAK_IP_MAX_HDR_LEN+TM_PAK_MAX_TCP_HDR];
    } vjsUnion;
    tt8Bit                       vjsUsed;
    tt8Bit                       vjsConnId;
    tt8Bit                       vjsIpHdrLength;
    tt8Bit                       vjsTcpHdrLength;
} ttVjCompData;

typedef ttVjCompData TM_FAR *ttVjCompDataPtr;

#ifdef TM_PPP_LQM
/*
 * PPP LQM (Link Quality Management) State vector.
 */

typedef struct  tsLqmVect
{
    ttLqrCountDeltas    lqrCountDeltas;
    ttLqrCountsPtr      lastRcvdLqrPtr;
    ttLqmMonitorFuncPtr monitorFuncPtr;
    ttTimerPtr          lqrTimerPtr;
    ttTimerPtr          lqrReTxTimerPtr;
    tt32Bit             lastTickCount;
    tt32Bit             lqrTimerPeriodMsec;
    tt32Bit             negotiatedLqrTimerPeriodMsec;
    tt32Bit             peerLqrTimerPeriodMsec;
    tt32Bit             lqrReTxPeriodMsec;
    tt32Bit             txSaveInLqrs;
    tt16Bit             hysteresisMaxFailures;
    tt16Bit             failureCount;
    tt16Bit             hysteresisSamples;
    tt16Bit             sampleCount;
    tt8Bit              lqrReTxCount;
    tt8Bit              enabledStatus;
    tt8Bit              rcvLqrPendingStatus;
    tt8Bit              filler;
} ttLqmVect;
typedef ttLqmVect TM_FAR * ttLqmVectPtr;

/*
 * Link-Quality-Report Packet Type
 */
typedef struct tsPppLqrPacketType
{
    tt32Bit magicNumber;
    tt32Bit lastOutLqrs;
    tt32Bit lastOutPackets;
    tt32Bit lastOutOctets;
    tt32Bit peerInLqrs;
    tt32Bit peerInPackets;
    tt32Bit peerInDiscards;
    tt32Bit peerInErrors;
    tt32Bit peerInOctets;
    tt32Bit peerOutLqrs;
    tt32Bit peerOutPackets;
    tt32Bit peerOutOctets;
} ttPppLqrPacketType;

typedef ttPppLqrPacketType TM_FAR *ttPppLqrPacketTypePtr;
#endif /* TM_PPP_LQM */

/*
 * PPP State vector.
 */
typedef struct tsPppVect
{
/* Note: NextPtr need to be first for recycle list */
    struct tsPppVect TM_FAR * pppsNextPtr;
/* The packet we are working on now for receive */
    ttPacketPtr               pppsPacketPtr;
/* The device entry that we are linked to */
    ttDeviceEntryPtr          pppsDeviceEntryPtr;
/* Where are we in the packet data we are creating with receive */
    tt8BitPtr                 pppsWorkingPtr;

/*
 * Timer to handle waiting for the user to open another protocol family
 * if one has failed.  Only used in IPv4/IPv6 dual stack mode.
 */
    ttTimerPtr                pppsOpenFailTimerPtr;

#ifdef TM_USE_IPV4
/* Pointer to the most recently used entries in VJ data table */
    struct tsVjCompData TM_FAR * pppsVjSendDataPtr;
    struct tsVjCompData TM_FAR * pppsVjRecvDataPtr;
#endif /* TM_USE_IPV4 */

/*
 * Array of pointers to the state information for each layer
 * Size must allow for each of the pppsXxxState structs listed below
 */
    ttCpStatePtr              pppsStateInfoPtrArray[5];
    ttLcpState                pppsLcpState;
    ttPapState                pppsPapState;
    ttChapState               pppsChapState;
#ifdef TM_USE_IPV4
    ttIpcpState               pppsIpcpState;
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
    ttIp6cpState              pppsIp6cpState;
#endif /* TM_USE_IPV6 */
#ifdef TM_USE_PPP_CALLBACK
    ttCallbackState           pppsCallbackState;
#endif /* TM_USE_PPP_CALLBACK */

/*
 * Pointer to send buffer. Either allocated on user demand or point inside
 * preallocated pppsSendBuf &pppsSendBuf[0].
 */
    ttCharPtr                 pppsSendBufPtr;

/* Pointer to the IP Header Compression state vector, if being used. */
    ttIphcVectPtr             pppsIphcVectPtr;

#ifdef TM_PPP_LQM
/* pointer to LQM state vector */
    ttLqmVectPtr              pppsLqmVectPtr;

/* pointer to user-defined function to handle Echo-Reply */
    ttEchoReplyFuncPtr        pppsEchoReplyFuncPtr;

/* [RFC1989].R2.3:10, per-frame count of InGoodOctets */
    tt32Bit                   pppsInGoodFrameOctets;
#endif /* TM_PPP_LQM */

#ifdef TM_USE_IPV6
/*
 * Random interface identifiers for both ends of the PPP link.  Generated at
 * initialization.  The IEEE EUI-64 universal/local bit ("u") must be set to
 * zero. ppps6RandomLocalId[0] and ppps6RandomPeerId[0] are most significat.
 */
    tt32Bit                   ppps6RandomLocalId[2];
    tt32Bit                   ppps6RandomPeerId[2];
#endif /* TM_USE_IPV6 */

    ttPktLen                  pppsHdrDecompressSpace;

/* Size of buffer to copy data into on transmit */
    tt16Bit                   pppsSendBufSize;
    tt16Bit                   pppsUserSendBufSize;

/* The Frame Check Sequence we have in this receive session */
    tt16Bit                   pppsWorkingFcs;

/* For input Processing (where are we in unstuffing) */
    tt8Bit                    pppsLastByteStuffState;

#ifdef TM_USE_IPV4
/* For input processing (where are we in padding the VJ Fields) */
    tt8Bit                    pppsVjCompFlag;
    tt8Bit                    pppsVjOptionFlags;
    tt8Bit                    pppsVjOffset;

/* Previous VJ compression connection */
    tt8Bit                    pppsLastSentConnId;
    tt8Bit                    pppsLastRecvConnId;
#else /* !TM_USE_IPV4 */
    tt8Bit                    ppps6Padding;
#endif /* TM_USE_IPV4 */

    tt8Bit                    pppsEndFrame;
/*
 * Amount of time (in seconds) to wait for the user to open another protocol
 * family (such as IPv4) if the other one has failed.
 */
    tt8Bit                    pppsOpenFailTimeout;

/* Length of the last Conf-Req sent (used for incoming Conf-Ack verification */
    tt8Bit                    pppsLastConfReqLen;

#ifdef TM_USE_IPV6
    tt8Bit                    ppps6LastConfReqLen;
#else /* !TM_USE_IPV6 */
    tt8Bit                    pppsPadding[1];
#endif /* TM_USE_IPV6 */



/*
 * Buffer containing the last Conf-Req sent (used for incoming Conf-Ack
 * verification).
 */
    tt8Bit                    pppsLastConfReq[TM_PPP_MAX_CONF_REQ];

#ifdef TM_USE_IPV6
/*
 * Last IPV6CP Conf-Req sent.  When using the stack in dual-mode, a new
 * buffer is needed, since IPCP and IPV6CP could be used simultaneously;
 * When only IPV6CP is being used, the normal can be re-used.
 */
#ifdef TM_USE_IPV4
    tt8Bit                    ppps6LastConfReq[TM_PPP_MAX_CONF_REQ];
#else /* !TM_USE_IPV4 */
#define ppps6LastConfReq  pppsLastConfReq
#endif /* TM_USE_IPV4 */
#endif /* TM_USE_IPV6 */
    tt8Bit                    pppsClientState;
/* This field has to be last */
    char                      pppsSendBuf[TM_PPP_DEF_BUF_SIZE];
} ttPppVect;

typedef ttPppVect TM_FAR * ttPppVectPtr;


#ifdef TM_DNS_USE_SRV
/* Extended addrinfo structure with extra field for SRV-specific info */
typedef struct tsAddrInfoExt
{

/* Defines to access addrinfo structure members more easily */
#define aie_flags       aie_addrinfo.ai_flags
#define aie_family      aie_addrinfo.ai_family
#define aie_socktype    aie_addrinfo.ai_socktype
#define aie_protocol    aie_addrinfo.ai_protocol
#define aie_srvpri      aie_addrinfo.ai_addrlen
#define aie_srvhostname aie_addrinfo.ai_canonname
#define aie_addr        aie_addrinfo.ai_addr
#define aie_next        aie_addrinfo.ai_next

/* Standard addrinfo structure */
    struct addrinfo          aie_addrinfo;

#ifdef TM_USE_IPV4
/* Pointer to linked list of addrinfo structures containing v4 addresses */
    struct addrinfo TM_FAR * aie_ip4addrs;
#endif /* TM_USE_IPV4 */

#ifdef TM_USE_IPV6
/* Pointer to linked list of addrinfo structures containing v6 addresses */
    struct addrinfo TM_FAR * aie_ip6addrs;
#endif /* TM_USE_IPV6 */

/* SRV server weight */
    unsigned int             aie_srvweight;

/* SRV port */
    tt16Bit                  aie_port;

/* Extra flags */
    tt8Bit                   aie_extflags;

/* Owner count for this data structure */
    tt8Bit                   aie_ownercount;

/* Number of addrinfo structs pointed to by aie_ip4addrs and aie_ip6addrs */
    tt8Bit                   aie_addrcount;
} ttAddrInfoExt, TM_FAR * ttAddrInfoExtPtr;
#endif /* TM_DNS_USE_SRV */

/*
 * DNS host table support.
 */
typedef struct tsDnsHostEntry
{
    ttNode                  hostEntryNode;
    ttCharPtr               hostnameStr;
    struct sockaddr_storage hostAddress;
} ttDnsHostEntry;

typedef ttDnsHostEntry TM_FAR * ttDnsHostEntryPtr;
typedef ttDnsHostEntryPtr TM_FAR * ttDnsHostEntryPtrPtr;

typedef ttDnsHostEntryPtr (TM_CODE_FAR * ttDnsHostTableSearchFuncPtr)(
    const char TM_FAR * hostnameStr );

/*
 * DNS Resolver Cache Entry Structure
 */
typedef struct tsDnsCacheEntry
{

/* Next entry in cache; set to zero if this entry is last */
    struct tsDnsCacheEntry TM_FAR * dnscNextEntryPtr;

/* Previous entry in cache; set to zero if this entry is first */
    struct tsDnsCacheEntry TM_FAR * dnscPrevEntryPtr;

/* Pointer to chain of address information structures. */
    struct addrinfo        TM_FAR * dnscAddrInfoPtr;

/* Hostname (eg, "server.treck.com") for this entry */
    ttCharPtr                       dnscHostnameStr;

/* String to contain hostname from reverse lookup */
    ttCharPtr                       dnscRevHostnameStr;

#ifdef TM_USE_DNS_DOMAIN_SEARCH
/* Original hostname, prior to adding domain suffix (binary form) */
    tt8BitPtr                       dnscOrigRequestStr;

/* List of domain names to try with hostname (binary form) */
    tt8BitPtr                       dnscDomainList;

/* Next domain name in dnscDomainList */
    tt8BitPtr                       dnscDomainNext;
#endif /* TM_USE_DNS_DOMAIN_SEARCH */

/* Retransmission timer */
    ttTimerPtr                      dnscTimerPtr;

/*
 * String used in DNS query packet: the requested hostname (ASCII) translated
 * to the DNS label format.
 */
    ttCharPtr                       dnscRequestStr;
#ifdef TM_PEND_POST_NEEDED
/* Semaphore used in blocking mode */
    ttPendEntry                     dnscPendEntry;
#endif /* TM_PEND_POST_NEEDED */

#ifdef TM_USE_IPV6
/* IPv6 only: Device index of interface the response was received on. */
    tt32Bit                         dnsc6DevIndex;

/* IPv6 only: Site ID of the interface the response was received on. */
    tt32Bit                         dnsc6SiteId;
#endif /* TM_USE_IPV6 */

/* Error code (if any) returned from socket of DNS server */
    int                             dnscErrorCode;

/* Number of retransmissions left before request is aborted */
    int                             dnscRetriesLeft;

/* Index of the current DNS server */
    int                             dnscServerNum;

/* Flags indicating which DNS servers have been tried */
    ttGenericUnion                  dnscCurServerList;

/* Socket descriptor to send requests with */
    int                             dnscSocket;

/* Value of 'tvTime' when this DNS response was recieved */
    tt32Bit                         dnscTimestamp;

/* Time in milliseconds,since 'dnscTimestamp',that this cache entry is valid */
    tt32Bit                         dnscTtl;

/* Indicates if this entry is completed and has been retrieved by the user */
    tt16Bit                         dnscFlags;

/* Indicates how many applications are pending or quering the entry */
    tt16Bit                         dnscCount;

/* ID of the last request sent that was associated with this cache entry */
    tt16Bit                         dnscRequestId;

/* Query type (Name, MX, reverse) */
    tt16Bit                         dnscQueryType;

#ifdef TM_DNS_USE_SRV
/* Number of servers that have been sorted so far (used by SRV) */
    tt16Bit                         dnscSrvSortedCount;

/* Number of servers associated with this cache entry (used by SRV) */
    tt8Bit                          dnscSrvHostCount;
#endif /* TM_DNS_USE_SRV */

} ttDnsCacheEntry;

typedef ttDnsCacheEntry TM_FAR * ttDnsCacheEntryPtr;
typedef ttDnsCacheEntryPtr TM_FAR * ttDnsCacheEntryPtrPtr;

typedef struct tsDnsServerEntry
{
    struct sockaddr_storage dseServerAddress;
    unsigned int            dseFailures;
} ttDnsServerEntry;
typedef ttDnsServerEntry TM_FAR * ttDnsServerEntryPtr;

#ifdef TM_USE_RFC3484
typedef struct tsDnsListEntry
{
    struct addrinfo TM_FAR *    dleAddrInfoPtr;
    ttDeviceEntryPtr            dleDevPtr;
    struct sockaddr_storage     dleSourceAddr;
    ttRtCacheEntry              dleRouteCache;
    tt32Bit                     dleFlags;
    int                         dleMatchingPrefixLen;
    tt16Bit                     dleV6MhomeIndex;
    ttUser8Bit                  dleScope;
    tt8Bit                      dlePrecedence;
} ttDnsListEntry;
typedef ttDnsListEntry TM_FAR * ttDnsListEntryPtr;
typedef struct tsAddrPolicyEntry
{
    ttNode                      apeNode;
    tt6IpAddress                apePrefix;
    int                         apePrefixLen;
    tt8Bit                      apePrecedence;
    tt8Bit                      apeLabel;
} ttAddrPolicyEntry;
typedef ttAddrPolicyEntry TM_FAR * ttAddrPolicyEntryPtr;
#endif /* TM_USE_RFC3484 */

/*
 * Common between FTP server and Telnet server.
 */

/*
 * Doubly linked Queue structure.
 */
typedef struct tsQueue
{
/* Pointer to next entry in list of connections */
    ttVoidPtr                     qNextEntryPtr;
    ttVoidPtr                     qPrevEntryPtr;
} ttQueue;

/* Server queue structure (for RUN Q and open connection list) */
typedef struct tsServerQueue
{
#define servNextQEntryPtr(qIndex)       servQEntry[qIndex].qNextEntryPtr
#define servPrevQEntryPtr(qIndex)       servQEntry[qIndex].qPrevEntryPtr
/* One queue for RUN Q, and one queue for open connection list */
    ttQueue                    servQEntry[2];
} ttServerQueue;

typedef ttServerQueue TM_FAR * ttServerQueuePtr;

/* Server head queue structure (for head of RUN Q and open connection list) */
typedef struct tsServerQueueHead
{
#define servHeadNextQEntryPtr(qIndex) servQHead.servQEntry[qIndex].qNextEntryPtr
#define servHeadPrevQEntryPtr(qIndex) servQHead.servQEntry[qIndex].qPrevEntryPtr
    ttServerQueue              servQHead;
    int                        servQHeadCount[2];
} ttServerQueueHead;
/* Node descriptor for Generic linked list */

typedef ttServerQueueHead TM_FAR * ttServerQueueHeadPtr;

#ifdef TM_SNMP_MIB
typedef struct tsIpMib
{
    ttS32Bit      ipForwarding;
    ttS32Bit      ipDefaultTTL;
    tt32Bit       ipInReceives;
    tt32Bit       ipInHdrErrors;
    tt32Bit       ipInAddrErrors;
    tt32Bit       ipForwDatagrams;
    tt32Bit       ipInUnknownProtos;
    tt32Bit       ipInDiscards;
    tt32Bit       ipInDelivers;
    tt32Bit       ipOutRequests;
    tt32Bit       ipOutDiscards;
    tt32Bit       ipOutNoRoutes;
    ttS32Bit      ipReasmTimeout;
    tt32Bit       ipReasmReqds;
    tt32Bit       ipReasmOKs;
    tt32Bit       ipReasmFails;
    tt32Bit       ipFragOKs;
    tt32Bit       ipFragFails;
    tt32Bit       ipFragCreates;
    tt32Bit       ipRoutingDiscards;
    tt32Bit       ipv4InterfaceTableLastChange;
#ifdef TM_USE_IPV6
    tt32Bit       ipv6InterfaceTableLastChange;
    tt32Bit       ipv6IpForwarding;
    tt32Bit       ipv6IpDefaultHopLimit;
#endif /* TM_USE_IPV6 */
    tt32Bit       ipAddressSpinLock;
    tt32Bit       inetCidrRouteNumber;
#ifdef U_ip
U_ip
#endif /* U_ip */
    char          valid[3];
    char          ipFiller;
} ttIpMib;

typedef struct tsIcmpMib
{
    tt32Bit       icmpInMsgs;
    tt32Bit       icmpInErrors;
    tt32Bit       icmpInDestUnreachs;
    tt32Bit       icmpInTimeExcds;
    tt32Bit       icmpInParmProbs;
    tt32Bit       icmpInSrcQuenchs;
    tt32Bit       icmpInRedirects;
    tt32Bit       icmpInEchos;
    tt32Bit       icmpInEchoReps;
    tt32Bit       icmpInTimestamps;
    tt32Bit       icmpInTimestampReps;
    tt32Bit       icmpInAddrMasks;
    tt32Bit       icmpInAddrMaskReps;
    tt32Bit       icmpOutMsgs;
    tt32Bit       icmpOutErrors;
    tt32Bit       icmpOutDestUnreachs;
    tt32Bit       icmpOutTimeExcds;
    tt32Bit       icmpOutParmProbs;
    tt32Bit       icmpOutSrcQuenchs;
    tt32Bit       icmpOutRedirects;
    tt32Bit       icmpOutEchos;
    tt32Bit       icmpOutEchoReps;
    tt32Bit       icmpOutTimestamps;
    tt32Bit       icmpOutTimestampReps;
    tt32Bit       icmpOutAddrMasks;
    tt32Bit       icmpOutAddrMaskReps;
#ifdef U_icmp
U_icmp
#endif /* U_icmp */
    char            valid[4];
} ttIcmpMib;

typedef struct ttTcpMib
{
    ttS32Bit      tcpRtoAlgorithm;
    ttS32Bit      tcpRtoMin;
    ttS32Bit      tcpRtoMax;
    ttS32Bit      tcpMaxConn;
    tt32Bit       tcpActiveOpens;
    tt32Bit       tcpPassiveOpens;
    tt32Bit       tcpAttemptFails;
    tt32Bit       tcpEstabResets;
    tt32Bit       tcpCurrEstab;
#ifdef TM_USE_NG_MIB2
    tt64Bit       tcpHCInSegs;
    tt64Bit       tcpHCOutSegs;
#else /* TM_USE_NG_MIB2 */
    tt32Bit       tcpInSegs;
    tt32Bit       tcpOutSegs;
#endif /* !TM_USE_NG_MIB2 */
    tt32Bit       tcpRetransSegs;
    tt32Bit       tcpInErrs;
    tt32Bit       tcpOutRsts;
#ifdef U_tcp
U_tcp
#endif /* U_tcp */
    char          valid[2];
    char          tcpFiller[2];
} ttTcpMib;

typedef struct tsUdpMib
{
    tt32Bit       udpNoPorts;
    tt32Bit       udpInErrors;
#ifdef TM_USE_NG_MIB2
    tt64Bit       udpHCInDatagrams;
    tt64Bit       udpHCOutDatagrams;
#else /* TM_USE_NG_MIB2 */
    tt32Bit       udpInDatagrams;
    tt32Bit       udpOutDatagrams;
#endif /* !TM_USE_NG_MIB2 */
#ifdef U_udp
U_udp
#endif /* U_udp */
    char          valid[1];
    char          udpFiller[3];
} ttUdpMib;

#endif /* TM_SNMP_MIB */

#ifdef TM_USE_IPV4

/* ARP collision detection function call back type */
typedef void (TM_CODE_FAR *ttArpChkIn)(
#ifdef TM_USE_STRONG_ESL
                                        ttDeviceEntryPtr devPtr,
#endif /* TM_USE_STRONG_ESL */
                                        int              operation,
                                        tt4IpAddress     senderNetAddress,
                                        tt4IpAddress     targetNetAddress,
                                        tt8BitPtr        enetAddress );
/* Entry in the collision detection list */
typedef struct tsArpChkEntry
{
    struct tsArpChkEntry TM_FAR * arckNextPtr;
    struct tsArpChkEntry TM_FAR * arckPrevPtr;
    ttDeviceEntryPtr              arckDevPtr;
    ttTimerPtr                    arckTimerPtr;
    ttArpChkCBFunc                arckCbFunc;
    tt4IpAddress                  arckIpAddress;
    ttUserGenericUnion            arckCbParam;
    tt32Bit                       arckTimeout;
    int                           arckNumberProbes;
#define TM_ARCK_FLAG_ACTIVE 0x01
    tt8Bit                        arckFlags;
} ttArpChkEntry;

typedef ttArpChkEntry TM_FAR * ttArpChkEntryPtr;
#endif /* TM_USE_IPV4 */

/* IP decapsulation handler function */
typedef void (TM_CODE_FAR *ttIpHandlerFuncPtr)( ttPacketPtr packetPtr,
                                                tt8Bit      ulp );

/* support for debug, error and trace logging to circular buffer */
typedef struct tsLogMsgHdr
{
/* messages are padded so that the msg hdr starts on a 32-bit boundary */
    tt8Bit lmhBeginHdr[4];  /* "HDR" indicates start of the hdr */
    union
    {
        struct tsLogMsgHdr TM_FAR * lmhMsgPrevPtr; /* pointer to prev msg */

/* pointer to next msg, used by tfLogWalk to walk the copy of the log buffer */
        struct tsLogMsgHdr TM_FAR * lmhMsgNextPtr;
    } lmhUnion;
    tt16Bit lmhMsgSeqNo;    /* 15-bit message sequence number */
    tt16Bit lmhMsgLen;      /* length of this message, including hdr and pad */
    tt8Bit lmhMsgData[TM_LOG_MSG_HDR_PAD_LEN]; /* start of message data */
} ttLogMsgHdr;

typedef ttLogMsgHdr TM_FAR * ttLogMsgHdrPtr;
typedef struct tsLogCtrlBlk
{
#ifdef TM_LOCK_NEEDED
    ttLockEntry lcbLockEntry;   /* lock for this structure */
#endif /* TM_LOCK_NEEDED */
    ttLogMsgHdrPtr lcbLastMsgPtr; /* pointer to the last message logged */
    tt8BitPtr lcbBufPtr;        /* pointer to head of circular buffer */
    tt32Bit lcbBufLen;          /* size of circular buffer, including pad */
    tt16Bit lcbBufEndPadLen;    /* padding at end of buffer */
    tt16Bit lcbMsgSeqNo;        /* next available message sequence number */
} ttLogCtrlBlk;

typedef ttLogCtrlBlk TM_FAR * ttLogCtrlBlkPtr;
#ifdef TM_USE_LOGGING_LEVELS
typedef struct ttLogLevelStorage
{
/* One log message buffer per module */
    char                llsLogLevelMessage[(TM_LOG_MODULE_MAX + 1)]
                                [TM_LOG_MAX_MESSAGE_TEXT_LENGTH];
    tt8Bit              llsLogVerbosity;                              
    tt8Bit              llsLogLevelArray[(TM_LOG_MODULE_MAX + 1)];
#ifdef TM_LOCK_NEEDED
    ttLockEntry         llsLogModuleLock[(TM_LOG_MODULE_MAX + 1)];
#endif /* TM_LOCK_NEEDED */
} ttLogLevelStorage;
typedef ttLogLevelStorage TM_FAR * ttLogLevelStoragePtr;
#endif /* TM_USE_LOGGING_LEVELS */

/* The parameter structure for device driver ISR */
typedef struct tsDeviceIsrPara
{
    ttUserInterface deviInterfaceHandle;
#ifdef TM_MULTIPLE_CONTEXT
    ttUserContext   deviContextHandle;
#endif /* TM_MULTIPLE_CONTEXT */
} ttDeviceIsrPara;

typedef ttDeviceIsrPara TM_FAR * ttDeviceIsrParaPtr;

#ifdef TM_SNMP_CACHE

#ifdef TM_USE_IPV4
typedef struct ts4SnmpArpSearch
{
    tt32Bit             snmpa4DevIndex;
    tt4IpAddress        snmpa4Dest;
} tt4SnmpArpSearch;

typedef tt4SnmpArpSearch TM_FAR * tt4SnmpArpSearchPtr;

typedef struct ts4SnmpRteSearch
{
    tt4IpAddress        snmpr4Dest;
    tt16Bit             snmpr4BitOffset;
#ifdef TM_USE_STRONG_ESL
    tt32Bit             snmpr4Hops;
    tt32Bit             snmpr4DevIndex;
#endif /* TM_USE_STRONG_ESL */
} tt4SnmpRouteSearch;

typedef tt4SnmpRouteSearch TM_FAR * tt4SnmpRouteSearchPtr;

typedef struct ts4SnmpUdpTuple
{
    tt4IpAddress        snmpu4LocalAddress;
    ttIpPort            snmpu4LocalPort;
#ifdef TM_USE_STRONG_ESL
    tt32Bit             snmpu4DevIndex;
#endif /* TM_USE_STRONG_ESL */
} tt4SnmpUdpTuple;

typedef tt4SnmpUdpTuple TM_FAR * tt4SnmpUdpTuplePtr;

typedef struct ts4SnmpTcpTuple
{
    tt4IpAddress        snmpt4LocalAddress;
    ttIpPort            snmpt4LocalPort;
    tt4IpAddress        snmpt4RemoteAddress;
    ttIpPort            snmpt4RemotePort;
#ifdef TM_USE_STRONG_ESL
    tt32Bit             snmpt4DevIndex;
#endif /* TM_USE_STRONG_ESL */
} tt4SnmpTcpTuple;

typedef tt4SnmpTcpTuple TM_FAR * tt4SnmpTcpTuplePtr;

#endif /* TM_USE_IPV4 */

#ifdef TM_USE_IPV6
typedef struct tsSnmpArpSearch
{
    tt32Bit             snmpaDevIndex;
    ttIpAddress         snmpaDest;
} ttSnmpArpSearch;

typedef ttSnmpArpSearch TM_FAR * ttSnmpArpSearchPtr;

typedef struct tsSnmpRouteSearch
{
    ttIpAddress         snmprDest;
    tt16Bit             snmprBitOffset;
#ifdef TM_USE_STRONG_ESL
    tt32Bit             snmprHops;
    tt32Bit             snmprDevIndex;
#endif /* TM_USE_STRONG_ESL */
} ttSnmpRouteSearch;

typedef ttSnmpRouteSearch TM_FAR * ttSnmpRouteSearchPtr;

typedef struct tsSnmpUdpTuple
{
    ttIpAddress         snmpuLocalAddress;
    ttIpPort            snmpuLocalPort;
#ifdef TM_USE_STRONG_ESL
    tt32Bit             snmpuDevIndex;
#endif /* TM_USE_STRONG_ESL */
} ttSnmpUdpTuple;

typedef ttSnmpUdpTuple TM_FAR * ttSnmpUdpTuplePtr;

typedef struct tsSnmpTcpTuple
{
    ttIpAddress         snmptLocalAddress;
    ttIpPort            snmptLocalPort;
    ttIpAddress         snmptRemoteAddress;
    ttIpPort            snmptRemotePort;
#ifdef TM_USE_STRONG_ESL
    tt32Bit             snmptDevIndex;
#endif /* TM_USE_STRONG_ESL */
} ttSnmpTcpTuple;

typedef ttSnmpTcpTuple TM_FAR * ttSnmpTcpTuplePtr;

#endif /* TM_USE_IPV6 */

typedef struct tsSnmpdCacheHead
{
/* Cache list */
    ttList              snmpcList;
/* Next Node to scan in the list when inserting */
    ttNodePtr           snmpcNextNodePtr;
/* Pointer to entry last read in the cache */
    ttNodePtr           snmpcLastReadNodePtr;
#ifdef TM_LOCK_NEEDED
    ttLockEntry         snmpcLockEntry;
#endif /* TM_LOCK_NEEDED */
} ttSnmpdCacheHead;

typedef ttSnmpdCacheHead TM_FAR * ttSnmpdCacheHeadPtr;

#endif /* TM_SNMP_CACHE */

/* IPsec AH header */
typedef struct tsAhHeader
{
    tt8Bit      ahNextHeader;       /* Next Header */
    tt8Bit      ahPayloadLen;       /* Length of data + 1, in 32bit */
    tt16Bit     ahReserve;          /* Reserved for future use */
    tt32Bit     ahSpi;              /* Security parameter index */
    tt32Bit     ahSeq;              /* Sequence number field */
/* variable size, 32bit bound*/ /* Authentication data */
} ttAhHeader;
typedef ttAhHeader TM_FAR * ttAhHeaderPtr;
typedef ttAhHeaderPtr TM_FAR * ttAhHeaderPtrPtr;

typedef struct tsTime {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
} ttTime;

typedef ttTime TM_FAR * ttTimePtr;




#ifdef TM_USE_IPV6
//#include <t6type.h>
#endif /* TM_USE_IPV6 */



#ifdef TM_USE_STOP_TRECK
struct tsListCBRemove
{
    ttListPtr   lcbrListPtr;
    ttVoidPtr   lcbrContextHandle;
};

typedef struct tsListCBRemove TM_FAR * ttListCBRemovePtr;
#endif /* TM_USE_STOP_TRECK */


#ifdef __cplusplus
}
#endif

#endif /* _TRTYPE_H_ */

/* Processed by Treck Shipping Tool v2.62 
 * 2012/11/21 10:16:06      For: gainspan_2411
 * File Name: trtype.h      File Revision: 6.0.2.47 
 * Project Name: tcpip.pj   Project Release: 6.0.1.29
 * Input checksum: 58468    Output checksum: 42170
 */
