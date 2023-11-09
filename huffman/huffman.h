#pragma once

#include "huffmanTree.h"
#include <stdlib.h>

// insertion sort step
void insertionSortStep(const HuffmanTree** const array, const size_t index);

// insertion sort
void insertionSort(const HuffmanTree** const array, const size_t size);

// compress
char* const compress(const char* string, size_t* const resultSize);