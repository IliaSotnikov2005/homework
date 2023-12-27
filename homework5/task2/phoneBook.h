#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 101
#define MAX_PHONE_LENGTH 12

// Phone book error code
typedef enum PhoneBookErrorCode
{
    phoneBookOk = 0,
    phoneBookDataFileNotFound = -1,
    phoneBookInvalidInput = -2,
    phoneBookNullPointerError = -3,
    phoneBookMemoryAllocationError = -4,
    maximumNumberOfUsersReached = -5,
    noSuchFieldInPhoneBook = -6,
    userIsAlreadyInPhoneBook = -7
} PhoneBookErrorCode;

typedef struct PhoneBook PhoneBook;

// Create phone book
PhoneBook* phoneBookCreate(void);

// Add user to phone book
PhoneBookErrorCode phoneBookAdd(const char* name, const char* phoneNumber, PhoneBook* phoneBook);

// Print contacts
PhoneBookErrorCode phoneBookPrintContacts(PhoneBook* phoneBook);

// Free phone book
PhoneBookErrorCode phoneBookFree(PhoneBook** phoneBook);

// Find phone by name
PhoneBookErrorCode phoneBookPhoneSearch(const char* name, char* phoneNumber, const PhoneBook* phoneBook);

// Find name by phone
PhoneBookErrorCode phoneBookNameSearch(const char* phoneNumber, char* name, const PhoneBook* phoneBook);

// Save phone book
PhoneBookErrorCode phoneBookSave(PhoneBook* phoneBook);