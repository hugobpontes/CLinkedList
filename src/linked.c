#include "linked.h"
#include <stdlib.h>

#define VALID_PTR(p) (p != NULL)
#define NON_EMPTY_LIST(pList) (pList->pFirst != NULL)
#define ENTRY_EXISTS(pList,Idx) (EntryIndex >= 0 && EntryIndex < pList->EntriesNr)
#define ENTRY_IS_NEW_AT_END(pList,Idx) (EntryIndex == pList->EntriesNr)

#define ENTRY_IS_AT_START(pEntry) (pEntry->pPrevious == NULL)
/* 
* @brief Creates new linked list entry with input data and empty pointers
* @param ppEntry Pointer to pointer that will point to new entry
* @param pVal Pointer to the data to be assigned to new entry
*/
static inline void CreateLinkedEntry(LinkedEntry_t** ppEntry, LinkedData_t* pVal){
        *ppEntry = malloc(sizeof(LinkedEntry_t));
        (*ppEntry)->Data = *pVal;
        (*ppEntry)->pNext=NULL;
        (*ppEntry)->pPrevious=NULL;
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
* @details Given a specific E, its previous entry P and
* its next entry N: 
    * makes P's "next" pointer point to N instead of E
    * makes N's "previous" pointer point to P instead of E
* some caveats regarding start and end entries apply
* @param pList Pointer to linked list
* @param EntryIndex Index of the entry to be bypassed
* @return Pointer to the bypassed entry
*/
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
/* 
* @brief Manages list entries' pointers so a new entry is inserted before a 
* specific place in the list (inserts at the end if last index +1 is
* used in EntryIndex)
* @param pList Pointer to linked list
* @param pNewEntry Pointer to new entry
* @param EntryIndex Index of the entry before which the
* new one is inserted
*/
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
        //insert at start if list is empty
        pList->pFirst = pNewEntry;        
    } else if (EntryIndex == pList->EntriesNr){  
        //insert at the end if input index is max + 1
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
/* 
* @brief Deletes and frees all entries in a list
* @param pList Pointer to the linked list to be cleared
*/
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
        /*Nothing for list first to point to*/
        pList->pFirst = NULL;
    }
}
/*
* @brief Returns number of entries in the linked list
* @param pList Pointer to the linked list
* @return Number of entries in the linked list
*/
int LinkedListGetEntriesNr(LinkedList_t* pList){
    return pList->EntriesNr;
}
/* 
* @brief Inserts a new entry with new data before a specific place in the list
* (inserts at the end if last index +1 is used in EntryIndex)
* @param pList Pointer to linked list
* @param pData Pointer to data to be added to new inserted entry
* @param EntryIndex Index of the entry before which the new item is inserted
*/
void LinkedListInsert(LinkedList_t* pList, LinkedData_t* pData,int EntryIndex){
    LinkedEntry_t* pNewEntry;
    /*To insert at the end of the list, last existing index + 1 is used so it is a valid input*/
    if (VALID_PTR(pList) && VALID_PTR(pData) && (ENTRY_EXISTS(pList,EntryIndex) || ENTRY_IS_NEW_AT_END(pList,EntryIndex))){
        CreateLinkedEntry(&pNewEntry,pData);
        LinkedListInsertEntry(pList,pNewEntry,EntryIndex);
    }
}    
/* 
* @brief Inserts a new entry with new data at the start of the linked list
* @param pList Pointer to linked list
* @param pData Pointer to data to be added to new inserted entry
*/
void LinkedListInsertStart(LinkedList_t* pList, LinkedData_t* pData){
    LinkedListInsert(pList, pData,0);    
}
/* 
* @brief Inserts a new entry with new data at the end of the linked list
* @param pList Pointer to linked list
* @param pData Pointer to data to be added to new inserted entry
*/
void LinkedListInsertEnd(LinkedList_t* pList, LinkedData_t* pData){
    LinkedListInsert(pList, pData,pList->EntriesNr);    
}
/* 
* @brief Reads new data from linked list entry to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
* @param EntryIndex Index of the list entry to get data from
*/
void LinkedListGet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex){  
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && VALID_PTR(pData) && NON_EMPTY_LIST(pList) && ENTRY_EXISTS(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        *pData = pEntry->Data;
    }
}
/* 
* @brief Writes new data to linked list entry from provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied from
* @param EntryIndex Index of the list entry to set data in
*/
void LinkedListSet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex){  
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && VALID_PTR(pData) && NON_EMPTY_LIST(pList) && ENTRY_EXISTS(pList,EntryIndex)){
        pEntry = GetEntryPtr(pList, EntryIndex);
        pEntry->Data = *pData;
    }
}
/* 
* @brief Removes entry from list and writes its contents to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
* @param EntryIndex Index of the entry to pop
*/
void LinkedListPop(LinkedList_t* pList, LinkedData_t* pData, int EntryIndex){
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_PTR(pData) && ENTRY_EXISTS(pList,EntryIndex)){
        pEntry = LinkedListBypassEntry(pList,EntryIndex);
        *pData = pEntry->Data;
        free(pEntry); 
        pList->EntriesNr--;
    }    
}
/* 
* @brief Removes entry from start of list and writes its contents to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
*/
void LinkedListPopStart(LinkedList_t* pList, LinkedData_t* pData){
   LinkedListPop(pList,pData,0); 
}
/* 
* @brief Removes entry from end of list and writes its contents to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
*/
void LinkedListPopEnd(LinkedList_t* pList, LinkedData_t* pData){
   LinkedListPop(pList,pData,pList->EntriesNr-1); 
}
/* 
* @brief Removes entry from list
* @param pList Pointer to linked list
* @param EntryIndex Index of the entry to remove
*/
void LinkedListRemove(LinkedList_t* pList, int EntryIndex){
    LinkedEntry_t* pEntry;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && ENTRY_EXISTS(pList,EntryIndex)){
        pEntry = LinkedListBypassEntry(pList,EntryIndex);
        free(pEntry); 
        pList->EntriesNr--;
    }    
}
/* 
* @brief Removes entry from start of list
* @param pList Pointer to linked list
*/
void LinkedListRemoveStart(LinkedList_t* pList){
   LinkedListRemove(pList,0); 
}
/* 
* @brief Removes entry from end of list
* @param pList Pointer to linked list
*/
void LinkedListRemoveEnd(LinkedList_t* pList){
   LinkedListRemove(pList,pList->EntriesNr-1); 
}