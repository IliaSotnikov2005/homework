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

void sumBin(int* bin1, int* bin2, int* result, const int size)
{
    int carry = 0;
    for (int i = size - 1; i >= 0; --i)
    {
        result[i] = (bin1[i] + bin2[i] + carry) % 2;
        carry = (bin1[i] + bin2[i] + carry > 1) ? 1 : 0;
    }
}

void printBin(const int* bin, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d", bin[i]);
    }
    printf("\n");
}

int binToDecimal(int* bin, int size)
{
    int negative = (bin[0] == 1) ? -1 : 1;
    if (bin[0] == 1)
    {
        for (int i = size - 1; i >= 0; --i)
        {
            if (bin[i] == 1)
            {
                for (int j = i + 1; j < size; ++j)
                {
                    bin[j] = 1;
                }
                bin[i] = 0;
                break;
            }
        }
        for (int i = 0; i < size; ++i)
        {
            bin[i] = !bin[i];
        }
    }
    int result = 0;
    for (int i = 1; i <= size; ++i)
    {
        result += bin[size - i] * (1 << (i - 1));
    }
    return negative * result;
}

void toTwosComplement(int number, int* bin, int size) {
    for (int i = size - 1; i >= 0; i--) {
        bin[i] = number & 1;
        number >>= 1;
    }
}

int test()
{
    return 0;
}

int main()
{
    setlocale(LC_ALL, "RU");

    if (test() != 0)
    {
        return -1;
    }

    printf("Введите желаемое число двоичных разрядов: ");
    int bitDepth = getNum();
    int lowLimit = -(1 << (bitDepth - 1)), highLimit = (1 << (bitDepth - 1)) - 1;
    printf("\nСейчас вы работаете с числами в промежутке от %d до %d\n", lowLimit, highLimit);

    printf("\nВведите первое число: ");
    int number1 = getNum();
    if (number1 < lowLimit || number1 > highLimit)
    {
        printf("Неверный ввод данных\n");
        return -1;
    }
    int *binNumber1 = calloc(bitDepth, sizeof(int));
    if (binNumber1 == NULL)
    {
        return -1;
    }
    toTwosComplement(number1, binNumber1, bitDepth);
    printf("\nПервое число в дополнительном коде: ");
    printBin(binNumber1, bitDepth);

    printf("\nВведите второе число: ");
    int number2 = getNum();
    if (number2 < lowLimit || number2 > highLimit)
    {
        printf("Неверный ввод данных\n");
        return -1;
    }
    int *binNumber2 = calloc(bitDepth, sizeof(int));
    if (binNumber2 == NULL)
    {
        return -1;
    }
    toTwosComplement(number2, binNumber2, bitDepth);
    printf("\nВторое число в дополнительном коде: ");
    printBin(binNumber2, bitDepth);

    if (number1 + number2 < lowLimit || number1 + number2 > highLimit)
    {
        printf("\nРезультат вычисления суммы вышел за рамки указанного выше диапазона\n");
        return -1;
    }

    int* binNumberSum = calloc(bitDepth, sizeof(int));
    if (binNumberSum == NULL)
    {
        return -1;
    }
    sumBin(binNumber1, binNumber2, binNumberSum, bitDepth);
    printf("\nСумма двух чисел в бинарной системе: ");
    printBin(binNumberSum, bitDepth);

    int result = binToDecimal(binNumberSum, bitDepth);
    printf("\nВ десятичной системе: %d\n", result);
}