#pragma once

#include <stdlib.h>
#include <stdbool.h>

// List error codes
typedef enum ListErrorCode
{
    ListOK = 0,
    ListMemoryAllocationError = -1,
    ListNULLPointerError = -2,
    ListElementDoesNotExist = -3
} ListErrorCode;

typedef struct ListElement ListElement;
typedef struct List List;

// Create list
List* listCreate();

// Add element to list
ListErrorCode listPush(const int key, const int intValue, List* list);

// Find element in list
unsigned int listFind(const List* list, const int key);

// Get size of list
size_t listSize(const List* list);

ListErrorCode listGetKeys(const List* list, int** keys);

// Print list
ListErrorCode listPrint(const List* list);

// Free list
ListErrorCode listFree(List** list);