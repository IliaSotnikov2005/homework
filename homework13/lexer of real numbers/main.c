#include "test.h"
#include "lexerOfRealNumber.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int errorCode = test();
    if (errorCode != 0)
    {
        printf("Test %d failed", errorCode);
        return -1;
    }

    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        return 0;
    }

    printf("Enter a string: ");
    char string[101] = { 0 };
    if (fgets(string, 101, stdin) == NULL)
    {
        printf("Invalid input");
        return -1;
    }
    string[strcspn(string, "\n")] = '\0';

    printf(isRealNumber(string) ? "\nThis is real number\n" : "\nThis is not real number\n");
}