#include "huffman.h"
#include "huffmanTree.h"

#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

void insertionSortStep(const HuffmanTree** const array, const size_t index)
{
    for (size_t i = index; i >= 1 && getCount(array[i - 1]) < getCount(array[i]); --i)
    {
        const HuffmanTree* temporary = array[i];
        array[i] = array[i - 1];
        array[i - 1] = temporary;
    }
}

void insertionSort(const HuffmanTree** const array, const size_t size)
{
    for (size_t i = 1; i < size; ++i)
    {
        insertionSortStep(array, i);
    }
}

char* const compress(const char* const string, size_t* const resultSize)
{
    size_t* const charCount = (size_t*)calloc(ALPHABET_SIZE, sizeof(size_t));
    if (charCount == NULL)
    {
        return NULL;
    }
    size_t stringLength = strlen(string);

    for (size_t i = 0; i < stringLength; ++i)
    {
        ++charCount[string[i]];
    }

    HuffmanTree** treeArray = (HuffmanTree**)calloc(ALPHABET_SIZE, sizeof(HuffmanTree*));
    if (treeArray == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; ++i)
    {
        treeArray[i] = makeLeaf((char)i, charCount[i]);
    }

    insertionSort(treeArray, ALPHABET_SIZE);
}