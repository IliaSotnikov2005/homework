#include "../../lib/functions.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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

bool* powerTest(float (*powerFunction)(int, int), bool* testResult)
{
    float testCases[][3] = {
        {2, 3, 8},
        {5, 2, 25},
        {2, -3, 0.125},
        {5, -2, 0.04},
        {2, 0, 1},
        {0, 3, 0},
        {2, 1, 2},
        {5, 1, 5},
        {-2, 4, 16},
        {-5, 2, 25},
        {-2, 3, -8},
        {-5, 3, -125}
    };

    for (int i = 0; i < 12; ++i)
    {
        int input1 = (int)testCases[i][0];
        int input2 = (int)testCases[i][1];
        float expectedOutput = testCases[i][2];
        float actualOutput = powerFunction(input1, input2);

        testResult[i] = (actualOutput == expectedOutput);
    }
}

int main()
{
    bool testResult[12] = { 0 };
    powerTest(&linearExponentiation, testResult);
    for (int i = 0; i < 12; ++i)
    {
        if (!testResult[i])
        {
            printf("LINEAR TEST %d FAILED\n", i + 1);
        }
    }
    powerTest(&recursiveExponentiation, testResult);
    for (int i = 0; i < 12; ++i)
    {
        if (!testResult[i])
        {
            printf("RECURSIVE TEST %d FAILED\n", i + 1);
        }
    }

    printf("Enter a number and a power:\nnumber = ");
    int number = getNum();
    printf("power = ");
    int power = getNum();

    float resultLinear = linearExponentiation(number, power), resultRecursive = recursiveExponentiation(number, power);
    printf("\nThe result of the linear algorithm: %f\n", resultLinear);
    printf("\nThe result of the recursive algorithm: %f\n", resultRecursive);
}