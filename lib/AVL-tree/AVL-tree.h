#pragma once

#include "errorCodes.h"

typedef struct Node Node;

typedef struct AVLTree AVLTree;

// create tree
AVLTree* createAVLTree();

// free AVL-Tree
void freeAVLTree(AVLTree* tree);

// add element
ErrorCode addElement(const char* key, const char* value, AVLTree* tree);

// get value by key
char* get(char* key, AVLTree* tree);

// delete element
ErrorCode deleteElement(const char* key, AVLTree* tree);