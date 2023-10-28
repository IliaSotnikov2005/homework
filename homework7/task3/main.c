#include "../../lib/list.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkResult(List* list, int* correct, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (getNth(list, i) != correct[i])
        { }
    }
}

bool* test(bool* testResults)
{
    List* list = createList();
    push(&list, 7);
    int correct[] = { 7 };
    int* listArray = toArray(list);
    testResults[0] = memcmp(listArray, correct, sizeof(correct)) == 0;

    push(&list, 1);
    int correct1[] = {1, 7};
    listArray = toArray(list);
    testResults[1] = memcmp(listArray, correct1, sizeof(correct1)) == 0;

    push(&list, 5);
    int correct2[] = { 1, 5, 7 };
    listArray = toArray(list);
    testResults[2] = memcmp(listArray, correct2, sizeof(correct2)) == 0;

    push(&list, 9);
    int correct3[] = { 1, 5, 7, 9 };
    listArray = toArray(list);
    testResults[3] = memcmp(listArray, correct3, sizeof(correct3)) == 0;

    deleteNth(&list, 1);
    int correct4[] = { 1, 7, 9 };
    listArray = toArray(list);
    testResults[4] = memcmp(listArray, correct4, sizeof(correct4)) == 0;

    deleteList(&list);
}

int main()
{
    bool testResults[5] = {0};
    test(testResults);
    for (int i = 0; i < 5; ++i)
    {
        if (!testResults[i])
        {
            printf("TEST %d FAILED\n", i);
        }
    }

    List* list = createList();
    printf("List of commands:\n0 - exit\n1 - add element to list\n2 - delete element\n3 - print list\n");
    printf("Enter your command: ");
    int number = 0;
    if (scanf_s("%d", &number) == NULL)
    {
        printf("Invalid input");
        return -1;
    }
    while (number != 0)
    {
        switch (number)
        {
        case 1:
        {
            printf("\nEnter the value to add: ");
            int value = 0;
            if (scanf_s("%d", &value) == NULL)
            {
                printf("Invalid input");
                return -1;
            }
            push(&list, value);
            break;
        }
        case 2:
        {
            printf("\nEnter the index of the item to delete: ");
            int index = 0;
            if (scanf_s("%d", &index) == NULL)
            {
                return -1;
            }
            deleteNth(&list, index);
            break;
        }
        case 3:
        {
            printf("\nPrint the list: ");
            printList(list);
            break;
        }
        default:
        {
            break;
        }
        }
        printf("\nEnter your command: ");
        if (scanf_s("%d", &number) == NULL)
        {
            printf("Invalid input");
            return -1;
        }
    }
    deleteList(&list);
    printf("\nGood bye");
}