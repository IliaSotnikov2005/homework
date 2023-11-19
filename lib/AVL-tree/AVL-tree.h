#pragma once

#include "errorCodes.h"

typedef struct Node Node;

typedef struct AVLTree AVLTree;

// create tree
AVLTree* createAVLTree();

// free AVL-Tree
void freeAVLTree(AVLTree* tree);

// make leaf
ErrorCode addElement(const char* key, const char* value, AVLTree** tree);
