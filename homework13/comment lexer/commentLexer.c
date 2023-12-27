#include "commentLexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 7
#define COLUMNS 3

static enum States
{
    start = 0,
    end = 5
};

static int tableCreate(int table[ROWS][COLUMNS])
{
    FILE* tableFile = fopen("table.txt", "r");
    if (tableFile == NULL)
    {
        return -1;
    }

    for (size_t row = 0; row < ROWS; ++row)
    {
        for (size_t column = 0; column < COLUMNS; ++column)
        {
            if (row == 0)
            {
                int symbol = fgetc(tableFile);
                if (symbol == EOF)
                {
                    fclose(tableFile);
                    return -2;
                }
                table[row][column] = symbol;
                fgetc(tableFile);
                continue;
            }
            
            if (fscanf(tableFile, "%d", &table[row][column]) == 0)
            {
                fclose(tableFile);
                return -2;
            }
        }
    }

    fclose(tableFile);

    return 0;
}

static int nextState(const int state, const char symbol, const int table[ROWS][COLUMNS])
{
    for (size_t i = 0; i < COLUMNS - 1; ++i)
    {
        if (symbol == table[0][i])
        {
            return table[state + 1][i];
        }
    }

    return table[state + 1][COLUMNS - 1];
}

char* commentLexer(const char* filename)
{
    char* comments = calloc(100, sizeof(char));
    if (comments == NULL)
    {
        return NULL;
    }

    int table[ROWS][COLUMNS] = { 0 };
    if (tableCreate(table) != ok)
    {
        return errorCreatingTheTable;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return fileNotFound;
    }

    int state = start;
    char buffer[101] = { 0 };
    size_t index = 0;
    char symbol = fgetc(file);

    while (!feof(file))
    {
        state = nextState(state, symbol, table);
        if (state == start)
        {
            index = 0;
        }
        if (state == end)
        {
            buffer[index] = symbol;
            ++index;
            buffer[index] = '\0';
            strcat(comments, buffer);
        }

        buffer[index] = symbol;
        ++index;
        symbol = fgetc(file);
    }
    fclose(file);
    return comments;
}