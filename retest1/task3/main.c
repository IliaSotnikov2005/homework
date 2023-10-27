#include <stdio.h>
#include <string.h>

int main()
{
    char string[] = "123aboba\n334kflr\n";
    int countingChars[257] = { 0 };
    char charArray[257] = { 0 };
    int charArraySize = 0;
    
    for (int i = 0; i < strlen(string); ++i)
    {
        int index = strstr(charArray, string[i]);
        if (index != NULL)
        {
            ++countingChars[index];
        }
        else
        {
            charArray[charArraySize] = string[i];
            ++charArraySize;
        }
    }
    for (int i = 0; i < charArraySize; ++i)
    {
        printf("/afefeada\n");
    }
}
