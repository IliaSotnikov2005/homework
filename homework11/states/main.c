#include "graph.h"

#include <stdio.h>
#include <stdbool.h>

int distributeCities(Graph* graph)
{
    if (graph == NULL)
    {
        return - 1;
    }

    unsigned int remained = graphNumberOfTowns(graph) - graphNumberOfStates(graph);
    unsigned int state = 0;
    while (remained != 0)
    {
        if (graphAttachACity(state, graph)== GraphOK);
        {
            --remained;
        }
        state = (state + 1) % graphNumberOfStates(graph);
    }

    return 0;
}

int main()
{
    Graph* graph = graphCreateFromFile("cities.txt");
    if (graph == NULL)
    {
        return -1;
    }

    if (distributeCities(graph) != 0)
    {
        return -2;
    }

    graphFree(graph);
    return;
}