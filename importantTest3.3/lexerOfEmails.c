#include "lexerOfEmails.h"

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum States
{
    start = 0,
    nameSymbol = 1,
    atSymbol = 2,
    domainSymbol = 3,
    domainDigit = 4,
    domainTopLevelLetter = 5,
    domainNotTopLevelLetter = 6,
    domainDot = 7
} States;

bool isEmailAddress(const char* string)
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
            if (isdigit(current) || isalpha(current) || strchr(".%+-_", current) != NULL)
            {
                state = nameSymbol;
                break;
            }

            return false;
        }
        case nameSymbol:
        {
            if (isdigit(current) || isalpha(current) || strchr(".%+-_", current) != NULL)
            {
                break;
            }
            else if (current == '@')
            {
                state = atSymbol;
                break;
            }

            return false;
        }
        case atSymbol:
        {
            if (isalpha(current))
            {
                state = domainNotTopLevelLetter;
                break;
            }
            else if (strchr("-.", current) != NULL)
            {
                state = domainSymbol;
                break;
            }
            else if (isdigit(current))
            {
                state = domainDigit;
                break;
            }

            return false;
        }
        case domainSymbol:
        {
            if (current == '-')
            {
                break;
            }
            else if (isalpha(current))
            {
                state = domainNotTopLevelLetter;
                break;
            }
            else if (isdigit(current))
            {
                state = domainDigit;
                break;
            }
            else if (current == '.')
            {
                state = domainDot;
                break;
            }
            
            return false;
        case domainDigit:
        {
            if (current == '-')
            {
                state = domainSymbol;
                break;
            }
            else if (isalpha(current))
            {
                state = domainNotTopLevelLetter;
                break;
            }
            else if (isdigit(current))
            {
                break;
            }
            else if (current == '.')
            {
                state = domainDot;
                break;
            }

            return false;
        }
        case domainTopLevelLetter:
        {
            if (isalpha(current))
            {
                break;
            }
            if (current == '-')
            {
                state = domainSymbol;
                break;
            }
            else if (isdigit(current))
            {
                state = domainDigit;
                break;
            }
            else if (current == '.')
            {
                state = domainDot;
                break;
            }

            return false;
        }
        case domainNotTopLevelLetter:
        {
            if (isalpha(current))
            {
                break;
            }
            if (current == '-')
            {
                state = domainSymbol;
                break;
            }
            else if (isdigit(current))
            {
                state = domainDigit;
                break;
            }
            else if (current == '.')
            {
                state = domainDot;
                break;
            }

            return false;
        }
        case domainDot:
        {
            if (isalpha(current))
            {
                state = domainTopLevelLetter;
                break;
            }

            else if (isdigit(current))
            {
                state = domainDigit;
                break;
            }
            
            return false;
        }
        default:
            break;
        }
        }

        ++index;
        current = string[index];
    }

    return state == domainTopLevelLetter;
}