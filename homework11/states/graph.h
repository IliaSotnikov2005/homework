#pragma once

#include "../../lib/list/list.h"

typedef enum GraphErrorCode
{
    GraphOK = 0,
    GraphMemoryAllocationError = -1,
    GraphNULLPointerError = -2,
    GraphFileNotFound = -3,
    GraphCouldntAttachTheCity = -4
} GraphErrorCode;


typedef struct Graph Graph;

Graph* graphCreateFromFile(const char* filename);

unsigned int graphNumberOfTowns(Graph* graph);

unsigned int graphNumberOfStates(Graph* graph);

GraphErrorCode graphAttachACity(unsigned int state, Graph* graph);

GraphErrorCode graphFree(Graph* graph);