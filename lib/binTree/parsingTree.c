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
            return NULL;
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

        return operator;
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

Node* buildTreeFromFile(const char* filename)
{
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0)
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

    fclose(file);
    int pointer = 0;
    Node* root = buildTree(expression, &pointer);
    return root;
}

void printTree(Node* root)
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

int evaluate(Node* node)
{
    if (strstr("+-/*", node->value))
    {
        char operator = node->value[0];
        int operand1 = evaluate(node->leftChild);
        int operand2 = evaluate(node->rightChild);
        switch (operator)
        {
        case '+':
        {
            return operand1 + operand2;
            break;
        }
        case '-':
        {
            return operand1 - operand2;
            break;
        }
        case '*':
        {
            return operand1 * operand2;
            break;
        }
        case '/':
        {
            return operand1 / operand2;
            break;
        }
        default:
            return -1;
            break;
        }
    }
    else
    {
        return atoi(node->value);
    }
}