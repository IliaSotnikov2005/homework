#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isSorted(const int const* array, const size_t size)
{
    for (size_t i = 1; i < size; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }

    return true;
}

void monkeySort(int* array, const size_t size)
{
    while (!isSorted(array, size))
    {
        for (size_t i = 0; i < size; ++i)
        {
            size_t j = rand() % size;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

void printArray(const int const* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int test(void)
{
    int input[4][10] = { { 9, 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1 , 0},
                         {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                         { 11 , -2452 , 5 , 7 , -3 , 2 , 5 , 346 , -4 , 32 },
                         NULL };
    int expected[4][10] = { {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                            {-2452, -4, -3, 2, 5, 5, 7, 11, 32, 346},
                            NULL};
    for (size_t i = 0; i < 4; ++i)
    {
        monkeySort(input[i], 10);
        if (memcmp(input[i], expected[i], 10) != 0)
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    int testFailed = test();
    if (testFailed != 0)
    {
        printf("TEST %d FAILED", testFailed);
        return -1;
    }

    int array[] = { 10, 9, 2, 3, 4, 2, 5 };
    monkeySort(array, 7);
    printArray(array, 7);
}