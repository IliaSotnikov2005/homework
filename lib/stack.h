#pragma once

typedef struct Stack Stack;

// create stack
Stack* createStack();

//push value to stack
void push(Stack** head, const int value);

//pop value from stack
char pop(Stack** head);

//clean stack
int freeStack(Stack** head);

//return stack size
int stackSize(Stack* head);

//return stack top element
int top(Stack* head);