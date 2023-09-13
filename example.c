#include <stdio.h>
#include "linked.h"

int main (){


  LinkedList_t MyLinkedList;
  LinkedListInit(&MyLinkedList);

  LinkedListAdd(&MyLinkedList, 11);
  LinkedListAdd(&MyLinkedList, 22);
  LinkedListAdd(&MyLinkedList,33);
  LinkedListAdd(&MyLinkedList, 55);
  LinkedListAdd(&MyLinkedList, 66);
  LinkedListAdd(&MyLinkedList,77);

  printf("N of Elements: %d \n", LinkListGetElements(&MyLinkedList));

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, 0));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));
  printf("Element 2: %d \n",LinkedListGet(&MyLinkedList, 2));

  printf("Setting Element 2: %d \n",99);
  LinkedListSet(&MyLinkedList,2,99);

  printf("Popping Element 1: %d \n",LinkedListPop(&MyLinkedList, 1));
  printf("Popping End: %d \n",LinkedListPopEnd(&MyLinkedList));
  printf("Popping Start: %d \n",LinkedListPopStart(&MyLinkedList));

  printf("N of Elements: %d \n", LinkListGetElements(&MyLinkedList));

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, 0));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));
  printf("Element 2: %d \n",LinkedListGet(&MyLinkedList, 2));
  
  return 0;
}
