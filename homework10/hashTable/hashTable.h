#pragma once

#include <stdlib.h>

// Hash table error codes
typedef enum HashTableErrorCode
{
    HashTableOK = 0,
    HashTableMemoryAllocationError = -1,
    HashTableNULLPointerError = -2
} HashTableErrorCode;

typedef struct HashTable HashTable;

// Create hash table
HashTable* hashTableCreate(const size_t size);

// Get hash table fill factor, 0 if nullptr
float hashTablefillFactor(const HashTable* table);

// Add word to hash table
HashTableErrorCode hashTableAdd(const char* key, HashTable** hashTable);

// Print hash table
void hashTablePrint(HashTable* table);

// Max list length inside hash table
int hashTableMaxListLength(HashTable* table);

// Average list lenght inside hash table
float hashTableAverageListLength(HashTable* table);

// Free hash table
HashTableErrorCode hashTableFree(HashTable * *table);