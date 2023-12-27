#pragma once

typedef struct List List;

// create list
List *createList();

// add element to list
int push(List** head, int value);

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

// removes the Nth element and shifts the head of the list
int deleteNthWithShift(List** head, int index);

// shift to 1 element
void shift(List** head);