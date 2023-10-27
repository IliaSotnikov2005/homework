#include <stdio.h>
#include <string.h>

#define CHARS_AMOUNT 256

int* charsCounting(char* filename, char* charCountingArray)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return -1;
    }
    int size = 0;
    char buffer[100] = { 0 };
    while (size = fgets(buffer, 100, file) > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            charCountingArray[buffer[i]]++;
        }
    }
    fclose(file);
}


int main()
{
    int occurrences[CHARS_AMOUNT] = { 0 };
    charsCounting("text.txt", occurrences);
    for (int i = 0; i < CHARS_AMOUNT; ++i)
    {
        if (occurrences[i] > 0)
        {
            printf("%c - %d\n", i, occurrences[i]);
        }
    }
}
