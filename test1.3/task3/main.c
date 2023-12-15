#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 100

void removeConsecutiveChars(char* string, const size_t size)
{
    if (size <= 1)
    {
        return;
    }
    size_t index = 0;
    for (size_t i = 1; i < size; ++i)
    {
        if (string[i] != string[index])
        {
            ++index;
            string[index] = string[i];
        }
    }

    string[index + 1] = '\0';
}

char* readStringFromFile(const char const* filename, size_t* textSize)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (fileSize >= MAX_FILE_SIZE)
    {
        return NULL;
    }

    char* text = calloc(MAX_FILE_SIZE, sizeof(char));
    if (text == NULL)
    {
        return NULL;
    }
    
    fread(text, sizeof(char), fileSize, file);

    fclose(file);

    *textSize = fileSize;

    return text;
}


int test(void)
{
    char input[3][7] = {"aaaaa", "", "a\n\n\nbb\n"};
    char expected[3][5] = { "a", "", "a\nb\n\0" };

    for (size_t i = 0; i < 3; ++i)
    {
        removeConsecutiveChars(input[i], 7);
        if (strcmp(input[i], expected[i]) != 0)
        {
            return i + 1;
        }

    }

    return 0;
}


int main()
{
    int testFailed = test();
    if (testFailed != 0)
    {
        printf("FAILED %d TEST\n", testFailed);
        return -1;
    }

    size_t textSize = 0;
    char* text = readStringFromFile("text.txt", &textSize);
    if (text == NULL)
    {
        printf("The file could not be read\n");
        return -1;
    }
    
    printf("Input: %s\n", text);
    removeConsecutiveChars(text, textSize);
    printf("\nResult: %s\n", text);
    free(text);
}