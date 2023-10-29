#pragma once

typedef struct List List;

// create list
List *createList();

// add element to list
int push(List** head, char* name, int phoneNumber);

// delete head element
int pop(List** head);

// print list
void printList(const List* head);

// get Nth element
List* getNth(List* head, int index);

// get last element
List* getLast(List* head);

// add element to back
int pushBack(List* head, int value);

// delete Nth element
int deleteNth(List** head, int index);

// free list
void deleteList(List** head);

// returns next element
List* nextElement(List* head);

// shift to 1 element
void shift(List** head);

// changes next element
void changeNext(List* head, List* newList);

// get name
char* getName(List* head);

// get phone
int getPhone(List* head);

//create list from file
List* listFromFile(const char* filename);

// merge sort list
void mergeSort(List** head, const int sortType);

// split list
void splitList(List* source, List** firstPart, List** secondPart);