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
typedef struct Linked {
    LinkedData_t Data;
    struct Linked * pNext;
    struct Linked * pPrevious;
} LinkedEntry_t;
/* 
* @brief Linked list handle
* @param pFirst Pointer to the first element in the linked list
* @param EntriesNr Current number of entries in the linked list
*/
typedef struct {
    LinkedEntry_t* pFirst;
    int EntriesNr;
}
LinkedList_t;

void LinkedListInit(LinkedList_t* pList);
int LinkedListGetEntriesNr(LinkedList_t* pList);
void LinkedListClear(LinkedList_t* pList);

void LinkedListInsert(LinkedList_t* pList, LinkedData_t* pData,int EntryIndex);
void LinkedListInsertStart(LinkedList_t* pList, LinkedData_t* pData);
void LinkedListInsertEnd(LinkedList_t* pList, LinkedData_t* pData);

void LinkedListGet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex);
void LinkedListSet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex);

void LinkedListPop(LinkedList_t* pList, LinkedData_t* pData, int EntryIndex);
void LinkedListPopStart(LinkedList_t* pList, LinkedData_t* pData);
void LinkedListPopEnd(LinkedList_t* pList, LinkedData_t* pData);

void LinkedListRemove(LinkedList_t* pList, int EntryIndex);
void LinkedListRemoveStart(LinkedList_t* pList);
void LinkedListRemoveEnd(LinkedList_t* pList);

