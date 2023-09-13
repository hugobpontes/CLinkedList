#include "linked.h"
#include <stdlib.h>

#define LINKED_ERROR_CODE -1

#define VALID_LIST(pList) (pList != NULL)
#define NON_EMPTY_LIST(pList) (pList->pFirst != NULL)
#define VALID_INDEX(pList,Idx) (EntryIndex >= 0 && EntryIndex < pList->Elements)

static inline void CreateLinkedEntry(LinkedEntry_t** ppEntry, LinkedData_t Val, LinkedEntry_t* pPrevious){
        *ppEntry = malloc(sizeof(LinkedEntry_t));
        (*ppEntry)->Data = Val;
        (*ppEntry)->pPrevious = pPrevious;    
} 

static inline LinkedEntry_t* GetEntryPtr(LinkedList_t* pList, int EntryIndex){
        
    LinkedEntry_t* pCurrent;
    int ReturnIdx;
    int CurrentIdx = 0;

    pCurrent = pList->pFirst;  
    for (CurrentIdx = 0;CurrentIdx<EntryIndex;CurrentIdx++)
    {
        pCurrent = pCurrent->pNext;
    }

    return pCurrent;
}

void LinkedListAdd(LinkedList_t* pList, LinkedData_t Val){
    LinkedEntry_t* pLast;
    if (VALID_LIST(pList)){
        if (pList->pFirst == NULL){
            CreateLinkedEntry(&pList->pFirst,Val,NULL);
        } else {
            pLast = GetEntryPtr(pList, pList->Elements-1);
            CreateLinkedEntry(&pLast->pNext,Val,pLast);
        }
        pList->Elements++;
    }
}

void LinkedListInit(LinkedList_t* pList){
    if (pList!= NULL){
        pList->Elements = 0;
        pList->pFirst = NULL;
    }
}

LinkedData_t LinkedListGet (LinkedList_t* pList, int EntryIndex){  
    LinkedEntry_t* pEntry;
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    int CurrentIdx = 0; 

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        ReturnData = pEntry->Data;
    }
    return ReturnData;
}

LinkedData_t LinkedListPop(LinkedList_t* pList, int EntryIndex){

    LinkedEntry_t* pEntry;  
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        if (EntryIndex != 0){
            pEntry->pPrevious->pNext = pEntry->pNext;
        } else {
            pList->pFirst = pEntry->pNext;
        }
        if (EntryIndex < pList->Elements-1){
            pEntry->pNext->pPrevious = pEntry->pPrevious;
        }
        ReturnData = pEntry->Data;
        pList->Elements--;
        free(pEntry); 
    }    
    return ReturnData;
}

int LinkListGetElements(LinkedList_t* pList){
    return pList->Elements;
}

LinkedData_t LinkedListPopEnd(LinkedList_t* pList){
   return LinkedListPop(pList, pList->Elements-1); 
}

LinkedData_t LinkedListPopStart(LinkedList_t* pList){
   return LinkedListPop(pList, 0); 
}

//set
//remove (just calls pop at max index)
//clear (delete and free all elements)