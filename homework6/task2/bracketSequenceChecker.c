#include "bracketSequenceChecker.h"
#include "stack.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static char findLeftPair(const char rightBracket)
{
    if (rightBracket == ')')
    {
        return '(';
    }
    if (rightBracket == '}')
    {
        return '{';
    }
    if (rightBracket == ']')
    {
        return '[';
    }
}

bool isCorrectBracketSequence(const char* string)
{
    Stack* stack = stackCreate();
    if (stack == NULL)
    {
        return false;
    }

    size_t size = strlen(string);

    for (size_t i = 0; i < size; ++i)
    {
        if (strchr("({[", string[i]))
        {
            stackPush(stack, string[i]);
        }
        else if (strchr(")]}", string[i]))
        {
            if (stackSize(stack) == 0)
            {
                stackFree(&stack);
                return false;
            }
            else
            {
                char bracket = '\0';
                stackPop(stack, &bracket);
                if (findLeftPair(string[i]) != bracket)
                {
                    stackFree(&stack);
                    return false;
                }
            }
        }
    }

    if (stackSize(stack) == 0)
    {
        stackFree(&stack);
        return true;
    }

    stackFree(&stack);
    return false;
}