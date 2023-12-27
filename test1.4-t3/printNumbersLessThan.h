#pragma once

typedef enum PrinterErrorCode
{
    printerOk = 0,
    printerFileNotFound = -1,
    printerFileCreationError = -2,
    printerInvalidInput = -3
} PrinterErrorCode;

// Print numbers less than number X from another file to new file.
PrinterErrorCode fprintNumbersLessThan(const char* source, const char* fileWithNumber, const char* destination);