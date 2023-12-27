#include "hashTable.h"
#include "hashTableTest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int test()
{
    bool testResults[6] = { 0 };
    HashTable* table = hashTableCreate(2);
    if (table == NULL)
    {
        return 1;
    }

    testResults[0] = hashTableAdd("alo", &table) == HashTableOK;
    testResults[1] = hashTableAdd("alo", &table) == HashTableOK;
    testResults[2] = hashTableAdd("bob", &table) == HashTableOK;
    testResults[3] = hashTableMaxListLength(table) == 1;
    testResults[4] = hashTableAdd("vovanchik", &table) == HashTableOK;
    float a = hashTablefillFactor(table);
    testResults[5] = hashTablefillFactor(table) == (float)3 / (float)4;

    for (unsigned int i = 0; i < 6; ++i)
    {
        if (!testResults[i])
        {
            hashTableFree(&table);
            return i + 2;
        }
    }

    hashTableFree(&table);

    return 0;
}