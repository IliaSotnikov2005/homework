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
    int size3 = max(size1, size2);
    int transfer = 0;
    for (int i = size3; i > -1; --i)
    {
        result[i] += transfer;
        if (i - (i - size1) > -1)
        {
            result[i] += bin1[i - (i - size1)];
        }
        if (i - (i - size2) > -1)
        {
            result[i] += bin2[i - (i - size2)];
        }
        if (result > 1)
        {
            transfer = 1;
        }
        else
        {
            transfer = 0;
        }
        result[i] %= 2;
        printf("\n%d %d %d\n", (bin1[i] + bin2[i]) % 2, result[i], i);
    }
}

void reverse(int* binNumber, int size)
{
    int i = 0, j = size - 1;
    int temp = 0;
    while (i < j)
    {
        temp = binNumber[i];
        binNumber[i] = binNumber[j];
        binNumber[j] = temp;
        ++i;
        --j;
    }
}

void toTwosComplement(int number, int *bin, int size)
{
    int i = 0;
    int addition = (number < 0) ? 1: 0;
    number = abs(number);
    while (number > 0)
    {
        bin[i] = ((number % 2) + addition) % 2;
        printf("^%d^", bin[i]);
        number /= 2;
        ++i;
    }
    reverse(bin, size);
}

void printBin(const int* bin, const int size)
{
    printf("->%d<-", size);
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
    int size1 = (int)floor(log2(abs(number1))) + 2;
    int *binNumber1 = calloc(size1, sizeof(int));
    toTwosComplement(number1, binNumber1, size1);
    reverse(binNumber1, size1);
    printf("\nПервое число в дополнительном коде: ");
    printBin(binNumber1, size1);

    printf("\nВведите второе число:\n");
    int number2 = getNum();
    int size2 = (int)floor(log2(abs(number2))) + 2;
    int *binNumber2 = calloc(size2, sizeof(int));
    toTwosComplement(number2, binNumber2, size2);
    //reverse(binNumber2, size2);

    printBin(binNumber1, size1);

  
    //int* binNumberSum = calloc(max(size1, size2) + 1, sizeof(int));
    //sumBin(binNumber1, binNumber2, binNumberSum);
    //printf("----------->");
    //printBin(binNumber1);
    //reverse(binNumber1, size1);
    //printf("      ");
   // printBin(binNumber1);
    //printBin(binNumberSum);
}