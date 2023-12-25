#include "findMostFrequentFunction.h"

#include <stdio.h>
#include <stdlib.h>

enum ErrorCode
{
    ok = 0,
    invalidName = -1,
    fileNotFound = -2
};

int test(void)
{
    char inputFiles[5][10] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "frgtd.txt"};
    int expected[5][2] = { {4, 0}, {-3, 0}, {7, 0}, {1, 0}, {0, -1} };

    for (size_t i = 0; i < 5; ++i)
    {
        findMostFrequentErrorCode errorCode = 0;
        int result = findMostFrequent(inputFiles[i], &errorCode);
        if (result != expected[i][0] || errorCode != expected[i][1])
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
        printf("Failed %d test", errorCode);
        return errorCode;
    }

    printf("Enter the name of file: ");

    char filename[101] = { 0 };
    if (scanf_s("%[^\n]", filename, 101) == 0)
    {
        printf("Invalid name");
        return invalidName;
    }

    findMostFrequentErrorCode exitCode = 0;
    int mostFrequent = findMostFrequent(filename, &exitCode);

    switch (exitCode)
    {
    case findMostFrequentOk:
    {
        break;
    }
    case findMostFrequentFileNotFound:
    {
        printf("File not found");
        return findMostFrequentFileNotFound;
    }
    case findMostFrequentInvalidInput:
    {
        printf("Invalid input");
        return findMostFrequentInvalidInput;
    }
    case findMostFrequentMemoryAllocationError:
    {
        printf("Memory allocation error");
        return findMostFrequentMemoryAllocationError;
    }
    default:
        break;
    }

    printf("\nThe most frequent element is %d\n", mostFrequent);
}