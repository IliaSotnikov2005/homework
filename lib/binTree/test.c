#include "parsingTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    Node* root = buildTreeFromFile("test.txt");
    printTree(root);

}
