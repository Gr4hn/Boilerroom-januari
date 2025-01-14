#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <ctime>
#include <iomanip>
#include <windows.h>

using namespace std;

mutex mtx;

class BankAccount {
    private:
        int balance;
        int accountNum;
    public:
    BankAccount() {
        this->balance = balance;
        this->accountNum = accountNum;
    } // Har denna o göra med att map behöver en default constructor?

    BankAccount(int balance, int accountNum) {
        this->balance = balance;
        this->accountNum = accountNum;
    }
    BankAccount(int accountNum) {
        this->balance = 0;
        this->accountNum = accountNum;
    }
    
    void deposit(int amount) {
        balance += amount;
    }

    void withdraw(int amount) {
        balance -= amount;
    }

    int getBalance() {
        return balance;
    }

    int getAccountNum() {
        return accountNum;
    }

};

class BankManagement {
    private:

    public:
    map<int, BankAccount> accounts;
    map<int, BankAccount>::iterator it = accounts.begin();

    void addBankAccount (int AccountNuminput) {
        accounts[AccountNuminput] = BankAccount(AccountNuminput);
    }
};

void mainMenu (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected, bool &running);
void Client1 (BankAccount &account, map<int, BankAccount> *accounts);
void Client2 (BankAccount &account, map<int, BankAccount> *accounts);
void AccountSelection (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected);
int randomBalance();

int randomBalance () {
    srand(time(NULL));
    int random = rand() % 1000 + 45;
    return random;
}



/* int randomAccontNumber () {
    int random0 = 0;
    int random1 = 0;
    int random[1];
    srand(time(NULL));
    for (int i = 0; i < 1; i++) {
        random[i] = rand() % 10000 + 45;
        if (random[i] == random[1]) {
            random1 = random[i];
        } else {
            random0 = random[i];
        }
    }

    srand(time(NULL));
    int random1 = rand() % 10000 + 45;
    int random2 = random1 + rand() % 10000 + 45; 
    int first = random1;
    int second;
    do{
        second = random2;
    }while (second == first);

    return {first, second};
    return random1;
} */

void Client1 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 1 is running" << endl;
    cin.ignore();
    cin.get();
    cout << "Current Balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.deposit(randomBalance() + 60);
    cout << "Client 1 has deposited to account: " << account.getAccountNum() << setw(10) << " || " << "\tCurrent balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.withdraw(randomBalance() - 42);
    cout << "Client 1 has withdrawn from account: " << account.getAccountNum() << setw(10) << " || " << "\tCurrent balance: " << account.getBalance() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

/* void Client2 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 2 is running" << endl; 
    cout << "Current Balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.deposit(randomBalance() + 12);
    cout << "Client 2 has deposited to account: " << account.getAccountNum() << setw(10) << " || " << "\tCurrent balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.withdraw(randomBalance() - 50);
    cout << "Client 2 has withdrawn from account: " << account.getAccountNum() << setw(10) << " || " << "\tCurrent balance: " << account.getBalance() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(500));   
} */

/* void Client3 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 3 is running" << endl; 
    cout << "Current Balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.deposit(randomBalance());
    cout << "Client 2 has deposited to account : " << account.getAccountNum() << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.withdraw(randomBalance());
    cout << "Client 2 has withdrawn from account : " << account.getAccountNum() << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));   
} */
/* void Client4 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 4 is running" << endl; 
    cout << "Current Balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.deposit(randomBalance());
    cout << "Client 2 has deposited to account : " <<  account.getAccountNum() << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.withdraw(randomBalance());
    cout << "Client 2 has withdrawn from account : " <<  account.getAccountNum() << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));   
}
 */
/* void Client5 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 5 is running" << endl; 
    cout << "Current Balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.deposit(randomBalance());
    cout << "Client 2 has deposited to account : " << account.getAccountNum() << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.withdraw(randomBalance());
    cout << "Client 2 has withdrawn from account : " <<  account.getAccountNum() << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));   
} */

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





int main() {
    BankAccount account1(1000, 111);
    BankAccount account2(2000, 222);
/*  BankAccount account3(3000, 333);
    BankAccount account4(4000, 444);
    BankAccount account5(5000, 555); */

    
    map<int, BankAccount> accounts;
    accounts[111] = account1;
    accounts[222] = account2;
/*  accounts[3] = account3; // Assign a unique key for account3
    accounts[4] = account4;
    accounts[5] = account5; */

    cout << "Hello, World!" << endl << endl;
    Sleep(2000);
    system("cls");

    BankAccount account;
    BankManagement bankManagement;
    bool accontSelected = false;
    bool running = true;

    AccountSelection(account, &accounts, accontSelected);
    mainMenu(account, &accounts, accontSelected, bankManagement, running);

    
    //Thread 1
     thread t1 ([&account1, &accounts]() {
        mtx.lock();
        cout << "Thread 1 is running" << endl;
        Client1(account1, &accounts);
        mtx.unlock();
    });

    //Thread 2
/*     thread t2 ([&account2, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 2 is running" << endl;
        Client2(account2, &accounts);
        mtx.unlock();
    }); */

/*     thread t3 ([&account3, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 3 is running" << endl;
        Client2(account3, &accounts);
        mtx.unlock();
    });
    thread t4 ([&account4, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 4 is running" << endl;
        Client2(account4, &accounts);
        mtx.unlock();
    });
    thread t5 ([&account5, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 5 is running" << endl;
        Client2(account5, &accounts);
        mtx.unlock();
    }); */

 
    t1.join();
/*  t2.join(); */
/*  t3.join();
    t4.join();
    t5.join(); */


    return 0;
}