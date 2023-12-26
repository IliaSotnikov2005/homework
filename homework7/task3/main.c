#include "list.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum ErrorCode
{
    ok = 0,
    memoryAllocationError = -1,
    invalidInput = -2
};

int main()
{
    // do tests

    SortedList* list = createList();
    if (list == NULL)
    {
        printf("Memory allocation error");
        return memoryAllocationError;
    }

    printf("List of commands:\n"
           "0 - exit\n"
           "1 - add element to list\n"
           "2 - delete element\n"
           "3 - print list\n");

    int command = -1;

    while (command != 0)
    {
        printf("Enter your command: ");
        if (scanf_s("%d", &command) == 0)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        switch (command)
        {
        case 1:
        {
            printf("\nAdding a value to sorted list:\n");
            printf("\nEnter the value to add: ");

            int value = 0;
            if (scanf_s("%d", &value) == 0)
            {
                printf("Invalid input");
                return invalidInput;
            }

            sortedListPush(list, value);

            break;
        }
        case 2:
        {
            printf("\nRemoving the value:\n");
            printf("\nEnter the value to delete: ");

            int value = 0;
            if (scanf_s("%d", &value) == 0)
            {
                return invalidInput;
            }

            sortedListRemove(list, value);

            printf("\nSuccess\n");
            break;
        }
        case 3:
        {
            printf("\nContents of the sorted list: ");
            sortedListPrint(list);
            break;
        }
        default:
        {
            printf("\nUnknown command\n");
            break;
        }
        }
    }

    sortedListFree(&list);
    printf("\nGood bye");
}