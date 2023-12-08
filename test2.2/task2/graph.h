#pragma once

#include <stdbool.h>

// Graph error codes
typedef enum GraphErrorCode
{
    graphOk = 0,
    graphMemoryAllocationError = -1,
    graphNullPointerError = -2,
    graphFileNotFound = -3,
    graphInvalidInput = -4,
    graphIsCreatedError = -5
} GraphErrorCode;

typedef struct Graph Graph;

// Create graph from file
GraphErrorCode graphCreateFromFile(const char const* filename, Graph** graph);

// Free graph
GraphErrorCode graphFree(Graph** graph);

// Get get a list of node neighbors
bool* graphGetNeighbours(const unsigned int node, const Graph const* graph);

// Get graph nodes count
unsigned int graphNodesCount(Graph* graph);