#include "findSubstring.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void getLPSArray(const char* pattern, size_t patternLength, int* lps)
{
    int length = 0;
    lps[0] = 0;
    for (size_t i = 1; i < patternLength;)
    {
        if (pattern[i] == pattern[length])
        {
            ++length;
            lps[i] = length;
            ++i;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }
}

size_t KMPSearch(const char* pattern, const char* text)
{
    size_t patternLength = strlen(pattern);
    size_t textLength = strlen(text);
    int* lpsArray = calloc(patternLength, sizeof(int));
    if (lpsArray == NULL)
    {
        return -1;
    }

    getLPSArray(pattern, patternLength, lpsArray);
    for (size_t i = 0, j = 0; i < textLength;)
    {
        if (pattern[j] == text[i])
        {
            ++j;
            ++i;
        }
        if (j == patternLength)
        {
            free(lpsArray);
            return i - j;
        }
        else if (i < textLength && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lpsArray[j - 1];
            }
            else
            {
                ++i;
            }
        }
    }

    free(lpsArray);
    return -1;
}
