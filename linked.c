#include "linked.h"
#include <stdlib.h>


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

    if (EntryIndex < pList->Elements){
        for (CurrentIdx = 0;CurrentIdx<EntryIndex;CurrentIdx++)
        {
            pCurrent = pCurrent->pNext;
        }
    }

    return pCurrent;
}

void LinkedListAdd(LinkedList_t* pList, LinkedData_t Val){
    LinkedEntry_t* pLast;
    if (pList!= NULL){
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
    LinkedData_t ReturnData = 0;

    int CurrentIdx = 0; 

    if (pList != NULL && pList->pFirst != NULL){
        pEntry = GetEntryPtr(pList, EntryIndex);
        ReturnData = pEntry->Data;
    }
    return ReturnData;
}

//set
//remove (just calls pop at max index)
//pop
//clear (delete and free all elements)