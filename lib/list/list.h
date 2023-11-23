#pragma once

#include "errorCodes.h"

#include <stdlib.h>

typedef struct List List;

// create list
List* listCreate();

// add element to list
ErrorCode listPush(const char* stringValue, const int intValue, List* list);

// add element to the end of list
ErrorCode listPushBack(const char* stringValue, const int intValue, List* list);

// remove first list element
ErrorCode listPop(List* list, char* stringValue, int* intValue);

// remove element from list by index
ErrorCode listRemove(List* list, unsigned int index);

// get element by index
ErrorCode listGet(List* list, unsigned int index, char* stringValue, int* intValue);

// extend list
ErrorCode listExtend(List* list1, List* list2);

// get size of list
size_t listSize(const List* list);

// print list
ErrorCode listPrint(const List* list);

// free list
ErrorCode listFree(List* list);