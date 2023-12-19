#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VALUE_SIZE 100

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

void randomIntArrayFill(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int value = rand();
        array[i] = value;
    }
}

void fillIntArray(int* array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("array[%d] = ", i);
        array[i] = getNum();
    }
}

void fillStringArray(char** array, int size)
{
    for (int i = 0; i < size; ++i)
    {

        printf("array[%d] = ", i);
        char value[MAX_VALUE_SIZE] = { 0 };
        scanf_s("%s", value, MAX_VALUE_SIZE);

        array[i] = (char*)malloc((strlen(value) + 1) * sizeof(char));
        strcpy(array[i], value);
    }
}

void printStringArray(char** array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%s ", array[i]);
    }
    printf("\n");
}

void printIntArray(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}