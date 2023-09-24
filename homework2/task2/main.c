#include <stdio.h>

int recursiveExponentiation(int number, int power)
{
    if (power == 0)
    {
        return 1;
    }
    if (power % 2 != 0)
    {
        return number * recursiveExponentiation(number, power - 1);
    }
    int b = recursiveExponentiation(number, power / 2);
    return b * b;
}

int linearExponentiation(int number, int power)
{
    int result = 1;
    for (int i = 0; i < power; ++i)
    {
        result *= number;
    }
    return result;
}

int main()
{
    printf("Table of results for numbers from 2 to 7 raised to a power from 0 to 10\n\n\n");
    for (int number = 2; number < 8; ++number)
    {
        printf("Number %d\nLinear    Recursive\n", number);
        for (int power = 0; power <= 10; ++power)
        {
            printf("%9d    %9d\n", linearExponentiation(number, power), recursiveExponentiation(number, power));
        }
        printf("\n\n");
    }
}