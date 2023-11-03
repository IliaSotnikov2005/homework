#include "huffmanTree.h"
#include <stdlib.h>

struct Node
{
    char value;
    size_t count;
    Node* leftChild;
    Node* rightChild;
};

struct HuffmanTree
{
    Node* root;
};

Node* makeLeaf(const char value, const size_t count)
{
    Node* leaf = calloc(1, sizeof(Node));
    leaf->value = value;
    leaf->count = count;
    
    HuffmanTree* tree = calloc(1, sizeof(HuffmanTree));
    tree->root = leaf;
    return tree;
}

HuffmanTree* getCount(HuffmanTree* tree)
{
    return tree->root->count;
}