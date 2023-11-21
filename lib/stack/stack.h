#pragma once

typedef enum ErrorCode
{
    OK = 0,
    StackIsEmpty = -1,
    OutOfMemory = -2,
    NULLPointer = -3
} ErrorCode;

typedef struct Stack Stack;

// create stack
Stack* createStack();

// add an element to stack
ErrorCode stackPush(Stack* stack, int value);

// remove top element from stack
int stackPop(Stack* stack);

// free stack
ErrorCode stackFree(Stack* stack);

// print stack
ErrorCode stackPrint(Stack* stack);