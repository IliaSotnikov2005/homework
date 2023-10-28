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
    if ((*head) == NULL)
    {
        temp->next = temp;
        (*head) = temp;
        return 0;
    }
    List *nextOld = (*head)->next;
    (*head)->next = temp;
    temp->next = nextOld;
    (*head) = temp;
    return 0;
}

void shift(List **head)
{
    if ((*head) == NULL)
    {
        return;
    }
    (*head) = (*head)->next;
}

int pop(List** head)
{
    if ((*head) == NULL)
    {
        return NULL;
    }
    List* temp = (*head);
    while (temp->next != (*head))
    {
        temp = temp->next;
    }
    temp->next = (*head)->next;
    int headValue = (*head)->value;
    if ((*head) == temp)
    {
        free(*head);
        *head = NULL;
        return headValue;
    }
    free(*head);
    *head = temp->next;
    return headValue;
}

List* getNth(List* head, unsigned int index)
{
    while (head != NULL && index > 0)
    {
        head = head->next;
        --index;
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
    while ((*head)->next)
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

int deleteNthWithShift(List** head, int index)
{
    if (index == 0)
    {
        return pop(head);
    }
    while (index > 1)
    {
        (*head) = (*head)->next;
        --index;
    }
    return pop(head);
}