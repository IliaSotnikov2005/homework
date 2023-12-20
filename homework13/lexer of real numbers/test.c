#include "test.h"
#include "lexerOfRealNumber.h"

#include <stdlib.h>

int test(void)
{
    const char* tests[] = { "3.14", "2E+10", "abc", "0.5E-3", "1234.5678", "3.14.15" };
    const int expected[] = { 1, 1, 0, 1, 1, 0 };

    for (size_t i = 0; i < 6; ++i)
    {
        if (isRealNumber(tests[i]) != expected[i])
        {
            return i + 1;
        }
    }

    return 0;
}