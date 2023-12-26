#include "infixToPostfixConverter.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>

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

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        if ('0' <= expression[i] && expression[i] <= '9')
        {
            expression[index] = expression[i];
            expression[index + 1] = ' ';
            index += 2;
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
                expression[index + 1] = ' ';
                index += 2;
                stackPop(inputStack, &item);
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*')
        {
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
        if (index - 1 < i)
        {
            expression[i] = '\0';
        }
    }

    while (stackSize(inputStack) != 0)
    {
        char value = '\0';
        stackPop(inputStack, &value);
        expression[index] = value;
    }

    stackFree(&inputStack);

    return converterOk;
}