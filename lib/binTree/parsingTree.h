#pragma once

typedef struct Node Node;

// build tree from file
Node* buildTreeFromFile(const char* filename);

// print tree
void printTree(Node* root);

// evaluate tree
int evaluate(Node* node);