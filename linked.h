//Change here to whatever you want to have a linked list of
typedef int LinkedData_t;

typedef struct Linked {
    LinkedData_t Data;
    struct Linked * pNext;
    struct Linked * pPrevious;
} LinkedEntry_t;

typedef struct {
    LinkedEntry_t* pFirst;
    int Elements;
}
LinkedList_t;

void LinkedListInit(LinkedList_t* pList);
LinkedData_t LinkedListGet (LinkedList_t* pList, int EntryIndex);
void LinkedListAdd(LinkedList_t* pList, LinkedData_t Val);
LinkedData_t LinkedListPop(LinkedList_t* pList, int EntryIndex);
int LinkListGetElements(LinkedList_t* pList);