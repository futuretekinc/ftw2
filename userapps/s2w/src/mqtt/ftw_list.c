#include "ftw_includes.h"

GSN_STATUS_T    FTW_LIST_init(FTW_LIST_T *  pList)
{
    GSN_ASSERT(pList != NULL);
    GSN_STATUS_T    xStatus;
    
    FTW_LIST_NODE_T *   pNode = (FTW_LIST_NODE_T *)gsn_malloc(sizeof(FTW_LIST_NODE_T));
    if (pNode == NULL)
    {
        return  GSN_FAILURE;
    }

    pNode->pNext = pNode;
    pNode->pPrev = pNode;
    pList->pHead  = pNode;
    pList->nCount = 0;

    xStatus = GsnOsal_SemCreate(&pList->xLock, 1);
    if (xStatus != GSN_SUCCESS)
    {
        gsn_free(pNode);
        pList->pHead = NULL;
        return  xStatus;
    }
    
    return  GSN_SUCCESS;
}

GSN_STATUS_T    FTW_LIST_final(FTW_LIST_T *  pList)
{
    FTW_LIST_NODE_T * pNode;
    FTW_LIST_NODE_T * pNextNode ;
    
    GSN_ASSERT(pList != NULL);
    pNode = pList->pHead;
    while(pNode != pList->pHead)
    {
        pNextNode = pNode->pNext;
        gsn_free(pNode);
        pNode = pNextNode;
    }

    GsnOsal_SemDelete(&pList->xLock);
    gsn_free(pList->pHead);
    pList->pHead = NULL;
    pList->nCount= 0;
    
    return  GSN_SUCCESS;
}

GSN_STATUS_T FTW_LIST_isInitialized(FTW_LIST_T *  pList)
{
    if ((pList == NULL) || (pList->pHead == NULL))
    {
        return  GSN_FAILURE;
    }
    
    return  GSN_SUCCESS;
}

GSN_STATUS_T     FTW_LIST_isExist(FTW_LIST_T *  pList, void * pItem)
{
    FTW_LIST_NODE_T *    pNode = pList->pHead;
    if (pNode != NULL)
    {
        pNode = pNode->pNext;
        
        while(pNode != pList->pHead)
        {
            if (pNode->pItem == pItem)
            {
                return  GSN_SUCCESS;
            }
            
            pNode = pNode->pNext;
        }
    }
    
    return  GSN_FAILURE;
}

UINT32     FTW_LIST_count(FTW_LIST_T *  pList)
{
    GSN_ASSERT(pList != NULL);
    
    return  pList->nCount;
}

GSN_STATUS_T    FTW_LIST_pushFront(FTW_LIST_T *  pList, void * pItem)
{
    FTW_LIST_NODE_T *   pNode;
    GSN_ASSERT((pList != NULL) && (pItem != NULL));

    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
    
    pNode = (FTW_LIST_NODE_T *)gsn_malloc(sizeof(FTW_LIST_NODE_T));
    if (pNode == NULL)
    {
        FTW_PRINT_ERROR("Not enough memory!\n");
        return  GSN_FAILURE;
    }

    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);
    
    pNode->pItem = pItem;
    
    pNode->pPrev = pList->pHead;
    pNode->pNext = pList->pHead->pNext;
        
    pList->pHead->pNext->pPrev = pNode;
    pList->pHead->pNext = pNode;     
    pList->nCount++;
    
    GsnOsal_SemRelease(&pList->xLock);
    
    return  GSN_SUCCESS;
}

GSN_STATUS_T    FTW_LIST_pushBack(FTW_LIST_T *  pList, void * pItem)
{
    FTW_LIST_NODE_T *   pNode;

    GSN_ASSERT((pList != NULL) && (pItem != NULL));
    
    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
    
    pNode = (FTW_LIST_NODE_T *)gsn_malloc(sizeof(FTW_LIST_NODE_T));
    if (pNode == NULL)
    {
        FTW_PRINT_ERROR("Not enough memory!\n");
        return  GSN_FAILURE;
    }

    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);

    pNode->pItem = pItem;
    
    pNode->pPrev = pList->pHead->pPrev;
    pNode->pNext = pList->pHead;
        
    pList->pHead->pPrev->pNext = pNode;
    pList->pHead->pPrev = pNode;    
    pList->nCount++;
    
    GsnOsal_SemRelease(&pList->xLock);
  
    return  GSN_SUCCESS;
}

GSN_STATUS_T    FTW_LIST_pushSort(FTW_LIST_T *  pList, void * pItem, int (*comparator)(void * a, void * b))
{
    FTW_LIST_NODE_T *   pNode;
    FTW_LIST_NODE_T *   pNextNode;

    GSN_ASSERT((pList != NULL) && (pItem != NULL));
    
    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
    
    pNode = (FTW_LIST_NODE_T *)gsn_malloc(sizeof(FTW_LIST_NODE_T));
    if (pNode == NULL)
    {
        FTW_PRINT_ERROR("Not enough memory!\n");
        return  GSN_FAILURE;
    }

    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);

    pNode->pItem = pItem;
    
    pNextNode = pList->pHead->pNext;
    while(pNextNode != pList->pHead)
    {
        if (comparator(pItem, pNextNode->pItem) < 0)
        {
            break;
        }
        pNextNode = pNextNode->pNext;
    }
    
    pNode->pPrev = pNextNode->pPrev;
    pNode->pNext = pNextNode;
        
    pNextNode->pPrev->pNext = pNode;
    pNextNode->pPrev = pNode;    
    
    pList->nCount++;
    
    GsnOsal_SemRelease(&pList->xLock);
   
    return  GSN_SUCCESS;
}

GSN_STATUS_T    FTW_LIST_popFront(FTW_LIST_T *  pList, void ** ppItem)
{
    GSN_ASSERT(pList != NULL);
    
    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
    
    if (pList->nCount == 0)
    {
        return  GSN_FAILURE;
    }

    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);
    
    FTW_LIST_NODE_T *   pNode = pList->pHead->pNext;
    
    pNode->pPrev->pNext = pNode->pNext;
    pNode->pNext->pPrev = pNode->pPrev;
    pList->nCount--;
   
    if (ppItem != NULL)
    {
        *ppItem = pNode->pItem;
    }
    
    GsnOsal_SemRelease(&pList->xLock);
    
    gsn_free(pNode);

    return  GSN_SUCCESS;
}

GSN_STATUS_T    FTW_LIST_popBack(FTW_LIST_T *  pList, void ** ppItem)
{
    GSN_ASSERT(pList != NULL);
    
    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
    
    if (pList->nCount == 0)
    {
        return  GSN_FAILURE;
    }
    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);

    FTW_LIST_NODE_T *   pNode = pList->pHead->pPrev;
    
    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);
    pList->pHead->pPrev = pNode->pPrev;
    pNode->pPrev->pNext = pNode->pNext;
    pList->nCount--;

    GsnOsal_SemRelease(&pList->xLock);
    
    if (ppItem != NULL)
    {
        *ppItem = pNode->pItem;
    }

    gsn_free(pNode);
    
    return  GSN_SUCCESS;
}

void * FTW_LIST_getAt(FTW_LIST_T *  pList, UINT32 ulIndex)
{
    GSN_ASSERT(pList != NULL);
    
    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
    
    if (pList->nCount <= ulIndex)
    {
        return  NULL;
    }
    
    FTW_LIST_NODE_T *    pNode = pList->pHead->pNext;
    while((pNode != pList->pHead) && (ulIndex > 0))
    {
        pNode = pNode->pNext;
        ulIndex--;
    }
    
    if (ulIndex != 0)
    {
        return  NULL;
    }
    
    return  pNode->pItem;
}


GSN_STATUS_T    FTW_LIST_remove(FTW_LIST_T *  pList, void * pItem)
{
    FTW_LIST_NODE_T *   pNode;

    GSN_ASSERT((pList != NULL) && (pItem != NULL));
    
    if (FTW_LIST_isInitialized(pList) != GSN_SUCCESS)
    {
        FTW_LIST_init(pList);
    }
        
    GsnOsal_SemAcquire(&pList->xLock, TX_WAIT_FOREVER);
    
    pNode = pList->pHead->pNext;
    
    while(pNode != pList->pHead)
    {
        if (pNode->pItem == pItem)
        {
            pNode->pPrev->pNext = pNode->pNext;
            pNode->pNext->pPrev = pNode->pPrev;            
            pList->nCount--;
             
            GsnOsal_SemRelease(&pList->xLock);
            
            gsn_free(pNode);
            
            return  GSN_SUCCESS;
        }
        
        pNode = pNode->pNext;
    }
    
    GsnOsal_SemRelease(&pList->xLock);
    
    return  GSN_FAILURE;
}

