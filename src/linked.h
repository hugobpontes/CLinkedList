/* 
* @brief Data type of data to be linked (int by default, can be changed in linked.h)
*/
typedef int LinkedData_t;
/* 
* @brief Linked list node
* @param Data Data stored in the linked node
* @param pNext Pointer to the next node
* @param pPrevious Pointer to the previous node
*/
typedef struct LinkedNode {
    LinkedData_t Data;
    struct LinkedNode * pNext;
    struct LinkedNode * pPrevious;
} LinkedNode_t;
/* 
* @brief Linked list handle
* @param pFirst Pointer to the first element in the linked list
* @param NodesNr Current number of nodes in the linked list
*/
typedef struct {
    LinkedNode_t* pFirst;
    int NodesNr;
}
LinkedList_t;

void LinkedListInit(LinkedList_t* pList);
int LinkedListGetNodesNr(LinkedList_t* pList);
void LinkedListClear(LinkedList_t* pList);

void LinkedListInsert(LinkedList_t* pList, LinkedData_t* pData,int NodeIndex);
void LinkedListInsertStart(LinkedList_t* pList, LinkedData_t* pData);
void LinkedListInsertEnd(LinkedList_t* pList, LinkedData_t* pData);

void LinkedListGet (LinkedList_t* pList, LinkedData_t* pData, int NodeIndex);
void LinkedListSet (LinkedList_t* pList, LinkedData_t* pData, int NodeIndex);

void LinkedListPop(LinkedList_t* pList, LinkedData_t* pData, int NodeIndex);
void LinkedListPopStart(LinkedList_t* pList, LinkedData_t* pData);
void LinkedListPopEnd(LinkedList_t* pList, LinkedData_t* pData);

void LinkedListRemove(LinkedList_t* pList, int NodeIndex);
void LinkedListRemoveStart(LinkedList_t* pList);
void LinkedListRemoveEnd(LinkedList_t* pList);

