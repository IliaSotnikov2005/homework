#include "phoneBook.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS_COUNT 100

typedef struct User
{
    char* name;
    char* phoneNumber;
} User;

struct PhoneBook
{
    User** database;
    size_t usersCount;
    size_t newUsers;
};

phoneBookErrorCode phoneBookFree(PhoneBook** phoneBook)
{
    if (phoneBook == NULL)
    {
        return phoneBookNullPointerError;
    }
    if (*phoneBook == NULL)
    {
        return phoneBookNullPointerError;
    }
    if ((*phoneBook)->database == NULL)
    {
        free(*phoneBook);
        return phoneBookOk;
    }

    for (size_t i = 0; i < MAX_USERS_COUNT && (*phoneBook)->database[i] != NULL; ++i)
    {
        free((*phoneBook)->database[i]->name);
        free((*phoneBook)->database[i]->phoneNumber);
        free((*phoneBook)->database[i]);
    }
    free((*phoneBook)->database);
    free(*phoneBook);

    return phoneBookOk;
}

static phoneBookErrorCode read(PhoneBook* phoneBook)
{
    FILE* database = fopen("database.txt", "r");
    if (database == NULL)
    {
        return phoneBookDataFileNotFound;
    }

    char name[MAX_NAME_LENGTH] = { 0 };
    char phoneNumber[MAX_PHONE_LENGTH] = { 0 };

    while (fgets(name, MAX_NAME_LENGTH, database) != NULL)
    {
        if (fgets(phoneNumber, MAX_PHONE_LENGTH, database) == NULL)
        {
            fclose(database);
            return phoneBookInvalidInput;
        }

        name[strcspn(name, "\n")] = '\0';
        phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

        phoneBook->database[phoneBook->usersCount] = calloc(1, sizeof(User));
        if (phoneBook->database[phoneBook->usersCount] == NULL)
        {
            fclose(database);
            return phoneBookMemoryAllocationError;
        }
        phoneBook->database[phoneBook->usersCount]->name = strdup(name);
        phoneBook->database[phoneBook->usersCount]->phoneNumber = strdup(phoneNumber);

        ++phoneBook->usersCount;
    }
    --phoneBook->usersCount;

    fclose(database);

    return phoneBookOk;
}

PhoneBook* phoneBookCreate(void)
{
    PhoneBook* phoneBook = calloc(1, sizeof(PhoneBook));
    if (phoneBook == NULL)
    {
        return NULL;
    }

    phoneBook->database = calloc(MAX_USERS_COUNT, sizeof(User*));
    if (phoneBook->database == NULL)
    {
        phoneBookFree(&phoneBook);
        return NULL;
    }

    if (read(phoneBook) != phoneBookOk)
    {
        phoneBookFree(&phoneBook);
        return NULL;
    }

    return phoneBook;
}

static bool inPhoneBook(const char* name, const char* phoneeNumber, const PhoneBook* phoneBook)
{
    for (size_t i = 0; i < MAX_USERS_COUNT && phoneBook->database[i] != NULL; ++i)
    {
        if (strcmp(name, phoneBook->database[i]->name) == 0 || strcmp(phoneeNumber, phoneBook->database[i]->phoneNumber) == 0)
        {
            return true;
        }
    }

    return false;
}

phoneBookErrorCode phoneBookAdd(const char* name, const char* phoneNumber, PhoneBook* phoneBook)
{
    if (phoneBook == NULL)
    {
        return phoneBookNullPointerError;
    }
    if (phoneBook->usersCount == MAX_USERS_COUNT)
    {
        return maximumNumberOfUsersReached;
    }

    if (inPhoneBook(name, phoneNumber, phoneBook))
    {
        return userIsAlreadyInPhoneBook;
    }

    User* newUser = calloc(1, sizeof(User));
    if (newUser == NULL)
    {
        return phoneBookMemoryAllocationError;
    }

    newUser->name = strdup(name);
    newUser->phoneNumber = strdup(phoneNumber);

    phoneBook->database[phoneBook->usersCount] = newUser;
    ++phoneBook->usersCount;
    ++phoneBook->newUsers;

    return phoneBookOk;
}

phoneBookErrorCode phoneBookPrintContacts(PhoneBook* phoneBook)
{
    if (phoneBook == NULL)
    {
        return phoneBookNullPointerError;
    }

    for (size_t i = 0; i < MAX_USERS_COUNT && phoneBook->database[i] != NULL; ++i)
    {
        printf("%s - %s\n", phoneBook->database[i]->name, phoneBook->database[i]->phoneNumber);
    }

    return phoneBookOk;
}

phoneBookErrorCode phoneBookPhoneSearch(const char* name, char* phoneNumber, const PhoneBook* phoneBook)
{
    if (phoneBook == NULL)
    {
        return phoneBookNullPointerError;
    }

    for (size_t i = 0; i < MAX_USERS_COUNT && phoneBook->database[i] != NULL; ++i)
    {
        if (strcmp(phoneBook->database[i]->name, name) == 0)
        {
            strcat(phoneNumber, phoneBook->database[i]->phoneNumber);
        }
    }

    return noSuchFieldInPhoneBook;
}

phoneBookErrorCode phoneBookNameSearch(const char* phoneNumber, char* name, const PhoneBook* phoneBook)
{
    if (phoneBook == NULL)
    {
        return phoneBookNullPointerError;
    }

    for (size_t i = 0; i < MAX_USERS_COUNT && phoneBook->database[i] != NULL; ++i)
    {
        if (strcmp(phoneBook->database[i]->phoneNumber, phoneNumber) == 0)
        {
            strcat(name, phoneBook->database[i]->name);
        }
    }

    return noSuchFieldInPhoneBook;
}

phoneBookErrorCode phoneBookSave(PhoneBook* phoneBook)
{
    if (phoneBook->newUsers == 0)
    {
        return phoneBookOk;
    }

    FILE* database = fopen("database.txt", "a+");
    if (database == NULL)
    {
        return phoneBookMemoryAllocationError;
    }

    fseek(database, 0, SEEK_END);
    for (size_t i = 0; i < phoneBook->newUsers; ++i)
    {
        fprintf(database, "%s\n%s\n", phoneBook->database[phoneBook->usersCount - phoneBook->newUsers + i]->name, phoneBook->database[phoneBook->usersCount - phoneBook->newUsers + i]->phoneNumber);
    }

    fclose(database);

    return phoneBookOk;
}