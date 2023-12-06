#include "graph.h"
#include "distributeCities.h"
#include "test.h"

#include <stdio.h>
#include <stdbool.h>

int main()
{
    if (test() != 0)
    {
        return -33;
    }

    Graph* graph = graphCreateFromFile("cities.txt");
    if (graph == NULL)
    {
        printf("Failed to build a graph\n");
        return -1;
    }

    if (distributeCities(graph) != 0)
    {
        return -2;
    }
    printStates(graph);
    graphFree(&graph);
}