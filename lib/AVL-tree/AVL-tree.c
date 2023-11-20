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
    int height;
};

struct AVLTree
{
    Node* root;
};

AVLTree* createAVLTree()
{
    AVLTree* tree = calloc(1, sizeof(AVLTree));
    if (tree == NULL)
    {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}

static unsigned int height(Node* node)
{
    return (node != NULL) ? node->height : 0;
}

static fixHeight(Node* node)
{
    unsigned int heightLeft = height(node->leftChild);
    unsigned int heightRight = height(node->rightChild);
    node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

static int balanceFactor(Node* node)
{
    return height(node->rightChild) - height(node->leftChild);
}

static Node* rotateRight(Node* node)
{
    Node* left = node->leftChild;
    node->leftChild = left->rightChild;
    left->rightChild = node;
    
    fixHeight(node);
    fixHeight(left);

    return left;
}

static Node* rotateLeft(Node* node)
{
    Node* right = node->rightChild;
    node->rightChild = right->leftChild;
    right->leftChild = node;

    fixHeight(node);
    fixHeight(right);

    return right;
}

static Node* balance(Node** node)
{
    if ((*node) == NULL)
    {
        return NULL;
    }

    fixHeight((*node));
    if (balanceFactor((*node)) == 2)
    {
        if (balanceFactor((*node)->rightChild) < 0)
        {
            (*node)->rightChild = rotateRight((*node)->rightChild);
        }
        return rotateLeft((*node));
    }
    if (balanceFactor((*node)) == -2)
    {
        if (balanceFactor((*node)->leftChild) > 0)
        {
            (*node)->leftChild = rotateLeft((*node)->leftChild);
        }
        return rotateRight((*node));
    }

    return (*node);
}

static ErrorCode insertElement(Node** node, const char* key, const char* value)
{
    if ((*node) == NULL)
    {
        Node* newNode = (Node*)calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            return MemoryAllocationError;
        }
        newNode->key = calloc(strlen(key) + 1, sizeof(char));
        newNode->value = calloc(strlen(value) + 1, sizeof(char));
        newNode->height = 1;
        if (newNode->key == NULL || newNode->value == NULL)
        {
            free(newNode->key);
            free(newNode->value);
            free(newNode);
            return MemoryAllocationError;
        }
        strcpy(newNode->key, key);
        strcpy(newNode->value, value);
        (*node) = newNode;
        return OK;
    }

    int compareResult = strcmp((*node)->key, key);
    if (compareResult == 0)
    {
        free((*node)->value);
        (*node)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*node)->value == NULL)
        {
            return MemoryAllocationError;
        }
        strcpy((*node)->value, value);
        return OK;
    }

    if (compareResult > 0)
    {
        insertElement(&(*node)->leftChild, key, value);
    }

    if (compareResult < 0)
    {
        insertElement(&(*node)->rightChild, key, value);
    }

    fixHeight((*node));
    return OK;
}

ErrorCode addElement(const char* key, const char* value, AVLTree* tree)
{
    ErrorCode errorCode = insertElement(&tree->root, key, value);
    if (errorCode)
    {
        return errorCode;
    }
    tree->root = balance(&(tree->root));
    return OK;
}

static char* find(const char* key, Node* node)
{
    if (node == NULL)
    {
        return NULL;
    }

    int compareResult = strcmp(node->key, key);
    if (compareResult == 0)
    {
        return node->value;
    }
    if (compareResult > 0)
    {
        return find(key, node->leftChild);
    }

    return find(key, node->rightChild);
}

char* get(char* key, AVLTree* tree)
{
    return tree ? find(key, tree->root) : NULL;
}

static Node* findClosest(Node* node)
{
    return node->leftChild ? findClosest(node->leftChild) : node;
}

static void freeNode(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->key);
    free(node->value);
    free(node);
}

Node* removeClosest(Node* node)
{
    if (node->leftChild == NULL)
    {
        return node->rightChild;
    }
    node->leftChild = removeClosest(node->leftChild);
    return balance(node);
}

static Node* deleteNode(const char* key, Node* node)
{
    if (node == NULL)
    {
        return OK;
    }

    int compareResult = strcmp(node->key, key);
    if (compareResult == 0)
    {
        Node* leftChild = node->leftChild;
        Node* rightChild = node->rightChild;
        if (rightChild == NULL)
        {
            freeNode(rightChild);
            return leftChild;
        }
        Node* closest = findClosest(rightChild);
        closest->rightChild = deleteNode(closest->key, rightChild);
        closest->leftChild = leftChild;
        return balance(&closest);
    }
    if (compareResult > 0)
    {
        node->leftChild = deleteNode(key, node->leftChild);
    }
    if (compareResult < 0)
    {
        node->rightChild = deleteNode(key, node->rightChild);
    }

    return balance(&node);
}

ErrorCode deleteElement(const char* key, AVLTree* tree)
{
    if (tree == NULL)
    {
        return OK;
    }
    tree->root = deleteNode(key, tree->root);

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
    freeAVLTree(node->leftChild);
    freeAVLTree(node->rightChild);
    free(node);
}

void freeAVLTree(AVLTree* tree)
{
    if (tree == NULL)
    {
        return;
    }
    freeTree(tree->root);
    free(tree);
}
