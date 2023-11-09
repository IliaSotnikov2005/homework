#include "huffmanTree.h"
#include <stdlib.h>

typedef struct Node
{
    char value;
    size_t count;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct HuffmanTree
{
    Node* root;
};

const HuffmanTree* makeLeaf(const char value, const size_t count)
{
    Node* leaf = (Node*)calloc(1, sizeof(Node));
    if (leaf == NULL)
    {
        return NULL;
    }
    leaf->value = value;
    leaf->count = count;

    HuffmanTree* tree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    if (tree == NULL)
    {
        free(leaf);
        return NULL;
    }
    tree->root = tree;

    return tree;
}

const int getCount(HuffmanTree* tree)
{
    return tree->root->count;
}