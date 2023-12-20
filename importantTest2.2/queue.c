#include "queue.h"
#include "stack.h"
#include "errorCodes.h"

#include <stdbool.h>
#include <stdlib.h>

struct Queue
{
    Stack* inputStack;
    Stack* outputStack;
};

Queue* queueCreate(void)
{
    Queue* queue = calloc(1, sizeof(Queue));
    if (queue == NULL)
    {
        return NULL;
    }

    queue->inputStack = stackCreate();
    queue->outputStack = stackCreate();
    if (queue->inputStack == NULL || queue->outputStack == NULL)
    {
        free(queue->inputStack);
        free(queue->outputStack);
        free(queue);
        return NULL;
    }

    return queue;
}

ErrorCode enqueue(const int value, Queue* queue)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }

    return stackPush(queue->inputStack, value);
}

ErrorCode dequeue(Queue* queue, int* value)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }

    if (stackIsEmpty(queue->outputStack))
    {
        while (!stackIsEmpty(queue->inputStack))
        {
            int stackValue = 0;
            stackPop(queue->inputStack, &stackValue);
            stackPush(queue->outputStack, stackValue);
        }
    }

    return stackPop(queue->outputStack, value);
}

ErrorCode queueFree(Queue** queue)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }
    if (*queue == NULL)
    {
        return nullPointerError;
    }

    stackFree(&(*queue)->inputStack);
    stackFree(&(*queue)->outputStack);
    free(*queue);

    *queue = NULL;

    return ok;
}