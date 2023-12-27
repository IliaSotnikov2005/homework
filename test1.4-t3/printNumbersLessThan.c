#include "printNumbersLessThan.h"

#include <stdio.h>

PrinterErrorCode fprintNumbersLessThan(const char* source, const char* fileWithNumberName, const char* destination)
{
    FILE* sourceFile = fopen(source, "r");
    if (sourceFile == NULL)
    {
        return printerFileNotFound;
    }

    FILE* fileWithNumber = fopen(fileWithNumberName, "r");
    if (fileWithNumber == NULL)
    {
        fclose(sourceFile);
        return printerFileNotFound;
    }

    FILE* output = fopen(destination, "w");
    if (output == NULL)
    {
        fclose(sourceFile);
        fclose(fileWithNumber);
        return printerFileCreationError;
    }

    int number = 0;
    if (fscanf_s(fileWithNumber, "%d", &number) == 0)
    {
        fclose(sourceFile);
        fclose(fileWithNumber);
        fclose(output);
        return printerInvalidInput;
    }

    int sourceNumber = 0;
    while (fscanf_s(sourceFile, "%d", &sourceNumber) != EOF)
    {
        if (sourceNumber < number)
        {
            fprintf(output, "%d ", sourceNumber);
        }
    }

    fclose(sourceFile);
    fclose(fileWithNumber);
    fclose(output);

    return printerOk;
}