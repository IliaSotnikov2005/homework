#pragma once
#ifndef HEADER_H
#define HEADER_H

typedef struct Stack
{
    int value;
    struct Stack* previous;
    int size;
} Stack;

//push value to stack
void push(Stack** head, const int value);

//pop value from stack
int pop(Stack** head);

//clean stack
int clean(Stack** head);

#endif