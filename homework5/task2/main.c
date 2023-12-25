#include "phoneBook.h"
#include "testPhoneBook.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum ErrorCode
{
    ok = 0,
    memoryAllocationError = -1,
    invalidInput = -2
};

int main()
{
    phoneBookErrorCode errorCode = test();
    if (errorCode != phoneBookOk)
    {
        printf("Test %d failed", errorCode);
        return errorCode;
    }

    PhoneBook* phoneBook = phoneBookCreate();
    if (phoneBook == NULL)
    {
        return memoryAllocationError;
    }

    int command = -1;

    while (command != 0)
    {
        printf("Waiting for your command: ");
        if (scanf_s("%d", &command) == 0)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        switch (command)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            printf("\nAdding a new user\nEnter the name of new user: ");
            char name[MAX_NAME_LENGTH] = { 0 };
            if (scanf_s("%s", name, MAX_NAME_LENGTH) == 0)
            {
                printf("Invalid input");
                break;
            }

            printf("Enter the phoneNumber of new user: ");
            char phoneNumber[MAX_PHONE_LENGTH] = { 0 };
            if (scanf_s("%s", phoneNumber, MAX_PHONE_LENGTH) == 0)
            {
                printf("Invalid input");
                break;
            }

            printf(phoneBookAdd(name, phoneNumber, phoneBook) == userIsAlreadyInPhoneBook ? "User is already in phone book\n\n" : "\nSuccess!\n\n");

            break;
        }
        case 2:
        {
            printf("\nThe list of all contacts:\n");
            phoneBookPrintContacts(phoneBook);
            printf("\n");

            break;
        }
        case 3:
        {
            printf("\nSearch for a phone by name\n\nEnter a name: ");
            
            char name[MAX_NAME_LENGTH] = { 0 };
            if (scanf_s("%s", name, MAX_NAME_LENGTH) == 0)
            {
                printf("Invalid input");
                break;
            }

            char phoneNumber[MAX_PHONE_LENGTH] = { 0 };
            phoneBookPhoneSearch(name, phoneNumber, phoneBook);
            if (phoneNumber[0] == '\0')
            {
                printf("No such user has been found\n\n");
            }
            else
            {
                printf("Phone number - %s\n\n", phoneNumber);
            }

            break;
        }
        case 4:
        {
            printf("\nSearch for a name by phone number\n\nEnter a phone number: ");

            char phoneNumber[MAX_PHONE_LENGTH] = { 0 };
            if (scanf_s("%s", phoneNumber, MAX_PHONE_LENGTH) == 0)
            {
                printf("Invalid input");
                break;
            }

            char name[MAX_NAME_LENGTH] = { 0 };
            phoneBookNameSearch(phoneNumber, name, phoneBook);
            if (name[0] == '\0')
            {
                printf("No such phone number has been found\n\n");
            }
            else
            {
                printf("Name - %s\n\n", name);
            }

            break;
        }
        case 5:
        {
            printf("Saving phone book...\n");
            printf(phoneBookSave(phoneBook) != phoneBookOk ? "An error occured\n" : "Success!\n\n");

            break;
        }
        default:
        {
            printf("\nUnknown command\n");
            break;
        }
        }
    }

    phoneBookFree(&phoneBook);
    printf("\nGood bye!");
}