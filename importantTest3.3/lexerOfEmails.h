#pragma once

#include <stdbool.h>

// Lexer error codes.
typedef enum lexerErrorCode
{
    lexerOk = 0
} lexerErrorCode;

// Checks if given string is email address.
bool isEmailAddress(const char* string);