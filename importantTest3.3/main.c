#include "lexerOfEmails.h"

#include <stdio.h>

enum ErrorCode
{
    ok = 0,
    invalidInput = -1
};

int main()
{
    char string[100] = { 0 };
    if (scanf_s("%s", string, 100) == 0)
    {
        printf("Invalid input");
        return invalidInput;
    }

    printf(isEmailAddress(string) ? "DA" : "NET");
}