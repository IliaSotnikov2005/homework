#include "findSubstring.h"
#include "readFileFromText.h"

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
    char* pattern = calloc(100, sizeof(char));
    if (pattern == NULL)
    {
        return -1;
    }
    
    fgets(pattern, 100, stdin);
    pattern[strlen(pattern) - 1] = '\0';

    int index = findSubstring(pattern, text);
    free(text);
    if (index != -1)
    {
        printf("First occurence: %d", index);
    }
    else
    {
        printf("No such pattern");
    }
}