#include "graph.h"
#include "../../lib/list/list.h"

#include "../../lib/list/list.h"

#include <stdlib.h>
#include <stdio.h>

struct Graph 
{
    List** towns;
    List** states;
    unsigned int townsCount;
    unsigned int numberOfStates;
    unsigned int* citiesBelonging;
};

Graph* graphCreateFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return GraphFileNotFound;
    }

    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return GraphMemoryAllocationError;
    }

    unsigned int townsCount = 0;
    fscanf_s(file, "%u", &townsCount);
    graph->townsCount = townsCount;

    unsigned int roadsCount = 0;
    fscanf_s(file, "%u", &roadsCount);

    graph->towns = calloc(townsCount, sizeof(int*));
    if (graph->towns == NULL)
    {
        return GraphMemoryAllocationError;
    }

    for (size_t i = 0; i < townsCount; ++i)
    {
        graph->towns[i] = listCreate();
    }

    for (size_t i = 0; i < roadsCount; ++i)
    {
        unsigned int town1 = 0;
        unsigned int town2 = 0;
        unsigned int roadLength = 0;

        fscanf_s(file, "%u %u %u", &town1, &town2, &roadLength);
        listPush(town1 - 1, roadLength, graph->towns[town2 - 1]);
        listPush(town2 - 1, roadLength, graph->towns[town1 - 1]);
    }

    unsigned int statesCount = 0;
    fscanf_s(file, "%u", &statesCount);
    graph->numberOfStates = statesCount;

    graph->states = calloc(graph->townsCount, sizeof(int));
    if (graph->states == NULL)
    {
        return GraphMemoryAllocationError;
    }

    for (size_t i = 0; i < statesCount; ++i)
    {
        unsigned int capital = 0;
        fscanf_s(file, "%u", &capital);
        graph->states[capital - 1] = listCreate();
    }

    return graph;
}

unsigned int graphNumberOfTowns(Graph* graph)
{
    return graph == NULL ? 0 : graph->townsCount;
}

unsigned int graphNumberOfStates(Graph* graph)
{
    return graph == NULL ? 0 : graph->numberOfStates;
}

GraphErrorCode graphAttachACity(unsigned int state, Graph* graph)
{
    if (graph == NULL)
    {
        return GraphNULLPointerError;
    }

    unsigned int cityToAttach = graph->townsCount;
    unsigned int cityToAttachRoadLength = 99999999;
    for (size_t city = 0; city < graph->townsCount; ++city)
    {
        unsigned int roadFromTownToStateLength = listFind(graph->towns[city], state);
        if (roadFromTownToStateLength != 0)
        {
            if (roadFromTownToStateLength < cityToAttachRoadLength)
            {
                cityToAttach = city;
                cityToAttachRoadLength = roadFromTownToStateLength;
            }
        }
    }
    if (cityToAttach == graph->townsCount)
    {
        return GraphCouldntAttachTheCity; // кароче надо использовать где то тут список привязанных городов, и как то надо проверятт не только кратчайший путь до столицы, но и вообще к городам страны как то так
    }

    listPush(cityToAttach, cityToAttachRoadLength, graph->states[state]);

    return GraphOK;
}

GraphErrorCode graphFree(Graph* graph)
{
    if (graph == NULL)
    {
        return GraphNULLPointerError;
    }

    listFree(graph->states);
    listFree(graph->towns);
    free(graph);
}