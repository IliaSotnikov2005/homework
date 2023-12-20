#include "queue.h"
#include "queueTest.h"

#include <stdio.h>

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    int value = 0;
    Queue* queue = queueCreate();

    enqueue(1, queue);
    enqueue(2, queue);
    enqueue(3, queue);
    enqueue(4, queue);
    enqueue(5, queue);
    enqueue(6, queue);
    enqueue(7, queue);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    enqueue(1, queue);
    enqueue(2, queue);
    enqueue(3, queue);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);
    dequeue(queue, &value);
    printf("%d", value);

    queueFree(&queue);
    return;
}