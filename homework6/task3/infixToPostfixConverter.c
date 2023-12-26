#include "infixToPostfixConverter.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>

static int getPriority(const char c)
{
    switch (c)
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

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        if ('0' <= expression[i] && expression[i] <= '9')
        {
            expression[index] = expression[i];
            ++index;
        }
        else if ('(' == expression[i])
        {
            stackPush(inputStack, '(');
        }
        else if (')' == expression[i])
        {
            char item = '\0';
            stackPop(inputStack, &item);
            while (item != '(')
            {
                expression[index] = item;
                stackPop(inputStack, &item);
                ++index;
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*')
        {
            while (getPriority(expression[i]) <= getPriority(stackTop(inputStack)))
            {
                char value = '\0';
                stackPop(inputStack, &value);
                expression[index] = value;
                ++index;
            }
            stackPush(inputStack, expression[i]);
        }
        expression[i] = 0;
    }

    while (stackSize(inputStack) != 0)
    {
        char value = '\0';
        stackPop(inputStack, &value);
        expression[index] = value;
        ++index;
    }

    stackFree(&inputStack);

    return converterOk;
}