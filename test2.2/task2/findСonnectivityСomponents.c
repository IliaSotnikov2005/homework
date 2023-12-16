#include "graph.h"
#include "find—onnectivity—omponents.h"

#include <stdlib.h>
#include <stdbool.h>

static void componentAdd(unsigned int node, int* component, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (component[i] == 0)
        {
            component[i] = node;
            break;
        }
    }
}

static void findComponent(unsigned int node, bool* visited, int** components, unsigned int componentNumber, Graph* graph)
{
    visited[node] = true;
    componentAdd(node + 1, components[componentNumber], graphNodesCount(graph));
    if (visited[node] == true)
    {   
        bool* neighbours = graphGetNeighbours(node, graph);
        for (size_t i = 0; i < graphNodesCount(graph); ++i)
        {
            if (neighbours[i])
            {
                if (!visited[i])
                {
                    findComponent(i, visited, components, componentNumber, graph);
                }
            }
        }
    }
    
}

int** find—onnectivity—omponents(const Graph const* graph)
{
    unsigned int nodesCount = graphNodesCount(graph);
    int** components = calloc(nodesCount, sizeof(int*));
    if (components == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < nodesCount; ++i)
    {
        components[i] = calloc(nodesCount, sizeof(int*));
        if (components[i] == NULL)
        {
            return NULL;
        }
    }

    bool* visited = calloc(nodesCount, sizeof(bool));
    if (visited == NULL)
    {
        return NULL;
    }

    unsigned int componentNumber = 0;

    for (size_t i = 0; i < graphNodesCount(graph); ++i)
    {
        if (!visited[i])
        {
            findComponent(i, visited, components, componentNumber, graph);
            ++componentNumber;
        }
    }

    return components;
}