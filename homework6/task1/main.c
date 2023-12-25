#include "../../lib/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum ErrorCode
{
    divisionByZeroError = -1
} ErrorCode;

#define EXPRESSION_LENGTH 100

int calculatePostfixExpression(char *expression, ErrorCode* errorCode)
{
    Stack* stack = NULL;
    int result = 0;

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        int operand1 = 0;
        int operand2 = 0;
        char symbol = expression[i];

        if (symbol == ' ' || symbol == '\n')
        {
            continue;
        }
        if (symbol >= '0' && symbol <= '9')
        {
            push(&stack, symbol - '0');
        }
        else
        {
            operand2 = pop(&stack);
            operand1 = pop(&stack);

            switch (symbol)
            {
            case '+':
            {
                result = operand1 + operand2;
                break;
            }
            case '-':
            {
                result = operand1 - operand2;
                break;
            }
            case '*':
            {
                result = operand1 * operand2;
                break;
            }
            case '/':
            {
                if (operand2 != 0)
                {
                    result = operand1 / operand2;
                }
                else
                {
                    *errorCode = divisionByZeroError;
                }
                break;
            }

            default:
                break;
            }

            push(&stack, result);
        }
    }

    while (stackSize(stack) > 1)
    {
        int operand1 = 0;
        int operand2 = 0;

        operand2 = pop(&stack);
        operand1 = pop(&stack);
        result = operand1 * operand2;
        push(&stack, result);
    }

    result = top(stack);
    freeStack(&stack);

    return result;
}

int test(void)
{
    char expressions[6][20] =
    {
        "5 3 +",
        "9 2 - 3 *",
        "7 2 / 4 *",
        "1 2 + 3 * 4 -",
        "9 3 / 2 + 5 *",
        "1 0 /"
    };

    int expected[] = { 8, 21, 12, 5, 25, 0 };
    int expectedErrorCode[] = { 0, 0, 0, 0, 0, -1 };

    for (size_t i = 0; i < 6; ++i)
    {
        ErrorCode errorCode = 0;
        int result = calculatePostfixExpression(expressions[i], &errorCode);
        if (result != expected[i] || errorCode != expectedErrorCode[i])
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

    char expression[EXPRESSION_LENGTH] = { 0 };
    fgets(expression, EXPRESSION_LENGTH, stdin);

    printf("Result is %d", calculatePostfixExpression(expression));
}