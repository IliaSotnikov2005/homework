#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100

bool isPalindrome(char* string, const int size)
{
    bool flag = true;
    for (int i = 0; i < size; ++i)
    {
        if (string[size - 1 - i] != string[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}

void removeSpaces(char* string, const int size)
{
    char* newString = calloc(size + 1, sizeof(char));
    int index = 0;
    for (int i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] != ' ')
        {
            newString[index++] = string[i];
        }
    }
    if (newString)
    {
        newString[index] = '\0';
        strcpy(string, newString);
    }
    free(newString);
}

int test(void)
{
    char string1[] = "Aa A a";
    removeSpaces(string1, 6);
    if (isPalindrome(string1, 4))
    {
        return -1;
    }
    char string2[] = "AaaabaaaA";
    if (!isPalindrome(string2, 9))
    {
        return -2;
    }
    char string3[] = "";
    if (!isPalindrome(string3, 0))
    {
        return -3;
    }
    return 0;
}

int main()
{
    if (test() != 0)
    {
        return -1;
    }

    printf("Enter the string:\n");

    char string[MAX_STRING_SIZE] = { 0 };
    if (scanf_s("%[^\n]", string, MAX_STRING_SIZE) == 0)
    {
        printf("\nInvalid input");
        return -1;
    }
    int size = strlen(string);

    removeSpaces(string, size);
    size = strlen(string);

    if (isPalindrome(string, size))
    {
        printf("\nThe string is palindrome");
    }
    else
    {
        printf("\nThe striing is not palindrome\n");
    }
}