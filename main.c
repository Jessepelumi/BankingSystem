#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ACCOUNTS 500

struct Account
{
    char account_name[30];
    char account_number[15];
    char account_password[25];
    int transaction_pin;
    float account_balance;
    float loan_balance;
};

char account_numbers[MAX_ACCOUNTS][15];
int num_acounts = 0;

void generate_account_number(char *account_number)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < 10; i++)
    {
        account_number[i] = '0' + rand() % 10;
    }
    account_number[i] = '\0';
}

int account_number_exists(char *account_number)
{
    for (int i = 0; i < num_acounts; i++)
    {
        if (strcmp(account_numbers[i], account_number) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    struct Account account;
    FILE *file_pointer;
    char filename[15];
    int option;

    char user_account_number[15];
    char user_account_password[25];

    printf("\nWelcome to Jeolad Banking System\n\n");

    do
    {
        printf("Enter the appropriate option to perform the corresponding operation\n");
        printf("1: Open a new account\n");
        printf("2: Login to your account\n");
        printf("3: Exit\n");
        printf("Enter your option here: ");
        scanf("%d", &option);

        if (option == 1)
        {
#ifdef _WIN32
            system("cls"); // Windows
#else
            system("clear"); // Unix-based systems
#endif

            printf("Account name: ");
            scanf("%s", account.account_name);

            do
            {
                generate_account_number(account.account_number);
            } while (account_number_exists(account.account_number));

            printf("Account password: ");
            scanf("%s", account.account_password);

            printf("Transaction pin: ");
            scanf("%d", &account.transaction_pin);

            account.account_balance = 0;
            account.loan_balance = 0;

            strcpy(filename, account.account_number);
            strcat(filename, ".dat");

            file_pointer = fopen(filename, "wb");
            size_t written = fwrite(&account, sizeof(struct Account), 1, file_pointer);

            if (written == 1)
            {
                printf("Account successfully registered. Login to continue.\n");
                printf("Your account number is %s\n\n", account.account_number);
            }
            else
            {
                printf("Error in creating account. Try again.\n\n");
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

            printf("Enter your login details.\n");

            printf("Account number: ");
            scanf("%s", user_account_number);

            printf("Password: ");
            scanf("%s", user_account_password);

            strcpy(filename, user_account_number);
            strcat(filename, ".dat");
            file_pointer = fopen(filename, "r");

            if (file_pointer == NULL)
            {
                printf("Error encountered: Account does not exist!\n\n");
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
        else if (option == 3)
        {
            break;
        }
        else
        {
#ifdef _WIN32
            system("cls"); // Windows
#else
            system("clear"); // Unix-based systems
#endif
            printf("invalid option\n");
        }
    } while (option != 3);

    return 0;
}