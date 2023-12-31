#include "../../lib/functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPrime(int number)
{
    bool prime = true;
    for (int divider = 2; divider * divider < number + 1; ++divider)
    {
        if (number % divider == 0)
        {
            prime = false;
            break;
        }
    }
    return prime;
}

int main(const unsigned int argc, const char* const argv[])
{
    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        return 0;
    }

    printf("Enter the limit: ");
    int limit = getNum();

    printf("\nPrime numbers not exceeding a given number: ");
    for (int number = 2; number < limit + 1; ++number)
    {
        if (isPrime(number))
        {
            printf("%d ", number);
        }
    }
    printf(limit > 1 ? "\n" : "\n\nThere is no prime numbers not exceeding a given number\n");
}