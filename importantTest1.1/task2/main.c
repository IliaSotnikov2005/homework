#include "priorityQueue.h"

#include <stdio.h>

int main()
{
    PriorityQueue* queue = priorityQueueCreate();
    priorityQueueEnqueue(1, 1, queue);
    priorityQueueEnqueue(5, 5, queue);
    priorityQueueEnqueue(3, 3, queue);
    priorityQueueEnqueue(4, 1, queue);
    priorityQueueFree(queue);
    
}