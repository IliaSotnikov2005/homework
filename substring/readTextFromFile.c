#include "readTextFromFile.h"

#include <stdio.h>
#include <stdlib.h>

char* readTextFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* text = calloc(fileSize, sizeof(char));
    if (text == NULL)
    {
        return NULL;
    }

    fread(text, sizeof(char), fileSize, file);

    fclose(file);

    return text;
}