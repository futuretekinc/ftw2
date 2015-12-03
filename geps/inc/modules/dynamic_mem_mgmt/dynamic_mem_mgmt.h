#ifndef _DYNAMIC_MEM_MGMT_H_
#define _DYNAMIC_MEM_MGMT_H_

#define GSN_MODULE_ID_GSN   0
#define GSN_MODULE_ID_SUPP  1
#define GSN_MODULE_ID_XML   2
#define GSN_MODULE_ID_SYS   3


typedef struct GSN_BYTE_POOL_LINK
{
	struct GSN_BYTE_POOL_LINK *pNext;
	TX_BYTE_POOL  bPool;
}GSN_BYTE_POOL_LINK_T;

extern GSN_BYTE_POOL_LINK_T *pGsnBytePoolHead;

VOID* GsnDynMemMgmt_Alloc( UINT32 size, UINT32 line, UINT32 moduleId );

VOID* GsnDynMemMgmt_Realloc( VOID* ptr, UINT32 size, UINT32 line, UINT32 moduleId );

VOID GsnDynMemMgmt_Free( VOID *ptr );

#define gsn_malloc( size ) GsnDynMemMgmt_Alloc((size), __LINE__, GSN_MODULE_ID_GSN )
#define gsn_realloc( ptr, size ) GsnDynMemMgmt_Realloc( (ptr), (size), __LINE__, GSN_MODULE_ID_GSN )
#define gsn_free( ptr ) GsnDynMemMgmt_Free( (ptr) )

VOID* MALLOC( UINT32 size );

VOID FREE( VOID *ptr );

VOID* REALLOC( VOID *ptr, UINT32 size );


#endif /* _DYNAMIC_MEM_MGMT_H_ */
