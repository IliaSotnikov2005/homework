#include "../../lib/functions.h"
#include <stdio.h>
#include  <time.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000

void sortingByCounting(int* array, int size)
{
    int max = array[0];
    int min = array[0];

    for (int i = 0; i < size; ++i)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
        if (array[i] < min)
        {
            min = array[i];
        }
    }

    if (min < 0)
    {
        min = -min;
    }
    else
    {
        min = 0;
    }

    int* countingArray = calloc(max + min + 1, sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        ++countingArray[array[i] + min];
    }

    int index = 0;
    for (int i = 0; i < max + min + 1; ++i)
    {
        for (int j = 0; j < countingArray[i]; ++j)
        {
            array[index] = i - min;
            ++index;
        }
    }
    free(countingArray);
}

void bubbleSorting(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int testBubble(void)
{
    int array1[] = { 3, 7, 1, 9, 2 };
    int array1c[] = { 1, 2, 3, 7, 9 };
    bubbleSorting(array1, 5);
    if (memcmp(array1, array1c, sizeof(array1)) != 0)
    {
        return -1;
    }

    int array2[] = { -5, 0, 10, -2, 7 };
    int array2c[] = { -5, -2, 0, 7, 10 };
    bubbleSorting(array2, 5);
    if (memcmp(array2, array2c, sizeof(array2)) != 0)
    {
        return -1;
    }

    int array3[] = { 5, 5, 5, 5, 5 };
    int array3c[] = { 5, 5, 5, 5, 5 };
    bubbleSorting(array3, 5);
    if (memcmp(array3, array3c, sizeof(array3)) != 0)
    {
        return -1;
    }
    return 1;
}

int testCounting(void)
{
    int array1[] = { 3, 7, 1, 9, 2 };
    int array1c[] = { 1, 2, 3, 7, 9 };
    sortingByCounting(array1, 5);
    if (memcmp(array1, array1c, sizeof(array1)) != 0)
    {
        return -1;
    }

    int array2[] = { -5, 0, 10, -2, 7 };
    int array2c[] = { -5, -2, 0, 7, 10 };
    sortingByCounting(array2, 5);
    if (memcmp(array2, array2c, sizeof(array2)) != 0)
    {
        return -1;
    }

    int array3[] = { 5, 5, 5, 5, 5 };
    int array3c[] = { 5, 5, 5, 5, 5 };
    sortingByCounting(array3, 5);
    if (memcmp(array3, array3c, sizeof(array3)) != 0)
    {
        return -1;
    }
    return 1;
}

int main()
{
    if (testBubble() == -1 || testCounting() == -1)
    {
        return -1;
    }

    printf("Now the algorithms are sorting the array, please wait\n\n");

    int array1[ARRAY_SIZE] = { 0 };
    int array2[ARRAY_SIZE] = { 0 };
    randomIntArrayFill(array1, ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        array2[i] = array1[i];
    }

    clock_t start = clock();
    bubbleSorting(array1, ARRAY_SIZE);
    clock_t end = clock();
    float bubbleSortingRuntime = end - start;

    start = clock();
    sortingByCounting(array2, ARRAY_SIZE);
    end = clock();
    float sortingByCountingRuntime = end - start;

    printf("Runtime of bubble sorting = %.10f\nRuntime of sotring by counting = %.10f\n", bubbleSortingRuntime / CLOCKS_PER_SEC, sortingByCountingRuntime / CLOCKS_PER_SEC);
}