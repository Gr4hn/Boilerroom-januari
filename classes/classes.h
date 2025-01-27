#ifndef CLASSES_H
#define CLASSES_H
#include "basics.h"
#include "functions.h"

using namespace std;

class BankAccount {
    private:
        int balance;
        int accountNum;
        int totalDeposits;
        int totalWithdrawals;
    public:
    BankAccount() {
        this->balance = balance;
        this->accountNum = accountNum;
        this->totalDeposits = 0;
        this->totalWithdrawals = 0;
    } // Har denna o göra med att map behöver en default constructor?

    BankAccount(int balance, int accountNum) {
        this->balance = balance;
        this->accountNum = accountNum;
    }
    BankAccount(int accountNum) {
        this->balance = 0;
        this->accountNum = accountNum;
    }
    
    void deposit(int amount, mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        balance += amount;
    }

    void withdraw(int amount, mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        balance -= amount;
    }

    int getBalance(mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        return balance;
    }

    int getAccountNum(mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        return accountNum;
    }

    int getTotalDeposits(mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        return totalDeposits;
    }

    int getTotalWithdrawals(mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        return totalWithdrawals;
    }

    void logDepoist (int &RB, BankAccount &account, mutex &funcMtx) {
        unique_lock<mutex> lock(funcMtx);
        account.totalDeposits += RB;
        ofstream logFile("Deposit.txt", ios::app);
        if (logFile.is_open()) {
            logFile << "Deposit: " << RB << " to account " << account.getAccountNum(funcMtx) << endl << endl;
            logFile.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }

    void logWithdraw (int &RB, BankAccount &account, mutex &funcMtx, mutex &testMtx) {
        unique_lock<mutex> lock(funcMtx);
        account.totalWithdrawals += RB;
        ofstream logFile("Withdraw.txt", ios::app);
        if (logFile.is_open()) {
            logFile << "Withdrawal: " << RB << " to account " << account.getAccountNum(funcMtx) << endl << endl;
            logFile.close();
        } else {
            cout << "Unable to open file" << endl;
        }
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


#endif