#ifndef CLASSES_H
#define CLASSES_H
#include "basics.h"
#include "functions.h"

using namespace std;

// Class to handle bank accounts
class BankAccount {
    private:
        int balance;             // Bankaccount balance   
        int accountNum;   
        int totalDeposits;       // Total deposited amount
        int totalWithdrawals;    //Total withdrawn amount
    public:
    BankAccount() {              // Default constructor
        this->balance = balance;
        this->accountNum = accountNum;
        this->totalDeposits = 0;
        this->totalWithdrawals = 0;

    } 
    
    // Constructor with balance and account number
    BankAccount(int balance, int accountNum) {
        this->balance = balance;
        this->accountNum = accountNum;
        this->totalDeposits = 0;
        this->totalWithdrawals = 0;
    }

    // Constructor with only account number, balance set to 0
    BankAccount(int accountNum) {
        this->balance = 0;
        this->accountNum = accountNum;
    }

    ~BankAccount() {             // Destructor
        cout << "Account " << accountNum << " has been deleted" << endl;
    }
    // Function to deposit money into the account
    void deposit(int amount) {
        cout << "Entered withdraw" << endl;
        balance += amount;
    }

    // Function to withdraw money from the account
    void withdraw(int amount, map<int, BankAccount> &accounts) {
        cout << "Entered withdraw" << endl;
        balance -= amount;
        if (balance < 0) {
            //accounts[accountNum].~BankAccount();
            accounts.erase(accountNum);
            cout << "Account " << accountNum << " has been deleted" << endl;
            return;
        }
        else {
            cout << "Withdrawal successful" << endl;
        }   
        getBalance();
        getTotalWithdrawals();
    }

    // Returns the current balance
    int getBalance() {
        return balance;
    }

    // Returns the account number
    int getAccountNum() {
        return accountNum;
    }


    // Returns the total deposits
    int getTotalDeposits() {
        return totalDeposits;
    }

    // Returns the total withdrawals
    int getTotalWithdrawals() {
        return totalWithdrawals;
    }

    // Logs a deposit to a file
    void logDepoist (int &RB, BankAccount &CustomerID, mutex &funcMtx) {
        totalDeposits += RB;
        ofstream logFile("Deposit.txt", ios::app);
        if (logFile.is_open()) {
            logFile << "Deposit: " << RB << " to account " << getAccountNum() << endl << endl;
            logFile.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }

    // Logs a withdrawal to a file
    void logWithdraw (int &RB, BankAccount &CustomerID, mutex &funcMtx) {
        totalWithdrawals += RB;
        ofstream logFile("Withdraw.txt", ios::app);
        if (logFile.is_open()) {
            logFile << "Withdrawal: " << RB << " to account " << getAccountNum() << endl << endl;
            logFile.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }

};

// Class to manage multiple bank accounts   
class BankManagement {
    private:

    public:
    map<int, BankAccount> accounts;      // A map storing bank accounts with account number as key
    map<int, BankAccount>::iterator it = accounts.begin();    // Iterator to browse accounts

    // Function to add a new bank account
    void addBankAccount (int AccountNuminput) {
        accounts[AccountNuminput] = BankAccount(AccountNuminput);
    }
};


#endif