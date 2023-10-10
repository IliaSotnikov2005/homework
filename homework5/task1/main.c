#include "../../lib/functions.h"
#include "module.h"
#include <stdio.h>
#include <stdlib.h>

int test(void)
{
    int exitCode = 0;
    int result = 0;
    test("test1.txt", exitCode);
    if (result != 4 || exitCode != 0)
    {
        return -1;
    }
    test("test2.txt", exitCode);
    if (result != -3 || exitCode != 0)
    {
        return -2;
    }
    test("test3.txt", exitCode);
    if (result != 7 || exitCode != 0)
    {
        return -3;
    }
    test("test4.txt", exitCode);
    if ((result != 1 && result != 2) || exitCode != 0)
    {
        return -4;
    }
    test("asfawfawfewaweafev.txt", exitCode);
    if (exitCode != -1)
    {
        return -5;
    }
    return 0;
}

int main()
{
    //if (test() != 0)
    //{
        //printf("%d", test());
        //return -1;
    //}

    printf("Enter the name of file:\n");
    char name[100];
    if (scanf_s("%[^\n]", name, 100) == NULL)
    {
        printf("\nInvalid name\n");
        return -1;
    }

    int exitCode = 0;
    int mostFrequent = findMostFrequent(name);
    if (exitCode == -1)
    {
        printf("\nError");
        return -1;
    }

    printf("\nThe most frequent element is %d", mostFrequent);
}