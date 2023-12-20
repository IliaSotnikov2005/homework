#pragma once

#include "errorCodes.h"

typedef struct Queue Queue;

// Create queue
Queue* queueCreate(void);

// Add element to queue
ErrorCode enqueue(const int value, Queue* queue);

// Delete element from queue
ErrorCode dequeue(Queue* queue, int* value);

// Free queue
ErrorCode queueFree(Queue** queue);