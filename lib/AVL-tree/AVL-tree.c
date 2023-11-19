#include "AVL-tree.h"
#include "errorCodes.h"

#include <stdlib.h>
#include <string.h>

struct Node
{
    char* key;
    char* value;
    Node* rightChild;
    Node* leftChild;
    int balance;
};

struct AVLTree
{
    Node* root;
};

AVLTree* createAVLTree()
{
    Node* root = NULL;
    AVLTree* tree = (AVLTree*)calloc(1, sizeof(AVLTree));
    if (tree == NULL)
    {
        return MemoryAllocationError;
    }

    tree->root = root;
    return tree;
}

ErrorCode addElement(const char* key, const char* value, AVLTree** tree)
{
    if ((*tree)->root == NULL)
    {
        Node* node = (Node*)calloc(1, sizeof(Node));
        if (node == NULL)
        {
            return MemoryAllocationError;
        }

        node->key = calloc(strlen(key) + 1, sizeof(char));
        node->value = calloc(strlen(value) + 1, sizeof(char));
        if (node->key == NULL || node->value == NULL)
        {
            free(node->key);
            free(node->value);
            free(node);
            return MemoryAllocationError;
        }
        strcpy(node->key, key);
        strcpy(node->value, value);
        (*tree)->root = node;
        return OK;
    }

    Node** place = findPlaceFor(node, &(*tree)->root); // to redo
    (*place) = node;
    return OK;
}

static void freeTree(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->key);
    free(node->value);
    freeTree(node->leftChild);
    freeTree(node->rightChild);
    free(node);
}

void freeAVLTree(AVLTree* tree)
{
    if (tree == NULL)
    {
        return;
    }
    freeTree(tree->root);
}