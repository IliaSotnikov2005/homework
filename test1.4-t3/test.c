#include "test.h"
#include "printNumbersLessThan.h"

#include <stdio.h>
#include <string.h>

int test(void)
{
    if (fprintNumbersLessThan("test.txt", "testNumber.txt", "output.txt") != printerOk)
    {
        return 1;
    }

    FILE* output = fopen("output.txt", "r");
    if (output == NULL)
    {
        return 2;
    }

    char buffer[100] = { 0 };
    if (fscanf_s(output, "%[^\n]", buffer, 100) == 0)
    {
        fclose(output);
        return 3;
    }

    if (strcmp("9 8 7 6 5 4 3 1 1 3 ", buffer) != 0)
    {
        fclose(output);
        return 4;
    }

    if (fprintNumbersLessThan("fwfewf", "fsfd", "fsfs") != printerFileNotFound)
    {
        fclose(output);
        return 5;
    }

    fclose(output);

    return 0;
}