#include "AVL-test.h"
#include "AVL-tree.h"
#include "errorCodes.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
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
                   
            char* key = (char*)calloc(100, sizeof(char));
            char* value = (char*)calloc(100, sizeof(char));
            if (key == NULL || value == NULL)
            {
                free(key);
                free(value);
                freeAVLTree(tree);
                printf("Memory allocation error");
                return MemoryAllocationError;
            }

            printf("\nEnter a key: ");
            if (scanf_s("%s", key, 100) == 0)
            {
                free(key);
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            printf("Enter a value: ");
            if (scanf_s("%s", value, 100) == 0)
            {
                free(key);
                freeAVLTree(tree);
                printf("Invalid input");
                return InvalidInput;
            }

            if (addElement(key, value, tree) == MemoryAllocationError)
            {
                printf("Memory allocation error");
                return MemoryAllocationError;
            }
            break;
        }
        case 2:
        {
            printf("\nEnter key to find value: ");
            char* key = calloc(100, sizeof(char));
            if (key == NULL)
            {
                printf("Memory allocation error");
                return MemoryAllocationError;
            }
            if (scanf_s("%s", key) == 0)
            {
                printf("Invalid input");
                return InvalidInput;
            }

            char* result = get(key, tree);
            printf(result ? "\nResult: %s\n" : "\n%s is not in dictionary\n", result ? result : key);

            free(key);
            break;
        }
        case 3:
        {
            printf("Enter the key to verify that it is inside: ");
            char* key = calloc(100, sizeof(char));
            if (key == NULL)
            {
                printf("Memory allocation error");
                return MemoryAllocationError;
            }
            if (scanf_s("%s", key) == 0)
            {
                printf("Invalid input");
                return InvalidInput;
            }

            char* result = get(key, tree);
            printf(result ? "\nKey is inside\n" : "\nKey is not inside\n");

            free(key);
            break;
        }
        case 4:
            printf("\nEnter the key to delete element: ");
            char* key = calloc(100, sizeof(char));
            if (key == NULL)
            {
                printf("Memory allocation error");
                return MemoryAllocationError;
            }
            if (scanf_s("%s", key) == 0)
            {
                printf("Invalid input");
                return InvalidInput;
            }

            deleteElement(key, tree);
            printf("\nSuccessful\n");

            free(key);
            break;

        default:
           break;
        }
        printf("\nEnter your command: ");
        if (scanf_s("%d", &command) == 0)
        {
            freeAVLTree(tree);
            printf("\nInvalid input\n");
            return InvalidInput;
        }
    }

    return 0;
}