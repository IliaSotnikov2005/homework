#include "commentLexer.h"
#include "test.h"

#include <stdio.h>

int main()
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    char* comments = commentLexer("text.txt");
    printf("%s", comments);
    free(comments);
}