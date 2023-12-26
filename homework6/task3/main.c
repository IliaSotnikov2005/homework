#include "stack.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

enum ErrorCode
{
    ok = 0,
    invalidInput = -1
};

int test()
{
    char expression1[] = "2 + 2 * 2";
    char expected1[] = "2 2 2 * +";
    convertInfixToPostfix(expression1);
    strcmp(expression1, expected1) == 0;

    char expression2[] = "9 / (5 - 3)";
    char expected2[] = "9 5 3 - /";
    convertInfixToPostfix(expression2);
    strcmp(expression2, expected2) == 0;

    char expression3[] = "(7 + 3) * (4 - 2)";
    char expected3[] = "7 3 + 4 2 - *";
    convertInfixToPostfix(expression3);
    strcmp(expression3, expected3) == 0;

    char expression4[] = "8 / 4 / 2";
    char expected4[] = "8 4 / 2 /";
    convertInfixToPostfix(expression4);
    strcmp(expression4, expected4) == 0;

    char expression5[] = "1 + 2 + 3 + 4 + 5";
    char expected5[] = "1 2 + 3 + 4 + 5 +";
    convertInfixToPostfix(expression5);
    strcmp(expression5, expected5) == 0;
}

int main()
{
    int errorCode = 0;
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    printf("Enter the expression: ");

    char expression[MAX_EXPRESSION_LENGTH] = { 0 };
    if (fgets(expression, MAX_EXPRESSION_LENGTH, stdin) == 0)
    {
        return invalidInput;
    }

    convertInfixToPostfix(expression);
    printf("\nThe result: %s", expression);
}