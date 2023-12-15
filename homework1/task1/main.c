#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countZeros(int* array, int size)
{
    int zeroCounter = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] == 0)
        {
            ++zeroCounter;
        }
    }
    return zeroCounter;
}

int main(const unsigned int argc, const char* const argv[])
{
    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        return 0;
    }

    printf("Enter the length of the array: ");

    int arraySize = getNum();
    while (arraySize < 0)
    {
        printf("\nThe size of array should be greater than 0\nTry again: ");
        arraySize = getNum();
    }
    int* arrayOfNumbers = malloc(arraySize * sizeof(int));

    printf("\nEnter the array elements one by one:\n");
    fillIntArray(arrayOfNumbers, arraySize);

    int zeroCount = countZeros(arrayOfNumbers, arraySize);
    free(arrayOfNumbers);
    printf("\nThe number of zeros in the array: %d\n", zeroCount);
}