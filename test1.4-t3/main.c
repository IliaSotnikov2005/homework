#include "printNumbersLessThan.h"
#include "test.h"

#include <stdio.h>

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    fprintNumbersLessThan("f.txt", "g.txt", "h.txt");
}