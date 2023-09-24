#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseArray(char** array, int start, int length)
{
    for (int i = start; i < start + (length / 2); ++i)
    {
        char* temp = array[i];
        array[i] = array[start + length - 1 - (i - start)];
        array[start + length - 1 - (i - start)] = temp;
    }
}

int main()
{
    printf("Enter the size of array: ");
    int arraySize = getNum();
    while (arraySize < 0)
    {
        printf("\nThe size of array should be greater than 0 or equal\nTry again: ");
        arraySize = getNum();
    }
    char** array = (char**)malloc(arraySize * sizeof(char*));

    printf("\nEnter the array elements one by one:\n");
    fillStringArray(array, arraySize);

    printf("\nEnter the length of the first segment: ");
    int firstPartLength = getNum();
    while (firstPartLength < 0 || firstPartLength > arraySize)
    {
        printf("\nThe length of the first part should be from 0 to the length of the array (%d)\nTry again: ", arraySize);
        firstPartLength = getNum();
    }

    const int secondPartLength = arraySize - firstPartLength;
    printf("\nThe length of the second segment is %d\n", secondPartLength);

    printf("\nThe original array: ");
    printStringArray(array, arraySize);

    reverseArray(array, 0, firstPartLength);
    reverseArray(array, firstPartLength, secondPartLength);
    reverseArray(array, 0, firstPartLength + secondPartLength);

    printf("The result:         ");
    printStringArray(array, arraySize);

    for (int i = 0; i < arraySize; ++i)
    {
        free(array[i]);
    }
    free(array);
}