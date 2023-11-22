#include "list.h"
#include "errorCodes.h"

#include <stdlib.h>
#include <stdio.h>

struct List
{
    int value;
    List* next;
};

List* listCreate()
{
    return NULL;
}

ErrorCode listPush(List** head, const int value)
{
    if (head == NULL)
    {
        return NULLPointer;
    }

    List* newElement = calloc(1, sizeof(List));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }

    newElement->value = value;
    newElement->next = (*head);
    (*head) = newElement;
    return OK;
}

List** listFind(const List** head, int index)
{
    List** node = NULL;
    for (node = head; *node != NULL; node = &(*node)->next)
    {
        if (index == 0)
        {
            break;
        }
        --index;
    }
    return node;
}

ErrorCode listPop(List** head)
{
    if (head == NULL)
    {
        return NULLPointer;
    }

    List* oldElement = *head;
    *head = (*head)->next;
    free(oldElement);

    return OK;
}

ErrorCode listPrint(const List* head)
{
    if (head == NULL)
    {
        return NULLPointer;
    }
    while (head)
    {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
    return OK;
}

int listSize(const List* head)
{
    if (head == NULL)
    {
        return NULLPointer;
    }

    int size = 0;
    while (head)
    {
        ++size;
        head = head->next;
    }
    return size;
}

int* listToArray(const List* head)
{
    int size = listSize(head);
    int* values = calloc(size, sizeof(int));
    if (values == NULL)
    {
        return -1;
    }
    int i = 0;
    while (head)
    {
        values[i] = head->value;
        ++i;
        head = head->next;
    }
    return values;
}

ErrorCode listFree(List** head)
{
    if (head == NULL)
    {
        return NULLPointer;
    }

    List* temp = NULL;
    while (*head)
    {
        temp = (*head);
        *head = (*head)->next;
        free(temp);
    }
    free(*head);

    return OK;
}