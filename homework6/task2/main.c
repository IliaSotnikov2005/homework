#include "bracketSequenceChecker.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

enum ErrorCode
{
    ok = 0,
    invalidInput = -1
};

int test(void)
{
    char* testStrings[] = { "()", "{[]}", "(]", "({})", "{[()]}", "{[(])}", "{[()]}{}()" };
    bool expectedResults[] = { true, true, false, true, true, false, true };

    for (size_t i = 0; i < 7; ++i)
    {
        if (isCorrectBracketSequence(testStrings[i]) != expectedResults[i])
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("TEST %d FAILED\n", errorCode);
        return errorCode;
    }

    printf("Enter the bracket sequence: ");
    char string[MAX_LENGTH] = { 0 };
    if (scanf_s("%s", string, MAX_LENGTH) == 0)
    {
        return invalidInput;
    }

    printf("\nThis sequence is ");
    printf(isCorrectBracketSequence(string) ? "correct" : "incorrect");
}