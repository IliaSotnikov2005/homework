#pragma once

// Error codes
typedef enum findMostFrequentErrorCode
{
    findMostFrequentOk = 0,
    findMostFrequentFileNotFound = -1,
    findMostFrequentInvalidInput = -2,
    findMostFrequentMemoryAllocationError = -3
} findMostFrequentErrorCode;

// Find most frequent element
int findMostFrequent(const char* filename, findMostFrequentErrorCode* errorCode);