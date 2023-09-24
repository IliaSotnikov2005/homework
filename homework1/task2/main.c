#include "../../lib/functions.h"
#include <stdio.h>
#include <stdbool.h>

int main()
{
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