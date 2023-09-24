#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    char string[80] = { 0 };
    printf("Enter a bracket sequence of no more than 80 characters long: ");
    scanf_s("%s", string, 80);
    const int stringSize = strlen(string);

    char openBracket = '(', closedBracket = ')';
    if (strstr("{", string) || strstr("}", string))
    {
        openBracket = '{';
        closedBracket = '}';
    }
    if (strstr("[", string) || strstr("]", string))
    {
        openBracket = '[';
        closedBracket = ']';
    }

    int bracketBalance = 0;
    bool sequenceIsCorrect = true;
    for (int i = 0; i < stringSize; ++i)
    {
        if ((string[i] != openBracket) && (string[i] != closedBracket))
        {
            printf("\nError: different brackets are used or there are extraneous characters in the sequence\n");
            sequenceIsCorrect = false;
            break;
        }
        if (bracketBalance < 0)
        {
            sequenceIsCorrect = false;
            break;
        }
        if (string[i] == openBracket)
        {
            ++bracketBalance;
        }
        if (string[i] == closedBracket)
        {
            --bracketBalance;
        }
    }
    if (sequenceIsCorrect && bracketBalance == 0)
    {
        printf("\nThe bracket sequence is correct\n");
    }
    else
    {
        printf("\nThe bracket sequence is incorrect\n");
    }
}