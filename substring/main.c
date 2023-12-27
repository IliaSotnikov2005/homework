#include "findSubstring.h"
#include "readTextFromFile.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int testFailed = test();
    if (testFailed != 0)
    {
        printf("TEST %d FAILED", testFailed);
        return -1;
    }

    char* text = readTextFromFile("text.txt");
    if (text == NULL)
    {
        return -1;
    }

    printf("Enter the pattern to find: ");
    char pattern[100] = { 0 };
    fgets(pattern, 100, stdin);
    pattern[strlen(pattern) - 1] = '\0';

    size_t index = KMPSearch(pattern, text);
    free(text);
    if (index != -1)
    {
        printf("First occurence: %d", (int)index);
    }
    else
    {
        printf("No such pattern");
    }
}
