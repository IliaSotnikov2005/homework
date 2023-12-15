#include "findSubstring.h"

#include <stdlib.h>

int findSubstring(const char const * pattern, const char const * string)
{
    if (string == NULL || pattern == NULL)
    {
        return -1;
    }

    size_t prefixLength = 0;
    for (int i = 0;; ++i)
    {
        if (pattern[prefixLength] == '\0')
        {
            return i - prefixLength;
        }

        if (string[i] == '\0')
        {
            return -1;
        }

        if (string[i] == pattern[prefixLength])
        {
            ++prefixLength;
        }
        else
        {
            prefixLength = 0;
        }
    }
}