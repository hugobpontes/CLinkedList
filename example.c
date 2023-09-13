#include <stdio.h>
#include "linked.h"

int main (){


  LinkedList_t MyLinkedList;
  LinkedListInit(&MyLinkedList);

  LinkedListAdd(&MyLinkedList, 11);
  LinkedListAdd(&MyLinkedList, 22);
  LinkedListAdd(&MyLinkedList,33);

  printf("N of Elements: %d \n", LinkListGetElements(&MyLinkedList));

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, 0));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));
  printf("Element 2: %d \n",LinkedListGet(&MyLinkedList, 2));

  printf("Popping Element 1: %d \n",LinkedListPop(&MyLinkedList, 1));

  printf("N of Elements: %d \n", LinkListGetElements(&MyLinkedList));

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, -7));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));
  
  return 0;
}
