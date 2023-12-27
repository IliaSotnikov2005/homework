#include "parsingTree.h"
#include "test.h"
#include <stdlib.h>

int test(void)
{
    char testFiles[][28] = { "test1.txt", "test2.txt", "test3.txt" };
    int expected[] = { 3, 13, 1 };
    size_t testsAmount = 3;

    for (size_t i = 0; i < testsAmount; ++i)
    {
        Node* root = buildTreeFromFile(testFiles[i]);
        if (evaluate(root) != expected[i])
        {
            freeTree(&root);
            return i + 1;
        }

        freeTree(&root);
    }

    return 0;
}