#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct ListElement
{
    char* key;
    int intValue;
    ListElement* next;
};

struct List
{
    ListElement* head;
    ListElement* back;
    size_t length;
};

List* listCreate()
{
    return (List*)calloc(1, sizeof(List));
}

static ListErrorCode freeListElement(ListElement* listElement)
{
    if (listElement == NULL)
    {
        return ListNULLPointerError;
    }

    free(listElement->key);
    free(listElement);

    return ListOK;
}

ListErrorCode listPush(const char* key, const int intValue, List* list)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return ListMemoryAllocationError;
    }

    newElement->key = strdup(key);
    if (newElement->key == NULL)
    {
        ListMemoryAllocationError;
    }
    newElement->intValue = intValue;
    newElement->next = list->head;
    list->head = newElement;
    if (list->length == 0)
    {
        list->back = newElement;
    }
    ++list->length;

    return ListOK;
}

static ListElement** find(const List* list, const char* key)
{
    ListElement** pointerToElement = NULL;
    for (pointerToElement = &(list->head); (*pointerToElement) != NULL; pointerToElement = &((*pointerToElement)->next))
    {
        if (strcmp(key, (*pointerToElement)->key) == 0)
        {
            break;
        }
    }

    return pointerToElement;
}

ListElement* listFind(const List* list, const char* key)
{
    return list == NULL ? NULL : *find(list, key);
}

int listElementGetValue(const ListElement* element)
{
    return element == NULL ? 0 : element->intValue;
}

ListErrorCode listElementChangeValue(ListElement* element, const int value)
{
    if (element == NULL)
    {
        return ListNULLPointerError;
    }

    element->intValue = value;

    return ListOK;
}

size_t listSize(const List* list)
{
    return list == NULL ? 0 : list->length;
}

bool listIsEmpty(const List* list)
{
    return list == NULL ? true : list->head == NULL;
}

ListErrorCode listGetItems(const List* list, char*** keys, int** values)
{
    if (list == NULL)
    {
        return ListNULLPointerError;
    }

    char** listKeys = calloc(list->length, sizeof(char*));
    int* listValues = calloc(list->length, sizeof(int));

    if (listKeys == NULL || listValues == NULL)
    {
        free(listKeys);
        free(listValues);
        return ListMemoryAllocationError;
    }

    ListElement* element = list->head;
    for (size_t i = 0; i < list->length; ++i)
    {
        listKeys[i] = strdup(element->key);
        listValues[i] = element->intValue;
        element = element->next;
    }

    (*keys) = listKeys;
    (*values) = listValues;

    return ListOK;
}

ListErrorCode listPrint(const List* list)
{
    if (list == NULL)
    {
        return ListNULLPointerError;
    }

    ListElement* head = list->head;
    if (head == NULL)
    {
        return ListOK;
    }

    while (head)
    {
        printf("(%s, %d) ", head->key, head->intValue);
        head = head->next;
    }
    printf("\n");

    return ListOK;
}

ListErrorCode listFree(List** list)
{
    if ((*list) == NULL)
    {
        return ListNULLPointerError;
    }

    ListElement* head = (*list)->head;
    if (head == NULL)
    {
        free((*list));
        (*list) = NULL;

        return ListOK;
    }
    ListElement* beingDeleted = NULL;
    while (head->next)
    {
        beingDeleted = head;
        head = head->next;
        freeListElement(beingDeleted);
    }
    freeListElement(head);
    free((*list));
    (*list) = NULL;

    return ListOK;
}