#include <stdio.h>
#include <stdlib.h>

#define DATA_FILE "account.dat"

typedef struct {
    int accountNumber;
    char holderName[60];
    double balance;
} Account;

static int loadAccount(Account *a) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) return 0;
    if (fread(a, sizeof *a, 1, fp) != 1) { fclose(fp); return 0; }
    fclose(fp);
    return 1;
}

static int saveAccount(const Account *a) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) { perror("Unable to save account"); return 0; }
    if (fwrite(a, sizeof *a, 1, fp) != 1) { fclose(fp); return 0; }
    fclose(fp);
    return 1;
}

int main(void) {
    Account account;
    int choice;
    double amount;

    if (!loadAccount(&account)) {
        account.accountNumber = 1001;
        snprintf(account.holderName, sizeof account.holderName, "Demo Customer");
        account.balance = 0.0;
        if (!saveAccount(&account)) return 1;
        printf("Created demo account 1001 (Demo Customer).\n");
    }

    for (;;) {
        printf("\n=== CodeAlpha Banking System ===\n");
        printf("Account: %d | Holder: %s\n", account.accountNumber, account.holderName);
        printf("1. Deposit\n2. Withdraw\n3. Balance Enquiry\n4. Exit\nChoose: ");
        if (scanf("%d", &choice) != 1) {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Please enter a valid menu number.");
            continue;
        }
        switch (choice) {
            case 1:
                printf("Deposit amount: ");
                if (scanf("%lf", &amount) != 1 || amount <= 0) {
                    puts("Enter an amount greater than zero."); break;
                }
                account.balance += amount;
                if (saveAccount(&account)) printf("Deposit successful. Balance: %.2f\n", account.balance);
                break;
            case 2:
                printf("Withdrawal amount: ");
                if (scanf("%lf", &amount) != 1 || amount <= 0) {
                    puts("Enter an amount greater than zero."); break;
                }
                if (amount > account.balance) {
                    puts("Insufficient balance."); break;
                }
                account.balance -= amount;
                if (saveAccount(&account)) printf("Withdrawal successful. Balance: %.2f\n", account.balance);
                break;
            case 3:
                printf("Current balance: %.2f\n", account.balance);
                break;
            case 4:
                puts("Thank you for using the banking system.");
                return 0;
            default:
                puts("Invalid menu option.");
        }
    }
}
