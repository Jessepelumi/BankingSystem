#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Account
{
    char account_name[30];
    char account_number[15];
    char account_password[25];
    int transaction_pin;
    float account_balance;
    float loan_balance;
};

int main()
{
    struct Account account;
    FILE *file_pointer;
    char filename[15];
    int option;

    char user_account_number[15];
    char user_account_password[25];

    printf("Welcome to Jeolad Banking System\n\n");
    printf("Enter the appropriate option to perform the corresponding operation\n");

    printf("Enter your option here: ");
    scanf("%d", &option);
    printf("%d\n", option);

    if (option == 1)
    {
#ifdef _WIN32
        system("cls"); // Windows
#else
        system("clear"); // Unix-based systems
#endif

        printf("Account name: ");
        scanf("%s", account.account_name);
        printf("Account number: ");
        scanf("%s", account.account_number);
        printf("Account password: ");
        scanf("%s", account.account_password);
        printf("Transaction pin: ");
        scanf("%d", &account.transaction_pin);
        account.account_balance = 0;
        account.loan_balance = 0;

        strcpy(filename, account.account_number);
        strcat(filename, ".dat");

        printf("Filename: %s\n", filename);
        file_pointer = fopen(filename, "wb");
        size_t written = fwrite(&account, sizeof(struct Account), 1, file_pointer);

        if (written == 1)
        {
            printf("Account successfully registered.\n");
        }
        else
        {
            printf("Error in creating account. Try again.\n");
        }

        fclose(file_pointer);
    }
    else if (option == 2)
    {
#ifdef _WIN32
        system("cls"); // Windows
#else
        system("clear"); // Unix-based systems
#endif

        printf("Enter your credentials to login\n");
        printf("Account number: ");
        scanf("%s", user_account_number);
        printf("Password: ");
        scanf("%s", user_account_password);

        strcpy(filename, user_account_number);
        strcat(filename, ".dat");
        file_pointer = fopen(filename, "r");
        if (file_pointer == NULL)
        {
            printf("Account does not exist. Create new account.\n");
        }
        else
        {
            fread(&account, sizeof(struct Account), 1, file_pointer);
            fclose(file_pointer);

            int password_check = strcmp(user_account_password, account.account_password);

            if (password_check == 0)
            {
                printf("Valid password\n");
            }
            else
            {
                printf("Invalid password\n");
            }
        }
    }
    else
    {
        printf("invalid option\n");
    }

    return 0;
}