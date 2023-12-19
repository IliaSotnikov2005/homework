#include <stdio.h>
#include <stdlib.h>

int comparator(const int* a, const int* b)
{
    return (*a - *b);
}

int findMostFrequent(int* array, const size_t size)
{
    qsort(array, size, sizeof(int), comparator);
    int mostFrequent = 0;
    int mostFrequentStreak = 0;
    int current = array[0];
    int currentStreak = 1;

    for (size_t i = 1; i < size; ++i)
    {
        if (array[i] == current)
        {
            ++currentStreak;
        }
        else
        {
            if (mostFrequentStreak < currentStreak)
            {
                mostFrequent = current;
                mostFrequentStreak = currentStreak;
            }
            current = array[i];
            currentStreak = 1;
        }
    }
    mostFrequentStreak < currentStreak ? mostFrequent = current : NULL;

    return mostFrequent;
}

int test(void)
{
    int array1[] = { 2, 1, 3, 3, 3, 4, 4, 4, 4 };
    int size1 = 9;
    int result1 = findMostFrequent(array1, size1);
    if (result1 != 4)
    {
        return 1;
    }

    int array2[] = { -5, -3, -5, -2, -3, -4, -3, -4 };

    int size2 = 8;
    int result2 = findMostFrequent(&array2, size2);
    if (result2 != -3)
    {
        return 2;
    }

    int array3[] = { 7, 7, 7, 7, 7, 7, 7 };
    int size3 = 7;
    int result3 = findMostFrequent(array3, size3);
    if (result3 != 7)
    {
        return 3;
    }
    return 0;
}

int main()
{
    int testErrorCode = test();
    if (testErrorCode != 0)
    {
        printf("Test %d failed", testErrorCode);
        return testErrorCode;
    }

    printf("Enter the size of the array:\n");

    int size = 0;
    if (scanf_s("%d", &size) == 0 || size < 0)
    {
        printf("\nInvalid input");
        return -1;
    }

    printf("\nEnter the elements of array one by one\n");
    int* array = calloc(size, sizeof(int));
    if (array == NULL)
    {
        printf("Memory allocation error");
        return -2;
    }

    for (size_t i = 0; i < size; ++i)
    {
        printf("array[%d] = ", (int)i);
        if (scanf_s("%d", &array[i]) == 0)
        {
            printf("Invalid input");
            return -1;
        }
    }

    int mostFrequent = findMostFrequent(array, size);
    free(array);

    printf("\nThe most frequent element is %d", mostFrequent);
}