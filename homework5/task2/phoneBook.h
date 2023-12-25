#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 101
#define MAX_PHONE_LENGTH 12

// Phone book error code
typedef enum phoneBookErrorCode
{
    phoneBookOk = 0,
    phoneBookDataFileNotFound = -1,
    phoneBookInvalidInput = -2,
    phoneBookNullPointerError = -3,
    phoneBookMemoryAllocationError = -4,
    maximumNumberOfUsersReached = -5,
    noSuchFieldInPhoneBook = -6,
    userIsAlreadyInPhoneBook = -7
} phoneBookErrorCode;

typedef struct PhoneBook PhoneBook;

// Create phone book
PhoneBook* phoneBookCreate(void);

// Add user to phone book
phoneBookErrorCode phoneBookAdd(const char* name, const char* phoneNumber, PhoneBook* phoneBook);

// Print contacts
phoneBookErrorCode phoneBookPrintContacts(PhoneBook* phoneBook);

// Free phone book
phoneBookErrorCode phoneBookFree(PhoneBook** phoneBook);

// Find phone by name
phoneBookErrorCode phoneBookPhoneSearch(const char* name, char* phoneNumber, const PhoneBook* phoneBook);

// Find name by phone
phoneBookErrorCode phoneBookNameSearch(const char* phoneNumber, char* name, const PhoneBook* phoneBook);

// Save phone book
phoneBookErrorCode phoneBookSave(PhoneBook* phoneBook);