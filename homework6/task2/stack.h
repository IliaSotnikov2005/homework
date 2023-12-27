#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Stack error codes.
typedef enum StackErrorCode
{
    stackOk = 0,
    stackMemoryAllocationError = -1,
    stackNullPointerError = -2,
    stackIsEmptyError = -3,
} StackErrorCode;

typedef struct Stack Stack;

// Create stack.
Stack* stackCreate(void);

// Add an element to stack.
StackErrorCode stackPush(Stack* stack, const char value);

// Remove top element from stack.
StackErrorCode stackPop(Stack* stack, char* value);

// Check if stack is empty.
bool stackIsEmpty(const Stack* stack);

// Free stack.
StackErrorCode stackFree(Stack** stack);

// Get stack size.
size_t stackSize(const Stack* stack);