#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void outputComments(char* filename)
{
    FILE* file = fopen("1.txt", "r");
    if (file == NULL)
    {
        printf("File not found");
        return -1;
    }
    while (!feof(file))
    {
        char* buffer = malloc(sizeof(char) * 100);
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0)
        {
            break;
        }
        bool flag = false;
        for (int i = 0; buffer[i] != '\0'; ++i)
        {
            if (buffer[i] == ';' && !flag)
            {
                flag = true;
            }
            if (flag)
            {
                printf("%c", buffer[i]);
            }
        }
    }
    fclose(file);
}

int main()
{
    outputComments("1.txt");
}