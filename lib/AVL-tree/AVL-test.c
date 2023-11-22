#include "AVL-test.h"
#include "AVL-tree.h"
#include "errorCodes.h"

#include <stdlib.h>
#include <string.h>

int test()
{
    size_t testsCount = 5;
    bool* testResults = calloc(testsCount, sizeof(bool));
    if (testResults == NULL)
    {
        return -1;
    }
    AVLTree* tree = createAVLTree();
    addElement("6", "6", tree);
    addElement("7", "7", tree);
    addElement("8", "8", tree);
    addElement("9", "9", tree);
    addElement("2", "2", tree);
    addElement("1", "1", tree);

    int* array = toArray(tree, 6);
    int expected0[] = { 1, 2, 6, 7, 8, 9 };
    testResults[0] = memcmp(expected0, array, sizeof(expected0));
    free(array);

    deleteElement("7", tree);
    array = toArray(tree, 5);
    int expected1[] = { 1, 2, 6, 8, 9 };
    testResults[1] = memcmp(expected1, array, sizeof(expected1));
    free(array);

    deleteElement("1", tree);
    array = toArray(tree, 4);
    int expected2[] = { 2, 6, 8, 9 };
    testResults[2] = memcmp(expected2, array, sizeof(expected2));
    free(array);

    char* value = get("6", tree);
    testResults[3] = strcmp(value, "6") == 0;
    free(value);

    value = get("32", tree);
    testResults[4] = value == NULL;
    free(value);

    int failedTest = -1;
    for (size_t i = 0; i < testsCount; ++i)
    {
        if (!testResults[i])
        {
            failedTest = (int)i;
            break;
        }
    }
    return failedTest;


}