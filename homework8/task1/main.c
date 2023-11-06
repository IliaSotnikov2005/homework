#include "../../lib/binTree/parsingTree.h"
#include "../../lib/binTree/test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    bool* testResult = test();
    size_t testsAmount = sizeof(testResult) / 2;
    for (size_t i = 0; i < testsAmount; ++i)
    {
        if (!testResult[i])
        {
            printf("TEST %d FAILED", (int)i);
        }
    }

    Node* root = buildTreeFromFile("text.txt");
    printf("Parsing tree from file: ");
    printTree(root);
    printf("\n\nExpression value: %d", evaluate(root));
}