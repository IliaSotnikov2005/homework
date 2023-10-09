#include "../../lib/functions.h"
#include "module.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter the name of file:\n");
    char name[100];
    if (name == NULL)
    {
        printf("\nCannot to allocate the memory\n");
        return -1;
    }
    if (scanf_s("%[^\n]", name, 100) == NULL)
    {
        printf("\nInvalid name\n");
        return -1;
    }

    int mostFrequent = findMostFrequent(name);

    printf("\nThe most frequent element is %d", mostFrequent);
}