#include "../../lib/stack.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Stack* stack = NULL;
    char symbol = 0;
    int operand1 = 0;
    int operand2 = 0;
    int result = 0;

    while ((symbol = getchar()) != EOF)
    {
        if (symbol == ' ')
        {
            continue;
        }
        if (symbol == '\n')
        {
            break;
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
    printf("Result is %d", top(stack));

    freeStack(&stack);
}