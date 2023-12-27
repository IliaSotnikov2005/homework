#include "parsingTree.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int testResult = test();
    if (testResult != 0)
        {
            printf("TEST %d FAILED", testResult);
            return testResult;
    }

    Node* root = buildTreeFromFile("text.txt");
    printf("Parsing tree from file: ");
    printTree(root);
    printf("\n\nExpression value: %d", evaluate(root));
    freeTree(&root);
}
