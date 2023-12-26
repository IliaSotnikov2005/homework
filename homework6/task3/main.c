#include "infixToPostfixConverter.h"

#include <stdio.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

enum ErrorCode
{
    ok = 0,
    invalidInput = -1
};

int test(void)
{
    char inputs[6][18] =
    {
        "2 + 2 * 2",
        "9 / (5 - 3)",
        "(7 + 3) * (4 - 2)",
        "8 / 4 / 2",
        "1 + 2 + 3 + 4 + 5",
        "fqko 2 9 4 -"
    };
    char expected[6][17] =
    {
        "2 2 2 * +",
        "9 5 3 - /",
        "7 3 + 4 2 - *",
        "8 4 / 2 /",
        "1 2 + 3 + 4 + 5 +",
        ""
    };

    for (size_t i = 0; i < 6; ++i)
    {
        convertInfixToPostfix(inputs[i]);
        if (strcmp(inputs[i], expected[i]) != 0)
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