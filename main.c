#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Account
{
    char account_name[30];
    char account_number[10];
    char account_password[24];
    int transaction_pin;
    float account_balance;
    float loan_balance;
};

int main()
{
    struct Account account;
    int option;

    printf("Welcome to Jeolad Banking System\n\n");
    printf("Enter the appropriate option to perform the corresponding operation\n");

    printf("Enter your option here: ");
    scanf("%d", &option);
    printf("%d\n", option);

    if (option == 1)
    {
        system("clear");
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
    } else if (option == 2)
    {
        printf("Login module\n");
    } else {
        printf("invalid option\n");
    }

    return 0;
}