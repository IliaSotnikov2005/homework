#include "lexerOfEmails.h"
#include "test.h"

#include <stdlib.h>
#include <stdbool.h>

int test(void)
{
    char input[8][30] =
    {
        "john.doe@example.com",
        "mary-ann.smith123@gmail.co.uk",
        "bob+jones%22@my-website.net",
        "user_name123@sub.domain.org",
        "invalid_email@.com",
        "user@invalid_domain",
        "user123@example..com",
        "user@website@domain.com"
    };

    bool expected[8] = { true, true, true, true, false, false, false, false };

    for (size_t i = 0; i < 8; ++i)
    {
        if (isEmailAddress(input[i]) != expected[i])
        {
            return i + 1;
        }
    }

    return 0;
}