#include <stdio.h>
#include "linked.h"

int main (){


  LinkedList_t MyLinkedList;
  LinkedListInit(&MyLinkedList);

  LinkedListAdd(&MyLinkedList, 10);
  LinkedListAdd(&MyLinkedList, 20);

  printf("Element 0: %d \n",LinkedListGet(&MyLinkedList, 0));
  printf("Element 1: %d \n",LinkedListGet(&MyLinkedList, 1));

  return 0;
}
