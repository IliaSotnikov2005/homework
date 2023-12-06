#include "test.h"
#include "graph.h"
#include "distributeCities.h"

#include<stdlib.h>
#include<stdbool.h>

static bool testCase(const char* const filename, const unsigned int* testStates, const size_t statesCount)
{
    Graph* graph = graphCreateFromFile(filename);
    if (graph == NULL)
    {
        return false;
    }

    distributeCities(graph);

    bool testResult = graphCheck(graph, testStates, statesCount);
    graphFree(&graph);

    return testResult;
}

int test()
{
    if (testCase("test1.txt", NULL, 0))
    {
        return -1;
    }

    unsigned int testStates2[2][3] = { {3, 2, 1}, {5, 4, 0} };
    if (!testCase("test2.txt", &testStates2[0][0], 2))
    {
        return -2;
    }

    return 0;
}