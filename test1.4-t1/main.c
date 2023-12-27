#include <stdio.h>
#include <stdlib.h>

unsigned int findSumOfEvenFibonacciNumbers(unsigned int topLimit)
{
    unsigned int number1 = 1;
    unsigned int number2 = 1;
    unsigned int number3 = 2;

    if (topLimit < 1)
    {
        return 0;
    }
    if (topLimit < 2)
    {
        return 0;
    }

    unsigned int result = 2;

    while (number3 < topLimit)
    {
        number1 = number2;
        number2 = number3;
        number3 = number1 + number2;
        if (number3 < topLimit && number3 % 2 == 0)
        {
            result += number3;
        }
    }

    return result;
}

int test(void)
{
    int input[] = { 1, 4, 7, 35 };
    int expected[] = { 0, 2, 2, 44 };

    for (size_t i = 0; i < 4; ++i)
    {
        if (findSumOfEvenFibonacciNumbers(input[i]) != expected[i])
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
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    printf("%d", findSumOfEvenFibonacciNumbers(1000000));
}
