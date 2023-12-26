#include "sortedList.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum ErrorCode
{
    ok = 0,
    memoryAllocationError = -1,
    invalidInput = -2
};

bool arraysIsEqual(int* array1, int* array2, size_t arraySize)
{
    for (size_t i = 0; i < arraySize; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }

    return true;
}

int test(void)
{
    SortedList* list = createSortedList();
    if (list == NULL)
    {
        return 1;
    }

    int input[5] = { 2, 1, 3, 6, 4 };
    int expected[5][5] = {{ 2 }, { 1, 2 }, { 1, 2, 3 }, { 1, 2, 3, 6 }, { 1, 2, 3, 4, 6 }};
    for (size_t i = 0; i < 5; ++i)
    {
        sortedListPush(list, input[i]);
        int* listArray = sortedListToArray(list);
        if (!arraysIsEqual(listArray, expected[i], i + 1) != 0)
        {
            free(listArray);
            sortedListFree(&list);
            return i + 1;
        }
        free(listArray);
    }

    sortedListRemove(list, 3);
    int expected1[] = {1, 2, 4, 6};
    int* listArray = sortedListToArray(list);
    if (memcmp(listArray, expected1, sizeof(expected1)) != 0)
    {
        free(listArray);
        sortedListFree(&list);
        return 6;
    }

    free(listArray);
    sortedListFree(&list);

    return 0;
}

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    SortedList* list = createSortedList();
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