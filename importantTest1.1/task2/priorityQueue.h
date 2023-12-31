#pragma once

typedef enum PriorityQueueErrorCode
{
    PriorityQueueOk = 0,
    PriorityQueueMemoryAllocationError = -1,
    PriorityQueueNullPointerError = -2,
    PriorityQueueIsEmpty = -3
} PriorityQueueErrorCode;

typedef struct PriorityQueue PriorityQueue;

// create priority queue
PriorityQueue* priorityQueueCreate();

// add element to priority queue
PriorityQueueErrorCode priorityQueueEnqueue(const int value, const int priority, PriorityQueue* queue);

// delete element from priority queue
PriorityQueueErrorCode priorityQueueDequeue(PriorityQueue* queue);

// free priority queue
PriorityQueueErrorCode priorityQueueFree(PriorityQueue * *queue);

void printQ(PriorityQueue* queue);
