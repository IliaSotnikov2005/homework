#include <stdio.h>
#include <string.h>

int main()
{
    char originalString[80] = { 0 };
    printf("Enter an original string: ");
    scanf_s("%s", originalString, 80);

    char substring[80] = { 0 };
    printf("\nEnter an substring: ");
    scanf_s("%s", substring, 80);
    const int substringSize = strlen(substring);

    int count = 0;
    char* startOfTheSearch = originalString;
    while ((startOfTheSearch = strstr(startOfTheSearch, substring)) != NULL)
    {
        ++count;
        startOfTheSearch += substringSize;
    }

    printf("\nThe string %s enters the original string %d times\n", substring, count);
}