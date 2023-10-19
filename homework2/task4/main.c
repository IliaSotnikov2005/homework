#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 100

int* distribute(int* array, int size)
{
    if (size <= 1)
    {
        return;
    }
    int pivot = array[0];
    int pIndex = 0, index = 0;
    for (int i = 1; i < size; ++i)
    {
        if (array[i] < pivot)
        {
            int temp = array[pIndex];
            array[pIndex] = array[i];
            array[i] = temp;
            ++pIndex;
            index = i;
        }
    }
    int temp = array[pIndex];
    array[pIndex] = pivot;
    array[index] = temp;
    return;
}

bool checkArray(int* array, int size, int number)
{
    bool isGreater = false;
    for (int i = 0; i < size; ++i)
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
    for (int i = 0; i < 3; ++i)
    {
        if (!testResult[i])
        {
            printf("TEST %d FAILED\n", i);
        }
    }

    int array[SIZE] = { 0 };
    randomIntArrayFill(array, SIZE);
    array[0] = rand();

    printf("Original array:\n");
    printIntArray(array, SIZE);

    int value = array[0];
    printf("\nThe firts number in array: %d\n", array[0]);

    distribute(array, SIZE);
    printf("\nResult:\n");
    printIntArray(array, SIZE);
}