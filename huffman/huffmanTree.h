#pragma once

typedef struct Node Node;
typedef struct HuffmanTree HuffmanTree;

// create leaf
Node* makeLeaf(const char value, const unsigned int count);