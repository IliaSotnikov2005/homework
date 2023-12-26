#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct StackElement
{
    char value;
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

StackErrorCode stackPush(Stack* stack, const char value)
{
    if (stack == NULL)
    {
        return stackNullPointerError;
    }

    StackElement* newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL)
    {
        return stackMemoryAllocationError;
    }

    newElement->value = value;
    newElement->next = stack->top;
    stack->top = newElement;
    ++stack->size;

    return stackOk;
}

StackErrorCode stackPop(Stack* stack, char* value)
{
    if (stack == NULL)
    {
        return stackNullPointerError;
    }
    if (stack->top == NULL)
    {
        return stackIsEmptyError;
    }

    StackElement* topElement = stack->top;
    char stackValue = topElement->value;
    stack->top = topElement->next;

    free(topElement);

    *value = stackValue;
    --stack->size;

    return stackOk;
}

bool stackIsEmpty(const Stack* stack)
{
    if (stack == NULL)
    {
        return true;
    }

    return stack->top == NULL;
}

StackErrorCode stackFree(Stack** stack)
{
    if (stack == NULL)
    {
        return stackNullPointerError;
    }
    if (*stack == NULL)
    {
        return stackNullPointerError;
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

    return stackOk;
}

size_t stackSize(const Stack* stack)
{
    return stack != NULL ? stack->size : 0;
}

char stackTop(const Stack* stack)
{
    if (stack == NULL)
    {
        return '\0';
    }

    return stack->top != NULL ? stack->top->value : '\0';
}