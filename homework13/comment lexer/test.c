#include "test.h"
#include "commentLexer.h"

#include <string.h>

int test(void)
{
    char* comments = commentLexer("test1.txt");
    char expected[] = "";
    if (strcmp(comments, expected) != 0)
    {
        return 1;
    }
    free(comments);

    comments = commentLexer("test2.txt");
    char expected2[] = "/*aboba*/";
    if (strcmp(comments, expected2) != 0)
    {
        return 2;
    }

    free(comments);

    return 0;
}