#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void randomIntArrayFill(int* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        array[i] = rand() - RAND_MAX;
    }
}

void printIntArray(const int * array, const size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}