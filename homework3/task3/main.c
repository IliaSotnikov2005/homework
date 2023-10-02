#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>

int findMostFrequent(int* array, const int size)
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
        if (countingArray[i] > countingArray[index])
        {
            index = i;
        }
    }
    free(countingArray);

    return index - min;
}

int test(void)
{
    int array1[] = { 1, 2, 3, 3, 3, 4, 4, 4, 4 };
    int size1 = sizeof(array1) / sizeof(array1[0]);
    int result1 = findMostFrequent(array1, size1);
    if (result1 != 4)
    {
        return -1;
    }

    int array2[] = { -5, -3, -5, -2, -3, -4, -3, -4 };
    int size2 = sizeof(array2) / sizeof(array2[0]);
    int result2 = findMostFrequent(array2, size2);
    if (result2 != -3)
    {
        return -2;
    }

    int array3[] = { 7, 7, 7, 7, 7, 7, 7 };
    int size3 = sizeof(array3) / sizeof(array3[0]);
    int result3 = findMostFrequent(array3, size3);
    if (result3 != 7)
    {
        return -3;
    }
    return 0;
}

int main()
{
    if (test() != 0)
    {
        return -1;
    }
    printf("Enter the size of the array:\n");
    int size = getNum();
    if (size < 0)
    {
        printf("\nInvalid size value");
        return -1;
    }

    printf("\nEnter the elements of array one by one\n");
    int* array = calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        printf("array[%d] = ", i);
        array[i] = getNum();
    }

    int mostFrequent = findMostFrequent(array, size);

    printf("\nThe most frequent element is %d", mostFrequent);
}