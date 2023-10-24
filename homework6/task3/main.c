#include "../../lib/stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

int priority(const char c)
{
    switch (c)
    {
    case '*':
    case '/':
    case '%':
        return 2;

    case '+':
    case '-':
        return 1;
    }
    return 0;
}

char* fromInfixToPostfix(char* expression)
{
    Stack* inputStack = createStack();
    Stack* outputStack = createStack();

    size_t expressionSize = strlen(expression);

    for (int i = 0; i < expressionSize; ++i)
    {
        if ('0' <= expression[i] && expressionSize <= '9')
        {
            push(&outputStack, expression[i]);
        }
        else if ('(' == expression[i])
        {
            push(&inputStack, '(');
        }
        else if (')' == expression[i])
        {
            char item = pop(&inputStack);
            while (item != '(')
            {
                push(&outputStack, item);
                item = pop(&inputStack);
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*')
        {
            while (priority(expression[i]) <= priority(top(inputStack)))
            {
                char value = pop(&inputStack);
                push(&outputStack, value);
            }
            push(&inputStack, expression[i]);
        }
        expression[i] = 0;
    }

    while (stackSize(inputStack) != 0)
    {
        char value = pop(&inputStack);
        push(&outputStack, value);
    }

    for (int i = (stackSize(outputStack) - 1) * 2; i > 0; i -= 2)
    {
        expression[i] = pop(&outputStack);
        expression[i - 1] = ' ';
    }
    expression[0] = pop(&outputStack);

    freeStack(&inputStack);
    freeStack(&outputStack);
}

bool* test(bool* testResults)
{
    char expression1[] = "2 + 2 * 2";
    char expected1[] = "2 2 2 * +";
    fromInfixToPostfix(expression1);
    testResults[0] = strcmp(expression1, expected1) == 0;

    char expression2[] = "9 / (5 - 3)";
    char expected2[] = "9 5 3 - /";
    fromInfixToPostfix(expression2);
    testResults[1] = strcmp(expression2, expected2) == 0;

    char expression3[] = "(7 + 3) * (4 - 2)";
    char expected3[] = "7 3 + 4 2 - *";
    fromInfixToPostfix(expression3);
    testResults[2] = strcmp(expression3, expected3) == 0;

    char expression4[] = "8 / 4 / 2";
    char expected4[] = "8 4 / 2 /";
    fromInfixToPostfix(expression4);
    testResults[3] = strcmp(expression4, expected4) == 0;

    char expression5[] = "1 + 2 + 3 + 4 + 5";
    char expected5[] = "1 2 + 3 + 4 + 5 +";
    fromInfixToPostfix(expression5);
    testResults[4] = strcmp(expression5, expected5) == 0;
}

int main()
{
    bool testResults[5] = { 0 };
    test(testResults);
    for (int i = 0; i < 5; ++i)
    {
        if (!testResults[i])
        {
            printf("TEST %d FAILED\n", i + 1);
        }
    }

    printf("Enter the expression: ");

    char expression[MAX_EXPRESSION_LENGTH] = { 0 };
    if (fgets(expression, MAX_EXPRESSION_LENGTH, stdin) == NULL)
    {
        return -1;
    }

    fromInfixToPostfix(expression);
    printf("\nThe result: %s", expression);
}