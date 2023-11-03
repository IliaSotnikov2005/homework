#include "huffmanTree.h"
#include "huffman.h"
#include <string.h>
#include <stdlib.h>

void insertionSortStep(HuffmanTree* const* const array, const size_t index)
{
    for (size_t i = index; i >= 1; --i)
    {
        if (array[])
    }
}

char* const compress(const char* string, size_t* const resultSize)
{
    size_t* const charCount = calloc(256, sizeof(size_t));
    const size_t stringLength = strlen(string);

    for (int i = 0; i < stringLength; ++i)
    {
        ++charCount[string[i]];
    }

    HuffmanTree** treeArray = calloc(256, sizeof(HuffmanTree*));
    for (int i = 0; i < 256; ++i)
    {
        treeArray[i] = makeLeaf(string[i], charCount[i]);
    }
}