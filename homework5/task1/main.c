#include "module.h"
#include <stdio.h>
#include <stdlib.h>

int test(void)
{
    int exitCode = 0;
    int result = 0;
    result = findMostFrequent("test1.txt", &exitCode);
    if (result != 4 || exitCode != 0)
    {
        return -1;
    }
    result = findMostFrequent("test2.txt", &exitCode);
    if (result != -3 || exitCode != 0)
    {
        return -2;
    }
    result = findMostFrequent("test3.txt", &exitCode);
    if (result != 7 || exitCode != 0)
    {
        return -3;
    }
    result = findMostFrequent("test4.txt", &exitCode);
    if ((result != 1 && result != 2) || exitCode != 0)
    {
        return -4;
    }
    result = findMostFrequent("asfawfawfewaweafev.txt", &exitCode);
    if (exitCode != -1)
    {
        return exitCode;
    }
    return 0;
}

int main()
{
    if (test() != 0)
    {
        return -1;
    }

    printf("Enter the name of file:\n");
    char name[100];
    if (scanf_s("%[^\n]", name, 100) == NULL)
    {
        printf("\nInvalid name\n");
        return -1;
    }

    int exitCode = 0;
    int mostFrequent = findMostFrequent(name, &exitCode);
    if (exitCode == -1)
    {
        printf("\nFile not found");
        return -1;
    }

    printf("\nThe most frequent element is %d", mostFrequent);
}