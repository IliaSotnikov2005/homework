#include "dictionaty.h"
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
    Node* root = calloc(1, sizeof(Node));
    root = NULL;
    return root;
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
        return "not in dictionary";
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

    return "not in dictionary";
}

bool isContained(const int key, Node* tree)
{
    if (tree == NULL)
    {
        return false;
    }
    if (tree->key == key)
    {
        return true;
    }
    else if (key > tree->key && tree->rightChild)
    {
        return isContained(key, tree->rightChild);
    }
    else if (key < tree->key && tree->leftChild)
    {
        return isContained(key, tree->leftChild);
    }

    return false;
}

int deleteNode(const int key, Node** tree) {
    if (*tree == NULL)
    {
        free(*tree);
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
            (*tree)->value = strdup(leafToReplace->value);
            deleteNode(leafToReplace->key, &((*tree)->leftChild));
        }

        return 0;
    }
}

Node* findNearestElement(Node* tree)
{
    if (tree->rightChild == NULL)
    {
        return tree;
    }
    return findNearestElement(tree->rightChild);
}

void freeTree(Node** node)
{
    if ((*node) == NULL)
    {
        free(*node);
        return;
    }

    freeTree(&(*node)->leftChild);
    freeTree(&(*node)->rightChild);
    free((*node)->value);
}

void inOrderTraversal(const Node* node, int* array, int* index)
{
    if (node == NULL)
    {
        return;
    }

    inOrderTraversal(node->leftChild, array, index);
    array[*index] = node->key;
    ++(*index);
    inOrderTraversal(node->rightChild, array, index);
}

int* toArray(const Node* tree, const size_t size)
{
    int* array = calloc(size, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }

    int index = 0;
    inOrderTraversal(tree, array, &index);

    return array;
}
