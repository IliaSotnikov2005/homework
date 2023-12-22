#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

struct Stack
{
    StackElement* top;
    size_t size;
};

Stack* stackCreate(void)
{
    return calloc(1, sizeof(Stack));
}

ErrorCode stackPush(Stack* stack, const int value)
{
    if (stack == NULL)
    {
        return nullPointerError;
    }

    StackElement* newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL)
    {
        return memoryAllocationError;
    }

    newElement->value = value;
    newElement->next = stack->top;
    stack->top = newElement;
    ++stack->size;

    return ok;
}

ErrorCode stackPop(Stack* stack, int* value)
{
    if (stack == NULL)
    {
        return nullPointerError;
    }
    if (stack->top == NULL)
    {
        return stackIsEmptyError;
    }

    StackElement* topElement = stack->top;
    int stackValue = topElement->value;
    stack->top = topElement->next;

    free(topElement);

    *value = stackValue;
    --stack->size;

    return ok;
}

bool stackIsEmpty(const Stack* stack)
{
    if (stack == NULL)
    {
        return true;
    }

    return stack->top == NULL;
}

ErrorCode stackFree(Stack** stack)
{
    if (stack == NULL)
    {
        return nullPointerError;
    }
    if (*stack == NULL)
    {
        return nullPointerError;
    }

    StackElement* topElement = (*stack)->top;
    while (topElement != NULL)
    {
        StackElement* next = topElement->next;
        free(topElement);
        topElement = next;
    }

    free(*stack);
    (*stack) = NULL;

    return ok;
}

int* stackToArray(const Stack* stack)
{
    if (stack == NULL)
    {
        return NULL;
    }

    int* array = calloc(stack->size, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }

    StackElement* topElement = stack->top;
    for (size_t i = 0; i < stack->size & topElement != NULL; ++i)
    {
        array[i] = topElement->value;
        StackElement* next = topElement->next;
        topElement = next;
    }

    return array;
}

size_t stackSize(const Stack* stack)
{
    return stack != NULL ? stack->size : 0;
}