#include "../../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS_COUNT 100
#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGHT 12

typedef struct User
{
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGHT];
} User;

int addUser(User *userData, User newUser, int *usersCount)
{
    if (*usersCount >= MAX_USERS_COUNT)
    {
        return -1;
    }
    userData[*usersCount] = newUser;
    (*usersCount)++;
    return 0;
}

int findPhoneByName(User* userData, char *name, const int usersCount, char *phoneNumber)
{
    for (int i = 0; i < usersCount; ++i)
    {
        if (strcmp(userData[i].name, name) == 0)
        {
            memcpy(phoneNumber, userData[i].phoneNumber, MAX_PHONE_LENGHT);
            return 0;
        }
    }
    memcpy(phoneNumber, "empty", MAX_PHONE_LENGHT);
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
    memcpy(name, "empty", MAX_NAME_LENGTH);
    return -1;
}

void showContacts(const User *userData, const int usersCount)
{
    for (int i = 0; i < usersCount; ++i)
    {
        printf("\n%s - %s", userData[i].name, userData[i].phoneNumber);
    }
    printf("\n\n");
}

int save(FILE *database, User *userData, const int usersCount, const int newUsers)
{
    if (!newUsers)
    {
        return 0;
    }
    fseek(database, 0, SEEK_END);
    for (int i = 0; i < newUsers; ++i)
    {
        fprintf(database, "\n%s\n%s", userData[usersCount - newUsers + i].name, userData[usersCount - newUsers + i].phoneNumber);
    }
}

int read(FILE* database, User* userData, int *usersCount)
{
    int i = 0;
    while (!feof(database))
    {
        if (fscanf_s(database, "%s", userData[i].name, 100) == NULL)
        {
            return -1;
        }
        if (fscanf_s(database, "%s", userData[i].phoneNumber, 12) == NULL)
        {
            return -1;
        }
        ++i;
        ++(*usersCount);
    }
}

int main()
{
    FILE* database = fopen("database.txt", "r+");
    if (database == NULL)
    {
        database = fopen("database.txt", "a+");
    }
    
    int usersCount = 0;
    User* userData[MAX_USERS_COUNT] = { 0 };

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
            if (scanf_s("%s", newUser.name, 100) == NULL)
            {
                return -1;
            }
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
            char phone[MAX_PHONE_LENGHT] = { 0 };
            findPhoneByName(userData, name, usersCount, phone);
            printf("The result: %s\n\n", phone);
            break;
        }
        case 4:
        {
            printf("\nSearch for a name by phone\n\nEnter a phone: ");
            char phoneNumber[MAX_PHONE_LENGHT] = { 0 };
            if (scanf_s("%s", phoneNumber, MAX_PHONE_LENGHT) == NULL)
            {
                return -1;
            }
            char name[MAX_NAME_LENGTH] = { 0 };
            findNameByPhone(userData, phoneNumber, usersCount, name);
            printf("The result: %s\n\n", name);
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