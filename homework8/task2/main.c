#include "../../lib/ADT-dictionary/dictionaty.h"
#include "../../lib/ADT-dictionary/testDictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    bool* testResults = test();
    for (size_t i = 0; i < sizeof(testResults) / 2; ++i)
    {
        if (!testResults[i])
        {
            printf("TEST %d FAILED\n", (int)i);
        }
    }

    Node* tree = createTree();

    printf("List of commands:\n"
        "0 - exit\n"
        "1 - add element\n"
        "2 - get element\n"
        "3 - check key exist\n"
        "4 - delete element\n");

    int command = 0;
    printf("\nEnter command: ");
    if (scanf_s("%d", &command) == NULL)
    {
        return -1;
    }

    while (command != 0)
    {
        switch (command)
        {
        case 1:
        {
            printf("\nEnter key and value:\nkey = ");
            int key = 0;
            if (scanf_s("%d", &key) == NULL)
            {
                return -1;
            }

            printf("\nValue = ");
            char* value = calloc(50, sizeof(char));
            if (scanf_s("%s", value, 50) != 1)
            {
                return -1;
            }

            createLeaf(key, value, &tree);
            break;
        }
        case 2:
        {
            printf("Enter key to find: ");
            int key = 0;
            if (scanf_s("%d", &key) == NULL)
            {
                return -1;
            }

            char value[50] = { 0 };
            strcpy(value, get(key, tree));
            printf("\nThe value of this key: %s", value);
            break;
        }
        case 3:
        {
            printf("Enter key to check for existence: ");
            int key = 0;
            if (scanf_s("%d", &key) == NULL)
            {
                return -1;
            }

            printf(isContained(key, tree) ? "\nThe key is in dictionary\n" : "\nThe key is not in dictionary");
            break;
        }
        case 4:
        {
            printf("Enter key to delete element: ");
            int key = 0;
            if (scanf_s("%d", &key) == NULL)
            {
                return -1;
            }

            deleteNode(key, &tree);
            printf("\nDeleted\n");
            break;
        }
        default:
            break;
        }
        printf("\nEnter command: ");
        if (scanf_s("%d", &command) == NULL)
        {
            return -1;
        }
    }

    freeTree(&tree);
}