#include "../../lib/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EXPRESSION_LENGTH 100

int postfixCalculator(char *expression)
{
    Stack* stack = NULL;
    int operand1 = 0;
    int operand2 = 0;
    int result = 0;

    int i = 0;
    while (expression[i] != '\0')
    {
        char symbol = expression[i];
        ++i;
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
                result = operand1 / operand2;
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
        operand2 = pop(&stack);
        operand1 = pop(&stack);
        result = operand1 * operand2;
        push(&stack, result);
    }

    result = top(stack);
    freeStack(&stack);

    return result;
}

void testCalculator(bool *testResults) {
    char expressions[5][20] = {
        "5 3 +",
        "9 2 - 3 *",
        "7 2 / 4 *",
        "1 2 + 3 * 4 -",
        "9 3 / 2 + 5 *"
    };

    if (postfixCalculator(expressions[0]) == 8) {
        testResults[0] = true;
    }

    if (postfixCalculator(expressions[1]) == 21) {
        testResults[1] = true;
    }

    if (postfixCalculator(expressions[2]) == 12) {
        testResults[2] = true;
    }

    if (postfixCalculator(expressions[3]) == 5) {
        testResults[3] = true;
    }

    if (postfixCalculator(expressions[4]) == 25) {
        testResults[4] = true;
    }
}

int main()
{
    bool testResults[5] = { 0 };
    testCalculator(&testResults);
    for (int i = 0; i < 5; ++i)
    {
        if (!testResults[i])
        {
            printf("TEST %d FAILED", i);
        }
    }

    char expression[EXPRESSION_LENGTH] = { 0 };
    fgets(expression, EXPRESSION_LENGTH, stdin);

    printf("Result is %d", postfixCalculator(expression));
}