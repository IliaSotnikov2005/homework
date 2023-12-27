#include "graph.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Graph
{
    List** cityRoads;
    List** states;
    unsigned int citiesCount;
    unsigned int statesCount;
    bool* linkedCities;
};

Graph* graphCreateFromFile(const char const * filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }

    unsigned int citiesCount = 0;
    if (fscanf_s(file, "%u", &citiesCount) != 1)
    {
        graphFree(&graph);
        return NULL;
    }
    graph->citiesCount = citiesCount;

    graph->cityRoads = calloc(citiesCount, sizeof(int*));
    graph->linkedCities = calloc(citiesCount, sizeof(bool));

    if (graph->linkedCities == NULL || graph->cityRoads == NULL)
    {
        graphFree(&graph);
        return NULL;
    }

    for (size_t i = 0; i < citiesCount; ++i)
    {
        graph->cityRoads[i] = listCreate();
        if (graph->cityRoads[i] == NULL)
        {
            graphFree(&graph);
            return NULL;
        }
    }

    unsigned int roadsCount = 0;
    if (fscanf_s(file, "%u", &roadsCount) != 1)
    {
        graphFree(&graph);
        return NULL;
    }

    for (size_t i = 0; i < roadsCount; ++i)
    {
        unsigned int city1 = 0;
        unsigned int city2 = 0;
        unsigned int roadLength = 0;

        if (fscanf_s(file, "%u %u %u", &city1, &city2, &roadLength) != 3)
        {
            graphFree(&graph);
            return NULL;
        }
        
        listPush(city1, roadLength, graph->cityRoads[city2 - 1]);
        listPush(city2, roadLength, graph->cityRoads[city1 - 1]);
    }

    unsigned int statesCount = 0;
    if (fscanf_s(file, "%u", &statesCount) != 1)
    {
        graphFree(&graph);
        return NULL;
    }
    graph->statesCount = statesCount;

    graph->states = calloc(graph->statesCount, sizeof(int));
    if (graph->states == NULL)
    {
        graphFree(&graph);
        return NULL;
    }

    for (size_t i = 0; i < statesCount; ++i)
    {
        unsigned int capital = 0;
        if (fscanf_s(file, "%u", &capital) != 1)
        {
            graphFree(&graph);
            return NULL;
        }
        
        graph->states[i] = listCreate();
        if (graph->states[i] == NULL)
        {
            graphFree(&graph);
            return NULL;
        }

        listPush(capital, 0, graph->states[i]);
        graph->linkedCities[capital - 1] = true;
    }

    return graph;
}

unsigned int graphCitiesCount(const Graph const * graph)
{
    return graph == NULL ? 0 : graph->citiesCount;
}

unsigned int graphStatesCount(const Graph const * graph)
{
    return graph == NULL ? 0 : graph->statesCount;
}

GraphErrorCode graphLinkACity(const unsigned int stateNumber, Graph* graph)
{
    if (graph == NULL)
    {
        return GraphNULLPointerError;
    }

    List* state = graph->states[stateNumber];
    unsigned int cityToLink = 0;
    unsigned int cityToLinkRoadLength = 99999999;

    int* stateCities = NULL;
    listGetKeys(state, &stateCities);

    for (size_t i = 0; i < listSize(state); ++i)
    {
        int* citiesNearby = NULL;
        listGetKeys(graph->cityRoads[stateCities[i] - 1], &citiesNearby);
        if (citiesNearby == NULL)
        {
            return GraphMemoryAllocationError;
        }

        for (size_t j = 0; j < listSize(graph->cityRoads[stateCities[i] - 1]); ++j)
        {
            if (graph->linkedCities[citiesNearby[j] - 1] == 0)
            {
                unsigned int roadFromCityToStateLength = listFind(graph->cityRoads[stateCities[i] - 1], citiesNearby[j]);
                if (roadFromCityToStateLength != 0 && roadFromCityToStateLength < cityToLinkRoadLength)
                {
                    cityToLink = citiesNearby[j];
                    cityToLinkRoadLength = roadFromCityToStateLength;
                }
            }
        }

        free(citiesNearby);
    }
    if (cityToLink == 0)
    {
        return GraphCouldntAttachTheCity;
    }

    listPush(cityToLink, cityToLinkRoadLength, state);
    graph->linkedCities[cityToLink - 1] = true;
    
    free(stateCities);

    return GraphOK;
}

void printStates(const Graph const * graph)
{
    for (size_t i = 0; i < graph->statesCount; ++i)
    {
        printf("\nState %d", (int)(i + 1));
        printf("\nCities: ");
        listPrint(graph->states[i]);
        printf("\n");
    }
}

GraphErrorCode graphFree(Graph** graph)
{
    if (graph == NULL)
    {
        return GraphNULLPointerError;
    }

    listFree((*graph)->states);
    listFree((*graph)->cityRoads);
    free(*graph);
    *graph = NULL;

    return GraphOK;
}

bool graphCheck(const Graph* const graph, const unsigned int* states, const size_t statesCount)
{
    if (graphStatesCount(graph) != statesCount)
    {
        return false;
    }

    for (size_t i = 0; i < statesCount; ++i)
    {
        int* graphStates = NULL;
        listGetKeys(graph->states[i], &graphStates);
        return memcmp(graphStates, states, sizeof(graphStates)) == 0;
    }

    return true;
}