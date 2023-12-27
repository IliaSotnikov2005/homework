#include "hashTable.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct HashTable
{
    List** buckets;
    size_t size;
    size_t itemsAmount;
};

HashTable* hashTableCreate(const size_t size)
{
    HashTable* table = calloc(1, sizeof(HashTable));
    if (table == NULL)
    {
        return NULL;
    }

    table->buckets = calloc(size, sizeof(List*));
    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }

    for (size_t i = 0; i < size; ++i)
    {
        (table->buckets)[i] = listCreate();
        if (table->buckets[i] == NULL)
        {
            hashTableFree(&table);
            return NULL;
        }
    }

    table->size = size;
    table->itemsAmount = 0;

    return table;
}

static int hash(const char* key)
{
    int result = 351512341234;
    for (int i = 0; key[i] != '\0'; ++i)
    {
        result += 37 * result + key[i];
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

static HashTableErrorCode hashTableInsert(const char* key, const int value, HashTable* hashTable)
{
    if (hashTable == NULL)
    {
        return HashTableNULLPointerError;
    }

    List** buckets = hashTable->buckets;

    int bucketIndex = hash(key) % hashTable->size;

    listPush(key, value, buckets[bucketIndex]);
    ++hashTable->itemsAmount;

    return HashTableOK;
}

static HashTableErrorCode extend(HashTable** table)
{
    if (table == NULL)
    {
        return HashTableNULLPointerError;
    }
    if (*table == NULL)
    {
        return HashTableNULLPointerError;
    }

    HashTable* newHashTable = hashTableCreate((*table)->size * 2);
    for (size_t i = 0; i < (*table)->size; ++i)
    {
        List* bucket = (*table)->buckets[i];
        if (!listIsEmpty(bucket))
        {
            char** keys = NULL;
            int* values = NULL;
            listGetItems(bucket, &keys, &values);
            for (size_t i = 0; i < listSize(bucket); ++i)
            {
                hashTableInsert(keys[i], values[i], newHashTable);
                free(keys[i]);
            }
            free(keys);
            free(values);
        }
    }

    hashTableFree(table);
    (*table) = newHashTable;

    return HashTableOK;
}

HashTableErrorCode hashTableAdd(const char* key, HashTable** hashTable)
{
    if (hashTable == NULL)
    {
        return HashTableNULLPointerError;
    }
    if (*hashTable == NULL)
    {
        return HashTableNULLPointerError;
    }

    if (loadFactor(*hashTable) > 0.75)
    {
        extend(hashTable);
    }
    List** buckets = (*hashTable)->buckets;

    int bucketIndex = hash(key) % (*hashTable)->size;

    if (listIsEmpty(buckets[bucketIndex]))
    {
        ++(*hashTable)->itemsAmount;
    }

    ListElement* element = listFind(buckets[bucketIndex], key);
    if (element == NULL)
    {
        listPush(key, 1, buckets[bucketIndex]);
        return HashTableOK;
    }

    listElementChangeValue(element, listElementGetValue(element) + 1);

    return HashTableOK;
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

float hashTablefillFactor(const HashTable* table)
{
    return table == NULL ? 0 : (float)table->itemsAmount / (float)table->size;
}

int hashTableMaxListLength(HashTable* table)
{
    List** buckets = table->buckets;
    int result = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        int size = listSize(buckets[i]);
        if (size > result)
        {
            result = listSize(buckets[i]);
        }
    }

    return result;
}

float hashTableAverageListLength(HashTable* table)
{
    List** buckets = table->buckets;
    float result = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        result += listSize(buckets[i]);
    }

    result /= (float)table->itemsAmount;

    return result;
}

HashTableErrorCode hashTableFree(HashTable** table)
{
    if (table == NULL)
    {
        return HashTableNULLPointerError;
    }
    if ((*table) == NULL)
    {
        return HashTableNULLPointerError;
    }

    for (size_t i = 0; i < (*table)->size; ++i)
    {
        listFree(&((*table)->buckets[i]));
    }

    free(*table);
    (*table) = NULL;

    return HashTableOK;
}