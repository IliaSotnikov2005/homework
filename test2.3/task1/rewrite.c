#include "rewrite.h"
#include "stack.h"

#include <stdio.h>

int rewrite(const char* inputFilename, const int lowerBound, const int upperBound)
{
    FILE* inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL)
    {
        return -1;
    }

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        fclose(inputFile);
        return -2;
    }

    Stack* belowLowerLimit = stackCreate();
    Stack* withinBorders = stackCreate();
    Stack* aboveUpperLimit = stackCreate();
    if (belowLowerLimit == NULL || withinBorders == NULL || aboveUpperLimit == NULL)
    {
        fclose(inputFile);
        fclose(outputFile);
        stackFree(belowLowerLimit);
        stackFree(withinBorders);
        stackFree(aboveUpperLimit);
        return -3;
    }

    int number = 0;
    while (fscanf_s(inputFile, "%d", &number) != -1)
    {
        if (number < lowerBound)
        {
            stackPush(belowLowerLimit, number);
        }
        else if (number > upperBound)
        {
            stackPush(aboveUpperLimit, number);
        }
        else
        {
            stackPush(withinBorders, number);
        }
    }
    fclose(inputFile);

    int* array = stackToArray(belowLowerLimit);
    size_t arraySize = stackSize(belowLowerLimit);
    for (size_t i =arraySize; i >= 1; --i)
    {
        fprintf(outputFile, "%d ", array[i - 1]);
    }
    free(array);
    array = stackToArray(withinBorders);
    arraySize = stackSize(withinBorders);
    for (size_t i = arraySize; i >= 1; --i)
    {
        fprintf(outputFile, "%d ", array[i - 1]);
    }
    free(array);
    array = stackToArray(aboveUpperLimit);
    arraySize = stackSize(aboveUpperLimit);
    for (size_t i = arraySize; i >= 1; --i)
    {
        fprintf(outputFile, "%d ", array[i - 1]);
    }
    free(array);

    stackFree(&aboveUpperLimit);
    stackFree(&aboveUpperLimit);
    stackFree(&belowLowerLimit);
    fprintf(outputFile, "\n");

    fclose(outputFile);

    return 0;
}