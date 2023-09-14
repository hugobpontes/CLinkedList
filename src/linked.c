#include "linked.h"
#include <stdlib.h>

#define LINKED_ERROR_CODE -1

#define VALID_PTR(p) (p != NULL)
#define NON_EMPTY_LIST(pList) (pList->pFirst != NULL)
#define ENTRY_IDX_EXISTS(pList,Idx) (EntryIndex >= 0 && EntryIndex < pList->EntriesNr)
#define ENTRY_IDX_IS_MAX(pList,Idx) (EntryIndex == pList->EntriesNr)

#define ENTRY_IS_AT_START(pEntry) (pEntry->pPrevious == NULL)

static inline void CreateLinkedEntry(LinkedEntry_t** ppEntry, LinkedData_t* pVal){
        *ppEntry = malloc(sizeof(LinkedEntry_t));
        (*ppEntry)->Data = *pVal;
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

static inline LinkedEntry_t* LinkedListBypassEntry(LinkedList_t* pList,int EntryIndex){
    LinkedEntry_t* pEntry;

    pEntry =  GetEntryPtr(pList,EntryIndex);
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

    return pEntry;
}

static inline void LinkedListInsertEntry(LinkedList_t* pList,LinkedEntry_t* pNewEntry,int EntryIndex){
   
    /*(insertion is before old entry)*/
    /*Example: Middle Insertion into position 1: 
    |A|B|C|  -> |A|I|B|C|
    |0|1|2|  -> |0|1|2|3|*/
    /*Example: Start Insertion into position 0: 
    |A|B|C|  -> |I|A|B|C|
    |0|1|2|  -> |0|1|2|3|*/  
    /*Example: End Insertion into position 3: 
    |A|B|C|  -> |A|B|C|I|
    |0|1|2|  -> |0|1|2|3|*/    
   
    LinkedEntry_t* pPrevious;
    LinkedEntry_t* pNext;
    LinkedEntry_t* pLastEntry;

    if (!NON_EMPTY_LIST(pList)){
        pList->pFirst = pNewEntry;        
    } else if (EntryIndex == pList->EntriesNr){  
        pLastEntry = GetEntryPtr(pList,EntryIndex-1);
        pLastEntry->pNext = pNewEntry;
        pNewEntry->pPrevious = pLastEntry;
    } else {
        pNext = GetEntryPtr(pList,EntryIndex);

        if (ENTRY_IS_AT_START(pNext)) { 
            /*Inserting at start*/
            pList->pFirst = pNewEntry;
            pNewEntry->pNext = pNext;
            pNewEntry->pNext->pPrevious = pNewEntry; 
        } else {
            /*Inserting in middle*/
            pNewEntry->pNext = pNext;
            pNewEntry->pPrevious = pNext->pPrevious;
            pNewEntry->pPrevious->pNext = pNewEntry;
            pNewEntry->pNext->pPrevious = pNewEntry;
        }        
    }

    pList->EntriesNr++;
}
/* 
* @brief Initializes linked list
* @param pList Pointer to the linked list to be initialized
*/
void LinkedListInit(LinkedList_t* pList){
    if (VALID_PTR(pList)){
        pList->EntriesNr = 0;
        pList->pFirst = NULL;
    }
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
int LinkedListGetEntriesNr(LinkedList_t* pList){
    return pList->EntriesNr;
}

void LinkedListInsert(LinkedList_t* pList, LinkedData_t* pData,int EntryIndex){
    LinkedEntry_t* pNewEntry;
    if (VALID_PTR(pList) && VALID_PTR(pData) && (ENTRY_IDX_EXISTS(pList,EntryIndex) || ENTRY_IDX_IS_MAX(pList,EntryIndex))){
        CreateLinkedEntry(&pNewEntry,pData);
        LinkedListInsertEntry(pList,pNewEntry,EntryIndex);
    }
}    

void LinkedListInsertStart(LinkedList_t* pList, LinkedData_t* pData){
    LinkedListInsert(pList, pData,0);    
}

void LinkedListInsertEnd(LinkedList_t* pList, LinkedData_t* pData){
    LinkedListInsert(pList, pData,pList->EntriesNr);    
}

void LinkedListGet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex){  
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && VALID_PTR(pData) && NON_EMPTY_LIST(pList) && ENTRY_IDX_EXISTS(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        *pData = pEntry->Data;
    }
}

void LinkedListSet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex){  
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && VALID_PTR(pData) && NON_EMPTY_LIST(pList) && ENTRY_IDX_EXISTS(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pEntry->Data = *pData;
    }
}

void LinkedListPop(LinkedList_t* pList, LinkedData_t* pData, int EntryIndex){
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_PTR(pData) && ENTRY_IDX_EXISTS(pList,EntryIndex)){
        pEntry = LinkedListBypassEntry(pList,EntryIndex);
        *pData = pEntry->Data;
        free(pEntry); 
        pList->EntriesNr--;
    }    
}

void LinkedListPopStart(LinkedList_t* pList, LinkedData_t* pData){
   LinkedListPop(pList,pData,0); 
}
void LinkedListPopEnd(LinkedList_t* pList, LinkedData_t* pData){
   LinkedListPop(pList,pData,pList->EntriesNr-1); 
}

void LinkedListRemove(LinkedList_t* pList, int EntryIndex){
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && ENTRY_IDX_EXISTS(pList,EntryIndex)){
        pEntry = LinkedListBypassEntry(pList,EntryIndex);
        free(pEntry); 
        pList->EntriesNr--;
    }    
}

void LinkedListRemoveStart(LinkedList_t* pList){
   LinkedListRemove(pList,0); 
}

void LinkedListRemoveEnd(LinkedList_t* pList){
   LinkedListRemove(pList,pList->EntriesNr-1); 
}