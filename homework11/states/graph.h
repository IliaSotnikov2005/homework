#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Graph error codes
typedef enum GraphErrorCode
{
    GraphOK = 0,
    GraphMemoryAllocationError = -1,
    GraphNULLPointerError = -2,
    GraphFileNotFound = -3,
    GraphCouldntAttachTheCity = -4
} GraphErrorCode;

typedef struct Graph Graph;

// Create graph from file
Graph* graphCreateFromFile(const char const * filename);

// Get cities count
unsigned int graphCitiesCount(const Graph const * graph);

// Get states count
unsigned int graphStatesCount(const Graph const * graph);

// Link a nearest city to state
GraphErrorCode graphLinkACity(const unsigned int state, Graph* graph);

// Print states
void printStates(const Graph const * graph);

// Free graph
GraphErrorCode graphFree(Graph** graph);

// Check graph with your data
bool graphCheck(const Graph* const graph, const unsigned int* states, const size_t statesCount);