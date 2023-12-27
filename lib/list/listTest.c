#include "listTest.h"
#include "list.h"
#include "errorCodes.h"

#include <stdlib.h>
#include <stdbool.h>

int test()
{
    size_t testsCount = 5;
    bool* testResults = calloc(testsCount, sizeof(bool));
    if (testResults == NULL)
    {
        return -1;
    }

    List* list = listCreate();
    listPush("1", 1, list);
    listPush("2", 2, list);
    listPushBack("3", 3, list);
    int number1 = 0;
    int number2 = 0;
    int number3 = 0;

    listGet(list, 0, "", &number1);
    listGet(list, 1, "", &number2);
    listGet(list, 2, "", &number3);
    testResults[0] = number1 == 2 && number2 == 1 && number3 == 3;

    testResults[1] = listRemove(list, 4) == ListIndexOutOfRange;
    listRemove(list, 1);
    listGet(list, 0, "", &number1);
    listGet(list, 1, "", &number2);
    testResults[2] = number1 == 2 && number2 == 3;

    List* list2 = listCreate();
    listPushBack("1121", 1121, list2);
    listPushBack("444", 444, list2);
    listGet(list2, 0, "", &number1);
    listGet(list2, 1, "", &number2);
    testResults[3] = number1 == 1121 && number2 == 444;

    listExtend(list, list2);
    listGet(list, 3, "", &number1);
    listGet(list, 1, "", &number2);
    testResults[4] = number1 == 444 && number2 == 3;

    for (size_t i = 0; i < testsCount; ++i)
    {
        if (!testResults[i])
        {
            return i + 1;
        }
    }

    return OK;
}