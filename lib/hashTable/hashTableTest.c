#include "../list/list.h"
#include "hashTable.h"
#include "hashTableTest.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    HashTable* table = hashTableCreate();
    hashTableAdd("bo", table);
    hashTableAdd("bo", table);
    hashTableAdd("rr", table);
    hashTableAdd("bo", table);
    hashTableAdd("dsao", table);
    hashTablePrint(table);

    hashTableFree(&table);
    hashTablePrint(table);
    table = hashTableCreate();
    hashTableAdd("bo", table);
    hashTableAdd("bo", table);
    hashTablePrint(table);
}