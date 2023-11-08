#include "dictionaty.h"
#include "testDictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool* test()
{
    bool* testResults = calloc(30, sizeof(bool));
    Node* tree = createTree();

    createLeaf(10, "a", &tree);
    int* array = toArray(tree, 1);
    int expected0[] = { 10 };
    testResults[0] = memcmp(expected0, array, sizeof(expected0)) == 0;
    free(array);

    createLeaf(4, "b", &tree);
    array = toArray(tree, 2);
    int expected1[] = { 4, 10 };
    testResults[1] = memcmp(expected1, array, sizeof(expected1)) == 0;
    free(array);

    createLeaf(12, "c", &tree);
    array = toArray(tree, 3);
    int expected2[] = { 4, 10, 12 };
    testResults[2] = memcmp(expected2, array, sizeof(expected2)) == 0;
    free(array);

    createLeaf(6, "d", &tree);
    array = toArray(tree, 4);
    int expected3[] = { 4, 6, 10, 12 };
    testResults[3] = memcmp(expected3, array, sizeof(expected3)) == 0;
    free(array);

    createLeaf(1, "e", &tree);
    array = toArray(tree, 5);
    int expected4[] = { 1, 4, 6, 10, 12 };
    testResults[4] = memcmp(expected4, array, sizeof(expected4)) == 0;
    free(array);
    
    createLeaf(18, "f", &tree);
    array = toArray(tree, 6);
    int expected5[] = { 1, 4, 6, 10, 12, 18 };
    testResults[5] = memcmp(expected5, array, sizeof(expected5)) == 0;
    free(array);

    testResults[6] = isContained(12, tree);
    testResults[7] = !isContained(44, tree);

    testResults[8] = strcmp("a", get(10, tree)) == 0;

    deleteNode(1, &tree);
    array = toArray(tree, 5);
    int expected6[] = { 4, 6, 10, 12, 18 };
    testResults[9] = memcmp(expected6, array, sizeof(expected6)) == 0;
    free(array);

    deleteNode(10, &tree);
    array = toArray(tree, 4);
    int expected7[] = { 4, 6, 12, 18 };
    testResults[10] = memcmp(expected7, array, sizeof(expected7)) == 0;
    free(array);

    freeTree(&tree);
    return testResults;
}