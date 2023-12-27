#include "cycleList.h"

#include <stdio.h>
#include <stdlib.h>

struct List
{
    int value;
    List* next;
    List* previous;
};

List* createList(void)
{
    return NULL;
}

int push(List** head, int value)
{
    List* temp = calloc(1, sizeof(List));

    if (temp == NULL)
    {
        return -1;
    }
    temp->value = value;
    if (*head == NULL)
    {
        temp->next = temp;
        temp->previous = temp;
        (*head) = temp;
        return 0;
    }
    List* nextOld = (*head)->next;
    (*head)->next = temp;
    temp->previous = (*head);
    temp->next = nextOld;
    nextOld->previous = temp;
    (*head) = temp;
    return 0;
}

void shift(List** head)
{
    if ((*head) == NULL)
    {
        return;
    }
    (*head) = (*head)->next;
}

int pop(List** head)
{
    if ((*head) == NULL)
    {
        return 0;
    }
    List* temp = (*head);
    int headValue = temp->value;
    List* newHead = temp->next;
    if (temp == newHead)
    {
        free(temp);
        (*head) = NULL;
        return headValue;
    }
    temp->previous->next = newHead;
    newHead->previous = temp->previous;
    
    free(temp);
    *head = newHead;
    return headValue;
}

void deleteList(List** head)
{
    List* previous = NULL;
    while ((*head) != NULL)
    {
        pop(head);
    }
}