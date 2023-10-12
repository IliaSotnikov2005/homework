#include <stdio.h>

typedef struct User
{
    char* name[100];
    char* phoneNumber[12];
} User;

int add(const char *name, const char *phoneNumber)
{

}

int main()
{
    FILE* database = fopen("database.txt", "r+");
    if (database == NULL)
    {
        database = fopen("database.txt", "a+");
        fprintf(database, "%d\n", 0);
    }
    

    int command = -1;
    while (command != 0)
    {
        printf("Waiting for your command: ");
        if (scanf_s("%d", &command) == NULL)
        {
            printf("\nError");
            return -1;
        }
        switch (command)
        {
        case 1:
            add;
            break;
        case 2:
            printf("\nprintDatabase\n");
            break;
        case 3:
            printf("\nfindNumber\n");
            break;
        case 4:
            printf("\nfindPerson\n");
            break;
        case 5:
            printf("\nsave\n");

        default:
            break;
        }
    }
    fclose(database);
    printf("\nGood bye!");
}