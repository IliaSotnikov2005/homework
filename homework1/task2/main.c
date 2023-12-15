#include "../../lib/functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(const unsigned int argc, const char* const argv[])
{
    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        return 0;
    }

    int number1 = 0;
    printf("Enter the first number: ");
    number1 = getNum();

    int number2 = 0;
    printf("\nEnter the second number: ");
    number2 = getNum();

    printf("\nInitial numbers: %d, %d\n", number1, number2);
    number1 += number2;
    number2 = number1 - number2;
    number1 = number1 - number2;
    printf("The resulting numbers: %d, %d\n", number1, number2);
}