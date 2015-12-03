#ifndef __FTW_LIST_H__
#define __FTW_LIST_H__

typedef struct  _FTW_LIST_NODE_STRUCT 
{
    struct  _FTW_LIST_NODE_STRUCT * pPrev;
    struct  _FTW_LIST_NODE_STRUCT * pNext;
    void *  pItem;
    UINT32  nReserved;
}   FTW_LIST_NODE_T;

typedef struct _FTW_LIST_STRUCT
{
    UINT32              nCount;
    FTW_LIST_NODE_T *   pHead;
    GSN_OSAL_SEM_T      xLock;
}   FTW_LIST_T;

typedef FTW_LIST_T  FTW_LIST;

GSN_STATUS_T   FTW_LIST_init(FTW_LIST_T * pList);
GSN_STATUS_T   FTW_LIST_final(FTW_LIST_T * pList);

GSN_STATUS_T   FTW_LIST_isInitialized(FTW_LIST_T * pList);
GSN_STATUS_T   FTW_LIST_isExist(FTW_LIST_T * pList, void * pItem);

UINT32          FTW_LIST_count(FTW_LIST_T * pList);

GSN_STATUS_T   FTW_LIST_pushFront(FTW_LIST_T * pList, void * pItem);
GSN_STATUS_T   FTW_LIST_pushBack(FTW_LIST_T * pList, void * pItem);
GSN_STATUS_T   FTW_LIST_pushSort(FTW_LIST_T * pList, void * pItem, int (*comparator)(void * a, void * b));
GSN_STATUS_T   FTW_LIST_popFront(FTW_LIST_T * pList, void ** ppItem);
GSN_STATUS_T   FTW_LIST_popBack(FTW_LIST_T * pList, void ** ppItem);
GSN_STATUS_T   FTW_LIST_remove(FTW_LIST_T * pList, void * pItem);

void *  FTW_LIST_getAt(FTW_LIST_T * pList, UINT32 ulIndex);

#endif
