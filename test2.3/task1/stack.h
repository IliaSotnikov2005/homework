#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Error codes
typedef enum ErrorCode
{
    ok = 0,
    memoryAllocationError = -1,
    nullPointerError = -2,
    stackIsEmptyError = -3,
} ErrorCode;

typedef struct Stack Stack;

// Create stack
Stack* stackCreate(void);

// Add an element to stack
ErrorCode stackPush(Stack* stack, const int value);

// Remove top element from stack
ErrorCode stackPop(Stack* stack, int* value);

// Check if stack is empty
bool stackIsEmpty(Stack* stack);

// Free stack
ErrorCode stackFree(Stack** stack);

// Get array from stack
int* stackToArray(const Stack* stack);

// Get stack size
size_t stackSize(const Stack* stack);