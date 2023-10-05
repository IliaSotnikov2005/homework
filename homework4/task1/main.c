#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
            printf("\nНеправильный формат ввода\nПопробуйте снова: ");
        }
        while ((symbol = getchar()) != '\n' && symbol != EOF);
    }
    return number;
}

void sumBin(int* bin1, int* bin2, int* result)
{
    int size1 = sizeof(bin1) / sizeof(int);
    int size2 = sizeof(bin2) / sizeof(int);
    int size3 = sizeof(result) / sizeof(int);

    

}

void toBin(int number, int *bin)
{
    int size = sizeof(bin) / sizeof(int);
    int i = size - 1;
    while (number > 0)
    {
        bin[i] = number % 2;
        number /= 2;
        --i;
    }
    if (number < 0)
    {
        for (i = 0; i < size; ++i)
        {
            bin[i] = (bin[i] + 1) % 2;
        }
    }
}

void printBin(const int* bin)
{
    int size = sizeof(bin) / sizeof(int);
    for (int i = 0; i < size; ++i)
    {
        printf("%d", bin[i]);
    }
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "RU");

    printf("Введите первое число:\n");
    int number1 = getNum();
    int size = (int)ceil(log2(number1));
    int *binNumber1 = calloc(size + 1, sizeof(int));

    printf("\nВведите второе число:\n");
    int number2 = getNum();
    size = (int)ceil(log2(number2));
    int *binNumber2 = calloc(size + 1, sizeof(int));

    toBin(number1, binNumber1);
    printf("-----------> ");
    printBin(binNumber1);
}