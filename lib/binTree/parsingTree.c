#include "parsingTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node
{
    char* value;
    Node* leftChild;
    Node* rightChild;
};

Node* buildTreeFromFile(const char const* const filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    char expression[100][100] = { 0 };
    char input[100];
    fgets(input, sizeof(input), file);
    char* substring = strtok(input, " ");
    for (int i = 0; substring != NULL; ++i)
    {
        if (substring[0] == '(')
        {
            ++substring;
        }
        char *pointer = strchr(substring, ')');
        if (pointer)
        {
            *pointer = '\0';
        }
        strcpy(expression[i], substring);
        substring = strtok(NULL, " ");
    }
    int pointer = 0;
    Node* root = buildTree(expression, &pointer);
    return root;
}

Node* buildTree(char expression[100][100], int* pointer)
{
    char* item = expression[*pointer];
    ++(*pointer);
    if (!item[0])
    {
        return NULL;
    }
    if (strstr("+-/*", item))
    {
        Node* operator = calloc(1, sizeof(Node));
        if (operator == NULL)
        {
            return -1;
        }
        operator->value = calloc(2, sizeof(char));
        if (operator->value == NULL)
        {
            return NULL;
        }
        strcpy(operator->value, item);
        
        Node* operand1 = calloc(1, sizeof(Node*));
        if (operand1 == NULL)
        {
            return NULL;
        }
        operand1 = buildTree(expression, pointer);
        operator->leftChild = operand1;

        Node* operand2 = calloc(1, sizeof(Node*));
        if (operand2 == NULL)
        {
            return NULL;
        }
        operand2 = buildTree(expression, pointer);
        operator->rightChild = operand2;

    }
    else
    {
        Node* operand = calloc(1, sizeof(Node));
        if (operand == NULL)
        {
            return NULL;
        }
        operand->value = calloc(strlen(item), sizeof(char));
        strcpy(operand->value, item);
        return operand;
    }
}

int printTree(Node* root)
{
    if (root->leftChild == NULL)
    {
        printf(" %s ", root->value);
    }
    else
    {
        Node *operator = root;
        printf("( %s ", operator->value);
        printTree(operator->leftChild);
        printTree(operator->rightChild);
        printf(")");
    }
}