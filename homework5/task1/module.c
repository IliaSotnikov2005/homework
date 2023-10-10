#include "module.h"
#include <stdio.h>
#include <stdlib.h>

int findMostFrequent(char *name)
{
    int *exitCode = 0;
    FILE* file = fopen(name, "r");
    if (file == NULL) {
        printf("\n%s\nError: file not found\n", name);
        *exitCode = -1;
        return 0;
    }

    char line[100];
    if (fgets(line, 100, file) == NULL)
    {
        *exitCode = -1;
        return 0;
    }
    int size = 0;
    if (sscanf(line, "%d", &size) == NULL)
    {
        *exitCode = -1;
        return 0;
    }

    int *array = calloc(size, sizeof(int));
    if (array == NULL)
    {
        *exitCode = -1;
        return 0;
    }
    for (int i = 0; i < size; ++i) {
        fgets(line, sizeof(line), file);
        if (sscanf(line, "%d", &array[i]) == NULL)
        {
            *exitCode = -1;
            return 0;
        }
    }

    int max = array[0];
    int min = array[0];

    for (int i = 0; i < size; ++i)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
        if (array[i] < min)
        {
            min = array[i];
        }
    }

    if (min < 0)
    {
        min = -min;
    }
    else
    {
        min = 0;
    }

    int* countingArray = calloc(max + min + 1, sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        ++countingArray[array[i] + min];
    }

    int index = 0;
    for (int i = 0; i < max + min + 1; ++i)
    {
        if (countingArray[i] > countingArray[index])
        {
            index = i;
        }
    }
    free(countingArray);
    free(array);
    fclose(file);

    return index - min;
}