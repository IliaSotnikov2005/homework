#pragma once

typedef struct List List;

// create list
List *createList();

// print list
void printList(const List* head);

// free list
void deleteList(List** head);

//create list from file
List* listFromFile(const char* filename);

// merge sort list
int mergeSort(List** head, const int sortType);

// split list
void splitList(List* source, List** firstPart, List** secondPart);