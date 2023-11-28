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

ListErrorCode listPushBack(const char* key, const int intValue, List* list)
{
    if (list == NULL)
    {
        return ListNULLPointerError;
    }

    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return ListMemoryAllocationError;
    }

    newElement->intValue = intValue;
    newElement->key = strdup(key);
    newElement->next = NULL;

    ListElement* listElement = list->back;

    if (listElement == NULL)
    {
        list->head = newElement;
        list->back = newElement;
        return ListOK;
    }

    listElement->next = newElement;
    list->back = newElement;
    ++list->length;

    return ListOK;
}

ListErrorCode listPop(List* list, char* key, int* intValue)
{
    if (list == NULL)
    {
        return ListNULLPointerError;
    }

    ListElement* beingDeleted = list->head;
    if (list->head != NULL)
    {
        list->head = list->head->next;
        key = strdup(beingDeleted->key);
        *intValue = beingDeleted->intValue;
    }

    freeListElement(beingDeleted);
    --list->length;

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

ListErrorCode listRemove(const List* list, const char* key)
{
    if (list == NULL)
    {
        return ListNULLPointerError;
    }

    ListElement** pointerToElement = find(list, key);
    if (*pointerToElement == NULL)
    {
        return ListElementDoesNotExist;
    }

    ListElement* beingDeleted = *pointerToElement;
    *pointerToElement = (*pointerToElement)->next;
    freeListElement(beingDeleted);

    return ListOK;
}

ListElement* listFind(const List* list, char* key)
{
    return list == NULL ? NULL : *find(list, key);
}

int listElementGetValue(ListElement* element)
{
    return element == NULL ? 0: element->intValue;
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

ListErrorCode listExtend(const List* list1, List* list2)
{
    if (list1 == NULL || list2 == NULL)
    {
        return ListNULLPointerError;
    }

    ListElement* lastList1Element = list1->back;
    lastList1Element->next = list2->head;

    return ListOK;
}

size_t listSize(const List* list)
{
    return list == NULL ? 0 : list->length;
}

bool listIsEmpty(const List* list)
{
    return list == NULL ? ListNULLPointerError: list->head == NULL;
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