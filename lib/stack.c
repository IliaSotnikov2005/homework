#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void push(Stack** head, const int value)
{
    Stack* next = malloc(sizeof(Stack));
    if (next == NULL)
    {
        return -1;
    }
    next->value = value;
    next->size = (*head)->size + 1;
    next->previous = *head;
    *head = next;
    return 0;
}

int pop(Stack** head)
{
    if (head == NULL)
    {
        return -1;
    }
    Stack* trash = *head;
    *head = (*head)->previous;
    int trashValue = trash->value;
    if (trash->size == 1)
    {
        (*head)->previous = NULL;
        (*head)->size = 0;
        (*head)->value = NULL;
    }
    free(trash);
    return trashValue;
}

int clean(Stack** head)
{
    Stack* next = (*head)->previous;
    free(*head);
    while (next != NULL)
    {
        Stack* temp = next;
        next = next->previous;
        free(temp);
    }
}