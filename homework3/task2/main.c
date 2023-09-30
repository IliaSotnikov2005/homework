#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const int number1, const int number2)
{
    if (number1 == number2) return 0;
    else if (number1 < number2) return -1;
    else return 1;
}

int binarySearch(const int number, const int* array, const int size)
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

int test()
{
    const int* array1[] = { 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 };
    const int size = 10;
    if (binarySearch(0, array1, size) != 0)
    {
        return 1;
    }
    if (binarySearch(9, array1, size) != 9)
    {
        return 2;
    }
    if (binarySearch(10, array1, size) != -1)
    {
        return 3;
    }
    if (binarySearch(-2, array1, size) != -1)
    {
        return 4;
    }
    if (binarySearch(4, array1, -2) != -1)
    {
        return 5;
    }
    if (binarySearch(7, array1, -2) != -1)
    {
        return 6;
    }
    const int array2[] = {0, 0, 0, 0};
    if (binarySearch(0, array2, 4) == -1)
    {
        return 7;
    }
    return 0;
}

int main()
{
    if (test() != 0)
    {
        return -1;
    }
    printf("Enter the size of the array: ");
    const int size = getNum();
    if (size < 0)
    {
        printf("\nThe length of the array must be greater or equal\n");
        return -1;
    }
    int* array = calloc(size, sizeof(int));
    randomIntArrayFill(array, size);

    printf("\nEnter the count or numbers: ");
    const int numbersCount = getNum();
    if (numbersCount < 0)
    {
        printf("\nThe length of the array must be greater or equal\n");
        return -1;
    }
    int* numberArray = calloc(size, sizeof(int));
    randomIntArrayFill(numberArray, numbersCount);

    numberArray[0] = array[0]; // ну чтобы хоть 1 элемент был

    printf("\nArray:\n");
    printIntArray(array, size);

    printf("\nNumbers to search for:\n");
    printIntArray(numberArray, numbersCount);

    qsort(array, size, sizeof(int), compare);

    for (int i = 0; i < numbersCount; ++i)
    {
        if (binarySearch(numberArray[i], array, size) != -1)
        {
            printf("\n%d is in array", numberArray[i]);
        }
        else
        {
            printf("\n%d is not in array", numberArray[i]);
        }
    }
}