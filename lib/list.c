#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct List
{
    char* name;
    char* phoneNumber;
    List* next;
    
};

List* createList()
{
    List* list = malloc(sizeof(List));
    list = NULL;

    return list;
}

int push(List** head, char* name, char* phoneNumber)
{
    List* temp = malloc(sizeof(List));

    if (temp == NULL)
    {
        return -1;
    }
    temp->name = calloc(strlen(name), sizeof(char));
    if (temp->name == NULL)
    {
        return -1;
    }
    strcpy(temp->name, name);
    temp->phoneNumber = calloc(strlen(phoneNumber), sizeof(char));
    if (temp->phoneNumber == NULL)
    {
        return -1;
    }
    strcpy(temp->phoneNumber, phoneNumber);
    temp->next = (*head);
    (*head) = temp;

    return 0;
}

List* listFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }
    List* list = createList();

    char buffer[100] = { 0 };
    while (fgets(buffer, 100, file) != NULL)
    {
        char* name = strtok(buffer, " -");
        char* phoneNumber = strtok(NULL, "-");
        push(&list, name, phoneNumber);
    }

    fclose(file);
    return list;
}

void splitList(List* source, List** firstPart, List** secondPart)
{
    List* slow = source;
    List* fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *firstPart = source;
    *secondPart = slow->next;
    slow->next = NULL;
}

List* mergeLists(List* firstPart, List* secondPart, const int sortType)
{
    List* result = NULL;

    if (firstPart == NULL)
    {
        return secondPart;
    }
    if (secondPart == NULL)
    {
        return firstPart;
    }

    if (sortType == 1)
    {
        if (strcmp(firstPart->name, secondPart->name) < 0)
        {
            result = firstPart;
            result->next = mergeLists(firstPart->next, secondPart, sortType);
        }
        else
        {
            result = secondPart;
            result->next = mergeLists(firstPart, secondPart->next, sortType);
        }
    }
    else if (sortType == 2)
    {
        if (strcmp(firstPart->phoneNumber, secondPart->phoneNumber) < 0)
        {
            result = firstPart;
            result->next = mergeLists(firstPart->next, secondPart, sortType);
        }
        else
        {
            result = secondPart;
            result->next = mergeLists(firstPart, secondPart->next, sortType);
        }
    }
    return result;
}

int mergeSort(List** head, const int sortType)
{
    if (sortType != 1 || sortType != 2)
    {
        return -1;
    }
    if (((*head) == NULL) || ((*head)->next == NULL))
    {
        return -1;
    }

    List* firstPart;
    List* secondPart;
    splitList(*head, &firstPart, &secondPart);

    mergeSort(&firstPart, sortType);
    mergeSort(&secondPart, sortType);

    (*head) = mergeLists(firstPart, secondPart, sortType);
    return 0;
}

void deleteList(List** head)
{
    if ((*head) == NULL)
    {
        free(*head);
    }
    List* previous = NULL;
    while ((*head)->next)
    {
        previous = (*head);
        *head = (*head)->next;
        free(previous->name);
        free(previous->phoneNumber);
        free(previous);
    }
    free((*head)->name);
    free((*head)->phoneNumber);
    free(*head);
}

void printList(const List* head)
{
    while (head) {
        printf("%s -%s", head->name, head->phoneNumber);
        head = head->next;
    }
    printf("\n");
}

