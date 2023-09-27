#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void* a, const void* b)
{
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}

int bSearch(const int number, const int *array, const int size)
{
    int attempt = 1;
    int index = size / 2;
    while (2 >> attempt <= size)
    {
        if (array[index] == number)
        {
            return index;
        }
        if (array[index] > number)
        {
            index /= 2;
        }
        else if (array[index] < number)
        {
            index *= 2;
        }
        ++attempt;
    }
    return -1;
}

int main()
{
    printf("Enter the size of the array: ");
    int size = getNum();
    if (size < 0)
    {
        printf("\nThe length of the array must be greater or equal\n");
        return -1;
    }
    int *array = calloc(size, sizeof(int));
    randomIntArrayFill(array, size);

    printf("\nEnter the count or numbers: ");
    int numbersCount = getNum();
    if (numbersCount < 0)
    {
        printf("\nThe length of the array must be greater or equal\n");
        return -1;
    }
    int* numberArray = calloc(size, sizeof(int));
    randomIntArrayFill(numberArray, numbersCount);

    numberArray[0] = array[0];
    qsort(array, size, sizeof(int), compare);
    printIntArray(array, size);
    printIntArray(numberArray, numbersCount);

    for (int i = 0; i < numbersCount; ++i)
    {
        if (bSearch(numberArray[i], array, size))
        {
            printf("\n%d is in array\n", numberArray[i]);
        }
        else
        {
            printf("\n%d is not in array\n", numberArray[i]);
        }
    }
}