#include "list.h"
#include <stdlib.h>

struct List
{
    int value;
    List* next;
    
};

List* createList()
{
    List* list = malloc(sizeof(List));
    list = NULL;

    return list;
}

int push(List** head, int value)
{
    List* temp = malloc(sizeof(List));

    if (temp == NULL)
    {
        return -1;
    }
    temp->value = value;
    List* node = (*head);
    List* previous = NULL;
    if ((*head) == NULL)
    {
        temp->next = (*head);
        (*head) = temp;
        return 0;
    }
    while (value > node->value)
    {
        previous = node;
        node = node->next;
        if (node == NULL)
        {
            previous->next = temp;
            temp->next = NULL;
            return 0;
        }
    }
    if (previous == NULL)
    {
        temp->next = (*head);
        (*head) = temp;
        return 0;
    }
    temp->next = node;
    previous->next = temp;
    return 0;
}

int pop(List** head)
{
    if ((*head) == NULL)
    {
        return NULL;
    }
    List* temp = (*head);
    (*head) = (*head)->next;
    int tempValue = temp->value;
    free(temp);

    return tempValue;
}

List* getNth(List* head, unsigned int index)
{
    while (head != NULL && index > 0)
    {
        head = head->next;
        --index;
    }
    if (index != 0)
    {
        return NULL;
    }
    return head;
}

List* getLast(List* head)
{
    if (head == NULL)
    {
        return NULL;
    }
    while (head->next)
    {
        head = head->next;
    }

    return head;
}

int pushBack(List* head, int value)
{
    List *last = getLast(head);
    List* temp = malloc(sizeof(List));

    if (temp == NULL)
    {
        return -1;
    }
    temp->value = value;
    temp->next = NULL;
    last->next = temp;

    return 0;
}

int deleteNth(List** head, int index)
{
    if (index == 0)
    {
        return pop(head);
    }
    List* previous = getNth(*head, index - 1);
    if (previous == NULL)
    {
        return NULL;
    }
    List* element = previous->next;
    if (element == NULL)
    {
        return NULL;
    }

    int trashValue = element->value;
    previous->next = element->next;

    free(element);
    return trashValue;
}

void deleteList(List** head)
{
    List* previous = NULL;
    while (*head)
    {
        previous = (*head);
        *head = (*head)->next;
        free(previous);
    }
    free(*head);
}

void printList(const List* head)
{
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int length(List *head)
{
    int counter = 0;
    while (head)
    {
        ++counter;
        head = head->next;
    }
    return counter;
}


int* toArray(const List* head)
{
    int size = length(head);
    int* values = calloc(size, sizeof(int));
    if (values == NULL)
    {
        return -1;
    }
    int i = 0;
    while (head)
    {
        values[i] = head->value;
        ++i;
        head = head->next;
    }
    return values;
}