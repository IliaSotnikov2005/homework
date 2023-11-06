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

    if (min < 0)
    {
        min = -min;
    }
    else
    {
        min = 0;
    }

    int* countingArray = calloc(max + min + 1, sizeof(int));
    if (countingArray == NULL)
    {
        return;
    }

    for (size_t i = 0; i < size; ++i)
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

void bubbleSorting(int* array, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
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
    for (size_t i = 0; i < size; i++)
    {
        int value = rand();
        array[i] = value;
    }
}

void sortTest(void (*sortFunction)(int* array, const size_t size), bool* testResults)
{
    int testBase[][5] = { { 3, 7, 1, 9, 2 }, { -5, 0, 10, -2, 7 }, { 5, 5, 5, 5, 5 } };
    int expectedResults[][5] = { { 1, 2, 3, 7, 9 }, { -5, -2, 0, 7, 10 }, { 5, 5, 5, 5, 5 } };
    size_t testsAmount = sizeof(testBase) / sizeof(testBase[0]);

    for (size_t i = 0; i < testsAmount; ++i)
    {
        sortFunction(testBase[i], 5);
        testResults[i] = memcmp(testBase[i], expectedResults[i], sizeof(testBase[0])) == 0;
    }
}

int main()
{
    bool testResults[3] = { 0 };
    sortTest(&bubbleSorting, testResults);
    for (size_t i = 0; i * 2 < sizeof(testResults); ++i)
    {
        if (!testResults[i])
        {
            printf("BUBBLE SORTING TEST %d FAILED\n", (int)i);
        }
    }

    sortTest(&sortingByCounting, testResults);
    for (size_t i = 0; i * 2 < sizeof(testResults); ++i)
    {
        if (!testResults[i])
        {
            printf("SORTING BY COUNTING TEST %d FAILED\n", (int)i);
        }
    }

    printf("Now the algorithms are sorting the array, please wait\n\n");

    int* array1 = calloc(ARRAY_SIZE, sizeof(int));
    if (array1 == NULL)
    {
        return -1;
    }
    int* array2 = calloc(ARRAY_SIZE, sizeof(int));
    if (array2 == NULL)
    {
        return -1;
    }
    randomIntArrayFill(array1, ARRAY_SIZE);

    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        array2[i] = array1[i];
    }

    clock_t start = clock();
    bubbleSorting(array1, ARRAY_SIZE);
    clock_t end = clock();
    float bubbleSortingRuntime = (float)((end - start) / CLOCKS_PER_SEC);
    free(array1);

    start = clock();
    sortingByCounting(array2, ARRAY_SIZE);
    end = clock();
    float sortingByCountingRuntime = (float)((end - start) / CLOCKS_PER_SEC);
    free(array2);

    printf("Runtime of bubble sorting = %.10f\nRuntime of sotring by counting = %.10f\n", bubbleSortingRuntime, sortingByCountingRuntime);
}