#include "graph.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Graph
{
    bool** adjacencyMatrix;
    unsigned int nodesCount;
};

static GraphErrorCode graphFillFromFile(const FILE const* file, Graph* graph)
{
    unsigned int edgesCount = 0;
    if (fscanf_s(file, "%u", &edgesCount) != 1)
    {
        return graphInvalidInput;
    }

    for (size_t i = 0; i < edgesCount; ++i)
    {
        unsigned int node1 = 0;
        unsigned int node2 = 0;
        if (fscanf_s(file, "%u %u", &node1, &node2) != 2)
        {
            return graphInvalidInput;
        }

        graph->adjacencyMatrix[node1 - 1][node2 - 1] = true;
        graph->adjacencyMatrix[node2 - 1][node1 - 1] = true;
    }

    return graphOk;
}

GraphErrorCode graphFree(Graph** graph)
{
    if (graph == NULL)
    {
        return graphNullPointerError;
    }
    if (*graph == NULL)
    {
        return graphOk;
    }

    for (size_t i = 0; i < (*graph)->nodesCount; ++i)
    {
        free((*graph)->adjacencyMatrix[i]);
    }
    free((*graph)->adjacencyMatrix);
    free(*graph);

    *graph = NULL;

    return graphOk;
}

GraphErrorCode graphCreateFromFile(const char const* filename, Graph** graph)
{
    if (graph == NULL)
    {
        return graphNullPointerError;
    }

    if (*graph != NULL)
    {
        return graphIsCreatedError;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return graphFileNotFound;
    }

    unsigned int nodesCount = 0;
    if (fscanf_s(file, "%u", &nodesCount) != 1)
    {
        return graphInvalidInput;
    }

    Graph* newGraph = calloc(1, sizeof(Graph));
    if (newGraph == NULL)
    {
        return graphMemoryAllocationError;
    }

    newGraph->nodesCount = nodesCount;

    newGraph->adjacencyMatrix = calloc(nodesCount, sizeof(int**));
    if (newGraph->adjacencyMatrix == NULL)
    {
        free(newGraph);
        return graphMemoryAllocationError;
    }
    for (size_t i = 0; i < nodesCount; ++i)
    {
        newGraph->adjacencyMatrix[i] = calloc(nodesCount, sizeof(int));
    }

    GraphErrorCode errorCode = graphFillFromFile(file, newGraph);
    if (errorCode != graphOk)
    {
        graphFree(&newGraph);
        return errorCode;
    }
    fclose(file);

    *graph = newGraph;

    return graphOk;
}

unsigned int graphNodesCount(Graph* graph)
{
    return graph == NULL ? 0 : graph->nodesCount;
}

bool* graphGetNeighbours(const unsigned int node, const Graph const* graph)
{
    return graph == NULL ? NULL : graph->adjacencyMatrix[node];
}