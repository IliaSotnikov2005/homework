#pragma once

#include "errorCodes.h"

#include <stdbool.h>

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