#include "../../lib/list.h"

#include <stdio.h>
#include <stdbool.h>

int findLastPeople(const int amount, const int step)
{
    List* list = createList();
    for (int i = 0; i < amount; ++i)
    {
        push(&list, i + 1);
    }
    shift(&list);
    int lastValue = 0;
    int killedNumber = 1;
    while (killedNumber != 0)
    {
        for (int i = 1; i < step; ++i)
        {
            shift(&list);
        }
        lastValue = killedNumber;
        killedNumber = pop(&list);
    }

    deleteList(&list);
    return lastValue;
}

int test(void)
{
    const int testCases[][3] =
    {
        {5, 2, 3},
        {10, 3, 4},
        {7, 1, 7},
        {1, 5, 1},
        {15, 4, 13}
    };
    size_t numTests = 5;

    for (size_t i = 0; i < numTests; ++i)
    {
        int amount = testCases[i][0];
        int step = testCases[i][1];
        int expected = testCases[i][2];

        int result = findLastPeople(amount, step);
        if (result != expected)
        {
            return i + 1;
        }
    }

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

    printf("Enter the number of soldiers: ");
    int amount = 0;
    if (scanf_s("%d", &amount) == NULL)
    {
        printf("\nInvalid input");
        return -1;
    }

    printf("\nThe number of the person we're going to kill: ");
    int step = 0;
    if (scanf_s("%d", &step) == NULL)
    {
        printf("\nInvalid input");
        return -1;
    }

    printf("%d", findLastPeople(amount, step));
}