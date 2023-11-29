#include "../../lib/hashTable/hashTable.h"
#include "../../lib/hashTable/hashTableTest.h"

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
                if (ispunct(*i) || *i == '\n')
                {
                    *i = '\0';
                }
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

    printf("Words and their number in the text: \n");
    hashTablePrint(table);
    printf("\nFill factor: %f\n", hashTablefillFactor(table));
    printf("\nMax length of list: %d\n", hashTableMaxListLenght(table));
    printf("\nAverage length of list: %f\n", hashTableAverageListLenght(table));

    hashTableFree(&table);
}