#include "basics.h"
#include "classes.h"
#include "functions.h"



void mainMenu (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected, bool &running);
void Client1 (BankAccount &account, map<int, BankAccount> *accounts);
void Client2 (BankAccount &account, map<int, BankAccount> *accounts);
void Client3 (BankAccount &account, map<int, BankAccount> *accounts);
void AccountSelection (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected);
int randomBalance();

int randomBalance () {
    srand(time(NULL));
    int random = rand() % 1000 + 45;
    return random;
}

void Client1 (BankAccount &account, map<int, BankAccount> *accounts, mutex &mtx) {
    lock_guard<mutex> lock(mtx);
    cout << "Client 1 is running" << endl;
    //cin.get();
    cout << "Client 1 is depositing 500 from account " << account.getAccountNum() << endl << endl;
    account.deposit(500);
    Sleep(500);
}

void Client2 (BankAccount &account, map<int, BankAccount> *accounts, mutex &mtx) {
    lock_guard<mutex> lock(mtx);
    cout << "Client 2 is running" << endl;
    //cin.get();
    cout << "Client 2 is withdrawing 200 from account " << account.getAccountNum() << endl << endl;
    account.withdraw(200);
    Sleep(500);

}

void Client3 (BankAccount &account, map<int, BankAccount> *accounts, mutex &mtx) {
    lock_guard<mutex> lock(mtx);
    cout << "Client 3 is running" << endl;
    //cin.get();
    cout << "Client 3 is checking it's balance for account" << account.getAccountNum() << ": " << account.getBalance() << endl << endl;
    Sleep(500);

}

void AccountSelection (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected) {
    system("cls");
    cout << "Enter a bank account number to enter the banking system: " << endl;
    for (auto &acc : *accounts) {
        cout << "Account Number: " << acc.second.getAccountNum() << endl << "Balance: " << acc.second.getBalance() << endl << endl;
    }
    cout << "Enter a bank account number: ";
    int accountNum;
    cin >> accountNum;
    auto it = accounts->find(accountNum);
    if (it != accounts->end()) {
        account = it->second;
        cout << "Account selected: " << account.getAccountNum() << endl;
        accountSelected = true;
        Sleep(2000);
    } else {
        cout << "Account not found." << endl;
        cout << "Please try again." << endl;
        Sleep(2000);
        system("cls");
        AccountSelection(account, accounts, accountSelected);
    }
}

void mainMenu (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected, BankManagement bankManagement, bool &running) {
    system("cls");
    cout << "Welcome to the Main Menu" << endl << endl;
    Sleep(2000);
    system("cls");
    if (accountSelected = true) {
        do
        {
            int choiceInMenu;
            system("cls");
            cout << "Main menu" << endl << "Current account: " << account.getAccountNum() 
            << endl << "Current Balance: " << account.getBalance() << endl << endl
            << "1. Deposit" << endl << "2. Withdraw" << endl << "3. Add a new bank account" << endl << "4. Change bank account"
            << endl << "5. Exit program" << endl << endl << "Enter your choice: ";
            cin >> choiceInMenu;
            switch (choiceInMenu) {
            case 1:
                cout << "Enter an amount to deposit: ";
                int amountToDeposit;
                cin >> amountToDeposit;
                account.deposit(amountToDeposit);
                cout << "Your new balance is: " << account.getBalance();
                cin.ignore();
                cin.get();
                break;
            case 2:
                cout << "Enter an amount to withdraw: ";
                int amountToWidthdraw;
                cin >> amountToWidthdraw;
                account.withdraw(amountToWidthdraw);
                cout << "Your new balance is: " << account.getBalance();
                cin.ignore();
                cin.get();
                break;
            case 3:
                cout << "Enter a new bank account number: ";
                int newAccountNum;
                cin >> newAccountNum;
                bankManagement.addBankAccount(newAccountNum);
                accounts->emplace(newAccountNum, BankAccount(newAccountNum));
                cout << "New account added: " << newAccountNum;
                cin.ignore();
                cin.get();
                break;
            case 4:
                AccountSelection(account, accounts, accountSelected);
                break;
            case 5:
                cout << "Exiting program...";
                Sleep(1000);
                running = false;
                break;
            default: 
                cout << "Enter a choice from the list";
                Sleep(2000);
                break;
            }
        } while (running);
    }
    else {
        AccountSelection(account, accounts, accountSelected);
    }
    system("cls");
    cout << "Goodbye!" << endl;
    Sleep(2000);
}