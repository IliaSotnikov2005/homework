#include "hashTable.h"
#include "../list/list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct HashTable
{
    List** buckets;
    size_t size;
    size_t itemsAmount;
};

HashTable* hashTableCreate()
{
    HashTable* table = calloc(1, sizeof(HashTable));
    if (table == NULL)
    {
        return NULL;
    }

    table->buckets = calloc(8, sizeof(List*));
    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }

    for (size_t i = 0; i < 8; ++i)
    {
        (table->buckets)[i] = listCreate();
    }

    table->size = 8;
    table->itemsAmount = 0;

    return table;
}

static int hash(const char* key)
{
    int result = 0;
    for (int i = 0; key[i] != '\0'; ++i)
    {
        result += key[i];
    }

    return result;
}

static float loadFactor(const HashTable* table)
{
    if (table == NULL)
    {
        return 0;
    }

    return (float)table->itemsAmount / (float)table->size;
}

void hashTablePrint(HashTable* table)
{
    if (table == NULL)
    {
        return;
    }

    for (int i = 0; i < table->size; ++i)
    {
        listPrint(table->buckets[i]);
    }
}

HashTableErrorCode hashTableAdd(const char* key, HashTable* hashTable)
{
    if (hashTable == NULL)
    {
        return HashTableNULLPointerError;
    }

    List** buckets = hashTable->buckets;

    int bucketIndex = hash(key) % hashTable->size;

    ListElement* element = listFind(buckets[bucketIndex], key);
    if (element == NULL)
    {
        listPush(key, 1, buckets[bucketIndex]);
        ++hashTable->itemsAmount;
    }

    listElementChangeValue(element, listElementGetValue(element) + 1);

    return HashTableOK;
}

HashTableErrorCode hashTableGet(const char* key, int* value, HashTable* hashTable)
{
    if (hashTable == NULL)
    {
        return HashTableNULLPointerError;
    }

    List** buckets = hashTable->buckets;

    int bucketIndex = hash(key) % hashTable->size;

    if (listIsEmpty(buckets[bucketIndex]))
    {
        return -5;
    }

    int intValue = 0;
    if (listFind(buckets[bucketIndex], key, &intValue) == HashTableOK)
    {
        *value = intValue;
        return HashTableOK;
    }

    return -5;
}

HashTableErrorCode hashTableFree(HashTable** table)
{
    if ((*table) == NULL)
    {
        return HashTableNULLPointerError;
    }

    for (int i = 0; i < (*table)->size; ++i)
    {
        listFree(&(*table)->buckets[i]);
    }

    free(*table);
    (*table) = NULL;
    
    return HashTableOK;
}