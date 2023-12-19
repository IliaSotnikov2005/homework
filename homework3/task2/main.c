#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum ErrorCode
{
    ok = 0,
    invalidInput = -1,
    memoryAllocationError = -2
} ErrorCode;

int compare(const int number1, const int number2)
{
    if (number1 == number2)
    {
        return 0;
    }
    else if (number1 < number2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int binarySearch(const int number, const int* array, const size_t size)
{
    int leftIndex = 0;
    int rightIndex = size - 1;
    int mid = 0;

    while (leftIndex <= rightIndex)
    {
        mid = (leftIndex + rightIndex) / 2;
        if (array[mid] == number)
        {
            return mid;
        }

        if (array[mid] > number)
        {
            rightIndex = mid - 1;
        }

        else
        {
            leftIndex = mid + 1;
        }
    }

    return -1;
}

int test(void)
{
    const int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const int input[] = {0, 9, 10, -2, 4, 7};
    const int expected[] = { 0, 9, -1, -1, 4, 7 };
    const size_t size = 10;
    for (size_t i = 0; i < 6; ++i)
    {
        if (binarySearch(input[i], array, size) != expected[i])
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    int testErrorCode = test();
    if (testErrorCode != 0)
    {
        printf("Test %d failed", testErrorCode);
        return testErrorCode;
    }

    printf("Enter the size of the array: ");
    int arraySize = 0;
    if (scanf_s("%d", &arraySize) == 0 || arraySize < 0)
    {
        printf("Invalid input");
        return invalidInput;
    }

    int* array = calloc(arraySize, sizeof(int));
    if (array == NULL)
    {
        printf("Memory allocations error");
        return memoryAllocationError;
    }

    randomIntArrayFill(array, arraySize);

    printf("\nEnter the count or numbers: ");
    int numbersCount = 0;
    if (scanf_s("%d", &numbersCount) == 0 || numbersCount < 0)
    {
        free(array);
        printf("Invalid input");
        return invalidInput;
    }

    int* numberArray = calloc(numbersCount, sizeof(int));
    if (numberArray == NULL)
    {
        free(array);
        printf("Memory allocations error");
        return memoryAllocationError;
    }

    randomIntArrayFill(numberArray, numbersCount);

    numberArray[rand() % numbersCount] = array[rand() % arraySize]; // let at least 1 element always be inside

    printf("\nArray:\n");
    printIntArray(array, arraySize);

    printf("\nNumbers to search for:\n");
    printIntArray(numberArray, numbersCount);

    qsort(array, arraySize, sizeof(int), compare);

    for (int i = 0; i < numbersCount; ++i)
    {
        if (binarySearch(numberArray[i], array, arraySize) != -1)
        {
            printf("\n%d is in array", numberArray[i]);
        }
        else
        {
            printf("\n%d is not in array", numberArray[i]);
        }
    }

    free(numberArray);
    free(array);
}