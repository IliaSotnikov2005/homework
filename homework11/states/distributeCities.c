#include "distributeCities.h"
#include "graph.h"

#include <stdlib.h>

int distributeCities(Graph* graph)
{
    if (graph == NULL)
    {
        return -1;
    }

    unsigned int remained = graphCitiesCount(graph) - graphStatesCount(graph);
    unsigned int state = 0;
    while (remained != 0)
    {
        if (graphLinkACity(state, graph) == GraphOK);
        {
            --remained;
        }
        state = (state + 1) % graphStatesCount(graph);
    }

    return 0;
}