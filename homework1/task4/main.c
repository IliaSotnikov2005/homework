#include <stdio.h>
#include <string.h>

int main(const unsigned int argc, const char* const argv[])
{
    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        return 0;
    }

    int numberOfAmounts[28] = { 0 };
    for (int number = 0; number < 1000; number++)
    {
        int sumOfDigits = number / 100 + number % 100 / 10 + number % 10;
        numberOfAmounts[sumOfDigits]++;
    }

    int numberOfHappyTickets = 0;
    for (int sumOfDigits = 0; sumOfDigits < 28; sumOfDigits++)
    {
        numberOfHappyTickets += numberOfAmounts[sumOfDigits] * numberOfAmounts[sumOfDigits];
    }

    printf("Number of lucky tickets = %d\n", numberOfHappyTickets);
}