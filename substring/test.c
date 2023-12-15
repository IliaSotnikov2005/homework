#include "test.h"
#include "findSubstring.h"
#include "readFileFromText.h"

#include <stdlib.h>

int test()
{
    char* inputFiles[] = { "test1.txt", "test2.txt" };
    char* inputPatterns[] = { "fae", "mishka freddi" };
    int expected[] = { -1, 17 };
    for (size_t i = 0; i < 2; ++i)
    {
        char* text = readTextFromFile(inputFiles[i]);
        if (findSubstring(inputPatterns[i], text) != expected[i])
        {
            return i + 1;
        }

        free(text);
    }

    return 0;
}