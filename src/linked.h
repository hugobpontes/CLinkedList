//Change here to whatever you want to have a linked list of
typedef int LinkedData_t;

typedef struct Linked {
    LinkedData_t Data;
    struct Linked * pNext;
    struct Linked * pPrevious;
} LinkedEntry_t;

typedef struct {
    LinkedEntry_t* pFirst;
    int EntriesNr;
}
LinkedList_t;

void LinkedListInit(LinkedList_t* pList);
int LinkedListGetEntriesNr(LinkedList_t* pList);
void LinkedListClear(LinkedList_t* pList);

void LinkedListAdd(LinkedList_t* pList, LinkedData_t Val);
void LinkedListSet (LinkedList_t* pList, int EntryIndex, LinkedData_t Val);

LinkedData_t LinkedListGet (LinkedList_t* pList, int EntryIndex);
LinkedData_t LinkedListPop(LinkedList_t* pList, int EntryIndex);
LinkedData_t LinkedListPopEnd(LinkedList_t* pList);
LinkedData_t LinkedListPopStart(LinkedList_t* pList);

void LinkedListPopNoReturn(LinkedList_t* pList, int EntryIndex);
LinkedData_t* LinkedListGetPtr (LinkedList_t* pList, int EntryIndex);
void LinkedListPopEndNoReturn(LinkedList_t* pList);
void LinkedListPopStartNoReturn(LinkedList_t* pList);
