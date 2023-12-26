#pragma once

typedef enum sortedListErrorCode
{
    sortedListOk = 0,
    sortedListMemoruAllocationError = -1,
    sortedListNullPointerError = -2,
    sortedListListIsEmptyError = -3,
    sortedListNoSuchElementInList = -4
} sortedListErrorCode;

typedef struct SortedList SortedList;

// Create list.
SortedList* createSortedList(void);

// Add element to list.
sortedListErrorCode sortedListPush(SortedList* list, const int value);

// Remove list element by value.
sortedListErrorCode sortedListRemove(SortedList* list, const int value);

// Print list.
sortedListErrorCode sortedListPrint(const SortedList* list);

// Free list.
sortedListErrorCode sortedListFree(SortedList** head);

// List to array.
int* sortedListToArray(const SortedList* head);