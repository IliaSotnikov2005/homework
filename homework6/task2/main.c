#include "../../lib/stack.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

char findLeftPair(char rightBracket)
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

bool isCorrect(const char* string, const size_t size)
{
    Stack* stack = createStack();
    for (int i = 0; i < size; ++i)
    {
        if (strchr("({[", string[i]))
        {
            push(&stack, string[i]);
        }
        else if (strchr(")]}", string[i]))
        {
            if (stackSize(stack) == 0)
            {
                return false;
            }
            else
            {
                if (!(findLeftPair(string[i]) == pop(&stack)))
                {
                    return false;
                }
            }
        }
    }
    if (stackSize(stack) == 0)
    {
        freeStack(&stack);
        return true;
    }
    freeStack(&stack);
    return false;
}

int main()
{
    char string[MAX_LENGTH] = { 0 };
    if (scanf_s("%s", string, MAX_LENGTH) == NULL)
    {
        return -1;
    }

    printf(isCorrect(string, strlen(string)) ? "\nCorrect" : "\nIncorrect");
}