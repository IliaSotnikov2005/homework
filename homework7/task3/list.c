#include "list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement
{
    int value;
    struct ListElement* next;
} ListElement;

struct SortedList
{
    ListElement* head;
    size_t length;
};

SortedList* createList(void)
{
    return calloc(1, sizeof(SortedList));
}

sortedListErrorCode sortedListPush(SortedList* list, const int value)
{
    if (list == NULL)
    {
        return sortedListNullPointerError;
    }

    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return sortedListMemoruAllocationError;
    }

    newElement->value = value;
    ListElement* element = list->head;
    ListElement* previous = NULL;
    if (element == NULL)
    {
        newElement->next = element;
        list->head = newElement;

        return sortedListOk;
    }

    while (value > element->value)
    {
        previous = element;
        element = element->next;
        if (element == NULL)
        {
            previous->next = newElement;
            newElement->next = NULL;

            return sortedListOk;
        }
    }

    newElement->next = list->head;
    list->head = newElement;
    ++list->length;

    return sortedListOk;
}

sortedListErrorCode sortedListRemove(SortedList* list, const int value)
{
    if (list == NULL)
    {
        return sortedListNullPointerError;
    }

    ListElement* element = list->head;
    if (element == NULL)
    {
        return sortedListListIsEmptyError;
    }

    ListElement* previous = NULL;
    while (element->value != value && element != NULL)
    {
        previous = element;
        element = element->next;
    }

    if (element == NULL)
    {
        return sortedListNoSuchElementInList;
    }

    previous->next = element->next;
    free(element);
    --list->length;

    return sortedListOk;
}

sortedListErrorCode sortedListPrint(const SortedList* list)
{
    if (list == NULL)
    {
        return sortedListNullPointerError;
    }

    ListElement* element = list->head;
    while (element != NULL)
    {
        printf("%d ", element->value);
        element = element->next;
    }

    printf("\n");

    return sortedListOk;
}

sortedListErrorCode sortedListFree(SortedList** list)
{
    if (list == NULL)
    {
        return sortedListNullPointerError;
    }

    ListElement* element = (*list)->head;
    ListElement* beeingDeleted = NULL;
    while (element != NULL)
    {
        beeingDeleted = element;
        element = element->next;
        free(beeingDeleted);
    }

    free(*list);
    *list = NULL;

    return sortedListOk;
}

int* sortedListToArray(const SortedList* list)
{
    if (list == NULL)
    {
        return NULL;
    }

    int* array = calloc(list->length, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }

    ListElement* element = list->head;
    for (size_t i = 0; element != NULL; ++i)
    {
        array[i] = element->value;
        element = element->next;
    }

    return array;
}