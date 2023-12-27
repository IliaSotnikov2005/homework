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

// Find element in list
ListElement* listFind(const List* list, const char* key);

// Get value of list element, 0 if nullptr given
int listElementGetValue(const ListElement* element);

// Change value of list element
ListErrorCode listElementChangeValue(ListElement* element, const int value);

// Get size of list, 0 if nullprt given
size_t listSize(const List* list);

// Check if list is empty
bool listIsEmpty(const List* list);

// Get list items
ListErrorCode listGetItems(const List* list, char*** keys, int** values);

// Print list
ListErrorCode listPrint(const List* list);

// Free list
ListErrorCode listFree(List * *list);
