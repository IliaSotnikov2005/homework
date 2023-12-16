#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int createMinimalNumber(int number)
{
    if (number < 0)
    {
        return -1;
    }

    unsigned int countOfDigitsInNumber[10] = { 0 };
    size_t digitsCount = 0;
    while (number != 0)
    {
        countOfDigitsInNumber[number % 10] += 1;
        number /= 10;
        ++digitsCount;
    }

    bool zerosInNumber = countOfDigitsInNumber[0] != 0;
    for (size_t i = 1; digitsCount != 0; ++i)
    {
        while (countOfDigitsInNumber[i] != 0)
        {
            number += i * pow(10, digitsCount - 1);
            --digitsCount;
            --countOfDigitsInNumber[i];

            if (zerosInNumber)
            {
                digitsCount -= countOfDigitsInNumber[0];
                zerosInNumber = false;
            }
        }
    }

    return number;
}

int test()
{
    int input[5] = {100, 120, 143215532, 0, -2345};
    int expected[5] = { 100, 102, 112233455, 0, -1 };
    for (size_t i = 0; i < 5; ++i)
    {
        if (createMinimalNumber(input[i]) != expected[i])
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Failed test: %d\n", errorCode);
    }

    int number = 0;
    printf("Enter a natural number: ");
    if (scanf_s("%d", &number) != 1 || number < 0)
    {
        printf("\nError: Invalid input\n");
        return -1;
    }

    number = createMinimalNumber(number);

    printf("\nThe result: %u\n", number);
}