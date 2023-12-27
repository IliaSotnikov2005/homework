#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ErrorCode
{
    ok = 0,
    invalidInput = -1
};

void sortingByChoice(int* array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        int* minimal = &array[i];
        for (size_t j = i + 1; j < size; ++j)
        {
            if (array[j] < *minimal)
            {
                minimal = &array[j];
            }
        }
        int temp = array[i];
        array[i] = *minimal;
        *minimal = temp;
    }
}

int test(void)
{
    int input[2][10] =
    {
        {5, 6, 3, 8, 5, 9, 3, 6, 1, 0},
        {0, 9, 8, 7, 6, 5, 4, 3, 2, 1}
    };

    int expected[2][10] =
    {
        {0, 1, 3, 3, 5, 5, 6, 6, 8, 9},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    for (size_t i = 0; i < 2; ++i)
    {
        sortingByChoice(input[i], 10);
        if (memcmp(input[i], expected[i], 10) != 0)
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    int array[10] = { 0 };

    printf("Enter the array:\n");
    for (size_t i = 0; i < 10; ++i)
    {
        printf("array[%d] = ", (int)i);
        if (scanf_s("%d", &array[i]) == 0)
        {
            printf("Invalid input");
            return invalidInput;
        }
    }

    sortingByChoice(array, 10);
    printf("The result: ");
    for (size_t i = 0; i < 10; ++i)
    {
        printf("%d ", array[i]);
    }
}