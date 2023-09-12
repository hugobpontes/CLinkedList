#include "linked.h"
#include <stdlib.h>


static inline void CreateLinkedEntry(LinkedEntry_t** ppEntry, LinkedData_t Val, LinkedEntry_t* pPrevious){
        *ppEntry = malloc(sizeof(LinkedEntry_t));
        (*ppEntry)->Data = Val;
        (*ppEntry)->pPrevious = pPrevious;    
} 

void LinkedListAdd(LinkedList_t* pList, LinkedData_t Val){
    LinkedEntry_t* pCurrent;

    if (pList->pFirst == NULL){
        CreateLinkedEntry(&pList->pFirst,Val,NULL);
    } else {
        pCurrent = pList->pFirst;  
        
        while (pCurrent->pNext != NULL){
            pCurrent = pCurrent->pNext;
        }
        CreateLinkedEntry(&pCurrent->pNext,Val,pCurrent);
    }
    pList->Elements++;
}

void LinkedListInit(LinkedList_t* pList){
    pList->Elements = 0;
    pList->pFirst = NULL;
}

LinkedData_t LinkedListGet (LinkedList_t* pList, int Index){  
    LinkedEntry_t* pCurrent;
    LinkedData_t ReturnData = 0;
    int CurrentIdx = 0; 

    if (pList->pFirst != NULL){
        pCurrent = pList->pFirst;  

        if (Index < pList->Elements){
            for (CurrentIdx = 0;CurrentIdx<Index;CurrentIdx++)
            {
                pCurrent = pCurrent->pNext;
            }
            ReturnData = pCurrent->Data;
        }
    }
    return ReturnData;
}

//set
//remove (just calls pop at max index)
//pop
//clear (delete and free all elements)