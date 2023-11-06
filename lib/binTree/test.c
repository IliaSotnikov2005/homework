#include "parsingTree.h"
#include "test.h"
#include <stdlib.h>

bool* test()
{
    char testFiles[][28] = { "../../lib/binTree/test1.txt", "../../lib/binTree/test2.txt", "../../lib/binTree/test3.txt" };
    int expected[] = { 3, 13, 1 };
    size_t testsAmount = sizeof(testFiles) / sizeof(testFiles[0]);
    bool* testResults = calloc(testsAmount, sizeof(bool));
    if (testResults == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < testsAmount; ++i)
    {
        Node* root = buildTreeFromFile(testFiles[i]);
        testResults[i] = evaluate(root) == expected[i];
        freeTree(&root);
    }

    return testResults;
}