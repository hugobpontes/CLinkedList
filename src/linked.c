#include "linked.h"
#include <stdlib.h>

#define LINKED_ERROR_CODE -1

#define VALID_LIST(pList) (pList != NULL)
#define NON_EMPTY_LIST(pList) (pList->pFirst != NULL)
#define VALID_INDEX(pList,Idx) (EntryIndex >= 0 && EntryIndex < pList->EntriesNr)

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
            pLast = GetEntryPtr(pList, pList->EntriesNr-1);
            CreateLinkedEntry(&pLast->pNext,Val,pLast);
        }
        pList->EntriesNr++;
    }
}

void LinkedListInit(LinkedList_t* pList){
    if (pList!= NULL){
        pList->EntriesNr = 0;
        pList->pFirst = NULL;
    }
}

LinkedData_t LinkedListGet (LinkedList_t* pList, int EntryIndex){  
    LinkedEntry_t* pEntry;
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        ReturnData = pEntry->Data;
    }
    return ReturnData;
}

LinkedData_t* LinkedListGetPtr (LinkedList_t* pList, int EntryIndex){  
    LinkedEntry_t* pEntry;
    LinkedData_t* pData = NULL;

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pData = &(pEntry->Data);
    }
    return pData;
}

void LinkedListSet (LinkedList_t* pList, int EntryIndex, LinkedData_t Val){  
    LinkedEntry_t* pEntry;

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pEntry->Data = Val;
    }
}

LinkedData_t LinkedListPop(LinkedList_t* pList, int EntryIndex){

    LinkedEntry_t* pEntry;  
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        /*Set previous next to current next, unless first element, 
        in which case set current next to first entry*/
        pEntry = GetEntryPtr(pList, EntryIndex);
        if (EntryIndex != 0){
            pEntry->pPrevious->pNext = pEntry->pNext;
        } else {
            pList->pFirst = pEntry->pNext;
        }
        /*If not last entry, set previous of next to current previous*/
        if (EntryIndex < pList->EntriesNr-1){
            pEntry->pNext->pPrevious = pEntry->pPrevious;
        }
        ReturnData = pEntry->Data;
        pList->EntriesNr--;
        free(pEntry); 
    }    
    return ReturnData;
}

int LinkedListGetEntriesNr(LinkedList_t* pList){
    return pList->EntriesNr;
}

LinkedData_t LinkedListPopEnd(LinkedList_t* pList){
   return LinkedListPop(pList, pList->EntriesNr-1); 
}

LinkedData_t LinkedListPopStart(LinkedList_t* pList){
   return LinkedListPop(pList, 0); 
}

void LinkedListClear(LinkedList_t* pList){
    LinkedEntry_t* pCurrent;
    LinkedEntry_t* pTemp;
    int CurrentIdx = 0;
    int EntriesToClear;

    if (VALID_LIST(pList) && NON_EMPTY_LIST(pList)){
        pCurrent = pList->pFirst;  
        EntriesToClear = pList->EntriesNr;
        for (CurrentIdx = 0;CurrentIdx<EntriesToClear;CurrentIdx++)
        {     
            pTemp = pCurrent;
            pCurrent = pCurrent->pNext;
            free(pTemp);

            pList->EntriesNr--;
        }
    }
}