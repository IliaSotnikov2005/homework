#include "../../lib/stack.h"
#include <stdio.h>
#include <stdbool.h>

int op_preced(const char c)
{
    switch (c)
    {
    case '!':
        return 4;

    case '*':
    case '/':
    case '%':
        return 3;

    case '+':
    case '-':
        return 2;

    case '=':
        return 1;
    }
    return 0;
}

bool op_left_assoc(const char c)
{
    switch (c)
    {
        // ����-������������� ���������
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
    case '=':
        return true;
        // �����-������������� ���������
    case '!':
        return false;
    }
    return false;
}

char* fromInfixToPostfix(char *expression)
{

}

int main()
{
    
}