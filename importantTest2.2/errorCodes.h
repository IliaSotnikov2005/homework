#pragma once

// Error codes
typedef enum ErrorCode
{
    ok = 0,
    memoryAllocationError = -1,
    nullPointerError = -2,
    stackIsEmptyError = -3,
    queueIsEmpty = -3
} ErrorCode;