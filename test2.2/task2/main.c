#include "graph.h"
#include "find—onnectivity—omponents.h"

#include <stdio.h>

int main()
{
    Graph* graph = NULL;
    int error = graphCreateFromFile("graph.txt", &graph);
    if (error != graphOk)
    {
        printf("No %d", error);
    }
    int** components = find—onnectivity—omponents(graph);
    for (size_t i = 0; i < graphNodesCount(graph); ++i)
    {
        if (components[i][0] == 0)
        {
            continue;
        }
        printf("Component %d: ", (int)i);
        for (size_t j = 0; j < graphNodesCount(graph); ++j)
        {
            if (components[i][j] == 0)
            {
                continue;
            }
            printf("%d ", components[i][j]);
        }
        printf("\n");
        free(components[i]);
    }
    free(components);

    graphFree(&graph);
}