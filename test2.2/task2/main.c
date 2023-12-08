#include "graph.h"
#include "find—onnectivity—omponents.h"

#include <stdio.h>

bool test()
{
    Graph* graph = NULL;
    int error = graphCreateFromFile("graphTest.txt", &graph);
    if (error != graphOk)
    {
        return -1;
    }
    int** components = find—onnectivity—omponents(graph);
    int expected[4][4] = { {1, 2, 3}, {4} };
    for (size_t i = 0; i < graphNodesCount(graph); ++i)
    {
        for (size_t j = 0; j < graphNodesCount(graph); ++j)
        {
            if (components[i][j] != expected[i][j])
            {
                for (size_t k = i; k < graphNodesCount(graph); ++k)
                {
                    free(components[k]);
                }
                free(components);
                return -2;
            }
        }
        free(components[i]);
    }
    free(components);

    graphFree(&graph);
    return 0;
}

int main()
{
    if (test() != 0)
    {
        printf("TEST FAILED");
        return -1;
    }

    Graph* graph = NULL;
    int error = graphCreateFromFile("graph.txt", &graph);
    if (error != graphOk)
    {
        printf("Error %d", error);
        return -1;
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