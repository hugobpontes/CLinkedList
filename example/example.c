#include <stdio.h>
#include "linked.h"


void PrintList(LinkedList_t* pList){
  printf("List: ");
  LinkedData_t PrintVal;
  for (int idx = 0;idx<pList->EntriesNr;idx++){
    LinkedListGet(pList,&PrintVal,idx);
    printf("[%d]",PrintVal);
  }
  printf("\n");
}

int main (){


  LinkedList_t MyLinkedList;
  LinkedListInit(&MyLinkedList);

  LinkedData_t v[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

  LinkedData_t PopVal;

  printf("DEBUG: Inserting 0,1,2,3,4 at end \n");
  LinkedListInsertEnd(&MyLinkedList,&v[0]);
  LinkedListInsertEnd(&MyLinkedList,&v[1]);
  LinkedListInsertEnd(&MyLinkedList,&v[2]);
  LinkedListInsertEnd(&MyLinkedList,&v[3]);
  LinkedListInsertEnd(&MyLinkedList,&v[4]);
  PrintList(&MyLinkedList);

  printf("DEBUG: Inserting 7 at end \n");
  LinkedListInsertEnd(&MyLinkedList,&v[7]);
  PrintList(&MyLinkedList);

  printf("DEBUG: Inserting 8 at start \n");
  LinkedListInsertStart(&MyLinkedList,&v[8]);
  PrintList(&MyLinkedList);

  printf("DEBUG: Inserting 9 at idx 4 \n");
  LinkedListInsert(&MyLinkedList,&v[9],4);
  PrintList(&MyLinkedList);

  printf("DEBUG: Setting idx 4 to 5 \n");
  LinkedListSet(&MyLinkedList,&v[5],4);
  PrintList(&MyLinkedList);

  LinkedListPopStart(&MyLinkedList,&PopVal);
  printf("DEBUG: Popped start: %d \n",PopVal);
  PrintList(&MyLinkedList);

  LinkedListPopEnd(&MyLinkedList,&PopVal);
  printf("DEBUG: Popped end: %d \n",PopVal);
  PrintList(&MyLinkedList);

  LinkedListPop(&MyLinkedList,&PopVal,1);
  printf("DEBUG: Popped idx 1: %d \n",PopVal);
  PrintList(&MyLinkedList);

  LinkedListRemoveStart(&MyLinkedList);
  printf("DEBUG: Removed Start \n");
  PrintList(&MyLinkedList);

  LinkedListRemoveEnd(&MyLinkedList);
  printf("DEBUG: Removed End \n");
  PrintList(&MyLinkedList);

  LinkedListRemove(&MyLinkedList,1);
  printf("DEBUG: Removed Index 1 \n");
  PrintList(&MyLinkedList);

  LinkedListRemoveEnd(&MyLinkedList);
  LinkedListRemoveEnd(&MyLinkedList);
  printf("DEBUG: Removed two from End \n");
  PrintList(&MyLinkedList);

  printf("DEBUG: Popping start from empty list (should do nothing) \n");
  LinkedListPopStart(&MyLinkedList,&PopVal);
  PrintList(&MyLinkedList);

  printf("DEBUG: Popping end from empty list (should do nothing) \n");
  LinkedListPopEnd(&MyLinkedList,&PopVal);
  PrintList(&MyLinkedList);

  printf("DEBUG: Inserting 7 at index 9 (should do nothing) \n");
  LinkedListInsert(&MyLinkedList,&v[7],9);
  PrintList(&MyLinkedList);

  printf("DEBUG: Repeating initial insertion just to finish with something on list :) \n");
  LinkedListInsertEnd(&MyLinkedList,&v[0]);
  LinkedListInsertEnd(&MyLinkedList,&v[1]);
  LinkedListInsertEnd(&MyLinkedList,&v[2]);
  LinkedListInsertEnd(&MyLinkedList,&v[3]);
  LinkedListInsertEnd(&MyLinkedList,&v[4]);
  PrintList(&MyLinkedList);

  return 0;
}
