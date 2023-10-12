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

int addUser(User **userData, User newUser, int *usersCount)
{
    if (*usersCount >= MAX_USERS_COUNT)
    {
        return -1;
    }
    showContacts(*userData, usersCount);
    return 0;
}

int readData(const char* filename)
{

}

void showContacts(const User *userData, const int count)
{
    for (int i = 0; i < count; ++i)
    {
        printf("\n%s - %s", userData[i].name, userData[i].phoneNumber);
    }
    printf("\n\n");
}

int main()
{
    FILE* database = fopen("database.txt", "r+");
    if (database == NULL)
    {
        database = fopen("database.txt", "a+");
        fprintf(database, "%d\n", 0);
    }
    
    int usersCount = 0;
    fscanf_s(database, "%d", &usersCount);

    User *userData = malloc(usersCount * sizeof(User));
    for (int i = 0; i < usersCount * 2; ++i)
    { 
        if (fscanf_s(database, "%s", userData[i].name, 100) == NULL)
        {
            return -1;
        }
        if (fscanf_s(database, "%s", userData[i].phoneNumber, 12) == NULL)
        {
            return -1;
        }
    }

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
            addUser(&userData, newUser, &usersCount);
            break;
        }
        case 2:
        {
            showContacts(userData, usersCount);
            break;
        }
        case 3:
        {
            printf("\nfindNumber\n");
            break;
        }
        case 4:
        {
            printf("\nfindPerson\n");
            break;
        }
        case 5:
        {
            printf("\nsave\n");
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