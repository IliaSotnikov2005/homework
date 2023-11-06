#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define AMOUNT_OF_FIBONACCI_NUMBERS 40

unsigned int recursiveFibonacci(unsigned int number)
{
    if (number == 0)
    {
        return 0;
    }
    if (number == 1 || number == 2)
    {
        return 1;
    }
    return recursiveFibonacci(number - 1) + recursiveFibonacci(number - 2);
}

unsigned int linearFibonacci(unsigned int number)
{
    int number1 = 1, number2 = 1, number3 = 2;
    if (number == 0)
    {
        return 0;
    }
    if (number == 1 || number == 2)
    {
        return 1;
    }
    for (unsigned int i = 3; i < number; i++)
    {
        number1 = number2;
        number2 = number3;
        number3 = number1 + number2;
    }
    return number3;
}

void fibonacciTest(unsigned int (*fibonacciFunction)(unsigned int), bool* testResult)
{
    int testCases[][2] = {
        {0, 0},
        {1, 1},
        {2, 1},
        {3, 2},
        {4, 3},
        {5, 5},
        {6, 8},
        {7, 13},
        {8, 21}
    };

    for (int i = 0; i < 9; ++i)
    {
        int input = testCases[i][0];
        int expectedOutput = testCases[i][1];
        int actualOutput = fibonacciFunction(input);

        testResult[i] = (actualOutput == expectedOutput);
    }
}

int main()
{
    bool testResult[9] = { 0 };
    fibonacciTest(&linearFibonacci, testResult);
    for (int i = 0; i < 9; ++i)
    {
        if (!testResult[i])
        {
            printf("LINEAR TEST %d FAILED\n", i + 1);
        }
    }
    fibonacciTest(&recursiveFibonacci, testResult);
    for (int i = 0; i < 9; ++i)
    {
        if (!testResult[i])
        {
            printf("RECURSIVE TEST %d FAILED\n", i + 1);
        }
    }

    printf("The fibonacci sequence constructed by a linear algorithm:\n");
    float runtimesLinear[AMOUNT_OF_FIBONACCI_NUMBERS] = { 0 };
    for (int number = 1; number < AMOUNT_OF_FIBONACCI_NUMBERS + 1; ++number)
    {
        clock_t start = clock();
        printf("%d ", linearFibonacci(number));
        clock_t end = clock();
        runtimesLinear[number - 1] = ((float)(end - start) / CLOCKS_PER_SEC);
    }

    printf("\n\n");

    printf("The fibonacci sequence constructed by a recursive algorithm:\n");
    float runtimesRecursive[AMOUNT_OF_FIBONACCI_NUMBERS] = { 0 };
    for (int number = 1; number < AMOUNT_OF_FIBONACCI_NUMBERS + 1; ++number)
    {
        clock_t start = clock();
        printf("%d ", recursiveFibonacci(number));
        clock_t end = clock();
        runtimesRecursive[number - 1] = ((float) (end - start) / CLOCKS_PER_SEC);
    }

    printf("\n\n");

    for (int i = 0; i < AMOUNT_OF_FIBONACCI_NUMBERS; i++)
    {
        float advantage = (runtimesRecursive[i] - runtimesLinear[i]);
        if (advantage > 0)
        {
            printf("When calculating %d fibonacci number linear algoritm is faster then recursive by %.5f seconds\n", i + 1, advantage);
        }
    }
}
