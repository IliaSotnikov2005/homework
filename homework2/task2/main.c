#include "../../lib/functions.h"
#include <stdio.h>
#include <math.h>

float recursiveExponentiation(int number, int power)
{
    if (power < 0)
    {
        return 1 / recursiveExponentiation(number, -power);
    }
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

float linearExponentiation(int number, int power)
{
    int result = 1;
    for (int i = 0; i < abs(power); ++i)
    {
        result *= number;
    }
    if (power >= 0)
    {
        return result;
    }
    return (float)1 / result;
}

int testLinearExponentiation(void) {
    if (linearExponentiation(2, 3) != 8)
    {
        return -1;
    }
    if (linearExponentiation(5, 2) != 25)
    {
        return -2;
    }
    if (linearExponentiation(2, -3) != 0.125)
    {
        return -3;
    }
    if (linearExponentiation(5, -2) != (float)0.04)
    {
        return -4;
    }
    if (linearExponentiation(2, 0) != 1)
    {
        return -5;
    }
    if (linearExponentiation(5, 0) != 1)
    {
        return -6;
    }
    if (linearExponentiation(0, 3) != 0)
    {
        return -7;
    }
    if (linearExponentiation(2, 1) != 2)
    {
        return -8;
    }
    if (linearExponentiation(5, 1) != 5)
    {
        return -9;
    }
    if (linearExponentiation(-2, 4) != 16)
    {
        return -10;
    }
    if (linearExponentiation(-5, 2) != 25)
    {
        return -11;
    }
    if (linearExponentiation(-2, 3) != -8)
    {
        return -12;
    }
    if (linearExponentiation(-5, 3) != -125)
    {
        return -13;
    }
    return 0;
}


int testRecursiveExponentiation(void) {
    if (recursiveExponentiation(2, 3) != 8)
    {
        return -1;
    }
    if (recursiveExponentiation(5, 2) != 25)
    {
        return -2;
    }
    if (recursiveExponentiation(2, -3) != (float)0.125)
    {
        return -3;
    }
    if (recursiveExponentiation(5, -2) != (float)0.04)
    {
        return -4;
    }
    if (recursiveExponentiation(2, 0) != 1)
    {
        return -5;
    }
    if (recursiveExponentiation(5, 0) != 1)
    {
        return -6;
    }
    if (recursiveExponentiation(0, 3) != 0)
    {
        return -7;
    }
    if (recursiveExponentiation(2, 1) != 2)
    {
        return -8;
    }
    if (recursiveExponentiation(5, 1) != 5)
    {
        return -9;
    }
    if (recursiveExponentiation(-2, 4) != 16)
    {
        return -10;
    }
    if (recursiveExponentiation(-5, 2) != 25)
    {
        return -11;
    }
    if (recursiveExponentiation(-2, 3) != -8)
    {
        return -12;
    }
    if (recursiveExponentiation(-5, 3) != -125)
    {
        return -13;
    }
    return 0;
}

int main()
{
    if (testLinearExponentiation() != 0 || testRecursiveExponentiation() != 0)
    {
        return -1;
    }
    printf("Enter a number and a power:\nnumber = ");
    int number = getNum();
    printf("power = ");
    int power = getNum();

    float resultLinear = linearExponentiation(number, power), resultRecursive = recursiveExponentiation(number, power);
    printf("\nThe result of the linear algorithm: %f\n", resultLinear);
    printf("\nThe result of the recursive algorithm: %f\n", resultRecursive);
}