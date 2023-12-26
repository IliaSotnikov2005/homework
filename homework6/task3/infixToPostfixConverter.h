#pragma once

// Converter error codes.
typedef enum ConverterErrorCode
{
    converterOk = 0,
    converterMemoryAllocationError = -1
} ConverterErrorCode;

// Convert infix to postfix.
int convertInfixToPostfix(char* expression);