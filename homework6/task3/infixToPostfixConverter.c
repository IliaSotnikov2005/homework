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

    Stack* outputStack = stackCreate();
    if (outputStack == NULL)
    {
        return converterMemoryAllocationError;
    }

    size_t expressionSize = strlen(expression);

    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        if ('0' <= expression[i] && expression[i] <= '9')
        {
            stackPush(outputStack, expression[i]);
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
                stackPush(outputStack, item);
                stackPop(inputStack, &item);
            }
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*')
        {
            while (getPriority(expression[i]) <= getPriority(stackTop(inputStack)))
            {
                char value = '\0';
                stackPop(inputStack, &value);
                stackPush(outputStack, value);
            }
            stackPush(inputStack, expression[i]);
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