#include <stdio.h>
#include <stdbool.h>

int toDecimal(const bool const * number, const size_t size)
{
    int decimalNumber = 0;
    for (int i = size - 1; i >= 0; --i)
    {
        if (number[i])
        {
            decimalNumber +=  1 << i;
        }
    }

    return decimalNumber;
}

bool compare(const bool const * number1, const bool const * number2)
{
    size_t size1 = sizeof(number1) / sizeof(bool);
    size_t size2 = sizeof(number2) / sizeof(bool);
    return toDecimal(number1, size1) > toDecimal(number2, size2);
}

void printArray(const bool const* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", (int)array[i]);
    }

    printf("\n");
}

int test(void)
{
    bool number1[] = {1, 0, 1};
    bool number2[] = {1, 1, 1};
    if (compare(number1, number2))
    {
        return 1;
    }

    return 0;
}

int main()
{
    if (test() != 0)
    {
        printf("test not passed");
        return -1;
    }

    bool number1[] = { 1, 1, 1, 1, 1 };
    bool number2[] = { 0, 1, 1 };

    printArray(number1, 5);
    printArray(number2, 3);
    printf(compare(number1, number2) ? "Number 1 is bigger" : "Number 2 is bigger");
}