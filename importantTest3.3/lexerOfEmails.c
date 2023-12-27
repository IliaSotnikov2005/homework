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
    domainDot = 4,
    topLevelDomain = 5,
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
            if (isdigit(current) || isalpha(current) || strchr("-.", current) != NULL)
            {
                state = domainSymbol;
                break;
            }

            return false;
        }
        case domainSymbol:
        {
            if (isalpha(current) || isdigit(current) || current == '-')
            {
                break;
            }
            else if (current == '.')
            {
                state = domainDot;
                break;
            }
            
            return false;
        case domainDot:
        {
            if (isalpha(current))
            {
                state = topLevelDomain;
                break;
            }
            
            return false;
        }
        case topLevelDomain:
        {
            if (isalpha(current))
            {
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

    return state == topLevelDomain;
}