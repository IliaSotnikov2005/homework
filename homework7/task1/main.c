#include "../../lib/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_MAX_LENGTH 100

int main()
{
    printf("Enter a filename: ");
    char filename[FILENAME_MAX_LENGTH] = { 0 };
    if (scanf_s("%s", filename, FILENAME_MAX_LENGTH) == NULL)
    {
        return -1;
    }

    printf("Enter:\n1 - for sorting by name\n2 - for sorting by phone number\n->");
    int sortType = 0;
    if (scanf_s("%d", &sortType) == NULL)
    {
        return -1;
    }


    List* list = listFromFile(filename);
    mergeSort(&list, sortType);
    printList(list);
}