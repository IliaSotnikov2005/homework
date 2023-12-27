#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum ErrorCode
{
    ok = 0,
    divisionByZeroError = -1,
    memoryAllocationError = -2,
    operandFindingError = -3,
    incorrectPostfixExpressionError = -4,
    invalidOperatorError = -5
} ErrorCode;

#define EXPRESSION_LENGTH 100

int calculatePostfixExpression(char* expression, ErrorCode* errorCode)
{
    *errorCode = ok;

    Stack* stack = stackCreate();
    if (stack == NULL)
    {
        *errorCode = memoryAllocationError;
        return 0;
    }

    int result = 0;

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        char symbol = expression[i];

        if (symbol == ' ' || symbol == '\n')
        {
            continue;
        }

        if (symbol >= '0' && symbol <= '9')
        {
            stackPush(stack, symbol - '0');
            continue;
        }
        int operand1 = 0;
        int operand2 = 0;

        if (stackPop(stack, &operand2) != stackOk || stackPop(stack, &operand1) != stackOk)
        {
            *errorCode = operandFindingError;
            stackFree(&stack);
            return 0;
        }

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
                stackFree(&stack);
                return 0;
            }
            break;
        }
        default:
        {
            *errorCode = invalidOperatorError;
            return 0;
            break;
        }
        }

        stackPush(stack, result);

    }

    while (stackSize(stack) > 1)
    {
        *errorCode = incorrectPostfixExpressionError;
        stackFree(&stack);
        return 0;
    }

    if (stackPop(stack, &result) != stackOk)
    {
        *errorCode = operandFindingError;
        stackFree(&stack);
        return 0;
    }

    stackFree(&stack);

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
            return (int)i + 1;
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
    printf("Enter the postfix expression: ");
    fgets(expression, EXPRESSION_LENGTH, stdin);

    errorCode = ok;
    int result = calculatePostfixExpression(expression, &errorCode);
    if (errorCode != ok)
    {
        printf("An error occured %d", errorCode);
        return errorCode;
    }

    printf("Result is %d", result);
}