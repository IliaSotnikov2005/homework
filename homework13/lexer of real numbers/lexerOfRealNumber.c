#include "lexerOfRealNumber.h"
#include <ctype.h>

#include <stdlib.h>
#include <stdbool.h>

typedef enum State
{
    start,
    digit,
    point,
    afterPointDigit,
    exponent,
    exponentSign,
    afterExponentDigit,
    end
} State;

static bool startState(State* state, const char current)
{
    if (isdigit(current))
    {
        *state = digit;
        return true;
    }

    return false;
}

static bool digigtState(State* state, const char current)
{
    if (isdigit(current))
    {
        return true;
    }
    if (current == '.')
    {
        *state = point;
        return true;
    }
    if (current == 'E')
    {
        *state = exponent;
        return true;
    }

    return false;
}

static bool pointState(State* state, const char current)
{
    if (isdigit(current))
    {
        *state = afterPointDigit;
        return true;
    }

    return false;
}

static bool afterPointDigitState(State* state, const char current)
{
    if (isdigit(current))
    {
        return true;
    }
    if (current == 'E')
    {
        *state = exponent;
        return true;
    }

    return false;
}

static bool exponentState(State* state, const char current)
{
    if (current == '-' || current == '+')
    {
        *state = exponentSign;
        return true;
    }
    if (isdigit(current))
    {
        *state = afterExponentDigit;
        return true;
    }

    return false;
}

static bool exponentSignState(State* state, const char current)
{
    if (isdigit(current))
    {
        *state = afterExponentDigit;
        return true;
    }

    return false;
}

static bool afterExponentDigitState(State* state, const char current)
{
    if (isdigit(current))
    {
        return true;
    }

    return false;
}

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
            if (startState(&state, current))
            {
                break;
            }

            return false;
        }
        case digit:
        {
            if (digigtState(&state, current))
            {
                break;
            }

            return false;
        }
        case point:
        {
            if (pointState(&state, current))
            {
                break;
            }

            return false;
        }
        case afterPointDigit:
        {
            if (afterPointDigitState(&state, current))
            {
                break;
            }

            return false;
        }
        case exponent:
        {
            if (exponentState(&state, current))
            {
                break;
            }
            
            return false;
        }
        case exponentSign:
        {
            if (exponentSignState(&state, current))
            {
                break;
            }

            return false;
        }
        case afterExponentDigit:
        {
            if (afterExponentDigitState(&state, current))
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