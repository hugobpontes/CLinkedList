#include <stdio.h>
#include "linked.h"

int main (){


  LinkedList_t MyLinkedList;
  LinkedListInit(&MyLinkedList);

  LinkedData_t v33 = 33;

  LinkedListAdd(&MyLinkedList, 11);
  LinkedListAdd(&MyLinkedList, 22);
  LinkedListPtrAdd(&MyLinkedList,&v33);
  LinkedListAdd(&MyLinkedList, 55);
  LinkedListAdd(&MyLinkedList, 66);
  LinkedListAdd(&MyLinkedList,77);

  printf("EntriesNr: %d \n", LinkedListGetEntriesNr(&MyLinkedList));

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, 0));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));
  printf("Element 2: %d \n",LinkedListGet(&MyLinkedList, 2));
  printf("Element 3: %d \n",LinkedListGet(&MyLinkedList, 3));
  printf("Element 4: %d \n",LinkedListGet(&MyLinkedList, 4));
  printf("Element 5: %d \n",LinkedListGet(&MyLinkedList, 5));

  printf("Setting Element 2: 99 \n");
  LinkedListSet(&MyLinkedList,2,99);
  printf("Setting Element 5: 33 \n");
  LinkedListPtrSet(&MyLinkedList,5,&v33);

  printf("Popping Element 1: %d \n",LinkedListPop(&MyLinkedList, 1));
  printf("Popping End: %d \n",LinkedListPopEnd(&MyLinkedList));
  printf("Popping Start: %d \n",LinkedListPopStart(&MyLinkedList));

  printf("EntriesNr: %d \n", LinkedListGetEntriesNr(&MyLinkedList));

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, 0));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));
  printf("Element 2: %d \n",LinkedListGet(&MyLinkedList, 2));
  
  printf("Element 2 (via pointer): %d \n",*LinkedListGetPtr(&MyLinkedList, 2));

  printf("Clearing list \n");
  LinkedListClear(&MyLinkedList);

  printf("EntriesNr: %d \n", LinkedListGetEntriesNr(&MyLinkedList));

  return 0;
}
