#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

enum ErrorCode
{
    ok = 0,
    invalidInput = -1,
    memoryAllocationError = -2
};

bool* sumBinary(const bool* number1, const bool* number2)
{
    bool* result = calloc(sizeof(int) * 8, sizeof(bool));
    if (result == NULL)
    {
        return NULL;
    }

    int carry = 0;
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i)
    {
        result[i] = (number1[i] + number2[i] + carry) % 2;
        carry = (number1[i] + number2[i] + carry > 1) ? 1 : 0;
    }

    return result;
}

void printBinary(const bool* bin)
{
    for (size_t i = 0; i < sizeof(int) * 8; ++i)
    {
        printf("%d", bin[i]);
    }

    printf("\n");
}

int toDecimal(const bool* binaryNumber)
{
    int decimal = 0;

    for (size_t i = 0; i < sizeof(int) * 8; ++i)
    {
        decimal += binaryNumber[31 - i] * (1 << i);
    }

    return decimal;
}

bool* toBinary(int number)
{
    bool* binaryNumber = calloc(sizeof(number) * 8, sizeof(bool));
    if (binaryNumber == NULL)
    {
        return NULL;
    }

    for (int i = sizeof(number) * 8 - 1; i >= 0; --i)
    {
        binaryNumber[i] = number & 1;
        number >>= 1;
    }

    return binaryNumber;
}

int test(void)
{
    int inputNumbers1[] = { 0, 10, -50, -127 };
    int inputNumbers2[] = { 10, -5, -77, 127 };
    int expected[] = { 10, 5, -127, 0 };

    for (size_t i = 0; i < 4; ++i)
    {
        bool* binaryNumber1 = toBinary(inputNumbers1[i]);
        bool* binaryNumber2 = toBinary(inputNumbers2[i]);
        bool* binarySum = sumBinary(binaryNumber1, binaryNumber2);
        if (toDecimal(binarySum) != expected[i])
        {
            free(binaryNumber1);
            free(binaryNumber2);
            free(binarySum);
            return i;
        }

        free(binaryNumber1);
        free(binaryNumber2);
        free(binarySum);
    }

    return 0;
}

int main()
{
    setlocale(LC_ALL, "RU");

    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    printf("Введите первое число: ");
    int number1 = 0;
    if (scanf_s("%d", &number1) == 0)
    {
        printf("Invalid input");
        return invalidInput;
    }

    bool* binaryNumber1 = toBinary(number1);
    if (binaryNumber1 == NULL)
    {
        printf("Memory allocation error");
        return memoryAllocationError;
    }

    printf("\nПервое число в двоичной системе счисления: ");
    printBinary(binaryNumber1);

    printf("\nВведите второе число: ");
    int number2 = 0;
    if (scanf_s("%d", &number2) == 0)
    {
        printf("Invalid input");
        return invalidInput;
    }

    bool* binaryNumber2 = toBinary(number2);
    if (binaryNumber2 == NULL)
    {
        free(binaryNumber1);
        printf("Memory allocation error");
        return memoryAllocationError;
    }

    printf("\nВторое число в двоичной системе счисления: ");
    printBinary(binaryNumber2);

    bool* binaryNumbersSum = sumBinary(binaryNumber1, binaryNumber2);
    if (binaryNumbersSum == NULL)
    {
        free(binaryNumber1);
        free(binaryNumber2);
        printf("Memory allocation error");
        return memoryAllocationError;
    }

    printf("\nСумма двух чисел в бинарной системе: ");
    printBinary(binaryNumbersSum);

    int decimalSum = toDecimal(binaryNumbersSum);
    printf("\nВ десятичной системе: %d\n", decimalSum);

    free(binaryNumber1);
    free(binaryNumber2);
    free(binaryNumbersSum);
}