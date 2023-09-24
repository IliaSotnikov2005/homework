#pragma once
#include<stdio.h>
#include<stdbool.h>

int getNum(void)
{
    int number = 0;
    while (true)
    {
        char symbol = 0;
        int input = scanf_s("%d%c", &number, &symbol);
        if (input == 2 && symbol == '\n')
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

void fillArray(int* array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("array[%d] = ", i);
        array[i] = getNum();
    }
}