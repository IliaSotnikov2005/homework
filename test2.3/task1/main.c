#include "rearrangeNumbers.h"

#include <stdio.h>

int test(void)
{
    rearrangeNumbers("test.txt", -4, 6);
    int expected[] = { -12, -5, -6, 6, 5, 4, 3, 2, 1, 0, -4, 3, 4, 3, 10, 9, 8, 7, 7 };
    FILE* output = fopen("output.txt", "r");
    if (output == NULL)
    {
        return 1;
    }
     
    int number = 0;
    for (size_t i = 0; i < 19; ++i)
    {
        if (fscanf_s(output, "%d", &number) == -1)
        {
            return 2;
        }
        if (number != expected[i])
        {
            return i + 3;
        }
    }

    return 0;
}

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("test %d failed", errorCode);
        return errorCode;
    }

    errorCode = rearrangeNumbers("text.txt", 4, 10);
    if (errorCode != 0)
    {
        printf("An error occured");
        return errorCode;
    }
    
    printf("Success! Result is in output.txt");
}