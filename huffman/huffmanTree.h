#pragma once

typedef struct HuffmanTree HuffmanTree;

// make leaf
const HuffmanTree* makeLeaf(const char value, const size_t count);

// get count
const int getCount(HuffmanTree* tree);