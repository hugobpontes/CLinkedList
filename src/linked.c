#include "linked.h"
#include <stdlib.h>

#define LINKED_ERROR_CODE -1

#define VALID_PTR(p) (p != NULL)
#define NON_EMPTY_LIST(pList) (pList->pFirst != NULL)
#define VALID_INDEX(pList,Idx) (EntryIndex >= 0 && EntryIndex < pList->EntriesNr)
/* 
* @brief Creates new linked list entry and makes provides pointer point to it
* @param ppEntry Pointer to pointer to new entry
* @param pVal Pointer to the data to be assigned to new entry
* @param pPrevious Pointer to previous entry of new entry
*/
static inline void CreateLinkedEntry(LinkedEntry_t** ppEntry, LinkedData_t* pVal, LinkedEntry_t* pPrevious){
        *ppEntry = malloc(sizeof(LinkedEntry_t));
        (*ppEntry)->Data = *pVal;
        (*ppEntry)->pPrevious = pPrevious;    
} 
/* 
* @brief Returns pointer to specified linked list entry 
* @param pList pointer to linked list
* @param EntryIndex Index of the entry whose pointer is returned
*/
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
/* 
* @brief Bypasses a specific element in the linked list
* @details Given a specific entry, makes previous entry's
* "next" pointer point to the next entry and makes next 
* entry's previous pointer point to the previous entry.
* @param pList Pointer to linked list
* @param pEntry Pointer to the entry to be bypassed
* @param EntryIndex Index of the entry to be bypassed
*/
static inline void LinkedListBypassEntry(LinkedList_t* pList,LinkedEntry_t* pEntry,int EntryIndex){
    /*Set previous next to current next, unless first element in list, 
    in which case first entry to current next*/
    if (EntryIndex != 0){
        pEntry->pPrevious->pNext = pEntry->pNext;
    } else {
        pList->pFirst = pEntry->pNext;
    }
    /*If not last entry, set previous of next to current previous*/
    if (EntryIndex < pList->EntriesNr-1){
        pEntry->pNext->pPrevious = pEntry->pPrevious;
    }
    pList->EntriesNr--;
}
/* 
* @brief Adds a new entry at the end of the linked list
* @param pList Pointer to the linked list to add entry to
* @param Val Data to be stored in the new entry
*/
void LinkedListAdd(LinkedList_t* pList, LinkedData_t Val){
    LinkedEntry_t* pLast;
    if (VALID_PTR(pList)){
        if (pList->pFirst == NULL){
            CreateLinkedEntry(&pList->pFirst,&Val,NULL);
        } else {
            pLast = GetEntryPtr(pList, pList->EntriesNr-1);
            CreateLinkedEntry(&pLast->pNext,&Val,pLast);
        }
        pList->EntriesNr++;
    }
}
/* 
* @brief Adds a new entry at the end of the linked list via pointer
* @param pList Pointer to the linked list to add entry to
* @param pVal Pointer to Data to be stored in the new entry
*/
void LinkedListPtrAdd(LinkedList_t* pList, LinkedData_t* pVal){
    LinkedEntry_t* pLast;
    if (VALID_PTR(pList) && VALID_PTR(pVal)){
        if (pList->pFirst == NULL){
            CreateLinkedEntry(&pList->pFirst,pVal,NULL);
        } else {
            pLast = GetEntryPtr(pList, pList->EntriesNr-1);
            CreateLinkedEntry(&pLast->pNext,pVal,pLast);
        }
        pList->EntriesNr++;
    }
}
/* 
* @brief Initializes linked list
* @param pList Pointer to the linked list to be initialized
*/
void LinkedListInit(LinkedList_t* pList){
    if (pList!= NULL){
        pList->EntriesNr = 0;
        pList->pFirst = NULL;
    }
}
/* 
* @brief Returns data in the selected linked list entry
* @param pList Pointer to the linked list to be initialized
* @param EntryIndex index of the entry where data is returned from
* @return Data in the selected entry
*/
LinkedData_t LinkedListGet (LinkedList_t* pList, int EntryIndex){  
    LinkedEntry_t* pEntry;
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        ReturnData = pEntry->Data;
    }
    return ReturnData;
}
/* 
* @brief Returns pointer to data in the selected linked list entry
* @param pList Pointer to the linked list to be initialized
* @param EntryIndex index of the entry where data is returned from
* @return Pointer to data in the selected entry
*/
LinkedData_t* LinkedListGetPtr (LinkedList_t* pList, int EntryIndex){  
    LinkedEntry_t* pEntry;
    LinkedData_t* pData = NULL;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pData = &(pEntry->Data);
    }
    return pData;
}

void LinkedListSet (LinkedList_t* pList, int EntryIndex, LinkedData_t Val){  
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pEntry->Data = Val;
    }
}

void LinkedListPtrSet(LinkedList_t* pList, int EntryIndex, LinkedData_t* pVal){  
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex) && VALID_PTR(pVal)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pEntry->Data = *pVal;
    }
}

LinkedData_t LinkedListPop(LinkedList_t* pList, int EntryIndex){

    LinkedEntry_t* pEntry;  
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        LinkedListBypassEntry(pList,pEntry,EntryIndex);
        ReturnData = pEntry->Data;
        free(pEntry); 
    }    
    return ReturnData;
}

void LinkedListPopNoReturn(LinkedList_t* pList, int EntryIndex){

    LinkedEntry_t* pEntry;  
    LinkedData_t ReturnData = LINKED_ERROR_CODE;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_INDEX(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        LinkedListBypassEntry(pList,pEntry,EntryIndex);
        free(pEntry); 
    }
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

void LinkedListPopEndNoReturn(LinkedList_t* pList){
   LinkedListPopNoReturn(pList, pList->EntriesNr-1); 
}

void LinkedListPopStartNoReturn(LinkedList_t* pList){
   LinkedListPop(pList, 0); 
}


void LinkedListClear(LinkedList_t* pList){
    LinkedEntry_t* pCurrent;
    LinkedEntry_t* pTemp;
    int CurrentIdx = 0;
    int EntriesToClear;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList)){
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