#include "../list/list.h"
#include "hashTable.h"
#include "hashTableTest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

HashTable* countWords(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    HashTable* table = hashTableCreate(8);
    if (table == NULL)
    {
        return NULL;
    }

    char buffer[100] = { 0 };
    while (fgets(buffer, 100, file) != NULL)
    {
        char* word = strtok(buffer, " ");
        while (word != NULL)
        {
            for (char* i = word; *i; ++i)
            {
                *i = tolower(*i);
            }

            hashTableAdd(word, &table);
            word = strtok(NULL, " ");
        }
    }

    return table;
}

int main()
{
    HashTable* table = countWords("text.txt");
    hashTablePrint(table);
}