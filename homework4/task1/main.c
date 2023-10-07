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
            printf("\n������������ ������ �����\n���������� �����: ");
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

void toTwosComplement(int number, int *bin, int size)
 {
    int i = 0;
    bool negative = number < 0;
    number = abs(number);
    while (number > 0)
    {
        bin[i] = number % 2;
        number /= 2;
        ++i;
    }
    if (negative)
    {
        for (i = 0; i < size; ++i)
        {
            bin[i] = !bin[i];
        }
        int carry = 1;
        for (i = 0; i < size; ++i)
        {
            bin[i] = bin[i] + carry;
            carry = bin[i] / 2;
            bin[i] %= 2;

        }
    }
    reverse(bin, size);
}

int main()
{
    setlocale(LC_ALL, "RU");

    printf("������� �������� ����� �������� ��������: ");
    int bitDepth = getNum();
    int lowLimit = -(1 << (bitDepth - 1)), highLimit = (1 << (bitDepth - 1)) - 1;
    printf("\n������ �� ��������� � ������� � ���������� �� %d �� %d\n", lowLimit, highLimit);

    printf("\n������� ������ �����: ");
    int number1 = getNum();
    if (number1 < lowLimit || number1 > highLimit)
    {
        printf("�������� ���� ������\n");
        return -1;
    }
    int *binNumber1 = calloc(bitDepth, sizeof(int));
    toTwosComplement(number1, binNumber1, bitDepth);
    printf("\n������ ����� � �������������� ����: ");
    printBin(binNumber1, bitDepth);

    printf("\n������� ������ �����: ");
    int number2 = getNum();
    if (number2 < lowLimit || number2 > highLimit)
    {
        printf("�������� ���� ������\n");
        return -1;
    }
    int *binNumber2 = calloc(bitDepth, sizeof(int));
    toTwosComplement(number2, binNumber2, bitDepth);
    printf("\n������ ����� � �������������� ����: ");
    printBin(binNumber2, bitDepth);

    if (number1 + number2 < lowLimit || number1 + number2 > highLimit)
    {
        printf("\n��������� ���������� ����� ����� �� ����� ���������� ���� ���������\n");
        return -1;
    }

    int* binNumberSum = calloc(bitDepth, sizeof(int));
    sumBin(binNumber1, binNumber2, binNumberSum, bitDepth);
    printf("\n����� ���� ����� � �������� �������: ");
    printBin(binNumberSum, bitDepth);

    int result = binToDecimal(binNumberSum, bitDepth);
    printf("\n� ���������� �������: %d\n", result);
}