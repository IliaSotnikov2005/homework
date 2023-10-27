#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int* shellSorting(int* array, const int size)
{
    int step = size / 2;
    while (step > 0)
    {
        for (int i = step; i < size; ++i)
        {
            int temp = array[i];
            int j = i;
            for (j; j >= step; j -= step)
            {
                if (array[j - step] > temp)
                {
                    array[j] = array[j - step];
                }
                else
                {
                    break;
                }
            }
            array[j] = temp;
        }
        step /= 2;
    }
}

bool test(bool* testResults)
{
    int correñtArray[] = { 0, 1, 2, 3, 4, 5 , 6 };
    int array[] = { 6, 5, 4, 3, 2, 1, 0 };
    shellSorting(array, 7);
    testResults[0] = memcmp(array, correñtArray, sizeof(array)) == 0;

    int correñtArray2[] = { 10, 47, 54, 54, 84 };
    int array2[] = { 10, 54, 47, 84, 54 };
    shellSorting(array, 5);
    testResults[0] = memcmp(array2, correñtArray2, sizeof(array2)) == 0;
}

int main()
{
    bool testResults[2] = { 0 };
    test(testResults);
    for (int i = 0; i < 2; ++i)
    {
        if (!testResults)
        {
            printf("TEST %d FAILED\n", i);
        }
    }

    const int size = 8;
    int array[] = { 12, 4, 67, 47, 3, 435, 674, 22 };
    printf("The original array: ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    shellSorting(array, size);
    printf("\nShell sorting result: ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
}
