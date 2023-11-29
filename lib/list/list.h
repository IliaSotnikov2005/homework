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
ListErrorCode listPush(const char* key, const int intValue, List* list);

// Add element to the end of list
ListErrorCode listPushBack(const char* key, const int intValue, List* list);

// Remove first list element
ListErrorCode listPop(List* list, char* key, int* intValue);

// Remove element from list by index
ListErrorCode listRemove(const List* list, const char* key);

// Find element in list
ListElement* listFind(const List* list, const char* const key);

// Get value of list element
int listElementGetValue(ListElement* element);

// Change value of list element
ListErrorCode listElementChangeValue(ListElement* element, const int value);

// Extend list by another list
ListErrorCode listExtend(List* list1, List* list2);

// Get size of list
size_t listSize(const List* list);

// Check if list is empty
bool listIsEmpty(const List* list);

ListErrorCode listItems(const List* list, char*** keys, int** values);

// Print list
ListErrorCode listPrint(const List* list);

// Free list
ListErrorCode listFree(List** list);