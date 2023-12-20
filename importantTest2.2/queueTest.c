#include "queueTest.h"
#include "queue.h"
#include "errorCodes.h"
#include <stdlib.h>

int test(void)
{
    Queue* queue = queueCreate();
    int value = 0;

    if (dequeue(queue, &value) != -3 || value != 0)
    {
        return 1;
    }
    for (size_t i = 2; i < 10; ++i)
    {
        if (enqueue((int)i, queue) != ok)
        {
            return (int)i;
        }
    }

    int expected[] = { 2, 3, 4, 5 };
    for (size_t i = 0; i < 4; ++i)
    {
        if (dequeue(queue, &value) != ok || value != expected[i])
        {
            return (int)i + 10;
        }
    }

    for (size_t i = 14; i < 17; ++i)
    {
        if (enqueue((int)i, queue) != ok)
        {
            return (int)i;
        }
    }

    int expected2[] = { 6, 7, 8, 9, 14, 15, 16 };
    for (size_t i = 0; i < 7; ++i)
    {
        if (dequeue(queue, &value) != ok || value != expected2[i])
        {
            return (int)i + 17;
        }
    }

    if (queueFree(&queue) != ok)
    {
        return 24;
    }

    return 0;
}