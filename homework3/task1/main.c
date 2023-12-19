#include "../../lib/functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum ErrorCode
{
    ok = 0,
    memoryAllocationError = -1,
    invalidInput = -2,
    testFailed = -3
} ErrorCode;

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* array, const int start, const unsigned int end)
{
    for (unsigned int i = start + 1; i < end + 1; ++i)
    {
        bool sorted = true;
        for (unsigned int j = i; j > 0; --j)
        {
            if (array[j - 1] > array[j])
            {
                swap(&array[j], &array[j - 1]);
                sorted = false;
            }

            if (array[end - j] > array[end - j + 1])
            {
                swap(&array[end - j], &array[end - j + 1]);
                sorted = false;
            }
        }
        if (sorted)
        {
            break;
        }
    }
}

void smartQSort(int* array, const unsigned int start, const unsigned int end)
{
    if (end - start + 1 < 10)
    {
        insertionSort(array, start, end);
        return;
    }
    if (start < end)
    {
        int separator = array[end];
        int left = start;
        int right = end;
        while (left <= right)
        {
            for (; array[left] < separator; ++left);
            for (; array[right] > separator; --right);
            if (left <= right)
            {
                swap(&array[left], &array[right]);
                ++left;
                --right;
            }
        }
        smartQSort(array, start, right);
        smartQSort(array, left, end);
    }
}

unsigned int test(void)
{
    int arrayLess10[][9] = {
        {3, 7, 1, 9, 2, 34, 33, 3, -5},
        {-5, 0, 10, -2, -70, 67, 9, 17, -10}
    };
    int expected1[][9] = {
        {-5, 1, 2, 3, 3, 7, 9, 33, 34},
        {-70, -10, -5, -2, 0, 9, 10, 17, 67}
    };

    for (unsigned int i = 0; i < 2; ++i)
    {
        smartQSort(arrayLess10[i], 0, 8);
        if (memcmp(arrayLess10[i], expected1[i], sizeof(arrayLess10[i])) != 0)
        {
            return i + 1;
        }
    }

    int arrayMore10[][15] = {
        {5, 10, 3, 8, 15, 7, 12, 1, 9, 6, 2, 11, 4, 13, 14},
        {17, 22, -19, 24, 31, 27, 20, 16, 29, 26, 21, 30, 18, 28, 23}
    };
    int expected2[][15] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        {-19, 16, 17, 18, 20, 21, 22, 23, 24, 26, 27, 28, 29, 30, 31}
    };

    for (unsigned int i = 2; i < 4; ++i)
    {
        smartQSort(arrayMore10[i - 2], 0, 14);
        if (memcmp(arrayMore10[i - 2], expected2[i - 2], sizeof(arrayMore10[i - 2])) != 0)
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    unsigned int testErrorCode = test();
    if (testErrorCode != 0)
    {
        printf("Test %d failed", testErrorCode);
        return testErrorCode;
    }

    printf("Enter the size of the array\n");
    int size = getNum();
    if (size < 0)
    {
        printf("The size must be greater than 0");
        return invalidInput;
    }

    printf("Enter the numbers one by one\n");
    int* array = calloc(size, sizeof(int));
    if (array == NULL)
    {
        printf("Memory allocation error");
        return memoryAllocationError;
    }
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