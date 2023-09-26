#include <stdio.h>
#include <time.h>

#define NUMBER_OF_FIBONACCI_NUMBERS 40

int recursiveFibonacci(int number)
{
    if (number < 1)
    {
        return -1;
    }
    if (number == 1 || number == 2)
    {
        return 1;
    }
    return recursiveFibonacci(number - 1) + recursiveFibonacci(number - 2);
}

int linearFibonacci(int number)
{
    int number1 = 1, number2 = 1, number3 = 2;
    if (number < 1)
    {
        return -1;
    }
    if (number == 1 || number == 2)
    {
        return 1;
    }
    for (int i = 3; i < number; i++)
    {
        number1 = number2;
        number2 = number3;
        number3 = number1 + number2;
    }
    return number3;
}

int main()
{
    printf("The fibonacci sequence constructed by a linear algorithm:\n");
    float runtimesLinear[NUMBER_OF_FIBONACCI_NUMBERS] = { 0 };
    for (int number = 1; number < NUMBER_OF_FIBONACCI_NUMBERS + 1; ++number)
    {
        clock_t start = clock();
        printf("%d ", linearFibonacci(number));
        clock_t end = clock();
        runtimesLinear[number - 1] = end - start;
    }

    printf("\n\n");

    printf("The fibonacci sequence constructed by a recursive algorithm:\n");
    float runtimesRecursive[NUMBER_OF_FIBONACCI_NUMBERS] = { 0 };
    for (int number = 1; number < NUMBER_OF_FIBONACCI_NUMBERS + 1; ++number)
    {
        clock_t start = clock();
        printf("%d ", recursiveFibonacci(number));
        clock_t end = clock();
        runtimesRecursive[number - 1] = end - start;
    }

    printf("\n\n");

    for (int i = 0; i < NUMBER_OF_FIBONACCI_NUMBERS; i++)
    {
        float advantage = (runtimesRecursive[i] - runtimesLinear[i]) / CLOCKS_PER_SEC;
        if (advantage > 0)
        {
            printf("When calculating %d fibonacci number linear algoritm is faster then recursive by %.5f seconds\n", i + 1, advantage);
        }
    }
}