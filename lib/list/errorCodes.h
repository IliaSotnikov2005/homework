#pragma once

typedef enum ErrorCode
{
    OK = 0,
    MemoryAllocationError = -1,
    NULLPointerError = -2,
    ListIndexOutOfRange = -3
} ErrorCode;