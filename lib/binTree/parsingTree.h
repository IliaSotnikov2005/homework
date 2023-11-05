#pragma once

typedef struct Node Node;

// build tree from file
Node* buildTreeFromFile(const char const* const filename);

// build tree
Node* buildTree(char expression[100][100], int* pointer);

// print tree
int printTree(Node* root);