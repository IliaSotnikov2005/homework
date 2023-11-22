#pragma once

#include "errorCodes.h"

typedef struct List List;

// create list
List* listCreate();

// add element to list
ErrorCode listPush(List** head, const int value);

// find element by index in list
List** listFind(const List** head, int index);

// remove lists head
ErrorCode listPop(List** head);

// print list
ErrorCode listPrint(const List* head);

// get list size
int listSize(const List* head);

// list to array
int* listToArray(const List* head);

// free list
ErrorCode listFree(List** head);