#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>

void evenBubbleSort(int* array, int size)
{
    for (int i = 0; i < size; i += 2)
    {
        for (int j = i + 2; j < size; j += 2)
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

int test(void)
{
    int array1[] = { 5, 4, 3, 2, 1};
    int array1c[] = { 1, 4, 3, 2, 5};
    evenBubbleSort(array1, 5);
    if (memcmp(array1, array1c, sizeof(array1)) != 0)
    {
        return -1;
    }

    int array2[] = { -5, 0, 10, -2, 7 };
    int array2c[] = { -5, 0, 7, -2, 10 };
    evenBubbleSort(array2, 5);
    if (memcmp(array2, array2c, sizeof(array2)) != 0)
    {
        return -2;
    }

    int array3[] = { 5, 5, 5, 5, 5 };
    int array3c[] = { 5, 5, 5, 5, 5 };
    evenBubbleSort(array3, 5);
    if (memcmp(array3, array3c, sizeof(array3)) != 0)
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
        printf("\nInvalid value");
        return -1;
    }

    int* array = calloc(size, sizeof(int));
    fillIntArray(array, size);

    printf("\nThe original array:\n");
    printIntArray(array, size);

    evenBubbleSort(array, size);

    printf("\nThe result:\n");
    printIntArray(array, size);
}