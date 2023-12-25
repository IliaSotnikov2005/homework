#include "phoneBook.h"
#include "testPhoneBook.h"

#include <stdlib.h>
#include <string.h>

int test(void)
{
    PhoneBook* phoneBook = phoneBookCreate();
    if (phoneBook == NULL)
    {
        return 1;
    }

    char names[5][5] = { "Ivan", "Oleg", "Goga", "Biba", "Boba" };
    char phoneNumbers[5][8] = { "1234567", "5485167", "4993122", "7465888", "7788999" };
    
    for (size_t i = 0; i < 5; ++i)
    {
        phoneBookErrorCode errorCode = phoneBookAdd(names[i], phoneNumbers[i], phoneBook);
        if (errorCode != phoneBookOk)
        {
            phoneBookFree(&phoneBook);
            return i + 2;
        }
    }

    for (size_t i = 0; i < 5; ++i)
    {
        char phone[MAX_PHONE_LENGTH] = { 0 };
        phoneBookErrorCode errorCode = phoneBookPhoneSearch(names[i], phone, phoneBook);
        if (errorCode != phoneBookOk || strcmp(phone, phoneNumbers[i]) != 0)
        {
            phoneBookFree(&phoneBook);
            return i + 7;
        }
    }

    for (size_t i = 0; i < 5; ++i)
    {
        char name[MAX_NAME_LENGTH] = { 0 };
        phoneBookErrorCode errorCode = phoneBookNameSearch(phoneNumbers[i], name, phoneBook);
        if (errorCode != phoneBookOk || strcmp(name, names[i]) != 0)
        {
            phoneBookFree(&phoneBook);
            return i + 12;
        }
    }

    phoneBookSave(phoneBook);

    FILE* database = fopen("database.txt", "r");
    if (database == NULL)
    {
        phoneBookFree(&phoneBook);
        return 17;
    }

    char name[MAX_NAME_LENGTH] = { 0 };
    char phoneNumber[MAX_PHONE_LENGTH] = { 0 };
    for (size_t i = 0; fscanf_s(database, "%s\n%s\n", name, phoneNumber) != EOF; ++i)
    {
        if (strcmp(name, names[i]) != 0 || strcmp(phoneNumber, phoneNumbers[i]) != 0)
        {
            phoneBookFree(&phoneBook);
            fclose(database);
            return i + 18;
        }
    }

    phoneBookFree(&phoneBook);
    fclose(database);

    return 0;
}
