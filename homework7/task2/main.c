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
    while (killedNumber != NULL)
    {
        for (int i = 1; i < step; ++i)
        {
            shift(&list);
        }
        lastValue = killedNumber;
        killedNumber = pop(&list);
    }
    return lastValue;
}


bool* test(bool* testResults) {
    const int testCases[][3] = {
        {5, 2, 3},
        {10, 3, 4},
        {7, 1, 7},
        {1, 5, 1},
        {15, 4, 13}
    };
    const int numTests = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTests; i++)
    {
        int amount = testCases[i][0];
        int step = testCases[i][1];
        int expected = testCases[i][2];

        int result = findLastPeople(amount, step);
        testResults[i] = (result == expected);
    }
}

int main()
{
    bool testResults[5] = { 0 };
    test(testResults);
    for (int i = 0; i < 5; ++i)
    {
        if (!testResults[i])
        {
            printf("TEST %d FAILED\n", i);
        }
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