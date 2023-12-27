#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE 100

void distribute(int* array, const size_t size)
{
    if (size <= 1)
    {
        return;
    }

    int separator = array[0];
    int correctSeparatorPosition = 0;
    size_t separatorPosition = 0;
    for (size_t i = 1; i < size; ++i)
    {
        if (array[i] < separator)
        {
            int temp = array[correctSeparatorPosition];
            array[correctSeparatorPosition] = array[i];
            array[i] = temp;
            ++correctSeparatorPosition;
            separatorPosition = i;
        }
    }
    int temp = array[correctSeparatorPosition];
    array[correctSeparatorPosition] = separator;
    array[separatorPosition] = temp;
}

bool checkArray(const int* array, const size_t size, const int number)
{
    bool isGreater = false;
    for (size_t i = 0; i < size; ++i)
    {
        if (array[i] == number)
        {
            isGreater = true;
        }
        if (isGreater != (array[i] >= number))
        {
            return false;
        }
    }
    return true;
}

void testDistribute(bool *testResult)
{
    int array1[] = { 5, 3, 8, 2, 9 };
    distribute(array1, 5);
    testResult[0] = checkArray(array1, 5, 5);

    int array2[] = { 4, 4, 2, 6, 1, 5 };
    distribute(array2, 6);
    testResult[1] = checkArray(array2, 6, 4);

    int array3[] = { 1 };
    distribute(array3, 1);
    testResult[2] = checkArray(array3, 1, 1);
}

int main()
{
    bool testResult[3] = { 0 };
    testDistribute(testResult);
    for (size_t i = 0; i < 3; ++i)
    {
        if (!testResult[i])
        {
            printf("TEST %d FAILED\n", (int)i);
        }
    }

    int array[ARRAY_SIZE] = { 0 };
    randomIntArrayFill(array, ARRAY_SIZE);
    array[0] = rand();

    printf("Original array:\n");
    printIntArray(array, ARRAY_SIZE);

    printf("\nThe firts number in array: %d\n", array[0]);

    distribute(array, ARRAY_SIZE);
    printf("\nResult:\n");
    printIntArray(array, ARRAY_SIZE);
}