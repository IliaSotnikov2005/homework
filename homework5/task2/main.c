#include <stdio.h>

int main()
{
    FILE* database = fopen("database.txt", "a+");
    int command = -1;
    while (command != 0)
    {
        printf("Waiting for your command: ");
    }
    printf("\nGood bye!");
}