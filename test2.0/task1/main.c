#include "list.h"
#include "errorCodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

ErrorCode deleteElementsInOddPlaces(List* list)
{
    if (list == NULL)
    {
        return NULLPointer;
    }
    for (size_t i = 1; i < listSize(list); ++i)
    {
        List** element = listFind(&list, i);
        listPop(element);
    }

    return OK;
}

bool test()
{
    List* list = listCreate();
    listPush(&list, 3);
    listPush(&list, 4);
    listPush(&list, 5);
    listPush(&list, 6);
    listPush(&list, 7);
    listPush(&list, 8);
    listPush(&list, 9);
    listPush(&list, 10);
    deleteElementsInOddPlaces(list);

    int* array = listToArray(list);
    int expected[] = { 10, 8, 6, 4 };

    bool result = memcmp(array, expected, sizeof(expected)) == 0;
    listFree(&list);
    free(array);
    return result;
}

int main()
{
    if (!test())
    {
        printf("TEST DID NOT PASSED\n");
    }
    List* list = listCreate();

    listPush(&list, 1);
    listPush(&list, 2);
    listPush(&list, 3);
    listPush(&list, 4);
    listPush(&list, 5);
    deleteElementsInOddPlaces(list);
    listPrint(list);

    listFree(&list);
}