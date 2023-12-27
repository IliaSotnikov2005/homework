#include "infixToPostfixConverter.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int getPriority(const char sign)
{
    switch (sign)
    {
    case '*':
    case '/':
    case '%':
    {
        return 2;
    }
    case '+':
    case '-':
    {
        return 1;
    }
    }

    return 0;
}

ConverterErrorCode convertInfixToPostfix(char* expression)
{
    Stack* inputStack = stackCreate();
    if (inputStack == NULL)
    {
        return converterMemoryAllocationError;
    }

    size_t index = 0;
    bool numberExpected = true;

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        bool allowed—har = expression[i] == ' ' || expression[i] == '\n';

        if ('0' <= expression[i] && expression[i] <= '9')
        {
            if (!numberExpected)
            {
                stackFree(&inputStack);
                expression[0] = '\0';
                return converterIncorrectExpressionFormat;
            }
            numberExpected = false;
            allowed—har = true;
            expression[index] = expression[i];
            expression[index + 1] = ' ';
            index += 2;
        }
        else if ('(' == expression[i])
        {
            allowed—har = true;
            stackPush(inputStack, '(');
        }
        else if (')' == expression[i])
        {
            allowed—har = true;
            char item = '\0';
            stackPop(inputStack, &item);
            while (item != '(')
            {
                expression[index] = item;
                expression[index + 1] = ' ';
                index += 2;
                stackPop(inputStack, &item);
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*')
        {
            if (numberExpected)
            {
                stackFree(&inputStack);
                expression[0] = '\0';
                return converterIncorrectExpressionFormat;
            }
            numberExpected = true;
            allowed—har = true;
            while (getPriority(expression[i]) <= getPriority(stackTop(inputStack)))
            {
                char value = '\0';
                stackPop(inputStack, &value);
                expression[index] = value;
                expression[index + 1] = ' ';
                index += 2;
            }
            stackPush(inputStack, expression[i]);
        }
        if (!allowed—har)
        {
            expression[0] = '\0';
            stackFree(&inputStack);
            return converterIncorrectExpressionFormat;
        }

        if (index < i)
        {
            expression[i] = '\0';
        }
    }

    while (stackSize(inputStack) != 0)
    {
        char value = '\0';
        stackPop(inputStack, &value);
        expression[index] = value;
        expression[index + 1] = ' ';
        index += 2;
    }
    expression[index - 1] = '\0';

    stackFree(&inputStack);

    return converterOk;
}