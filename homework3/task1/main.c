#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>

int partition(int *array, const int start, const int end, const int pivot)
{
    if (start < 0 || end < 0)
    {
        return -1;
    }
    int i = start;
    int j = start;
    while (i <= end)
    {
        if (array[i] > pivot)
        {
            i++;
        }
        else {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j++;
        }
    }
    return j - 1;
}

int smartQSort(int *array, const int start, const int end)
{
    if (start < 0 || end < 0)
    {
        return -1;
    }
    if (end - start + 1 < 10)
    {
        for (int i = 1; i < end + 1; ++i)
        {
            for (int j = i; j > 0 && array[j - 1] > array[j]; --j)
            {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
        return 0;
    }
    if (start < end) {
        int pivot = array[end];
        int pIndex = partition(array, start, end, pivot);

        smartQSort(array, start, pIndex - 1);
        smartQSort(array, pIndex + 1, end);
    }
}

int test(void)
{
    int array1[] = { 3, 7, 1, 9, 2 };
    int array1c[] = { 1, 2, 3, 7, 9 };
    smartQSort(array1, 0, 4);
    if (memcmp(array1, array1c, sizeof(array1)) != 0)
    {
        return -1;
    }

    int array2[] = { -5, 0, 10, -2, 7 };
    int array2c[] = { -5, -2, 0, 7, 10 };
    smartQSort(array2, 0, 4);
    if (memcmp(array2, array2c, sizeof(array2)) != 0)
    {
        return -1;
    }

    int array3[] = { 5, 5, 5, 5, 5 };
    int array3c[] = { 5, 5, 5, 5, 5 };
    smartQSort(array3, 0, 4);
    if (memcmp(array3, array3c, sizeof(array3)) != 0)
    {
        return -1;
    }
    return 1;
}

int main()
{
    if (test == -1)
    {
        return -1;
    }
    printf("Enter the size of the array\n");
    int size = getNum();
    if (size < 0)
    {
        printf("The size must be greater than 0");
        return -1;
    }

    printf("Enter the numbers one by one\n");
    int* array = calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        printf("array[%d] = ", i);
        array[i] = getNum();
    }

    printf("\nOriginal array:\n");
    printIntArray(array, size);

    smartQSort(array, 0, size - 1);

    printf("\nThe result:\n");
    printIntArray(array, size);
}