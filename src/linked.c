#include "linked.h"
#include <stdlib.h>

#define VALID_PTR(p) (p != NULL)
#define NON_EMPTY_LIST(pList) (pList->pFirst != NULL)
#define NODE_EXISTS(pList,Idx) (NodeIndex >= 0 && NodeIndex < pList->NodesNr)
#define NODE_IS_NEW_AT_END(pList,Idx) (NodeIndex == pList->NodesNr)

#define NODE_IS_AT_START(pNode) (pNode->pPrevious == NULL)
/* 
* @brief Creates new linked list node with input data and empty pointers
* @param ppNode Pointer to pointer that will point to new node
* @param pVal Pointer to the data to be assigned to new node
*/
static inline void CreateLinkedNode(LinkedNode_t** ppNode, LinkedData_t* pVal){
        *ppNode = malloc(sizeof(LinkedNode_t));
        (*ppNode)->Data = *pVal;
        (*ppNode)->pNext=NULL;
        (*ppNode)->pPrevious=NULL;
} 
/* 
* @brief Returns pointer to specified linked list node 
* @param pList pointer to linked list
* @param NodeIndex Index of the node whose pointer is returned
*/
static inline LinkedNode_t* GetNodePtr(LinkedList_t* pList, int NodeIndex){
        
    LinkedNode_t* pCurrent;
    int ReturnIdx;
    int CurrentIdx = 0;

    pCurrent = pList->pFirst;  
    for (CurrentIdx = 0;CurrentIdx<NodeIndex;CurrentIdx++)
    {
        pCurrent = pCurrent->pNext;
    }

    return pCurrent;
}
/* 
* @brief Bypasses a specific element in the linked list
* @details Given a specific E, its previous node P and
* its next node N: 
    * makes P's "next" pointer point to N instead of E
    * makes N's "previous" pointer point to P instead of E
* some caveats regarding start and end nodes apply
* @param pList Pointer to linked list
* @param NodeIndex Index of the node to be bypassed
* @return Pointer to the bypassed node
*/
static inline LinkedNode_t* LinkedListBypassNode(LinkedList_t* pList,int NodeIndex){
    LinkedNode_t* pNode;

    pNode =  GetNodePtr(pList,NodeIndex);
    /*Set previous next to current next, unless first element in list, 
    in which case first node to current next*/
    if (NodeIndex != 0){
        pNode->pPrevious->pNext = pNode->pNext;
    } else {
        pList->pFirst = pNode->pNext;
    }
    /*If not last node, set previous of next to current previous*/
    if (NodeIndex < pList->NodesNr-1){
        pNode->pNext->pPrevious = pNode->pPrevious;
    }

    return pNode;
}
/* 
* @brief Manages list nodes' pointers so a new node is inserted before a 
* specific place in the list (inserts at the end if last index +1 is
* used in NodeIndex)
* @param pList Pointer to linked list
* @param pNewNode Pointer to new node
* @param NodeIndex Index of the node before which the
* new one is inserted
*/
static inline void LinkedListInsertNode(LinkedList_t* pList,LinkedNode_t* pNewNode,int NodeIndex){
   
    /*(insertion is before old node)*/
    /*Example: Middle Insertion into position 1: 
    |A|B|C|  -> |A|I|B|C|
    |0|1|2|  -> |0|1|2|3|*/
    /*Example: Start Insertion into position 0: 
    |A|B|C|  -> |I|A|B|C|
    |0|1|2|  -> |0|1|2|3|*/  
    /*Example: End Insertion into position 3: 
    |A|B|C|  -> |A|B|C|I|
    |0|1|2|  -> |0|1|2|3|*/    
   
    LinkedNode_t* pPrevious;
    LinkedNode_t* pNext;
    LinkedNode_t* pLastNode;

    if (!NON_EMPTY_LIST(pList)){
        //insert at start if list is empty
        pList->pFirst = pNewNode;        
    } else if (NodeIndex == pList->NodesNr){  
        //insert at the end if input index is max + 1
        pLastNode = GetNodePtr(pList,NodeIndex-1);
        pLastNode->pNext = pNewNode;
        pNewNode->pPrevious = pLastNode;
    } else {
        pNext = GetNodePtr(pList,NodeIndex);

        if (NODE_IS_AT_START(pNext)) { 
            /*Inserting at start*/
            pList->pFirst = pNewNode;
            pNewNode->pNext = pNext;
            pNewNode->pNext->pPrevious = pNewNode; 
        } else {
            /*Inserting in middle*/
            pNewNode->pNext = pNext;
            pNewNode->pPrevious = pNext->pPrevious;
            pNewNode->pPrevious->pNext = pNewNode;
            pNewNode->pNext->pPrevious = pNewNode;
        }        
    }

    pList->NodesNr++;
}
/* 
* @brief Initializes linked list
* @param pList Pointer to the linked list to be initialized
*/
void LinkedListInit(LinkedList_t* pList){
    if (VALID_PTR(pList)){
        pList->NodesNr = 0;
        pList->pFirst = NULL;
    }
}
/* 
* @brief Deletes and frees all nodes in a list
* @param pList Pointer to the linked list to be cleared
*/
void LinkedListClear(LinkedList_t* pList){
    LinkedNode_t* pCurrent;
    LinkedNode_t* pTemp;
    int CurrentIdx = 0;
    int NodesToClear;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList)){
        pCurrent = pList->pFirst;  
        NodesToClear = pList->NodesNr;
        for (CurrentIdx = 0;CurrentIdx<NodesToClear;CurrentIdx++)
        {     
            pTemp = pCurrent;
            pCurrent = pCurrent->pNext;
            free(pTemp);

            pList->NodesNr--;
        }
        /*Nothing for list first to point to*/
        pList->pFirst = NULL;
    }
}
/*
* @brief Returns number of nodes in the linked list
* @param pList Pointer to the linked list
* @return Number of nodes in the linked list
*/
int LinkedListGetNodesNr(LinkedList_t* pList){
    return pList->NodesNr;
}
/* 
* @brief Inserts a new node with new data before a specific place in the list
* (inserts at the end if last index +1 is used in NodeIndex)
* @param pList Pointer to linked list
* @param pData Pointer to data to be added to new inserted node
* @param NodeIndex Index of the node before which the new item is inserted
*/
void LinkedListInsert(LinkedList_t* pList, LinkedData_t* pData,int NodeIndex){
    LinkedNode_t* pNewNode;
    /*To insert at the end of the list, last existing index + 1 is used so it is a valid input*/
    if (VALID_PTR(pList) && VALID_PTR(pData) && (NODE_EXISTS(pList,NodeIndex) || NODE_IS_NEW_AT_END(pList,NodeIndex))){
        CreateLinkedNode(&pNewNode,pData);
        LinkedListInsertNode(pList,pNewNode,NodeIndex);
    }
}    
/* 
* @brief Inserts a new node with new data at the start of the linked list
* @param pList Pointer to linked list
* @param pData Pointer to data to be added to new inserted node
*/
void LinkedListInsertStart(LinkedList_t* pList, LinkedData_t* pData){
    LinkedListInsert(pList, pData,0);    
}
/* 
* @brief Inserts a new node with new data at the end of the linked list
* @param pList Pointer to linked list
* @param pData Pointer to data to be added to new inserted node
*/
void LinkedListInsertEnd(LinkedList_t* pList, LinkedData_t* pData){
    LinkedListInsert(pList, pData,pList->NodesNr);    
}
/* 
* @brief Reads new data from linked list node to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
* @param NodeIndex Index of the list node to get data from
*/
void LinkedListGet (LinkedList_t* pList, LinkedData_t* pData, int NodeIndex){  
    LinkedNode_t* pNode;

    if (VALID_PTR(pList) && VALID_PTR(pData) && NON_EMPTY_LIST(pList) && NODE_EXISTS(pList,NodeIndex)){
        pNode = GetNodePtr(pList, NodeIndex);
        *pData = pNode->Data;
    }
}
/* 
* @brief Writes new data to linked list node from provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied from
* @param NodeIndex Index of the list node to set data in
*/
void LinkedListSet (LinkedList_t* pList, LinkedData_t* pData, int NodeIndex){  
    LinkedNode_t* pNode;

    if (VALID_PTR(pList) && VALID_PTR(pData) && NON_EMPTY_LIST(pList) && NODE_EXISTS(pList,NodeIndex)){
        pNode = GetNodePtr(pList, NodeIndex);
        pNode->Data = *pData;
    }
}
/* 
* @brief Removes node from list and writes its contents to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
* @param NodeIndex Index of the node to pop
*/
void LinkedListPop(LinkedList_t* pList, LinkedData_t* pData, int NodeIndex){
    LinkedNode_t* pNode;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && VALID_PTR(pData) && NODE_EXISTS(pList,NodeIndex)){
        pNode = LinkedListBypassNode(pList,NodeIndex);
        *pData = pNode->Data;
        free(pNode); 
        pList->NodesNr--;
    }    
}
/* 
* @brief Removes node from start of list and writes its contents to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
*/
void LinkedListPopStart(LinkedList_t* pList, LinkedData_t* pData){
   LinkedListPop(pList,pData,0); 
}
/* 
* @brief Removes node from end of list and writes its contents to provided location
* @param pList Pointer to linked list
* @param pData Pointer to where linked data is copied to
*/
void LinkedListPopEnd(LinkedList_t* pList, LinkedData_t* pData){
   LinkedListPop(pList,pData,pList->NodesNr-1); 
}
/* 
* @brief Removes node from list
* @param pList Pointer to linked list
* @param NodeIndex Index of the node to remove
*/
void LinkedListRemove(LinkedList_t* pList, int NodeIndex){
    LinkedNode_t* pNode;

    if (VALID_PTR(pList) && NON_EMPTY_LIST(pList) && NODE_EXISTS(pList,NodeIndex)){
        pNode = LinkedListBypassNode(pList,NodeIndex);
        free(pNode); 
        pList->NodesNr--;
    }    
}
/* 
* @brief Removes node from start of list
* @param pList Pointer to linked list
*/
void LinkedListRemoveStart(LinkedList_t* pList){
   LinkedListRemove(pList,0); 
}
/* 
* @brief Removes node from end of list
* @param pList Pointer to linked list
*/
void LinkedListRemoveEnd(LinkedList_t* pList){
   LinkedListRemove(pList,pList->NodesNr-1); 
}