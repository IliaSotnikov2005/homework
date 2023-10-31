#include "../../lib/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_MAX_LENGTH 100

void freeArray(char** array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        free(array[i]);
    }
    free(array);
}

int test()
{
    List* list = listFromFile("test.txt");
    char arrNames[5][7] = { "aaaaaa", "aaaaab", "nejrea", "kkrieo", "iirpoe" };
    char arrNumbers[5][7] = { "111112", "111112", "121112", "400122", "930112" };
    mergeSort(&list, 2);
    char** listArray = toArray(list);
    for (int i = 0; i < 5; ++i)
    {
        if ((strcmp(listArray[2 * i], arrNames[i]) != 0) || (strcmp(listArray[2 * i + 1], arrNumbers[i]) != 0))
        {
            freeArray(listArray, length(list) * 2);
            return -1;
        }
    }
    freeArray(listArray, length(list) * 2);
    return 0;
}

int main()
{
    if (test() == -1)
    {
        printf("TEST FAILED");
        return -1;
    }

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
    if (mergeSort(&list, sortType) == -1)
    {
        return -1;
    }
    printList(list);
}