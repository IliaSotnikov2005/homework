#include "list.h"
#include "errorCodes.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct ListElement ListElement;
struct ListElement
{
    char* stringValue;
    int intValue;
    ListElement* next;
};

struct List
{
    ListElement* head;
};

List* listCreate()
{
    List* list = (List*)calloc(1, sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    return list;
}

static ErrorCode freeListElement(ListElement* listElement)
{
    if (listElement == NULL)
    {
        return NULLPointerError;
    }

    free(listElement->stringValue);
    free(listElement);

    return OK;
}

ErrorCode listPush(const char* stringValue, const int intValue, List* list)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }

    newElement->stringValue = strdup(stringValue);
    newElement->intValue = intValue;
    newElement->next = list->head;
    list->head = newElement;

    return OK;
}

static ListElement* getLast(const List* list)
{
    ListElement* element = list->head;
    if (element == NULL)
    {
        return NULL;
    }
    while (element->next != NULL)
    {
        element = element->next;
    }

    return element;
}

ErrorCode listPushBack(const char* stringValue, const int intValue, List* list)
{
    if (list == NULL)
    {
        return NULLPointerError;
    }

    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }

    newElement->intValue = intValue;
    newElement->stringValue = strdup(stringValue);
    newElement->next = NULL;

    ListElement* listElement = getLast(list);

    if (listElement == NULL)
    {
        list->head = newElement;
        return OK;
    }

    listElement->next = newElement;

    return OK;
    
}

ErrorCode listPop(List* list, char* stringValue, int* intValue)
{
    if (list == NULL)
    {
        return NULLPointerError;
    }

    ListElement* beingDeleted = list->head;
    if (list->head != NULL)
    {
        list->head = list->head->next;
        stringValue = strdup(beingDeleted->stringValue);
        *intValue = beingDeleted->intValue;
    }

    freeListElement(beingDeleted);

    return OK;
}

static ListElement** find(const List* list, unsigned int index)
{
    ListElement** pointerToElement = NULL;
    for (pointerToElement = &(list->head); (*pointerToElement) != NULL && index != 0; pointerToElement = &((*pointerToElement)->next))
    {
        if (index == 0)
        {
            break;
        }

        --index;
    }

    return pointerToElement;
}

ErrorCode listRemove(const List* list, unsigned int index)
{
    if (list == NULL)
    {
        return NULLPointerError;
    }

    ListElement** pointerToElement = find(list, index);
    if (*pointerToElement == NULL)
    {
        return ListIndexOutOfRange;
    }

    ListElement* beingDeleted = *pointerToElement;
    *pointerToElement = (*pointerToElement)->next;
    freeListElement(beingDeleted);

    return OK;
}

ErrorCode listGet(const List* list, unsigned int index, char* stringValue, int* intValue)
{
    if (list == NULL)
    {
        return NULLPointerError;
    }

    ListElement* listElement = list->head;
    for (index; index != 0 && listElement != NULL; --index)
    {
        listElement = listElement->next;
    }
    if (index != 0 || listElement == NULL)
    {
        return ListIndexOutOfRange;
    }

    stringValue = strdup(listElement->stringValue);
    (*intValue) = listElement->intValue;
    return OK;
}

ErrorCode listExtend(const List* list1, List* list2)
{
    if (list1 == NULL || list2 == NULL)
    {
        return NULLPointerError;
    }

    ListElement* lastList1Element = getLast(list1);
    lastList1Element->next = list2->head;

    return OK;
}

size_t listSize(const List* list)
{
    if (list == NULL)
    {
        return 0;
    }

    ListElement* listElement = list->head;
    int counter = 0;
    while (listElement != NULL)
    {
        ++counter;
    }

    return counter;
}

ErrorCode listPrint(const List* list)
{
    if (list == NULL)
    {
        return NULLPointerError;
    }

    ListElement* head = list->head;
    while (head)
    {
        printf("(%s, %d) ", head->stringValue, head->intValue);
        head = head->next;
    }
    printf("\n");

    return OK;
}

ErrorCode listFree(List* list)
{
    if (list == NULL)
    {
        return NULLPointerError;
    }

    ListElement* head = list->head;
    ListElement* beingDeleted = NULL;
    while (head->next)
    {
        beingDeleted = head;
        head = head->next;
        freeListElement(beingDeleted);
    }
    freeListElement(head);
    free(list);

    return OK;
}