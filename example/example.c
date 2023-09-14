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

  LinkedData_t v[10] = {0,1,2,3,4,5,6,7,8,9};

  LinkedData_t GetVal;

  printf("DEBUG: Inserting 0,1,2 at end \n");
  LinkedListInsertEnd(&MyLinkedList,&v[0]);
  LinkedListInsertEnd(&MyLinkedList,&v[1]);
  LinkedListInsertEnd(&MyLinkedList,&v[2]);
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

  return 0;
}
