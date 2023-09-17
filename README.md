<!-- Just fill in the brackets -->
# C LINKED LIST

[![master](https://img.shields.io/badge/master-v1.0-red.svg?style=flat-square)]()

CLinkedList is a simple linked list library in pure C, allowing one to store any data type in dynamically sized lists. This library provides all the essential linked list features while being flexible enough to be usable with any data type the user wishes.

Features
--------
The following linked list features are provided:
- Get Linked Node Data
- Set Linked Node Data
- Pop Linked Node
- Insert Linked Node
- Remove Linked
- Get Number of Nodes
- Clear linked list

Pop, Insert and Remove features also have "at Start" and "at End" variants to make usage simpler 

Contents
-------------------------

 - **src**
	 - linked.c
	 - linked.h
 - **example**
	 - example.c
 - .gitignore
 - LICENSE
 - README.md
 
 **linked.c** is the source file, containing all implementation code, while **linked.h** defines the public interfaces and public types. These are just standard src files.

 **example.c** contains a small program that exercises this library, showing all its features and printing debug information to stdout. Consult this for a practical example on how to use this library.

The remaining files are standard repository files. 

Usage
----------

To use this library simply include linked.h in your application/program and use it. It is very intuitive, and the example file shows the intended use, but here are the important steps one should take anyway:
- In **linked.h** change the ```LinkedData_t``` typedef so that the data type stored in the linked nodes matches your needs (by default ```int``` is used)
- Declare a linked list handle.
- Initialize linked list with ```LinkedListInit``` (resets first pointer and number of nodes). 
- Insert at least one node using the ```LinkedListInsertStart``` or ```LinkedListInsertEnd``` or even the generic insert function, ```LinkedListInsert```.
- Insert, pop, or remove nodes as you want using ```LinkedListInsert```,```LinkedListPop```,```LinkedListRemove``` and its start and end varations.
- When done with using the linked list, clear it with ```LinkedListClear```, which frees up all memory taken by the LinkedList nodes.

Contributing
----------

Pull requests and any sort of feedback/requests are welcome.

Contact
----------

You can reach me at hpontes9@gmail.com

