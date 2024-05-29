#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
                bool isPasswordValid = false;
                int password_attempts = 0;

                do
                {
                    int password_check = strcmp(user_account_password, account.account_password);
                    int operation;
                    float amount;

                    if (password_check == 0)
                    {
#ifdef _WIN32
                        system("cls"); // Windows
#else
                        system("clear"); // Unix-based systems
#endif

                        isPasswordValid = true;
                        printf("Login successful!\n");
                        printf("What operation do you want to perform?\n\n");
                        printf("1: Check account balance\n");
                        printf("2: Deposit money\n");
                        printf("3: Withdraw money\n");
                        printf("4: Request loan\n");
                        printf("5: Repay loan\n");
                        printf("6: Change password\n");
                        printf("7: Logout\n");

                        printf("Operation: ");
                        scanf("%d", &operation);

                        int user_transaction_pin;

                        float minimum_loan_amount = 5000.00;
                        float maximum_loan_amount = account.account_balance * 10;
                        float loan_amount;

                        switch (operation)
                        {
                        case 1:
                            printf("Your current balance is ₦%.2f\n\n", account.account_balance);
                            break;
                        case 2:
                            printf("How much do you want to deposit?\n");
                            printf("Amount: ₦");
                            scanf("%f", &amount);

                            account.account_balance += amount;

                            file_pointer = fopen(filename, "wb");
                            size_t written = fwrite(&account, sizeof(struct Account), 1, file_pointer);
                            if (written == 1)
                            {
                                printf("Yaay! Deposit successful.\n");
                                printf("Your new balance is ₦%.2f\n\n", account.account_balance);
                            }
                            else
                            {
                                printf("Error encountered. Deposit unsuccessful.\n\n");
                            }
                            fclose(file_pointer);
                            break;
                        case 3:
                            printf("How much do you want to withdraw?\n");
                            printf("Amount: ₦");
                            scanf("%f", &amount);
                            printf("Transaction pin: ");
                            scanf("%d", &user_transaction_pin);

                            if (user_transaction_pin == account.transaction_pin)
                            {
                                if (amount > account.account_balance)
                                {
                                    printf("Insufficient funds! Withdrawal successful.\n\n");
                                }
                                else
                                {
                                    account.account_balance -= amount;

                                    file_pointer = fopen(filename, "wb");
                                    size_t written = fwrite(&account, sizeof(struct Account), 1, file_pointer);
                                    if (written == 1)
                                    {
                                        printf("Yaay! Withdrawal successful.\n");
                                        printf("Your new balance is ₦%.2f\n\n", account.account_balance);
                                    }
                                    else
                                    {
                                        printf("Error encountered. Withdrawal unsuccessful.\n\n");
                                    }
                                    fclose(file_pointer);
                                }
                            }
                            else
                            {
                                printf("Invalid pin. Cannot complete witdrawal.");
                            }
                            break;
                        case 4:
                            printf("Enter your transaction pin to access loan system\n");
                            printf("Transaction pin: ");
                            scanf("%d", &user_transaction_pin);
                            if (user_transaction_pin == account.transaction_pin)
                            {
                                printf("You now have access to the loan system\n");
                                printf("You are eligible to borrow a minimum of ₦%.2f and a maximum of ₦%.2f\n", minimum_loan_amount, maximum_loan_amount);

                                printf("Enter loan amount: ");
                                scanf("%f", &loan_amount);

                                if (loan_amount < minimum_loan_amount)
                                {
                                    printf("Minimum allowed is ₦%.2f", minimum_loan_amount);
                                }
                                else if (loan_amount > maximum_loan_amount)
                                {
                                    printf("Maximum allowed is ₦%.2f\n\n", maximum_loan_amount);
                                }
                                else
                                {
                                    account.loan_balance += loan_amount + (loan_amount * 0.25);
                                    account.account_balance += loan_amount;

                                    file_pointer = fopen(filename, "wb");
                                    size_t written = fwrite(&account, sizeof(struct Account), 1, file_pointer);
                                    if (written == 1)
                                    {
                                        printf("Loan collected.\n");
                                        printf("Your new account balance is ₦%.2f\n", account.account_balance);
                                        printf("Your loan balance is ₦%.2f\n\n", account.loan_balance);
                                    }
                                    else
                                    {
                                        printf("Error encountered. Loan request unsuccessful.\n\n");
                                    }
                                    fclose(file_pointer);
                                }
                            }
                            else
                            {
                                printf("Access Denied");
                            }
                            break;
                        case 5:
                            printf("You have an outstanding loan of %.2f\n", account.loan_balance);
                            if (account.loan_balance == 0)
                            {
                                printf("No outstanding loan to be paid");
                                break;
                            }
                            else
                            {
                                printf("Enter amount: ");
                                scanf("%f", &amount);
                                if (amount < account.account_balance)
                                {
                                    printf("Insufficient funds. Enter an amount more than ₦%.2f", account.account_balance);
                                }
                                else if (amount > account.loan_balance)
                                {
                                    printf("You have entered excess funds. Enter an amount between ₦%.2f and ₦%.2f", account.account_balance, account.loan_balance);
                                }
                                else
                                {
                                    account.loan_balance -= amount;
                                    account.account_balance -= amount;

                                    file_pointer = fopen(filename, "wb");
                                    size_t written = fwrite(&account, sizeof(struct Account), 1, file_pointer);
                                    if (written == 1)
                                    {
                                        printf("Deposit added.\n");
                                        printf("Your new account balance is ₦%.2f\n", account.account_balance);
                                        printf("Your loan balance is ₦%.2f\n\n", account.loan_balance);
                                    }
                                    else
                                    {
                                        printf("Error encountered. Deposit unsuccessful.\n\n");
                                    }
                                    fclose(file_pointer);
                                }
                            }
                            break;
                            // case 6:
                            //     printf("Change password module\n\n");
                            //     break;
                            // case 7:
                            //     printf("Exit\n\n");
                            //     break;

                            // default:
                            //     printf("Invalid option. Try again!\n\n");
                            //     break;
                        }
                    }
                    else
                    {
                        password_attempts++;
                        if (password_attempts <= 5)
                        {
                            printf("You entered an incorrect password. Try again!\n");
                            printf("Password: ");
                            scanf("%s", user_account_password);
                        }
                        else
                        {
                            printf("You have reached a maximum of 5 attempts. No more attempts allowed!\n\n");
                            break;
                        }
                    }
                } while (!isPasswordValid);
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