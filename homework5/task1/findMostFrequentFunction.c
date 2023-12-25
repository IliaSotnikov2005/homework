#include "findMostFrequentFunction.h"

#include <stdlib.h>
#include <stdio.h>

static int comparator(const int* a, const int* b)
{
    return (*a - *b);
}

static int findMostFrequentFunction(int* array, const size_t size)
{
    qsort(array, size, sizeof(int), comparator);
    int mostFrequent = 0;
    int mostFrequentStreak = 0;
    int current = array[0];
    int currentStreak = 1;

    for (size_t i = 1; i < size; ++i)
    {
        if (array[i] == current)
        {
            ++currentStreak;
        }
        else
        {
            if (mostFrequentStreak < currentStreak)
            {
                mostFrequent = current;
                mostFrequentStreak = currentStreak;
            }
            current = array[i];
            currentStreak = 1;
        }
    }
    mostFrequentStreak < currentStreak ? mostFrequent = current : NULL;

    return mostFrequent;
}

static int* createIntArrayFromFile(const char* filemane, size_t* arraySize, findMostFrequentErrorCode* errorCode)
{
    *errorCode = findMostFrequentOk;

    FILE* file = fopen(filemane, "r");
    if (file == NULL)
    {
        *errorCode = findMostFrequentFileNotFound;
        return NULL;
    }

    int numbersAmount = 0;
    if (fscanf_s(file, "%d", &numbersAmount) == 0)
    {
        fclose(file);
        *errorCode = findMostFrequentInvalidInput;
        return NULL;
    }
    *arraySize = numbersAmount;

    int* array = calloc(numbersAmount, sizeof(int));
    if (array == NULL)
    {
        free(array);
        fclose(file);
        *errorCode = findMostFrequentMemoryAllocationError;
        return NULL;
    }

    for (size_t i = 0; i < numbersAmount; ++i)
    {
        if (fscanf_s(file, "%d", &array[i]) == 0)
        {
            free(array);
            fclose(file);
            *errorCode = findMostFrequentInvalidInput;
            return NULL;
        }
    }

    fclose(file);

    return array;
}

int findMostFrequent(const char* filename, findMostFrequentErrorCode* errorCode)
{
    *errorCode = 0;
    size_t arraySize = 0;
    int* array = createIntArrayFromFile(filename, &arraySize, errorCode);
    if (array == NULL)
    {
        return 0;
    }

    int mostFrequentElement = findMostFrequentFunction(array, arraySize);
    free(array);

    return mostFrequentElement;
}
