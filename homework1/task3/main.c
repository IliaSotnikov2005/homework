#include "../../lib/functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int findIncompleteQuotient(int dividend, int divisor, int* exitCode)
{
    if (divisor == 0)
    {
        *exitCode = -1;
        return 0;
    }
    int sign = (dividend < 0) != (divisor < 0) ? -1 : 1;
    bool dividendIsNegative = abs(dividend) != dividend;

    dividend = abs(dividend);
    divisor = abs(divisor);

    int incompleteQuotient = 0;
    do
    {
        ++incompleteQuotient;
        dividend -= divisor;
    } while (dividend > 0);

    if (!dividendIsNegative && (dividend != 0))
    {
        --incompleteQuotient;
    }

    *exitCode = 0;
    return sign * incompleteQuotient;
}

int test(void)
{
    int exitCode = 0;
    if (findIncompleteQuotient(-12, 5, &exitCode) != -3 || exitCode != 0)
    {
        return 1;
    }
    if (findIncompleteQuotient(12, -5, &exitCode) != -2 || exitCode != 0)
    {
        return 2;
    }
    if (findIncompleteQuotient(12, 5, &exitCode) != 2 || exitCode != 0)
    {
        return 3;
    }
    if (findIncompleteQuotient(-12, -5, &exitCode) != 3 || exitCode != 0)
    {
        return 4;
    }
    if (findIncompleteQuotient(-12, 0, &exitCode) != 0 || exitCode != -1)
    {
        return 5;
    }
    exitCode = 0;
    if (findIncompleteQuotient(12, 0, &exitCode) != 0 || exitCode != -1)
    {
        return 6;
    }
    if (findIncompleteQuotient(12, 12, &exitCode) != 1 || exitCode != 0)
    {
        return 7;
    }
    if (findIncompleteQuotient(-12, -12, &exitCode) != 1 || exitCode != 0)
    {
        return 8;
    }
    if (findIncompleteQuotient(12, 1, &exitCode) != 12 || exitCode != 0)
    {
        return 9;
    }
    if (findIncompleteQuotient(12, -1, &exitCode) != -12 || exitCode != 0)
    {
        return 10;
    }
    if (findIncompleteQuotient(3, 7, &exitCode) != 0 || exitCode != 0)
    {
        return 11;
    }
    if (findIncompleteQuotient(-3, 7, &exitCode) != -1 || exitCode != 0)
    {
        return 12;
    }
    return 0;
}

int main()
{
    if (test() != 0)
    {
        printf("failed %d test", test());
        return -1;
    }
    printf("Enter the dividend\na = ");
    int number1 = getNum();

    printf("\nEnter the divisor\nb = ");
    int number2 = getNum();

    int exitCode = 0;
    int incompleteQuotient = findIncompleteQuotient(number1, number2, &exitCode);

    if (exitCode == -1)
    {
        printf("\nError: Division by zero\n");
        return -1;
    }

    printf("\nResult of an incomplete quotient: %d\n", incompleteQuotient);
}