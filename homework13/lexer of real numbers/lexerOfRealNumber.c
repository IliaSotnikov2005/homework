#include "lexerOfRealNumber.h"
#include <ctype.h>

#include <stdlib.h>
#include <stdbool.h>

typedef enum States
{
    start = 0,
    digit = 1,
    point = 2,
    afterPointDigit = 3,
    exponent = 4,
    exponentSign = 5,
    afterExponentDigit = 6,
    end = 7
} States;

bool isRealNumber(const char* string)
{
    unsigned int state = start;
    size_t index = 0;
    char current = string[0];
    while (current != '\0')
    {
        switch (state)
        {
        case start:
        {
            if (isspace(current))
            {
                state = end;
                break;
            }
            if (isdigit(current))
            {
                state = digit;
                break;
            }

            return false;
        }
        case digit:
        {
            if (isdigit(current))
            {
                break;
            }
            if (current == '.')
            {
                state = point;
                break;
            }
            if (current == 'E')
            {
                state = exponent;
                break;
            }
            if (isspace(current))
            {
                state = end;
                break;
            }

            return false;
        }
        case point:
        {
            if (isdigit(current))
            {
                state = afterPointDigit;
                break;
            }

            return false;
        }
        case afterPointDigit:
        {
            if (isdigit(current))
            {
                break;
            }
            if (current == 'E')
            {
                state = exponent;
                break;
            }
            if (isspace(current))
            {
                state = end;
                break;
            }

            return false;
        }
        case exponent:
        {
            if (current == '-' || current == '+')
            {
                state = exponentSign;
                break;
            }
            if (isdigit(current))
            {
                state = afterExponentDigit;
                break;
            }
            
            return false;
        }
        case exponentSign:
        {
            if (isdigit(current))
            {
                state = afterExponentDigit;
                break;
            }

            return false;
        }
        case afterExponentDigit:
        {
            if (isdigit(current))
            {
                break;
            }

            return false;
        }
        case end:
        {
            return true;
        }
        default:
        {
            break;
        }
        }
        ++index;
        current = string[index];
    }

    return state == digit || state == afterPointDigit || state == afterExponentDigit || state == end;
}