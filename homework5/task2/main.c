#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_USERS_COUNT 100
#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 12

typedef struct User
{
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];
} User;

int addUser(User* userData, User newUser, int* usersCount)
{
    if (*usersCount >= MAX_USERS_COUNT)
    {
        return -1;
    }
    userData[*usersCount] = newUser;
    (*usersCount)++;
    return 0;
}

int findPhoneByName(User* userData, char* name, const int usersCount, char* phoneNumber)
{
    for (int i = 0; i < usersCount; ++i)
    {
        if (strcmp(userData[i].name, name) == 0)
        {
            memcpy(phoneNumber, userData[i].phoneNumber, MAX_PHONE_LENGTH);
            return 0;
        }
    }
    return -1;
}

int findNameByPhone(User* userData, char* phoneNumber, const int usersCount, char* name)
{
    for (int i = 0; i < usersCount; ++i)
    {
        if (strcmp(userData[i].phoneNumber, phoneNumber) == 0)
        {
            memcpy(name, userData[i].name, MAX_NAME_LENGTH);
            return 0;
        }
    }
    return -1;
}

void showContacts(const User* userData, const int usersCount)
{
    for (int i = 0; i < usersCount; ++i)
    {
        printf("\n%s - %s", userData[i].name, userData[i].phoneNumber);
    }
    printf("\n\n");
}

int save(FILE* database, User* userData, const int usersCount, const int newUsers)
{
    if (!newUsers)
    {
        return 0;
    }
    fseek(database, 0, SEEK_END);
    for (int i = 0; i < newUsers; ++i)
    {
        fprintf(database, "%s\n%s\n", userData[usersCount - newUsers + i].name, userData[usersCount - newUsers + i].phoneNumber);
    }
    return 0;
}

int testSave() {
    FILE* database = fopen("testSave.txt", "w");
    if (database == NULL)
    {
        return -1;
    }
    User userData[MAX_USERS_COUNT];
    int usersCount = 3;
    int newUsers = 3;

    strcpy(userData[0].name, "ivan");
    strcpy(userData[0].phoneNumber, "1234567890");
    strcpy(userData[1].name, "petr");
    strcpy(userData[1].phoneNumber, "2345678901");
    strcpy(userData[2].name, "sidr");
    strcpy(userData[2].phoneNumber, "3456789012");

    save(database, userData, usersCount, newUsers);

    fclose(database);

    database = fopen("testSave.txt", "r");
    if (database == NULL) {
        return -1;
    }

    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];
    int i = 0;
    while (fscanf(database, "%s\n%s\n", name, phoneNumber) != EOF) {
        assert(strcmp(name, userData[i].name) == 0);
        assert(strcmp(phoneNumber, userData[i].phoneNumber) == 0);
        i++;
    }

    fclose(database);

    return 0;
}

int read(FILE* database, User *userData, int* usersCount) {
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];

    while (fgets(name, MAX_NAME_LENGTH, database) != NULL) {
        if (fgets(phoneNumber, MAX_PHONE_LENGTH, database) == NULL) {
            break;
        }

        name[strcspn(name, "\n")] = '\0';
        phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

        strcpy(userData[(*usersCount)].name, name);
        strcpy(userData[(*usersCount)].phoneNumber, phoneNumber);

        (*usersCount)++;
    }

}

bool compare(User* user1, User* user2)
{
    return ((strcmp(user1->name, user2->name) == 0) && (strcmp(user1->phoneNumber, user2->phoneNumber) == 0));
}

int testAddUser(void)
{
    User userData[2] = { 0 };
    int usersCount = 0;
    User newUser1 = { .name = "ivan", .phoneNumber = "3377312" };
    User newUser2 = { .name = "oleg", .phoneNumber = "141413" };

    User correct[] = { newUser1, newUser2 };

    addUser(userData, newUser1, &usersCount);
    addUser(userData, newUser2, &usersCount);

    for (int i = 0; i < usersCount; ++i)
    {
        if (!compare(&userData[i], &correct[i]))
        {
            return -1;
        }
    }
    return 0;
}

int testFindPhone(void)
{
    User userData[2] = { 0 };
    int usersCount = 0;
    User newUser1 = { .name = "ivan", .phoneNumber = "33" };
    User newUser2 = { .name = "oleg", .phoneNumber = "141413" };
    addUser(userData, newUser1, &usersCount);
    addUser(userData, newUser2, &usersCount);
    char phone[MAX_PHONE_LENGTH] = { 0 };
    char name[] = "ivan";
    char correct[] = "33";
    findPhoneByName(userData, name, usersCount, phone);
    if (strcmp(phone, correct) == 0)
    {
        return 0;
    }
    return -1;
}

int testFindName(void)
{
    User userData[2] = { 0 };
    int usersCount = 0;
    User newUser1 = { .name = "ivan", .phoneNumber = "33" };
    User newUser2 = { .name = "oleg", .phoneNumber = "141413" };
    addUser(userData, newUser1, &usersCount);
    addUser(userData, newUser2, &usersCount);
    char name[MAX_NAME_LENGTH] = { 0 };
    char phone[] = "33";
    char correct[] = "ivan";
    findNameByPhone(userData, phone, usersCount, name);
    if (strcmp(name, correct) == 0)
    {
        return 0;
    }
    return -1;
}

int testRead(void)
{
    FILE* database = fopen("testRead.txt", "r");
    User userData[MAX_USERS_COUNT] = { 0 };
    int usersCount = 0;

    if (database == NULL) {
        return -1;
    }

    read(database, userData, &usersCount);

    fclose(database);

    assert(usersCount == 3);
    assert(strcmp(userData[0].name, "ivan") == 0);
    assert(strcmp(userData[0].phoneNumber, "1234567890") == 0);
    assert(strcmp(userData[1].name, "petr") == 0);
    assert(strcmp(userData[1].phoneNumber, "2345678901") == 0);
    assert(strcmp(userData[2].name, "sidr") == 0);
    assert(strcmp(userData[2].phoneNumber, "3456789012") == 0);

    return 0;
}

int main()
{
    if (testAddUser() != 0)
    {
        return -1;
    }
    if (testFindPhone() != 0)
    {
        return -2;
    }
    if (testFindName() != 0)
    {
        return -3;
    }
    if (testRead() != 0)
    {
        return -4;
    }
    if (testSave() != 0)
    {
        return -5;
    }

    FILE* database = fopen("database.txt", "r+");
    if (database == NULL)
    {
        database = fopen("database.txt", "a+");
    }

    int usersCount = 0;
    User userData[MAX_USERS_COUNT] = {0};

    read(database, userData, &usersCount);

    int newUsers = 0;

    int command = -1;
    while (command != 0)
    {
        printf("Waiting for your command: ");
        command = getNum();
        switch (command)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            printf("\nAdding a new user\nEnter the name of new user: ");
            User newUser;
            char name[MAX_NAME_LENGTH] = { 0 };
            if (fgets(name, MAX_NAME_LENGTH, stdin) == NULL)
            {
                return -1;
            }
            name[strcspn(name, "\n")] = '\0';
            strcpy(newUser.name, name);
            printf("Enter the phone of new user: ");
            if (scanf_s("%s", newUser.phoneNumber, 12) == NULL)
            {
                return -1;
            }
            if (addUser(userData, newUser, &usersCount) == -1)
            {
                printf("\nThere is already a maximum number of people in your phone book\n");
                break;
            }
            ++newUsers;
            printf("\nSuccessful!\n\n");
            break;
        }
        case 2:
        {
            showContacts(userData, usersCount);
            break;
        }
        case 3:
        {
            printf("\nSearch for a phone by name\n\nEnter a name: ");
            char name[MAX_NAME_LENGTH] = { 0 };
            if (scanf_s("%s", name, MAX_NAME_LENGTH) == NULL)
            {
                return -1;
            }
            char phone[MAX_PHONE_LENGTH] = { 0 };
            findPhoneByName(userData, name, usersCount, phone);
            printf("The result: %s\n\n", phone == NULL ? "empty" : phone);
            break;
        }
        case 4:
        {
            printf("\nSearch for a name by phone\n\nEnter a phone: ");
            char phoneNumber[MAX_PHONE_LENGTH] = { 0 };
            if (scanf_s("%s", phoneNumber, MAX_PHONE_LENGTH) == NULL)
            {
                return -1;
            }
            char name[MAX_NAME_LENGTH] = { 0 };
            findNameByPhone(userData, phoneNumber, usersCount, name);
            printf("The result: %s\n\n", name == NULL ? "empty" : name);
            break;
        }
        case 5:
        {
            save(database, userData, usersCount, newUsers);
            break;
        }
        default:
        {
            printf("\nUnknown command\n");
            break;
        }
        }
    }
    fclose(database);
    printf("\nGood bye!");
}