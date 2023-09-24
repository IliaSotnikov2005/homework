#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int countZeros(int* array, int size)
{
    int zeroCounter = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] == 0)
        {
            ++zeroCounter;
        }
    }
    return zeroCounter;
}

int getNum(void)
{
    int number = 0;
    while (true)
    {
        int input = scanf_s("%d", &number);
        char symbol = 0;
        int input2 = scanf_s("%c", &symbol);
        if (input == 1 && input2 == 1 && symbol == '\n')
        {
            break;
        }
        else
        {
            printf("\nInvalid input format\nTry again: ");
        }
        while ((symbol = getchar()) != '\n' && symbol != EOF);
    }
    return number;
}

void fillIntArray(int* array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("array[%d] = ", i);
        array[i] = getNum();
    }
}

int main()
{
    printf("Enter the length of the array: ");
    int arraySize = getNum();
    while (arraySize < 0)
    {
        printf("\nThe size of array should be greater than 0\nTry again: ");
        arraySize = getNum();
    }
    int* arrayOfNumbers = malloc(arraySize * sizeof(int));

    printf("\nEnter the array elements one by one:\n");
    fillIntArray(arrayOfNumbers, arraySize);

    int zeroCount = countZeros(arrayOfNumbers, arraySize);
    free(arrayOfNumbers);
    printf("\nThe number of zeros in the array: %d\n", zeroCount);
}