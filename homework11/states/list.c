#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct ListElement
{
    int city;
    int roadLength;
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

    free(listElement);

    return ListOK;
}

ListErrorCode listPush(const int city, const int roadLength, List* list)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return ListMemoryAllocationError;
    }

    newElement->city = city;
    newElement->roadLength = roadLength;
    newElement->next = list->head;
    list->head = newElement;
    if (list->length == 0)
    {
        list->back = newElement;
    }
    ++list->length;

    return ListOK;
}

static unsigned int find(const List* list, const int key)
{
    ListElement* pointerToElement = NULL;
    for (pointerToElement = list->head; pointerToElement != NULL; pointerToElement = pointerToElement->next)
    {
        if (key == pointerToElement->city)
        {
            break;
        }
    }

    return pointerToElement == NULL ? 0: pointerToElement->roadLength;
}

unsigned int listFind(const List* list, const int key)
{
    return list == NULL ? NULL : find(list, key);
}

size_t listSize(const List* list)
{
    return list == NULL ? 0 : list->length;
}

ListErrorCode listGetKeys(const List* list, int** keys)
{
    if (list == NULL || keys == NULL)
    {
        return ListNULLPointerError;
    }

    int* listKeys = calloc(list->length, sizeof(int));

    if (listKeys == NULL)
    {
        free(listKeys);
        return ListMemoryAllocationError;
    }

    ListElement* element = list->head;
    for (size_t i = 0; i < list->length; ++i)
    {
        listKeys[i] = element->city;
        element = element->next;
    }

    (*keys) = listKeys;

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
        printf("%d ", head->city);
        head = head->next;
    }
    printf("\n");

    return ListOK;
}

ListErrorCode listFree(List** list)
{
    if (list == NULL)
    {
        return ListNULLPointerError;
    }
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