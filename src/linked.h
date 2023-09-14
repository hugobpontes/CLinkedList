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

void LinkedListInsert(LinkedList_t* pList, LinkedData_t* pData,int EntryIndex);
void LinkedListInsertStart(LinkedList_t* pList, LinkedData_t* pData);
void LinkedListInsertEnd(LinkedList_t* pList, LinkedData_t* pData);

void LinkedListGet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex);
void LinkedListSet (LinkedList_t* pList, LinkedData_t* pData, int EntryIndex);
//(all pointer)
//insert start -done
//insert -done
//insert end
//pop start
//pop 
//pop end
//remove start
//remove 
//remove end

//set
//get- done

