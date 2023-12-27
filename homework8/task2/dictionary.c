#include "dictionary.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node
{
    int key;
    char* value;
    Node* leftChild;
    Node* rightChild;
};

Node* createTree()
{
    return NULL;
}

int createLeaf(int key, char* value, Node** tree)
{
    if ((*tree) == NULL)
    {
        Node* leaf = calloc(1, sizeof(Node));
        if (leaf == NULL)
        {
            return -1;
        }
        leaf->key = key;
        leaf->value = strdup(value);
        (*tree) = leaf;
        return 0;
    }
    if (key == (*tree)->key)
    {
        free((*tree)->value);
        (*tree)->value = strdup(value);
        return 0;
    }
    if (key > (*tree)->key)
    {
        createLeaf(key, value, &(*tree)->rightChild);
        return 0;
    }
    createLeaf(key, value, &(*tree)->leftChild);
    return 0;
}

char* get(const int key, Node* tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree->key == key)
    {
        return tree->value;
    }
    else if (key > tree->key && tree->rightChild)
    {
        return get(key, tree->rightChild);
    }
    else if (key < tree->key && tree->leftChild)
    {
        return get(key, tree->leftChild);
    }

    return NULL;
}

bool isContained(const int key, Node* tree)
{
    return get(key, tree) != NULL;
}

static Node* findNearestElement(Node* tree)
{
    if (tree->rightChild == NULL)
    {
        return tree;
    }
    return findNearestElement(tree->rightChild);
}

int deleteNode(const int key, Node** tree)
{
    if (*tree == NULL)
    {
        return 0;
    }

    if (key < (*tree)->key)
    {
        return deleteNode(key, &((*tree)->leftChild));
    }
    if (key > (*tree)->key)
    {
        return deleteNode(key, &((*tree)->rightChild));
    }
    else
    {
        if ((*tree)->leftChild == NULL && (*tree)->rightChild == NULL)
        {
            free((*tree)->value);
            free(*tree);
            *tree = NULL;
        }
        else if ((*tree)->leftChild == NULL)
        {
            Node* temp = *tree;
            *tree = (*tree)->rightChild;
            free(temp->value);
            free(temp);
        }
        else if ((*tree)->rightChild == NULL)
        {
            Node* temp = *tree;
            *tree = (*tree)->leftChild;
            free(temp->value);
            free(temp);
        }
        else
        {
            Node* leafToReplace = findNearestElement((*tree)->leftChild);
            (*tree)->key = leafToReplace->key;
            free((*tree)->value);
            (*tree)->value = strdup(leafToReplace->value);
            deleteNode(leafToReplace->key, &((*tree)->leftChild));
        }

        return 0;
    }
}

void freeTree(Node** node)
{
    if ((*node) == NULL)
    {
        return;
    }

    freeTree(&(*node)->leftChild);
    freeTree(&(*node)->rightChild);
    free((*node)->value);
    free(*node);
}

static void inorderTraversal(const Node* node, int* array, int* index)
{
    if (node == NULL)
    {
        return;
    }

    inorderTraversal(node->leftChild, array, index);
    array[*index] = node->key;
    ++(*index);
    inorderTraversal(node->rightChild, array, index);
}

int* toArray(const Node* tree, const size_t size)
{
    int* array = calloc(size, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }

    int index = 0;
    inorderTraversal(tree, array, &index);

    return array;
}
