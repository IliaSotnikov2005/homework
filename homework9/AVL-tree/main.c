#include "../../lib/AVL-tree/AVL-tree.h"
#include "../../lib/AVL-tree/AVL-test.h"
#include "../../lib/AVL-tree/errorCodes.h"

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100

int main()
{
    int failedTest = test();
    if (failedTest != -1)
    {
        printf("TEST %d FAILED\n", failedTest);
        return failedTest;
    }

    AVLTree* tree = createAVLTree();

    printf("List of commands:\n"
        "1 - add new element\n"
        "2 - get element by key\n"
        "3 - check element existence\n"
        "4 - delete element from tree\n\n");

    printf("Enter your command: ");

    int command = 0;
    if (scanf_s("%d", &command) == 0)
    {
        freeAVLTree(tree);
        printf("\nInvalid input\n");
        return InvalidInput;
    }

    while (command != 0)
    {
        switch (command)
        {
        case 1:
        {
            printf("\nAdding a new element");

            char key[LENGTH] = { 0 };
            char value[LENGTH] = { 0 };

            printf("\nEnter a key: ");
            if (scanf_s("%s", key, LENGTH) == 0)
            {
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            printf("Enter a value: ");
            if (scanf_s("%s", value, LENGTH) == 0)
            {
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            if (addElement(key, value, tree) == MemoryAllocationError)
            {
                freeAVLTree(tree);
                printf("Memory allocation error");
                return MemoryAllocationError;
            }
            break;
        }
        case 2:
        {
            printf("\nEnter key to find value: ");
            char key[LENGTH] = { 0 };
            if (scanf_s("%s", key, LENGTH) == 0)
            {
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            char* result = get(key, tree);
            printf(result ? "\nResult: %s\n" : "\n%s is not in dictionary\n", result ? result : key);

            break;
        }
        case 3:
        {
            printf("Enter the key to verify that it is inside: ");
            char key[LENGTH] = { 0 };
            if (scanf_s("%s", key, LENGTH) == 0)
            {
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            char* result = get(key, tree);
            printf(result ? "\nKey is inside\n" : "\nKey is not inside\n");

            break;
        }
        case 4:
        {
            printf("\nEnter the key to delete element: ");
            char key[LENGTH] = { 0 };
            if (scanf_s("%s", key, LENGTH) == 0)
            {
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            deleteElement(key, tree);
            printf("\nSuccessful\n");

            break;
        }
        default:
        {
            break;
        }
        }
        printf("\nEnter your command: ");
        if (scanf_s("%d", &command) == 0)
        {
            freeAVLTree(tree);
            printf("\nInvalid input\n");
            return InvalidInput;
        }
    }

    freeAVLTree(tree);
    return 0;
}