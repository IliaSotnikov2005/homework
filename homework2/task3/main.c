#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE 100000

void sortingByCounting(int* array, const size_t size)
{
    int max = array[0];
    int min = array[0];

    for (size_t i = 0; i < size; ++i)
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

    size_t countingArraySize = max - min + 1;
    int* countingArray = calloc(countingArraySize, sizeof(int));
    if (countingArray == NULL)
    {
        return;
    }

    int shifter = min;

    for (size_t i = 0; i < size; ++i)
    {
        ++countingArray[array[i] - shifter];
    }

    int index = 0;
    for (size_t i = 0; i < countingArraySize; ++i)
    {
        for (int j = 0; j < countingArray[i]; ++j)
        {
            array[index] = i + shifter;
            ++index;
        }
    }

    free(countingArray);
}

void bubbleSorting(int* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
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

void randomIntArrayFill(int* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = rand() - RAND_MAX / 2;
    }
}

int sortTest(void (*sortFunction)(int* array, const size_t size))
{
    int testBase[][5] = { { 3, 7, 1, 9, 2 }, { -5, 0, 10, -2, 7 }, { 5, 5, 5, 5, 5 } };
    int expectedResults[][5] = { { 1, 2, 3, 7, 9 }, { -5, -2, 0, 7, 10 }, { 5, 5, 5, 5, 5 } };
    size_t testsAmount = sizeof(testBase) / sizeof(testBase[0]);

    for (size_t i = 0; i < testsAmount; ++i)
    {
        sortFunction(testBase[i], 5);
        if (memcmp(testBase[i], expectedResults[i], sizeof(testBase[0])) != 0)
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    int testErrorCode = sortTest(&bubbleSorting);
    if (testErrorCode != 0)
    {
        printf("Bubble sorting failed %d test", testErrorCode);
        return -1;
    }

    testErrorCode = sortTest(&bubbleSorting);
    if (testErrorCode != 0)
    {
        printf("Sorting by counting failed %d test", testErrorCode);
        return -1;
    }

    int* array1 = calloc(ARRAY_SIZE, sizeof(int));
    if (array1 == NULL)
    {
        printf("Memory allocation error");
        return -2;
    }

    int* array2 = calloc(ARRAY_SIZE, sizeof(int));
    if (array2 == NULL)
    {
        free(array1);
        printf("Memory allocation error");
        return -2;
    }

    randomIntArrayFill(array1, ARRAY_SIZE);
    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        array2[i] = array1[i];
    }

    printf("Now the algorithms are sorting the array, please wait\n\n");

    clock_t start = clock();
    bubbleSorting(array1, ARRAY_SIZE);
    clock_t end = clock();
    float bubbleSortingRuntime = ((float)(end - start) / CLOCKS_PER_SEC);
    free(array1);

    start = clock();
    sortingByCounting(array2, ARRAY_SIZE);
    end = clock();
    float sortingByCountingRuntime = ((float)(end - start) / CLOCKS_PER_SEC);
    free(array2);

    printf("Runtime of bubble sorting = %.10f sec\nRuntime of sorting by counting = %.10f sec\n", bubbleSortingRuntime, sortingByCountingRuntime);
}