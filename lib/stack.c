#include "stack.h"
#include <stdlib.h>

struct Stack
{
    char value;
    struct Stack* previous;
    int size;
};

int stackSize(Stack* head)
{
    return head->size;
}

int top(Stack* head)
{
    return head->value;
}

void push(Stack** head, const char value)
{
    Stack* next = malloc(sizeof(Stack));
    if (next == NULL)
    {
        return;
    }
    next->value = value;
    next->size = (*head == NULL) ? 1 : (*head)->size + 1;
    next->previous = *head;
    *head = next;
}

char pop(Stack** head)
{
    if (head == NULL)
    {
        return -1;
    }
    Stack* trash = *head;
    *head = (*head)->previous;
    char trashValue = trash->value;
    free(trash);
    return trashValue;
}

int freeStack(Stack** head)
{
    if (&head == NULL)
    {
        return 0;
    }
    Stack* next = (*head)->previous;
    free(*head);
    while (next != NULL)
    {
        Stack* temp = next;
        next = next->previous;
        free(temp);
    }
    return 0;
}

Stack* createStack()
{
    Stack* stack = calloc(1, sizeof(Stack));
    return stack;
}