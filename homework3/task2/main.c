#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>

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


}