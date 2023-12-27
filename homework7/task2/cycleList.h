#pragma once

typedef struct List List;

// create list
List* createList(void);

// add element to list
int push(List** head, int value);

// delete head element
int pop(List** head);

// free list
void deleteList(List** head);

// shift to 1 element
void shift(List** head);