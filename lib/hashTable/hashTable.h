#pragma once

typedef enum HashTableErrorCode
{
    HashTableOK = 0,
    HashTableMemoryAllocationError = -1,
    HashTableNULLPointerError = -2
} HashTableErrorCode;

typedef struct HashTable HashTable;

HashTable* hashTableCreate(const size_t size);

void hashTablePrint(HashTable* table);

HashTableErrorCode hashTableAdd(const char* key, HashTable** hashTable);

HashTableErrorCode hashTableFree(HashTable** table);