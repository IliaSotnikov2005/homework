#pragma once
#include <stdbool.h>

typedef struct Node Node;

// create tree
Node* createTree();

// create element
int createLeaf(int key, char* value, Node** tree);

// get value
char* get(const int key, Node* tree);

// checks that the key exists in the dictionary
bool isContained(const int key, Node* tree);

// delete element
int deleteNode(const int key, Node** tree);

// free tree
void freeTree(Node** node);

// find nearest element in left part of tree
Node* findNearestElement(Node* tree);

// convert tree to array
int* toArray(const Node* tree, const size_t size);

// tree traversal
void inorderTraversal(const Node* node, int* array, int* index);