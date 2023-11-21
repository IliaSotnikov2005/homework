#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

typedef struct Stack
{
    StackElement* top;
} Stack;

Stack* createStack(void)
{
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    return stack;
}

ErrorCode stackPush(Stack* stack, const int value)
{
    if (stack == NULL)
    {
        return NULLPointer;
    }

    StackElement* newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL)
    {
        return OutOfMemory;
    }

    newElement->value = value;
    newElement->next = stack->top;
    stack->top = newElement;
    return OK;
}

int stackPop(Stack* stack)
{
    if (stack == NULL)
    {
        return NULLPointer;
    }
    if (stack->top == NULL)
    {
        return StackIsEmpty;
    }

    StackElement* topElement = stack->top;
    int value = topElement->value;
    stack->top = topElement->next;

    free(topElement);
    return value;
}

ErrorCode stackFree(Stack* stack)
{
    if (stack == NULL)
    {
        return NULLPointer;
    }

    StackElement* topElement = stack->top;
    while (topElement != NULL)
    {
        StackElement* next = topElement->next;
        free(topElement);
        topElement = next;
    }

    stack->top = NULL;
    return OK;
}

ErrorCode stackPrint(const Stack* stack)
{
    if (stack == NULL)
    {
        return NULLPointer;
    }

    StackElement* topElement = stack->top;
    while (topElement != NULL)
    {
        StackElement* next = topElement->next;
        printf("%d ", topElement->value);
        topElement = next;
    }

    return OK;
}