#pragma once

// Error codes
typedef enum ErrorCode
{
    ok = 0,
    fileNotFound = -1,
    errorCreatingTheTable = -2
} ErrorCode;

// Comment lexer
char* commentLexer(const char* filename);