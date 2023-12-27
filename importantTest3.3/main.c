#include "lexerOfEmails.h"
#include "test.h"

#include <stdio.h>

enum ErrorCode
{
    ok = 0,
    invalidInput = -1
};

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    printf("Enter a line to check if it is an email: ");
    char string[100] = { 0 };
    if (scanf_s("%s", string, 100) == 0)
    {
        printf("Invalid input");
        return invalidInput;
    }

    printf(isEmailAddress(string) ? "Yes it is" : "No it is not");
}