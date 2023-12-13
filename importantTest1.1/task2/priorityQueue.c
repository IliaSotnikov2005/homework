#include "priorityQueue.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueueElement
{
    int priority;
    int value;
    struct PriorityQueueElement* next;
} PriorityQueueElement;

struct PriorityQueue
{
    PriorityQueueElement* head;
};

PriorityQueue* priorityQueueCreate()
{
    return calloc(1, sizeof(PriorityQueue));
}

PriorityQueueErrorCode priorityQueueEnqueue(const int value, const int priority, PriorityQueue* queue)
{
    if (queue == NULL)
    {
        return PriorityQueueNullPointerError;
    }

    PriorityQueueElement* newElement = calloc(1, sizeof(PriorityQueueElement));
    if (newElement == NULL)
    {
        return PriorityQueueMemoryAllocationError;
    }

    newElement->priority = priority;
    newElement->value = value;

    PriorityQueueElement* element = queue->head;
    if (element == NULL)
    {
        newElement->next = NULL;
        queue->head = newElement;
        return PriorityQueueOk;
    }

    newElement->next = queue->head;
    queue->head = newElement;

    return PriorityQueueOk;
}

int priorityQueueDequeue(PriorityQueue* queue, PriorityQueueErrorCode* errorCode)
{
    if (queue == NULL)
    {
        *errorCode = PriorityQueueNullPointerError;
        return 0;
    }
    
    
    PriorityQueueElement* maxPriorityElement = queue->head;

    PriorityQueueElement* element = queue->head;
    while (element != NULL)
    {
        if (element->priority > maxPriorityElement->next->priority)
        {
            maxPriorityElement = element;
        }
    }
    
    if (element == NULL)
    {
        return -1;
    }

    int value = element->value;
    
    

    return value;
}

void printQ(PriorityQueue* queue)
{
    PriorityQueueElement* elem = queue->head;
    while (elem != NULL)
    {
        printf("%d ", elem->value);
        elem = elem->next;
    }
    printf("\n");
}

PriorityQueueErrorCode priorityQueueFree(PriorityQueue** queue)
{
    if (*queue == NULL)
    {
        return PriorityQueueOk;
    }

    PriorityQueueElement* element = (*queue)->head;
    while (element != NULL)
    {
        PriorityQueueElement* toDelete = element;
        element = element->next;
        free(toDelete);
    }

    return PriorityQueueOk;
}
