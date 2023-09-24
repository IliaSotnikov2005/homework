#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100

void sort(int* array, int size)
{
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
        }
    }
    int temp = array[pIndex];
    array[pIndex] = pivot;
    array[pIndex + 1] = temp;
}

int checkArray(int* array, int size, int number)
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
            return -1;
        }
    }
    return 0;
}

int main()
{
    int array[SIZE] = { 0 };
    randomIntArrayFill(array, SIZE);
    array[0] = rand();

    printf("Original array:\n");
    printIntArray(array, SIZE);

    int value = array[0];
    printf("\nThe firts number in array: %d\n", array[0]);

    sort(array, SIZE);
    printf("\nResult:\n");
    printIntArray(array, SIZE);

    if (checkArray(array, SIZE, value) != 0)
    {
        printf("Array is incorrect\n");
        return -1;
    }
}